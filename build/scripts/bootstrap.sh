#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple bootstrap tool to compile any part of the FLL project.
# The dependencies of this script are: bash, basename, cp, dirname, grep, ln, mkdir, rm, sed, and touch.
#
# This script is only designed specifically for bootstrap compiling the FLL project and does not necessarily fully follow the fake (featureless make) build process.

bootstrap_main() {

  local public_name="Simple FLL Bootstrap Script"
  local system_name=bootstrap
  local called_name=$(basename $0)
  local version=0.5.9

  local grab_next=
  local do_color=dark
  local do_help=
  local i=0
  local m=
  local p=
  local t=0

  local c_reset="\\033[0m"
  local c_title="\\033[1;33m"
  local c_error="\\033[1;31m"
  local c_warning="\\033[0;33m"
  local c_highlight="\\033[1;32m"
  local c_notice="\\033[0;01m"
  local c_important="\\033[0;32m"
  local c_subtle="\\033[1;30m"
  local c_prefix="\\"

  local variables=
  local settings_name=settings
  local settings_file=
  local settings_defines=
  local mode=
  local modes=
  local modes_available=
  local operation=
  local operation_failure=
  local path_build=build/
  local path_build_stage=build/stage/
  local path_data=data/
  local path_settings=${path_data}settings/
  local path_sources=sources/
  local path_language=c/
  local path_work=
  local project_built=
  local project_built_shared=
  local project_built_static=
  local project_label=
  local override_path_build=
  local override_path_data=
  local override_path_sources=
  local override_path_work=
  local defines_override=
  local process=
  local verbosity=normal
  local verbose=
  local verbose_common=

  local enable_shared=
  local enable_static=

  if [[ $# -gt 0 ]] ; then
    t=$#

    while [[ $i -lt $t ]] ; do
      let i=$i+1
      p=${!i}

      if [[ $grab_next == "" ]] ; then
        if [[ $p == "-h" || $p == "--help" ]] ; then
          do_help=yes
        elif [[ $p == "+d" || $p == "++dark" ]] ; then
          do_color=dark
          context="+d"
        elif [[ $p == "+l" || $p == "++light" ]] ; then
          do_color=light
          context="+l"
        elif [[ $p == "+n" || $p == "++no_color" ]] ; then
          do_color=none
          context="+n"
        elif [[ $p == "+q" || $p == "++quiet" ]] ; then
          verbosity="quiet"
          verbose=
          verbose_common=
        elif [[ $p == "+N" || $p == "++normal" ]] ; then
          verbosity=
          verbose=
          verbose_common=
        elif [[ $p == "+V" || $p == "++verbose" ]] ; then
          verbosity="verbose"
          verbose="+V"
          verbose_common="-v"
        elif [[ $p == "+D" || $p == "++debug" ]] ; then
          verbosity="debug"
          verbose="+D"
          verbose_common="-v"
        elif [[ $p == "+v" || $p == "++version" ]] ; then
          echo $version
          return
        elif [[ $p == "-d" || $p == "--defines" ]] ; then
          grab_next=defines_override
        elif [[ $p == "-m" || $p == "--mode" ]] ; then
          grab_next="mode"
        elif [[ $p == "-p" || $p == "--process" ]] ; then
          grab_next="process"
        elif [[ $p == "-s" || $p == "--settings" ]] ; then
          grab_next=settings_name
        elif [[ $p == "-b" || $p == "--build" ]] ; then
          grab_next=path_build
        elif [[ $p == "-d" || $p == "--data" ]] ; then
          grab_next=path_data
        elif [[ $p == "-S" || $p == "--sources" ]] ; then
          grab_next=path_sources
        elif [[ $p == "-w" || $p == "--work" ]] ; then
          grab_next=path_work
        elif [[ $p == "--enable-shared" ]] ; then
          enable_shared="yes"
        elif [[ $p == "--disable-shared" ]] ; then
          enable_shared="no"
        elif [[ $p == "--enable-static" ]] ; then
          enable_static="yes"
        elif [[ $p == "--disable-static" ]] ; then
          enable_static="no"
        elif [[ $operation == "" ]] ; then
          operation="$p"
        elif [[ $operation_failure == "" ]] ; then
          operation_failure=fail-multiple
        fi
      else
        if [[ $grab_next == "defines_override" ]] ; then
          defines_override="$p"
        elif [[ $grab_next == "mode" ]] ; then
          modes="$modes$p "
        elif [[ $grab_next == "process" ]] ; then
          process="$p"
        elif [[ $grab_next == "settings_name" ]] ; then
          settings_name="$p"
        elif [[ $grab_next == "path_build" ]] ; then
          path_build=$(echo $p | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_build="y"
        elif [[ $grab_next == "path_data" ]] ; then
          path_data=$(echo $p | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_data="y"
        elif [[ $grab_next == "path_sources" ]] ; then
          path_sources=$(echo $p | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_sources="y"
        elif [[ $grab_next == "path_work" ]] ; then
          path_work=$(echo $p | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_work="y"
        fi

        grab_next=
      fi
    done

    p=
  fi

  settings_file="${path_data}build/$settings_name"
  settings_defines="${path_data}build/defines"
  path_settings="${path_data}settings/"
  path_build_stage="${path_build}stage/"

  bootstrap_handle_colors

  if [[ $do_help == "yes" ]] ; then
    bootstrap_help
    bootstrap_cleanup

    return 0
  fi

  bootstrap_load_settings

  # FSS and Featurless Make supports more flexible mode names, but for the purpose of this bootstrap script and avoiding potential problems, keep it simple.
  if [[ $modes != "" ]] ; then
    for mode in $modes ; do
      if [[ $(echo "$mode" | grep -s -o "[^_[:alnum:]+-]") != "" ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: The mode $c_notice$mode$c_error includes invalid characters, only alphanumeric, underscore, minus, and plus are allowed.$c_reset"
        fi

        bootstrap_cleanup

        return 1
      fi
    done
  fi

  if [[ $? -ne 0 ]] ; then
    bootstrap_cleanup

    return 1
  fi

  bootstrap_load_settings_mode

  if [[ $? -ne 0 ]] ; then
    bootstrap_cleanup

    return 1
  fi

  bootstrap_load_settings_has

  if [[ $? -ne 0 ]] ; then
    bootstrap_cleanup

    return 1
  fi

  project_built="${path_build_stage}${variables[$(bootstrap_id build_name)]}"
  if [[ $process != "" ]] ; then
    project_built="${project_built}-$process"
  fi

  project_built_shared="${project_built}.shared"
  project_built_static="${project_built}.static"

  if [[ $modes_available == "" ]] ; then
    if [[ $modes != "" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The mode(s) $c_notice$modes$c_error are not a valid modes, there are no available modes.$c_error$c_reset"
      fi

      bootstrap_cleanup

      return 1
    fi
  else
    let i=0
    for m in $modes_available ; do

      for mode in $modes ; do

        if [[ "$mode" == "$m" ]] ; then
          let i=1

          break
        fi
      done

      if [[ $i -eq 1 ]] ; then break ; fi
    done

    if [[ $i -eq 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The mode(s) $c_notice$modes$c_error are not valid modes, they must be one of: $c_notice$modes_available$c_error.$c_reset"
      fi

      bootstrap_cleanup

      return 1
    fi
  fi

  if [[ ${variables[$(bootstrap_id build_name)]} == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The required setting '${c_notice}build_name$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${variables[$(bootstrap_id version_major)]} == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The required setting '${c_notice}version_major$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${variables[$(bootstrap_id version_minor)]} == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The required setting '${c_notice}version_minor$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${variables[$(bootstrap_id version_micro)]} == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The required setting '${c_notice}version_micro$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ $path_data == "" || ! -d $path_data ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The data directory $c_notice$path_data$c_error is not a valid directory.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ $path_sources == "" || ! -d $path_sources ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The sources directory $c_notice$path_sources$c_error is not a valid directory.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ $path_work != "" && ! -d $path_work ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The work directory $c_notice$path_work$c_error is not a valid directory.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ $defines_override != "" && $(echo "$defines_override" | grep -s -o "[^_[:alnum:][:space:]]") != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The defines override $c_notice$defines_override$c_error includes invalid characters, only alphanumeric, whitespace, and underscore are allowed.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  project_label="${variables[$(bootstrap_id build_name)]}"

  if [[ "${variables[$(bootstrap_id version_major)]}" != "" ]] ; then
    project_label="${project_label}-${variables[$(bootstrap_id version_major)]}"

    if [[ "${variables[$(bootstrap_id version_minor)]}" != "" ]] ; then
      project_label="${project_label}.${variables[$(bootstrap_id version_minor)]}"

      if [[ "${variables[$(bootstrap_id version_micro)]}" != "" ]] ; then
        project_label="${project_label}.${variables[$(bootstrap_id version_micro)]}"
      fi
    fi
  fi

  if [[ $operation_failure == "fail-multiple" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Only one operation may be specified at a time.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  elif [[ $operation == "build" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Building:${c_reset} $c_notice$project_label${c_highlight}.$c_reset"
    fi

    if [[ ! -f ${project_built}.prepared ]] ; then
      bootstrap_prepare_build

      if [[ $? -ne 0 ]] ; then
        bootstrap_cleanup

        return 1
      fi
    fi

    bootstrap_operation_build

    if [[ $? -ne 0 ]] ; then
      bootstrap_cleanup

      return 1
    fi
  elif [[ $operation == "clean" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Cleaning Project:${c_reset} $c_notice$project_label${c_highlight}.$c_reset"
    fi

    bootstrap_operation_clean
  elif [[ $operation == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: No operation was given.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  else
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The operation $c_notice$operation$c_error was not recognized.$c_reset"
    fi

    bootstrap_cleanup

    return 1
  fi

  bootstrap_cleanup

  return 0
}

bootstrap_handle_colors() {

  if [[ $do_color == "light" ]] ; then
    c_error="\\033[1;31m"
    c_warning="\\033[0;31m"
    c_title="\\033[1;34m"
    c_highlight="\\033[0;34m"
    c_notice="\\033[0;01m"
    c_important="\\033[0;35m"
  elif [[ $do_color == "none" ]] ; then
    c_reset=
    c_title=
    c_error=
    c_warning=
    c_highlight=
    c_notice=
    c_important=
    c_subtle=
    c_prefix=
  fi
}

bootstrap_help() {

  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset $c_notice[${c_reset} options $c_notice]$c_reset $c_notice[${c_reset} operation $c_notice]$c_reset"
  echo -e " ${c_important}build${c_reset}  Build or compile the code based on build settings file."
  echo -e " ${c_important}clean${c_reset}  Delete all build files."
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen."
  echo -e " +${c_important}d$c_reset, ++${c_important}dark$c_reset      Use color modes that show up better on dark backgrounds."
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds."
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color."
  echo -e " +${c_important}q$c_reset, ++${c_important}quiet$c_reset     Decrease verbosity, silencing most output."
  echo -e " +${c_important}N$c_reset, ++${c_important}normal$c_reset    Set verbosity to normal."
  echo -e " +${c_important}V$c_reset, ++${c_important}verbose$c_reset   Increase verbosity beyond normal output."
  echo -e " +${c_important}D$c_reset, ++${c_important}debug$c_reset     Enable debugging, significantly increasing verbosity beyond normal output."
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program."
  echo
  echo -e "${c_highlight}Bootstrap Options:$c_reset"
  echo -e " -${c_important}d$c_reset, --${c_important}defines${c_reset}    Override custom defines with these defines."
  echo -e " -${c_important}m$c_reset, --${c_important}mode${c_reset}       Use this mode when processing the build settings."
  echo -e " -${c_important}p$c_reset, --${c_important}process${c_reset}    Process name for storing build states."
  echo -e " -${c_important}s$c_reset, --${c_important}settings${c_reset}   Use this settings file, from within the source settings directory."
  echo
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}      Specify a custom build directory."
  echo -e " -${c_important}D$c_reset, --${c_important}data${c_reset}       Specify a custom path to the data files."
  echo -e " -${c_important}S$c_reset, --${c_important}sources${c_reset}    Specify a custom path to the source files."
  echo -e " -${c_important}w$c_reset, --${c_important}work${c_reset}       Use includes/libraries/programs from this directory instead of system."
  echo
  echo -e "${c_highlight}Special Options:$c_reset"
  echo -e " --${c_important}enable-shared${c_reset}   Forcibly do build shared files."
  echo -e " --${c_important}disable-shared${c_reset}  Forcibly do not build shared files."
  echo -e " --${c_important}enable-static${c_reset}   Forcibly do build static files."
  echo -e " --${c_important}disable-static${c_reset}  Forcibly do not build static files."
  echo
}

bootstrap_id() {

  case $1 in
    "build_compiler") echo -n 0;;
    "build_indexer") echo -n 1;;
    "build_indexer_arguments") echo -n 2;;
    "build_language") echo -n 3;;
    "build_libraries") echo -n 4;;
    "build_libraries_shared") echo -n 5;;
    "build_libraries_static") echo -n 6;;
    "build_name") echo -n 7;;
    "build_objects_library") echo -n 8;;
    "build_objects_library_shared") echo -n 9;;
    "build_objects_library_static") echo -n 10;;
    "build_objects_program") echo -n 11;;
    "build_objects_program_shared") echo -n 12;;
    "build_objects_program_static") echo -n 13;;
    "build_script") echo -n 14;;
    "build_shared") echo -n 15;;
    "build_sources_headers") echo -n 16;;
    "build_sources_headers_shared") echo -n 17;;
    "build_sources_headers_static") echo -n 18;;
    "build_sources_library") echo -n 19;;
    "build_sources_library_shared") echo -n 20;;
    "build_sources_library_static") echo -n 21;;
    "build_sources_object") echo -n 22;;
    "build_sources_object_shared") echo -n 23;;
    "build_sources_object_static") echo -n 24;;
    "build_sources_program") echo -n 25;;
    "build_sources_program_shared") echo -n 26;;
    "build_sources_program_static") echo -n 27;;
    "build_sources_script") echo -n 28;;
    "build_sources_setting") echo -n 29;;
    "build_static") echo -n 30;;
    "defines") echo -n 31;;
    "defines_library") echo -n 32;;
    "defines_library_shared") echo -n 33;;
    "defines_library_static") echo -n 34;;
    "defines_object") echo -n 35;;
    "defines_object_shared") echo -n 36;;
    "defines_object_static") echo -n 37;;
    "defines_program") echo -n 38;;
    "defines_program_shared") echo -n 39;;
    "defines_program_static") echo -n 40;;
    "defines_shared") echo -n 41;;
    "defines_static") echo -n 42;;
    "environment") echo -n 43;;
    "flags") echo -n 44;;
    "flags_library") echo -n 45;;
    "flags_library_shared") echo -n 46;;
    "flags_library_static") echo -n 47;;
    "flags_object") echo -n 48;;
    "flags_object_shared") echo -n 49;;
    "flags_object_static") echo -n 50;;
    "flags_program") echo -n 51;;
    "flags_program_shared") echo -n 52;;
    "flags_program_static") echo -n 53;;
    "flags_shared") echo -n 54;;
    "flags_static") echo -n 55;;
    "has_path_standard") echo -n 56;;
    "modes") echo -n 57;;
    "modes_default") echo -n 58;;
    "path_headers") echo -n 59;;
    "path_language") echo -n 60;;
    "path_library_script") echo -n 61;;
    "path_library_shared") echo -n 62;;
    "path_library_static") echo -n 63;;
    "path_object_script") echo -n 64;;
    "path_object_shared") echo -n 65;;
    "path_object_static") echo -n 66;;
    "path_program_script") echo -n 67;;
    "path_program_shared") echo -n 68;;
    "path_program_static") echo -n 69;;
    "path_sources") echo -n 70;;
    "path_sources_object") echo -n 71;;
    "preserve_path_headers") echo -n 72;;
    "process_post") echo -n 73;;
    "process_pre") echo -n 74;;
    "search_exclusive") echo -n 75;;
    "search_shared") echo -n 76;;
    "search_static") echo -n 77;;
    "version_file") echo -n 78;;
    "version_major") echo -n 79;;
    "version_major_prefix") echo -n 80;;
    "version_micro") echo -n 81;;
    "version_micro_prefix") echo -n 82;;
    "version_minor") echo -n 83;;
    "version_minor_prefix") echo -n 84;;
    "version_nano") echo -n 85;;
    "version_nano_prefix") echo -n 86;;
    "version_target") echo -n 87;;

    "build_compiler-mode") echo -n 88;;
    "build_indexer-mode") echo -n 89;;
    "build_indexer_arguments-mode") echo -n 90;;
    "build_language-mode") echo -n 91;;
    "build_libraries-mode") echo -n 92;;
    "build_libraries_shared-mode") echo -n 93;;
    "build_libraries_static-mode") echo -n 94;;
    "build_name-mode") echo -n 95;;
    "build_objects_library-mode") echo -n 96;;
    "build_objects_library_shared-mode") echo -n 97;;
    "build_objects_library_static-mode") echo -n 98;;
    "build_objects_program-mode") echo -n 99;;
    "build_objects_program_shared-mode") echo -n 100;;
    "build_objects_program_static-mode") echo -n 101;;
    "build_script-mode") echo -n 102;;
    "build_shared-mode") echo -n 103;;
    "build_sources_headers-mode") echo -n 104;;
    "build_sources_headers_shared-mode") echo -n 105;;
    "build_sources_headers_static-mode") echo -n 106;;
    "build_sources_library-mode") echo -n 107;;
    "build_sources_library_shared-mode") echo -n 108;;
    "build_sources_library_static-mode") echo -n 109;;
    "build_sources_object-mode") echo -n 110;;
    "build_sources_object_shared-mode") echo -n 111;;
    "build_sources_object_static-mode") echo -n 112;;
    "build_sources_program-mode") echo -n 113;;
    "build_sources_program_shared-mode") echo -n 114;;
    "build_sources_program_static-mode") echo -n 115;;
    "build_sources_script-mode") echo -n 116;;
    "build_sources_setting-mode") echo -n 117;;
    "build_static-mode") echo -n 118;;
    "defines-mode") echo -n 119;;
    "defines_library-mode") echo -n 120;;
    "defines_library_shared-mode") echo -n 121;;
    "defines_library_static-mode") echo -n 122;;
    "defines_object-mode") echo -n 123;;
    "defines_object_shared-mode") echo -n 124;;
    "defines_object_static-mode") echo -n 125;;
    "defines_program-mode") echo -n 126;;
    "defines_program_shared-mode") echo -n 127;;
    "defines_program_static-mode") echo -n 128;;
    "defines_shared-mode") echo -n 129;;
    "defines_static-mode") echo -n 130;;
    "environment-mode") echo -n 131;;
    "flags-mode") echo -n 132;;
    "flags_library-mode") echo -n 133;;
    "flags_library_shared-mode") echo -n 134;;
    "flags_library_static-mode") echo -n 135;;
    "flags_object-mode") echo -n 136;;
    "flags_object_shared-mode") echo -n 137;;
    "flags_object_static-mode") echo -n 138;;
    "flags_program-mode") echo -n 139;;
    "flags_program_shared-mode") echo -n 140;;
    "flags_program_static-mode") echo -n 141;;
    "flags_shared-mode") echo -n 142;;
    "flags_static-mode") echo -n 143;;
    "has_path_standard-mode") echo -n 144;;
    "path_headers-mode") echo -n 145;;
    "path_language-mode") echo -n 146;;
    "path_library_script-mode") echo -n 147;;
    "path_library_shared-mode") echo -n 148;;
    "path_library_static-mode") echo -n 149;;
    "path_object_script-mode") echo -n 150;;
    "path_object_shared-mode") echo -n 151;;
    "path_object_static-mode") echo -n 152;;
    "path_program_script-mode") echo -n 153;;
    "path_program_shared-mode") echo -n 154;;
    "path_program_static-mode") echo -n 155;;
    "path_sources-mode") echo -n 156;;
    "path_sources_object-mode") echo -n 157;;
    "preserve_path_headers-mode") echo -n 158;;
    "process_post-mode") echo -n 159;;
    "process_pre-mode") echo -n 160;;
    "search_exclusive-mode") echo -n 161;;
    "search_shared-mode") echo -n 162;;
    "search_static-mode") echo -n 163;;
    "version_file-mode") echo -n 164;;
    "version_major-mode") echo -n 165;;
    "version_major_prefix-mode") echo -n 166;;
    "version_micro-mode") echo -n 167;;
    "version_micro_prefix-mode") echo -n 168;;
    "version_minor-mode") echo -n 169;;
    "version_minor_prefix-mode") echo -n 170;;
    "version_nano-mode") echo -n 171;;
    "version_nano_prefix-mode") echo -n 172;;
    "version_target-mode") echo -n 173;;

    "has-has_path_standard") echo -n 175;;
    "has-path_library_script") echo -n 176;;
    "has-path_library_shared") echo -n 177;;
    "has-path_library_static") echo -n 178;;
    "has-path_object_script") echo -n 179;;
    "has-path_object_shared") echo -n 180;;
    "has-path_object_static") echo -n 181;;
    "has-path_program_script") echo -n 182;;
    "has-path_program_shared") echo -n 183;;
    "has-path_program_static") echo -n 184;;
    "has-path_sources") echo -n 185;;
    "has-path_sources_object") echo -n 186;;
    "has-search_shared") echo -n 187;;
    "has-version_major_prefix") echo -n 188;;
    "has-version_micro_prefix") echo -n 189;;
    "has-version_minor_prefix") echo -n 190;;
    "has-version_nano_prefix") echo -n 191;;
  esac
}

bootstrap_load_settings() {

  local -i failure=0
  local i=
  local key=
  local value=

  if [[ ! -d ${path_data}build/ ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: No build settings directory '$c_notice${path_data}build/$c_error' could not be found or is not a valid directory.$c_reset"
    fi

    let failure=1
  elif [[ ! -f $settings_file ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: No settings file $c_notice$settings_file$c_error could not be found or is not a valid file.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 1 ]] ; then
    return 1
  fi

  # Get available modes.
  if [[ $modes_available == "" ]] ; then
    modes_available=$(grep -s -o "^[[:space:]]*modes[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*modes\>||" -e 's|^[[:space:]]*||')
  fi

  # Get default modes.
  modes_default=$(grep -s -o "^[[:space:]]*modes_default[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*modes_default\>||" -e 's|^[[:space:]]*||')

  # Use default modes if no mode is explicitly provided.
  if [[ $modes == "" ]] ; then
    modes=$modes_default
  fi

  # Single value Objects.
  for i in build_compiler build_indexer build_language build_name build_script build_shared build_sources_object build_sources_object_shared build_sources_object_static build_static has_path_standard path_headers path_language path_library_script path_library_shared path_library_static path_object_script path_object_shared path_object_static path_program_script path_program_shared path_program_static path_sources path_sources_object preserve_path_headers process_post process_pre search_exclusive search_shared search_static version_file version_major version_major_prefix version_micro version_micro_prefix version_minor version_minor_prefix version_nano version_nano_prefix version_target ; do
    key=$(bootstrap_id $i)

    if [[ $key == "" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_warning}WARNING: Failed to find index for '$c_notice$i$c_error' when calling ${c_notice}bootstrap_id()$c_error.$c_reset"
      fi
    else
      value=$(grep -s -o "^[[:space:]]*$i[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')

      if [[ $value != "" ]] ; then
        variables[$key]="$value"
      fi
    fi
  done

  # Multi value Objects.
  for i in build_indexer_arguments build_libraries build_libraries_shared build_libraries_static build_objects_library build_objects_library_shared build_objects_library_static build_objects_program build_objects_program_shared build_objects_program_static build_sources_headers build_sources_headers_shared build_sources_headers_static build_sources_library build_sources_library_shared build_sources_library_static build_sources_program build_sources_program_shared build_sources_program_static build_sources_script build_sources_setting defines defines_library defines_library_shared defines_library_static defines_object defines_object_shared defines_object_static defines_program defines_program_shared defines_program_static defines_shared defines_static environment flags flags_library flags_library_shared flags_library_static flags_object flags_object_shared flags_object_static flags_program flags_program_shared flags_program_static flags_shared flags_static ; do
    key=$(bootstrap_id $i)

    if [[ $key == "" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_warning}WARNING: Failed to find index for '$c_notice$i$c_error' when calling ${c_notice}bootstrap_id()$c_error.$c_reset"
      fi
    else
      value=$(grep -s -o "^[[:space:]]*$i[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')

      if [[ $value != "" ]] ; then
        variables[$key]="$value"
      fi
    fi
  done
}

bootstrap_load_settings_mode() {

  local i=
  local key=
  local m=
  local value=

  for m in $modes ; do

    # Single value Objects.
    for i in build_compiler build_indexer build_language build_name build_script build_shared build_sources_object build_sources_object_shared build_sources_object_static build_static has_path_standard path_headers path_language path_library_script path_library_shared path_library_static path_object_script path_object_shared path_object_static path_program_script path_program_shared path_program_static path_sources path_sources_object preserve_path_headers process_post process_pre search_exclusive search_shared search_static version_file version_major version_major_prefix version_micro version_micro_prefix version_minor version_minor_prefix version_nano version_nano_prefix version_target ; do
      key=$(bootstrap_id $i-mode)

      if [[ $key == "" ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_warning}WARNING: Failed to find index for '$c_notice$i-$m$c_error' when calling ${c_notice}bootstrap_id()$c_error.$c_reset"
        fi
      else
        value=$(grep -s -o "^[[:space:]]*$i-$m[[:space:]].*\$" $settings_file | sed -e "H;/$i-$m/h;\$!d;x" | sed -e "s|^[[:space:]]*$i-$m\>||" -e 's|^[[:space:]]*||')

        if [[ $value != "" ]] ; then
          variables[$key]="$value"
        fi
      fi
    done

    # Multi value Objects.
    for i in build_indexer_arguments build_libraries build_libraries_shared build_libraries_static build_objects_library build_objects_library_shared build_objects_library_static build_objects_program build_objects_program_shared build_objects_program_static build_sources_headers build_sources_headers_shared build_sources_headers_static build_sources_library build_sources_library_shared build_sources_library_static build_sources_program build_sources_program_shared build_sources_program_static build_sources_script build_sources_setting defines defines_library defines_library_shared defines_library_static defines_object defines_object_shared defines_object_static defines_program defines_program_shared defines_program_static defines_shared defines_static environment flags flags_library flags_library_shared flags_library_static flags_object flags_object_shared flags_object_static flags_program flags_program_shared flags_program_static flags_shared flags_static ; do
      key=$(bootstrap_id $i-mode)

      if [[ $key == "" ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_warning}WARNING: Failed to find index for '$c_notice$i-$m$c_warning' when calling ${c_notice}bootstrap_id()$c_warning.$c_reset"
        fi
      else
        value=$(grep -s -o "^[[:space:]]*$i-$m[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*$i-$m\>||" -e 's|^[[:space:]]*||')

        if [[ $value != "" ]] ; then
          variables[$key]="$value"
        fi
      fi
    done
  done
}

bootstrap_load_settings_has() {

  local i=
  local m=

  for i in build_compiler build_indexer build_shared has_path_standard path_library_script path_library_shared path_library_static path_object_script path_object_shared path_object_static path_program_script path_program_shared path_program_static path_sources path_sources_object search_shared version_major_prefix version_minor_prefix version_micro_prefix version_nano_prefix ; do
    if [[ $(grep -s -o "^[[:space:]]*$i\>" $settings_file | sed -e "s|^[[:space:]]*||") ]] ; then
      variables[$(bootstrap_id has-$i)]="yes"
    else
      variables[$(bootstrap_id has-$i)]="no"
    fi
  done

  for m in $modes ; do
    for i in build_compiler build_indexer build_shared has_path_standard path_library_script path_library_shared path_library_static path_object_script path_object_shared path_object_static path_program_script path_program_shared path_program_static path_sources path_sources_object search_shared version_major_prefix version_minor_prefix version_micro_prefix version_nano_prefix ; do
      if [[ $(grep -s -o "^[[:space:]]*$i-$m\>" $settings_file | sed -e "s|^[[:space:]]*||") ]] ; then
        variables[$(bootstrap_id has-$i-mode)]="yes"
      else
        variables[$(bootstrap_id has-$i-mode)]="no"
      fi
    done
  done
}

bootstrap_prepare_build() {

  local -i failure=0
  local alt=$1
  local i=

  mkdir $verbose -p ${path_build}{documents,includes,libraries/{script,shared,static},objects/{script,shared,static},programs/{script,shared,static},settings,stage} || failure=1

  if [[ $failure -eq 1 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_warning}WARNING: Failed to create build directories in '$c_notice$path_build$c_errror'.$c_reset"
    fi

    return $failure
  fi

  if [[ ${variables[$(bootstrap_id path_headers-mode)]} != "" ]] ; then
    mkdir $verbose -p ${path_build}includes/${variables[$(bootstrap_id path_headers-mode)]} || failure=1
  elif [[ ${variables[$(bootstrap_id path_headers)]} != "" ]] ; then
    mkdir $verbose -p ${path_build}includes/${variables[$(bootstrap_id path_headers)]} || failure=1
  fi

  if [[ $failure -eq 1 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_warning}WARNING: Failed to create $c_noticepath_heades$c_error build directories in '$c_notice$path_build$c_errror'.$c_reset"
    fi

    return $failure
  fi

  touch ${project_built}.prepared
}

bootstrap_operation_build() {

  local -i failure=0
  local i=
  local n=
  local version_file=
  local version_target=
  local alt=$1
  local directory=

  local build_compiler=${variables[$(bootstrap_id build_compiler)]}
  local build_indexer=${variables[$(bootstrap_id build_indexer)]}
  local build_indexer_arguments=${variables[$(bootstrap_id build_indexer_arguments)]}
  local build_name=${variables[$(bootstrap_id build_name)]}
  local build_shared=${variables[$(bootstrap_id build_shared)]}
  local build_static=${variables[$(bootstrap_id build_static)]}
  local defines=${variables[$(bootstrap_id defines)]}
  local defines_library=${variables[$(bootstrap_id defines_library)]}
  local defines_library_shared=${variables[$(bootstrap_id defines_library_shared)]}
  local defines_library_static=${variables[$(bootstrap_id defines_library_static)]}
  local defines_object=${variables[$(bootstrap_id defines_object)]}
  local defines_object_shared=${variables[$(bootstrap_id defines_object_shared)]}
  local defines_object_static=${variables[$(bootstrap_id defines_object_static)]}
  local defines_program=${variables[$(bootstrap_id defines_program)]}
  local defines_program_shared=${variables[$(bootstrap_id defines_program_shared)]}
  local defines_program_static=${variables[$(bootstrap_id defines_program_static)]}
  local defines_shared=${variables[$(bootstrap_id defines_shared)]}
  local defines_static=${variables[$(bootstrap_id defines_static)]}
  local flags=${variables[$(bootstrap_id flags)]}
  local flags_library=${variables[$(bootstrap_id flags_library)]}
  local flags_library_shared=${variables[$(bootstrap_id flags_library_shared)]}
  local flags_library_static=${variables[$(bootstrap_id flags_library_static)]}
  local flags_object=${variables[$(bootstrap_id flags_object)]}
  local flags_object_shared=${variables[$(bootstrap_id flags_object_shared)]}
  local flags_object_static=${variables[$(bootstrap_id flags_object_static)]}
  local flags_program=${variables[$(bootstrap_id flags_program)]}
  local flags_program_shared=${variables[$(bootstrap_id flags_program_shared)]}
  local flags_program_static=${variables[$(bootstrap_id flags_program_static)]}
  local flags_shared=${variables[$(bootstrap_id flags_shared)]}
  local flags_static=${variables[$(bootstrap_id flags_static)]}
  local libraries=${variables[$(bootstrap_id build_libraries)]}
  local libraries_shared=${variables[$(bootstrap_id build_libraries_shared)]}
  local libraries_static=${variables[$(bootstrap_id build_libraries_static)]}
  local links=
  local objects_library=${variables[$(bootstrap_id build_objects_library)]}
  local objects_library_shared=${variables[$(bootstrap_id build_objects_library_shared)]}
  local objects_library_static=${variables[$(bootstrap_id build_objects_library_static)]}
  local objects_program=${variables[$(bootstrap_id build_objects_program)]}
  local objects_program_shared=${variables[$(bootstrap_id build_objects_program_shared)]}
  local objects_program_static=${variables[$(bootstrap_id build_objects_program_static)]}
  local path_headers=${variables[$(bootstrap_id path_headers)]}
  local preserve_path_headers=${variables[$(bootstrap_id preserve_path_headers)]}
  local path_library_script=${variables[$(bootstrap_id path_library_script)]}
  local path_library_shared=${variables[$(bootstrap_id path_library_shared)]}
  local path_library_static=${variables[$(bootstrap_id path_library_static)]}
  local path_object_script=${variables[$(bootstrap_id path_object_script)]}
  local path_object_shared=${variables[$(bootstrap_id path_object_shared)]}
  local path_object_static=${variables[$(bootstrap_id path_object_static)]}
  local path_program_script=${variables[$(bootstrap_id path_program_script)]}
  local path_program_shared=${variables[$(bootstrap_id path_program_shared)]}
  local path_program_static=${variables[$(bootstrap_id path_program_static)]}
  local has_path_standard=${variables[$(bootstrap_id has_path_standard)]}
  local search_exclusive=${variables[$(bootstrap_id search_exclusive)]}
  local search_shared=${variables[$(bootstrap_id search_shared)]}
  local search_static=${variables[$(bootstrap_id search_static)]}
  local sources_headers=${variables[$(bootstrap_id build_sources_headers)]}
  local sources_library=${variables[$(bootstrap_id build_sources_library)]}
  local sources_library_shared=${variables[$(bootstrap_id build_sources_library_shared)]}
  local sources_library_static=${variables[$(bootstrap_id build_sources_library_static)]}
  local sources_object=${variables[$(bootstrap_id build_sources_object)]}
  local sources_object_shared=${variables[$(bootstrap_id build_sources_object_shared)]}
  local sources_object_static=${variables[$(bootstrap_id build_sources_object_static)]}
  local sources_program=${variables[$(bootstrap_id build_sources_program)]}
  local sources_program_shared=${variables[$(bootstrap_id build_sources_program_shared)]}
  local sources_program_static=${variables[$(bootstrap_id build_sources_program_static)]}
  local sources_script=${variables[$(bootstrap_id build_sources_script)]}
  local sources_setting=${variables[$(bootstrap_id build_sources_setting)]}
  local sources=
  local version_file_value=${variables[$(bootstrap_id version_file)]}
  local version_major=${variables[$(bootstrap_id version_major)]}
  local version_major_prefix=${variables[$(bootstrap_id version_major_prefix)]}
  local version_minor=${variables[$(bootstrap_id version_minor)]}
  local version_minor_prefix=${variables[$(bootstrap_id version_minor_prefix)]}
  local version_micro=${variables[$(bootstrap_id version_micro)]}
  local version_micro_prefix=${variables[$(bootstrap_id version_micro_prefix)]}
  local version_nano=${variables[$(bootstrap_id version_nano)]}
  local version_nano_prefix=${variables[$(bootstrap_id version_nano_prefix)]}
  local version_target_value=${variables[$(bootstrap_id version_target)]}

  bootstrap_operation_build_prepare_defaults

  bootstrap_operation_build_prepare_versions

  bootstrap_operation_build_prepare_shared_static

  bootstrap_operation_build_prepare_paths

  bootstrap_operation_build_prepare_flags

  bootstrap_operation_build_prepare_defines

  bootstrap_operation_build_prepare_libraries

  bootstrap_operation_build_prepare_objects

  bootstrap_operation_build_prepare_programs

  bootstrap_operation_build_prepare_settings

  bootstrap_operation_build_prepare_headers

  bootstrap_operation_build_prepare_remaining

  if [[ $build_shared == "yes" && -f ${project_built_shared}.built || $build_static == "yes" && -f ${project_built_static}.built ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_warning}WARNING: This project has already been built.$c_reset"
    fi

    return 0
  fi

  local arguments_include="-I${path_build}includes/"
  local arguments_shared="-L${path_build}libraries/$path_library_shared"
  local arguments_static="-L${path_build}libraries/$path_library_static"

  if [[ $path_work != "" ]] ; then
    arguments_include="$arguments_include -I${path_work}includes/"
    arguments_shared="$arguments_shared -L${path_work}libraries/$path_library_shared"
    arguments_static="$arguments_static -L${path_work}libraries/$path_library_static"
  fi

  bootstrap_operation_build_validate_paths

  bootstrap_operation_build_validate_shared_static

  bootstrap_operation_build_validate_sources

  bootstrap_operation_build_validate_search

  bootstrap_operation_build_validate_build

  if [[ $failure -eq 1 ]] ; then
    return 1
  fi

  if [[ $sources_setting != "" ]] ; then
    for i in $sources_setting ; do
      directory=$(dirname $i)

      if [[ $directory == "." ]] ; then
        cp $verbose -R $path_settings$i ${path_build}settings/ || failure=1
      else
        mkdir $verbose -p ${path_build}settings/$directory || failure=1

        if [[ $failure -eq 0 ]] ; then
          cp $verbose -R $path_settings$i ${path_build}settings/${directory}/ || failure=1
        fi
      fi
    done
  fi

  if [[ $failure -eq 0 && $sources_headers != "" ]] ; then
    if [[ $preserve_path_headers == "yes" ]] ; then
      for i in $sources_headers ; do
        directory=$(dirname $i)

        if [[ $directory == "." ]] ; then
          cp $verbose -f $path_sources$path_language$i ${path_build}includes/$path_headers || failure=1
        else
          if [[ ! -d ${path_build}includes/$path_headers$directory ]] ; then
            mkdir $verbose -p ${path_build}includes/$path_headers$directory || failure=1
          fi

          if [[ $failure -eq 0 ]] ; then
            cp $verbose -f $path_sources$path_language$i ${path_build}includes/$path_headers$i || failure=1
          fi
        fi
      done
    else
      for i in $sources_headers ; do
        cp $verbose -f $path_sources$path_language$i ${path_build}includes/$path_headers || failure=1
      done
    fi
  fi

  if [[ $failure -eq 0 && $build_shared == "yes" && ! -f ${project_built_shared}.built ]] ; then
    if [[ $sources_object != "" || $sources_object_shared != "" ]] ; then
      sources=
      let count=0

      # Sources object only allows for a single value.
      if [[ $sources_object_shared != "" ]] ; then
        for i in $sources_object_shared ; do
          let count++
        done

        if [[ $count -gt 1 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object_shared$c_warning' found, only using the first one found is going to be used.$c_reset"
          fi
        fi

        for i in $sources_object_shared ; do
          sources="$path_sources_object$path_language$i "
          break
        done
      else
        for i in $sources_object ; do
          let count++
        done

        if [[ $count -gt 1 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object$c_warning' found, only using the first one found is going to be used.$c_reset"
          fi
        fi

        for i in $sources_object ; do
          sources="$path_sources_object$path_language$i "
          break
        done
      fi

      if [[ $verbosity == "verbose" ]] ; then
        echo $build_compiler $sources -c -o ${path_build}objects/$path_object_shared$build_name.o $arguments_shared $arguments_include $libraries $libraries_shared $flags $flags_shared $flags_object $flags_object_shared $defines $defines_shared $defines_object $defines_object_shared
      fi

      $build_compiler $sources -c -o ${path_build}objects/$path_object_shared$build_name.o $arguments_shared $arguments_include $libraries $libraries_shared $flags $flags_shared $flags_object $flags_object_shared $defines $defines_shared $defines_object $defines_object_shared || failure=1
    fi

    if [[ $sources_library != "" || $sources_library_shared != "" ]] ; then
      sources=

      if [[ $objects_library != "" || $objects_library_shared != "" ]] ; then
        for i in $objects_library $objects_library_shared ; do
          sources="$sources${path_build}objects/${path_object_shared}$i "
        done
      fi

      for i in $sources_library $sources_library_shared ; do
        sources="$sources$path_sources$path_language$i "
      done

      if [[ $verbosity == "verbose" ]] ; then
        echo $build_compiler $sources -shared -Wl,-soname,lib$build_name.so$version_target -o ${path_build}libraries/${path_library_shared}lib$build_name.so$version_file $arguments_shared $arguments_include $libraries $libraries_shared $flags $flags_shared $flags_library $flags_library_shared $defines $defines_shared $defines_library $defines_library_shared
      fi

      $build_compiler $sources -shared -Wl,-soname,lib$build_name.so$version_target -o ${path_build}libraries/${path_library_shared}lib$build_name.so$version_file $arguments_shared $arguments_include $libraries $libraries_shared $flags $flags_shared $flags_library $flags_library_shared $defines $defines_shared $defines_library $defines_library_shared || failure=1

      if [[ $failure -eq 0 ]] ; then
        if [[ $version_file_value != "major" ]] ; then
          if [[ $version_file_value == "minor" ]] ; then
            ln $verbose -sf lib$build_name.so$version_file ${path_build}libraries/${path_library_shared}lib$build_name.so$version_major_prefix$version_major || failure=1
          else
            ln $verbose -sf lib$build_name.so$version_major_prefix$version_major$version_minor_prefix$version_minor ${path_build}libraries/${path_library_shared}lib$build_name.so$version_major_prefix$version_major || failure=1

            if [[ $failure -eq 0 ]] ; then
              if [[ $version_file_value == "micro" ]] ; then
                ln $verbose -sf lib$build_name.so$version_file ${path_build}libraries/${path_library_shared}lib$build_name.so$version_major_prefix$version_major$version_minor_prefix$version_minor || failure=1
              else
                ln $verbose -sf lib$build_name.so$version_major_prefix$version_major$version_minor_prefix$version_minor$version_micro_prefix$version_micro ${path_build}libraries/${path_library_shared}lib$build_name.so$version_major_prefix$version_major$version_minor_prefix$version_minor || failure=1

                if [[ $failure -eq 0 ]] ; then
                  ln $verbose -sf lib$build_name.so$version_file ${path_build}libraries/${path_library_shared}lib$build_name.so$version_major_prefix$version_major$version_minor_prefix$version_minor_prefix$version_minor$version_micro_prefix$version_micro || failure=1
                fi
              fi
            fi
          fi
        fi

        if [[ $failure -eq 0 ]] ; then
          ln $verbose -sf lib$build_name.so$version_major_prefix$version_major ${path_build}libraries/${path_library_shared}lib$build_name.so || failure=1
        fi
      fi
    fi

    if [[ $failure -eq 0 && $sources_program != "" ]] ; then
      sources=
      links=

      if [[ $sources_library != "" || $sources_library_shared != "" ]] ; then
        links="-l$build_name "
      fi

      if [[ $objects_program != "" || $objects_program_shared != "" ]] ; then
        for i in $objects_program $objects_program_shared ; do
          sources="$sources${path_build}objects/${path_object_shared}$i "
        done
      fi

      for i in $sources_program $sources_program_shared ; do
        sources="$sources$path_sources$path_language$i "
      done

      if [[ $verbosity == "verbose" ]] ; then
        echo $build_compiler $sources -o ${path_build}programs/${path_program_shared}$build_name $arguments_shared $arguments_include $links $libraries $libraries_shared $flags $flags_shared $flags_program $flags_program_shared $defines $defines_shared $defines_program $defines_program_shared
      fi

      $build_compiler $sources -o ${path_build}programs/${path_program_shared}$build_name $arguments_shared $arguments_include $links $libraries $libraries_shared $flags $flags_shared $flags_program $flags_program_shared $defines $defines_shared $defines_program $defines_program_shared || failure=1
    fi

    if [[ $failure -eq 0 ]] ; then
      touch ${project_built_shared}.built
    fi
  fi

  if [[ $failure -eq 0 && $build_static == "yes" && ! -f ${project_built_static}.built ]] ; then
    if [[ $sources_object != "" || $sources_object_static != "" ]] ; then
      let count=0

      # Sources object only allows for a single value.
      if [[ $sources_object_static != "" ]] ; then
        for i in $sources_object_static ; do
          let count++
        done

        if [[ $count -gt 1 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object_static$c_warning' found, only using the first one found is going to be used.$c_reset"
          fi
        fi

        for i in $sources_object_static ; do
          sources="$path_sources_object$path_language$i "
          break
        done
      else
        for i in $sources_object ; do
          let count++
        done

        if [[ $count -gt 1 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object$c_warning' found, only using the first one found is going to be used.$c_reset"
          fi
        fi

        for i in $sources_object ; do
          sources="$path_sources_object$path_language$i "
          break
        done
      fi

      if [[ $verbosity == "verbose" ]] ; then
        echo $build_compiler $sources -c -o ${path_build}objects/$path_object_static$build_name.o $arguments_static $arguments_include $libraries $libraries_static $flags $flags_static $flags_object $flags_object_static $defines $defines_static $defines_object $defines_object_static
      fi

      $build_compiler $sources -c -o ${path_build}objects/$path_object_static$build_name.o $arguments_static $arguments_include $libraries $libraries_static $flags $flags_static $flags_object $flags_object_static $defines $defines_static $defines_object $defines_object_static || failure=1
    fi

    if [[ $sources_library != "" || $sources_library_static != "" ]] ; then
      sources=

      if [[ $objects_library != "" || $objects_library_static != "" ]] ; then
        for i in $objects_library $objects_library_static ; do
          sources="$sources${path_build}objects/${path_object_static}$i "
        done
      fi

      for i in $sources_library $sources_library_static ; do
        directory=$(dirname $i)
        n=$(basename $i | sed -e 's|\.c$||')

        if [[ $directory != "." && ! -d ${path_build}objects/$directory ]] ; then
          mkdir $verbose -p ${path_build}objects/$directory

          if [[ $? -ne 0 ]] ; then
            let failure=1

            break;
          fi
        fi

        # These are objects created by the static build step rather than objects created by the object build step.
        sources="$sources${path_build}objects/$directory/$n.o "

        if [[ $verbosity == "verbose" ]] ; then
          echo $build_compiler $path_sources$path_language$i -c -static -o ${path_build}objects/$directory/$n.o $arguments_static $arguments_include $libraries $libraries_static $flags $flags_static $flags_library $flags_library_static $defines $defines_static $defines_library $defines_library_static
        fi

        $build_compiler $path_sources$path_language$i -c -static -o ${path_build}objects/$directory/$n.o $arguments_static $arguments_include $libraries $libraries_static $flags $flags_static $flags_library $flags_library_static $defines $defines_static $defines_library $defines_library_static || failure=1

        if [[ $failure -eq 1 ]] ; then
          break;
        fi
      done

      if [[ $failure -eq 0 && ( $sources_library != "" || $sources_library_static != "" ) ]] ; then

        if [[ $verbosity == "verbose" ]] ; then
          echo $build_indexer $build_indexer_arguments ${path_build}libraries/${path_library_static}lib$build_name.a $sources
        fi

        $build_indexer $build_indexer_arguments ${path_build}libraries/${path_library_static}lib$build_name.a $sources || failure=1
      fi
    fi

    if [[ $failure -eq 0 && $sources_program != "" ]] ; then
      sources=
      links=

      if [[ $sources_library != "" || $sources_library_static != "" ]] ; then
        links="-l$build_name "
      fi

      if [[ $objects_program != "" || $objects_program_static != "" ]] ; then
        for i in $objects_program $objects_program_static ; do
          sources="$sources${path_build}objects/${path_object_static}$i "
        done
      fi

      for i in $sources_program $sources_program_static ; do
        sources="$sources$path_sources$path_language$i "
      done

      if [[ $verbosity == "verbose" ]] ; then
        echo $build_compiler $sources -static -o ${path_build}programs/${path_program_static}$build_name $arguments_static $arguments_include $links $libraries $libraries_static $flags $flags_static $flags_program $flags_program_static $defines $defines_static $defines_program $defines_program_static
      fi

      $build_compiler $sources -static -o ${path_build}programs/${path_program_static}$build_name $arguments_static $arguments_include $links $libraries $libraries_static $flags $flags_static $flags_program $flags_program_static $defines $defines_static $defines_program $defines_program_static || failure=1
    fi

    if [[ $failure -eq 0 ]] ; then
      touch ${project_built_static}.built
    fi
  fi

  if [[ $failure -eq 1 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to build.$c_reset"
    fi

    return 1
  fi
}

bootstrap_operation_build_prepare_defaults() {

  if [[ ${variables[$(bootstrap_id has-version_major_prefix)]} != "yes" ]] ; then
    version_major_prefix="."
  fi

  if [[ ${variables[$(bootstrap_id has-version_minor_prefix)]} != "yes" ]] ; then
    version_minor_prefix="."
  fi

  if [[ ${variables[$(bootstrap_id has-version_micro_prefix)]} != "yes" ]] ; then
    version_micro_prefix="."
  fi

  if [[ ${variables[$(bootstrap_id has-version_nano_prefix)]} != "yes" ]] ; then
    version_nano_prefix="."
  fi

  if [[ ${variables[$(bootstrap_id has-build_compiler)]} != "yes" ]] ; then
    build_compiler="gcc"
  fi

  if [[ ${variables[$(bootstrap_id has-build_indexer)]} != "yes" ]] ; then
    build_indexer="ar"
  fi

  if [[ ${variables[$(bootstrap_id has-path_library_script)]} != "yes" ]] ; then
    path_library_script="script/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_library_shared)]} != "yes" ]] ; then
    path_library_shared="shared/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_library_static)]} != "yes" ]] ; then
    path_library_static="static/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_object_script)]} != "yes" ]] ; then
    path_object_script="script/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_object_shared)]} != "yes" ]] ; then
    path_object_shared="shared/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_object_static)]} != "yes" ]] ; then
    path_object_static="static/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_program_script)]} != "yes" ]] ; then
    path_program_script="script/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_program_shared)]} != "yes" ]] ; then
    path_program_shared="shared/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_program_static)]} != "yes" ]] ; then
    path_program_static="static/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_sources)]} != "yes" ]] ; then
    path_sources="sources/"
  fi

  if [[ ${variables[$(bootstrap_id has-path_sources_object)]} != "yes" ]] ; then
    path_sources_object="sources/"
  fi

  if [[ ${variables[$(bootstrap_id has-has_path_standard)]} != "yes" ]] ; then
    has_path_standard="yes"
  fi

  if [[ ${variables[$(bootstrap_id has-search_shared)]} != "yes" ]] ; then
    search_shared="yes"
  fi

  if [[ ${variables[$(bootstrap_id has-build_shared)]} != "yes" ]] ; then
    build_shared="yes"
  fi
}

bootstrap_operation_build_prepare_defines() {

  if [[ $defines == "" ]] ; then
    defines=${variables[$(bootstrap_id defines-mode)]}
  else
    defines="$defines ${variables[$(bootstrap_id defines-mode)]}"
  fi

  if [[ $defines_library == "" ]] ; then
    defines_library=${variables[$(bootstrap_id defines_library-mode)]}
  else
    defines_library="$defines_library ${variables[$(bootstrap_id defines_library-mode)]}"
  fi

  if [[ $defines_library_shared == "" ]] ; then
    defines_library_shared=${variables[$(bootstrap_id defines_library_shared-mode)]}
  else
    defines_library_shared="$defines_library_shared ${variables[$(bootstrap_id defines_library_shared-mode)]}"
  fi

  if [[ $defines_library_static == "" ]] ; then
    defines_library_static=${variables[$(bootstrap_id defines_library_static-mode)]}
  else
    defines_library_static="$defines_library_static ${variables[$(bootstrap_id defines_library_static-mode)]}"
  fi

  if [[ $defines_object_library == "" ]] ; then
    defines_object_library=${variables[$(bootstrap_id defines_object_library-mode)]}
  else
    defines_object_library="$defines_object_library ${variables[$(bootstrap_id defines_object_library-mode)]}"
  fi

  if [[ $defines_object_library_shared == "" ]] ; then
    defines_object_library_shared=${variables[$(bootstrap_id defines_object_library_shared-mode)]}
  else
    defines_object_library_shared="$defines_object_library_shared ${variables[$(bootstrap_id defines_object_library_shared-mode)]}"
  fi

  if [[ $defines_object_library_static == "" ]] ; then
    defines_object_library_static=${variables[$(bootstrap_id defines_object_library_static-mode)]}
  else
    defines_object_library_static="$defines_object_library_static ${variables[$(bootstrap_id defines_object_library_static-mode)]}"
  fi

  if [[ $defines_object_program == "" ]] ; then
    defines_object_program=${variables[$(bootstrap_id defines_object_program-mode)]}
  else
    defines_object_program="$defines_object_program ${variables[$(bootstrap_id defines_object_program-mode)]}"
  fi

  if [[ $defines_object_program_shared == "" ]] ; then
    defines_object_program_shared=${variables[$(bootstrap_id defines_object_program_shared-mode)]}
  else
    defines_object_program_shared="$defines_object_program_shared ${variables[$(bootstrap_id defines_object_program_shared-mode)]}"
  fi

  if [[ $defines_object_program_static == "" ]] ; then
    defines_object_program_static=${variables[$(bootstrap_id defines_object_program_static-mode)]}
  else
    defines_object_program_static="$defines_object_program_static ${variables[$(bootstrap_id defines_object_program_static-mode)]}"
  fi

  if [[ $defines_program == "" ]] ; then
    defines_program=${variables[$(bootstrap_id defines_program-mode)]}
  else
    defines_program="$defines_program ${variables[$(bootstrap_id defines_program-mode)]}"
  fi

  if [[ $defines_program_shared == "" ]] ; then
    defines_program_shared=${variables[$(bootstrap_id defines_program_shared-mode)]}
  else
    defines_program_shared="$defines_program_shared ${variables[$(bootstrap_id defines_program_shared-mode)]}"
  fi

  if [[ $defines_program_static == "" ]] ; then
    defines_program_static=${variables[$(bootstrap_id defines_program_static-mode)]}
  else
    defines_program_static="$defines_program_static ${variables[$(bootstrap_id defines_program_static-mode)]}"
  fi

  if [[ $defines_shared == "" ]] ; then
    defines_shared=${variables[$(bootstrap_id defines_shared-mode)]}
  else
    defines_shared="$defines_shared ${variables[$(bootstrap_id defines_shared-mode)]}"
  fi

  if [[ $defines_static == "" ]] ; then
    defines_static=${variables[$(bootstrap_id defines_static-mode)]}
  else
    defines_static="$defines_static ${variables[$(bootstrap_id defines_static-mode)]}"
  fi

  if [[ $defines_override != "" ]] ; then
    defines="$defines_override"
    defines_library=
    defines_object_library=
    defines_object_program=
    defines_program=
    defines_shared=
    defines_static=
  fi
}

bootstrap_operation_build_prepare_flags() {

  if [[ $flags == "" ]] ; then
    flags=${variables[$(bootstrap_id flags-mode)]}
  else
    flags="$flags ${variables[$(bootstrap_id flags-mode)]}"
  fi

  if [[ $flags_library == "" ]] ; then
    flags_library=${variables[$(bootstrap_id flags_library-mode)]}
  else
    flags_library="$flags_library ${variables[$(bootstrap_id flags_library-mode)]}"
  fi

  if [[ $flags_library_shared == "" ]] ; then
    flags_library_shared=${variables[$(bootstrap_id flags_library_shared-mode)]}
  else
    flags_library_shared="$flags_library_shared ${variables[$(bootstrap_id flags_library_shared-mode)]}"
  fi

  if [[ $flags_library_static == "" ]] ; then
    flags_library_static=${variables[$(bootstrap_id flags_library_static-mode)]}
  else
    flags_library_static="$flags_library_static ${variables[$(bootstrap_id flags_library_static-mode)]}"
  fi

  if [[ $flags_object_library == "" ]] ; then
    flags_object_library=${variables[$(bootstrap_id flags_object_library-mode)]}
  else
    flags_object_library="$flags_object_library ${variables[$(bootstrap_id flags_object_library-mode)]}"
  fi

  if [[ $flags_object_library_shared == "" ]] ; then
    flags_object_library_shared=${variables[$(bootstrap_id flags_object_library_shared-mode)]}
  else
    flags_object_library_shared="$flags_object_library_shared ${variables[$(bootstrap_id flags_object_library_shared-mode)]}"
  fi

  if [[ $flags_object_library_static == "" ]] ; then
    flags_object_library_static=${variables[$(bootstrap_id flags_object_library_static-mode)]}
  else
    flags_object_library_static="$flags_object_library_static ${variables[$(bootstrap_id flags_object_library_static-mode)]}"
  fi

  if [[ $flags_object_program == "" ]] ; then
    flags_object_program=${variables[$(bootstrap_id flags_object_program-mode)]}
  else
    flags_object_program="$flags_object_program ${variables[$(bootstrap_id flags_object_program-mode)]}"
  fi

  if [[ $flags_object_program_shared == "" ]] ; then
    flags_object_program_shared=${variables[$(bootstrap_id flags_object_program_shared-mode)]}
  else
    flags_object_program_shared="$flags_object_program_shared ${variables[$(bootstrap_id flags_object_program_shared-mode)]}"
  fi

  if [[ $flags_object_program_static == "" ]] ; then
    flags_object_program_static=${variables[$(bootstrap_id flags_object_program_static-mode)]}
  else
    flags_object_program_static="$flags_object_program_static ${variables[$(bootstrap_id flags_object_program_static-mode)]}"
  fi

  if [[ $flags_program == "" ]] ; then
    flags_program=${variables[$(bootstrap_id flags_program-mode)]}
  else
    flags_program="$flags_program ${variables[$(bootstrap_id flags_program-mode)]}"
  fi

  if [[ $flags_program_shared == "" ]] ; then
    flags_program_shared=${variables[$(bootstrap_id flags_program_shared-mode)]}
  else
    flags_program_shared="$flags_program_shared ${variables[$(bootstrap_id flags_program_shared-mode)]}"
  fi

  if [[ $flags_program_static == "" ]] ; then
    flags_program_static=${variables[$(bootstrap_id flags_program_static-mode)]}
  else
    flags_program_static="$flags_program_static ${variables[$(bootstrap_id flags_program_static-mode)]}"
  fi

  if [[ $flags_shared == "" ]] ; then
    flags_shared=${variables[$(bootstrap_id flags_shared-mode)]}
  else
    flags_shared="$flags_shared ${variables[$(bootstrap_id flags_shared-mode)]}"
  fi

  if [[ $flags_static == "" ]] ; then
    flags_static=${variables[$(bootstrap_id flags_static-mode)]}
  else
    flags_static="$flags_static ${variables[$(bootstrap_id flags_static-mode)]}"
  fi
}

bootstrap_operation_build_prepare_headers() {

  if [[ $sources_headers == "" ]] ; then
    sources_headers=${variables[$(bootstrap_id build_sources_headers-mode)]}
  else
    sources_headers="$sources_headers ${variables[$(bootstrap_id build_sources_headers-mode)]}"
  fi

  if [[ $build_shared == "yes" ]] ; then
    if [[ $sources_headers == "" ]] ; then
      sources_headers=${variables[$(bootstrap_id build_sources_headers_shared)]}
    else
      sources_headers="$sources_headers ${variables[$(bootstrap_id build_sources_headers_shared)]}"
    fi

    if [[ $sources_headers == "" ]] ; then
      sources_headers=${variables[$(bootstrap_id build_sources_headers_static)]}
    else
      sources_headers="$sources_headers ${variables[$(bootstrap_id build_sources_headers_static)]}"
    fi
  fi

  if [[ $build_static == "yes" ]] ; then
    if [[ $sources_headers == "" ]] ; then
      sources_headers=${variables[$(bootstrap_id build_sources_headers_shared-mode)]}
    else
      sources_headers="$sources_headers ${variables[$(bootstrap_id build_sources_headers_shared-mode)]}"
    fi

    if [[ $sources_headers == "" ]] ; then
      sources_headers=${variables[$(bootstrap_id build_sources_headers_static-mode)]}
    else
      sources_headers="$sources_headers ${variables[$(bootstrap_id build_sources_headers_static-mode)]}"
    fi
  fi

  if [[ ${variables[$(bootstrap_id path_headers-mode)]} != "" ]] ; then
    path_headers=${variables[$(bootstrap_id path_headers-mode)]}
  elif [[ ${variables[$(bootstrap_id path_headers)]} != "" ]] ; then
    path_headers=${variables[$(bootstrap_id path_headers)]}
  fi

  if [[ $path_headers != "" ]] ; then
    path_headers=$(echo $path_headers | sed -e 's|/*$|/|')
  fi
}

bootstrap_operation_build_prepare_libraries() {

  if [[ $libraries == "" ]] ; then
    libraries=${variables[$(bootstrap_id build_libraries-mode)]}
  else
    libraries="${variables[$(bootstrap_id build_libraries-mode)]} $libraries"
  fi

  if [[ $libraries_shared == "" ]] ; then
    libraries_shared=${variables[$(bootstrap_id build_libraries_shared-mode)]}
  else
    libraries_shared="${variables[$(bootstrap_id build_libraries_shared-mode)]} $libraries_shared"
  fi

  if [[ $libraries_static == "" ]] ; then
    libraries_static=${variables[$(bootstrap_id build_libraries_static-mode)]}
  else
    libraries_static="${variables[$(bootstrap_id build_libraries_static-mode)]} $libraries_static"
  fi

  if [[ $sources_library == "" ]] ; then
    sources_library=${variables[$(bootstrap_id build_sources_library-mode)]}
  else
    sources_library="$sources_library ${variables[$(bootstrap_id build_sources_library-mode)]}"
  fi

  if [[ $sources_library_shared == "" ]] ; then
    sources_library_shared=${variables[$(bootstrap_id build_sources_library_shared-mode)]}
  else
    sources_library_shared="$build_sources_library_shared ${variables[$(bootstrap_id build_sources_library_shared-mode)]}"
  fi

  if [[ $sources_library_static == "" ]] ; then
    sources_library_static=${variables[$(bootstrap_id build_sources_library_static-mode)]}
  else
    sources_library_static="$build_sources_library_static ${variables[$(bootstrap_id build_sources_library_static-mode)]}"
  fi
}

bootstrap_operation_build_prepare_objects() {

  if [[ $objects_library == "" ]] ; then
    objects_library=${variables[$(bootstrap_id build_objects_library-mode)]}
  else
    objects_library="${variables[$(bootstrap_id build_objects_library-mode)]} $objects_library"
  fi

  if [[ $objects_library_shared == "" ]] ; then
    objects_library_shared=${variables[$(bootstrap_id build_objects_library_shared-mode)]}
  else
    objects_library_shared="${variables[$(bootstrap_id build_objects_library_shared-mode)]} $objects_library_shared"
  fi

  if [[ $objects_library_static == "" ]] ; then
    objects_library_static=${variables[$(bootstrap_id build_objects_library_static-mode)]}
  else
    objects_library_static="${variables[$(bootstrap_id build_objects_library_static-mode)]} $objects_library_static"
  fi

  if [[ $objects_program == "" ]] ; then
    objects_program=${variables[$(bootstrap_id build_objects_program-mode)]}
  else
    objects_program="${variables[$(bootstrap_id build_objects_program-mode)]} $objects_program"
  fi

  if [[ $objects_program_shared == "" ]] ; then
    objects_program_shared=${variables[$(bootstrap_id build_objects_program_shared-mode)]}
  else
    objects_program_shared="${variables[$(bootstrap_id build_objects_program_shared-mode)]} $objects_program_shared"
  fi

  if [[ $objects_program_static == "" ]] ; then
    objects_program_static=${variables[$(bootstrap_id build_objects_program_static-mode)]}
  else
    objects_program_static="${variables[$(bootstrap_id build_objects_program_static-mode)]} $objects_program_static"
  fi

  if [[ $sources_object == "" ]] ; then
    sources_object=${variables[$(bootstrap_id build_sources_object-mode)]}
  fi

  if [[ $sources_object_shared == "" ]] ; then
    sources_object_shared=${variables[$(bootstrap_id build_sources_object_shared-mode)]}
  fi

  if [[ $sources_object_static == "" ]] ; then
    sources_object_static=${variables[$(bootstrap_id build_sources_object_static-mode)]}
  fi
}

bootstrap_operation_build_prepare_paths() {

  if [[ $override_path_sources == "" ]] ; then
    if [[ ${variables[$(bootstrap_id path_sources-mode)]} != "" ]] ; then
      path_sources=${variables[$(bootstrap_id path_sources-mode)]}
    elif [[ ${variables[$(bootstrap_id path_sources)]} != "" ]] ; then
      path_sources=${variables[$(bootstrap_id path_sources)]}
    fi
  fi

  if [[ $path_sources != "" ]] ; then
    path_sources=$(echo $path_sources | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_sources_object-mode)]} != "" ]] ; then
    path_sources_object=${variables[$(bootstrap_id path_sources_object-mode)]}
  elif [[ ${variables[$(bootstrap_id path_sources_object)]} != "" ]] ; then
    path_sources_object=${variables[$(bootstrap_id path_sources_object)]}
  fi

  if [[ $path_sources_object != "" ]] ; then
    path_sources_object=$(echo $path_sources_object | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_headers-mode)]} != "" ]] ; then
    path_headers=${variables[$(bootstrap_id path_headers-mode)]}
  fi

  if [[ $path_headers != "" ]] ; then
    path_headers=$(echo $path_headers | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id has_path_standard-mode)]} != "" ]] ; then
    has_path_standard=${variables[$(bootstrap_id has_path_standard-mode)]}
  fi

  if [[ $has_path_standard == "no" ]] ; then
    path_language=
  else
    if [[ ${variables[$(bootstrap_id path_language-mode)]} != "" ]] ; then
      path_language=${variables[$(bootstrap_id path_language-mode)]}
    elif [[ ${variables[$(bootstrap_id path_language)]} != "" ]] ; then
      path_language=${variables[$(bootstrap_id path_language)]}
    fi

    if [[ $path_language != "" ]] ; then
      path_language=$(echo $path_language | sed -e 's|//*|/|g' -e 's|/*$|/|')
    fi
  fi

  if [[ ${variables[$(bootstrap_id path_object_library-mode)]} != "" ]] ; then
    path_object_library=${variables[$(bootstrap_id path_object_library-mode)]}
  fi

  if [[ $path_object_library != "" ]] ; then
    path_object_library=$(echo $path_object_library | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_program-mode)]} != "" ]] ; then
    path_object_program=${variables[$(bootstrap_id path_object_program-mode)]}
  fi

  if [[ $path_object_program != "" ]] ; then
    path_object_program=$(echo $path_object_program | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_library_script-mode)]} != "" ]] ; then
    path_library_script=${variables[$(bootstrap_id path_library_script-mode)]}
  fi

  if [[ $path_library_script != "" ]] ; then
    path_library_script=$(echo $path_library_script | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_library_shared-mode)]} != "" ]] ; then
    path_library_shared=${variables[$(bootstrap_id path_library_shared-mode)]}
  fi

  if [[ $path_library_shared != "" ]] ; then
    path_library_shared=$(echo $path_library_shared | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_library_static-mode)]} != "" ]] ; then
    path_library_static=${variables[$(bootstrap_id path_library_static-mode)]}
  fi

  if [[ $path_library_static != "" ]] ; then
    path_library_static=$(echo $path_library_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_library_script-mode)]} != "" ]] ; then
    path_object_library_script=${variables[$(bootstrap_id path_object_library_script-mode)]}
  fi

  if [[ $path_object_library_script != "" ]] ; then
    path_object_library_script=$(echo $path_object_library_script | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_library_shared-mode)]} != "" ]] ; then
    path_object_library_shared=${variables[$(bootstrap_id path_object_library_shared-mode)]}
  fi

  if [[ $path_object_library_shared != "" ]] ; then
    path_object_library_shared=$(echo $path_object_library_shared | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_library_static-mode)]} != "" ]] ; then
    path_object_library_static=${variables[$(bootstrap_id path_object_library_static-mode)]}
  fi

  if [[ $path_object_library_static != "" ]] ; then
    path_object_library_static=$(echo $path_object_library_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_program_script-mode)]} != "" ]] ; then
    path_object_program_script=${variables[$(bootstrap_id path_object_program_script-mode)]}
  fi

  if [[ $path_object_program_script != "" ]] ; then
    path_object_program_script=$(echo $path_object_program_script | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_program_shared-mode)]} != "" ]] ; then
    path_object_program_shared=${variables[$(bootstrap_id path_object_program_shared-mode)]}
  fi

  if [[ $path_object_program_shared != "" ]] ; then
    path_object_program_shared=$(echo $path_object_program_shared | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_program_static-mode)]} != "" ]] ; then
    path_object_program_static=${variables[$(bootstrap_id path_object_program_static-mode)]}
  fi

  if [[ $path_object_program_static != "" ]] ; then
    path_object_program_static=$(echo $path_object_program_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_script-mode)]} != "" ]] ; then
    path_object_script=${variables[$(bootstrap_id path_object_script-mode)]}
  fi

  if [[ $path_object_script != "" ]] ; then
    path_object_script=$(echo $path_object_script | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_shared-mode)]} != "" ]] ; then
    path_object_shared=${variables[$(bootstrap_id path_object_shared-mode)]}
  fi

  if [[ $path_object_shared != "" ]] ; then
    path_object_shared=$(echo $path_object_shared | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_object_static-mode)]} != "" ]] ; then
    path_object_static=${variables[$(bootstrap_id path_object_static-mode)]}
  fi

  if [[ $path_object_static != "" ]] ; then
    path_object_static=$(echo $path_object_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ $path_object_static != "" ]] ; then
    path_object_static=$(echo $path_object_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_program_script-mode)]} != "" ]] ; then
    path_program_script=${variables[$(bootstrap_id path_program_script-mode)]}
  fi

  if [[ $path_program_script != "" ]] ; then
    path_program_script=$(echo $path_program_script | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_program_shared-mode)]} != "" ]] ; then
    path_program_shared=${variables[$(bootstrap_id path_program_shared-mode)]}
  fi

  if [[ $path_program_shared != "" ]] ; then
    path_program_shared=$(echo $path_program_shared | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${variables[$(bootstrap_id path_program_static-mode)]} != "" ]] ; then
    path_program_static=${variables[$(bootstrap_id path_program_static-mode)]}
  fi

  if [[ $path_program_static != "" ]] ; then
    path_program_static=$(echo $path_program_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ $path_program_static != "" ]] ; then
    path_program_static=$(echo $path_program_static | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi
}

bootstrap_operation_build_prepare_programs() {

  if [[ $sources_program == "" ]] ; then
    sources_program=${variables[$(bootstrap_id build_sources_program-mode)]}
  else
    sources_program="$sources_program ${variables[$(bootstrap_id build_sources_program-mode)]}"
  fi

  if [[ $sources_program_shared == "" ]] ; then
    sources_program_shared=${variables[$(bootstrap_id build_sources_program_shared-mode)]}
  else
    sources_program_shared="$sources_program_shared ${variables[$(bootstrap_id build_sources_program_shared-mode)]}"
  fi

  if [[ $sources_program_static == "" ]] ; then
    sources_program_static=${variables[$(bootstrap_id build_sources_program_static-mode)]}
  else
    sources_program_static="$sources_program_static ${variables[$(bootstrap_id build_sources_program_static-mode)]}"
  fi
}

bootstrap_operation_build_prepare_remaining() {

  if [[ ${variables[$(bootstrap_id build_name-mode)]} != "" ]] ; then
    build_name=${variables[$(bootstrap_id build_name-mode)]}
  fi

  if [[ ${variables[$(bootstrap_id build_compiler-mode)]} != "" ]] ; then
    build_compiler=${variables[$(bootstrap_id build_compiler-mode)]}
  fi

  if [[ ${variables[$(bootstrap_id build_indexer-mode)]} != "" ]] ; then
    build_indexer=${variables[$(bootstrap_id build_indexer-mode)]}
  fi

  if [[ ${variables[$(bootstrap_id build_indexer_arguments-mode)]} != "" ]] ; then
    build_indexer_arguments=${variables[$(bootstrap_id build_indexer_arguments)]}
  fi

  if [[ ${variables[$(bootstrap_id version_major-mode)]} != "" ]] ; then
    version_major=${variables[$(bootstrap_id version_major)]}
  fi

  if [[ ${variables[$(bootstrap_id version_major_prefix-mode)]} != "" ]] ; then
    version_major_prefix=${variables[$(bootstrap_id version_major_prefix)]}
  fi

  if [[ ${variables[$(bootstrap_id version_minor-mode)]} != "" ]] ; then
    version_minor=${variables[$(bootstrap_id version_minor)]}
  fi

  if [[ ${variables[$(bootstrap_id version_minor_prefix-mode)]} != "" ]] ; then
    version_minor_prefix=${variables[$(bootstrap_id version_minor_prefix)]}
  fi

  if [[ ${variables[$(bootstrap_id version_micro-mode)]} != "" ]] ; then
    version_micro=${variables[$(bootstrap_id version_micro)]}
  fi

  if [[ ${variables[$(bootstrap_id version_micro_prefix-mode)]} != "" ]] ; then
    version_micro_prefix=${variables[$(bootstrap_id version_micro_prefix)]}
  fi

  if [[ ${variables[$(bootstrap_id version_nano-mode)]} != "" ]] ; then
    version_nano=${variables[$(bootstrap_id version_nano)]}
  fi

  if [[ ${variables[$(bootstrap_id version_nano_prefix-mode)]} != "" ]] ; then
    version_nano_prefix=${variables[$(bootstrap_id version_nano_prefix)]}
  fi

  if [[ ${variables[$(bootstrap_id path_headers-mode)]} != "" ]] ; then
    path_headers=${variables[$(bootstrap_id path_headers)]}
  fi

  if [[ ${variables[$(bootstrap_id preserve_path_headers-mode)]} != "" ]] ; then
    preserve_path_headers=${variables[$(bootstrap_id preserve_path_headers)]}
  fi

  if [[ ${variables[$(bootstrap_id path_library_script-mode)]} != "" ]] ; then
    path_library_script=${variables[$(bootstrap_id path_library_script)]}
  fi

  if [[ ${variables[$(bootstrap_id path_library_shared-mode)]} != "" ]] ; then
    path_library_shared=${variables[$(bootstrap_id path_library_shared)]}
  fi

  if [[ ${variables[$(bootstrap_id path_library_static-mode)]} != "" ]] ; then
    path_library_static=${variables[$(bootstrap_id path_library_static)]}
  fi

  if [[ ${variables[$(bootstrap_id path_object_script-mode)]} != "" ]] ; then
    path_object_script=${variables[$(bootstrap_id path_object_script)]}
  fi

  if [[ ${variables[$(bootstrap_id path_object_shared-mode)]} != "" ]] ; then
    path_object_shared=${variables[$(bootstrap_id path_object_shared)]}
  fi

  if [[ ${variables[$(bootstrap_id path_object_static-mode)]} != "" ]] ; then
    path_object_static=${variables[$(bootstrap_id path_object_static)]}
  fi

  if [[ ${variables[$(bootstrap_id path_program_script-mode)]} != "" ]] ; then
    path_program_script=${variables[$(bootstrap_id path_program_script)]}
  fi

  if [[ ${variables[$(bootstrap_id path_program_shared-mode)]} != "" ]] ; then
    path_program_shared=${variables[$(bootstrap_id path_program_shared)]}
  fi

  if [[ ${variables[$(bootstrap_id path_program_static-mode)]} != "" ]] ; then
    path_program_static=${variables[$(bootstrap_id path_program_static)]}
  fi

  if [[ ${variables[$(bootstrap_id has_path_standard-mode)]} != "" ]] ; then
    has_path_standard=${variables[$(bootstrap_id has_path_standard)]}
  fi

  if [[ ${variables[$(bootstrap_id search_exclusive-mode)]} != "" ]] ; then
    search_exclusive=${variables[$(bootstrap_id search_exclusive)]}
  fi

  if [[ ${variables[$(bootstrap_id search_shared-mode)]} != "" ]] ; then
    search_shared=${variables[$(bootstrap_id search_shared)]}
  fi

  if [[ ${variables[$(bootstrap_id search_static-mode)]} != "" ]] ; then
    search_static=${variables[$(bootstrap_id search_static)]}
  fi
}

bootstrap_operation_build_prepare_settings() {

  if [[ $sources_setting == "" ]] ; then
    sources_setting=${variables[$(bootstrap_id build_sources_setting-mode)]}
  else
    sources_setting="$sources_setting ${variables[$(bootstrap_id build_sources_setting-mode)]}"
  fi
}

bootstrap_operation_build_prepare_shared_static() {

  if [[ ${variables[$(bootstrap_id build_shared-mode)]} != "" ]] ; then
    build_shared=${variables[$(bootstrap_id build_shared-mode)]}
  fi

  if [[ ${variables[$(bootstrap_id build_static-mode)]} != "" ]] ; then
    build_static=${variables[$(bootstrap_id build_static-mode)]}
  fi

  if [[ $enable_shared == "yes" ]] ; then
    build_shared="yes"
    search_shared="yes"
  elif [[ $enable_shared == "no" ]] ; then
    build_shared="no"
    search_shared="no"
  fi

  if [[ $enable_static == "yes" ]] ; then
    build_static="yes"
    search_static="yes"
  elif [[ $enable_static == "no" ]] ; then
    build_static="no"
    search_static="no"
  fi

  if [[ $search_shared == "no" ]] ; then
    arguments_shared=
  fi

  if [[ $search_static == "no" ]] ; then
    arguments_static=
  fi
}

bootstrap_operation_build_validate_build() {

  if [[ $build_compiler == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, no '${c_notice}build_compiler${c_error}' specified, such as '${c_notice}gcc${c_error}'.$c_reset"
    fi

    let failure=1
  fi

  if [[ $build_indexer == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, no '${c_notice}build_indexer${c_error}' specified, such as '${c_notice}ar${c_error}'.$c_reset"
    fi

    let failure=1
  fi
}

bootstrap_operation_build_validate_paths() {

  if [[ $path_sources == "" || ! -d $path_sources ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The sources directory $c_notice$path_sources$c_error is not a valid directory.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 0 && $path_sources_object != "" && ! -d $path_sources_object ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The sources object directory $c_notice$path_sources_object$c_error is not a valid directory.$c_reset"
    fi

    let failure=1
  fi
}

bootstrap_operation_build_validate_search() {

  # When not in search exclusive mode, allow static libraries to be linked into shared libraries if the shared library is not found first.
  if [[ $search_exclusive == "no" ]] ; then
    arguments_shared="$arguments_shared $arguments_static"
  fi
}

bootstrap_operation_build_validate_shared_static() {

  if [[ $build_shared != "yes" && $build_static != "yes" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, either build_shared or build_static must be set to 'yes'.$c_reset"
    fi

    let failure=1
  fi

  if [[ $search_shared != "yes" && $search_static != "yes" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, either search_shared or search_static must be set to 'yes'.$c_reset"
    fi

    let failure=1
  fi
}

bootstrap_operation_build_validate_sources() {

  for i in $sources_script ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_script path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done

  for i in $sources_headers ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_headers path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done

  for i in $sources_library ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_library path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done

  for i in $sources_library_object ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_library_object path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done

  for i in $sources_program_object ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_program_object path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done

  for i in $sources_program ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_program path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done

  for i in $sources_setting ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Cannot Build, invalid sources_setting path provided: '$i'.$c_reset"
      fi

      let failure=1
    fi
  done
}

bootstrap_operation_build_prepare_versions() {

  if [[ ${variables[$(bootstrap_id version_file-mode)]} != "" ]] ; then
    version_file_value=${variables[$(bootstrap_id version_file-mode)]}
  fi

  if [[ ${variables[$(bootstrap_id version_target-mode)]} != "" ]] ; then
    version_target_value=${variables[$(bootstrap_id version_target-mode)]}
  fi

  if [[ $version_file_value == "" ]] ; then
    version_file_value="micro"
  fi

  if [[ $version_target_value == "" ]] ; then
    version_target_value="major"
  fi

  if [[ $version_major == "" ]] ; then
    version_major_prefix=
  fi

  if [[ $version_minor == "" ]] ; then
    version_minor_prefix=
  fi

  if [[ $version_micro == "" ]] ; then
    version_micro_prefix=
  fi

  if [[ $version_nano == "" ]] ; then
    version_nano_prefix=
  fi

  if [[ $version_file_value == "major" ]] ; then
    version_file="$version_major_prefix$version_major"
  elif [[ $version_file_value == "minor" ]] ; then
    version_file="$version_major_prefix$version_major$version_minor_prefix$version_minor"
  elif [[ $version_file_value == "micro" ]] ; then
    version_file="$version_major_prefix$version_major$version_minor_prefix$version_minor$version_micro_prefix$version_micro"
  elif [[ $version_file_value == "nano" ]] ; then
    version_file="$version_major_prefix$version_major$version_minor_prefix$version_minor$version_micro_prefix$version_micro$version_nano_prefix$version_nano"
  fi

  if [[ $version_target_value == "major" ]] ; then
    version_target="$version_major_prefix$version_major"
  elif [[ $version_target_value == "minor" ]] ; then
    version_target="$version_major_prefix$version_major$version_minor_prefix$version_minor"
  elif [[ $version_target_value == "micro" ]] ; then
    version_target="$version_major_prefix$version_major$version_minor_prefix$version_minor$version_micro_prefix$version_micro"
  elif [[ $version_target_value == "nano" ]] ; then
    version_target="$version_major_prefix$version_major$version_minor_prefix$version_minor$version_micro_prefix$version_micro$version_nano_prefix$version_nano"
  fi
}

bootstrap_operation_clean() {

  local i=

  for i in ${path_build}{documents,includes,libraries,objects,programs,settings,stage} ; do
    if [[ -e $i ]] ; then
      rm $verbose -Rf $i
    fi
  done

  if [[ -f ${project_built}.prepared ]] ; then
    rm $verbose -f ${project_built}.prepared
  fi

  if [[ -f ${project_built_shared}.built ]] ; then
    rm $verbose -f ${project_built_shared}.built
  fi

  if [[ -f ${project_built_static}.built ]] ; then
    rm $verbose -f ${project_built_static}.built
  fi
}

bootstrap_cleanup() {

  unset bootstrap_main
  unset bootstrap_handle_colors
  unset bootstrap_help
  unset bootstrap_id
  unset bootstrap_load_settings
  unset bootstrap_load_settings_mode
  unset bootstrap_load_settings_has
  unset bootstrap_prepare_build
  unset bootstrap_operation_build
  unset bootstrap_operation_build_prepare_defaults
  unset bootstrap_operation_build_prepare_defines
  unset bootstrap_operation_build_prepare_flags
  unset bootstrap_operation_build_prepare_headers
  unset bootstrap_operation_build_prepare_libraries
  unset bootstrap_operation_build_prepare_objects
  unset bootstrap_operation_build_prepare_paths
  unset bootstrap_operation_build_prepare_programs
  unset bootstrap_operation_build_prepare_remaining
  unset bootstrap_operation_build_prepare_settings
  unset bootstrap_operation_build_prepare_shared_static
  unset bootstrap_operation_build_prepare_versions
  unset bootstrap_operation_build_validate_build
  unset bootstrap_operation_build_validate_paths
  unset bootstrap_operation_build_validate_search
  unset bootstrap_operation_build_validate_shared_static
  unset bootstrap_operation_build_validate_sources
  unset bootstrap_operation_clean
  unset bootstrap_cleanup
}

bootstrap_main $*

#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple bootstrap tool to compile any part of the FLL project.
# The dependencies of this script are: bash, basename, dirname, grep, and sed.
#
# This script is only designed specifically for bootstrap compiling the FLL project and does not necessarily fully follow the fake (featureless make) build process.

bootstrap_main() {
  local public_name="Simple FLL Bootstrap Script"
  local system_name=bootstrap
  local called_name=$(basename $0)
  local version=0.5.0

  local grab_next=
  local do_color=normal
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
  local operation=
  local operation_failure=
  local path_build=build/
  local path_build_stage=build/stage/
  local path_data=data/
  local path_settings=data/build/settings/
  local path_sources=sources/
  local path_c=sources/c/
  local path_work=
  local project_built=
  local defines_override=
  local process=

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
        elif [[ $p == "+n" || $p == "++no_color" ]] ; then
          do_color=none
        elif [[ $p == "+l" || $p == "++light" ]] ; then
          do_color=light
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
          mode="$p"
        elif [[ $grab_next == "process" ]] ; then
          process="$p"
        elif [[ $grab_next == "settings_name" ]] ; then
          settings_name="$p"
        elif [[ $grab_next == "path_build" ]] ; then
          path_build=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_data" ]] ; then
          path_data=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_sources" ]] ; then
          path_sources=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_c="${path_sources}c/"
        elif [[ $grab_next == "path_work" ]] ; then
          path_work=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        fi

        grab_next=
      fi
    done

    p=
  fi

  settings_file="${path_data}build/$settings_name"
  settings_defines="${path_data}build/defines"
  path_settings="${path_data}build/settings/"
  path_build_stage="${path_build}stage/"

  bootstrap_handle_colors

  if [[ $do_help == "yes" ]] ; then
    bootstrap_help
    bootstrap_cleanup
    return 0
  fi

  # FSS and Featurless Make supports more flexible mode names, but for the purpose of this bootstrap script and avoiding potential problems, keep it simple.
  if [[ $mode != "" && $(echo "$mode" | grep -s -o "[^_[:alnum:]+-]") != "" ]] ; then
    echo -e "${c_error}ERROR: the mode $c_notice$mode$c_error includes invalid characters, only alphanumeric, underscore, minus, and plus are allowed.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  bootstrap_load_settings

  if [[ $mode == "" ]] ; then
    mode=${variables[$(bootstrap_id modes_default)]}

    if [[ $mode != "" && $(echo "$mode" | grep -s -o "[^_[:alnum:]+-]") != "" ]] ; then
      echo -e "${c_error}ERROR: the mode $c_notice$mode$c_error includes invalid characters, only alphanumeric, underscore, minus, and plus are allowed.$c_reset"
      bootstrap_cleanup
      return 1
    fi
  fi

  bootstrap_load_settings_mode

  project_built="${path_build_stage}${variables[$(bootstrap_id project_name)]}"
  if [[ $process != "" ]] ; then
    project_built="${project_built}-$process"
  fi

  if [[ ${variables[$(bootstrap_id modes)]} == "" ]] ; then
    if [[ $mode != "" ]] ; then
      echo -e "${c_error}ERROR: the mode $c_notice$mode$c_error is not a valid mode, there are no available modes.$c_error$c_reset"
      bootstrap_cleanup
      return 1
    fi
  else
    let i=0
    for m in ${variables[$(bootstrap_id modes)]} ; do
      if [[ "$mode" == "$m" ]] ; then
        let i=1
        break
      fi
    done

    if [[ $i -eq 0 ]] ; then
      echo -e "${c_error}ERROR: the mode $c_notice$mode$c_error is not a valid mode, it must be one of: $c_notice${variables[$(bootstrap_id modes)]}$c_error.$c_reset"
      bootstrap_cleanup
      return 1
    fi
  fi

  if [[ ${variables[$(bootstrap_id project_name)]} == "" ]] ; then
    echo -e "${c_error}ERROR: the required setting '${c_notice}project_name$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ ${variables[$(bootstrap_id version_major)]} == "" ]] ; then
    echo -e "${c_error}ERROR: the required setting '${c_notice}version_major$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ ${variables[$(bootstrap_id version_minor)]} == "" ]] ; then
    echo -e "${c_error}ERROR: the required setting '${c_notice}version_minor$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ ${variables[$(bootstrap_id version_micro)]} == "" ]] ; then
    echo -e "${c_error}ERROR: the required setting '${c_notice}version_micro$c_error' is not specified in the build settings file '$c_notice$settings_file$c_error'.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ $path_data == "" || ! -d $path_data ]] ; then
    echo -e "${c_error}ERROR: the data directory $c_notice$path_data$c_error is not a valid directory.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ $path_sources == "" || ! -d $path_sources ]] ; then
    echo -e "${c_error}ERROR: the sources directory $c_notice$path_sources$c_error is not a valid directory.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ $path_work != "" && ! -d $path_work ]] ; then
    echo -e "${c_error}ERROR: the work directory $c_notice$path_work$c_error is not a valid directory.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ $defines_override != "" && $(echo "$defines_override" | grep -s -o "[^_[:alnum:][:space:]]") != "" ]] ; then
    echo -e "${c_error}ERROR: the defines override $c_notice$defines_override$c_error includes invalid characters, only alphanumeric, whitespace, and underscore are allowed.$c_reset"
    bootstrap_cleanup
    return 1
  fi

  if [[ $operation_failure == "fail-multiple" ]] ; then
    echo -e "${c_error}ERROR: only one operation may be specified at a time.$c_reset"
    bootstrap_cleanup
    return 1
  elif [[ $operation == "build" ]] ; then
    if [[ -f ${project_built}.built ]] ; then
      echo -e "${c_warning}WARNING: this project has already been built.$c_reset"
    else
      if [[ ! -f ${project_built}.prepared ]] ; then
        bootstrap_prepare_build
      fi

      bootstrap_operation_build
    fi
  elif [[ $operation == "clean" ]] ; then
    bootstrap_operation_clean
  elif [[ $operation == "" ]] ; then
    echo -e "${c_error}ERROR: no operation was given.$c_reset"
    bootstrap_cleanup
    return 1
  else
    echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
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
  echo -e "$c_highlight$system_name$c_reset $c_notice<${c_reset}operation$c_notice>$c_reset"
  echo -e " ${c_important}build${c_reset}  Build or compile the code based on build settings file."
  echo -e " ${c_important}clean${c_reset}  Delete all build files."
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen."
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds."
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color."
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
  local name=$1

  case $name in
    "build_compiler") echo -n 0;;
    "build_language") echo -n 1;;
    "build_libraries") echo -n 2;;
    "build_linker") echo -n 3;;
    "build_script") echo -n 4;;
    "build_shared") echo -n 5;;
    "build_sources_headers") echo -n 6;;
    "build_sources_library") echo -n 7;;
    "build_sources_program") echo -n 8;;
    "build_sources_setting") echo -n 9;;
    "build_sources_script") echo -n 10;;
    "build_static") echo -n 11;;
    "defines_all") echo -n 12;;
    "defines_shared") echo -n 13;;
    "defines_static") echo -n 14;;
    "environment") echo -n 15;;
    "flags_all") echo -n 16;;
    "flags_library") echo -n 17;;
    "flags_program") echo -n 18;;
    "flags_shared") echo -n 19;;
    "flags_static") echo -n 20;;
    "modes") echo -n 21;;
    "modes_default") echo -n 22;;
    "path_language") echo -n 23;;
    "path_headers") echo -n 24;;
    "path_library_script") echo -n 25;;
    "path_library_shared") echo -n 26;;
    "path_library_static") echo -n 27;;
    "path_program_script") echo -n 28;;
    "path_program_shared") echo -n 29;;
    "path_program_static") echo -n 30;;
    "process_post") echo -n 31;;
    "process_pre") echo -n 32;;
    "project_name") echo -n 33;;
    "search_exclusive") echo -n 34;;
    "search_shared") echo -n 35;;
    "search_static") echo -n 36;;
    "version_major") echo -n 37;;
    "version_micro") echo -n 38;;
    "version_minor") echo -n 39;;
    "version_target") echo -n 40;;

    "build_libraries-$mode") echo -n 41;;
    "build_sources_headers-$mode") echo -n 42;;
    "build_sources_library-$mode") echo -n 43;;
    "build_sources_program-$mode") echo -n 44;;
    "build_sources_setting-$mode") echo -n 45;;
    "build_sources_script-$mode") echo -n 46;;
    "defines_all-$mode") echo -n 47;;
    "defines_shared-$mode") echo -n 48;;
    "defines_static-$mode") echo -n 49;;
    "environment-$mode") echo -n 50;;
    "flags_all-$mode") echo -n 51;;
    "flags_library-$mode") echo -n 52;;
    "flags_program-$mode") echo -n 53;;
    "flags_shared-$mode") echo -n 54;;
    "flags_static-$mode") echo -n 55;;
  esac
}

bootstrap_load_settings() {
  local failure=
  local i=
  local key=

  if [[ ! -d ${path_data}build/ ]] ; then
    echo -e "${c_error}ERROR: no build settings directory '$c_notice${path_data}build/$c_error' could not be found or is not a valid directory.$c_reset"
    failure=1
  elif [[ ! -f $settings_file ]] ; then
    echo -e "${c_error}ERROR: no settings file $c_notice$settings_file$c_error could not be found or is not a valid file.$c_reset"
    failure=1
  fi

  if [[ $failure != "" ]] ; then
    bootstrap_cleanup
    exit $failure
  fi

  for i in build_compiler build_language build_libraries build_linker build_script build_shared build_sources_headers build_sources_library build_sources_program build_sources_setting build_sources_script build_static defines_all defines_shared defines_static environment flags_all flags_library flags_program flags_shared flags_static modes modes_default path_language path_headers path_library_script path_library_shared path_library_static path_program_script path_program_shared path_program_static process_post process_pre project_name search_exclusive search_shared search_static version_major version_micro version_minor ; do
    variables[$(bootstrap_id $i)]=$(grep -s -o "^[[:space:]]*$i[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')
  done
}

bootstrap_load_settings_mode() {
  local i=

  for i in build_libraries-$mode build_sources_headers-$mode build_sources_library-$mode build_sources_program-$mode build_sources_setting-$mode build_sources_script-$mode defines_all-$mode defines_shared-$mode defines_static-$mode environment-$mode flags_all-$mode flags_library-$mode flags_program-$mode flags_shared-$mode flags_static-$mode ; do
    variables[$(bootstrap_id $i)]=$(grep -s -o "^[[:space:]]*$i[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')
  done
}

bootstrap_prepare_build() {
  local failure=
  local alt=$1
  local i=

  mkdir -vp ${path_build}{documents,includes,libraries/{script,shared,static},objects,programs/{script,shared,static},settings,stage} || failure=1

  if [[ $failure == "" ]] ; then
    for i in ${variables[$(bootstrap_id path_headers)]} ; do
      mkdir -vp ${path_build}includes/$i || failure=1
    done
  fi

  if [[ $failure != "" ]] ; then
    bootstrap_cleanup
    exit $failure
  fi

  touch ${project_built}.prepared
}

bootstrap_operation_build() {
  local failure=
  local name=${variables[$(bootstrap_id project_name)]}
  local major=${variables[$(bootstrap_id version_major)]}
  local minor=${variables[$(bootstrap_id version_minor)]}
  local micro=${variables[$(bootstrap_id version_micro)]}
  local target=${variables[$(bootstrap_id version_target)]}
  local compiler=${variables[$(bootstrap_id build_compiler)]}
  local linker=${variables[$(bootstrap_id build_linker)]}
  local arguments_include="-I${path_build}includes"
  local arguments_shared="-L${path_build}libraries/shared"
  local arguments_static="-L${path_build}libraries/static"
  local search_exclusive=${variables[$(bootstrap_id search_exlusive)]}
  local search_shared=${variables[$(bootstrap_id search_shared)]}
  local search_static=${variables[$(bootstrap_id search_static)]}
  local shared=${variables[$(bootstrap_id build_shared)]}
  local static=${variables[$(bootstrap_id build_static)]}
  local sources_library=${variables[$(bootstrap_id build_sources_library)]}
  local sources_program=${variables[$(bootstrap_id build_sources_program)]}
  local sources_headers=${variables[$(bootstrap_id build_sources_headers)]}
  local sources_bash=${variables[$(bootstrap_id build_sources_bash)]}
  local sources_setting=${variables[$(bootstrap_id build_sources_setting)]}
  local sources=
  local libraries=${variables[$(bootstrap_id build_libraries)]}
  local links=
  local defines=${variables[$(bootstrap_id defines_all)]}
  local defines_shared=${variables[$(bootstrap_id defines_shared)]}
  local defines_static=${variables[$(bootstrap_id defines_static)]}
  local flags_all=${variables[$(bootstrap_id flags_all)]}
  local flags_shared=${variables[$(bootstrap_id flags_shared)]}
  local flags_static=${variables[$(bootstrap_id flags_static)]}
  local flags_library=${variables[$(bootstrap_id flags_library)]}
  local flags_program=${variables[$(bootstrap_id flags_program)]}
  local i=
  local n=
  local version=
  local alt=$1
  local directory=
  local path_headers=${variables[$(bootstrap_id path_headers)]}

  if [[ $target == "" ]] ; then
    target="major"
  fi

  if [[ $target == "major" ]] ; then
    version="$major"
  elif [[ $target == "minor" ]] ; then
    version="${major}.$minor"
  elif [[ $target == "micro" ]] ; then
    version="${major}.${minor}.$micro"
  fi

  if [[ $sources_library == "" ]] ; then
    sources_library=${variables[$(bootstrap_id build_sources_library-$mode)]}
  else
    sources_library="$sources_library ${variables[$(bootstrap_id build_sources_library-$mode)]}"
  fi

  if [[ $sources_program == "" ]] ; then
    sources_program=${variables[$(bootstrap_id build_sources_program-$mode)]}
  else
    sources_program="$sources_program ${variables[$(bootstrap_id build_sources_program-$mode)]}"
  fi

  if [[ $sources_headers == "" ]] ; then
    sources_headers=${variables[$(bootstrap_id build_sources_headers-$mode)]}
  else
    sources_headers="$sources_headers ${variables[$(bootstrap_id build_sources_headers-$mode)]}"
  fi

  if [[ $sources_setting == "" ]] ; then
    sources_setting=${variables[$(bootstrap_id build_sources_setting-$mode)]}
  else
    sources_setting="$sources_setting ${variables[$(bootstrap_id build_sources_setting-$mode)]}"
  fi

  if [[ $libraries == "" ]] ; then
    libraries=${variables[$(bootstrap_id build_libraries-$mode)]}
  else
    libraries="$libraries ${variables[$(bootstrap_id build_libraries-$mode)]}"
  fi

  if [[ $defines == "" ]] ; then
    defines=${variables[$(bootstrap_id defines_all-$mode)]}
  else
    defines="$defines ${variables[$(bootstrap_id defines_all-$mode)]}"
  fi

  if [[ $defines_shared == "" ]] ; then
    defines_shared=${variables[$(bootstrap_id defines_shared-$mode)]}
  else
    defines_shared="$defines_shared ${variables[$(bootstrap_id defines_shared-$mode)]}"
  fi

  if [[ $defines_static == "" ]] ; then
    defines_static=${variables[$(bootstrap_id defines_static-$mode)]}
  else
    defines_static="$defines_static ${variables[$(bootstrap_id defines_static-$mode)]}"
  fi

  if [[ $flags_all == "" ]] ; then
    flags_all=${variables[$(bootstrap_id flags_all-$mode)]}
  else
    flags_all="$flags_all ${variables[$(bootstrap_id flags_all-$mode)]}"
  fi

  if [[ $flags_shared == "" ]] ; then
    flags_shared=${variables[$(bootstrap_id flags_shared-$mode)]}
  else
    flags_shared="$flags_shared ${variables[$(bootstrap_id flags_shared-$mode)]}"
  fi

  if [[ $flags_static == "" ]] ; then
    flags_static=${variables[$(bootstrap_id flags_static-$mode)]}
  else
    flags_static="$flags_static ${variables[$(bootstrap_id flags_static-$mode)]}"
  fi

  if [[ $flags_library == "" ]] ; then
    flags_library=${variables[$(bootstrap_id flags_library-$mode)]}
  else
    flags_library="$flags_library ${variables[$(bootstrap_id flags_library-$mode)]}"
  fi

  if [[ $flags_program == "" ]] ; then
    flags_program=${variables[$(bootstrap_id flags_program-$mode)]}
  else
    flags_program="$flags_program ${variables[$(bootstrap_id flags_program-$mode)]}"
  fi

  if [[ $path_work != "" ]] ; then
    arguments_include="$arguments_include -I${path_work}includes/"
    arguments_shared="$arguments_shared -L${path_work}libraries/shared/"
    arguments_static="$arguments_static -L${path_work}libraries/static/"
  fi

  if [[ $defines_override != "" ]] ; then
    defines="$defines_override"
    defines_shared=
    defines_static=
  fi

  if [[ $defines != "" ]] ; then
    flags_all="$flags_all "
    for i in $defines ; do
      flags_all="${flags_all}-D$i "
    done
  fi

  if [[ $defines_shared != "" ]] ; then
    flags_shared="$flags_shared "
    for i in $defines_shared ; do
      flags_shared="${flags_shared}-D$i "
    done
  fi

  if [[ $defines_static != "" ]] ; then
    flags_static="$flags_static "
    for i in $defines_static ; do
      flags_static="${flags_static}-D$i "
    done
  fi

  if [[ $enable_shared == "yes" ]] ; then
    shared="yes"
    search_shared="yes"
  elif [[ $enable_shared == "no" ]] ; then
    shared="no"
    search_shared="no"
  fi

  if [[ $enable_static == "yes" ]] ; then
    static="yes"
    search_static="yes"
  elif [[ $enable_static == "no" ]] ; then
    static="no"
    search_static="no"
  fi

  if [[ $shared != "yes" && $static != "yes" ]] ; then
    echo -e "${c_error}ERROR: Cannot Build, either build_shared or build_static must be set to 'yes'.$c_reset"
    bootstrap_cleanup
    exit -1
  fi

  if [[ $search_shared != "yes" && $search_static != "yes" ]] ; then
    echo -e "${c_error}ERROR: Cannot Build, either search_shared or search_static must be set to 'yes'.$c_reset"
    bootstrap_cleanup
    exit -1
  fi

  for i in $sources_library ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid source_library path provided: '$i'.$c_reset"
      bootstrap_cleanup
      exit -1
    fi
  done

  for i in $sources_program ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_program path provided: '$i'.$c_reset"
      bootstrap_cleanup
      exit -1
    fi
  done

  for i in $sources_headers ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_headers path provided: '$i'.$c_reset"
      bootstrap_cleanup
      exit -1
    fi
  done

  for i in $sources_bash ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_bash path provided: '$i'.$c_reset"
      bootstrap_cleanup
      exit -1
    fi
  done

  for i in $sources_setting ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_setting path provided: '$i'.$c_reset"
      bootstrap_cleanup
      exit -1
    fi
  done

  if [[ $search_shared == "no" ]] ; then
    arguments_shared=
  fi

  if [[ $search_static == "no" ]] ; then
    arguments_static=
  fi

  # when not in search exclusive mode, allow static libraries to be linked into shared libraries if the shared library is not found first.
  if [[ $search_exclusive == "no" ]] ; then
    arguments_shared="$arguments_shared $arguments_static"
  fi

  if [[ $sources_setting != "" ]] ; then
    for i in $sources_setting ; do
      directory=$(dirname $i)

      if [[ $directory == "." ]] ; then
        cp -vR $path_settings$i ${path_build}settings/ || failure=1
      else
        mkdir -vp ${path_build}settings/$directory || failure=1

        if [[ $failure == "" ]] ; then
          cp -vR $path_settings$i ${path_build}settings/${directory}/ || failure=1
        fi
      fi
    done
  fi

  if [[ $failure == "" && $sources_headers != "" ]] ; then
    if [[ $path_headers == "" ]] ; then
      for i in $sources_headers ; do
        directory=$(dirname $i)

        if [[ $directory == "." ]] ; then
          cp -vf $path_c$i ${path_build}includes/ || failure=1
        else
          mkdir -vp ${path_build}includes/$directory || failure=1

          if [[ $failure == "" ]] ; then
            cp -vf $path_c$i ${path_build}includes/$i || failure=1
          fi
        fi
      done
    else
      for i in $sources_headers ; do
        cp -vf $path_c$i ${path_build}includes/$path_headers/ || failure=1
      done
    fi
  fi

  if [[ $failure == "" && $shared == "yes" ]] ; then
    if [[ $sources_library != "" ]] ; then
      sources=
      for i in $sources_library ; do
        sources="$sources$path_c$i "
      done

      echo $compiler $sources -shared -Wl,-soname,lib$name.so.$version -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments_shared $arguments_include $libraries $flags_all $flags_shared $flags_library
      $compiler $sources -shared -Wl,-soname,lib$name.so.$version -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments_shared $arguments_include $libraries $flags_all $flags_shared $flags_library || failure=1

      if [[ $failure == "" ]] ; then
        ln -vsf lib$name.so.$major.$minor.$micro ${path_build}libraries/shared/lib$name.so.$major || failure=1
        ln -vsf lib$name.so.$major ${path_build}libraries/shared/lib$name.so || failure=1
      fi
    fi

    if [[ $failure == "" && $sources_program != "" ]] ; then
      sources=
      links=

      if [[ $sources_library != "" ]] ; then
        links="-l$name "
      fi

      for i in $sources_program ; do
        sources="$sources$path_c$i "
      done

      echo $compiler $sources -o ${path_build}programs/shared/$name $arguments_shared $arguments_include $links $libraries $flags_all $flags_shared $flags_program
      $compiler $sources -o ${path_build}programs/shared/$name $arguments_shared $arguments_include $links $libraries $flags_all $flags_shared $flags_program || failure=1
    fi
  fi

  if [[ $failure == "" && $static == "yes" ]] ; then
    sources=
    if [[ $sources_library != "" ]] ; then
      for i in $sources_library ; do
        directory=$(dirname $i)
        n=$(basename $i | sed -e 's|\.c$||')

        if [[ $directory != "." && ! -d ${path_build}objects/$directory ]] ; then
          mkdir -vp ${path_build}objects/$directory

          if [[ $? -ne 0 ]] ; then
            failure=1
            break;
          fi
        fi

        sources="$sources${path_build}objects/$directory/$n.o "

        echo $compiler $path_c$i -c -static -o ${path_build}objects/$directory/$n.o $arguments_static $arguments_include $libraries $flags_all $flags_static $flags_library
        $compiler $path_c$i -c -static -o ${path_build}objects/$directory/$n.o $arguments_static $arguments_include $libraries $flags_all $flags_static $flags_library || failure=1

        if [[ $failure == "1" ]] ; then
          break;
        fi
      done

      if [[ $failure == "" ]] ; then
        echo $linker rcs ${path_build}libraries/static/lib$name.a $sources
        $linker rcs ${path_build}libraries/static/lib$name.a $sources || failure=1
      fi
    fi

    if [[ $failure == "" && $sources_program != "" ]] ; then
      sources=
      links=

      if [[ $sources_library != "" ]] ; then
        links="-l$name "
      fi

      for i in $sources_program ; do
        sources="$sources$path_c$i "
      done

      echo $compiler $sources -static -o ${path_build}programs/static/$name $arguments_static $arguments_include $links $libraries $flags_all $flags_static $flags_program
      $compiler $sources -static -o ${path_build}programs/static/$name $arguments_static $arguments_include $links $libraries $flags_all $flags_static $flags_program || failure=1
    fi
  fi

  if [[ $failure != "" ]] ; then
    echo -e "${c_error}ERROR: failed to build.$c_reset"
    bootstrap_cleanup
    exit $failure
  fi

  touch ${project_built}.built
}

bootstrap_operation_clean() {
  local i=

  for i in ${path_build}{documents,includes,libraries,objects,programs,settings,stage} ; do
    if [[ -e $i ]] ; then
      rm -vRf $i
    fi
  done

  if [[ -f ${project_built}.prepared ]] ; then
    rm -vf ${project_built}.prepared
  fi

  if [[ -f ${project_built}.built ]] ; then
    rm -vf ${project_built}.built
  fi
}

bootstrap_cleanup() {
  unset bootstrap_main
  unset bootstrap_handle_colors
  unset bootstrap_help
  unset bootstrap_id
  unset bootstrap_load_settings
  unset bootstrap_load_settings_mode
  unset bootstrap_prepare_build
  unset bootstrap_operation_build
  unset bootstrap_operation_clean
  unset bootstrap_cleanup
}

bootstrap_main $*

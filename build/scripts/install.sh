#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple installer tool to copy any part of the FLL project onto a system.
# This assumes the destination directories already exist and does not attempt to create them.
# Ideally, the package manager of the system should be used, but this is provided as a guide or a fallback.
# Settings files are not copied over, but a warning will be printed to inform the installer of their existence.
# The dependencies of this script are: bash, grep, and sed.

install_main() {
  local public_name="Simple FLL Project Install Script"
  local system_name=install
  local called_name=$(basename $0)
  local version=0.5.4

  local grab_next=
  local do_color=normal
  local do_help=
  local i=0
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
  local settings_file=data/build/settings
  local operation=
  local operation_failure=
  local verbosity="normal"
  local verbose=

  local path_build=build/
  local path_programs=programs/
  local path_includes=includes/
  local path_libraries=libraries/
  local path_settings=settings/
  local path_static=static/
  local path_shared=shared/

  local destination_prefix=/usr/local/
  local destination_programs=bin/
  local destination_includes=include/
  local destination_libraries=lib/
  local destination_libraries_static=
  local destination_libraries_shared=
  local destination_programs_static=
  local destination_programs_shared=

  local work=

  local enable_shared=
  local enable_shared_programs=
  local enable_shared_libraries=
  local enable_static=
  local enable_static_programs=
  local enable_static_libraries=
  local enable_includes="yes"

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
        elif [[ $p == "+q" || $p == "++quiet" ]] ; then
          verbosity="quiet"
          verbose=
        elif [[ $p == "+v" || $p == "++version" ]] ; then
          echo $version
          return
        elif [[ $p == "+V" || $p == "++verbose" ]] ; then
          verbosity="verbose"
          verbose="-v"
        elif [[ $p == "-b" || $p == "--build" ]] ; then
          grab_next=path_build
        elif [[ $p == "-s" || $p == "--settings" ]] ; then
          grab_next=settings_file
        elif [[ $p == "-P" || $p == "--prefix" ]] ; then
          grab_next=prefix
        elif [[ $p == "-B" || $p == "--bindir" ]] ; then
          grab_next=bindir
        elif [[ $p == "-I" || $p == "--includedir" ]] ; then
          grab_next=includedir
        elif [[ $p == "-L" || $p == "--libdir" ]] ; then
          grab_next=libdir
        elif [[ $p == "-w" || $p == "--work" ]] ; then
          grab_next=work
        elif [[ $p == "--enable-shared" ]] ; then
          enable_shared="yes"
        elif [[ $p == "--disable-shared" ]] ; then
          enable_shared="no"
        elif [[ $p == "--disable-shared-programs" ]] ; then
          enable_shared_programs="no"
        elif [[ $p == "--disable-shared-libraries" ]] ; then
          enable_shared_libraries="no"
        elif [[ $p == "--disable-static-programs" ]] ; then
          enable_static_programs="no"
        elif [[ $p == "--disable-static-libraries" ]] ; then
          enable_static_libraries="no"
        elif [[ $p == "--enable-static" ]] ; then
          enable_static="yes"
        elif [[ $p == "--disable-static" ]] ; then
          enable_static="no"
        elif [[ $p == "--enable-includes" ]] ; then
          enable_includes="yes"
        elif [[ $p == "--disable-includes" ]] ; then
          enable_includes="no"
        elif [[ $p == "--libraries-static" ]] ; then
          grab_next="destination_libraries_static"
        elif [[ $p == "--libraries-shared" ]] ; then
          grab_next="destination_libraries_shared"
        elif [[ $p == "--programs-static" ]] ; then
          grab_next="destination_programs_static"
        elif [[ $p == "--programs-shared" ]] ; then
          grab_next="destination_programs_shared"
        elif [[ $operation_failure == "" ]] ; then
          operation="$p"
          operation_failure=fail-unsupported
        fi
      else
        if [[ $grab_next == "path_build" ]] ; then
          path_build=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "settings_file" ]] ; then
          settings_file=$(echo $p | sed -e 's|^//*|/|' -e 's|^//*|/|')
        elif [[ $grab_next == "prefix" ]] ; then
          destination_prefix=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "bindir" ]] ; then
          destination_programs=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "includedir" ]] ; then
          destination_includes=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "libdir" ]] ; then
          destination_libraries=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "work" ]] ; then
          work=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "destination_libraries_static" ]] ; then
          destination_libraries_static=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "destination_libraries_shared" ]] ; then
          destination_libraries_shared=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "destination_programs_static" ]] ; then
          destination_programs_static=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "destination_programs_shared" ]] ; then
          destination_programs_shared=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        fi

        grab_next=
      fi
    done

    p=
  fi

  install_handle_colors

  if [[ $do_help == "yes" ]] ; then
    install_help
    install_cleanup
    return 0
  fi

  if [[ $operation_failure == "fail-unsupported" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ ! -d $path_build ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the build path $c_notice$path_build$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && $destination_prefix != "" && ! -d $destination_prefix ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination prefix $c_notice$destination_prefix$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $destination_prefix != "" ]] ; then
    if [[ $(echo $destination_programs | grep -o '^/') == "" ]] ; then
      destination_programs="$destination_prefix$destination_programs"
    fi

    if [[ $(echo $destination_includes | grep -o '^/') == "" ]] ; then
      destination_includes="$destination_prefix$destination_includes"
    fi

    if [[ $(echo $destination_libraries | grep -o '^/') == "" ]] ; then
      destination_libraries="$destination_prefix$destination_libraries"
    fi
  fi

  if [[ $destination_libraries_static != "" ]] ; then
    if [[ $(echo $destination_libraries_static | grep -o '^/') == "" ]] ; then
      destination_libraries_static=$destination_libraries$destination_libraries_static
    fi
  else
    destination_libraries_static=$destination_libraries
  fi

  if [[ $destination_libraries_shared != "" ]] ; then
    if [[ $(echo $destination_libraries_shared | grep -o '^/') == "" ]] ; then
      destination_libraries_shared=$destination_libraries$destination_libraries_shared
    fi
  else
    destination_libraries_shared=$destination_libraries
  fi

  if [[ $destination_programs_static != "" ]] ; then
    if [[ $(echo $destination_programs_static | grep -o '^/') == "" ]] ; then
      destination_programs_static=$destination_programs$destination_programs_static
    fi
  else
    destination_programs_static=$destination_programs
  fi

  if [[ $destination_programs_shared != "" ]] ; then
    if [[ $(echo $destination_programs_shared | grep -o '^/') == "" ]] ; then
      destination_programs_shared=$destination_programs$destination_programs_shared
    fi
  else
    destination_programs_shared=$destination_programs
  fi

  if [[ $work != "" && ! -d $work ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the work directory $c_notice$work$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && ! -d $destination_programs ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination bindir $c_notice$destination_programs$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && ! -d $destination_programs_static ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination (static) bindir $c_notice$destination_programs_static$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && ! -d $destination_programs_shared ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination (shared) bindir $c_notice$destination_programs_shared$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && ! -d $destination_includes ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination incluedir $c_notice$destination_includes$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && ! -d $destination_libraries_static ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination (static) libdir $c_notice$destination_libraries_static$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  if [[ $work == "" && ! -d $destination_libraries_shared ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the destination (shared) libdir $c_notice$destination_libraries_shared$c_error is not a valid directory.$c_reset"
    fi

    install_cleanup
    return 1
  fi

  install_load_settings

  install_perform_install

  install_cleanup
  return 0
}

install_handle_colors() {
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

install_help() {
  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset"
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen."
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds."
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color."
  echo -e " +${c_important}q$c_reset, ++${c_important}quiet$c_reset     Decrease verbosity beyond normal output."
  echo -e " +${c_important}V$c_reset, ++${c_important}verbose$c_reset   Increase verbosity beyond normal output."
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program."
  echo
  echo -e "${c_highlight}Install Options:$c_reset"
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}       Custom build directory."
  echo -e " -${c_important}s$c_reset, --${c_important}settings${c_reset}    Custom build settings file."
  echo -e " -${c_important}P$c_reset, --${c_important}prefix${c_reset}      Custom destination prefix."
  echo -e " -${c_important}B$c_reset, --${c_important}bindir${c_reset}      Custom destination bin/ directory."
  echo -e " -${c_important}I$c_reset, --${c_important}includedir${c_reset}  Custom destination include/ directory."
  echo -e " -${c_important}L$c_reset, --${c_important}libdir${c_reset}      Custom destination lib/ directory."
  echo -e " -${c_important}w$c_reset, --${c_important}work${c_reset}        Install to this directory instead of system."
  echo
  echo -e "${c_highlight}Special Options:$c_reset"
  echo -e " --${c_important}enable-shared${c_reset}             Forcibly do install shared files."
  echo -e " --${c_important}disable-shared${c_reset}            Forcibly do not install shared files."
  echo -e " --${c_important}disable-shared-programs${c_reset}   Forcibly do not install shared programs."
  echo -e " --${c_important}disable-shared-libraries${c_reset}  Forcibly do not install shared libraries."
  echo -e " --${c_important}enable-static${c_reset}             Forcibly do install static files."
  echo -e " --${c_important}disable-static${c_reset}            Forcibly do not install static files."
  echo -e " --${c_important}disable-static-programs${c_reset}   Forcibly do not install shared programs."
  echo -e " --${c_important}disable-static-libraries${c_reset}  Forcibly do not install shared libraries."
  echo -e " --${c_important}enable-includes${c_reset}           Forcibly do not install include files."
  echo -e " --${c_important}disable-includes${c_reset}          Forcibly do not install include files."
  echo -e " --${c_important}libraries-static${c_reset}          Custom destination for static libraries."
  echo -e " --${c_important}libraries-shared${c_reset}          Custom destination for shared libraries."
  echo -e " --${c_important}programs-static${c_reset}           Custom destination for static programs."
  echo -e " --${c_important}programs-shared${c_reset}           Custom destination for shared programs."
  echo
}

install_id() {
  local name=$1

  case $name in
    "build_sources_library") echo -n 1;;
    "build_sources_program") echo -n 2;;
    "build_sources_headers") echo -n 3;;
    "build_sources_setting") echo -n 4;;
    "build_shared") echo -n 5;;
    "build_static") echo -n 6;;
  esac
}

install_load_settings() {
  local failure=
  local i=

  if [[ $settings_file == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: no settings file has been defined.$c_reset"
    fi

    failure=1
  elif [[ ! -f $settings_file ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: no settings file $c_notice$settings_file$c_error could not be found or is not a valid file.$c_reset"
    fi

    failure=1
  fi

  if [[ $failure != "" ]] ; then
    install_cleanup
    exit $failure
  fi

  for i in build_sources_library build_sources_program build_sources_headers build_sources_setting build_shared build_static ; do
    variables[$(install_id $i)]=$(grep -s -o "^[[:space:]]*$i\>.*$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')
  done
}

install_perform_install() {
  local build_sources_library=${variables[$(install_id build_sources_library)]}
  local build_sources_program=${variables[$(install_id build_sources_program)]}
  local build_sources_headers=${variables[$(install_id build_sources_headers)]}
  local build_sources_setting=${variables[$(install_id build_sources_setting)]}
  local build_shared=${variables[$(install_id build_shared)]}
  local build_static=${variables[$(install_id build_static)]}
  local failure=

  if [[ $build_shared == "yes" ]] ; then
    if [[ $enable_shared == "" ]] ; then
      enable_shared="yes"
    fi

    if [[ $enable_shared == "no" ]] ; then
      enable_shared_programs="no"
      enable_shared_libraries="no"
    else
      if [[ $enable_shared_programs == "" ]] ; then
        enable_shared_programs="yes"
      fi

      if [[ $enable_shared_libraries == "" ]] ; then
        enable_shared_libraries="yes"
      fi
    fi
  elif [[ $build_shared == "no" ]] ; then
    if [[ $enable_shared == "" ]] ; then
      enable_shared="no"
    fi

    if [[ $enable_shared == "no" ]] ; then
      enable_shared_programs="no"
      enable_shared_libraries="no"
    else
      if [[ $enable_shared_programs == "" ]] ; then
        enable_shared_programs="yes"
      fi

      if [[ $enable_shared_libraries == "" ]] ; then
        enable_shared_libraries="yes"
      fi
    fi
  else
    if [[ $enable_shared == "" ]] ; then
      enable_shared="yes"
    fi

    if [[ $enable_shared_programs == "" ]] ; then
      enable_shared_programs="yes"
    fi

    if [[ $enable_shared_libraries == "" ]] ; then
      enable_shared_libraries="yes"
    fi
  fi

  if [[ $build_static == "yes" ]] ; then
    if [[ $enable_static == "" ]] ; then
      enable_static="yes"
    fi

    if [[ $enable_static == "no" ]] ; then
      enable_static_programs="no"
      enable_static_libraries="no"
    else
      if [[ $enable_static_programs == "" ]] ; then
        enable_static_programs="yes"
      fi

      if [[ $enable_static_libraries == "" ]] ; then
        enable_static_libraries="yes"
      fi
    fi
  elif [[ $build_static == "no" ]] ; then
    if [[ $enable_static == "" ]] ; then
      enable_static="no"
    fi

    if [[ $enable_static == "no" ]] ; then
      enable_static_programs="no"
      enable_static_libraries="no"
    else
      if [[ $enable_static_programs == "" ]] ; then
        enable_static_programs="yes"
      fi

      if [[ $enable_static_libraries == "" ]] ; then
        enable_static_libraries="yes"
      fi
    fi
  else
    if [[ $enable_static == "" ]] ; then
      enable_static="yes"
    fi

    if [[ $enable_static_programs == "" ]] ; then
      enable_static_programs="yes"
    fi

    if [[ $enable_static_libraries == "" ]] ; then
      enable_static_libraries="yes"
    fi
  fi

  if [[ $work != "" ]] ; then
    if [[ $build_sources_program != "" && ( $enable_shared_programs == "yes" || $enable_static_programs == "yes" ) ]] ; then
      if [[ ! -d ${work}programs ]] ; then
        mkdir $verbose ${work}programs

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}programs$c_error.$c_reset"
          fi

          failure=1
        fi
      fi

      if [[ $enable_shared_programs == "yes" && ! -d ${work}programs/shared ]] ; then
        mkdir $verbose ${work}programs/shared

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}programs/shared$c_error.$c_reset"
          fi

          failure=1
        fi
      fi

      if [[ $enable_static_programs == "yes" && ! -d ${work}programs/static ]] ; then
        mkdir $verbose ${work}programs/static

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}programs/static$c_error.$c_reset"
          fi

          failure=1
        fi
      fi
    fi

    if [[ $build_sources_library != "" && ( $enable_shared_libraries == "yes" || $enable_static_libraries == "yes" ) ]] ; then
      if [[ ! -d ${work}libraries ]] ; then
        mkdir $verbose ${work}libraries

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}libraries$c_error.$c_reset"
          fi

          failure=1
        fi
      fi

      if [[ $enable_shared_libraries == "yes" && ! -d ${work}libraries/shared ]] ; then
        mkdir $verbose ${work}libraries/shared

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}libraries/shared$c_error.$c_reset"
          fi

          failure=1
        fi
      fi

      if [[ $enable_static_libraries == "yes" && ! -d ${work}libraries/static ]] ; then
        mkdir $verbose ${work}libraries/static

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}libraries/static$c_error.$c_reset"
          fi

          failure=1
        fi
      fi
    fi

    if [[ $build_sources_headers != "" && $enable_includes == "yes" ]] ; then
      if [[ ! -d ${work}includes ]] ; then
        mkdir $verbose ${work}includes

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: failed to create work directories $c_notice${work}includes$c_error.$c_reset"
          fi

          failure=1
        fi
      fi
    fi

    if [[ $failure == "" ]] ; then
      destination_prefix=$work
      destination_programs=${work}programs/
      destination_programs_static=${destination_programs}static/
      destination_programs_shared=${destination_programs}shared/
      destination_includes=${work}includes/
      destination_libraries=${work}libraries/
      destination_libraries_static=${destination_libraries}static/
      destination_libraries_shared=${destination_libraries}shared/
    fi
  fi

  if [[ $failure == "" && $build_sources_headers != "" && $enable_includes == "yes" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Installing Includes to: $c_reset$c_notice$destination_includes$c_reset${c_highlight}.$c_reset"
    fi

    cp $verbose -R $path_build${path_includes}* $destination_includes

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: failed to copy include files from $c_notice$path_build$path_includes$c_error to $c_notice$destination_includes$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure == "" && ( $enable_shared_libraries == "yes" || $enable_static_libraries == "yes" ) ]] ; then
    if [[ $enable_static_libraries == "yes" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo -e "${c_highlight}Installing (static) Libraries to: $c_reset$c_notice$destination_libraries_static$c_reset${c_highlight}.$c_reset"
      fi

      cp $verbose -R $path_build$path_libraries${path_static}* $destination_libraries_static

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: failed to copy (static) library files from $c_notice$path_build$path_libraries$path_static$c_error to $c_notice$destination_libraries_static$c_error.$c_reset"
        fi

        failure=1
      fi
    fi

    if [[ $failure == "" && $enable_shared_libraries == "yes" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo -e "${c_highlight}Installing (shared) Libraries to: $c_reset$c_notice$destination_libraries_shared$c_reset${c_highlight}.$c_reset"
      fi

      cp $verbose -R $path_build$path_libraries${path_shared}* $destination_libraries_shared

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: failed to copy (shared) library files from $c_notice$path_build$path_libraries$path_shared$c_error to $c_notice$destination_libraries_shared$c_error.$c_reset"
        fi

        failure=1
      fi
    fi
  fi

  if [[ $failure == "" && $build_sources_program != "" && ( $enable_shared_programs == "yes" || $enable_static_programs == "yes" ) ]] ; then
    if [[ $enable_static_programs == "yes" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo -e "${c_highlight}Installing (static) Programs to: $c_reset$c_notice$destination_programs_static$c_reset${c_highlight}.$c_reset"
      fi

      cp $verbose -R $path_build$path_programs${path_static}* $destination_programs_static

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: failed to copy (static) program files from $c_notice$path_build$path_programs$path_static$c_error to $c_notice$destination_programs_static$c_error.$c_reset"
        fi

        failure=1
      fi
    fi

    if [[ $failure == "" && $enable_shared_programs == "yes" ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo -e "${c_highlight}Installing (shared) Programs to: $c_reset$c_notice$destination_programs_shared$c_reset${c_highlight}.$c_reset"
      fi

      cp $verbose -R $path_build$path_programs${path_shared}* $destination_programs_shared

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: failed to copy (shared) program files from $c_notice$path_build$path_programs$path_shared$c_error to $c_notice$destination_programs_shared$c_error.$c_reset"
        fi

        failure=1
      fi
    fi
  fi

  if [[ $failure == "" && $build_sources_setting != "" && $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_warning}Settings Files Detected, see: $c_reset$c_notice$path_build$path_settings$c_reset${c_warning}.$c_reset"
  fi

  if [[ $failure != "" ]] ; then
    install_cleanup
    exit $failure
  fi
}

install_cleanup() {
  unset install_main
  unset install_handle_colors
  unset install_help
  unset install_id
  unset install_load_settings
  unset install_perform_install

  unset install_cleanup
}

install_main $*

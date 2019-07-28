#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple installer tool to copy any part of the FLL project onto a system.
# This assumes the destination directories already exist and does not attempt to create them.
# Ideally, the package manager of the system should be used, but this is provided as a guide or a fallback.
# Settings files are not copied over, but a warning will be printed to inform the installer of their existence.
# The dependencies of this script are: bash, grep, and sed.

install_main(){
  local public_name="Simple FLL Project Install Script"
  local system_name=install
  local called_name=$(basename $0)
  local version=0.4.3

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
        elif [[ $p == "-b" || $p == "--build" ]] ; then
          grab_next=path_build
        elif [[ $p == "-s" || $p == "--settings" ]] ; then
          grab_next=settings_file
        elif [[ $p == "-P" || $p == "--prefix" ]] ; then
          grab_next=prefix
        elif [[ $p == "-B" || $p == "--bindir" ]] ; then
          grab_next=bindir
        elif [[ $p == "-I" || $p == "--includedir" ]] ; then
          grab_next=includes
        elif [[ $p == "-L" || $p == "--libdir" ]] ; then
          grab_next=libraries
        elif [[ $p == "--enable-shared" ]] ; then
          enable_shared="yes"
        elif [[ $p == "--disable-shared" ]] ; then
          enable_shared="no"
        elif [[ $p == "--enable-static" ]] ; then
          enable_static="yes"
        elif [[ $p == "--disable-static" ]] ; then
          enable_static="no"
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
    exit 0
  fi

  if [[ $operation_failure == "fail-unsupported" ]] ; then
    echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
    exit 1
  else
    if [[ $prefix == "" && ! -d $path_build ]] ; then
      echo -e "${c_error}ERROR: the build path $c_notice$path_build$c_error is not a valid directory.$c_reset"
      exit 1
    fi

    if [[ $destination_prefix != "" && ! -d $destination_prefix ]] ; then
      echo -e "${c_error}ERROR: the destination prefix $c_notice$destination_prefix$c_error is not a valid directory.$c_reset"
      exit 1
    fi

    if [[ $destination_prefix != "" ]] ; then
      if [[ $(echo $destination_prefix | grep -o '^/') == "" ]] ; then
        destination_prefix="$destination_prefix$destination_prefix"
      fi

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

    if [[ ! -d $destination_programs ]] ; then
      echo -e "${c_error}ERROR: the destination bindir $c_notice$destination_programs$c_error is not a valid directory.$c_reset"
      exit 1
    fi

    if [[ ! -d $destination_includes ]] ; then
      echo -e "${c_error}ERROR: the destination incluedir $c_notice$destination_includes$c_error is not a valid directory.$c_reset"
      exit 1
    fi

    if [[ ! -d $destination_libraries ]] ; then
      echo -e "${c_error}ERROR: the destination libdir $c_notice$destination_libraries$c_error is not a valid directory.$c_reset"
      exit 1
    fi

    install_load_settings

    install_perform_install
  fi
}

install_handle_colors(){
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

install_help(){
  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset"
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen"
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds"
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color"
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program"
  echo
  echo -e "${c_highlight}Install Options:$c_reset"
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}       Specify a custom build directory"
  echo -e " -${c_important}s$c_reset, --${c_important}settings${c_reset}    Specify a custom build settings file"
  echo -e " -${c_important}P$c_reset, --${c_important}prefix${c_reset}      Specify a custom destination prefix"
  echo -e " -${c_important}B$c_reset, --${c_important}bindir${c_reset}      Specify a custom destination bin/ directory"
  echo -e " -${c_important}I$c_reset, --${c_important}includedir${c_reset}  Specify a custom destination include/ directory"
  echo -e " -${c_important}L$c_reset, --${c_important}libdir${c_reset}      Specify a custom destination lib/ directory"
  echo
  echo -e "${c_highlight}Special Options:$c_reset"
  echo -e " --${c_important}enable-shared${c_reset}   Forcibly do install shared files"
  echo -e " --${c_important}disable-shared${c_reset}  Forcibly do not install shared files"
  echo -e " --${c_important}enable-static${c_reset}   Forcibly do install static files"
  echo -e " --${c_important}disable-static${c_reset}  Forcibly do not install static files"
  echo
}

install_id(){
  local name=$1

  case $name in
    "build_sources_library") echo -n 1;;
    "build_sources_program") echo -n 2;;
    "build_sources_headers") echo -n 3;;
    "build_sources_settings") echo -n 4;;
    "build_shared") echo -n 5;;
    "build_static") echo -n 6;;
  esac
}

install_load_settings(){
  local failure=
  local i=

  if [[ $settings_file == "" ]] ; then
    echo -e "${c_error}ERROR: no settings file has been defined.$c_reset"
    failure=1
  elif [[ ! -f $settings_file ]] ; then
    echo -e "${c_error}ERROR: no settings file $c_notice$settings_file$c_error could not be found or is not a valid file.$c_reset"
    failure=1
  fi

  if [[ $failure != "" ]] ; then
    install_cleanup
    exit $failure
  fi

  for i in build_sources_library build_sources_program build_sources_headers build_sources_settings build_shared build_static ; do
    variables[$(install_id $i)]=$(grep -s -o "^[[:space:]]*$i\>.*$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')
  done
}

install_perform_install(){
  local build_sources_library=${variables[$(install_id build_sources_library)]}
  local build_sources_program=${variables[$(install_id build_sources_program)]}
  local build_sources_headers=${variables[$(install_id build_sources_headers)]}
  local build_sources_settings=${variables[$(install_id build_sources_settings)]}
  local build_shared=${variables[$(install_id build_shared)]}
  local build_static=${variables[$(install_id build_static)]}
  local failure=

  if [[ $enable_shared == "yes" ]] ; then
    build_shared="yes"
  elif [[ $enable_shared == "no" ]] ; then
    build_shared="no"
  fi

  if [[ $enable_static == "yes" ]] ; then
    build_static="yes"
  elif [[ $enable_static == "no" ]] ; then
    build_static="no"
  fi

  if [[ $build_sources_headers != "" ]] ; then
    echo
    echo -e "${c_highlight}Installing Includes to: $c_reset$c_notice$destination_includes$c_reset${c_highlight}.$c_reset"
    cp -vR $path_build${path_includes}* $destination_includes

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to copy include files from $c_notice$path_build$path_includes$c_error to $c_notice$destination_includes$c_error.$c_reset"
      failure=1
    fi
  fi

  if [[ $failure == "" && ( $build_sources_library != "" || $build_sources_program != "" ) ]] ; then
    if [[ $build_static == "yes" ]] ; then
      echo
      echo -e "${c_highlight}Installing (static) Libraries to: $c_reset$c_notice$destination_libraries$c_reset${c_highlight}.$c_reset"
      cp -vR $path_build$path_libraries${path_static}* $destination_libraries

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy (static) library files from $c_notice$path_build$path_libraries$path_static$c_error to $c_notice$destination_libraries$c_error.$c_reset"
        failure=1
      fi
    fi

    if [[ $failure == "" && $build_shared == "yes" ]] ; then
      echo
      echo -e "${c_highlight}Installing (shared) Libraries to: $c_reset$c_notice$destination_libraries$c_reset${c_highlight}.$c_reset"
      cp -vR $path_build$path_libraries${path_shared}* $destination_libraries

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy (shared) library files from $c_notice$path_build$path_libraries$build_shared$c_error to $c_notice$destination_libraries$c_error.$c_reset"
        failure=1
      fi
    fi
  fi

  if [[ $failure == "" && $build_sources_program != "" ]] ; then
    if [[ $build_static == "yes" ]] ; then
      echo
      echo -e "${c_highlight}Installing (static) Programs to: $c_reset$c_notice$destination_programs$c_reset${c_highlight}.$c_reset"
      cp -vR $path_build$path_programs${path_static}* $destination_programs

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy (static) library files from $c_notice$path_build$path_programs$path_static$c_error to $c_notice$destination_programs$c_error.$c_reset"
        failure=1
      fi
    fi

    if [[ $failure == "" && $build_shared == "yes" ]] ; then
      echo
      echo -e "${c_highlight}Installing (shared) Programs to: $c_reset$c_notice$destination_programs$c_reset${c_highlight}.$c_reset"
      cp -vR $path_build$path_programs${path_shared}* $destination_programs

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy (shared) library files from $c_notice$path_build$path_programs$build_shared$c_error to $c_notice$destination_programs$c_error.$c_reset"
        failure=1
      fi
    fi
  fi

  if [[ $failure == "" && $build_sources_settings != "" ]] ; then
    echo
    echo -e "${c_warning}Settings Files Detected, see: $c_reset$c_notice$path_build$path_settings$c_reset${c_warning}.$c_reset"
  fi

  if [[ $failure != "" ]] ; then
    install_cleanup
    exit $failure
  fi
}

install_cleanup(){
  unset install_main
  unset install_handle_colors
  unset install_help
  unset install_id
  unset install_load_settings
  unset install_perform_install

  unset install_cleanup
}

install_main $*
install_cleanup

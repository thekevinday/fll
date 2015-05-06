#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple bootstrap tool to compile any part of the FLL project.
# The dependencies of this script are: bash, grep, and sed.

generate_main(){
  local public_name="Simple FLL Project Make Script"
  local system_name=generate
  local called_name=$(basename $0)
  local version=0.4.2

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
  local path_build=build/
  local path_c=sources/c/
  local path_bash=sources/bash/
  local project_built=

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
        elif [[ $p == "-B" || $p == "--bash_path" ]] ; then
          grab_next=path_bash
        elif [[ $p == "-c" || $p == "--c_path" ]] ; then
          grab_next=path_c
        elif [[ $p == "-p" || $p == "--project" ]] ; then
          grab_next=project_built
        elif [[ $operation == "" ]] ; then
          operation=$p
        else
          operation=fail-multiple
        fi
      else
        if [[ $grab_next == "path_build" ]] ; then
          path_build=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "settings_file" ]] ; then
          settings_file=$(echo $p | sed -e 's|^//*|/|')
        elif [[ $grab_next == "path_bash" ]] ; then
          path_bash=$(echo $p | sed -e 's|/*$|/|')
        elif [[ $grab_next == "path_c" ]] ; then
          path_c=$(echo $p | sed -e 's|/*$|/|')
        elif [[ $grab_next == "project_built" ]] ; then
          project_built="-$(echo $p | sed -e 's|/*$||')"
        fi

        grab_next=
      fi
    done

    p=
  fi

  generate_handle_colors

  if [[ $do_help == "yes" ]] ; then
    generate_help
    generate_cleanup
    exit 0
  fi

  generate_load_settings

  # TODO: enable when bash support is implemented
  #if [[ ! -d $path_bash ]] ; then
  #  echo -e "${c_error}ERROR: the bash path of $c_notice$path_bash$c_error is invalid.$c_reset"
  #  generate_cleanup
  #  exit 0
  #fi

  if [[ ! -d $path_c && ( ${variables[$(generate_id build_sources_library)]} != "" || ${variables[$(generate_id build_sources_program)]} != "" || ${variables[$(generate_id build_sources_headers)]} != "" ) ]] ; then
    echo -e "${c_error}ERROR: the c path of '$c_notice$path_c$c_error' is invalid.$c_reset"
    generate_cleanup
    exit 0
  fi

  if [[ $operation == "build" ]] ; then
    if [[ -f ${path_build}.built$project_built ]] ; then
      echo -e "${c_warning}WARNING: this project has already been built.$c_reset"
    else
      if [[ ! -f ${path_build}.prepared$project_built ]] ; then
        generate_prepare_build
      fi

      generate_operation_build
    fi
  elif [[ $operation == "clean" ]] ; then
    generate_operation_clean
  elif [[ $operation == "fail-multiple" ]] ; then
    echo -e "${c_error}ERROR: only one operation may be specified at a time.$c_reset"
  elif [[ $operation == "" ]] ; then
    echo -e "${c_error}ERROR: no operation was given.$c_reset"
  else
    echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
  fi
}

generate_handle_colors(){
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

generate_help(){
  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset $c_notice<${c_reset}operation$c_notice>$c_reset"
  echo -e " ${c_important}build${c_reset}      Build or compile the code"
  echo -e " ${c_important}clean${c_reset}      Delete all build files"
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen"
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds"
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color"
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program"
  echo
  echo -e "${c_highlight}Generate Options:$c_reset"
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}          Specify a custom build directory"
  echo -e " -${c_important}s$c_reset, --${c_important}settings${c_reset}       Specify a custom build settings file"
  echo -e " -${c_important}B$c_reset, --${c_important}bash_path${c_reset}      Specify a custom path to the bash source files"
  echo -e " -${c_important}c$c_reset, --${c_important}c_path${c_reset}         Specify a custom path to the c source files"
  echo -e " -${c_important}p$c_reset, --${c_important}project${c_reset}        Specify a project name for storing built status"
  echo
}

generate_id(){
  local name=$1

  case $name in
    "project_name") echo -n 0;;
    "project_level") echo -n 1;;
    "version_major") echo -n 2;;
    "version_minor") echo -n 3;;
    "version_micro") echo -n 4;;
    "build_compiler") echo -n 5;;
    "build_linker") echo -n 6;;
    "build_libraries") echo -n 7;;
    "build_sources_library") echo -n 8;;
    "build_sources_program") echo -n 9;;
    "build_sources_headers") echo -n 10;;
    "build_sources_settings") echo -n 11;;
    "build_shared") echo -n 12;;
    "build_static") echo -n 13;;
    "flags_all") echo -n 14;;
    "flags_shared") echo -n 15;;
    "flags_static") echo -n 16;;
    "flags_library") echo -n 17;;
    "flags_program") echo -n 18;;
  esac
}

generate_load_settings(){
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
    generate_cleanup
    exit $failure
  fi

  for i in project_name project_level version_major version_minor version_micro build_compiler build_linker build_libraries build_sources_library build_sources_program build_sources_headers build_sources_settings build_shared build_static flags_all flags_shared flags_static flags_library flags_program ; do
    variables[$(generate_id $i)]=$(grep -s -o "^[[:space:]]*$i\>.*$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')
  done

  if [[ $project_name == "" ]] ; then
    if [[ $variables['project_name'] != "" ]] ; then
      project_built="-${variables['project_name']}"
    fi
  fi
}

generate_prepare_build(){
  local failure=
  local level=${variables[$(generate_id project_level)]}
  local alt=$1

  mkdir -vp ${path_build}{includes,programs/{shared,static},libraries/{shared,static},settings} || failure=1

  if [[ $failure == "" && $level != "" ]] ; then
    mkdir -vp ${path_build}includes/level_$level || failure=1
  fi

  if [[ $failure == "" ]] ; then
    for i in $headers ; do
      ln -vsf ../../$i ${path_build}includes/level_$level/

      if [[ $? != 0 ]] ; then
        failure=1
        break
      fi
    done
  fi

  if [[ $failure != "" ]] ; then
    generate_cleanup
    exit $failure
  fi

  touch ${path_build}.prepared$project_built
}

generate_operation_build(){
  local failure=
  local name=${variables[$(generate_id project_name)]}
  local level=${variables[$(generate_id project_level)]}
  local major=${variables[$(generate_id version_major)]}
  local minor=${variables[$(generate_id version_minor)]}
  local micro=${variables[$(generate_id version_micro)]}
  local compiler=${variables[$(generate_id build_compiler)]}
  local linker=${variables[$(generate_id build_linker)]}
  local arguments="-I${path_build}includes -L${path_build}libraries ${variables[$(generate_id flags_all)]} ${variables[$(generate_id build_libraries)]}"
  local shared=${variables[$(generate_id build_shared)]}
  local static=${variables[$(generate_id build_static)]}
  local sources_library=${variables[$(generate_id build_sources_library)]}
  local sources_program=${variables[$(generate_id build_sources_program)]}
  local sources_headers=${variables[$(generate_id build_sources_headers)]}
  local sources_settings=${variables[$(generate_id build_sources_settings)]}
  local sources=
  local i=
  local alt=$1


  if [[ $shared != "yes" && $static != "yes" ]] ;then
    echo -e "${c_error}ERROR: Cannot Build, either build_shared or build_static must be set to 'yes'.$c_reset"
    generate_cleanup
    exit -1
  fi

  if [[ $sources_settings != "" ]] ; then
    for i in $sources_settings ; do
      cp -vf $path_c$i ${path_build}settings/ || failure=1
    done
  fi

  if [[ $failure == "" && $sources_headers != "" ]] ; then
    for i in $sources_headers ; do
      cp -vf $path_c$i ${path_build}includes/level_$level/ || failure=1
    done
  fi

  if [[ $failure == "" && $shared == "yes" ]] ; then
    if [[ $sources_library != "" ]] ; then
      sources=
      for i in $sources_library ; do
        sources="$sources$path_c$i "
      done

      echo $compiler $sources -shared -Wl,-soname,lib$name.so.$major -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments ${variables[$(generate_id flags_shared)]} ${variables[$(generate_id flags_library)]}
      $compiler $sources -shared -Wl,-soname,lib$name.so.$major -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments ${variables[$(generate_id flags_shared)]} ${variables[$(generate_id flags_library)]} || failure=1

      if [[ $failure == "" ]] ; then
        ln -vsf lib$name.so.$major.$minor.$micro ${path_build}libraries/shared/lib$name.so.$major || failure=1
        ln -vsf lib$name.so.$major ${path_build}libraries/shared/lib$name.so || failure=1
      fi
    fi

    if [[ $failure == "" && $sources_program != "" ]] ; then
      sources=
      if [[ $sources_library != "" ]] ; then
        for i in $sources_library ; do
          sources="$sources$path_c$i "
        done
      fi

      for i in $sources_program ; do
        sources="$sources$path_c$i "
      done

      echo $compiler $sources -o ${path_build}programs/shared/$name $arguments ${variables[$(generate_id flags_shared)]} ${variables[$(generate_id flags_program)]}
      $compiler $sources -o ${path_build}programs/shared/$name $arguments ${variables[$(generate_id flags_shared)]} ${variables[$(generate_id flags_program)]} || failure=1
    fi
  fi

  if [[ $failure == "" && $static == "yes" ]] ; then
    sources=
    if [[ $sources_library != "" ]] ; then
      for i in $sources_library ; do
        sources="$sources${path_build}libraries/$i.o "

        echo $compiler $path_c$i -c -static -o ${path_build}libraries/static/$i.o $arguments ${variables[$(generate_id flags_static)]} ${variables[$(generate_id flags_library)]}
        $compiler $path_c$i -c -static -o ${path_build}libraries/static/$i.o $arguments ${variables[$(generate_id flags_static)]} ${variables[$(generate_id flags_library)]} || failure=1

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
      if [[ $sources_library != "" ]] ; then
        for i in $sources_library ; do
          sources="$sources$path_c$i "
        done
      fi

      for i in $sources_program ; do
        sources="$sources$path_c$i "
      done

      echo $compiler -static -o ${path_build}programs/static/$name $sources $arguments ${variables[$(generate_id flags_static)]} ${variables[$(generate_id flags_program)]}
      $compiler -static -o ${path_build}programs/static/$name $sources $arguments ${variables[$(generate_id flags_static)]} ${variables[$(generate_id flags_program)]} || failure=1
    fi
  fi

  if [[ $failure != "" ]] ; then
    echo -e "${c_error}ERROR: failed to build.$c_reset"
    generate_cleanup
    exit $failure
  fi

  touch ${path_build}.built$project_built
}

generate_operation_clean(){
  local i=

  for i in ${path_build}{includes,programs,libraries,settings} ; do
    if [[ -e $i ]] ; then
      rm -vRf $i
    fi
  done

  if [[ -f ${path_build}.prepared$project_built ]] ; then
    rm -vf ${path_build}.prepared$project_built
  fi

  if [[ -f ${path_build}.built$project_built ]] ; then
    rm -vf ${path_build}.built$project_built
  fi
}

generate_cleanup(){
  unset generate_main
  unset generate_handle_colors
  unset generate_help
  unset generate_id
  unset generate_load_settings
  unset generate_prepare_build
  unset generate_operation_build
  unset generate_operation_clean
  unset generate_cleanup
}

generate_main $*
generate_cleanup

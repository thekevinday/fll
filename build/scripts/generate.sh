#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple bootstrap tool to compile any part of the FLL project.
# The dependencies of this script are: bash, dirname, grep, and sed.

generate_main(){
  local public_name="Simple FLL Project Make Script"
  local system_name=generate
  local called_name=$(basename $0)
  local version=0.5.0

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

  local build_libraries_fll="build_libraries_fll"
  local variables=
  local settings_file=
  local settings_defines=
  local operation=
  local operation_failure=
  local path_build=build/
  local path_build_settings=
  local path_c=sources/c/
  local path_settings=data/settings/
  local path_bash=
  local project_built=
  local work_directory=
  local defines_override=

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
          grab_next=build_settings
        elif [[ $p == "-B" || $p == "--path_bash" ]] ; then
          grab_next=path_bash
        elif [[ $p == "-c" || $p == "--path_c" ]] ; then
          grab_next=path_c
        elif [[ $p == "-S" || $p == "--path_settings" ]] ; then
          grab_next=path_settings
        elif [[ $p == "-p" || $p == "--project" ]] ; then
          grab_next=project_built
        elif [[ $p == "-w" || $p == "--work_directory" ]] ; then
          grab_next=work_directory
        elif [[ $p == "-d" || $p == "--defines" ]] ; then
          grab_next=defines_override
        elif [[ $p == "-l" || $p == "--level" ]] ; then
          build_libraries_fll="build_libraries_fll-level"
        elif [[ $p == "-m" || $p == "--monolithic" ]] ; then
          build_libraries_fll="build_libraries_fll-monolithic"
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
        if [[ $grab_next == "path_build" ]] ; then
          path_build=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "build_settings" ]] ; then
          path_build_settings=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_bash" ]] ; then
          path_bash=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_c" ]] ; then
          path_c=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_settings" ]] ; then
          path_settings=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "project_built" ]] ; then
          project_built="-$(echo $p | sed -e 's|/*$||')"
        elif [[ $grab_next == "work_directory" ]] ; then
          work_directory=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "defines_override" ]] ; then
          defines_override="$p"
        fi

        grab_next=
      fi
    done

    p=
  fi

  if [[ $path_build_settings == "" ]] ; then
    path_build_settings=data/build/
  fi

  settings_file=${path_build_settings}settings
  settings_defines=${path_build_settings}defines

  generate_handle_colors

  if [[ $do_help == "yes" ]] ; then
    generate_help
    generate_cleanup
    exit 0
  fi

  generate_load_settings

  if [[ $path_bash == "" ]] ; then
    path_bash=sources/bash/
  elif [[ ! -d $path_bash ]] ; then
    echo -e "${c_error}ERROR: the bash path of $c_notice$path_bash$c_error is not a valid directory.$c_reset"
    generate_cleanup
    exit 0
  fi

  if [[ $work_directory != "" && ! -d $work_directory ]] ; then
    echo -e "${c_error}ERROR: the work directory $c_notice$work_directory$c_error is not a valid directory.$c_reset"
    exit 1
  fi

  if [[ $defines_override != "" && $(echo "$defines_override" | grep -s -o "[^_[:alnum:][:space:]]") != "" ]] ; then
    echo -e "${c_error}ERROR: the defines override $c_notice$defines_override$c_error includes invalid characters, only alphanumeric, whitespace, and underscore are allowed.$c_reset"
    exit 1
  fi

  if [[ ! -d $path_c && ( ${variables[$(generate_id build_sources_library)]} != "" || ${variables[$(generate_id build_sources_program)]} != "" || ${variables[$(generate_id build_sources_headers)]} != "" ) ]] ; then
    echo -e "${c_error}ERROR: the c path of '$c_notice$path_c$c_error' is invalid.$c_reset"
    generate_cleanup
    exit 1
  fi

  if [[ $operation_failure == "fail-multiple" ]] ; then
    echo -e "${c_error}ERROR: only one operation may be specified at a time.$c_reset"
    exit 1
  elif [[ $operation == "build" ]] ; then
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
  elif [[ $operation == "" ]] ; then
    echo -e "${c_error}ERROR: no operation was given.$c_reset"
    exit 1
  else
    echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
    exit 1
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
  echo -e " ${c_important}build${c_reset}  Build or compile the code"
  echo -e " ${c_important}clean${c_reset}  Delete all build files"
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen"
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds"
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color"
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program"
  echo
  echo -e "${c_highlight}Generate Options:$c_reset"
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}           Custom build directory"
  echo -e " -${c_important}s$c_reset, --${c_important}settings${c_reset}        Custom build settings directory"
  echo -e " -${c_important}B$c_reset, --${c_important}path_bash${c_reset}       Custom path to the bash source files"
  echo -e " -${c_important}c$c_reset, --${c_important}path_c${c_reset}          Custom path to the c source files"
  echo -e " -${c_important}S$c_reset, --${c_important}path_settings${c_reset}   Custom path to the settings files"
  echo -e " -${c_important}p$c_reset, --${c_important}project${c_reset}         Project name for storing built status"
  echo -e " -${c_important}w$c_reset, --${c_important}work_directory${c_reset}  Use includes/libraries from this directory instead of system"
  echo -e " -${c_important}d$c_reset, --${c_important}defines${c_reset}         Override custom defines with these defines"
  echo -e " -${c_important}l$c_reset, --${c_important}level${c_reset}           Use FLL dependencies by level (-lfll_0, -lfll_1, -lfll_2)"
  echo -e " -${c_important}m$c_reset, --${c_important}monolithic${c_reset}      Use FLL dependencies by monolithic (-lfll)"
  echo
  echo -e "${c_highlight}Special Options:$c_reset"
  echo -e " --${c_important}enable-shared${c_reset}   Forcibly do install shared files"
  echo -e " --${c_important}disable-shared${c_reset}  Forcibly do not install shared files"
  echo -e " --${c_important}enable-static${c_reset}   Forcibly do install static files"
  echo -e " --${c_important}disable-static${c_reset}  Forcibly do not install static files"
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
    "$build_libraries_fll") echo -n 8;;
    "build_sources_library") echo -n 9;;
    "build_sources_program") echo -n 10;;
    "build_sources_headers") echo -n 11;;
    "build_sources_bash") echo -n 12;;
    "build_sources_settings") echo -n 13;;
    "build_shared") echo -n 14;;
    "build_static") echo -n 15;;
    "defines_all") echo -n 16;;
    "defines_shared") echo -n 17;;
    "defines_static") echo -n 18;;
    "flags_all") echo -n 19;;
    "flags_shared") echo -n 20;;
    "flags_static") echo -n 21;;
    "flags_library") echo -n 22;;
    "flags_program") echo -n 23;;
  esac
}

generate_load_settings(){
  local failure=
  local i=
  local key=

  if [[ ! -d $path_build_settings ]] ; then
    echo -e "${c_error}ERROR: no build settings directory $c_notice$path_build_settings$c_error could not be found or is not a valid directory.$c_reset"
    failure=1
  elif [[ ! -f $settings_file ]] ; then
    echo -e "${c_error}ERROR: no settings file $c_notice$settings_file$c_error could not be found or is not a valid file.$c_reset"
    failure=1
  fi

  if [[ $failure != "" ]] ; then
    generate_cleanup
    exit $failure
  fi

  for i in project_name project_level version_major version_minor version_micro build_compiler build_linker build_libraries $build_libraries_fll build_sources_library build_sources_program build_sources_headers build_sources_settings build_shared build_static defines_all defines_shared defines_static flags_all flags_shared flags_static flags_library flags_program ; do
    variables[$(generate_id $i)]=$(grep -s -o "^[[:space:]]*$i[[:space:]].*\$" $settings_file | sed -e "s|^[[:space:]]*$i\>||" -e 's|^[[:space:]]*||')
  done

  if [[ $project_name == "" ]] ; then
    key="project_name"
    if [[ ${variables[$key]} != "" ]] ; then
      project_built="-${variables[$key]}"
    fi
  fi
}

generate_prepare_build(){
  local failure=
  local level=${variables[$(generate_id project_level)]}
  local alt=$1

  mkdir -vp ${path_build}{includes,programs/{shared,static},libraries/{shared,static},objects,bash,settings} || failure=1

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
  local arguments="${variables[$(generate_id "$build_libraries_fll")]} ${variables[$(generate_id build_libraries)]}"
  local arguments_include="-I${path_build}includes"
  local arguments_shared="-L${path_build}libraries/shared"
  local arguments_static="-L${path_build}libraries/static"
  local shared=${variables[$(generate_id build_shared)]}
  local static=${variables[$(generate_id build_static)]}
  local sources_library=${variables[$(generate_id build_sources_library)]}
  local sources_program=${variables[$(generate_id build_sources_program)]}
  local sources_headers=${variables[$(generate_id build_sources_headers)]}
  local sources_bash=${variables[$(generate_id build_sources_bash)]}
  local sources_settings=${variables[$(generate_id build_sources_settings)]}
  local sources=
  local defines=${variables[$(generate_id defines_all)]}
  local defines_shared=${variables[$(generate_id defines_shared)]}
  local defines_static=${variables[$(generate_id defines_static)]}
  local flags_all=${variables[$(generate_id flags_all)]}
  local flags_shared=${variables[$(generate_id flags_shared)]}
  local flags_static=${variables[$(generate_id flags_static)]}
  local flags_library=${variables[$(generate_id flags_library)]}
  local flags_program=${variables[$(generate_id flags_program)]}
  local i=
  local alt=$1
  local directory=

  if [[ $work_directory != "" ]] ; then
    flags_all="-I${work_directory}includes/ $flags_all"
    flags_shared="-L${work_directory}libraries/shared/ $flags_shared"
    flags_static="-L${work_directory}libraries/static/ $flags_static"
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
  elif [[ $enable_shared == "no" ]] ; then
    shared="no"
  fi

  if [[ $enable_static == "yes" ]] ; then
    static="yes"
  elif [[ $enable_static == "no" ]] ; then
    static="no"
  fi

  if [[ $shared != "yes" && $static != "yes" ]] ; then
    echo -e "${c_error}ERROR: Cannot Build, either build_shared or build_static must be set to 'yes'.$c_reset"
    generate_cleanup
    exit -1
  fi

  for i in $sources_library ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid source_library path provided: '$i'.$c_reset"
      generate_cleanup
      exit -1
    fi
  done

  for i in $sources_program ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_program path provided: '$i'.$c_reset"
      generate_cleanup
      exit -1
    fi
  done

  for i in $sources_headers ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_headers path provided: '$i'.$c_reset"
      generate_cleanup
      exit -1
    fi
  done

  for i in $sources_bash ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_bash path provided: '$i'.$c_reset"
      generate_cleanup
      exit -1
    fi
  done

  for i in $sources_settings ; do
    if [[ $i != "$(echo $i | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      echo -e "${c_error}ERROR: Cannot Build, invalid sources_settings path provided: '$i'.$c_reset"
      generate_cleanup
      exit -1
    fi
  done

  if [[ $sources_settings != "" ]] ; then
    for i in $sources_settings ; do
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
    if [[ $level == "" ]] ; then
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
        cp -vf $path_c$i ${path_build}includes/level_$level/ || failure=1
      done
    fi
  fi

  if [[ $failure == "" && $shared == "yes" ]] ; then
    if [[ $sources_library != "" ]] ; then
      sources=
      for i in $sources_library ; do
        sources="$sources$path_c$i "
      done

      echo $compiler $sources -shared -Wl,-soname,lib$name.so.$major -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments_shared $arguments_include $flags_all $arguments $flags_shared $flags_library
      $compiler $sources -shared -Wl,-soname,lib$name.so.$major -o ${path_build}libraries/shared/lib$name.so.$major.$minor.$micro $arguments_shared $arguments_include $flags_all $arguments $flags_shared $flags_library || failure=1

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

      echo $compiler $sources -o ${path_build}programs/shared/$name $arguments_shared $arguments_include $flags_all $arguments $flags_shared $flags_program
      $compiler $sources -o ${path_build}programs/shared/$name $arguments_shared $arguments_include $flags_all $arguments $flags_shared $flags_program || failure=1
    fi
  fi

  if [[ $failure == "" && $static == "yes" ]] ; then
    sources=
    if [[ $sources_library != "" ]] ; then
      for i in $sources_library ; do
        directory=$(dirname $i)

        if [[ $directory != "." && ! -d ${path_build}objects/$directory ]] ; then
          mkdir -vp ${path_build}objects/$directory

          if [[ $? -ne 0 ]] ; then
            failure=1
            break;
          fi
        fi

        sources="$sources${path_build}objects/$i.o "

        echo $compiler $path_c$i -c -static -o ${path_build}objects/$i.o $arguments_static $arguments_include $flags_all $arguments $flags_static $flags_library
        $compiler $path_c$i -c -static -o ${path_build}objects/$i.o $arguments_static $arguments_include $flags_all $arguments $flags_static $flags_library || failure=1

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

      echo $compiler -static -o ${path_build}programs/static/$name $sources $arguments_static $arguments_include $flags_all $arguments $flags_static $flags_program
      $compiler -static -o ${path_build}programs/static/$name $sources $arguments_static $arguments_include $flags_all $arguments $flags_static $flags_program || failure=1
    fi
  fi

  if [[ $failure == "" && $sources_bash != "" ]] ; then
    for i in $sources_bash ; do
      directory=$(dirname $i)

      if [[ $directory == "." ]] ; then
        cp -vf $path_bash$i ${path_build}bash/ || failure=1
      else
        mkdir -vp ${path_build}bash/$directory || failure=1

        if [[ $failure == "" ]] ; then
          cp -vf $path_bash$i ${path_build}bash/${directory}/ || failure=1
        fi
      fi
    done
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

  for i in ${path_build}{includes,programs,libraries,objects,bash,settings} ; do
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

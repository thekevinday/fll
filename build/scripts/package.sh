#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to create releases from the project source.
# These release directories can then be used to compile the project or to package the project.
# The dependencies of this script are: basename, bash, chmod, grep, and sed.

package_main() {
  local public_name="Simple FLL Project Package Script"
  local system_name=package
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

  local variables=
  local operation=
  local operation_failure=
  local mode_individual=
  local mode_level=
  local mode_monolithic=
  local mode_program=
  local path_build=build/
  local path_destination=package/
  local path_sources=./
  local verbosity="normal"

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
        elif [[ $p == "-d" || $p == "--destination" ]] ; then
          grab_next=path_destination
        elif [[ $p == "-i" || $p == "--individual" ]] ; then
          mode_individual="yes"
        elif [[ $p == "-l" || $p == "--level" ]] ; then
          mode_level="yes"
        elif [[ $p == "-m" || $p == "--monolithic" ]] ; then
          mode_monolithic="yes"
        elif [[ $p == "-p" || $p == "--program" ]] ; then
          mode_program="yes"
        elif [[ $p == "-s" || $p == "--sources" ]] ; then
          grab_next=path_sources
        elif [[ $operation == "" ]] ; then
          operation="$p"
        elif [[ $operation_failure == "" ]] ; then
          operation_failure=fail-multiple
          operation="$p"
        fi
      else
        if [[ $grab_next == "path_build" ]] ; then
          path_build=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_destination" ]] ; then
          path_destination=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        elif [[ $grab_next == "path_sources" ]] ; then
          path_sources=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
        fi

        grab_next=
      fi
    done

    p=
  fi

  package_handle_colors

  if [[ $do_help == "yes" ]] ; then
    package_help
    package_cleanup
    return 0
  fi

  if [[ $operation_failure == "fail-multiple" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: only one operation may be specified at a time.$c_reset"
    fi

    package_cleanup
    return 1
  elif [[ $operation == "build" ]] ; then
    if [[ ! -d $path_build ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: build directory '$path_build' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    if [[ ! -d $path_destination ]] ; then
      mkdir $verbose -p $path_destination
      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: package directory '$path_destination' is invalid or could not be created.$c_reset"
        fi

        package_cleanup
        return 1
      fi
    fi

    if [[ ! -d $path_sources ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: sources directory '$path_sources' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    if [[ ! -d ${path_sources}level_0/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: build sources directory '${path_sources}level_0/' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    if [[ ! -d ${path_sources}level_1/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: build sources directory '${path_sources}level_1/' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    if [[ ! -d ${path_sources}level_2/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: build sources directory '${path_sources}level_2/' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    if [[ ! -d ${path_sources}level_3/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: build sources directory '${path_sources}level_3/' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    if [[ $mode_individual == "" && $mode_level == "" && $mode_monolithic == "" && $mode_program == "" ]] ; then
      mode_individual="yes"
    fi

    if [[ $mode_individual == "yes" ]] ; then
      package_operation_individual
    fi

    if [[ $mode_level == "yes" ]] ; then
      package_operation_level
    fi

    if [[ $mode_monolithic == "yes" ]] ; then
      package_operation_monolithic
    fi

    if [[ $mode_program == "yes" ]] ; then
      package_operation_program
    fi
  elif [[ $operation == "dependencies" ]] ; then
    if [[ ! -d $path_sources ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: sources directory '$path_sources' is invalid or missing.$c_reset"
      fi

      package_cleanup
      return 1
    fi

    package_operation_dependencies
  elif [[ $operation == "clean" ]] ; then
    if [[ ! -d $path_destination ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_warning}WARNING: package directory '$path_destination' does not exist, there is nothing to clean.$c_reset"
      fi

      package_cleanup
      return 0
    fi

    package_operation_clean
  elif [[ $operation == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: no operation was given.$c_reset"
    fi

    package_cleanup
    return 1
  else
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
    fi

    package_cleanup
    return 1
  fi

  package_cleanup
  return 0
}

package_handle_colors() {
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

package_help() {
  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset $c_notice<${c_reset}operation$c_notice>$c_reset"
  echo -e " ${c_important}build${c_reset}         Build the package."
  echo -e " ${c_important}dependencies${c_reset}  Rebuild all dependencies."
  echo -e " ${c_important}clean${c_reset}         Delete all built packages."
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen."
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds."
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color."
  echo -e " +${c_important}q$c_reset, ++${c_important}quiet$c_reset     Decrease verbosity beyond normal output."
  echo -e " +${c_important}V$c_reset, ++${c_important}verbose$c_reset   Increase verbosity beyond normal output."
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program."
  echo
  echo -e "${c_highlight}Package Options:$c_reset"
  echo -e " -${c_important}d$c_reset, --${c_important}destination${c_reset}  Specify a custom package destination directory."
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}        Specify a custom build directory."
  echo -e " -${c_important}i$c_reset, --${c_important}individual${c_reset}   Build packages by individual package (levels 0. 1. and 2)."
  echo -e " -${c_important}l$c_reset, --${c_important}level${c_reset}        Build packages by level (levels 0. 1. and 2)."
  echo -e " -${c_important}m$c_reset, --${c_important}monolithic${c_reset}   Build a monolithic package (levels 0. 1. and 2)."
  echo -e " -${c_important}p$c_reset, --${c_important}program${c_reset}      Build program packages (level 3)."
  echo -e " -${c_important}s$c_reset, --${c_important}sources${c_reset}      Specify a custom sources directory."
  echo
}

package_create_base_files() {

  if [[ ! -d $package ]] ; then
    mkdir $verbose -p $package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice$package$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure == "" && ! -d ${path_build}documents ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build directory $c_notice${path_build}documents$c_error cannot be found or is invalid.$c_reset"
    fi

    failure=1
  fi

  if [[ $failure == "" ]] ; then
    cp $verbose -R ${path_build}documents $package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy directory $c_notice${path_build}documents$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure == "" ]] ; then
    if [[ -d ${path_build}licenses ]] ; then
      cp $verbose -R ${path_build}licenses $package

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy directory $c_notice${path_build}licenses$c_error to $c_notice$package$c_error.$c_reset"
        fi

        failure=1
      fi
    elif [[ -d ${path_build}../licenses ]] ; then
      cp $verbose -R ${path_build}../licenses $package

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy directory $c_notice${path_build}../licenses$c_error to $c_notice$package$c_error.$c_reset"
        fi

        failure=1
      fi
    else
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: neither directory $c_notice${path_build}licenses$c_error nor $c_notice${path_build}../licenses$c_error can be found or are invalid.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure == "" ]] ; then
    cp $verbose -R ${path_build}scripts/bootstrap.sh $package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy script $c_notice${path_build}bootstrap.sh$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
    fi

    if [[ $failure == "" ]] ; then
      chmod ugo+x ${package}bootstrap.sh

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to set executable permissions on script $c_notice${package}bootstrap.sh$c_error.$c_reset"
        fi

        failure=1
      fi
    fi

    if [[ $failure == "" ]] ; then
      cp $verbose -R ${path_build}scripts/install.sh $package

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy script $c_notice${path_build}install.sh$c_error to $c_notice$package$c_error.$c_reset"
        fi

        failure=1
      fi
    fi

    if [[ $failure == "" ]] ; then
      chmod ugo+x ${package}install.sh

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to set executable permissions on script $c_notice${package}install.sh$c_error.$c_reset"
        fi

        failure=1
      fi
    fi
  fi

  if [[ $failure != "" && ! -d ${package}build ]] ; then
    mkdir $verbose -p ${package}build

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}build$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}sources ]] ; then
    mkdir $verbose -p ${package}sources

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}sources$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}documents ]] ; then
    mkdir $verbose -p ${package}documents

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}documents$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}licenses ]] ; then
    mkdir $verbose -p ${package}licenses

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}licenses$c_error.$c_reset"
      fi

      failure=1
    fi
  fi

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_dependencies_individual() {
  local level=
  local level_current=
  local directory=
  local settings=
  local name=
  local dependencies=
  local dependency=
  local sub_level=
  local sub_dependencies=
  local sub_dependency=
  local sub_sub_level=
  local sub_sub_dependencies=
  local sub_sub_dependency=
  local individual_dependencies=

  for directory in ${path_sources}level_0/* ${path_sources}level_1/* ${path_sources}level_2/* ${path_sources}level_3/* ; do
    name="$(echo $directory | sed -e "s|${path_sources}level_0/||" -e "s|${path_sources}level_1/||" -e "s|${path_sources}level_2/||" -e "s|${path_sources}level_3/||")"

    level_current="$(echo $directory | grep -o '\<level_[[:digit:]]/' | sed -e 's|level_||' -e 's|/$||')"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Building Dependencies for $c_reset$c_notice${name}$c_reset${c_highlight}.$c_reset"
    fi

    if [[ ! -f ${directory}/data/build/dependencies ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: cannot build dependencies, failed to find $c_notice${directory}/data/build/dependencies$c_error.$c_reset"
      fi

      failure=1
      return
    fi

    if [[ ! -f ${directory}/data/build/settings ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: cannot build dependencies for $c_reset$c_notice${name}$c_reset${c_error}, failed to find $c_notice${directory}/data/build/settings$c_error.$c_reset"
      fi

      failure=1
      return
    fi

    dependencies=
    if [[ -f ${directory}/data/build/dependencies ]] ; then
      dependencies=$(cat ${directory}/data/build/dependencies | sed -e "/^\s*#/d" -e "s|#\.*$||")
    fi

    individual_dependencies=
    for dependency in $dependencies ; do
      if [[ $(echo "$dependency" | grep -o "^f_") != "" ]] ; then
        level=level_0
      elif [[ $(echo "$dependency" | grep -o "^fl_") != "" ]] ; then
        level=level_1
      elif [[ $(echo "$dependency" | grep -o "^fll_") != "" ]] ; then
        level=level_2
      else
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_warning}WARNING: failed to detect level for dependency $c_notice$dependency$c_warning.$c_reset"
        fi

        continue
      fi

      if [[ ! -d ${path_sources}${level}/${dependency}/data/build/ ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to find dependency data directory $c_notice${path_sources}${level}/${dependency}/data/build/$c_error.$c_reset"
        fi

        failure=1
        return
      fi

      sub_dependencies=
      if [[ -f ${path_sources}${level}/${dependency}/data/build/dependencies ]] ; then
        sub_dependencies=$(cat ${path_sources}${level}/${dependency}/data/build/dependencies | sed -e "/^\s*#/d" -e "s|#\.*$||")
      fi

      for sub_dependency in $sub_dependencies ; do
        if [[ $(echo "$sub_dependency" | grep -o "^f_") != "" ]] ; then
          sub_level=level_0
        elif [[ $(echo "$sub_dependency" | grep -o "^fl_") != "" ]] ; then
          sub_level=level_1
        else
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: failed to detect level for sub-dependency $c_notice$sub_dependency$c_warning.$c_reset"
          fi

          continue
        fi

        if [[ ! -d ${path_sources}${sub_level}/${sub_dependency}/data/build/ ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Failed to find dependency data directory $c_notice${path_sources}${sub_level}/${sub_dependency}/data/build/$c_error.$c_reset"
          fi

          failure=1
          return
        fi

        sub_sub_dependencies=
        if [[ -f ${path_sources}${sub_level}/${sub_dependency}/data/build/dependencies ]] ; then
          sub_sub_dependencies=$(cat ${path_sources}${sub_level}/${sub_dependency}/data/build/dependencies | sed -e "/^\s*#/d" -e "s|#\.*$||")
        fi

        for sub_sub_dependency in $sub_sub_dependencies ; do
          if [[ $(echo "$sub_sub_dependency" | grep -o "^f_") != "" ]] ; then
            sub_sub_level=level_0
          else
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_warning}WARNING: failed to detect level for sub-sub-dependency $c_notice$sub_sub_dependency$c_warning.$c_reset"
            fi

            continue
          fi

          package_dependencies_individual_append "$sub_sub_level" "$sub_sub_dependency"
        done

        if [[ $failure != "" ]] ; then
          break;
        fi

        package_dependencies_individual_append "$sub_level" "$sub_dependency"

        if [[ $failure != "" ]] ; then
          break;
        fi
      done

      if [[ $failure != "" ]] ; then
        break;
      fi

      package_dependencies_individual_append "$level" "$dependency"

      if [[ $failure != "" ]] ; then
        break;
      fi
    done

    if [[ $failure != "" ]] ; then
      break;
    fi

    individual_dependencies=$(echo "$individual_dependencies" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    if [[ $individual_dependencies != "" ]] ; then
      if [[ $verbosity == "verbose" ]] ; then
        echo -e " $individual_dependencies"
      fi

      individual_dependencies=" $individual_dependencies"
    fi

    settings=${directory}/data/build/settings
    sed -i -e "s|^\s*build_libraries-individual\>.*\$|build_libraries-individual$individual_dependencies|" $settings

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to update settings file $c_notice${settings}$c_error.$c_reset"
      fi

      failure=1
      return
    fi

    # all level 3 are expected to support all modes: individual, level, and monolithic.
    if [[ $level_current == "3" ]] ; then
      sed -i -e "s|^\s*build_libraries-level\>.*\$|build_libraries-level -lfll_2 -lfll_1 -lfll_0|" $settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to update settings file $c_notice${settings}$c_error.$c_reset"
        fi

        failure=1
        return
      fi

      sed -i -e "s|^\s*build_libraries-monolithic\>.*\$|build_libraries-monolithic -lfll|" $settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to update settings file $c_notice${settings}$c_error.$c_reset"
        fi

        failure=1
        return
      fi
    fi
  done
}

package_dependencies_individual_append() {
  local level="$1"
  local dependency="$2"
  local settings=
  local libraries=

  settings=${path_sources}${level}/${dependency}/data/build/settings
  if [[ ! -f $settings ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to find dependency settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi

  libraries=$(grep -o '^\s*build_sources_library\>.*$' $settings | sed -e 's|^\s*build_sources_library\>||' -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  if [[ $libraries != "" ]] ; then
    if [[ $(echo -n $individual_dependencies | grep -o "\-l$dependency\>") == "" ]] ; then
      individual_dependencies="-l$dependency $individual_dependencies"
    fi
  fi
}

package_dependencies_level() {
  local directory=
  local name=
  local settings=
  local library=
  local libraries=
  local header=
  local headers=

  package_dependencies_level_update "level_0" ""

  if [[ $failure != "" ]] ; then
    return;
  fi

  package_dependencies_level_update "level_1" " -lfll_0"

  if [[ $failure != "" ]] ; then
    return;
  fi

  package_dependencies_level_update "level_2" " -lfll_1 -lfll_0"
}

package_dependencies_level_update() {
  local level="$1"
  local level_libraries="$2"
  local level_sources_library=
  local level_sources_headers=
  local monolithic_libraries=
  local monolithic_headers=

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Building Dependencies: $c_notice$level${c_highlight}.$c_reset"
  fi

  for directory in $path_sources${level}/* ; do
    name="$(echo $directory | sed -e "s|$path_sources${level}/||")"

    settings=${directory}/data/build/settings
    if [[ ! -f $settings ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to find settings file $c_notice$settings$c_error.$c_reset"
      fi

      failure=1
      return
    fi

    libraries=$(grep -o '^\s*build_sources_library\>.*$' $settings | sed -e 's|^\s*build_sources_library\>||' -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    for library in $libraries ; do
      level_sources_library="$level_sources_library $library"
      monolithic_libraries="$monolithic_libraries $level/$library"
    done

    headers=$(grep -o '^\s*build_sources_headers\>.*$' $settings | sed -e 's|^\s*build_sources_headers\>||' -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    for header in $headers ; do
      level_sources_headers="$level_sources_headers $header"
      monolithic_headers="$monolithic_headers $level/$header"
    done
  done

  settings=${path_sources}/build/${level}/settings

  if [[ ! -f $settings ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to find settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi

  sed -i -e "s|^\s*build_libraries-level\>.*\$|build_libraries-level$level_libraries|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update libraries for settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi

  level_sources_library=$(echo "$level_sources_library" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  if [[ $level_sources_library != "" ]] ; then
    echo " $level_sources_library"
    level_sources_library=" $level_sources_library"
  fi

  sed -i -e "s|^\s*build_sources_library\>.*\$|build_sources_library$level_sources_library|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update libraries for settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi

  level_sources_headers=$(echo "$level_sources_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  if [[ $level_sources_headers != "" ]] ; then
    echo " $level_sources_headers"
    level_sources_headers=" $level_sources_headers"
  fi

  sed -i -e "s|^\s*build_sources_headers\>.*\$|build_sources_headers$level_sources_headers|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update headers for settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi

  if [[ $level == "level_0" ]] ; then
    level_0_libraries=$(echo "$monolithic_libraries" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_0_headers=$(echo "$monolithic_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  elif [[ $level == "level_1" ]] ; then
    level_1_libraries=$(echo "$monolithic_libraries" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_1_headers=$(echo "$monolithic_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  elif [[ $level == "level_2" ]] ; then
    level_2_libraries=$(echo "$monolithic_libraries" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_2_headers=$(echo "$monolithic_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  fi
}

package_dependencies_monolithic() {
  local monolithic_libraries=""
  local monolithic_headers=""

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Building Dependencies: ${c_notice}monolithic${c_highlight}.$c_reset"
  fi

  if [[ $level_0_libraries != "" ]] ; then
    monolithic_libraries="$level_0_libraries"
  fi

  if [[ $level_0_headers != "" ]] ; then
    monolithic_headers="$level_0_headers"
  fi

  if [[ $level_1_libraries != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_libraries="$level_1_libraries"
    else
      monolithic_libraries="$monolithic_libraries $level_1_libraries"
    fi
  fi

  if [[ $level_1_headers != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_headers="$level_1_headers"
    else
      monolithic_headers="$monolithic_headers $level_1_headers"
    fi
  fi

  if [[ $level_2_libraries != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_libraries="$level_2_libraries"
    else
      monolithic_libraries="$monolithic_libraries $level_2_libraries"
    fi
  fi

  if [[ $level_2_headers != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_headers="$level_2_headers"
    else
      monolithic_headers="$monolithic_headers $level_2_headers"
    fi
  fi

  settings=${path_sources}/build/monolithic/settings

  if [[ $monolithic_libraries != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo " $monolithic_libraries"
    fi

    monolithic_libraries=" $monolithic_libraries"
  fi

  sed -i -e "s|^\s*build_sources_library\>.*\$|build_sources_library$monolithic_libraries|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update libraries for settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi


  if [[ $monolithic_headers != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo " $monolithic_headers"
    fi

    monolithic_headers=" $monolithic_headers"
  fi

  sed -i -e "s|^\s*build_sources_headers\>.*\$|build_sources_headers$monolithic_headers|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update headers for settings file $c_notice$settings$c_error.$c_reset"
    fi

    failure=1
    return
  fi
}

package_operation_clean() {
  local i=

  if [[ $mode_individual == "yes" ]] ; then
    if [[ -d ${path_destination}individual ]] ; then
      rm $verbose -Rf ${path_destination}individual
    fi
  fi

  if [[ $mode_level == "yes" ]] ; then
    if [[ -d ${path_destination}level ]] ; then
      rm $verbose -Rf ${path_destination}level
    fi
  fi

  if [[ $mode_monolithic == "yes" ]] ; then
    if [[ -d ${path_destination}monolithic ]] ; then
      rm $verbose -Rf ${path_destination}monolithic
    fi
  fi

  if [[ $mode_program == "yes" ]] ; then
    if [[ -d ${path_destination}program ]] ; then
      rm $verbose -Rf ${path_destination}program
    fi
  fi
}

package_operation_copy_package() {
  if [[ -d ${package}sources/data/ ]] ; then
    cp $verbose -R ${package}sources/data ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy the data directory $c_notice${package}sources/data$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    rm $verbose -Rf ${package}sources/data

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove directory $c_notice${package}sources/data$c_error.$c_reset"
      fi

      failure=1
      break
    fi
  fi

  if [[ -d ${package}sources/documents/ ]] ; then
    cp $verbose -R ${package}sources/documents/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources documents directory $c_notice${path_sources}sources/documents$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    rm $verbose -Rf ${package}sources/documents/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources documents directory $c_notice${path_sources}sources/documents$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi
  fi

  if [[ -d ${package}sources/licenses/ ]] ; then
    cp $verbose -R ${package}sources/licenses/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources licenses directory $c_notice${path_sources}sources/licenses$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    rm $verbose -Rf ${package}sources/licenses/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources licenses directory $c_notice${path_sources}sources/licenses$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi
  fi

  if [[ -d ${package}sources/specifications/ ]] ; then
    cp $verbose -R ${package}sources/specifications/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources specifications directory $c_notice${path_sources}sources/specifications$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    rm $verbose -Rf ${package}sources/specifications/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources specifications directory $c_notice${path_sources}sources/specifications$c_error to $c_notice$package$c_error.$c_reset"
      fi

      failure=1
      break
    fi
  fi
}

package_operation_dependencies() {
  local failure=
  local level_0_libraries=
  local level_1_libraries=
  local level_2_libraries=
  local level_0_headers=
  local level_1_headers=
  local level_2_headers=

  package_dependencies_individual

  if [[ $failure != "" ]] ; then
    return;
  fi

  package_dependencies_level

  if [[ $failure != "" ]] ; then
    return;
  fi

  package_dependencies_monolithic
}

package_operation_individual() {
  local failure=
  local name=
  local directory=
  local package=

  if [[ ! -d ${path_destination}individual ]] ; then
    mkdir $verbose -p ${path_destination}individual

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${path_destination}individual$c_error.$c_reset"
      fi

      package_cleanup
      exit $failure
    fi
  fi

  for directory in ${path_sources}level_0/* ${path_sources}level_1/* ${path_sources}level_2/* ; do
    name="$(echo $directory | sed -e "s|${path_sources}level_0/||" -e "s|${path_sources}level_1/||" -e "s|${path_sources}level_2/||")"
    package="${path_destination}individual/${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project$c_reset (individual) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"
    fi

    package_create_base_files

    cp $verbose -R $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy sources directory $c_notice$directory$c_error to $c_notice${package}sources$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    package_operation_copy_package
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_level() {
  local failure=
  local name=
  local level=
  local directory=
  local package=

  for level in level_0 level_1 level_2 ; do
    name="fll-$level"
    package="${path_destination}level/${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project$c_reset (level) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"
    fi

    if [[ ! -d $path_build$level ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: build settings directory $c_notice$path_build$level$c_error is invalid or missing.$c_reset"
      fi

      failure=1
      break
    fi

    package_create_base_files

    if [[ ! -d ${package}data/ ]] ; then
      mkdir $verbose ${package}data/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}data$c_error.$c_reset"
        fi

        failure=1
        break
      fi
    fi

    if [[ -d $path_build${level}/build ]] ; then
      cp $verbose -R $path_build${level}/build ${package}data/
    else
      cp $verbose -R $path_build$level ${package}data/build
    fi

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move the directory $c_notice$path_build$level$c_error as $c_notice$path_build${level}build$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    if [[ ! -d ${package}sources/ ]] ; then
      mkdir $verbose ${package}sources/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}sources$c_error.$c_reset"
        fi

        failure=1
        break
      fi
    fi

    for directory in $path_sources${level}/* ; do
      cp $verbose -R $directory/* ${package}sources/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy files from sources directory $c_notice$directory$c_error to $c_notice${package}sources$c_error.$c_reset"
        fi

        failure=1
        break
      fi

      rm $verbose -Rf ${package}sources/data/build/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to remove directory $c_notice${package}sources/data/build$c_error.$c_reset"
        fi

        failure=1
        break
      fi

      package_operation_copy_package
    done

    if [[ $failure != "" ]] ; then
      break;
    fi
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_monolithic() {
  local failure=
  local name=
  local level=
  local directory=
  local package=
  local subdirectory=
  local pathname=

  name="fll"
  package="${path_destination}monolithic/${name}-${version}/"

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Packaging Project$c_reset (monolithic) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"
  fi

  if [[ ! -d ${path_build}monolithic ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: build settings directory $c_notice${path_build}monolithic$c_error is invalid or missing.$c_reset"
    fi

    package_cleanup
    return 1
  fi

  package_create_base_files

  if [[ ! -d ${package}data/ ]] ; then
    mkdir $verbose ${package}data/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}data$c_error.$c_reset"
      fi

      package_cleanup
      return 1
    fi
  fi

  if [[ -d ${path_build}monolithic/build ]] ; then
    cp $verbose -R ${path_build}monolithic/build ${package}data
  else
    cp $verbose -R ${path_build}monolithic ${package}data/build
  fi

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to move the directory $c_notice$path_build$level$c_error as $c_notice$path_build${level}build$c_error.$c_reset"
    fi

    package_cleanup
    return 1
  fi

  if [[ ! -d ${package}sources/ ]] ; then
    mkdir $verbose ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${package}sources$c_error.$c_reset"
      fi

      package_cleanup
      return 1
    fi
  fi

  for level in level_0 level_1 level_2 ; do
    for directory in $path_sources${level}/* ; do
      for subdirectory in $directory/* ; do
        pathname="$(basename $subdirectory)"

        if [[ $pathname == "data" ]] ; then
          if [[ ! -d ${package}data/$level ]] ; then
            mkdir $verbose -p ${package}data/$level

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to create package data directory $c_notice${package}data/$level$c_error.$c_reset"
              fi

              failure=1
              break
            fi
          fi

          cp $verbose -R $subdirectory ${package}sources/data

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory $c_notice$subdirectory$c_error to $c_notice${package}sources/data$level$c_error.$c_reset"
            fi

            failure=1
            break
          fi

          rm $verbose -Rf ${package}sources/data/build/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to remove directory $c_notice${package}sources/data/build$c_error.$c_reset"
            fi

            failure=1
            break
          fi

          if [[ "$(ls ${package}sources/data)" != "" ]] ; then
            cp $verbose -R ${package}sources/data/* ${package}data/$level

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to copy the data directory $c_notice${package}sources/data/$level/data$c_error to $c_notice${package}data/$level$c_error.$c_reset"
              fi

              failure=1
              break
            fi
          fi

          rm $verbose -Rf ${package}sources/data

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to remove directory $c_notice${package}sources/data$c_error.$c_reset"
            fi

            failure=1
            break
          fi
        elif [[ $pathname == "documents" ]] ; then
          cp $verbose -R $subdirectory ${package}sources/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory $c_notice$subdirectory$c_error to $c_notice${package}sources/documents$c_error.$c_reset"
            fi

            failure=1
            break
          fi
        elif [[ $pathname == "licenses" ]] ; then
          cp $verbose -R $subdirectory ${package}sources/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory $c_notice$subdirectory$c_error to $c_notice${package}sources/licenses$c_error.$c_reset"
            fi

            failure=1
            break
          fi
        elif [[ $pathname == "specifications" ]] ; then
          cp $verbose -R $subdirectory ${package}sources/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory $c_notice$subdirectory$c_error to $c_notice${package}sources/specifications$c_error.$c_reset"
            fi

            failure=1
            break
          fi
        else
          if [[ ! -d ${package}sources/$pathname/$level ]] ; then
            mkdir $verbose -p ${package}sources/$pathname/$level

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to create package sources directory $c_notice${package}sources/$pathname/$level$c_error.$c_reset"
              fi

              failure=1
              break
            fi
          fi

          cp $verbose -R $subdirectory/* ${package}sources/$pathname/$level

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from sources directory $c_notice$subdirectory$c_error to $c_notice${package}sources/$pathname/$level$c_error.$c_reset"
            fi

            failure=1
            break
          fi
        fi
      done

      if [[ $failure != "" ]] ; then
        break;
      fi
    done

    if [[ $failure != "" ]] ; then
      break;
    fi
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_program() {
  local failure=
  local name=
  local directory=
  local package=

  if [[ ! -d ${path_destination}program ]] ; then
    mkdir $verbose -p ${path_destination}program

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory $c_notice${path_destination}program$c_error.$c_reset"
      fi

      package_cleanup
      exit $failure
    fi
  fi

  for directory in ${path_sources}level_3/* ; do
    name="$(echo $directory | sed -e "s|${path_sources}level_3/||")"
    package="${path_destination}program/${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project$c_reset (program) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"
    fi

    package_create_base_files

    cp $verbose -R $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy sources directory $c_notice$directory$c_error to $c_notice${package}sources$c_error.$c_reset"
      fi

      failure=1
      break
    fi

    package_operation_copy_package
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_cleanup() {
  unset package_main
  unset package_handle_colors
  unset package_help
  unset package_build
  unset package_create_base_files
  unset package_dependencies_individual
  unset package_dependencies_individual_append
  unset package_dependencies_level
  unset package_dependencies_level_update
  unset package_dependencies_monolithic
  unset package_operation_clean
  unset package_operation_copy_package
  unset package_operation_individual
  unset package_operation_level
  unset package_operation_monolithic
  unset package_operation_program
  unset package_operation_dependencies
  unset package_cleanup
}

package_main $*

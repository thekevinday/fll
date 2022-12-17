#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# The purpose of this script is to create releases from the project source.
# These release directories can then be used to compile the project or to package the project.
#
# The dependencies of this script are: basename, bash, chmod, grep, sed, and sort.
#
# This script can also be run under zsh rather than bash by setting the environment variable SHELL_ENGINE to "zsh", such as:
#   SHELL_ENGINE="zsh" zsh ./package.sh --help
#

package_main() {

  if [[ $SHELL_ENGINE == "zsh" ]] ; then
    emulate ksh
  fi

  local public_name="Simple FLL Project Package Script"
  local system_name=package
  local called_name=$(basename $0)
  local version=0.7.0

  local grab_next=
  local do_color=dark
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

  local -A variables=()
  local operation=
  local operation_failure=
  local mode_individual=
  local mode_level=
  local mode_monolithic=
  local mode_program=
  local mode_stand_alone=
  local path_build=build/
  local path_destination=package/
  local path_sources=./
  local prepend=
  local verbosity=normal
  local verbose=
  local verbose_common=
  local result=

  if [[ $# -gt 0 ]] ; then
    t=$#

    while [[ $i -lt $t ]] ; do
      let i=$i+1

      if [[ $SHELL_ENGINE == "zsh" ]] ; then
        p=${(P)i}
      else
        p=${!i}
      fi

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
          verbose="+q"
          verbose_common=
        elif [[ $p == "+N" || $p == "++normal" ]] ; then
          verbosity=
          verbose="+N"
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
        elif [[ $p == "-P" || $p == "--prepend" ]] ; then
          grab_next=prepend
        elif [[ $p == "-p" || $p == "--program" ]] ; then
          mode_program="yes"
        elif [[ $p == "-s" || $p == "--sources" ]] ; then
          grab_next=path_sources
        elif [[ $p == "-S" || $p == "--stand_alone" ]] ; then
          grab_next=stand_alone
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
        elif [[ $grab_next == "stand_alone" ]] ; then
          mode_stand_alone="$mode_stand_alone$p "
        elif [[ $grab_next == "prepend" ]] ; then

          # Provide a bare minimal sanitizer that probably doesn't catch everything that it ideally should.
          prepend=$(echo $p | sed -e 's|[\!~\`@#$%^&*();:><?/"\\]||g' -e 's@|@@g' -e "s|'||g" -e "s|\s*||g")
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
      echo -e "${c_error}ERROR: Only one operation may be specified at a time.${c_reset}"
    fi

    package_cleanup

    return 1
  fi

  if [[ $mode_stand_alone != "" ]] ; then
    for i in $mode_stand_alone ; do

      if [[ ! -f build/stand_alone/$i.settings ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Unknown or unsupported stand alone program '${c_notice}$i${c_error}'.${c_reset}"
        fi

        package_cleanup

        return 1
      fi
    done
  fi

  if [[ $operation == "build" || $operation == "rebuild" ]] ; then
    if [[ ! -d $path_build ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Build directory '${c_notice}$path_build${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    if [[ ! -d $path_destination ]] ; then
      mkdir $verbose_common -p $path_destination
      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Package directory '${c_notice}$path_destination${c_error}' is invalid or could not be created.${c_reset}"
        fi

        package_cleanup

        return 1
      fi
    fi

    if [[ ! -d $path_sources ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Sources directory '${c_notice}$path_sources${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    if [[ ! -d ${path_sources}level_0/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Build sources directory '${c_notice}${path_sources}level_0/${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    if [[ ! -d ${path_sources}level_1/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Build sources directory '${c_notice}${path_sources}level_1/${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    if [[ ! -d ${path_sources}level_2/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Build sources directory '${c_notice}${path_sources}level_2/${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    if [[ ! -d ${path_sources}level_3/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Build sources directory '${c_notice}${path_sources}level_3/${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    if [[ $operation == "rebuild" ]] ; then
      package_operation_clean

      if [[ $failure -ne 0 ]] ; then
        return 1
      fi
    fi

    if [[ $mode_individual == "" && $mode_level == "" && $mode_monolithic == "" && $mode_program == "" && $mode_stand_alone == "" ]] ; then
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

    if [[ $mode_stand_alone != "" ]] ; then
      package_operation_stand_alone
    fi
  elif [[ $operation == "dependencies" ]] ; then
    if [[ ! -d $path_sources ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Sources directory '${c_notice}${path_sources}${c_error}' is invalid or missing.${c_reset}"
      fi

      package_cleanup

      return 1
    fi

    package_operation_dependencies
  elif [[ $operation == "clean" ]] ; then
    if [[ ! -d $path_destination ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_warning}WARNING: Package directory '${c_notice}${path_destination}${c_error}' does not exist, there is nothing to clean.${c_reset}"
      fi

      package_cleanup

      return 0
    fi

    package_operation_clean
  elif [[ $operation == "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: No operation was given.${c_reset}"
    fi

    package_cleanup

    return 1
  else
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The operation ${c_notice}${operation}${c_error} was not recognized.${c_reset}"
    fi

    package_cleanup

    return 1
  fi

  # Always append a new line at the end.
  if [[ $verbosity != "quiet" ]] ; then
    echo
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
  echo -e "${c_title}${public_name}${c_reset}"
  echo -e " ${c_notice}Version ${version}${c_reset}"
  echo
  echo -e "${c_highlight}${system_name}${c_reset} ${c_notice}[${c_reset} options ${c_notice}]${c_reset} ${c_notice}[${c_reset} operation ${c_notice}]${c_reset}"
  echo -e " ${c_important}build${c_reset}         Build the package."
  echo -e " ${c_important}clean${c_reset}         Delete all built packages."
  echo -e " ${c_important}dependencies${c_reset}  Rebuild all dependencies."
  echo -e " ${c_important}rebuild${c_reset}       Delete all built packages then build the package."
  echo
  echo -e "${c_highlight}Options:${c_reset}"
  echo -e " -${c_important}h${c_reset}, --${c_important}help${c_reset}      Print this help screen."
  echo -e " +${c_important}d${c_reset}, ++${c_important}dark${c_reset}      Use color modes that show up better on dark backgrounds."
  echo -e " +${c_important}l${c_reset}, ++${c_important}light${c_reset}     Use color modes that show up better on light backgrounds."
  echo -e " +${c_important}n${c_reset}, ++${c_important}no_color${c_reset}  Do not use color."
  echo -e " +${c_important}q${c_reset}, ++${c_important}quiet${c_reset}     Decrease verbosity, silencing most output."
  echo -e " +${c_important}N${c_reset}, ++${c_important}normal${c_reset}    Set verbosity to normal."
  echo -e " +${c_important}V${c_reset}, ++${c_important}verbose${c_reset}   Increase verbosity beyond normal output."
  echo -e " +${c_important}D${c_reset}, ++${c_important}debug${c_reset}     Enable debugging, significantly increasing verbosity beyond normal output."
  echo -e " +${c_important}v${c_reset}, ++${c_important}version${c_reset}   Print the version number of this program."
  echo
  echo -e "${c_highlight}Package Options:${c_reset}"
  echo -e " -${c_important}d${c_reset}, --${c_important}destination${c_reset}  Specify a custom package destination directory."
  echo -e " -${c_important}b${c_reset}, --${c_important}build${c_reset}        Specify a custom build directory."
  echo -e " -${c_important}i${c_reset}, --${c_important}individual${c_reset}   Build packages by individual package (levels 0. 1. and 2)."
  echo -e " -${c_important}l${c_reset}, --${c_important}level${c_reset}        Build packages by level (levels 0. 1. and 2)."
  echo -e " -${c_important}m${c_reset}, --${c_important}monolithic${c_reset}   Build a monolithic package (levels 0. 1. and 2)."
  echo -e " -${c_important}P${c_reset}, --${c_important}prepend${c_reset}      Prepend a string (with a restricted character set) before the built directory name."
  echo -e " -${c_important}p${c_reset}, --${c_important}program${c_reset}      Build program packages (level 3)."
  echo -e " -${c_important}s${c_reset}, --${c_important}sources${c_reset}      Specify a custom sources directory."
  echo -e " -${c_important}S${c_reset}, --${c_important}stand_alone${c_reset}  Build a specified program package as stand alone."
  echo
}

package_create_base_files() {

  if [[ ! -d $package ]] ; then
    mkdir $verbose_common -p $package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ $failure == "" && ! -d ${path_build}documents ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build directory ${c_notice}${path_build}documents${c_error} cannot be found or is invalid.${c_reset}"
    fi

    let failure=1
  fi

  if [[ $failure == "" ]] ; then
    cp $verbose_common -R ${path_build}documents $package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy directory ${c_notice}${path_build}documents${c_error} to ${c_notice}$package${c_error}.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ $failure == "" ]] ; then
    if [[ -d ${path_build}licenses ]] ; then
      cp $verbose_common -R ${path_build}licenses $package

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy directory ${c_notice}${path_build}licenses${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
        fi

        let failure=1
      fi
    elif [[ -d ${path_build}../licenses ]] ; then
      cp $verbose_common -R ${path_build}../licenses $package

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy directory ${c_notice}${path_build}../licenses${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
        fi

        let failure=1
      fi
    else
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Neither directory ${c_notice}${path_build}licenses${c_error} nor ${c_notice}${path_build}../licenses${c_error} can be found or are invalid.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ $failure == "" ]] ; then
    cp $verbose_common -R ${path_build}scripts/bootstrap.sh $package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy script ${c_notice}${path_build}bootstrap.sh${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1
    fi

    if [[ $failure == "" ]] ; then
      chmod ugo+x ${package}bootstrap.sh

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to set executable permissions on script ${c_notice}${package}bootstrap.sh${c_error}.${c_reset}"
        fi

        let failure=1
      fi
    fi

    if [[ $failure == "" ]] ; then
      cp $verbose_common -R ${path_build}scripts/install.sh $package

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy script ${c_notice}${path_build}install.sh${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
        fi

        let failure=1
      fi
    fi

    if [[ $failure == "" ]] ; then
      chmod ugo+x ${package}install.sh

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to set executable permissions on script ${c_notice}${package}install.sh${c_error}.${c_reset}"
        fi

        let failure=1
      fi
    fi
  fi

  if [[ $failure != "" && ! -d ${package}build ]] ; then
    mkdir $verbose_common -p ${package}build

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}build${c_error}.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}sources ]] ; then
    mkdir $verbose_common -p ${package}sources

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}sources${c_error}.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}documents ]] ; then
    mkdir $verbose_common -p ${package}documents

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}documents${c_error}.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}licenses ]] ; then
    mkdir $verbose_common -p ${package}licenses

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}licenses${c_error}.${c_reset}"
      fi

      let failure=1
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
  local dependencies_0=
  local dependencies_1=
  local dependencies_2=
  local dependencies_thread=
  local dependencies_individual=
  local dependencies_individual_threadless=
  local dependency=
  local dependency_file=
  local dependency_files=
  local dependency_suffix=
  local has_thread=
  local sub_level=
  local sub_dependencies=
  local sub_dependency=
  local sub_sub_level=
  local sub_sub_dependencies=
  local sub_sub_dependency=

  for directory in ${path_sources}level_0/* ${path_sources}level_1/* ${path_sources}level_2/* ${path_sources}level_3/* ; do

    name="$(echo $directory | sed -e "s|${path_sources}level_0/||" -e "s|${path_sources}level_1/||" -e "s|${path_sources}level_2/||" -e "s|${path_sources}level_3/||")"

    level_current="$(echo $directory | grep -o '\<level_[[:digit:]]/' | sed -e 's|level_||' -e 's|/$||')"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Building Dependencies for ${c_reset}${c_notice}${name}${c_reset}${c_highlight}.${c_reset}"
    fi

    if [[ ! -d ${directory}/data/build/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_warning}WARNING: The project build directory ${c_notice}${dependency_file}${c_warning} is not found.${c_reset}"
      fi

      continue
    fi

    # Additional dependency files are only supported in level_3.
    if [[ $(echo "$directory" | grep -o "^${path_sources}level_3/") != "" ]] ; then
      dependency_files="yes"

      # When the files don't exist bash treats the pattern as a literal file.
      # Do not loop through this wild-carded name (a file with the unexpanded name 'dependencies.*' is therefore not supported).
      for dependency_file in ${directory}/data/build/dependencies.* ; do

        if [[ "${directory}/data/build/dependencies.*" == $dependency_file ]] ; then
          dependency_files="no"
        fi

        break
      done
    else
      dependency_files="no"
    fi

    for dependency_file in ${directory}/data/build/dependencies{,.*} ; do

      if [[ ! -f $dependency_file ]] ; then

        if [[ $dependency_files == "yes" && "${directory}/data/build/dependencies" != $dependency_file ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: The dependency file ${c_notice}${dependency_file}${c_warning} is not found.${c_reset}"
          fi
        elif [[ $dependency_files == "no" && "${directory}/data/build/dependencies.*" != $dependency_file ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Cannot build dependencies, failed to find ${c_notice}${dependency_file}${c_error} file(s).${c_reset}"
          fi
        fi

        continue
      fi

      if [[ $dependency_file == "${directory}/data/build/dependencies" ]] ; then
        dependency_suffix=
      else
        dependency_suffix=$(echo $dependency_file | sed -e "s|^${directory}/data/build/dependencies||")
      fi

      if [[ ! -f ${directory}/data/build/settings${dependency_suffix} ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Cannot build dependencies for ${c_reset}${c_notice}${name}${c_reset}${c_error}, failed to find ${c_notice}${directory}/data/build/settings${dependency_suffix}${c_error}.${c_reset}"
        fi

        let failure=1

        return
      fi

      dependencies=
      dependencies_0=
      dependencies_1=
      dependencies_2=
      dependencies_thread=
      dependencies_individual=
      has_thread=

      dependencies=$(cat $dependency_file | sed -e "/^\s*#/d" -e "s|#\.*$||")

      if [[ $(echo "$dependencies" | grep -o "\<f_thread\>") != "" ]] ; then
        has_thread="yes"
      fi

      for dependency in $dependencies ; do

        if [[ $(echo "$dependency" | grep -o "^f_") != "" ]] ; then
          level=level_0
        elif [[ $(echo "$dependency" | grep -o "^fl_") != "" ]] ; then
          level=level_1
        elif [[ $(echo "$dependency" | grep -o "^fll_") != "" ]] ; then
          level=level_2
        else
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_warning}WARNING: Failed to detect level for dependency ${c_notice}${dependency}${c_warning}.${c_reset}"
          fi

          continue
        fi

        if [[ ! -d ${path_sources}${level}/${dependency}/data/build/ ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Failed to find dependency data directory ${c_notice}${path_sources}${level}/${dependency}/data/build/${c_error}.${c_reset}"
          fi

          let failure=1

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
              echo -e "${c_warning}WARNING: Failed to detect level for sub-dependency ${c_notice}${sub_dependency}${c_warning}.${c_reset}"
            fi

            continue
          fi

          if [[ ! -d ${path_sources}${sub_level}/${sub_dependency}/data/build/ ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to find dependency data directory ${c_notice}${path_sources}${sub_level}/${sub_dependency}/data/build/${c_error}.${c_reset}"
            fi

            let failure=1

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
                echo -e "${c_warning}WARNING: Failed to detect level for sub-sub-dependency ${c_notice}$sub_sub_dependency${c_warning}.${c_reset}"
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

      if [[ $failure != "" ]] ; then
        break;
      fi

      dependencies_individual=$(echo "$dependencies_individual" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||' -e 's|[[:space:]][[:space:]]*$| |')
      if [[ $dependencies_individual != "" ]] ; then
        if [[ $verbosity == "verbose" ]] ; then
          echo -e " $dependencies_individual"
        fi

        dependencies_individual=" $dependencies_individual"
      fi

      settings=${directory}/data/build/settings${dependency_suffix}
      sed -i -e "s|^\s*build_libraries-individual[[:space:]].*\$|build_libraries-individual${dependencies_individual}|" $settings &&
      sed -i -e "s|^\s*build_libraries-individual\$|build_libraries-individual${dependencies_individual}|" $settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to update settings file ${c_notice}${settings}${c_error}.${c_reset}"
        fi

        let failure=1

        break
      fi

      if [[ $has_thread == "yes" && $dependencies_individual != "" && $(grep -o "^\s*build_libraries-individual_threadless\>" $settings) != "" ]] ; then
        dependencies_individual_threadless=$(echo "$dependencies_individual" | sed -e "s| \-lf_thread\>||g")

        if [[ $verbosity == "verbose" ]] ; then
          echo -e " (threadless) $dependencies_individual_threadless"
        fi

        settings=${directory}/data/build/settings
        sed -i -e "s|^\s*build_libraries-individual_threadless[[:space:]].*\$|build_libraries-individual_threadless${dependencies_individual_threadless}|" $settings &&
        sed -i -e "s|^\s*build_libraries-individual_threadless\$|build_libraries-individual_threadless${dependencies_individual_threadless}|" $settings

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Failed to update settings file ${c_notice}${settings}${c_error}.${c_reset}"
          fi

          let failure=1

          break
        fi
      fi

      # All level 3 are expected to support all modes: individual, level, and monolithic.
      if [[ $level_current == "3" ]] ; then
        sed -i -e "s|^\s*build_libraries-level\>.*\$|build_libraries-level -lfll_2 -lfll_1 -lfll_0|" $settings &&
        sed -i -e "s|^\s*build_libraries-level\$|build_libraries-level -lfll_2 -lfll_1 -lfll_0|" $settings

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Failed to update settings file ${c_notice}${settings}${c_error}.${c_reset}"
          fi

          let failure=1

          break
        fi

        sed -i -e "s|^\s*build_libraries-monolithic\>.*\$|build_libraries-monolithic -lfll|" $settings &&
        sed -i -e "s|^\s*build_libraries-monolithic\$|build_libraries-monolithic -lfll|" $settings

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Failed to update settings file ${c_notice}${settings}${c_error}.${c_reset}"
          fi

          let failure=1

          break
        fi
      fi
    done

    if [[ $failure != "" ]] ; then
      break;
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
      echo -e "${c_error}ERROR: Failed to find dependency settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi

  libraries=$(grep -o '^\s*build_sources_library\s.*$' $settings | sed -e 's|^\s*build_sources_library\>||' -e 's|^\s*||' -e 's|\s*$||')

  if [[ $libraries != "" ]] ; then
    if [[ $(echo -n $dependencies_individual | grep -o "\-l$dependency\>") == "" ]] ; then

      if [[ "$(type -p sort)" != "" ]] ; then
        if [[ $level == "level_0" ]] ; then
          dependencies_0="-l$dependency $dependencies_0"
          dependencies_0="$(for i in $dependencies_0; do echo $i ; done | sort)"
          dependencies_0=$(echo $dependencies_0)
        elif [[ $level == "level_1" ]] ; then
          dependencies_1="-l$dependency $dependencies_1"
          dependencies_1=" $(for i in $dependencies_1; do echo $i ; done | sort)"
          dependencies_1=$(echo $dependencies_1)
        else
          dependencies_2="-l$dependency $dependencies_2"
          dependencies_2=" $(for i in $dependencies_2; do echo $i ; done | sort)"
          dependencies_2=$(echo $dependencies_2)
        fi
      else

        # Sort is not available, so do not bother trying to sort.
        if [[ $level == "level_0" ]] ; then
          dependencies_0="-l$dependency $dependencies_0"
        elif [[ $level == "level_1" ]] ; then
          dependencies_1="-l$dependency $dependencies_1"
        else
          dependencies_2="-l$dependency $dependencies_2"
        fi
      fi

      dependencies_individual=

      if [[ $dependencies_0 != "" ]] ; then
        dependencies_individual="$dependencies_0"
      fi

      if [[ $dependencies_1 != "" ]] ; then
        dependencies_individual="$dependencies_1 $dependencies_individual"
      fi

      if [[ $dependencies_2 != "" ]] ; then
        dependencies_individual="$dependencies_2 $dependencies_individual"
      fi
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
  local level_sources_library_threaded=
  local level_sources_headers_threaded=
  local monolithic_libraries=
  local monolithic_headers=
  local monolithic_libraries_threaded=
  local monolithic_headers_threaded=

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Building Dependencies: ${c_notice}${level}${c_highlight}.${c_reset}"
  fi

  for directory in $path_sources${level}/* ; do

    name="$(echo $directory | sed -e "s|${path_sources}${level}/||")"

    settings=${directory}/data/build/settings
    if [[ ! -f $settings ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to find settings file ${c_notice}${settings}${c_error}.${c_reset}"
      fi

      let failure=1

      return
    fi

    libraries=$(grep -o '^\s*build_sources_library\s.*$' $settings | sed -e 's|^\s*build_sources_library\>||' -e 's|^\s*||' -e 's|\s*$||')

    for library in $libraries ; do

      if [[ $name == "f_thread" ]] ; then
        level_sources_library_threaded="$level_sources_library_threaded $library"
        monolithic_libraries_threaded="$monolithic_libraries_threaded ${level}/${library}"
      else
        level_sources_library="$level_sources_library $library"
        monolithic_libraries="$monolithic_libraries ${level}/${library}"
      fi
    done

    headers=$(grep -o '^\s*build_sources_headers\s.*$' $settings | sed -e 's|^\s*build_sources_headers\>||' -e 's|^\s*||' -e 's|\s*$||')

    for header in $headers ; do

      if [[ $name == "f_thread" ]] ; then
        level_sources_headers_threaded="$level_sources_headers_threaded $header"
        monolithic_headers_threaded="$monolithic_headers_threaded ${level}/${header}"
      else
        level_sources_headers="$level_sources_headers $header"
        monolithic_headers="$monolithic_headers ${level}/${header}"
      fi
    done
  done

  settings=${path_sources}/build/${level}/settings

  if [[ ! -f $settings ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to find settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi

  sed -i -e "s|^\s*build_libraries-level\s.*\$|build_libraries-level${level_libraries}|" $settings &&
  sed -i -e "s|^\s*build_libraries-level\$|build_libraries-level${level_libraries}|" $settings &&
  sed -i -e "s|^\s*build_libraries-level_threadless\s.*\$|build_libraries-level_threadless${level_libraries}|" $settings &&
  sed -i -e "s|^\s*build_libraries-level_threadless\$|build_libraries-level_threadless${level_libraries}|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update libraries for settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi

  level_sources_library=$(echo "$level_sources_library" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  if [[ $level_sources_library != "" ]] ; then
    echo " $level_sources_library"
    level_sources_library=" $level_sources_library"
  fi

  sed -i -e "s|^\s*build_sources_library\s.*\$|build_sources_library${level_sources_library}|" $settings &&
  sed -i -e "s|^\s*build_sources_library\$|build_sources_library${level_sources_library}|" $settings &&
  sed -i -e "s|^\s*build_sources_library-level\s.*\$|build_sources_library-level${level_sources_library_threaded}|" $settings &&
  sed -i -e "s|^\s*build_sources_library-level\$|build_sources_library-level${level_sources_library_threaded}|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update libraries for settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi

  level_sources_headers=$(echo "$level_sources_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  if [[ $level_sources_headers != "" ]] ; then
    echo " $level_sources_headers"
    level_sources_headers=" $level_sources_headers"
  fi

  sed -i -e "s|^\s*build_sources_headers\s.*\$|build_sources_headers${level_sources_headers}|" $settings &&
  sed -i -e "s|^\s*build_sources_headers\$|build_sources_headers${level_sources_headers}|" $settings &&
  sed -i -e "s|^\s*build_sources_headers-level\s.*\$|build_sources_headers-level${level_sources_headers_threaded}|" $settings &&
  sed -i -e "s|^\s*build_sources_headers-level\$|build_sources_headers-level${level_sources_headers_threaded}|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update headers for settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi

  if [[ $level == "level_0" ]] ; then
    level_0_libraries=$(echo "$monolithic_libraries" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_0_headers=$(echo "$monolithic_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')

    level_0_libraries_threaded=$(echo "$monolithic_libraries_threaded" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_0_headers_threaded=$(echo "$monolithic_headers_threaded" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  elif [[ $level == "level_1" ]] ; then
    level_1_libraries=$(echo "$monolithic_libraries" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_1_headers=$(echo "$monolithic_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')

    level_1_libraries_threaded=$(echo "$monolithic_libraries_threaded" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_1_headers_threaded=$(echo "$monolithic_headers_threaded" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  elif [[ $level == "level_2" ]] ; then
    level_2_libraries=$(echo "$monolithic_libraries" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_2_headers=$(echo "$monolithic_headers" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')

    level_2_libraries_threaded=$(echo "$monolithic_libraries_threaded" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
    level_2_headers_threaded=$(echo "$monolithic_headers_threaded" | sed -e 's|^[[:space:]]*||' -e 's|[[:space:]]*$||')
  fi
}

package_dependencies_monolithic() {
  local monolithic_libraries=""
  local monolithic_libraries_threaded=""
  local monolithic_headers=""
  local monolithic_headers_threaded=""

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Building Dependencies: ${c_notice}monolithic${c_highlight}.${c_reset}"
  fi

  if [[ $level_0_libraries != "" ]] ; then
    monolithic_libraries="$level_0_libraries"
  fi

  if [[ $level_0_libraries_threaded != "" ]] ; then
    monolithic_libraries_threaded="$level_0_libraries_threaded"
  fi

  if [[ $level_0_headers != "" ]] ; then
    monolithic_headers="$level_0_headers"
  fi

  if [[ $level_0_headers_threaded != "" ]] ; then
    monolithic_headers_threaded="$level_0_headers_threaded"
  fi

  if [[ $level_1_libraries != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_libraries="$level_1_libraries"
    else
      monolithic_libraries="$monolithic_libraries $level_1_libraries"
    fi
  fi

  if [[ $level_1_libraries_threaded != "" ]] ; then
    if [[ $monolithic_libraries_threaded == "" ]] ; then
      monolithic_libraries_threaded="$level_1_libraries_threaded"
    else
      monolithic_libraries_threaded="$monolithic_libraries_threaded $level_1_libraries_threaded"
    fi
  fi

  if [[ $level_1_headers != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_headers="$level_1_headers"
    else
      monolithic_headers="$monolithic_headers $level_1_headers"
    fi
  fi

  if [[ $level_1_headers_threaded != "" ]] ; then
    if [[ $monolithic_libraries_threaded == "" ]] ; then
      monolithic_headers_threaded="$level_1_headers_threaded"
    else
      monolithic_headers_threaded="$monolithic_headers_threaded $level_1_headers_threaded"
    fi
  fi

  if [[ $level_2_libraries != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_libraries="$level_2_libraries"
    else
      monolithic_libraries="$monolithic_libraries $level_2_libraries"
    fi
  fi

  if [[ $level_2_libraries_threaded != "" ]] ; then
    if [[ $monolithic_libraries_threaded == "" ]] ; then
      monolithic_libraries_threaded="$level_2_libraries_threaded"
    else
      monolithic_libraries_threaded="$monolithic_libraries_threaded $level_2_libraries_threaded"
    fi
  fi

  if [[ $level_2_headers != "" ]] ; then
    if [[ $monolithic_libraries == "" ]] ; then
      monolithic_headers="$level_2_headers"
    else
      monolithic_headers="$monolithic_headers $level_2_headers"
    fi
  fi

  if [[ $level_2_headers_threaded != "" ]] ; then
    if [[ $monolithic_libraries_threaded == "" ]] ; then
      monolithic_headers_threaded="$level_2_headers_threaded"
    else
      monolithic_headers_threaded="$monolithic_headers_threaded $level_2_headers_threaded"
    fi
  fi

  settings=${path_sources}/build/monolithic/settings

  if [[ $monolithic_libraries != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo " $monolithic_libraries"
    fi

    monolithic_libraries=" $monolithic_libraries"
  fi

  if [[ $monolithic_libraries_threaded != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo " (threaded) $monolithic_libraries_threaded"
    fi

    monolithic_libraries_threaded=" $monolithic_libraries_threaded"
  fi

  sed -i -e "s|^\s*build_sources_library\s.*\$|build_sources_library${monolithic_libraries}|" $settings &&
  sed -i -e "s|^\s*build_sources_library\$|build_sources_library${monolithic_libraries}|" $settings &&
  sed -i -e "s|^\s*build_sources_library-monolithic\s.*\$|build_sources_library-monolithic${monolithic_libraries_threaded}|" $settings &&
  sed -i -e "s|^\s*build_sources_library-monolithic\$|build_sources_library-monolithic${monolithic_libraries_threaded}|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update libraries for settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi

  if [[ $monolithic_headers != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo " $monolithic_headers"
    fi

    monolithic_headers=" $monolithic_headers"
  fi

  if [[ $monolithic_headers_threaded != "" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo " (threaded) $monolithic_headers_threaded"
    fi

    monolithic_headers_threaded=" $monolithic_headers_threaded"
  fi

  sed -i -e "s|^\s*build_sources_headers\s.*\$|build_sources_headers${monolithic_headers}|" $settings &&
  sed -i -e "s|^\s*build_sources_headers\$|build_sources_headers${monolithic_headers}|" $settings &&
  sed -i -e "s|^\s*build_sources_headers-monolithic\s.*\$|build_sources_headers-monolithic${monolithic_headers_threaded}|" $settings &&
  sed -i -e "s|^\s*build_sources_headers-monolithic\$|build_sources_headers-monolithic${monolithic_headers_threaded}|" $settings

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to update headers for settings file ${c_notice}${settings}${c_error}.${c_reset}"
    fi

    let failure=1

    return
  fi
}

package_operation_clean() {
  local i=

  if [[ $mode_individual == "yes" ]] ; then
    if [[ -d ${path_destination}individual ]] ; then
      rm $verbose_common -Rf ${path_destination}individual

      if [[ $? -ne 0 ]] ; then
        let failure=1

        return
      fi
    fi

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo "Cleaned '${path_destination}individual'."
    fi
  fi

  if [[ $mode_level == "yes" ]] ; then
    if [[ -d ${path_destination}level ]] ; then
      rm $verbose_common -Rf ${path_destination}level

      if [[ $? -ne 0 ]] ; then
        let failure=1

        return
      fi
    fi

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo "Cleaned '${path_destination}level'."
    fi
  fi

  if [[ $mode_monolithic == "yes" ]] ; then
    if [[ -d ${path_destination}monolithic ]] ; then
      rm $verbose_common -Rf ${path_destination}monolithic

      if [[ $? -ne 0 ]] ; then
        let failure=1

        return
      fi
    fi

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo "Cleaned '${path_destination}monolithic'."
    fi
  fi

  if [[ $mode_program == "yes" ]] ; then
    if [[ -d ${path_destination}program ]] ; then
      rm $verbose_common -Rf ${path_destination}program

      if [[ $? -ne 0 ]] ; then
        let failure=1

        return
      fi
    fi

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo "Cleaned '${path_destination}program'."
    fi
  fi

  if [[ $mode_stand_alone != "" ]] ; then
    if [[ -d ${path_destination}stand_alone ]] ; then

      for i in $mode_stand_alone ; do

        if [[ -d ${path_destination}stand_alone/${prepend}${i}-${version}/ ]] ; then
          rm $verbose_common -Rf ${path_destination}stand_alone/${prepend}${i}-${version}/

          if [[ $? -ne 0 ]] ; then
            let failure=1

            return
          fi
        fi

        if [[ $verbosity != "quiet" ]] ; then
          echo
          echo "Cleaned '${path_destination}stand_alone/${prepend}${i}-${version}/'."
        fi
      done

      rmdir $verbose_common --ignore-fail-on-non-empty ${path_destination}stand_alone
    else
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo "Cleaned '${path_destination}stand_alone'."
      fi
    fi
  fi
}

package_operation_copy_package() {

  if [[ -d ${package}sources/data/ ]] ; then
    cp $verbose_common -R ${package}sources/data ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy the data directory ${c_notice}${package}sources/data${c_error} to ${c_notice}$package${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi

    rm $verbose_common -Rf ${package}sources/data

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove directory ${c_notice}${package}sources/data${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi

    package_operation_create_config_stubs
  fi

  if [[ -d ${package}sources/documents/ ]] ; then
    cp $verbose_common -R ${package}sources/documents/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources documents directory ${c_notice}${path_sources}sources/documents${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi

    rm $verbose_common -Rf ${package}sources/documents/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources documents directory ${c_notice}${path_sources}sources/documents${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi
  fi

  if [[ -d ${package}sources/licenses/ ]] ; then
    cp $verbose_common -R ${package}sources/licenses/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources licenses directory ${c_notice}${path_sources}sources/licenses${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi

    rm $verbose_common -Rf ${package}sources/licenses/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources licenses directory ${c_notice}${path_sources}sources/licenses${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi
  fi

  if [[ -d ${package}sources/specifications/ ]] ; then
    cp $verbose_common -R ${package}sources/specifications/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources specifications directory ${c_notice}${path_sources}sources/specifications${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi

    rm $verbose_common -Rf ${package}sources/specifications/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources specifications directory ${c_notice}${path_sources}sources/specifications${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi
  fi

  if [[ -d ${package}sources/tests/ ]] ; then
    cp $verbose_common -R ${package}sources/tests/ ${package}

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move sources tests directory ${c_notice}${path_sources}sources/tests${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi

    rm $verbose_common -Rf ${package}sources/tests/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to remove sources tests directory ${c_notice}${path_sources}sources/tests${c_error} to ${c_notice}${package}${c_error}.${c_reset}"
      fi

      let failure=1

      return $failure
    fi
  fi
}

package_operation_create_config_stubs() {

  if [[ ! -f ${package}data/build/settings ]] ; then
    return 0
  fi

  local language=

  if [[ $(grep -soP '^\s*\bbuild_language\b\s+c\s*$' ${package}data/build/settings) != "" ]] ; then
    language="c"
  elif [[  $(grep -soP '^\s*\bbuild_language\b\s+c\+\+\s*$' ${package}data/build/settings) != "" ]] ; then
    language="c++"
  else
    return 0
  fi

  if [[ $language == "c" && ! -f ${package}sources/c/config.c ]] ; then
    if [[ $(grep -soP '^\s*\bbuild_sources_program\b\s+\S' ${package}data/build/settings) != "" ]] ; then
      sed -i -E -e "s|^\s*\bbuild_sources_program\s+|&config.c |" ${package}data/build/settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to insert the config.c into ${c_notice}${package}data/build/settings${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    elif [[ $(grep -soP '^\s*\bbuild_sources_library\b\s+\S' ${package}data/build/settings) != "" ]] ; then
      sed -i -E -e "s|^\s*\bbuild_sources_library\s+|&config.c |" ${package}data/build/settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to insert the config.c into ${c_notice}${package}data/build/settings${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    fi

    if [[ $(grep -soP '^\s*\bbuild_sources_program\b\s+\S' ${package}data/build/settings) != "" || $(grep -soP '^\s*\bbuild_sources_library\b\s+\S' ${package}data/build/settings) != "" ]] ; then
      echo > ${package}sources/c/config.c &&
      echo "#include \"config.h\"" >> ${package}sources/c/config.c

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create the config.c at ${c_notice}${package}sources/c/config.c${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    fi
  elif [[ $language == "c++" && ! -f ${package}sources/c/config.cpp ]] ; then
    if [[ $(grep -soP '^\s*\bbuild_sources_program\b\s+\S' ${package}data/build/settings) != "" ]] ; then
      sed -i -E -e "s|^\s*\bbuild_sources_program\s+|&config.cpp |" ${package}data/build/settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to insert the config.cpp into ${c_notice}${package}data/build/settings${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    elif [[ $(grep -soP '^\s*\bbuild_sources_library\b\s+\S' ${package}data/build/settings) != "" ]] ; then
      sed -i -E -e "s|^\s*\bbuild_sources_library\s+|&config.cpp |" ${package}data/build/settings

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to insert the config.cpp into ${c_notice}${package}data/build/settings${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    fi

    if [[ $(grep -soP '^\s*\bbuild_sources_program\b\s+\S' ${package}data/build/settings) != "" || $(grep -soP '^\s*\bbuild_sources_library\b\s+\S' ${package}data/build/settings) != "" ]] ; then
      echo > ${package}sources/c++/config.cpp &&
      echo "#include \"config.h\"" >> ${package}sources/c++/config.cpp

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create the config.cpp at ${c_notice}${package}sources/c++/config.cpp${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    fi
  fi

  if [[ ( $language == "c" && ! -f ${package}sources/c/config.h ) || ( $language == "c++" && ! -f ${package}sources/c++/config.h ) ]] ; then
    if [[ $(grep -soP '^\s*\bbuild_language\b\s+c\s*$' ${package}data/build/settings) != "" ]] ; then
      echo > ${package}sources/c/config.h

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create the config.cpp at ${c_notice}${package}sources/c/config.h${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
    else
      echo > ${package}sources/c++/config.h

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create the config.cpp at ${c_notice}${package}sources/c++/config.h${c_error}.${c_reset}"
        fi

        let failure=1

        return $failure
      fi
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
    mkdir $verbose_common -p ${path_destination}individual

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${path_destination}individual${c_error}.${c_reset}"
      fi

      package_cleanup

      exit $failure
    fi
  fi

  for directory in ${path_sources}level_0/* ${path_sources}level_1/* ${path_sources}level_2/* ; do

    name="$(echo $directory | sed -e "s|${path_sources}level_0/||" -e "s|${path_sources}level_1/||" -e "s|${path_sources}level_2/||")"
    package="${path_destination}individual/${prepend}${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project${c_reset} (individual) ${c_notice}${prepend}${name}-${version}${c_reset}${c_highlight}.${c_reset}"
    fi

    package_create_base_files

    cp $verbose_common -R $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy sources directory ${c_notice}${directory}${c_error} to ${c_notice}${package}sources${c_error}.${c_reset}"
      fi

      let failure=1

      break
    fi

    package_operation_copy_package

    if [[ $failure != "" ]] ; then
      break;
    fi
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
    package="${path_destination}level/${prepend}${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project${c_reset} (level) ${c_notice}${prepend}${name}-${version}${c_reset}${c_highlight}.${c_reset}"
    fi

    if [[ ! -d $path_build$level ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Build settings directory ${c_notice}${path_build}${level}${c_error} is invalid or missing.${c_reset}"
      fi

      let failure=1

      break
    fi

    package_create_base_files

    if [[ ! -d ${package}data/ ]] ; then
      mkdir $verbose_common ${package}data/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}data${c_error}.${c_reset}"
        fi

        let failure=1

        break
      fi
    fi

    if [[ -d $path_build${level}/build ]] ; then
      cp $verbose_common -R ${path_build}${level}/build ${package}data/
    else
      cp $verbose_common -R ${path_build}${level} ${package}data/build
    fi

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to move the directory ${c_notice}${path_build}${level}${c_error} as ${c_notice}${path_build}${level}build${c_error}.${c_reset}"
      fi

      let failure=1

      break
    fi

    if [[ ! -d ${package}sources/ ]] ; then
      mkdir $verbose_common ${package}sources/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}sources${c_error}.${c_reset}"
        fi

        let failure=1

        break
      fi
    fi

    for directory in ${path_sources}${level}/* ; do

      cp $verbose_common -R ${directory}/* ${package}sources/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy files from sources directory ${c_notice}${directory}${c_error} to ${c_notice}${package}sources${c_error}.${c_reset}"
        fi

        let failure=1

        break
      fi

      rm $verbose_common -Rf ${package}sources/data/build/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to remove directory ${c_notice}${package}sources/data/build${c_error}.${c_reset}"
        fi

        let failure=1
        break
      fi

      package_operation_copy_package

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

package_operation_monolithic() {
  local failure=
  local name=
  local level=
  local directory=
  local package=
  local directory_sub=
  local path_name=

  name="fll"
  package="${path_destination}monolithic/${prepend}${name}-${version}/"

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Packaging Project${c_reset} (monolithic) ${c_notice}${prepend}${name}-${version}${c_reset}${c_highlight}.${c_reset}"
  fi

  if [[ ! -d ${path_build}monolithic ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Build settings directory ${c_notice}${path_build}monolithic${c_error} is invalid or missing.${c_reset}"
    fi

    package_cleanup

    return 1
  fi

  package_create_base_files

  if [[ ! -d ${package}data/ ]] ; then
    mkdir $verbose_common ${package}data/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}data${c_error}.${c_reset}"
      fi

      package_cleanup

      return 1
    fi
  fi

  if [[ -d ${path_build}monolithic/build ]] ; then
    cp $verbose_common -R ${path_build}monolithic/build ${package}data
  else
    cp $verbose_common -R ${path_build}monolithic ${package}data/build
  fi

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Failed to move the directory ${c_notice}${path_build}${level}${c_error} as ${c_notice}${path_build}${level}build${c_error}.${c_reset}"
    fi

    package_cleanup

    return 1
  fi

  if [[ ! -d ${package}sources/ ]] ; then
    mkdir $verbose_common ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}sources${c_error}.${c_reset}"
      fi

      package_cleanup

      return 1
    fi
  fi

  if [[ ! -d ${package}tests/ ]] ; then
    mkdir $verbose_common ${package}tests/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${package}tests${c_error}.${c_reset}"
      fi

      package_cleanup

      return 1
    fi
  fi

  for level in level_0 level_1 level_2 ; do

    for directory in $path_sources${level}/* ; do

      for directory_sub in $directory/* ; do

        path_name="$(basename $directory_sub)"

        if [[ $path_name == "data" ]] ; then
          if [[ ! -d ${package}data/$level ]] ; then
            mkdir $verbose_common -p ${package}data/$level

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to create package data directory ${c_notice}${package}data/${level}${c_error}.${c_reset}"
              fi

              let failure=1

              break
            fi
          fi

          cp $verbose_common -R $directory_sub ${package}sources/data

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory ${c_notice}${directory_sub}${c_error} to ${c_notice}${package}sources/data$level${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi

          rm $verbose_common -Rf ${package}sources/data/build/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to remove directory ${c_notice}${package}sources/data/build${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi

          if [[ "$(ls ${package}sources/data)" != "" ]] ; then
            cp $verbose_common -R ${package}sources/data/* ${package}data/${level}

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to copy the data directory ${c_notice}${package}sources/data/${level}/data${c_error} to ${c_notice}${package}data/${level}${c_error}.${c_reset}"
              fi

              let failure=1

              break
            fi
          fi

          rm $verbose_common -Rf ${package}sources/data

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to remove directory ${c_notice}${package}sources/data${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi
        elif [[ $path_name == "documents" ]] ; then
          cp $verbose_common -R $directory_sub ${package}sources/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory ${c_notice}${directory_sub}${c_error} to ${c_notice}${package}sources/documents${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi
        elif [[ $path_name == "licenses" ]] ; then
          cp $verbose_common -R $directory_sub ${package}sources/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory ${c_notice}${directory_sub}${c_error} to ${c_notice}${package}sources/licenses${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi
        elif [[ $path_name == "specifications" ]] ; then
          cp $verbose_common -R $directory_sub ${package}sources/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory ${c_notice}${directory_sub}${c_error} to ${c_notice}${package}sources/specifications${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi
        elif [[ $path_name == "tests" ]] ; then
          cp $verbose_common -R $directory_sub ${package}

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from data directory ${c_notice}${directory_sub}${c_error} to ${c_notice}${package}tests${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi
        else
          if [[ ! -d ${package}sources/${path_name}/${level} ]] ; then
            mkdir $verbose_common -p ${package}sources/${path_name}/${level}

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to create package sources directory ${c_notice}${package}sources/${path_name}/${level}${c_error}.${c_reset}"
              fi

              let failure=1

              break
            fi
          fi

          cp $verbose_common -R ${directory_sub}/* ${package}sources/${path_name}/${level}

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to copy files from sources directory ${c_notice}${directory_sub}${c_error} to ${c_notice}${package}sources/${path_name}/${level}${c_error}.${c_reset}"
            fi

            let failure=1

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

  if [[ $failure == "" ]] ; then
    package_operation_create_config_stubs
  fi

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
    mkdir $verbose_common -p ${path_destination}program

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${path_destination}program${c_error}.${c_reset}"
      fi

      package_cleanup

      exit $failure
    fi
  fi

  for directory in ${path_sources}level_3/* ; do

    name="$(echo $directory | sed -e "s|${path_sources}level_3/||")"
    package="${path_destination}program/${prepend}${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project${c_reset} (program) ${c_notice}${prepend}${name}-${version}${c_reset}${c_highlight}.${c_reset}"
    fi

    package_create_base_files

    cp $verbose_common -R $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy sources directory ${c_notice}${directory}${c_error} to ${c_notice}${package}sources${c_error}.${c_reset}"
      fi

      let failure=1

      break
    fi

    package_operation_copy_package

    if [[ $failure != "" ]] ; then
      break
    fi
  done

  if [[ $failure != "" ]] ; then
    package_cleanup

    exit $failure
  fi
}

package_operation_stand_alone() {
  local failure=
  local name=
  local directory=
  local directory_level=
  local directory_sub=
  local package=
  local package_sub=
  local packages=
  local level=
  local path_=
  local path_sub=
  local path_name=
  local path_name_sub=

  if [[ ! -d ${path_destination}stand_alone ]] ; then
    mkdir $verbose_common -p ${path_destination}stand_alone

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to create directory ${c_notice}${path_destination}stand_alone${c_error}.${c_reset}"
      fi

      package_cleanup

      exit $failure
    fi
  fi

  for name in $mode_stand_alone ; do

    directory="${path_sources}level_3/${name}"
    package="${path_destination}stand_alone/${prepend}${name}-${version}/"

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Packaging Project${c_reset} (stand_alone) ${c_notice}${prepend}${name}-${version}${c_reset}${c_highlight}.${c_reset}"
    fi

    package_create_base_files

    cp $verbose_common -R $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy sources directory ${c_notice}${directory}${c_error} to ${c_notice}${package}sources${c_error}.${c_reset}"
      fi

      let failure=1

      break
    fi

    package_operation_copy_package

    if [[ $failure != "" ]] ; then
      break
    fi

    cp $verbose_common -R ${path_build}stand_alone/${name}.settings ${package}data/build/settings

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: Failed to copy file ${c_notice}${path_build}stand_alone/${name}.settings${c_error} to ${c_notice}${package}data/build/settings${c_error}.${c_reset}"
      fi

      let failure=1

      break
    fi

    if [[ ! -d ${package}sources/c/program/${name}/ ]] ; then
      mkdir $verbose_common -p ${package}sources/c/program/$name/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to create package sources directory ${c_notice}${package}sources/c/program/${name}/${c_error}.${c_reset}"
        fi

        let failure=1

        break
      fi
    fi

    # Copy all sources into a named sub-directory.
    for path_ in ${package}sources/* ; do

      path_name="$(basename $path_)"

      for path_sub in ${package}sources/${path_name}/* ; do

        path_name_sub="$(basename $path_sub)"

        # Do not attempt copying into self.
        if [[ $path_name_sub == "program" ]] ; then
          continue
        fi

        if [[ ! -d ${package}sources/${path_name}/program/${name}/ ]] ; then
          mkdir $verbose_common -p ${package}sources/${path_name}/program/${name}/

          if [[ $? -ne 0 ]] ; then
            if [[ $verbosity != "quiet" ]] ; then
              echo -e "${c_error}ERROR: Failed to create package sources directory ${c_notice}${package}sources/${path_name}/program/${name}/${c_error}.${c_reset}"
            fi

            let failure=1

            break
          fi
        fi

        mv $verbose_common $path_sub ${package}sources/${path_name}/program/${name}/

        if [[ $? -ne 0 ]] ; then
          if [[ $verbosity != "quiet" ]] ; then
            echo -e "${c_error}ERROR: Failed to move path ${c_notice}${path_sub}${c_error} to ${c_notice}${package}sources/${path_name}/program/${name}/${c_error}.${c_reset}"
          fi

          let failure=1

          break
        fi
      done

      if [[ $failure != "" ]] ; then
        break
      fi
    done

    if [[ $failure != "" ]] ; then
      break
    fi

    if [[ -f ${path_build}stand_alone/${name}.config.h ]] ; then
      cp $verbose_common -R ${path_build}stand_alone/${name}.config.h ${package}sources/c/config.h

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo -e "${c_error}ERROR: Failed to copy file ${c_notice}${path_build}stand_alone/config.h${c_error} to ${c_notice}${package}sources/c/${c_error}.${c_reset}"
        fi

        let failure=1

        break
      fi
    fi

    if [[ -f ${package}data/build/dependencies ]] ; then
      packages=$(grep -soP '^\s*[^\s]+' ${package}data/build/dependencies | sed -e 's|^[[:space:]]*||g')

      if [[ $packages != "" ]] ; then
        for package_sub in $packages ; do

          if [[ -d ${path_sources}level_0/${package_sub}/ ]] ; then
            level=level_0
          elif [[ -d ${path_sources}level_1/${package_sub}/ ]] ; then
            level=level_1
          elif [[ -d ${path_sources}level_2/${package_sub}/ ]] ; then
            level=level_2
          else

            # Skip unknown dependencies.
            continue
          fi

          directory_level="${path_sources}${level}/${package_sub}/"

          for directory_sub in ${directory_level}* ; do

            path_name="$(basename $directory_sub)"

            # Skip directories that are not to be copied.
            if [[ $path_name == "data" || $path_name == "documents" || $path_name == "licenses" || $path_name == "specifications" || $path_name == "tests" ]] ; then
              continue
            fi

            if [[ ! -d ${package}sources/${path_name}/fll/${level}/ ]] ; then
              mkdir $verbose_common -p ${package}sources/${path_name}/fll/${level}/

              if [[ $? -ne 0 ]] ; then
                if [[ $verbosity != "quiet" ]] ; then
                  echo -e "${c_error}ERROR: Failed to create package sources directory ${c_notice}${package}sources/${path_name}/fll/${level}/${c_error}.${c_reset}"
                fi

                let failure=1

                break
              fi
            fi

            cp $verbose_common -R ${directory_level}${path_name}/* ${package}sources/${path_name}/fll/${level}/

            if [[ $? -ne 0 ]] ; then
              if [[ $verbosity != "quiet" ]] ; then
                echo -e "${c_error}ERROR: Failed to copy files from sources directory ${c_notice}${directory_level}${path_name}/${c_error} to ${c_notice}${package}sources/${path_name}/fll/${level}/${c_error}.${c_reset}"
              fi

              let failure=1

              break
            fi
          done

          if [[ $failure != "" ]] ; then
            break
          fi
        done

        if [[ $failure != "" ]] ; then
          break
        fi
      fi
    fi
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
  unset package_operation_create_config_stubs
  unset package_operation_dependencies
  unset package_operation_individual
  unset package_operation_level
  unset package_operation_monolithic
  unset package_operation_program
  unset package_operation_stand_alone
  unset package_cleanup
}

package_main $*

#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to create release directories from the project source.
# These release directories can then be used to compile the project or to package the project.
# The dependencies of this script are: bash, chmod, grep, and sed.

package_main(){
  local public_name="Simple FLL Project Package Script"
  local system_name=package
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
  local operation=
  local operation_failure=
  local mode_individual=
  local mode_level=
  local mode_monolithic=
  local mode_program=
  local path_build=build/
  local path_destination=package/
  local path_sources=./

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
    exit 0
  fi

  if [[ ! -d $path_build ]] ; then
    echo -e "${c_error}ERROR: build directory '$path_build' is invalid or missing.$c_reset"
    exit 1
  fi

  if [[ ! -d $path_destination ]] ; then
    mkdir -vp $path_destination
    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: package directory '$path_destination' is invalid or could not be created.$c_reset"
      exit 1
    fi
  fi

  if [[ ! -d $path_sources ]] ; then
    echo -e "${c_error}ERROR: sources directory '$path_sources' is invalid or missing.$c_reset"
    exit 1
  fi

  if [[ ! -d ${path_sources}level_0/ ]] ; then
    echo -e "${c_error}ERROR: build sources directory '${path_sources}level_0/' is invalid or missing.$c_reset"
    exit 1
  fi

  if [[ ! -d ${path_sources}level_1/ ]] ; then
    echo -e "${c_error}ERROR: build sources directory '${path_sources}level_1/' is invalid or missing.$c_reset"
    exit 1
  fi

  if [[ ! -d ${path_sources}level_2/ ]] ; then
    echo -e "${c_error}ERROR: build sources directory '${path_sources}level_2/' is invalid or missing.$c_reset"
    exit 1
  fi

  if [[ ! -d ${path_sources}level_3/ ]] ; then
    echo -e "${c_error}ERROR: build sources directory '${path_sources}level_3/' is invalid or missing.$c_reset"
    exit 1
  fi

  if [[ $operation_failure == "fail-multiple" ]] ; then
    echo -e "${c_error}ERROR: only one operation may be specified at a time.$c_reset"
    exit 1
  elif [[ $operation == "build" ]] ; then
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
  elif [[ $operation == "clean" ]] ; then
    package_operation_clean
  elif [[ $operation == "" ]] ; then
    echo -e "${c_error}ERROR: no operation was given.$c_reset"
    exit 1
  else
    echo -e "${c_error}ERROR: the operation $c_notice$operation$c_error was not recognized.$c_reset"
    exit 1
  fi
}

package_handle_colors(){
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

package_help(){
  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset $c_notice<${c_reset}operation$c_notice>$c_reset"
  echo -e " ${c_important}build${c_reset}  Build the package"
  echo -e " ${c_important}clean${c_reset}  Delete all built packages"
  echo
  echo -e "${c_highlight}Options:$c_reset"
  echo -e " -${c_important}h$c_reset, --${c_important}help$c_reset      Print this help screen"
  echo -e " +${c_important}l$c_reset, ++${c_important}light$c_reset     Use color modes that show up better on light backgrounds"
  echo -e " +${c_important}n$c_reset, ++${c_important}no_color$c_reset  Do not use color"
  echo -e " +${c_important}v$c_reset, ++${c_important}version$c_reset   Print the version number of this program"
  echo
  echo -e "${c_highlight}Package Options:$c_reset"
  echo -e " -${c_important}d$c_reset, --${c_important}destination${c_reset}  Specify a custom package destination directory"
  echo -e " -${c_important}b$c_reset, --${c_important}build${c_reset}        Specify a custom build directory"
  echo -e " -${c_important}i$c_reset, --${c_important}individual${c_reset}   Build packages by individual package (levels 0. 1. and 2)"
  echo -e " -${c_important}l$c_reset, --${c_important}level${c_reset}        Build packages by level (levels 0. 1. and 2)"
  echo -e " -${c_important}m$c_reset, --${c_important}monolithic${c_reset}   Build a monolithic package (levels 0. 1. and 2)"
  echo -e " -${c_important}p$c_reset, --${c_important}program${c_reset}      Build program packages (level 3)"
  echo -e " -${c_important}s$c_reset, --${c_important}sources${c_reset}      Specify a custom sources directory"
  echo
}

package_create_base_files() {

  if [[ ! -d $package ]] ; then
    mkdir -vp $package

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to create directory $c_notice$package$c_error.$c_reset"
      failure=1
    fi
  fi

  if [[ $failure == "" && ! -d ${path_build}documents ]] ; then
    echo -e "${c_error}ERROR: the build directory $c_notice${path_build}documents$c_error cannot be found or is invalid.$c_reset"
    failure=1
  fi

  if [[ $failure == "" ]] ; then
    cp -vR ${path_build}documents $package

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to copy directory $c_notice${path_build}documents$c_error to $c_notice$package$c_error.$c_reset"
      failure=1
    fi
  fi

  if [[ $failure == "" ]] ; then
    if [[ -d ${path_build}licenses ]] ; then
      cp -vR ${path_build}licenses $package

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy directory $c_notice${path_build}licenses$c_error to $c_notice$package$c_error.$c_reset"
        failure=1
      fi
    elif [[ -d ${path_build}../licenses ]] ; then
      cp -vR ${path_build}../licenses $package

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy directory $c_notice${path_build}../licenses$c_error to $c_notice$package$c_error.$c_reset"
        failure=1
      fi
    else
      echo -e "${c_error}ERROR: neither directory $c_notice${path_build}licenses$c_error nor $c_notice${path_build}../licenses$c_error can be found or are invalid.$c_reset"
      failure=1
    fi
  fi

  if [[ $failure == "" ]] ; then
    cp -vR ${path_build}scripts/generate.sh $package

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to copy script $c_notice${path_build}generate.sh$c_error to $c_notice$package$c_error.$c_reset"
      failure=1
    fi

    if [[ $failure == "" ]] ; then
      chmod ugo+x ${package}generate.sh

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to set executable permissions on script $c_notice${package}generate.sh$c_error.$c_reset"
        failure=1
      fi
    fi

    if [[ $failure == "" ]] ; then
      cp -vR ${path_build}scripts/install.sh $package

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy script $c_notice${path_build}install.sh$c_error to $c_notice$package$c_error.$c_reset"
        failure=1
      fi
    fi

    if [[ $failure == "" ]] ; then
      chmod ugo+x ${package}install.sh

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to set executable permissions on script $c_notice${package}install.sh$c_error.$c_reset"
        failure=1
      fi
    fi
  fi

  if [[ $failure != "" && ! -d ${package}build ]] ; then
    mkdir -vp ${package}build

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to create directory $c_notice${package}build$c_error.$c_reset"
      failure=1
    fi
  fi

  if [[ $failure != "" && ! -d ${package}sources ]] ; then
    mkdir -vp ${package}sources

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to create directory $c_notice${package}sources$c_error.$c_reset"
      failure=1
    fi
  fi

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_individual(){
  local failure=
  local name=
  local directory=
  local package=

  if [[ ! -d ${path_destination}individual ]] ; then
    mkdir -vp ${path_destination}individual

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to create directory $c_notice${path_destination}individual$c_error.$c_reset"
      package_cleanup
      exit $failure
    fi
  fi

  for directory in ${path_sources}level_0/* ${path_sources}level_1/* ${path_sources}level_2/* ; do
    name="$(echo $directory | sed -e "s|${path_sources}level_0/||" -e "s|${path_sources}level_1/||" -e "s|${path_sources}level_2/||")"
    package="${path_destination}individual/${name}-${version}/"

    echo
    echo -e "${c_highlight}Processing Package$c_reset (individual) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"

    package_create_base_files

    cp -vR $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to copy sources directory $c_notice$directory$c_error to $c_notice${package}sources$c_error.$c_reset"
      failure=1
      break
    fi

    if [[ -d ${package}sources/data/ ]] ; then
      mv -v ${package}sources/data/ ${package}

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to move sources data directory $c_notice${path_sources}sources/data$c_error to $c_notice$package$c_error.$c_reset"
        failure=1
        break
      fi
    fi
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_level(){
  local failure=
  local name=
  local level=
  local directory=

  for level in level_0 level_1 level_2 ; do
    name="fll-$level"
    package="${path_destination}level/${name}-${version}/"

    echo
    echo -e "${c_highlight}Processing Package$c_reset (level) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"

    if [[ ! -d $path_build$level ]] ; then
      echo -e "${c_error}ERROR: build settings directory $c_notice$path_build$level$c_error is invalid or missing.$c_reset"
      failure=1
      break
    fi

    package_create_base_files

    if [[ ! -d ${package}data/ ]] ; then
      mkdir -v ${package}data/

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to create directory $c_notice${package}data$c_error.$c_reset"
        failure=1
        break
      fi
    fi

    if [[ -d ${package}data/build ]] ; then
      cp -vR $path_build$level ${package}data
    else
      cp -vR $path_build$level ${package}data/build
    fi

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to move the directory $c_notice$path_build$level$c_error as $c_notice$path_build${level}build$c_error.$c_reset"
      failure=1
      break
    fi

    if [[ ! -d ${package}sources/ ]] ; then
      mkdir -v ${package}sources/

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to create directory $c_notice${package}sources$c_error.$c_reset"
        failure=1
        break
      fi
    fi

    for directory in $path_sources${level}/* ; do
      cp -vR $directory/* ${package}sources/

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy files from sources directory $c_notice$directory$c_error to $c_notice${package}sources$c_error.$c_reset"
        failure=1
        break
      fi

      rm -vRf ${package}sources/data/build/

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to remove directory $c_notice${package}sources/data/build$c_error.$c_reset"
        failure=1
        break
      fi

      cp -vR ${package}sources/data $package

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to copy the data directory $c_notice${package}sources/data$c_error to $c_notice$package$c_error.$c_reset"
        failure=1
        break
      fi

      rm -vRf ${package}sources/data

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to remove directory $c_notice${package}sources/data$c_error.$c_reset"
        failure=1
        break
      fi
    done

    if [[ $falure != "" ]] ; then
      break;
    fi
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_monolithic(){
  local failure=
  local name=
  local directory=

  echo -e "${c_error}ERROR: monolithic build is not implemented.$c_reset"
  package_cleanup
  exit $failure

  # TODO

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_program(){
  local failure=
  local name=
  local directory=

  if [[ ! -d ${path_destination}program ]] ; then
    mkdir -vp ${path_destination}program

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to create directory $c_notice${path_destination}program$c_error.$c_reset"
      package_cleanup
      exit $failure
    fi
  fi

  for directory in ${path_sources}level_3/* ; do
    name="$(echo $directory | sed -e "s|${path_sources}level_3/||")"
    package="${path_destination}program/${name}-${version}/"

    echo
    echo -e "${c_highlight}Processing Package$c_reset (program) $c_notice${name}-${version}$c_reset${c_highlight}.$c_reset"

    package_create_base_files

    cp -vR $directory ${package}sources/

    if [[ $? -ne 0 ]] ; then
      echo -e "${c_error}ERROR: failed to copy sources directory $c_notice$directory$c_error to $c_notice${package}sources$c_error.$c_reset"
      failure=1
      break
    fi

    if [[ -d ${package}sources/data/ ]] ; then
      mv -v ${package}sources/data/ ${package}

      if [[ $? -ne 0 ]] ; then
        echo -e "${c_error}ERROR: failed to move sources data directory $c_notice${path_sources}sources/data$c_error to $c_notice$package$c_error.$c_reset"
        failure=1
        break
      fi
    fi
  done

  if [[ $failure != "" ]] ; then
    package_cleanup
    exit $failure
  fi
}

package_operation_clean(){
  local i=

  for i in ${path_destination}{individual,level,monolithic,program} ; do
    if [[ -d $i ]] ; then
      rm -vRf $i
    fi
  done
}

package_cleanup(){
  unset package_main
  unset package_handle_colors
  unset package_help
  unset package_build
  unset package_create_base_files
  unset package_operation_clean
  unset package_operation_individual
  unset package_operation_level
  unset package_operation_monolithic
  unset package_operation_program
  unset package_cleanup
}

package_main $*
package_cleanup

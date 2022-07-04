#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# The purpose of this script is to mass execute tests.
# This is intended to be run directly from the bare source tree.
# The tests can still be run as normal by directly running the appropriate fake command (such as "fake make -f testfile") inside the appropriate project.
# This calls other scripts and expects this to be run in the project root.
# The dependencies of this script are: bash, grep, and sed.

test_main() {
  local public_name="FLL Project Mass Test Script"
  local system_name=install
  local called_name=$(basename $0)
  local version=0.6.0

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

  local build_compiler=
  local build_project=no
  local path_scripts=$PWD/build/scripts/
  local path_scripts_package=${path_scripts}package.sh
  local path_test=$PWD/test/
  local path_test_package=${path_test}package/
  local path_test_project=${path_test}project/
  local path_test_work=${path_test}work/
  local path_test_package_individual=${path_test_package}individual/
  local path_test_package_monolithic=${path_test_package}monolithic/
  local path_test_package_program=${path_test_package}program/
  local test_system=

  local context=
  local failure=
  local operation=
  local operation_failure=
  local verbosity=normal
  local verbose=
  local verbose_common=

  local projects="f_type f_status f_memory f_type_array f_string f_utf f_account f_capability f_color f_console f_control_group f_conversion f_directory f_environment f_execute f_file f_fss f_iki f_limit f_path f_pipe f_print f_serialize f_signal f_socket f_status_string f_thread fl_control_group fl_conversion fl_directory fl_environment fl_execute fl_fss fl_iki fl_print fl_signal fl_string fl_utf fl_utf_file fll_control_group fll_error fll_execute fll_file fll_fss fll_fss_status_string fll_iki fll_path fll_print fll_program fll_status_string"
  local projects_no_tests="f_type"

  let failure=0

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
        elif [[ $p == "-c" || $p == "--compiler" ]] ; then
          grab_next=build_compiler
        elif [[ $p == "-p" || $p == "--project" ]] ; then
          build_project=yes
        elif [[ $p == "-s" || $p == "--path_scripts" ]] ; then
          grab_next=path_scripts
          path_scripts=
        elif [[ $p == "-t" || $p == "--path_test" ]] ; then
          grab_next=path_test
          path_test=
        elif [[ $test_system == "" ]] ; then
          test_system="$p"
        else
          operation="$operation "
          operation_failure=fail-too_many
        fi
      else
        if [[ $grab_next == "build_compiler" ]] ; then
          build_compiler=$p
        elif [[ $grab_next == "path_scripts" ]] ; then
          path_scripts=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_scripts_package=${path_scripts}package.sh
        elif [[ $grab_next == "path_test" ]] ; then
          path_test=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_test_package=${path_test}package/
          path_test_package_individual=${path_test_package}individual/
          path_test_package_monolithic=${path_test_package}monolithic/
          path_test_package_program=${path_test_package}program/
          path_test_project=${path_test}project/
          path_test_work=${path_test}work/
        fi

        grab_next=
      fi
    done

    p=
  fi

  test_handle_colors

  if [[ $do_help == "yes" ]] ; then
    test_help
    test_cleanup

    return 0
  fi

  if [[ $operation_failure == "fail-too_many" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Only a single build system is supported, received the following test systems $c_notice$test_system $operation$c_error was not recognized.$c_reset"
    fi

    let failure=1
  fi

  if [[ $test_system == "" ]] ; then
    test_system=normal
  fi

  if [[ $grab_next != "build_compiler" && $build_compiler == "" ]] ; then
    build_compiler=gcc
  fi

  if [[ $failure -eq 0 && $test_system != "normal" && $test_system != "github" && $test_system != "gitlab" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The test system must be one of ${c_notice}normal$c_error, ${c_notice}github$c_error, or  ${c_notice}gitlab$c_error.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 0 && $test_system == "gitlab" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build system $c_notice$test_system$c_error is not currently implemented.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 0 && $build_compiler != "gcc" && $build_compiler != "clang" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build compiler $c_notice$build_compiler$c_error is not currently directly supported.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 0 && ! -d $path_scripts ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build scripts path $c_notice$path_scripts$c_error is not a valid directory.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 0 && ! -f $path_scripts_package ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Unable to find the package build script file under the build scripts path at $c_notice$path_scripts_package$c_error.$c_reset"
    fi

    let failure=1
  fi

  if [[ $failure -eq 0 && ! -d $path_test ]] ; then
    mkdir $verbose_common -p $path_test

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The test path $c_notice$path_test$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      let failure=1
    fi
  fi

  if [[ $failure -eq 0 && ! -d $path_test_package ]] ; then
    mkdir $verbose_common $path_test_package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The package path $c_notice$path_test_package$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      let failure=1
    fi
  fi

  if [[ $failure -eq 0 && ! -d $path_test_project ]] ; then
    mkdir $verbose_common $path_test_project

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The test project path $c_notice$path_test_project$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      let failure=1
    fi
  fi

  if [[ $failure -eq 0 && ! -d $path_test_work ]] ; then
    mkdir $verbose_common $path_test_work

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The test work path $c_notice$path_test_work$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      let failure=1
    fi
  fi

  if [[ $failure -eq 0 ]] ; then
    test_operate
    let failure=$?
  fi

  if [[ $verbosity != "quiet" ]] ; then
    echo
  fi

  test_cleanup

  return $failure
}

test_handle_colors() {

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

test_help() {

  echo
  echo -e "${c_title}$public_name$c_reset"
  echo -e " ${c_notice}Version $version$c_reset"
  echo
  echo -e "$c_highlight$system_name$c_reset $c_notice[${c_reset} options $c_notice]$c_reset $c_notice[${c_reset} test_system $c_notice]$c_reset"
  echo -e " ${c_important}normal${c_reset}  Perform a normal test (default)."
  echo -e " ${c_important}github${c_reset}  Perform a test meant to be used within Github."
  echo -e " ${c_important}gitlab${c_reset}  Perform a test meant to be used within Gitlab (not yet supported)."
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
  echo -e "${c_highlight}Install Options:$c_reset"
  echo -e " -${c_important}c$c_reset, --${c_important}compiler${c_reset}      Specify the compiler, either gcc (default) or clang."
  echo -e " -${c_important}p$c_reset, --${c_important}project${c_reset}       Designate that the project files must also be built."
  echo -e " -${c_important}s$c_reset, --${c_important}path_scripts${c_reset}  Specify a custom directory where the build scripts are found."
  echo -e " -${c_important}t$c_reset, --${c_important}path_test${c_reset}     Specify a custom directory where the test environment is found."
  echo
}

test_operate() {
  local env_path="${path_test_project}programs/shared"
  local env_libs="${path_test_project}libraries/shared"
  local work_path="${path_test_project}"
  local includes_path="${work_path}includes/"
  local libraries_path="${work_path}libraries/shared/"
  local github_arguments=

  if [[ $PATH != "" ]] ; then
    env_path="$env_path:$PATH"
  fi

  if [[ $LD_LIBRARY_PATH != "" ]] ; then
    env_libs="$env_libs:$LD_LIBRARY_PATH"
  fi

  if [[ $test_system == "github" ]] ; then
    github_arguments="-d -I$includes_path -d -L$libraries_path"

    test_operate_github_prebuild

    if [[ $? -ne 0 ]] ; then
      return 1
    fi
  fi

  if [[ $build_project == "yes" ]] ; then
    test_operate_build_tools

    if [[ $? -ne 0 ]] ; then
      return 1
    fi
  fi

  test_operate_build_individual

  if [[ $? -ne 0 ]] ; then
    return 1
  fi

  if [[ $test_system == "github" ]] ; then
    test_operate_github_pretest

    if [[ $? -ne 0 ]] ; then
      return 1
    fi
  fi

  test_operate_tests

  return $?
}

test_operate_build_individual() {
  local -i failure=0
  local project=
  local path_original="$PWD/"

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Cleaning and building package.$c_reset"
    echo -e "${c_title}------------------------------$c_reset"
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "bash ${path_scripts_package} $verbose $context -d $path_test_package -i clean &&"
    echo "bash ${path_scripts_package} $verbose $context -d $path_test_package -i build"
  fi

  bash ${path_scripts_package} $verbose $context -d $path_test_package -i clean &&
  bash ${path_scripts_package} $verbose $context -d $path_test_package -i build

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to clean and build the individual packages.$c_reset"
    fi

    return 1
  fi

  for project in $projects ; do

    test_operate_build_project "$path_test_package_individual" "$path_test_work" "$project" individual

    if [[ $? -ne 0 ]] ; then
      let failure=1

      cd $path_original

      break;
    fi

    cd $path_original
  done

  return $failure
}

test_operate_build_project() {
  local path="$1"
  local destination="$2"
  local project="$3"
  local mode="$4"
  local bootstrap="$5"

  if [[ ! -d ${path}$project-$version/ ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Package directory '${c_notice}${path}$project-$version$c_error' is invalid or missing.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo -e "Running '${c_notice}cd ${path}$project-$version/$c_reset'."
  fi

  cd ${path}$project-$version/

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to change into directory '${c_notice}${path}$project-$version$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $bootstrap == "" ]] ; then
    if [[ $verbosity == "debug" ]] ; then
      echo

      if [[ $build_compiler == "gcc" ]] ; then
        echo "PATH=\"$env_path\" LD_LIBRARY_PATH=\"$env_libs\" fake $verbose $context -w \"$destination\" -m $mode clean build $github_arguments"
      else
        echo "PATH=\"$env_path\" LD_LIBRARY_PATH=\"$env_libs\" fake $verbose $context -w \"$destination\" -m individual -m $build_compiler clean make -f testfile $github_arguments"
      fi
    fi

    if [[ $build_compiler == "gcc" ]] ; then
      PATH="$env_path" LD_LIBRARY_PATH="$env_libs" fake $verbose $context -w "$destination" -m $mode -m test clean build $github_arguments
    else
      PATH="$env_path" LD_LIBRARY_PATH="$env_libs" fake $verbose $context -w "$destination" -m $mode -m test -m $build_compiler clean build $github_arguments
    fi
  else
    if [[ $verbosity == "debug" ]] ; then
      echo

      if [[ $build_compiler == "gcc" ]] ; then
        echo "./bootstrap.sh $verbose $context -w \"$destination\" -m $mode -m test build"
      else
        echo "./bootstrap.sh $verbose $context -w \"$destination\" -m $mode -m test -m $build_compiler build"
      fi
    fi

    if [[ $build_compiler == "gcc" ]] ; then
      ./bootstrap.sh $verbose $context -w "$destination" -m $mode -m test build
    else
      ./bootstrap.sh $verbose $context -w "$destination" -m $mode -m test -m $build_compiler build
    fi
  fi

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to build $mode project '$c_notice$project$c_reset$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "Installing $mode project '$c_notice$project$c_reset'."
  fi

  ./install.sh $verbose $context -w "$destination"

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to install $mode project '$c_notice$project$c_reset$c_error'.$c_reset"
    fi

    return 1
  fi

  return 0
}

test_operate_build_tools() {
  local -i failure=0
  local path_original="$PWD/"

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Building project build tools.$c_reset"
    echo -e "${c_title}-----------------------------$c_reset"
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "bash ${path_scripts_package} $verbose $context -d $path_test_package -m clean &&"
    echo "bash ${path_scripts_package} $verbose $context -d $path_test_package -m build"
  fi

  bash ${path_scripts_package} $verbose $context -d $path_test_package -m clean &&
  bash ${path_scripts_package} $verbose $context -d $path_test_package -m build

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to clean and build the monolithic packages.$c_reset"
    fi

    return 1
  fi

  test_operate_build_project "$path_test_package_monolithic" "$path_test_project" fll monolithic bootstrap

  if [[ $? -ne 0 ]] ; then
    let failure=1
  fi

  cd $path_original

  if [[ $failure -eq 0 ]] ; then
    if [[ $verbosity == "debug" ]] ; then
      echo
      echo "bash ${path_scripts_package} $verbose $context -d $path_test_package -p clean &&"
      echo "bash ${path_scripts_package} $verbose $context -d $path_test_package -p build"
    fi

    bash ${path_scripts_package} $verbose $context -d $path_test_package -p clean &&
    bash ${path_scripts_package} $verbose $context -d $path_test_package -p build

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo -e "${c_error}ERROR: Failed to clean and build the program packages.$c_reset"
      fi

      return 1
    fi

    test_operate_build_project "$path_test_package_program" "$path_test_project" fake monolithic bootstrap

    if [[ $? -ne 0 ]] ; then
      let failure=1
    fi
  fi

  cd $path_original

  return $failure
}

test_operate_github_prebuild() {
  local clone_quiet=
  local path_original="$PWD/"
  local result=

  if [[ $verbosity == "quiet" ]] ; then
    clone_quiet="-q"
  fi

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Performing Github Specific Pre-Build Operations.$c_reset"
    echo -e "${c_title}------------------------------------------------$c_reset"
  fi

  test_operate_github_prebuild_libcap
  result=$?

  cd ${path_original}

  return $result
}

test_operate_github_pretest() {
  local clone_quiet=
  local path_original="$PWD/"
  local result=

  if [[ $verbosity == "quiet" ]] ; then
    clone_quiet="-q"
  fi

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_highlight}Performing Github Specific Pre-Test Operations.$c_reset"
    echo -e "${c_title}-----------------------------------------------$c_reset"
  fi

  test_operate_github_pretest_cmocka
  result=$?

  cd ${path_original}

  return $result
}

test_operate_github_pretest_cmocka() {
  local cmocka_path="${path_test}cmocka/"
  local cmocka_build="${cmocka_path}build/"
  local cmocka_data="${cmocka_path}data/build/"
  local cmocka_settings="${path_original}level_3/fake/data/projects/cmocka/1.1.5/settings"
  local cmocka_uri="https://github.com/coreboot/cmocka.git"
  local cmocka_branch="cmocka-1.1.5"

  if [[ -d $cmocka_path ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "Detected existing cmocka repository at \"$c_notice$cmocka_path$c_reset\", skipping the cmocka process."
    fi

    return 0
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "git clone $clone_quiet --single-branch -b $cmocka_branch \"$cmocka_uri\" $cmocka_path"
  fi

  git clone $clone_quiet --single-branch -b $cmocka_branch "$cmocka_uri" $cmocka_path

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to git clone '${c_notice}$cmocka_uri$c_error' onto  '${c_notice}$cmocka_path$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "mkdir $verbose_common -p $cmocka_data"
  fi

  mkdir $verbose_common -p $cmocka_data

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to create cmocka build data directory '$c_notice$cmocka_data$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "cp $verbose_common $cmocka_settings $cmocka_data"
  fi

  cp $verbose_common $cmocka_settings $cmocka_data

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to copy cmocka build settings: '$c_notice$cmocka_settings$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "cd $cmocka_path"
  fi

  cd $cmocka_path

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to change cmocka source directory '$c_notice$cmocka_path$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "PATH=\"$env_path\" LD_LIBRARY_PATH=\"$env_libs\" fake $verbose $context -w \"$path_test_work\" -m $build_compiler clean build $github_arguments"
  fi

  PATH="$env_path" LD_LIBRARY_PATH="$env_libs" fake $verbose $context -w "$path_test_work" -m $build_compiler clean build $github_arguments

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to build '${c_notice}cmocka$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "cp $verbose_common -R ${cmocka_build}includes/* ${work_path}includes/"
  fi

  cp $verbose_common -R ${cmocka_build}includes/* ${work_path}includes/

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to install cmocka headers to '$c_notice${work_path}includes/$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "cp $verbose_common -R ${cmocka_build}libraries/shared/* ${work_path}libraries/shared/"
  fi

  cp $verbose_common -R ${cmocka_build}libraries/shared/* ${work_path}libraries/shared/

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to install cmocka libraries to '$c_notice${work_path}libraries/shared/$c_error'.$c_reset"
    fi

    return 1
  fi

  return 0
}

test_operate_github_prebuild_libcap() {
  local libcap_path="${path_test}libcap/"
  local libcap_uri="https://github.com/thekevinday/kernel.org-libcap.git"
  local libcap_branch="master"

  if [[ -d $libcap_path ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "Detected existing libcap repository at \"$c_notice$libcap_path$c_reset\", skipping the libcap process."
    fi

    return 0
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "git clone $clone_quiet --single-branch -b $libcap_branch \"$libcap_uri\" $libcap_path"
  fi

  git clone $clone_quiet --single-branch -b $libcap_branch "$libcap_uri" $libcap_path

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to git clone '${c_notice}$libcap_uri$c_error' onto  '${c_notice}$libcap_path$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "cd $libcap_path"
  fi

  cd $libcap_path

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to change libcap source directory '$c_notice$libcap_path$c_error'.$c_reset"
    fi

    return 1
  fi

  if [[ $verbosity == "debug" ]] ; then
    echo
    echo "make MANDIR=${work_path}fake/ SBINDIR=${work_path}fake/ INCDIR=${work_path}includes/ LIBDIR=${work_path}libraries/shared/ PKGCONFIGDIR=${work_path}fake/ install"
  fi

  make MANDIR=${work_path}fake/ SBINDIR=${work_path}fake/ INCDIR=${work_path}includes/ LIBDIR=${work_path}libraries/shared/ PKGCONFIGDIR=${work_path}fake/ install

  if [[ $? -ne 0 ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_error}ERROR: Failed to build and install libcap into the work directory '$c_notice${work_path}$c_error'.$c_reset"
    fi

    return 1
  fi

  return 0
}

test_operate_tests() {
  local -i failure=0
  local project=
  local path_original="$PWD/"
  local destination="$path_test_work"

  for project in $projects ; do

    if [[ $verbosity != "quiet" ]] ; then
      echo
      echo -e "${c_highlight}Testing Project $project.$c_reset"
      echo -e "${c_title}--------------------------------------$c_reset"
    fi

    if [[ ! -d $path_test_package_individual$project-$version/ ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo
        echo -e "${c_error}ERROR: Package directory '$c_notice$path_test_package_individual$project-$version$c_error' is invalid or missing.$c_reset"
      fi

      let failure=1
    fi

    if [[ $failure -eq 0 ]] ; then
      if [[ ! -f $path_test_package_individual$project-$version/data/build/testfile ]] ; then
        if [[ $(echo $projects_no_tests | grep -o "\<$project\>") == "" ]] ; then
          if [[ $verbosity == "verbose" || $verbosity == "debug" ]] ; then
            echo
            echo -e "${c_warning}WARNING: Project '$c_notice$project$c_warning' does not have a testfile.$c_reset"
          fi
        else
          echo
          echo -e "Project '$c_notice$project$c_reset' has no tests and is not expected to.$c_reset"
        fi

        continue
      fi
    fi

    if [[ $failure -eq 0 ]] ; then
      if [[ $verbosity == "debug" ]] ; then
        echo
        echo -e "Running '${c_notice}cd $path_test_package_individual$project-$version/$c_reset'."
      fi

      cd $path_test_package_individual$project-$version/

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo
          echo -e "${c_error}ERROR: Failed to change into directory '$c_notice$path_test_package_individual$project-$version$c_error'.$c_reset"
        fi

        let failure=1
      fi
    fi

    if [[ $failure -eq 0 ]] ; then
      if [[ $verbosity == "debug" ]] ; then
        echo

        if [[ $build_compiler == "gcc" ]] ; then
          echo "PATH=\"$env_path\" LD_LIBRARY_PATH=\"$env_libs\" fake $verbose $context -w \"$destination\" -m individual -m test clean make -f testfile $github_arguments"
        else
          echo "PATH=\"$env_path\" LD_LIBRARY_PATH=\"$env_libs\" fake $verbose $context -w \"$destination\" -m individual -m test -m $build_compiler clean make -f testfile $github_arguments"
        fi
      fi

      if [[ $build_compiler == "gcc" ]] ; then
        PATH="$env_path" LD_LIBRARY_PATH="$env_libs" fake $verbose $context -w "$destination" -m individual -m test clean make -f testfile $github_arguments
      else
        PATH="$env_path" LD_LIBRARY_PATH="$env_libs" fake $verbose $context -w "$destination" -m individual -m test -m $build_compiler clean make -f testfile $github_arguments
      fi

      if [[ $? -ne 0 ]] ; then
        if [[ $verbosity != "quiet" ]] ; then
          echo
          echo -e "${c_error}ERROR: Failure while testing project '$c_notice$project$c_reset$c_error'.$c_reset"
        fi

        let failure=1
      fi
    fi

    cd $path_original

    if [[ $failure -ne 0 ]] ; then
      break;
    fi
  done

  return $failure
}

test_cleanup() {

  unset test_main
  unset test_handle_colors
  unset test_help

  unset test_cleanup
  unset test_operate
  unset test_operate_build_individual
  unset test_operate_build_project
  unset test_operate_build_tools
  unset test_operate_github_prebuild
  unset test_operate_github_prebuild_libcap
  unset test_operate_github_pretest
  unset test_operate_github_pretest_cmocka
  unset test_operate_tests
}

test_main $*

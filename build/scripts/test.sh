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
  local version=0.5.9

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

  local build_project=no
  local path_scripts=build/scripts/
  local path_scripts_bootstrap=${path_scripts}bootstrap-example.sh
  local path_scripts_package=${path_scripts}package.sh
  local path_test=test/
  local path_test_project=${path_test}project/
  local path_test_work=${path_test}work/
  local path_package=package/
  local path_package_individual=${path_package}individual/
  local path_package_monolithic=${path_package}monolithic/
  local path_package_program=${path_package}program/
  local test_system=

  local context=
  local failure=
  local operation=
  local operation_failure=
  local verbosity=normal
  local verbose=
  local verbose_common=

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
        elif [[ $p == "-P" || $p == "--project" ]] ; then
          build_project=yes
        elif [[ $p == "-p" || $p == "--path_package" ]] ; then
          grab_next=path_package
        elif [[ $p == "-s" || $p == "--path_scripts" ]] ; then
          grab_next=path_scripts
        elif [[ $p == "-t" || $p == "--path_test" ]] ; then
          grab_next=path_test
        elif [[ $test_system == "" ]] ; then
          test_system="$p"
        else
          operation="$operation "
          operation_failure=fail-too_many
        fi
      else
        if [[ $grab_next == "path_package" ]] ; then
          path_package=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_package_individual=${path_package}individual/
          path_package_monolithic=${path_package}monolithic/
          path_package_program=${path_package}program/
        elif [[ $grab_next == "path_scripts" ]] ; then
          path_scripts=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_scripts_bootstrap=${path_scripts}bootstrap-example.sh
          path_scripts_package=${path_scripts}package.sh
        elif [[ $grab_next == "path_test" ]] ; then
          path_test=$(echo $p | sed -e 's|^//*|/|' -e 's|/*$|/|')
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

    test_cleanup

    return 1
  fi

  if [[ $test_system == "" ]] ; then
    test_system=normal
  fi

  if [[ $test_system != "normal" && $test_system != "github" && $test_system != "gitlab" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The test system must be one of ${c_notice}normal$c_error, ${c_notice}github$c_error, or  ${c_notice}gitlab$c_error.$c_reset"
    fi

    test_cleanup

    return 1
  fi

  if [[ $test_system == "github" || $test_system == "gitlab" ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build system $c_notice$test_system$c_error is not currently implemented.$c_reset"
    fi

    test_cleanup

    return 1
  fi

  if [[ ! -d $path_scripts ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: The build scripts path $c_notice$path_scripts$c_error is not a valid directory.$c_reset"
    fi

    test_cleanup

    return 1
  fi

  if [[ ! -f $path_scripts_bootstrap ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Unable to find the example bootstrap script file under the build scripts path at $c_notice$path_scripts$c_error.$c_reset"
    fi

    test_cleanup

    return 1
  fi

  if [[ ! -f $path_scripts_package ]] ; then
    if [[ $verbosity != "quiet" ]] ; then
      echo -e "${c_error}ERROR: Unable to find the package build script file under the build scripts path at $c_notice$path_scripts_package$c_error.$c_reset"
    fi

    test_cleanup

    return 1
  fi

  if [[ ! -d $path_package ]] ; then
    mkdir $verbose_common $path_package

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The package path $c_notice$path_package$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      test_cleanup

      return 1
    fi
  fi

  if [[ ! -d $path_test ]] ; then
    mkdir $verbose_common $path_test

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The test path $c_notice$path_test$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      test_cleanup

      return 1
    fi
  fi

  if [[ ! -d $path_test_work ]] ; then
    mkdir $verbose_common $path_test_work

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The test work path $c_notice$path_test_work$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      test_cleanup

      return 1
    fi
  fi

  if [[ ! -d $path_test_project ]] ; then
    mkdir $verbose_common $path_test_project

    if [[ $? -ne 0 ]] ; then
      if [[ $verbosity != "quiet" ]] ; then
        echo -e "${c_error}ERROR: The test project path $c_notice$path_test_project$c_error, does not exist and could not be created or exists and is not a valid directory.$c_reset"
      fi

      test_cleanup

      return 1
    fi
  fi

  test_operate
  let failure=$?

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
  echo -e " ${c_important}github${c_reset}  Perform a test meant to be used within Github (not yet supported)."
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
  echo -e " -${c_important}P$c_reset, --${c_important}project${c_reset}       Designate that the project files must also be built."
  echo -e " -${c_important}s$c_reset, --${c_important}path_scripts${c_reset}  Specify a custom directory where the build scripts are found."
  echo -e " -${c_important}t$c_reset, --${c_important}path_test${c_reset}     Specify a custom directory where the test dependencies are found."
  echo -e " -${c_important}p$c_reset, --${c_important}path_package${c_reset}  Specify a custom directory where the package is extracted."
  echo
}

test_operate() {
  # TODO: print messages as needed.

  bash $path_scripts_bootstrap monolithic -w $path_test_work $verbose $context

  if [[ $? -ne 0 ]] ; then
    return 1
  fi

  # TODO: everything else.

  return 0
}

test_cleanup() {
  unset test_main
  unset test_handle_colors
  unset test_help

  unset test_cleanup
  unset test_operate
}

test_main $*

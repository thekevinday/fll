#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# The purpose of this script is to mass execute tests.
# This is intended to be run directly from the bare source tree.
# The tests can still be run as normal by directly running the appropriate fake command (such as "fake make -f testfile") inside the appropriate project.
# This calls other scripts and expects this to be run in the project root.
#
# The dependencies of this script are: bash, grep, and sed.
#
# This script can also be run under zsh rather than bash by setting the environment variable SHELL_ENGINE to "zsh", such as:
#   SHELL_ENGINE="zsh" zsh ./test.sh --help
#

test_main() {
  local shell_command=bash

  if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
    shell_command=zsh

    emulate ksh
  fi

  local public_name="FLL Project Mass Test Script"
  local system_name=install
  local called_name=$(basename ${0})
  local version=0.6.6

  local grab_next=
  local do_color=dark
  local do_help=
  local do_copyright=
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
  local build_project_thread="thread"
  local path_scripts=${PWD}/build/scripts/
  local path_scripts_package=${path_scripts}package.sh
  local path_test=${PWD}/test/
  local path_test_package=${path_test}package/
  local path_test_project=${path_test}project/
  local path_test_work=${path_test}work/
  local path_test_package_individual=${path_test_package}individual/
  local path_test_package_stand_alone=${path_test_package}stand_alone/
  local print_line_first="yes"
  local print_line_last="yes"
  local test_system=
  local test_thread="thread"
  local test_thread_individual="thread_individual"

  local context=
  local failure=0
  local operation=
  local operation_failure=
  local verbosity=normal
  local verbose=
  local verbose_common=

  local projects="f_type f_status f_memory f_type_array f_string f_utf f_account f_capability f_color f_console f_control_group f_conversion f_directory f_environment f_execute f_file f_fss f_iki f_limit f_path f_pipe f_print f_serialize f_signal f_socket f_status_string f_thread fl_control_group fl_conversion fl_directory fl_environment fl_execute fl_fss fl_iki fl_print fl_signal fl_string fl_utf fl_utf_file fll_control_group fll_error fll_execute fll_file fll_fss fll_fss_status_string fll_iki fll_path fll_print fll_program fll_status_string"
  local projects_no_tests="f_type"

  if [[ $# -gt 0 ]] ; then
    t=$#

    while [[ ${i} -lt ${t} ]] ; do

      let i=${i}+1

      if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
        p=${(P)i}
      else
        p=${!i}
      fi

      if [[ ${grab_next} == "" ]] ; then
        if [[ ${p} == "-h" || ${p} == "--help" ]] ; then
          do_help=yes
        elif [[ ${p} == "+C" || ${p} == "++copyright" ]] ; then
          do_copyright="yes"
        elif [[ ${p} == "+d" || ${p} == "++dark" ]] ; then
          do_color=dark
          context="+d"
        elif [[ ${p} == "+l" || ${p} == "++light" ]] ; then
          do_color=light
          context="+l"
        elif [[ ${p} == "+n" || ${p} == "++no_color" ]] ; then
          do_color=none
          context="+n"
        elif [[ ${p} == "+Q" || ${p} == "++quiet" ]] ; then
          verbosity="quiet"
          verbose="+Q"
          verbose_common=
        elif [[ ${p} == "+E" || ${p} == "++error" ]] ; then
          verbosity="error"
          verbose="+E"
          verbose_common=
        elif [[ ${p} == "+N" || ${p} == "++normal" ]] ; then
          verbosity=
          verbose="+N"
          verbose_common=
        elif [[ ${p} == "+V" || ${p} == "++verbose" ]] ; then
          verbosity="verbose"
          verbose="+V"
          verbose_common="-v"
        elif [[ ${p} == "+D" || ${p} == "++debug" ]] ; then
          verbosity="debug"
          verbose="+D"
          verbose_common="-v"
        elif [[ ${p} == "+v" || ${p} == "++version" ]] ; then
          echo ${version}
          return 0
        elif [[ ${p} == "-c" || ${p} == "--compiler" ]] ; then
          grab_next=build_compiler
        elif [[ ${p} == "-p" || ${p} == "--project" ]] ; then
          build_project=yes
        elif [[ ${p} == "-s" || ${p} == "--path_scripts" ]] ; then
          grab_next=path_scripts
          path_scripts=
        elif [[ ${p} == "-t" || ${p} == "--path_test" ]] ; then
          grab_next=path_test
          path_test=
        elif [[ ${p} == "-T" || ${p} == "--thread" ]] ; then
          test_thread="thread"
          test_thread_individual="thread_individual"
        elif [[ ${p} == "-L" || ${p} == "--threadless" ]] ; then
          test_thread="threadless"
          test_thread_individual=""
        elif [[ ${test_system} == "" ]] ; then
          test_system="${p}"
        else
          operation="${operation} "
          operation_failure=fail-too_many
        fi
      else
        if [[ ${grab_next} == "build_compiler" ]] ; then
          build_compiler=${p}
        elif [[ ${grab_next} == "path_scripts" ]] ; then
          path_scripts=$(echo ${p} | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_scripts_package=${path_scripts}package.sh
        elif [[ ${grab_next} == "path_test" ]] ; then
          path_test=$(echo ${p} | sed -e 's|^//*|/|' -e 's|/*$|/|')
          path_test_package=${path_test}package/
          path_test_package_individual=${path_test_package}individual/
          path_test_package_stand_alone=${path_test_package}stand_alone/
          path_test_project=${path_test}project/
          path_test_work=${path_test}work/
        fi

        grab_next=
      fi
    done

    p=
  fi

  if [[ ${verbosity} == "quiet" ]] ; then
    print_line_first="no"
    print_line_last="no"
  fi

  test_handle_colors

  if [[ ${do_help} == "yes" ]] ; then
    test_help
    test_cleanup

    return 0
  fi

  if [[ ${do_copyright} == "yes" ]] ; then
    test_copyright
    test_cleanup

    return 0
  fi

  if [[ ${operation_failure} == "fail-too_many" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Only a single build system is supported, received the following test systems ${c_notice}${test_system} ${operation}${c_error} was not recognized.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${test_system} == "" ]] ; then
    test_system=normal
  fi

  if [[ ${grab_next} != "build_compiler" && ${build_compiler} == "" ]] ; then
    build_compiler=gcc
  fi

  if [[ ${failure} -eq 0 && ${test_system} != "normal" && ${test_system} != "github" && ${test_system} != "gitlab" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: The test system must be one of ${c_notice}normal${c_error}, ${c_notice}github${c_error}, or  ${c_notice}gitlab${c_error}.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 0 && ${build_compiler} != "gcc" && ${build_compiler} != "clang" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: The build compiler ${c_notice}${build_compiler}${c_error} is not currently directly supported.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 0 && ! -d ${path_scripts} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: The build scripts path ${c_notice}${path_scripts}${c_error} is not a valid directory.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 0 && ! -f ${path_scripts_package} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Unable to find the package build script file under the build scripts path at ${c_notice}${path_scripts_package}${c_error}.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 0 && ! -d ${path_test} ]] ; then
    mkdir ${verbose_common} -p ${path_test}

    if [[ ${?} -ne 0 ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        test_print_first

        echo -e "${c_error}ERROR: The test path ${c_notice}${path_test}${c_error}, does not exist and could not be created or exists and is not a valid directory.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ ${failure} -eq 0 && ! -d ${path_test_package} ]] ; then
    mkdir ${verbose_common} ${path_test_package}

    if [[ ${?} -ne 0 ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        test_print_first

        echo -e "${c_error}ERROR: The package path ${c_notice}${path_test_package}${c_error}, does not exist and could not be created or exists and is not a valid directory.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ ${failure} -eq 0 && ! -d ${path_test_project} ]] ; then
    mkdir ${verbose_common} ${path_test_project}

    if [[ ${?} -ne 0 ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        test_print_first

        echo -e "${c_error}ERROR: The test project path ${c_notice}${path_test_project}${c_error}, does not exist and could not be created or exists and is not a valid directory.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ ${failure} -eq 0 && ! -d ${path_test_work} ]] ; then
    mkdir ${verbose_common} ${path_test_work}

    if [[ ${?} -ne 0 ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        test_print_first

        echo -e "${c_error}ERROR: The test work path ${c_notice}${path_test_work}${c_error}, does not exist and could not be created or exists and is not a valid directory.${c_reset}"
      fi

      let failure=1
    fi
  fi

  if [[ ${failure} -eq 0 ]] ; then
    test_operate
    let failure=$?
  fi

  if [[ ${verbosity} != "quiet" ]] ; then
    if [[ ${failure} -eq 1 || ${verbosity} != "error" ]] ; then
      test_print_last
    fi
  fi

  test_cleanup

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

test_handle_colors() {

  if [[ ${do_color} == "light" ]] ; then
    c_error="\\033[1;31m"
    c_warning="\\033[0;31m"
    c_title="\\033[1;34m"
    c_highlight="\\033[0;34m"
    c_notice="\\033[0;01m"
    c_important="\\033[0;35m"
  elif [[ ${do_color} == "none" ]] ; then
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

  test_print_first

  echo -e "${c_title}${public_name}${c_reset}"
  echo -e " ${c_notice}Version ${version}${c_reset}"
  echo
  echo -e "${c_highlight}${system_name}${c_reset} ${c_notice}[${c_reset} options ${c_notice}]${c_reset} ${c_notice}[${c_reset} test_system ${c_notice}]${c_reset}"
  echo -e " ${c_important}normal${c_reset}  Perform a normal test (default)."
  echo -e " ${c_important}github${c_reset}  Perform a test meant to be used within Github."
  echo -e " ${c_important}gitlab${c_reset}  Perform a test meant to be used within Gitlab (not yet supported)."
  echo
  echo -e "${c_highlight}Available Options:${c_reset}"
  echo -e " -${c_important}h${c_reset}, --${c_important}help${c_reset}       Print this help message."
  echo -e " +${c_important}C${c_reset}, ++${c_important}copyright${c_reset}  Print the copyright."
  echo -e " +${c_important}d${c_reset}, ++${c_important}dark${c_reset}       Output using colors that show up better on dark backgrounds."
  echo -e " +${c_important}l${c_reset}, ++${c_important}light${c_reset}      Output using colors that show up better on light backgrounds."
  echo -e " +${c_important}n${c_reset}, ++${c_important}no_color${c_reset}   Do not print using color."
  echo -e " +${c_important}Q${c_reset}, ++${c_important}quiet${c_reset}      Decrease verbosity, silencing most print.to."
  echo -e " +${c_important}E${c_reset}, ++${c_important}error${c_reset}      Decrease verbosity, using only error print.to."
  echo -e " +${c_important}N${c_reset}, ++${c_important}normal${c_reset}     Set verbosity to normal."
  echo -e " +${c_important}V${c_reset}, ++${c_important}verbose${c_reset}    Increase verbosity beyond normal print.to."
  echo -e " +${c_important}D${c_reset}, ++${c_important}debug${c_reset}      Enable debugging, significantly increasing verbosity beyond normal print.to."
  echo -e " +${c_important}v${c_reset}, ++${c_important}version${c_reset}    Print only the version number."
  echo
  echo -e " -${c_important}c${c_reset}, --${c_important}compiler${c_reset}      Specify the compiler, either gcc (default) or clang."
  echo -e " -${c_important}p${c_reset}, --${c_important}project${c_reset}       Designate that the project files must also be built."
  echo -e " -${c_important}s${c_reset}, --${c_important}path_scripts${c_reset}  Specify a custom directory where the build scripts are found."
  echo -e " -${c_important}t${c_reset}, --${c_important}path_test${c_reset}     Specify a custom directory where the test environment is found."
  echo -e " -${c_important}T${c_reset}, --${c_important}thread${c_reset}        Compile code being tested with threads enabled."
  echo -e " -${c_important}L${c_reset}, --${c_important}threadless${c_reset}    Compile code being tested with threads disabled."

  test_print_last
}

test_copyright() {

  test_print_first

  echo "Copyright © 2007-2023 Kevin Day."
  echo
  echo "Source code license lgpl-2.1-or-later."
  echo "Standard and specification license open-standard-license-1.0."
  echo "Documentation license cc-by-sa-4.0."

  test_print_last
}

test_operate() {
  local env_path="${path_test_project}programs/shared"
  local env_libs="${path_test_project}libraries/shared"
  local work_path="${path_test_project}"
  local includes_path="${work_path}includes/"
  local libraries_path="${work_path}libraries/shared/"
  local ci_arguments=

  if [[ ${PATH} != "" ]] ; then
    env_path="${env_path}:${PATH}"
  fi

  if [[ ${LD_LIBRARY_PATH} != "" ]] ; then
    env_libs="${env_libs}:${LD_LIBRARY_PATH}"
  fi

  if [[ ${test_system} == "github" || ${test_system} == "gitlab" ]] ; then
    ci_arguments="-d -I${includes_path} -d -L${libraries_path}"

    test_operate_ci_prebuild

    if [[ ${?} -ne 0 ]] ; then
      let failure=1

      return 1
    fi
  fi

  if [[ ${build_project} == "yes" ]] ; then
    test_operate_build_tools

    if [[ ${?} -ne 0 ]] ; then
      let failure=1

      return 1
    fi
  fi

  test_operate_build_individual

  if [[ ${?} -ne 0 ]] ; then
    let failure=1

    return 1
  fi

  if [[ ${test_system} == "github" || ${test_system} == "gitlab" ]] ; then
    test_operate_ci_pretest

    if [[ ${?} -ne 0 ]] ; then
      let failure=1

      return 1
    fi
  fi

  test_operate_tests

  return $?
}

test_operate_build_individual() {
  local project=
  local path_original="${PWD}/"

  if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
    test_print_first_or_always

    echo -e "${c_highlight}Cleaning and building package.${c_reset}"
    echo -e "${c_title}------------------------------${c_reset}"
    echo
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "${shell_command} ${path_scripts_package} ${verbose} ${context} -d ${path_test_package} -i rebuild"
  fi

  ${shell_command} ${path_scripts_package} ${verbose} ${context} -d ${path_test_package} -i rebuild

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to clean and build the individual packages.${c_reset}"
    fi

    return 1
  fi

  for project in ${projects} ; do

    test_operate_build_project "${path_test_package_individual}" "${path_test_work}" "${project}" individual ${test_thread} ${test_thread_individual}

    if [[ ${?} -ne 0 ]] ; then
      let failure=1

      cd ${path_original}

      break;
    fi

    cd ${path_original}
  done

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

test_operate_build_project() {
  local path_="${1}"
  local destination="${2}"
  local project="${3}"
  local mode="${4}"
  local bootstrap="${5}"
  local mode_thread_param=
  local mode_thread_value=
  local mode_thread_individual_param=
  local mode_thread_individual_value=

  if [[ ${6} != "" ]] ; then
    local mode_thread_param="-m"
    local mode_thread_value="${6}"
  fi

  if [[ ${7} != "" ]] ; then
    local mode_thread_individual_param="-m"
    local mode_thread_individual_value="${7}"
  fi

  if [[ ! -d ${path_}${project}-${version}/ ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Package directory '${c_notice}${path_}${project}-${version}${c_error}' is invalid or missing.${c_reset}"
    fi

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo -e "Running '${c_notice}cd ${path_}${project}-${version}/${c_reset}'."
  fi

  cd ${path_}${project}-${version}/

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to change into directory '${c_notice}${path_}${project}-${version}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${bootstrap} == "" ]] ; then
    if [[ ${verbosity} == "debug" ]] ; then
      test_print_first_or_always

      if [[ ${build_compiler} == "gcc" ]] ; then
        echo "PATH=\"${env_path}\" LD_LIBRARY_PATH=\"${env_libs}\" fake ${verbose} ${context} -w \"${destination}\" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} clean build ${ci_arguments}"
      else
        echo "PATH=\"${env_path}\" LD_LIBRARY_PATH=\"${env_libs}\" fake ${verbose} ${context} -w \"${destination}\" -m ${mode} ${mode_thread_param} ${mode_thread_value} -m ${build_compiler} ${mode_thread_individual_param} ${mode_thread_individual_value} clean make -f testfile ${ci_arguments}"
      fi
    fi

    if [[ ${build_compiler} == "gcc" ]] ; then
      PATH="${env_path}" LD_LIBRARY_PATH="${env_libs}" fake ${verbose} ${context} -w "${destination}" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test clean build ${ci_arguments}
    else
      PATH="${env_path}" LD_LIBRARY_PATH="${env_libs}" fake ${verbose} ${context} -w "${destination}" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test -m ${build_compiler} clean build ${ci_arguments}
    fi
  else
    if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
      if [[ ${verbosity} == "debug" ]] ; then
        test_print_first_or_always

        if [[ ${build_compiler} == "gcc" ]] ; then
          echo "zsh ./bootstrap.sh ${verbose} ${context} -w \"${destination}\" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test build"
        else
          echo "zsh ./bootstrap.sh ${verbose} ${context} -w \"${destination}\" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test -m ${build_compiler} build"
        fi
      fi

      if [[ ${build_compiler} == "gcc" ]] ; then
        zsh ./bootstrap.sh ${verbose} ${context} -w "${destination}" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test build
      else
        zsh ./bootstrap.sh ${verbose} ${context} -w "${destination}" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test -m ${build_compiler} build
      fi
    else
      if [[ ${verbosity} == "debug" ]] ; then
        test_print_first_or_always

        if [[ ${build_compiler} == "gcc" ]] ; then
          echo "./bootstrap.sh ${verbose} ${context} -w \"${destination}\" -m ${mode} ${mode_thread_individual_param} ${mode_thread_individual_value} ${mode_thread_param} ${mode_thread_value} -m test build"
        else
          echo "./bootstrap.sh ${verbose} ${context} -w \"${destination}\" -m ${mode} ${mode_thread_individual_param} ${mode_thread_individual_value} ${mode_thread_param} ${mode_thread_value} -m test -m ${build_compiler} build"
        fi
      fi

      if [[ ${build_compiler} == "gcc" ]] ; then
        ./bootstrap.sh ${verbose} ${context} -w "${destination}" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test build
      else
        ./bootstrap.sh ${verbose} ${context} -w "${destination}" -m ${mode} ${mode_thread_param} ${mode_thread_value} ${mode_thread_individual_param} ${mode_thread_individual_value} -m test -m ${build_compiler} build
      fi
    fi
  fi

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to build ${mode} project '${c_notice}${project}${c_reset}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
    echo -e "Installing ${mode} project '${c_notice}${project}${c_reset}'."
    echo
  fi

  if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
    zsh ./install.sh ${verbose} ${context} -w "${destination}"
  else
    ./install.sh ${verbose} ${context} -w "${destination}"
  fi

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to install ${mode} project '${c_notice}${project}${c_reset}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  return 0
}

test_operate_build_tools() {
  local path_original="${PWD}/"

  if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
    test_print_first_or_always

    echo -e "${c_highlight}Building project build tools.${c_reset}"
    echo -e "${c_title}-----------------------------${c_reset}"
    echo
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "${shell_command} ${path_scripts_package} ${verbose} ${context} -d ${path_test_package} -S fake rebuild"
  fi

  ${shell_command} ${path_scripts_package} ${verbose} ${context} -d ${path_test_package} -S fake rebuild

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to clean and build the stand_alone fake package.${c_reset}"
    fi

    return 1
  fi

  test_operate_build_project "${path_test_package_stand_alone}" "${path_test_project}" fake stand_alone bootstrap ${build_project_thread}

  if [[ ${?} -ne 0 ]] ; then
    let failure=1
  fi

  cd ${path_original}

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

test_operate_ci_prebuild() {
  local clone_quiet=
  local path_original="${PWD}/"
  local result=

  if [[ ${verbosity} == "quiet" ]] ; then
    clone_quiet="-q"
  fi

  if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
    test_print_first_or_always

    echo -e "${c_highlight}Performing Github Specific Pre-Build Operations.${c_reset}"
    echo -e "${c_title}------------------------------------------------${c_reset}"
    echo
  fi

  test_operate_ci_prebuild_libcap

  if [[ ${?} -ne 0 ]] ; then
    let failure=1
  fi

  cd ${path_original}

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

test_operate_ci_pretest() {
  local clone_quiet=
  local path_original="${PWD}/"
  local result=

  if [[ ${verbosity} == "quiet" ]] ; then
    clone_quiet="-q"
  fi

  if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
    test_print_first_or_always

    echo -e "${c_highlight}Performing Github Specific Pre-Test Operations.${c_reset}"
    echo -e "${c_title}-----------------------------------------------${c_reset}"
    echo
  fi

  test_operate_ci_pretest_cmocka

  if [[ ${?} -ne 0 ]] ; then
    let failure=1
  fi

  cd ${path_original}

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

test_operate_ci_pretest_cmocka() {
  local cmocka_path="${path_test}cmocka/"
  local cmocka_build="${cmocka_path}build/"
  local cmocka_data="${cmocka_path}data/build/"
  local cmocka_settings="${path_original}level_3/fake/data/projects/cmocka/1.1.5/settings"
  local cmocka_uri="https://github.com/coreboot/cmocka.git"
  local cmocka_branch="cmocka-1.1.5"

  if [[ -d ${cmocka_path} ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      test_print_first_or_always

      echo -e "Detected existing cmocka repository at \"${c_notice}${cmocka_path}${c_reset}\", skipping the cmocka process."
    fi

    return 0
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "git clone ${clone_quiet} --single-branch -b ${cmocka_branch} \"${cmocka_uri}\" ${cmocka_path}"
  fi

  git clone ${clone_quiet} --single-branch -b ${cmocka_branch} "${cmocka_uri}" ${cmocka_path}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to git clone '${c_notice}${cmocka_uri}${c_error}' onto  '${c_notice}${cmocka_path}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "mkdir ${verbose_common} -p ${cmocka_data}"
  fi

  mkdir ${verbose_common} -p ${cmocka_data}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to create cmocka build data directory '${c_notice}${cmocka_data}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "cp ${verbose_common} ${cmocka_settings} ${cmocka_data}"
  fi

  cp ${verbose_common} ${cmocka_settings} ${cmocka_data}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to copy cmocka build settings: '${c_notice}${cmocka_settings}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "cd ${cmocka_path}"
  fi

  cd ${cmocka_path}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to change cmocka source directory '${c_notice}${cmocka_path}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "PATH=\"${env_path}\" LD_LIBRARY_PATH=\"${env_libs}\" fake ${verbose} ${context} -w \"${path_test_work}\" -m ${build_compiler} -m ${test_thread} clean build ${ci_arguments}"
  fi

  PATH="${env_path}" LD_LIBRARY_PATH="${env_libs}" fake ${verbose} ${context} -w "${path_test_work}" -m ${build_compiler} -m ${test_thread} clean build ${ci_arguments}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to build '${c_notice}cmocka${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "cp ${verbose_common} -R ${cmocka_build}includes/* ${work_path}includes/"
  fi

  cp ${verbose_common} -R ${cmocka_build}includes/* ${work_path}includes/

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to install cmocka headers to '${c_notice}${work_path}includes/${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "cp ${verbose_common} -R ${cmocka_build}libraries/shared/* ${work_path}libraries/shared/"
  fi

  cp ${verbose_common} -R ${cmocka_build}libraries/shared/* ${work_path}libraries/shared/

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to install cmocka libraries to '${c_notice}${work_path}libraries/shared/${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  return 0
}

test_operate_ci_prebuild_libcap() {
  local libcap_path="${path_test}libcap/"
  local libcap_uri="https://github.com/thekevinday/kernel.org-libcap.git"
  local libcap_branch="master"

  if [[ -d ${libcap_path} ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      test_print_first_or_always

      echo -e "Detected existing libcap repository at \"${c_notice}${libcap_path}${c_reset}\", skipping the libcap process."
    fi

    return 0
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "git clone ${clone_quiet} --single-branch -b ${libcap_branch} \"${libcap_uri}\" ${libcap_path}"
  fi

  git clone ${clone_quiet} --single-branch -b ${libcap_branch} "${libcap_uri}" ${libcap_path}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to git clone '${c_notice}${libcap_uri}${c_error}' onto  '${c_notice}${libcap_path}${c_error}'.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "cd ${libcap_path}"
  fi

  cd ${libcap_path}

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to change libcap source directory '${c_notice}${libcap_path}${c_error}'.${c_reset}"

      test_print_last
    fi

    let failure=1

    return 1
  fi

  if [[ ${verbosity} == "debug" ]] ; then
    test_print_first_or_always

    echo "make MANDIR=${work_path}fake/ SBINDIR=${work_path}fake/ INCDIR=${work_path}includes/ LIBDIR=${work_path}libraries/shared/ PKGCONFIGDIR=${work_path}fake/ install"
  fi

  make MANDIR=${work_path}fake/ SBINDIR=${work_path}fake/ INCDIR=${work_path}includes/ LIBDIR=${work_path}libraries/shared/ PKGCONFIGDIR=${work_path}fake/ install

  if [[ ${?} -ne 0 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      test_print_first

      echo -e "${c_error}ERROR: Failed to build and install libcap into the work directory '${c_notice}${work_path}${c_error}'.${c_reset}"

      test_print_last
    fi

    let failure=1

    return 1
  fi

  return 0
}

test_operate_tests() {
  local project=
  local path_original="${PWD}/"
  local destination="${path_test_work}"
  local thread_individual_param=
  local thread_individual_value="${test_thread_individual}"

  if [[ ${test_thread_individual} != "" ]] ; then
    thread_individual_param="-m"
  fi

  for project in ${projects} ; do

    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      test_print_first_or_always

      echo -e "${c_highlight}Testing Project ${project}.${c_reset}"
      echo -e "${c_title}--------------------------------------${c_reset}"
      echo
    fi

    if [[ ! -d ${path_test_package_individual}${project}-${version}/ ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        test_print_first

        echo -e "${c_error}ERROR: Package directory '${c_notice}${path_test_package_individual}${project}-${version}${c_error}' is invalid or missing.${c_reset}"

        test_print_last
      fi

      let failure=1
    fi

    if [[ ${failure} -eq 0 ]] ; then
      if [[ ! -f ${path_test_package_individual}${project}-${version}/data/build/testfile ]] ; then
        if [[ $(echo ${projects_no_tests} | grep -o "\<${project}\>") == "" ]] ; then
          if [[ ${verbosity} == "verbose" || ${verbosity} == "debug" ]] ; then
            test_print_first_or_always

            echo -e "${c_warning}WARNING: Project '${c_notice}${project}${c_warning}' does not have a testfile.${c_reset}"
          fi
        else
          test_print_first_or_always

          echo -e "Project '${c_notice}${project}${c_reset}' has no tests and is not expected to.${c_reset}"
        fi

        continue
      fi
    fi

    if [[ ${failure} -eq 0 ]] ; then
      if [[ ${verbosity} == "debug" ]] ; then
        test_print_first_or_always

        echo -e "Running '${c_notice}cd ${path_test_package_individual}${project}-${version}/${c_reset}'."
      fi

      cd ${path_test_package_individual}${project}-${version}/

      if [[ ${?} -ne 0 ]] ; then
        if [[ ${verbosity} != "quiet" ]] ; then
          test_print_first

          echo -e "${c_error}ERROR: Failed to change into directory '${c_notice}${path_test_package_individual}${project}-${version}${c_error}'.${c_reset}"

          test_print_last
        fi

        let failure=1
      fi
    fi

    if [[ ${failure} -eq 0 ]] ; then
      if [[ ${verbosity} == "debug" ]] ; then
        test_print_first_or_always

        if [[ ${build_compiler} == "gcc" ]] ; then
          echo "PATH=\"${env_path}\" LD_LIBRARY_PATH=\"${env_libs}\" fake ${verbose} ${context} -w \"${destination}\" -m individual -m ${test_thread} ${thread_individual_param} ${thread_individual_value} -m test clean make -f testfile ${ci_arguments}"
        else
          echo "PATH=\"${env_path}\" LD_LIBRARY_PATH=\"${env_libs}\" fake ${verbose} ${context} -w \"${destination}\" -m individual -m ${test_thread} ${thread_individual_param} ${thread_individual_value} -m test -m ${build_compiler} clean make -f testfile ${ci_arguments}"
        fi
      fi

      if [[ ${build_compiler} == "gcc" ]] ; then
        PATH="${env_path}" LD_LIBRARY_PATH="${env_libs}" fake ${verbose} ${context} -w "${destination}" -m individual -m ${test_thread} ${thread_individual_param} ${thread_individual_value} -m test clean make -f testfile ${ci_arguments}
      else
        PATH="${env_path}" LD_LIBRARY_PATH="${env_libs}" fake ${verbose} ${context} -w "${destination}" -m individual -m ${test_thread} ${thread_individual_param} ${thread_individual_value} -m test -m ${build_compiler} clean make -f testfile ${ci_arguments}
      fi

      if [[ ${?} -ne 0 ]] ; then
        if [[ ${verbosity} != "quiet" ]] ; then
          test_print_first

          echo -e "${c_error}ERROR: Failure while testing project '${c_notice}${project}${c_reset}${c_error}'.${c_reset}"

          test_print_last
        fi

        let failure=1
      fi
    fi

    cd ${path_original}

    if [[ ${failure} -eq 1 ]] ; then
      break;
    fi
  done

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

test_print_first() {

  if [[ ${print_line_first} == "yes" ]] ; then
    echo

    print_line_first=
  fi
}

test_print_first_or_always() {

  if [[ ${print_line_first} == "yes" ]] ; then
    echo

    print_line_first=
  elif [[ ${print_line_first} == "no" ]] ; then
    print_line_first=
  else
    echo
  fi
}

test_print_last() {

  if [[ ${print_line_last} == "yes" ]] ; then
    echo
  fi
}

test_cleanup() {

  unset test_copyright
  unset test_main
  unset test_handle_colors
  unset test_help
  unset test_operate
  unset test_operate_build_individual
  unset test_operate_build_project
  unset test_operate_build_tools
  unset test_operate_ci_prebuild
  unset test_operate_ci_prebuild_libcap
  unset test_operate_ci_pretest
  unset test_operate_ci_pretest_cmocka
  unset test_operate_tests
  unset test_print_first
  unset test_print_first_or_always
  unset test_print_last
  unset test_cleanup
}

test_main $*

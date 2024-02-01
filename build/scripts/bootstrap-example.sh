#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# The purpose of this script is to provide an example on how to bootstrap this project using command line arguments.
# Unlike the other scripts, this is not inteded to be run as if it were a program.
# Instead this provides a functional example on what commands to perform to perform the bootstrap.
#
# This only accepts one argument, followed by these optional arguments:
# 1) One of "Modes" from below.
# 2) Optional, may be one of: +d, +l, +n, +V, +Q, +E, +N, +D, --enable-shared, --enable-static, --disable-shared, --disable-static.
# 3) Optional, may be one of: -w, --work.
# 4) Optional, may be: clang.
#
# Modes:
#   - "individual"
#   - "level"
#   - "monolithic"
#   - "fake-individual"
#   - "fake-level"
#   - "fake-monolithic"
#   - "fake-stand_alone"
#   - "utf8-individual"
#   - "utf8-level"
#   - "utf8-monolithic"
#   - "utf8-stand_alone"
#   - "programs-individual"
#   - "programs-level"
#   - "programs-monolithic"
#
# The -w/--work requires the path to the work directory following it.
# The clang parameter does not need the "-m".
#
# This will create a directory at he present working directory of the script caller called "fll" where everything will be installed.
# This assumes the shell script is GNU bash.
# This is not intended to provide any extensive or thorough error handling.
#
# This script can also be run under zsh rather than bash by setting the environment variable SHELL_ENGINE to "zsh", such as:
#   SHELL_ENGINE="zsh" zsh ./bootstrap-example.sh --help
#

if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
  emulate ksh
fi

path_original="${PWD}/"
path_work="${path_original}fll/"

verbose=
verbose_common=
color=
shared=
static=
version=0.7.0
clang=
mode_part=
mode_parameter=
mode_path=
mode_value=
mode_thread_param="-m"
mode_thread_value="thread"
build_mode=
build_mode_extra_param_1=
build_mode_extra_value_1=
build_mode_extra_param_2=
build_mode_extra_value_2=
shell_command=bash
suppress_first="+F"

if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
  shell_command=zsh
fi

let i=2
p=

while [[ ${i} -le $# ]] ; do

  if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
    p=${(P)i}
  else
    p=${!i}
  fi

  if [[ ${p} == "+d" ]] ; then
    color="+d"
  elif [[ ${p} == "+l" ]] ; then
    color="+l"
  elif [[ ${p} == "+n" ]] ; then
    color="+n"
  elif [[ ${p} == "+Q" ]] ; then
    verbose="+Q"
    verbose_common=
  elif [[ ${p} == "+E" ]] ; then
    verbose="+E"
    verbose_common=
  elif [[ ${p} == "+N" ]] ; then
    verbose="+N"
    verbose_common=
  elif [[ ${p} == "+V" ]] ; then
    verbose="+V"
    verbose_common="-v"
  elif [[ ${p} == "+D" ]] ; then
    verbose="+D"
    verbose_common="-v"
  elif [[ ${p} == "--enable-static" ]] ; then
    static="--enable-static"
  elif [[ ${p} == "--disable-static" ]] ; then
    static="--disable-static"
  elif [[ ${p} == "--enable-shared" ]] ; then
    shared="--enable-shared"
  elif [[ ${p} == "--disable-shared" ]] ; then
    shared="--disable-shared"
  elif [[ ${p} == "clang" ]] ; then
    clang="-m clang"
  elif [[ ${p} == "-w" || ${p} == "--work" ]] ; then
    let i++

    if [[ ${i} -le $# ]] ; then
      path_work=${p}
    fi
  fi

  let i++
done

if [[ ! -d ${path_work} ]] ; then
  mkdir ${verbose_common} -p ${path_work}
fi

if [[ ${1} == "individual" ]] ; then
  ${shell_command} build/scripts/package.sh ${verbose} ${color} rebuild -i

  if [[ ${?} -eq 0 ]] ; then
    for i in f_type f_status f_memory f_type_array f_string f_utf f_abstruse f_account f_capability f_color f_compare f_console f_control_group f_conversion f_directory f_environment f_execute f_file f_fss f_iki f_limit f_network f_parse f_path f_pipe f_print f_random f_rip f_serialize f_signal f_socket f_status_string f_thread f_time fl_control_group fl_conversion fl_directory fl_environment fl_execute fl_fss fl_iki fl_path fl_print fl_status_string fl_utf_file fll_control_group fll_error fll_execute fll_file fll_fss fll_fss_status_string fll_iki fll_print fll_program ; do
      echo && echo "Processing ${i}." &&

      cd package/individual/${i}-${version}/ &&

      ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

      ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m individual -m individual_thread ${mode_thread_param} ${mode_thread_value} ${clang} &&

      ${shell_command} ./install.sh ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} &&

      cd ${path_original} || break
    done
  fi
fi

if [[ ${1} == "level" ]] ; then
  ${shell_command} build/scripts/package.sh ${verbose} ${color} rebuild -l &&

  cd package/level/fll-level_0-${version}/ &&

  ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

  ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m level ${mode_thread_param} ${mode_thread_value} ${clang} &&

  ${shell_command} ./install.sh ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} &&

  cd ${path_original} &&

  cd package/level/fll-level_1-${version}/ &&

  ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

  ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m level ${mode_thread_param} ${mode_thread_value} &&

  ${shell_command} ./install.sh ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} &&

  cd ${path_original} &&

  cd package/level/fll-level_2-${version}/ &&

  ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

  ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m level ${mode_thread_param} ${mode_thread_value} &&

  ${shell_command} ./install.sh ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work}
fi

if [[ ${1} == "monolithic" ]] ; then
  ${shell_command} build/scripts/package.sh ${verbose} ${color} rebuild -m &&

  cd package/monolithic/fll-${version}/ &&

  ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

  ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m monolithic ${mode_thread_param} ${mode_thread_value} ${clang} &&

  ${shell_command} ./install.sh ${verbose} ${color} ${shared} ${suppress_first} ${static} -w ${path_work}
fi

# The following in an example on building individual projects.
for mode_part in fake utf8 ; do
  if [[ ${1} == "${mode_part}-individual" || ${1} == "${mode_part}-level" || ${1} == "${mode_part}-monolithic" || ${1} == "${mode_part}-stand_alone" ]] ; then
    break;
  fi

  mode_part=
done

if [[ ${mode_part} != "" ]] ; then
  mode_parameter="-p"
  mode_path="program"
  mode_value=
  build_mode_extra_param_1=
  build_mode_extra_value_1=
  build_mode_extra_param_2=
  build_mode_extra_value_2=

  if [[ ${1} == "${mode_part}-individual" ]] ; then
    build_mode="individual"

    if [[ ${mode_thread_param} != "" ]] ; then
      build_mode_extra_param_1="-m"
      build_mode_extra_value_1="individual_thread"
    fi

    build_mode_extra_param_2=${mode_thread_param}
    build_mode_extra_value_2=${mode_thread_value}
  elif [[ ${1} == "${mode_part}-level" ]] ; then
    build_mode="level"
    build_mode_extra_param_1=${mode_thread_param}
    build_mode_extra_value_1=${mode_thread_value}
  elif [[ ${1} == "${mode_part}-monolithic" ]] ; then
    build_mode="monolithic"
    build_mode_extra_param_1=${mode_thread_param}
    build_mode_extra_value_1=${mode_thread_value}
  elif [[ ${1} == "${mode_part}-stand_alone" ]] ; then
    build_mode="stand_alone"
    mode_path="stand_alone"
    mode_parameter="-S"
    mode_value="${mode_part}"
    build_mode_extra_param_1=${mode_thread_param}
    build_mode_extra_value_1=${mode_thread_value}
  fi

  ${shell_command} build/scripts/package.sh ${verbose} ${color} rebuild ${mode_parameter} ${mode_value} &&

  cd package/${mode_path}/${mode_part}-${version}/ &&

  ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

  ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m ${build_mode} ${build_mode_extra_param_1} ${build_mode_extra_value_1} ${mode_thread_param} ${mode_thread_value} &&

  ${shell_command} ./install.sh ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work}

# The following in an example on building all FLL program projects using the project bootstrapped from above.
elif [[ ${1} == "programs-individual" || ${1} == "programs-level" || ${1} == "programs-monolithic" ]] ; then
  build_mode_extra_param_1=
  build_mode_extra_value_1=
  build_mode_extra_param_2=
  build_mode_extra_value_2=

  if [[ ${1} == "programs-individual" ]] ; then
    build_mode="individual"

    if [[ ${mode_thread_param} != "" ]] ; then
      build_mode_extra_param_1="-m"
      build_mode_extra_value_1="individual_thread"
    fi

    build_mode_extra_param_2=${mode_thread_param}
    build_mode_extra_value_2=${mode_thread_value}
  elif [[ ${1} == "programs-level" ]] ; then
    build_mode="level"
    build_mode_extra_param_1=${mode_thread_param}
    build_mode_extra_value_1=${mode_thread_value}
  elif [[ ${1} == "programs-monolithic" ]] ; then
    build_mode="monolithic"
    build_mode_extra_param_1=${mode_thread_param}
    build_mode_extra_value_1=${mode_thread_value}
  fi

  ${shell_command} build/scripts/package.sh ${verbose} ${color} rebuild -p &&

  cd package/program

  if [[ ${?} -eq 0 ]] ; then

    for i in * ; do

      cd ${path_original}package/program/${i} &&

      ${shell_command} ./bootstrap.sh clean ${verbose} ${color} ${suppress_first} &&

      ${shell_command} ./bootstrap.sh build ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} -m ${build_mode} ${build_mode_extra_param_1} ${build_mode_extra_value_1} ${build_mode_extra_param_2} ${build_mode_extra_value_2} &&

      ${shell_command} ./install.sh ${verbose} ${color} ${suppress_first} ${shared} ${static} -w ${path_work} ||

      break
    done
  else
    echo
    echo "ERROR: failed to change directory to 'package/program'."
    echo
  fi
elif [[ ${1} != "individual" && ${1} != "level" && ${1} != "monolithic" ]] ; then
  echo
  echo "ERROR: '${1}' is not a supported build mode."
  echo
fi

# Regardless of what happens always return to the starting directory.
cd ${path_original}

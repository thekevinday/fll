#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide an example on how to bootstrap this project using command line arguments.
# Unlike the other scripts, this is not inteded to be run as if it were a program.
# Instead this provides a functional example on what commands to perform to perform the bootstrap.
#
# This only accepts a two arguments (both are required):
# 1) One of "individual", "level", "monolithic", "fake-individual", "fake-level", or "fake-monolithic"..
# 2) The version number of the project, such as "0.5.0".
#
# This will create a directory at he present working directory of the script caller called "fll" where everything will be installed.
# This assumes the shell script is GNU bash.
# This is not intended to provide any extensive or thorough error handling.

original_path="$PWD/"
install_path="${original_path}fll/"

mkdir -vp $install_path

if [[ $1 == "individual" ]] ; then
  bash build/scripts/package.sh build -i

  if [[ $? -eq 0 ]] ; then
    for i in f_type f_status f_memory f_string f_utf f_color f_console f_conversion f_directory f_environment f_file f_fss f_path f_pipe f_print f_serialized f_socket fl_color fl_console fl_directory fl_fss fl_print fl_serialized fl_socket fl_status fl_string fl_utf fl_utf_file fll_directory fll_execute fll_file fll_fss fll_program fll_status ; do
      cd package/individual/$i-$2/ &&

      ./bootstrap.sh clean &&

      ./bootstrap.sh build -w $install_path -m individual &&

      ./install.sh -w $install_path &&

      cd $original_path || break
    done
  fi
fi

if [[ $1 == "level" ]] ; then
  bash build/scripts/package.sh build -l &&

  cd package/level/fll-level_0-$2/ &&

  ./bootstrap.sh clean &&

  ./bootstrap.sh build -w $install_path -m level &&

  ./install.sh -w $install_path &&

  cd $original_path &&

  cd package/level/fll-level_1-$2/ &&

  ./bootstrap.sh clean &&

  ./bootstrap.sh build -w $install_path -m level &&

  ./install.sh -w $install_path &&

  cd $original_path &&

  cd package/level/fll-level_2-$2/ &&

  ./bootstrap.sh clean &&

  ./bootstrap.sh build -w $install_path -m level &&

  ./install.sh -w $install_path
fi

if [[ $1 == "monolithic" ]] ; then
  bash build/scripts/package.sh build -m &&

  cd package/monolithic/fll-$2/ &&

  ./bootstrap.sh clean &&

  ./bootstrap.sh build -w $install_path -m monolithic &&

  ./install.sh -w $install_path
fi

# the following in an example on building the Featureless Make project (fake) from the project bootstrapped from above.
if [[ $1 == "fake-individual" || $1 == "fake-level" || $1 == "fake-monolithic" ]] ; then
  if [[ $1 == "fake-individual" ]] ; then
    build_mode="individual"
  elif [[ $1 == "fake-level" ]] ; then
    build_mode="level"
  elif [[ $1 == "fake-monolithic" ]] ; then
    build_mode="monolithic"
  fi

  bash build/scripts/package.sh build -p &&

  cd package/program/fake-$2/ &&

  ./bootstrap.sh clean &&

  ./bootstrap.sh build -w $install_path -m $build_mode &&

  ./install.sh -w $install_path
fi

# regardless of what happens always return to the starting directory.
cd $original_path

#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide an example on how to bootstrap this project using command line arguments.
# Unlike the other scripts, this is not inteded to be run as if it were a program.
# Instead this provides a functional example on what commands to perform to perform the bootstrap.
#
# This only accepts two arguments, followed by two optional arguments (first two are required and in the specified order):
# 1) One of "individual", "level", "monolithic", "fake-individual", "fake-level", or "fake-monolithic".
# 2) The version number of the project, such as "0.5.2".
# 3) Optional, may be one of: +V, +q, +n, +l, +d.
# 4) Optional, may be one of: +V, +q, +n, +l, +d.
#
# This will create a directory at he present working directory of the script caller called "fll" where everything will be installed.
# This assumes the shell script is GNU bash.
# This is not intended to provide any extensive or thorough error handling.

original_path="$PWD/"
install_path="${original_path}fll/"

verbose=
if [[ $3 == "+V" || $4 == "+V" ]] ; then
  verbose="+V"
elif [[ $3 == "+q" || $4 == "+q" ]] ; then
  verbose="+q"
fi

color=
if [[ $3 == "+d" || $4 == "+d" ]] ; then
  color="+d"
elif [[ $3 == "+l" || $4 == "+l" ]] ; then
  color="+l"
elif [[ $3 == "+n" || $4 == "+n" ]] ; then
  color="+n"
fi

mkdir -vp $install_path

if [[ $1 == "individual" ]] ; then
  bash build/scripts/package.sh $verbose $color build -i

  if [[ $? -eq 0 ]] ; then
    for i in f_type f_status f_memory f_string f_utf f_account f_capability f_color f_console f_control_group f_conversion f_directory f_environment f_execute f_file f_fss f_iki f_path f_pipe f_print f_process f_serialize f_signal f_socket fl_color fl_console fl_control_group fl_conversion fl_directory fl_environment fl_execute fl_fss fl_iki fl_print fl_status fl_string fl_type fl_utf fl_utf_file fll_control_group fll_environment fll_error fll_execute fll_file fll_fss fll_iki fll_path fll_program fll_status ; do
      echo && echo "Processing $i." &&

      cd package/individual/$i-$2/ &&

      ./bootstrap.sh clean $verbose $color &&

      ./bootstrap.sh build $verbose $color -w $install_path -m individual &&

      ./install.sh $verbose $color -w $install_path &&

      cd $original_path || break
    done
  fi
fi

if [[ $1 == "level" ]] ; then
  bash build/scripts/package.sh $verbose $color build -l &&

  cd package/level/fll-level_0-$2/ &&

  ./bootstrap.sh $verbose $color clean &&

  ./bootstrap.sh $verbose $color build -w $install_path -m level &&

  ./install.sh $verbose $color -w $install_path &&

  cd $original_path &&

  cd package/level/fll-level_1-$2/ &&

  ./bootstrap.sh $verbose $color clean &&

  ./bootstrap.sh $verbose $color build -w $install_path -m level &&

  ./install.sh $verbose $color -w $install_path &&

  cd $original_path &&

  cd package/level/fll-level_2-$2/ &&

  ./bootstrap.sh $verbose $color clean &&

  ./bootstrap.sh $verbose $color build -w $install_path -m level &&

  ./install.sh $verbose $color -w $install_path
fi

if [[ $1 == "monolithic" ]] ; then
  bash build/scripts/package.sh $verbose $color build -m &&

  cd package/monolithic/fll-$2/ &&

  ./bootstrap.sh $verbose $color clean &&

  ./bootstrap.sh $verbose $color build -w $install_path -m monolithic &&

  ./install.sh $verbose $color -w $install_path
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

  bash build/scripts/package.sh $verbose $color build -p &&

  cd package/program/fake-$2/ &&

  ./bootstrap.sh $verbose $color clean &&

  ./bootstrap.sh $verbose $color build -w $install_path -m $build_mode &&

  ./install.sh $verbose $color -w $install_path
fi

# regardless of what happens always return to the starting directory.
cd $original_path

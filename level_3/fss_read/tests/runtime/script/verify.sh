#!/bin.bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# Helper script for manually verifying tests.
#
# This is a simple script that only accepts these arguments in this specific order:
#   1) The build path containing the program output files for each test.
#   2) The expect path containing the generated and expected program output files for each test to match against.
#
# Note: Either update this script to pass "+FL" as an argument or manually remove the leading/trailing new lines.
#

verify_main() {
  local path_build="${1}"
  local path_expect="${2}"
  local failure=0
  local basename_file=
  local hash_build=
  local hash_expect=

  if [[ $path_build == "" ]] ; then
    echo "ERROR: No build path specified."

    return 1
  fi

  if [[ $path_expect == "" ]] ; then
    echo "ERROR: No expect path specified."

    return 1
  fi

  path_build=$(echo ${path_build} | sed -e 's|^//*|/|' -e 's|/*$|/|')
  path_expect=$(echo ${path_expect} | sed -e 's|^//*|/|' -e 's|/*$|/|')

  if [[ ! -d ${path_build} ]] ; then
    echo "ERROR: The build path '${path_build}' either does not exist or is not a directory."

    return 1
  fi

  if [[ ! -d ${path_expect} ]] ; then
    echo "ERROR: The expect path '${path_expect}' either does not exist or is not a directory."

    return 1
  fi

  verify_operate_test_standard

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

verify_operate_test_standard() {

  for i in ${path_build}* ; do

    basename_file=$(basename ${i})

    if [[ $? -ne 0 ]] ; then
      echo "ERROR: basename ${i} failed."

      let failure=1

      break
    fi

    hash_build=$(md5sum ${path_build}${basename_file} | sed -e 's| .*$||')

    if [[ $? -ne 0 ]] ; then
      echo "ERROR: md5sum ${path_build}${basename_file} | sed -e 's| .*$||' failed."

      let failure=1

      break
    fi

    hash_expect=$(md5sum ${path_expect}${basename_file} | sed -e 's| .*$||')

    if [[ $? -ne 0 ]] ; then
      echo "ERROR: md5sum ${path_expect}${basename_file} | sed -e 's| .*$||' failed."

      let failure=1

      break
    fi

    basename_file=$(echo -n ${basename_file} | sed -e 's|\.expect$||')

    if [[ $hash_build == $hash_expect ]] ; then
      echo "[ Success ] = ${basename_file}."
    else
      echo "[ Failure ] = ${basename_file}."

      let failure=1
    fi

  done

  echo

  if [[ $failure -eq 1 ]] ; then
    echo "Failure! Some or all tests failed."
  else
    echo "Success! All tests passed."
  fi

  return $failure
}

verify_cleanup() {

  unset verify_main
  unset verify_operate_test_standard
  unset verify_cleanup
}

verify_main $*

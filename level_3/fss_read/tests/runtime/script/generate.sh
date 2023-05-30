#!/bin.bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# Helper script for manually generating tests.
#
# This is a simple script that only accepts these arguments in this specific order:
#   1) The standard, using the 4-digit standard hexidecimal number (may also prepend "test-" to use 'fss_read -A').
#   2) The source file to read.
#   3) The destination directory to write to.
#
# Tests using the -n/--name will need to be manually created.
#
# Note: Either update this script to pass "+FL" as an argument or manually remove the leading/trailing new lines.
#       Alternatively, once fss_read is complete and working, rewrite this to require fss_read.
#

generate_main() {
  local standard="${1}"
  local file_source="${2}"
  local path_destination="${3}"
  local failure=0
  local test_base=
  local test_current=

  if [[ $standard == "" ]] ; then
    echo "ERROR: No standard specified."

    return 1
  fi

  if [[ $file_source == "" ]] ; then
    echo "ERROR: No source file specified."

    return 1
  fi

  if [[ $path_destination == "" ]] ; then
    echo "ERROR: No destination path specified."

    return 1
  fi

  file_source=$(echo ${file_source} | sed -e 's|^//*|/|' -e 's|//*|/|' -e 's|/*$||')
  path_destination=$(echo ${path_destination} | sed -e 's|^//*|/|' -e 's|/*$|/|')

  if [[ ! -f ${file_source} ]] ; then
    echo "ERROR: The source file '${file_source}' either does not exist or is not a file."

    return 1
  fi

  if [[ ! -d ${path_destination} ]] ; then
    echo "ERROR: The destination path '${path_destination}' either does not exist or is not a directory."

    return 1
  fi

  test_base=$(echo $file_source | sed -e 's|.*/||g' -e 's|\..*$||')
  test_current="${path_destination}${test_base}-"

  if [[ ${1} == "0000" ]] ; then
    generate_operate_0000
  elif [[ ${1} == "0001" ]] ; then
    generate_operate_0001
  elif [[ ${1} == "0002" ]] ; then
    generate_operate_0002
  elif [[ ${1} == "0003" ]] ; then
    generate_operate_0003
  elif [[ ${1} == "0008" ]] ; then
    generate_operate_0008
  elif [[ ${1} == "000e" ]] ; then
    generate_operate_000e
  elif [[ ${1} == "test-0000" ]] ; then
    generate_operate_test_standard
  elif [[ ${1} == "test-0001" ]] ; then
    generate_operate_test_standard
  elif [[ ${1} == "test-0002" ]] ; then
    generate_operate_test_standard
  elif [[ ${1} == "test-0003" ]] ; then
    generate_operate_test_standard
  elif [[ ${1} == "test-0008" ]] ; then
    generate_operate_test_standard
  elif [[ ${1} == "test-000e" ]] ; then
    generate_operate_test_standard
  fi

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

generate_operate_0000() {

  fss_basic_read +n -c ${file_source} > ${test_current}content.expect &&
  fss_basic_read +n -cO ${file_source} > ${test_current}content-original.expect &&
  fss_basic_read +n -ct ${file_source} > ${test_current}content-total.expect &&
  fss_basic_read +n -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_basic_read +n -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_basic_read +n -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_basic_read +n -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_basic_read +n -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_basic_read +n -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_basic_read +n -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_basic_read +n -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_basic_read +n -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_basic_read +n -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_basic_read +n -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_basic_read +n -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_basic_read +n -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_basic_read +n -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_basic_read +n -o ${file_source} > ${test_current}object.expect &&
  fss_basic_read +n -oO ${file_source} > ${test_current}object-original.expect &&
  fss_basic_read +n -ot ${file_source} > ${test_current}object-total.expect &&
  fss_basic_read +n -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_basic_read +n -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_basic_read +n -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_basic_read +n -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_basic_read +n -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_basic_read +n -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_basic_read +n -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_basic_read +n -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_basic_read +n -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_basic_read +n -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_basic_read +n -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_basic_read +n -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_basic_read +n -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_basic_read +n -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_basic_read +n -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_basic_read +n -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_basic_read +n -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_basic_read +n -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_basic_read +n -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_basic_read +n -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_basic_read +n -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_basic_read +n -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_basic_read +n -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_basic_read +n -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_basic_read +n -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_basic_read +n -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_basic_read +n -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_basic_read +n -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_basic_read +n -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_basic_read +n -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_basic_read +n -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation Complete"

  if [[ $? -ne 0 ]] ; then
    let failure=0
  fi

  return $failure
}

generate_operate_0001() {

  fss_extended_read +n -c ${file_source} > ${test_current}content.expect &&
  fss_extended_read +n -cO ${file_source} > ${test_current}content-original.expect &&
  fss_extended_read +n -ct ${file_source} > ${test_current}content-total.expect &&
  fss_extended_read +n -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_extended_read +n -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_extended_read +n -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_extended_read +n -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_extended_read +n -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_extended_read +n -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_extended_read +n -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_extended_read +n -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_extended_read +n -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_extended_read +n -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_extended_read +n -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_extended_read +n -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_extended_read +n -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_extended_read +n -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_extended_read +n -o ${file_source} > ${test_current}object.expect &&
  fss_extended_read +n -oO ${file_source} > ${test_current}object-original.expect &&
  fss_extended_read +n -ot ${file_source} > ${test_current}object-total.expect &&
  fss_extended_read +n -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_extended_read +n -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_extended_read +n -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_extended_read +n -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_extended_read +n -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_extended_read +n -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_extended_read +n -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_extended_read +n -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_extended_read +n -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_extended_read +n -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_extended_read +n -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_extended_read +n -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_extended_read +n -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_extended_read +n -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_extended_read +n -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_extended_read +n -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_extended_read +n -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_extended_read +n -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_extended_read +n -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_extended_read +n -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_extended_read +n -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_extended_read +n -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_extended_read +n -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_extended_read +n -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_extended_read +n -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_extended_read +n -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_extended_read +n -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_extended_read +n -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_extended_read +n -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_extended_read +n -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_extended_read +n -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation Complete"

  if [[ $? -ne 0 ]] ; then
    let failure=0
  fi

  return $failure
}

generate_operate_0002() {

  fss_basic_list_read +n -c ${file_source} > ${test_current}content.expect &&
  fss_basic_list_read +n -cO ${file_source} > ${test_current}content-original.expect &&
  fss_basic_list_read +n -ct ${file_source} > ${test_current}content-total.expect &&
  fss_basic_list_read +n -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_basic_list_read +n -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_basic_list_read +n -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_basic_list_read +n -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_basic_list_read +n -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_basic_list_read +n -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_basic_list_read +n -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_basic_list_read +n -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_basic_list_read +n -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_basic_list_read +n -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_basic_list_read +n -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_basic_list_read +n -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_basic_list_read +n -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_basic_list_read +n -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_basic_list_read +n -o ${file_source} > ${test_current}object.expect &&
  fss_basic_list_read +n -oO ${file_source} > ${test_current}object-original.expect &&
  fss_basic_list_read +n -ot ${file_source} > ${test_current}object-total.expect &&
  fss_basic_list_read +n -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_basic_list_read +n -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_basic_list_read +n -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_basic_list_read +n -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_basic_list_read +n -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_basic_list_read +n -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_basic_list_read +n -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_basic_list_read +n -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_basic_list_read +n -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_basic_list_read +n -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_basic_list_read +n -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_basic_list_read +n -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_basic_list_read +n -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_basic_list_read +n -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_basic_list_read +n -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_basic_list_read +n -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_basic_list_read +n -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_basic_list_read +n -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_basic_list_read +n -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_basic_list_read +n -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_basic_list_read +n -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_basic_list_read +n -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_basic_list_read +n -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_basic_list_read +n -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_basic_list_read +n -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_basic_list_read +n -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_basic_list_read +n -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_basic_list_read +n -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_basic_list_read +n -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_basic_list_read +n -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_basic_list_read +n -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation Complete"

  if [[ $? -ne 0 ]] ; then
    let failure=0
  fi

  return $failure
}

generate_operate_0003() {

  fss_extended_list_read +n -c ${file_source} > ${test_current}content.expect &&
  fss_extended_list_read +n -cO ${file_source} > ${test_current}content-original.expect &&
  fss_extended_list_read +n -ct ${file_source} > ${test_current}content-total.expect &&
  fss_extended_list_read +n -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_extended_list_read +n -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_extended_list_read +n -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_extended_list_read +n -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_extended_list_read +n -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_extended_list_read +n -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_extended_list_read +n -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_extended_list_read +n -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_extended_list_read +n -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_extended_list_read +n -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_extended_list_read +n -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_extended_list_read +n -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_extended_list_read +n -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_extended_list_read +n -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_extended_list_read +n -o ${file_source} > ${test_current}object.expect &&
  fss_extended_list_read +n -oO ${file_source} > ${test_current}object-original.expect &&
  fss_extended_list_read +n -ot ${file_source} > ${test_current}object-total.expect &&
  fss_extended_list_read +n -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_extended_list_read +n -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_extended_list_read +n -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_extended_list_read +n -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_extended_list_read +n -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_extended_list_read +n -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_extended_list_read +n -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_extended_list_read +n -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_extended_list_read +n -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_extended_list_read +n -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_extended_list_read +n -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_extended_list_read +n -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_extended_list_read +n -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_extended_list_read +n -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_extended_list_read +n -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_extended_list_read +n -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_extended_list_read +n -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_extended_list_read +n -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_extended_list_read +n -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_extended_list_read +n -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_extended_list_read +n -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_extended_list_read +n -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_extended_list_read +n -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_extended_list_read +n -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_extended_list_read +n -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_extended_list_read +n -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_extended_list_read +n -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_extended_list_read +n -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_extended_list_read +n -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_extended_list_read +n -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_extended_list_read +n -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation Complete"

  if [[ $? -ne 0 ]] ; then
    let failure=0
  fi

  return $failure
}

generate_operate_0008() {

  fss_embedded_list_read +n -c ${file_source} > ${test_current}content.expect &&
  fss_embedded_list_read +n -cO ${file_source} > ${test_current}content-original.expect &&
  fss_embedded_list_read +n -ct ${file_source} > ${test_current}content-total.expect &&
  fss_embedded_list_read +n -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_embedded_list_read +n -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_embedded_list_read +n -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_embedded_list_read +n -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_embedded_list_read +n -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_embedded_list_read +n -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_embedded_list_read +n -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_embedded_list_read +n -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_embedded_list_read +n -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_embedded_list_read +n -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_embedded_list_read +n -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_embedded_list_read +n -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_embedded_list_read +n -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_embedded_list_read +n -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_embedded_list_read +n -o ${file_source} > ${test_current}object.expect &&
  fss_embedded_list_read +n -oO ${file_source} > ${test_current}object-original.expect &&
  fss_embedded_list_read +n -ot ${file_source} > ${test_current}object-total.expect &&
  fss_embedded_list_read +n -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_embedded_list_read +n -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_embedded_list_read +n -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_embedded_list_read +n -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_embedded_list_read +n -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_embedded_list_read +n -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_embedded_list_read +n -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_embedded_list_read +n -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_embedded_list_read +n -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_embedded_list_read +n -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_embedded_list_read +n -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_embedded_list_read +n -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_embedded_list_read +n -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_embedded_list_read +n -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_embedded_list_read +n -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_embedded_list_read +n -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_embedded_list_read +n -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_embedded_list_read +n -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_embedded_list_read +n -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_embedded_list_read +n -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_embedded_list_read +n -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_embedded_list_read +n -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_embedded_list_read +n -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_embedded_list_read +n -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_embedded_list_read +n -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_embedded_list_read +n -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_embedded_list_read +n -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_embedded_list_read +n -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_embedded_list_read +n -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_embedded_list_read +n -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_embedded_list_read +n -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation Complete"

  if [[ $? -ne 0 ]] ; then
    let failure=0
  fi

  return $failure
}

generate_operate_000e() {

  fss_payload_read +n -c ${file_source} > ${test_current}content.expect &&
  fss_payload_read +n -cO ${file_source} > ${test_current}content-original.expect &&
  fss_payload_read +n -ct ${file_source} > ${test_current}content-total.expect &&
  fss_payload_read +n -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_payload_read +n -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_payload_read +n -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_payload_read +n -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_payload_read +n -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_payload_read +n -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_payload_read +n -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_payload_read +n -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_payload_read +n -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_payload_read +n -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_payload_read +n -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_payload_read +n -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_payload_read +n -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_payload_read +n -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_payload_read +n -o ${file_source} > ${test_current}object.expect &&
  fss_payload_read +n -oO ${file_source} > ${test_current}object-original.expect &&
  fss_payload_read +n -ot ${file_source} > ${test_current}object-total.expect &&
  fss_payload_read +n -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_payload_read +n -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_payload_read +n -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_payload_read +n -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_payload_read +n -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_payload_read +n -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_payload_read +n -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_payload_read +n -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_payload_read +n -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_payload_read +n -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_payload_read +n -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_payload_read +n -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_payload_read +n -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_payload_read +n -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_payload_read +n -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_payload_read +n -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_payload_read +n -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_payload_read +n -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_payload_read +n -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_payload_read +n -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_payload_read +n -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_payload_read +n -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_payload_read +n -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_payload_read +n -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_payload_read +n -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_payload_read +n -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_payload_read +n -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_payload_read +n -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_payload_read +n -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_payload_read +n -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_payload_read +n -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation Complete"

  if [[ $? -ne 0 ]] ; then
    let failure=0
  fi

  return $failure
}

generate_operate_test_standard() {
  standard=$(echo "${standard}" | sed -e 's|^test-||')

  fss_read +FLn -A ${standard} -c ${file_source} > ${test_current}content.expect &&
  fss_read +FLn -A ${standard} -cO ${file_source} > ${test_current}content-original.expect &&
  fss_read +FLn -A ${standard} -ct ${file_source} > ${test_current}content-total.expect &&
  fss_read +FLn -A ${standard} -cT ${file_source} > ${test_current}content-trim.expect &&
  fss_read +FLn -A ${standard} -cl 0 ${file_source} > ${test_current}content-line-0.expect &&
  fss_read +FLn -A ${standard} -cl 1 ${file_source} > ${test_current}content-line-1.expect &&
  fss_read +FLn -A ${standard} -cl 5 ${file_source} > ${test_current}content-line-5.expect &&
  fss_read +FLn -A ${standard} -cl 100 ${file_source} > ${test_current}content-line-100.expect &&
  fss_read +FLn -A ${standard} -cs 0 ${file_source} > ${test_current}content-select-0.expect &&
  fss_read +FLn -A ${standard} -cs 1 ${file_source} > ${test_current}content-select-1.expect &&
  fss_read +FLn -A ${standard} -cs 5 ${file_source} > ${test_current}content-select-5.expect &&
  fss_read +FLn -A ${standard} -cs 100 ${file_source} > ${test_current}content-select-100.expect &&
  fss_read +FLn -A ${standard} -cC ${file_source} > ${test_current}content-columns.expect &&
  fss_read +FLn -A ${standard} -ca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_read +FLn -A ${standard} -ca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_read +FLn -A ${standard} -ca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_read +FLn -A ${standard} -ca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  fss_read +FLn -A ${standard} -o ${file_source} > ${test_current}object.expect &&
  fss_read +FLn -A ${standard} -oO ${file_source} > ${test_current}object-original.expect &&
  fss_read +FLn -A ${standard} -ot ${file_source} > ${test_current}object-total.expect &&
  fss_read +FLn -A ${standard} -oT ${file_source} > ${test_current}object-trim.expect &&
  fss_read +FLn -A ${standard} -ol 0 ${file_source} > ${test_current}object-line-0.expect &&
  fss_read +FLn -A ${standard} -ol 1 ${file_source} > ${test_current}object-line-1.expect &&
  fss_read +FLn -A ${standard} -ol 5 ${file_source} > ${test_current}object-line-5.expect &&
  fss_read +FLn -A ${standard} -ol 100 ${file_source} > ${test_current}object-line-100.expect &&
  fss_read +FLn -A ${standard} -os 0 ${file_source} > ${test_current}object-select-0.expect &&
  fss_read +FLn -A ${standard} -os 1 ${file_source} > ${test_current}object-select-1.expect &&
  fss_read +FLn -A ${standard} -os 5 ${file_source} > ${test_current}object-select-5.expect &&
  fss_read +FLn -A ${standard} -os 100 ${file_source} > ${test_current}object-select-100.expect &&
  fss_read +FLn -A ${standard} -oC ${file_source} > ${test_current}object-columns.expect &&
  fss_read +FLn -A ${standard} -oa 0 ${file_source} > ${test_current}object-at-0.expect &&
  fss_read +FLn -A ${standard} -oa 1 ${file_source} > ${test_current}object-at-1.expect &&
  fss_read +FLn -A ${standard} -oa 5 ${file_source} > ${test_current}object-at-5.expect &&
  fss_read +FLn -A ${standard} -oa 100 ${file_source} > ${test_current}object-at-100.expect &&

  fss_read +FLn -A ${standard} -oc ${file_source} > ${test_current}object_and_content.expect &&
  fss_read +FLn -A ${standard} -ocO ${file_source} > ${test_current}object_and_content-original.expect &&
  fss_read +FLn -A ${standard} -oct ${file_source} > ${test_current}object_and_content-total.expect &&
  fss_read +FLn -A ${standard} -ocT ${file_source} > ${test_current}object_and_content-trim.expect &&
  fss_read +FLn -A ${standard} -ocl 0 ${file_source} > ${test_current}object_and_content-line-0.expect &&
  fss_read +FLn -A ${standard} -ocl 1 ${file_source} > ${test_current}object_and_content-line-1.expect &&
  fss_read +FLn -A ${standard} -ocl 5 ${file_source} > ${test_current}object_and_content-line-5.expect &&
  fss_read +FLn -A ${standard} -ocl 100 ${file_source} > ${test_current}object_and_content-line-100.expect &&
  fss_read +FLn -A ${standard} -ocs 0 ${file_source} > ${test_current}object_and_content-select-0.expect &&
  fss_read +FLn -A ${standard} -ocs 1 ${file_source} > ${test_current}object_and_content-select-1.expect &&
  fss_read +FLn -A ${standard} -ocs 5 ${file_source} > ${test_current}object_and_content-select-5.expect &&
  fss_read +FLn -A ${standard} -ocs 100 ${file_source} > ${test_current}object_and_content-select-100.expect &&
  fss_read +FLn -A ${standard} -ocC ${file_source} > ${test_current}object_and_content-columns.expect &&
  fss_read +FLn -A ${standard} -oca 0 ${file_source} > ${test_current}object_and_content-at-0.expect &&
  fss_read +FLn -A ${standard} -oca 1 ${file_source} > ${test_current}object_and_content-at-1.expect &&
  fss_read +FLn -A ${standard} -oca 5 ${file_source} > ${test_current}object_and_content-at-5.expect &&
  fss_read +FLn -A ${standard} -oca 100 ${file_source} > ${test_current}object_and_content-at-100.expect &&

  echo "Generation complete."

  if [[ $? -ne 0 ]] ; then
    let failure=1

    echo "Generation failed."
  fi

  return $failure
}

generate_cleanup() {

  unset generate_main
  unset generate_operate_0000
  unset generate_operate_0001
  unset generate_operate_0002
  unset generate_operate_0003
  unset generate_operate_0008
  unset generate_operate_000e
  unset generate_operate_test_standard
  unset generate_cleanup
}

generate_main $*

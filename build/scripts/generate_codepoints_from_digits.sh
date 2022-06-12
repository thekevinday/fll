#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# A simple script for generating code regarding unicode codepoint values.
#
# For example, given the Private Use Area range U+E000 to U+F8FF look like:
# ./generate_codepoints_from_digits.sh 57344 63743
#

main() {
  local -i first="$1"
  local -i last="$2"

  while [[ $first -le $last ]] ; do
    printf "U+%04X\n" $first

    let first++
  done
}

main "$1" "$2"

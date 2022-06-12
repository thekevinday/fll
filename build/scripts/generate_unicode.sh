#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# A simple script for generating code regarding unicode values.
# This requires the python "unicode" program.
#
# The following modes are supported:
# - source: Generate C source code if condition blocks (default).
# - test: Generate unit test byte data (in base 10) files.
#

main() {
  local file_input="codes.txt"
  local mode=$1
  local code=
  local sequence=
  local block=
  local previous=
  local s0=
  local s1=
  local s2=
  local s3=
  local u0=
  local u1=
  local u2=
  local u3=
  local -i i=0

  if [[ $mode == "" ]] ; then
    mode=source
  elif [[ ! ($mode == "source" || $mode == "test") ]] ; then

    # return on invalid parameter.
    return 1
  fi

  for code in $(cat $file_input) ; do

    process

    if [[ "$previous" == "" || "$block" == "$previous" ]] ; then
      if [[ $i -eq 0 ]] ; then
        s0=$sequence
        u0=$code
        let i++
      elif [[ $i -eq 1 ]] ; then
        s1=$sequence
        u1=$code
        let i++
      elif [[ $i -eq 2 ]] ; then
        s2=$sequence
        u2=$code
        let i++
      else
        s3=$sequence
        u3=$code

        generate "$block"

        s0=
        s1=
        s2=
        s3=

        u0=
        u1=
        u2=
        u3=

        let i=0
      fi
    else
      if [[ $i -gt 0 ]] ; then
        generate "$previous"
      fi

      s0=$sequence
      s1=
      s2=
      s3=

      u0=$code
      u1=
      u2=
      u3=

      let i=1
    fi

    previous="$block"
  done

  if [[ $s0 != "" ]] ; then
    generate "$previous"
  fi
}

process() {
  local utf8=$(unicode --color=0 $code | grep -o "^UTF-8:.*UTF-16BE:" | sed -e 's|UTF-8:||' -e 's|UTF-16BE:||' | sed -e 's| ||g')

  block=$(unicode --color=0 $code | grep -o "^Unicode block: .*$" | sed -e 's|Unicode block:.*; ||')

  if [[ $mode == "source" ]] ; then
    sequence="0x$utf8"

    if [[ $(echo -n "$utf8" | wc -c) -eq 2 ]] ; then
      sequence="${sequence}000000"
    elif [[ $(echo -n "$utf8" | wc -c) -eq 4 ]] ; then
      sequence="${sequence}0000"
    elif [[ $(echo -n "$utf8" | wc -c) -eq 6 ]] ; then
      sequence="${sequence}00"
    fi
  elif [[ $mode == "test" ]] ; then
    sequence="$utf8"
  fi
}

generate() {
  if [[ $mode == "source" ]] ; then
    generate_source "$1"
  elif [[ $mode == "test" ]] ; then
    generate_test "$1"
  fi
}

generate_source() {
  local comment=
  local condition=
  local block="$1"

  if [[ $u3 == "" ]] ; then
    if [[ $u2 == "" ]] ; then
      if [[ $u1 == "" ]] ; then
        comment="$u0"
        condition="character == $s0"
      else
        comment="$u0, $u1"
        condition="character == $s0 || character == $s1"
      fi
    else
      comment="$u0, $u1, $u2"
      condition="character == $s0 || character == $s1 || character == $s2"
    fi
  else
    comment="$u0, $u1, $u2, $u3"
    condition="character == $s0 || character == $s1 || character == $s2 || character == $s3"
  fi

  echo
  echo "// $block: $comment."
  echo "if ($condition) {"
  echo "  return F_true;"
  echo "}"
}

generate_test() {

  if [[ $s0 != "" ]] ; then
    printf "%llu\n" $((16#$s0))
  fi

  if [[ $s1 != "" ]] ; then
    printf "%llu\n" $((16#$s1))
  fi

  if [[ $s2 != "" ]] ; then
    printf "%llu\n" $((16#$s2))
  fi

  if [[ $s3 != "" ]] ; then
    printf "%llu\n" $((16#$s3))
  fi
}

main "$1"

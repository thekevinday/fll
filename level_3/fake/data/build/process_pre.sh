#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide an example for the pre-process part of Fake.
# Despite being an example, it is intended to be actually used when using fake to build the fake project.
#
process_pre_main(){
  local grab_next=
  local do_color=normal
  local i=0
  local p=
  local t=0

  # custom color codes.
  local c_reset="\\033[0m"
  local c_title="\\033[1;33m"
  local c_error="\\033[1;31m"
  local c_warning="\\033[0;33m"
  local c_highlight="\\033[1;32m"
  local c_notice="\\033[0;01m"
  local c_important="\\033[0;32m"
  local c_subtle="\\033[1;30m"
  local c_prefix="\\"

  # the three supported parameters.
  local operation=
  local mode=
  local defines=
  local verbosity=

  # grab all supported parameters, ignoring duplicates.
  if [[ $# -gt 0 ]] ; then
    t=$#

    while [[ $i -lt $t ]] ; do
      let i=$i+1
      p="${!i}"

      if [[ $grab_next == "" ]] ; then
        if [[ $p == "build" || $p == "clean" || $p == "make" || $p == "skeleton" ]] ; then
          if [[ $operation == "" ]] ; then
            operation=$p
          fi
        elif [[ $p == "-m" ]] ; then
          grab_next="mode"
        elif [[ $p == "-d" ]] ; then
          grab_next="defines"
        elif [[ $p == "+q" ]] ; then
          verbosity=quiet
        elif [[ $p == "+V" ]] ; then
          verbosity=verbose
        elif [[ $p == "+D" ]] ; then
          verbosity=debug
        elif [[ $p == "+n" ]] ; then
          if [[ $do_color == "normal" ]] ; then
            do_color=none
          fi
        elif [[ $p == "+l" ]] ; then
          if [[ $do_color == "normal" ]] ; then
            do_color=light
          fi
        fi
      else
        if [[ $grab_next == "mode" ]] ; then
          if [[ $mode == "" ]] ; then
            mode=$p
          else
            mode="$mode $p"
          fi
        elif [[ $grab_next == "defines" ]] ; then
          if [[ $defines == "" ]] ; then
            defines=$p
          fi
        fi

        grab_next=
      fi
    done

    p=
  fi

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

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_title}Begin Processing Operation: $c_reset$c_notice$operation$c_reset"

    if [[ $mode != "" ]] ; then
      echo -e "  Modes: $c_reset$c_notice$mode$c_reset"
    fi

    if [[ $defines != "" ]] ; then
      echo -e "  Defines: $c_reset$c_notice$defines$c_reset"
    fi

    echo
  fi

  # cleanup and return
  unset process_pre_main
  return 0
}

# note: "$@" is necessary to preserve quoted arguments when passing though.
process_pre_main "$@"

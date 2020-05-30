#!/bin/bash
# license: lgpl-2.1
# programmer: Kevin Day
#
# The purpose of this script is to provide an example for the pre-process part of Fake.
# Despite being an example, it is intended to be actually used when using fake to build the fake project.
#
# The dependencies of this script are: bash and sed.
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

  # the supported parameters.
  local operation=
  local defines=
  local modes=
  local process=
  local file_settings=
  local path_build=
  local path_data=
  local path_sources=
  local path_work=
  local verbosity=
  local build_status=

  # generated paths and standard paths.
  local path_directory_separator="/"
  local path_data_build=
  local path_documents="documents/"
  local path_licenses="licenses/"
  local path_sources_bash=
  local path_sources_c=
  local path_sources_cpp=
  local path_work_includes=
  local path_work_libraries=
  local path_work_libraries_script=
  local path_work_libraries_shared=
  local path_work_libraries_static=
  local path_work_programs=
  local path_work_programs_script=
  local path_work_programs_shared=
  local path_work_programs_static=

  # generated file paths.
  local file_data_build_dependencies=
  local file_data_build_settings=
  local file_documents_readme=

  # standard build paths.
  local path_build_documents=
  local path_build_includes=
  local path_build_libraries=
  local path_build_libraries_script=
  local path_build_libraries_shared=
  local path_build_libraries_static=
  local path_build_objects=
  local path_build_process=
  local path_build_programs=
  local path_build_programs_script=
  local path_build_programs_shared=
  local path_build_programs_static=
  local path_build_settings=

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
        elif [[ $p == "-d" ]] ; then
          grab_next="defines"
        elif [[ $p == "-m" ]] ; then
          grab_next="modes"
        elif [[ $p == "-o" ]] ; then
          grab_next="process"
        elif [[ $p == "-s" ]] ; then
          grab_next="file_settings"
        elif [[ $p == "-b" ]] ; then
          grab_next="path_build"
        elif [[ $p == "-D" ]] ; then
          grab_next="path_data"
        elif [[ $p == "-S" ]] ; then
          grab_next="path_sources"
        elif [[ $p == "-w" ]] ; then
          grab_next="path_work"
        elif [[ $p == "+D" ]] ; then
          verbosity=debug
        elif [[ $p == "+q" ]] ; then
          verbosity=quiet
        elif [[ $p == "+V" ]] ; then
          verbosity=verbose
        elif [[ $p == "+l" ]] ; then
          if [[ $do_color == "normal" ]] ; then
            do_color=light
          fi
        elif [[ $p == "+n" ]] ; then
          if [[ $do_color == "normal" ]] ; then
            do_color=none
          fi
        elif [[ $p == "++status" ]] ; then
          grab_next=build_status
        fi
      else
        if [[ $grab_next == "defines" ]] ; then
          if [[ $defines == "" ]] ; then
            defines=$p
          else
            defines="$defines $p"
          fi
        elif [[ $grab_next == "modes" ]] ; then
          if [[ $modes == "" ]] ; then
            modes=$p
          else
            modes="$modes $p"
          fi
        elif [[ $grab_next == "process" ]] ; then
          process="$p"
        elif [[ $grab_next == "file_settings" ]] ; then
          file_settings="$p"
        elif [[ $grab_next == "path_build" ]] ; then
          path_build=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_build" ]] ; then
          path_source_build=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_codes" ]] ; then
          path_source_codes=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_common" ]] ; then
          path_source_common=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_data" ]] ; then
          path_source_data=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_documents" ]] ; then
          path_source_documents=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_licenses" ]] ; then
          path_source_licenses=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_source_settings" ]] ; then
          path_source_settings=$(process_pre_path_fix $p)
        elif [[ $grab_next == "path_work" ]] ; then
          path_work=$(process_pre_path_fix $p)
        elif [[ $grab_next == "build_status" ]] ; then
          build_status="$p"
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

  # update paths based on parameters.
  path_data_build="${path_data}build$path_directory_separator"

  path_sources_bash="${path_sources}bash$path_directory_separator"
  path_sources_c="${path_sources}c$path_directory_separator"
  path_sources_cpp="${path_sources}c++$path_directory_separator"

  path_build_documents="${path_build}documents$path_directory_separator"
  path_build_includes="${path_build}includes$path_directory_separator"
  path_build_libraries="${path_build}libraries$path_directory_separator"
  path_build_libraries_script="${path_build_libraries}script$path_directory_separator"
  path_build_libraries_shared="${path_build_libraries}shared$path_directory_separator"
  path_build_libraries_static="${path_build_libraries}static$path_directory_separator"
  path_build_objects="${path_build}objects$path_directory_separator"
  path_build_process="${path_build}process$path_directory_separator"
  path_build_programs="${path_build}programs$path_directory_separator"
  path_build_programs_script="${path_build_programs}script$path_directory_separator"
  path_build_programs_shared="${path_build_programs}shared$path_directory_separator"
  path_build_programs_static="${path_build_programs}static$path_directory_separator"
  path_build_settings="${path_build}settings$path_directory_separator"

  if [[ $path_work != "" ]] ; then
    path_work_includes="${path_work}includes$path_directory_separator"
    path_work_libraries="${path_work_libraries}libraries$path_directory_separator"
    path_work_libraries_script="${path_work_libraries_script}script$path_directory_separator"
    path_work_libraries_shared="${path_work_libraries_shared}shared$path_directory_separator"
    path_work_libraries_static="${path_work_libraries_static}static$path_directory_separator"
    path_work_programs="${path_work_programs}programs$path_directory_separator"
    path_work_programs_script="${path_work_programs_script}script$path_directory_separator"
    path_work_programs_shared="${path_work_programs_shared}shared$path_directory_separator"
    path_work_programs_static="${path_work_programs_static}static$path_directory_separator"
  fi

  file_data_build_dependencies="${path_data_build}dependencies"
  file_data_build_settings="${path_data_build}settings"
  file_documents_readme="${path_documents}readme"

  if [[ $verbosity != "quiet" ]] ; then
    echo
    echo -e "${c_title}Processing Operation: $c_reset$c_notice$operation$c_reset"

    if [[ $modes != "" ]] ; then
      echo -e "  Modes: $c_reset$c_notice$modes$c_reset"
    fi

    if [[ $defines != "" ]] ; then
      echo -e "  Defines: $c_reset$c_notice$defines$c_reset"
    fi
  fi

  # cleanup and return.
  unset process_pre_main
  unset process_pre_path_fix
  return 0
}

process_pre_path_fix(){
  echo -n $* | sed -e "s|^${path_directory_separator}${path_directory_separator}*|${path_directory_separator}|" -e "s|${path_directory_separator}*$|${path_directory_separator}|"
}

# note: "$@" is necessary to preserve quoted arguments when passing to function.
process_pre_main "$@"

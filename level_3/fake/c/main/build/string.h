/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build string functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_string_h
#define _fake_build_string_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_s_
  #define FAKE_build_documentation_files_s "documentation files"
  #define FAKE_build_header_files_s        "header files"
  #define FAKE_build_header_files_shared_s "shared header files"
  #define FAKE_build_header_files_static_s "static header files"
  #define FAKE_build_scripts_s             "scripts"
  #define FAKE_build_setting_files_s       "setting files"

  #define FAKE_build_documentation_files_s_length 19
  #define FAKE_build_header_files_s_length        12
  #define FAKE_build_header_files_shared_s_length 19
  #define FAKE_build_header_files_static_s_length 19
  #define FAKE_build_scripts_s_length             7
  #define FAKE_build_setting_files_s_length       13

  extern const f_string_static_t fake_build_documentation_files_s;
  extern const f_string_static_t fake_build_header_files_s;
  extern const f_string_static_t fake_build_header_files_shared_s;
  extern const f_string_static_t fake_build_header_files_static_s;
  extern const f_string_static_t fake_build_scripts_s;
  extern const f_string_static_t fake_build_setting_files_s;
#endif // _di_fake_build_s_

/**
 * The build language strings.
 *
 * fake_build_language_*_s:
 *   - bash: The GNU Bash language.
 *   - c:    The C language.
 *   - cpp:  The C++ language.
 *   - zsh:  The ZSH language (Similar to and somewhat compatible with GNU Bash).
 */
#ifndef _di_fake_build_language_s_
  #define FAKE_build_language_bash_s "bash"
  #define FAKE_build_language_c_s    "c"
  #define FAKE_build_language_cpp_s  "c++"
  #define FAKE_build_language_zsh_s  "zsh"

  #define FAKE_build_language_bash_s_length 4
  #define FAKE_build_language_c_s_length    1
  #define FAKE_build_language_cpp_s_length  3
  #define FAKE_build_language_zsh_s_length  3

  extern const f_string_static_t fake_build_language_bash_s;
  extern const f_string_static_t fake_build_language_c_s;
  extern const f_string_static_t fake_build_language_cpp_s;
  extern const f_string_static_t fake_build_language_zsh_s;
#endif // _di_fake_build_language_s_

/**
 * The program version strings.
 */
#ifndef _di_fake_build_version_s_
  #define FAKE_build_version_major_s "major"
  #define FAKE_build_version_minor_s "minor"
  #define FAKE_build_version_micro_s "micro"
  #define FAKE_build_version_nano_s  "nano"

  #define FAKE_build_version_major_s_length 5
  #define FAKE_build_version_minor_s_length 5
  #define FAKE_build_version_micro_s_length 5
  #define FAKE_build_version_nano_s_length  4

  extern const f_string_static_t fake_build_version_major_s;
  extern const f_string_static_t fake_build_version_minor_s;
  extern const f_string_static_t fake_build_version_micro_s;
  extern const f_string_static_t fake_build_version_nano_s;
#endif // _di_fake_build_version_s_

#ifndef _di_fake_build_setting_s_
  #define FAKE_build_setting_default_ar_s             "ar"
  #define FAKE_build_setting_default_gcc_s            "gcc"
  #define FAKE_build_setting_default_version_s        "0"
  #define FAKE_build_setting_default_version_prefix_s "."
  #define FAKE_build_setting_default_yes_s            "yes"

  #define FAKE_build_setting_name_build_compiler_s               "build_compiler"
  #define FAKE_build_setting_name_build_indexer_s                "build_indexer"
  #define FAKE_build_setting_name_build_indexer_arguments_s      "build_indexer_arguments"
  #define FAKE_build_setting_name_build_language_s               "build_language"
  #define FAKE_build_setting_name_build_libraries_s              "build_libraries"
  #define FAKE_build_setting_name_build_libraries_shared_s       "build_libraries_shared"
  #define FAKE_build_setting_name_build_libraries_static_s       "build_libraries_static"
  #define FAKE_build_setting_name_build_name_s                   "build_name"
  #define FAKE_build_setting_name_build_objects_library_s        "build_objects_library"
  #define FAKE_build_setting_name_build_objects_library_shared_s "build_objects_library_shared"
  #define FAKE_build_setting_name_build_objects_library_static_s "build_objects_library_static"
  #define FAKE_build_setting_name_build_objects_program_s        "build_objects_program"
  #define FAKE_build_setting_name_build_objects_program_shared_s "build_objects_program_shared"
  #define FAKE_build_setting_name_build_objects_program_static_s "build_objects_program_static"
  #define FAKE_build_setting_name_build_script_s                 "build_script"
  #define FAKE_build_setting_name_build_shared_s                 "build_shared"
  #define FAKE_build_setting_name_build_sources_documentation_s  "build_sources_documentation"
  #define FAKE_build_setting_name_build_sources_headers_s        "build_sources_headers"
  #define FAKE_build_setting_name_build_sources_headers_shared_s "build_sources_headers_shared"
  #define FAKE_build_setting_name_build_sources_headers_static_s "build_sources_headers_static"
  #define FAKE_build_setting_name_build_sources_library_s        "build_sources_library"
  #define FAKE_build_setting_name_build_sources_library_shared_s "build_sources_library_shared"
  #define FAKE_build_setting_name_build_sources_library_static_s "build_sources_library_static"
  #define FAKE_build_setting_name_build_sources_object_s         "build_sources_object"
  #define FAKE_build_setting_name_build_sources_object_shared_s  "build_sources_object_shared"
  #define FAKE_build_setting_name_build_sources_object_static_s  "build_sources_object_static"
  #define FAKE_build_setting_name_build_sources_program_s        "build_sources_program"
  #define FAKE_build_setting_name_build_sources_program_shared_s "build_sources_program_shared"
  #define FAKE_build_setting_name_build_sources_program_static_s "build_sources_program_static"
  #define FAKE_build_setting_name_build_sources_script_s         "build_sources_script"
  #define FAKE_build_setting_name_build_sources_setting_s        "build_sources_setting"
  #define FAKE_build_setting_name_build_static_s                 "build_static"
  #define FAKE_build_setting_name_defines_s                      "defines"
  #define FAKE_build_setting_name_defines_library_s              "defines_library"
  #define FAKE_build_setting_name_defines_library_shared_s       "defines_library_shared"
  #define FAKE_build_setting_name_defines_library_static_s       "defines_library_static"
  #define FAKE_build_setting_name_defines_object_s               "defines_object"
  #define FAKE_build_setting_name_defines_object_shared_s        "defines_object_shared"
  #define FAKE_build_setting_name_defines_object_static_s        "defines_object_static"
  #define FAKE_build_setting_name_defines_program_s              "defines_program"
  #define FAKE_build_setting_name_defines_program_shared_s       "defines_program_shared"
  #define FAKE_build_setting_name_defines_program_static_s       "defines_program_static"
  #define FAKE_build_setting_name_defines_shared_s               "defines_shared"
  #define FAKE_build_setting_name_defines_static_s               "defines_static"
  #define FAKE_build_setting_name_environment_s                  "environment"
  #define FAKE_build_setting_name_flags_s                        "flags"
  #define FAKE_build_setting_name_flags_library_s                "flags_library"
  #define FAKE_build_setting_name_flags_library_shared_s         "flags_library_shared"
  #define FAKE_build_setting_name_flags_library_static_s         "flags_library_static"
  #define FAKE_build_setting_name_flags_object_s                 "flags_object"
  #define FAKE_build_setting_name_flags_object_shared_s          "flags_object_shared"
  #define FAKE_build_setting_name_flags_object_static_s          "flags_object_static"
  #define FAKE_build_setting_name_flags_program_s                "flags_program"
  #define FAKE_build_setting_name_flags_program_shared_s         "flags_program_shared"
  #define FAKE_build_setting_name_flags_program_static_s         "flags_program_static"
  #define FAKE_build_setting_name_flags_shared_s                 "flags_shared"
  #define FAKE_build_setting_name_flags_static_s                 "flags_static"
  #define FAKE_build_setting_name_has_path_standard_s            "has_path_standard"
  #define FAKE_build_setting_name_modes_s                        "modes"
  #define FAKE_build_setting_name_modes_default_s                "modes_default"
  #define FAKE_build_setting_name_path_headers_s                 "path_headers"
  #define FAKE_build_setting_name_path_language_s                "path_language"
  #define FAKE_build_setting_name_path_library_script_s          "path_library_script"
  #define FAKE_build_setting_name_path_library_shared_s          "path_library_shared"
  #define FAKE_build_setting_name_path_library_static_s          "path_library_static"
  #define FAKE_build_setting_name_path_object_script_s           "path_object_script"
  #define FAKE_build_setting_name_path_object_shared_s           "path_object_shared"
  #define FAKE_build_setting_name_path_object_static_s           "path_object_static"
  #define FAKE_build_setting_name_path_program_script_s          "path_program_script"
  #define FAKE_build_setting_name_path_program_shared_s          "path_program_shared"
  #define FAKE_build_setting_name_path_program_static_s          "path_program_static"
  #define FAKE_build_setting_name_path_sources_s                 "path_sources"
  #define FAKE_build_setting_name_path_sources_object_s          "path_sources_object"
  #define FAKE_build_setting_name_preserve_path_headers_s        "preserve_path_headers"
  #define FAKE_build_setting_name_process_post_s                 "process_post"
  #define FAKE_build_setting_name_process_pre_s                  "process_pre"
  #define FAKE_build_setting_name_search_exclusive_s             "search_exclusive"
  #define FAKE_build_setting_name_search_shared_s                "search_shared"
  #define FAKE_build_setting_name_search_static_s                "search_static"
  #define FAKE_build_setting_name_version_file_s                 "version_file"
  #define FAKE_build_setting_name_version_major_s                "version_major"
  #define FAKE_build_setting_name_version_major_prefix_s         "version_major_prefix"
  #define FAKE_build_setting_name_version_micro_s                "version_micro"
  #define FAKE_build_setting_name_version_micro_prefix_s         "version_micro_prefix"
  #define FAKE_build_setting_name_version_minor_s                "version_minor"
  #define FAKE_build_setting_name_version_minor_prefix_s         "version_minor_prefix"
  #define FAKE_build_setting_name_version_nano_s                 "version_nano"
  #define FAKE_build_setting_name_version_nano_prefix_s          "version_nano_prefix"
  #define FAKE_build_setting_name_version_target_s               "version_target"

  #define FAKE_build_setting_default_ar_s_length             2
  #define FAKE_build_setting_default_gcc_s_length            3
  #define FAKE_build_setting_default_version_s_length        1
  #define FAKE_build_setting_default_version_prefix_s_length 1
  #define FAKE_build_setting_default_yes_s_length            3

  #define FAKE_build_setting_name_build_compiler_s_length               14
  #define FAKE_build_setting_name_build_indexer_s_length                13
  #define FAKE_build_setting_name_build_indexer_arguments_s_length      23
  #define FAKE_build_setting_name_build_language_s_length               14
  #define FAKE_build_setting_name_build_libraries_s_length              15
  #define FAKE_build_setting_name_build_libraries_shared_s_length       22
  #define FAKE_build_setting_name_build_libraries_static_s_length       22
  #define FAKE_build_setting_name_build_name_s_length                   10
  #define FAKE_build_setting_name_build_objects_library_s_length        21
  #define FAKE_build_setting_name_build_objects_library_shared_s_length 28
  #define FAKE_build_setting_name_build_objects_library_static_s_length 28
  #define FAKE_build_setting_name_build_objects_program_s_length        21
  #define FAKE_build_setting_name_build_objects_program_shared_s_length 28
  #define FAKE_build_setting_name_build_objects_program_static_s_length 28
  #define FAKE_build_setting_name_build_script_s_length                 12
  #define FAKE_build_setting_name_build_shared_s_length                 12
  #define FAKE_build_setting_name_build_sources_documentation_s_length  27
  #define FAKE_build_setting_name_build_sources_headers_s_length        21
  #define FAKE_build_setting_name_build_sources_headers_shared_s_length 28
  #define FAKE_build_setting_name_build_sources_headers_static_s_length 28
  #define FAKE_build_setting_name_build_sources_library_s_length        21
  #define FAKE_build_setting_name_build_sources_library_shared_s_length 28
  #define FAKE_build_setting_name_build_sources_library_static_s_length 28
  #define FAKE_build_setting_name_build_sources_object_s_length         20
  #define FAKE_build_setting_name_build_sources_object_shared_s_length  27
  #define FAKE_build_setting_name_build_sources_object_static_s_length  27
  #define FAKE_build_setting_name_build_sources_program_s_length        21
  #define FAKE_build_setting_name_build_sources_program_shared_s_length 28
  #define FAKE_build_setting_name_build_sources_program_static_s_length 28
  #define FAKE_build_setting_name_build_sources_script_s_length         20
  #define FAKE_build_setting_name_build_sources_setting_s_length        21
  #define FAKE_build_setting_name_build_static_s_length                 12
  #define FAKE_build_setting_name_environment_s_length                  11
  #define FAKE_build_setting_name_defines_s_length                      7
  #define FAKE_build_setting_name_defines_library_s_length              15
  #define FAKE_build_setting_name_defines_library_shared_s_length       22
  #define FAKE_build_setting_name_defines_library_static_s_length       22
  #define FAKE_build_setting_name_defines_object_s_length               14
  #define FAKE_build_setting_name_defines_object_shared_s_length        21
  #define FAKE_build_setting_name_defines_object_static_s_length        21
  #define FAKE_build_setting_name_defines_program_s_length              15
  #define FAKE_build_setting_name_defines_program_shared_s_length       22
  #define FAKE_build_setting_name_defines_program_static_s_length       22
  #define FAKE_build_setting_name_defines_shared_s_length               14
  #define FAKE_build_setting_name_defines_static_s_length               14
  #define FAKE_build_setting_name_flags_s_length                        5
  #define FAKE_build_setting_name_flags_library_s_length                13
  #define FAKE_build_setting_name_flags_library_shared_s_length         20
  #define FAKE_build_setting_name_flags_library_static_s_length         20
  #define FAKE_build_setting_name_flags_object_s_length                 12
  #define FAKE_build_setting_name_flags_object_shared_s_length          19
  #define FAKE_build_setting_name_flags_object_static_s_length          19
  #define FAKE_build_setting_name_flags_program_s_length                13
  #define FAKE_build_setting_name_flags_program_shared_s_length         20
  #define FAKE_build_setting_name_flags_program_static_s_length         20
  #define FAKE_build_setting_name_flags_shared_s_length                 12
  #define FAKE_build_setting_name_flags_static_s_length                 12
  #define FAKE_build_setting_name_has_path_standard_s_length            17
  #define FAKE_build_setting_name_modes_s_length                        5
  #define FAKE_build_setting_name_modes_default_s_length                13
  #define FAKE_build_setting_name_path_headers_s_length                 12
  #define FAKE_build_setting_name_path_language_s_length                13
  #define FAKE_build_setting_name_path_library_script_s_length          19
  #define FAKE_build_setting_name_path_library_shared_s_length          19
  #define FAKE_build_setting_name_path_library_static_s_length          19
  #define FAKE_build_setting_name_path_object_script_s_length           18
  #define FAKE_build_setting_name_path_object_shared_s_length           18
  #define FAKE_build_setting_name_path_object_static_s_length           18
  #define FAKE_build_setting_name_path_program_script_s_length          19
  #define FAKE_build_setting_name_path_program_shared_s_length          19
  #define FAKE_build_setting_name_path_program_static_s_length          19
  #define FAKE_build_setting_name_path_sources_s_length                 12
  #define FAKE_build_setting_name_path_sources_object_s_length          19
  #define FAKE_build_setting_name_preserve_path_headers_s_length        21
  #define FAKE_build_setting_name_process_post_s_length                 12
  #define FAKE_build_setting_name_process_pre_s_length                  11
  #define FAKE_build_setting_name_search_exclusive_s_length             16
  #define FAKE_build_setting_name_search_shared_s_length                13
  #define FAKE_build_setting_name_search_static_s_length                13
  #define FAKE_build_setting_name_version_file_s_length                 12
  #define FAKE_build_setting_name_version_major_s_length                13
  #define FAKE_build_setting_name_version_major_prefix_s_length         20
  #define FAKE_build_setting_name_version_micro_s_length                13
  #define FAKE_build_setting_name_version_micro_prefix_s_length         20
  #define FAKE_build_setting_name_version_minor_s_length                13
  #define FAKE_build_setting_name_version_minor_prefix_s_length         20
  #define FAKE_build_setting_name_version_nano_s_length                 12
  #define FAKE_build_setting_name_version_nano_prefix_s_length          19
  #define FAKE_build_setting_name_version_target_s_length               14

  extern const f_string_static_t fake_build_setting_default_ar_s;
  extern const f_string_static_t fake_build_setting_default_gcc_s;
  extern const f_string_static_t fake_build_setting_default_version_s;
  extern const f_string_static_t fake_build_setting_default_version_prefix_s;
  extern const f_string_static_t fake_build_setting_default_yes_s;

  extern const f_string_static_t fake_build_setting_name_build_compiler_s;
  extern const f_string_static_t fake_build_setting_name_build_indexer_s;
  extern const f_string_static_t fake_build_setting_name_build_indexer_arguments_s;
  extern const f_string_static_t fake_build_setting_name_build_language_s;
  extern const f_string_static_t fake_build_setting_name_build_libraries_s;
  extern const f_string_static_t fake_build_setting_name_build_libraries_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_libraries_static_s;
  extern const f_string_static_t fake_build_setting_name_build_name_s;
  extern const f_string_static_t fake_build_setting_name_build_objects_library_s;
  extern const f_string_static_t fake_build_setting_name_build_objects_library_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_objects_library_static_s;
  extern const f_string_static_t fake_build_setting_name_build_objects_program_s;
  extern const f_string_static_t fake_build_setting_name_build_objects_program_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_objects_program_static_s;
  extern const f_string_static_t fake_build_setting_name_build_script_s;
  extern const f_string_static_t fake_build_setting_name_build_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_documentation_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_headers_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_headers_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_headers_static_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_library_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_library_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_library_static_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_object_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_object_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_object_static_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_program_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_program_shared_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_program_static_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_script_s;
  extern const f_string_static_t fake_build_setting_name_build_sources_setting_s;
  extern const f_string_static_t fake_build_setting_name_build_static_s;
  extern const f_string_static_t fake_build_setting_name_defines_s;
  extern const f_string_static_t fake_build_setting_name_defines_library_s;
  extern const f_string_static_t fake_build_setting_name_defines_library_shared_s;
  extern const f_string_static_t fake_build_setting_name_defines_library_static_s;
  extern const f_string_static_t fake_build_setting_name_defines_object_s;
  extern const f_string_static_t fake_build_setting_name_defines_object_shared_s;
  extern const f_string_static_t fake_build_setting_name_defines_object_static_s;
  extern const f_string_static_t fake_build_setting_name_defines_program_s;
  extern const f_string_static_t fake_build_setting_name_defines_program_shared_s;
  extern const f_string_static_t fake_build_setting_name_defines_program_static_s;
  extern const f_string_static_t fake_build_setting_name_defines_shared_s;
  extern const f_string_static_t fake_build_setting_name_defines_static_s;
  extern const f_string_static_t fake_build_setting_name_environment_s;
  extern const f_string_static_t fake_build_setting_name_flags_s;
  extern const f_string_static_t fake_build_setting_name_flags_library_s;
  extern const f_string_static_t fake_build_setting_name_flags_library_shared_s;
  extern const f_string_static_t fake_build_setting_name_flags_library_static_s;
  extern const f_string_static_t fake_build_setting_name_flags_object_s;
  extern const f_string_static_t fake_build_setting_name_flags_object_shared_s;
  extern const f_string_static_t fake_build_setting_name_flags_object_static_s;
  extern const f_string_static_t fake_build_setting_name_flags_program_s;
  extern const f_string_static_t fake_build_setting_name_flags_program_shared_s;
  extern const f_string_static_t fake_build_setting_name_flags_program_static_s;
  extern const f_string_static_t fake_build_setting_name_flags_shared_s;
  extern const f_string_static_t fake_build_setting_name_flags_static_s;
  extern const f_string_static_t fake_build_setting_name_has_path_standard_s;
  extern const f_string_static_t fake_build_setting_name_modes_s;
  extern const f_string_static_t fake_build_setting_name_modes_default_s;
  extern const f_string_static_t fake_build_setting_name_path_headers_s;
  extern const f_string_static_t fake_build_setting_name_path_language_s;
  extern const f_string_static_t fake_build_setting_name_path_library_script_s;
  extern const f_string_static_t fake_build_setting_name_path_library_shared_s;
  extern const f_string_static_t fake_build_setting_name_path_library_static_s;
  extern const f_string_static_t fake_build_setting_name_path_object_script_s;
  extern const f_string_static_t fake_build_setting_name_path_object_shared_s;
  extern const f_string_static_t fake_build_setting_name_path_object_static_s;
  extern const f_string_static_t fake_build_setting_name_path_program_script_s;
  extern const f_string_static_t fake_build_setting_name_path_program_shared_s;
  extern const f_string_static_t fake_build_setting_name_path_program_static_s;
  extern const f_string_static_t fake_build_setting_name_path_sources_s;
  extern const f_string_static_t fake_build_setting_name_path_sources_object_s;
  extern const f_string_static_t fake_build_setting_name_preserve_path_headers_s;
  extern const f_string_static_t fake_build_setting_name_process_post_s;
  extern const f_string_static_t fake_build_setting_name_process_pre_s;
  extern const f_string_static_t fake_build_setting_name_search_exclusive_s;
  extern const f_string_static_t fake_build_setting_name_search_shared_s;
  extern const f_string_static_t fake_build_setting_name_search_static_s;
  extern const f_string_static_t fake_build_setting_name_version_file_s;
  extern const f_string_static_t fake_build_setting_name_version_major_s;
  extern const f_string_static_t fake_build_setting_name_version_major_prefix_s;
  extern const f_string_static_t fake_build_setting_name_version_micro_s;
  extern const f_string_static_t fake_build_setting_name_version_micro_prefix_s;
  extern const f_string_static_t fake_build_setting_name_version_minor_s;
  extern const f_string_static_t fake_build_setting_name_version_minor_prefix_s;
  extern const f_string_static_t fake_build_setting_name_version_nano_s;
  extern const f_string_static_t fake_build_setting_name_version_nano_prefix_s;
  extern const f_string_static_t fake_build_setting_name_version_target_s;
#endif // _di_fake_build_setting_s_

#ifndef _di_fake_build_stage_s_
  #define FAKE_build_stage_built_s                 ".built"
  #define FAKE_build_stage_library_script_s        "library_script"
  #define FAKE_build_stage_library_shared_s        "library_shared"
  #define FAKE_build_stage_library_static_s        "library_static"
  #define FAKE_build_stage_object_script_s         "object_script"
  #define FAKE_build_stage_object_shared_s         "object_shared"
  #define FAKE_build_stage_object_static_s         "object_static"
  #define FAKE_build_stage_objects_static_s        "objects_static"
  #define FAKE_build_stage_process_post_s          "process_post"
  #define FAKE_build_stage_process_pre_s           "process_pre"
  #define FAKE_build_stage_program_script_s        "program_script"
  #define FAKE_build_stage_program_shared_s        "program_shared"
  #define FAKE_build_stage_program_static_s        "program_static"
  #define FAKE_build_stage_separate_s              "-"
  #define FAKE_build_stage_skeleton_s              "skeleton"
  #define FAKE_build_stage_sources_documentation_s "sources_documentation"
  #define FAKE_build_stage_sources_headers_s       "sources_headers"
  #define FAKE_build_stage_sources_script_s        "sources_script"
  #define FAKE_build_stage_sources_settings_s      "sources_settings"

  #define FAKE_build_stage_built_s_length                 6
  #define FAKE_build_stage_library_script_s_length        14
  #define FAKE_build_stage_library_shared_s_length        14
  #define FAKE_build_stage_library_static_s_length        14
  #define FAKE_build_stage_object_script_s_length         13
  #define FAKE_build_stage_object_shared_s_length         13
  #define FAKE_build_stage_object_static_s_length         13
  #define FAKE_build_stage_objects_static_s_length        14
  #define FAKE_build_stage_process_post_s_length          12
  #define FAKE_build_stage_process_pre_s_length           11
  #define FAKE_build_stage_program_script_s_length        14
  #define FAKE_build_stage_program_shared_s_length        14
  #define FAKE_build_stage_program_static_s_length        14
  #define FAKE_build_stage_separate_s_length              1
  #define FAKE_build_stage_skeleton_s_length              8
  #define FAKE_build_stage_sources_documentation_s_length 21
  #define FAKE_build_stage_sources_headers_s_length       15
  #define FAKE_build_stage_sources_script_s_length        14
  #define FAKE_build_stage_sources_settings_s_length      16

  extern const f_string_static_t fake_build_stage_built_s;
  extern const f_string_static_t fake_build_stage_library_script_s;
  extern const f_string_static_t fake_build_stage_library_shared_s;
  extern const f_string_static_t fake_build_stage_library_static_s;
  extern const f_string_static_t fake_build_stage_object_script_s;
  extern const f_string_static_t fake_build_stage_object_shared_s;
  extern const f_string_static_t fake_build_stage_object_static_s;
  extern const f_string_static_t fake_build_stage_objects_static_s;
  extern const f_string_static_t fake_build_stage_process_post_s;
  extern const f_string_static_t fake_build_stage_process_pre_s;
  extern const f_string_static_t fake_build_stage_program_script_s;
  extern const f_string_static_t fake_build_stage_program_shared_s;
  extern const f_string_static_t fake_build_stage_program_static_s;
  extern const f_string_static_t fake_build_stage_separate_s;
  extern const f_string_static_t fake_build_stage_skeleton_s;
  extern const f_string_static_t fake_build_stage_sources_documentation_s;
  extern const f_string_static_t fake_build_stage_sources_headers_s;
  extern const f_string_static_t fake_build_stage_sources_script_s;
  extern const f_string_static_t fake_build_stage_sources_settings_s;
#endif // _di_fake_build_stage_s_

#ifndef _di_fake_build_parameter_s_
  #define FAKE_build_parameter_library_include_s            "-I"
  #define FAKE_build_parameter_library_link_file_s          "-l"
  #define FAKE_build_parameter_library_link_path_s          "-L"
  #define FAKE_build_parameter_library_name_prefix_s        "lib"
  #define FAKE_build_parameter_library_name_suffix_shared_s ".so"
  #define FAKE_build_parameter_library_name_suffix_static_s ".a"
  #define FAKE_build_parameter_library_output_s             "-o"
  #define FAKE_build_parameter_library_shared_s             "-shared"
  #define FAKE_build_parameter_library_static_s             "-static"
  #define FAKE_build_parameter_library_shared_prefix_s      "-Wl,-soname,"

  #define FAKE_build_parameter_library_include_s_length            2
  #define FAKE_build_parameter_library_link_file_s_length          2
  #define FAKE_build_parameter_library_link_path_s_length          2
  #define FAKE_build_parameter_library_name_prefix_s_length        3
  #define FAKE_build_parameter_library_name_suffix_shared_s_length 3
  #define FAKE_build_parameter_library_name_suffix_static_s_length 2
  #define FAKE_build_parameter_library_output_s_length             2
  #define FAKE_build_parameter_library_shared_s_length             7
  #define FAKE_build_parameter_library_static_s_length             7
  #define FAKE_build_parameter_library_shared_prefix_s_length      12

  extern const f_string_static_t fake_build_parameter_library_include_s;
  extern const f_string_static_t fake_build_parameter_library_link_file_s;
  extern const f_string_static_t fake_build_parameter_library_link_path_s;
  extern const f_string_static_t fake_build_parameter_library_name_prefix_s;
  extern const f_string_static_t fake_build_parameter_library_name_suffix_shared_s;
  extern const f_string_static_t fake_build_parameter_library_name_suffix_static_s;
  extern const f_string_static_t fake_build_parameter_library_output_s;
  extern const f_string_static_t fake_build_parameter_library_shared_s;
  extern const f_string_static_t fake_build_parameter_library_static_s;
  extern const f_string_static_t fake_build_parameter_library_shared_prefix_s;

  #define FAKE_build_parameter_object_compile_s     "-c"
  #define FAKE_build_parameter_object_name_suffix_s ".o"
  #define FAKE_build_parameter_object_output_s      "-o"
  #define FAKE_build_parameter_object_static_s      "-static"

  #define FAKE_build_parameter_object_compile_s_length     2
  #define FAKE_build_parameter_object_name_suffix_s_length 2
  #define FAKE_build_parameter_object_output_s_length      2
  #define FAKE_build_parameter_object_static_s_length      7

  extern const f_string_static_t fake_build_parameter_object_compile_s;
  extern const f_string_static_t fake_build_parameter_object_name_suffix_s;
  extern const f_string_static_t fake_build_parameter_object_output_s;
  extern const f_string_static_t fake_build_parameter_object_static_s;
#endif // _di_fake_build_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_string_h

/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_string_h
#define _fake_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fake_program_version_s_
  #define FAKE_program_version_major_s F_string_ascii_0_s
  #define FAKE_program_version_minor_s F_string_ascii_7_s
  #define FAKE_program_version_micro_s F_string_ascii_0_s

  #define FAKE_program_version_major_s_length F_string_ascii_0_s_length
  #define FAKE_program_version_minor_s_length F_string_ascii_7_s_length
  #define FAKE_program_version_micro_s_length F_string_ascii_0_s_length

  #ifndef FAKE_program_version_nano_prefix_s
    #define FAKE_program_version_nano_prefix_s
    #define FAKE_program_version_nano_prefix_s_length 0
  #endif // FAKE_program_version_major_s_length F_string_ascii_0_s_length

  #ifndef FAKE_program_version_nano_s
    #define FAKE_program_version_nano_s
    #define FAKE_program_version_nano_s_length 0
  #endif // FAKE_program_version_nano_s

  #define FAKE_program_version_s FAKE_program_version_major_s F_string_ascii_period_s FAKE_program_version_minor_s F_string_ascii_period_s FAKE_program_version_micro_s FAKE_program_version_nano_prefix_s FAKE_program_version_nano_s

  #define FAKE_program_version_s_length FAKE_program_version_major_s_length + F_string_ascii_period_s_length + FAKE_program_version_minor_s_length + F_string_ascii_period_s_length + FAKE_program_version_micro_s_length + FAKE_program_version_nano_prefix_s_length + FAKE_program_version_nano_s_length

  extern const f_string_static_t fake_program_version_s;
#endif // _di_fake_program_version_s_

/**
 * The program name.
 */
#ifndef _di_fake_program_name_s_
  #define FAKE_program_name_s      "fake"
  #define FAKE_program_name_long_s "Featureless Make"

  #define FAKE_program_name_s_length      4
  #define FAKE_program_name_long_s_length 16

  extern const f_string_static_t fake_program_name_s;
  extern const f_string_static_t fake_program_name_long_s;
#endif // _di_fake_program_name_s_

/**
 * The program help related data.
 */
#ifndef _di_fake_program_help_parameter_s_
  #define FAKE_program_help_parameters_s "operation / section"

  #define FAKE_program_help_parameters_s_length 19

  extern const f_string_static_t fake_program_help_parameters_s;
#endif // _di_fake_program_help_parameter_s_

/**
 * The build operation utilizes pre-defined path structures.
 * These structures are hard-coded by their individual pieces to be constructed later on.
 */
#ifndef _di_fake_path_s_
  #define FAKE_path_part_build_s          "build"          F_path_separator_s
  #define FAKE_path_part_c_s              "c"              F_path_separator_s
  #define FAKE_path_part_cpp_s            "c++"            F_path_separator_s
  #define FAKE_path_part_data_s           "data"           F_path_separator_s
  #define FAKE_path_part_documentation_s  "documentation"  F_path_separator_s
  #define FAKE_path_part_documents_s      "documents"      F_path_separator_s
  #define FAKE_path_part_includes_s       "includes"       F_path_separator_s
  #define FAKE_path_part_libraries_s      "libraries"      F_path_separator_s
  #define FAKE_path_part_licenses_s       "licenses"       F_path_separator_s
  #define FAKE_path_part_objects_s        "objects"        F_path_separator_s
  #define FAKE_path_part_process_s        "process"        F_path_separator_s
  #define FAKE_path_part_programs_s       "programs"       F_path_separator_s
  #define FAKE_path_part_script_s         "script"         F_path_separator_s
  #define FAKE_path_part_settings_s       "settings"       F_path_separator_s
  #define FAKE_path_part_shared_s         "shared"         F_path_separator_s
  #define FAKE_path_part_shell_s          "shell"          F_path_separator_s
  #define FAKE_path_part_specifications_s "specifications" F_path_separator_s
  #define FAKE_path_part_stage_s          "stage"          F_path_separator_s
  #define FAKE_path_part_static_s         "static"         F_path_separator_s

  #define FAKE_path_part_build_s_length          5 + F_path_separator_s_length
  #define FAKE_path_part_c_s_length              1 + F_path_separator_s_length
  #define FAKE_path_part_cpp_s_length            3 + F_path_separator_s_length
  #define FAKE_path_part_data_s_length           4 + F_path_separator_s_length
  #define FAKE_path_part_documentation_s_length  13 + F_path_separator_s_length
  #define FAKE_path_part_documents_s_length      9 + F_path_separator_s_length
  #define FAKE_path_part_includes_s_length       8 + F_path_separator_s_length
  #define FAKE_path_part_libraries_s_length      9 + F_path_separator_s_length
  #define FAKE_path_part_licenses_s_length       8 + F_path_separator_s_length
  #define FAKE_path_part_objects_s_length        7 + F_path_separator_s_length
  #define FAKE_path_part_process_s_length        7 + F_path_separator_s_length
  #define FAKE_path_part_programs_s_length       8 + F_path_separator_s_length
  #define FAKE_path_part_script_s_length         6 + F_path_separator_s_length
  #define FAKE_path_part_settings_s_length       8 + F_path_separator_s_length
  #define FAKE_path_part_shared_s_length         6 + F_path_separator_s_length
  #define FAKE_path_part_shell_s_length          5 + F_path_separator_s_length
  #define FAKE_path_part_specifications_s_length 14 + F_path_separator_s_length
  #define FAKE_path_part_stage_s_length          5 + F_path_separator_s_length
  #define FAKE_path_part_static_s_length         6 + F_path_separator_s_length

  extern const f_string_static_t fake_path_part_build_s;
  extern const f_string_static_t fake_path_part_c_s;
  extern const f_string_static_t fake_path_part_cpp_s;
  extern const f_string_static_t fake_path_part_data_s;
  extern const f_string_static_t fake_path_part_documentation_s;
  extern const f_string_static_t fake_path_part_documents_s;
  extern const f_string_static_t fake_path_part_includes_s;
  extern const f_string_static_t fake_path_part_libraries_s;
  extern const f_string_static_t fake_path_part_licenses_s;
  extern const f_string_static_t fake_path_part_objects_s;
  extern const f_string_static_t fake_path_part_process_s;
  extern const f_string_static_t fake_path_part_programs_s;
  extern const f_string_static_t fake_path_part_script_s;
  extern const f_string_static_t fake_path_part_settings_s;
  extern const f_string_static_t fake_path_part_shared_s;
  extern const f_string_static_t fake_path_part_shell_s;
  extern const f_string_static_t fake_path_part_specifications_s;
  extern const f_string_static_t fake_path_part_stage_s;
  extern const f_string_static_t fake_path_part_static_s;
#endif // _di_fake_path_s_

/**
 * The file settings.
 */
#ifndef _di_fake_file_s_
  #define FAKE_file_defines_s      "defines"
  #define FAKE_file_dependencies_s "dependencies"
  #define FAKE_file_process_pre_s  "process_pre.sh"
  #define FAKE_file_process_post_s "process_post.sh"
  #define FAKE_file_readme_s       "readme.txt"

  #define FAKE_file_defines_s_length      7
  #define FAKE_file_dependencies_s_length 12
  #define FAKE_file_process_pre_s_length  14
  #define FAKE_file_process_post_s_length 15
  #define FAKE_file_readme_s_length       10

  extern const f_string_static_t fake_file_defines_s;
  extern const f_string_static_t fake_file_dependencies_s;
  extern const f_string_static_t fake_file_process_pre_s;
  extern const f_string_static_t fake_file_process_post_s;
  extern const f_string_static_t fake_file_readme_s;
#endif // _di_fake_file_s_

/**
 * Provide default settings.
 */
#ifndef _di_fake_default_s_
  #define FAKE_default_build_s     "build"     F_path_separator_s
  #define FAKE_default_data_s      "data"      F_path_separator_s
  #define FAKE_default_documents_s "documents" F_path_separator_s
  #define FAKE_default_fakefile_s  "fakefile"
  #define FAKE_default_licenses_s  "licenses"  F_path_separator_s
  #define FAKE_default_process_s   ""
  #define FAKE_default_settings_s  "settings"
  #define FAKE_default_sources_s   "sources"   F_path_separator_s
  #define FAKE_default_work_s      ""

  #define FAKE_default_build_s_length     5 + F_path_separator_s_length
  #define FAKE_default_data_s_length      4 + F_path_separator_s_length
  #define FAKE_default_documents_s_length 9 + F_path_separator_s_length
  #define FAKE_default_fakefile_s_length  8
  #define FAKE_default_licenses_s_length  8 + F_path_separator_s_length
  #define FAKE_default_process_s_length   0
  #define FAKE_default_settings_s_length  8
  #define FAKE_default_sources_s_length   7 + F_path_separator_s_length
  #define FAKE_default_work_s_length      0

  extern const f_string_static_t fake_default_build_s;
  extern const f_string_static_t fake_default_data_s;
  extern const f_string_static_t fake_default_documents_s;
  extern const f_string_static_t fake_default_fakefile_s;
  extern const f_string_static_t fake_default_licenses_s;
  extern const f_string_static_t fake_default_process_s;
  extern const f_string_static_t fake_default_settings_s;
  extern const f_string_static_t fake_default_sources_s;
  extern const f_string_static_t fake_default_work_s;
#endif // _di_fake_default_s_

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

/**
 * The main program parameters.
 */
#ifndef _di_fake_parameter_s_
  #define FAKE_short_build_s     "b"
  #define FAKE_short_data_s      "D"
  #define FAKE_short_define_s    "d"
  #define FAKE_short_documents_s "O"
  #define FAKE_short_fakefile_s  "f"
  #define FAKE_short_licenses_s  "l"
  #define FAKE_short_mode_s      "m"
  #define FAKE_short_process_s   "p"
  #define FAKE_short_settings_s  "s"
  #define FAKE_short_sources_s   "S"
  #define FAKE_short_work_s      "w"

  #define FAKE_long_build_s     "build"
  #define FAKE_long_data_s      "data"
  #define FAKE_long_define_s    "define"
  #define FAKE_long_documents_s "documents"
  #define FAKE_long_fakefile_s  "fakefile"
  #define FAKE_long_licenses_s  "licenses"
  #define FAKE_long_mode_s      "mode"
  #define FAKE_long_process_s   "process"
  #define FAKE_long_settings_s  "settings"
  #define FAKE_long_sources_s   "sources"
  #define FAKE_long_work_s      "work"

  // These special parameters are provided in such a way that they mimic the traditional ./configure script.
  #define FAKE_long_documents_disabled_s "disable-doc"
  #define FAKE_long_documents_enabled_s  "enable-doc"
  #define FAKE_long_shared_disabled_s    "disable-shared"
  #define FAKE_long_shared_enabled_s     "enable-shared"
  #define FAKE_long_static_disabled_s    "disable-static"
  #define FAKE_long_static_enabled_s     "enable-static"

  #define FAKE_other_operation_build_s    "build"
  #define FAKE_other_operation_clean_s    "clean"
  #define FAKE_other_operation_make_s     "make"
  #define FAKE_other_operation_skeleton_s "skeleton"

  #define FAKE_short_build_s_length     1
  #define FAKE_short_data_s_length      1
  #define FAKE_short_define_s_length    1
  #define FAKE_short_documents_s_length 1
  #define FAKE_short_fakefile_s_length  1
  #define FAKE_short_licenses_s_length  1
  #define FAKE_short_mode_s_length      1
  #define FAKE_short_process_s_length   1
  #define FAKE_short_settings_s_length  1
  #define FAKE_short_sources_s_length   1
  #define FAKE_short_work_s_length      1

  #define FAKE_long_build_s_length     5
  #define FAKE_long_data_s_length      4
  #define FAKE_long_define_s_length    6
  #define FAKE_long_documents_s_length 9
  #define FAKE_long_fakefile_s_length  8
  #define FAKE_long_licenses_s_length  8
  #define FAKE_long_mode_s_length      4
  #define FAKE_long_process_s_length   7
  #define FAKE_long_settings_s_length  8
  #define FAKE_long_sources_s_length   7
  #define FAKE_long_work_s_length      4

  #define FAKE_long_documents_disabled_s_length 11
  #define FAKE_long_documents_enabled_s_length  10
  #define FAKE_long_shared_disabled_s_length    14
  #define FAKE_long_shared_enabled_s_length     13
  #define FAKE_long_static_disabled_s_length    14
  #define FAKE_long_static_enabled_s_length     13

  #define FAKE_other_operation_build_s_length    5
  #define FAKE_other_operation_clean_s_length    5
  #define FAKE_other_operation_make_s_length     4
  #define FAKE_other_operation_skeleton_s_length 8

  extern const f_string_static_t fake_short_build_s;
  extern const f_string_static_t fake_short_data_s;
  extern const f_string_static_t fake_short_define_s;
  extern const f_string_static_t fake_short_documents_s;
  extern const f_string_static_t fake_short_fakefile_s;
  extern const f_string_static_t fake_short_licenses_s;
  extern const f_string_static_t fake_short_mode_s;
  extern const f_string_static_t fake_short_process_s;
  extern const f_string_static_t fake_short_settings_s;
  extern const f_string_static_t fake_short_sources_s;
  extern const f_string_static_t fake_short_work_s;

  extern const f_string_static_t fake_long_build_s;
  extern const f_string_static_t fake_long_data_s;
  extern const f_string_static_t fake_long_define_s;
  extern const f_string_static_t fake_long_documents_s;
  extern const f_string_static_t fake_long_fakefile_s;
  extern const f_string_static_t fake_long_licenses_s;
  extern const f_string_static_t fake_long_mode_s;
  extern const f_string_static_t fake_long_process_s;
  extern const f_string_static_t fake_long_settings_s;
  extern const f_string_static_t fake_long_sources_s;
  extern const f_string_static_t fake_long_work_s;

  extern const f_string_static_t fake_long_documents_disabled_s;
  extern const f_string_static_t fake_long_documents_enabled_s;
  extern const f_string_static_t fake_long_shared_disabled_s;
  extern const f_string_static_t fake_long_shared_enabled_s;
  extern const f_string_static_t fake_long_static_disabled_s;
  extern const f_string_static_t fake_long_static_enabled_s;

  extern const f_string_static_t fake_other_operation_build_s;
  extern const f_string_static_t fake_other_operation_clean_s;
  extern const f_string_static_t fake_other_operation_make_s;
  extern const f_string_static_t fake_other_operation_skeleton_s;
#endif // _di_fake_parameter_s_

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

#ifndef _di_fake_common_s_
  #define FAKE_common_file_directory_copy_s      "copy directory"
  #define FAKE_common_file_path_access_s         "access"
  #define FAKE_common_file_path_change_to_s      "change path to"
  #define FAKE_common_file_path_determine_real_s "determine real path of"
  #define FAKE_common_file_path_stack_s          "path stack"
  #define FAKE_common_file_populate_pre_s        "pre-populate"

  #define FAKE_common_setting_bool_yes_s "yes"
  #define FAKE_common_setting_bool_no_s  "no"

  #define FAKE_common_setting_list_s "list"

  #define FAKE_common_file_directory_copy_s_length      14
  #define FAKE_common_file_path_access_s_length         6
  #define FAKE_common_file_path_change_to_s_length      14
  #define FAKE_common_file_path_determine_real_s_length 22
  #define FAKE_common_file_path_stack_s_length          10
  #define FAKE_common_file_populate_pre_s_length        12

  #define FAKE_common_setting_bool_yes_s_length 3
  #define FAKE_common_setting_bool_no_s_length  2

  #define FAKE_common_setting_list_s_length 4

  extern const f_string_static_t fake_common_file_directory_copy_s;
  extern const f_string_static_t fake_common_file_path_access_s;
  extern const f_string_static_t fake_common_file_path_change_to_s;
  extern const f_string_static_t fake_common_file_path_determine_real_s;
  extern const f_string_static_t fake_common_file_path_stack_s;
  extern const f_string_static_t fake_common_file_populate_pre_s;

  extern const f_string_static_t fake_common_setting_bool_yes_s;
  extern const f_string_static_t fake_common_setting_bool_no_s;

  extern const f_string_static_t fake_common_setting_list_s;
#endif // _di_fake_common_s_

#ifndef _di_fake_make_section_s_
  #define FAKE_make_section_main_s     "main"
  #define FAKE_make_section_settings_s "settings"

  #define FAKE_make_section_main_s_length     4
  #define FAKE_make_section_settings_s_length 8

  extern const f_string_static_t fake_make_section_main_s;
  extern const f_string_static_t fake_make_section_settings_s;
#endif // _di_fake_make_section_s_

#ifndef _di_fake_make_setting_s_
  #define FAKE_make_setting_compiler_s          "compiler"
  #define FAKE_make_setting_define_s            "define"
  #define FAKE_make_setting_environment_s       "environment"
  #define FAKE_make_setting_fail_s              "fail"
  #define FAKE_make_setting_indexer_s           "indexer"
  #define FAKE_make_setting_indexer_arguments_s "indexer_arguments"
  #define FAKE_make_setting_load_build_s        "load_build"
  #define FAKE_make_setting_parameter_s         "parameter"
  #define FAKE_make_setting_return_s            "return"

  #define FAKE_make_setting_compiler_s_length          8
  #define FAKE_make_setting_define_s_length            6
  #define FAKE_make_setting_environment_s_length       11
  #define FAKE_make_setting_fail_s_length              4
  #define FAKE_make_setting_indexer_s_length           7
  #define FAKE_make_setting_indexer_arguments_s_length 17
  #define FAKE_make_setting_load_build_s_length        10
  #define FAKE_make_setting_parameter_s_length         9
  #define FAKE_make_setting_return_s_length            6

  extern const f_string_static_t fake_make_setting_compiler_s;
  extern const f_string_static_t fake_make_setting_define_s;
  extern const f_string_static_t fake_make_setting_environment_s;
  extern const f_string_static_t fake_make_setting_fail_s;
  extern const f_string_static_t fake_make_setting_indexer_s;
  extern const f_string_static_t fake_make_setting_indexer_arguments_s;
  extern const f_string_static_t fake_make_setting_load_build_s;
  extern const f_string_static_t fake_make_setting_parameter_s;
  extern const f_string_static_t fake_make_setting_return_s;
#endif // _di_fake_make_setting_s_

#ifndef _di_fake_make_operation_s_
  #define FAKE_make_operation_and_s       "and"
  #define FAKE_make_operation_break_s     "break"
  #define FAKE_make_operation_build_s     "build"
  #define FAKE_make_operation_clean_s     "clean"
  #define FAKE_make_operation_clone_s     "clone"
  #define FAKE_make_operation_compile_s   "compile"
  #define FAKE_make_operation_copy_s      "copy"
  #define FAKE_make_operation_define_s    "define"
  #define FAKE_make_operation_delete_s    "delete"
  #define FAKE_make_operation_deletes_s   "deletes"
  #define FAKE_make_operation_else_s      "else"
  #define FAKE_make_operation_exit_s      "exit"
  #define FAKE_make_operation_fail_s      "fail"
  #define FAKE_make_operation_group_s     "group"
  #define FAKE_make_operation_groups_s    "groups"
  #define FAKE_make_operation_if_s        "if"
  #define FAKE_make_operation_index_s     "index"
  #define FAKE_make_operation_link_s      "link"
  #define FAKE_make_operation_mode_s      "mode"
  #define FAKE_make_operation_modes_s     "modes"
  #define FAKE_make_operation_move_s      "move"
  #define FAKE_make_operation_operate_s   "operate"
  #define FAKE_make_operation_or_s        "or"
  #define FAKE_make_operation_owner_s     "owner"
  #define FAKE_make_operation_owners_s    "owners"
  #define FAKE_make_operation_parameter_s "parameter"
  #define FAKE_make_operation_pop_s       "pop"
  #define FAKE_make_operation_print_s     "print"
  #define FAKE_make_operation_run_s       "run"
  #define FAKE_make_operation_shell_s     "shell"
  #define FAKE_make_operation_skeleton_s  "skeleton"
  #define FAKE_make_operation_to_s        "to"
  #define FAKE_make_operation_top_s       "top"
  #define FAKE_make_operation_touch_s     "touch"
  #define FAKE_make_operation_write_s     "write"

  #define FAKE_make_operation_and_s_length       3
  #define FAKE_make_operation_break_s_length     5
  #define FAKE_make_operation_build_s_length     5
  #define FAKE_make_operation_clean_s_length     5
  #define FAKE_make_operation_clone_s_length     5
  #define FAKE_make_operation_compile_s_length   7
  #define FAKE_make_operation_copy_s_length      4
  #define FAKE_make_operation_define_s_length    6
  #define FAKE_make_operation_delete_s_length    6
  #define FAKE_make_operation_deletes_s_length   7
  #define FAKE_make_operation_else_s_length      4
  #define FAKE_make_operation_exit_s_length      4
  #define FAKE_make_operation_fail_s_length      4
  #define FAKE_make_operation_group_s_length     5
  #define FAKE_make_operation_groups_s_length    6
  #define FAKE_make_operation_if_s_length        2
  #define FAKE_make_operation_index_s_length     5
  #define FAKE_make_operation_link_s_length      4
  #define FAKE_make_operation_mode_s_length      4
  #define FAKE_make_operation_modes_s_length     5
  #define FAKE_make_operation_move_s_length      4
  #define FAKE_make_operation_operate_s_length   7
  #define FAKE_make_operation_or_s_length        2
  #define FAKE_make_operation_owner_s_length     5
  #define FAKE_make_operation_owners_s_length    6
  #define FAKE_make_operation_parameter_s_length 9
  #define FAKE_make_operation_pop_s_length       3
  #define FAKE_make_operation_print_s_length     5
  #define FAKE_make_operation_run_s_length       3
  #define FAKE_make_operation_shell_s_length     5
  #define FAKE_make_operation_skeleton_s_length  8
  #define FAKE_make_operation_to_s_length        2
  #define FAKE_make_operation_top_s_length       3
  #define FAKE_make_operation_touch_s_length     5
  #define FAKE_make_operation_write_s_length     5

  extern const f_string_static_t fake_make_operation_and_s;
  extern const f_string_static_t fake_make_operation_break_s;
  extern const f_string_static_t fake_make_operation_build_s;
  extern const f_string_static_t fake_make_operation_clean_s;
  extern const f_string_static_t fake_make_operation_clone_s;
  extern const f_string_static_t fake_make_operation_compile_s;
  extern const f_string_static_t fake_make_operation_copy_s;
  extern const f_string_static_t fake_make_operation_define_s;
  extern const f_string_static_t fake_make_operation_delete_s;
  extern const f_string_static_t fake_make_operation_deletes_s;
  extern const f_string_static_t fake_make_operation_else_s;
  extern const f_string_static_t fake_make_operation_exit_s;
  extern const f_string_static_t fake_make_operation_fail_s;
  extern const f_string_static_t fake_make_operation_group_s;
  extern const f_string_static_t fake_make_operation_groups_s;
  extern const f_string_static_t fake_make_operation_if_s;
  extern const f_string_static_t fake_make_operation_index_s;
  extern const f_string_static_t fake_make_operation_link_s;
  extern const f_string_static_t fake_make_operation_mode_s;
  extern const f_string_static_t fake_make_operation_modes_s;
  extern const f_string_static_t fake_make_operation_move_s;
  extern const f_string_static_t fake_make_operation_operate_s;
  extern const f_string_static_t fake_make_operation_or_s;
  extern const f_string_static_t fake_make_operation_owner_s;
  extern const f_string_static_t fake_make_operation_owners_s;
  extern const f_string_static_t fake_make_operation_parameter_s;
  extern const f_string_static_t fake_make_operation_pop_s;
  extern const f_string_static_t fake_make_operation_print_s;
  extern const f_string_static_t fake_make_operation_run_s;
  extern const f_string_static_t fake_make_operation_shell_s;
  extern const f_string_static_t fake_make_operation_skeleton_s;
  extern const f_string_static_t fake_make_operation_to_s;
  extern const f_string_static_t fake_make_operation_top_s;
  extern const f_string_static_t fake_make_operation_touch_s;
  extern const f_string_static_t fake_make_operation_write_s;

  #define FAKE_make_operation_argument_directory_s      "directory"
  #define FAKE_make_operation_argument_environment_s    "environment"
  #define FAKE_make_operation_argument_error_s          "error"
  #define FAKE_make_operation_argument_exit_s           "exit"
  #define FAKE_make_operation_argument_failure_s        "failure"
  #define FAKE_make_operation_argument_file_s           "file"
  #define FAKE_make_operation_argument_force_s          "force"
  #define FAKE_make_operation_argument_has_s            "has"
  #define FAKE_make_operation_argument_ignore_s         "ignore"
  #define FAKE_make_operation_argument_is_s             "is"
  #define FAKE_make_operation_argument_no_dereference_s "no_dereference"
  #define FAKE_make_operation_argument_parameter_s      "parameter"
  #define FAKE_make_operation_argument_point_s          "point"
  #define FAKE_make_operation_argument_recursive_s      "recursive"
  #define FAKE_make_operation_argument_strict_s         "strict"
  #define FAKE_make_operation_argument_success_s        "success"
  #define FAKE_make_operation_argument_target_s         "target"
  #define FAKE_make_operation_argument_warn_s           "warn"

  #define FAKE_make_operation_argument_directory_s_length      9
  #define FAKE_make_operation_argument_environment_s_length    11
  #define FAKE_make_operation_argument_error_s_length          5
  #define FAKE_make_operation_argument_exit_s_length           4
  #define FAKE_make_operation_argument_failure_s_length        7
  #define FAKE_make_operation_argument_file_s_length           4
  #define FAKE_make_operation_argument_force_s_length          5
  #define FAKE_make_operation_argument_has_s_length            3
  #define FAKE_make_operation_argument_ignore_s_length         6
  #define FAKE_make_operation_argument_is_s_length             2
  #define FAKE_make_operation_argument_no_dereference_s_length 14
  #define FAKE_make_operation_argument_parameter_s_length      9
  #define FAKE_make_operation_argument_point_s_length          5
  #define FAKE_make_operation_argument_recursive_s_length      9
  #define FAKE_make_operation_argument_strict_s_length         6
  #define FAKE_make_operation_argument_success_s_length        7
  #define FAKE_make_operation_argument_target_s_length         6
  #define FAKE_make_operation_argument_warn_s_length           4

  extern const f_string_static_t fake_make_operation_argument_directory_s;
  extern const f_string_static_t fake_make_operation_argument_environment_s;
  extern const f_string_static_t fake_make_operation_argument_error_s;
  extern const f_string_static_t fake_make_operation_argument_exit_s;
  extern const f_string_static_t fake_make_operation_argument_failure_s;
  extern const f_string_static_t fake_make_operation_argument_file_s;
  extern const f_string_static_t fake_make_operation_argument_force_s;
  extern const f_string_static_t fake_make_operation_argument_has_s;
  extern const f_string_static_t fake_make_operation_argument_ignore_s;
  extern const f_string_static_t fake_make_operation_argument_is_s;
  extern const f_string_static_t fake_make_operation_argument_no_dereference_s;
  extern const f_string_static_t fake_make_operation_argument_parameter_s;
  extern const f_string_static_t fake_make_operation_argument_point_s;
  extern const f_string_static_t fake_make_operation_argument_recursive_s;
  extern const f_string_static_t fake_make_operation_argument_strict_s;
  extern const f_string_static_t fake_make_operation_argument_success_s;
  extern const f_string_static_t fake_make_operation_argument_target_s;
  extern const f_string_static_t fake_make_operation_argument_warn_s;

  #define FAKE_make_operation_argument_if_define_s        "define"
  #define FAKE_make_operation_argument_if_equal_s         "=="
  #define FAKE_make_operation_argument_if_equal_not_s     "<>"
  #define FAKE_make_operation_argument_if_exist_s         "exist"
  #define FAKE_make_operation_argument_if_failure_s       "failure"
  #define FAKE_make_operation_argument_if_greater_s       ">"
  #define FAKE_make_operation_argument_if_greater_equal_s ">="
  #define FAKE_make_operation_argument_if_group_s         "group"
  #define FAKE_make_operation_argument_if_is_s            "is"
  #define FAKE_make_operation_argument_if_is_for_s        "for"
  #define FAKE_make_operation_argument_if_less_s          "<"
  #define FAKE_make_operation_argument_if_less_equal_s    "<="
  #define FAKE_make_operation_argument_if_mode_s          "mode"
  #define FAKE_make_operation_argument_if_not_s           "not"
  #define FAKE_make_operation_argument_if_owner_s         "owner"
  #define FAKE_make_operation_argument_if_parameter_s     "parameter"
  #define FAKE_make_operation_argument_if_success_s       "success"

  #define FAKE_make_operation_argument_if_define_s_length        6
  #define FAKE_make_operation_argument_if_equal_s_length         2
  #define FAKE_make_operation_argument_if_equal_not_s_length     2
  #define FAKE_make_operation_argument_if_exist_s_length         5
  #define FAKE_make_operation_argument_if_failure_s_length       7
  #define FAKE_make_operation_argument_if_greater_s_length       1
  #define FAKE_make_operation_argument_if_greater_equal_s_length 2
  #define FAKE_make_operation_argument_if_group_s_length         5
  #define FAKE_make_operation_argument_if_is_s_length            2
  #define FAKE_make_operation_argument_if_is_for_s_length        3
  #define FAKE_make_operation_argument_if_less_s_length          1
  #define FAKE_make_operation_argument_if_less_equal_s_length    2
  #define FAKE_make_operation_argument_if_mode_s_length          4
  #define FAKE_make_operation_argument_if_not_s_length           3
  #define FAKE_make_operation_argument_if_owner_s_length         5
  #define FAKE_make_operation_argument_if_parameter_s_length     9
  #define FAKE_make_operation_argument_if_success_s_length       7

  extern const f_string_static_t fake_make_operation_argument_if_define_s;
  extern const f_string_static_t fake_make_operation_argument_if_equal_s;
  extern const f_string_static_t fake_make_operation_argument_if_equal_not_s;
  extern const f_string_static_t fake_make_operation_argument_if_exist_s;
  extern const f_string_static_t fake_make_operation_argument_if_failure_s;
  extern const f_string_static_t fake_make_operation_argument_if_greater_s;
  extern const f_string_static_t fake_make_operation_argument_if_greater_equal_s;
  extern const f_string_static_t fake_make_operation_argument_if_group_s;
  extern const f_string_static_t fake_make_operation_argument_if_is_s;
  extern const f_string_static_t fake_make_operation_argument_if_is_for_s;
  extern const f_string_static_t fake_make_operation_argument_if_less_s;
  extern const f_string_static_t fake_make_operation_argument_if_less_equal_s;
  extern const f_string_static_t fake_make_operation_argument_if_mode_s;
  extern const f_string_static_t fake_make_operation_argument_if_not_s;
  extern const f_string_static_t fake_make_operation_argument_if_owner_s;
  extern const f_string_static_t fake_make_operation_argument_if_parameter_s;
  extern const f_string_static_t fake_make_operation_argument_if_success_s;
#endif // _di_fake_make_operation_s_

#ifndef _di_fake_make_parameter_s_
  #define FAKE_make_parameter_iki_option_s ":option"
  #define FAKE_make_parameter_iki_value_s  ":value"

  #define FAKE_make_parameter_variable_build_s     "build"
  #define FAKE_make_parameter_variable_color_s     "color"
  #define FAKE_make_parameter_variable_current_s   "current"
  #define FAKE_make_parameter_variable_data_s      "data"
  #define FAKE_make_parameter_variable_define_s    "define"
  #define FAKE_make_parameter_variable_documents_s "documents"
  #define FAKE_make_parameter_variable_fakefile_s  "fakefile"
  #define FAKE_make_parameter_variable_licenses_s  "licenses"
  #define FAKE_make_parameter_variable_mode_s      "mode"
  #define FAKE_make_parameter_variable_process_s   "process"
  #define FAKE_make_parameter_variable_return_s    "return"
  #define FAKE_make_parameter_variable_settings_s  "settings"
  #define FAKE_make_parameter_variable_sources_s   "sources"
  #define FAKE_make_parameter_variable_top_s       "top"
  #define FAKE_make_parameter_variable_verbosity_s "verbosity"
  #define FAKE_make_parameter_variable_work_s      "work"

  #define FAKE_make_parameter_variable_option_build_s     FAKE_make_parameter_variable_build_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_color_s     FAKE_make_parameter_variable_color_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_data_s      FAKE_make_parameter_variable_data_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_define_s    FAKE_make_parameter_variable_define_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_documents_s FAKE_make_parameter_variable_documents_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_fakefile_s  FAKE_make_parameter_variable_fakefile_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_licenses_s  FAKE_make_parameter_variable_licenses_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_mode_s      FAKE_make_parameter_variable_mode_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_process_s   FAKE_make_parameter_variable_process_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_settings_s  FAKE_make_parameter_variable_settings_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_sources_s   FAKE_make_parameter_variable_sources_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_verbosity_s FAKE_make_parameter_variable_verbosity_s FAKE_make_parameter_iki_option_s
  #define FAKE_make_parameter_variable_option_work_s      FAKE_make_parameter_variable_work_s FAKE_make_parameter_iki_option_s

  #define FAKE_make_parameter_variable_value_build_s     FAKE_make_parameter_variable_build_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_color_s     FAKE_make_parameter_variable_color_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_data_s      FAKE_make_parameter_variable_data_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_define_s    FAKE_make_parameter_variable_define_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_documents_s FAKE_make_parameter_variable_documents_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_fakefile_s  FAKE_make_parameter_variable_fakefile_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_licenses_s  FAKE_make_parameter_variable_licenses_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_mode_s      FAKE_make_parameter_variable_mode_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_process_s   FAKE_make_parameter_variable_process_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_settings_s  FAKE_make_parameter_variable_settings_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_sources_s   FAKE_make_parameter_variable_sources_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_verbosity_s FAKE_make_parameter_variable_verbosity_s FAKE_make_parameter_iki_value_s
  #define FAKE_make_parameter_variable_value_work_s      FAKE_make_parameter_variable_work_s FAKE_make_parameter_iki_value_s

  #define FAKE_make_parameter_iki_option_s_length 7
  #define FAKE_make_parameter_iki_value_s_length  6

  #define FAKE_make_parameter_variable_build_s_length     5
  #define FAKE_make_parameter_variable_color_s_length     5
  #define FAKE_make_parameter_variable_current_s_length   7
  #define FAKE_make_parameter_variable_data_s_length      4
  #define FAKE_make_parameter_variable_define_s_length    6
  #define FAKE_make_parameter_variable_documents_s_length 9
  #define FAKE_make_parameter_variable_fakefile_s_length  8
  #define FAKE_make_parameter_variable_licenses_s_length  8
  #define FAKE_make_parameter_variable_data_s_length      4
  #define FAKE_make_parameter_variable_mode_s_length      4
  #define FAKE_make_parameter_variable_process_s_length   7
  #define FAKE_make_parameter_variable_return_s_length    6
  #define FAKE_make_parameter_variable_settings_s_length  8
  #define FAKE_make_parameter_variable_sources_s_length   7
  #define FAKE_make_parameter_variable_top_s_length       3
  #define FAKE_make_parameter_variable_verbosity_s_length 9
  #define FAKE_make_parameter_variable_work_s_length      4

  #define FAKE_make_parameter_variable_option_build_s_length     FAKE_make_parameter_variable_build_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_color_s_length     FAKE_make_parameter_variable_color_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_data_s_length      FAKE_make_parameter_variable_data_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_define_s_length    FAKE_make_parameter_variable_define_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_documents_s_length FAKE_make_parameter_variable_documents_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_fakefile_s_length  FAKE_make_parameter_variable_fakefile_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_licenses_s_length  FAKE_make_parameter_variable_licenses_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_mode_s_length      FAKE_make_parameter_variable_mode_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_process_s_length   FAKE_make_parameter_variable_process_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_settings_s_length  FAKE_make_parameter_variable_settings_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_sources_s_length   FAKE_make_parameter_variable_sources_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_verbosity_s_length FAKE_make_parameter_variable_verbosity_s_length + FAKE_make_parameter_iki_option_s_length
  #define FAKE_make_parameter_variable_option_work_s_length      FAKE_make_parameter_variable_work_s_length + FAKE_make_parameter_iki_option_s_length

  #define FAKE_make_parameter_variable_value_build_s_length     FAKE_make_parameter_variable_build_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_color_s_length     FAKE_make_parameter_variable_color_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_data_s_length      FAKE_make_parameter_variable_data_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_documents_s_length FAKE_make_parameter_variable_documents_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_define_s_length    FAKE_make_parameter_variable_define_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_fakefile_s_length  FAKE_make_parameter_variable_fakefile_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_licenses_s_length  FAKE_make_parameter_variable_licenses_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_mode_s_length      FAKE_make_parameter_variable_mode_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_process_s_length   FAKE_make_parameter_variable_process_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_settings_s_length  FAKE_make_parameter_variable_settings_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_sources_s_length   FAKE_make_parameter_variable_sources_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_verbosity_s_length FAKE_make_parameter_variable_verbosity_s_length + FAKE_make_parameter_iki_value_s_length
  #define FAKE_make_parameter_variable_value_work_s_length      FAKE_make_parameter_variable_work_s_length + FAKE_make_parameter_iki_value_s_length

  extern const f_string_static_t fake_make_parameter_iki_option_s;
  extern const f_string_static_t fake_make_parameter_iki_value_s;

  extern const f_string_static_t fake_make_parameter_variable_build_s;
  extern const f_string_static_t fake_make_parameter_variable_color_s;
  extern const f_string_static_t fake_make_parameter_variable_current_s;
  extern const f_string_static_t fake_make_parameter_variable_data_s;
  extern const f_string_static_t fake_make_parameter_variable_define_s;
  extern const f_string_static_t fake_make_parameter_variable_documents_s;
  extern const f_string_static_t fake_make_parameter_variable_fakefile_s;
  extern const f_string_static_t fake_make_parameter_variable_licenses_s;
  extern const f_string_static_t fake_make_parameter_variable_mode_s;
  extern const f_string_static_t fake_make_parameter_variable_process_s;
  extern const f_string_static_t fake_make_parameter_variable_return_s;
  extern const f_string_static_t fake_make_parameter_variable_settings_s;
  extern const f_string_static_t fake_make_parameter_variable_sources_s;
  extern const f_string_static_t fake_make_parameter_variable_top_s;
  extern const f_string_static_t fake_make_parameter_variable_verbosity_s;
  extern const f_string_static_t fake_make_parameter_variable_work_s;

  extern const f_string_static_t fake_make_parameter_variable_option_build_s;
  extern const f_string_static_t fake_make_parameter_variable_option_color_s;
  extern const f_string_static_t fake_make_parameter_variable_option_data_s;
  extern const f_string_static_t fake_make_parameter_variable_option_define_s;
  extern const f_string_static_t fake_make_parameter_variable_option_documents_s;
  extern const f_string_static_t fake_make_parameter_variable_option_fakefile_s;
  extern const f_string_static_t fake_make_parameter_variable_option_licenses_s;
  extern const f_string_static_t fake_make_parameter_variable_option_mode_s;
  extern const f_string_static_t fake_make_parameter_variable_option_process_s;
  extern const f_string_static_t fake_make_parameter_variable_option_settings_s;
  extern const f_string_static_t fake_make_parameter_variable_option_sources_s;
  extern const f_string_static_t fake_make_parameter_variable_option_verbosity_s;
  extern const f_string_static_t fake_make_parameter_variable_option_work_s;

  extern const f_string_static_t fake_make_parameter_variable_value_build_s;
  extern const f_string_static_t fake_make_parameter_variable_value_color_s;
  extern const f_string_static_t fake_make_parameter_variable_value_data_s;
  extern const f_string_static_t fake_make_parameter_variable_value_define_s;
  extern const f_string_static_t fake_make_parameter_variable_value_documents_s;
  extern const f_string_static_t fake_make_parameter_variable_value_fakefile_s;
  extern const f_string_static_t fake_make_parameter_variable_value_licenses_s;
  extern const f_string_static_t fake_make_parameter_variable_value_mode_s;
  extern const f_string_static_t fake_make_parameter_variable_value_process_s;
  extern const f_string_static_t fake_make_parameter_variable_value_settings_s;
  extern const f_string_static_t fake_make_parameter_variable_value_sources_s;
  extern const f_string_static_t fake_make_parameter_variable_value_verbosity_s;
  extern const f_string_static_t fake_make_parameter_variable_value_work_s;
#endif // _di_fake_make_parameter_s_

#ifndef _di_fake_skeleton_content_s_
  #define FAKE_make_skeleton_content_defines_s      "# fss-0000\n\n"
  #define FAKE_make_skeleton_content_dependencies_s "# fss-0000\n\n"
  #define FAKE_make_skeleton_content_fakefile_s     "# fss-0005 iki-0002\n\nsettings:\n  fail exit\n\nmain:\n\n"
  #define FAKE_make_skeleton_content_process_post_s "#!/bin/bash\n\n"
  #define FAKE_make_skeleton_content_process_pre_s  "#!/bin/bash\n\n"
  #define FAKE_make_skeleton_content_settings_s     "# fss-0001\n\n"

  #define FAKE_make_skeleton_content_defines_s_length      12
  #define FAKE_make_skeleton_content_dependencies_s_length 12
  #define FAKE_make_skeleton_content_fakefile_s_length     51
  #define FAKE_make_skeleton_content_process_post_s_length 13
  #define FAKE_make_skeleton_content_process_pre_s_length  13
  #define FAKE_make_skeleton_content_settings_s_length     12

  extern const f_string_static_t fake_make_skeleton_content_defines_s;
  extern const f_string_static_t fake_make_skeleton_content_dependencies_s;
  extern const f_string_static_t fake_make_skeleton_content_fakefile_s;
  extern const f_string_static_t fake_make_skeleton_content_process_post_s;
  extern const f_string_static_t fake_make_skeleton_content_process_pre_s;
  extern const f_string_static_t fake_make_skeleton_content_settings_s;
#endif // _di_fake_skeleton_content_s_

#ifndef _di_fake_make_context_s_
  #define FAKE_make_context_error_s     "error"
  #define FAKE_make_context_important_s "important"
  #define FAKE_make_context_normal_s    "normal"
  #define FAKE_make_context_notable_s   "notable"
  #define FAKE_make_context_reset_s     "reset"
  #define FAKE_make_context_standout_s  "standout"
  #define FAKE_make_context_success_s   "success"
  #define FAKE_make_context_title_s     "title"
  #define FAKE_make_context_warning_s   "warning"

  #define FAKE_make_context_error_s_length     5
  #define FAKE_make_context_important_s_length 9
  #define FAKE_make_context_normal_s_length    6
  #define FAKE_make_context_notable_s_length   7
  #define FAKE_make_context_reset_s_length     5
  #define FAKE_make_context_standout_s_length  8
  #define FAKE_make_context_success_s_length   7
  #define FAKE_make_context_title_s_length     5
  #define FAKE_make_context_warning_s_length   7

  extern const f_string_static_t fake_make_context_error_s;
  extern const f_string_static_t fake_make_context_important_s;
  extern const f_string_static_t fake_make_context_normal_s;
  extern const f_string_static_t fake_make_context_notable_s;
  extern const f_string_static_t fake_make_context_reset_s;
  extern const f_string_static_t fake_make_context_standout_s;
  extern const f_string_static_t fake_make_context_success_s;
  extern const f_string_static_t fake_make_context_title_s;
  extern const f_string_static_t fake_make_context_warning_s;
#endif // _di_fake_make_context_s_

#ifndef _di_fake_file_data_build_s_
  #define FAKE_file_data_build_process_post_s "process_post.sh"
  #define FAKE_file_data_build_process_pre_s  "process_pre.sh"

  #define FAKE_file_data_build_process_post_s_length 15
  #define FAKE_file_data_build_process_pre_s_length  14

  extern const f_string_static_t fake_file_data_build_process_post_s;
  extern const f_string_static_t fake_file_data_build_process_pre_s;
#endif // _di_fake_file_data_build_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_string_h

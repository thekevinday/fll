/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_h
#define _fake_common_h

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

/***
 * Default allocations.
 *
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 *
 * fake_default_allocation_*_d:
 *   - large: A buffer size used for large allocations.
 *   - pipe:  A buffer size used for processing piped data.
 *   - small: A buffer size used for small allocations.
 */
#ifndef _di_fake_default_d_
  #define fake_default_allocation_large_d 64
  #define fake_default_allocation_pipe_d  16384
  #define fake_default_allocation_small_d 8
#endif // _di_fake_default_d_

/**
 * Provide default settings.
 */
#ifndef _di_fake_default_s_
  #define FAKE_default_path_build_s   "build"   F_path_separator_s
  #define FAKE_default_path_data_s    "data"    F_path_separator_s
  #define FAKE_default_path_sources_s "sources" F_path_separator_s
  #define FAKE_default_path_work_s    ""

  #define FAKE_default_fakefile_s "fakefile"
  #define FAKE_default_process_s  ""
  #define FAKE_default_settings_s "settings"

  #define FAKE_default_path_build_s_length   5 + F_path_separator_s_length
  #define FAKE_default_path_data_s_length    4 + F_path_separator_s_length
  #define FAKE_default_path_sources_s_length 7 + F_path_separator_s_length
  #define FAKE_default_path_work_s_length    0

  #define FAKE_default_fakefile_s_length 8
  #define FAKE_default_process_s_length  0
  #define FAKE_default_settings_s_length 8

  extern const f_string_static_t fake_default_path_build_s;
  extern const f_string_static_t fake_default_path_data_s;
  extern const f_string_static_t fake_default_path_sources_s;
  extern const f_string_static_t fake_default_path_work_s;

  extern const f_string_static_t fake_default_fakefile_s;
  extern const f_string_static_t fake_default_process_s;
  extern const f_string_static_t fake_default_settings_s;
#endif // _di_fake_default_s_

/**
 * The build language enumerations.
 *
 * fake_build_language_type_*_e:
 *   - bash: The GNU Bash language.
 *   - c:    The C language.
 *   - cpp:  The C++ language.
 *   - zsh:  The ZSH language (Similar to and somewhat compatible with GNU Bash).
 */
#ifndef _di_fake_build_language_e_
  enum {
    fake_build_language_type_bash_e = 1,
    fake_build_language_type_c_e,
    fake_build_language_type_cpp_e,
    fake_build_language_type_zsh_e,
  }; // enum
#endif // _di_fake_build_language_e_

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
 * The program version enumerations.
 */
#ifndef _di_fake_build_version_e_
  enum {
    fake_build_version_type_major_e = 1,
    fake_build_version_type_minor_e,
    fake_build_version_type_micro_e,
    fake_build_version_type_nano_e,
  }; // enum
#endif // _di_fake_build_version_e_

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
 * The program operation enumerations.
 *
 * fake_operation_*_e:
 *   - build:    The build operation.
 *   - clean:    The clean operation.
 *   - make:     The make operation.
 *   - skeleton: The skeleton operation.
 */
#ifndef _di_fake_operation_e_
  enum {
    fake_operation_build_e = 1,
    fake_operation_clean_e,
    fake_operation_make_e,
    fake_operation_skeleton_e,
  }; // enum
#endif // _di_fake_operation_e_

/**
 * The program defines.
 *
 * fake_signal_*_d:
 *   - check:       The normal signal check (@fixme is needed anymore as-is?).
 *   - check_tiny:  The tiny check (@fixme is needed anymore as-is?).
 *   - check_short: The short signal check (@fixme this is used everywhere).
 */
#ifndef _di_fake_signal_d_
  #define fake_signal_check_d       500000
  #define fake_signal_check_tiny_d  4
  #define fake_signal_check_short_d 16
#endif // _di_fake_signal_d_

/**
 * The main program parameters.
 */
#ifndef _di_fake_parameter_d_
  #define FAKE_short_define_s   "d"
  #define FAKE_short_fakefile_s "f"
  #define FAKE_short_mode_s     "m"
  #define FAKE_short_process_s  "p"
  #define FAKE_short_settings_s "s"

  #define FAKE_short_path_build_s   "b"
  #define FAKE_short_path_data_s    "D"
  #define FAKE_short_path_sources_s "S"
  #define FAKE_short_path_work_s    "w"

  #define FAKE_long_define_s   "define"
  #define FAKE_long_fakefile_s "fakefile"
  #define FAKE_long_mode_s     "mode"
  #define FAKE_long_process_s  "process"
  #define FAKE_long_settings_s "settings"

  #define FAKE_long_path_build_s   "build"
  #define FAKE_long_path_data_s    "data"
  #define FAKE_long_path_sources_s "sources"
  #define FAKE_long_path_work_s    "work"

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

  #define FAKE_short_define_s_length   1
  #define FAKE_short_fakefile_s_length 1
  #define FAKE_short_mode_s_length     1
  #define FAKE_short_process_s_length  1
  #define FAKE_short_settings_s_length 1

  #define FAKE_short_path_build_s_length   1
  #define FAKE_short_path_data_s_length    1
  #define FAKE_short_path_sources_s_length 1
  #define FAKE_short_path_work_s_length    1

  #define FAKE_long_define_s_length   6
  #define FAKE_long_fakefile_s_length 8
  #define FAKE_long_mode_s_length     4
  #define FAKE_long_process_s_length  7
  #define FAKE_long_settings_s_length 8

  #define FAKE_long_path_build_s_length   5
  #define FAKE_long_path_data_s_length    4
  #define FAKE_long_path_sources_s_length 7
  #define FAKE_long_path_work_s_length    4

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

  extern const f_string_static_t fake_short_define_s;
  extern const f_string_static_t fake_short_fakefile_s;
  extern const f_string_static_t fake_short_mode_s;
  extern const f_string_static_t fake_short_process_s;
  extern const f_string_static_t fake_short_settings_s;

  extern const f_string_static_t fake_short_path_build_s;
  extern const f_string_static_t fake_short_path_data_s;
  extern const f_string_static_t fake_short_path_sources_s;
  extern const f_string_static_t fake_short_path_work_s;

  extern const f_string_static_t fake_long_define_s;
  extern const f_string_static_t fake_long_fakefile_s;
  extern const f_string_static_t fake_long_mode_s;
  extern const f_string_static_t fake_long_process_s;
  extern const f_string_static_t fake_long_settings_s;

  extern const f_string_static_t fake_long_path_build_s;
  extern const f_string_static_t fake_long_path_data_s;
  extern const f_string_static_t fake_long_path_sources_s;
  extern const f_string_static_t fake_long_path_work_s;

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

  enum {
    fake_parameter_help_e,
    fake_parameter_light_e,
    fake_parameter_dark_e,
    fake_parameter_no_color_e,
    fake_parameter_verbosity_quiet_e,
    fake_parameter_verbosity_error_e,
    fake_parameter_verbosity_normal_e,
    fake_parameter_verbosity_verbose_e,
    fake_parameter_verbosity_debug_e,
    fake_parameter_version_e,
    fake_parameter_line_first_no_e,
    fake_parameter_line_last_no_e,

    fake_parameter_define_e,
    fake_parameter_fakefile_e,
    fake_parameter_mode_e,
    fake_parameter_process_e,
    fake_parameter_settings_e,

    fake_parameter_path_build_e,
    fake_parameter_path_data_e,
    fake_parameter_path_sources_e,
    fake_parameter_path_work_e,

    fake_parameter_documents_disable_e,
    fake_parameter_documents_enable_e,
    fake_parameter_shared_disable_e,
    fake_parameter_shared_enable_e,
    fake_parameter_static_disable_e,
    fake_parameter_static_enable_e,

    fake_parameter_operation_build_e,
    fake_parameter_operation_clean_e,
    fake_parameter_operation_make_e,
    fake_parameter_operation_skeleton_e,
  }; // enum

  #define fake_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_4(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize_4(fake_short_define_s,       fake_long_define_s,             1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_fakefile_s,     fake_long_fakefile_s,           1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_mode_s,         fake_long_mode_s,               1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_process_s,      fake_long_process_s,            1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_settings_s,     fake_long_settings_s,           1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_path_build_s,   fake_long_path_build_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_path_data_s,    fake_long_path_data_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_path_sources_s, fake_long_path_sources_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_4(fake_short_path_work_s,    fake_long_path_work_s,          1, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_6(fake_long_documents_disabled_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_6(fake_long_documents_enabled_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_6(fake_long_shared_disabled_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_6(fake_long_shared_enabled_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_6(fake_long_static_disabled_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_6(fake_long_static_enabled_s,     0, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_7(fake_other_operation_build_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_7(fake_other_operation_clean_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_7(fake_other_operation_make_s,     0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_7(fake_other_operation_skeleton_s, 0, f_console_flag_simple_e), \
    }

  #define fake_total_parameters_d 31
#endif // _di_fake_parameter_d_

/**
 * Flags passed to the main function or program.
 *
 * fake_main_flag_*_e:
 *   - none:             No flags set.
 *   - enable_documents: Enable documents, as-in --enable-doc (not specifying means --disable-doc).
 *   - enable_shared:    Enable shared, as-in --enable-shared (not specifying means --disable-shared).
 *   - enable_static:    Enable static, as-in --enable-static (not specifying means --disable-static).
 *   - file_from:        Using a specified source file.
 *   - file_to:          Using a specified destination file.
 *   - header:           Enable printing of headers.
 *   - help:             Print help.
 *   - operation:        Designate that an operation is explicitly passed.
 *   - separate:         Enable printing of separators.
 *   - strip_invalid:    Using strip invalid character mode.
 *   - verify:           Using verify mode.
 *   - version:          Print version.
 */
#ifndef _di_fake_main_flag_e_
  enum {
    fake_main_flag_none_e             = 0x0,
    fake_main_flag_enable_documents_e = 0x1,
    fake_main_flag_enable_shared_e    = 0x2,
    fake_main_flag_enable_static_e    = 0x4,
    fake_main_flag_file_from_e        = 0x8,
    fake_main_flag_file_to_e          = 0x10,
    fake_main_flag_header_e           = 0x20,
    fake_main_flag_help_e             = 0x40,
    fake_data_flag_operation_e        = 0x80,
    fake_main_flag_separate_e         = 0x100,
    fake_main_flag_strip_invalid_e    = 0x200,
    fake_main_flag_verify_e           = 0x400,
    fake_main_flag_version_e          = 0x800,
  }; // enum
#endif // _di_fake_main_flag_e_

/**
 * The fake main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * state:  The state data used when processing the FSS data.
 * status: The main status code, generally used by the load settings and main functions.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 *
 * build:    The build directory.
 * data:     The data directory.
 * fakefile: The fakefile file path.
 * process:  The process name.
 * settings: The settings file path.
 * sources:  The sources directory.
 * work:     The work directory.
 *
 * path_build:                  The build path.
 * path_build_documentation:    The build documentation path.
 * path_build_documents:        The build documents path.
 * path_build_includes:         The build includes path.
 * path_build_libraries:        The build libraries path.
 * path_build_libraries_script: The build libraries_script path.
 * path_build_libraries_shared: The build libraries_shared path.
 * path_build_libraries_static: The build libraries_static path.
 * path_build_objects:          The build objects path.
 * path_build_objects_script:   The build objects_script path.
 * path_build_objects_shared:   The build objects_shared path.
 * path_build_objects_static:   The build objects_static path.
 * path_build_programs:         The build programs path.
 * path_build_programs_script:  The build programs_script path.
 * path_build_programs_shared:  The build programs_shared path.
 * path_build_programs_static:  The build programs_static path.
 * path_build_settings:         The build settings path.
 * path_build_stage:            The build stage path.
 *
 * path_data:               The data path.
 * path_data_build:         The build data path.
 * path_data_documentation: The documentation data path.
 * path_data_settings:      The settings data path.
 *
 * path_documents: The documents path.
 * path_licenses:  The licenses path.
 * path_sources:   The sources path.
 *
 * path_work:                  The work path.
 * path_work_includes:         The includes work path.
 * path_work_libraries:        The libraries work path.
 * path_work_libraries_script: The libraries_script work path.
 * path_work_libraries_shared: The libraries_shared work path.
 * path_work_libraries_static: The libraries_static work path.
 * path_work_programs:         The programs work path.
 * path_work_programs_script:  The programs_script work path.
 * path_work_programs_shared:  The programs_shared work path.
 * path_work_programs_static:  The programs_static work path.
 *
 * file_data_build_defines:      The defines build file data.
 * file_data_build_dependencies: The dependencies build file data.
 * file_data_build_fakefile:     The fakefile build file data.
 * file_data_build_process_post: The process_post_s build file data.
 * file_data_build_process_pre:  The process_pre_s build file data.
 * file_data_build_settings:     The settings build file data.
 *
 * file_documents_readme: The documents readme file data.

 * defines: The define data.
 * modes:   The mode data.
 *
 * operations: The operations, in the order in which they are given.
 */
#ifndef _di_fake_setting_t_
  typedef struct {
    uint16_t flag;

    f_state_t state;
    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;

    f_string_dynamic_t build;
    f_string_dynamic_t data;
    f_string_dynamic_t fakefile;
    f_string_dynamic_t process;
    f_string_dynamic_t settings;
    f_string_dynamic_t sources;
    f_string_dynamic_t work;

    f_string_dynamic_t path_build;
    f_string_dynamic_t path_build_documentation;
    f_string_dynamic_t path_build_documents;
    f_string_dynamic_t path_build_includes;
    f_string_dynamic_t path_build_libraries;
    f_string_dynamic_t path_build_libraries_script;
    f_string_dynamic_t path_build_libraries_shared;
    f_string_dynamic_t path_build_libraries_static;
    f_string_dynamic_t path_build_objects;
    f_string_dynamic_t path_build_objects_script;
    f_string_dynamic_t path_build_objects_shared;
    f_string_dynamic_t path_build_objects_static;
    f_string_dynamic_t path_build_programs;
    f_string_dynamic_t path_build_programs_script;
    f_string_dynamic_t path_build_programs_shared;
    f_string_dynamic_t path_build_programs_static;
    f_string_dynamic_t path_build_settings;
    f_string_dynamic_t path_build_stage;

    f_string_dynamic_t path_data;
    f_string_dynamic_t path_data_build;
    f_string_dynamic_t path_data_documentation;
    f_string_dynamic_t path_data_settings;

    f_string_dynamic_t path_documents;

    f_string_dynamic_t path_licenses;

    f_string_dynamic_t path_sources;

    f_string_dynamic_t path_work;
    f_string_dynamic_t path_work_includes;
    f_string_dynamic_t path_work_libraries;
    f_string_dynamic_t path_work_libraries_script;
    f_string_dynamic_t path_work_libraries_shared;
    f_string_dynamic_t path_work_libraries_static;
    f_string_dynamic_t path_work_programs;
    f_string_dynamic_t path_work_programs_script;
    f_string_dynamic_t path_work_programs_shared;
    f_string_dynamic_t path_work_programs_static;

    // @fixme there is overlap here with setting->fakefile and similar.
    f_string_dynamic_t file_data_build_defines;
    f_string_dynamic_t file_data_build_dependencies;
    f_string_dynamic_t file_data_build_fakefile;
    f_string_dynamic_t file_data_build_process_post;
    f_string_dynamic_t file_data_build_process_pre;
    f_string_dynamic_t file_data_build_settings;

    f_string_dynamic_t file_documents_readme;

    f_string_dynamics_t defines;
    f_string_dynamics_t modes;

    f_uint8s_t operations;
  } fake_setting_t;

  #define fake_setting_t_initialize \
    { \
      fake_main_flag_none_e, \
      f_state_t_initialize, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_uint8s_t_initialize, \
    }
#endif // _di_fake_setting_t_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fake_setting_delete_
  extern f_status_t fake_setting_delete(fake_setting_t * const setting);
#endif // _di_fake_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_fake_setting_load_
  extern void fake_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fake_setting_t * const setting);
#endif // _di_fake_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_fake_setting_unload_
  extern f_status_t fake_setting_unload(fll_program_data_t * const main, fake_setting_t * const setting);
#endif // _di_fake_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_h

/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.6
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
#ifndef _di_fake_program_version_
  #define FAKE_program_version_major_s F_string_ascii_0_s
  #define FAKE_program_version_minor_s F_string_ascii_6_s
  #define FAKE_program_version_micro_s F_string_ascii_9_s

  #define FAKE_program_version_major_s_length F_string_ascii_0_s_length
  #define FAKE_program_version_minor_s_length F_string_ascii_6_s_length
  #define FAKE_program_version_micro_s_length F_string_ascii_9_s_length

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
#endif // _di_fake_program_version_

/**
 * The program name.
 */
#ifndef _di_fake_program_name_
  #define FAKE_program_name_s      "fake"
  #define FAKE_program_name_long_s "Featureless Make"

  #define FAKE_program_name_s_length      4
  #define FAKE_program_name_long_s_length 16

  extern const f_string_static_t fake_program_name_s;
  extern const f_string_static_t fake_program_name_long_s;
#endif // _di_fake_program_name_

/**
 * The program help related data.
 */
#ifndef _di_fake_program_help_parameters_
  #define FAKE_program_help_parameters_s "operation / section"
  #define FAKE_program_help_parameters_s_length 19

  extern const f_string_static_t fake_program_help_parameters_s;
#endif // _di_fake_program_help_parameters_

/***
 * Default allocations.
 *
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_fake_default_allocation_
  #define fake_default_allocation_pipe_d  16384
  #define fake_default_allocation_large_d 64
  #define fake_default_allocation_small_d 8
#endif // _di_fake_default_allocation_

/**
 * The build operation utilizes pre-defined path structures.
 * These structures are hard-coded by their individual pieces to be constructed later on.
 */
#ifndef _di_fake_path_
  #define FAKE_path_part_bash_s           "bash"           F_path_separator_s
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
  #define FAKE_path_part_specifications_s "specifications" F_path_separator_s
  #define FAKE_path_part_stage_s          "stage"          F_path_separator_s
  #define FAKE_path_part_static_s         "static"         F_path_separator_s

  #define FAKE_path_part_bash_s_length           4 + F_path_separator_s_length
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
  #define FAKE_path_part_specifications_s_length 14 + F_path_separator_s_length
  #define FAKE_path_part_stage_s_length          5 + F_path_separator_s_length
  #define FAKE_path_part_static_s_length         6 + F_path_separator_s_length

  extern const f_string_static_t fake_path_part_bash_s;
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
  extern const f_string_static_t fake_path_part_specifications_s;
  extern const f_string_static_t fake_path_part_stage_s;
  extern const f_string_static_t fake_path_part_static_s;
#endif // _di_fake_path_

/**
 * The file settings.
 */
#ifndef _di_fake_file_
  #define FAKE_file_defines_s      "defines"
  #define FAKE_file_dependencies_s "dependencies"
  #define FAKE_file_process_pre_s  "process_pre.sh"
  #define FAKE_file_process_post_s "process_post.sh"
  #define FAKE_file_readme_s       "readme"

  #define FAKE_file_defines_s_length      7
  #define FAKE_file_dependencies_s_length 12
  #define FAKE_file_process_pre_s_length  14
  #define FAKE_file_process_post_s_length 15
  #define FAKE_file_readme_s_length       6

  extern const f_string_static_t fake_file_defines_s;
  extern const f_string_static_t fake_file_dependencies_s;
  extern const f_string_static_t fake_file_process_pre_s;
  extern const f_string_static_t fake_file_process_post_s;
  extern const f_string_static_t fake_file_readme_s;
#endif // _di_fake_file_

/**
 * Provide default settings.
 */
#ifndef _di_fake_defaults_
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
#endif // _di_fake_defaults_

/**
 * The build languages.
 */
#ifndef _di_fake_build_language_
  enum {
    fake_build_language_type_bash_e = 1,
    fake_build_language_type_c_e,
    fake_build_language_type_cpp_e,
  }; // enum

  #define FAKE_build_language_bash_s "bash"
  #define FAKE_build_language_c_s    "c"
  #define FAKE_build_language_cpp_s  "c++"

  #define FAKE_build_language_bash_s_length 4
  #define FAKE_build_language_c_s_length    1
  #define FAKE_build_language_cpp_s_length  3

  extern const f_string_static_t fake_build_language_bash_s;
  extern const f_string_static_t fake_build_language_c_s;
  extern const f_string_static_t fake_build_language_cpp_s;
#endif // _di_fake_build_language_

/**
 * The program version.
 */
#ifndef _di_fake_build_version_
  enum {
    fake_build_version_type_major_e = 1,
    fake_build_version_type_minor_e,
    fake_build_version_type_micro_e,
    fake_build_version_type_nano_e,
  }; // enum

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
#endif // _di_fake_build_version_

/**
 * The program defines.
 */
#ifndef _di_fake_defines_
  enum {
    fake_operation_build_e = 1,
    fake_operation_clean_e,
    fake_operation_make_e,
    fake_operation_skeleton_e,
  }; // enum

  #define fake_signal_check_d       500000
  #define fake_signal_check_tiny_d  4
  #define fake_signal_check_short_d 16

  #define fake_operations_total_d    4
  #define fake_operations_initialize { 0, 0, 0, 0 }
#endif // _di_fake_defines_

/**
 * The main program parameters.
 */
#ifndef _di_fake_parameters_
  #define FAKE_short_define_s   "d"
  #define FAKE_short_fakefile_s "f"
  #define FAKE_short_mode_s     "m"
  #define FAKE_short_process_s  "p"
  #define FAKE_short_settings_s "s"

  #define FAKE_short_path_build_s   "b"
  #define FAKE_short_path_data_s    "D"
  #define FAKE_short_path_sources_s "S"
  #define FAKE_short_path_under_s   "U"
  #define FAKE_short_path_work_s    "w"

  #define FAKE_long_define_s   "define"
  #define FAKE_long_fakefile_s "fakefile"
  #define FAKE_long_mode_s     "mode"
  #define FAKE_long_process_s  "process"
  #define FAKE_long_settings_s "settings"

  #define FAKE_long_path_build_s   "build"
  #define FAKE_long_path_data_s    "data"
  #define FAKE_long_path_sources_s "sources"
  #define FAKE_long_path_under_s   "under"
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
  #define FAKE_short_path_under_s_length   1
  #define FAKE_short_path_work_s_length    1

  #define FAKE_long_define_s_length   6
  #define FAKE_long_fakefile_s_length 8
  #define FAKE_long_mode_s_length     4
  #define FAKE_long_process_s_length  7
  #define FAKE_long_settings_s_length 8

  #define FAKE_long_path_build_s_length   5
  #define FAKE_long_path_data_s_length    4
  #define FAKE_long_path_sources_s_length 7
  #define FAKE_long_path_under_s_length   5
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
  extern const f_string_static_t fake_short_path_under_s;
  extern const f_string_static_t fake_short_path_work_s;

  extern const f_string_static_t fake_long_define_s;
  extern const f_string_static_t fake_long_fakefile_s;
  extern const f_string_static_t fake_long_mode_s;
  extern const f_string_static_t fake_long_process_s;
  extern const f_string_static_t fake_long_settings_s;

  extern const f_string_static_t fake_long_path_build_s;
  extern const f_string_static_t fake_long_path_data_s;
  extern const f_string_static_t fake_long_path_sources_s;
  extern const f_string_static_t fake_long_path_under_s;
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
    fake_parameter_copyright_e,
    fake_parameter_light_e,
    fake_parameter_dark_e,
    fake_parameter_no_color_e,
    fake_parameter_verbosity_quiet_e,
    fake_parameter_verbosity_error_e,
    fake_parameter_verbosity_normal_e,
    fake_parameter_verbosity_verbose_e,
    fake_parameter_verbosity_debug_e,
    fake_parameter_version_e,

    fake_parameter_define_e,
    fake_parameter_fakefile_e,
    fake_parameter_mode_e,
    fake_parameter_process_e,
    fake_parameter_settings_e,

    fake_parameter_path_build_e,
    fake_parameter_path_data_e,
    fake_parameter_path_sources_e,
    fake_parameter_path_under_e,
    fake_parameter_path_work_e,

    fake_parameter_documents_disabled_e,
    fake_parameter_documents_enabled_e,
    fake_parameter_shared_disabled_e,
    fake_parameter_shared_enabled_e,
    fake_parameter_static_disabled_e,
    fake_parameter_static_enabled_e,

    fake_parameter_operation_build_e,
    fake_parameter_operation_clean_e,
    fake_parameter_operation_make_e,
    fake_parameter_operation_skeleton_e,
  }; // enum

  #define fake_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_copyright_s.string, f_console_standard_long_copyright_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_error_s.string, f_console_standard_long_error_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(fake_short_define_s.string, fake_long_define_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_fakefile_s.string, fake_long_fakefile_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_mode_s.string, fake_long_mode_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_process_s.string, fake_long_process_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_settings_s.string, fake_long_settings_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_build_s.string, fake_long_path_build_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_data_s.string, fake_long_path_data_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_sources_s.string, fake_long_path_sources_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_under_s.string, fake_long_path_under_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_work_s.string, fake_long_path_work_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_documents_disabled_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_documents_enabled_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_shared_disabled_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_shared_enabled_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_static_disabled_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_static_enabled_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_build_s.string, 0, f_console_type_other_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_clean_s.string, 0, f_console_type_other_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_make_s.string, 0, f_console_type_other_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_skeleton_s.string, 0, f_console_type_other_e), \
    }

  #define fake_total_parameters_d 31
#endif // _di_fake_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_h

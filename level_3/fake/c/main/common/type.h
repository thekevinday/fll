/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_type_h
#define _fake_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

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
 * The program defines.
 *
 * fake_signal_*_d:
 *   - check:       The normal signal check.
 *   - check_tiny:  The tiny check.
 *   - check_short: The short signal check.
 */
#ifndef _di_fake_signal_d_
  #define fake_signal_check_d       500000
  #define fake_signal_check_tiny_d  4
  #define fake_signal_check_short_d 16
#endif // _di_fake_signal_d_

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
 * Flags passed to the main function or program.
 *
 * fake_main_flag_*_e:
 *   - none:               No flags set.
 *   - copyright:          Print copyright.
 *   - enable_documents:   Enable documents, as in --enable-doc (not specifying means --disable-doc).
 *   - enable_shared:      Enable shared, as in --enable-shared (not specifying means --disable-shared).
 *   - enable_static:      Enable static, as in --enable-static (not specifying means --disable-static).
 *   - file_from:          Using a specified source file.
 *   - file_to:            Using a specified destination file.
 *   - header:             Enable printing of headers.
 *   - help:               Print help.
 *   - operation:          Designate that an operation is explicitly passed.
 *   - operation_build:    The build operation is designated.
 *   - operation_clean:    The clean operation is designated.
 *   - operation_make:     The make operation is designated (or enabled as default).
 *   - operation_skeleton: The skeleton operation is designated.
 *   - separate:           Enable printing of separators.
 *   - strip_invalid:      Using strip invalid character mode.
 *   - verify:             Using verify mode.
 *   - version:            Print version.
 */
#ifndef _di_fake_main_flag_e_
  enum {
    fake_main_flag_none_e               = 0x0,
    fake_main_flag_copyright_e          = 0x1,
    fake_main_flag_enable_documents_e   = 0x2,
    fake_main_flag_enable_shared_e      = 0x4,
    fake_main_flag_enable_static_e      = 0x8,
    fake_main_flag_file_from_e          = 0x10,
    fake_main_flag_file_to_e            = 0x20,
    fake_main_flag_header_e             = 0x40,
    fake_main_flag_help_e               = 0x80,
    fake_main_flag_operation_e          = 0x100,
    fake_main_flag_operation_build_e    = 0x200,
    fake_main_flag_operation_clean_e    = 0x400,
    fake_main_flag_operation_make_e     = 0x800,
    fake_main_flag_operation_skeleton_e = 0x1000,
    fake_main_flag_separate_e           = 0x2000,
    fake_main_flag_strip_invalid_e      = 0x4000,
    fake_main_flag_verify_e             = 0x8000,
    fake_main_flag_version_e            = 0x10000,
  }; // enum
#endif // _di_fake_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_fake_parameter_e_
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
    fake_parameter_line_first_no_e,
    fake_parameter_line_last_no_e,

    fake_parameter_build_e,
    fake_parameter_data_e,
    fake_parameter_define_e,
    fake_parameter_documents_e,
    fake_parameter_fakefile_e,
    fake_parameter_licenses_e,
    fake_parameter_mode_e,
    fake_parameter_process_e,
    fake_parameter_settings_e,
    fake_parameter_sources_e,
    fake_parameter_work_e,

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
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_copyright_s,     f_console_standard_long_copyright_s,     0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize_3(fake_short_build_s,     fake_long_build_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_data_s,      fake_long_data_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_define_s,    fake_long_define_s,        1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_documents_s, fake_long_documents_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_fakefile_s,  fake_long_fakefile_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_licenses_s,  fake_long_licenses_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_mode_s,      fake_long_mode_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_process_s,   fake_long_process_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_settings_s,  fake_long_settings_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_sources_s,   fake_long_sources_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_work_s,      fake_long_work_s,          1, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_5(fake_long_documents_disabled_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_documents_enabled_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_shared_disabled_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_shared_enabled_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_static_disabled_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_static_enabled_s,     0, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_build_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_clean_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_make_s,     0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_skeleton_s, 0, f_console_flag_simple_e), \
    }

  #define fake_total_parameters_d 34
#endif // _di_fake_parameter_e_

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

 * defines: The define data.
 * modes:   The mode data.
 *
 * operations: The operations, in the order in which they are given.
 */
#ifndef _di_fake_setting_t_
  typedef struct {
    uint32_t flag;

    f_state_t state;
    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;

    f_string_dynamic_t build;
    f_string_dynamic_t data;
    f_string_dynamic_t documents;
    f_string_dynamic_t fakefile;
    f_string_dynamic_t licenses;
    f_string_dynamic_t process;
    f_string_dynamic_t settings;
    f_string_dynamic_t sources;
    f_string_dynamic_t work;

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
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_uint8s_t_initialize, \
    }
#endif // _di_fake_setting_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_type_h

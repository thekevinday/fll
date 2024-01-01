/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_h
#define _status_code_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_status_code_program_version_
  #define STATUS_CODE_program_version_major_s F_string_ascii_0_s
  #define STATUS_CODE_program_version_minor_s F_string_ascii_6_s
  #define STATUS_CODE_program_version_micro_s F_string_ascii_9_s

  #define STATUS_CODE_program_version_major_s_length F_string_ascii_0_s_length
  #define STATUS_CODE_program_version_minor_s_length F_string_ascii_6_s_length
  #define STATUS_CODE_program_version_micro_s_length F_string_ascii_9_s_length

  #if !(defined(STATUS_CODE_program_version_nano_prefix_s) && defined(STATUS_CODE_program_version_nano_prefix_s_length))
    #define STATUS_CODE_program_version_nano_prefix_s
    #define STATUS_CODE_program_version_nano_prefix_s_length 0
  #endif // !(defined(STATUS_CODE_program_version_nano_prefix_s) && defined(STATUS_CODE_program_version_nano_prefix_s_length))

  #if !(defined(STATUS_CODE_program_version_nano_s) && defined(STATUS_CODE_program_version_nano_s_length))
    #define STATUS_CODE_program_version_nano_s
    #define STATUS_CODE_program_version_nano_s_length 0
  #endif // !(defined(STATUS_CODE_program_version_nano_s) && defined(STATUS_CODE_program_version_nano_s_length))

  #define STATUS_CODE_program_version_s STATUS_CODE_program_version_major_s F_string_ascii_period_s STATUS_CODE_program_version_minor_s F_string_ascii_period_s STATUS_CODE_program_version_micro_s STATUS_CODE_program_version_nano_prefix_s STATUS_CODE_program_version_nano_s

  #define STATUS_CODE_program_version_s_length STATUS_CODE_program_version_major_s_length + F_string_ascii_period_s_length + STATUS_CODE_program_version_minor_s_length + F_string_ascii_period_s_length + STATUS_CODE_program_version_micro_s_length + STATUS_CODE_program_version_nano_prefix_s_length + STATUS_CODE_program_version_nano_s_length

  extern const f_string_static_t status_code_program_version_s;
#endif // _di_status_code_program_version_

/**
 * The program name.
 */
#ifndef _di_status_code_program_name_
  #define STATUS_CODE_program_name_s      "status_code"
  #define STATUS_CODE_program_name_long_s "Status Code"

  #define STATUS_CODE_program_name_s_length      11
  #define STATUS_CODE_program_name_long_s_length 11

  extern const f_string_static_t status_code_program_name_s;
  extern const f_string_static_t status_code_program_name_long_s;
#endif // _di_status_code_program_name_

/**
 * The program help related data.
 */
#ifndef _di_status_code_program_help_parameters_
  #define STATUS_CODE_program_help_parameters_s "status code(s)"
  #define STATUS_CODE_program_help_parameters_s_length 14

  extern const f_string_static_t status_code_program_help_parameters_s;
#endif // _di_status_code_program_help_parameters_

/**
 * The program defines.
 */
#ifndef _di_status_code_defines_
  #define status_code_signal_check_d 20000
#endif // _di_status_code_defines_

/**
 * The main program parameters.
 */
#ifndef _di_status_code_parameters_
  #define STATUS_CODE_short_fine_s    "f"
  #define STATUS_CODE_short_warning_s "w"
  #define STATUS_CODE_short_error_s   "e"
  #define STATUS_CODE_short_number_s  "n"

  #define STATUS_CODE_long_fine_s    "fine"
  #define STATUS_CODE_long_warning_s "warning"
  #define STATUS_CODE_long_error_s   "error"
  #define STATUS_CODE_long_number_s  "number"

  #define STATUS_CODE_short_fine_s_length    1
  #define STATUS_CODE_short_warning_s_length 1
  #define STATUS_CODE_short_error_s_length   1
  #define STATUS_CODE_short_number_s_length  1

  #define STATUS_CODE_long_fine_s_length    4
  #define STATUS_CODE_long_warning_s_length 7
  #define STATUS_CODE_long_error_s_length   5
  #define STATUS_CODE_long_number_s_length  6

  extern const f_string_static_t status_code_short_fine_s;
  extern const f_string_static_t status_code_short_warning_s;
  extern const f_string_static_t status_code_short_error_s;
  extern const f_string_static_t status_code_short_number_s;

  extern const f_string_static_t status_code_long_fine_s;
  extern const f_string_static_t status_code_long_warning_s;
  extern const f_string_static_t status_code_long_error_s;
  extern const f_string_static_t status_code_long_number_s;

  enum {
    status_code_parameter_help_e,
    status_code_parameter_copyright_e,
    status_code_parameter_light_e,
    status_code_parameter_dark_e,
    status_code_parameter_no_color_e,
    status_code_parameter_verbosity_quiet_e,
    status_code_parameter_verbosity_error_e,
    status_code_parameter_verbosity_normal_e,
    status_code_parameter_verbosity_verbose_e,
    status_code_parameter_verbosity_debug_e,
    status_code_parameter_version_e,

    status_code_parameter_fine_e,
    status_code_parameter_warning_e,
    status_code_parameter_error_e,
    status_code_parameter_number_e,
  };

  #define status_code_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(status_code_short_fine_s.string, status_code_long_fine_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(status_code_short_warning_s.string, status_code_long_warning_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(status_code_short_error_s.string, status_code_long_error_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(status_code_short_number_s.string, status_code_long_number_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define status_code_total_parameters_d 15
#endif // _di_status_code_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_h

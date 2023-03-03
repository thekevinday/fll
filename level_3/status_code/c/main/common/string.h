/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_string_h
#define _status_code_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_status_code_program_version_s_
  #define STATUS_CODE_program_version_major_s F_string_ascii_0_s
  #define STATUS_CODE_program_version_minor_s F_string_ascii_7_s
  #define STATUS_CODE_program_version_micro_s F_string_ascii_0_s

  #define STATUS_CODE_program_version_major_s_length F_string_ascii_0_s_length
  #define STATUS_CODE_program_version_minor_s_length F_string_ascii_7_s_length
  #define STATUS_CODE_program_version_micro_s_length F_string_ascii_0_s_length

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
#endif // _di_status_code_program_version_s_

/**
 * The program name.
 */
#ifndef _di_status_code_program_name_s_
  #define STATUS_CODE_program_name_s      "status_code"
  #define STATUS_CODE_program_name_long_s "Status Code"

  #define STATUS_CODE_program_name_s_length      11
  #define STATUS_CODE_program_name_long_s_length 11

  extern const f_string_static_t status_code_program_name_s;
  extern const f_string_static_t status_code_program_name_long_s;
#endif // _di_status_code_program_name_s_

/**
 * The program help related data.
 */
#ifndef _di_status_code_program_help_parameters_s_
  #define STATUS_CODE_program_help_parameters_s "status code(s)"
  #define STATUS_CODE_program_help_parameters_s_length 14

  extern const f_string_static_t status_code_program_help_parameters_s;
#endif // _di_status_code_program_help_parameters_s_

/**
 * Special strings used by this program.
 */
#ifndef _di_status_code_s_
  #define STATUS_CODE_failed_to_convert_s "failed to convert"
  #define STATUS_CODE_invalid_number_s    "invalid number"
  #define STATUS_CODE_invalid_name_s      "invalid name"
  #define STATUS_CODE_invalid_main_s      "invalid main"
  #define STATUS_CODE_out_of_range_s      "out of range"
  #define STATUS_CODE_unknown_code_s      "unknown code"
  #define STATUS_CODE_unknown_name_s      "unknown name"

  #define STATUS_CODE_failed_to_convert_s_length 17
  #define STATUS_CODE_invalid_number_s_length    14
  #define STATUS_CODE_invalid_name_s_length      12
  #define STATUS_CODE_invalid_main_s_length      12
  #define STATUS_CODE_out_of_range_s_length      12
  #define STATUS_CODE_unknown_code_s_length      12
  #define STATUS_CODE_unknown_name_s_length      12

  extern const f_string_static_t status_code_failed_to_convert_s;
  extern const f_string_static_t status_code_invalid_number_s;
  extern const f_string_static_t status_code_invalid_name_s;
  extern const f_string_static_t status_code_invalid_main_s;
  extern const f_string_static_t status_code_out_of_range_s;
  extern const f_string_static_t status_code_unknown_code_s;
  extern const f_string_static_t status_code_unknown_name_s;
#endif // _di_status_code_s_

/**
 * The main program parameters.
 */
#ifndef _di_status_code_parameter_s_
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
#endif // _di_status_code_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_string_h

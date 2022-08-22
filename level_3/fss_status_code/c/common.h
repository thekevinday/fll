/**
 * FLL - Level 3
 *
 * Project: FSS Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_status_code_common_h
#define _fss_status_code_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_status_code_program_version_
  #define FSS_STATUS_CODE_program_version_major_s F_string_ascii_0_s
  #define FSS_STATUS_CODE_program_version_minor_s F_string_ascii_7_s
  #define FSS_STATUS_CODE_program_version_micro_s F_string_ascii_0_s

  #define FSS_STATUS_CODE_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_STATUS_CODE_program_version_minor_s_length F_string_ascii_7_s_length
  #define FSS_STATUS_CODE_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(FSS_STATUS_CODE_program_version_nano_prefix_s) && defined(FSS_STATUS_CODE_program_version_nano_prefix_s_length))
    #define FSS_STATUS_CODE_program_version_nano_prefix_s
    #define FSS_STATUS_CODE_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_STATUS_CODE_program_version_nano_prefix_s) && defined(FSS_STATUS_CODE_program_version_nano_prefix_s_length))

  #if !(defined(FSS_STATUS_CODE_program_version_nano_s) && defined(FSS_STATUS_CODE_program_version_nano_s_length))
    #define FSS_STATUS_CODE_program_version_nano_s
    #define FSS_STATUS_CODE_program_version_nano_s_length 0
  #endif // !(defined(FSS_STATUS_CODE_program_version_nano_s) && defined(FSS_STATUS_CODE_program_version_nano_s_length))

  #define FSS_STATUS_CODE_program_version_s FSS_STATUS_CODE_program_version_major_s F_string_ascii_period_s FSS_STATUS_CODE_program_version_minor_s F_string_ascii_period_s FSS_STATUS_CODE_program_version_micro_s FSS_STATUS_CODE_program_version_nano_prefix_s FSS_STATUS_CODE_program_version_nano_s

  #define FSS_STATUS_CODE_program_version_s_length FSS_STATUS_CODE_program_version_major_s_length + F_string_ascii_period_s_length + FSS_STATUS_CODE_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_STATUS_CODE_program_version_micro_s_length + FSS_STATUS_CODE_program_version_nano_prefix_s_length + FSS_STATUS_CODE_program_version_nano_s_length

  extern const f_string_static_t fss_status_code_program_version_s;
#endif // _di_fss_status_code_program_version_

/**
 * The program name.
 */
#ifndef _di_fss_status_code_program_name_
  #define FSS_STATUS_CODE_program_name_s      "fss_status_code"
  #define FSS_STATUS_CODE_program_name_long_s "FSS Status Code"

  #define FSS_STATUS_CODE_program_name_s_length      15
  #define FSS_STATUS_CODE_program_name_long_s_length 15

  extern const f_string_static_t fss_status_code_program_name_s;
  extern const f_string_static_t fss_status_code_program_name_long_s;
#endif // _di_fss_status_code_program_name_

/**
 * The program help related data.
 */
#ifndef _di_fss_status_code_program_help_parameters_
  #define FSS_STATUS_CODE_program_help_parameters_s "status code(s)"
  #define FSS_STATUS_CODE_program_help_parameters_s_length 14

  extern const f_string_static_t fss_status_code_program_help_parameters_s;
#endif // _di_fss_status_code_program_help_parameters_

/**
 * Special strings used by this program.
 */
#ifndef _di_fss_status_code_strings_
  #define FSS_STATUS_CODE_failed_to_convert_s "failed to convert"
  #define FSS_STATUS_CODE_invalid_number_s    "invalid number"
  #define FSS_STATUS_CODE_invalid_name_s      "invalid name"
  #define FSS_STATUS_CODE_invalid_main_s      "invalid main"
  #define FSS_STATUS_CODE_out_of_range_s      "out of range"
  #define FSS_STATUS_CODE_unknown_code_s      "unknown code"
  #define FSS_STATUS_CODE_unknown_name_s      "unknown name"

  #define FSS_STATUS_CODE_failed_to_convert_s_length 17
  #define FSS_STATUS_CODE_invalid_number_s_length    14
  #define FSS_STATUS_CODE_invalid_name_s_length      12
  #define FSS_STATUS_CODE_invalid_main_s_length      12
  #define FSS_STATUS_CODE_out_of_range_s_length      12
  #define FSS_STATUS_CODE_unknown_code_s_length      12
  #define FSS_STATUS_CODE_unknown_name_s_length      12

  extern const f_string_static_t fss_status_code_failed_to_convert_s;
  extern const f_string_static_t fss_status_code_invalid_number_s;
  extern const f_string_static_t fss_status_code_invalid_name_s;
  extern const f_string_static_t fss_status_code_invalid_main_s;
  extern const f_string_static_t fss_status_code_out_of_range_s;
  extern const f_string_static_t fss_status_code_unknown_code_s;
  extern const f_string_static_t fss_status_code_unknown_name_s;
#endif // _di_fss_status_code_strings_

/**
 * The program defines.
 */
#ifndef _di_fss_status_code_defines_
  #define fss_status_code_signal_check_d 20000
#endif // _di_fss_status_code_defines_

/**
 * The main program parameters.
 */
#ifndef _di_fss_status_code_parameters_
  #define FSS_STATUS_CODE_short_fine_s    "f"
  #define FSS_STATUS_CODE_short_warning_s "w"
  #define FSS_STATUS_CODE_short_error_s   "e"
  #define FSS_STATUS_CODE_short_number_s  "n"

  #define FSS_STATUS_CODE_long_fine_s    "fine"
  #define FSS_STATUS_CODE_long_warning_s "warning"
  #define FSS_STATUS_CODE_long_error_s   "error"
  #define FSS_STATUS_CODE_long_number_s  "number"

  #define FSS_STATUS_CODE_short_fine_s_length    1
  #define FSS_STATUS_CODE_short_warning_s_length 1
  #define FSS_STATUS_CODE_short_error_s_length   1
  #define FSS_STATUS_CODE_short_number_s_length  1

  #define FSS_STATUS_CODE_long_fine_s_length    4
  #define FSS_STATUS_CODE_long_warning_s_length 7
  #define FSS_STATUS_CODE_long_error_s_length   5
  #define FSS_STATUS_CODE_long_number_s_length  6

  extern const f_string_static_t fss_status_code_short_fine_s;
  extern const f_string_static_t fss_status_code_short_warning_s;
  extern const f_string_static_t fss_status_code_short_error_s;
  extern const f_string_static_t fss_status_code_short_number_s;

  extern const f_string_static_t fss_status_code_long_fine_s;
  extern const f_string_static_t fss_status_code_long_warning_s;
  extern const f_string_static_t fss_status_code_long_error_s;
  extern const f_string_static_t fss_status_code_long_number_s;

  enum {
    fss_status_code_parameter_help_e,
    fss_status_code_parameter_light_e,
    fss_status_code_parameter_dark_e,
    fss_status_code_parameter_no_color_e,
    fss_status_code_parameter_verbosity_quiet_e,
    fss_status_code_parameter_verbosity_error_e,
    fss_status_code_parameter_verbosity_normal_e,
    fss_status_code_parameter_verbosity_verbose_e,
    fss_status_code_parameter_verbosity_debug_e,
    fss_status_code_parameter_version_e,
    fss_status_code_parameter_line_first_no_e,
    fss_status_code_parameter_line_last_no_e,

    fss_status_code_parameter_fine_e,
    fss_status_code_parameter_warning_e,
    fss_status_code_parameter_error_e,
    fss_status_code_parameter_number_e,
  };

  #define fss_status_code_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_type_inverse_e), \
      \
      macro_f_console_parameter_t_initialize2(fss_status_code_short_fine_s.string, fss_status_code_long_fine_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(fss_status_code_short_warning_s.string, fss_status_code_long_warning_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(fss_status_code_short_error_s.string, fss_status_code_long_error_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize2(fss_status_code_short_number_s.string, fss_status_code_long_number_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define fss_status_code_total_parameters_d 16
#endif // _di_fss_status_code_parameters_

/**
 * Flags used to represent flags passed to the main function.
 *
 * When number mode is not specified, then mode is "string" mode (there is no flag for "string" mode).
 *
 * fss_status_code_main_flag_*_e:
 *   - none:    No modes in use.
 *   - error:   Check if status is "error".
 *   - fine:    Check if status is "fine".
 *   - help:    Print help.
 *   - number:  Operate in number mode.
 *   - version: Print version.
 *   - warning: Check if status is "warning".
 */
#ifndef _di_fss_status_code_main_flag_e_
  enum {
    fss_status_code_main_flag_none_e    = 0x0,
    fss_status_code_main_flag_error_e   = 0x1,
    fss_status_code_main_flag_fine_e    = 0x2,
    fss_status_code_main_flag_help_e    = 0x4,
    fss_status_code_main_flag_number_e  = 0x8,
    fss_status_code_main_flag_version_e = 0x10,
    fss_status_code_main_flag_warning_e = 0x20,
  };
#endif // _di_fss_status_code_main_flag_e_

/**
 * The status code main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status: The main status code, generally used by the load settings and main functions.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 */
#ifndef _di_fss_status_code_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;
  } fss_status_code_setting_t;

  #define fss_status_code_setting_t_initialize \
    { \
      fss_status_code_main_flag_none_e, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }
#endif // _di_fss_status_code_setting_t_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fss_status_code_setting_delete_
  extern f_status_t fss_status_code_setting_delete(fss_status_code_setting_t * const setting);
#endif // _di_fss_status_code_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately retuns without doing anything.
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
#ifndef _di_fss_status_code_setting_load_
  extern void fss_status_code_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_status_code_setting_t * const setting);
#endif // _di_fss_status_code_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   This does not alter setting.status.
 *   All buffers are deallocated.
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
#ifndef _di_fss_status_code_setting_unload_
  extern f_status_t fss_status_code_setting_unload(fll_program_data_t * const main, fss_status_code_setting_t * const setting);
#endif // _di_fss_status_code_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_status_code_common_h

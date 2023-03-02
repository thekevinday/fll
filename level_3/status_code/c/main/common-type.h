/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_type_h
#define _status_code_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * macro_status_code_setting:
 *   - Used to represent a cast to ((status_code_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_status_code_d_
  #define status_code_signal_check_d 20000

  #define macro_status_code_setting(setting) ((status_code_setting_t *) setting)
#endif // _di_status_code_d_

/**
 * Flags passed to the main function or program.
 *
 * When number mode is not specified, then mode is "string" mode (there is no flag for "string" mode).
 *
 * status_code_main_flag_*_e:
 *   - none:      No flags set.
 *   - copyright: Print copyright.
 *   - error:     Check if status is "error".
 *   - fine:      Check if status is "fine".
 *   - help:      Print help.
 *   - number:    Operate in number mode.
 *   - version:   Print version.
 *   - warning:   Check if status is "warning".
 */
#ifndef _di_status_code_main_flag_e_
  enum {
    status_code_main_flag_none_e      = 0x0,
    status_code_main_flag_copyright_e = 0x1,
    status_code_main_flag_error_e     = 0x2,
    status_code_main_flag_fine_e      = 0x4,
    status_code_main_flag_help_e      = 0x8,
    status_code_main_flag_number_e    = 0x10,
    status_code_main_flag_version_e   = 0x20,
    status_code_main_flag_warning_e   = 0x40,
  };
#endif // _di_status_code_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_status_code_parameter_e_
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
    status_code_parameter_line_first_no_e,
    status_code_parameter_line_last_no_e,

    status_code_parameter_fine_e,
    status_code_parameter_warning_e,
    status_code_parameter_error_e,
    status_code_parameter_number_e,
  }; // enum

  #define status_code_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize_3(status_code_short_fine_s,    status_code_long_fine_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(status_code_short_warning_s, status_code_long_warning_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(status_code_short_error_s,   status_code_long_error_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(status_code_short_number_s,  status_code_long_number_s,  0, f_console_flag_normal_e), \
    }

  #define status_code_total_parameters_d 17
#endif // _di_status_code_parameter_e_

/**
 * The status code main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * state: The state information.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 *
 * status_string_from:        A pointer to the status string function (usually either fll_status_string_from() or fll_fss_status_string_from()).
 * status_string_to:          A pointer to the status string function (usually either f_status_string_to() or fll_fss_status_string_to()).
 * status_string_help_detail: Print additional, more detailed help, in the help page (The setting paramete must be of type status_code_setting_t).
 */
#ifndef _di_status_code_setting_t_
  typedef struct {
    uint16_t flag;

    f_state_t state;

    f_string_static_t line_first;
    f_string_static_t line_last;

    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;

    f_status_t (*status_string_from)(const f_string_static_t name, f_status_t * const code);
    f_status_t (*status_string_to)(const f_status_t code, f_string_static_t * const name);
    void (*status_string_help_detail)(void * const setting, const fl_print_t print);
  } status_code_setting_t;

  #define status_code_setting_t_initialize \
    { \
      status_code_main_flag_none_e, \
      f_state_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      0, \
    }
#endif // _di_status_code_setting_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_type_h

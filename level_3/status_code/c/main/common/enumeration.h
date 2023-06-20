/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_enumeration_h
#define _status_code_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * When number mode is not specified, then mode is "string" mode (there is no flag for "string" mode).
 *
 * status_code_main_flag_*_e:
 *   - none:        No flags set.
 *   - copyright:   Print copyright.
 *   - error:       Check if status is "error".
 *   - fine:        Check if status is "fine".
 *   - help:        Print help.
 *   - number:      Operate in number mode.
 *   - print_first: When set, print new line to message output on program begin after loading settings.
 *   - print_last:  When set, print new line to message output on program end.
 *   - version:     Print version.
 *   - warning:     Check if status is "warning".
 */
#ifndef _di_status_code_main_flag_e_
  enum {
    status_code_main_flag_none_e        = 0x0,
    status_code_main_flag_copyright_e   = 0x1,
    status_code_main_flag_error_e       = 0x2,
    status_code_main_flag_fine_e        = 0x4,
    status_code_main_flag_help_e        = 0x8,
    status_code_main_flag_number_e      = 0x10,
    status_code_main_flag_print_first_e = 0x20,
    status_code_main_flag_print_last_e  = 0x40,
    status_code_main_flag_version_e     = 0x80,
    status_code_main_flag_warning_e     = 0x100,
  }; // enum
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
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(status_code_short_fine_s,    status_code_long_fine_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(status_code_short_warning_s, status_code_long_warning_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(status_code_short_error_s,   status_code_long_error_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(status_code_short_number_s,  status_code_long_number_s,  0, f_console_flag_normal_e), \
    }

  #define status_code_parameter_total_d 17
#endif // _di_status_code_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * status_code_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_status_code_print_flag_e_
  enum {
    status_code_print_flag_none_e    = 0x0,
    status_code_print_flag_debug_e   = 0x1,
    status_code_print_flag_error_e   = 0x2,
    status_code_print_flag_file_e    = 0x4,
    status_code_print_flag_in_e      = 0x8,
    status_code_print_flag_out_e     = 0x10,
    status_code_print_flag_message_e = 0x20,
    status_code_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_status_code_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_enumeration_h

/**
 * FLL - Level 3
 *
 * Project: Example
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _example_common_enumeration_h
#define _example_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * When number mode is not specified, then mode is "string" mode (there is no flag for "string" mode).
 *
 * example_main_flag_*_e:
 *   - none:                   No flags set.
 *   - copyright:              Print copyright.
 *   - error:                  Check if status is "error".
 *   - fine:                   Check if status is "fine".
 *   - help:                   Print help.
 *   - pipe:                   Use the input pipe.
 *   - print_first:            When set, print new line to message output on program begin after loading settings.
 *   - print_last:             When set, print new line to message output on program end.
 *   - version:                Print version.
 *   - version_copyright_help: A helper flag representing version, copyright, and help flag bits being set.
 *   - warning:                Check if status is "warning".
 */
#ifndef _di_example_main_flag_e_
  enum {
    example_main_flag_none_e                   = 0x0,
    example_main_flag_copyright_e              = 0x1,
    example_main_flag_error_e                  = 0x2,
    example_main_flag_fine_e                   = 0x4,
    example_main_flag_help_e                   = 0x8,
    example_main_flag_pipe_e                   = 0x10,
    example_main_flag_print_first_e            = 0x20,
    example_main_flag_print_last_e             = 0x40,
    example_main_flag_version_e                = 0x80,
    example_main_flag_version_copyright_help_e = 0x89,
    example_main_flag_warning_e                = 0x100,
  }; // enum
#endif // _di_example_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_example_parameter_e_
  enum {
    example_parameter_example_e = f_console_standard_parameter_last_e,
  }; // enum

  #define example_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(example_short_example_s, example_long_example_s, 0, f_console_flag_normal_e), \
    }

  #define example_parameter_total_d (f_console_parameter_state_type_total_d + 1)
#endif // _di_example_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * example_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_example_print_flag_e_
  enum {
    example_print_flag_none_e    = 0x0,
    example_print_flag_debug_e   = 0x1,
    example_print_flag_error_e   = 0x2,
    example_print_flag_file_e    = 0x4,
    example_print_flag_in_e      = 0x8,
    example_print_flag_out_e     = 0x10,
    example_print_flag_message_e = 0x20,
    example_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_example_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _example_common_enumeration_h

/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_enumeration_h
#define _iki_write_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * iki_write_main_flag_*_e:
 *   - none:        No flags set.
 *   - content:     The Content being written is specified.
 *   - copyright:   Print copyright.
 *   - file_to:     Using a specified destination file.
 *   - help:        Print help.
 *   - object:      The Object being written is specified.
 *   - print_first: When set, print new line to message output on program begin after loading settings.
 *   - print_last:  When set, print new line to message output on program end.
 *   - print_last:  The Object being written is specified.
 *   - version:     Print version.
 *   - wrap:        Wrap the vocabulary.
 */
#ifndef _di_iki_write_main_flag_e_
  enum {
    iki_write_main_flag_none_e        = 0x0,
    iki_write_main_flag_content_e     = 0x1,
    iki_write_main_flag_copyright_e   = 0x2,
    iki_write_main_flag_file_to_e     = 0x4,
    iki_write_main_flag_help_e        = 0x8,
    iki_write_main_flag_object_e      = 0x10,
    iki_write_main_flag_print_first_e = 0x20,
    iki_write_main_flag_print_last_e  = 0x40,
    iki_write_main_flag_version_e     = 0x80,
    iki_write_main_flag_wrap_e        = 0x100,
  }; // enum
#endif // _di_iki_write_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_iki_write_parameter_e_
  enum {
    iki_write_parameter_help_e,
    iki_write_parameter_copyright_e,
    iki_write_parameter_light_e,
    iki_write_parameter_dark_e,
    iki_write_parameter_no_color_e,
    iki_write_parameter_verbosity_quiet_e,
    iki_write_parameter_verbosity_error_e,
    iki_write_parameter_verbosity_normal_e,
    iki_write_parameter_verbosity_verbose_e,
    iki_write_parameter_verbosity_debug_e,
    iki_write_parameter_version_e,
    iki_write_parameter_line_first_no_e,
    iki_write_parameter_line_last_no_e,

    iki_write_parameter_backtick_e,
    iki_write_parameter_content_e,
    iki_write_parameter_double_e,
    iki_write_parameter_file_e,
    iki_write_parameter_object_e,
    iki_write_parameter_single_e,
    iki_write_parameter_wrap_e,
  }; // enum

  #define iki_write_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(iki_write_short_backtick_s, iki_write_long_backtick_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_content_s,  iki_write_long_content_s,  1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_double_s,   iki_write_long_double_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_file_s,     iki_write_long_file_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_object_s,   iki_write_long_object_s,   1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_single_s,   iki_write_long_single_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_write_short_wrap_s,     iki_write_long_wrap_s,     0, f_console_flag_normal_e), \
    }

  #define iki_write_parameter_total_d 20
#endif // _di_iki_write_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * iki_write_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_iki_write_print_flag_e_
  enum {
    iki_write_print_flag_none_e    = 0x0,
    iki_write_print_flag_debug_e   = 0x1,
    iki_write_print_flag_error_e   = 0x2,
    iki_write_print_flag_file_e    = 0x4,
    iki_write_print_flag_in_e      = 0x8,
    iki_write_print_flag_out_e     = 0x10,
    iki_write_print_flag_message_e = 0x20,
    iki_write_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_iki_write_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_enumeration_h

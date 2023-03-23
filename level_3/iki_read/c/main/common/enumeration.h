/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_enumeration_h
#define _iki_read_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * iki_read_main_flag_*_e:
 *   - none:        No flags set.
 *   - at:          Selecting at a specific index.
 *   - content:     Print Contents.
 *   - copyright:   Print copyright.
 *   - help:        Print help.
 *   - literal:     Print as literal data (printing entire variable).
 *   - line:        Selecting at a specific line.
 *   - name:        Selecting using a specific Vocabulary name.
 *   - object:      Print Objects.
 *   - print_first: When set, print new line to message output on program begin after loading settings.
 *   - print_last:  When set, print new line to message output on program end.
 *   - replace:     Using re-assignments.
 *   - replace:     Using replacements.
 *   - substitute:  Using substitutions.
 *   - total:       Enable printing of "total" count.
 *   - version:     Print version.
 *   - whole:       Print all data.
 *   - wrap:        Using wrapping.
 */
#ifndef _di_iki_read_main_flag_e_
  enum {
    iki_read_main_flag_none_e        = 0x0,
    iki_read_main_flag_at_e          = 0x1,
    iki_read_main_flag_content_e     = 0x2,
    iki_read_main_flag_copyright_e   = 0x4,
    iki_read_main_flag_help_e        = 0x8,
    iki_read_main_flag_literal_e     = 0x10,
    iki_read_main_flag_line_e        = 0x20,
    iki_read_main_flag_name_e        = 0x40,
    iki_read_main_flag_object_e      = 0x80,
    iki_read_main_flag_print_first_e = 0x100,
    iki_read_main_flag_print_last_e  = 0x200,
    iki_read_main_flag_reassign_e    = 0x400,
    iki_read_main_flag_replace_e     = 0x800,
    iki_read_main_flag_substitute_e  = 0x1000,
    iki_read_main_flag_total_e       = 0x2000,
    iki_read_main_flag_version_e     = 0x4000,
    iki_read_main_flag_whole_e       = 0x8000,
    iki_read_main_flag_wrap_e        = 0x10000,
  }; // enum
#endif // _di_iki_read_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_iki_read_parameter_e_
  enum {
    iki_read_parameter_help_e,
    iki_read_parameter_copyright_e,
    iki_read_parameter_light_e,
    iki_read_parameter_dark_e,
    iki_read_parameter_no_color_e,
    iki_read_parameter_verbosity_quiet_e,
    iki_read_parameter_verbosity_error_e,
    iki_read_parameter_verbosity_normal_e,
    iki_read_parameter_verbosity_verbose_e,
    iki_read_parameter_verbosity_debug_e,
    iki_read_parameter_version_e,
    iki_read_parameter_line_first_no_e,
    iki_read_parameter_line_last_no_e,

    iki_read_parameter_at_e,
    iki_read_parameter_content_e,
    iki_read_parameter_line_e,
    iki_read_parameter_literal_e,
    iki_read_parameter_name_e,
    iki_read_parameter_object_e,
    iki_read_parameter_reassign_e,
    iki_read_parameter_replace_e,
    iki_read_parameter_substitute_e,
    iki_read_parameter_total_e,
    iki_read_parameter_whole_e,
    iki_read_parameter_wrap_e,
  }; // enum

  #define iki_read_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize_3(iki_read_short_at_s,         iki_read_long_at_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_content_s,    iki_read_long_content_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_line_s,       iki_read_long_line_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_literal_s,    iki_read_long_literal_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_name_s,       iki_read_long_name_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_object_s,     iki_read_long_object_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_reassign_s,   iki_read_long_reassign_s,   3, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_replace_s,    iki_read_long_replace_s,    2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_substitute_s, iki_read_long_substitute_s, 3, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_total_s,      iki_read_long_total_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_whole_s,      iki_read_long_whole_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_wrap_s,       iki_read_long_wrap_s,       3, f_console_flag_normal_e), \
    }

  #define iki_read_total_parameters_d 25
#endif // _di_iki_read_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * iki_read_print_flag_*_e:
 *   - none:      No flags set.
 *   - debug:     Stream is for debug printing.
 *   - error:     Stream is for error printing.
 *   - message:   Stream is for message printing.
 *   - warning:   Stream is for warning printing.
 *   - file_to:   Stream is a destination file.
 *   - file_from: Stream is a source file.
 */
#ifndef _di_iki_read_print_flag_e_
  enum {
    iki_read_print_flag_none_e      = 0x0,
    iki_read_print_flag_debug_e     = 0x1,
    iki_read_print_flag_error_e     = 0x2,
    iki_read_print_flag_message_e   = 0x4,
    iki_read_print_flag_warning_e   = 0x8,
    iki_read_print_flag_file_to_e   = 0x10,
    iki_read_print_flag_file_from_e = 0x20,
  }; // enum
#endif // _di_iki_read_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_enumeration_h

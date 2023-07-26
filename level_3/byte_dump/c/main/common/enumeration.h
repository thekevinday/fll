/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_common_enumeration_h
#define _byte_dump_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Byte Dump modes.
 *
 * byte_dump_mode_*_e:
 *   - hexidecimal: Display using hexidecimal notation (base 16).
 *   - duodecimal:  Display using duodecimal notation (base 12).
 *   - octal:       Display using octal notation (base 8).
 *   - binary:      Display using binary notation (base 2).
 *   - decimal:     Display using decimal notation (base 10).
 */
#ifndef _di_byte_dump_modes_e_
  enum {
    byte_dump_mode_hexidecimal_e = 1,
    byte_dump_mode_duodecimal_e,
    byte_dump_mode_octal_e,
    byte_dump_mode_binary_e,
    byte_dump_mode_decimal_e,
  }; // enum
#endif // _di_byte_dump_modes_e_

/**
 * Byte Dump presentations.
 *
 * byte_dump_presentation_*_e:
 *   - normal:  Normal presentation mode.
 *   - simple:  Simple presentation mode.
 *   - classic: Classic presentation mode.
 */
#ifndef _di_byte_dump_presentations_e_
  enum {
    byte_dump_presentation_normal_e = 1,
    byte_dump_presentation_simple_e,
    byte_dump_presentation_classic_e,
  }; // enum
#endif // _di_byte_dump_presentations_e_

/**
 * Flags passed to the main function or program.
 *
 * byte_dump_main_flag_*_e:
 *   - none:        No flags set.
 *   - classic:     Classic is specified.
 *   - copyright:   Print the copyright.
 *   - first:       The first position is specified.
 *   - help:        Print help.
 *   - last:        The last position is specified.
 *   - placeholder: Placeholder is specified.
 *   - pipe:        Use the input pipe.
 *   - print_first: When set, print new line to message output on program begin after loading settings.
 *   - print_last:  When set, print new line to message output on program end.
 *   - text:        Text is specified.
 *   - unicode:     Unicode is specified.
 *   - version:     Print version.
 *   - wide:        Wide option is specified for printing wide.
 */
#ifndef _di_byte_dump_main_flag_e_
  enum {
    byte_dump_main_flag_none_e        = 0x0,
    byte_dump_main_flag_classic_e     = 0x1,
    byte_dump_main_flag_copyright_e   = 0x2,
    byte_dump_main_flag_first_e       = 0x4,
    byte_dump_main_flag_help_e        = 0x8,
    byte_dump_main_flag_last_e        = 0x10,
    byte_dump_main_flag_pipe_e        = 0x20,
    byte_dump_main_flag_placeholder_e = 0x40,
    byte_dump_main_flag_print_first_e = 0x80,
    byte_dump_main_flag_print_last_e  = 0x100,
    byte_dump_main_flag_text_e        = 0x200,
    byte_dump_main_flag_unicode_e     = 0x400,
    byte_dump_main_flag_version_e     = 0x800,
    byte_dump_main_flag_wide_e        = 0x1000,
  }; // enum
#endif // _di_byte_dump_main_flag_e_

/**
 * The program parameters.
 *
 * byte_dump_parameter_*_e:
 *   - first: First offset byte size.
 *   - last:  Last offset byte size.
 *
 *   - narrow:      Each character in the displyed text will take at least 1 columns.
 *   - placeholder: Display (colored) placeholders to signify codes that are UTF-8 fragments.
 *   - text:        Display text
 *   - wide:        Each character in the displyed text will take at least 2 columns.
 *   - width:       Number of characters to display per row.
 *
 *   - binary:      Display using binary format.
 *   - decimal:     Display using decimal format.
 *   - duodecimal:  Display using duodecimal format.
 *   - hexidecimal: Display using hexidecimal format.
 *   - octal:       Display using octal format.
 *   - unicode:     Display using Unicode format.
 *
 *   - normal:  Use normal presentation, displaying UTF-8 sequence codes for ASCII special codes.
 *   - simple:  Use simple presentation, displaying spaces for ASCII special codes instead of UTF-8 sequence codes.
 *   - classic: Use classic presentation, displaying periods for ASCII special codes instead of UTF-8 sequence codes.
 */
#ifndef _di_byte_dump_parameter_e_
  enum {
    byte_dump_parameter_help_e,
    byte_dump_parameter_copyright_e,
    byte_dump_parameter_light_e,
    byte_dump_parameter_dark_e,
    byte_dump_parameter_no_color_e,
    byte_dump_parameter_verbosity_quiet_e,
    byte_dump_parameter_verbosity_error_e,
    byte_dump_parameter_verbosity_normal_e,
    byte_dump_parameter_verbosity_verbose_e,
    byte_dump_parameter_verbosity_debug_e,
    byte_dump_parameter_version_e,
    byte_dump_parameter_line_first_no_e,
    byte_dump_parameter_line_last_no_e,

    byte_dump_parameter_binary_e,
    byte_dump_parameter_decimal_e,
    byte_dump_parameter_duodecimal_e,
    byte_dump_parameter_hexidecimal_e,
    byte_dump_parameter_octal_e,
    byte_dump_parameter_unicode_e,

    byte_dump_parameter_first_e,
    byte_dump_parameter_last_e,

    byte_dump_parameter_narrow_e,
    byte_dump_parameter_placeholder_e,
    byte_dump_parameter_text_e,
    byte_dump_parameter_wide_e,
    byte_dump_parameter_width_e,

    byte_dump_parameter_normal_e,
    byte_dump_parameter_simple_e,
    byte_dump_parameter_classic_e,
  }; // enum

  #define byte_dump_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_binary_s,      byte_dump_long_binary_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_decimal_s,     byte_dump_long_decimal_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_duodecimal_s,  byte_dump_long_duodecimal_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_hexidecimal_s, byte_dump_long_hexidecimal_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_octal_s,       byte_dump_long_octal_s,       0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_unicode_s,     byte_dump_long_unicode_s,     0, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_first_s,       byte_dump_long_first_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_last_s,        byte_dump_long_last_s,        1, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_narrow_s,      byte_dump_long_narrow_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_placeholder_s, byte_dump_long_placeholder_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_text_s,        byte_dump_long_text_s,        0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_wide_s,        byte_dump_long_wide_s,        0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(byte_dump_short_width_s,       byte_dump_long_width_s,       1, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_5(byte_dump_long_normal_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(byte_dump_long_simple_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(byte_dump_long_classic_s, 0, f_console_flag_normal_e), \
    }

  #define byte_dump_parameter_total_d 29
#endif // _di_byte_dump_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * byte_dump_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_byte_dump_print_flag_e_
  enum {
    byte_dump_print_flag_none_e    = 0x0,
    byte_dump_print_flag_debug_e   = 0x1,
    byte_dump_print_flag_error_e   = 0x2,
    byte_dump_print_flag_file_e    = 0x4,
    byte_dump_print_flag_in_e      = 0x8,
    byte_dump_print_flag_out_e     = 0x10,
    byte_dump_print_flag_message_e = 0x20,
    byte_dump_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_byte_dump_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_common_enumeration_h

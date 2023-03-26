/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_enumeration_h
#define _utf8_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Modes used to designate how to the input and output are to be processed.
 *
 * utf8_mode_*_e:
 *   - none: No flags set.
 *
 * utf8_mode_from_*_e:
 *   - bytesequence: The input format is bytesequence.
 *   - codepoint:    The input format is codepoint (U+XXXX or U+XXXXXX).
 *
 * utf8_mode_to_*_e:
 *   - bytesequence: The output format is bytesequence.
 *   - codepoint:    The output format is codepoint (U+XXXX or U+XXXXXX).
 *   - combining:    The output format is whether or not character is combining (may be used with "width").
 *   - width:        The output format is how wide the character is (may be used with "combining").
 */
#ifndef _di_utf8_modes_e_
  enum {
    utf8_mode_none_e              = 0x0,
    utf8_mode_from_bytesequence_e = 0x1,
    utf8_mode_from_codepoint_e    = 0x2,
    utf8_mode_to_bytesequence_e   = 0x4,
    utf8_mode_to_codepoint_e      = 0x8,
    utf8_mode_to_combining_e      = 0x10,
    utf8_mode_to_width_e          = 0x20,
  }; // enum
#endif // _di_utf8_modes_e_

/**
 * Flags passed to the main function or program.
 *
 * utf8_main_flag_*_e:
 *   - none:          No flags set.
 *   - copyright:     Print the copyright.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file.
 *   - header:        Enable printing of headers.
 *   - help:          Print help.
 *   - pipe:          Use the input pipe.
 *   - print_first:   When set, print new line to message output on program begin after loading settings.
 *   - print_last:    When set, print new line to message output on program end.
 *   - separate:      Enable printing of separators.
 *   - strip_invalid: Using strip invalid character mode.
 *   - verify:        Using verify mode.
 *   - version:       Print version.
 */
#ifndef _di_utf8_main_flag_e_
  enum {
    utf8_main_flag_none_e          = 0x0,
    utf8_main_flag_copyright_e     = 0x1,
    utf8_main_flag_file_from_e     = 0x2,
    utf8_main_flag_file_to_e       = 0x4,
    utf8_main_flag_header_e        = 0x8,
    utf8_main_flag_help_e          = 0x10,
    utf8_main_flag_pipe_e          = 0x20,
    utf8_main_flag_print_first_e   = 0x40,
    utf8_main_flag_print_last_e    = 0x80,
    utf8_main_flag_separate_e      = 0x100,
    utf8_main_flag_strip_invalid_e = 0x200,
    utf8_main_flag_verify_e        = 0x400,
    utf8_main_flag_version_e       = 0x800,
  }; // enum
#endif // _di_utf8_main_flag_e_

/**
 * Codepoint modes for converting to/from binary and codepoint values.
 *
 * The special "raw" format is used only for reading from codepoint format where that format represents binary character that is not a valid Unicode character.
 * This is intended to be used to save and restore the original binary data even if that data is invalid.
 *
 * private_utf8_codepoint_mode_*:
 *   - ready:      The codepoint has yet to be processed, skip leading spaces until first 'U' is matched.
 *   - begin:      The first 'U' is matched, look for the '+'.
 *   - number:     The '+' is matched, process numbers.
 *   - end:        The last number is reached (at either white space or EOS/EOF).
 *   - bad:        This is not a valid codepoint.
 *   - bad_begin:  This is the beginning of an invalid codepoint.
 *   - bad_end:    The end of bad is detected, which happens on white space or end of buffer.
 *   - raw_begin:  This is the beginning of a potential raw data (matched '0').
 *   - raw_number: This is the confirmed beginning of raw data (matched 'X'), process numbers.
 *   - raw_end:    The end of raw data is detected, which happens on white space or end of buffer.
 */
#ifndef _di_utf8_codepoint_modes_
  enum {
    utf8_codepoint_mode_ready_e = 1,
    utf8_codepoint_mode_begin_e,
    utf8_codepoint_mode_number_e,
    utf8_codepoint_mode_end_e,
    utf8_codepoint_mode_bad_e,
    utf8_codepoint_mode_bad_begin_e,
    utf8_codepoint_mode_bad_end_e,
    utf8_codepoint_mode_raw_begin_e,
    utf8_codepoint_mode_raw_number_e,
    utf8_codepoint_mode_raw_end_e,
  }; // enum
#endif // _di__utf8_codepoint_modes_

/**
 * The main program parameters.
 */
#ifndef _di_utf8_parameter_e_
  enum {
    utf8_parameter_help_e,
    utf8_parameter_copyright_e,
    utf8_parameter_light_e,
    utf8_parameter_dark_e,
    utf8_parameter_no_color_e,
    utf8_parameter_verbosity_quiet_e,
    utf8_parameter_verbosity_error_e,
    utf8_parameter_verbosity_normal_e,
    utf8_parameter_verbosity_verbose_e,
    utf8_parameter_verbosity_debug_e,
    utf8_parameter_version_e,
    utf8_parameter_line_first_no_e,
    utf8_parameter_line_last_no_e,

    utf8_parameter_from_bytesequence_e,
    utf8_parameter_from_codepoint_e,
    utf8_parameter_from_file_e,

    utf8_parameter_headers_e,
    utf8_parameter_separate_e,
    utf8_parameter_strip_invalid_e,

    utf8_parameter_to_bytesequence_e,
    utf8_parameter_to_codepoint_e,
    utf8_parameter_to_combining_e,
    utf8_parameter_to_file_e,
    utf8_parameter_to_width_e,

    utf8_parameter_verify_e,
  }; // enum

  #define utf8_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(utf8_short_from_bytesequence_s, utf8_long_from_bytesequence_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_from_codepoint_s,    utf8_long_from_codepoint_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_from_file_s,         utf8_long_from_file_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_headers_s,           utf8_long_headers_s,           0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_separate_s,          utf8_long_separate_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_strip_invalid_s,     utf8_long_strip_invalid_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_to_bytesequence_s,   utf8_long_to_bytesequence_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_to_codepoint_s,      utf8_long_to_codepoint_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_to_combining_s,      utf8_long_to_combining_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_to_file_s,           utf8_long_to_file_s,           1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_to_width_s,          utf8_long_to_width_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(utf8_short_verify_s,            utf8_long_verify_s,            0, f_console_flag_normal_e), \
    }

  #define utf8_total_parameters_d 25
#endif // _di_utf8_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * utf8_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_utf8_print_flag_e_
  enum {
    utf8_print_flag_none_e    = 0x0,
    utf8_print_flag_debug_e   = 0x1,
    utf8_print_flag_error_e   = 0x2,
    utf8_print_flag_file_e    = 0x4,
    utf8_print_flag_in_e      = 0x8,
    utf8_print_flag_out_e     = 0x10,
    utf8_print_flag_message_e = 0x20,
    utf8_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_utf8_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_enumeration_h

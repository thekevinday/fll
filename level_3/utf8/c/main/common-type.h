/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_type_h
#define _utf8_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_utf8_default_d_
  #define utf8_default_allocation_step_d 16
#endif // _di_utf8_default_d_

/**
 * The program defines.
 */
#ifndef _di_utf8_d_
  #define utf8_signal_check_d 20000
#endif // _di_utf8_d_

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
 *   - none:           No flags set.
 *   - copyright:      Print the copyright.
 *   - file_from:      Using a specified source file.
 *   - file_to:        Using a specified destination file.
 *   - header:         Enable printing of headers.
 *   - help:           Print help.
 *   - pipe:           Use the input pipe.
 *   - separate:       Enable printing of separators.
 *   - strip_invalid:  Using strip invalid character mode.
 *   - verify:         Using verify mode.
 *   - version:        Print version.
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
    utf8_main_flag_separate_e      = 0x40,
    utf8_main_flag_strip_invalid_e = 0x80,
    utf8_main_flag_verify_e        = 0x100,
    utf8_main_flag_version_e       = 0x200,
  }; // enum
#endif // _di_utf8_main_flag_e_

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
 * The utf8 main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * mode: The input/output mode (see utf8_modes_e).
 * flag: Flags passed to the main function.
 *
 * state: The state information.
 *
 * valid:     Designate the output context set for valid characters.
 * valid_not: Designate the output context set for invalid characters.
 *
 * append:  A string to append. A value of NULL results in not appending.
 * prepend: A string to prepend. A value of NULL results in not prepending.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 *
 * buffer: A buffer to use for printing output (generally for storing a block of input from an input file).
 * text:   A buffer for storing a series of characters for processing (generally for code point processing).
 *
 * path_files_from: An array of all "from" file paths for when the flag utf8_main_flag_file_from_e is set.
 * path_files_to:   An array of all "to" file paths for when the flag utf8_main_flag_file_to_e is set.
 * remaining:       An array containing all remaining arguments passed to the program.
 */
#ifndef _di_utf8_setting_t_
  typedef struct {
    uint8_t mode;
    uint16_t flag;

    f_state_t state;

    f_color_set_t valid;
    f_color_set_t valid_not;

    f_string_static_t append;
    f_string_static_t prepend;

    f_string_static_t line_first;
    f_string_static_t line_last;

    f_string_dynamic_t buffer;
    f_string_dynamic_t text;

    f_string_dynamics_t path_files_from;
    f_string_dynamics_t path_files_to;
    f_string_dynamics_t remaining;
  } utf8_setting_t;

  #define utf8_setting_t_initialize \
    { \
      utf8_mode_from_bytesequence_e | utf8_mode_to_codepoint_e, \
      utf8_main_flag_none_e, \
      f_state_initialize_t, \
      f_color_set_t_initialize, \
      f_color_set_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_eol_s, \
      f_string_eol_s, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_utf8_setting_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_type_h

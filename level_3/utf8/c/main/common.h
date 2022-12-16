/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_h
#define _utf8_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_utf8_program_version_s_
  #define UTF8_program_version_major_s F_string_ascii_0_s
  #define UTF8_program_version_minor_s F_string_ascii_7_s
  #define UTF8_program_version_micro_s F_string_ascii_0_s

  #define UTF8_program_version_major_s_length F_string_ascii_0_s_length
  #define UTF8_program_version_minor_s_length F_string_ascii_7_s_length
  #define UTF8_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(UTF8_program_version_nano_prefix_s) && defined(UTF8_program_version_nano_prefix_s_length))
    #define UTF8_program_version_nano_prefix_s
    #define UTF8_program_version_nano_prefix_s_length 0
  #endif // !(defined(UTF8_program_version_nano_prefix_s) && defined(UTF8_program_version_nano_prefix_s_length))

  #if !(defined(UTF8_program_version_nano_s) && defined(UTF8_program_version_nano_s_length))
    #define UTF8_program_version_nano_s
    #define UTF8_program_version_nano_s_length 0
  #endif // !(defined(UTF8_program_version_nano_s) && defined(UTF8_program_version_nano_s_length))

  #define UTF8_program_version_s UTF8_program_version_major_s F_string_ascii_period_s UTF8_program_version_minor_s F_string_ascii_period_s UTF8_program_version_micro_s UTF8_program_version_nano_prefix_s UTF8_program_version_nano_s

  #define UTF8_program_version_s_length UTF8_program_version_major_s_length + F_string_ascii_period_s_length + UTF8_program_version_minor_s_length + F_string_ascii_period_s_length + UTF8_program_version_micro_s_length + UTF8_program_version_nano_prefix_s_length + UTF8_program_version_nano_s_length

  extern const f_string_static_t utf8_program_version_s;
#endif // _di_utf8_program_version_s_

/**
 * The program name.
 */
#ifndef _di_utf8_program_name_s_
  #define UTF8_program_name_s      "utf8"
  #define UTF8_program_name_long_s "UTF-8"

  #define UTF8_program_name_s_length      4
  #define UTF8_program_name_long_s_length 5

  extern const f_string_static_t utf8_program_name_s;
  extern const f_string_static_t utf8_program_name_long_s;
#endif // _di_utf8_program_name_s_

/**
 * The program help related data.
 */
#ifndef _di_utf8_program_help_parameters_s_
  #define UTF8_program_help_parameters_s "character(s)"
  #define UTF8_program_help_parameters_s_length 12

  extern const f_string_static_t utf8_program_help_parameters_s;
#endif // _di_utf8_program_help_parameters_s_

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
 * The program strings.
 */
#ifndef _di_utf8_s_
  #define UTF8_string_combining_is_s  "C"
  #define UTF8_string_combining_not_s "N"
  #define UTF8_string_unknown_s       "?"

  #define UTF8_string_from_s "from"
  #define UTF8_string_to_s   "to"

  #define UTF8_string_prepend_padding_s "  "

  #define UTF8_string_valid_not_s "�"

  #define UTF8_string_verified_valid_s     "Verified Valid"
  #define UTF8_string_verified_valid_not_s "Verified Invalid"

  #define UTF8_string_width_0_s "0"
  #define UTF8_string_width_1_s "1"
  #define UTF8_string_width_2_s "2"
  #define UTF8_string_width_3_s "3"
  #define UTF8_string_width_4_s "4"

  #define UTF8_string_combining_is_s_length  1
  #define UTF8_string_combining_not_s_length 1
  #define UTF8_string_unknown_s_length       1

  #define UTF8_string_from_s_length 4
  #define UTF8_string_to_s_length   2

  #define UTF8_string_prepend_padding_s_length 2

  #define UTF8_string_valid_not_s_length 3

  #define UTF8_string_verified_valid_s_length     14
  #define UTF8_string_verified_valid_not_s_length 16

  #define UTF8_string_width_0_s_length 1
  #define UTF8_string_width_1_s_length 1
  #define UTF8_string_width_2_s_length 1
  #define UTF8_string_width_3_s_length 1
  #define UTF8_string_width_4_s_length 1

  extern const f_string_static_t utf8_string_combining_is_s;
  extern const f_string_static_t utf8_string_combining_not_s;
  extern const f_string_static_t utf8_string_unknown_s;

  extern const f_string_static_t utf8_string_from_s;
  extern const f_string_static_t utf8_string_to_s;

  extern const f_string_static_t utf8_string_prepend_padding_s;

  extern const f_string_static_t utf8_string_verified_valid_s;
  extern const f_string_static_t utf8_string_verified_valid_not_s;

  extern const f_string_static_t utf8_string_width_0_s;
  extern const f_string_static_t utf8_string_width_1_s;
  extern const f_string_static_t utf8_string_width_2_s;
  extern const f_string_static_t utf8_string_width_3_s;
  extern const f_string_static_t utf8_string_width_4_s;

  extern const f_string_static_t utf8_string_valid_not_s;
#endif // _di_utf8_s_

/**
 * The main program parameters.
 */
#ifndef _di_utf8_parameter_d_
  #define UTF8_short_from_bytesequence_s "b"
  #define UTF8_short_from_codepoint_s    "c"
  #define UTF8_short_from_file_s         "f"

  #define UTF8_short_headers_s       "H"
  #define UTF8_short_separate_s      "S"
  #define UTF8_short_strip_invalid_s "s"
  #define UTF8_short_verify_s        "v"

  #define UTF8_short_to_bytesequence_s "B"
  #define UTF8_short_to_codepoint_s    "C"
  #define UTF8_short_to_combining_s    "O"
  #define UTF8_short_to_file_s         "F"
  #define UTF8_short_to_width_s        "W"

  #define UTF8_long_from_bytesequence_s "from_bytesequence"
  #define UTF8_long_from_codepoint_s    "from_codepoint"
  #define UTF8_long_from_file_s         "from_file"

  #define UTF8_long_headers_s       "headers"
  #define UTF8_long_separate_s      "separate"
  #define UTF8_long_strip_invalid_s "strip_invalid"
  #define UTF8_long_verify_s        "verify"

  #define UTF8_long_to_bytesequence_s "to_bytesequence"
  #define UTF8_long_to_codepoint_s    "to_codepoint"
  #define UTF8_long_to_combining_s    "to_combining"
  #define UTF8_long_to_file_s         "to_file"
  #define UTF8_long_to_width_s        "to_width"

  #define UTF8_short_from_bytesequence_s_length  1
  #define UTF8_short_from_codepoint_s_length 1
  #define UTF8_short_from_file_s_length      1

  #define UTF8_short_headers_s_length       1
  #define UTF8_short_separate_s_length      1
  #define UTF8_short_strip_invalid_s_length 1
  #define UTF8_short_verify_s_length        1

  #define UTF8_short_to_bytesequence_s_length  1
  #define UTF8_short_to_codepoint_s_length 1
  #define UTF8_short_to_combining_s_length 1
  #define UTF8_short_to_file_s_length      1
  #define UTF8_short_to_width_s_length     1

  #define UTF8_long_from_bytesequence_s_length 17
  #define UTF8_long_from_codepoint_s_length    14
  #define UTF8_long_from_file_s_length         9

  #define UTF8_long_headers_s_length       7
  #define UTF8_long_separate_s_length      8
  #define UTF8_long_strip_invalid_s_length 13
  #define UTF8_long_verify_s_length        6

  #define UTF8_long_to_bytesequence_s_length 15
  #define UTF8_long_to_codepoint_s_length    12
  #define UTF8_long_to_combining_s_length    12
  #define UTF8_long_to_file_s_length         7
  #define UTF8_long_to_width_s_length        8

  extern const f_string_static_t utf8_short_from_bytesequence_s;
  extern const f_string_static_t utf8_short_from_codepoint_s;
  extern const f_string_static_t utf8_short_from_file_s;

  extern const f_string_static_t utf8_short_headers_s;
  extern const f_string_static_t utf8_short_separate_s;
  extern const f_string_static_t utf8_short_strip_invalid_s;
  extern const f_string_static_t utf8_short_verify_s;

  extern const f_string_static_t utf8_short_to_bytesequence_s;
  extern const f_string_static_t utf8_short_to_codepoint_s;
  extern const f_string_static_t utf8_short_to_combining_s;
  extern const f_string_static_t utf8_short_to_file_s;
  extern const f_string_static_t utf8_short_to_width_s;

  extern const f_string_static_t utf8_long_from_bytesequence_s;
  extern const f_string_static_t utf8_long_from_codepoint_s;
  extern const f_string_static_t utf8_long_from_file_s;

  extern const f_string_static_t utf8_long_headers_s;
  extern const f_string_static_t utf8_long_separate_s;
  extern const f_string_static_t utf8_long_strip_invalid_s;
  extern const f_string_static_t utf8_long_verify_s;

  extern const f_string_static_t utf8_long_to_bytesequence_s;
  extern const f_string_static_t utf8_long_to_codepoint_s;
  extern const f_string_static_t utf8_long_to_combining_s;
  extern const f_string_static_t utf8_long_to_file_s;
  extern const f_string_static_t utf8_long_to_width_s;

  enum {
    utf8_parameter_help_e,
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
      macro_f_console_parameter_t_initialize4(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e, 0), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e, 0), \
      \
      macro_f_console_parameter_t_initialize4(utf8_short_from_bytesequence_s, utf8_long_from_bytesequence_s, 0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_from_codepoint_s,    utf8_long_from_codepoint_s,    0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_from_file_s,         utf8_long_from_file_s,         1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_headers_s,           utf8_long_headers_s,           0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_separate_s,          utf8_long_separate_s,          0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_strip_invalid_s,     utf8_long_strip_invalid_s,     0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_to_bytesequence_s,   utf8_long_to_bytesequence_s,   0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_to_codepoint_s,      utf8_long_to_codepoint_s,      0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_to_combining_s,      utf8_long_to_combining_s,      0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_to_file_s,           utf8_long_to_file_s,           1, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_to_width_s,          utf8_long_to_width_s,          0, f_console_flag_normal_e, 0), \
      macro_f_console_parameter_t_initialize4(utf8_short_verify_s,            utf8_long_verify_s,            0, f_console_flag_normal_e, 0), \
    }

  #define utf8_total_parameters_d 24
#endif // _di_utf8_parameter_d_

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
    utf8_main_flag_file_from_e     = 0x1,
    utf8_main_flag_file_to_e       = 0x2,
    utf8_main_flag_header_e        = 0x4,
    utf8_main_flag_help_e          = 0x8,
    utf8_main_flag_pipe_e          = 0x10,
    utf8_main_flag_separate_e      = 0x20,
    utf8_main_flag_strip_invalid_e = 0x40,
    utf8_main_flag_verify_e        = 0x80,
    utf8_main_flag_version_e       = 0x100,
  }; // enum
#endif // _di_utf8_main_flag_e_

/**
 * The utf8 main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * mode: The input/output mode (see utf8_modes_e).
 * flag: Flags passed to the main function.
 *
 * status: The main status code, generally used by the load settings and main functions.
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

    f_status_t status;

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
      F_none, \
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

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_utf8_setting_delete_
  extern f_status_t utf8_setting_delete(utf8_setting_t * const setting);
#endif // _di_utf8_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
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
#ifndef _di_utf8_setting_load_
  extern void utf8_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
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
#ifndef _di_utf8_setting_unload_
  extern f_status_t utf8_setting_unload(fll_program_data_t * const main, utf8_setting_t * const setting);
#endif // _di_utf8_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_h

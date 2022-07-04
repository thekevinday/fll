/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.6
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
#ifndef _di_utf8_program_version_
  #define UTF8_program_version_major_s F_string_ascii_0_s
  #define UTF8_program_version_minor_s F_string_ascii_6_s
  #define UTF8_program_version_micro_s F_string_ascii_0_s

  #define UTF8_program_version_major_s_length F_string_ascii_0_s_length
  #define UTF8_program_version_minor_s_length F_string_ascii_6_s_length
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
#endif // _di_utf8_program_version_

/**
 * The program name.
 */
#ifndef _di_utf8_program_name_
  #define UTF8_program_name_s      "utf8"
  #define UTF8_program_name_long_s "UTF-8"

  #define UTF8_program_name_s_length      4
  #define UTF8_program_name_long_s_length 5

  extern const f_string_static_t utf8_program_name_s;
  extern const f_string_static_t utf8_program_name_long_s;
#endif // _di_utf8_program_name_

/**
 * The program help related data.
 */
#ifndef _di_utf8_program_help_parameters_
  #define UTF8_program_help_parameters_s "character(s)"
  #define UTF8_program_help_parameters_s_length 12

  extern const f_string_static_t utf8_program_help_parameters_s;
#endif // _di_utf8_program_help_parameters_

/**
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_utf8_default_allocation_step_
  #define utf8_default_allocation_step_d 16
#endif // _di_utf8_default_allocation_step_

/**
 * The program defines.
 */
#ifndef _di_utf8_defines_
  #define utf8_signal_check_d 20000

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
#endif // _di_utf8_defines_

/**
 * The main program parameters.
 */
#ifndef _di_utf8_parameters_
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
    utf8_parameter_verbosity_normal_e,
    utf8_parameter_verbosity_verbose_e,
    utf8_parameter_verbosity_debug_e,
    utf8_parameter_version_e,

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
  };

  #define utf8_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(utf8_short_from_bytesequence_s.string, utf8_long_from_bytesequence_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_from_codepoint_s.string, utf8_long_from_codepoint_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_from_file_s.string, utf8_long_from_file_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_headers_s.string, utf8_long_headers_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_separate_s.string, utf8_long_headers_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_strip_invalid_s.string, utf8_long_strip_invalid_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_bytesequence_s.string, utf8_long_to_bytesequence_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_codepoint_s.string, utf8_long_to_codepoint_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_combining_s.string, utf8_long_to_combining_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_file_s.string, utf8_long_to_file_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_to_width_s.string, utf8_long_to_width_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(utf8_short_verify_s.string, utf8_long_verify_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define utf8_total_parameters_d 21
#endif // _di_utf8_parameters_

/**
 * Modes used to designate how to the input and output are to be processed.
 *
 * utf8_mode_from_*:
 *   - bytesequence: The input format is bytesequence.
 *   - codepoint:    The input format is codepoint (U+XXXX or U+XXXXXX).
 *
 * utf8_mode_to_*:
 *   - bytesequence: The outout format is bytesequence.
 *   - codepoint:    The outout format is codepoint (U+XXXX or U+XXXXXX).
 *   - combining:    The outout format is whether or not character is combining (may be used with "width").
 *   - width:        The outout format is how wide the character is (may be used with "combining").
 */
#ifndef _di_utf8_modes_
  #define utf8_mode_from_bytesequence_d 0x1
  #define utf8_mode_from_codepoint_d    0x2
  #define utf8_mode_to_bytesequence_d   0x4
  #define utf8_mode_to_codepoint_d      0x8
  #define utf8_mode_to_combining_d      0x10
  #define utf8_mode_to_width_d          0x20
#endif // _di_utf8_modes_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_h

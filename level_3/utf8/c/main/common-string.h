/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_string_h
#define _utf8_common_string_h

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
#ifndef _di_utf8_parameter_s_
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
#endif // _di_utf8_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_string_h

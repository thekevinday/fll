/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_common_string_h
#define _byte_dump_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_byte_dump_program_version_d_
  #define BYTE_DUMP_program_version_major_s F_string_ascii_0_s
  #define BYTE_DUMP_program_version_minor_s F_string_ascii_7_s
  #define BYTE_DUMP_program_version_micro_s F_string_ascii_0_s

  #define BYTE_DUMP_program_version_major_s_length F_string_ascii_0_s_length
  #define BYTE_DUMP_program_version_minor_s_length F_string_ascii_7_s_length
  #define BYTE_DUMP_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(BYTE_DUMP_program_version_nano_prefix_s) && defined(BYTE_DUMP_program_version_nano_prefix_s_length))
    #define BYTE_DUMP_program_version_nano_prefix_s
    #define BYTE_DUMP_program_version_nano_prefix_s_length 0
  #endif // !(defined(BYTE_DUMP_program_version_nano_prefix_s) && defined(BYTE_DUMP_program_version_nano_prefix_s_length))

  #if !(defined(BYTE_DUMP_program_version_nano_s) && defined(BYTE_DUMP_program_version_nano_s_length))
    #define BYTE_DUMP_program_version_nano_s
    #define BYTE_DUMP_program_version_nano_s_length 0
  #endif // !(defined(BYTE_DUMP_program_version_nano_s) && defined(BYTE_DUMP_program_version_nano_s_length))

  #define BYTE_DUMP_program_version_s BYTE_DUMP_program_version_major_s F_string_ascii_period_s BYTE_DUMP_program_version_minor_s F_string_ascii_period_s BYTE_DUMP_program_version_micro_s BYTE_DUMP_program_version_nano_prefix_s BYTE_DUMP_program_version_nano_s

  #define BYTE_DUMP_program_version_s_length BYTE_DUMP_program_version_major_s_length + F_string_ascii_period_s_length + BYTE_DUMP_program_version_minor_s_length + F_string_ascii_period_s_length + BYTE_DUMP_program_version_micro_s_length + BYTE_DUMP_program_version_nano_prefix_s_length + BYTE_DUMP_program_version_nano_s_length

  extern const f_string_static_t byte_dump_program_version_s;
#endif // _di_byte_dump_program_version_d_

/**
 * The program name.
 */
#ifndef _di_byte_dump_program_name_s_
  #define BYTE_DUMP_program_name_s      "byte_dump"
  #define BYTE_DUMP_program_name_long_s "Byte Dump"

  #define BYTE_DUMP_program_name_s_length      9
  #define BYTE_DUMP_program_name_long_s_length 9

  extern const f_string_static_t byte_dump_program_name_s;
  extern const f_string_static_t byte_dump_program_name_long_s;
#endif // _di_byte_dump_program_name_s_

/**
 * The program strings for printing.
 */
#ifndef _di_byte_dump_s_
  #define BYTE_DUMP_hexidecimal_s "Hexidecimal"
  #define BYTE_DUMP_duodecimal_s  "Duodecimal"
  #define BYTE_DUMP_octal_s       "Octal"
  #define BYTE_DUMP_binary_s      "Binary"
  #define BYTE_DUMP_decimal_s     "Decimal"

  #define BYTE_DUMP_character_wall_s        "|"
  #define BYTE_DUMP_character_placeholder_s "␣" // Other likely choices: (substitute form 1: '␚', substitute form 2: '␦').
  #define BYTE_DUMP_character_incomplete_s  "�"
  #define BYTE_DUMP_character_unused_s      "�"

  #define BYTE_DUMP_hexidecimal_s_length 11
  #define BYTE_DUMP_duodecimal_s_length  10
  #define BYTE_DUMP_octal_s_length       5
  #define BYTE_DUMP_binary_s_length      6
  #define BYTE_DUMP_decimal_s_length     7

  #define BYTE_DUMP_character_wall_s_length        1
  #define BYTE_DUMP_character_placeholder_s_length 3
  #define BYTE_DUMP_character_incomplete_s_length  3
  #define BYTE_DUMP_character_unused_s_length      3

  extern const f_string_static_t byte_dump_hexidecimal_s;
  extern const f_string_static_t byte_dump_duodecimal_s;
  extern const f_string_static_t byte_dump_octal_s;
  extern const f_string_static_t byte_dump_binary_s;
  extern const f_string_static_t byte_dump_decimal_s;

  extern const f_string_static_t byte_dump_character_wall_s;
  extern const f_string_static_t byte_dump_character_placeholder_s;
  extern const f_string_static_t byte_dump_character_incomplete_s;
  extern const f_string_static_t byte_dump_character_unused_s;
#endif // _di_byte_dump_s_

/**
 * Paddings and an array containing the paddings for quick reference.
 *
 * The byte_dump_padding_s is an array with the following structure:
 *   - index 0: unicode.
 *   - index 1: hexidecimal.
 *   - index 2: duodecimal.
 *   - index 3: octal.
 *   - index 4: binary.
 *   - index 5: decimal.
 */
#ifndef _di_byte_dump_padding_s_
  #define BYTE_DUMP_padding_3_s "   "
  #define BYTE_DUMP_padding_4_s "    "
  #define BYTE_DUMP_padding_5_s "     "
  #define BYTE_DUMP_padding_6_s "      "
  #define BYTE_DUMP_padding_8_s "        "
  #define BYTE_DUMP_padding_9_s "         "

  #define BYTE_DUMP_padding_3_s_length 3
  #define BYTE_DUMP_padding_4_s_length 4
  #define BYTE_DUMP_padding_5_s_length 5
  #define BYTE_DUMP_padding_6_s_length 6
  #define BYTE_DUMP_padding_8_s_length 8
  #define BYTE_DUMP_padding_9_s_length 9

  extern const f_string_static_t byte_dump_padding_3_s;
  extern const f_string_static_t byte_dump_padding_4_s;
  extern const f_string_static_t byte_dump_padding_5_s;
  extern const f_string_static_t byte_dump_padding_6_s;
  extern const f_string_static_t byte_dump_padding_8_s;
  extern const f_string_static_t byte_dump_padding_9_s;

  extern const f_string_static_t byte_dump_padding_s[];
#endif // _di_byte_dump_padding_s_

/**
 * The main program parameters.
 */
#ifndef _di_byte_dump_parameter_s_
  #define BYTE_DUMP_short_binary_s      "b"
  #define BYTE_DUMP_short_decimal_s     "d"
  #define BYTE_DUMP_short_duodecimal_s  "D"
  #define BYTE_DUMP_short_hexidecimal_s "x"
  #define BYTE_DUMP_short_octal_s       "o"
  #define BYTE_DUMP_short_unicode_s     "U"

  #define BYTE_DUMP_short_first_s       "f"
  #define BYTE_DUMP_short_last_s        "l"

  #define BYTE_DUMP_short_narrow_s      "N"
  #define BYTE_DUMP_short_placeholder_s "p"
  #define BYTE_DUMP_short_text_s        "t"
  #define BYTE_DUMP_short_wide_s        "W"
  #define BYTE_DUMP_short_width_s       "w"

  #define BYTE_DUMP_long_binary_s      "binary"
  #define BYTE_DUMP_long_decimal_s     "decimal"
  #define BYTE_DUMP_long_duodecimal_s  "duodecimal"
  #define BYTE_DUMP_long_hexidecimal_s "hexidecimal"
  #define BYTE_DUMP_long_octal_s       "octal"
  #define BYTE_DUMP_long_unicode_s     "unicode"

  #define BYTE_DUMP_long_first_s "first"
  #define BYTE_DUMP_long_last_s  "last"

  #define BYTE_DUMP_long_narrow_s      "narrow"
  #define BYTE_DUMP_long_placeholder_s "placeholder"
  #define BYTE_DUMP_long_text_s        "text"
  #define BYTE_DUMP_long_wide_s        "wide"
  #define BYTE_DUMP_long_width_s       "width"

  #define BYTE_DUMP_long_normal_s  "normal"
  #define BYTE_DUMP_long_simple_s  "simple"
  #define BYTE_DUMP_long_classic_s "classic"

  #define BYTE_DUMP_short_binary_s_length      1
  #define BYTE_DUMP_short_decimal_s_length     1
  #define BYTE_DUMP_short_duodecimal_s_length  1
  #define BYTE_DUMP_short_hexidecimal_s_length 1
  #define BYTE_DUMP_short_octal_s_length       1
  #define BYTE_DUMP_short_unicode_s_length     1

  #define BYTE_DUMP_short_first_s_length       1
  #define BYTE_DUMP_short_last_s_length        1

  #define BYTE_DUMP_short_narrow_s_length      1
  #define BYTE_DUMP_short_placeholder_s_length 1
  #define BYTE_DUMP_short_text_s_length        1
  #define BYTE_DUMP_short_wide_s_length        1
  #define BYTE_DUMP_short_width_s_length       1

  #define BYTE_DUMP_long_binary_s_length      6
  #define BYTE_DUMP_long_decimal_s_length     7
  #define BYTE_DUMP_long_duodecimal_s_length  10
  #define BYTE_DUMP_long_hexidecimal_s_length 11
  #define BYTE_DUMP_long_octal_s_length       5
  #define BYTE_DUMP_long_unicode_s_length     7

  #define BYTE_DUMP_long_first_s_length 5
  #define BYTE_DUMP_long_last_s_length  4

  #define BYTE_DUMP_long_narrow_s_length      6
  #define BYTE_DUMP_long_placeholder_s_length 11
  #define BYTE_DUMP_long_text_s_length        4
  #define BYTE_DUMP_long_wide_s_length        4
  #define BYTE_DUMP_long_width_s_length       5

  #define BYTE_DUMP_long_normal_s_length  6
  #define BYTE_DUMP_long_simple_s_length  6
  #define BYTE_DUMP_long_classic_s_length 7

  extern const f_string_static_t byte_dump_short_binary_s;
  extern const f_string_static_t byte_dump_short_decimal_s;
  extern const f_string_static_t byte_dump_short_duodecimal_s;
  extern const f_string_static_t byte_dump_short_hexidecimal_s;
  extern const f_string_static_t byte_dump_short_octal_s;
  extern const f_string_static_t byte_dump_short_unicode_s;

  extern const f_string_static_t byte_dump_short_first_s;
  extern const f_string_static_t byte_dump_short_last_s;

  extern const f_string_static_t byte_dump_short_narrow_s;
  extern const f_string_static_t byte_dump_short_placeholder_s;
  extern const f_string_static_t byte_dump_short_text_s;
  extern const f_string_static_t byte_dump_short_wide_s;
  extern const f_string_static_t byte_dump_short_width_s;

  extern const f_string_static_t byte_dump_long_binary_s;
  extern const f_string_static_t byte_dump_long_decimal_s;
  extern const f_string_static_t byte_dump_long_duodecimal_s;
  extern const f_string_static_t byte_dump_long_hexidecimal_s;
  extern const f_string_static_t byte_dump_long_octal_s;
  extern const f_string_static_t byte_dump_long_unicode_s;

  extern const f_string_static_t byte_dump_long_first_s;
  extern const f_string_static_t byte_dump_long_last_s;

  extern const f_string_static_t byte_dump_long_narrow_s;
  extern const f_string_static_t byte_dump_long_placeholder_s;
  extern const f_string_static_t byte_dump_long_text_s;
  extern const f_string_static_t byte_dump_long_wide_s;
  extern const f_string_static_t byte_dump_long_width_s;

  extern const f_string_static_t byte_dump_long_normal_s;
  extern const f_string_static_t byte_dump_long_simple_s;
  extern const f_string_static_t byte_dump_long_classic_s;
#endif // _di_byte_dump_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_common_string_h

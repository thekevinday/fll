/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_common_h
#define _byte_dump_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_byte_dump_program_version_
  #define BYTE_DUMP_program_version_major_s F_string_ascii_0_s
  #define BYTE_DUMP_program_version_minor_s F_string_ascii_6_s
  #define BYTE_DUMP_program_version_micro_s F_string_ascii_1_s F_string_ascii_0_s

  #define BYTE_DUMP_program_version_major_s_length F_string_ascii_0_s_length
  #define BYTE_DUMP_program_version_minor_s_length F_string_ascii_6_s_length
  #define BYTE_DUMP_program_version_micro_s_length (F_string_ascii_1_s_length + F_string_ascii_0_s_length)

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
#endif // _di_byte_dump_program_version_

/**
 * The program name.
 */
#ifndef _di_byte_dump_program_name_
  #define BYTE_DUMP_program_name_s      "byte_dump"
  #define BYTE_DUMP_program_name_long_s "Byte Dump"

  #define BYTE_DUMP_program_name_s_length      9
  #define BYTE_DUMP_program_name_long_s_length 9

  extern const f_string_static_t byte_dump_program_name_s;
  extern const f_string_static_t byte_dump_program_name_long_s;
#endif // _di_byte_dump_program_name_

/**
 * The program strings for printing.
 */
#ifndef _di_byte_dump_print_strings_
  #define BYTE_DUMP_print_strings_hexidecimal_s "Hexidecimal"
  #define BYTE_DUMP_print_strings_duodecimal_s  "Duodecimal"
  #define BYTE_DUMP_print_strings_octal_s       "Octal"
  #define BYTE_DUMP_print_strings_binary_s      "Binary"
  #define BYTE_DUMP_print_strings_decimal_s     "Decimal"

  #define BYTE_DUMP_print_strings_hexidecimal_s_length 11
  #define BYTE_DUMP_print_strings_duodecimal_s_length  10
  #define BYTE_DUMP_print_strings_octal_s_length       5
  #define BYTE_DUMP_print_strings_binary_s_length      6
  #define BYTE_DUMP_print_strings_decimal_s_length     7

  extern const f_string_static_t byte_dump_print_strings_hexidecimal_s;
  extern const f_string_static_t byte_dump_print_strings_duodecimal_s;
  extern const f_string_static_t byte_dump_print_strings_octal_s;
  extern const f_string_static_t byte_dump_print_strings_binary_s;
  extern const f_string_static_t byte_dump_print_strings_decimal_s;
#endif // _di_byte_dump_print_strings_

/**
 * Set to at least 4 to provide a UTF-8 friendly allocation step.
 */
#ifndef _di_byte_dump_default_allocation_step_
  #define byte_dump_default_allocation_step_d 4
#endif // _di_byte_dump_default_allocation_step_

/**
 * The program defines.
 *
 * byte_dump_mode_*:
 *   - hexidecimal: Display using hexidecimal notation (base 16).
 *   - duodecimal:  Display using duodecimal notation (base 12).
 *   - octal:       Display using octal notation (base 8).
 *   - binary:      Display using binary notation (base 2).
 *   - decimal:     Display using decimal notation (base 10).
 *
 * byte_dump_presentation_*:
 *   - normal:  Normal presentation mode.
 *   - simple:  Simple presentation mode.
 *   - classic: Classic presentation mode.
 */
#ifndef _di_byte_dump_defines_
  enum {
    byte_dump_mode_hexidecimal_e = 1,
    byte_dump_mode_duodecimal_e,
    byte_dump_mode_octal_e,
    byte_dump_mode_binary_e,
    byte_dump_mode_decimal_e,
  };

  enum {
    byte_dump_presentation_normal_e = 1,
    byte_dump_presentation_simple_e,
    byte_dump_presentation_classic_e,
  };

  #define byte_dump_option_wide_d 0x1

  #define byte_dump_signal_check_d 20000

  #define BYTE_DUMP_character_wall_s        "|"
  #define BYTE_DUMP_character_placeholder_s "␣" // Other likely choices: (substitute form 1: '␚', substitute form 2: '␦').
  #define BYTE_DUMP_character_incomplete_s  "�"
  #define BYTE_DUMP_character_unused_s      "�"

  #define BYTE_DUMP_character_wall_s_length        1
  #define BYTE_DUMP_character_placeholder_s_length 3
  #define BYTE_DUMP_character_incomplete_s_length  3
  #define BYTE_DUMP_character_unused_s_length      3

  extern const f_string_static_t byte_dump_character_wall_s;
  extern const f_string_static_t byte_dump_character_placeholder_s;
  extern const f_string_static_t byte_dump_character_incomplete_s;
  extern const f_string_static_t byte_dump_character_unused_s;
#endif // _di_byte_dump_defines_

/**
 * The program parameters.
 *
 * byte_dump parameters:
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
#ifndef _di_byte_dump_parameters_
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
  };

  #define byte_dump_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_copyright_s.string, f_console_standard_long_copyright_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_error_s.string, f_console_standard_long_error_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_binary_s.string, byte_dump_long_binary_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_decimal_s.string, byte_dump_long_decimal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_duodecimal_s.string, byte_dump_long_duodecimal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_hexidecimal_s.string, byte_dump_long_hexidecimal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_octal_s.string, byte_dump_long_octal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_unicode_s.string, byte_dump_long_unicode_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_first_s.string, byte_dump_long_first_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_last_s.string, byte_dump_long_last_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_narrow_s.string, byte_dump_long_narrow_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_placeholder_s.string, byte_dump_long_placeholder_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_text_s.string, byte_dump_long_text_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_wide_s.string, byte_dump_long_wide_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(byte_dump_short_width_s.string, byte_dump_long_width_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, byte_dump_long_normal_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, byte_dump_long_simple_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, byte_dump_long_classic_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define byte_dump_total_parameters_d 27
#endif // _di_byte_dump_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_common_h

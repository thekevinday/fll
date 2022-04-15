/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project utf.
 *
 * @fixme this code probably only works on little-endian only as-is, this needs to be checked for and possibly redesign to support both big or little.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _F_utf_common_h
#define _F_utf_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Define the UTF-8 bytes.
 *
 * The bytes are for checking a single 8-bit character value (specifically, checking the first bits).
 *
 * The byte offs are used for determining the character width of a UTF-8 character.
 *
 * The f_utf_byte_is method will return non-zero if the character is a UTF-8 character of any width.
 *
 * The F_utf_byte_1_d is specifically used only on UTF-8 fragments.
 * For example, with the 2-byte-wide UTF-8 character '1100x xxxx 10yy yyyy', the 8-byte block '10yy yyyy' would be a fragment.
 *
 * The macro_f_utf_byte_is_* macros are used to determine a width of the character (either 1, 2, 3, or 4, respectively).
 *
 * The macro_f_utf_byte_width macro determines a width of the character.
 * The macro_f_utf_byte_width_is is identical to macro_f_utf_byte_width, except it returns 0 when character is ASCII.
 */
#ifndef _di_f_utf_byte_
  #define F_utf_byte_1_d 0x80 // 1000 0000
  #define F_utf_byte_2_d 0xc0 // 1100 0000
  #define F_utf_byte_3_d 0xe0 // 1110 0000
  #define F_utf_byte_4_d 0xf0 // 1111 0000

  #define F_utf_byte_off_1_d 0xc0 // 1100 0000
  #define F_utf_byte_off_2_d 0xe0 // 1110 0000
  #define F_utf_byte_off_3_d 0xf0 // 1111 0000
  #define F_utf_byte_off_4_d 0xf8 // 1111 1000

  #define macro_f_utf_byte_is(character) ((character) & F_utf_byte_1_d)

  #define macro_f_utf_byte_is_1(character) (((character) & F_utf_byte_off_1_d) == F_utf_byte_1_d) // (10xx xxxx & 1100 0000) == 1000 0000
  #define macro_f_utf_byte_is_2(character) (((character) & F_utf_byte_off_2_d) == F_utf_byte_2_d) // (110x xxxx & 1110 0000) == 1100 0000
  #define macro_f_utf_byte_is_3(character) (((character) & F_utf_byte_off_3_d) == F_utf_byte_3_d) // (1110 xxxx & 1111 0000) == 1110 0000
  #define macro_f_utf_byte_is_4(character) (((character) & F_utf_byte_off_4_d) == F_utf_byte_4_d) // (1111 0xxx & 1111 1000) == 1111 0000

  #define macro_f_utf_byte_width(character)    ((!macro_f_utf_byte_is(character) || macro_f_utf_byte_is_1(character)) ? 1 : (macro_f_utf_byte_is_2(character) ? 2 : (macro_f_utf_byte_is_3(character) ? 3 : 4)))
  #define macro_f_utf_byte_width_is(character) (macro_f_utf_byte_is(character) ? (macro_f_utf_byte_is_1(character) ? 1 : (macro_f_utf_byte_is_2(character) ? 2 : (macro_f_utf_byte_is_3(character) ? 3 : 4))) : 0)
#endif // _di_f_utf_byte_

/**
 * Define the UTF-8 general whitespace codes.
 *
 * These are integers representing character codes that represent types of spaces.
 *
 * This does not provide whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_space_
  #define F_utf_space_em_s_length           3
  #define F_utf_space_em_quad_s_length      3
  #define F_utf_space_em_per_three_s_length 3
  #define F_utf_space_em_per_four_s_length  3
  #define F_utf_space_em_per_six_s_length   3

  #define F_utf_space_en_s_length      3
  #define F_utf_space_en_quad_s_length 3

  #define F_utf_space_line_feed_reverse_s_length 2
  #define F_utf_space_line_next_s_length         2

  #define F_utf_space_medium_mathematical_s_length 3

  #define F_utf_space_no_break_s_length        2
  #define F_utf_space_no_break_narrow_s_length 3

  #define F_utf_space_ogham_s_length       3
  #define F_utf_space_figure_s_length      3
  #define F_utf_space_punctuation_s_length 3
  #define F_utf_space_thin_s_length        3
  #define F_utf_space_hair_s_length        3
  #define F_utf_space_ideographic_s_length 3

  #define F_utf_space_separator_line_s_length      3
  #define F_utf_space_separator_paragraph_s_length 3

  extern const uint8_t f_utf_space_em_s[];
  extern const uint8_t f_utf_space_em_quad_s[];
  extern const uint8_t f_utf_space_em_per_three_s[];
  extern const uint8_t f_utf_space_em_per_four_s[];
  extern const uint8_t f_utf_space_em_per_six_s[];

  extern const uint8_t f_utf_space_en_s[];
  extern const uint8_t f_utf_space_en_quad_s[];

  extern const uint8_t f_utf_space_line_feed_reverse_s[];
  extern const uint8_t f_utf_space_line_next_s[];

  extern const uint8_t f_utf_space_medium_mathematical_s[];

  extern const uint8_t f_utf_space_no_break_s[];
  extern const uint8_t f_utf_space_no_break_narrow_s[];

  extern const uint8_t f_utf_space_ogham_s[];
  extern const uint8_t f_utf_space_figure_s[];
  extern const uint8_t f_utf_space_punctuation_s[];
  extern const uint8_t f_utf_space_thin_s[];
  extern const uint8_t f_utf_space_hair_s[];
  extern const uint8_t f_utf_space_ideographic_s[];

  extern const uint8_t f_utf_space_separator_line_s[];
  extern const uint8_t f_utf_space_separator_paragraph_s[];
#endif // _di_f_utf_space_

/**
 * Define the UTF-8 general substitute whitespace codes.
 *
 * These are integers representing character codes that represent types of substitute spaces.
 *
 * Substitute codes are not actual codes and are actually prints of the codes so they should not be treated as the actual codes.
 *
 * This does not provide substitute whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_substitute_
  #define F_utf_substitute_symbol_blank_s_length 3
  #define F_utf_substitute_symbol_space_s_length 3

  #define F_utf_substitute_middle_dot_s_length 2

  #define F_utf_substitute_open_box_s_length            3
  #define F_utf_substitute_open_box_shouldered_s_length 3

  extern const uint8_t f_utf_substitute_symbol_blank_s[];
  extern const uint8_t f_utf_substitute_symbol_space_s[];

  extern const uint8_t f_utf_substitute_middle_dot_s[];

  extern const uint8_t f_utf_substitute_open_box_s[];
  extern const uint8_t f_utf_substitute_open_box_shouldered_s[];
#endif // _di_f_utf_substitute_

/**
 * Provide a basic UTF-8 character as a single 4-byte variable.
 *
 * This is intended to be used when a single variable is desired to represent a 1-byte, 2-byte, 3-byte, or even 4-byte character.
 *
 * This "character" type is stored as a big-endian 4-byte integer (32-bits).
 * A helper function, f_utf_is_big_endian(), is provided to detect system endianness so that character arrays (uint8_t []) can be correctly processed.
 *
 * The byte structure is intended to be read left to right in memory regardless of system endianness.
 * This is done so that the first character (the left most) can be read naturally as a string, such as string[0] = first character.
 *
 * The macro_f_utf_char_t_mask_byte_* are used to get the entire character set fo a given width.
 *
 * The macro_f_utf_char_t_mask_char_* are used to get a specific UTF-8 block as a single character range.
 *
 * The macro_f_utf_char_t_to_char_* are used to convert a f_utf_char_t into a uint8_t, for a given 8-bit block.
 *
 * The macro_f_utf_char_t_from_char_* are used to convert a uint8_t into part of a f_utf_char_t, for a given 8-bit block.
 *
 * The macro_f_utf_char_t_width is used to determine the width of the UTF-8 character based on macro_f_utf_byte_width.
 * The macro_f_utf_char_t_width_is is used to determine the width of the UTF-8 character based on macro_f_utf_byte_width_is.
 *
 * The macro_f_utf_char_t_width macro determines a width of the UTF-8 character based on macro_f_utf_byte_width.
 * The macro_f_utf_char_t_width_is is identical to macro_f_utf_char_t_width, except it returns 0 when character is ASCII.
 *
 * @see f_utf_is_big_endian()
 */
#ifndef _di_f_utf_char_t_
  typedef uint32_t f_utf_char_t;

  #define f_utf_char_t_initialize 0

  #define macro_f_utf_char_t_initialize(code) code

  #ifdef _is_F_endian_big
    #define F_utf_char_mask_byte_1_d 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111
    #define F_utf_char_mask_byte_2_d 0x0000ffff // 0000 0000, 0000 0000, 1111 1111, 1111 1111
    #define F_utf_char_mask_byte_3_d 0x00ffffff // 0000 0000, 1111 1111, 1111 1111, 1111 1111
    #define F_utf_char_mask_byte_4_d 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

    #define F_utf_char_mask_char_1_d 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111
    #define F_utf_char_mask_char_2_d 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
    #define F_utf_char_mask_char_3_d 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
    #define F_utf_char_mask_char_4_d 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000

    #define macro_f_utf_char_t_to_char_1(character) (((character) & F_utf_char_mask_char_1_d))        // Grab first byte.
    #define macro_f_utf_char_t_to_char_2(character) (((character) & F_utf_char_mask_char_2_d) >> 8u)  // Grab second byte.
    #define macro_f_utf_char_t_to_char_3(character) (((character) & F_utf_char_mask_char_3_d) >> 16u) // Grab third byte.
    #define macro_f_utf_char_t_to_char_4(character) (((character) & F_utf_char_mask_char_4_d) >> 24u) // Grab fourth byte.

    #define macro_f_utf_char_t_from_char_1(character) (((character)) & F_utf_char_mask_char_1_d)        // Shift to first byte.
    #define macro_f_utf_char_t_from_char_2(character) (((character) << 8u) & F_utf_char_mask_char_2_d)  // Shift to second byte.
    #define macro_f_utf_char_t_from_char_3(character) (((character) << 16u) & F_utf_char_mask_char_3_d) // Shift to third byte.
    #define macro_f_utf_char_t_from_char_4(character) (((character) << 24u) & F_utf_char_mask_char_4_d) // Shift to fourth byte.
  #else
    #define F_utf_char_mask_byte_1_d 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
    #define F_utf_char_mask_byte_2_d 0xffff0000 // 1111 1111, 1111 1111, 0000 0000, 0000 0000
    #define F_utf_char_mask_byte_3_d 0xffffff00 // 1111 1111, 1111 1111, 1111 1111, 0000 0000
    #define F_utf_char_mask_byte_4_d 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

    #define F_utf_char_mask_char_1_d 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
    #define F_utf_char_mask_char_2_d 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
    #define F_utf_char_mask_char_3_d 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
    #define F_utf_char_mask_char_4_d 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111

    #define macro_f_utf_char_t_to_char_1(character) (((character) & F_utf_char_mask_char_1_d) >> 24) // Grab first byte.
    #define macro_f_utf_char_t_to_char_2(character) (((character) & F_utf_char_mask_char_2_d) >> 16) // Grab second byte.
    #define macro_f_utf_char_t_to_char_3(character) (((character) & F_utf_char_mask_char_3_d) >> 8)  // Grab third byte.
    #define macro_f_utf_char_t_to_char_4(character) ((character) & F_utf_char_mask_char_4_d)         // Grab fourth byte.

    #define macro_f_utf_char_t_from_char_1(character) (((character) << 24) & F_utf_char_mask_char_1_d) // Shift to first byte.
    #define macro_f_utf_char_t_from_char_2(character) (((character) << 16) & F_utf_char_mask_char_2_d) // Shift to second byte.
    #define macro_f_utf_char_t_from_char_3(character) (((character) << 8) & F_utf_char_mask_char_3_d)  // Shift to third byte.
    #define macro_f_utf_char_t_from_char_4(character) ((character) & F_utf_char_mask_char_4_d)         // Shift to fourth byte.
  #endif // _is_F_endian_big

  #define macro_f_utf_char_t_width(character)    (macro_f_utf_byte_width(macro_f_utf_char_t_to_char_1(character)))
  #define macro_f_utf_char_t_width_is(character) (macro_f_utf_byte_width_is(macro_f_utf_char_t_to_char_1(character)))
#endif // _di_f_utf_char_t_

/**
 * Provide f_utf_char_t special "characters".
 *
 * These strings are created via digits and then cast.
 */
#ifndef _di_f_utf_char_t_codes_
  #ifdef _is_F_endian_big
    #define F_utf_char_t_eol_s         0x0000000a // 0000 0000, 0000 0000, 0000 0000, 0000 1010
    #define F_utf_char_t_eos_s         0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
    #define F_utf_char_t_placeholder_s 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
  #else
    #define F_utf_char_t_eol_s         0x0a000000 // 0000 1010, 0000 0000, 0000 0000, 0000 0000
    #define F_utf_char_t_eos_s         0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
    #define F_utf_char_t_placeholder_s 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
  #endif // _is_F_endian_big

  extern const f_utf_char_t f_utf_char_t_eol_s;
  extern const f_utf_char_t f_utf_char_t_eos_s;
  extern const f_utf_char_t f_utf_char_t_placeholder_s;
#endif // _di_f_utf_char_t_codes_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_utf_string_dynamic_t for dynamic allocation.
 */
#ifndef _di_f_utf_string_t_
  typedef f_utf_char_t *f_utf_string_t;

  #define f_utf_string_t_initialize 0

  #define macro_f_utf_string_t_clear(string) string = 0;

  #define macro_f_utf_string_t_resize(status, string, length_old, length_new) status = f_memory_resize(length_old, length_new, sizeof(f_utf_string_t), (void **) & string);
  #define macro_f_utf_string_t_adjust(status, string, length_old, length_new) status = f_memory_adjust(length_old, length_new, sizeof(f_utf_string_t), (void **) & string);

  #define macro_f_utf_string_t_delete_simple(string, length)  f_memory_resize(length, 0, sizeof(f_utf_string_t), (void **) & string);
  #define macro_f_utf_string_t_destroy_simple(string, length) f_memory_adjust(length, 0, sizeof(f_utf_string_t), (void **) & string);
#endif // _di_f_utf_string_t_

/**
 * Define unicode special character widths.
 *
 * F_utf_width_*:
 *   - none:      Designate this is not a width value or has no width (aka: NULL).
 *   - ambiguous: Characters appear in East Asian DBCS and in SBCS.
 *   - full:      Wide character that has a equivilent to a narrow character.
 *   - half:      Narrow character that has a equivilent to a wide character.
 *   - narrow:    Narrow character, without a wide equivalent.
 *   - nuetral:   Characters that do not appear in East Asian DBCS codes.
 *   - wide:      Wide character, without a narrow equivalent.
 */
#ifndef _di_f_utf_widths_t_
  enum {
    F_utf_width_none_e,
    F_utf_width_ambiguous_e,
    F_utf_width_full_e,
    F_utf_width_half_e,
    F_utf_width_narrow_e,
    F_utf_width_nuetral_e,
    F_utf_width_wide_e,
  };
#endif // _di_f_utf_widths_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_common_h

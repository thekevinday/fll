/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project utf.
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
 * The f_utf_byte_1 is specifically used only on UTF-8 fragments.
 * For example, with the 2-byte-wide UTF-8 character '1100x xxxx 10yy yyyy', the 8-byte block '10yy yyyy' would be a fragment.
 *
 * The f_macro_utf_byte_is_* macros are used to determine a width of the character (either 1, 2, 3, or 4, respectively).
 *
 * The f_macro_utf_byte_width macro determines a width of the character.
 * The f_macro_utf_byte_width_is is identical to f_macro_utf_byte_width, except it returns 0 when character is not UTF-8.
 */
#ifndef _di_f_utf_byte_
  #define f_utf_byte_1 0x80 // 1000 0000
  #define f_utf_byte_2 0xc0 // 1100 0000
  #define f_utf_byte_3 0xe0 // 1110 0000
  #define f_utf_byte_4 0xf0 // 1111 0000

  #define f_utf_byte_off_1 0xc0 // 1100 0000
  #define f_utf_byte_off_2 0xe0 // 1110 0000
  #define f_utf_byte_off_3 0xf0 // 1111 0000
  #define f_utf_byte_off_4 0xf8 // 1111 1000

  #define f_macro_utf_byte_is(character) ((character) & f_utf_byte_1)

  #define f_macro_utf_byte_is_1(character) (((character) & f_utf_byte_off_1) == f_utf_byte_1) // (10xx xxxx & 1100 0000) == 1000 0000
  #define f_macro_utf_byte_is_2(character) (((character) & f_utf_byte_off_2) == f_utf_byte_2) // (110x xxxx & 1110 0000) == 1100 0000
  #define f_macro_utf_byte_is_3(character) (((character) & f_utf_byte_off_3) == f_utf_byte_3) // (1110 xxxx & 1111 0000) == 1110 0000
  #define f_macro_utf_byte_is_4(character) (((character) & f_utf_byte_off_4) == f_utf_byte_4) // (1111 0xxx & 1111 1000) == 1111 0000

  #define f_macro_utf_byte_width(character)    ((!f_macro_utf_byte_is(character) || f_macro_utf_byte_is_1(character)) ? 1 : (f_macro_utf_byte_is_2(character) ? 2 : (f_macro_utf_byte_is_3(character) ? 3 : 4)))
  #define f_macro_utf_byte_width_is(character) (f_macro_utf_byte_is(character) ? (f_macro_utf_byte_is_1(character) ? 1 : (f_macro_utf_byte_is_2(character) ? 2 : (f_macro_utf_byte_is_3(character) ? 3 : 4))) : 0)
#endif // _di_f_utf_byte_

/**
 * Define the UTF-8 general whitespace codes.
 *
 * These are integers representing character codes that represent types of spaces.
 *
 * This does not provide whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_space_
  #define f_utf_space_em_length           3
  #define f_utf_space_em_quad_length      3
  #define f_utf_space_em_per_three_length 3
  #define f_utf_space_em_per_four_length  3
  #define f_utf_space_em_per_six_length   3

  #define f_utf_space_en_length      3
  #define f_utf_space_en_quad_length 3

  #define f_utf_space_line_feed_reverse_length 2
  #define f_utf_space_line_next_length         2

  #define f_utf_space_medium_mathematical_length 3

  #define f_utf_space_no_break_length        2
  #define f_utf_space_no_break_narrow_length 3

  #define f_utf_space_ogham_length       3
  #define f_utf_space_figure_length      3
  #define f_utf_space_punctuation_length 3
  #define f_utf_space_thin_length        3
  #define f_utf_space_hair_length        3
  #define f_utf_space_ideographic_length 3

  #define f_utf_space_separator_line_length      3
  #define f_utf_space_separator_paragraph_length 3

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
  #define f_utf_substitute_symbol_blank_length 3
  #define f_utf_substitute_symbol_space_length 3

  #define f_utf_substitute_middle_dot_length 2

  #define f_utf_substitute_open_box_length            3
  #define f_utf_substitute_open_box_shouldered_length 3

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
 * The byte structure is intended to be read left to right.
 *
 * The f_macro_utf_character_t_mask_byte_* are used to get the entire character set fo a given width.
 *
 * The f_macro_utf_character_t_mask_char_* are used to get a specific UTF-8 block as a single character range.
 *
 * The f_macro_utf_character_t_to_char_* are used to convert a f_utf_character_t into a uint8_t, for a given 8-bit block.
 *
 * The f_macro_utf_character_t_from_char_* are used to convert a uint8_t into part of a f_utf_character_t, for a given 8-bit block.
 *
 * The f_macro_utf_character_t_width is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width.
 * The f_macro_utf_character_t_width_is is used to determine the width of the UTF-8 character based on f_macro_utf_byte_width_is.
 *
 * @see f_utf_is_big_endian()
 */
#ifndef _di_f_utf_character_t_
  typedef uint32_t f_utf_character_t;

  #define f_utf_character_mask_byte_1 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_mask_byte_2 0xffff0000 // 1111 1111, 1111 1111, 0000 0000, 0000 0000
  #define f_utf_character_mask_byte_3 0xffffff00 // 1111 1111, 1111 1111, 1111 1111, 0000 0000
  #define f_utf_character_mask_byte_4 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

  #define f_utf_character_mask_char_1 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_mask_char_2 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
  #define f_utf_character_mask_char_3 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
  #define f_utf_character_mask_char_4 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111

  #define f_macro_utf_character_t_to_char_1(character) (((character) & f_utf_character_mask_char_1) >> 24) // grab first byte.
  #define f_macro_utf_character_t_to_char_2(character) (((character) & f_utf_character_mask_char_2) >> 16) // grab second byte.
  #define f_macro_utf_character_t_to_char_3(character) (((character) & f_utf_character_mask_char_3) >> 8)  // grab third byte.
  #define f_macro_utf_character_t_to_char_4(character) ((character) & f_utf_character_mask_char_4)         // grab fourth byte.

  #define f_macro_utf_character_t_from_char_1(character) (((character) << 24) & f_utf_character_mask_char_1) // shift to first byte.
  #define f_macro_utf_character_t_from_char_2(character) (((character) << 16) & f_utf_character_mask_char_2) // shift to second byte.
  #define f_macro_utf_character_t_from_char_3(character) (((character) << 8) & f_utf_character_mask_char_3)  // shift to third byte.
  #define f_macro_utf_character_t_from_char_4(character) ((character) & f_utf_character_mask_char_4)         // shift to fourth byte.

  #define f_macro_utf_character_t_width(character)    (f_macro_utf_byte_width(f_macro_utf_character_t_to_char_1(character)))
  #define f_macro_utf_character_t_width_is(character) (f_macro_utf_byte_width_is(f_macro_utf_character_t_to_char_1(character)))
#endif // _di_f_utf_character_t_

#ifndef _di_f_utf_character_t_codes_
  #define f_utf_character_t_eol         0x0a000000 // 0000 1010, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_t_eos         0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
  #define f_utf_character_t_placeholder 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
#endif // _di_f_utf_character_t_codes_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_utf_string_dynamic_t for dynamic allocation.
 */
#ifndef _di_f_utf_string_t_
  typedef f_utf_character_t *f_utf_string_t;

  #define f_utf_string_t_initialize 0

  #define f_macro_utf_string_t_clear(string) string = 0;

  #define f_macro_utf_string_t_resize(status, string, length_old, length_new) status = f_memory_resize(length_old, length_new, sizeof(f_utf_string_t), (void **) & string);
  #define f_macro_utf_string_t_adjust(status, string, length_old, length_new) status = f_memory_adjust(length_old, length_new, sizeof(f_utf_string_t), (void **) & string);

  #define f_macro_utf_string_t_delete_simple(string, length)  f_memory_resize(length, 0, sizeof(f_utf_string_t), (void **) & string);
  #define f_macro_utf_string_t_destroy_simple(string, length) f_memory_adjust(length, 0, sizeof(f_utf_string_t), (void **) & string);
#endif // _di_f_utf_string_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_common_h

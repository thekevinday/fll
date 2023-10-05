/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
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
 * The F_utf_byte_1_d is specifically used only on UTF-8 fragments.
 * For example, with the 2-byte-wide UTF-8 character '1100x xxxx 10yy yyyy', the 8-byte block '10yy yyyy' would be a fragment.
 *
 * The macro_f_utf_byte_is_* macros are used to determine a width of the character (either 1, 2, 3, or 4, respectively).
 *
 * The macro_f_utf_byte_width macro determines a width of the character.
 * The macro_f_utf_byte_width_is is identical to macro_f_utf_byte_width, except it returns 0 when character is ASCII.
 */
#ifndef _di_f_utf_byte_d_
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
#endif // _di_f_utf_byte_d_

/**
 * Define the UTF-8 general whitespace codes.
 *
 * These are integers representing character codes that represent types of spaces.
 *
 * This does not provide whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_space_s_
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

  #ifndef _di_f_utf_space_em_s_
    extern const f_char_t f_utf_space_em_s[];
  #endif // _di_f_f_utf_space_em_s_

  #ifndef _di_f_utf_space_em_quad_s_
    extern const f_char_t f_utf_space_em_quad_s[];
  #endif // _di_f_f_utf_space_em_quad_s_

  #ifndef _di_f_utf_space_em_per_three_s_
    extern const f_char_t f_utf_space_em_per_three_s[];
  #endif // _di_f_f_utf_space_em_per_three_s_

  #ifndef _di_f_utf_space_em_per_four_s_
    extern const f_char_t f_utf_space_em_per_four_s[];
  #endif // _di_f_f_utf_space_em_per_four_s_

  #ifndef _di_f_utf_space_em_per_six_s_
    extern const f_char_t f_utf_space_em_per_six_s[];
  #endif // _di_f_f_utf_space_em_per_six_s_

  #ifndef _di_f_utf_space_en_s_
    extern const f_char_t f_utf_space_en_s[];
  #endif // _di_f_f_utf_space_en_s_

  #ifndef _di_f_utf_space_en_quad_s_
    extern const f_char_t f_utf_space_en_quad_s[];
  #endif // _di_f_f_utf_space_en_quad_s_

  #ifndef _di_f_utf_space_line_feed_reverse_s_
    extern const f_char_t f_utf_space_line_feed_reverse_s[];
  #endif // _di_f_f_utf_space_line_feed_reverse_s_

  #ifndef _di_f_utf_space_line_next_s_
    extern const f_char_t f_utf_space_line_next_s[];
  #endif // _di_f_f_utf_space_line_next_s_

  #ifndef _di_f_utf_space_medium_mathematical_s_
    extern const f_char_t f_utf_space_medium_mathematical_s[];
  #endif // _di_f_f_utf_space_medium_mathematical_s_

  #ifndef _di_f_utf_space_no_break_s_
    extern const f_char_t f_utf_space_no_break_s[];
  #endif // _di_f_f_utf_space_no_break_s_

  #ifndef _di_f_utf_space_no_break_narrow_s_
    extern const f_char_t f_utf_space_no_break_narrow_s[];
  #endif // _di_f_f_utf_space_no_break_narrow_s_

  #ifndef _di_f_utf_space_ogham_s_
    extern const f_char_t f_utf_space_ogham_s[];
  #endif // _di_f_f_utf_space_ogham_s_

  #ifndef _di_f_utf_space_figure_s_
    extern const f_char_t f_utf_space_figure_s[];
  #endif // _di_f_f_utf_space_figure_s_

  #ifndef _di_f_utf_space_punctuation_s_
    extern const f_char_t f_utf_space_punctuation_s[];
  #endif // _di_f_f_utf_space_punctuation_s_

  #ifndef _di_f_utf_space_thin_s_
    extern const f_char_t f_utf_space_thin_s[];
  #endif // _di_f_f_utf_space_thin_s_

  #ifndef _di_f_utf_space_hair_s_
    extern const f_char_t f_utf_space_hair_s[];
  #endif // _di_f_f_utf_space_hair_s_

  #ifndef _di_f_utf_space_ideographic_s_
    extern const f_char_t f_utf_space_ideographic_s[];
  #endif // _di_f_f_utf_space_ideographic_s_

  #ifndef _di_f_utf_space_separator_line_s_
    extern const f_char_t f_utf_space_separator_line_s[];
  #endif // _di_f_f_utf_space_separator_line_s_

  #ifndef _di_f_utf_space_separator_paragraph_s_
    extern const f_char_t f_utf_space_separator_paragraph_s[];
  #endif // _di_f_f_utf_space_separator_paragraph_s_
#endif // _di_f_utf_space_s_

/**
 * Define the UTF-8 general substitute whitespace codes.
 *
 * These are integers representing character codes that represent types of substitute spaces.
 *
 * Substitute codes are not actual codes and are actually prints of the codes so they should not be treated as the actual codes.
 *
 * This does not provide substitute whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_substitute_s_
  #define F_utf_substitute_symbol_blank_s_length 3
  #define F_utf_substitute_symbol_space_s_length 3

  #define F_utf_substitute_middle_dot_s_length 2

  #define F_utf_substitute_open_box_s_length            3
  #define F_utf_substitute_open_box_shouldered_s_length 3

  #ifndef _di_f_utf_substitute_symbol_blank_s_
    extern const f_char_t f_utf_substitute_symbol_blank_s[];
  #endif // _di_f_f_utf_substitute_symbol_blank_s_

  #ifndef _di_f_utf_substitute_symbol_space_s_
    extern const f_char_t f_utf_substitute_symbol_space_s[];
  #endif // _di_f_f_utf_substitute_symbol_space_s_

  #ifndef _di_f_utf_substitute_middle_dot_s_
    extern const f_char_t f_utf_substitute_middle_dot_s[];
  #endif // _di_f_f_utf_substitute_middle_dot_s_

  #ifndef _di_f_utf_substitute_open_box_s_
    extern const f_char_t f_utf_substitute_open_box_s[];
  #endif // _di_f_f_utf_substitute_open_box_s_

  #ifndef _di_f_utf_substitute_open_box_shouldered_s_
    extern const f_char_t f_utf_substitute_open_box_shouldered_s[];
  #endif // _di_f_f_utf_substitute_open_box_shouldered_s_
#endif // _di_f_utf_substitute_s_

/**
 * Provide a basic UTF-8 byte sequence as a single 4-byte variable.
 *
 * This is intended to be used when a single variable is desired to represent a 1-byte, 2-byte, 3-byte, or even 4-byte sequence.
 *
 * This byte sequence type is stored as a big-endian 4-byte integer (32-bits).
 * A helper function, f_utf_is_big_endian(), is provided to detect system endianness so that byte sequence arrays (uint8_t []) can be correctly processed.
 *
 * The byte structure is intended to be read left to right in memory regardless of system endianness.
 * This is done so that the first byte (the left most) can be read naturally as a string, such as string[0] = first byte.
 *
 * On little-endian systems, the hex-string 0xff is represented as internally as 0x000000ff.
 * This needs to be converted into the internal representation of 0xff000000 to be properly represented as a "f_utf_char_t".
 *
 * The macro_f_utf_char_t_mask_byte_* are used to get the entire byte sequence for a given width.
 *
 * The macro_f_utf_char_t_mask_char_* are used to get a specific UTF-8 block as a single byte sequence range.
 *
 * The macro_f_utf_char_t_to_char_* are used to convert a f_utf_char_t into a uint8_t, for a given 8-bit block.
 *
 * The macro_f_utf_char_t_from_char_* are used to convert a uint8_t into part of a f_utf_char_t, for a given 8-bit block.
 *
 * The macro_f_utf_char_t_width is used to determine the width of the UTF-8 byte sequence based on macro_f_utf_byte_width.
 * The macro_f_utf_char_t_width_is is used to determine the width of the UTF-8 byte sequence based on macro_f_utf_byte_width_is.
 *
 * The macro_f_utf_char_t_width macro determines a width of the UTF-8 byte sequence based on macro_f_utf_byte_width.
 * The macro_f_utf_char_t_width_is is identical to macro_f_utf_char_t_width, except it returns 0 when byte sequence is ASCII.
 *
 * The macros that end in "_be" or "_le" represent "big endian" and "little endian".
 * The default macros without the "_be" should be in "big endian" because the strings are always stored as if they were "big endian" without regard to the host byte order.
 *
 * @see f_utf_is_big_endian()
 */
#ifndef _di_f_utf_char_t_
  typedef uint32_t f_utf_char_t;

  #define f_utf_char_t_initialize 0

  #define macro_f_utf_char_t_initialize_1(code) code

  // Big Endian.
  #define F_utf_char_mask_byte_1_be_d 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define F_utf_char_mask_byte_2_be_d 0xffff0000 // 1111 1111, 1111 1111, 0000 0000, 0000 0000
  #define F_utf_char_mask_byte_3_be_d 0xffffff00 // 1111 1111, 1111 1111, 1111 1111, 0000 0000
  #define F_utf_char_mask_byte_4_be_d 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

  #define F_utf_char_mask_char_1_be_d 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000
  #define F_utf_char_mask_char_2_be_d 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
  #define F_utf_char_mask_char_3_be_d 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
  #define F_utf_char_mask_char_4_be_d 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111

  #define macro_f_utf_char_t_to_char_1_be(sequence) (((sequence) & F_utf_char_mask_char_1_be_d) >> 24) // Grab first byte.
  #define macro_f_utf_char_t_to_char_2_be(sequence) (((sequence) & F_utf_char_mask_char_2_be_d) >> 16) // Grab second byte.
  #define macro_f_utf_char_t_to_char_3_be(sequence) (((sequence) & F_utf_char_mask_char_3_be_d) >> 8)  // Grab third byte.
  #define macro_f_utf_char_t_to_char_4_be(sequence) ((sequence) & F_utf_char_mask_char_4_be_d)         // Grab fourth byte.

  #define macro_f_utf_char_t_from_char_1_be(sequence) (((sequence) << 24) & F_utf_char_mask_char_1_be_d) // Shift to first byte.
  #define macro_f_utf_char_t_from_char_2_be(sequence) (((sequence) << 16) & F_utf_char_mask_char_2_be_d) // Shift to second byte.
  #define macro_f_utf_char_t_from_char_3_be(sequence) (((sequence) << 8) & F_utf_char_mask_char_3_be_d)  // Shift to third byte.
  #define macro_f_utf_char_t_from_char_4_be(sequence) ((sequence) & F_utf_char_mask_char_4_be_d)         // Shift to fourth byte.

  // Little Endian.
  #define F_utf_char_mask_byte_1_le_d 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111
  #define F_utf_char_mask_byte_2_le_d 0x0000ffff // 0000 0000, 0000 0000, 1111 1111, 1111 1111
  #define F_utf_char_mask_byte_3_le_d 0x00ffffff // 0000 0000, 1111 1111, 1111 1111, 1111 1111
  #define F_utf_char_mask_byte_4_le_d 0xffffffff // 1111 1111, 1111 1111, 1111 1111, 1111 1111

  #define F_utf_char_mask_char_1_le_d 0x000000ff // 0000 0000, 0000 0000, 0000 0000, 1111 1111
  #define F_utf_char_mask_char_2_le_d 0x0000ff00 // 0000 0000, 0000 0000, 1111 1111, 0000 0000
  #define F_utf_char_mask_char_3_le_d 0x00ff0000 // 0000 0000, 1111 1111, 0000 0000, 0000 0000
  #define F_utf_char_mask_char_4_le_d 0xff000000 // 1111 1111, 0000 0000, 0000 0000, 0000 0000

  #define macro_f_utf_char_t_to_char_1_le(sequence) ((sequence) & F_utf_char_mask_char_1_le_d)         // Grab first byte.
  #define macro_f_utf_char_t_to_char_2_le(sequence) (((sequence) & F_utf_char_mask_char_2_le_d) >> 8)  // Grab second byte.
  #define macro_f_utf_char_t_to_char_3_le(sequence) (((sequence) & F_utf_char_mask_char_3_le_d) >> 16) // Grab third byte.
  #define macro_f_utf_char_t_to_char_4_le(sequence) (((sequence) & F_utf_char_mask_char_4_le_d) >> 24) // Grab fourth byte.

  #define macro_f_utf_char_t_from_char_1_le(sequence) ((sequence) & F_utf_char_mask_char_1_le_d)         // Shift to first byte.
  #define macro_f_utf_char_t_from_char_2_le(sequence) (((sequence) << 8) & F_utf_char_mask_char_2_le_d)  // Shift to second byte.
  #define macro_f_utf_char_t_from_char_3_le(sequence) (((sequence) << 16) & F_utf_char_mask_char_3_le_d) // Shift to third byte.
  #define macro_f_utf_char_t_from_char_4_le(sequence) (((sequence) << 24) & F_utf_char_mask_char_4_le_d) // Shift to fourth byte.

  #define F_utf_char_mask_byte_1_d F_utf_char_mask_byte_1_be_d
  #define F_utf_char_mask_byte_2_d F_utf_char_mask_byte_2_be_d
  #define F_utf_char_mask_byte_3_d F_utf_char_mask_byte_3_be_d
  #define F_utf_char_mask_byte_4_d F_utf_char_mask_byte_4_be_d

  #define F_utf_char_mask_char_1_d F_utf_char_mask_char_1_be_d
  #define F_utf_char_mask_char_2_d F_utf_char_mask_char_2_be_d
  #define F_utf_char_mask_char_3_d F_utf_char_mask_char_3_be_d
  #define F_utf_char_mask_char_4_d F_utf_char_mask_char_4_be_d

  #define macro_f_utf_char_t_to_char_1(sequence) macro_f_utf_char_t_to_char_1_be(sequence)
  #define macro_f_utf_char_t_to_char_2(sequence) macro_f_utf_char_t_to_char_2_be(sequence)
  #define macro_f_utf_char_t_to_char_3(sequence) macro_f_utf_char_t_to_char_3_be(sequence)
  #define macro_f_utf_char_t_to_char_4(sequence) macro_f_utf_char_t_to_char_4_be(sequence)

  #define macro_f_utf_char_t_from_char_1(sequence) macro_f_utf_char_t_from_char_1_be(sequence)
  #define macro_f_utf_char_t_from_char_2(sequence) macro_f_utf_char_t_from_char_2_be(sequence)
  #define macro_f_utf_char_t_from_char_3(sequence) macro_f_utf_char_t_from_char_3_be(sequence)
  #define macro_f_utf_char_t_from_char_4(sequence) macro_f_utf_char_t_from_char_4_be(sequence)

  #define macro_f_utf_char_t_width(sequence)    (macro_f_utf_byte_width(macro_f_utf_char_t_to_char_1_be(sequence)))
  #define macro_f_utf_char_t_width_is(sequence) (macro_f_utf_byte_width_is(macro_f_utf_char_t_to_char_1_be(sequence)))
#endif // _di_f_utf_char_t_

/**
 * Provide f_utf_char_t special "characters".
 *
 * These strings are created via digits and then cast.
 *
 * The macros that end in "_be" or "_le" represent "big endian" and "little endian".
 * The default macros without the "_be" should be in "big endian" because the strings are always stored as if they were "big endian" without regard to the host byte order.
 */
#ifndef _di_f_utf_char_s_

  // Big Endian.
  #define F_utf_char_eol_be_s         0x0a000000 // 0000 1010, 0000 0000, 0000 0000, 0000 0000
  #define F_utf_char_eos_be_s         0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
  #define F_utf_char_placeholder_be_s 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000

  // Little Endian.
  #define F_utf_char_eol_le_s         0x0000000a // 0000 0000, 0000 0000, 0000 0000, 0000 1010
  #define F_utf_char_eos_le_s         0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000
  #define F_utf_char_placeholder_le_s 0x00000000 // 0000 0000, 0000 0000, 0000 0000, 0000 0000

  #define F_utf_char_eol_s         F_utf_char_eol_be_s
  #define F_utf_char_eos_s         F_utf_char_eos_be_s
  #define F_utf_char_placeholder_s F_utf_char_placeholder_be_s

  #ifndef _di_f_utf_char_eol_s_
    extern const f_utf_char_t f_utf_char_eol_s;
  #endif // _di_f_utf_char_eol_s_

  #ifndef _di_f_utf_char_eos_s_
    extern const f_utf_char_t f_utf_char_eos_s;
  #endif // _di_f_utf_char_eos_s_

  #ifndef _di_f_utf_char_placeholder_s_
    extern const f_utf_char_t f_utf_char_t_placeholder_s;
  #endif // _di_f_utf_char_placeholder_s_
#endif // _di_f_utf_char_s_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_utf_string_dynamic_t for dynamic allocation.
 */
#ifndef _di_f_utf_string_t_
  typedef f_utf_char_t *f_utf_string_t;

  #define f_utf_string_t_initialize 0

  #define macro_f_utf_string_t_initialize_1(string) string

  #define macro_f_utf_string_t_clear(string) string = 0;
#endif // _di_f_utf_string_t_

/**
 * Define unicode special byte sequence widths.
 *
 * F_utf_width_*:
 *   - none:      Designate this is not a width value or has no width (aka: NULL).
 *   - ambiguous: Characters appear in East Asian DBCS and in SBCS.
 *   - full:      Wide byte sequence that has a equivilent to a narrow byte sequence.
 *   - half:      Narrow byte sequence that has a equivilent to a wide byte sequence.
 *   - narrow:    Narrow byte sequence, without a wide equivalent.
 *   - nuetral:   Characters that do not appear in East Asian DBCS codes.
 *   - wide:      Wide byte sequence, without a narrow equivalent.
 */
#ifndef _di_f_utf_width_e_
  enum {
    F_utf_width_none_e = 0,
    F_utf_width_ambiguous_e,
    F_utf_width_full_e,
    F_utf_width_half_e,
    F_utf_width_narrow_e,
    F_utf_width_nuetral_e,
    F_utf_width_wide_e,
  }; // enum
#endif // _di_f_utf_width_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_common_h

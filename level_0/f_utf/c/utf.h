/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 capabilities.
 *
 * Identifiers:
 * - UTF_8-1: 1000 0000
 * - UTF_8-2: 1100 0000
 * - UTF_8-3: 1110 0000
 * - UTF_8-4: 1111 0000
 *
 * Values:
 * - UTF_8-1: 1011 1111
 * - UTF_8-2: 1101 1111
 * - UTF_8-3: 1110 1111
 * - UTF_8-4: 1111 0111
 *
 * Identifier Structure:
 * - UTF_8-1: 1000 0000
 * - UTF_8-2: 1100 0000 1000 0000
 * - UTF_8-3: 1110 0000 1000 0000 1000 0000
 * - UTF_8-4: 1111 0000 1000 0000 1000 0000 1000 0000
 *
 * Value Structure:
 * - UTF_8-1: 10xx xxxx
 * - UTF_8-2: 110x xxxx, 10xx xxxx
 * - UTF_8-3: 1110 xxxx, 10xx xxxx, 10xx xxxx
 * - UTF_8-4: 1111 0xxx, 10xx xxxx, 10xx xxxx, 10xx xxxx
 */
#ifndef _F_utf_h
#define _F_utf_h

// libc includes
#include <string.h>

// fll includes
#include <level_0/errors.h>
#include <level_0/types.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Define the UTF-8 BOM.
 *
 * The BOM designates that a string is in UTF-8.
 * The BOM must be checked for when processing strings.
 *
 * In many cases, this should be removed such that only one exists in some string block.
 */
#ifndef _di_f_utf_bom_
  #define f_utf_bom_length 3

  const static char f_utf_bom[f_utf_bom_length] = { 0xef, 0xbb, 0xbf }; // 1110 1111, 1011 1011, 1011 1111
#endif // _di_f_utf_bom_

/**
 * Define the UTF-8 bytes.
 *
 * The bytes are for checking a single 8-bit character value (specifically, checking the first bits).
 *
 * The byte offs are used for determining the character width of a UTF-8 character.
 *
 * The f_utf_byte_is method will return non-zero if the character is a UTF-8 character of any width.
 *
 * The f_macro_utf_byte_is_* macros are used to determine a width of the character (either 1, 2, 3, or 4, respectively).
 *
 * The f_macro_utf_byte_width macro determines a width of the character.
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

  #define f_macro_utf_byte_is(character) (character & f_utf_byte_1)

  #define f_macro_utf_byte_is_1(character) ((character & f_utf_byte_off_1) == f_utf_byte_1) // (10xx xxxx & 1100 0000) == 1000 0000
  #define f_macro_utf_byte_is_2(character) ((character & f_utf_byte_off_2) == f_utf_byte_2) // (110x xxxx & 1110 0000) == 1100 0000
  #define f_macro_utf_byte_is_3(character) ((character & f_utf_byte_off_3) == f_utf_byte_3) // (1110 xxxx & 1111 0000) == 1110 0000
  #define f_macro_utf_byte_is_4(character) ((character & f_utf_byte_off_4) == f_utf_byte_4) // (1111 0xxx & 1111 1000) == 1111 0000

  #define f_macro_utf_byte_width(character) (!f_macro_utf_byte_is(character) || f_macro_utf_byte_is_1(character)) ? 1 : (f_macro_utf_byte_is_2(character) ? 2 : (f_macro_utf_byte_is_3(character) ? 3 : 4))
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

  const static char f_utf_space_em[f_utf_space_em_length]                     = { 0xe2, 0x80, 0x83 };
  const static char f_utf_space_em_quad[f_utf_space_em_quad_length]           = { 0xe2, 0x80, 0x81 };
  const static char f_utf_space_em_per_three[f_utf_space_em_per_three_length] = { 0xe2, 0x80, 0x84 };
  const static char f_utf_space_em_per_four[f_utf_space_em_per_four_length]   = { 0xe2, 0x80, 0x85 };
  const static char f_utf_space_em_per_six[f_utf_space_em_per_six_length]     = { 0xe2, 0x80, 0x86 };

  const static char f_utf_space_en[f_utf_space_en_length]           = { 0xe2, 0x80, 0x82 };
  const static char f_utf_space_en_quad[f_utf_space_en_quad_length] = { 0xe2, 0x80, 0x80 };

  const static char f_utf_space_line_feed_reverse[f_utf_space_line_feed_reverse_length] = { 0xc2, 0x8d };
  const static char f_utf_space_line_next[f_utf_space_line_next_length]                 = { 0xc2, 0x85 };

  const static char f_utf_space_medium_mathematical[f_utf_space_medium_mathematical_length] = { 0xe2, 0x81, 0x9f };

  const static char f_utf_space_no_break[f_utf_space_no_break_length]               = { 0xc2, 0xa0 };
  const static char f_utf_space_no_break_narrow[f_utf_space_no_break_narrow_length] = { 0xe2, 0x80, 0xaf };

  const static char f_utf_space_ogham[f_utf_space_ogham_length]             = { 0xe1, 0x9a, 0x80 };
  const static char f_utf_space_figure[f_utf_space_figure_length]           = { 0xe2, 0x80, 0x87 };
  const static char f_utf_space_punctuation[f_utf_space_punctuation_length] = { 0xe2, 0x80, 0x88 };
  const static char f_utf_space_thin[f_utf_space_thin_length]               = { 0xe2, 0x80, 0x89 };
  const static char f_utf_space_hair[f_utf_space_hair_length]               = { 0xe2, 0x80, 0x8a };
  const static char f_utf_space_ideographic[f_utf_space_ideographic_length] = { 0xe3, 0x80, 0x80 };

  const static char f_utf_space_separator_line[f_utf_space_separator_line_length]           = { 0xe2, 0x80, 0xa8 };
  const static char f_utf_space_separator_paragraph[f_utf_space_separator_paragraph_length] = { 0xe2, 0x80, 0xa8 };
#endif // _di_f_utf_space_

/**
 * Define the UTF-8 general substitute whitespace codes.
 *
 * These are integers representing character codes that represent types of substitute spaces.
 *
 * This does not provide substitute whitespace codes for standard ascii whitespaces, such as '\t' or '\r'.
 */
#ifndef _di_f_utf_substitute_
  #define f_utf_substitute_symbol_blank_length 3
  #define f_utf_substitute_symbol_space_length 3

  #define f_utf_substitute_middle_dot_length 2

  #define f_utf_substitute_open_box_length            3
  #define f_utf_substitute_open_box_shouldered_length 3

  const static char f_utf_substitute_symbol_blank[f_utf_substitute_symbol_blank_length] = { 0xe2, 0x90, 0xa2 };
  const static char f_utf_substitute_symbol_space[f_utf_substitute_symbol_space_length] = { 0xe2, 0x90, 0xa0 };

  const static char f_utf_substitute_middle_dot[f_utf_substitute_middle_dot_length] = { 0xc2, 0xb7 };

  const static char f_utf_substitute_open_box[f_utf_substitute_open_box_length]                       = { 0xe2, 0x90, 0xa3 };
  const static char f_utf_substitute_open_box_shouldered[f_utf_substitute_open_box_shouldered_length] = { 0xe2, 0x8d, 0xbd };
#endif // _di_f_utf_substitute_

/**
 * Check to see if the entire byte block of the character is a UTF-8 BOM.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by maxWidth.
 * @param maxWidth
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 whitespace or substitute.
 *   f_false if not a UTF-8 whitespace or substitute.
 *   f_maybe (with error bit) if this could be a whitespace or substitute but width is not long enough.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_bom_
  extern f_return_status f_utf_is_bom(const f_string character, const f_u_short maxWidth);
#endif // _di_f_utf_is_bom_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace or substitute character.
 *
 * This will also return TRUE for the UTF-8 BOM.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by maxWidth.
 * @param maxWidth
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 whitespace, substitute, or UTF-8 BOM.
 *   f_false if not a UTF-8 whitespace or substitute.
 *   f_maybe (with error bit) if this could be a whitespace or substitute but width is not long enough.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_space_
  extern f_return_status f_utf_is_space(const f_string character, const f_u_short maxWidth);
#endif // _di_f_utf_is_space_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace substitute character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by maxWidth.
 * @param maxWidth
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 substitute.
 *   f_false if not a UTF-8 substitute.
 *   f_maybe (with error bit) if this could be a substitute but width is not long enough.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_substitute_
  extern f_return_status f_utf_is_substitute(const f_string character, const f_u_short maxWidth);
#endif // _di_f_utf_is_substitute_

/**
 * Check to see if the entire byte block of the character is a UTF-8 general whitespace character.
 *
 * This does not check non-UTF-8 whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by maxWidth.
 * @param maxWidth
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   f_true if a UTF-8 whitespace.
 *   f_false if not a UTF-8 whitespace.
 *   f_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_whitespace_
  extern f_return_status f_utf_is_whitespace(const f_string character, const f_u_short maxWidth);
#endif // _di_f_utf_is_whitespace_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h

/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides UTF-8 capabilities.
 *
 * @todo consider is_graph() functions being their own data set (review unicode to see which of checking only for graph() vs checking for all not-graph will be the smaller set).
 *
 * Identifiers:
 *   - UTF_8-1: 1000 0000
 *   - UTF_8-2: 1100 0000
 *   - UTF_8-3: 1110 0000
 *   - UTF_8-4: 1111 0000
 *
 * Values:
 *   - UTF_8-1: 1011 1111
 *   - UTF_8-2: 1101 1111
 *   - UTF_8-3: 1110 1111
 *   - UTF_8-4: 1111 0111
 *
 * Identifier Structure:
 *   - UTF_8-1: 1000 0000
 *   - UTF_8-2: 1100 0000 1000 0000
 *   - UTF_8-3: 1110 0000 1000 0000 1000 0000
 *   - UTF_8-4: 1111 0000 1000 0000 1000 0000 1000 0000
 *
 * Value Structure:
 *   - UTF_8-1: 10xx xxxx
 *   - UTF_8-2: 110x xxxx, 10xx xxxx
 *   - UTF_8-3: 1110 xxxx, 10xx xxxx, 10xx xxxx
 *   - UTF_8-4: 1111 0xxx, 10xx xxxx, 10xx xxxx, 10xx xxxx
 */
#ifndef _F_utf_h
#define _F_utf_h

// libc includes.
#include <endian.h>
#include <ctype.h>
#include <string.h>

// fll-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// fll-0 utf includes
#include <fll/level_0/utf-common.h>
#include <fll/level_0/utf_dynamic.h>
#include <fll/level_0/utf_map.h>
#include <fll/level_0/utf_string.h>
#include <fll/level_0/utf_triple.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Continue to the previous character, based on step and character width.
 *
 * For navigating a range within the given buffer by a specific number of characters that could be of any width allowed by UTF-8.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to decrement the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be sizeof(uint8_t), which is 1.
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(uint8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_data_not if buffer is empty or out of range.
 *
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_buffer_decrement_
  extern f_status_t f_utf_buffer_decrement(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step);
#endif // _di_f_utf_buffer_decrement_

/**
 * Continue to the next character, based on step and character width.
 *
 * For navigating a range within the given buffer by a specific number of characters that could be of any width allowed by UTF-8.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to increment the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be sizeof(uint8_t), which is 1.
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(uint8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_data_not if buffer is empty or out of range.
 *
 *   F_complete_not_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_buffer_increment_
  extern f_status_t f_utf_buffer_increment(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step);
#endif // _di_f_utf_buffer_increment_

/**
 * Check to see if the entire byte block of the character is a non-ASCII UTF-8 character.
 *
 * This does not validate if the UTF-8 character is a valid UTF-8 character, for that use f_utf_character_is_valid().
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 *   F_utf_fragment if this is a UTF-8 character fragment.
 *
 * @see f_utf_character_is_valid()
 */
#ifndef _di_f_utf_character_is_
  extern f_status_t f_utf_character_is(const f_utf_character_t character);
#endif // _di_f_utf_character_is_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alphabet character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalpha()
 */
#ifndef _di_f_utf_character_is_alpha_
  extern f_status_t f_utf_character_is_alpha(const f_utf_character_t character);
#endif // _di_f_utf_character_is_alpha_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabetic or digit character.
 *
 * Digit characters are decimal digits and letter numbers.
 *
 * This does not include number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 alpha-digit character.
 *   F_false if not a UTF-8 alpha-digit character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_alpha_digit_
  extern f_status_t f_utf_character_is_alpha_digit(const f_utf_character_t character);
#endif // _di_f_utf_character_is_alpha_digit_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabetic or numeric character.
 *
 * Numeric characters are decimal digits, letter numbers, and number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 alpha-numeric character.
 *   F_false if not a UTF-8 alpha-numeric character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_alpha_numeric_
  extern f_status_t f_utf_character_is_alpha_numeric(const f_utf_character_t character);
#endif // _di_f_utf_character_is_alpha_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII character.
 *
 * This does not validate whether the UTF-8 character is valid or not.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if an ASCII character.
 *   F_false if not an ASCII character.
 */
#ifndef _di_f_utf_character_is_ascii_
  extern f_status_t f_utf_character_is_ascii(const f_utf_character_t character);
#endif // _di_f_utf_character_is_ascii_

/**
 * Check to see if the entire byte block of the character is a UTF-8 combining character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 combining character.
 *   F_false if not a UTF-8 combining character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_combining_
  extern f_status_t f_utf_character_is_combining(const f_utf_character_t character);
#endif // _di_f_utf_character_is_combining_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
 *
 * This includes control code and control format characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_character_is_control_
  extern f_status_t f_utf_character_is_control(const f_utf_character_t character);
#endif // _di_f_utf_character_is_control_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control code character.
 *
 * Control Code characters are the traditional control characters, such as "\n" as well as some newer Unicode ones.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 control code character.
 *   F_false if not a UTF-8 control code character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_character_is_control_code_
  extern f_status_t f_utf_character_is_control_code(const f_utf_character_t character);
#endif // _di_f_utf_character_is_control_code_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control format character.
 *
 * Control Format characters are special characters used for formatting.
 * These are considered control characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 control format character.
 *   F_false if not a UTF-8 control format character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_control_format_
  extern f_status_t f_utf_character_is_control_format(const f_utf_character_t character);
#endif // _di_f_utf_character_is_control_format_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control picture character.
 *
 * Control Picture characters are placeholders for special ASCII characters and therefore there are no ASCII Control Picture characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_control_picture_
  extern f_status_t f_utf_character_is_control_picture(const f_utf_character_t character);
#endif // _di_f_utf_character_is_control_picture_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 digit character.
 *
 * Digit characters are decimal digits and letter numbers.
 *
 * This does not include number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 digit character.
 *   F_false if not a UTF-8 digit character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_character_is_digit_
  extern f_status_t f_utf_character_is_digit(const f_utf_character_t character);
#endif // _di_f_utf_character_is_digit_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 emoji character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 emoji character.
 *   F_false if not a UTF-8 emoji character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_emoji_
  extern f_status_t f_utf_character_is_emoji(const f_utf_character_t character);
#endif // _di_f_utf_character_is_emoji_

/**
 * Check to see if the entire byte block of the character is a 1-width UTF-8 character fragment.
 *
 * Characters whose width is 1-byte are invalid.
 * However, the character could have been cut-off, so whether or not this is actually valid should be determined by the caller.
 *
 * For normal validation functions, try using f_utf_character_is() or f_utf_character_is_valid().
 *
 * According to rfc3629, the valid octect sequences for UTF-8 are:
 *   UTF8-octets = *( UTF8-char )
 *   UTF8-char   = UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
 *   UTF8-1      = %x00-7F
 *   UTF8-2      = %xC2-DF UTF8-tail
 *   UTF8-3      = %xE0 %xA0-BF UTF8-tail / %xE1-EC 2( UTF8-tail ) /
 *                 %xED %x80-9F UTF8-tail / %xEE-EF 2( UTF8-tail )
 *   UTF8-4      = %xF0 %x90-BF 2( UTF8-tail ) / %xF1-F3 3( UTF8-tail ) /
 *                 %xF4 %x80-8F 2( UTF8-tail )
 *   UTF8-tail   = %x80-BF
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is()
 * @see f_utf_character_is_valid()
 */
#ifndef _di_f_utf_character_is_fragment_
  extern f_status_t f_utf_character_is_fragment(const f_utf_character_t character);
#endif // _di_f_utf_character_is_fragment_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 printable character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 graph.
 *   F_false if not a UTF-8 graph.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isgraph()
 */
#ifndef _di_f_utf_character_is_graph_
  extern f_status_t f_utf_character_is_graph(const f_utf_character_t character);
#endif // _di_f_utf_character_is_graph_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 numeric character.
 *
 * Numeric characters are decimal digits, letter numbers, and number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 numeric character.
 *   F_false if not a UTF-8 numeric character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_character_is_numeric_
  extern f_status_t f_utf_character_is_numeric(const f_utf_character_t character);
#endif // _di_f_utf_character_is_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 phonetic character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 phonetic character.
 *   F_false if not a UTF-8 phonetic character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_phonetic_
  extern f_status_t f_utf_character_is_phonetic(const f_utf_character_t character);
#endif // _di_f_utf_character_is_phonetic_

/**
 * Check to see if the entire byte block of the character is a UTF-8 private character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 private character.
 *   F_false if not a UTF-8 private character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_private_
  extern f_status_t f_utf_character_is_private(const f_utf_character_t character);
#endif // _di_f_utf_character_is_private_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 punctuation character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 punctuation character.
 *   F_false if not a UTF-8 punctuation character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_punctuation_
  extern f_status_t f_utf_character_is_punctuation(const f_utf_character_t character);
#endif // _di_f_utf_character_is_punctuation_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 symbol character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 symbol character.
 *   F_false if not a UTF-8 symbol character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_symbol_
  extern f_status_t f_utf_character_is_symbol(const f_utf_character_t character);
#endif // _di_f_utf_character_is_symbol_

/**
 * Check to see if the entire byte block of the character is a unassigned (well-formed) UTF-8 character.
 *
 * The Surrogates and Private Use are not considered unassigned.
 *
 * This does validate if the UTF-8 character is a unassigned UTF-8 character.
 * To not do this, use f_utf_character_is().
 *
 * @param character
 *   The character to unassignedate.
 *
 * @return
 *   F_true if a UTF-8 unassigned character.
 *   F_false if not a UTF-8 unassigned character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is()
 * @see f_utf_character_is_fragment()
 */
#ifndef _di_f_utf_character_is_unassigned_
  extern f_status_t f_utf_character_is_unassigned(const f_utf_character_t character);
#endif // _di_f_utf_character_is_value_

/**
 * Check to see if the entire byte block of the character is a valid (well-formed) UTF-8 character.
 *
 * This does validate if the UTF-8 character is a valid UTF-8 character.
 * To not do this, use f_utf_character_is().
 *
 * ASCII character codes are considered valid by this function.
 *
 * Codes U+FDD0 to U+FDEF and any character ending in FFFE or FFFF are non-characters, and are therefore invalid.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is()
 * @see f_utf_character_is_fragment()
 */
#ifndef _di_f_utf_character_is_valid_
  extern f_status_t f_utf_character_is_valid(const f_utf_character_t character);
#endif // _di_f_utf_character_is_value_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general space character.
 *
 * Non-printing or zero-width characters are not considered whitespace.
 * This does include line separators like '\n'.
 * This does not include phonetic spaces, like whitespace modifiers.
 * This does not include non-true whitespace characters, such as Ogham Space Mark ( ).
 *
 * Phonetic spaces are whitespaces with additional phonetic meaning associated with them.
 * However, because they are not renderred as whitespace, they are technically not white space.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isspace()
 */
#ifndef _di_f_utf_character_is_whitespace_
  extern f_status_t f_utf_character_is_whitespace(const f_utf_character_t character);
#endif // _di_f_utf_character_is_whitespace_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 whitespace modifier character.
 *
 * These are phonetic spaces.
 *
 * Phonetic spaces are whitespaces with additional phonetic meaning associated with them.
 * Therefore, these are valid spaces in the technical sense, even if they are not visibly whitespace.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 modifier character.
 *   F_false if not a UTF-8 modifier character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_whitespace_modifier_
  extern f_status_t f_utf_character_is_whitespace_modifier(const f_utf_character_t character);
#endif // _di_f_utf_character_is_whitespace_modifier_

/**
 * Check to see if the entire byte block of the character is an other type of UTF-8 space character.
 *
 * This is a list of whitespace that are not actual whitespace (because they are graph characters) but are considered whitespace, such as Ogham Space Mark ( ).
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 (other) whitespace.
 *   F_false if not a UTF-8 (other) whitespace.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isspace()
 */
#ifndef _di_f_utf_character_is_whitespace_other_
  extern f_status_t f_utf_character_is_whitespace_other(const f_utf_character_t character);
#endif // _di_f_utf_character_is_whitespace_other_

/**
 * Get whether or not the UTF-8 character is a wide character on display.
 *
 * This is not the wide as in width in bytes that the codepoint takes up in UTF-8.
 * Instead, this is the width in characters on the screen the character takes up.
 * When "wide" characters that take up either 2 characters on render.
 * When "narrow" characters that take up either 1 character on render.
 *
 * @param character
 *   The (UTF-8) character.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_wide_
  extern f_status_t f_utf_character_is_wide(const f_utf_character_t character);
#endif // _di_f_utf_character_is_wide_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-numeric or an underscore '_'.
 *
 * @param character
 *   The character to validate.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word character.
 *   F_false if not a UTF-8 word character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_word_
  extern f_status_t f_utf_character_is_word(const f_utf_character_t character, const bool strict);
#endif // _di_f_utf_character_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alpha-numeric, an underscore '_' or a dash '-'.
 *
 * Unicode appears to refer to dashes that connect words as a hyphen.
 * Therefore, only these hyphens are considered dashes for the purposes of this function.
 * All other dash-like Unicode characters are not considered a dash here.
 * The dash here is intended for combining words, which matches the context of the Unicode "hyphen".
 *
 * @param character
 *   The character to validate.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_word_dash_
  extern f_status_t f_utf_character_is_word_dash(const f_utf_character_t character, const bool strict);
#endif // _di_f_utf_character_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash plus character is alpha-digit, an underscore '_', a dash '-', or a plus '+'.
 *
 * Unicode appears to refer to dashes that connect words as a hyphen.
 * Therefore, only these hyphens are considered dashes for the purposes of this function.
 * All other dash-like Unicode characters are not considered a dash here.
 * The dash here is intended for combining words, which matches the context of the Unicode "hyphen".
 *
 * This does not include zero-width punctuation, such as "invisible plus" (U+2064) (even in strict mode).
 *
 * @param character
 *   The character to validate.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_word_dash_plus_
  extern f_status_t f_utf_character_is_word_dash_plus(const f_utf_character_t character, const bool strict);
#endif // _di_f_utf_character_is_word_dash_plus_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general non-printing character.
 *
 * Only characters that do not print, which are generally called zero-width.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 non-printing or zero-width character.
 *   F_false if not a UTF-8 non-printing or zero-width character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_is_zero_width_
  extern f_status_t f_utf_character_is_zero_width(const f_utf_character_t character);
#endif // _di_f_utf_character_is_zero_width_

/**
 * Convert a specialized f_utf_character_t type to a uint8_t, stored as a string (character buffer).
 *
 * This will also convert ASCII characters stored in the utf_character array.
 * This will not resize character.
 *
 * @param utf_character
 *   The UTF-8 character to convert from.
 * @param character
 *   A uint8_t representation of the UTF-8 character, stored as a string of width bytes.
 *   If width_max is 0, then this should be set to 0.
 * @param width_max
 *   This is set to the max number of bytes available.
 *   This is then updated to represent the max bytes used if enough space is available.
 *
 * @return
 *   F_none if conversion was successful.
 *
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_to_char_
  extern f_status_t f_utf_character_to_char(const f_utf_character_t utf_character, f_string_t *character, f_array_length_t *width_max);
#endif // _di_f_utf_character_to_char_

/**
 * Convert a given (UTF-8) character into Unicode.
 *
 * The f_utf_character_t is a 32-bit integer containing UTF-8 sequences, unchanged.
 * The Unicode is a 32-bit integer representing the Unicode (such as U+0001).
 * The Unciode does not need to be interpretted like UTF-8, it simple is a sequence of number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @param character
 *   The (UTF-8) character.
 * @param unicode
 *   The Unicode number.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_valid()
 */
#ifndef _di_f_utf_character_unicode_to_
  extern f_status_t f_utf_character_unicode_to(const f_utf_character_t character, uint32_t *unicode);
#endif // _di_f_utf_character_unicode_to_

/**
 * Convert a given Unicode into (UTF-8) character.
 *
 * The f_utf_character_t is a 32-bit integer containing UTF-8 sequences, unchanged.
 * The Unicode is a 32-bit integer representing the Unicode (such as U+0001).
 * The Unciode does not need to be interpretted like UTF-8, it simple is a sequence of number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @param unicode
 *   The Unicode number.
 * @param character
 *   The (UTF-8) character.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_character_unicode_from_
  extern f_status_t f_utf_character_unicode_from(const uint32_t unicode, f_utf_character_t *character);
#endif // _di_f_utf_character_unicode_from_

/**
 * Convert a string of the format "U+FFFF" into the codepoint value.
 *
 * This ignores NULL characters.
 * The string may only contain "U+" followed by a hexidecimal digit, upper or lower case.
 * The "U+" prefix is optional.
 * Only ASCII characters are allowed to represent the Unicode sequence string.
 *
 * @param string
 *   The string representing a Unicode sequence.
 * @param length
 *   The maximum number of characters.
 * @param unicode
 *   A 32-bit integer representing the Unicode (such as U+0001).
 *   Does not need to be interpretted like UTF-8, this is a number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_valid_not (with error bit) if string is not a valid Unicode string.
 */
#ifndef _di_f_utf_character_unicode_string_to_
  extern f_status_t f_utf_character_unicode_string_to(const f_utf_string_t string, const f_array_length_t length, uint32_t *unicode);
#endif // _di_f_utf_character_unicode_string_to_

/**
 * Check to see if the entire byte block of the character is a non-ASCII UTF-8 character.
 *
 * This does not check the validity of the character, for that instead use f_utf_is_valid().
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 */
#ifndef _di_f_utf_is_
  extern f_status_t f_utf_is(const f_string_t character);
#endif // _di_f_utf_is_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alphabet character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalpha()
 */
#ifndef _di_f_utf_is_alpha_
  extern f_status_t f_utf_is_alpha(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_alpha_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet or digit character.
 *
 * Digit characters are decimal digits and letter numbers.
 *
 * This does not include number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alpha-numeric character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_alpha_digit_
  extern f_status_t f_utf_is_alpha_digit(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_alpha_digit_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet or numeric character.
 *
 * Numeric characters are decimal digits, letter numbers, and number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alpha-numeric character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_alpha_numeric_
  extern f_status_t f_utf_is_alpha_numeric(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_alpha_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if an ASCII character.
 *   F_false if not an ASCII character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_ascii_
  extern f_status_t f_utf_is_ascii(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_ascii_

/**
 * Check to see if the entire byte block of the character is a UTF-8 combining character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 combining character.
 *   F_false if not a UTF-8 combining character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_combining_
  extern f_status_t f_utf_is_combining(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_combining_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
 *
 * This includes control code and control format characters.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_is_control_
  extern f_status_t f_utf_is_control(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control code character.
 *
 * Control Code characters are the traditional control characters, such as "\n" as well as some newer Unicode ones.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control code character.
 *   F_false if not a UTF-8 control code character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_control_code_
  extern f_status_t f_utf_is_control_code(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_code_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control format character.
 *
 * Control Format characters are special characters used for formatting.
 * These are considered control characters.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control format character.
 *   F_false if not a UTF-8 control format character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_control_format_
  extern f_status_t f_utf_is_control_format(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_format_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control picture character.
 *
 * Control Picture characters are placeholders for special ASCII characters and therefore there are no ASCII Control Picture characters.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_control_picture_
  extern f_status_t f_utf_is_control_picture(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_picture_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 digit character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 digit character.
 *   F_false if not a UTF-8 digit character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_is_digit_
  extern f_status_t f_utf_is_digit(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_digit_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 emoji character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 emoji character.
 *   F_false if not a UTF-8 emoji character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_emoji_
  extern f_status_t f_utf_is_emoji(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_emoji_

/**
 * Check to see if the entire byte block of the character is a 1-width UTF-8 character fragment.
 *
 * Characters whose width is 1-byte are invalid.
 * However, the character could have been cut-off, so whether or not this is actually valid should be determined by the caller.
 *
 * For normal validation functions, try using f_utf_character_is() or f_utf_character_is_valid().
 *
 * According to rfc3629, the valid octect sequences for UTF-8 are:
 *   UTF8-octets = *( UTF8-char )
 *   UTF8-char   = UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
 *   UTF8-1      = %x00-7F
 *   UTF8-2      = %xC2-DF UTF8-tail
 *   UTF8-3      = %xE0 %xA0-BF UTF8-tail / %xE1-EC 2( UTF8-tail ) /
 *                 %xED %x80-9F UTF8-tail / %xEE-EF 2( UTF8-tail )
 *   UTF8-4      = %xF0 %x90-BF 2( UTF8-tail ) / %xF1-F3 3( UTF8-tail ) /
 *                 %xF4 %x80-8F 2( UTF8-tail )
 *   UTF8-tail   = %x80-BF
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 */
#ifndef _di_f_utf_is_fragment_
  extern f_status_t f_utf_is_fragment(const f_string_t character);
#endif // _di_f_utf_is_fragment_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 printable character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 graph.
 *   F_false if not a UTF-8 graph.
 *
 *   F_maybe (with error bit) if this could be a graph but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isgraph()
 */
#ifndef _di_f_utf_is_graph_
  extern f_status_t f_utf_is_graph(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_graph_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 numeric character.
 *
 * Numeric characters are decimal digits, letter numbers, and number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 numeric character.
 *   F_false if not a UTF-8 numeric character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_is_numeric_
  extern f_status_t f_utf_is_numeric(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 phonetic character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 phonetic character.
 *   F_false if not a UTF-8 phonetic character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_phonetic_
  extern f_status_t f_utf_is_phonetic(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_phonetic_

/**
 * Check to see if the entire byte block of the character is a UTF-8 private character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 punctuation character.
 *   F_false if not a UTF-8 punctuation character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_private_
  extern f_status_t f_utf_is_private(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_private_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 punctuation character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 punctuation character.
 *   F_false if not a UTF-8 punctuation character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_punctuation_
  extern f_status_t f_utf_is_punctuation(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_punctuation_

/**
 * Check to see if the entire byte block of the character is a surrogate UTF-8 character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 symbol character.
 *   F_false if not a UTF-8 symbol character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_surrogate_
  extern f_status_t f_utf_is_surrogate(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_surrogate_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 symbol character.
 *
 * @todo Incomplete, UTF-8 codes not yet checked!
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 symbol character.
 *   F_false if not a UTF-8 symbol character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_symbol_
  extern f_status_t f_utf_is_symbol(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_symbol_

/**
 * Check to see if the entire byte block of the character is a unassigned UTF-8 character.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if an unassigned UTF-8 character.
 *   F_false if not an unassigned UTF-8 character.
 *
 *   F_parameter (with error bit) if a parameter is inunassigned.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_unassigned_
  extern f_status_t f_utf_is_unassigned(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_unassigned_

/**
 * Check to see if the entire byte block of the character is a valid (well-formed) UTF-8 character.
 *
 * This does validate if the UTF-8 character is a valid UTF-8 character.
 * To not do this, use f_utf_is().
 *
 * Valid ASCII character codes are considered valid by this function.
 *
 * Codes U+FDD0 to U+FDEF and any character ending in FFFE or FFFF are non-characters, and are therefore invalid.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a valid UTF-8 character or is an ASCII character.
 *   F_false if not a valid UTF-8 character.
 *
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_valid_
  extern f_status_t f_utf_is_valid(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_valid_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general space character.
 *
 * Non-printing or zero-width characters are not considered whitespace.
 * This does include line separators like '\n'.
 * This does not include phonetic spaces, like whitespace modifiers.
 * This does not include non-true whitespace characters, such as Ogham Space Mark ( ).
 *
 * Phonetic spaces are whitespaces with additional phonetic meaning associated with them.
 * However, because they are not renderred as whitespace, they are technically not white space.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isspace()
 */
#ifndef _di_f_utf_is_whitespace_
  extern f_status_t f_utf_is_whitespace(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_

/**
 * Check to see if the entire byte block of the character is a UTF-8 whitespace modifier character.
 *
 * These are phonetic spaces.
 *
 * Phonetic spaces are whitespaces with additional phonetic meaning associated with them.
 * Therefore, these are valid spaces in the technical sense, even if they are not visibly whitespace.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_whitespace_modifier_
  extern f_status_t f_utf_is_whitespace_modifier(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_modifier_

/**
 * Check to see if the entire byte block of the character is an other type of UTF-8 space character.
 *
 * This is a list of whitespace that are not actual whitespace (because they are graph characters) but are considered whitespace, such as Ogham Space Mark ( ).
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_whitespace_other_
  extern f_status_t f_utf_is_whitespace_other(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_other_

/**
 * Get whether or not the UTF-8 character is a wide character on display.
 *
 * This is not the wide as in width in bytes that the codepoint takes up in UTF-8.
 * Instead, this is the width in characters on the screen the character takes up.
 * When "wide" characters that take up either 2 characters on render.
 * When "narrow" characters that take up either 1 character on render.
 *
 * @param character
 *   The (UTF-8) character.
 * @param width_max
 *   The max width available for representing the UTF-8 character.
 *   There must be enough space in the character buffer to handle the Unicode width.
 *   It is recommended to always have 4 characters (4 uint8_t) of space available in character.
 *   This is the width in bytes the codepoint takes up in UTF-8.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_wide_
  extern f_status_t f_utf_is_wide(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_wide_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-digit or an underscore '_'.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word character.
 *   F_false if not a UTF-8 word character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_
  extern f_status_t f_utf_is_word(const f_string_t character, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alpha-digit, an underscore '_' or a dash '-'.
 *
 * Unicode appears to refer to dashes that connect words as a hyphen.
 * Therefore, only these hyphens are considered dashes for the purposes of this function.
 * All other dash-like Unicode characters are not considered a dash here.
 * The dash here is intended for combining words, which matches the context of the Unicode "hyphen".
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_dash_
  extern f_status_t f_utf_is_word_dash(const f_string_t character, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash plus character is alpha-digit, an underscore '_', a dash '-', or a plus '+'.
 *
 * Unicode appears to refer to dashes that connect words as a hyphen.
 * Therefore, only these hyphens are considered dashes for the purposes of this function.
 * All other dash-like Unicode characters are not considered a dash here.
 * The dash here is intended for combining words, which matches the context of the Unicode "hyphen".
 *
 * This does not include zero-width punctuation, such as "invisible plus" (U+2064) (even in strict mode).
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_dash_plus_
  extern f_status_t f_utf_is_word_dash_plus(const f_string_t character, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_word_dash_plus_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general non-printing character.
 *
 * Only characters that do not print, which are generally called zero-width.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_zero_width_
  extern f_status_t f_utf_is_zero_width(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_zero_width_

/**
 * Convert an ASCII or UTF-8 character, stored as a string (character buffer), to the specialized f_utf_character_t type.
 *
 * @param character
 *   The character string to be converted to the f_utf_character_t type.
 *   There must be enough space allocated to convert against, as limited by width_max.
 * @param width_max
 *   The maximum width available for converting.
 *   Can be anything greater than 0.
 * @param character_utf
 *   The generated character of type f_utf_character_t.
 *   This value may be cleared, even on error.
 *
 * @return
 *   F_none if conversion was successful.
 *
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_char_to_character_
  extern f_status_t f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_character_t *character_utf);
#endif // _di_f_utf_char_to_character_

/**
 * Convert a given Unicode into a string block representing a single character.
 *
 * @param character
 *   The (UTF-8) character.
 *   The f_utf_character_t is a 32-bit integer containing UTF-8 sequences, unchanged.
 * @param width_max
 *   The max width available for representing the UTF-8 character.
 *   There must be enough space in the character buffer to handle the Unicode width.
 *   It is recommended to always have 4 characters (4 uint8_t) of space available in character.
 * @param unicode
 *   A 32-bit integer representing the Unicode (such as U+0001).
 *   Does not need to be interpretted like UTF-8, this is a number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_unicode_from_
  extern f_status_t f_utf_unicode_from(const uint32_t unicode, const f_array_length_t width_max, f_string_t *character);
#endif // _di_f_utf_unicode_from_

/**
 * Convert a given string block representing a single character into Unicode.
 *
 * @param character
 *   The (UTF-8) character to convert to the Unicode representation.
 *   The f_utf_character_t is a 32-bit integer containing UTF-8 sequences, unchanged.
 * @param width_max
 *   The max width available for representing the UTF-8 character.
 *   There must be enough space in the character buffer to handle the Unicode width.
 *   It is recommended to always have 4 characters (4 uint8_t) of space available in character.
 * @param unicode
 *   A 32-bit integer representing the Unicode (such as U+0001).
 *   Does not need to be interpretted like UTF-8, this is a number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_valid()
 */
#ifndef _di_f_utf_unicode_to_
  extern f_status_t f_utf_unicode_to(const f_string_t character, const f_array_length_t width_max, uint32_t *unicode);
#endif // _di_f_utf_unicode_to_

/**
 * Convert a string of the format "U+FFFF" into the codepoint value.
 *
 * This ignores NULL characters.
 * The string may only contain "U+" followed by a hexidecimal digit, upper or lower case.
 * The "U+" prefix is optional.
 * Only ASCII characters are allowed to represent the Unicode sequence string.
 *
 * @param string
 *   The string representing a Unicode sequence.
 * @param length
 *   The maximum number of characters.
 * @param unicode
 *   A 32-bit integer representing the Unicode (such as U+0001).
 *   Does not need to be interpretted like UTF-8, this is a number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_valid_not (with error bit) if string is not a valid Unicode string.
 */
#ifndef _di_f_utf_unicode_string_to_
  extern f_status_t f_utf_unicode_string_to(const f_string_t string, const f_array_length_t length, uint32_t *unicode);
#endif // _di_f_utf_unicode_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h

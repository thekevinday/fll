/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 capabilities.
 *
 * @todo consider is_graph() functions being their own data set (review unicode to see which of checking only for graph() vs checking for all not-graph will be the smaller set).
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
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

// fll-0 utf includes
#include <level_0/utf-common.h>
#include <level_0/utf_dynamic.h>
#include <level_0/utf_map.h>
#include <level_0/utf_quantity.h>
#include <level_0/utf_range.h>
#include <level_0/utf_triple.h>

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
 *   (For ASCII each step would be sizeof(int8_t), which is 1.
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(int8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_data_not if buffer is empty or out of range.
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
 *   (For ASCII each step would be sizeof(int8_t), which is 1.
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(int8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_data_not if buffer is empty or out of range.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_alpha_numeric_
  extern f_status_t f_utf_character_is_alpha_numeric(const f_utf_character_t character);
#endif // _di_f_utf_character_is_alpha_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if an ASCII character.
 *   F_false if not an ASCII character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_character_is_combining_
  extern f_status_t f_utf_character_is_combining(const f_utf_character_t character);
#endif // _di_f_utf_character_is_combining_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_character_is_control_
  extern f_status_t f_utf_character_is_control(const f_utf_character_t character);
#endif // _di_f_utf_character_is_control_

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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_character_is_symbol_
  extern f_status_t f_utf_character_is_symbol(const f_utf_character_t character);
#endif // _di_f_utf_character_is_symbol_

/**
 * Check to see if the entire byte block of the character is a unassigned (well-formed) UTF-8 character.
 *
 * This does unassignedate if the UTF-8 character is a unassigned UTF-8 character.
 * To not do this, use f_utf_character_is().
 *
 * @param character
 *   The character to unassignedate.
 *
 * @return
 *   F_true if a UTF-8 unassigned character.
 *   F_false if not a UTF-8 unassigned character.
 *   F_utf (with error bit) if character is an inunassigned UTF-8 character.
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
 * Valid ASCII character codes are considered valid by this function.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see isspace()
 */
#ifndef _di_f_utf_character_is_whitespace_other_
  extern f_status_t f_utf_character_is_whitespace_other(const f_utf_character_t character);
#endif // _di_f_utf_character_is_whitespace_other_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-numeric or an underscore '_'.
 *
 * This does not include zero-width punctuation.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 * This does not include zero-width punctuation.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
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
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_character_is_zero_width_
  extern f_status_t f_utf_character_is_zero_width(const f_utf_character_t character);
#endif // _di_f_utf_character_is_zero_width_

/**
 * Convert a specialized f_utf_character_t type to a int8_t, stored as a string (character buffer).
 *
 * This will also convert ASCII characters stored in the utf_character array.
 *
 * @param utf_character
 *   The UTF-8 characterr to convert from.
 * @param character
 *   A int8_t representation of the UTF-8 character, stored as a string of width bytes.
 *   If width_max is 0, then this should not be allocated (set the pointer address to 0).
 * @param width_max
 *   The number of bytes the generated character represents.
 *   If this is set to 0, then the character will be allocated and this will be set to the width of the utf_character.
 *   If this is set to some value greater than 0 (up to 4), then this represents the size of the character array (no allocations are performed).
 *   If this is greater than 0, and the utf_character width is larger than this size, then an error is returned.
 *
 * @return
 *   F_none if conversion was successful.
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_not (with error bit) on out of memory.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *   F_failure (with error bit) if width is not long enough to convert.
 */
#ifndef _di_f_utf_character_to_char_
  extern f_status_t f_utf_character_to_char(const f_utf_character_t utf_character, f_string_t *character, f_array_length_t *width_max);
#endif // _di_f_utf_character_to_char_

/**
 * Helper function for UTF-8 processing code to determine endianess of the system.
 *
 * @todo relocate this outside of f_utf into a more general path, perhaps f_memory (f_memory_is_big_endian).
 *
 * @return
 *   F_true if the system is big-endian.
 *   F_false if the system is little-endian.
 */
#ifndef _di_f_utf_is_big_endian_
  extern f_status_t f_utf_is_big_endian();
#endif // _di_f_utf_is_big_endian_

/**
 * Check to see if the entire byte block of the character is a non-ASCII UTF-8 character.
 *
 * This does not check the validity of the character, for that instead use f_utf_is_valid().
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_
  extern f_status_t f_utf_is(const f_string_t character, const f_array_length_t width_max);
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_false if not a UTF-8 alpha-numeric character.x
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_false if not a UTF-8 alpha-numeric character.x
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_combining_
  extern f_status_t f_utf_is_combining(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_combining_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_is_control_
  extern f_status_t f_utf_is_control(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_

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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 */
#ifndef _di_f_utf_is_fragment_
  extern f_status_t f_utf_is_fragment(const f_string_t character, const f_array_length_t width_max);
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a graph but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_punctuation_
  extern f_status_t f_utf_is_punctuation(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_punctuation_

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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_symbol_
  extern f_status_t f_utf_is_symbol(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_symbol_

/**
 * Check to see if the entire byte block of the character is a unassigned UTF-8 character.
 *
 * Unassigned as of Unicode version 13.0.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is inunassigned.
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
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a valid UTF-8 character.
 *   F_false if not a valid UTF-8 character.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_whitespace_other_
  extern f_status_t f_utf_is_whitespace_other(const f_string_t character, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_other_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-digit or an underscore '_'.
 *
 * This does not include zero-width punctuation.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 * This does not include zero-width punctuation.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
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
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_char_to_character_
  extern f_status_t f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_character_t *character_utf);
#endif // _di_f_utf_char_to_character_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_append_
  extern f_status_t f_utf_string_append(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_append_

/**
 * Append the source string onto the destination, but only if the string is not already at the end.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_append_assure_
  extern f_status_t f_utf_string_append_assure(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_append_assure_

/**
 * Append the source string onto the destination, but only if the string is not already at the end.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_append_assure_nulless_
  extern f_status_t f_utf_string_append_assure_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_append_nulless_
  extern f_status_t f_utf_string_append_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_append_nulless_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_append_
  extern f_status_t f_utf_string_dynamic_append(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_append_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_append_assure_
  extern f_status_t f_utf_string_dynamic_append_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_append_assure_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_append_assure_nulless_
  extern f_status_t f_utf_string_dynamic_append_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_append_nulless_
  extern f_status_t f_utf_string_dynamic_append_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_append_nulless_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_mash_
  extern f_status_t f_utf_string_dynamic_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_mash_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_mash_nulless_
  extern f_status_t f_utf_string_dynamic_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_mish_
  extern f_status_t f_utf_string_dynamic_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_mish_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_mish_nulless_
  extern f_status_t f_utf_string_dynamic_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_mish_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_append_
  extern f_status_t f_utf_string_dynamic_partial_append(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_append_

/**
 * Append the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_append_assure_
  extern f_status_t f_utf_string_dynamic_partial_append_assure(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_append_assure_

/**
 * Append the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_append_assure_nulless_
  extern f_status_t f_utf_string_dynamic_partial_append_assure_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_append_assure_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_append_nulless_
  extern f_status_t f_utf_string_dynamic_partial_append_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_append_nulless_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_mash_
  extern f_status_t f_utf_string_dynamic_partial_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_mash_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_mash_nulless_
  extern f_status_t f_utf_string_dynamic_partial_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_mish_
  extern f_status_t f_utf_string_dynamic_partial_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_mish_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_mish_nulless_
  extern f_status_t f_utf_string_dynamic_partial_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_mish_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_prepend_
  extern f_status_t f_utf_string_dynamic_partial_prepend(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_
  extern f_status_t f_utf_string_dynamic_partial_prepend_assure(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_prepend_assure_nulless_
  extern f_status_t f_utf_string_dynamic_partial_prepend_assure_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_partial_prepend_nulless_
  extern f_status_t f_utf_string_dynamic_partial_prepend_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_partial_prepend_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_prepend_
  extern f_status_t f_utf_string_dynamic_prepend(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_prepend_assure_
  extern f_status_t f_utf_string_dynamic_prepend_assure(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_prepend_assure_nulless_
  extern f_status_t f_utf_string_dynamic_prepend_assure_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_dynamic_prepend_nulless_
  extern f_status_t f_utf_string_dynamic_prepend_nulless(const f_utf_string_static_t source, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_prepend_nulless_

/**
 * Seek the buffer location forward until the UTF-8 character or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A UTF-8 character representing a character to seek to.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_eos if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_string_dynamic_seek_line_to_
  extern f_status_t f_utf_string_dynamic_seek_line_to(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const f_utf_character_t seek_to_this);
#endif // _di_f_utf_string_dynamic_seek_line_to_

/**
 * Seek the buffer location forward until the UTF-8 character is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A UTF-8 character representing a character to seek to.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_eos if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_string_dynamic_seek_to_
  extern f_status_t f_utf_string_dynamic_seek_to(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const f_utf_character_t seek_to_this);
#endif // _di_f_utf_string_dynamic_seek_to_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This is intended to be used for anything requiring NULL terminated strings.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 */
#ifndef _di_f_utf_string_dynamic_terminate_
  extern f_status_t f_utf_string_dynamic_terminate(f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_terminate_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This ensures that the terminating NULL not only exists but is not counted in destination.used.
 *
 * This is intended to be used for anything requiring NULL terminated strings whose used length cannot be counted.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 */
#ifndef _di_f_utf_string_dynamic_terminate_after_
  extern f_status_t f_utf_string_dynamic_terminate_after(f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_dynamic_terminate_after_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_mash_
  extern f_status_t f_utf_string_mash(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_mash_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_mash_nulless_
  extern f_status_t f_utf_string_mash_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_mish_
  extern f_status_t f_utf_string_mish(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_mish_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_mish_nulless_
  extern f_status_t f_utf_string_mish_nulless(const f_utf_string_t glue, const f_array_length_t glue_length, const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_mish_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_prepend_
  extern f_status_t f_utf_string_prepend(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_prepend_assure_
  extern f_status_t f_utf_string_prepend_assure(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when prepending.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_prepend_assure_nulless_
  extern f_status_t f_utf_string_prepend_assure_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when prepending.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_utf_string_prepend_nulless_
  extern f_status_t f_utf_string_prepend_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_f_utf_string_prepend_nulless_

/**
 * Seek the UTF-8 string location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_string_seek_line_to_
  extern f_status_t f_utf_string_seek_line_to(const f_utf_string_t string, f_utf_string_range_t *range, const f_utf_character_t seek_to_this);
#endif // _di_f_utf_string_seek_line_to_

/**
 * Seek the string location forward until the character (1-byte wide) is reached.
 *
 * @param string
 *   The sting to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A UTF-8 character representing a character to seek to.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_string_seek_to_
  extern f_status_t f_utf_string_seek_to(const f_utf_string_t string, f_utf_string_range_t *range, const f_utf_character_t seek_to_this);
#endif // _di_f_utf_string_seek_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h

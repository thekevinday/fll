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
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_buffer_decrement_
  extern f_return_status f_utf_buffer_decrement(const f_string_static buffer, f_string_range *range, const f_string_length step);
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
 *   F_incomplete_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_buffer_increment_
  extern f_return_status f_utf_buffer_increment(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_f_utf_buffer_increment_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character.
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
  extern f_return_status f_utf_character_is(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_alpha(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_alpha_digit(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_alpha_numeric(const f_utf_character character);
#endif // _di_f_utf_character_is_alpha_numeric_

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
  extern f_return_status f_utf_character_is_combining(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_control(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_control_picture(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_digit(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_emoji(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_fragment(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_graph(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_numeric(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_phonetic(const f_utf_character character);
#endif // _di_f_utf_character_is_phonetic_

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
  extern f_return_status f_utf_character_is_punctuation(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_symbol(const f_utf_character character);
#endif // _di_f_utf_character_is_symbol_

/**
 * Check to see if the entire byte block of the character is a valid UTF-8 character.
 *
 * This does validate if the UTF-8 character is a valid UTF-8 character.
 * To not do this, use f_utf_character_is().
 *
 * This function can be expensive due to how Unicode has invalid codes spread randomly through it.
 * For simpler error checking, try f_utf_is_fragment(), to just check that the width is valid or not.
 * (First characters should not have a width of 1, and all other characters should have a width of 1.)
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
  extern f_return_status f_utf_character_is_valid(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_whitespace(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_whitespace_modifier(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_whitespace_other(const f_utf_character character);
#endif // _di_f_utf_character_is_whitespace_other_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alpha-numeric or an underscore '_'.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 word character.
 *   F_false if not a UTF-8 word character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_word_
  extern f_return_status f_utf_character_is_word(const f_utf_character character);
#endif // _di_f_utf_character_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alpha-numeric, an underscore '_' or a dash '-'.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_word_dash_
  extern f_return_status f_utf_character_is_word_dash(const f_utf_character character);
#endif // _di_f_utf_character_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash character is alpha-numeric, an underscore '_', a dash '-', or a plus '+'.
 *
 * This does not include "invisible plus".
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_character_is_word_dash_plus_
  extern f_return_status f_utf_character_is_word_dash_plus(const f_utf_character character);
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
  extern f_return_status f_utf_character_is_zero_width(const f_utf_character character);
#endif // _di_f_utf_character_is_zero_width_

/**
 * Convert a specialized f_utf_character type to a int8_t, stored as a string (character buffer).
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
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *   F_failure (with error bit) if width is not long enough to convert.
 */
#ifndef _di_f_utf_character_to_char_
  extern f_return_status f_utf_character_to_char(const f_utf_character utf_character, f_string *character, f_string_length *width_max);
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
  extern f_return_status f_utf_is_big_endian();
#endif // _di_f_utf_is_big_endian_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character.
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_
  extern f_return_status f_utf_is(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalpha()
 */
#ifndef _di_f_utf_is_alpha_
  extern f_return_status f_utf_is_alpha(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_alpha_digit_
  extern f_return_status f_utf_is_alpha_digit(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_alpha_numeric_
  extern f_return_status f_utf_is_alpha_numeric(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_alpha_numeric_

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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_combining_
  extern f_return_status f_utf_is_combining(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_is_control_
  extern f_return_status f_utf_is_control(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_control_picture_
  extern f_return_status f_utf_is_control_picture(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_is_digit_
  extern f_return_status f_utf_is_digit(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_emoji_
  extern f_return_status f_utf_is_emoji(const f_string character, const f_string_length width_max);
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
  extern f_return_status f_utf_is_fragment(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a graph but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see isgraph()
 */
#ifndef _di_f_utf_is_graph_
  extern f_return_status f_utf_is_graph(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_is_numeric_
  extern f_return_status f_utf_is_numeric(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_phonetic_
  extern f_return_status f_utf_is_phonetic(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_phonetic_

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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_punctuation_
  extern f_return_status f_utf_is_punctuation(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 */
#ifndef _di_f_utf_is_symbol_
  extern f_return_status f_utf_is_symbol(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_symbol_

/**
 * Check to see if the entire byte block of the character is a UTF-8 character and if that character is a valid UTF-8.
 *
 * This does check the validity of the character, to not do this use f_utf_is().
 *
 * This function can be expensive due to how Unicode has invalid codes spread randomly through it.
 * For simpler error checking, try f_utf_is_fragment(), to just check that the width is valid or not.
 * (First characters should have a width of not 1, and all other characters should not have a width of 1.)
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_valid_
  extern f_return_status f_utf_is_valid(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see isspace()
 */
#ifndef _di_f_utf_is_whitespace_
  extern f_return_status f_utf_is_whitespace(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_whitespace_modifier_
  extern f_return_status f_utf_is_whitespace_modifier(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_whitespace_other_
  extern f_return_status f_utf_is_whitespace_other(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_whitespace_other_

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
 *
 * @return
 *   F_true if a UTF-8 word character.
 *   F_false if not a UTF-8 word character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_
  extern f_return_status f_utf_is_word(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alpha-digit, an underscore '_' or a dash '-'.
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_dash_
  extern f_return_status f_utf_is_word_dash(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash character is alpha-digit, an underscore '_', a dash '-', or a plus '+'.
 *
 * This does not include "invisible plus".
 *
 * @param character
 *   The character to validate.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 word or dash character.
 *   F_false if not a UTF-8 word or dash character.
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_dash_plus_
  extern f_return_status f_utf_is_word_dash_plus(const f_string character, const f_string_length width_max);
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
 *   F_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if this could be a whitespace but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_is_zero_width_
  extern f_return_status f_utf_is_zero_width(const f_string character, const f_string_length width_max);
#endif // _di_f_utf_is_zero_width_

/**
 * Convert an ASCII or UTF-8 character, stored as a string (character buffer), to the specialized f_utf_character type.
 *
 * @param character
 *   The character string to be converted to the f_utf_character type.
 *   There must be enough space allocated to convert against, as limited by width_max.
 * @param width_max
 *   The maximum width available for converting.
 *   Can be anything greater than 0.
 * @param character_utf
 *   The generated character of type f_utf_character.
 *   This value may be cleared, even on error.
 *
 * @return
 *   F_none if conversion was successful.
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 */
#ifndef _di_f_utf_char_to_character_
  extern f_return_status f_utf_char_to_character(const f_string character, const f_string_length width_max, f_utf_character *character_utf);
#endif // _di_f_utf_char_to_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h

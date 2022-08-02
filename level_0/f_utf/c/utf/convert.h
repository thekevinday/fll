/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgplv2.1
 *
 * Defines UTF-8 "convert" functions.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _F_utf_convert_h
#define _F_utf_convert_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a specialized f_utf_char_t type to a uint8_t, stored as a string (character buffer).
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
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_char_to_char_
  extern f_status_t f_utf_char_to_char(const f_utf_char_t utf_character, f_string_t *character, f_array_length_t *width_max);
#endif // _di_f_utf_char_to_char_

/**
 * Convert a given (UTF-8) character into Unicode.
 *
 * The f_utf_char_t is a 32-bit integer containing UTF-8 sequences, unchanged.
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
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_valid()
 */
#ifndef _di_f_utf_character_unicode_to_
  extern f_status_t f_utf_character_unicode_to(const f_utf_char_t character, uint32_t *unicode);
#endif // _di_f_utf_character_unicode_to_

/**
 * Convert a given Unicode into (UTF-8) character.
 *
 * The f_utf_char_t is a 32-bit integer containing UTF-8 sequences, unchanged.
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
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_character_unicode_from_
  extern f_status_t f_utf_character_unicode_from(const uint32_t unicode, f_utf_char_t *character);
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
 * @param codepoint
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
  extern f_status_t f_utf_character_unicode_string_to(const f_utf_string_t string, const f_array_length_t length, f_utf_char_t *codepoint);
#endif // _di_f_utf_character_unicode_string_to_

/**
 * Convert an ASCII or UTF-8 character, stored as a string (character buffer), to the specialized f_utf_char_t type.
 *
 * @param character
 *   The character string to be converted to the f_utf_char_t type.
 *   There must be enough space allocated to convert against, as limited by width_max.
 * @param width_max
 *   The maximum width available for converting.
 *   Can be anything greater than 0.
 * @param character_utf
 *   The generated character of type f_utf_char_t.
 *   This value may be cleared, even on error.
 *
 * @return
 *   F_none if conversion was successful.
 *
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_char_to_character_
  extern f_status_t f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_char_t *character_utf);
#endif // _di_f_utf_char_to_character_

/**
 * Convert a given Unicode into a string block representing a single character.
 *
 * @param unicode
 *   A 32-bit integer representing the Unicode (such as U+0001).
 *   Does not need to be interpretted like UTF-8, this is a number from 0 onto max supported Unicode integer value (U+10FFFF).
 * @param width_max
 *   The max width available for representing the UTF-8 character.
 *   There must be enough space in the character buffer to handle the Unicode width.
 *   It is recommended to always have 4 characters (4 uint8_t) of space available in character.
 * @param character
 *   The (UTF-8) character as a sequence of bytes.
 *   This must have a length equal to the width (up to 4 characters) to be safely used.
 *   The caller is expected to ensure this.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_unicode_from_
  extern f_status_t f_utf_unicode_from(const uint32_t unicode, const f_array_length_t width_max, f_string_t *character);
#endif // _di_f_utf_unicode_from_

/**
 * Convert a given string block representing a single character into Unicode.
 *
 * @param character
 *   The (UTF-8) character to convert to the Unicode representation.
 *   The f_utf_char_t is a 32-bit integer containing UTF-8 sequences, unchanged.
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
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
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

#endif // _F_utf_is_h

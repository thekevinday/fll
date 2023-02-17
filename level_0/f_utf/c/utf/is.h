/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgplv2.1
 *
 * Defines UTF-8 "is" functions.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _F_utf_is_h
#define _F_utf_is_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to see if the entire byte block of the character is a non-ASCII UTF-8 character.
 *
 * This does not check the validity of the character, for that instead use f_utf_is_valid().
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 */
#ifndef _di_f_utf_is_
  extern f_status_t f_utf_is(const f_string_t sequence);
#endif // _di_f_utf_is_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alphabet character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isalpha()
 */
#ifndef _di_f_utf_is_alphabetic_
  extern f_status_t f_utf_is_alphabetic(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_alphabetic_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabet or digit character.
 *
 * Digit characters are digit of any base, such as decimal (base-10) or hexidecimal (base-16).
 *
 * This does not include fractions such as 1/2 (½) (U+00BD).
 *
 * This also processes large values such as Roman Numerals.
 * Roman Numerals, however, conflict with traditional alphabetic characters.
 * To avoid this only Unicode Roman Numerals found in range U+2160 to U+2188 are treated as their respective digits.
 * For example, the Roman Numeral 'Ⅿ' (U+216F) represents 1000 rather than having 'M' (U+004D) representing 1000.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 * @param value
 *   (optional) The integer representation of the sequence if the sequence represents a decimal of any base type.
 *   Set to NULL to not use.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alpha-numeric character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isalpha()
 * @see isdigit()
 */
#ifndef _di_f_utf_is_alphabetic_digit_
  extern f_status_t f_utf_is_alphabetic_digit(const f_string_t sequence, const f_array_length_t width_max, uint64_t * const value);
#endif // _di_f_utf_is_alphabetic_digit_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 alphabetic or numeric character.
 *
 * Numeric characters are decimal digits, letter numbers, and number-like, such as 1/2 (½) (U+00BD) or superscript 2 (²) (U+00B2).
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 alphabet character.
 *   F_false if not a UTF-8 alpha-numeric character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_alphabetic_numeric_
  extern f_status_t f_utf_is_alphabetic_numeric(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_alphabetic_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if an ASCII character.
 *   F_false if not an ASCII character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_ascii_
  extern f_status_t f_utf_is_ascii(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_ascii_

/**
 * Check to see if the entire byte block of the character is a UTF-8 combining character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 combining character.
 *   F_false if not a UTF-8 combining character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_combining_
  extern f_status_t f_utf_is_combining(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_combining_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 control character.
 *
 * This includes control code and control format characters.
 *
 * The control codes U+0009..U+000D and U+0085 are considered white space and line breaking.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see iscntrl()
 */
#ifndef _di_f_utf_is_control_
  extern f_status_t f_utf_is_control(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control code character.
 *
 * Control Code characters are the traditional control characters, such as "\n" as well as some newer Unicode ones.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control code character.
 *   F_false if not a UTF-8 control code character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_control_code_
  extern f_status_t f_utf_is_control_code(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_code_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control format character.
 *
 * Control Format characters are special characters used for formatting.
 * These are considered control characters.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control format character.
 *   F_false if not a UTF-8 control format character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_control_format_
  extern f_status_t f_utf_is_control_format(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_format_

/**
 * Check to see if the entire byte block of the character is a UTF-8 control picture character.
 *
 * Control Picture characters are placeholders for special ASCII characters and therefore there are no ASCII Control Picture characters.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_control_picture_
  extern f_status_t f_utf_is_control_picture(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_control_picture_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 decimal character.
 *
 * Digit characters are digit of any base, such as decimal (base-10) or hexidecimal (base-16).
 *
 * This does not include fractions such as 1/2 (½) (U+00BD).
 *
 * This also processes large values such as Roman Numerals.
 * Roman Numerals, however, conflict with traditional alphabetic characters.
 * To avoid this only Unicode Roman Numerals found in range U+2160 to U+2188 are treated as their respective digits.
 * For example, the Roman Numeral 'Ⅿ' (U+216F) represents 1000 rather than having 'M' (U+004D) representing 1000.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 * @param value
 *   (optional) The integer representation of the sequence if the sequence represents a decimal of any base type.
 *   Set to NULL to not use.
 *
 * @return
 *   F_true if a UTF-8 digit character.
 *   F_false if not a UTF-8 digit character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_is_digit_
  extern f_status_t f_utf_is_digit(const f_string_t sequence, const f_array_length_t width_max, uint64_t * const value);
#endif // _di_f_utf_is_digit_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 emoji character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 emoji character.
 *   F_false if not a UTF-8 emoji character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_emoji_
  extern f_status_t f_utf_is_emoji(const f_string_t sequence, const f_array_length_t width_max);
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
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 */
#ifndef _di_f_utf_is_fragment_
  extern f_status_t f_utf_is_fragment(const f_string_t sequence);
#endif // _di_f_utf_is_fragment_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 printable character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 graph.
 *   F_false if not a UTF-8 graph.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_maybe (with error bit) if this could be a graph but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isgraph()
 */
#ifndef _di_f_utf_is_graph_
  extern f_status_t f_utf_is_graph(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_graph_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 numeric character.
 *
 * Numeric characters are decimal digits, letter numbers, and number-like, such as 1/2 (½) or superscript 2 (²).
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 numeric character.
 *   F_false if not a UTF-8 numeric character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isdigit()
 */
#ifndef _di_f_utf_is_numeric_
  extern f_status_t f_utf_is_numeric(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_numeric_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 phonetic character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 phonetic character.
 *   F_false if not a UTF-8 phonetic character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_phonetic_
  extern f_status_t f_utf_is_phonetic(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_phonetic_

/**
 * Check to see if the entire byte block of the character is a UTF-8 private character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 punctuation character.
 *   F_false if not a UTF-8 punctuation character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_private_
  extern f_status_t f_utf_is_private(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_private_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 punctuation character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 punctuation character.
 *   F_false if not a UTF-8 punctuation character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_punctuation_
  extern f_status_t f_utf_is_punctuation(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_punctuation_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 subscript character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 subscript character.
 *   F_false if not a UTF-8 subscript character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_subscript_
  extern f_status_t f_utf_is_subscript(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_subscript_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 superscript character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 superscript character.
 *   F_false if not a UTF-8 superscript character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_superscript_
  extern f_status_t f_utf_is_superscript(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_superscript_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 symbol character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 symbol character.
 *   F_false if not a UTF-8 symbol character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_symbol_
  extern f_status_t f_utf_is_symbol(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_symbol_

/**
 * Check to see if the entire byte block of the character is a unassigned UTF-8 character.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if an unassigned UTF-8 character.
 *   F_false if not an unassigned UTF-8 character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_parameter (with error bit) if a parameter is unassigned.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_unassigned_
  extern f_status_t f_utf_is_unassigned(const f_string_t sequence, const f_array_length_t width_max);
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
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a valid UTF-8 character or is an ASCII character.
 *   F_false if not a valid UTF-8 character.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 */
#ifndef _di_f_utf_is_valid_
  extern f_status_t f_utf_is_valid(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_valid_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general space character.
 *
 * Non-printing or zero-width characters are not considered white space.
 * This does include line separators like '\n' (U+000A).
 * This does not include phonetic spaces, like white space modifiers.
 * This does not include non-true white space characters, such as Ogham Space Mark ' ' (U+1680).
 *
 * Phonetic spaces are white spaces with additional phonetic meaning associated with them.
 * However, because they are not renderred as white space, they are technically not white space.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-white space characters that are treated as white space by Unicode are not treated as white space.
 *
 * @return
 *   F_true if a UTF-8 white space.
 *   F_false if not a UTF-8 white space.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_maybe (with error bit) if this could be a white space but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isspace()
 */
#ifndef _di_f_utf_is_whitespace_
  extern f_status_t f_utf_is_whitespace(const f_string_t sequence, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_whitespace_

/**
 * Check to see if the entire byte block of the character is a UTF-8 white space modifier character.
 *
 * These are phonetic spaces.
 *
 * Phonetic spaces are whitespaces with additional phonetic meaning associated with them.
 * Therefore, these are valid spaces in the technical sense, even if they are not visibly white space.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 (modifier) white space.
 *   F_false if not a UTF-8 (modifier) white space.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_maybe (with error bit) if this could be a white space but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_whitespace_modifier_
  extern f_status_t f_utf_is_whitespace_modifier(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_modifier_

/**
 * Check to see if the entire byte block of the character is an other type of UTF-8 space character.
 *
 * This is a list of white space that are not actual white space (because they are graph characters) but are considered white space, such as Ogham Space Mark ' ' (U+1680).
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 (other) white space.
 *   F_false if not a UTF-8 (other) white space.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_maybe (with error bit) if this could be a white space but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_whitespace_other_
  extern f_status_t f_utf_is_whitespace_other(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_other_

/**
 * Check to see if the entire byte block of the character is an other type of UTF-8 space character.
 *
 * This is a list of white space that are actually zero-width space (which is not a space), such as Zero-Width Space (U+200B).
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 (zero-width) white space.
 *   F_false if not a UTF-8 (zero-width) white space.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_maybe (with error bit) if this could be a white space but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_whitespace_zero_width_
  extern f_status_t f_utf_is_whitespace_zero_width(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_whitespace_zero_width_

/**
 * Get whether or not the UTF-8 character is a wide character on display.
 *
 * This is not the wide as in width in bytes that the codepoint takes up in UTF-8.
 * Instead, this is the width in characters on the screen the character takes up.
 * When "wide" characters that take up either 2 characters on render.
 * When "narrow" characters that take up either 1 character on render.
 *
 * @param sequence
 *   The (UTF-8) character.
 * @param width_max
 *   The max width available for representing the UTF-8 character.
 *   There must be enough space in the character buffer to handle the Unicode width.
 *   It is recommended to always have 4 characters (4 uint8_t) of space available in character.
 *   This is the width in bytes the codepoint takes up in UTF-8.
 *
 * @return
 *   F_none on success.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_wide_
  extern f_status_t f_utf_is_wide(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_wide_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word character.
 *
 * A word character is alphabetic-decimal or an underscore '_'.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
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
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_
  extern f_status_t f_utf_is_word(const f_string_t sequence, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_word_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word or dash character.
 *
 * A word dash character is alphabetic-decimal, an underscore '_' or a dash '-'.
 *
 * Unicode appears to refer to dashes that connect words as a hyphen.
 * Therefore, only these hyphens are considered dashes for the purposes of this function.
 * All other dash-like Unicode characters are not considered a dash here.
 * The dash here is intended for combining words, which matches the context of the Unicode "hyphen".
 *
 * @param sequence
 *   The byte sequence to validate as a character.
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
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_dash_
  extern f_status_t f_utf_is_word_dash(const f_string_t sequence, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_word_dash_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 word, dash, or plus character.
 *
 * A word dash plus character is alphabetic-decimal, an underscore '_', a dash '-', or a plus '+'.
 *
 * Unicode appears to refer to dashes that connect words as a hyphen.
 * Therefore, only these hyphens are considered dashes for the purposes of this function.
 * All other dash-like Unicode characters are not considered a dash here.
 * The dash here is intended for combining words, which matches the context of the Unicode "hyphen".
 *
 * This does not include zero-width punctuation, such as "invisible plus" (U+2064) (even in strict mode).
 *
 * @param sequence
 *   The byte sequence to validate as a character.
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
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 *
 * @see isalnum()
 */
#ifndef _di_f_utf_is_word_dash_plus_
  extern f_status_t f_utf_is_word_dash_plus(const f_string_t sequence, const f_array_length_t width_max, const bool strict);
#endif // _di_f_utf_is_word_dash_plus_

/**
 * Check to see if the entire byte block of the character is an ASCII or UTF-8 general non-printing character.
 *
 * Only characters that do not print, which are generally called zero-width.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *   There must be enough space allocated to compare against, as limited by width_max.
 * @param width_max
 *   The maximum width available for checking.
 *   Can be anything greater than 0.
 *
 * @return
 *   F_true if a UTF-8 white space.
 *   F_false if not a UTF-8 white space.
 *   F_data_not if width_max is less than 1.
 *
 *   F_complete_not_utf (with error bit set) if character is an incomplete UTF-8 sequence.
 *   F_maybe (with error bit) if this could be a white space but width is not long enough.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if Unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_is_zero_width_
  extern f_status_t f_utf_is_zero_width(const f_string_t sequence, const f_array_length_t width_max);
#endif // _di_f_utf_is_zero_width_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_is_h

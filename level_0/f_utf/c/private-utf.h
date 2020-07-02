/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 capabilities.
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_utf_h
#define _PRIVATE_F_utf_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_alpha().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_alpha()
 * @see f_utf_is_alpha()
 */
#if !defined(_di_f_utf_character_is_alpha_) || !defined(_di_f_utf_is_alpha_)
  extern f_return_status private_f_utf_character_is_alpha(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_alpha_) || !defined(_di_f_utf_is_alpha_)

/**
 * Private implementation of f_utf_character_is_alpha_digit().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_alpha_digit()
 * @see f_utf_is_alpha_digit()
 */
#if !defined(_di_f_utf_character_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_digit_)
  extern f_return_status private_f_utf_character_is_alpha_digit(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_digit_)

/**
 * Private implementation of f_utf_character_is_alpha_numeric().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_alpha_numeric()
 * @see f_utf_is_alpha_numeric()
 */
#if !defined(_di_f_utf_character_is_alpha_numeric_) || !defined(_di_f_utf_is_alpha_numeric_)
  extern f_return_status private_f_utf_character_is_alpha_numeric(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_alpha_numeric_) || !defined(_di_f_utf_is_alpha_numeric_)

/**
 * Private implementation of f_utf_character_is_combining().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_is_combining()
 */
#if !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)
  extern f_return_status private_f_utf_character_is_combining(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)

/**
 * Private implementation of f_utf_character_is_control().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_control()
 * @see f_utf_is_control()
 */
#if !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)
  extern f_return_status private_f_utf_character_is_control(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)

/**
 * Private implementation of f_utf_character_is_control_picture().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_control_picture()
 * @see f_utf_is_control_picture()
 */
#if !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)
  extern f_return_status private_f_utf_character_is_control_picture(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)

/**
 * Private implementation of f_utf_character_is_digit().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_digit()
 * @see f_utf_is_digit()
 */
#if !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)
  extern f_return_status private_f_utf_character_is_digit(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)

/**
 * Private implementation of f_utf_character_is_emoji().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_emoji()
 * @see f_utf_is_emoji()
 */
#if !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)
  extern f_return_status private_f_utf_character_is_emoji(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)

/**
 * Private implementation of f_utf_character_is_numeric().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_numeric()
 * @see f_utf_is_numeric()
 */
#if !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)
  extern f_return_status private_f_utf_character_is_numeric(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)

/**
 * Private implementation of f_utf_character_is_phonetic().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_phonetic()
 * @see f_utf_is_phonetic()
 */
#if !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)
  extern f_return_status private_f_utf_character_is_phonetic(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)

/**
 * Private implementation of f_utf_character_is_punctuation().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_punctuation()
 * @see f_utf_is_punctuation()
 */
#if !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_is_punctuation_)
  extern f_return_status private_f_utf_character_is_punctuation(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_is_punctuation_)

/**
 * Private implementation of f_utf_character_is_symbol().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_symbol()
 * @see f_utf_is_symbol()
 */
#if !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)
  extern f_return_status private_f_utf_character_is_symbol(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)

/**
 * Private implementation of f_utf_character_is_valid().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 character.
 *   F_false if not a UTF-8 character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_valid()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)
  extern f_return_status private_f_utf_character_is_valid(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)

/**
 * Private implementation of f_utf_character_is_whitespace().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_whitespace()
 * @see f_utf_is_whitespace()
 */
#if !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)
  extern f_return_status private_f_utf_character_is_whitespace(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)

/**
 * Private implementation of f_utf_character_is_whitespace_modifier().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 phonetic whitespace.
 *   F_false if not a UTF-8 phonetic whitespace.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_whitespace_modifier()
 * @see f_utf_is_whitespace_modifier()
 */
#if !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)
  extern f_return_status private_f_utf_character_is_whitespace_modifier(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)

/**
 * Private implementation of f_utf_character_is_whitespace_other().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 whitespace.
 *   F_false if not a UTF-8 whitespace.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_whitespace_other()
 * @see f_utf_is_whitespace_other()
 */
#if !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)
  extern f_return_status private_f_utf_character_is_whitespace_other(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)

/**
 * Private implementation of f_utf_character_is_word().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_word()
 * @see f_utf_is_word()
 */
#if !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)
  extern f_return_status private_f_utf_character_is_word(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)

/**
 * Private implementation of f_utf_character_is_word_dash().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_word_dash()
 * @see f_utf_is_word_dash()
 */
#if !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)
  extern f_return_status private_f_utf_character_is_word_dash(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)

/**
 * Private implementation of f_utf_character_is_word_dash_plus().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_word_dash()
 * @see f_utf_is_word_dash()
 */
#if !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)
  extern f_return_status private_f_utf_character_is_word_dash_plus(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)

/**
 * Private implementation of f_utf_character_is_zero_width().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param width
 *   The number of bytes repesenting the character width.
 *
 * @return
 *   F_true if a UTF-8 non-printing or zero-width character.
 *   F_false if not a UTF-8 non-printing or zero-width character.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 * @see f_utf_character_is_zero_width()
 * @see f_utf_is_zero_width()
 */
#if !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)
  extern f_return_status private_f_utf_character_is_zero_width(const f_utf_character character, const uint8_t width) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_h

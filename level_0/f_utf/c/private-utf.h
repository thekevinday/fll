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
 * Private implementation of f_utf_char_to_character().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *   F_failure (with error bit) if width_max is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_char_to_character()
 * @see f_utf_character_is_valid()
 * @see f_utf_is_valid()
 * @see f_utf_is_alpha()
 * @see f_utf_is_alpha_digit()
 * @see f_utf_is_alpha_numeric()
 * @see f_utf_is_ascii()
 * @see f_utf_is_combining_  _di_f_utf_is_control()
 * @see f_utf_is_control_picture()
 * @see f_utf_is_digit()
 * @see f_utf_is_emoji()
 * @see f_utf_is_graph()
 * @see f_utf_is_numeric()
 * @see f_utf_is_phonetic()
 * @see f_utf_is_private()
 * @see f_utf_is_punctuation()
 * @see f_utf_is_symbol()
 * @see f_utf_is_unassigned()
 * @see f_utf_is_valid()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_whitespace_modifier()
 * @see f_utf_is_whitespace_other()
 * @see f_utf_is_wide()
 * @see f_utf_is_word()
 * @see f_utf_is_word_dash()
 * @see f_utf_is_word_dash_plus()
 * @see f_utf_is_zero_width()
 * @see f_utf_unicode_to()
 */
#if !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alpha_) || !defined(_di_f_utf_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)
  extern f_status_t private_f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_character_t *character_utf) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alpha_) || !defined(_di_f_utf_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)

/**
 * Private implementation of f_utf_character_is_alpha().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_alpha()
 * @see f_utf_is_alpha()
 */
#if !defined(_di_f_utf_character_is_alpha_) || !defined(_di_f_utf_is_alpha_)
  extern f_status_t private_f_utf_character_is_alpha(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alpha_) || !defined(_di_f_utf_is_alpha_)

/**
 * Private implementation of f_utf_character_is_alpha_digit().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_alpha_digit()
 * @see f_utf_is_alpha_digit()
 */
#if !defined(_di_f_utf_character_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_digit_)
  extern f_status_t private_f_utf_character_is_alpha_digit(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alpha_digit_) || !defined(_di_f_utf_is_alpha_digit_)

/**
 * Private implementation of f_utf_character_is_alpha_numeric().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_alpha_numeric()
 * @see f_utf_is_alpha_numeric()
 */
#if !defined(_di_f_utf_character_is_alpha_numeric_) || !defined(_di_f_utf_is_alpha_numeric_)
  extern f_status_t private_f_utf_character_is_alpha_numeric(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alpha_numeric_) || !defined(_di_f_utf_is_alpha_numeric_)

/**
 * Private implementation of f_utf_character_is_ascii().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *
 * @see f_utf_character_is_ascii()
 * @see f_utf_is_ascii()
 */
#if !defined(_di_f_utf_character_is_ascii_) || !defined(_di_f_utf_is_ascii_)
  extern f_status_t private_f_utf_character_is_ascii(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_ascii_) || !defined(_di_f_utf_is_ascii_)

/**
 * Private implementation of f_utf_character_is_combining().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_is_combining()
 */
#if !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)
  extern f_status_t private_f_utf_character_is_combining(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_combining_) || !defined(_di_f_utf_is_combining_)

/**
 * Private implementation of f_utf_character_is_control().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_control()
 * @see f_utf_is_control()
 */
#if !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)
  extern f_status_t private_f_utf_character_is_control(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)

/**
 * Private implementation of f_utf_character_is_control_code().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_control_code()
 * @see f_utf_is_control_code()
 */
#if !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_control_code_)
  extern f_status_t private_f_utf_character_is_control_code(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_control_code_)

/**
 * Private implementation of f_utf_character_is_control_format().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_control_format()
 * @see f_utf_is_control_format()
 */
#if !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)
  extern f_status_t private_f_utf_character_is_control_format(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)

/**
 * Private implementation of f_utf_character_is_control_picture().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *
 * @see f_utf_character_is_control_picture()
 * @see f_utf_is_control_picture()
 */
#if !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)
  extern f_status_t private_f_utf_character_is_control_picture(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)

/**
 * Private implementation of f_utf_character_is_digit().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_digit()
 * @see f_utf_is_digit()
 */
#if !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)
  extern f_status_t private_f_utf_character_is_digit(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_digit_) || !defined(_di_f_utf_is_digit_)

/**
 * Private implementation of f_utf_character_is_emoji().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_emoji()
 * @see f_utf_is_emoji()
 */
#if !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)
  extern f_status_t private_f_utf_character_is_emoji(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_emoji_) || !defined(_di_f_utf_is_emoji_)

/**
 * Private implementation of f_utf_character_is_numeric().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_numeric()
 * @see f_utf_is_numeric()
 */
#if !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)
  extern f_status_t private_f_utf_character_is_numeric(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_numeric_) || !defined(_di_f_utf_is_numeric_)

/**
 * Private implementation of f_utf_character_is_phonetic().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_phonetic()
 * @see f_utf_is_phonetic()
 */
#if !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)
  extern f_status_t private_f_utf_character_is_phonetic(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_phonetic_) || !defined(_di_f_utf_is_phonetic_)

/**
 * Private implementation of f_utf_character_is_private().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_private()
 * @see f_utf_is_private()
 */
#if !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)
  extern f_status_t private_f_utf_character_is_private(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_private_) || !defined(_di_f_utf_is_private_)

/**
 * Private implementation of f_utf_character_is_punctuation().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_punctuation()
 * @see f_utf_is_punctuation()
 */
#if !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_is_punctuation_)
  extern f_status_t private_f_utf_character_is_punctuation(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_punctuation_) || !defined(_di_f_utf_is_punctuation_)

/**
 * Private implementation of f_utf_character_is_symbol().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_symbol()
 * @see f_utf_is_symbol()
 */
#if !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)
  extern f_status_t private_f_utf_character_is_symbol(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_symbol_) || !defined(_di_f_utf_is_symbol_)

/**
 * Private implementation of f_utf_character_is_unassigned().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_unassigned()
 * @see f_utf_is_unassigned()
 */
#if !defined(_di_f_utf_character_is_unassigned_) || !defined(_di_f_utf_is_unassigned_)
  extern f_status_t private_f_utf_character_is_unassigned(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_unassigned_) || !defined(_di_f_utf_is_unassigned_)

/**
 * Private implementation of f_utf_character_is_valid().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_valid()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)
  extern f_status_t private_f_utf_character_is_valid(const f_utf_character_t characterh) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_valid_) || !defined(_di_f_utf_is_valid_)

/**
 * Private implementation of f_utf_character_is_whitespace().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_whitespace()
 * @see f_utf_is_whitespace()
 */
#if !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)
  extern f_status_t private_f_utf_character_is_whitespace(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)

/**
 * Private implementation of f_utf_character_is_whitespace_modifier().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 phonetic whitespace.
 *   F_false if not a UTF-8 phonetic whitespace.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_whitespace_modifier()
 * @see f_utf_is_whitespace_modifier()
 */
#if !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)
  extern f_status_t private_f_utf_character_is_whitespace_modifier(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)

/**
 * Private implementation of f_utf_character_is_whitespace_other().
 *
 * Intended to be shared to each of the different implementation variations.
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
 * @see f_utf_character_is_whitespace_other()
 * @see f_utf_is_whitespace_other()
 */
#if !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)
  extern f_status_t private_f_utf_character_is_whitespace_other(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)

/**
 * Private implementation of f_utf_character_is_wide().
 *
 * Intended to be shared to each of the different implementation variations.
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
#if !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)
  extern f_status_t private_f_utf_character_is_wide(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_wide_) || !defined(_di_f_utf_is_wide_)

/**
 * Private implementation of f_utf_character_is_word().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_word()
 * @see f_utf_is_word()
 */
#if !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)
  extern f_status_t private_f_utf_character_is_word(const f_utf_character_t character, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_is_word_)

/**
 * Private implementation of f_utf_character_is_word_dash().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_word_dash()
 * @see f_utf_is_word_dash()
 */
#if !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)
  extern f_status_t private_f_utf_character_is_word_dash(const f_utf_character_t character, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_is_word_dash_)

/**
 * Private implementation of f_utf_character_is_word_dash_plus().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to validate.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf (with error bit) if unicode is an invalid Unicode character.
 *   F_utf_fragment (with error bit) if character is an incomplete UTF-8 fragment.
 *
 * @see f_utf_character_is_word_dash_plus()
 * @see f_utf_is_word_dash_plus()
 */
#if !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)
  extern f_status_t private_f_utf_character_is_word_dash_plus(const f_utf_character_t character, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)

/**
 * Private implementation of f_utf_character_is_zero_width().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *
 * @see f_utf_character_is_zero_width()
 * @see f_utf_is_zero_width()
 */
#if !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)
  extern f_status_t private_f_utf_character_is_zero_width(const f_utf_character_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_h

/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
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
 * @param sequence
 *   The character string to be converted to the f_utf_char_t type.
 *   There must be enough space allocated to convert against, as limited by width_max.
 * @param width_max
 *   The maximum width available for converting.
 *   Can be anything greater than 0.
 * @param sequence_utf
 *   The generated character of type f_utf_char_t.
 *   This value may be cleared, even on error.
 *
 * @return
 *   F_none if conversion was successful.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 sequence.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if codepoint is an invalid Unicode character.
 *
 * @see f_utf_char_to_character()
 * @see f_utf_character_is_valid()
 * @see f_utf_is_valid()
 * @see f_utf_is_alphabetic()
 * @see f_utf_is_alphabetic_decimal()
 * @see f_utf_is_alphabetic_numeric()
 * @see f_utf_is_ascii()
 * @see f_utf_is_combining()
 * @see f_utf_is_control()
 * @see f_utf_is_control_picture()
 * @see f_utf_is_decimal()
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
#if !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_decimal_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)
  extern f_status_t private_f_utf_char_to_character(const f_string_t character, const f_array_length_t width_max, f_utf_char_t *character_utf) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_char_to_character_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_decimal_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_ascii_) || !defined(_di_f_utf_is_combining_) || !defined(_di_f_utf_is_control_) || !defined(_di_f_utf_is_control_picture_) || !defined(_di_f_utf_is_decimal_) || !defined(_di_f_utf_is_digit_) || !defined(_di_f_utf_is_emoji_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_numeric_) || !defined(_di_f_utf_is_phonetic_) || !defined(_di_f_utf_is_private_) || !defined(_di_f_utf_is_punctuation_) || !defined(_di_f_utf_is_symbol_) || !defined(_di_f_utf_is_unassigned_) || !defined(_di_f_utf_is_valid_) || !defined(_di_f_utf_is_whitespace_) || !defined(_di_f_utf_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_other_) || !defined(_di_f_utf_is_wide_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_) || !defined(f_utf_unicode_to)

/**
 * Private implementation of f_utf_character_is_zero_width().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param sequence
 *   The (UTF-8) character to convert to the Unicode representation.
 *   The f_utf_char_t is a 32-bit integer containing UTF-8 sequences, unchanged.
 * @param codepoint
 *   A 32-bit integer representing the Unicode (such as U+0001).
 *   Does not need to be interpretted like UTF-8, this is a number from 0 onto max supported Unicode integer value (U+10FFFF).
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) if width is not long enough to convert.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if codepoint is an invalid Unicode character.
 *
 * @see f_utf_character_unicode_to()
 * @see f_utf_unicode_to()
 */
#if !defined(_di_f_utf_character_unicode_to_) || !defined(_di_f_utf_unicode_to_)
  extern f_status_t private_f_utf_character_unicode_to(const f_utf_char_t sequence, uint32_t *codepoint) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_unicode_to_) || !defined(_di_f_utf_unicode_to_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_h

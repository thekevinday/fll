/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides UTF-8 capabilities.
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_utf_zero_width_h
#define _PRIVATE_F_utf_zero_width_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_zero_width().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 non-printing or zero-width character.
 *   F_false if not a UTF-8 non-printing or zero-width character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alphabetic()
 * @see f_utf_character_is_alphabetic_numeric()
 * @see f_utf_character_is_alphabetic_digit()
 * @see f_utf_character_is_graph()
 * @see f_utf_character_is_word()
 * @see f_utf_character_is_word_dash()
 * @see f_utf_character_is_word_dash_plus()
 * @see f_utf_character_is_zero_width()
 * @see f_utf_is_alphabetic()
 * @see f_utf_is_alphabetic_digit()
 * @see f_utf_is_alphabetic_numeric()
 * @see f_utf_is_graph()
 * @see f_utf_is_word()
 * @see f_utf_is_word_dash()
 * @see f_utf_is_word_dash_plus()
 * @see f_utf_is_zero_width_
 */
#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_graph_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_)
  extern f_status_t private_f_utf_character_is_zero_width(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_graph_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_character_is_zero_width_) || !defined(_di_f_utf_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabetic_numeric_) || !defined(_di_f_utf_is_graph_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_) || !defined(_di_f_utf_is_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_zero_width_h

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
#ifndef _PRIVATE_F_utf_alphabetic_h
#define _PRIVATE_F_utf_alphabetic_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_alphabetic().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 alphabetic character.
 *   F_false if not a UTF-8 alphabetic character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alphabetic()
 * @see f_utf_is_alphabetic()
 */
#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_)
  extern f_status_t private_f_utf_character_is_alphabetic(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_is_alphabetic_)

/**
 * Private implementation of f_utf_character_is_alphabetic_digit().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 * @param value
 *   (optional) The integer representation of the sequence if the sequence represents a decimal of any base type.
 *   Set to NULL to not use.
 *
 * @return
 *   F_true if a UTF-8 alphabetic or a digit character.
 *   F_false if not a UTF-8 alphabetic nor a digit character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alphabetic_digit()
 * @see f_utf_character_is_word()
 * @see f_utf_character_is_word_dash()
 * @see f_utf_character_is_word_dash_plus()
 * @see f_utf_is_alphabetic_digit()
 * @see f_utf_is_word()
 * @see f_utf_is_word_dash()
 * @see f_utf_is_word_dash_plus_()
 */
#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

  extern f_status_t private_f_utf_character_is_alphabetic_digit(const f_utf_char_t sequence, uint64_t * const value) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_alphabetic_digit_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

/**
 * Private implementation of f_utf_character_is_alphabetic_numeric().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 alphabetic or a numeric character.
 *   F_false if not a UTF-8 alphabetic nor a numeric character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alphabetic_numeric()
 * @see f_utf_is_alphabetic_numeric()
 */
#if !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_is_alphabetic_numeric_)
  extern f_status_t private_f_utf_character_is_alphabetic_numeric(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_is_alphabetic_numeric_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_alphabetic_h

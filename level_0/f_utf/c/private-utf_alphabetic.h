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
#ifndef _PRIVATE_F_utf_alphabetic_h
#define _PRIVATE_F_utf_alphabetic_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_alpha().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 alphabetic character.
 *   F_false if not a UTF-8 alphabetic character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alpha()
 * @see f_utf_is_alphabetic()
 */
#if !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_is_alphabeticbetic_)
  extern f_status_t private_f_utf_character_is_alphabetic(const f_utf_char_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_) || !defined(_di_f_utf_is_alphabeticbetic_)

/**
 * Private implementation of f_utf_character_is_alphabetic_digit().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 alphabetic or a digit character.
 *   F_false if not a UTF-8 alphabetic nor a digit character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alphabetic_digit()
 * @see f_utf_is_alphabeticbetic_digit()
 */
#if !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabeticbetic_digit_)
  extern f_status_t private_f_utf_character_is_alphabetic_digit(const f_utf_char_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_digit_) || !defined(_di_f_utf_is_alphabeticbetic_digit_)

/**
 * Private implementation of f_utf_character_is_alphabetic_numeric().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if a UTF-8 alphabetic or a numeric character.
 *   F_false if not a UTF-8 alphabetic nor a numeric character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_alphabetic_numeric()
 * @see f_utf_is_alphabeticbetic_numeric()
 */
#if !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_is_alphabeticbetic_numeric_)
  extern f_status_t private_f_utf_character_is_alphabetic_numeric(const f_utf_char_t character) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_alphabetic_numeric_) || !defined(_di_f_utf_is_alphabeticbetic_numeric_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_alphabetic_h

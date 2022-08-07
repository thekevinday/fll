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
#ifndef _PRIVATE_F_utf_word_h
#define _PRIVATE_F_utf_word_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_word().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word character.
 *   F_false if not a UTF-8 word character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_word()
 * @see f_utf_character_is_word_dash()
 * @see f_utf_character_is_word_dash_plus()
 * @see f_utf_is_word()
 * @see f_utf_is_word_dash()
 * @see f_utf_is_word_dash_plus()
 */
#if !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  extern f_status_t private_f_utf_character_is_word(const f_utf_char_t sequence, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_word_) || !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

/**
 * Private implementation of f_utf_character_is_word_dash().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word character or dash character.
 *   F_false if not a UTF-8 word character or dash character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_word_dash()
 * @see f_utf_character_is_word_dash_plus()
 * @see f_utf_is_word_dash()
 * @see f_utf_is_word_dash_plus()
 */
#if !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)
  extern f_status_t private_f_utf_character_is_word_dash(const f_utf_char_t sequence, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_word_dash_) || !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_) || !defined(_di_f_utf_is_word_dash_plus_)

/**
 * Private implementation of f_utf_character_is_word_dash_plus().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-inline punctuation connectors are not considered a character (such as U+FE33 '︳').
 *   When FALSE, zero-width punctuation characters are not considered a character.
 *
 * @return
 *   F_true if a UTF-8 word character, dash character, or plus character.
 *   F_false if not a UTF-8 word character, dash character, or plus character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_word_dash_plus()
 * @see f_utf_is_word_dash_plus()
 */
#if !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)
  extern f_status_t private_f_utf_character_is_word_dash_plus(const f_utf_char_t sequence, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_word_dash_plus_) || !defined(_di_f_utf_is_word_dash_plus_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_word_h

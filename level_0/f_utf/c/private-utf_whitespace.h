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
#ifndef _PRIVATE_F_utf_whitespace_h
#define _PRIVATE_F_utf_whitespace_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_whitespace().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 * @param strict
 *   When TRUE, include all appropriate characters by type as per Unicode.
 *   When FALSE, non-white space characters that are treated as white space by Unicode are not treated as white space.
 *
 * @return
 *   F_true if a UTF-8 white space.
 *   F_false if not a UTF-8 white space.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_whitespace()
 * @see f_utf_is_whitespace()
 */
#if !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)
  extern f_status_t private_f_utf_character_is_whitespace(const f_utf_char_t sequence, const bool strict) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_) || !defined(_di_f_utf_is_whitespace_)

/**
 * Private implementation of f_utf_character_is_whitespace_modifier().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 white space modifier.
 *   F_false if not a UTF-8 white space modifier.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_whitespace_modifier()
 * @see f_utf_is_whitespace_modifier()
 */
#if !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)
  extern f_status_t private_f_utf_character_is_whitespace_modifier(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_modifier_) || !defined(_di_f_utf_is_whitespace_modifier_)

/**
 * Private implementation of f_utf_character_is_whitespace_other().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 white space other.
 *   F_false if not a UTF-8 white space other.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_whitespace_other()
 * @see f_utf_is_whitespace_other()
 */
#if !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)
  extern f_status_t private_f_utf_character_is_whitespace_other(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_other_) || !defined(_di_f_utf_is_whitespace_other_)

/**
 * Private implementation of f_utf_character_is_whitespace_zero_width().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 white space other.
 *   F_false if not a UTF-8 white space other.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_whitespace_zero_width()
 * @see f_utf_is_whitespace_zero_width()
 */
#if !defined(_di_f_utf_character_is_whitespace_zero_width_) || !defined(_di_f_utf_is_whitespace_zero_width_)
  extern f_status_t private_f_utf_character_is_whitespace_zero_width(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_whitespace_zero_width_) || !defined(_di_f_utf_is_whitespace_zero_width_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_whitespace_h

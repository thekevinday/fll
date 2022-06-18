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
#ifndef _PRIVATE_F_utf_control_h
#define _PRIVATE_F_utf_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_control().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_control()
 * @see f_utf_is_control()
 */
#if !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)
  extern f_status_t private_f_utf_character_is_control(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_) || !defined(_di_f_utf_is_control_)

/**
 * Private implementation of f_utf_character_is_control_code().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_control_code()
 * @see f_utf_is_control_code()
 */
#if !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_control_code_)
  extern f_status_t private_f_utf_character_is_control_code(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_code_) || !defined(_di_f_utf_is_control_code_)

/**
 * Private implementation of f_utf_character_is_control_format().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 control character.
 *   F_false if not a UTF-8 control character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_control_format()
 * @see f_utf_is_control_format()
 */
#if !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)
  extern f_status_t private_f_utf_character_is_control_format(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_format_) || !defined(_di_f_utf_is_control_format_)

/**
 * Private implementation of f_utf_character_is_control_picture().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 *
 * @return
 *   F_true if a UTF-8 control picture character.
 *   F_false if not a UTF-8 control picture character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_control_picture()
 * @see f_utf_is_control_picture()
 */
#if !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)
  extern f_status_t private_f_utf_character_is_control_picture(const f_utf_char_t sequence) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_control_picture_) || !defined(_di_f_utf_is_control_picture_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_control_h

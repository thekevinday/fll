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
#ifndef _PRIVATE_F_utf_decimal_h
#define _PRIVATE_F_utf_decimal_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_utf_character_is_decimal().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * This expects the character width to be of at least size 2.
 *
 * @param sequence
 *   The byte sequence to validate as a character.
 * @param always
 *   Set to F_true to always return F_true for valid digits even if the valid digit would be invalid because it is out of the requested base range.
 *   When F_false, this function returns F_true if the decimal digit is a valid decimal digit within the requested base range.
 * @param value
 *   (optional) The integer representation of the character if the character is a decimal.
 *   If specified, value is set to 0xffff to represent no known representation.
 *   If specified and is initially a value of 0, then this represents the operating normall has decimal (base-10).
 *   If specified and is initially a value from 1 to 16, then this represents operating as that base unit.
 *   For example, if value is 16, then this function will operate "is hexidecimal" rather than "is decimal".
 *   If specified and is initially a value of 0xffff, then this will grab all known integer digits.
 *   Set to NULL to not use.
 *
 * @return
 *   F_true if a UTF-8 decimal character.
 *   F_false if not a UTF-8 decimal character.
 *
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 * @see f_utf_character_is_decimal()
 * @see f_utf_is_decimal()
 */
#if !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)
  extern f_status_t private_f_utf_character_is_decimal(const f_utf_char_t sequence, const bool always, uint32_t * const value) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)

/**
 * Helper function for handling ascii-only tests.
 *
 * The width is always assumed to be 1.
 *
 * @param character
 *   The ASCII character to validate.
 * @param always
 *   Set to F_true to always return F_true for valid digits even if the valid digit would be invalid because it is out of the requested base range.
 *   When F_false, this function returns F_true if the decimal digit is a valid decimal digit within the requested base range.
 * @param value
 *   (optional) The integer representation of the character if the character is a decimal.
 *   If specified, value is set to 0xffffffff (F_type_size_max_32_unsigned_d) to represent no known representation.
 *   If specified and is initially a value of 0, then this represents the operating normall has decimal (base-10).
 *   If specified and is initially a value from 1 to 16, then this represents operating as that base unit.
 *   For example, if value is 16, then this function will operate "is hexidecimal" rather than "is decimal".
 *   If specified and is initially a value of 0xffffffff (F_type_size_max_32_unsigned_d), then this will grab all known integer digits.
 *   Set to NULL to not use.
 *
 * @return
 *   F_true if a UTF-8 decimal character.
 *   F_false if not a UTF-8 decimal character.
 *
 * @see isdigit()
 *
 * @see f_utf_character_is_decimal()
 * @see f_utf_is_decimal()
 */
#if !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)
  extern f_status_t private_f_utf_character_is_decimal_for_ascii(const f_char_t character, const bool always, uint32_t * const value) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_utf_character_is_decimal_) || !defined(_di_f_utf_is_decimal_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_utf_decimal_h

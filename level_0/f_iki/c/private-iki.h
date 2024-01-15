/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_iki_h
#define _PRIVATE_F_iki_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_iki_content_partial_is().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param buffer
 *   The string to validate as an content name.
 * @param length
 *   The length of the string to validate.
 * @param range
 *   The range within the buffer that represents the content name.
 * @param quote
 *   The quote character in use.
 *   This must be either a single quote (') (U+0027), double quote (") (U+0022), or grave (`) (U+0060).
 *
 * @return
 *   F_true on success and string is a valid content name.
 *   F_false on success and string is not a valid content name.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_iki_content_is()
 * @see f_iki_content_partial_is()
 */
#if !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)
  extern f_status_t private_f_iki_content_partial_is(const f_string_t buffer, const f_number_unsigned_t length, const f_char_t quote) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)

/**
 * Private implementation of f_iki_object_partial_is().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param buffer
 *   The string to validate as an object name.
 * @param length
 *   The length of the string to validate.
 *
 * @return
 *   F_true on success and string is a valid object name.
 *   F_false on success and string is not a valid object name.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_iki_object_is()
 * @see f_iki_object_partial_is()
 */
#if !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)
  extern f_status_t private_f_iki_object_partial_is(const f_string_t buffer, const f_number_unsigned_t length) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_iki_h

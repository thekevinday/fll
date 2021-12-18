/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.5
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
 * @param range
 *   The range within the buffer that represents the content name.
 * @param quote
 *   The quote character in use.
 *   This must be either a single (') or double (") quote.
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
  extern f_status_t private_f_iki_content_partial_is(const f_string_static_t buffer, const f_string_range_t range, const uint8_t quote) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)

/**
 * Private implementation of f_iki_object_partial_is().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param buffer
 *   The string to validate as an object name.
 * @param range
 *   The range within the buffer that represents the object name.
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
  extern f_status_t private_f_iki_object_partial_is(const f_string_static_t buffer, const f_string_range_t range) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)

/**
 * Seek until a word, a dash, or a plus is found or is not found.
 *
 * This will ignore the delimit placeholder.
 * This will stop at any special characters, such as a colon, a single quote, a double quote, or a backslash.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The range within the buffer that represents the current position being processed.
 *
 * @return
 *   F_true if stopped on a word, a dash, or a plus.
 *   F_false if stopped on a plus scolon, single quote, double quote, and backslash or stopped on something other than a word, a dash, or a plus.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_utf_is_word_dash_plus().
 *
 * @see f_utf_buffer_increment()
 * @see f_utf_is_word_dash_plus()
 */
#if !defined(_di_f_iki_read_)
  extern f_status_t private_f_iki_seek_special(const f_string_static_t buffer, f_string_range_t *range) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_iki_read_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_iki_h

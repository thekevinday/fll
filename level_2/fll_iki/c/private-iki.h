/**
 * FLL - Level 2
 *
 * Project: IKI
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FLL_iki_h
#define _PRIVATE_FLL_iki_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fll_iki_content_escape().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param content
 *   The string to escape.
 * @param range
 *   The range within the buffer that represents the content.
 * @param quote
 *   The quote character in use.
 *   This must be either a single (') or double (") quote.
 * @param escaped
 *   The content whose data is escaped.
 *   The escaped string data is appended to this, so set the escaped.used = 0 if "replace" behavior is desired.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see f_string_dynamic_resize()
 * @see f_string_dynamic_increase_by()
 */
#if !defined(_di_fll_iki_content_escape_) || !defined(_di_fll_iki_content_partial_escape_)
  extern f_status_t private_fll_iki_content_partial_escape(const f_string_static_t content, const f_string_range_t range, const f_char_t quote, f_string_dynamic_t * const escaped) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_iki_content_escape_) || !defined(_di_fll_iki_content_partial_escape_)

/**
 * Private implementation of fll_iki_content_unescape().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param content
 *   The string to escape.
 * @param range
 *   The range within the buffer that represents the content.
 * @param quote
 *   The quote character in use.
 *   This must be either a single (') or double (") quote.
 * @param unescaped
 *   The content whose data is unescaped.
 *   The unescaped string data is appended to this, so set the unescaped.used = 0 if "replace" behavior is desired.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_syntax (with error bit) if the given string is invalid, such as having an undelimited quote.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see f_string_dynamic_resize()
 * @see f_string_dynamic_increase_by()
 */
#if !defined(_di_fll_iki_content_unescape_) || !defined(_di_fll_iki_content_partial_unescape_)
  extern f_status_t private_fll_iki_content_partial_unescape(const f_string_static_t content, const f_string_range_t range, const f_char_t quote, f_string_dynamic_t * const unescaped) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_iki_content_unescape_) || !defined(_di_fll_iki_content_partial_unescape_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_iki_h

/**
 * FLL - Level 2
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides a Wiki-Like syntax meant to be much simpler.
 *
 * This simpler Wiki-Like syntax, called Iki, focuses just on simply adding context.
 * The context itself is not explicitly defined but a few common standards are provided.
 */
#ifndef _FLL_iki_h
#define _FLL_iki_h

// libc includes
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/iki.h>

// fll-1 includes
#include <fll/level_1/iki.h>
#include <fll/level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Escape a string to allow it to be used in its entirety as an IKI content.
 *
 * This does not copy NULL characters.
 *
 * @param content
 *   The string to escape.
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
 *   Errors (with error bit) from: macro_f_string_dynamic_t_resize().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 */
#ifndef _di_fll_iki_content_escape_
  extern f_status_t fll_iki_content_escape(const f_string_static_t content, const uint8_t quote, f_string_dynamic_t *escaped);
#endif // _di_fll_iki_content_escape_

/**
 * Escape a string, found within the given range, to allow it to be used in its entirety as an IKI content.
 *
 * This does not copy NULL characters.
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
 *   Errors (with error bit) from: macro_f_string_dynamic_t_resize().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 */
#ifndef _di_fll_iki_content_partial_escape_
  extern f_status_t fll_iki_content_partial_escape(const f_string_static_t content, const f_string_range_t range, const uint8_t quote, f_string_dynamic_t *escaped);
#endif // _di_fll_iki_content_partial_escape_

/**
 * Unescape a string, found within the given range, from IKI content to allow it to be used normally.
 *
 * This does not copy NULL characters.
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
 *   Errors (with error bit) from: macro_f_string_dynamic_t_resize().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 */
#ifndef _di_fll_iki_content_partial_unescape_
  extern f_status_t fll_iki_content_partial_unescape(const f_string_static_t content, const f_string_range_t range, const uint8_t quote, f_string_dynamic_t *unescaped);
#endif // _di_fll_iki_content_partial_unescape_

/**
 * Unescape a string from IKI content to allow it to be used normally.
 *
 * This does not copy NULL characters.
 *
 * @param content
 *   The string to escape.
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
 *   Errors (with error bit) from: macro_f_string_dynamic_t_resize().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 */
#ifndef _di_fll_iki_content_unescape_
  extern f_status_t fll_iki_content_unescape(const f_string_static_t content, const uint8_t quote, f_string_dynamic_t *unescaped);
#endif // _di_fll_iki_content_unescape_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_iki_h

/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_write_process_h
#define _iki_write_write_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process a given object and content, printing the IKI if valid or an error if invalid.
 *
 * @param main
 *   The program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_iki_object_is().
 *     Errors (with error bit) from: fll_iki_content_escape().
 *
 *     F_failure (with error bit) for any other failure.
 * @param object
 *   The object to validate and print.
 * @param content
 *   The content to escape and print.
 *
 * @see f_iki_object_is()
 * @see fll_iki_content_escape()
 */
#ifndef _di_iki_write_process_
  extern void iki_write_process(iki_write_main_t * const main, const f_string_static_t object, const f_string_static_t content) F_attribute_visibility_internal_d;
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_write_process_h

/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_write_h
#define _PRIVATE_write_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process a given object and content, printing the IKI if valid or an error if invalid.
 *
 * @param data
 *   The program data.
 * @param output
 *   The file to output to.
 * @param object
 *   The object to validate and print.
 * @param content
 *   The content to escape and print.
 * @param escaped
 *   A string buffer used as a string cache to save the string into while escaping.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_iki_write_process_
  extern f_status_t iki_write_process(iki_write_data_t * const data, const f_file_t output, const f_string_static_t object, const f_string_static_t content, f_string_dynamic_t *escaped) F_attribute_visibility_internal_d;
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_write_h

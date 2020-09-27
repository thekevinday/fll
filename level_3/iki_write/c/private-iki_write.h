/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_iki_write_h
#define _PRIVATE_iki_write_h

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
 * @param quote
 *   The quote character to use.
 *   This is either f_iki_syntax_quote_single or f_iki_syntax_quote_double.
 * @param escaped
 *   A string buffer used as a string cache to save the string into while escaping.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any othe failure.
 */
#ifndef _di_iki_write_process_
  extern f_return_status iki_write_process(const iki_write_data_t data, const f_file_t output, const f_string_static_t object, const f_string_static_t content, const uint8_t quote, f_string_dynamic_t *escaped) f_gcc_attribute_visibility_internal;
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_iki_write_h

/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_utf8_h
#define _PRIVATE_utf8_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_utf8_data_delete_
  extern void utf8_data_delete(utf8_data_t *data);
#endif // _di_utf8_data_delete_

/**
 * Convert the text from one format to other another format or verify text.
 *
 * @param data
 *   The program data.
 * @param text
 *   This represent a single text data.
 *   This text is NULL terminated and can therefore not contain any NULLs.
 *
 * @return
 *   F_true on success and is valid.
 *   F_false on success and contains invalid sequences.
 *   F_signal on (exit) signal received.
 *
 *   Errors (with error bit) from: utf8_convert_binary()
 *   Errors (with error bit) from: utf8_convert_codepoint()
 *   Errors (with error bit) from: utf8_detect_codepoint()
 *
 * @see utf8_convert_binary()
 * @see utf8_convert_codepoint()
 * @see utf8_detect_codepoint()
 * @see utf8_signal_received()
 */
#ifndef _di_utf8_process_text_
  extern f_status_t utf8_process_text(utf8_data_t * const data, const f_string_t text) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_text_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_h

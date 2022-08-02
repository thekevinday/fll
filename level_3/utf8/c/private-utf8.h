/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_utf8_h
#define _PRIVATE_utf8_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   F_interrupt on (exit) signal received.
 *
 *   Errors (with error bit) from: utf8_convert_bytesequence()
 *   Errors (with error bit) from: utf8_convert_codepoint()
 *   Errors (with error bit) from: utf8_detect_codepoint()
 *
 * @see utf8_convert_bytesequence()
 * @see utf8_convert_codepoint()
 * @see utf8_detect_codepoint()
 * @see utf8_signal_received()
 */
#ifndef _di_utf8_process_text_
  extern f_status_t utf8_process_text(utf8_data_t * const data, f_string_static_t text) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_text_

/**
 * Populate the text used and size based on the string.
 *
 * @param text
 *   The character data.
 *
 *   The used represents the actual length of the character in bytes.
 *   The size represents the expected length of the character in bytes.
 */
#ifndef _di_utf8_process_text_width_
  extern void utf8_process_text_width(f_string_static_t *text) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_text_width_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_h

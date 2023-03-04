/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_process_h
#define _utf8_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert the text from one format to other another format or verify text.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param text
 *   This represent a single text data.
 *   This text is NULL terminated and can therefore not contain any NULLs.
 *
 *   This alters setting.state.status:
 *     F_true on success and is valid.
 *     F_false on success and contains invalid sequences.
 *     F_interrupt on (exit) signal received.
 *
 *     Errors (with error bit) from: utf8_convert_bytesequence()
 *     Errors (with error bit) from: utf8_convert_codepoint()
 *     Errors (with error bit) from: utf8_detect_codepoint()
 *
 * @see utf8_convert_bytesequence()
 * @see utf8_convert_codepoint()
 * @see utf8_detect_codepoint()
 * @see utf8_signal_received()
 */
#ifndef _di_utf8_process_text_
  extern void utf8_process_text(fll_program_data_t * const main, utf8_setting_t * const setting, f_string_static_t text) F_attribute_visibility_internal_d;
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

#endif // _utf8_process_h

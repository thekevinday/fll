/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_utf8_bytesequence_h
#define _PRIVATE_utf8_bytesequence_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a byte sequence character to another format.
 *
 * This automatically determines the output format and is also handles the verify process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param sequence
 *   A byte sequences representing a single character to convert.
 *   This does not stop on NULL and will process all text until sequence.used.
 *
 * @return
 *   F_none on success.
 *   F_utf_not on invalid UTF-8 (which is still "success" when verifying).
 *
 *   F_utf_not (with error bit) if not verifying and
 *
 *   Errors (with error bit) from: f_utf_unicode_to()
 */
#ifndef _di_utf8_convert_bytesequence_
  extern f_status_t utf8_convert_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence) F_attribute_visibility_internal_d;
#endif // _di_utf8_convert_bytesequence_

/**
 * Process file as a bytesequence input, handling conversion or verification as appropriate.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param file
 *   The file stream to process.
 *   This file may contain NULLs.
 *
 * @return
 *   F_true on success and is valid.
 *   F_false on success and contains invalid sequences.
 *   F_interrupt on (exit) signal received.
 *
 *   Errors (with error bit) from: utf8_convert_bytesequence()
 *   Errors (with error bit) from: utf8_detect_codepoint()
 *
 * @see fll_program_standard_signal_received()
 * @see utf8_convert_bytesequence()
 * @see utf8_detect_codepoint()
 */
#ifndef _di_utf8_process_file_bytesequence_
  extern f_status_t utf8_process_file_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_file_t file) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_file_bytesequence_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_bytesequence_h

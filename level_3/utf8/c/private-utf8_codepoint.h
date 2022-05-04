/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_utf8_codepoint_h
#define _PRIVATE_utf8_codepoint_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a codepoint character representation to another format.
 *
 * This automatically determines the output format and is also handles the verify process.
 *
 * @param data
 *   The program data.
 * @param character
 *   The a single character currently being processed.
 * @param mode
 *   The codepoint mode the text is currently in.
 *
 * @return
 *   F_none on success.
 *   F_utf on invalid UTF-8 (which is still "success" when verifying).
 *
 *   F_utf (with error bit) if not verifying and
 *
 *   Errors (with error bit) from: f_utf_unicode_to()
 */
#ifndef _di_utf8_convert_codepoint_
  extern f_status_t utf8_convert_codepoint(utf8_data_t * const data, const f_string_static_t character, uint8_t *mode) F_attribute_visibility_internal_d;
#endif // _di_utf8_convert_codepoint_

/**
 * Detect a codepoint character.
 *
 * @param data
 *   The program data.
 * @param character
 *   The a single character to analyze.
 * @param mode
 *   Designate the mode in which the curent state is being processed.
 *
 * @return
 *   F_none on success.
 *   F_next on success, but should not be processed (it is whitespace or NULL).
 *
 *   Errors (with error bit) from: f_utf_is_whitespace()
 */
#ifndef _di_utf8_detect_codepoint_
  extern f_status_t utf8_detect_codepoint(utf8_data_t * const data, const f_string_static_t character, uint8_t *mode) F_attribute_visibility_internal_d;
#endif // _di_utf8_detect_codepoint_

/**
 * Process file as a codepoint input, handling conversion or verification as appropriate.
 *
 * @param data
 *   The program data.
 * @param file
 *   The file stream to process.
 *   This file may contain NULLs.
 *
 * @return
 *   F_true on success and is valid.
 *   F_false on success and contains invalid sequences.
 *   F_interrupt on (exit) signal received.
 *
 *   Errors (with error bit) from: utf8_convert_bytecode()
 *   Errors (with error bit) from: utf8_detect_codepoint()
 *
 * @see fll_program_standard_signal_received()
 * @see utf8_convert_bytecode()
 * @see utf8_detect_codepoint()
 */
#ifndef _di_utf8_process_file_codepoint_
  extern f_status_t utf8_process_file_codepoint(utf8_data_t * const data, const f_file_t file) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_file_codepoint_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_codepoint_h

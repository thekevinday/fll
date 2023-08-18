/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the codepoint functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _PRIVATE_utf8_codepoint_h
#define _PRIVATE_utf8_codepoint_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a codepoint character representation to another format.
 *
 * This automatically determines the output format and also handles the verify process.
 *
 * @param main
 *   The program and settings data.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *     F_utf_not on invalid UTF-8 (which is still "success" when verifying).
 *
 *     F_utf_not (with error bit) if not verifying and the Unicode value is invalid.
 *
 *     Errors (with error bit) from: f_utf_unicode_to()
 * @param unicode
 *   A set of bytes representing a single codepoint character to process.
 * @param mode
 *   The codepoint mode the text is currently in.
 *
 * @see f_utf_unicode_to()
 */
#ifndef _di_utf8_convert_codepoint_
  extern void utf8_convert_codepoint(utf8_main_t * const main, const f_string_static_t unicode, uint8_t *mode);
#endif // _di_utf8_convert_codepoint_

/**
 * Convert a raw character representation (hex-digit) to another format.
 *
 * This automatically determines the output format and also handles the verify process.
 *
 * @param main
 *   The program and settings data.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *     F_valid_not on invalid raw (which is still "success" when verifying).
 *
 *     F_valid_not (with error bit) if not verifying and the raw value is invalid.
 *
 *     Errors (with error bit) from: fl_conversion_dynamic_to_unsigned_detect()
 * @param hex
 *   A set of bytes representing hexidecimal digits of a character to process.
 * @param mode
 *   The codepoint mode the text is currently in.
 *
 * @see fl_conversion_dynamic_to_unsigned_detect()
 */
#ifndef _di_utf8_convert_raw_
  extern void utf8_convert_raw(utf8_main_t * const main, const f_string_static_t hex, uint8_t *mode);
#endif // _di_utf8_convert_raw_

/**
 * Detect a codepoint character.
 *
 * @param main
 *   The program and settings data.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *     F_next on success, but should not be processed (it is white space or NULL).
 *     F_space on success, but the character is whitespace.
 *
 *     Errors (with error bit) from: f_utf_is_whitespace()
 * @param unicode
 *   A set of bytes representing a single codepoint character to process.
 * @param mode
 *   Designate the mode in which the curent state is being processed.
 */
#ifndef _di_utf8_detect_codepoint_
  extern void utf8_detect_codepoint(utf8_main_t * const main, const f_string_static_t unicode, uint8_t *mode);
#endif // _di_utf8_detect_codepoint_

/**
 * Process file as a codepoint input, handling conversion or verification as appropriate.
 *
 * @param main
 *   The program and settings data.
 *
 *   This alters setting.state.status:
 *     F_true on success and is valid.
 *     F_false on success and contains invalid sequences.
 *     F_interrupt on (exit) signal received.
 *
 *     Errors (with error bit) from: utf8_convert_bytesequence()
 *     Errors (with error bit) from: utf8_detect_codepoint()
 * @param file
 *   The file stream to process.
 *   This file may contain NULLs.
 *
 * @see fll_program_standard_signal_received()
 * @see utf8_convert_bytesequence()
 * @see utf8_detect_codepoint()
 */
#ifndef _di_utf8_process_file_codepoint_
  extern void utf8_process_file_codepoint(utf8_main_t * const main, const f_file_t file);
#endif // _di_utf8_process_file_codepoint_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_codepoint_h

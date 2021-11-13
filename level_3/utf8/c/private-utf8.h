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
 * @todo make this a define rather than an enum so that "bad/invalid" can be passed along with different state values.
 *       Or do some sort of trick ("XXX >> 1, to get enum value such that the first bit represents valid/invalid).
 * private_utf8_codepoint_modes_*:
 *   - ready:  The codepoint has yet to be processed, skip leading spaces until first 'U' is matched.
 *   - begin:  The first 'U' is matched, look for the '+'.
 *   - number: The '+' is matched, process numbers.
 *   - end:    The last number is reached (at either whitespace or EOS/EOF).
 *   - bad:    This is not a valid codepoint.
 */
#ifndef _di_private_utf8_codepoint_modes_
  enum {
    private_utf8_codepoint_modes_ready = 1,
    private_utf8_codepoint_modes_begin,
    private_utf8_codepoint_modes_number,
    private_utf8_codepoint_modes_end,
    private_utf8_codepoint_modes_bad,
  };
#endif // _di_private_utf8_codepoint_modes_

/**
 * Convert a binary character to another format.
 *
 * This automatically determines the output format and is also handles the verify process.
 *
 * @param main
 *   The main program data.
 * @param character
 *   The a single character to convert.
 *   This does not stop on NULL and will process all text until text.used.
 *
 * @return
 *   F_none on success.
 *   F_utf on invalid UTF-8 (which is still "success" when verifying).
 *
 *   F_utf (with error bit) if not verifying and
 *
 *   Errors (with error bit) from: f_utf_unicode_to()
 */
#ifndef _di_utf8_convert_binary_
  extern f_status_t utf8_convert_binary(utf8_main_t * const main, const f_string_static_t character) F_attribute_visibility_internal_d;
#endif // _di_utf8_convert_binary_

/**
 * Convert a codepoint character representation to another format.
 *
 * This automatically determines the output format and is also handles the verify process.
 *
 * @param main
 *   The main program data.
 * @param character
 *   The a single character to convert.
 *   This does not stop on NULL and will process all text until text.used.
 * @param mode
 *   Designate the mode in which the curent state is being processed.
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
  extern f_status_t utf8_convert_codepoint(utf8_main_t * const main, const f_string_static_t text, uint8_t *mode) F_attribute_visibility_internal_d;
#endif // _di_utf8_convert_codepoint_

/**
 * Process file as a binary input, handling conversion or verification as appropriate.
 *
 * @param main
 *   The main program data.
 * @param file
 *   The file stream to process.
 *   This file may contain NULLs.
 *
 * @return
 *   F_true on success and is valid.
 *   F_false on success and contains invalid sequences.
 *   F_signal on (exit) signal received.
 *
 *   Errors (with error bit) from: utf8_convert_binary()
 *   Errors (with error bit) from: utf8_convert_codepoint()
 *
 * @see utf8_convert_binary()
 * @see utf8_signal_received()
 */
#ifndef _di_utf8_process_file_binary_
  extern f_status_t utf8_process_file_binary(utf8_main_t * const main, const f_file_t file) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_file_binary_

/**
 * Process file as a codepoint input, handling conversion or verification as appropriate.
 *
 * @param main
 *   The main program data.
 * @param file
 *   The file stream to process.
 *   This file may contain NULLs.
 *
 * @return
 *   F_true on success and is valid.
 *   F_false on success and contains invalid sequences.
 *   F_signal on (exit) signal received.
 *
 *   Errors (with error bit) from: utf8_convert_binary()
 *   Errors (with error bit) from: utf8_convert_codepoint()
 *
 * @see utf8_convert_binary()
 * @see utf8_convert_codepoint()
 * @see utf8_signal_received()
 */
#ifndef _di_utf8_process_file_codepoint_
  extern f_status_t utf8_process_file_codepoint(utf8_main_t * const main, const f_file_t file) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_file_codepoint_

/**
 * Convert the text from one format to other another format or verify text.
 *
 * @param main
 *   The main program data.
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
 *
 * @see utf8_convert_binary()
 * @see utf8_convert_codepoint()
 * @see utf8_signal_received()
 */
#ifndef _di_utf8_process_text_
  extern f_status_t utf8_process_text(utf8_main_t * const main, const f_string_t text) F_attribute_visibility_internal_d;
#endif // _di_utf8_process_text_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_utf8_signal_received_
  extern f_status_t utf8_signal_received(utf8_main_t * const main);
#endif // _di_utf8_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_utf8_h

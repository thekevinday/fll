/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Codepoint modes for converting to/from binary and codepoint values.
 *
 * The special "raw" format is used only for reading from codepoint format where that format represents binary character that is not a valid Unicode character.
 * This is intended to be used to save and restore the original binary data even if that data is invalid.
 *
 * private_utf8_codepoint_mode_*:
 *   - ready:      The codepoint has yet to be processed, skip leading spaces until first 'U' is matched.
 *   - begin:      The first 'U' is matched, look for the '+'.
 *   - number:     The '+' is matched, process numbers.
 *   - end:        The last number is reached (at either white space or EOS/EOF).
 *   - bad:        This is not a valid codepoint.
 *   - bad_begin:  This is the beginning of an invalid codepoint.
 *   - bad_end:    The end of bad is detected, which happens on white space or end of buffer.
 *   - raw_begin:  This is the beginning of a potential raw data (matched '0').
 *   - raw_number: This is the confirmed beginning of raw data (matched 'X'), process numbers.
 *   - raw_end:    The end of raw data is detected, which happens on white space or end of buffer.
 */
#ifndef _di_utf8_codepoint_modes_
  enum {
    utf8_codepoint_mode_ready_e = 1,
    utf8_codepoint_mode_begin_e,
    utf8_codepoint_mode_number_e,
    utf8_codepoint_mode_end_e,
    utf8_codepoint_mode_bad_e,
    utf8_codepoint_mode_bad_begin_e,
    utf8_codepoint_mode_bad_end_e,
    utf8_codepoint_mode_raw_begin_e,
    utf8_codepoint_mode_raw_number_e,
    utf8_codepoint_mode_raw_end_e,
  };
#endif // _di__utf8_codepoint_modes_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h

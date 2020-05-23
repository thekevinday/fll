/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _FL_fss_h
#define _FL_fss_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/conversion.h>
#include <level_0/status.h>
#include <level_0/file.h>
#include <level_0/fss.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss_status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Continue to the previous character, based on step and character width.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to decrement the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be (sizeof(int8_t), which is 1).
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(int8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_incomplete_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 */
#ifndef _di_fl_fss_decrement_buffer_
  extern f_return_status fl_fss_decrement_buffer(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_fl_fss_decrement_buffer_

/**
 * Identify FSS type from a buffered string.
 *
 * @param buffer
 *   The string to process.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   FL_fss_header_not if no header is found.
 *   FL_fss_header_not (with error bit) if the an error occurred prior to identifying a valid header.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_identify_
  extern f_return_status fl_fss_identify(const f_string_static buffer, f_fss_header *header);
#endif // _di_fl_fss_identify_

/**
 * Identify FSS type from a file.
 *
 * @param file
 *   The file information.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_file_read_until().
 *   Errors from (with error bit): fl_fss_identify()
 *   File errors (with error bit): F_file_seek, F_file_open_not.
 *
 * @see f_file_read_until()
 * @see fl_fss_identify()
 */
#ifndef _di_fl_fss_identify_file_
  extern f_return_status fl_fss_identify_file(f_file *file, f_fss_header *header);
#endif // _di_fl_fss_identify_file_

/**
 * Continue to the next character, based on step and character width.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to increment the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be (sizeof(int8_t), which is 1).
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(int8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_incomplete_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 */
#ifndef _di_fl_fss_increment_buffer_
  extern f_return_status fl_fss_increment_buffer(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_fl_fss_increment_buffer_

/**
 * Identify whether or not a character in the buffer is a graph (ASCII or UTF-8) character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_true if the character in the buffer is a graph character.
 *   F_false if the character in the buffer is not a graph character.
 *   F_maybe (with error bit) if the character width is outside the stop position.
 *   F_failure (with error bit) if the buffer is not wide enough or the width is outside the stop position.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_is_graph_
  extern f_return_status fl_fss_is_graph(const f_string_static buffer, const f_string_range range);
#endif // _di_fl_fss_is_graph_

/**
 * Identify whether or not a character in the buffer is a space (ASCII or UTF-8) character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_true if the character in the buffer is a space character.
 *   F_false if the character in the buffer is not a space character.
 *   F_maybe (with error bit) if the character width is outside the stop position.
 *   F_failure (with error bit) if the buffer is not wide enough or the width is outside the stop position.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_is_space_
  extern f_return_status fl_fss_is_space(const f_string_static buffer, const f_string_range range);
#endif // _di_fl_fss_is_space_

/**
 * Shift all of the delimiters to the end of the used buffer.
 *
 * This allows one to do a printf on the dynamic string without the delimiters arbitrarily stopping the output.
 * No reallocations are performed, this will only shift characters.
 *
 * @param buffer
 *   The string to process.
 *   This gets updated.
 * @param range
 *   A restriction on where within the buffer the shifting happens.
 *
 * @return
 *   F_none on success.
 *   F_utf (with error bit) if UTF-8 cannot be fully processed (buffer or range range not long enough).
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_shift_delimiters_
  extern f_return_status fl_fss_shift_delimiters(f_string_dynamic *buffer, const f_string_range range);
#endif // _di_fl_fss_shift_delimiters_

/**
 * Skip past all whitespace and control characters, except newline.
 *
 * Zero-width characters are not skipped because they might be part of a graph character, such as combining characters.
 * @todo needs consideration on how to handle zero-width before space/control vs zero-width before graph.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_skip_past_space_
  extern f_return_status fl_fss_skip_past_space(const f_string_static buffer, f_string_range *range);
#endif // _di_fl_fss_skip_past_space_

/**
 * Skip past all non-graph and non-zero-width characters (whitespace and control characters).
 *
 * Zero-width characters are not skipped because they might be part of a graph character, such as combining characters.
 * @todo needs consideration on how to handle zero-width before space/control vs zero-width before graph.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_skip_past_non_graph_
  extern f_return_status fl_fss_skip_past_non_graph(const f_string_static buffer, f_string_range *range);
#endif // _di_fl_fss_skip_past_non_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_h

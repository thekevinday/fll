/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines all datatypes to be used for/by project fss.
 *
 * The purpose of compression is not to compression the entire file's contents but only and individual objects content, so the file is still partially readable.
 * NOTE: all start/stop locations must be defined as a (start < stop) and not (start <= stop), therefore if (start == stop) then stop.
 */
#ifndef _F_fss_h
#define _F_fss_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

// fll-0 fss includes
#include <level_0/fss-common.h>
#include <level_0/fss-named.h>
#include <level_0/fss-nest.h>
#include <level_0/fss-set.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Count the number of new lines from the buffer before the given location.
 *
 * Use this to calculate where a given range exists in relation to a line.
 *
 * This does not initialize line, instead it only performs addition to line.
 *
 * @param buffer
 *   The string to process.
 * @param before
 *   The position in the buffer where to start counting before.
 * @param line
 *   The total lines found leading up to but not including before.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_count_lines_
  extern f_return_status f_fss_count_lines(const f_string_static buffer, const f_string_length before, f_string_length *line);
#endif // _di_f_fss_count_lines_

/**
 * Count the number of new lines from the given range in the buffer before the given location.
 *
 * Use this to calculate where a given range exists in relation to a line.
 *
 * This does not initialize line, instead it only performs addition to line.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The range within the buffer to process.
 * @param before
 *   The position in the buffer where to start counting before.
 * @param line
 *   The total lines found leading up to but not including before.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_count_lines_range_
  extern f_return_status f_fss_count_lines_range(const f_string_static buffer, const f_string_range range, const f_string_length before, f_string_length *line);
#endif // _di_f_fss_count_lines_range_

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
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_decrement_buffer_
  extern f_return_status f_fss_decrement_buffer(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_f_fss_decrement_buffer_

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
 *   F_incomplete_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_increment_buffer_
  extern f_return_status f_fss_increment_buffer(const f_string_static buffer, f_string_range *range, const f_string_length step);
#endif // _di_f_fss_increment_buffer_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_fss_is_graph_
  extern f_return_status f_fss_is_graph(const f_string_static buffer, const f_string_range range);
#endif // _di_f_fss_is_graph_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_space().
 *
 * @see f_utf_is_space()
 */
#ifndef _di_f_fss_is_space_
  extern f_return_status f_fss_is_space(const f_string_static buffer, const f_string_range range);
#endif // _di_f_fss_is_space_

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
#ifndef _di_f_fss_shift_delimiters_
  extern f_return_status f_fss_shift_delimiters(f_string_dynamic *buffer, const f_string_range range);
#endif // _di_f_fss_shift_delimiters_

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
 *   F_none_eol on success and EOL was reached.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment was found.
 *   F_incomplete_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *   F_incomplete_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_control().
 *   Errors from (with error bit): f_utf_is_whitespace().
 *   Errors from (with error bit): f_utf_is_zero_width().
 *
 * @see f_utf_is_control()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_space_
  extern f_return_status f_fss_skip_past_space(const f_string_static buffer, f_string_range *range);
#endif // _di_f_fss_skip_past_space_

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
 *   F_none_eol on success and EOL was reached.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment was found.
 *   F_incomplete_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *   F_incomplete_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): f_utf_is_graph().
 *   Errors from (with error bit): f_utf_is_zero_width().
 *
 * @see f_utf_is_graph()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_non_graph_
  extern f_return_status f_fss_skip_past_non_graph(const f_string_static buffer, f_string_range *range);
#endif // _di_f_fss_skip_past_non_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_h

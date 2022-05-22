/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines all datatypes to be used for/by project fss.
 *
 * The purpose of compression is not to compression the entire file's contents but only and individual objects content, so the file is still partially readable.
 * NOTE: all start/stop locations must be defined as a (start < stop) and not (start <= stop), therefore if (start == stop) then stop.
 */
#ifndef _F_fss_h
#define _F_fss_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// FLL-0 fss includes.
#include <fll/level_0/fss/comment.h>
#include <fll/level_0/fss/common.h>
#include <fll/level_0/fss/delimit.h>
#include <fll/level_0/fss/quote.h>
#include <fll/level_0/fss/named.h>
#include <fll/level_0/fss/nest.h>
#include <fll/level_0/fss/set.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Replace all 1-byte character locations specified by the delimits within the given buffer by a delimit placeholder.
 *
 * Any delimits out of range (beyond the buffer.used) are ignored.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param delimits
 *   An array of locations containing the delimits to apply within the buffer.
 * @param buffer
 *   The string to process.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_apply_delimit_
  extern f_status_t f_fss_apply_delimit(f_state_t state, const f_fss_delimits_t delimits, f_string_static_t * const buffer);
#endif // _di_f_fss_apply_delimit_

/**
 * Replace all 1-byte character locations specified by the delimits within the given buffer by a delimit placeholder if within the given range.
 *
 * If the delimits are found to be (inclusively) within the range specified by range, then those delimits are applied.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param delimits
 *   An array of locations containing the delimits to apply within the buffer.
 * @param range
 *   The range in which to restrict which delimits to apply.
 * @param buffer
 *   The string to process.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_apply_delimit_between_
  extern f_status_t f_fss_apply_delimit_between(f_state_t state, const f_fss_delimits_t delimits, const f_string_range_t range, f_string_static_t * const buffer);
#endif // _di_f_fss_apply_delimit_between_

/**
 * Count the number of new lines from the buffer before the given location.
 *
 * Use this to calculate where a given range exists in relation to a line.
 *
 * This does not initialize line, instead it only performs addition to line.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param buffer
 *   The string to process.
 * @param before
 *   The position in the buffer where to start counting before.
 * @param line
 *   The total lines found leading up to but not including before.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_count_lines_
  extern f_status_t f_fss_count_lines(f_state_t state, const f_string_static_t buffer, const f_array_length_t before, f_array_length_t * const line);
#endif // _di_f_fss_count_lines_

/**
 * Count the number of new lines from the given range in the buffer before the given location.
 *
 * Use this to calculate where a given range exists in relation to a line.
 *
 * This does not initialize line, instead it only performs addition to line.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_count_lines_range_
  extern f_status_t f_fss_count_lines_range(f_state_t state, const f_string_static_t buffer, const f_string_range_t range, const f_array_length_t before, f_array_length_t * const line);
#endif // _di_f_fss_count_lines_range_

/**
 * Using the state, check that the status should return an error or not on invalid UTF-8.
 *
 * When f_fss_state_flag_utf_fail_on_valid_not_e is set, UTF-8 failures are returned as is.
 * When f_fss_state_flag_utf_fail_on_valid_not_e is unset, UTF-8 failures are returned with the error bit removed.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param status
 *   The status code to check.
 *   This handles status codes (with error bit set):
 *   - F_complete_not_utf
 *   - F_utf_fragment
 *   - F_utf_not
 *
 * @return
 *   Status is either directly passed through or the error bit is removed depending on state.flag.
 */
#ifndef _di_f_fss_do_fail_utf_
  extern f_status_t f_fss_fail_utf(f_state_t state, const f_status_t status);
#endif // _di_f_fss_fail_utf_

/**
 * Using the state, check that the status should return an error or not on invalid UTF-8.
 *
 * When f_fss_state_flag_utf_fail_on_valid_not_e is set, UTF-8 failures are returned as is.
 * When f_fss_state_flag_utf_fail_on_valid_not_e is unset, UTF-8 failures are replaced with F_false.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param status
 *   The status code to check.
 *   This handles status codes (with error bit set):
 *   - F_complete_not_utf
 *   - F_utf_fragment
 *   - F_utf_not
 *
 * @return
 *   Status is either directly passed through or F_false is returned depending on state.flag.
 */
#ifndef _di_f_fss_do_fail_to_false_utf_
  extern f_status_t f_fss_fail_utf_to_false(f_state_t state, const f_status_t status);
#endif // _di_f_fss_fail_utf_to_false_

/**
 * Identify whether or not a character in the buffer is a graph (ASCII or UTF-8) character.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_fss_is_graph_
  extern f_status_t f_fss_is_graph(f_state_t state, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_f_fss_is_graph_

/**
 * Identify whether or not a character in the buffer is a non-zero-width whitespace or control (ASCII or UTF-8) character.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_control().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_control()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_fss_is_space_
  extern f_status_t f_fss_is_space(f_state_t state, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_f_fss_is_space_

/**
 * Identify whether or not a character in the buffer is a non-zero-width whitespace or control (ASCII or UTF-8) character.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_control().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_is_zero_width_
  extern f_status_t f_fss_is_zero_width(f_state_t state, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_f_fss_is_zero_width_

/**
 * Seek until an EOL character is reached.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_seek_to_eol_
  extern f_status_t f_fss_seek_to_eol(f_state_t state, const f_string_dynamic_t buffer, f_string_range_t * const range);
#endif // _di_f_fss_seek_to_eol_

/**
 * Shift all of the delimit placeholders to the end of the used buffer.
 *
 * This allows one to do a printf on the dynamic string without the delimiters arbitrarily stopping the output.
 * No reallocations are performed, this will only shift characters.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param range
 *   A restriction on where within the buffer the shifting happens.
 * @param buffer
 *   The string to process.
 *   This gets updated.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if UTF-8 cannot be fully processed (buffer or range range not long enough).
 */
#ifndef _di_f_fss_shift_delimit_
  extern f_status_t f_fss_shift_delimit(f_state_t state, const f_string_range_t range, f_string_dynamic_t * const buffer);
#endif // _di_f_fss_shift_delimit_

/**
 * Skip past all delimit placeholders until a non-delimit placeholder is reached.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success and EOS was reached.
 *   F_none_stop on success and stop point was reached.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_skip_past_delimit_
  extern f_status_t f_fss_skip_past_delimit(f_state_t state, const f_string_static_t buffer, f_string_range_t * const range);
#endif // _di_f_fss_skip_past_delimit_

/**
 * Skip past all whitespace and control characters, except newline.
 *
 * Zero-width characters are not skipped because they might be part of a graph character, such as combining characters.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
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
 *
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment was found.
 *   F_complete_not_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *   F_complete_not_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_control().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *   Errors (with error bit) from: f_utf_is_zero_width().
 *
 * @see f_utf_is_control()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_space_
  extern f_status_t f_fss_skip_past_space(f_state_t state, const f_string_static_t buffer, f_string_range_t * const range);
#endif // _di_f_fss_skip_past_space_

/**
 * Skip past all non-graph and non-zero-width characters (whitespace and control characters).
 *
 * Zero-width characters are not skipped because they might be part of a graph character, such as combining characters.
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
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
 *
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment was found.
 *   F_complete_not_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *   F_complete_not_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *   Errors (with error bit) from: f_utf_is_zero_width().
 *
 * @see f_utf_is_graph()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_non_graph_
  extern f_status_t f_fss_skip_past_non_graph(f_state_t state, const f_string_static_t buffer, f_string_range_t * const range);
#endif // _di_f_fss_skip_past_non_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_h

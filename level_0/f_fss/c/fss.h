/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
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
#include <fll/level_0/fss/common.h>
#include <fll/level_0/fss/item.h>
#include <fll/level_0/fss/named.h>
#include <fll/level_0/fss/nest.h>
#include <fll/level_0/fss/quote.h>
#include <fll/level_0/fss/set.h>
#include <fll/level_0/fss/set_quote.h>
#include <fll/level_0/fss/simple_packet.h>
#include <fll/level_0/fss/payload.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Replace all 1-byte character locations specified by the delimits within the given buffer by a delimit placeholder.
 *
 * Any delimits out of range (beyond the buffer.used) are ignored.
 *
 * @param delimits
 *   An array of locations containing the delimits to apply within the buffer.
 * @param buffer
 *   The string to process.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but buffer.used is 0.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_apply_delimit_
  extern void f_fss_apply_delimit(const f_number_unsigneds_t delimits, f_string_static_t * const buffer, f_state_t * const state);
#endif // _di_f_fss_apply_delimit_

/**
 * Replace all 1-byte character locations specified by the delimits within the given buffer by a delimit placeholder if within the given range.
 *
 * If the delimits are found to be (inclusively) within the range specified by range, then those delimits are applied.
 *
 * @param delimits
 *   An array of locations containing the delimits to apply within the buffer.
 * @param range
 *   The range in which to restrict which delimits to apply.
 * @param buffer
 *   The string to process.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but buffer.used is 0.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_apply_delimit_range_
  extern void f_fss_apply_delimit_range(const f_number_unsigneds_t delimits, const f_range_t range, f_string_static_t * const buffer, f_state_t * const state);
#endif // _di_f_fss_apply_delimit_range_

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
 *   This value is not reset and only additions are performed.
 *   When F_data_not is returned, this value is not altered.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but buffer.used is 0 (line is set to 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_count_lines_
  extern void f_fss_count_lines(const f_string_static_t buffer, const f_number_unsigned_t before, f_number_unsigned_t * const line, f_state_t * const state);
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
 * @param line
 *   The total lines found leading up to but not including before.
 *   This value is not reset and only additions are performed.
 *   When F_data_not is returned, this value is not altered.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but the range.start is greater than buffer.used or buffer.used is 0 (line is set to 0).
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_count_lines_range_
  extern void f_fss_count_lines_range(const f_string_static_t buffer, const f_range_t range, f_number_unsigned_t * const line, f_state_t * const state);
#endif // _di_f_fss_count_lines_range_

/**
 * Using the state, check that the status should return an error or not on invalid UTF-8.
 *
 * When f_fss_state_flag_utf_fail_on_valid_not_e is set, UTF-8 failures are returned as is.
 * When f_fss_state_flag_utf_fail_on_valid_not_e is unset, UTF-8 failures are returned with the error bit removed.
 *
 * This handles status codes (with error bit set):
 *   - F_complete_not_utf
 *   - F_utf_fragment
 *   - F_utf_not
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     Status is either directly passed through or the error bit is removed depending on state.flag.
 */
#ifndef _di_f_fss_fail_utf_
  extern void f_fss_fail_utf(f_state_t * const state);
#endif // _di_f_fss_fail_utf_

/**
 * Using the state, check that the status should return an error or not on invalid UTF-8.
 *
 * When f_fss_state_flag_utf_fail_on_valid_not_e is set, UTF-8 failures are returned as is.
 * When f_fss_state_flag_utf_fail_on_valid_not_e is unset, UTF-8 failures are replaced with F_false.
 *
 * This handles status codes (with error bit set):
 *   - F_complete_not_utf
 *   - F_utf_fragment
 *   - F_utf_not
 *
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     Status is either directly passed through or F_false is returned depending on state.flag.
 */
#ifndef _di_f_fss_fail_utf_to_false_
  extern void f_fss_fail_utf_to_false(f_state_t * const state);
#endif // _di_f_fss_fail_utf_to_false_

/**
 * Identify whether or not a character in the buffer is a combining (ASCII or UTF-8) character.
 *
 * This only checks if the given character is a combining character and does not check what this combines into.
 *
 * The combining characters combine from right to left.
 * It is recommended to use this after testing for other characters, such as f_fss_is_space() or f_fss_is_graph().
 * A combining character can follow any character, even if it is something like a control character.
 * This is unclear behavior so a simple strategy is to assume that a combining character results in a graph for anything except a non-combining zero-width character.
 * U+0020 followed by U+0301 would result in the combination of the two being considered a graph rather than a space.
 * Given that NULL characters are ignored by the general FSS standard, combining characters are not considered to combine into NULL.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_true if the character in the buffer is a combining character.
 *     F_false if the character in the buffer is not a combining character.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_utf_is_combining().
 *
 * @return
 *   F_true if the character in the buffer is a combining character.
 *   F_false if the character in the buffer is not a combining character.
 *   F_false is returned on any error.
 *
 * @see f_utf_is_combining()
 */
#ifndef _di_f_fss_is_combining_
  extern f_status_t f_fss_is_combining(const f_string_static_t buffer, const f_range_t range, f_state_t * const state);
#endif // _di_f_fss_is_combining_

/**
 * Identify whether or not a character in the buffer is a graph (ASCII or UTF-8) character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_true if the character in the buffer is a graph character.
 *     F_false if the character in the buffer is not a graph character.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_utf_is_graph().
 *
 * @return
 *   F_true if the character in the buffer is a graph character.
 *   F_false if the character in the buffer is not a graph character.
 *   F_false is returned on any error.
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_fss_is_graph_
  extern f_status_t f_fss_is_graph(const f_string_static_t buffer, const f_range_t range, f_state_t * const state);
#endif // _di_f_fss_is_graph_

/**
 * Identify whether or not a character in the buffer is a non-zero-width whitespace or non-zero-width control (ASCII or UTF-8) character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but nothing is processed.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_utf_is_control().
 *     Errors (with error bit) from: f_utf_is_whitespace().
 *     Errors (with error bit) from: f_utf_is_zero_width().
 *
 * @return
 *   F_true if the character in the buffer is a space character.
 *   F_false if the character in the buffer is not a space character.
 *   F_false is returned on any error.
 *
 * @see f_utf_is_control()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_is_space_
  extern f_status_t f_fss_is_space(const f_string_static_t buffer, const f_range_t range, f_state_t * const state);
#endif // _di_f_fss_is_space_

/**
 * Identify whether or not a character in the buffer is a zero-width (ASCII or UTF-8) character.
 *
 * The NULL character (U+0000) is a zero-width character.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The character at the start position will be checked against the graph.
 * @param header
 *   The header data to populate with results of this function.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_true if the character in the buffer is a zero-width character.
 *     F_false if the character in the buffer is not a zero-width character.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_utf_is_zero_width().
 *
 * @return
 *   F_true if the character in the buffer is a zero-width character.
 *   F_false if the character in the buffer is not a zero-width character.
 *   F_false is returned on any error.
 *
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_is_zero_width_
  extern f_status_t f_fss_is_zero_width(const f_string_static_t buffer, const f_range_t range, f_state_t * const state);
#endif // _di_f_fss_is_zero_width_

/**
 * Seek until an EOL character is reached.
 *
 * This does not check the character after the EOL is reached.
 * The character after an EOL should be checked to see if it is a combining character.
 * Combining characters after the EOL effectively make the EOL character a non-standard EOL.
 * For most, if not all, FSS standards, a combined EOL is not the same as a standard or normal EOL.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but buffer.used is 0, initial range.start is greater than range.stop, or initial range.start is greater than or equal to buffer.used.
 *     F_okay_eos on success and EOS was reached.
 *     F_okay_stop on success and stop point was reached.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_seek_to_eol_
  extern void f_fss_seek_to_eol(const f_string_dynamic_t buffer, f_range_t * const range, f_state_t * const state);
#endif // _di_f_fss_seek_to_eol_

/**
 * Skip past all delimit placeholders until a non-delimit placeholder is reached.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but buffer.used is 0, initial range.start is greater than range.stop, or initial range.start is greater than or equal to buffer.used.
 *     F_okay_eos on success and EOS was reached.
 *     F_okay_stop on success and stop point was reached.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_skip_past_delimit_
  extern void f_fss_skip_past_delimit(const f_string_static_t buffer, f_range_t * const range, f_state_t * const state);
#endif // _di_f_fss_skip_past_delimit_

/**
 * Skip past all white space, control characters, and zero-width characters, except newline '\n' (U+000A).
 *
 * If the first character in the given range is a combining character, then because this will not skip past anything.
 * This is because combining characters apply from right to left.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions in the buffer being processed.
 *   This increments range->start.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not on success but buffer.used is 0, initial range.start is greater than range.stop, or initial range.start is greater than or equal to buffer.used.
 *     F_okay_eol on success and EOL was reached.
 *     F_okay_eos on success and EOS was reached.
 *     F_okay_stop on success and stop point was reached.
 *
 *     F_complete_not_utf_eos (with error bit) if unable to get entire UTF-8 sequence due to EOS.
 *     F_complete_not_utf_start (with error bit) if the first character is a combining character.
 *     F_complete_not_utf_stop (with error bit) if unable to get entire UTF-8 sequence due to stop point reached.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_utf_is_combining().
 *     Errors (with error bit) from: f_utf_is_control().
 *     Errors (with error bit) from: f_utf_is_whitespace().
 *     Errors (with error bit) from: f_utf_is_zero_width().
 *
 * @see f_utf_is_combining()
 * @see f_utf_is_control()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_zero_width()
 */
#ifndef _di_f_fss_skip_past_space_
  extern void f_fss_skip_past_space(const f_string_static_t buffer, f_range_t * const range, f_state_t * const state);
#endif // _di_f_fss_skip_past_space_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_h

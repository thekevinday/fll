/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-0002 implementation.
 */
#ifndef _FL_fss_basic_list_h
#define _FL_fss_basic_list_h

// Libc includes.
#include <ctype.h>
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/fss.h>

// FLL-1 includes.
#include <fll/level_1/fss.h>
#include <fll/level_1/fss/basic.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read an fss-0002 content from a given string.
 *
 * This will record where delimit placeholders exist but will not apply the delimits.
 *
 * @param buffer
 *   The buffer to read from.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid content was found.
 * @param delimits
 *   A delimits array representing where delimits exist within the buffer.
 * @param comments
 *   An array of ranges representing where comments are found within any valid content.
 *   This only stores comments found within valid content only.
 *   The comment range will include the trailing newline.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 *
 *   Must not be NULL.
 *
 *   This alters state.status:
 *     F_fss_found_content on success and content was found (start location is at end of content).
 *     F_fss_found_content_not on success and no content was found (start location is after character designating this is not a content).
 *     F_okay_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *     F_okay_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *     F_data_not if buffer is empty (buffer.used is 0).
 *     F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *     F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *     F_end_not_group_eos if EOS was reached before the a group termination was reached.
 *     F_end_not_group_stop if stop point was reached before the a group termination was reached.
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_fss_is_space().
 *     Errors (with error bit) from: f_fss_seek_to_eol().
 *     Errors (with error bit) from: f_fss_skip_past_delimit().
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see f_fss_is_space()
 * @see f_fss_seek_to_eol()
 * @see f_fss_skip_past_delimit()
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_utf_buffer_increment()
 */
#ifndef _di_fl_fss_basic_list_content_read_
  extern void fl_fss_basic_list_content_read(const f_string_static_t buffer, f_range_t * const range, f_ranges_t * const found, f_number_unsigneds_t * const delimits, f_ranges_t * const comments, f_state_t * const state);
#endif // _di_fl_fss_basic_list_content_read_

/**
 * Write an fss-0002 content from a given string.
 *
 * This will write the given string range as a valid content.
 * Anything within this range will be escaped as necessary.
 *
 * The destination string may have NULLs.
 *
 * @param content
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param complete
 *   If f_fss_complete_none_e, then only the content is written.
 *   If f_fss_complete_next_e, then the content followed by any appropriate "next" character separating one content from the next, if applicable.
 *   If f_fss_complete_end_e, then the content followed by any appropriate "end" character designating the last content for some object, printing final newline, if applicable.
 *   If f_fss_complete_partial_e, this will write any appropriate open and close aspects of this content, except for the final newline.
 *   If f_fss_complete_full_e, this will write any appropriate open and close aspects of this content, including the final newline.
 * @param prepend
 *   A string of whitespace to prepend at the start of each line.
 *   This should only be whitespace, anything else could produce invalid content.
 *   Set the pointer address to 0 to disable.
 * @param range
 *   The start/stop location within the content string to write as an content.
 * @param destination
 *   The buffer where the content is written to.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 *
 *   Must not be NULL.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_okay_eol on success after reaching the end of the line.
 *     F_okay_eos on success after reaching the end of the buffer.
 *     F_data_not if content is empty (content.used is 0).
 *     F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *     F_data_not_stop no data to write due start location being greater than stop location.
 *     F_okay_stop on success after reaching stopping point.
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_fss_is_graph().
 *     Errors (with error bit) from: f_fss_skip_past_delimit().
 *     Errors (with error bit) from: f_fss_skip_past_space().
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see f_fss_is_graph()
 * @see f_fss_skip_past_delimit()
 * @see f_fss_skip_past_space()
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append()
 * @see f_utf_buffer_increment()
 */
#ifndef _di_fl_fss_basic_list_content_write_
  extern void fl_fss_basic_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t * const prepend, f_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state);
#endif // _di_fl_fss_basic_list_content_write_

/**
 * Read an fss-0002 object.
 *
 * This will record where delimit placeholders exist but will not apply the delimits.
 *
 * @param buffer
 *   The buffer to read from.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A location where a valid object was found.
 * @param delimits
 *   A delimits array representing where delimits exist within the buffer.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 *
 *   Must not be NULL.
 *
 *   This alters state.status:
 *     F_fss_found_object on success and object was found (start location is at end of object).
 *     F_fss_found_object_not on success and no object was found (start location is after character designating this is not an object).
 *     F_okay_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *     F_okay_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *     F_data_not if buffer is empty (buffer.used is 0).
 *     F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *     F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *     F_end_not_group_eos if EOS was reached before the a group termination was reached.
 *     F_end_not_group_stop if stop point was reached before the a group termination was reached.
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_fss_is_graph().
 *     Errors (with error bit) from: f_fss_is_space().
 *     Errors (with error bit) from: f_fss_is_zero_width().
 *     Errors (with error bit) from: f_fss_seek_to_eol().
 *     Errors (with error bit) from: f_fss_skip_past_delimit().
 *     Errors (with error bit) from: f_fss_skip_past_space().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see f_fss_is_graph()
 * @see f_fss_is_space()
 * @see f_fss_is_zero_width()
 * @see f_fss_seek_to_eol()
 * @see f_fss_skip_past_delimit()
 * @see f_fss_skip_past_space()
 * @see f_memory_array_increase_by()
 * @see f_utf_buffer_increment()
 */
#ifndef _di_fl_fss_basic_list_object_read_
  extern void fl_fss_basic_list_object_read(const f_string_static_t buffer, f_range_t * const range, f_range_t * const found, f_number_unsigneds_t * const delimits, f_state_t * const state);
#endif // _di_fl_fss_basic_list_object_read_

/**
 * Write an fss-0002 object.
 *
 * This will write the given string range as a valid object.
 * Anything within this range will be escaped as necessary.
 * This will stop if EOL is reached.
 *
 * The destination string may have NULLs.
 *
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param complete
 *   If f_fss_complete_none_e, then only the object name is written.
 *   If f_fss_complete_full_e, this will write any appropriate open and close aspects of this object.
 *   If f_fss_complete_full_trim_e, this will write any appropriate open and close aspects of this object, but will omit whitespace before and after the object.
 *   If f_fss_complete_partial_e, this will write any appropriate open and close aspects of this object.
 *   If f_fss_complete_partial_tim, this will write any appropriate open and close aspects of this object, but will omit whitespace before and after the object.
 * @param range
 *   The start/stop location within the object string to write as an object.
 * @param destination
 *   The buffer where the object is written to.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 *
 *   Must not be NULL.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_okay_eos on success after reaching the end of the buffer.
 *     F_data_not if object is empty (object.used is 0).
 *     F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *     F_data_not_stop no data to write due start location being greater than stop location.
 *     F_okay_stop on success after reaching stopping point.
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_okay_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_fss_is_graph().
 *     Errors (with error bit) from: f_fss_is_space().
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_fss_skip_past_delimit().
 *     Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see f_fss_is_graph()
 * @see f_fss_is_space()
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_fss_skip_past_delimit()
 * @see f_utf_buffer_increment()
 */
#ifndef _di_fl_fss_basic_list_object_write_
  extern void fl_fss_basic_list_object_write(const f_string_static_t object, const uint8_t complete, f_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state);
#endif // _di_fl_fss_basic_list_object_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_basic_list_h

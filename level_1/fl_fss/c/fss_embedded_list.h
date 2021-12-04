/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-0008 implementation.
 */
#ifndef _FL_fss_embedded_list_h
#define _FL_fss_embedded_list_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <fll/level_0/status.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/type.h>
#include <fll/level_0/utf.h>

// fll-1 includes
#include <fll/level_1/fss.h>
#include <fll/level_1/fss_basic.h>
#include <fll/level_1/fss_status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read an fss-0008 object.
 *
 * This will record where delimit placeholders exist but will not apply the delimits.
 *
 * @param buffer
 *   The buffer to read from.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions (@todo the additional parameters could be moved to a custom structure).
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A location where a valid object was found.
 * @param delimits
 *   A delimits array representing where delimits exist within the buffer.
 *
 * @return
 *   FL_fss_found_object on success and object was found (start location is at end of object).
 *   FL_fss_found_object_not on success and no object was found (start location is after character designating this is not an object).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_terminated_not_group_eos if EOS was reached before the a group termination was reached.
 *   F_terminated_not_group_stop if stop point was reached before the a group termination was reached.
 *
 *   F_array_too_large (with error bit) if a buffer is too large.
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_seek_to_eol().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_embedded_list_object_read_
  extern f_status_t fl_fss_embedded_list_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t *range, f_fss_object_t *found, f_fss_delimits_t *delimits);
#endif // _di_fl_fss_embedded_list_object_read_

/**
 * Read an fss-0008 content.
 *
 * This will record where delimit placeholders exist but will not apply the delimits.
 *
 * This operates on the assumption that found.array[0].array[found.array[0].used].content is the current content being processed.
 * Therefore the object for this content will also need to be found.array[0].array[found.array[0].used].object.
 * The object at depth 0 will not be populated, but all nested objects will be populated at their respective depth along with the content.
 *
 * @param buffer
 *   The buffer to read from.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions (@todo the additional parameters could be moved to a custom structure).
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
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
 *
 * @return
 *   FL_fss_found_content on success and content was found (start location is at end of content).
 *   FL_fss_found_content_not on success and no content was found (start location is after character designating this is not a content).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_terminated_not_group_eos if EOS was reached before the a group termination was reached.
 *   F_terminated_not_group_stop if stop point was reached before the a group termination was reached.
 *
 *   F_array_too_large (with error bit) if a buffer is too large.
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_embedded_list_content_read_
  extern f_status_t fl_fss_embedded_list_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t *range, f_fss_nest_t *found, f_fss_delimits_t *delimits, f_fss_comments_t *comments);
#endif // _di_fl_fss_embedded_list_content_read_

/**
 * Write an fss-0008 object from a given string.
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
 *   If f_fss_complete_none, then only the object name is written.
 *   If f_fss_complete_full, this will write any appropriate open and close aspects of this object.
 *   If f_fss_complete_full_trim, this will write any appropriate open and close aspects of this object, but will omit whitespace before and after the object.
 *   If f_fss_complete_partial, this will write any appropriate open and close aspects of this object.
 *   If f_fss_complete_partial_tim, this will write any appropriate open and close aspects of this object, but will omit whitespace before and after the object.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions (@todo the additional parameters could be moved to a custom structure).
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param range
 *   The start/stop location within the object string to write as an object.
 * @param destination
 *   The buffer where the object is written to.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_none_stop on success after reaching stopping point .
 *
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 */
#ifndef _di_fl_fss_embedded_list_object_write_string_
  extern f_status_t fl_fss_embedded_list_object_write_string(const f_string_static_t object, const uint8_t complete, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination);
#endif // _di_fl_fss_embedded_list_object_write_string_

/**
 * Write an fss-0008 content from a given string.
 *
 * This will write the given string range as a valid content.
 * Anything within this range will be escaped as necessary.
 *
 * The destination string may have NULLs.
 *
 * @param content
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param complete
 *   If f_fss_complete_none, then only the content is written.
 *   If f_fss_complete_next, then the content followed by any appropriate "next" character separating one content from the next, if applicable.
 *   If f_fss_complete_end, then the content followed by any appropriate "end" character designating the last content for some object, printing final newline, if applicable.
 *   If f_fss_complete_partial, this will write any appropriate open and close aspects of this content, except for the final newline.
 *   If f_fss_complete_full, this will write any appropriate open and close aspects of this content, including the final newline.
 * @param prepend
 *   A string of whitespace to prepend at the start of each line.
 *   This should only be whitespace, anything else could product invalid content.
 *   Set the pointer address to 0 to disable.
 * @param ignore
 *   An optional list of ranges within the string to ignore.
 *   These ranges are only checked/ignored if there is a valid nested object open or a valid nested object close.
 *   Any valid nested object open or valid nested object close inside an ingore range will not be escaped.
 *   Set the pointer address to 0 to disable.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions (@todo the additional parameters could be moved to a custom structure).
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param range
 *   The start/stop location within the content string to write as an content.
 * @param destination
 *   The buffer where the content is written to.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_none_stop on success after reaching stopping point.
 *
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 */
#ifndef _di_fl_fss_embedded_list_content_write_string_
  extern f_status_t fl_fss_embedded_list_content_write_string(const f_string_static_t content, const uint8_t complete, const f_string_static_t *prepend, const f_string_ranges_t *ignore, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination);
#endif // _di_fl_fss_embedded_list_content_write_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_embedded_list_h

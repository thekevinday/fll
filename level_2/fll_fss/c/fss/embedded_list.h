/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-0008 implementation.
 */
#ifndef _FLL_fss_embedded_list_h
#define _FLL_fss_embedded_list_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/fss.h>

// FLL-1 includes.
#include <fll/level_1/fss.h>
#include <fll/level_1/fss/embedded_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a buffer expected to be in fss-0008 format, getting all objects and their respective content.
 *
 * @param buffer
 *   The buffer to read from.
 * @param range
 *   The range within the buffer that is currently being read.
 * @param nest
 *   An nested set of all objects and content.
 * @param objects_delimits
 *   An array of delimits for objects detected during processing.
 *   The caller is expected to decide if and when to process them.
 * @param contents_delimits
 *   (optional) An array of delimits for contents detected during processing.
 *   The caller is expected to decide if and when to process them.
 *   Set pointer address to 0 and all delimits will instead utilize objects_delimits.
 * @param comments
 *   An array of ranges representing where comments are found within any valid content.
 *   This only stores comments found within valid content only.
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
 *   This alters state.status:
 *     F_okay on success (both valid object and valid content found with start location is at end of content).
 *     F_okay_eos on success after reaching the end of the buffer (both valid object and valid content found with start location is at end of buffer).
 *     F_okay_stop on success after reaching stopping point (both valid object and valid content found with start location is at stop point).
 *     F_data_not if buffer is empty (buffer.used is 0).
 *     F_data_not_eol if there is no data to write and EOL was reached.
 *     F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *     F_data_not_stop no data to write due start location being greater than stop location.
 *     F_fss_found_object_content_not on success and object was found but no content was found (start location is at end of object).
 *
 *     F_number_overflow (with error bit) if the maximum buffer size is reached.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_string_ranges_increase().
 *     Errors (with error bit) from: f_string_rangess_increase().
 *     Errors (with error bit) from: fl_fss_embedded_list_content_read().
 *     Errors (with error bit) from: fl_fss_embedded_list_object_read().
 *
 * @see f_memory_array_increase()
 * @see f_string_ranges_increase()
 * @see f_string_rangess_increase()
 * @see fl_fss_embedded_list_content_read()
 * @see fl_fss_embedded_list_object_read()
 */
#ifndef _di_fll_fss_embedded_list_read_
  extern void fll_fss_embedded_list_read(const f_string_static_t buffer, f_string_range_t * const range, f_fss_nest_t * const nest, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_string_ranges_t * const comments, f_state_t * const state);
#endif // _di_fll_fss_embedded_list_read_

/**
 * Write a single object string and content string to a buffer, using fss-0008 format.
 *
 * @param object
 *   A string representing the object.
 * @param content
 *   A string representing the content.
 * @param content_prepend
 *   A string to prepend at the start of each line in content, such as spaces.
 *   Set the pointer address to 0 to disable.
 * @param ignore
 *   An optional list of ranges within the string to ignore.
 *   These ranges are only checked/ignored if there is a valid nested object open or a valid nested object close.
 *   Any valid nested object open or valid nested object close inside an ingore range will not be escaped.
 *   Set the pointer address to 0 to disable.
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
 *   This alters state.status:
 *     F_okay on success.
 *     F_okay_eos on success after reaching the end of the buffer.
 *     F_okay_stop on success after reaching stopping point.
 *     F_data_not if object or contents are empty (either object.used or contents.used is 0).
 *     F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *     F_data_not_stop no data to write due start location being greater than stop location.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: fl_fss_embedded_list_content_write().
 *     Errors (with error bit) from: fl_fss_embedded_list_object_write().
 *
 * @see f_memory_array_increase()
 * @see fl_fss_embedded_list_content_write()
 * @see fl_fss_embedded_list_object_write()
 */
#ifndef _di_fll_fss_embedded_list_write_
  extern void fll_fss_embedded_list_write(const f_string_static_t object, const f_string_static_t content, const f_string_static_t *content_prepend, const f_string_ranges_t *ignore, f_string_dynamic_t * const destination, f_state_t * const state);
#endif // _di_fll_fss_embedded_list_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_embedded_list_h

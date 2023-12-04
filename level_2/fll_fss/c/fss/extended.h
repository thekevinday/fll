/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-0001 implementation.
 */
#ifndef _FLL_fss_extended_h
#define _FLL_fss_extended_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/fss.h>

// FLL-1 includes.
#include <fll/level_1/fss.h>
#include <fll/level_1/fss/extended.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a buffer expected to be in fss-0001 format, getting all objects and their respective content.
 *
 * @param buffer
 *   The buffer to read from.
 * @param range
 *   The range within the buffer that is currently being read.
 * @param objects
 *   This will be populated with all valid objects found.
 * @param contents
 *   This will be populated with all valid contents found.
 * @param objects_quoted
 *   (optional) An array mapped to each object in objects representing the quote type discovered (from the f_fss_quote_type_*_e), if any.
 *   Set the pointer address to 0 to disable.
 * @param contents_quoted
 *   (optional) An array mapped to each content in objects representing the quote type discovered (from the f_fss_quote_type_*_e), if any.
 *   Set the pointer address to 0 to disable.
 * @param objects_delimits
 *   An array of delimits for objects detected during processing.
 *   The caller is expected to decide if and when to process them.
 * @param contents_delimits
 *   (optional) An array of delimits for contents detected during processing.
 *   The caller is expected to decide if and when to process them.
 *   Set pointer address to 0 and all delimits will instead utilize objects_delimits.
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
 *     F_okay_stop on success after reaching stopping point.
 *     F_okay_eos on success after reaching the end of the buffer.
 *     F_data_not if buffer is empty (buffer.used is 0).
 *     F_data_not_stop no data to write due start location being greater than stop location.
 *     F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *     F_data_not_eol if there is no data to write and EOL was reached.
 *
 *     F_number_overflow (with error bit) if the maximum buffer size is reached.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: fl_fss_extended_content_read().
 *     Errors (with error bit) from: fl_fss_extended_object_read().
 *
 * @see f_memory_array_increase()
 * @see fl_fss_extended_content_read()
 * @see fl_fss_extended_object_read()
 */
#ifndef _di_fll_fss_extended_read_
  extern void fll_fss_extended_read(const f_string_static_t buffer, f_range_t * const range, f_ranges_t * const objects, f_rangess_t * const contents, f_uint8s_t * const objects_quoted, f_uint8ss_t * const contents_quoted, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_state_t * const state);
#endif // _di_fll_fss_extended_read_

/**
 * Write a single object string and content string to a buffer, using fss-0001 format.
 *
 * @param object
 *   A string representing the object.
 * @param contents
 *   An array of strings representing multiple content to write.
 * @param quote
 *   If 0, then double quotes are auto-inserted, when required.
 *   Otherwise, this is quote character to wrap the object in when writing.
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
 *     Errors (with error bit) from: fl_fss_extended_content_write().
 *     Errors (with error bit) from: fl_fss_extended_object_write().
 *
 * @see f_memory_array_increase()
 * @see fl_fss_extended_content_write()
 * @see fl_fss_extended_object_write()
 */
#ifndef _di_fll_fss_extended_write_
  extern void fll_fss_extended_write(const f_string_static_t object, const f_string_statics_t contents, const uint8_t quote, f_string_dynamic_t * const destination, f_state_t * const state);
#endif // _di_fll_fss_extended_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_extended_h

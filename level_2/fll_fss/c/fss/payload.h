/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-000e implementation.
 */
#ifndef _FLL_fss_payload_h
#define _FLL_fss_payload_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/fss.h>

// FLL-1 includes.
#include <fll/level_1/fss.h>
#include <fll/level_1/fss/basic_list.h>
#include <fll/level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a buffer expected to be in fss-000e format, getting all objects and their respective content.
 *
 * This processes only the outermost part and specially handles the payload.
 * The inner data, such as the fss-0001 inside of the "header", should be directly processed via the appropriate function.
 *
 * The "payload" Object is required and if it is not file, this function returns with the error flag set.
 *
 * @param buffer
 *   The buffer to read from.
 * @param state
 A state for providing flags and handling interrupts during long running operations.
 *   There is no print_error().
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param range
 *   The range within the buffer that is currently being read.
 * @param objects
 *   This will be populated with all valid objects found.
 * @param contents
 *   This will be populated with all valid contents found.
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
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_none_stop on success after reaching stopping point.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *
 *   F_fss_found_object_content_not (with error bit) When payload Content is missing.
 *   F_data_not_eos (with error bit) no data to write due start location being greater than or equal to buffer size, except that no "payload" is found.
 *   F_data_not_stop (with error bit) no data to write due start location being greater than stop location, except that no "payload" is found.
 *   F_none (with error bit) on success, except that no "payload" is found.
 *   F_none_eos (with error bit) on success after reaching the end of the buffer, except that no "payload" is found.
 *   F_none_stop (with error bit) on success after reaching stopping point, except that no "payload" is found.
 *   F_number_overflow (with error bit) if the maximum buffer size is reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_fss_basic_list_content_read().
 *   Errors (with error bit) from: fl_fss_basic_list_object_read().
 *
 *   F_number_overflow (with error bit) if the maximum buffer size is reached.
 *
 *   Errors (with error bit) from: f_string_ranges_increase().
 *   Errors (with error bit) from: f_string_rangess_increase().
 *   Errors (with error bit) from: f_uint8s_increase().
 *   Errors (with error bit) from: fl_fss_basic_list_content_read().
 *   Errors (with error bit) from: fl_fss_basic_list_object_read().
 *
 * @see f_string_ranges_increase()
 * @see f_string_rangess_increase()
 * @see f_uint8s_increase()
 * @see fl_fss_basic_list_content_read()
 * @see fl_fss_basic_list_object_read()
 */
#ifndef _di_fll_fss_payload_read_
  extern f_status_t fll_fss_payload_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_objects_t * const objects, f_fss_contents_t * const contents, f_fss_delimits_t * const objects_delimits, f_fss_delimits_t * const contents_delimits, f_fss_comments_t * const comments);
#endif // _di_fll_fss_payload_read_

/**
 * Write a single object string and content string to a buffer, using fss-0002 format.
 *
 * This processes only the outermost part and specially handles the payload.
 * The inner data, such as the fss-0001 inside of the "header", should be directly processed via the appropriate function.
 *
 * If the Object is "payload", then the Content is written directly without prcessing or escaping.
 *
 * @param object
 *   A string representing the object.
 * @param content
 *   A string representing the content.
 * @param trim
 *   If TRUE, the Object is passed f_fss_complete_full_trim_e.
 *   If FALSE, the Object is passed f_fss_complete_full_e.
 *   The Content is always passed f_fss_complete_full_e.
 * @param content_prepend
 *   A string to prepend at the start of each line in content, such as spaces.
 *   This will not be prepended for the Object "payload".
 *   Set the pointer address to 0 to disable.
 * @param state
 A state for providing flags and handling interrupts during long running operations.
 *   There is no print_error().
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param destination
 *   The buffer to append to.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_none_stop on success after reaching stopping point.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase().
 *   Errors (with error bit) from: fl_fss_basic_list_content_write().
 *   Errors (with error bit) from: fl_fss_basic_list_object_write().
 *
 * @see f_string_dynamic_increase()
 * @see fl_fss_basic_list_content_write()
 * @see fl_fss_basic_list_object_write()
 */
#ifndef _di_fll_fss_payload_write_
  extern f_status_t fll_fss_payload_write(const f_string_static_t object, const f_string_static_t content, const bool trim, const f_string_static_t * const content_prepend, f_state_t state, f_string_dynamic_t * const destination);
#endif // _di_fll_fss_payload_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_payload_h

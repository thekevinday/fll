/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0003 implementation.
 */
#ifndef _FLL_fss_extended_list_h
#define _FLL_fss_extended_list_h

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_extended_list.h>
#include <level_1/fss_status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a buffer expected to be in fss-0003 format, getting all objects and their respective content.
 *
 * This does not utilize recursion and has a max content depth of 1, see fss-0008 (Embedded List) for that purpose.
 *
 * @param buffer
 *   The buffer to read from.
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
 *   F_none on success (both valid object and valid content found with start location is at end of content).
 *   F_none_eos on success after reaching the end of the buffer (both valid object and valid content found with start location is at end of buffer).
 *   F_none_stop on success after reaching stopping point (both valid object and valid content found with start location is at stop point).
 *   F_data_not_eol if there is no data to write and EOL was reached (@todo: review related code and detemine what this is doing).
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_number_overflow (with error bit) if the maximimum buffer size is reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_terminated_not_eos (with error bit) if end of buffer is reached before a closing bracket is found (object was found).
 *   F_terminated_not_nest_eos (with error bit) if end of buffer is reached while inside a nested list before a closing bracket is found (object was found).
 *   F_terminated_not_nest_stop (with error bit) if stop location is reached while inside a nested list before a closing bracket is found (object was found).
 *   F_terminated_not_stop (with error bit) if stop location is reached before a closing bracket is found (object was found).
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   FL_fss_found_object_content_not on success and object was found but no content was found (start location is at end of object).
 *
 *   Errors (with error bit) from: fl_fss_extended_list_content_read().
 *   Errors (with error bit) from: fl_fss_extended_list_object_read().
 */
#ifndef _di_fll_fss_extended_list_read_
  extern f_status_t fll_fss_extended_list_read(const f_string_static_t buffer, f_string_range_t *range, f_fss_objects_t *objects, f_fss_contents_t *contents, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits, f_fss_comments_t *comments);
#endif // _di_fll_fss_extended_list_read_

/**
 * Write a single object string and content string to a buffer, using fss-0003 format.
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
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_none_stop on success after reaching stopping point.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: fl_fss_extended_list_content_write_string().
 *   Errors (with error bit) from: fl_fss_extended_list_object_write_string().
 *   Errors (with error bit) from: fl_string_dynamic_increase_by().
 */
#ifndef _di_fll_fss_extended_list_write_string_
  extern f_status_t fll_fss_extended_list_write_string(const f_string_static_t object, const f_string_static_t content, const f_string_static_t *content_prepend, const f_string_ranges_t *ignore, f_string_dynamic_t *destination);
#endif // _di_fll_fss_extended_list_write_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_extended_list_h

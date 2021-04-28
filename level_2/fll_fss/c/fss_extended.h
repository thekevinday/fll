/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0001 implementation.
 */
#ifndef _FLL_fss_extended_h
#define _FLL_fss_extended_h

// fll-0 includes
#include <fll/level_0/status.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/type.h>

// fll-1 includes
#include <fll/level_1/fss.h>
#include <fll/level_1/fss_status.h>
#include <fll/level_1/fss_extended.h>

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
 *   (optional) An array mapped to each object in objects representing the quote discovered, if any.
 *   Set the pointer address to 0 to disable.
 * @param contents_quoted
 *   (optional) An array mapped to each content in contents representing the quote discovered, if any.
 *   Set the pointer address to 0 to disable.
 * @param objects_delimits
 *   An array of delimits for objects detected during processing.
 *   The caller is expected to decide if and when to process them.
 * @param contents_delimits
 *   (optional) An array of delimits for contents detected during processing.
 *   The caller is expected to decide if and when to process them.
 *   Set pointer address to 0 and all delimits will instead utilize objects_delimits.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success after reaching stopping point .
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_data_not_eol if there is no data to write and EOL was reached (@todo: review related code and detemine what this is doing).
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_number_overflow (with error bit) if the maximimum buffer size is reached.
 *
 *   Errors (with error bit) from: fl_fss_extended_content_read().
 *   Errors (with error bit) from: fl_fss_extended_object_read().
 */
#ifndef _di_fll_fss_extended_read_
  extern f_status_t fll_fss_extended_read(const f_string_static_t buffer, f_string_range_t *range, f_fss_objects_t *objects, f_fss_contents_t *contents, f_fss_quotes_t *objects_quoted, f_fss_quotess_t *contents_quoted, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits);
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
 *   Otherwise, this is the type of quote to wrap the object in when writing.
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
 *   Errors (with error bit) from: fl_fss_extended_content_write_string().
 *   Errors (with error bit) from: fl_fss_extended_object_write_string().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 */
#ifndef _di_fll_fss_extended_write_string_
  extern f_status_t fll_fss_extended_write_string(const f_string_static_t object, const f_string_statics_t contents, const f_fss_quote_t quote, f_string_dynamic_t *destination);
#endif // _di_fll_fss_extended_write_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_extended_h

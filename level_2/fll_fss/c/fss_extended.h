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
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_status.h>
#include <level_1/fss_extended.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a buffer expected to be in fss-0001 format, getting all objects and their respective content.
 *
 * @param buffer
 *   The buffer to read from.
 * @param location
 *   The location within the buffer that is currently being read.
 * @param objects
 *   This will be populated with all valid objects found.
 * @param contents
 *   This will be populated with all valid contents found.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success after reaching stopping point .
 *   f_none_on_eos on success after reaching the end of the buffer.
 *   f_no_data_on_stop no data to write due start location being greater than stop location.
 *   f_no_data_on_eos no data to write due start location being greater than or equal to buffer size.
 *   f_no_data_on_eol if there is no data to write and EOL was reached (@todo: review related code and detemine what this is doing).
 *   f_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   f_invalid_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   f_reallocation_error (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) if the maximimum buffer size is reached.
 */
#ifndef _di_fll_fss_extended_read_
  extern f_return_status fll_fss_extended_read(f_string_dynamic *buffer, f_string_location *input, f_fss_objects *objects, f_fss_contents *contents);
#endif // _di_fll_fss_extended_read_

/**
 * Write a single object string and content string to a buffer, using fss-0001 format.
 *
 * @param object
 *   A string representing the object.
 * @param contents
 *   An array of strings representing multiple content to write.
 * @param buffer
 *   The buffer to write to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success after reaching stopping point .
 *   f_none_on_eos on success after reaching the end of the buffer.
 *   f_no_data_on_stop no data to write due start location being greater than stop location.
 *   f_no_data_on_eos no data to write due start location being greater than or equal to buffer size.
 *   f_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   f_invalid_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   f_reallocation_error (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fll_fss_extended_write_
  extern f_return_status fll_fss_extended_write(const f_string_dynamic object, const f_string_dynamics contents, f_string_dynamic *buffer);
#endif // _di_fll_fss_extended_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_extended_h

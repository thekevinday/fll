/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0000 implementation.
 */
#ifndef _FL_fss_basic_h
#define _FL_fss_basic_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/memory.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read an fss-0000 object.
 *
 * This will update the buffer at the given range with any placeholders to unescape any escaped data.
 * Calling this more than once on the same buffer range could result in multiple unescaping.
 *
 * @param buffer
 *   The buffer to read from.
 *   This will be updated with delimit placeholders as it is being processed.
 * @param location
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid object was found.
 *
 * @return
 *   fl_fss_found_object on success and object was found (start location is at end of object).
 *   fl_fss_found_no_object on success and no object was found (start location is after character designating this is not an object).
 *   f_none_on_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   f_none_on_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   f_no_data_on_stop no data found after reaching stopping point (essentially only comments are found).
 *   f_no_data_on_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   f_invalid_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_basic_object_read_
  extern f_return_status fl_fss_basic_object_read(f_string_dynamic *buffer, f_string_location *location, f_fss_object *found);
#endif // _di_fl_fss_basic_object_read_

/**
 * Read an fss-0000 content.
 *
 * This will update the buffer at the given range with any placeholders to unescape any escaped data.
 * Calling this more than once on the same buffer range could result in multiple unescaping.
 *
 * @param buffer
 *   The buffer to read from.
 *   This will be updated with delimit placeholders as it is being processed.
 * @param location
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid content was found.
 *
 * @return
 *   fl_fss_found_content on success and content was found (start location is at end of content).
 *   fl_fss_found_no_content on success and no content was found (start location is after character designating this is not a content).
 *   f_none_on_stop on success after reaching stopping point (a valid content is not yet confirmed).
 *   f_none_on_eos on success after reaching the end of the buffer (a valid content is not yet confirmed).
 *   f_no_data_on_stop no data found after reaching stopping point (essentially only comments are found).
 *   f_no_data_on_eos no content found after reaching the end of the buffer (essentially only comments are found).
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   f_invalid_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_basic_content_read_
  extern f_return_status fl_fss_basic_content_read(f_string_dynamic *buffer, f_string_location *location, f_fss_content *found);
#endif // _di_fl_fss_basic_content_read_

/**
 * Write an fss-0000 object.
 *
 * This will write the given string range as a valid object.
 * Anything within this range will be escaped as necessary.
 * This will stop if EOL is reached.
 *
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param location
 *   The start/stop location within the object string to write as an object.
 * @param buffer
 *   The buffer where the object is written to.
 *   This will be auto-incremented and must not be a static string.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success after reaching stopping point .
 *   f_none_on_eos on success after reaching the end of the buffer.
 *   f_no_data_on_stop no data to write due start location being greater than stop location.
 *   f_no_data_on_eos no data to write due start location being greater than or equal to buffer size.
 *   f_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   f_invalid_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_basic_object_write_
  extern f_return_status fl_fss_basic_object_write(f_string_dynamic *buffer, const f_string_dynamic object, f_string_location *location);
#endif // _di_fl_fss_basic_object_write_

/**
 * Write an fss-0000 content.
 *
 * This will write the given string range as a valid content.
 * Anything within this range will be escaped as necessary.
 *
 * @param content
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param location
 *   The start/stop location within the content string to write as an content.
 * @param buffer
 *   The buffer where the content is written to.
 *   This will be auto-incremented and must not be a static string.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success after reaching stopping point .
 *   f_none_on_eos on success after reaching the end of the buffer.
 *   f_no_data_on_stop no data to write due start location being greater than stop location.
 *   f_no_data_on_eos no data to write due start location being greater than or equal to buffer size.
 *   f_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   f_invalid_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_fss_basic_content_write_
  extern f_return_status fl_fss_basic_content_write(f_string_dynamic *buffer, const f_string_dynamic content, f_string_location *location);
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_basic_h

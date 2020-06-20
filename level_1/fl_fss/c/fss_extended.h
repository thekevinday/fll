/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0001 implementation.
 */
#ifndef _FL_fss_extended_h
#define _FL_fss_extended_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read an fss-0001 object.
 *
 * This will update the buffer at the given range with any placeholders to unescape any escaped data.
 * Calling this more than once on the same buffer range could result in multiple unescaping.
 *
 * @param buffer
 *   The buffer to read from.
 *   This will be updated with delimit placeholders as it is being processed.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid object was found.
 *
 * @return
 *   FL_fss_found_object on success and object was found (start location is at end of object).
 *   FL_fss_found_object_not on success and no object was found (start location is after character designating this is not an object).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_unterminated_group_eos (with warning bit) if EOS was reached before the a group termination was reached.
 *   F_unterminated_group_stop (with warning bit) if stop point was reached before the a group termination was reached.
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors from (with error bit): f_fss_increment_buffer().
 *   Errors from (with error bit): f_fss_is_graph().
 *   Errors from (with error bit): f_fss_is_space().
 *   Errors from (with error bit): f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_extended_object_read_
  extern f_return_status fl_fss_extended_object_read(f_string_dynamic *buffer, f_string_range *range, f_fss_object *found);
#endif // _di_fl_fss_extended_object_read_

/**
 * Read an fss-0001 content.
 *
 * This will update the buffer at the given range with any placeholders to unescape any escaped data.
 * Calling this more than once on the same buffer range could result in multiple unescaping.
 *
 * @param buffer
 *   The buffer to read from.
 *   This will be updated with delimit placeholders as it is being processed.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid content was found.
 *
 * @return
 *   FL_fss_found_content on success and content was found (start location is at end of content).
 *   FL_fss_found_content_not on success and no content was found (start location is after character designating this is not a content).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_unterminated_group_eos (with warning bit) if EOS was reached before the a group termination was reached.
 *   F_unterminated_group_stop (with warning bit) if stop point was reached before the a group termination was reached.
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors from (with error bit): f_fss_increment_buffer().
 *   Errors from (with error bit): f_fss_is_graph().
 *   Errors from (with error bit): f_fss_is_space().
 *   Errors from (with error bit): f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_extended_content_read_
  extern f_return_status fl_fss_extended_content_read(f_string_dynamic *buffer, f_string_range *range, f_fss_content *found);
#endif // _di_fl_fss_extended_content_read_

/**
 * Write an fss-0001 object.
 *
 * This will write the given string range as a valid object.
 * Anything within this range will be escaped as necessary.
 * This will stop if EOL is reached.
 *
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param range
 *   The start/stop location within the object string to write as an object.
 * @param buffer
 *   The buffer where the object is written to.
 *   This will be auto-incremented and must not be a static string.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_none_stop on success after reaching stopping point .
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors from (with error bit): f_fss_increment_buffer().
 */
#ifndef _di_fl_fss_extended_object_write_
  extern f_return_status fl_fss_extended_object_write(const f_string_static object, f_string_range *range, f_string_dynamic *buffer);
#endif // _di_fl_fss_extended_object_write_

/**
 * Write an fss-0001 content.
 *
 * This will write the given string range as a valid content.
 * Anything within this range will be escaped as necessary.
 *
 * @param content
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param range
 *   The start/stop location within the content string to write as an content.
 * @param buffer
 *   The buffer where the content is written to.
 *   This will be auto-incremented and must not be a static string.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_none_stop on success after reaching stopping point .
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors from (with error bit): f_fss_increment_buffer().
 */
#ifndef _di_fl_fss_extended_content_write_
  extern f_return_status fl_fss_extended_content_write(const f_string_static content, f_string_range *range, f_string_dynamic *buffer);
#endif // _di_fl_fss_extended_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_extended_h

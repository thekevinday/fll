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
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid object was found.
 * @param quote
 *   This will store whether or not this object is quote and what quote is in use.
 *   Set pointer address to 0 to not use.
 *
 * @return
 *   FL_fss_found_object on success and object was found (start location is at end of object).
 *   FL_fss_found_object_not on success and no object was found (start location is after character designating this is not an object).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_unterminated_group_eos if EOS was reached before the a group termination was reached.
 *   F_unterminated_group_stop if stop point was reached before the a group termination was reached.
 *   F_buffer_too_large (with error bit) if a buffer is too large.
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_basic_object_read_
  extern f_return_status fl_fss_basic_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quote);
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
 *   F_unterminated_group_eos if EOS was reached before the a group termination was reached.
 *   F_unterminated_group_stop if stop point was reached before the a group termination was reached.
 *   F_buffer_too_large (with error bit) if a buffer is too large.
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_basic_content_read_
  extern f_return_status fl_fss_basic_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found);
#endif // _di_fl_fss_basic_content_read_

/**
 * Write an fss-0000 object.
 *
 * This will write the given string range as a valid object.
 * Anything within this range will be escaped as necessary.
 * This will stop if EOL is reached.
 *
 * The destination string may have NULLs.
 *
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param quote
 *   If 0, then double quotes are auto-inserted, when required.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param complete
 *   If f_fss_complete_none, then only the object name is written.
 *   If f_fss_complete_partial, this will write any appropriate open and close aspects of this object.
 *   If f_fss_complete_full, this will write any appropriate open and close aspects of this object.
 * @param range
 *   The start/stop location within the object string to write as an object.
 * @param destination
 *   The buffer where the object is written to.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_none_stop on success after reaching the range stop.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the destination.
 *
 *   Errors (with error bit) from: f_fss_is_space().
 */
#ifndef _di_fl_fss_basic_object_write_
  extern f_return_status fl_fss_basic_object_write(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination);
#endif // _di_fl_fss_basic_object_write_

/**
 * Write an fss-0000 content.
 *
 * This will write the given string range as a valid content.
 * Anything within this range will be escaped as necessary.
 *
 * The destination string may have NULLs.
 *
 * @param content
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param complete
 *   If f_fss_complete_none, then only the object name is written.
 *   If f_fss_complete_partial, this will write any appropriate open and close aspects of this object, except for the final newline.
 *   If f_fss_complete_full, this will write any appropriate open and close aspects of this object, including the final newline.
 * @param range
 *   The start/stop location within the content string to write as an content.
 * @param destination
 *   The buffer where the content is written to.
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_none_stop on success after reaching the range stop.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the destination.
 */
#ifndef _di_fl_fss_basic_content_write_
  extern f_return_status fl_fss_basic_content_write(const f_string_static_t content, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination);
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_basic_h

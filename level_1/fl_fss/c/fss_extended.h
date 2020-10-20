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
 * This will record where delimit placeholders exist but will not apply the delimits.
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
 * @param quoted
 *   This will store whether or not this object is quoted and what quote is in use.
 *   Set pointer address to 0 to not use.
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
 *   F_unterminated_group_eos if EOS was reached before the a group termination was reached.
 *   F_unterminated_group_stop if stop point was reached before the a group termination was reached.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_is_zero_width().
 *   Errors (with error bit) from: f_fss_seek_to_eol().
 *   Errors (with error bit) from: f_fss_skip_past_delimit().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_extended_object_read_
  extern f_return_status fl_fss_extended_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quoted, f_fss_delimits_t *delimits);
#endif // _di_fl_fss_extended_object_read_

/**
 * Read an fss-0001 content.
 *
 * This will record where delimit placeholders exist but will not apply the delimits.
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
 * @param quotes
 *   An array of quotes designating whether or not content is quoted and what quote is in use.
 *   Set pointer address to 0 to not use.
 * @param delimits
 *   A delimits array representing where delimits exist within the buffer.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_is_zero_width().
 *   Errors (with error bit) from: f_fss_skip_past_delimit().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 */
#ifndef _di_fl_fss_extended_content_read_
  extern f_return_status fl_fss_extended_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found, f_fss_quotes_t *quotes, f_fss_delimits_t *delimits);
#endif // _di_fl_fss_extended_content_read_

/**
 * Write an fss-0001 object from a given string.
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
 *   If f_fss_complete_full, this will write any appropriate open and close aspects of this object.
 *   If f_fss_complete_partial, this will write any appropriate open and close aspects of this object.
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
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the destination.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_utf_buffer_increment().
 */
#ifndef _di_fl_fss_extended_object_write_string_
  extern f_return_status fl_fss_extended_object_write_string(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination);
#endif // _di_fl_fss_extended_object_write_string_

/**
 * Write an fss-0001 content from a given string.
 *
 * This will write the given string range as a valid content.
 * Anything within this range will be escaped as necessary.
 *
 * The destination string may have NULLs.
 *
 * @param content
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param quote
 *   If 0, then double quotes are auto-inserted, when required.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param complete
 *   If f_fss_complete_none, then only the content is written.
 *   If f_fss_complete_next, then the content followed by any appropriate "next" character separating one content from the next, if applicable.
 *   If f_fss_complete_end, then the content followed by any appropriate "end" character designating the last content for some object, printing final newline, if applicable.
 *   If f_fss_complete_partial, this will write any appropriate open and close aspects of this content, except for the final newline.
 *   If f_fss_complete_full, this will write any appropriate open and close aspects of this content, including the final newline.
 * @param range
 *   The start/stop location within the content string to write as an content.
 * @param destination
 *   The buffer where the content is written to.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success after reaching the end of the buffer.
 *   F_none_stop on success after reaching the range stop.
 *   F_data_not_stop no data to write due start location being greater than stop location.
 *   F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the destination.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_utf_buffer_increment().
 */
#ifndef _di_fl_fss_extended_content_write_string_
  extern f_return_status fl_fss_extended_content_write_string(const f_string_static_t content, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination);
#endif // _di_fl_fss_extended_content_write_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_extended_h

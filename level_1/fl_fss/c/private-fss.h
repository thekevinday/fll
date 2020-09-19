/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_fss_h
#define _PRIVATE_FL_fss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fl_fss_basic_object_read().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *   An array of delimits detected during processing.
 *   The caller is expected to decide if and when to process them.
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
 *
 * @see fl_fss_basic_object_read()
 * @see fl_fss_extended_object_read()
 */
#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)
  extern f_return_status private_fl_fss_basic_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quoted_t *quoted, f_string_lengths_t *delimits) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)

/**
 * Private implementation of fl_fss_basic_object_write().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param quoted
 *   If 0, then double quotes are auto-inserted, if needed.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param range
 *   The start/stop location within the object string to write as an object.
 * @param destination
 *   The buffer where the object is written to.
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
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see fl_fss_basic_object_write()
 * @see fl_fss_extended_object_write()
 */
#if !defined(fl_fss_basic_object_write) || !defined(fl_fss_extended_object_write)
  extern f_return_status private_fl_fss_basic_object_write(const f_string_static_t object, const f_fss_quoted_t quoted, f_string_range_t *range, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(fl_fss_basic_object_write) || !defined(fl_fss_extended_object_write)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_h

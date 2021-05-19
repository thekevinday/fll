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
 * Trim a given object used by the basic and extended object write functions.
 *
 * @param quote
 *   If 0, then double quotes are auto-inserted, when required.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param used_start
 *   The destination.used value before any operations were perfomed.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param destination
 *   The buffer where the object is written to.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *
 *   Errors (with error bit) from: f_fss_is_space().
 *
 * @see fl_fss_basic_object_write_string()
 * @see fl_fss_extended_object_write_string()
 */
#if !defined(_di_fl_fss_basic_object_write_string_) || !defined(_di_fl_fss_extended_object_write_string_)
  extern f_status_t private_fl_fss_basic_write_object_trim(const f_fss_quote_t quote, const f_array_length_t used_start, f_state_t state, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_fl_fss_basic_object_write_string_) || !defined(_di_fl_fss_extended_object_write_string_)

/**
 * Add all bytes to destination until stop point, buffer end, or EOL.
 *
 * @param buffer
 *   The buffer to seek through.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param range
 *   The start/stop location within the buffer string to process.
 * @param destination
 *   The buffer where the bytes are written to.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase().
 *
 * @see fl_fss_basic_list_content_write_string()
 * @see fl_fss_embedded_list_content_write_string()
 * @see fl_fss_extended_list_content_write_string()
 * @see f_string_dynamic_increase()
 */
#if !defined(_di_fl_fss_basic_list_content_write_string_) || !defined(_di_fl_fss_extended_list_content_write_string_) || !defined(_di_fl_fss_embedded_list_content_write_string_)
  extern f_status_t private_fl_fss_basic_list_write_add_until_end(const f_string_static_t buffer, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_fl_fss_basic_list_content_write_string_) || !defined(_di_fl_fss_extended_list_content_write_string_) || !defined(_di_fl_fss_embedded_list_content_write_string_)

/**
 * Trim a given object used by the basic list and extended list object write functions.
 *
 * @param used_start
 *   The destination.used value before any operations were performed.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param destination
 *   The buffer where the object is written to.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *
 *   Errors (with error bit) from: f_fss_is_space().
 *
 * @see fl_fss_basic_list_object_write_string()
 * @see fl_fss_extended_list_object_write_string()
 */
#if !defined(_di_fl_fss_basic_list_object_write_string_) || !defined(_di_fl_fss_extended_list_object_write_string_)
  extern f_status_t private_fl_fss_basic_list_write_object_trim(const f_array_length_t used_start, f_state_t state, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(_di_fl_fss_basic_list_object_write_string_) || !defined(_di_fl_fss_extended_list_object_write_string_)

/**
 * Private implementation of fl_fss_basic_object_read().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param buffer
 *   The buffer to read from.
 * @param object_as
 *   If TRUE, then this operate as an Object.
 *   IF FALSE, then this operates as a Content.
 *
 *   As Object, this checks if the first graph character is a comment character '#', or an escaped comment character '#'.
 *   As Content, this does nothing special in regards to a leading '#'.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
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
 *   F_terminated_not_group_eos if EOS was reached before the a group termination was reached.
 *   F_terminated_not_group_stop if stop point was reached before the a group termination was reached.
 *
 *   F_array_too_large (with error bit) if a buffer is too large.
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_is_zero_width().
 *   Errors (with error bit) from: f_fss_skip_past_delimit().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 *
 * @see fl_fss_basic_object_read()
 * @see fl_fss_extended_object_read()
 * @see fl_fss_extended_content_read()
 */
#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)
  extern f_status_t private_fl_fss_basic_read(const f_string_static_t buffer, const bool object_as, f_state_t state, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quoted, f_fss_delimits_t *delimits) f_attribute_visibility_internal;
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)

/**
 * Private implementation of fl_fss_basic_object_write_string().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * Note: this does not attempt to "complete" the object.
 *
 * @param object_as
 *   If TRUE, then this operate as an Object.
 *   IF FALSE, then this operates as a Content.
 *
 *   As Object, this checks if the first graph character is a comment character '#', or an escaped comment character '#'.
 *   As Content, this does nothing special in regards to a leading '#'.
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param quoted
 *   If 0, then double quotes are auto-inserted, if needed.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions.
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
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
 *
 *   F_complete_not_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the destination.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see fl_fss_basic_object_write_string()
 * @see fl_fss_extended_object_write_string()
 * @see fl_fss_extended_content_write_string()
 */
#if !defined(fl_fss_basic_object_write_string) || !defined(fl_fss_extended_object_write_string) || !defined(_di_fl_fss_extended_content_write_string_)
  extern f_status_t private_fl_fss_basic_write(const bool object_as, const f_string_static_t object, const f_fss_quote_t quoted, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination) f_attribute_visibility_internal;
#endif // !defined(fl_fss_basic_object_write_string) || !defined(fl_fss_extended_object_write_string) || !defined(_di_fl_fss_extended_content_write_string_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_h

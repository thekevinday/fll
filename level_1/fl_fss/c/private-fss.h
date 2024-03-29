/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
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
 * Add all bytes to destination until stop point, buffer end, or EOL.
 *
 * @param buffer
 *   The buffer to seek through.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
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
 * @see f_string_dynamic_increase()
 * @see fl_fss_basic_list_content_write()
 * @see fl_fss_embedded_list_content_write()
 * @see fl_fss_extended_list_content_write()
 */
#if !defined(_di_fl_fss_basic_list_content_write_) || !defined(_di_fl_fss_extended_list_content_write_) || !defined(_di_fl_fss_embedded_list_content_write_)
  extern f_status_t private_fl_fss_basic_list_write_add_until_end(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_basic_list_content_write_) || !defined(_di_fl_fss_extended_list_content_write_) || !defined(_di_fl_fss_embedded_list_content_write_)

/**
 * Trim a given object used by the basic list and extended list object write functions.
 *
 * @param used_start
 *   The destination.used value before any operations were performed.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
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
 * @see f_fss_is_space()
 * @see fl_fss_basic_list_object_write()
 * @see fl_fss_extended_list_object_write()
 */
#if !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_list_object_write_)
  extern f_status_t private_fl_fss_basic_list_write_object_trim(const f_array_length_t used_start, f_state_t state, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_list_object_write_)

/**
 * Provide common processing for Basic and Extended Object and Content read.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param buffer
 *   The buffer to read from.
 * @param flag
 *   Bits:
 *     - 0x0: When 0x1 bit is not set, then operate as a Content (extended).
 *     - 0x1: Operate as an Object (basic or extended).
 *     - 0x2: Operate with quoting disabled, treating all quotes and escaped quotes as literal (extended).
 *
 *   As an Object, this checks if the first graph character is a comment character '#', or an escaped comment character '#'.
 *   As Content, this does nothing special in regards to a leading '#'.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid object was found.
 * @param quote
 *   This will store the quote type representing the character to use (from the f_fss_quote_type_*_e).
 *   Set pointer address to 0 to not use.
 * @param delimits
 *   An array of delimits detected during processing.
 *   The caller is expected to decide if and when to process them.
 *
 * @return
 *   F_fss_found_object on success and object was found (start location is at end of object).
 *   F_fss_found_object_not on success and no object was found (start location is after character designating this is not an object).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_end_not_group_eos if EOS was reached before the a group termination was reached.
 *   F_end_not_group_stop if stop point was reached before the a group termination was reached.
 *
 *   F_fss_found_object_content_not (with error bit) If an unterminated quoted Object is found.
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_array_lengths_increase().
 *   Errors (with error bit) from: f_array_lengths_increase_by().
 *   Errors (with error bit) from: f_fss_is_graph().
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_is_zero_width().
 *   Errors (with error bit) from: f_fss_skip_past_delimit().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see f_array_lengths_increase()
 * @see f_array_lengths_increase_by()
 * @see f_fss_is_graph()
 * @see f_fss_is_space()
 * @see f_fss_is_zero_width()
 * @see f_fss_skip_past_delimit()
 * @see f_fss_skip_past_space()
 * @see f_utf_buffer_increment()
 * @see fl_fss_basic_object_read()
 * @see fl_fss_extended_object_read()
 * @see fl_fss_extended_content_read()
 */
#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)
  extern f_status_t private_fl_fss_basic_or_extended_read(const f_string_static_t buffer, const uint8_t flag, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_quote_t * const quote, f_fss_delimits_t * const delimits) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)

/**
 * Private implementation of fl_fss_basic_object_write().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * Note: this does not attempt to "complete" the object.
 *
 * @param flag
 *   Bits:
 *     - 0x0: When 0x1 bit is not set, then operate as a Content (extended).
 *     - 0x1: Operate as an Object (basic or extended).
 *
 *   As Object, this checks if the first graph character is a comment character '#', or an escaped comment character '#'.
 *   As Content, this does nothing special in regards to a leading '#'.
 * @param object
 *   The string to write as (does not stop at NULLS, they are ignored and not written).
 * @param quote
 *   If 0, then double quotes are auto-inserted, if needed.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
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
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_none_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_fss_is_space().
 *   Errors (with error bit) from: f_fss_skip_past_delimit().
 *   Errors (with error bit) from: f_fss_skip_past_space().
 *   Errors (with error bit) from: f_string_dynamic_increase().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *   Errors (with error bit) from: f_utf_buffer_increment().
 *
 * @see f_fss_is_space()
 * @see f_fss_skip_past_delimit()
 * @see f_fss_skip_past_space()
 * @see f_string_dynamic_increase()
 * @see f_string_dynamic_increase_by()
 * @see f_utf_buffer_increment()
 * @see fl_fss_basic_object_write()
 * @see fl_fss_extended_object_write()
 * @see fl_fss_extended_content_write()
 */
#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)
  extern f_status_t private_fl_fss_basic_write(const uint8_t flag, const f_string_static_t object, const f_fss_quote_t quote, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)

/**
 * Trim a given object used by the basic and extended object write functions.
 *
 * @param quote
 *   If 0, then double quotes are auto-inserted, when required.
 *   Otherwise, this is the type of quote to wrap the object in when writing.
 * @param used_start
 *   The destination.used value before any operations were perfomed.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   There is no state.handle().
 *   There is no "callbacks" structure.
 *   There is no data structure passed to these functions.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
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
 * @see f_fss_is_space()
 * @see fl_fss_basic_object_write()
 * @see fl_fss_extended_object_write()
 */
#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_)
  extern f_status_t private_fl_fss_basic_write_object_trim(const f_fss_quote_t quote, const f_array_length_t used_start, f_state_t state, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_h

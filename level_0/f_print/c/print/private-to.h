/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_print_to_h
#define _PRIVATE_F_print_to_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_print_to().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to()
 * @see f_print_to_dynamic()
 * @see f_print_to_dynamic_partial()
 */
#if !defined(_di_f_print_to_) || !defined(_di_f_print_to_dynamic_) || !defined(_di_f_print_to_dynamic_partial_)
  extern f_status_t private_f_print_to(const f_string_t string, const f_array_length_t length, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_) || !defined(_di_f_print_to_dynamic_) || !defined(_di_f_print_to_dynamic_partial_)

/**
 * Private implementation of f_print_to_character_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param character
 *   The character to verify as safe or not.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_character_safely()
 * @see f_print_to_safely()
 * @see f_print_to_safely_dynamic()
 * @see f_print_to_safely_dynamic_partial()
 * @see f_print_to_safely_terminated()
 * @see f_print_to_except_safely()
 * @see f_print_to_except_dynamic_safely()
 * @see f_print_to_except_dynamic_partial_safely()
 * @see f_print_to_except_in_safely()
 * @see f_print_to_except_in_dynamic_safely()
 * @see f_print_to_except_in_dynamic_partial_safely()
 */
#if !defined(_di_f_print_to_character_safely_) || !defined(_di_f_print_to_safely_) || !defined(_di_f_print_to_safely_dynamic_) || !defined(_di_f_print_to_safely_dynamic_partial_) || !defined(_di_f_print_to_safely_terminated_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)
  extern f_status_t private_f_print_to_character_safely(const f_char_t character, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_character_safely_) || !defined(_di_f_print_to_safely_) || !defined(_di_f_print_to_safely_dynamic_) || !defined(_di_f_print_to_safely_dynamic_partial_) || !defined(_di_f_print_to_safely_terminated_) || !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_) || !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)

/**
 * Private implementation of f_print_to().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_except()
 * @see f_print_to_except_dynamic()
 * @see f_print_to_except_dynamic_partial()
 */
#if !defined(_di_f_print_to_except_) || !defined(_di_f_print_to_except_dynamic_) || !defined(_di_f_print_to_except_dynamic_partial_)
  extern f_status_t private_f_print_to_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_) || !defined(_di_f_print_to_except_dynamic_) || !defined(_di_f_print_to_except_dynamic_partial_)
/**
 * Private implementation of f_print_to_except_in().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 *
 * @see f_print_to_except_in()
 * @see f_print_to_except_in_dynamic()
 * @see f_print_to_except_in_dynamic_partial()
 */
#if !defined(_di_f_print_to_except_in_) || !defined(_di_f_print_to_except_dynamic_in_) || !defined(_di_f_print_to_except_in_dynamic_partial_)
  extern f_status_t private_f_print_to_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_in_) || !defined(_di_f_print_to_except_dynamic_in_) || !defined(_di_f_print_to_except_in_dynamic_partial_)

/**
 * Private implementation of f_print_to_except_in_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 *
 * @see f_print_to_except_in_raw()
 * @see f_print_to_except_in_dynamic_raw()
 * @see f_print_to_except_in_dynamic_partial_raw()
 */
#if !defined(_di_f_print_to_except_in_raw_) || !defined(_di_f_print_to_except_dynamic_in_raw_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_)
  extern f_status_t private_f_print_to_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_in_raw_) || !defined(_di_f_print_to_except_dynamic_in_raw_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_)

/**
 * Private implementation of f_print_to_except_in_raw_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 *
 * @see f_print_to_except_in_raw_safely()
 * @see f_print_to_except_in_dynamic_raw_safely()
 * @see f_print_to_except_in_dynamic_partial_raw_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_to_except_in_raw_safely_) || !defined(_di_f_print_to_except_dynamic_in_raw_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_safely_)
  extern f_status_t private_f_print_to_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_in_raw_safely_) || !defined(_di_f_print_to_except_dynamic_in_raw_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_raw_safely_)

/**
 * Private implementation of f_print_to_except_in_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 *
 * @see f_print_to_except_in_safely()
 * @see f_print_to_except_in_dynamic_safely()
 * @see f_print_to_except_in_dynamic_partial_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_dynamic_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)
  extern f_status_t private_f_print_to_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except_at, f_string_ranges_t except_in, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_in_safely_) || !defined(_di_f_print_to_except_dynamic_in_safely_) || !defined(_di_f_print_to_except_in_dynamic_partial_safely_)

/**
 * Private implementation of f_print_to_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_except_raw()
 * @see f_print_to_except_dynamic_raw()
 * @see f_print_to_except_dynamic_partial_raw()
 */
#if !defined(_di_f_print_to_except_raw_) || !defined(_di_f_print_to_except_dynamic_raw_) || !defined(_di_f_print_to_except_dynamic_partial_raw_)
  extern f_status_t private_f_print_to_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_raw_) || !defined(_di_f_print_to_except_dynamic_raw_) || !defined(_di_f_print_to_except_dynamic_partial_raw_)

/**
 * Private implementation of f_print_to_except_raw_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_except_raw_safely()
 * @see f_print_to_except_dynamic_raw_safely()
 * @see f_print_to_except_dynamic_partial_raw_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_to_except_raw_safely_) || !defined(_di_f_print_to_except_dynamic_raw_safely_) || !defined(_di_f_print_to_except_dynamic_partial_raw_safely_)
  extern f_status_t private_f_print_to_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_raw_safely_) || !defined(_di_f_print_to_except_dynamic_raw_safely_) || !defined(_di_f_print_to_except_dynamic_partial_raw_safely_)

/**
 * Private implementation of f_print_to_except_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param stop
 *   The exclusive stop point to stop printing.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_except_safely()
 * @see f_print_to_except_dynamic_safely()
 * @see f_print_to_except_dynamic_partial_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_)
  extern f_status_t private_f_print_to_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t stop, const f_array_lengths_t except, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_except_safely_) || !defined(_di_f_print_to_except_dynamic_safely_) || !defined(_di_f_print_to_except_dynamic_partial_safely_)

/**
 * Private implementation of f_print_to_raw().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_raw()
 * @see f_print_to_dynamic_raw()
 * @see f_print_to_dynamic_partial_raw()
 */
#if !defined(_di_f_print_to_raw_) || !defined(_di_f_print_to_dynamic_raw_) || !defined(_di_f_print_to_dynamic_partial_raw_)
  extern f_status_t private_f_print_to_raw(const f_string_t string, const f_array_length_t length, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_raw_) || !defined(_di_f_print_to_dynamic_raw_) || !defined(_di_f_print_to_dynamic_partial_raw_

/**
 * Private implementation of f_print_to_raw_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_raw_safely()
 * @see f_print_to_dynamic_raw_safely()
 * @see f_print_to_dynamic_partial_raw_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_to_raw_safely_) || !defined(_di_f_print_to_dynamic_raw_safely_) || !defined(_di_f_print_to_dynamic_partial_raw_safely_)
  extern f_status_t private_f_print_to_raw_safely(const f_string_t string, const f_array_length_t length, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_raw_safely_) || !defined(_di_f_print_to_dynamic_raw_safely_) || !defined(_di_f_print_to_dynamic_partial_raw_safely_)

/**
 * Private implementation of f_print_to_safely().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_safely()
 * @see f_print_to_dynamic_safely()
 * @see f_print_to_dynamic_partial_safely()
 * @see f_utf_is_valid()
 */
#if !defined(_di_f_print_to_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_dynamic_partial_safely_)
  extern f_status_t private_f_print_to_safely(const f_string_t string, const f_array_length_t length, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_safely_) || !defined(_di_f_print_to_dynamic_safely_) || !defined(_di_f_print_to_dynamic_partial_safely_)

/**
 * Private implementation of f_print_to_terminated().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to output.
 * @param id
 *   The file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_filesystem_quota_block (with error bit) if quota is reached or exceeded.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_number_overflow (with error bit) if maximum size reached while writing or attempting to write beyond maximum allowed offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if a connected pipe or socket is closed.
 *   F_space_not (with error bit) cannot write, out of space.
 *   F_socket_not (with error bit) if socket is not connected.
 *
 *   F_output (with error bit) on any other failure.
 *
 * @see write()
 *
 * @see f_print_to_terminated()
 * @see f_print_to_raw_terminated()
 */
#if !defined(_di_f_print_to_terminated_) || !defined(_di_f_print_to_raw_terminated_)
  extern f_status_t private_f_print_to_terminated(const f_string_t string, const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_print_to_terminated_) || !defined(_di_f_print_to_raw_terminated_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_print_to_h

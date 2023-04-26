/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines print_to_* variants of print functins to be used for/by project print.
 *
 * This is auto-included by print.h and should not need to be explicitly included.
 */
#ifndef _F_print_to_h
#define _F_print_to_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_
  extern f_status_t f_print_to(const f_string_t string, const f_array_length_t length, const f_file_t file);
#endif // _di_f_print_to_

/**
 * Given a single 1-byte character, print the character.
 *
 * This will print NULL characters and is essentially a "raw" print.
 *
 * @param character
 *   The character to verify as safe or not and then print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_character_
  extern f_status_t f_print_to_character(const f_char_t character, const f_file_t file);
#endif // _di_f_print_to_character_

/**
 * Given a single 1-byte character, print the character or a replacement if the character is not considered safe.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 * This can result in the 1-byte character being substituted with a 3-byte character when printing.
 *
 * This should only be called for the first 1-byte character of a multibyte character.
 *
 * @param character
 *   The character to verify as safe or not and then print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_character_safely_
  extern f_status_t f_print_to_character_safely(const f_char_t character, const f_file_t file);
#endif // _di_f_print_to_character_safely_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the length of the buffer.
 *
 * @param buffer
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_
  extern f_status_t f_print_to_dynamic(const f_string_static_t buffer, const f_file_t file);
#endif // _di_f_print_to_dynamic_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the specified range within the buffer.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_partial_
  extern f_status_t f_print_to_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_file_t file);
#endif // _di_f_print_to_dynamic_partial_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to the specified range within the buffer.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_partial_raw_
  extern f_status_t f_print_to_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_file_t file);
#endif // _di_f_print_to_dynamic_partial_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to the specified range within the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_partial_raw_safely_
  extern f_status_t f_print_to_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_file_t file);
#endif // _di_f_print_to_dynamic_partial_raw_safely_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_partial_safely_
  extern f_status_t f_print_to_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_file_t file);
#endif // _di_f_print_to_dynamic_partial_safely_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * @param buffer
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_raw_
  extern f_status_t f_print_to_dynamic_raw(const f_string_static_t buffer, const f_file_t file);
#endif // _di_f_print_to_dynamic_raw_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_raw_safely_
  extern f_status_t f_print_to_dynamic_raw_safely(const f_string_static_t buffer, const f_file_t file);
#endif // _di_f_print_to_dynamic_raw_safely_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * @param buffer
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_dynamic_safely_
  extern f_status_t f_print_to_dynamic_safely(const f_string_static_t buffer, const f_file_t file);
#endif // _di_f_print_to_dynamic_safely_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_
  extern f_status_t f_print_to_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_
  extern f_status_t f_print_to_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_partial_
  extern f_status_t f_print_to_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_partial_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_partial_raw_
  extern f_status_t f_print_to_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_partial_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_partial_raw_safely_
  extern f_status_t f_print_to_except_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_partial_raw_safely_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * @param file
 *   The file structure containing the file descriptor to output to.
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_partial_safely_
  extern f_status_t f_print_to_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_partial_safely_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_raw_
  extern f_status_t f_print_to_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_raw_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_raw_safely_
  extern f_status_t f_print_to_except_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_raw_safely_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_dynamic_safely_
  extern f_status_t f_print_to_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_dynamic_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * An offset is provided because the except_at/except_in positions are expected to be relative to the start position, without the offset applied.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_
  extern f_status_t f_print_to_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to the length of the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_dynamic_
  extern f_status_t f_print_to_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to the specified range within the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_dynamic_partial_
  extern f_status_t f_print_to_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_partial_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_dynamic_partial_raw_
  extern f_status_t f_print_to_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_partial_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to the specified range within the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_dynamic_partial_raw_safely_
  extern f_status_t f_print_to_except_in_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_partial_raw_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to the specified range within the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_to_except_in_dynamic_partial_safely_
  extern f_status_t f_print_to_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_partial_safely_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_dynamic_raw_
  extern f_status_t f_print_to_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_raw_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to the length of the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_dynamic_raw_safely_
  extern f_status_t f_print_to_except_in_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_raw_safely_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to the length of the buffer.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_to_except_in_dynamic_safely_
  extern f_status_t f_print_to_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_dynamic_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * An offset is provided because the except_at/except_in positions are expected to be relative to the start position, without the offset applied.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_raw_
  extern f_status_t f_print_to_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * An offset is provided because the except_at/except_in positions are expected to be relative to the start position, without the offset applied.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_in_raw_safely_
  extern f_status_t f_print_to_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_raw_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * An offset is provided because the except_at/except_in positions are expected to be relative to the start position, without the offset applied.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_to_except_in_safely_
  extern f_status_t f_print_to_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, const f_file_t file);
#endif // _di_f_print_to_except_in_safely_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_raw_
  extern f_status_t f_print_to_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_raw_safely_
  extern f_status_t f_print_to_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_raw_safely_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_except_safely_
  extern f_status_t f_print_to_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, const f_file_t file);
#endif // _di_f_print_to_except_safely_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_raw_
  extern f_status_t f_print_to_raw(const f_string_t string, const f_array_length_t length, const f_file_t file);
#endif // _di_f_print_to_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * This is essentually a "safe" print that also prints NULL.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_raw_safely_
  extern f_status_t f_print_to_raw_safely(const f_string_t string, const f_array_length_t length, const f_file_t file);
#endif // _di_f_print_to_raw_safely_

/**
 * Similar to a c-library printf.
 *
 * Will stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_raw_terminated_
  extern f_status_t f_print_to_raw_terminated(const f_string_t string, const f_file_t file);
#endif // _di_f_print_to_raw_terminated_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_safely_
  extern f_status_t f_print_to_safely(const f_string_t string, const f_array_length_t length, const f_file_t file);
#endif // _di_f_print_to_safely_

/**
 * Similar to a c-library printf.
 *
 * Control characters are converted to the Unicode control character symbols, excluding NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will stop at NULL.
 * Will not print NULL (even as a control character symbol).
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_to_safely_terminated_
  extern f_status_t f_print_to_safely_terminated(const f_string_t string, const f_file_t file);
#endif // _di_f_print_to_safely_terminated_

/**
 * Similar to a c-library printf.
 *
 * Will stop at NULL.
 * Will not print NULL.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param file
 *   The file structure containing the file descriptor to output to.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_file_descriptor_not if file.id is -1.
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
 */
#ifndef _di_f_print_to_terminated_
  extern f_status_t f_print_to_terminated(const f_string_t string, const f_file_t file);
#endif // _di_f_print_to_terminated_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_print_to_h

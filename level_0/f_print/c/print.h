/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides some standard printing functions not available in a libc.
 *
 * Functions provided here are not UTF-8 aware.
 */
#ifndef _F_print_h
#define _F_print_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_
  extern f_status_t f_print(FILE *output, const f_string_t string, const f_array_length_t length);
#endif // _di_f_print_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the length of the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_dynamic_
  extern f_status_t f_print_dynamic(FILE *output, const f_string_static_t buffer);
#endif // _di_f_print_dynamic_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the specified range within the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_dynamic_partial_
  extern f_status_t f_print_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_f_print_dynamic_partial_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_except_
  extern f_status_t f_print_except(FILE *output, const f_string_t string, const f_array_length_t length, const f_array_lengths_t except);
#endif // _di_f_print_except_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_except_dynamic_
  extern f_status_t f_print_except_dynamic(FILE *output, const f_string_static_t buffer, const f_array_lengths_t except);
#endif // _di_f_print_except_dynamic_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
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
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_dynamic_except_partial_
  extern f_status_t f_print_except_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except);
#endif // _di_f_print_except_dynamic_partial_


/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to length 1-byte characters.
 *
 * @param id
 *   The file descriptor to output to.
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_
  extern f_status_t f_print_to(const int id, const f_string_t string, const f_array_length_t length);
#endif // _di_f_print_to_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the length of the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_
  extern f_status_t f_print_to_dynamic(const int id, const f_string_static_t buffer);
#endif // _di_f_print_to_dynamic_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the specified range within the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_partial_
  extern f_status_t f_print_to_dynamic_partial(const int id, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_f_print_to_dynamic_partial_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * @param id
 *   The file descriptor to output to.
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_
  extern f_status_t f_print_to_except(const int id, const f_string_t string, const f_array_length_t length, const f_array_lengths_t except);
#endif // _di_f_print_to_except_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_
  extern f_status_t f_print_to_except_dynamic(const int id, const f_string_static_t buffer, const f_array_lengths_t except);
#endif // _di_f_print_to_except_dynamic_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
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
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_partial_
  extern f_status_t f_print_to_except_dynamic_partial(const int id, const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except);
#endif // _di_f_print_to_except_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_print_h

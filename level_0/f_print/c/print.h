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
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
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
 *   F_data_not if length is 0.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_string_
  extern f_return_status f_print_string(FILE *output, const f_string_t string, const f_string_length_t length);
#endif // _di_f_print_string_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 *
 * @return
 *   F_none on success.
 *   F_data_not if buffer.used is 0.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_string_dynamic_
  extern f_return_status f_print_string_dynamic(FILE *output, const f_string_static_t buffer);
#endif // _di_f_print_string_dynamic_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the only the buffer range specified by range.
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
 *   F_data_not if buffer.used is 0.
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fputc()
 */
#ifndef _di_f_print_string_dynamic_partial_
  extern f_return_status f_print_string_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_f_print_string_dynamic_partial_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
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
 *   F_data_not if length is 0.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_
  extern f_return_status f_print_to(const int id, const f_string_t string, const f_string_length_t length);
#endif // _di_f_print_to_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
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
 *   F_data_not if buffer.used is 0.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_dynamic_to_
  extern f_return_status f_print_dynamic_to(const int id, const f_string_t string, const f_string_length_t length);
#endif // _di_f_print_dynamic_to_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
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
 *   F_data_not if buffer.used is 0.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_dynamic_partial_to_
  extern f_return_status f_print_dynamic_partial_to(const int id, const f_string_t string, const f_string_length_t length);
#endif // _di_f_print_dynamic_partial_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_print_h

/**
 * FLL - Level 0
 *
 * Project: Output
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides some standard printing functions not available in a libc.
 */
#ifndef _F_print_h
#define _F_print_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param string
 *   The string to output.
 *
 * @return
 *   f_none on success.
 *   f_output_error (with error bit) on failure.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_print_string_
  extern f_return_status f_print_string(FILE *output, const f_string string, const f_string_length length);
#endif // _di_f_print_string_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the entire dynamic string.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 *
 * @return
 *   f_none on success.
 *   f_output_error (with error bit) on failure.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_print_dynamic_string_
  extern f_return_status f_print_dynamic_string(FILE *output, const f_dynamic_string buffer);
#endif // _di_f_print_dynamic_string_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * The string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the only the buffer range specified by location.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 * @param location
 *   The range within the provided string to print.
 *
 * @return
 *   f_none on success.
 *   f_output_error (with error bit) on failure.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_print_partial_dynamic_string_
  extern f_return_status f_print_partial_dynamic_string(FILE *output, const f_dynamic_string buffer, const f_string_location location);
#endif // _di_f_print_partial_dynamic_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_print_h

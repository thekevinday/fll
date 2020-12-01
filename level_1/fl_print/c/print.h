/**
 * FLL - Level 1
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides some standard printing functions not available in a libc.
 *
 * Functions provided here are UTF-8 aware.
 */
#ifndef _FL_print_h
#define _FL_print_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will not print any 1-byte character at a location specified in except array.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 */
#ifndef _di_fl_print_trim_except_
  extern f_return_status fl_print_trim_except(FILE *output, const f_string_t string, const f_string_length_t length, const f_string_lengths_t except);
#endif // _di_fl_print_trim_except_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except array.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 */
#ifndef _di_fl_print_trim_except_dynamic_
  extern f_return_status fl_print_trim_except_dynamic(FILE *output, const f_string_static_t buffer, const f_string_lengths_t except);
#endif // _di_fl_print_trim_except_dynamic_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_
  extern f_return_status fl_print_trim_except_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range, const f_string_lengths_t except);
#endif // _di_fl_print_trim_except_dynamic_partial_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will not print any 1 UTF character at a location specified in except array.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 */
#ifndef _di_fl_print_trim_except_utf_
  extern f_return_status fl_print_trim_except_utf(FILE *output, const f_utf_string_t string, const f_utf_string_length_t length, const f_utf_string_lengths_t except);
#endif // _di_fl_print_trim_except_utf_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will not print any 1 UTF character at a location specified in except array.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 */
#ifndef _di_fl_print_trim_except_utf_dynamic_
  extern f_return_status fl_print_trim_except_utf_dynamic(FILE *output, const f_utf_string_static_t buffer, const f_utf_string_lengths_t except);
#endif // _di_fl_print_trim_except_utf_dynamic_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will not print any 1 UTF character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 */
#ifndef _di_fl_print_trim_except_utf_dynamic_partial_
  extern f_return_status fl_print_trim_except_utf_dynamic_partial(FILE *output, const f_utf_string_static_t buffer, const f_utf_string_range_t range, const f_utf_string_lengths_t except);
#endif // _di_fl_print_trim_except_utf_dynamic_partial_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 */
#ifndef _di_fl_print_trim_
  extern f_return_status fl_print_trim(FILE *output, const f_string_t string, const f_string_length_t length);
#endif // _di_fl_print_trim_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 */
#ifndef _di_fl_print_trim_dynamic_
  extern f_return_status fl_print_trim_dynamic(FILE *output, const f_string_static_t buffer);
#endif // _di_fl_print_trim_dynamic_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 */
#ifndef _di_fl_print_trim_dynamic_partial_
  extern f_return_status fl_print_trim_dynamic_partial(FILE *output, const f_string_static_t buffer, const f_string_range_t range);
#endif // _di_fl_print_trim_dynamic_partial_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 */
#ifndef _di_fl_print_trim_utf_
  extern f_return_status fl_print_trim_utf(FILE *output, const f_utf_string_t string, const f_utf_string_length_t length);
#endif // _di_fl_print_trim_utf_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * @param output
 *   The file to output to, including standard streams such as stdout and stderr.
 * @param buffer
 *   The string to output.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 */
#ifndef _di_fl_print_trim_utf_dynamic_
  extern f_return_status fl_print_trim_utf_dynamic(FILE *output, const f_utf_string_static_t buffer);
#endif // _di_fl_print_trim_utf_dynamic_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at \0.
 * Will not print \0.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
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
 *   F_data_not on success but there is nothing to print.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 */
#ifndef _di_fl_print_trim_utf_dynamic_partial_
  extern f_return_status fl_print_trim_utf_dynamic_partial(FILE *output, const f_utf_string_static_t buffer, const f_utf_string_range_t range);
#endif // _di_fl_print_trim_utf_dynamic_partial_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_print_h

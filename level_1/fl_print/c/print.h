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
 *
 * @fixme: the except_in and except_at only apply to 1-byte characters, so what happens if a single except byte is only a part of a single multibyte character?
 */
#ifndef _FL_print_h
#define _FL_print_h

// libc includes
#include <stdio.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A formatted print function similar to (but not the same as) the c-library fprintf() function.
 *
 * @todo add the complex documentation.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The formatted string to process and output.
 *   This is a NULL terminated string.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ...
 *   Additional arguments relating to the string.
 *
 * @return
 *   F_none on success.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *   Success from: f_print_dynamic().
 *   Success from: f_print_dynamic_raw().
 *   Success from: f_print_dynamic_safely().
 *   Success from: f_print_safely().
 *   Success from: f_print_terminated().
 *
 *   Errors (with error bit) from: f_conversion_number_signed_to_file().
 *   Errors (with error bit) from: f_conversion_number_unsigned_to_file().
 *   Errors (with error bit) from: f_print_dynamic().
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *   Errors (with error bit) from: f_print_safely().
 *   Errors (with error bit) from: f_print_terminated().
 *
 * @see fputc_unlocked()
 * @see va_start()
 * @see va_end()
 *
 * @see f_conversion_number_signed_to_file()
 * @see f_conversion_number_unsigned_to_file()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 */
#ifndef _di_fl_print_string_
  extern f_status_t fl_print_string(const f_string_t string, FILE *output, ...);
#endif // _di_fl_print_string_

/**
 * Convert and print a single part of a formatted string represented by the '%'.
 *
 * This should be called after each first '%' is encountered.
 * This should return only after a single '%' group is fully processed, end of current is reached, or an error occurs.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param current
 *   The current character position within the string.
 *   This pointer might be updated by this function.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable arguments list.
 *
 * @return
 *   F_none on success.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *   Success from: f_print_dynamic().
 *   Success from: f_print_dynamic_raw().
 *   Success from: f_print_dynamic_safely().
 *   Success from: f_print_safely().
 *   Success from: f_print_terminated().
 *
 *   Errors (with error bit) from: f_conversion_number_signed_to_file().
 *   Errors (with error bit) from: f_conversion_number_unsigned_to_file().
 *   Errors (with error bit) from: f_print_dynamic().
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *   Errors (with error bit) from: f_print_safely().
 *   Errors (with error bit) from: f_print_terminated().
 *
 * @see fputc_unlocked()
 *
 * @see f_conversion_number_signed_to_file()
 * @see f_conversion_number_unsigned_to_file()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 */
#ifndef _di_fl_print_string_convert_
  extern f_status_t fl_print_string_convert(char *current, FILE *output, va_list *ap);
#endif // _di_fl_print_string_convert_

/**
 * A formatted print function similar to (but not the same as) the c-library vfprintf() function.
 *
 * This is identical to fl_print_string() except it accepts a va_list as a variable instead of as "...".
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The formatted string to process and output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable list.
 *   The va_start(ap, string) and va_end(ap) is required to be called outside this function.
 *
 * @return
 *   F_none on success.
 *
 *   F_output (with error bit) on failure to print to the output file.
 *   F_valid_not (with error bit) on invalid syntax (such as terminating the string on a single '%').
 *
 *   Success from: f_print_dynamic().
 *   Success from: f_print_dynamic_raw().
 *   Success from: f_print_dynamic_safely().
 *   Success from: f_print_safely().
 *   Success from: f_print_terminated().
 *
 *   Errors (with error bit) from: f_conversion_number_signed_to_file().
 *   Errors (with error bit) from: f_conversion_number_unsigned_to_file().
 *   Errors (with error bit) from: f_print_dynamic().
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *   Errors (with error bit) from: f_print_safely().
 *   Errors (with error bit) from: f_print_terminated().
 *
 * @see fputc_unlocked()
 * @see va_start()
 * @see va_end()
 *
 * @see f_conversion_number_signed_to_file()
 * @see f_conversion_number_unsigned_to_file()
 * @see f_print_dynamic()
 * @see f_print_dynamic_raw()
 * @see f_print_dynamic_safely()
 * @see f_print_safely()
 * @see f_print_terminated()
 * @see fl_print_string()
 */
#ifndef _di_fl_print_string_va_
  extern f_status_t fl_print_string_va(const f_string_t string, FILE *output, va_list *ap);
#endif // _di_fl_print_string_va_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_
  extern f_status_t fl_print_trim(const f_string_t string, const f_array_length_t length, FILE *output);
#endif // _di_fl_print_trim_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_raw_
  extern f_status_t fl_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE *output);
#endif // _di_fl_print_trim_raw_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_safely_
  extern f_status_t fl_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE *output);
#endif // _di_fl_print_trim_safely_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_
  extern f_status_t fl_print_trim_dynamic(const f_string_static_t buffer, FILE *output);
#endif // _di_fl_print_trim_dynamic_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_raw_
  extern f_status_t fl_print_trim_dynamic_raw(const f_string_static_t buffer, FILE *output);
#endif // _di_fl_print_trim_dynamic_raw_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_safely_
  extern f_status_t fl_print_trim_dynamic_safely(const f_string_static_t buffer, FILE *output);
#endif // _di_fl_print_trim_dynamic_safely_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_partial_
  extern f_status_t fl_print_trim_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE *output);
#endif // _di_fl_print_trim_dynamic_partial_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_partial_raw_
  extern f_status_t fl_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE *output);
#endif // _di_fl_print_trim_dynamic_partial_raw_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_dynamic_partial_safely_
  extern f_status_t fl_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE *output);
#endif // _di_fl_print_trim_dynamic_partial_safely_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_
  extern f_status_t fl_print_trim_except(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_raw_
  extern f_status_t fl_print_trim_except_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_raw_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_safely_
  extern f_status_t fl_print_trim_except_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_safely_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_
  extern f_status_t fl_print_trim_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_dynamic_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_raw_
  extern f_status_t fl_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_dynamic_raw_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_safely_
  extern f_status_t fl_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_dynamic_safely_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_
  extern f_status_t fl_print_trim_except_in(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_raw_
  extern f_status_t fl_print_trim_except_in_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_raw_

/**
 * Print a string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_safely_
  extern f_status_t fl_print_trim_except_in_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_safely_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_
  extern f_status_t fl_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_dynamic_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_raw_
  extern f_status_t fl_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_dynamic_raw_

/**
 * Print a dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print the entire dynamic string, except for leading/trailing whitespace.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_safely_
  extern f_status_t fl_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_dynamic_safely_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_partial_
  extern f_status_t fl_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_dynamic_partial_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_partial_raw_
  extern f_status_t fl_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_dynamic_partial_raw_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_in_dynamic_partial_safely_
  extern f_status_t fl_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_fl_print_trim_except_in_dynamic_partial_safely_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_complete_not_utf_stop (with error bit) if character is an incomplete UTF-8 fragment at end of the string.
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_
  extern f_status_t fl_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_dynamic_partial_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Except for leading/trailing whitespace, the string is printed as-is without interpretation.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * All UTF-8 characters, invalid or not, are printed as is, except for trimmed characters.
 * Invalid UTF-8 characters are not considered whitespace for the purpose of trimming.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_raw_
  extern f_status_t fl_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_dynamic_partial_raw_

/**
 * Print a partial dynamic string, stripping leading and trailing whitespace.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except array.
 * Will print the only the buffer range specified by range, except for leading/trailing whitespace.
 *
 * NULL characters are treated as whitespace for the purpose of trimming.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to print.
 *
 *   F_output (with error bit) on error when printing to output.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_is_valid()
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fputc_unlocked()
 */
#ifndef _di_fl_print_trim_except_dynamic_partial_safely_
  extern f_status_t fl_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_fl_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_print_h

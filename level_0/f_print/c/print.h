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
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// fll-0 print includes
#include <fll/level_0/print-common.h>

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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_
  extern f_status_t f_print(const f_string_t string, const f_array_length_t length, FILE *output);
#endif // _di_f_print_

/**
 * Given a single 1-byte character, print the character.
 *
 * @param character
 *   The character to verify as safe or not and then print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_character_
  extern f_status_t f_print_character(const char character, FILE *output);
#endif // _di_f_print_character_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_character_safely_
  extern f_status_t f_print_character_safely(const char character, FILE *output);
#endif // _di_f_print_character_safely_

/**
 * Get a safe representation of the character if the character is considered unsafe.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with a width of 1 are converted to the unknown character '�'.
 * For all other UTF-8 sequences, 0 is returned because it cannot be processed via a single 8-byte character.
 *
 * The returned string will either be NULL (for characters that are already safe) or a string representing the replacement.
 * This can result in a 3-byte character being returned as a string of 3 1-bytes.
 *
 * This should only be called for the first 1-byte character of a multibyte character.
 *
 * @param character
 *   The character to verify as safe or not and then print.
 *
 * @return
 *   NULL is returned if the character is already safe or if the character has a UTF-8 width of 2 or greater.
 *   A non-NULL string is returned if the character needs safe replacement.
 *   The non-NULL strings returned are NULL terminated.
 *   The non-NULL strings returned are the 3-byte characters used as placeholder symbols.
 */
#ifndef _di_f_print_character_safely_get_
  extern f_string_t f_print_character_safely_get(const char character);
#endif // _di_f_print_character_safely_get_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the length of the buffer.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_
  extern f_status_t f_print_dynamic(const f_string_static_t buffer, FILE *output);
#endif // _di_f_print_dynamic_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_raw_
  extern f_status_t f_print_dynamic_raw(const f_string_static_t buffer, FILE *output);
#endif // _di_f_print_dynamic_raw_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print up to length 1-byte characters.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_dynamic_safely_
  extern f_status_t f_print_dynamic_safely(const f_string_static_t buffer, FILE *output);
#endif // _di_f_print_dynamic_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the specified range within the buffer.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_partial_
  extern f_status_t f_print_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE *output);
#endif // _di_f_print_dynamic_partial_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_partial_raw_
  extern f_status_t f_print_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE *output);
#endif // _di_f_print_dynamic_partial_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print up to the specified range within the buffer.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_dynamic_partial_safely_
  extern f_status_t f_print_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE *output);
#endif // _di_f_print_dynamic_partial_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_
  extern f_status_t f_print_except(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_raw_
  extern f_status_t f_print_except_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_except_safely_
  extern f_status_t f_print_except_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_safely_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_dynamic_
  extern f_status_t f_print_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_dynamic_raw_
  extern f_status_t f_print_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_raw_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_except_dynamic_safely_
  extern f_status_t f_print_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_in_
  extern f_status_t f_print_except_in(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_in_raw_
  extern f_status_t f_print_except_in_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except_at array.
 * Will not print any 1-byte character within the ranges specified in except_in array.
 * Will print up to length 1-byte characters.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_except_in_safely_
  extern f_status_t f_print_except_in_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_safely_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_in_dynamic_
  extern f_status_t f_print_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_dynamic_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_except_in_dynamic_raw_
  extern f_status_t f_print_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_dynamic_raw_

/**
 * Similar to a c-library printf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_except_in_dynamic_safely_
  extern f_status_t f_print_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_dynamic_safely_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_except_partial_
  extern f_status_t f_print_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_dynamic_partial_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_except_partial_raw_
  extern f_status_t f_print_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_dynamic_partial_raw_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_dynamic_except_partial_safely_
  extern f_status_t f_print_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE *output);
#endif // _di_f_print_except_in_dynamic_partial_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_except_partial_
  extern f_status_t f_print_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_partial_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_except_partial_raw_
  extern f_status_t f_print_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_partial_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_except_partial_
  extern f_status_t f_print_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_partial_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_dynamic_except_partial_raw_
  extern f_status_t f_print_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_partial_raw_

/**
 * Similar to a c-library printf, except that this will only print a specific range in a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_dynamic_except_partial_safely_
  extern f_status_t f_print_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE *output);
#endif // _di_f_print_except_dynamic_partial_safely_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Will not stop at NULL.
 * Will print NULL.
 * Will print up to length 1-byte characters.
 *
 * All UTF-8 characters, invalid or not, are printed as is.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_raw_
  extern f_status_t f_print_raw(const f_string_t string, const f_array_length_t length, FILE *output);
#endif // _di_f_print_raw_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_raw_terminated_
  extern f_status_t f_print_raw_terminated(const f_string_t string, FILE *output);
#endif // _di_f_print_raw_terminated_

/**
 * Similar to a c-library printf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print up to length 1-byte characters.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_safely_
  extern f_status_t f_print_safely(const f_string_t string, const f_array_length_t length, FILE *output);
#endif // _di_f_print_safely_

/**
 * Similar to a c-library printf.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will stop at NULL.
 * Will not print NULL (even as a control character symbol).
 * Will print up to length 1-byte characters.
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
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 *
 * @see f_utf_is_valid()
 */
#ifndef _di_f_print_safely_terminated_
  extern f_status_t f_print_safely_terminated(const f_string_t string, FILE *output);
#endif // _di_f_print_safely_terminated_

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
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none on success.
 *   F_data_not if there is nothing to print.
 *
 *   F_output (with error bit) on failure.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_print_terminated_
  extern f_status_t f_print_terminated(const f_string_t string, FILE *output);
#endif // _di_f_print_terminated_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_
  extern f_status_t f_print_to(const f_string_t string, const f_array_length_t length, const int id);
#endif // _di_f_print_to_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_raw_
  extern f_status_t f_print_to_raw(const f_string_t string, const f_array_length_t length, const int id);
#endif // _di_f_print_to_raw_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print up to length 1-byte characters.
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_safely_
  extern f_status_t f_print_to_safely(const f_string_t string, const f_array_length_t length, const int id);
#endif // _di_f_print_to_safely_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Will not stop at NULL.
 * Will not print NULL.
 * Will print up to the length of the buffer.
 *
 * @param buffer
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_
  extern f_status_t f_print_to_dynamic(const f_string_static_t buffer, const int id);
#endif // _di_f_print_to_dynamic_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_raw_
  extern f_status_t f_print_to_dynamic_raw(const f_string_static_t buffer, const int id);
#endif // _di_f_print_to_dynamic_raw_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print up to length 1-byte characters.
 *
 * @param buffer
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_safely_
  extern f_status_t f_print_to_dynamic_safely(const f_string_static_t buffer, const int id);
#endif // _di_f_print_to_dynamic_safely_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_partial_
  extern f_status_t f_print_to_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const int id);
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_partial_raw_
  extern f_status_t f_print_to_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const int id);
#endif // _di_f_print_to_dynamic_partial_raw_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will print up to length 1-byte characters.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_dynamic_partial_safely_
  extern f_status_t f_print_to_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const int id);
#endif // _di_f_print_to_dynamic_partial_safely_

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
 * @param length
 *   The total number of characters to print.
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_
  extern f_status_t f_print_to_except(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_

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
 * @param length
 *   The total number of characters to print.
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_raw_
  extern f_status_t f_print_to_except_raw(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_raw_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to length 1-byte characters.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_safely_
  extern f_status_t f_print_to_except_safely(const f_string_t string, const f_array_length_t length, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_safely_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_
  extern f_status_t f_print_to_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_dynamic_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_raw_
  extern f_status_t f_print_to_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_dynamic_raw_

/**
 * Similar to a c-library dprintf, except that this prints a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the length of the buffer.
 *
 * @param buffer
 *   The string to output.
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_safely_
  extern f_status_t f_print_to_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_dynamic_safely_

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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_partial_
  extern f_status_t f_print_to_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const int id);
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
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_print_to_except_dynamic_partial_raw_
  extern f_status_t f_print_to_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_dynamic_partial_raw_

/**
 * Similar to a c-library dprintf, except that this will only print a specific range in a given dynamic string.
 *
 * Control characters are converted to the Unicode control character symbols, including NULL.
 * UTF-8 sequences with invalid widths are converted to the unknown character '�'.
 *
 * Will not stop at NULL.
 * Will print NULL (as a control character symbol).
 * Will not print any 1-byte character at a location specified in except array.
 * Will print up to the specified range within the buffer.
 *
 * @param id
 *   The file descriptor to output to.
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
 *
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
#ifndef _di_f_print_to_except_dynamic_partial_safely_
  extern f_status_t f_print_to_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, const int id);
#endif // _di_f_print_to_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_print_h

/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provide means to convert one data type to another, such as a string to an integer.
 *
 * @fixme Currently these functions are very inefficient.
 *        These will be improved once I have finished studying on the matter.
 */
#ifndef _F_conversion_h
#define _F_conversion_h

// Libc includes.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// fll-0 conversion includes
#include <fll/level_0/conversion-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify whether or not the given 1-byte character represents a boolean digit.
 *
 * A boolean digit is either '0' or '1'.
 *
 * This only checks against ASCII characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a binary.
 *   F_false if character is not a binary.
 */
#ifndef _di_f_conversion_character_is_binary_
  extern f_status_t f_conversion_character_is_binary(const char character);
#endif // _di_f_conversion_character_is_binary_

/**
 * Identify whether or not the given 1-byte character represents a decimal digit.
 *
 * A decimal digit is a character from the numbers '0' to '9'.
 *
 * This only checks against ASCII characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a decimal.
 *   F_false if character is not a decimal.
 */
#ifndef _di_f_conversion_character_is_decimal_
  extern f_status_t f_conversion_character_is_decimal(const char character);
#endif // _di_f_conversion_character_is_decimal_

/**
 * Identify whether or not the given 1-byte character represents a duodecimal digit.
 *
 * A decimal digit is a character from the numbers '0' to '9' and the following:
 *   - 'a' or 'A': Character used to represent the number 10.
 *   - 'b' or 'B': Character used to represent the number 11.
 *
 * This only checks against ASCII characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a duodecimal.
 *   F_false if character is not a duodecimal.
 */
#ifndef _di_f_conversion_character_is_duodecimal_
  extern f_status_t f_conversion_character_is_duodecimal(const char character);
#endif // _di_f_conversion_character_is_duodecimal_

/**
 * Identify whether or not the given 1-byte character represents a hexidecimal digit.
 *
 * A decimal digit is a character from the numbers '0' to '9' and the following:
 *   - 'a' or 'A': Character used to represent the number 10.
 *   - 'b' or 'B': Character used to represent the number 11.
 *   - 'c' or 'C': Character used to represent the number 12.
 *   - 'd' or 'D': Character used to represent the number 13.
 *   - 'e' or 'E': Character used to represent the number 14.
 *   - 'f' or 'F': Character used to represent the number 15.
 *
 * This only checks against ASCII characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is a hexidecimal.
 *   F_false if character is not a hexidecimal.
 */
#ifndef _di_f_conversion_character_is_hexidecimal_
  extern f_status_t f_conversion_character_is_hexidecimal(const char character);
#endif // _di_f_conversion_character_is_hexidecimal_

/**
 * Identify whether or not the given 1-byte character represents a octal digit.
 *
 * A decimal digit is a character from the numbers '0' to '7'.
 *
 * This only checks against ASCII characters.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   F_true if character is an octal.
 *   F_false if character is not an octal.
 */
#ifndef _di_f_conversion_character_is_octal_
  extern f_status_t f_conversion_character_is_octal(const char character);
#endif // _di_f_conversion_character_is_octal_

/**
 * Convert a single character into the binary digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a binary.
 *
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_binary_
  extern f_status_t f_conversion_character_to_binary(const char character, uint8_t *number);
#endif // _di_f_conversion_character_to_binary_

/**
 * Convert a single character into the decimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a decimal.
 *
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_decimal_
  extern f_status_t f_conversion_character_to_decimal(const char character, uint8_t *number);
#endif // _di_f_conversion_character_to_decimal_

/**
 * Convert a single character into the duodecimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a duodecimal.
 *
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_duodecimal_
  extern f_status_t f_conversion_character_to_duodecimal(const char character, uint8_t *number);
#endif // _di_f_conversion_character_to_duodecimal_

/**
 * Convert a single character into the hexidecimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a hexidecimal.
 *
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_hexidecimal_
  extern f_status_t f_conversion_character_to_hexidecimal(const char character, uint8_t *number);
#endif // _di_f_conversion_character_to_hexidecimal_

/**
 * Convert a single character into the octal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param number
 *   This will store the value of the converted character.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if character was converted to a hexidecimal.
 *
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_octal_
  extern f_status_t f_conversion_character_to_octal(const char character, uint8_t *number);
#endif // _di_f_conversion_character_to_octal_

/**
 * Convert a signed number into the decimal digit string that it represents.
 *
 * The generated number is printed to the file stream.
 *
 * This only supports the following base units: 2 through 16.
 * This only supports base prefixes for: 2, 8, 10, 12, and 16.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param number
 *   The number to convert.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none if the number was converted to a string.
 *
 *   F_block (with error bit) if file stream is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_output (with error bit) on any other file output error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_conversion_number_signed_print_
  extern f_status_t f_conversion_number_signed_print(const f_number_signed_t number, const f_conversion_data_t data, FILE *output);
#endif // _di_f_conversion_number_signed_print_

/**
 * Convert a signed number into the decimal digit string that it represents.
 *
 * The generated number is appended to the destination string.
 *
 * This only supports the following base units: 2 through 16.
 * This only supports base prefixes for: 2, 8, 10, 12, and 16.
 *
 * @param number
 *   The number to convert.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param destination
 *   The destination the converted string is saved into.
 *
 * @return
 *   F_none if the number was converted to a string.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_conversion_number_signed_to_string_
  extern f_status_t f_conversion_number_signed_to_string(const f_number_signed_t number, const f_conversion_data_t data, f_string_dynamic_t *destination);
#endif // _di_f_conversion_number_signed_to_string_

/**
 * Convert an unsigned number into the decimal digit string that it represents.
 *
 * The generated number is printed to the file stream.
 *
 * This only supports the following base units: 2 through 16.
 * This only supports base prefixes for: 2, 8, 10, 12, and 16.
 *
 * This print function does not use locking, be sure something like flockfile() and funlockfile() are appropriately called.
 *
 * @param number
 *   The number to convert.
 *   This number is unsigned to allow for unsigned integers to be used.
 *   To represent a negative number, assign the flag f_conversion_data_flag_is_negative to data.flags.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   F_none if the number was converted to a string.
 *
 *   F_block (with error bit) if file stream is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_output (with error bit) on any other file output error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite_unlocked()
 */
#ifndef _di_f_conversion_number_unsigned_print_
  extern f_status_t f_conversion_number_unsigned_print(const f_number_unsigned_t number, const f_conversion_data_t data, FILE *output);
#endif // _di_f_conversion_number_unsigned_print_

/**
 * Convert an unsigned number into the decimal digit string that it represents.
 *
 * The generated number is appended to the destination string.
 *
 * This only supports the following base units: 2 through 16.
 * This only supports base prefixes for: 2, 8, 10, 12, and 16.
 *
 * @param number
 *   The number to convert.
 * @param data
 *   The settings designating how to perform the conversion.
 * @param destination
 *   The destination the converted string is saved into.
 *
 * @return
 *   F_none if the number was converted to a string.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_conversion_number_unsigned_to_string_
  extern f_status_t f_conversion_number_unsigned_to_string(const f_number_unsigned_t number, const f_conversion_data_t data, f_string_dynamic_t *destination);
#endif // _di_f_conversion_number_unsigned_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

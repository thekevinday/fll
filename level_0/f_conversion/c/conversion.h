/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to convert one data type to another, such as a string to an integer.
 */
#ifndef _F_conversion_h
#define _F_conversion_h

// libc includes
#include <stdlib.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a single character into the decimal value that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if character is a decimal.
 *   f_false if character is not a decimal.
 */
#ifndef _di_f_is_decimal_
  extern f_return_status f_is_decimal(const char character);
#endif // _di_f_is_decimal_

/**
 * Convert a single character into the hexidecimal digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if character is a hexidecimal.
 *   f_false if character is not a hexidecimal.
 */
#ifndef _di_f_is_hexidecimal_
  extern f_return_status f_is_hexidecimal(const char character);
#endif // _di_f_is_hexidecimal_

/**
 * Convert a single character into the digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param decimal
 *   This will store the value of the converted character.
 *   This value is not changed when f_no_data is returned.
 *
 * @return
 *   f_none if character was converted to a decimal.
 *   f_no_data if no conversion was made due to non-decimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_character_to_decimal_
  extern f_return_status f_character_to_decimal(const char character, unsigned long *decimal);
#endif // _di_f_character_to_decimal_

/**
 * Convert a single character into the hexidecimal digit that it represents.
 *
 * @param character
 *   The character to convert.
 * @param decimal
 *   This will store the value of the converted character.
 *   This value is not changed when f_no_data is returned.
 *
 * @return
 *   f_none if character was converted to a hexidecimal.
 *   f_no_data if no conversion was made due to non-hexidecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_character_to_hexidecimal_
  extern f_return_status f_character_to_hexidecimal(const char character, unsigned long *decimal);
#endif // _di_f_character_to_hexidecimal_

/**
 * Convert a series of positive decimal numbers characters into an unsigned long.
 *
 * This will stop at one of the following: EOS, max_length, or a non-digit.
 * This works like atoi, except there is a start/stop range.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param decimal
 *   This will store the value of the converted string.
 *   This value is not changed when f_no_data is returned.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the decimal string was converted to an unsigned long.
 *   f_no_data if no conversion was made due to non-decimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_to_decimal_
  extern f_return_status f_string_to_decimal(const f_string string, unsigned long *decimal, const f_string_location location);
#endif // _di_f_string_to_decimal_

/**
 * Convert a series of positive hexidecimal numbers characters into an unsigned long.
 *
 * This will stop at one of the following: EOS, max_length, or a non-digit.
 * This works like atoi, except there is a start/stop range.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param decimal
 *   This will store the value of the converted string.
 *   This value is not changed when f_no_data is returned.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the hexidecimal string was converted to an unsigned long.
 *   f_no_data if no conversion was made due to non-hexidecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_to_hexidecimal_
  extern f_return_status f_string_to_hexidecimal(const f_string string, unsigned long *decimal, const f_string_location location);
#endif // _di_f_string_to_hexidecimal_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

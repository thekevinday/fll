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
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a single character into the binary digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if character is a binary.
 *   f_false if character is not a binary.
 */
#ifndef _di_f_conversion_character_is_binary_
  extern f_return_status f_conversion_character_is_binary(const int8_t character);
#endif // _di_f_conversion_character_is_binary_

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
#ifndef _di_f_conversion_character_is_decimal_
  extern f_return_status f_conversion_character_is_decimal(const int8_t character);
#endif // _di_f_conversion_character_is_decimal_

/**
 * Convert a single character into the duodecimal digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if character is a duodecimal.
 *   f_false if character is not a duodecimal.
 */
#ifndef _di_f_conversion_character_is_duodecimal_
  extern f_return_status f_conversion_character_is_duodecimal(const int8_t character);
#endif // _di_f_conversion_character_is_duodecimal_

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
#ifndef _di_f_conversion_character_is_hexidecimal_
  extern f_return_status f_conversion_character_is_hexidecimal(const int8_t character);
#endif // _di_f_conversion_character_is_hexidecimal_

/**
 * Convert a single character into the octal digit that it represents.
 *
 * @param character
 *   The character to validate.
 *
 * @return
 *   f_true if character is an octal.
 *   f_false if character is not an octal.
 */
#ifndef _di_f_conversion_character_is_octal_
  extern f_return_status f_conversion_character_is_octal(const int8_t character);
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
 *   f_none if character was converted to a binary.
 *   f_invalid_number (with error bit) if no conversion was made due to non-binary values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_binary_
  extern f_return_status f_conversion_character_to_binary(const int8_t character, uint64_t *number);
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
 *   f_none if character was converted to a decimal.
 *   f_invalid_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_decimal_
  extern f_return_status f_conversion_character_to_decimal(const int8_t character, uint64_t *number);
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
 *   f_none if character was converted to a duodecimal.
 *   f_invalid_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_duodecimal_
  extern f_return_status f_conversion_character_to_duodecimal(const int8_t character, uint64_t *number);
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
 *   f_none if character was converted to a hexidecimal.
 *   f_invalid_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_hexidecimal_
  extern f_return_status f_conversion_character_to_hexidecimal(const int8_t character, uint64_t *number);
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
 *   f_none if character was converted to a hexidecimal.
 *   f_invalid_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_conversion_character_to_octal_
  extern f_return_status f_conversion_character_to_octal(const int8_t character, uint64_t *number);
#endif // _di_f_conversion_character_to_octal_

/**
 * Convert a series of positive or negative binary number characters into a int64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   f_none if the binary string was converted to an signed long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-binary values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 *   f_underflow (with error bit) on integer underflow.
 */
#ifndef _di_f_conversion_string_to_binary_signed_
  extern f_return_status f_conversion_string_to_binary_signed(const f_string string, int64_t *number, const f_string_location location, const bool negative);
#endif // _di_f_conversion_string_to_binary_signed_

/**
 * Convert a series of positive binary number characters into a uint64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the binary string was converted to an unsigned long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-binary values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 */
#ifndef _di_f_conversion_string_to_binary_unsigned_
  extern f_return_status f_conversion_string_to_binary_unsigned(const f_string string, uint64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_binary_unsigned_

/**
 * Convert a series of positive or negative decimal number characters into an int64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   f_none if the decimal string was converted to an signed long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 *   f_underflow (with error bit) on integer underflow.
 */
#ifndef _di_f_conversion_string_to_decimal_signed_
  extern f_return_status f_conversion_string_to_decimal_signed(const f_string string, int64_t *number, const f_string_location location, const bool negative);
#endif // _di_f_conversion_string_to_decimal_signed_

/**
 * Convert a series of positive decimal number characters into an uint64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the decimal string was converted to an unsigned long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 */
#ifndef _di_f_conversion_string_to_decimal_unsigned_
  extern f_return_status f_conversion_string_to_decimal_unsigned(const f_string string, uint64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_decimal_unsigned_

/**
 * Convert a series of positive or negative duodecimal number characters into an int64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   f_none if the duodecimal string was converted to an signed long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 *   f_underflow (with error bit) on integer underflow.
 */
#ifndef _di_f_conversion_string_to_duodecimal_signed_
  extern f_return_status f_conversion_string_to_duodecimal_signed(const f_string string, int64_t *number, const f_string_location location, const bool negative);
#endif // _di_f_conversion_string_to_duodecimal_signed_

/**
 * Convert a series of positive duodecimal number characters into an uint64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the duodecimal string was converted to an unsigned long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 */
#ifndef _di_f_conversion_string_to_duodecimal_unsigned_
  extern f_return_status f_conversion_string_to_duodecimal_unsigned(const f_string string, uint64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_duodecimal_unsigned_

/**
 * Convert a series of positive or negative hexidecimal number characters into an int64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   f_none if the hexidecimal string was converted to an signed long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 *   f_underflow (with error bit) on integer underflow.
 */
#ifndef _di_f_conversion_string_to_hexidecimal_signed_
  extern f_return_status f_conversion_string_to_hexidecimal_signed(const f_string string, int64_t *number, const f_string_location location, const bool negative);
#endif // _di_f_conversion_string_to_hexidecimal_signed_

/**
 * Convert a series of positive hexidecimal number characters into an uint64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the hexidecimal string was converted to an unsigned long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 */
#ifndef _di_f_conversion_string_to_hexidecimal_unsigned_
  extern f_return_status f_conversion_string_to_hexidecimal_unsigned(const f_string string, uint64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_hexidecimal_unsigned_

/**
 * Convert a series of positive or negative octal number characters into an int64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   f_none if the octal string was converted to an signed long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-octal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 */
#ifndef _di_f_conversion_string_to_octal_signed_
  extern f_return_status f_conversion_string_to_octal_signed(const f_string string, int64_t *number, const f_string_location location, const bool negative);
#endif // _di_f_conversion_string_to_octal_signed_

/**
 * Convert a series of positive octal number characters into an uint64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none if the octal string was converted to an unsigned long.
 *   f_invalid_number (with error bit) if no conversion was made due to non-octal values being found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_overflow (with error bit) on integer overflow.
 */
#ifndef _di_f_conversion_string_to_octal_unsigned_
  extern f_return_status f_conversion_string_to_octal_unsigned(const f_string string, uint64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_octal_unsigned_

/**
 * Convert a series of positive or negative number characters into an int64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will process signed statuses (+/-).
 * This will detect based types as follows:
 * - hexidecimals begin with either '0x' or '0X'.
 * - duodecimals begin with either '0d' or '0D'.
 * - octals begin with either '0o' or '0O'.
 * - binaries begin with either '0b' or '0B'.
 * - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * This function is similar to strtoll(), but the behavior of error handling and special bases are different.
 * In particular, octals are specified here with '0b' prefix or '0B' prefix instead of the ridiculous '0' prefix.
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none on success.
 *   f_no_data is returned if string only contains valid whitespace.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_number (with error bit) if parameter is not a number.
 *   f_overflow (with error bit) on integer overflow.
 *   f_underflow (with error bit) on integer underflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *
 * @see strtoll()
 */
#ifndef _di_f_conversion_string_to_number_signed_
  extern f_return_status f_conversion_string_to_number_signed(const f_string string, int64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_number_signed_

/**
 * Convert a series of positive number characters into an uint64_t.
 *
 * This will stop at one of the following: location.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 * This will detect based types as follows:
 * - hexidecimals begin with either '0x' or '0X'.
 * - duodecimals begin with either '0d' or '0D'.
 * - octals begin with either '0o' or '0O'.
 * - binaries begin with either '0b' or '0B'.
 * - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * This function is similar to strtoull(), but the behavior of error handling and special bases are different.
 * In particular, octals are specified here with '0b' prefix or '0B' prefix instead of the ridiculous '0' prefix.
 * Negative values are reported as such instead of being converted into the unsigned equivalent.
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param location
 *   The start/stop range to convert.
 *
 * @return
 *   f_none on success.
 *   f_no_data is returned if string only contains valid whitespace.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_number (with error bit) if parameter is not a number.
 *   f_negative_number (with error bit) on negative value.
 *   f_overflow (with error bit) on integer overflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *
 * @see strtoull()
 */
#ifndef _di_f_conversion_string_to_number_unsigned_
  extern f_return_status f_conversion_string_to_number_unsigned(const f_string string, uint64_t *number, const f_string_location location);
#endif // _di_f_conversion_string_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_h

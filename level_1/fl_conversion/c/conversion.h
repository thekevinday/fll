/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to convert one data type to another, such as a string to an integer.
 */
#ifndef _FL_conversion_h
#define _FL_conversion_h

// libc includes
#include <ctype.h>
#include <stdlib.h>

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
 * Convert a series of positive or negative binary number characters into a f_number_signed_t.
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
 *   F_none if the binary string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_binary_signed_
  extern f_return_status fl_conversion_string_to_binary_signed(const f_string_t string, f_number_signed_t *number, const f_string_range_t range, const bool negative);
#endif // _di_fl_conversion_string_to_binary_signed_

/**
 * Convert a series of positive binary number characters into a f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none if the binary string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_binary_unsigned_
  extern f_return_status fl_conversion_string_to_binary_unsigned(const f_string_t string, f_number_unsigned_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_binary_unsigned_

/**
 * Convert a series of positive or negative decimal number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   F_none if the decimal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_decimal_signed_
  extern f_return_status fl_conversion_string_to_decimal_signed(const f_string_t string, f_number_signed_t *number, const f_string_range_t range, const bool negative);
#endif // _di_fl_conversion_string_to_decimal_signed_

/**
 * Convert a series of positive decimal number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none if the decimal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_decimal_unsigned_
  extern f_return_status fl_conversion_string_to_decimal_unsigned(const f_string_t string, f_number_unsigned_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_decimal_unsigned_

/**
 * Convert a series of positive or negative duodecimal number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   F_none if the duodecimal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_duodecimal_signed_
  extern f_return_status fl_conversion_string_to_duodecimal_signed(const f_string_t string, f_number_signed_t *number, const f_string_range_t range, const bool negative);
#endif // _di_fl_conversion_string_to_duodecimal_signed_

/**
 * Convert a series of positive duodecimal number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none if the duodecimal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_duodecimal_unsigned_
  extern f_return_status fl_conversion_string_to_duodecimal_unsigned(const f_string_t string, f_number_unsigned_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_duodecimal_unsigned_

/**
 * Convert a series of positive or negative hexidecimal number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   F_none if the hexidecimal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_hexidecimal_signed_
  extern f_return_status fl_conversion_string_to_hexidecimal_signed(const f_string_t string, f_number_signed_t *number, const f_string_range_t range, const bool negative);
#endif // _di_fl_conversion_string_to_hexidecimal_signed_

/**
 * Convert a series of positive hexidecimal number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none if the hexidecimal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_hexidecimal_unsigned_
  extern f_return_status fl_conversion_string_to_hexidecimal_unsigned(const f_string_t string, f_number_unsigned_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_hexidecimal_unsigned_

/**
 * Convert a series of positive or negative octal number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 *
 * @return
 *   F_none if the octal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-octal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_octal_signed_
  extern f_return_status fl_conversion_string_to_octal_signed(const f_string_t string, f_number_signed_t *number, const f_string_range_t range, const bool negative);
#endif // _di_fl_conversion_string_to_octal_signed_

/**
 * Convert a series of positive octal number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param string
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none if the octal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *   F_number (with error bit) if no conversion was made due to non-octal values being found.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_string_to_octal_unsigned_
  extern f_return_status fl_conversion_string_to_octal_unsigned(const f_string_t string, f_number_unsigned_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_octal_unsigned_

/**
 * Convert a series of positive or negative number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
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
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoll()
 */
#ifndef _di_fl_conversion_string_to_number_signed_
  extern f_return_status fl_conversion_string_to_number_signed(const f_string_t string, f_number_signed_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_number_signed_

/**
 * Convert a series of positive number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
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
 * @param range
 *   The start/stop range to convert.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_positive (with error bit) on positive value (has a +, such as '+1', when only '1' is valid here).
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoull()
 */
#ifndef _di_fl_conversion_string_to_number_unsigned_
  extern f_return_status fl_conversion_string_to_number_unsigned(const f_string_t string, f_number_unsigned_t *number, const f_string_range_t range);
#endif // _di_fl_conversion_string_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_conversion_h

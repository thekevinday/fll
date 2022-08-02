/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provide means to convert one data type to another, such as a string to an integer.
 */
#ifndef _FL_conversion_h
#define _FL_conversion_h

// Libc includes.
#include <ctype.h>
#include <stdlib.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/conversion.h>

// FLL-1 conversion includes.
#include <fll/level_1/conversion/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a series of number characters into a f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 * @param buffer
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the binary string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_dynamic_partial_to_signed_
  extern f_status_t fl_conversion_dynamic_partial_to_signed(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_signed_t * const number);
#endif // _di_fl_conversion_dynamic_partial_to_signed_

/**
 * Convert a series of positive or negative number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will process signed statuses (+/-).
 * This will detect based types as follows:
 *   - hexidecimals begin with either '0x' or '0X'.
 *   - duodecimals begin with either '0d' or '0D'.
 *   - octals begin with either '0o' or '0O'.
 *   - binaries begin with either '0b' or '0B'.
 *   - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * This function is similar to strtoll(), but the behavior of error handling and special bases are different.
 * In particular, octals are specified here with '0b' prefix or '0B' prefix instead of the ridiculous '0' prefix.
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 * @param buffer
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoll()
 */
#ifndef _di_fl_conversion_dynamic_partial_to_signed_detect_
  extern f_status_t fl_conversion_dynamic_partial_to_signed_detect(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_signed_t * const number);
#endif // _di_fl_conversion_dynamic_partial_to_signed_detect_

/**
 * Convert a series of number characters into a f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 * @param buffer
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the binary string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_dynamic_partial_to_unsigned_
  extern f_status_t fl_conversion_dynamic_partial_to_unsigned(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number);
#endif // _di_fl_conversion_dynamic_partial_to_unsigned_

/**
 * Convert a series of positive number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: range.stop or a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 * This will detect based types as follows:
 *   - hexidecimals begin with either '0x' or '0X'.
 *   - duodecimals begin with either '0d' or '0D'.
 *   - octals begin with either '0o' or '0O'.
 *   - binaries begin with either '0b' or '0B'.
 *   - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * This function is similar to strtoull(), but the behavior of error handling and special bases are different.
 * In particular, octals are specified here with '0b' prefix or '0B' prefix instead of the ridiculous '0' prefix.
 * Negative values are reported as such instead of being converted into the unsigned equivalent.
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 *   This auto-detects the base and negative, ignoring the base number and negative flag.
 * @param buffer
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_positive (with error bit) on positive value (has a +, such as '+1', when only '1' is valid here).
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoull()
 */
#ifndef _di_fl_conversion_dynamic_partial_to_unsigned_detect_
  extern f_status_t fl_conversion_dynamic_partial_to_unsigned_detect(const fl_conversion_data_t data, const f_string_static_t buffer, const f_string_range_t range, f_number_unsigned_t * const number);
#endif // _di_fl_conversion_dynamic_partial_to_unsigned_detect_

/**
 * Convert a series of number characters into a f_number_signed_t.
 *
 * This will stop at one of the following: a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 * @param buffer
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the binary string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_dynamic_to_signed_
  extern f_status_t fl_conversion_dynamic_to_signed(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_signed_t * const number);
#endif // _di_fl_conversion_dynamic_to_signed_

/**
 * Convert a series of positive or negative number characters into an f_number_signed_t.
 *
 * This will stop at one of the following: a non-digit.
 * This will ignore NULL values.
 * This will process signed statuses (+/-).
 * This will detect based types as follows:
 *   - hexidecimals begin with either '0x' or '0X'.
 *   - duodecimals begin with either '0d' or '0D'.
 *   - octals begin with either '0o' or '0O'.
 *   - binaries begin with either '0b' or '0B'.
 *   - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * This function is similar to strtoll(), but the behavior of error handling and special bases are different.
 * In particular, octals are specified here with '0b' prefix or '0B' prefix instead of the ridiculous '0' prefix.
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 *   This auto-detects the base and negative, ignoring the base number and negative flag.
 * @param buffer
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoll()
 */
#ifndef _di_fl_conversion_dynamic_to_signed_detect_
  extern f_status_t fl_conversion_dynamic_to_signed_detect(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_signed_t * const number);
#endif // _di_fl_conversion_dynamic_to_signed_detect_

/**
 * Convert a series of number characters into a f_number_unsigned_t.
 *
 * This will stop at one of the following: a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 * @param buffer
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the binary string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_conversion_dynamic_to_unsigned_
  extern f_status_t fl_conversion_dynamic_to_unsigned(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_unsigned_t * const number);
#endif // _di_fl_conversion_dynamic_to_unsigned_

/**
 * Convert a series of positive number characters into an f_number_unsigned_t.
 *
 * This will stop at one of the following: a non-digit.
 * This will ignore NULL values.
 * This will not process signed statuses (+/-).
 * This will detect based types as follows:
 *   - hexidecimals begin with either '0x' or '0X'.
 *   - duodecimals begin with either '0d' or '0D'.
 *   - octals begin with either '0o' or '0O'.
 *   - binaries begin with either '0b' or '0B'.
 *   - decimal is used for all other cases.
 *
 * Leading 0's and whitespace are ignored.
 * Whitespace after the first digit is considered invalid.
 *
 * This function is similar to strtoull(), but the behavior of error handling and special bases are different.
 * In particular, octals are specified here with '0b' prefix or '0B' prefix instead of the ridiculous '0' prefix.
 * Negative values are reported as such instead of being converted into the unsigned equivalent.
 *
 * @param data
 *   Conversion data for specifying things such as treating this as a negative number.
 *   This auto-detects the base and negative, ignoring the base number and negative flag.
 * @param buffer
 *   The string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_base_not (with error bit) if no supported or valid base unit is provided.
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_positive (with error bit) on positive value (has a +, such as '+1', when only '1' is valid here).
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoull()
 */
#ifndef _di_fl_conversion_dynamic_to_unsigned_detect_
  extern f_status_t fl_conversion_dynamic_to_unsigned_detect(const fl_conversion_data_t data, const f_string_static_t buffer, f_number_unsigned_t * const number);
#endif // _di_fl_conversion_dynamic_to_unsigned_detect_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_conversion_h

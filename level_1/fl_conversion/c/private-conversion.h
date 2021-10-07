/**
 * FLL - Level 1
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_conversion_h
#define _PRIVATE_FL_conversion_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fl_conversion_string_to_binary_signed().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param location
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the binary string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_binary_signed_)
  extern f_status_t private_fl_conversion_string_to_binary_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_binary_signed_)

/**
 * Private implementation of fl_conversion_string_to_binary_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
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
 *   F_number (with error bit) if no conversion was made due to non-binary values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_binary_unsigned_)
  extern f_status_t private_fl_conversion_string_to_binary_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_binary_unsigned_)

/**
 * Private implementation of fl_conversion_string_to_decimal_signed().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the decimal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_decimal_signed_)
  extern f_status_t private_fl_conversion_string_to_decimal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_decimal_signed_)

/**
 * Private implementation of fl_conversion_string_to_decimal_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the decimal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-decimal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_decimal_unsigned_)
  extern f_status_t private_fl_conversion_string_to_decimal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_decimal_unsigned_)

/**
 * Private implementation of fl_conversion_string_to_duodecimal_signed().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the duodecimal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_duodecimal_signed_)
  extern f_status_t private_fl_conversion_string_to_duodecimal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_duodecimal_signed_)

/**
 * Private implementation of fl_conversion_string_to_duodecimal_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the duodecimal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-duodecimal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_duodecimal_unsigned_)
  extern f_status_t private_fl_conversion_string_to_duodecimal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_duodecimal_unsigned_)

/**
 * Private implementation of fl_conversion_string_to_hexidecimal_signed().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the hexidecimal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_hexidecimal_signed_)
  extern f_status_t private_fl_conversion_string_to_hexidecimal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_hexidecimal_signed_)

/**
 * Private implementation of fl_conversion_string_to_hexidecimal_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the hexidecimal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-hexidecimal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_hexidecimal_unsigned_)
  extern f_status_t private_fl_conversion_string_to_hexidecimal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_hexidecimal_unsigned_)

/**
 * Private implementation of fl_conversion_string_to_octal_signed().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param negative
 *   Set to 0 to treat string as a positive number, 1 for as a negative number.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the octal string was converted to an signed long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-octal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_octal_signed_)
  extern f_status_t private_fl_conversion_string_to_octal_signed(const f_string_t string, const f_string_range_t range, const bool negative, f_number_signed_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_octal_signed_)

/**
 * Private implementation of fl_conversion_string_to_octal_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to convert.
 * @param range
 *   The start/stop range to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none if the octal string was converted to an unsigned long.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_number (with error bit) if no conversion was made due to non-octal values being found.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_octal_unsigned_)
  extern f_status_t private_fl_conversion_string_to_octal_unsigned(const f_string_t string, const f_string_range_t range, f_number_unsigned_t *number);
#endif // !defined(_di_fl_conversion_string_to_binary_signed_) || !defined(_di_fl_conversion_string_to_number_signed_) || !(_di_fl_conversion_string_to_octal_unsigned_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_conversion_h

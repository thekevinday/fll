/**
 * FLL - Level 1
 *
 * Project: Conversion
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
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
 * Private implementation of fl_conversion_dynamic_to_binary_signed().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param flag
 *   Conversion data flags.
 * @param string
 *   The string to convert.
 * @param length
 *   The length of the string to convert.
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
 *
 * @see fl_conversion_dynamic_partial_to_binary_signed()
 * @see fl_conversion_dynamic_partial_to_signed_detect()
 * @see fl_conversion_dynamic_to_binary_signed()
 * @see fl_conversion_dynamic_to_signed_detect()
 */
#if !defined(_di_fl_conversion_dynamic_partial_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)
  extern f_status_t private_fl_conversion_dynamic_to_binary_signed(const uint16_t flag, const f_string_t string, const f_number_unsigned_t length, f_number_signed_t * const number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_conversion_dynamic_partial_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)

/**
 * Private implementation of fl_conversion_dynamic_to_binary_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param flag
 *   Conversion data flags.
 * @param string
 *   The string to convert.
 * @param length
 *   The length of the string to convert.
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
 *
 * @see fl_conversion_dynamic_partial_to_binary_unsigned()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fl_conversion_dynamic_to_binary_unsigned()
 * @see fl_conversion_dynamic_to_unsigned_detect()
 */
#if !defined(_di_fl_conversion_dynamic_partial_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)
  extern f_status_t private_fl_conversion_dynamic_to_binary_unsigned(const uint16_t flag, const f_string_t string, const f_number_unsigned_t length, f_number_unsigned_t * const number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_conversion_dynamic_partial_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_binary_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)

/**
 * Private implementation for converting for some given base unit.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param data
 *   Conversion data base unit and flags.
 * @param string
 *   The string to convert.
 * @param length
 *   The length of the string to convert.
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
 *
 * @see fl_conversion_dynamic_partial_to_unsigned()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fl_conversion_dynamic_to_decimal_unsigned()
 * @see fl_conversion_dynamic_to_unsigned_detect()
 */
#if !defined(_di_fl_conversion_dynamic_partial_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)
  extern f_status_t private_fl_conversion_dynamic_to_base_signed(const fl_conversion_data_t data, const f_string_t string, const f_number_unsigned_t length, f_number_signed_t * const number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_conversion_dynamic_partial_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_signed_) || !defined(_di_fl_conversion_dynamic_to_signed_detect_)

/**
 * Private implementation of fl_conversion_dynamic_to_decimal_unsigned().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param data
 *   Conversion data base unit and flags.
 * @param string
 *   The string to convert.
 * @param length
 *   The length of the string to convert.
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
 *
 * @see fl_conversion_dynamic_partial_to_unsigned()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fl_conversion_dynamic_to_decimal_unsigned()
 * @see fl_conversion_dynamic_to_unsigned_detect()
 */
#if !defined(_di_fl_conversion_dynamic_partial_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)
  extern f_status_t private_fl_conversion_dynamic_to_base_unsigned(const fl_conversion_data_t data, const f_string_t string, const f_number_unsigned_t length, f_number_unsigned_t * const number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_conversion_dynamic_partial_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_to_decimal_unsigned_) || !defined(_di_fl_conversion_dynamic_to_unsigned_detect_)

/**
 * Private implementation of fl_conversion_dynamic_to_signed_detect().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param flag
 *   Conversion data flags.
 * @param string
 *   The string to convert.
 * @param length
 *   The length of the string to convert.
 * @param number
 *   This will store the value of the converted string.
 *   This value is only changed on success.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts with a null (length is 0).
 *
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_number_underflow (with error bit) on integer underflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_fl_conversion_dynamic_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_)
  extern f_status_t private_fl_conversion_dynamic_to_signed_detect(const uint16_t flag, const f_string_t string, const f_number_unsigned_t length, f_number_signed_t * const number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_conversion_dynamic_to_signed_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_signed_detect_)

/**
 * Private implementation of fl_conversion_dynamic_to_unsigned_detect().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param flag
 *   Conversion data flags.
 *   This auto-detects the base and negative, ignoring the base number and negative flag.
 * @param string
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
 *   F_number_negative on negative value (has a -, such as '-1').
 *   F_number_positive on positive value (has a +, such as '+1').
 *
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_decimal (with error bit) if number has a decimal digit.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see strtoull()
 */
#if !defined(_di_fl_conversion_dynamic_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_)
  extern f_status_t private_fl_conversion_dynamic_to_unsigned_detect(const uint16_t flag, const f_string_t string, const f_number_unsigned_t length, f_number_unsigned_t * const number) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_conversion_dynamic_to_unsigned_detect_) || !defined(_di_fl_conversion_dynamic_partial_to_unsigned_detect_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_conversion_h

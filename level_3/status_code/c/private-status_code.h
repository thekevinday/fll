/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_status_code_h
#define _PRIVATE_status_code_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the 'check' processes, such as --fine or --error.
 *
 * @param data
 *   The program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   f_none on success.
 *   f_no_data (with error bit) if string starts wth a null (length is 0).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_number_invalid (with error bit) if parameter is not a number.
 *   f_number_negative (with error bit) on negative value.
 *   f_number_overflow (with error bit) on integer overflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 */
#ifndef _di_status_code_process_check_
  extern f_return_status status_code_process_check(const status_code_data data, const f_string value);
#endif // _di_status_code_process_check_

/**
 * Perform the 'number' processes, such as --number.
 *
 * @param data
 *   The program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   f_none on success.
 *   f_no_data (with error bit) if string is empty.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_status_code_process_number_
  extern f_return_status status_code_process_number(const status_code_data data, const f_string value);
#endif // _di_status_code_process_number_

/**
 * Perform the normal processes.
 *
 * @param data
 *   The program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   f_none on success.
 *   f_no_data (with error bit) if string starts wth a null (length is 0).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_number_invalid (with error bit) if parameter is not a number.
 *   f_number_negative (with error bit) on negative value.
 *   f_number_overflow (with error bit) on integer overflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 */
#ifndef _di_status_code_process_normal_
  extern f_return_status status_code_process_normal(const status_code_data data, const f_string value);
#endif // _di_status_code_process_normal_

/**
 * Convert the value string to the number, reporting any errors.
 *
 * @param data
 *   The program data.
 * @param value
 *   The parameter value to process.
 * @param number
 *   The converted number.
 *   Will not be updated on error.
 *
 * @return
 *   f_none on success.
 *   f_no_data (with error bit) if string starts wth a null (length is 0).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_number_invalid (with error bit) if parameter is not a number.
 *   f_number_negative (with error bit) on negative value.
 *   f_number_overflow (with error bit) on integer overflow.
 *   f_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 */
#ifndef _di_status_code_convert_number_
  extern f_return_status status_code_convert_number(const status_code_data data, const f_string value, f_number_unsigned *number);
#endif // _di_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_status_code_h

/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_status_code_h
#define _PRIVATE_fss_status_code_h

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
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *
 *   Errors from (with error bit): fss_status_code_convert_number().
 *
 * @see fss_status_code_convert_number()
 */
#ifndef _di_fss_status_code_process_check_
  extern f_return_status fss_status_code_process_check(const fss_status_code_data data, const f_string value) f_gcc_attribute_visibility_internal;
#endif // _di_fss_status_code_process_check_

/**
 * Perform the 'number' processes, such as --number.
 *
 * @param data
 *   The program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string is empty.
 *
 *   Errors from (with error bit): fl_console_parameter_to_number_unsigned().
 *   Errors from (with error bit): fll_fss_status_from_string().
 *
 * @see fl_console_parameter_to_number_unsigned()
 * @see fll_fss_status_from_string()
 */
#ifndef _di_fss_status_code_process_number_
  extern f_return_status fss_status_code_process_number(const fss_status_code_data data, const f_string value) f_gcc_attribute_visibility_internal;
#endif // _di_fss_status_code_process_number_

/**
 * Perform the normal processes.
 *
 * @param data
 *   The program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fll_fss_status_from_string().
 *   Errors from (with error bit): fss_status_code_convert_number().
 *
 * @see fll_fss_status_from_string()
 * @see fss_status_code_convert_number()
 */
#ifndef _di_fss_status_code_process_normal_
  extern f_return_status fss_status_code_process_normal(const fss_status_code_data data, const f_string value) f_gcc_attribute_visibility_internal;
#endif // _di_fss_status_code_process_normal_

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
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_incomplete_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_console_parameter_to_number_unsigned().
 *
 * @see fl_console_parameter_to_number_unsigned()
 */
#ifndef _di_fss_status_code_convert_number_
  extern f_return_status fss_status_code_convert_number(const fss_status_code_data data, const f_string value, f_number_unsigned *number) f_gcc_attribute_visibility_internal;
#endif // _di_fss_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_status_code_h

/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_fss_status_code_h
#define _PRIVATE_fss_status_code_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the 'check' processes, such as --fine or --error.
 *
 * @param main
 *   The main program data.
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
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *
 *   Errors (with error bit) from: fss_status_code_convert_number().
 *
 * @see fss_status_code_convert_number()
 */
#ifndef _di_fss_status_code_process_check_
  extern f_status_t fss_status_code_process_check(fll_program_data_t * const main, const f_string_static_t value) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_process_check_

/**
 * Perform the 'number' processes, such as --number.
 *
 * @param main
 *   The main program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string is empty.
 *
 *   Errors (with error bit) from: fl_console_parameter_to_number_unsigned().
 *   Errors (with error bit) from: fll_fss_status_string_from().
 *
 * @see fl_console_parameter_to_number_unsigned()
 * @see fll_fss_status_string_from()
 */
#ifndef _di_fss_status_code_process_number_
  extern f_status_t fss_status_code_process_number(fll_program_data_t * const main, const f_string_static_t value) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_process_number_

/**
 * Perform the normal processes.
 *
 * @param main
 *   The main program data.
 * @param value
 *   The parameter value to process.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fll_fss_status_string_from().
 *   Errors (with error bit) from: fss_status_code_convert_number().
 *
 * @see fll_fss_status_string_from()
 * @see fss_status_code_convert_number()
 */
#ifndef _di_fss_status_code_process_normal_
  extern f_status_t fss_status_code_process_normal(fll_program_data_t * const main, const f_string_static_t value) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_process_normal_

/**
 * Convert the value string to the number, reporting any errors.
 *
 * @param main
 *   The main program data.
 * @param value
 *   The parameter value to process.
 * @param number
 *   The converted number.
 *   Will not be updated on error.
 *
 * @return
 *   F_none on success.
 *   F_data_not if string starts wth a null (length is 0).
 *   F_complete_not_utf (with error bit) if an incomplete UTF-8 fragment is found.
 *   F_number (with error bit) if parameter is not a number.
 *   F_number_negative (with error bit) on negative value.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_console_parameter_to_number_unsigned().
 *
 * @see fl_console_parameter_to_number_unsigned()
 */
#ifndef _di_fss_status_code_convert_number_
  extern f_status_t fss_status_code_convert_number(fll_program_data_t * const main, const f_string_static_t value, f_number_unsigned_t *number) F_attribute_visibility_internal_d;
#endif // _di_fss_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_status_code_h

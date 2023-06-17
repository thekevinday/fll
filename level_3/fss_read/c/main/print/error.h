/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_print_error_h
#define _fss_read_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_fss_read_print_error_
  extern f_status_t fss_read_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_fss_read_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fss_read_print_error_file_
  extern f_status_t fss_read_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fss_read_print_error_file_

/**
 * Print an error message about the parameter requires something that is explained by the message parameter.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param message
 *   The message to print regarding why the message should be displayed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_fss_read_print_error_parameter_requires_message_
  extern f_status_t fss_read_print_error_parameter_requires_message(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t message);
#endif // _di_fss_read_print_error_parameter_requires_message_

/**
 * Print an error message about the parameter not allowing a value before another value.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value
 *   The parameter value that cannot be specified before the "before" function parameter.
 * @param before
 *   The parameter value that is before the "value" function parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_fss_read_print_error_parameter_value_before_value_number_
  extern f_status_t fss_read_print_error_parameter_value_before_value_number(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_number_unsigned_t value, const f_number_unsigned_t before);
#endif // _di_fss_read_print_error_parameter_value_before_value_number_

/**
 * Print an error message about the parameter only allowing the given value to be specified one time.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to the first parameter.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param value
 *   The parameter value that is already specified.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_fss_read_print_error_parameter_value_once_only_number_
  extern f_status_t fss_read_print_error_parameter_value_once_only_number(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_number_unsigned_t value);
#endif // _di_fss_read_print_error_parameter_value_once_only_number_

/**
 * Print an message about a multiple Content being unsupported for a particular standard.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_fss_read_print_error_one_content_only_
  extern f_status_t fss_read_print_error_one_content_only(fl_print_t * const print);
#endif // _di_fss_read_print_error_one_content_only_

/**
 * Print an error message about a parameter New Line character '\n' (U+000A) being unsupported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_fss_read_print_error_unsupported_eol_
  extern f_status_t fss_read_print_error_unsupported_eol(fl_print_t * const print);
#endif // _di_fss_read_print_error_unsupported_eol_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_print_error_h

/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_print_error_h
#define _status_code_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_status_code_print_error_
  extern f_status_t status_code_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_status_code_print_error_

/**
 * Print an error message when error parameter and warning parameter are specified without number parameter.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_status_code_print_error_cannot_error_warning_number_
  extern f_status_t status_code_print_error_cannot_error_warning_number(fl_print_t * const print);
#endif // _di_status_code_print_error_cannot_error_warning_number_

/**
 * Print an error message when no status codes are provided.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_error_no_status_codes_
  extern f_status_t status_code_print_error_no_status_codes(fl_print_t * const print);
#endif // _di_status_code_print_error_no_status_codes_

/**
 * Print an error message when a callback from status_code_setting_t is invalid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the callback setting that is invalid.
 *   This should either be 'status_string_from' or 'status_string_to'.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_status_code_print_error_invalid_callback_
  extern f_status_t status_code_print_error_invalid_callback(fl_print_t * const print, const f_string_t name);
#endif // _di_status_code_print_error_invalid_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_error_h

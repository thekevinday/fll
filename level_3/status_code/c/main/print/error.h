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
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_status_code_print_error_
  extern f_status_t status_code_print_error(status_code_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_status_code_print_error_

/**
 * Print an error message when error parameter and warning parameter are specified without number parameter.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_status_code_print_error_cannot_error_warning_number_
  extern f_status_t status_code_print_error_cannot_error_warning_number(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_error_cannot_error_warning_number_

/**
 * Print an error message when no status codes are provided.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_error_no_status_codes_
  extern f_status_t status_code_print_error_no_status_codes(status_code_setting_t * const setting, const fl_print_t print);
#endif // _di_status_code_print_error_no_status_codes_

/**
 * Print an error message when a callback from status_code_setting_t is invalid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name of the callback setting that is invalid.
 *   This should either be 'status_string_from' or 'status_string_to'.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_status_code_print_error_invalid_callback_
  extern f_status_t status_code_print_error_invalid_callback(status_code_setting_t * const setting, const fl_print_t print, const f_string_t name);
#endif // _di_status_code_print_error_invalid_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_error_h

/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_print_error_h
#define _fss_write_print_error_h

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
 */
#ifndef _di_fss_write_print_error_
  extern f_status_t fss_write_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_fss_write_print_error_

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
#ifndef _di_fss_write_print_error_file_
  extern f_status_t fss_write_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fss_write_print_error_file_

/**
 * Print an error message about the object and content parameters not being specified at least the same number of times when partial is not requested.
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
#ifndef _di_fss_write_print_error_parameter_same_times_at_least_
  extern f_status_t fss_write_print_error_parameter_same_times_at_least(fl_print_t * const print);
#endif // _di_fss_write_print_error_parameter_same_times_at_least_

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
#ifndef _di_fss_write_print_error_one_content_only_
  extern f_status_t fss_write_print_error_one_content_only(fl_print_t * const print);
#endif // _di_fss_write_print_error_one_content_only_

/**
 * Print error when prepend parameter has something other than white space.
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
#ifndef _fss_write_print_error_prepend_only_whitespace_
  extern f_status_t fss_write_print_error_prepend_only_whitespace(fl_print_t * const print);
#endif // _fss_write_print_error_prepend_only_whitespace_

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
#ifndef _di_fss_write_print_error_unsupported_eol_
  extern f_status_t fss_write_print_error_unsupported_eol(fl_print_t * const print);
#endif // _di_fss_write_print_error_unsupported_eol_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_print_error_h

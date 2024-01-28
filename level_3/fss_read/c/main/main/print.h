/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_read_main_print_h
#define _fss_read_main_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error message about a value given to the --as parameter being unknown.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param value
 *   A string representing the value that is of an unknown format.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fss_read_main_print_error_format_unknown_
  extern f_status_t fss_read_main_print_error_format_unknown(fl_print_t * const print, const f_string_static_t value);
#endif // _di_fss_read_main_print_error_format_unknown_

/**
 * Print an error message about a value given to the --as parameter changed after re-loading.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param previous
 *   A string representing the value of the previous --as parameter.
 * @param current
 *   A string representing the value of the current --as parameter.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fss_read_main_print_error_parameter_as_changed_
  extern f_status_t fss_read_main_print_error_parameter_as_changed(fl_print_t * const print, const f_string_static_t previous, const f_string_static_t current);
#endif // _di_fss_read_main_print_error_parameter_as_changed_

/**
 * Print help for "main" fss_read.
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
 */
#ifndef _di_fss_read_print_main_message_help_
  extern f_status_t fss_read_main_print_message_help(fl_print_t * const print);
#endif // _di_fss_read_print_main_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_main_print_h

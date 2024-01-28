/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fss_read_payload_print_h
#define _fss_read_payload_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the end of an Object (which is often the start of Content).
 *
 * This locks, uses, and unlocks the file stream.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 */
#ifndef _di_fss_read_payload_print_data_object_end_
  extern f_status_t fss_read_payload_print_data_object_end(fl_print_t * const print);
#endif // _di_fss_read_payload_print_data_object_end_

/**
 * Print an error message about the payload parameter not having a valid value.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The print.custom is expected to be of type fss_read_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param value
 *   The parameter value that is invalid.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if a parameter is NULL.
 */
#ifndef _di_fss_read_payload_print_error_parameter_value_payload_
  extern f_status_t fss_read_payload_print_error_parameter_value_payload(fl_print_t * const print, const f_string_static_t value);
#endif // _di_fss_read_payload_print_error_parameter_value_payload_

/**
 * Print help for FSS-000E (Payload).
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
#ifndef _di_fss_read_payload_print_message_help_
  extern f_status_t fss_read_payload_print_message_help(fl_print_t * const print);
#endif // _di_fss_read_payload_print_message_help_

/**
 * Print payload-specific help parameters details for FSS-000E (Payload).
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
#ifndef _di_fss_read_payload_print_message_help_payload_
  extern f_status_t fss_read_payload_print_message_help_payload(fl_print_t * const print);
#endif // _di_fss_read_payload_print_message_help_payload_

/**
 * Print payload-specific help special parameters for FSS-000E (Payload).
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
#ifndef _di_fss_read_payload_print_message_help_special_
  extern f_status_t fss_read_payload_print_message_help_special(fl_print_t * const print);
#endif // _di_fss_read_payload_print_message_help_special_

/**
 * Print error or warning message about the "payload" not being found.
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
 * @see fll_error_print()
 */
#ifndef _di_fss_read_payload_print_problem_payload_missing_
  extern f_status_t fss_read_payload_print_problem_payload_missing(fl_print_t * const print);
#endif // _di_fss_read_payload_print_problem_payload_missing_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_payload_print_h

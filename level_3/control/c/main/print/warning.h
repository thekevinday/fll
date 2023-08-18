/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_print_warning_h
#define _control_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a warning message about a response header being repeated (when debugging).
 *
 * This program currently does not support multiple headers for any given valid header Object.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param response_header
 *   The repeated response header.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_warning_packet_header_duplicate_object_
  extern f_status_t control_print_warning_packet_header_duplicate_object(fl_print_t * const print, const f_string_static_t response_header);
#endif // _di_control_print_warning_packet_header_duplicate_object_

/**
 * Print a warning message about a failure when calling f_status_string_to().
 *
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param status_of
 *   The status code to be translating to a string.
 * @param status_error
 *   The status code representing the failure status returned by f_status_string_to().
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_status_string_to()
 */
#ifndef _di_control_print_warning_packet_process_string_to_failed_
  extern f_status_t control_print_warning_packet_process_string_to_failed(fl_print_t * const print, const f_status_t status_of, const f_status_t status_error);
#endif // _di_control_print_warning_packet_process_string_to_failed_

/**
 * Print a warning about a packet response returning as busy.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param header
 *   The control payload packet header data.
 * @param status
 *   A string representing the name of the status code from header.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_warning_packet_response_busy_
  extern f_status_t control_print_warning_packet_response_busy(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status);
#endif // _di_control_print_warning_packet_response_busy_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_print_warning_h

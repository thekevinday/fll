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
#ifndef _control_print_message_h
#define _control_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
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
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fl_print_format()
 *
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_standard()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_control_print_message_help_
  extern f_status_t control_print_message_help(fl_print_t * const print);
#endif // _di_control_print_message_help_

/**
 * Print a message about a packet response.
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
#ifndef _di_control_print_message_packet_response_
  extern f_status_t control_print_message_packet_response(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status);
#endif // _di_control_print_message_packet_response_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_print_message_h

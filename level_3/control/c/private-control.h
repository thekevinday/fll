/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_control_h
#define _PRIVATE_control_h

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Identify the command code the given name represents.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param command
 *   The parameter representing a command.
 *
 * @return
 *   F_found on success.
 *   F_found_not if name is unknown.
 */
#ifndef _di_control_command_identify_
  extern f_status_t control_command_identify(fll_program_data_t * const main, control_data_t * const data, const f_string_static_t command) F_attribute_visibility_internal_d;
#endif // _di_control_command_identify_

/**
 * Verify that the additional parameters are reasonably correct for the identified command.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 */
#ifndef _di_control_command_verify_
  extern f_status_t control_command_verify(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_command_verify_

/**
 * Build the payload, storing it in the large cache.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 *
 * @return
 *   F_none on success.
 *
 *   F_too_large (with error bit) If the message is too large for the packet format to transmit.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_append()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_control_payload_build_
  extern f_status_t control_payload_build(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_payload_build_

/**
 * Receive the response from the remote socket, storing it in the large cache.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 *
 * @return
 *   F_none on success.
 *
 *   F_packet_not (with error bit) If the received packet is not a valid packet.
 *
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_control_payload_receive_
  extern f_status_t control_payload_receive(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_payload_receive_

/**
 * Send the payload to the remote socket, getting the payload from the large cache.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 */
#ifndef _di_control_payload_send_
  extern f_status_t control_payload_send(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_payload_send_
/**
 * Load and process the control settings file.
 *
 * This identifies and attempts to connect to the socket.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *   F_socket_not (with error bit) on socket related error preventing the socket from being created or connected to.
 *
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_file_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: f_socket_connect().
 *   Errors (with error bit) from: f_socket_create().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_append_assure().
 *   Errors (with error bit) from: f_string_dynamic_append_nulless().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *   Errors (with error bit) from: fl_fss_apply_delimit().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *
 * @see f_file_exists()
 * @see f_file_open()
 * @see f_file_stream_read()
 * @see f_socket_connect()
 * @see f_socket_create()
 * @see f_string_append()
 * @see f_string_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_partial_append_nulless()
 * @see f_string_dynamics_resize()
 * @see fl_fss_apply_delimit()
 * @see fll_fss_extended_read()
 */
#ifndef _di_control_settings_load_
  extern f_status_t control_settings_load(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_settings_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_h

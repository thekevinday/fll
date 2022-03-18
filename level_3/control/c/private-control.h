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
 * Identify the action code the given name represents.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param action
 *   The parameter representing a action.
 *
 * @return
 *   action type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_control_action_identify_
  extern uint8_t control_action_identify(fll_program_data_t * const main, control_data_t * const data, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_action_identify_

/**
 * Verify that the additional parameters are reasonably correct for the identified action.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 */
#ifndef _di_control_action_verify_
  extern f_status_t control_action_verify(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_action_verify_

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
#ifndef _di_control_packet_build_
  extern f_status_t control_packet_build(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_packet_build_

/**
 * Receive the response from the remote socket, storing it in the large cache.
 *
 * @todo consider returning F_header (with error bit) fo most header processing errors rather than individual status codes.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param header
 *   The control payload packet header data.
 *
 * @return
 *   F_none on success.
 *
 *   F_header_not (with error bit) If there is a problem processing the packet header.
 *   F_memory_not (with error bit) On out of memory issues (this is passed through from called functions).
 *   F_packet_not (with error bit) If the received packet is not a valid packet or not a supported packet structure.
 *   F_payload_not (with error bit) If there is a problem processing the packet payload.
 *   F_too_large (with error bit) If the received packet specifies a size that is too large or the actual size is larger than the specified size.
 *   F_too_small (with error bit) If the received packet actual size is smaller than the specified size.
 *
 *   Errors (with error bit) from: f_socket_read().
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_number_unsigned().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 *
 * @see f_socket_read()
 * @see f_string_dynamic_increase_by()
 * @see fl_conversion_dynamic_partial_to_number_unsigned()
 * @see fl_fss_apply_delimit()
 * @see fll_fss_extended_read()
 * @see fll_fss_basic_list_read()
 * @see fll_status_string_from()
 */
#ifndef _di_control_packet_receive_
  extern f_status_t control_packet_receive(fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) F_attribute_visibility_internal_d;
#endif // _di_control_packet_receive_

/**
 * Process the received and loaded packet.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param header
 *   The control payload packet header data.
 *
 * @return
 *   F_done on success but action has no success or failure states.
 *   F_success on success.
 *
 *   F_busy (with error bit)
 *   F_failure (with error bit) on success but controller returned failure for action.
 *   Any error (with error bit) on failure where the error is defined by the controller service.
 */
#ifndef _di_control_packet_process_
  extern f_status_t control_packet_process(fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) F_attribute_visibility_internal_d;
#endif // _di_control_packet_process_

/**
 * Send the payload to the remote socket, getting the payload from the large cache.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 */
#ifndef _di_control_packet_send_
  extern f_status_t control_packet_send(fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_packet_send_
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

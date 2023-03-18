/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_control_h
#define _PRIVATE_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Verify that the additional parameters are reasonably correct for the identified action.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) on parameter validation/verification failure.
 */
#ifndef _di_control_action_verify_
  extern f_status_t control_action_verify(const fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
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
 *   Errors (with error bit) from: fll_fss_extended_write().
 *   Errors (with error bit) from: fll_fss_payload_write().
 *
 * @see f_string_append()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_control_packet_build_
  extern f_status_t control_packet_build(const fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_packet_build_

/**
 * Given the header buffer, get the flag bits.
 *
 * @param buffer
 *   The buffer to read the length of and get the
 *
 * @return
 *   The 8-bit number representing the flags.
 */
#ifndef _di_control_packet_header_flag_
  extern uint8_t control_packet_header_flag(const uint8_t buffer[]) F_attribute_visibility_internal_d;
#endif // _di_control_packet_header_flag_

/**
 * Given the header buffer, get the length bits.
 *
 * The endianness is automatically detected and swapped by this function to guarantee host order bytes.
 *
 * @param is_big
 *   If TRUE, then the length in the buffer is in big endian format.
 *   If FALSE, then the length in the buffer is in little endian format.
 * @param buffer
 *   The buffer to read the length of and get the
 *
 * @return
 *   The 32-bit number representing the length.
 */
#ifndef _di_control_packet_header_length_
  extern uint32_t control_packet_header_length(const bool is_big, const uint8_t buffer[]) F_attribute_visibility_internal_d;
#endif // _di_control_packet_header_length_

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
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: fll_fss_extended_read().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 *
 * @see f_socket_read()
 * @see f_string_dynamic_increase_by()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see f_fss_apply_delimit()
 * @see fll_fss_extended_read()
 * @see fll_fss_basic_list_read()
 * @see fll_status_string_from()
 */
#ifndef _di_control_packet_receive_
  extern f_status_t control_packet_receive(const fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) F_attribute_visibility_internal_d;
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
 *   F_known_not (with error bit) if the Payload type is unknown.
 *   Any error (with error bit) on failure where the error is defined by the controller service.
 */
#ifndef _di_control_packet_process_
  extern f_status_t control_packet_process(const fll_program_data_t * const main, control_data_t * const data, control_payload_header_t * const header) F_attribute_visibility_internal_d;
#endif // _di_control_packet_process_

/**
 * Send the payload to the remote socket, getting the payload from the large cache.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_socket_write().
 *
 * @see f_socket_write()
 */
#ifndef _di_control_packet_send_
  extern f_status_t control_packet_send(const fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
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
 *   F_interrupt (with error bit) on interrupt signal received.
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
 *   Errors (with error bit) from: f_fss_apply_delimit().
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
 * @see f_fss_apply_delimit()
 * @see fll_fss_extended_read()
 */
#ifndef _di_control_settings_load_
  extern f_status_t control_settings_load(const fll_program_data_t * const main, control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_settings_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_h

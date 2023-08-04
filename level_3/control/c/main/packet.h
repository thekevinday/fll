/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the packet functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_packet_h
#define _control_packet_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Build the payload, storing it in the large cache.
 *
 * @param main
 *   The main program data.
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
  extern void control_packet_build(control_main_t * const main);
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
  extern uint8_t control_packet_header_flag(const uint8_t buffer[]);
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
  extern uint32_t control_packet_header_length(const bool is_big, const uint8_t buffer[]);
#endif // _di_control_packet_header_length_

/**
 * Receive the response from the remote socket, storing it in the large cache.
 *
 * @todo consider returning F_header (with error bit) fo most header processing errors rather than individual status codes.
 *
 * @param main
 *   The main program data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     F_header_not (with error bit) If there is a problem processing the packet header.
 *     F_memory_not (with error bit) On out of memory issues (this is passed through from called functions).
 *     F_packet_not (with error bit) If the received packet is not a valid packet or not a supported packet structure.
 *     F_payload_not (with error bit) If there is a problem processing the packet payload.
 *     F_too_large (with error bit) If the received packet specifies a size that is too large or the actual size is larger than the specified size.
 *     F_too_small (with error bit) If the received packet actual size is smaller than the specified size.
 *
 *     Errors (with error bit) from: f_socket_read().
 *     Errors (with error bit) from: f_string_dynamic_increase_by().
 *     Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *     Errors (with error bit) from: fll_fss_extended_read().
 *     Errors (with error bit) from: fll_fss_basic_list_read().
 * @param header
 *   The control payload packet header data.
 *
 * @see f_socket_read()
 * @see f_string_dynamic_increase_by()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see f_fss_apply_delimit()
 * @see fl_status_string_from()
 * @see fll_fss_extended_read()
 * @see fll_fss_basic_list_read()
 */
#ifndef _di_control_packet_receive_
  extern void control_packet_receive(control_main_t * const main, control_payload_header_t * const header);
#endif // _di_control_packet_receive_

/**
 * Process the received and loaded packet.
 *
 * @param main
 *   The main program data.
 *
 *   This alters main.setting.state.status:
 *     F_done on success but action has no success or failure states.
 *     F_success on success.
 *
 *     F_busy (with error bit)
 *     F_failure (with error bit) on success but controller returned failure for action.
 *     F_known_not (with error bit) if the Payload type is unknown.
 *     Any error (with error bit) on failure where the error is defined by the controller service.
 * @param header
 *   The control payload packet header data.
 */
#ifndef _di_control_packet_process_
  extern void control_packet_process(control_main_t * const main, control_payload_header_t * const header);
#endif // _di_control_packet_process_

/**
 * Send the payload to the remote socket, getting the payload from the large cache.
 *
 * @param main
 *   The main program data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_socket_write().
 *
 * @see f_socket_write()
 */
#ifndef _di_control_packet_send_
  extern void control_packet_send(control_main_t * const main);
#endif // _di_control_packet_send_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_packet_h

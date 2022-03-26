/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_control_h
#define _PRIVATE_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Accept connections from a control socket server.
 *
 * Connectons are processed and actions are performed.
 *
 * @param global
 *   The global data.
 * @param control
 *   The control data.
 *
 * @return
 *   F_none on success.
 *   F_valid_not on invalid packet from client (this is not an error with the function itself and so no error bit is set).
 *
 *   Errors (with error bit) from: f_socket_accept().
 *
 * @see f_socket_accept()
 */
#ifndef _di_controller_control_accept_
  extern f_status_t controller_control_accept(const controller_global_t * const global, controller_control_t * const control) F_attribute_visibility_internal_d;
#endif // _di_controller_control_accept_

/**
 * Configure client socket settings.
 *
 * @param global
 *   The global data.
 * @param client
 *   The client socket structure.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_socket_option_set().
 *
 * @see f_socket_option_set()
 */
#ifndef _di_controller_control_configure_client_
  extern f_status_t controller_control_configure_client(const controller_global_t * const global, f_socket_t * const client) F_attribute_visibility_internal_d;
#endif // _di_controller_control_configure_client_

/**
 * Configure server socket settings.
 *
 * @param global
 *   The global data.
 * @param server
 *   The server socket structure.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_socket_option_set().
 *
 * @see f_socket_option_set()
 */
#ifndef _di_controller_control_configure_server_
  extern f_status_t controller_control_configure_server(const controller_global_t * const global, f_socket_t * const server) F_attribute_visibility_internal_d;
#endif // _di_controller_control_configure_server_

/**
 * Given the header buffer, get the flag bits.
 *
 * @param buffer
 *   The buffer to read the length of and get the
 *
 * @return
 *   The 8-bit number representing the flags.
 */
#ifndef _di_controller_control_packet_header_flag_
  extern uint8_t controller_control_packet_header_flag(const f_char_t buffer[]) F_attribute_visibility_internal_d;
#endif // _di_controller_control_packet_header_flag_

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
#ifndef _di_controller_control_packet_header_length_
  extern uint32_t controller_control_packet_header_length(const bool is_big, const f_char_t buffer[]) F_attribute_visibility_internal_d;
#endif // _di_controller_control_packet_header_length_

/**
 * Construct the header portion of the payload.
 *
 * This also prepends the FSS identifier comment.
 *
 * This resets and uses control.cache_1 and control.cache_2.
 * Do not use either of these for passing strings to this function.
 *
 * The results of this function are appended to control.output.
 *
 * @param global
 *   The global data.
 * @param control
 *   The control data.
 * @param type
 *   The packet type.
 *   Set type.used to 0 to not add to the header.
 * @param status
 *   The status code.
 *   Set status.used to 0 to not add to the header.
 * @param length
 *   The length of the payload Content.
 *   This is always added to the header.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_conversion_number_unsigned_to_string().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: fll_fss_extended_write_string().
 *   Errors (with error bit) from: fll_fss_payload_write_string().
 *
 * @see f_conversion_number_unsigned_to_string()
 * @see f_string_append()
 * @see fll_fss_extended_write_string()
 * @see fll_fss_payload_write_string()
 */
#ifndef _di_controller_control_respond_build_header_
  extern f_status_t controller_control_respond_build_header(const controller_global_t * const global, controller_control_t * const control, const f_string_static_t type, const f_string_static_t status, const f_array_length_t length) F_attribute_visibility_internal_d;
#endif // _di_controller_control_respond_build_header_

/**
 * Accept connections from a control socket server.
 *
 * Connectons are processed and actions are performed.
 *
 * This resets and uses control.cache_3 and control.output.
 * This calls functions that resets and uses control.cache_1, control.cache_2.
 *
 * Common response error codes:
 *   - F_empty:         Packet is empty (does not even have headers).
 *   - F_packet_not:    Packet is not a valid packet.
 *   - F_supported_not: Format or action is not supported.
 *   - F_too_large:     Packet is too large (exceeds max packet length).
 *   - F_too_small:     Packet is too small (smaller than minimum header length).
 *
 * @param global
 *   The global data.
 * @param control
 *   The control data.
 * @param status
 *   The status code.
 * @param message
 *   A status message.
 *
 * @return
 *   Result of f_socket_write() on success.
 *
 *   Errors (with error bit) from: f_socket_write().
 *
 * @see f_socket_write()
 */
#ifndef _di_controller_control_respond_error_
  extern f_status_t controller_control_respond_error(const controller_global_t * const global, controller_control_t * const control, const f_status_t status, const f_string_static_t message) F_attribute_visibility_internal_d;
#endif // _di_controller_control_respond_error_

/**
 * Alternate version of controller_control_respond_error() that accepts f_string_t for message.
 *
 * This calls functions that resets and uses control.cache_1, control.cache_2, control.cache_3, and control.output.
 *
 * @param global
 *   The global data.
 * @param control
 *   The control data.
 * @param status
 *   The status code.
 * @param message
 *   A status message.
 *   This must be a NULL terminated string so that functions like strlen() may get the length of this string.
 *
 * @return
 *   Result of controller_control_respond_error() on success.
 *
 *   Errors (with error bit) from: controller_control_respond_error().
 *
 * @see controller_control_respond_error()
 */
#ifndef _di_controller_control_respond_error_string_
  extern f_status_t controller_control_respond_error_string(const controller_global_t * const global, controller_control_t * const control, const f_status_t status, const f_string_t message) F_attribute_visibility_internal_d;
#endif // _di_controller_control_respond_error_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_h

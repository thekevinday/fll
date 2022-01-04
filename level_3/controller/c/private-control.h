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
  extern f_status_t controller_control_configure_client(const controller_global_t *global, f_socket_t * const client) F_attribute_visibility_internal_d;
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
  extern f_status_t controller_control_configure_server(const controller_global_t *global, f_socket_t * const server) F_attribute_visibility_internal_d;
#endif // _di_controller_control_configure_server_

/**
 * Accept connections from a control socket server.
 *
 * Connectons are processed and actions are performed.
 *
 * @param global
 *   The global data.
 * @param socket
 *   The socket structure.
 * @param packet
 *   The control packet data structure.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_socket_accept().
 *
 * @see f_socket_accept()
 */
#ifndef _di_controller_control_accept_
  extern f_status_t controller_control_accept(const controller_global_t *global, f_socket_t * const server, controller_packet_t * const packet) F_attribute_visibility_internal_d;
#endif // _di_controller_control_accept_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_h

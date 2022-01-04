/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_control_h
#define _PRIVATE_common_control_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide default control settings.
 *
 * controller_control_default:
 *   - socket_backlog: The amount of waiting client connections to support while handling a socket connection.
 *   - socket_buffer:  The size of the buffer in bytes when processing packets (must not be set smaller the packet headers).
 *   - socket_header:  The minimum size of the packet header to read to be able to process the size information.
 *   - socket_linger:  The number of seconds to linger the connection before closing.
 *   - socket_timeout: The number of microseconds to wait.
 */
#ifndef _di_controller_control_defaults_
  #define controller_control_default_socket_backlog_d 64
  #define controller_control_default_socket_buffer_d  16384
  #define controller_control_default_socket_header_d  33
  #define controller_control_default_socket_linger_d  1
  #define controller_control_default_socket_timeout_d 10000 // 0.01 seconds.
#endif // _di_controller_defaults_

/**
 * A structure representing the packet payload.
 *
 * Payload structure: [uint32_t][char X].
 *
 * bytes:   The header repesenting the number of bytes in the character payload.
 * payload: The character payload whose size is represented by the header bytes.
 */
#ifndef _di_controller_packet_t_
  typedef struct {
    uint32_t bytes;
    f_string_dynamic_t payload;
  } controller_packet_t;

  #define controller_packet_t_initialize { 0, f_string_dynamic_t_initialize }

  #define macro_controller_packet_t_initialize(bytes, payload) { \
    bytes, \
    payload, \
  }
#endif // _di_controller_main_t_

/**
 * Fully deallocate all memory for the given packet without caring about return status.
 *
 * @param packet
 *   The packet to deallocate.
 */
#ifndef _di_controller_packet_delete_simple_
  extern void controller_packet_delete_simple(controller_packet_t * const packet) F_attribute_visibility_internal_d;
#endif // _di_controller_packet_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_control_h

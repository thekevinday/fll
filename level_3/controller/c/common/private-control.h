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
 *   - socket_backlog:     The amount of waiting client connections to support while handling a socket connection.
 *   - socket_buffer:      The preferred max size of the buffer such that if the buffer exceeds this then it is reallocated to this size at the end of processing.
 *   - socket_buffer_max:  The max size allowed in the buffer (this value must not be set smaller than the packet headers).
 *   - socket_cache:       The preferred max size of the contol cache such that if the cache exceeds this then it is reallocated to this size at the end of processing.
 *   - socket_header:      The minimum size in bytes of the packet header to read to be able to process the size information.
 *   - socket_linger:      The number of seconds to linger the connection before closing.
 *   - socket_timeout:     The number of microseconds to wait.
 *   - socket_payload_max: The max size allowed for the "payload" part of a packet and must be smaller than socket_buffer_max (this is smaller than socket_buffer_max to allow for enough room to afford a header).
 */
#ifndef _di_controller_control_defaults_
  #define controller_control_default_socket_backlog_d     64
  #define controller_control_default_socket_buffer_d      2048
  #define controller_control_default_socket_buffer_max_d  4294967296
  #define controller_control_default_socket_cache_d       128
  #define controller_control_default_socket_header_d      5
  #define controller_control_default_socket_linger_d      2
  #define controller_control_default_socket_timeout_d     10000 // 0.01 seconds.
  #define controller_control_default_socket_payload_max_d 4294965248
#endif // _di_controller_defaults_

/**
 * A structure for control processing.
 *
 * server:  The server socket connection.
 * client:  The client socket connection.
 * cache_1: A generic buffer used for caching control related data.
 * cache_2: A generic buffer used for caching control related data.
 * input:   A buffer used for receiving data from the client.
 * output:  A buffer used for transmitting data to the client.
 */
#ifndef _di_controller_control_t_
  typedef struct {
    f_socket_t *server;
    f_socket_t *client;

    f_string_dynamic_t cache_1;
    f_string_dynamic_t cache_2;
    f_string_dynamic_t cache_3;

    f_string_dynamic_t input;
    f_string_dynamic_t output;
  } controller_control_t;

  #define controller_control_t_initialize { 0, 0, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define macro_controller_control_t_initialize(server, client) { \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
  }
#endif // _di_controller_control_t_

/**
 * A codes repesent different flags associated with a packet.
 *
 * controller_control_packet_flag_*:
 *   - binary:     Designate that the packet is in binary mode (when not set then packet is in string mode).
 *   - endian_big: Designate that the packet is in big endian order (when not set then packet is in little endian order).
 */
#ifndef _di_controller_control_packet_flag_
  #define controller_control_packet_flag_binary_d     0x1
  #define controller_control_packet_flag_endian_big_d 0x2
#endif // _di_controller_control_packet_flag_

/**
 * A 34-bit long little-endian structure representing the packet header.
 *
 * This represents the packet header which is different from the header inside the packet.
 *
 * Generally, the string-based packet format is FSS-000E (Payload).
 * This format is stored within packet and has it's own header and payload parts.
 * Example pseudo-structure:
 *   [0][0][4294967296][# fss-000e
 *     header:
 *       type message
 *       length 4294965248
 *     payload:
 *      ...
 *   ]
 *
 * This means that string format is "technical" binary because of the header, but after the header it is entirely a string.
 * Unlike other strings, this string is not NULL terminated and is instead end of tranmsission or end of file terminated (as appropriate).
 *
 * type:   A boolean that when TRUE designates this as a binary and when FALSE designates this as a string packet.
 * endian: A boolean designating that when TRUE thath the length digit is big endian and when FALSE designates that the length is little endian.
 * length: A size representing how large the entire packet is (including the header that is 34 bits).
 */

/**
 * Fully deallocate all memory for the given control data without caring about return status.
 *
 * @param control
 *   The structure to deallocate.
 */
#ifndef _di_controller_control_delete_simple_
  extern void controller_control_delete_simple(controller_control_t * const control) F_attribute_visibility_internal_d;
#endif // _di_controller_control_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_control_h

/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project socket.
 *
 * This is auto-included by socket.h and should not need to be explicitly included.
 */
#ifndef _F_socket_common_h
#define _F_socket_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Socket Types.
 *
 * f_socket_close_*:
 * - fast:       Fast Socket close, as in close().
 * - read:       Read close, as in shutdown(, SHUT_RD).
 * - write:      Write close, as in shutdown(, SHUT_WR).
 * - read_write: Read/Write close, as in shutdown(, SHUT_RDWR).
 */
#ifndef _di_f_socket_types_
  enum {
    f_socket_close_fast_e = 1,
    f_socket_close_read_e,
    f_socket_close_write_e,
    f_socket_close_read_write_e,
  };
#endif // _di_f_socket_types_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_common_h

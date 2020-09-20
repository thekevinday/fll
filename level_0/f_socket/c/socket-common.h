/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project socket.
 *
 * This is auto-included by socket.h and should not need to be explicitly included.
 */
#ifndef _F_socket_common_h
#define _F_socket_common_h

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Socket Types.
 */
#ifndef _di_f_socket_types_
  enum {
    f_socket_close_fast = 1,   // As in close();
    f_socket_close_read,       // As in shutdown(, SHUT_RD);
    f_socket_close_write,      // As in shutdown(, SHUT_WR);
    f_socket_close_read_write, // As in shutdown(, SHUT_RDWR);
  };
#endif // _di_f_socket_types_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_common_h

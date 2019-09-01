/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to connect to and use sockets.
 */
#ifndef _F_socket_h
#define _F_socket_h

// libc includes
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// fll includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/types.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_socket_types_
  #define f_socket_id       f_s_int
  #define f_socket_close_id f_u_short

  enum {
    f_socket_close_fast,       // As in close();
    f_socket_close_read,       // As in shutdown(, SHUT_RD);
    f_socket_close_write,      // As in shutdown(, SHUT_WR);
    f_socket_close_read_write, // As in shutdown(, SHUT_RDWR);
  };
#endif // _di_f_socket_types_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_h

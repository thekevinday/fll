/**
 * FLL - Level 1
 *
 * Project: Socket
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to connect to and use sockets.
 */
#ifndef _FL_socket_h
#define _FL_socket_h

// libc includes
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

// fll includes
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/socket.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_socket_file_bind_
  /**
   * bind a socket.
   */
  extern f_return_status fl_socket_file_bind(const f_string socket_path, f_socket_id *socket_id, struct sockaddr_un *socket_address);
#endif // _di_fl_socket_file_bind_

#ifndef _di_fl_socket_listen_
  /**
   * terminate a socket connection.
   * suggested socket_backlog default setting = 8.
   */
  extern f_return_status fl_socket_listen(const f_socket_id socket_id, const f_u_int socket_backlog);
#endif // _di_fl_socket_listen_

#ifndef _di_fl_socket_close_client_
  /**
   * terminate a socket connection.
   * suggested default close_action = f_socket_close_fast.
   */
  extern f_return_status fl_socket_close_client(const f_socket_id socket_id_client, const f_socket_close_id close_action);
#endif // _di_fl_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_socket_h

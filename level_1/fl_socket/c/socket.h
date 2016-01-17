/* FLL - Level 1
 * Project:       Socket
 * Version:       0.4.2
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide means to connect to and use sockets.
 */
#ifndef _F_socket_h
#define _F_socket_h

// libc includes
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/socket.h>

// fll includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_socket_file_bind_
  // bind a socket.
  f_extern f_return_status fl_socket_file_bind(const f_string socket_path, f_socket_id *socket_id, f_socket_address *socket_address);
#endif // _di_fl_socket_file_bind_

#ifndef _di_fl_socket_listen_
  // terminate a socket connection
  // suggested socket_backlog default setting = 8.
  f_extern f_return_status fl_socket_listen(const f_socket_id socket_id, const f_u_int socket_backlog);
#endif // _di_fl_socket_listen_

#ifndef _di_fl_socket_close_client_
  // terminate a socket connection
  // suggested default close_action = f_socket_close_fast.
  f_extern f_return_status fl_socket_close_client(const f_socket_id socket_id_client, const f_socket_close_id close_action);
#endif // _di_fl_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_h

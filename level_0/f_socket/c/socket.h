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
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

// fll-0 socket includes
#include <level_0/socket-common.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Bind a UNIX socket.
 *
 * @param path
 *   The path to a socket file to bind to.
 * @param id
 *   The ID of a socket.
 * @param address
 *   The socket address information.
 *
 * @return
 *   F_none on success.
 *   F_address (with error bit) if address is already in use (therefore unavailable).
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_busy_socket (with error bit) if socket defined by id is already bound (therefore unavailable).
 *   F_descriptor (with error bit) if the id is not a socket descriptor.
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_file_found_not (with error bit) if file not found.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_string_too_large (with error bit) if string is too large to store in the buffer.
 *   F_unavailable_address (with error bit) if address is unavailable (is non-existent or not local).
 *   F_failure (with error bit) for any other error.
 *
 * @see bind()
 */
#ifndef _di_f_socket_file_bind_
  extern f_return_status f_socket_file_bind(const f_string_t path, const int id, struct sockaddr_un *address);
#endif // _di_f_socket_file_bind_

/**
 * Terminate a socket connection.
 *
 * @param id
 *   The ID of a socket.
 * @param max_backlog
 *   The max length of the pending connections queue.
 *   Suggested default setting: 8.
 *
 * @return
 *   F_none on success.
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_descriptor (with error bit) if the id is not a socket descriptor.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_unsupported (with error bit) if this socket does not support the listen() operation.
 *   F_failure (with error bit) for any other error.
 *
 * @see listen()
 */
#ifndef _di_f_socket_listen_
  extern f_return_status f_socket_listen(const int id, const unsigned int max_backlog);
#endif // _di_f_socket_listen_

/**
 * Terminate a client socket connection.
 *
 * @param id
 *   The ID of a socket.
 * @param action
 *   The action to perform on close.
 *   f_socket_close_fast calls close().
 *
 * @return
 *   F_none on success.
 *   F_connected_not if the socket is not connected.
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_descriptor (with error bit) if the id is not a socket descriptor.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting operation.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_unsupported (with error bit) if this socket does not support the listen() operation.
 *   F_failure (with error bit) for any other error.
 *
 * @see close()
 * @see shutdown()
 */
#ifndef _di_f_socket_close_client_
  extern f_return_status f_socket_close_client(const int id, const unsigned short action);
#endif // _di_f_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_h

/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provide means to interact with sockets.
 */
#ifndef _F_socket_h
#define _F_socket_h

// Libc includes.
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-0 socket includes.
#include <fll/level_0/socket/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Retrieve a client connection from a listening socket.
 *
 * @param socket
 *   The client socket structure.
 *   The structure should be memset as appropriate before calling this.
 *   The properties of the structure, namely socket.id, socket.address, and socket.length, are updated upon a successful return.
 * @param id
 *   The socket file descriptor representing an actively listening socket to retrieve from.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_block (with error bit) if socket is blocked.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_buffer_not (with error bit) if unable to create socket due to resource restrictions (maps to ENOBUFS).
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_interrupt (with error bit) if interrupt is received.
 *   F_memory_not (with error bit) if out of memory.
 *   F_network_client_not (with error bit) if the client is down.
 *   F_network_device_not (with error bit) if the network device no longer exists.
 *   F_network_not (with error bit) if network is down.
 *   F_network_reach_client_not (with error bit) if the client cannot be reached.
 *   F_network_reach_not (with error bit) if the network cannot be reached.
 *   F_option_not (with error bit) if the given option is unknown or is unsupported.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the file system does not permit this operation.
 *   F_protocol (with error bit) if a protocol error occurred.
 *   F_protocol_not (with error bit) if the given protocol is unknown or is unsupported.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_stream_not (with error bit) the socket type is not a stream.
 *   F_supported_not (with error bit) if this socket type is not supported.
 *   F_time_out (with error bit) if a timeout occurred.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see accept()
 */
#ifndef _di_f_socket_accept_
  extern f_status_t f_socket_accept(f_socket_t * const socket, const int id);
#endif // _di_f_socket_accept_

/**
 * Bind a socket to a name.
 *
 * This does not initialize or otherwise memset() the address.
 *
 * @param socket
 *   The socket structure.
 *   The socket.address may point to any valid structure, like "struct sockaddr", "struct sockaddr_un", or "struct sockaddr_in".
 *   The caller must appropriately initialize and configure the socket.address.
 *   The socket.length must represent the full size of the address structure.
 *   The socket.id must refer to a valid socket file descriptor.
 *
 * @return
 *   F_none on success.
 *
 *   F_address (with error bit) if address is already in use (therefore unavailable).
 *   F_available_not_address (with error bit) if address is unavailable (is non-existent or not local).
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_file_found_not (with error bit) if file not found.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_string_too_large (with error bit) if string is too large to store in the buffer.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see bind()
 */
#ifndef _di_f_socket_bind_
  extern f_status_t f_socket_bind(const f_socket_t socket);
#endif // _di_f_socket_bind_

/**
 * Bind a socket to a UNIX socket file.
 *
 * This does initialize and memset() the address with the address set to a UNIX socket (struct sockaddr_un).
 *
 * @param socket
 *   The socket structure.
 *   The socket.address must point to a "struct sockaddr_un".
 *   The socket.name must be assigned to a path.
 *   The socket.type must be assigned to f_socket_domain_file_d.
 *
 * @return
 *   F_none on success.
 *
 *   F_address (with error bit) if address is already in use (therefore unavailable).
 *   F_available_not_address (with error bit) if address is unavailable (is non-existent or not local).
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_file_found_not (with error bit) if file not found.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_string_too_large (with error bit) if string is too large to store in the buffer.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see bind()
 * @see memset()
 * @see strncpy()
 */
#ifndef _di_f_socket_bind_file_
  extern f_status_t f_socket_bind_file(const f_socket_t socket);
#endif // _di_f_socket_bind_file_

/**
 * Connect to a socket.
 *
 * @param socket
 *   The socket structure.
 *   The socket.address may point to any valid structure, like "struct sockaddr", "struct sockaddr_un", or "struct sockaddr_in".
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_available_not_address (with error bit) if address is unavailable (is non-existent or not local).
 *   F_block (with error bit) if socket is blocked.
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_complete_not (with error bit) if a non-blocking connection attempt is not yet completed.
 *   F_connect (with error bit) if already connected.
 *   F_connect_refuse (with error bit) if connection is refused because there is nothing listening.
 *   F_domain_not (with error bit) if the given domain is unknown or is unsupported.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_interrupt (with error bit) if interrupt is received.
 *   F_network_reach_not (with error bit) if the network is unreachable.
 *   F_progress (with error bit) if if a non-blocking connection cannot be completed immediately.
 *   F_prohibited (with error bit) if the file system does not permit this operation.
 *   F_protocol_not (with error bit) if the given protocol is unknown or is unsupported.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_time_out (with error bit) if a timeout occurred.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see connect()
 */
#ifndef _di_f_socket_connect_
  extern f_status_t f_socket_connect(const f_socket_t socket);
#endif // _di_f_socket_connect_

/**
 * Create a new socket.
 *
 * @param socket_structure
 *   The socket structure.
 *   The socket.address may point to any valid structure, like "struct sockaddr", "struct sockaddr_un", or "struct sockaddr_in".
 *   The socket.domain must be assigned the desired domain.
 *   The socket.type must be assigned the desired type.
 *   The socket.protocol must be assigned the desired protocol.
 *   The socket.id will be updated with a file descriptor representing the created socket.
 *
 *   This is named "socket_structure" rather than "socket" due to a conflict with the function "socket()".
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer_not (with error bit) if unable to create socket due to resource restrictions (maps to ENOBUFS).
 *   F_domain_not (with error bit) if the given domain is unknown or is unsupported.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_protocol_not (with error bit) if the given protocol is unknown or is unsupported.
 *   F_type_not (with error bit) if the given type is unknown or is unsupported.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see socket()
 */
#ifndef _di_f_socket_create_
  extern f_status_t f_socket_create(f_socket_t * const socket_structure);
#endif // _di_f_socket_create_

/**
 * Create a new pair of identical sockets.
 *
 * This is generally intended to be used for pipes.
 *
 * @param domain
 *   The protocol family.
 * @param type
 *   The communication type.
 * @param protocol
 *   The protocol to use.
 * @param id_1
 *   The first of the pair of socket file descriptors.
 * @param id_2
 *   The second of the pair of socket file descriptors.
 *
 *   This socket is supposed to be identical to the one specified by id_1.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer_not (with error bit) if unable to create socket due to resource restrictions (maps to ENOBUFS).
 *   F_domain_not (with error bit) if the given domain is unknown or is unsupported.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_not (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_protocol_not (with error bit) if the given protocol is unknown or is unsupported.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see socketpair()
 */
#ifndef _di_f_socket_create_pair_
  extern f_status_t f_socket_create_pair(const int domain, const int protocol, const int type, int * const id_1, int * const id_2);
#endif // _di_f_socket_create_pair_

/**
 * Terminate a socket connection.
 *
 * The shutdown() call is used for all actions, except f_socket_close_fast_e.
 * When shutdown() is called, a proper network disconnection process is initiated.
 * The network connection will properly send the FIN packets.
 * The shutdown() also allows current buffers to be properly flushed.
 * The file descriptor is not closed.
 * The remaining buffer can still be processed.
 * Be sure to call either this function again with f_socket_close_fast_e or call f_file_close() directly.
 *
 * When action is f_socket_close_fast_e, then close() is called.
 * What happens then is that rather than waiting for FIN a RST is immediately sent (RST is sent only if connection is still active).
 * All buffers are discarded.
 * The connection is immediately removed.
 * Thus, f_socket_close_fast_e (calling close()) on a socket results in bad network practice.
 *
 * In the above cases, whether or not a RST or FIN are sent is also dependent on whether the f_socket_option_linger_d is used (SO_LINGER).
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 * @param action
 *   The action to perform on close.
 *   f_socket_close_fast_e calls close().
 *
 * @return
 *   F_none on success.
 *   F_connect_not if the socket is not connected.
 *
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_supported_not (with error bit) if this socket does not support the listen() operation.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see close()
 * @see shutdown()
 */
#ifndef _di_f_socket_disconnect_
  extern f_status_t f_socket_disconnect(f_socket_t * const socket, const uint8_t action);
#endif // _di_f_socket_disconnect_

/**
 * Set the socket to listen mode (passive socket).
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 * @param max_backlog
 *   The max length of the pending connections queue.
 *   Suggested default setting: 8.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy_address (with error bit) if address is already in use (therefore unavailable).
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_supported_not (with error bit) if this socket does not support the listen() operation.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see listen()
 */
#ifndef _di_f_socket_listen_
  extern f_status_t f_socket_listen(f_socket_t * const socket, const unsigned int max_backlog);
#endif // _di_f_socket_listen_

/**
 * Get a socket option value.
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 * @param level
 *   The level in which the socket option is located.
 *   This may be synonymous with "layer".
 * @param option
 *   The option code used to represent the option name.
 * @param value
 *   The value to assign.
 * @param length
 *   The length of the value (often derived from a sizeof() call).
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer (with error bit) if the given value is out of scope.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_option_not (with error bit) if the type is not valid for the given level.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_value (with error bit) if either the value or the length is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see getsockopt()
 */
#ifndef _di_f_socket_option_get_
  extern f_status_t f_socket_option_get(f_socket_t * const socket, const int level, const int option, void * const value, socklen_t * const length);
#endif // _di_f_socket_option_get_

/**
 * Set a socket option value.
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 * @param level
 *   The level in which the socket option is located.
 *   This may be synonymous with "layer".
 * @param option
 *   The option code used to represent the option name.
 * @param value
 *   The value to assign.
 * @param length
 *   The length of the value (often derived from a sizeof() call).
 *
 * @return
 *   F_none on success.
 *
 *   F_buffer (with error bit) if the given value is out of scope.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_option_not (with error bit) if the type is not valid for the given level.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_value (with error bit) if either the value or the length is invalid.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see setsockopt()
 */
#ifndef _di_f_socket_option_set_
  extern f_status_t f_socket_option_set(f_socket_t * const socket, const int level, const int option, const void * const value, const socklen_t length);
#endif // _di_f_socket_option_set_

/**
 * Read from a socket.
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 *   The socket.size_read is used to represent the buffer size in buffer and must not be larger than the actual size of the buffer.
 * @param flags
 *   Read flags.
 * @param buffer
 *   The buffer to populate.
 * @param length
 *   (optional) The length of the buffer.
 *   This gets replaced with the value of a positive ssize_t representing the length read.
 *   Data may be lost if the amount of data read is larger than given buffer length.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_complete_not (with error bit) if an existing connection is not yet complete.
 *   F_connect_not (with error bit) if the socket is not connected.
 *   F_connect_refuse (with error bit) if connection is refused.
 *   F_connect_reset (with error bit) if connection is reset.
 *   F_block (with error bit) if socket is blocked.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_interrupt (with error bit) if interrupt is received.
 *   F_memory_not (with error bit) if out of memory.
 *   F_option_not (with error bit) if a flag is not supported.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if the local end of a connection oriented socket is closed or SIGPIPE is received.
 *   F_prohibited (with error bit) if the insufficient privileges to perform read.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_time_out (with error bit) if a timeout occurred.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see recvfrom()
 */
#ifndef _di_f_socket_read_
  extern f_status_t f_socket_read(f_socket_t * const socket, const int flags, void * const buffer, size_t * const length);
#endif // _di_f_socket_read_

/**
 * Read a message from a socket.
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 * @param flags
 *   Read flags.
 * @param header
 *   The message header.
 * @param length
 *   This gets replaced with the value of a positive ssize_t representing the length read.
 *   Data may be lost if the amount of data read is larger than given buffer length.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_complete_not (with error bit) if an existing connection is not yet complete.
 *   F_connect_not (with error bit) if the socket is not connected.
 *   F_connect_refuse (with error bit) if connection is refused.
 *   F_connect_reset (with error bit) if connection is reset.
 *   F_block (with error bit) if socket is blocked.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_interrupt (with error bit) if interrupt is received.
 *   F_memory_not (with error bit) if out of memory.
 *   F_option_not (with error bit) if a flag is not supported.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if the local end of a connection oriented socket is closed or SIGPIPE is received.
 *   F_prohibited (with error bit) if the insufficient privileges to perform read.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_time_out (with error bit) if a timeout occurred.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see recvmsg()
 */
#ifndef _di_f_socket_read_message_
  extern f_status_t f_socket_read_message(f_socket_t * const socket, const int flags, struct msghdr * const header, size_t * const length);
#endif // _di_f_socket_read_message_

/**
 * Send to a socket.
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 *   The socket.size_write is used to represent the buffer size in buffer and must not be larger than the actual size of the buffer.
 * @param flags
 *   Read flags.
 * @param buffer
 *   The buffer to populate.
 * @param length
 *   (optional) The length of the buffer.
 *   This gets replaced with the value of a positive ssize_t representing the length send.
 *   Data may be lost if the amount of data send is larger than given buffer length.
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_address_not (with error bit) if no address is provided and the connection is not "connection-mode".
 *   F_buffer_not (with error bit) if unable to send message because output buffer is full.
 *   F_complete_not (with error bit) if an existing connection is not yet complete.
 *   F_connect (with error bit) if an address is provided and the connection is "connection-mode".
 *   F_connect_not (with error bit) if the socket is not connected.
 *   F_connect_refuse (with error bit) if connection is refused.
 *   F_connect_reset (with error bit) if connection is reset.
 *   F_block (with error bit) if socket is blocked.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_interrupt (with error bit) if interrupt is received.
 *   F_memory_not (with error bit) if out of memory.
 *   F_option_not (with error bit) if a flag is not supported.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if the local end of a connection oriented socket is closed or SIGPIPE is received.
 *   F_prohibited (with error bit) if the insufficient privileges to perform send.
 *   F_size (with error bit) if size of message makes atomically sending message impossible on a socket type that requires this to be atomic.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_time_out (with error bit) if a timeout occurred.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sendto()
 */
#ifndef _di_f_socket_write_
  extern f_status_t f_socket_write(f_socket_t * const socket, const int flags, void * const buffer, size_t * const length);
#endif // _di_f_socket_write_

/**
 * Send a message to a socket.
 *
 * @param socket
 *   The socket structure.
 *   The socket.id must represent a valid socket file descriptor.
 * @param flags
 *   Read flags.
 * @param header
 *   The message header.
 * @param length
 *   This gets replaced with the value of a positive ssize_t representing the length send.
 *   Data may be lost if the amount of data send is larger than given buffer length.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_address_not (with error bit) if no address is provided and the connection is not "connection-mode".
 *   F_buffer_not (with error bit) if unable to send message because output buffer is full.
 *   F_complete_not (with error bit) if an existing connection is not yet complete.
 *   F_connect (with error bit) if an address is provided and the connection is "connection-mode".
 *   F_connect_not (with error bit) if the socket is not connected.
 *   F_connect_refuse (with error bit) if connection is refused.
 *   F_connect_reset (with error bit) if connection is reset.
 *   F_block (with error bit) if socket is blocked.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_descriptor (with error bit) if id is an invalid descriptor.
 *   F_interrupt (with error bit) if interrupt is received.
 *   F_memory_not (with error bit) if out of memory.
 *   F_option_not (with error bit) if a flag is not supported.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe (with error bit) if the local end of a connection oriented socket is closed or SIGPIPE is received.
 *   F_prohibited (with error bit) if the insufficient privileges to perform send.
 *   F_size (with error bit) if size of message makes atomically sending message impossible on a socket type that requires this to be atomic.
 *   F_socket_not (with error bit) if the id is not a socket descriptor.
 *   F_time_out (with error bit) if a timeout occurred.
 *
 *   F_failure (with error bit) for any other error.
 *
 * @see sendmsg()
 */
#ifndef _di_f_socket_write_message_
  extern f_status_t f_socket_write_message(f_socket_t * const socket, const int flags, struct msghdr * const header, size_t * const length);
#endif // _di_f_socket_write_message_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_h

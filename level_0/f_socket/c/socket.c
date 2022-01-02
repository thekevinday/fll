#include "socket.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_socket_accept_
  f_status_t f_socket_accept(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (accept(socket->id, socket->address, &socket->length) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_stream_not);
      if (errno == EPROTO) return F_status_set_error(F_protocol);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == ESOCKTNOSUPPORT) return F_status_set_error(F_supported_not);
      if (errno == EPROTONOSUPPORT) return F_status_set_error(F_protocol_not);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_accept_

#ifndef _di_f_socket_bind_
  f_status_t f_socket_bind(const f_socket_t socket) {

    if (bind(socket.id, socket.address, socket.length) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EADDRNOTAVAIL) return F_status_set_error(F_available_not_address);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_string_too_large);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_found_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_bind_

#ifndef _di_f_socket_bind_file_
  f_status_t f_socket_bind_file(const f_socket_t socket) {
    #ifndef _di_level_0_parameter_checking_
      if (socket.domain != f_socket_domain_file_d) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    memset(socket.address, 0, sizeof(struct sockaddr_un));
    ((struct sockaddr_un *) socket.address)->sun_family = f_socket_domain_file_d;

    strncpy(((struct sockaddr_un *) socket.address)->sun_path, socket.name, sizeof(((struct sockaddr_un *) socket.address)->sun_path) - 1);

    if (bind(socket.id, socket.address, sizeof(struct sockaddr_un)) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EADDRNOTAVAIL) return F_status_set_error(F_available_not_address);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_string_too_large);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_found_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_bind_file_

#ifndef _di_f_socket_connect_
  f_status_t f_socket_connect(const f_socket_t socket) {

    if (connect(socket.id, socket.address, socket.length) == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EADDRNOTAVAIL) return F_status_set_error(F_available_not_address);
      if (errno == EAFNOSUPPORT) return F_status_set_error(F_domain_not);
      if (errno == EAGAIN) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == EINPROGRESS) return F_status_set_error(F_progress);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EISCONN) return F_status_set_error(F_connect);
      if (errno == ENETUNREACH) return F_status_set_error(F_network_reach_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EPROTONOSUPPORT) return F_status_set_error(F_protocol_not);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_connect_

#ifndef _di_f_socket_create_
  f_status_t f_socket_create(f_socket_t * const socket_structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket_structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int result = socket(socket_structure->domain, socket_structure->type, socket_structure->protocol);

    if (result == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAFNOSUPPORT) return F_status_set_error(F_domain_not);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EPROTONOSUPPORT) return F_status_set_error(F_protocol_not);
      if (errno == ESOCKTNOSUPPORT) return F_status_set_error(F_type_not);

      return F_status_set_error(F_failure);
    }

    socket_structure->id = result;

    return F_none;
  }
#endif // _di_f_socket_create_

#ifndef _di_f_socket_create_pair_
  f_status_t f_socket_create_pair(const int domain, const int protocol, const int type, int *id_1, int *id_2) {
    #ifndef _di_level_0_parameter_checking_
      if (!id_1) return F_status_set_error(F_parameter);
      if (!id_2) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int pair[2] = { 0, 0 };

    if (socketpair(domain, type, protocol, pair) == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAFNOSUPPORT) return F_status_set_error(F_domain_not);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EPROTONOSUPPORT) return F_status_set_error(F_protocol_not);

      return F_status_set_error(F_failure);
    }

    *id_1 = pair[0];
    *id_2 = pair[1];

    return F_none;
  }
#endif // _di_f_socket_create_pair_

#ifndef _di_f_socket_disconnect_
  f_status_t f_socket_disconnect(f_socket_t * const socket, const unsigned short action) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = 0;

    if (action == f_socket_close_fast_e) {
      result = close(socket->id);
    }
    else if (action == f_socket_close_read_e || action == f_socket_close_write_e || action == f_socket_close_read_write_e) {
      result = shutdown(socket->id, action);
    }
    else {
      return F_status_set_error(F_supported_not);
    }

    if (result < 0) {

      // According to man pages, retrying close() after another close on error is invalid on Linux because Linux releases the descriptor before stages that cause failures.
      if (errno != EBADF && errno != EINTR) {
        socket->id = -1;
      }

      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_value);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOTCONN) return F_connect_not;
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == ENOSPC) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    socket->id = -1;

    return F_none;
  }
#endif // _di_f_socket_disconnect_

#ifndef _di_f_socket_listen_
  f_status_t f_socket_listen(f_socket_t * const socket, const unsigned int max_backlog) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (listen(socket->id, max_backlog) < 0) {
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_listen_

#ifndef _di_f_socket_option_get_
  f_status_t f_socket_option_get(f_socket_t * const socket, const int level, const int type, void *value, socklen_t *length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!value) return F_status_set_error(F_parameter);
      if (!length) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (getsockopt(socket->id, level, type, value, length) < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_value);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == ENOPROTOOPT) return F_status_set_error(F_option_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_option_get_

#ifndef _di_f_socket_option_set_
  f_status_t f_socket_option_set(f_socket_t * const socket, const int level, const int type, const void *value, const socklen_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!value) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (setsockopt(socket->id, level, type, value, length) < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_value);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == ENOPROTOOPT) return F_status_set_error(F_option_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_option_set_

#ifdef __cplusplus
} // extern "C"
#endif

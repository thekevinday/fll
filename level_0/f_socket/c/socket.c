#include "socket.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_socket_accept_
  f_status_t f_socket_accept(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const int result = accept(socket->id, (struct sockaddr *) &socket->address, &socket->length);

    if (result == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EHOSTDOWN) return F_status_set_error(F_network_client_not);
      if (errno == EHOSTUNREACH) return F_status_set_error(F_network_reach_client_not);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENETDOWN) return F_status_set_error(F_network_not);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENETUNREACH) return F_status_set_error(F_network_reach_not);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENONET) return F_status_set_error(F_network_device_not);
      if (errno == ENOPROTOOPT) return F_status_set_error(F_option_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_stream_not);
      if (errno == EPROTO) return F_status_set_error(F_protocol);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == ESOCKTNOSUPPORT) return F_status_set_error(F_support_not);
      if (errno == EPROTONOSUPPORT) return F_status_set_error(F_protocol_not);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    socket->id_data = result;

    return F_okay;
  }
#endif // _di_f_socket_accept_

#ifndef _di_f_socket_bind_
  f_status_t f_socket_bind(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (bind(socket->id, (struct sockaddr *) &socket->address, socket->length) == -1) {
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

    return F_okay;
  }
#endif // _di_f_socket_bind_

#ifndef _di_f_socket_bind_inet4_
  f_status_t f_socket_bind_inet4(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (socket->domain != f_socket_protocol_family_inet4_e) return F_status_set_error(F_address_not);

    socket->address.inet4.sin_family = f_socket_address_family_inet4_e;
    socket->length = sizeof(struct sockaddr_in);

    if (bind(socket->id, (struct sockaddr *) &socket->address.inet4, socket->length) == -1) {
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

    return F_okay;
  }
#endif // _di_f_socket_bind_inet4_

#ifndef _di_f_socket_bind_inet6_
  f_status_t f_socket_bind_inet6(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (socket->domain != f_socket_protocol_family_inet6_e) return F_status_set_error(F_address_not);

    socket->address.inet6.sin6_family = f_socket_address_family_inet6_e;
    socket->length = sizeof(struct sockaddr_in6);

    if (bind(socket->id, (struct sockaddr *) &socket->address.inet6, socket->length) == -1) {
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

    return F_okay;
  }
#endif // _di_f_socket_bind_inet6_

#ifndef _di_f_socket_bind_local_
  f_status_t f_socket_bind_local(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (socket->domain != f_socket_protocol_family_local_e) return F_status_set_error(F_local_not);

    socket->address.local.sun_family = f_socket_address_family_local_e;
    socket->length = sizeof(struct sockaddr_un);

    if (socket->name.used && socket->name.string) {
      memcpy((void *) socket->address.local.sun_path, (void *) socket->name.string, socket->name.used);
      socket->address.local.sun_path[socket->name.used] = 0;
    }
    else {
      socket->address.local.sun_path[0] = 0;
    }

    if (bind(socket->id, (struct sockaddr *) &socket->address.local, socket->length) == -1) {
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

    return F_okay;
  }
#endif // _di_f_socket_bind_local_

#ifndef _di_f_socket_connect_
  f_status_t f_socket_connect(const f_socket_t socket) {

    if (connect(socket.id, (struct sockaddr *) &socket.address, socket.length) == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EADDRNOTAVAIL) return F_status_set_error(F_available_not_address);
      if (errno == EAFNOSUPPORT) return F_status_set_error(F_domain_not);
      if (errno == EAGAIN) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == EINPROGRESS) return F_status_set_error(F_progress);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISCONN) return F_status_set_error(F_connect);
      if (errno == ENETUNREACH) return F_status_set_error(F_network_reach_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPROTONOSUPPORT) return F_status_set_error(F_protocol_not);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    return F_okay;
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

    return F_okay;
  }
#endif // _di_f_socket_create_

#ifndef _di_f_socket_create_pair_
  f_status_t f_socket_create_pair(const int domain, const int protocol, const int type, int * const id_1, int * const id_2) {
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

    return F_okay;
  }
#endif // _di_f_socket_create_pair_

#ifndef _di_f_socket_disconnect_
  f_status_t f_socket_disconnect(f_socket_t * const socket, const uint8_t action) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = 0;

    if (action == f_socket_close_fast_e) {
      result = close(socket->id);
    }
    else if (action == f_socket_close_read_e) {
      result = shutdown(socket->id, SHUT_RD);
    }
    else if (action == f_socket_close_write_e) {
      result = shutdown(socket->id, SHUT_WR);
    }
    else if (action == f_socket_close_read_write_e) {
      result = shutdown(socket->id, SHUT_RDWR);
    }
    else {
      return F_status_set_error(F_support_not);
    }

    if (result == -1) {

      // According to man pages, retrying close() after another close on error is invalid on Linux because Linux releases the descriptor before stages that cause failures.
      if (action == f_socket_close_fast_e && errno != EBADF) {
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

    if (action == f_socket_close_fast_e) {
      socket->id = -1;
    }

    return F_okay;
  }
#endif // _di_f_socket_disconnect_

#ifndef _di_f_socket_listen_
  f_status_t f_socket_listen(f_socket_t * const socket, const unsigned int backlog_max) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (listen(socket->id, backlog_max) == -1) {
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_support_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_socket_listen_

#ifndef _di_f_socket_option_get_
  f_status_t f_socket_option_get(f_socket_t * const socket, const int level, const int option, void * const value, socklen_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!value) return F_status_set_error(F_parameter);
      if (!length) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (getsockopt(socket->id, level, option, value, length) == -1) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_value);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == ENOPROTOOPT) return F_status_set_error(F_option_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_socket_option_get_

#ifndef _di_f_socket_option_set_
  f_status_t f_socket_option_set(f_socket_t * const socket, const int level, const int option, const void * const value, const socklen_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!value) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (setsockopt(socket->id, level, option, value, length) == -1) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_value);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == ENOPROTOOPT) return F_status_set_error(F_option_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_socket_option_set_

#ifndef _di_f_socket_name_host_
  f_status_t f_socket_name_host(f_socket_t * const socket, f_string_dynamic_t * const name) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!name) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!name->size) {
      const f_status_t status = f_memory_array_resize(F_socket_default_name_max_d, sizeof(f_char_t), (void **) &name->string, &name->used, &name->size);
      if (F_status_is_error(status)) return status;
    }

    {
      if (gethostname(name->string, (size_t) (name->used ? (name->size - name->used) : name->size)) == -1) {
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENAMETOOLONG) return F_status_set_error(F_string_too_large);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }
    }

    for (; name->used < name->size; ++name->used) {
      if (!name->string[name->used]) break;
    } // while

    return F_okay;
  }
#endif // _di_f_socket_host_name_

#ifndef _di_f_socket_name_peer_
  f_status_t f_socket_name_peer(f_socket_t * const socket) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (getpeername(socket->id, (struct sockaddr *) &socket->address, &socket->length) == -1) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_socket_name_peer_

#ifndef _di_f_socket_read_
  f_status_t f_socket_read(f_socket_t * const socket, const int flags, void * const buffer, size_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = recvfrom(socket->id_data, buffer, socket->size_read, flags, (struct sockaddr *) &socket->address, &socket->length);

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == ECONNRESET) return F_status_set_error(F_connect_reset);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_address_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_option_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    if (length) {
      *length = (size_t) result;
    }

    return F_okay;
  }
#endif // _di_f_socket_read_

#ifndef _di_f_socket_read_message_
  f_status_t f_socket_read_message(f_socket_t * const socket, const int flags, struct msghdr * const header, size_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!header) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = recvmsg(socket->id_data, header, flags);

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == ECONNRESET) return F_status_set_error(F_connect_reset);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_address_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_option_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    if (length) {
      *length = (size_t) result;
    }

    return F_okay;
  }
#endif // _di_f_socket_read_message_

#ifndef _di_f_socket_read_stream_
  f_status_t f_socket_read_stream(f_socket_t * const socket, const int flags, void * const buffer, size_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = recv(socket->id_data, buffer, socket->size_read, flags);

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == ECONNRESET) return F_status_set_error(F_connect_reset);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_address_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_option_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    if (length) {
      *length = (size_t) result;
    }

    return F_okay;
  }
#endif // _di_f_socket_read_stream_

#ifndef _di_f_socket_write_
  f_status_t f_socket_write(f_socket_t * const socket, const int flags, void * const buffer, size_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = sendto(socket->id_data, buffer, socket->size_write, flags, (struct sockaddr *) &socket->address, socket->length);

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == ECONNRESET) return F_status_set_error(F_connect_reset);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_address_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISCONN) return F_status_set_error(F_connect);
      if (errno == EMSGSIZE) return F_status_set_error(F_size);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_option_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    if (length) {
      *length = (size_t) result;
    }

    return F_okay;
  }
#endif // _di_f_socket_write_

#ifndef _di_f_socket_write_message_
  f_status_t f_socket_write_message(f_socket_t * const socket, const int flags, struct msghdr * const header, size_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!header) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = sendmsg(socket->id_data, header, flags);

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == ECONNRESET) return F_status_set_error(F_connect_reset);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_address_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISCONN) return F_status_set_error(F_connect);
      if (errno == EMSGSIZE) return F_status_set_error(F_size);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_option_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    if (length) {
      *length = (size_t) result;
    }

    return F_okay;
  }
#endif // _di_f_socket_write_message_

#ifndef _di_f_socket_write_stream_
  f_status_t f_socket_write_stream(f_socket_t * const socket, const int flags, void * const buffer, size_t * const length) {
    #ifndef _di_level_0_parameter_checking_
      if (!socket) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = send(socket->id_data, buffer, socket->size_write, flags);

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EALREADY) return F_status_set_error(F_complete_not);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ECONNREFUSED) return F_status_set_error(F_connect_refuse);
      if (errno == ECONNRESET) return F_status_set_error(F_connect_reset);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_address_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISCONN) return F_status_set_error(F_connect);
      if (errno == EMSGSIZE) return F_status_set_error(F_size);
      if (errno == ENOBUFS) return F_status_set_error(F_buffer_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTCONN) return F_status_set_error(F_connect_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_socket_not);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_option_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe);
      if (errno == ETIMEDOUT) return F_status_set_error(F_time_out);

      return F_status_set_error(F_failure);
    }

    if (length) {
      *length = (size_t) result;
    }

    return F_okay;
  }
#endif // _di_f_socket_write_stream_

#ifdef __cplusplus
} // extern "C"
#endif

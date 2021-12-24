#include "socket.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_socket_file_bind_
  f_status_t f_socket_file_bind(const f_string_t path, const int id, struct sockaddr_un *address) {
    #ifndef _di_level_0_parameter_checking_
      if (!address) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    memset(address, 0, sizeof(struct sockaddr_un));
    address->sun_family = AF_UNIX;

    strncpy(address->sun_path, path, sizeof(address->sun_path) - 1);

    if (bind(id, (struct sockaddr *) address, sizeof(struct sockaddr_un)) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EADDRNOTAVAIL) return F_status_set_error(F_available_not_address);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_busy_socket);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_string_too_large);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_found_not);
      if (errno == ENOTSOCK) return F_status_set_error(F_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_file_bind_

#ifndef _di_f_socket_listen_
  f_status_t f_socket_listen(const int id, const unsigned int max_backlog) {

    if (listen(id, max_backlog) < 0) {
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == ENOTSOCK) return F_status_set_error(F_descriptor);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_listen_

#ifndef _di_f_socket_close_client_
  f_status_t f_socket_close_client(const int id, const unsigned short action) {
    int result = 0;

    if (action == f_socket_close_fast_e) {
      result = close(id);
    }
    else {
      if (action == f_socket_close_read_e || action == f_socket_close_write_e || action == f_socket_close_read_write_e) {
        result = shutdown(id, action);
      }
      else {
        return F_status_set_error(F_supported_not);
      }
    }

    if (result < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_value);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOTCONN) return F_connected_not;
      if (errno == ENOTSOCK) return F_status_set_error(F_descriptor);
      if (errno == ENOSPC) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

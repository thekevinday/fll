#include "socket.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_socket_file_bind_
  f_return_status f_socket_file_bind(const f_string_t path, const int id, struct sockaddr_un *address) {
    memset(&address, 0, sizeof(struct sockaddr_un));
    address->sun_family = AF_UNIX;
    strncpy(address->sun_path, path, sizeof(address->sun_path) - 1);

    if (bind(id, (struct sockaddr *) address, sizeof(struct sockaddr_un)) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      else if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      else if (errno == EADDRNOTAVAIL) return F_status_set_error(F_unavailable_address);
      else if (errno == EFAULT) return F_status_set_error(F_buffer);
      else if (errno == EINVAL) return F_status_set_error(F_busy_socket);
      else if (errno == ELOOP) return F_status_set_error(F_loop);
      else if (errno == ENAMETOOLONG) return F_status_set_error(F_string_too_large);
      else if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      else if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      else if (errno == ENOTDIR) return F_status_set_error(F_directory_found_not);
      else if (errno == ENOTSOCK) return F_status_set_error(F_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_file_bind_

#ifndef _di_f_socket_listen_
  f_return_status f_socket_listen(const int id, const unsigned int max_backlog) {

    if (listen(id, max_backlog) < 0) {
      if (errno == EADDRINUSE) return F_status_set_error(F_busy_address);
      else if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      else if (errno == ENOTSOCK) return F_status_set_error(F_descriptor);
      else if (errno == EOPNOTSUPP) return F_status_set_error(F_unsupported);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_listen_

#ifndef _di_f_socket_close_client_
  f_return_status f_socket_close_client(const int id, const unsigned short action) {
    unsigned int error_code = 0;

    if (action == f_socket_close_fast) {
      if (close(id) < 0) {
        error_code = errno;
      }
    }
    else {
      if (action == f_socket_close_read || action == f_socket_close_write || action == f_socket_close_read_write) {
        if (shutdown(id, action) < 0) {
          error_code = errno;
        }
      }
      else {
        return F_status_set_error(F_unsupported);
      }
    }

    if (error_code > 0) {
      if (error_code == EBADF) return F_status_set_error(F_file_descriptor);
      else if (error_code == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      else if (error_code == EINTR) return F_status_set_error(F_interrupted);
      else if (error_code == EINVAL) return F_status_set_error(F_value);
      else if (error_code == EIO) return F_status_set_error(F_input_output);
      else if (error_code == ENOTCONN) return F_connected_not;
      else if (error_code == ENOTSOCK) return F_status_set_error(F_descriptor);
      else if (error_code == ENOSPC) return F_status_set_error(F_parameter);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

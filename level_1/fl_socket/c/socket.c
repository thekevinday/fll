#include <level_1/socket.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_socket_file_bind_
  f_return_status fl_socket_file_bind(const f_string socket_path, f_socket_id *socket_id, struct sockaddr_un *socket_address) {
    memset(&socket_address, 0, sizeof(struct sockaddr_un));
    socket_address->sun_family = AF_UNIX;
    strncpy(socket_address->sun_path, socket_path, sizeof(socket_address->sun_path) - 1);

    if (bind(*socket_id, (struct sockaddr *) socket_address, sizeof(struct sockaddr_un)) < 0) {
      if (errno == EACCES) {
        return f_access_denied;
      }
      else if (errno == EADDRINUSE) {
        return f_busy_address;
      }
      else if (errno == EADDRNOTAVAIL) {
        return f_unavailable_address;
      }
      else if (errno == EINVAL) {
        return f_busy_socket;
      }
      else if (errno == ENOTSOCK) {
        return f_invalid_socket;
      }
      else if (errno == ENAMETOOLONG) {
        return f_string_too_large;
      }
      else if (errno == ENOENT) {
        return f_file_not_found;
      }
      else if (errno == EFAULT) {
        return f_invalid_address;
      }
      else if (errno == ENOTDIR) {
        return f_directory_not_found;
      }
      else if (errno == ENOMEM) {
        return f_out_of_memory;
      }
      else if (errno == ELOOP) {
        return f_loop;
      }

      return f_failure;
    }

    return f_none;
  }
#endif // _di_fl_socket_file_bind_

#ifndef _di_fl_socket_listen_
  f_return_status fl_socket_listen(const f_socket_id socket_id, const unsigned int socket_backlog) {
    if (listen(socket_id, socket_backlog) < 0) {
      if (errno == EADDRINUSE) {
        return f_busy;
      }
      else if (errno == EBADF) {
        return f_file_descriptor_error;
      }
      else if (errno == ENOTSOCK) {
        return f_invalid_socket;
      }
      else if (errno == EOPNOTSUPP) {
        return f_unsupported;
      }

      return f_failure;
    }

    return f_none;
  }
#endif // _di_fl_socket_listen_

#ifndef _di_fl_socket_close_client_
  // terminate a socket connection.
  f_return_status fl_socket_close_client(const f_socket_id socket_id_client, const f_socket_close_id close_action) {
    unsigned int error_code = 0;

    if (close_action == f_socket_close_fast) {
      if (close(socket_id_client) < 0) {
        error_code = errno;
      }
    }
    else {
      if (close_action == f_socket_close_read || close_action == f_socket_close_write || close_action == f_socket_close_read_write) {
        if (shutdown(socket_id_client, close_action) < 0) {
          error_code = errno;
        }
      }
      else {
        // socket close id is unsupported.
        return f_unsupported;
      }
    }

    if (error_code > 0) {
      if (error_code == EBADF) {
        return f_file_descriptor_error;
      }
      else if (error_code == EINVAL) {
        return f_invalid_value;
      }
      else if (error_code == ENOTCONN) {
        return f_not_connected;
      }
      else if (error_code == ENOTSOCK) {
        return f_invalid_socket;
      }
      else if (error_code == EINTR) {
        return f_interrupted;
      }
      else if (error_code == EBADF) {
        return f_input_output_error;
      }

      return f_failure;
    }

    return f_none;
  }
#endif // _di_fl_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

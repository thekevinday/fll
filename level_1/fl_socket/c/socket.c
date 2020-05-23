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
        return F_access_denied;
      }
      else if (errno == EADDRINUSE) {
        return F_busy_address;
      }
      else if (errno == EADDRNOTAVAIL) {
        return F_unavailable_address;
      }
      else if (errno == EINVAL) {
        return F_busy_socket;
      }
      else if (errno == ENOTSOCK) {
        return F_socket;
      }
      else if (errno == ENAMETOOLONG) {
        return F_string_too_large;
      }
      else if (errno == ENOENT) {
        return F_file_found_not;
      }
      else if (errno == EFAULT) {
        return F_address;
      }
      else if (errno == ENOTDIR) {
        return F_directory_found_not;
      }
      else if (errno == ENOMEM) {
        return F_memory_out;
      }
      else if (errno == ELOOP) {
        return F_loop;
      }

      return F_failure;
    }

    return F_none;
  }
#endif // _di_fl_socket_file_bind_

#ifndef _di_fl_socket_listen_
  f_return_status fl_socket_listen(const f_socket_id socket_id, const unsigned int socket_backlog) {
    if (listen(socket_id, socket_backlog) < 0) {
      if (errno == EADDRINUSE) {
        return F_busy;
      }
      else if (errno == EBADF) {
        return F_file_descriptor;
      }
      else if (errno == ENOTSOCK) {
        return F_socket;
      }
      else if (errno == EOPNOTSUPP) {
        return F_unsupported;
      }

      return F_failure;
    }

    return F_none;
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
        return F_unsupported;
      }
    }

    if (error_code > 0) {
      if (error_code == EBADF) {
        return F_file_descriptor;
      }
      else if (error_code == EINVAL) {
        return F_value;
      }
      else if (error_code == ENOTCONN) {
        return F_connected_not;
      }
      else if (error_code == ENOTSOCK) {
        return F_socket;
      }
      else if (error_code == EINTR) {
        return F_interrupted;
      }
      else if (error_code == EBADF) {
        return F_input_output;
      }

      return F_failure;
    }

    return F_none;
  }
#endif // _di_fl_socket_close_client_

#ifdef __cplusplus
} // extern "C"
#endif

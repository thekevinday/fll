#include "mock-socket.h"

#ifdef __cplusplus
extern "C" {
#endif

int mock_unwrap = 0;
int mock_unwrap_f_memory = 1;

f_status_t __wrap_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

  if (mock_unwrap_f_memory) {
    return __real_f_memory_array_adjust(length, width, array, used, size);
  }

  if (!array || !used || !size) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

  if (mock_unwrap_f_memory) {
    return __real_f_memory_array_resize(length, width, array, used, size);
  }

  if (!array || !used || !size) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

int __wrap_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_close(int fd) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_gethostname(char *name, size_t len) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_listen(int sockfd, int backlog) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

ssize_t __wrap_recv(int sockfd, void *buf, size_t len, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

ssize_t __wrap_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

ssize_t __wrap_recvmsg(int sockfd, struct msghdr *msg, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

ssize_t __wrap_send(int sockfd, const void *buf, size_t len, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

ssize_t __wrap_sendmsg(int sockfd, const struct msghdr *msg, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

ssize_t __wrap_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_shutdown(int sockfd, int how) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_socket(int domain, int type, int protocol) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_socketpair(int domain, int type, int protocol, int sv[2]) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif

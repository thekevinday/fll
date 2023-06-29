#include "mock-network.h"

#ifdef __cplusplus
extern "C" {
#endif

struct hostent *__wrap_gethostbyaddr(const void *addr, socklen_t len, int type) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  return mock_type(struct hostent *);
}

struct hostent *__wrap_gethostbyname(const char *name) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  return mock_type(struct hostent *);
}

uint32_t __wrap_htonl(uint32_t hostlong) {

  return mock_type(uint32_t);
}

uint16_t __wrap_htons(uint16_t hostshort) {

  return mock_type(uint16_t);
}

const char *__wrap_inet_ntop(int af, const void *src, char *dst, socklen_t size) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  char *string = mock_type(char *);
  size_t total = mock_type(size_t);

  if (dst) {
    memcpy(dst, string, total);
    dst[total] = 0;
  }

  return dst;
}

uint32_t __wrap_ntohl(uint32_t netlong) {

  return mock_type(uint32_t);
}

uint16_t __wrap_ntohs(uint16_t netshort) {

  return mock_type(uint16_t);
}

int __wrap_inet_pton(int af, const char *src, void *dst) {

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

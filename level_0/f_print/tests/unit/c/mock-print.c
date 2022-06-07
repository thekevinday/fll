#include "mock-print.h"

#ifdef __cplusplus
extern "C" {
#endif

void __wrap_clearerr_unlocked(FILE *stream) {
}

int __wrap_ferror_unlocked(FILE *stream) {

  return mock_type(int);
}

size_t __wrap_fwrite_unlocked(const void *ptr, size_t size, size_t nmemb, FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return nmemb;
}

ssize_t __wrap_write(int fd, const void *buf, size_t count) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(ssize_t);
}

#ifdef __cplusplus
} // extern "C"
#endif

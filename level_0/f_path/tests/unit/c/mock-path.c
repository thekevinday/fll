#include "mock-path.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_chdir(const char *path) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_fchdir(int fd) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

char *__wrap_getcwd(char *buf, size_t size) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  return mock_type(char *);
}

char *__wrap_realpath(const char *path, char *resolved_path) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  resolved_path = mock_type(char *);

  return resolved_path;
}

#ifdef __cplusplus
} // extern "C"
#endif

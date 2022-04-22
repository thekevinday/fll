#include "mock-environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_libcap_
  int __wrap_cap_free(void *obj_d) {

    return mock_type(int);
  }

  int __wrap_cap_get_flag(cap_t cap_p, cap_value_t cap, cap_flag_t flag, cap_flag_value_t *value_p) {

    const bool failure = mock_type(bool);

    if (failure) {
      errno = mock_type(int);

      return -1;
    }

    *value_p = mock_type(cap_flag_value_t);

    return mock_type(int);
  }

  cap_t __wrap_cap_get_proc(void) {

    const bool failure = mock_type(bool);

    if (failure) {
      errno = mock_type(int);

      return 0;
    }

    return mock_type(cap_t);
  }

  int __wrap_cap_set_proc(cap_t cap_p) {

    const bool failure = mock_type(bool);

    if (failure) {
      errno = mock_type(int);

      return -1;
    }

    return mock_type(int);
  }
#endif // _di_libcap_

int __wrap_clearenv(void) {

  return mock_type(int);
}

int __wrap_getegid(void) {

  return mock_type(int);
}

char *__wrap_getenv(const char *name) {

  return mock_type(char *);
}

int __wrap_geteuid(void) {

  return mock_type(int);
}

int __wrap_getgid(void) {

  return mock_type(int);
}

int __wrap_getuid(void) {

  return mock_type(int);
}

int __wrap_setenv(const char *name, const char *value, int overwrite) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_unsetenv(const char *name) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

#ifdef __cplusplus
} // extern "C"
#endif

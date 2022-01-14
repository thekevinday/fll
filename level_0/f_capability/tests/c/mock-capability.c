#include "mock-capability.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_cap_get_ambient(cap_value_t value) {

  bool failure = mock_type(bool);

  if (failure) {
    return -1;
  }

  return 1;
}

int __wrap_cap_clear(cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_clear_flag(cap_t capability, cap_flag_value_t flag_value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_compare(cap_t capability_1, cap_t capability_2) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

ssize_t __wrap_cap_copy_ext(void *data, cap_t capability, ssize_t size) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

cap_t __wrap_cap_copy_int(void *data) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

int __wrap_cap_drop_bound(cap_value_t value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

cap_t __wrap_cap_dup(cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

int __wrap_cap_free(void *pointer) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_from_name(const char *name, cap_value_t *value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

cap_t __wrap_cap_from_text(const char *text) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

int __wrap_cap_get_bound(cap_value_t value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

cap_t __wrap_cap_get_fd(int descriptor) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

cap_t __wrap_cap_get_file(const char *path) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

int __wrap_cap_get_flag(cap_t capability, cap_value_t value, cap_flag_t flag, cap_flag_value_t *flag_value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

cap_mode_t __wrap_cap_get_mode(void) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_mode_t) 0;
  }

  return (cap_mode_t) 1;
}

uid_t __wrap_cap_get_nsowner(cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (uid_t) -1;
  }

  return (uid_t) 1;
}

cap_t __wrap_cap_init(void) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

const char *__wrap_cap_mode_name(cap_mode_t mode) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (char *) 0;
  }

  return (char *) 1;
}

cap_t __wrap_cap_get_pid(pid_t pid) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

cap_t __wrap_cap_get_proc(void) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (cap_t) 0;
  }

  return (cap_t) 1;
}

unsigned __wrap_cap_get_secbits(void) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_reset_ambient(void) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_ambient(cap_value_t value, cap_flag_value_t flag_value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_fd(int descriptor, cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_file(const char *path, cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_flag(cap_t capability, cap_flag_t flag, int number, const cap_value_t *value, cap_flag_value_t flag_value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_mode(cap_mode_t mode) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_nsowner(cap_t capability, uid_t id) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_proc(cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_set_secbits(unsigned bits) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_setgroups(gid_t gid, size_t total, const gid_t groups[]) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

int __wrap_cap_setuid(uid_t uid) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

ssize_t __wrap_cap_size(cap_t capability) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 1;
}

char * __wrap_cap_to_text(cap_t capability, ssize_t *size) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (char *) 0;
  }

  *size = mock_type(int);

  return mock_type(char *);
}

char * __wrap_cap_to_name(cap_value_t value) {

  bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return (char *) 0;
  }

  return mock_type(char *);
}

#ifdef __cplusplus
} // extern "C"
#endif

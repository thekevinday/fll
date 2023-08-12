#include "mock-account.h"

#ifdef __cplusplus
extern "C" {
#endif

int mock_unwrap = 0;

f_status_t __wrap_f_string_dynamic_adjust(const f_number_unsigned_t length, f_string_dynamic_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamic_adjust(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_dynamic_resize(const f_number_unsigned_t length, f_string_dynamic_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamic_resize(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

int __wrap_getpwnam_r(const char * const name, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 1;
  }

  *pwd = *mock_type(struct passwd *);
  *result = mock_type(struct passwd *);

  return 0;
}

int __wrap_getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 1;
  }

  *pwd = *mock_type(struct passwd *);
  *result = mock_type(struct passwd *);

  return 0;
}

int __wrap_getgrnam_r(const char * const name, struct group *grp, char *buf, size_t buflen, struct group **result) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 1;
  }

  *grp = *mock_type(struct group *);
  *result = mock_type(struct group *);

  return 0;
}

int __wrap_getgrgid_r(uid_t uid, struct group *grp, char *buf, size_t buflen, struct group **result) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 1;
  }

  *grp = *mock_type(struct group *);
  *result = mock_type(struct group *);

  return 0;
}

long __wrap_sysconf(int name) {

  return mock_type(long);
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "mock-account.h"

#ifdef __cplusplus
extern "C" {
#endif

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

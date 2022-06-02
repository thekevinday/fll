#include "mock-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

/*int __wrap_getgrgid_r(uid_t uid, struct group *grp, char *buf, size_t buflen, struct group **result) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 1;
  }

  *grp = *mock_type(struct group *);
  *result = mock_type(struct group *);

  return 0;
}*/

#ifdef __cplusplus
} // extern "C"
#endif

#include "mock-limit.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_prlimit(pid_t pid, int resource, const struct rlimit *new_limit, struct rlimit *old_limit) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  if (old_limit) {
    struct rlimit *mocked_limit = mock_type(struct rlimit *);

    old_limit->rlim_cur = mocked_limit->rlim_cur;
    old_limit->rlim_max = mocked_limit->rlim_max;
  }

  return mock_type(int);
}

#ifdef __cplusplus
} // extern "C"
#endif

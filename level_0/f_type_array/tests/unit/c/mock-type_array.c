#include "mock-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_poll(f_poll_t *fds, nfds_t nfds, int timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  fds->revents = mock_type(short);

  return mock_type(int);
}

#ifdef __cplusplus
} // extern "C"
#endif

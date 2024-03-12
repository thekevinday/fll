#include "mock-random.h"

#ifdef __cplusplus
extern "C" {
#endif

int mock_unwrap = 0;

ssize_t __wrap_getrandom(void *buf, size_t buflen, unsigned int flags) {

  if (mock_unwrap) {
    return __real_getrandom(buf, buflen, flags);
  }

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return mock_type(ssize_t);
  }

  memcpy(buf, mock_type(void *), buflen);

  return mock_type(ssize_t);
}

long __wrap_random(void) {

  if (mock_unwrap) {
    return __real_random();
  }

  return mock_type(long);
}

void __wrap_srandom(unsigned seed) {

  if (mock_unwrap) {
    return __real_srandom(seed);
  }

  // Do nothing.
}

#ifdef __cplusplus
} // extern "C"
#endif

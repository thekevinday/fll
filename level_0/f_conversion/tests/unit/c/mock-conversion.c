#include "mock-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t __wrap_fwrite_unlocked(const void *ptr, size_t size, size_t n, FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  check_expected(ptr);

  return n;
}

#ifdef __cplusplus
} // extern "C"
#endif

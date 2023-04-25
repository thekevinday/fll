#include "mock-conversion.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_ferror_unlocked(FILE *stream) {

  return mock_type(int);
}

size_t __wrap_fwrite_unlocked(const void * const ptr, size_t size, size_t nmemb, FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(size_t);
  }

  const bool check_ptr = mock_type(bool);

  if (check_ptr) {
    check_expected(ptr);
  }

  return nmemb;
}

#ifdef __cplusplus
} // extern "C"
#endif

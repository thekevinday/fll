#include "mock-color.h"

#ifdef __cplusplus
extern "C" {
#endif

char * __wrap_getenv(char *name) {

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

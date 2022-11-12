#include "mock-color.h"

#ifdef __cplusplus
extern "C" {
#endif

char * __wrap_getenv(char *name) {

  const bool failure = mock_type(bool);

  if (failure) {
    return (char *) 0;
  }

  return mock_type(char *);
}

#ifdef __cplusplus
} // extern "C"
#endif

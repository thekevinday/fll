#include "test-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *data__file_open__named(const f_string_t set, const f_string_t name, const f_string_t context) {

  char path[255];

  memset(path, 0, 255);

  snprintf(path, 254, "./data/tests/%s/%s-%s.txt", set, name, context);

  return fopen(path, "r");
}

FILE *data__file_open__named_at(const f_string_t set, const f_string_t name, const f_string_t context, const uint16_t at) {

  char path[255];

  memset(path, 0, 255);

  snprintf(path, 254, "./data/tests/%s/%s-%s-%d.txt", set, name, context, at);

  return fopen(path, "r");
}

#ifdef __cplusplus
} // extern "C"
#endif

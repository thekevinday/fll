#include "data-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *data__file_open__named__all_read(const f_string_t set, const f_string_t name) {
  char path[255];

  memset(path, 0, 255);

  snprintf(path, 254, "./data/tests/%s/%s-all_read.txt", set, name);

  return fopen(path, "r");
}

FILE *data__file_open__named_at__all_read(const f_string_t set, const f_string_t name, const uint8_t at) {
  char path[255];

  memset(path, 0, 255);

  snprintf(path, 254, "./data/tests/%s/%s-all_read-%d.txt", set, name, at);

  return fopen(path, "r");
}

#ifdef __cplusplus
} // extern "C"
#endif

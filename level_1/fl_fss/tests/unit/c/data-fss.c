#include "data-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *data__contents_file_open__basic_all_read(void) {
  return fopen("./data/tests/contents/basic-all_read.txt", "r");
}

FILE *data__objects_file_open__basic_all_read(void) {
  return fopen("./data/tests/objects/basic-all_read.txt", "r");
}

FILE *data__strings_file_open__basic_all_read(void) {
  return fopen("./data/tests/strings/basic-all_read.txt", "r");
}

#ifdef __cplusplus
} // extern "C"
#endif

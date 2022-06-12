#include "data-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *data__bytesequence_file_open__symbols(void) {

  return fopen("./data/tests/bytesequences/symbols-all.txt", "r");
}

FILE *data__bytesequence_file_open__private(void) {

  return fopen("./data/tests/bytesequences/private-all.txt", "r");
}

uint8_t data__bytesequence_get_line(FILE * const file, f_utf_char_t * const character) {

  size_t length = 32;
  char *line = 0;

  const int8_t bytes = (int8_t) getline(&line, &length, file);
  if (bytes == -1) return 0;

  if (!bytes) {
    if (line) {
      free(line);
    }

    return 0;
  }

  const long long number = atoll(line);

  if (line) {
    free(line);
  }

  if (!number) return -1;

  *character = (f_utf_char_t) number;

  // Network order is always big-endian so take advantage of this for converting little endian integers.
  #ifdef _is_F_endian_little
    *character = htonl(*character);
  #endif // _is_F_endian_little

  return bytes;
}

#ifdef __cplusplus
} // extern "C"
#endif

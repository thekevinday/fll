#include "data-utf.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *data__bytesequence_file_open__alphabetic(void) {

  return fopen("./data/tests/bytesequences/alphabetic-all.txt", "r");
}

FILE *data__bytesequence_file_open__combining(void) {

  return fopen("./data/tests/bytesequences/combining-all.txt", "r");
}

FILE *data__bytesequence_file_open__control(void) {

  return fopen("./data/tests/bytesequences/control-all.txt", "r");
}

FILE *data__bytesequence_file_open__digit(void) {

  return fopen("./data/tests/bytesequences/digit-all.txt", "r");
}

FILE *data__bytesequence_file_open__emoji(void) {

  return fopen("./data/tests/bytesequences/emoji-all.txt", "r");
}

FILE *data__bytesequence_file_open__numeric(void) {

  return fopen("./data/tests/bytesequences/numeric-all.txt", "r");
}

FILE *data__bytesequence_file_open__phonetic(void) {

  return fopen("./data/tests/bytesequences/phonetic-all.txt", "r");
}

FILE *data__bytesequence_file_open__private(void) {

  return fopen("./data/tests/bytesequences/private-all.txt", "r");
}

FILE *data__bytesequence_file_open__punctuation(void) {

  return fopen("./data/tests/bytesequences/punctuation-all.txt", "r");
}

FILE *data__bytesequence_file_open__subscript(void) {

  return fopen("./data/tests/bytesequences/subscript-all.txt", "r");
}

FILE *data__bytesequence_file_open__superscript(void) {

  return fopen("./data/tests/bytesequences/superscript-all.txt", "r");
}

FILE *data__bytesequence_file_open__surrogate(void) {

  return fopen("./data/tests/bytesequences/superscript-surrogate.txt", "r");
}

FILE *data__bytesequence_file_open__symbol(void) {

  return fopen("./data/tests/bytesequences/symbol-all.txt", "r");
}

FILE *data__bytesequence_file_open__valid(void) {

  return fopen("./data/tests/bytesequences/valid-all.txt", "r");
}

FILE *data__bytesequence_file_open__whitespace(void) {

  return fopen("./data/tests/bytesequences/whitespace-all.txt", "r");
}

FILE *data__bytesequence_file_open__wide(void) {

  return fopen("./data/tests/bytesequences/wide-all.txt", "r");
}

FILE *data__bytesequence_file_open__word(void) {

  return fopen("./data/tests/bytesequences/word-all.txt", "r");
}

FILE *data__bytesequence_file_open__zero_width(void) {

  return fopen("./data/tests/bytesequences/zero_width-all.txt", "r");
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

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

ssize_t data__bytesequence_get_line(FILE * const file, f_utf_char_t * const character) {

  size_t length = 0;
  char *line = 0;

  const ssize_t bytes = getline(&line, &length, file);

  if (bytes == -1 || !bytes) {
    if (line) {
      free(line);
    }

    return bytes;
  }

  const long long number = atoll(line);

  if (line) {
    free(line);
  }

  if (!number && bytes != 2 && line[0] != '0') return -1;

  #ifdef _is_F_endian_little
    if ((F_utf_char_mask_byte_1_le_d & number) == number) {
      *character = (f_utf_char_t) ((F_utf_char_mask_byte_1_le_d & number) << 24);
    }
    else if ((F_utf_char_mask_byte_2_le_d & number) == number) {
      *character = (f_utf_char_t) ((F_utf_char_mask_byte_2_le_d & number) << 16);
    }
    else if ((F_utf_char_mask_byte_3_le_d & number) == number) {
      *character = (f_utf_char_t) ((F_utf_char_mask_byte_3_le_d & number) << 8);
    }
    else if ((F_utf_char_mask_byte_4_le_d & number) == number) {
      *character = (f_utf_char_t) ((F_utf_char_mask_byte_4_le_d & number));
    }
  #else
    *character = (f_utf_char_t) number;
  #endif // _is_F_endian_little

  return bytes;
}

#ifdef __cplusplus
} // extern "C"
#endif

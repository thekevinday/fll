#include "test-utf.h"
#include "test-utf-character_is_phonetic.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_character_is_phonetic__works(void **state) {

  {
    FILE *file = data__bytesequence_file_open__phonetic();

    assert_non_null(file);

    f_utf_char_t sequence = 0;
    ssize_t bytes = 0;

    f_number_unsigned_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &sequence);

      if (bytes > 0) {
        const f_status_t status = f_utf_character_is_phonetic(sequence);

        assert_int_equal(status, F_true);
      }

      ++line;

    } while (bytes > 0);

    fclose(file);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

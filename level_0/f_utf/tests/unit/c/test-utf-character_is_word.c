#include "test-utf.h"
#include "test-utf-character_is_word.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_character_is_word__strict_is_false(void **state) {

  {
    FILE *file = data__bytesequence_file_open__word();

    assert_non_null(file);

    f_utf_char_t character = 0;
    int8_t bytes = 0;

    f_array_length_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &character);

      if (bytes) {
        const f_status_t status = f_utf_character_is_word(character, F_false);

        // @todo provide an array of codes that should return false when not strict.
        assert_true(status);
      }

      ++line;

    } while (bytes > 0);

    fclose(file);
  }
}

void test__f_utf_character_is_word__strict_is_true(void **state) {

  {
    FILE *file = data__bytesequence_file_open__word();

    assert_non_null(file);

    f_utf_char_t character = 0;
    int8_t bytes = 0;

    f_array_length_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &character);

      if (bytes) {
        const f_status_t status = f_utf_character_is_word(character, F_true);

        assert_true(status);
      }

      ++line;

    } while (bytes > 0);

    fclose(file);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

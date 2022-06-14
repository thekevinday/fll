#include "test-utf.h"
#include "test-utf-character_is_subscript.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_character_is_subscript__works(void **state) {

  {
    FILE *file = data__bytesequence_file_open__subscript();

    assert_non_null(file);

    f_utf_char_t character = 0;
    int8_t bytes = 0;

    f_array_length_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &character);

      if (bytes) {
        const f_status_t status = f_utf_character_is_subscript(character);

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

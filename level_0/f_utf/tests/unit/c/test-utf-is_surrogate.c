#include "test-utf.h"
#include "test-utf-is_surrogate.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_is_surrogate__works(void **state) {

  {
    FILE *file = data__bytesequence_file_open__surrogate();

    assert_non_null(file);

    f_utf_char_t character = 0;
    int8_t bytes = 0;

    f_array_length_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &character);

      if (bytes) {
        const uint8_t width = macro_f_utf_char_t_width(character);
        char buffer[5] = { 0, 0, 0, 0, 0 };

        buffer[0] = macro_f_utf_char_t_to_char_1(character);

        if (width > 1) {
          buffer[1] = macro_f_utf_char_t_to_char_2(character);

          if (width > 2) {
            buffer[2] = macro_f_utf_char_t_to_char_3(character);

            if (width > 3) {
              buffer[3] = macro_f_utf_char_t_to_char_4(character);
            }
          }
        }

        const f_status_t status = f_utf_is_surrogate(buffer, 5);

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

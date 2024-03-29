#include "test-utf.h"
#include "test-utf-is_word_dash_plus.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_is_word_dash_plus__strict_is_false(void **state) {

  {
    FILE *file = data__bytesequence_file_open__word_dash_plus__lax();

    assert_non_null(file);

    f_utf_char_t sequence = 0;
    ssize_t bytes = 0;

    f_array_length_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &sequence);

      if (bytes > 0) {
        const uint8_t width = macro_f_utf_char_t_width(sequence);
        char buffer[5] = { 0, 0, 0, 0, 0 };

        buffer[0] = macro_f_utf_char_t_to_char_1(sequence);

        if (width > 1) {
          buffer[1] = macro_f_utf_char_t_to_char_2(sequence);

          if (width > 2) {
            buffer[2] = macro_f_utf_char_t_to_char_3(sequence);

            if (width > 3) {
              buffer[3] = macro_f_utf_char_t_to_char_4(sequence);
            }
          }
        }

        const f_status_t status = f_utf_is_word_dash_plus(buffer, 5, F_false);

        assert_int_equal(status, F_true);
      }

      ++line;

    } while (bytes > 0);

    fclose(file);
  }
}

void test__f_utf_is_word_dash_plus__strict_is_true(void **state) {

  {
    FILE *file = data__bytesequence_file_open__word_dash_plus();

    assert_non_null(file);

    f_utf_char_t sequence = 0;
    ssize_t bytes = 0;

    f_array_length_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &sequence);

      if (bytes > 0) {
        const uint8_t width = macro_f_utf_char_t_width(sequence);
        char buffer[5] = { 0, 0, 0, 0, 0 };

        buffer[0] = macro_f_utf_char_t_to_char_1(sequence);

        if (width > 1) {
          buffer[1] = macro_f_utf_char_t_to_char_2(sequence);

          if (width > 2) {
            buffer[2] = macro_f_utf_char_t_to_char_3(sequence);

            if (width > 3) {
              buffer[3] = macro_f_utf_char_t_to_char_4(sequence);
            }
          }
        }

        const f_status_t status = f_utf_is_word_dash_plus(buffer, 5, F_true);

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

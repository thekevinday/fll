#include "test-utf.h"
#include "test-utf-is_digit.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_is_digit__works(void **state) {

  {
    FILE *file = data__bytesequence_file_open__digit();
    FILE *file_number = data__value_file_open__digit();

    assert_non_null(file);
    assert_non_null(file_number);

    f_utf_char_t sequence = 0;
    ssize_t bytes = 0;
    ssize_t bytes_number = 0;
    uint64_t number = 0;
    f_number_unsigned_t line = 0;

    do {
      bytes = data__bytesequence_get_line(file, &sequence);
      bytes_number = data__value_get_line_long_long(file_number, &number);

      if (bytes > 0 && bytes_number > 0) {
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

        uint64_t value = 0;

        const f_status_t status = f_utf_is_digit(buffer, 5, &value);

        assert_int_equal(status, F_true);
        assert_int_equal(value, number);
      }

      ++line;

    } while (bytes > 0 && bytes_number > 0);

    fclose(file);
    fclose(file_number);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

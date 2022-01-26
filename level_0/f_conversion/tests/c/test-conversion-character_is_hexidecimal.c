#include "test-conversion.h"
#include "test-conversion-character_is_hexidecimal.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_character_is_hexidecimal__works(void **state) {

  for (uint8_t i = 0; i <= 0xff; ++i) {

    const f_status_t status = f_conversion_character_is_hexidecimal(i);

    switch (i) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case 'a':
      case 'A':
      case 'b':
      case 'B':
      case 'c':
      case 'C':
      case 'd':
      case 'D':
      case 'e':
      case 'E':
      case 'f':
      case 'F':
        assert_int_equal(status, F_true);
        break;

      default:
        assert_int_equal(status, F_false);
        break;
    }

    if (i == 0xff) break;
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-conversion.h"
#include "test-conversion-character_is_binary.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_character_is_binary__works(void **state) {

  for (uint8_t i = 0; i <= 0xff; ++i) {

    const f_status_t status = f_conversion_character_is_binary(i);

    switch (i) {
      case '0':
      case '1':
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

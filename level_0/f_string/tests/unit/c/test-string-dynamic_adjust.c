#include "test-string.h"
#include "test-string-dynamic_adjust.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_adjust__works(void **state) {

  const int length = 5;
  f_string_dynamic_t data = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_adjust(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.string);
}

void test__f_string_dynamic_adjust__parameter_checking(void **state) {

  const int length = 5;
  f_string_dynamic_t data = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_adjust(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.string);
}

#ifdef __cplusplus
} // extern "C"
#endif

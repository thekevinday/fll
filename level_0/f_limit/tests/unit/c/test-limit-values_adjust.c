#include "test-limit.h"
#include "test-limit-values_adjust.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_values_adjust__parameter_checking(void **state) {

  const int length = 5;
  f_limit_values_t data = f_limit_values_t_initialize;

  {
    const f_status_t status = f_limit_values_adjust(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_limit_values_adjust__works(void **state) {

  const int length = 5;
  f_limit_values_t data = f_limit_values_t_initialize;

  {
    const f_status_t status = f_limit_values_adjust(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

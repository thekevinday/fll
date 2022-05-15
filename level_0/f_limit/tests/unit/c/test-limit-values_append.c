#include "test-limit.h"
#include "test-limit-values_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_values_append__parameter_checking(void **state) {

  const f_limit_value_t data = f_limit_value_t_initialize;

  {
    const f_status_t status = f_limit_values_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_limit_values_append__works(void **state) {

  const f_limit_value_t source = macro_f_limit_value_t_initialize(1, 2);
  f_limit_values_t destination = f_limit_values_t_initialize;

  {
    const f_status_t status = f_limit_values_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].rlim_cur, source.rlim_cur);
    assert_int_equal(destination.array[0].rlim_max, source.rlim_max);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

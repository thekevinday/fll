#include "test-limit.h"
#include "test-limit-sets_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_sets_append__parameter_checking(void **state) {

  const f_limit_set_t data = f_limit_set_t_initialize;

  {
    const f_status_t status = f_limit_sets_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_limit_sets_append__works(void **state) {

  const f_limit_set_t source = macro_f_limit_set_t_initialize_1(1, macro_f_limit_value_t_initialize_1(2, 3));
  f_limit_sets_t destination = f_limit_sets_t_initialize;

  {
    const f_status_t status = f_limit_sets_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].type, source.type);
    assert_int_equal(destination.array[0].value.rlim_cur, source.value.rlim_cur);
    assert_int_equal(destination.array[0].value.rlim_max, source.value.rlim_max);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

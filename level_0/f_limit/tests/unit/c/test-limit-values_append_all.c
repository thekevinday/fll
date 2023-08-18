#include "test-limit.h"
#include "test-limit-values_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_values_append_all__parameter_checking(void **state) {

  const f_limit_values_t data = f_limit_values_t_initialize;

  {
    const f_status_t status = f_limit_values_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_limit_values_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_limit_values_t source = f_limit_values_t_initialize;
  f_limit_values_t destination = f_limit_values_t_initialize;

  {
    const f_status_t status = f_limit_values_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_limit_values_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_limit_values_append_all__works(void **state) {

  const int length = 5;
  const int length_used = 2;
  f_limit_values_t source = f_limit_values_t_initialize;
  f_limit_values_t destination = f_limit_values_t_initialize;

  {
    const f_status_t status = f_limit_values_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length_used; ++source.used) {

    source.array[source.used].rlim_cur = source.used + 1;
    source.array[source.used].rlim_max = source.used + 2;
  } // for
  {
    const f_status_t status = f_limit_values_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      assert_int_equal(destination.array[i].rlim_cur, i + 1);
      assert_int_equal(destination.array[i].rlim_max, i + 2);
    } // for
  }

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

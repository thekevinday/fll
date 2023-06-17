#include "test-limit.h"
#include "test-limit-valuess_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_valuess_append__parameter_checking(void **state) {

  f_limit_values_t data = f_limit_valuess_t_initialize;

  {
    const f_status_t status = f_limit_valuess_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_limit_valuess_append__returns_data_not(void **state) {

  const int length = 5;
  f_limit_values_t source = f_limit_valuess_t_initialize;
  f_limit_valuess_t destination = f_limit_valuess_t_initialize;

  {
    const f_status_t status = f_limit_values_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_limit_valuess_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_limit_valuess_append__works(void **state) {

  const int length = 5;
  f_limit_values_t source = f_limit_valuess_t_initialize;
  f_limit_valuess_t destination = f_limit_valuess_t_initialize;

  {
    const f_status_t status = f_limit_values_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length; ++source.used) {

    source.array[source.used].rlim_cur = source.used + 1;
    source.array[source.used].rlim_max = source.used + 2;
  } // for

  {
    const f_status_t status = f_limit_valuess_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

      assert_int_equal(destination.array[0].array[i].rlim_cur, i + 1);
      assert_int_equal(destination.array[0].array[i].rlim_max, i + 2);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-limit.h"
#include "test-limit-setss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_setss_append__parameter_checking(void **state) {

  f_limit_sets_t data = f_limit_setss_t_initialize;

  {
    const f_status_t status = f_limit_setss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_limit_setss_append__returns_data_not(void **state) {

  const int length = 5;
  f_limit_sets_t source = f_limit_setss_t_initialize;
  f_limit_setss_t destination = f_limit_setss_t_initialize;

  {
    const f_status_t status = f_limit_sets_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_limit_setss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_limit_setss_append__works(void **state) {

  const int length = 5;
  f_limit_sets_t source = f_limit_setss_t_initialize;
  f_limit_setss_t destination = f_limit_setss_t_initialize;

  {
    const f_status_t status = f_limit_sets_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length; ++source.used) {

    source.array[source.used].type = source.used + 1;
    source.array[source.used].value.rlim_cur = source.used + 2;
    source.array[source.used].value.rlim_max = source.used + 3;
  } // for

  {
    const f_status_t status = f_limit_setss_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

      assert_int_equal(destination.array[0].array[i].type, i + 1);
      assert_int_equal(destination.array[0].array[i].value.rlim_cur, i + 2);
      assert_int_equal(destination.array[0].array[i].value.rlim_max, i + 3);
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

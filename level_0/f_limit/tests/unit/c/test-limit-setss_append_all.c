#include "test-limit.h"
#include "test-limit-setss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_limit_setss_append_all__parameter_checking(void **state) {

  const f_limit_setss_t data = f_limit_setss_t_initialize;

  {
    const f_status_t status = f_limit_setss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_limit_setss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_limit_setss_t source = f_limit_setss_t_initialize;
  f_limit_setss_t destination = f_limit_setss_t_initialize;

  {
    const f_status_t status = f_limit_setss_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_limit_setss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_limit_setss_append_all__works(void **state) {

  const int length = 5;
  const int length_inner = 2;
  f_limit_setss_t source = f_limit_setss_t_initialize;
  f_limit_setss_t destination = f_limit_setss_t_initialize;

  {
    const f_status_t status = f_limit_setss_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    for (; source.used < length; ++source.used) {

      const f_status_t status = f_limit_sets_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_okay);

      for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

        source.array[source.used].array[i].type = i + 1;
        source.array[source.used].array[i].value.rlim_cur = i + 2;
        source.array[source.used].array[i].value.rlim_max = i + 3;
      } // for

      source.array[source.used].used = length_inner;
    } // for
  }

  {
    const f_status_t status = f_limit_setss_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < destination.used; ++i) {

      assert_int_equal(destination.array[i].used, length_inner);
      assert_int_equal(destination.array[i].size, length_inner);

      for (f_number_unsigned_t j = 0; j < length_inner; ++j) {

        assert_int_equal(destination.array[i].array[j].type, j + 1);
        assert_int_equal(destination.array[i].array[j].value.rlim_cur, j + 2);
        assert_int_equal(destination.array[i].array[j].value.rlim_max, j + 3);
      } // for
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].array);
  } // for

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

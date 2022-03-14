#include "test-type_array.h"
#include "test-type_array-int64s_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int64s_append_all__works(void **state) {

  const int length = 5;
  const int length_used = 2;
  f_int64s_t source = f_int64s_t_initialize;
  f_int64s_t destination = f_int64s_t_initialize;

  {
    const f_status_t status = f_int64s_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length_used; ++source.used) {
    source.array[source.used] = source.used + 1;
  } // for

  {
    const f_status_t status = f_int64s_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_array_length_t i = 0; i < source.used; ++i) {
      assert_int_equal(destination.array[i], i + 1);
    } // for
  }

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_int64s_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_int64s_t source = f_int64s_t_initialize;
  f_int64s_t destination = f_int64s_t_initialize;

  {
    const f_status_t status = f_int64s_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_int64s_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_int64s_append_all__parameter_checking(void **state) {

  const f_int64s_t data = f_int64s_t_initialize;

  {
    const f_status_t status = f_int64s_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

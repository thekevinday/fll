#include "test-type_array.h"
#include "test-type_array-int16ss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int16ss_append__works(void **state) {

  const int length = 5;
  f_int16s_t source = f_int16s_t_initialize;
  f_int16ss_t destination = f_int16ss_t_initialize;

  {
    const f_status_t status = f_int16s_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  for (; source.used < length; ++source.used) {
    source.array[source.used] = source.used + 1;
  } // for

  {
    const f_status_t status = f_int16ss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_array_length_t i = 0; i < destination.array[0].used; ++i) {
      assert_int_equal(destination.array[0].array[i], i + 1);
    } // for
  }

  for (f_array_length_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_int16ss_append__returns_data_not(void **state) {

  const int length = 5;
  f_int16s_t source = f_int16s_t_initialize;
  f_int16ss_t destination = f_int16ss_t_initialize;

  {
    const f_status_t status = f_int16s_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_int16ss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_int16ss_append__parameter_checking(void **state) {

  f_int16s_t data = f_int16s_t_initialize;

  {
    const f_status_t status = f_int16ss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

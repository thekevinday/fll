#include "test-type_array.h"
#include "test-type_array-uint32ss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_uint32ss_append_all__parameter_checking(void **state) {

  const f_uint32ss_t data = f_uint32ss_t_initialize;

  {
    const f_status_t status = f_uint32ss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_uint32ss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_uint32ss_t source = f_uint32ss_t_initialize;
  f_uint32ss_t destination = f_uint32ss_t_initialize;

  {
    const f_status_t status = f_uint32ss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_uint32ss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_uint32ss_append_all__works(void **state) {

  const int length = 5;
  const int length_inner = 2;
  f_uint32ss_t source = f_uint32ss_t_initialize;
  f_uint32ss_t destination = f_uint32ss_t_initialize;

  {
    const f_status_t status = f_uint32ss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    for (; source.used < length; ++source.used) {

      const f_status_t status = f_uint32s_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_none);

      for (f_array_length_t i = 0; i < length_inner; ++i) {
        source.array[source.used].array[source.array[source.used].used++] = i + 1;
      } // for
    } // for
  }

  {
    const f_status_t status = f_uint32ss_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_array_length_t i = 0; i < destination.used; ++i) {

      assert_int_equal(destination.array[i].used, length_inner);
      assert_int_equal(destination.array[i].size, length_inner);

      for (f_array_length_t j = 0; j < length_inner; ++j) {
        assert_int_equal(destination.array[i].array[j], j + 1);
      } // for
    } // for
  }

  for (f_array_length_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].array);
  } // for

  for (f_array_length_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

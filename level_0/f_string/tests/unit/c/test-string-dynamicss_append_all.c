#include "test-string.h"
#include "test-string-dynamicss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamicss_append_all__works(void **state) {

  const int length_inner = 2;
  const int length_outer = 2;
  f_string_dynamicss_t source = f_string_dynamicss_t_initialize;
  f_string_dynamicss_t destination = f_string_dynamicss_t_initialize;

  const f_string_static_t test_names[] = {
    macro_f_string_static_t_initialize("test1", 0, 5),
    macro_f_string_static_t_initialize("test2", 0, 5),
  };

  {
    f_status_t status = f_string_dynamicss_resize(length_outer, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length_outer);

    f_array_length_t i = 0;

    for (; source.used < length_outer; ++source.used) {

      status = f_string_dynamics_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_none);
      assert_int_equal(source.array[source.used].used, 0);
      assert_int_equal(source.array[source.used].size, length_inner);

      for (i = 0; i < length_inner; ++i) {

        status = f_string_dynamic_append(test_names[i], &source.array[source.used].array[i]);

        assert_int_equal(status, F_none);
        assert_string_equal(source.array[source.used].array[i].string, test_names[i].string);
        assert_int_equal(source.array[source.used].array[i].used, test_names[i].used);
      } // for

      source.array[source.used].used = length_inner;
    } // for
  }

  {
    const f_status_t status = f_string_dynamicss_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    for (f_array_length_t j = 0; j < length_outer; ++j) {

      for (f_array_length_t i = 0; i < length_inner; ++i) {

        assert_int_equal(destination.array[j].array[i].used, test_names[i].used);

        assert_string_equal(destination.array[j].array[i].string, test_names[i].string);
      } // for
    } // for
  }

  for (f_array_length_t j = 0; j < source.used; ++j) {

    for (f_array_length_t i = 0; i < source.array[j].used; ++i) {
      free((void *) source.array[j].array[i].string);
    } // for

    free((void *) source.array[j].array);
  } // for

  for (f_array_length_t j = 0; j < destination.used; ++j) {

    for (f_array_length_t i = 0; i < destination.array[j].used; ++i) {
      free((void *) destination.array[j].array[i].string);
    } // for

    free((void *) destination.array[j].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_string_dynamicss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_string_dynamicss_t source = f_string_dynamicss_t_initialize;
  f_string_dynamicss_t destination = f_string_dynamicss_t_initialize;

  {
    const f_status_t status = f_string_dynamicss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_dynamicss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_dynamicss_append_all__parameter_checking(void **state) {

  const f_string_dynamicss_t data = f_string_dynamicss_t_initialize;

  {
    const f_status_t status = f_string_dynamicss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

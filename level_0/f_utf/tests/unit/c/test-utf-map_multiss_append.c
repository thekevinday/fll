#include "test-utf.h"
#include "test-utf-map_multiss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_map_multiss_append__works(void **state) {

  const int length_values = 2;
  const int length_inner = 2;
  f_utf_string_map_multis_t source = f_utf_string_map_multis_t_initialize;
  f_utf_string_map_multiss_t destination = f_utf_string_map_multiss_t_initialize;

  f_utf_string_static_t test_value_array1[] = {
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\01\0\0\0", 0, 11),
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\02\0\0\0", 0, 11),
  };

  f_utf_string_static_t test_value_array2[] = {
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\03\0\0\0", 0, 11),
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\04\0\0\0", 0, 11),
  };

  const f_utf_string_static_t test_names[] = {
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0n\0\0\0a\0\0\0m\0\0\0e\0\0\01\0\0\0", 0, 10),
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0n\0\0\0a\0\0\0m\0\0\0e\0\0\02\0\0\0", 0, 10),
  };

  const f_utf_string_statics_t test_values[] = {
    macro_f_utf_string_statics_t_initialize(test_value_array1, 0, length_values),
    macro_f_utf_string_statics_t_initialize(test_value_array2, 0, length_values),
  };

  {
    f_status_t status = f_utf_string_map_multis_resize(length_inner, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_utf_string_dynamic_append(test_names[source.used], &source.array[source.used].name);

      assert_int_equal(status, F_none);
      assert_string_equal(source.array[source.used].name.string, test_names[source.used].string);
      assert_int_equal(source.array[source.used].name.used, test_names[source.used].used);

      status = f_utf_string_dynamics_append_all(test_values[source.used], &source.array[source.used].value);

      assert_int_equal(status, F_none);
      assert_int_equal(source.array[source.used].value.used, test_values[source.used].used);
      assert_int_equal(source.array[source.used].value.array[0].used, test_values[source.used].array[0].used);
      assert_int_equal(source.array[source.used].value.array[1].used, test_values[source.used].array[1].used);

      assert_string_equal(source.array[source.used].value.array[0].string, test_values[source.used].array[0].string);
      assert_string_equal(source.array[source.used].value.array[1].string, test_values[source.used].array[1].string);
    } // for
  }

  {
    const f_status_t status = f_utf_string_map_multiss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.array[0].used, length_inner);

    for (f_array_length_t i = 0; i < length_inner; ++i) {

      assert_int_equal(destination.array[0].array[i].name.used, test_names[i].used);
      assert_int_equal(destination.array[0].array[i].value.used, test_values[i].used);
      assert_int_equal(destination.array[0].array[i].value.array[0].used, test_values[i].array[0].used);
      assert_int_equal(destination.array[0].array[i].value.array[1].used, test_values[i].array[1].used);

      assert_string_equal(destination.array[0].array[i].name.string, test_names[i].string);
      assert_string_equal(destination.array[0].array[i].value.array[0].string, test_values[i].array[0].string);
      assert_string_equal(destination.array[0].array[i].value.array[1].string, test_values[i].array[1].string);
    } // for
  }

  for (f_array_length_t i = 0; i < source.used; ++i) {

    free((void *) source.array[i].name.string);
    free((void *) source.array[i].value.array[0].string);
    free((void *) source.array[i].value.array[1].string);
    free((void *) source.array[i].value.array);
  } // for


  for (f_array_length_t i = 0; i < destination.array[0].used; ++i) {

    free((void *) destination.array[0].array[i].name.string);
    free((void *) destination.array[0].array[i].value.array[0].string);
    free((void *) destination.array[0].array[i].value.array[1].string);
    free((void *) destination.array[0].array[i].value.array);
  } // for

  free((void *) source.array);
  free((void *) destination.array[0].array);
  free((void *) destination.array);
}

void test__f_utf_map_multiss_append__returns_data_not(void **state) {

  const int length = 5;
  f_utf_string_map_multis_t source = f_utf_string_map_multiss_t_initialize;
  f_utf_string_map_multiss_t destination = f_utf_string_map_multiss_t_initialize;

  {
    const f_status_t status = f_utf_string_map_multis_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_utf_string_map_multiss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_utf_map_multiss_append__parameter_checking(void **state) {

  f_utf_string_map_multis_t data = f_utf_string_map_multis_t_initialize;

  {
    const f_status_t status = f_utf_string_map_multiss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

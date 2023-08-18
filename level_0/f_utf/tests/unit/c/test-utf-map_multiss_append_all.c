#include "test-utf.h"
#include "test-utf-map_multiss_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_map_multiss_append_all__works(void **state) {

  const int length_values = 2;
  const int length_inner = 2;
  const int length_outer = 2;
  f_utf_string_map_multiss_t source = f_utf_string_map_multiss_t_initialize;
  f_utf_string_map_multiss_t destination = f_utf_string_map_multiss_t_initialize;

  f_utf_string_static_t test_value_array1[] = {
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\01\0\0\0", 0, 11),
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\02\0\0\0", 0, 11),
  };

  f_utf_string_static_t test_value_array2[] = {
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\03\0\0\0", 0, 11),
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\04\0\0\0", 0, 11),
  };

  const f_utf_string_static_t test_names[] = {
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0n\0\0\0a\0\0\0m\0\0\0e\0\0\01\0\0\0", 0, 10),
    macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0n\0\0\0a\0\0\0m\0\0\0e\0\0\02\0\0\0", 0, 10),
  };

  const f_utf_string_statics_t test_values[] = {
    macro_f_utf_string_statics_t_initialize_1(test_value_array1, 0, length_values),
    macro_f_utf_string_statics_t_initialize_1(test_value_array2, 0, length_values),
  };

  {
    f_status_t status = f_utf_string_map_multiss_resize(length_outer, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length_outer);

    f_number_unsigned_t i = 0;

    for (; source.used < length_outer; ++source.used) {

      status = f_utf_string_map_multis_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[source.used].used, 0);
      assert_int_equal(source.array[source.used].size, length_inner);

      for (i = 0; i < length_inner; ++i) {

        status = f_utf_string_dynamic_append(test_names[i], &source.array[source.used].array[i].name);

        assert_int_equal(status, F_okay);
        assert_int_equal(source.array[source.used].array[i].name.used, test_names[i].used);
        assert_string_equal(source.array[source.used].array[i].name.string, test_names[i].string);

        status = f_utf_string_dynamics_append_all(test_values[i], &source.array[source.used].array[i].value);

        assert_int_equal(status, F_okay);
        assert_int_equal(source.array[source.used].array[i].value.used, test_values[i].used);
        assert_int_equal(source.array[source.used].array[i].value.array[0].used, test_values[i].array[0].used);
        assert_int_equal(source.array[source.used].array[i].value.array[1].used, test_values[i].array[1].used);

        assert_string_equal(source.array[source.used].array[i].value.array[0].string, test_values[i].array[0].string);
        assert_string_equal(source.array[source.used].array[i].value.array[1].string, test_values[i].array[1].string);
      } // for

      source.array[source.used].used = length_inner;
    } // for
  }

  {
    const f_status_t status = f_utf_string_map_multiss_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);

    for (f_number_unsigned_t j = 0; j < length_outer; ++j) {

      for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

        assert_int_equal(destination.array[j].array[i].name.used, test_names[i].used);
        assert_int_equal(destination.array[j].array[i].value.used, test_values[i].used);
        assert_int_equal(destination.array[j].array[i].value.array[0].used, test_values[i].array[0].used);
        assert_int_equal(destination.array[j].array[i].value.array[1].used, test_values[i].array[1].used);

        assert_string_equal(destination.array[j].array[i].name.string, test_names[i].string);
        assert_string_equal(destination.array[j].array[i].value.array[0].string, test_values[i].array[0].string);
        assert_string_equal(destination.array[j].array[i].value.array[1].string, test_values[i].array[1].string);
      } // for
    } // for
  }

  for (f_number_unsigned_t j = 0; j < source.used; ++j) {

    for (f_number_unsigned_t i = 0; i < source.array[j].used; ++i) {

      free((void *) source.array[j].array[i].name.string);
      free((void *) source.array[j].array[i].value.array[0].string);
      free((void *) source.array[j].array[i].value.array[1].string);
      free((void *) source.array[j].array[i].value.array);
    } // for

    free((void *) source.array[j].array);
  } // for

  for (f_number_unsigned_t j = 0; j < destination.used; ++j) {

    for (f_number_unsigned_t i = 0; i < destination.array[j].used; ++i) {

      free((void *) destination.array[j].array[i].name.string);
      free((void *) destination.array[j].array[i].value.array[0].string);
      free((void *) destination.array[j].array[i].value.array[1].string);
      free((void *) destination.array[j].array[i].value.array);
    } // for

    free((void *) destination.array[j].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_utf_map_multiss_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_utf_string_map_multiss_t source = f_utf_string_map_multiss_t_initialize;
  f_utf_string_map_multiss_t destination = f_utf_string_map_multiss_t_initialize;

  {
    const f_status_t status = f_utf_string_map_multiss_resize(length, &source);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_utf_string_map_multiss_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_utf_map_multiss_append_all__parameter_checking(void **state) {

  const f_utf_string_map_multiss_t data = f_utf_string_map_multiss_t_initialize;

  {
    const f_status_t status = f_utf_string_map_multiss_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

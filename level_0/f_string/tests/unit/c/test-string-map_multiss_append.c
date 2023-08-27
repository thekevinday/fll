#include "test-string.h"
#include "test-string-map_multiss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_map_multiss_append__works(void **state) {

  const int length_values = 2;
  const int length_inner = 2;
  f_string_map_multis_t source = f_string_map_multis_t_initialize;
  f_string_map_multiss_t destination = f_string_map_multiss_t_initialize;

  f_string_static_t test_value_array1[] = {
    macro_f_string_static_t_initialize_1("test_value1", 0, 11),
    macro_f_string_static_t_initialize_1("test_value2", 0, 11),
  };

  f_string_static_t test_value_array2[] = {
    macro_f_string_static_t_initialize_1("test_value3", 0, 11),
    macro_f_string_static_t_initialize_1("test_value4", 0, 11),
  };

  const f_string_static_t test_names[] = {
    macro_f_string_static_t_initialize_1("test_name1", 0, 10),
    macro_f_string_static_t_initialize_1("test_name2", 0, 10),
  };

  const f_string_statics_t test_values[] = {
    macro_f_string_statics_t_initialize_1(test_value_array1, 0, length_values),
    macro_f_string_statics_t_initialize_1(test_value_array2, 0, length_values),
  };

  {
    f_status_t status = f_memory_arrays_resize(length_inner, sizeof(f_string_map_multi_t), (void **) &source.array, &source.used, &source.size, &f_string_map_multis_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_string_dynamic_append(test_names[source.used], &source.array[source.used].name);

      assert_int_equal(status, F_okay);
      assert_string_equal(source.array[source.used].name.string, test_names[source.used].string);
      assert_int_equal(source.array[source.used].name.used, test_names[source.used].used);

      status = f_string_dynamics_append_all(test_values[source.used], &source.array[source.used].value);

      assert_int_equal(status, F_okay);
      assert_int_equal(source.array[source.used].value.used, test_values[source.used].used);
      assert_int_equal(source.array[source.used].value.array[0].used, test_values[source.used].array[0].used);
      assert_int_equal(source.array[source.used].value.array[1].used, test_values[source.used].array[1].used);

      assert_string_equal(source.array[source.used].value.array[0].string, test_values[source.used].array[0].string);
      assert_string_equal(source.array[source.used].value.array[1].string, test_values[source.used].array[1].string);
    } // for
  }

  {
    const f_status_t status = f_string_map_multiss_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.array[0].used, length_inner);

    for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

      assert_int_equal(destination.array[0].array[i].name.used, test_names[i].used);
      assert_int_equal(destination.array[0].array[i].value.used, test_values[i].used);
      assert_int_equal(destination.array[0].array[i].value.array[0].used, test_values[i].array[0].used);
      assert_int_equal(destination.array[0].array[i].value.array[1].used, test_values[i].array[1].used);

      assert_string_equal(destination.array[0].array[i].name.string, test_names[i].string);
      assert_string_equal(destination.array[0].array[i].value.array[0].string, test_values[i].array[0].string);
      assert_string_equal(destination.array[0].array[i].value.array[1].string, test_values[i].array[1].string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {

    free((void *) source.array[i].name.string);
    free((void *) source.array[i].value.array[0].string);
    free((void *) source.array[i].value.array[1].string);
    free((void *) source.array[i].value.array);
  } // for


  for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

    free((void *) destination.array[0].array[i].name.string);
    free((void *) destination.array[0].array[i].value.array[0].string);
    free((void *) destination.array[0].array[i].value.array[1].string);
    free((void *) destination.array[0].array[i].value.array);
  } // for

  free((void *) source.array);
  free((void *) destination.array[0].array);
  free((void *) destination.array);
}

void test__f_string_map_multiss_append__returns_data_not(void **state) {

  const int length = 5;
  f_string_map_multis_t source = f_string_map_multiss_t_initialize;
  f_string_map_multiss_t destination = f_string_map_multiss_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_string_map_multi_t), (void **) &source.array, &source.used, &source.size, &f_string_map_multis_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_map_multiss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_map_multiss_append__parameter_checking(void **state) {

  f_string_map_multis_t data = f_string_map_multis_t_initialize;

  {
    const f_status_t status = f_string_map_multiss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

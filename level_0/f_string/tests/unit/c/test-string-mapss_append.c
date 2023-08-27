#include "test-string.h"
#include "test-string-mapss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_mapss_append__works(void **state) {

  const int length_inner = 2;
  f_string_maps_t source = f_string_maps_t_initialize;
  f_string_mapss_t destination = f_string_mapss_t_initialize;

  const f_string_static_t test_names[] = {
    macro_f_string_static_t_initialize_1("test_name1", 0, 10),
    macro_f_string_static_t_initialize_1("test_name2", 0, 10),
  };

  const f_string_static_t test_values[] = {
    macro_f_string_static_t_initialize_1("test_value1", 0, 11),
    macro_f_string_static_t_initialize_1("test_value2", 0, 11),
  };

  {
    f_status_t status = f_memory_arrays_resize(length_inner, sizeof(f_string_map_t), (void **) &source.array, &source.used, &source.size, &f_string_maps_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_string_dynamic_append(test_names[source.used], &source.array[source.used].name);

      assert_int_equal(status, F_okay);
      assert_string_equal(source.array[source.used].name.string, test_names[source.used].string);
      assert_int_equal(source.array[source.used].name.used, test_names[source.used].used);

      status = f_string_dynamic_append(test_values[source.used], &source.array[source.used].value);

      assert_int_equal(status, F_okay);
      assert_string_equal(source.array[source.used].value.string, test_values[source.used].string);
      assert_int_equal(source.array[source.used].value.used, test_values[source.used].used);
    } // for
  }

  {
    const f_status_t status = f_string_mapss_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.array[0].used, length_inner);

    for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

      assert_int_equal(destination.array[0].array[i].name.used, test_names[i].used);
      assert_int_equal(destination.array[0].array[i].value.used, test_values[i].used);

      assert_string_equal(destination.array[0].array[i].name.string, test_names[i].string);
      assert_string_equal(destination.array[0].array[i].value.string, test_values[i].string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {

    free((void *) source.array[i].name.string);
    free((void *) source.array[i].value.string);
  } // for


  for (f_number_unsigned_t i = 0; i < destination.array[0].used; ++i) {

    free((void *) destination.array[0].array[i].name.string);
    free((void *) destination.array[0].array[i].value.string);
  } // for

  free((void *) destination.array[0].array);

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_string_mapss_append__returns_data_not(void **state) {

  const int length = 5;
  f_string_maps_t source = f_string_mapss_t_initialize;
  f_string_mapss_t destination = f_string_mapss_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_string_map_t), (void **) &source.array, &source.used, &source.size, &f_string_maps_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_mapss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_mapss_append__parameter_checking(void **state) {

  f_string_maps_t data = f_string_maps_t_initialize;

  {
    const f_status_t status = f_string_mapss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

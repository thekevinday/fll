#include "test-string.h"
#include "test-string-maps_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_maps_append_all__works(void **state) {

  const int length_inner = 2;
  f_string_maps_t source = f_string_maps_t_initialize;
  f_string_maps_t destination = f_string_maps_t_initialize;

  const f_string_static_t test_key = macro_f_string_static_t_initialize_1("test_key", 0, 8);
  const f_string_static_t test_value = macro_f_string_static_t_initialize_1("test_value", 0, 10);

  {
    f_status_t status = f_memory_arrays_resize(length_inner, sizeof(f_string_map_t), (void **) &source.array, &source.used, &source.size, &f_string_maps_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.size, length_inner);

    for (; source.used < length_inner; ++source.used) {

      status = f_string_dynamic_append(test_key, &source.array[source.used].key);

      assert_int_equal(status, F_okay);
      assert_string_equal(source.array[source.used].key.string, test_key.string);
      assert_int_equal(source.array[source.used].key.used, test_key.used);

      status = f_string_dynamic_append(test_value, &source.array[source.used].value);

      assert_int_equal(status, F_okay);
      assert_string_equal(source.array[source.used].value.string, test_value.string);
      assert_int_equal(source.array[source.used].value.used, test_value.used);
    } // for
  }

  {
    const f_status_t status = f_string_maps_append_all(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_number_unsigned_t i = 0; i < length_inner; ++i) {

      assert_int_equal(destination.array[i].key.used, source.array[i].key.used);
      assert_int_equal(destination.array[i].value.used, source.array[i].value.used);

      assert_string_equal(destination.array[i].key.string, source.array[i].key.string);
      assert_string_equal(destination.array[i].value.string, source.array[i].value.string);
    } // for
  }

  for (f_number_unsigned_t i = 0; i < source.used; ++i) {

    free((void *) source.array[i].key.string);
    free((void *) source.array[i].value.string);
  } // for

  for (f_number_unsigned_t i = 0; i < destination.used; ++i) {

    free((void *) destination.array[i].key.string);
    free((void *) destination.array[i].value.string);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_string_maps_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_string_maps_t source = f_string_maps_t_initialize;
  f_string_maps_t destination = f_string_maps_t_initialize;

  {
    const f_status_t status = f_memory_arrays_resize(length, sizeof(f_string_map_t), (void **) &source.array, &source.used, &source.size, &f_string_maps_delete_callback);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_string_maps_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_string_maps_append_all__parameter_checking(void **state) {

  const f_string_maps_t data = f_string_maps_t_initialize;

  {
    const f_status_t status = f_string_maps_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

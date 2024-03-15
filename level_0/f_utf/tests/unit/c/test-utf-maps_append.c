#include "test-utf.h"
#include "test-utf-maps_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_maps_append__works(void **state) {

  f_utf_string_map_t source = f_utf_string_map_t_initialize;
  f_utf_string_maps_t destination = f_utf_string_maps_t_initialize;

  const f_utf_string_static_t test_key = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0n\0\0\0a\0\0\0m\0\0\0e", 0, 9);
  const f_utf_string_static_t test_value = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e", 0, 10);

  {
    f_status_t status = f_utf_string_dynamic_append(test_key, &source.key);

    assert_int_equal(status, F_okay);
    assert_string_equal(source.key.string, test_key.string);
    assert_int_equal(source.key.used, test_key.used);

    status = f_utf_string_dynamic_append(test_value, &source.value);

    assert_int_equal(status, F_okay);
    assert_string_equal(source.value.string, test_value.string);
    assert_int_equal(source.value.used, test_value.used);
  }

  {
    const f_status_t status = f_utf_string_maps_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].key.used, source.key.used);
    assert_int_equal(destination.array[0].value.used, source.value.used);
    assert_string_equal(destination.array[0].key.string, source.key.string);
    assert_string_equal(destination.array[0].value.string, source.value.string);
  }

  free((void *) source.key.string);
  free((void *) source.value.string);

  free((void *) destination.array[0].key.string);
  free((void *) destination.array[0].value.string);

  free((void *) destination.array);
}

void test__f_utf_string_maps_append__parameter_checking(void **state) {

  const f_utf_string_map_t data = f_utf_string_map_t_initialize;

  {
    const f_status_t status = f_utf_string_maps_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

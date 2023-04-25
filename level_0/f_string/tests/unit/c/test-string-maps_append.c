#include "test-string.h"
#include "test-string-maps_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_maps_append__works(void **state) {

  f_string_map_t source = f_string_map_t_initialize;
  f_string_maps_t destination = f_string_maps_t_initialize;

  const f_string_static_t test_name = macro_f_string_static_t_initialize_1("test_name", 0, 9);
  const f_string_static_t test_value = macro_f_string_static_t_initialize_1("test_value", 0, 10);

  {
    f_status_t status = f_string_dynamic_append(test_name, &source.name);

    assert_int_equal(status, F_none);
    assert_string_equal(source.name.string, test_name.string);
    assert_int_equal(source.name.used, test_name.used);

    status = f_string_dynamic_append(test_value, &source.value);

    assert_int_equal(status, F_none);
    assert_string_equal(source.value.string, test_value.string);
    assert_int_equal(source.value.used, test_value.used);
  }

  {
    const f_status_t status = f_string_maps_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].name.used, source.name.used);
    assert_int_equal(destination.array[0].value.used, source.value.used);
    assert_string_equal(destination.array[0].name.string, source.name.string);
    assert_string_equal(destination.array[0].value.string, source.value.string);
  }

  free((void *) source.name.string);
  free((void *) source.value.string);

  free((void *) destination.array[0].name.string);
  free((void *) destination.array[0].value.string);

  free((void *) destination.array);
}

void test__f_string_maps_append__parameter_checking(void **state) {

  const f_string_map_t data = f_string_map_t_initialize;

  {
    const f_status_t status = f_string_maps_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

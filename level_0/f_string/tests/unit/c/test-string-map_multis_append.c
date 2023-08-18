#include "test-string.h"
#include "test-string-map_multis_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_map_multis_append__works(void **state) {

  const int length_values = 2;
  f_string_map_multi_t source = f_string_map_multi_t_initialize;
  f_string_map_multis_t destination = f_string_map_multis_t_initialize;

  f_string_static_t test_value_array[] = {
    macro_f_string_static_t_initialize_1("test_value1", 0, 11),
    macro_f_string_static_t_initialize_1("test_value2", 0, 11),
  };

  const f_string_static_t test_name = macro_f_string_static_t_initialize_1("test_name", 0, 9);
  const f_string_statics_t test_value = macro_f_string_statics_t_initialize_1(test_value_array, 0, length_values);

  {
    f_status_t status = f_string_dynamic_append(test_name, &source.name);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.name.used, test_name.used);
    assert_string_equal(source.name.string, test_name.string);

    status = f_string_dynamics_append_all(test_value, &source.value);

    assert_int_equal(status, F_okay);
    assert_int_equal(source.value.used, test_value.used);
    assert_int_equal(source.value.array[0].used, test_value.array[0].used);
    assert_int_equal(source.value.array[1].used, test_value.array[1].used);

    assert_string_equal(source.value.array[0].string, test_value.array[0].string);
    assert_string_equal(source.value.array[1].string, test_value.array[1].string);
  }

  {
    const f_status_t status = f_string_map_multis_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].name.used, source.name.used);
    assert_int_equal(destination.array[0].value.used, source.value.used);
    assert_int_equal(destination.array[0].value.array[0].used, source.value.array[0].used);
    assert_int_equal(destination.array[0].value.array[1].used, source.value.array[1].used);

    assert_string_equal(destination.array[0].name.string, source.name.string);
    assert_string_equal(destination.array[0].value.array[0].string, source.value.array[0].string);
    assert_string_equal(destination.array[0].value.array[1].string, source.value.array[1].string);
  }

  free((void *) source.name.string);
  free((void *) source.value.array[0].string);
  free((void *) source.value.array[1].string);
  free((void *) source.value.array);

  free((void *) destination.array[0].name.string);
  free((void *) destination.array[0].value.array[0].string);
  free((void *) destination.array[0].value.array[1].string);
  free((void *) destination.array[0].value.array);

  free((void *) destination.array);
}

void test__f_string_map_multis_append__parameter_checking(void **state) {

  const f_string_map_multi_t data = f_string_map_multi_t_initialize;

  {
    const f_status_t status = f_string_map_multis_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

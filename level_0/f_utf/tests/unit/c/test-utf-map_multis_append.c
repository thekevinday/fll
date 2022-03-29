#include "test-utf.h"
#include "test-utf-map_multis_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_map_multis_append__works(void **state) {

  const int length_values = 2;
  f_utf_string_map_multi_t source = f_utf_string_map_multi_t_initialize;
  f_utf_string_map_multis_t destination = f_utf_string_map_multis_t_initialize;

  f_utf_string_static_t test_value_array[] = {
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\01\0\0\0", 0, 11),
    macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0v\0\0\0a\0\0\0l\0\0\0u\0\0\0e\0\0\02\0\0\0", 0, 11),
  };

  const f_utf_string_static_t test_name = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0_\0\0\0n\0\0\0a\0\0\0m\0\0\0e\0\0\0", 0, 9);
  const f_utf_string_statics_t test_value = macro_f_utf_string_statics_t_initialize(test_value_array, 0, length_values);

  {
    f_status_t status = f_utf_string_dynamic_append(test_name, &source.name);

    assert_int_equal(status, F_none);
    assert_int_equal(source.name.used, test_name.used);

    for (f_array_length_t i = 0; i < source.name.used; ++i) {
      assert_int_equal(source.name.string[i], test_name.string[i]);
    } // for

    status = f_utf_string_dynamics_append_all(test_value, &source.value);

    assert_int_equal(status, F_none);
    assert_int_equal(source.value.used, test_value.used);
    assert_int_equal(source.value.array[0].used, test_value.array[0].used);
    assert_int_equal(source.value.array[1].used, test_value.array[1].used);

    for (f_array_length_t i = 0; i < source.value.array[0].used; ++i) {
      assert_int_equal(source.value.array[0].string[i], test_value.array[0].string[i]);
    } // for

    for (f_array_length_t i = 0; i < source.value.array[1].used; ++i) {
      assert_int_equal(source.value.array[1].string[i], test_value.array[1].string[i]);
    } // for
  }

  {
    const f_status_t status = f_utf_string_map_multis_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].name.used, source.name.used);
    assert_int_equal(destination.array[0].value.used, source.value.used);
    assert_int_equal(destination.array[0].value.array[0].used, source.value.array[0].used);
    assert_int_equal(destination.array[0].value.array[1].used, source.value.array[1].used);

    assert_string_equal(destination.array[0].name.string, source.name.string);
    assert_string_equal(destination.array[0].value.array[0].string, source.value.array[0].string);
    assert_string_equal(destination.array[0].value.array[1].string, source.value.array[1].string);

    for (f_array_length_t j = 0; j < destination.array[0].name.used; ++j) {
      assert_int_equal(destination.array[0].name.string[j], source.name.string[j]);
    } // for

    for (f_array_length_t j = 0; j < destination.array[0].value.array[0].used; ++j) {
      assert_int_equal(destination.array[0].value.array[0].string[j], source.value.array[0].string[j]);
    } // for

    for (f_array_length_t j = 0; j < destination.array[0].value.array[1].used; ++j) {
      assert_int_equal(destination.array[0].value.array[1].string[j], source.value.array[1].string[j]);
    } // for
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

void test__f_utf_map_multis_append__parameter_checking(void **state) {

  const f_utf_string_map_multi_t data = f_utf_string_map_multi_t_initialize;

  {
    const f_status_t status = f_utf_string_map_multis_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

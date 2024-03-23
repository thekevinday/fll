#include "test-utf.h"
#include "test-utf-map_multis_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_map_multis_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_utf_char_t key_string[] = { 'n', 0 };
  f_utf_char_t value_string[] = { 'v', 0 };

  f_utf_string_dynamic_t key = { .string = key_string, .used = 0, .size = 1 };
  f_utf_string_dynamic_t value = { .string = value_string, .used = 0, .size = 1 };
  f_utf_string_dynamic_t value_array[] = { value };
  f_utf_string_dynamics_t values = { .array = value_array, .used = 0, .size = 1 };

  f_utf_string_map_multi_t data = { .key = key, .value = values };
  f_utf_string_map_multi_t data_array[] = { data };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_utf_string_map_multis_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].key.size = 1;
  data_array[0].value.size = 1;
  data_array[0].value.array[0].size = 1;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_utf_string_map_multis_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].key.size = 1;
  data_array[0].value.size = 1;
  data_array[0].value.array[0].size = 1;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_utf_string_map_multis_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_utf_string_map_multis_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_utf_string_map_multis_t datas = f_utf_string_map_multis_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_utf_string_map_multi_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].key.string, &datas.array[0].key.used, &datas.array[0].key.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_utf_string_dynamic_t), (void **) &datas.array[0].value.array, &datas.array[0].value.used, &datas.array[0].value.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].value.array[0].string, &datas.array[0].value.array[0].used, &datas.array[0].value.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_utf_string_map_multis_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].key.size, 0);
    assert_int_equal(datas.array[0].value.size, 0);
  }

  free((void *) datas.array[0].key.string);
  free((void *) datas.array[0].value.array);
  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
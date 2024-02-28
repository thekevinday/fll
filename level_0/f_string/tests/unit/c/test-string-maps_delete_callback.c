#include "test-string.h"
#include "test-string-maps_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_maps_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_dynamic_t key = { .string = "key", .used = 0, .size = 1 };
  f_string_dynamic_t value = { .string = "value", .used = 0, .size = 1 };
  f_string_map_t data = { .key = key, .value = value };
  f_string_map_t data_array[] = { data };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_string_maps_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].key.size = 1;
  data_array[0].value.size = 1;

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_string_maps_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_string_maps_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_string_maps_t datas = f_string_maps_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_string_map_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].key.string, &datas.array[0].key.used, &datas.array[0].key.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_char_t), (void **) &datas.array[0].value.string, &datas.array[0].value.used, &datas.array[0].value.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_string_maps_delete_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].key.size, 0);
    assert_int_equal(datas.array[0].value.size, 0);
  }

  free((void *) datas.array[0].key.string);
  free((void *) datas.array[0].value.string);
  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

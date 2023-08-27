#include "test-utf.h"
#include "test-utf-dynamics_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_dynamics_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_utf_string_dynamic_t data = { .string = "", .used = 0, .size = 1 };
  f_utf_string_dynamic_t data_array[] = { data };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_utf_string_dynamics_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_utf_string_dynamics_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_utf_string_dynamics_t datas = f_utf_string_dynamics_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_utf_string_dynamic_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_utf_string_dynamics_delete_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

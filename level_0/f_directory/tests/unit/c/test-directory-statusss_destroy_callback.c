#include "test-directory.h"
#include "test-directory-statusss_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_statusss_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_static_t base = macro_f_string_static_t_initialize_1(F_string_empty_s, 1, 0);

  f_directory_status_t data = { .path = base };
  f_directory_status_t data_array[] = { data };
  f_directory_statuss_t datas = { .array = data_array, .used = 0, .size = 1 };
  f_directory_statuss_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_statusss_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].path = base;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_statusss_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_statusss_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_statusss_t datass = f_directory_statusss_t_initialize;

  {
    f_status_t status = f_memory_array_adjust(length, sizeof(f_directory_statuss_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_adjust(1, sizeof(f_directory_status_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_adjust(1, sizeof(f_char_t), (void **) &datass.array[0].array[0].path.string, &datass.array[0].array[0].path.used, &datass.array[0].array[0].path.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_directory_statusss_destroy_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
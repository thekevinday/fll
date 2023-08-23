#include "test-directory.h"
#include "test-directory-statuss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_statuss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_directory_status_t data = f_directory_status_t_initialize;
  f_directory_status_t data_array[] = { data };
  f_directory_statuss_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_statuss_t datass_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_statuss_delete_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_statuss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_statuss_t datas = f_directory_statuss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_directory_status_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_directory_statuss_delete_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].path.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

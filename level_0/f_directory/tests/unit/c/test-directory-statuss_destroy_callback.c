#include "test-directory.h"
#include "test-directory-statuss_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_statuss_destroy_callback__fails(void **state) {

  mock_unwrap = 0;

  f_directory_status_t data = f_directory_status_t_initialize;
  f_directory_status_t data_array[] = { data };
  f_directory_statuss_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_statuss_t datass_array[] = { datas };

  {
    will_return(__wrap_f_string_dynamic_adjust, true);
    will_return(__wrap_f_string_dynamic_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_statuss_destroy_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_statuss_destroy_callback__works(void **state) {

  mock_unwrap = 0;

  f_directory_status_t data = f_directory_status_t_initialize;
  f_directory_status_t data_array[] = { data };
  f_directory_statuss_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_statuss_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_string_dynamic_adjust, false);
    will_return(__wrap_f_string_dynamic_adjust, F_none);

    const f_status_t status = f_directory_statuss_destroy_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

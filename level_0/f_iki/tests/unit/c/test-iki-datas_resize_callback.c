#include "test-iki.h"
#include "test-iki-datas_resize_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_iki_datas_resize_callback__fails(void **state) {

  mock_unwrap = 0;

  f_iki_data_t data = f_iki_data_t_initialize;
  f_iki_data_t data_array[] = { data };
  f_iki_datas_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_iki_datas_t datass_array[] = { datas };

  {
    will_return(__wrap_f_string_ranges_resize, true);
    will_return(__wrap_f_string_ranges_resize, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_resize_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_resize_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_none);

    will_return(__wrap_f_string_ranges_resize, true);
    will_return(__wrap_f_string_ranges_resize, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_resize_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_none);

    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_string_ranges_resize, true);
    will_return(__wrap_f_string_ranges_resize, F_status_set_error(F_failure));

    const f_status_t status = f_iki_datas_resize_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_iki_datas_resize_callback__works(void **state) {

  mock_unwrap = 0;

  f_iki_data_t data = f_iki_data_t_initialize;
  f_iki_data_t data_array[] = { data };
  f_iki_datas_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_iki_datas_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_none);

    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    const f_status_t status = f_iki_datas_resize_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

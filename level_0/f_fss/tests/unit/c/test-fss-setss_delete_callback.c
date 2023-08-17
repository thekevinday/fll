#include "test-fss.h"
#include "test-fss-setss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_setss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_set_t data = f_fss_set_t_initialize;
  f_fss_set_t data_array[] = { data };
  f_fss_sets_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_fss_sets_t datas_array[] = { datas };

  {
    will_return(__wrap_f_string_ranges_resize, true);
    will_return(__wrap_f_string_ranges_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_setss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_none);

    will_return(__wrap_f_string_rangess_resize, true);
    will_return(__wrap_f_string_rangess_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_setss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_setss_delete_callback__works(void **state) {

  mock_unwrap = 1;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_setss_t datass = f_fss_setss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_fss_sets_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_none);

    status = f_memory_array_resize(1, sizeof(f_fss_set_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_none);

    status = f_string_ranges_resize(1, &datass.array[0].array[0].objects);
    assert_int_equal(status, F_none);

    status = f_string_rangess_resize(1, &datass.array[0].array[0].contents);
    assert_int_equal(status, F_none);
  }

  {
    const f_status_t status = f_fss_setss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_none);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

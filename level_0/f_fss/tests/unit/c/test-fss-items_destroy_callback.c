#include "test-fss.h"
#include "test-fss-items_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_items_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_range_t base = macro_f_range_t_initialize_1(1, 0);
  f_range_t base_array[] = { base };
  f_ranges_t bases = { .array = base_array, .used = 0, .size = 1 };

  f_fss_item_t data = { .content = bases };
  f_fss_item_t data_array[] = { data };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_items_destroy_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_items_destroy_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_items_t datas = f_fss_items_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_fss_item_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_range_t), (void **) &datas.array[0].content.array, &datas.array[0].content.used, &datas.array[0].content.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_items_destroy_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].content.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

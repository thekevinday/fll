#include "test-fss.h"
#include "test-fss-nests_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_nests_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_item_t item = f_fss_item_t_initialize;
  f_fss_item_t item_array[] = { item };
  f_fss_items_t items = { .array = item_array, .used = 1, .size = 1 };
  f_fss_items_t items_array[] = { items };
  f_fss_nest_t data = { .depth = items_array, .used = 1, .size = 1 };
  f_fss_nest_t data_array[] = { data };

  {
    will_return(__wrap_f_string_ranges_resize, true);
    will_return(__wrap_f_string_ranges_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nests_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nests_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nests_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_nests_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_item_t item = f_fss_item_t_initialize;
  f_fss_item_t item_array[] = { item };
  f_fss_items_t items = { .array = item_array, .used = 1, .size = 1 };
  f_fss_items_t items_array[] = { items };
  f_fss_nest_t data = { .depth = items_array, .used = 1, .size = 1 };
  f_fss_nest_t data_array[] = { data };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_string_ranges_resize, false);
    will_return(__wrap_f_string_ranges_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    const f_status_t status = f_fss_nests_delete_callback(0, length, (void *) data_array);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

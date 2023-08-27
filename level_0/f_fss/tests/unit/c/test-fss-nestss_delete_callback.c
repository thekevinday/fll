#include "test-fss.h"
#include "test-fss-nestss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_nestss_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_item_t item = f_fss_item_t_initialize;
  f_fss_item_t item_array[] = { item };
  f_fss_items_t items = { .array = item_array, .used = 1, .size = 1 };
  f_fss_items_t items_array[] = { items };
  f_fss_nest_t data = { .depth = items_array, .used = 1, .size = 1 };
  f_fss_nest_t data_array[] = { data };
  f_fss_nests_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_fss_nests_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nestss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_resize, false);
    will_return(__wrap_f_memory_array_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nestss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_nestss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_nestss_t datass = f_fss_nestss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_fss_nests_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_fss_nest_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_fss_items_t), (void **) &datass.array[0].array[0].depth, &datass.array[0].array[0].used, &datass.array[0].array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_fss_item_t), (void **) &datass.array[0].array[0].depth[0].array, &datass.array[0].array[0].depth[0].used, &datass.array[0].array[0].depth[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_range_t), (void **) &datass.array[0].array[0].depth[0].array[0].content.array, &datass.array[0].array[0].depth[0].array[0].content.used, &datass.array[0].array[0].depth[0].array[0].content.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_nestss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

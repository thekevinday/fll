#include "test-fss.h"
#include "test-fss-nest_destroy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_nest_destroy__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_item_t item = f_fss_item_t_initialize;
  f_fss_item_t item_array[] = { item };
  f_fss_items_t items = { .array = item_array, .used = 0, .size = 1 };
  f_fss_items_t items_array[] = { items };
  f_fss_nest_t data = { .depth = items_array, .used = 0, .size = 1 };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nest_destroy(&data);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_okay);

    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_fss_nest_destroy(&data);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_nest_destroy__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_nest_destroy(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_nest_destroy__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_nest_t data = f_fss_nest_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_fss_items_t), (void **) &data.depth, &data.used, &data.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_fss_item_t), (void **) &data.depth[0].array, &data.depth[0].used, &data.depth[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_range_t), (void **) &data.depth[0].array[0].content.array, &data.depth[0].array[0].content.used, &data.depth[0].array[0].content.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_nest_destroy(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.size, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-fss.h"
#include "test-fss-item_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_item_delete__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_fss_item_t data = f_fss_item_t_initialize;

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_item_delete(&data);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_item_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_item_delete(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_item_delete__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_item_t data = f_fss_item_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(length, sizeof(f_string_range_t), (void **) &data.content.array, &data.content.used, &data.content.size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_item_delete(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.content.size, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

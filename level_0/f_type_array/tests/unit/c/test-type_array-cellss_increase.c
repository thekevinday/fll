#include "test-type_array.h"
#include "test-type_array-cellss_increase.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_cellss_increase__works(void **state) {

  const int length = 5;
  f_cellss_t data = f_cells_t_initialize;

  {
    const f_status_t status = f_type_cellss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    data.used = length;

    const f_status_t status = f_type_cellss_increase(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, length);
    assert_int_equal(data.size, length * 2);
  }

  free((void *) data.array);
}

void test__f_type_array_cellss_increase__returns_data_not(void **state) {

  const int length = 5;
  f_cellss_t data = f_cells_t_initialize;

  {
    const f_status_t status = f_type_cellss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_type_cellss_increase(length, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_type_array_cellss_increase__fails_on_invalid_parameter(void **state) {

  const int length = 5;
  f_cellss_t data = f_cells_t_initialize;

  {
    const f_status_t status = f_type_cellss_increase(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
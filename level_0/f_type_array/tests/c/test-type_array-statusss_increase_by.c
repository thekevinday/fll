#include "test-type_array.h"
#include "test-type_array-statusss_increase_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_statusss_increase_by__works(void **state) {

  const int length = 5;
  f_statusss_t data = f_statuss_t_initialize;

  {
    const f_status_t status = f_type_statusss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    data.used = length;

    const f_status_t status = f_type_statusss_increase_by(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, length);
    assert_int_equal(data.size, length * 2);
  }

  free((void *) data.array);
}

void test__f_type_array_statusss_increase_by__fails_on_invalid_parameter(void **state) {

  const int length = 5;
  f_statusss_t data = f_statuss_t_initialize;

  {
    const f_status_t status = f_type_statusss_increase_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
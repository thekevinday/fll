#include "test-type_array.h"
#include "test-type_array-pollss_increase_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_pollss_increase_by__parameter_checking(void **poll) {

  const int length = 5;
  f_pollss_t data = f_polls_t_initialize;

  {
    const f_status_t status = f_pollss_increase_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_type_array_pollss_increase_by__returns_data_not(void **poll) {

  const int length = 5;
  f_pollss_t data = f_pollss_t_initialize;

  {
    const f_status_t status = f_pollss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_pollss_increase_by(0, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_pollss_increase_by(length, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_type_array_pollss_increase_by__works(void **poll) {

  const int length = 5;
  f_pollss_t data = f_polls_t_initialize;

  {
    const f_status_t status = f_pollss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    data.used = length;

    const f_status_t status = f_pollss_increase_by(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, length);
    assert_int_equal(data.size, length * 2);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
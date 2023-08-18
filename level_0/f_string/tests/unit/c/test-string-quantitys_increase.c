#include "test-string.h"
#include "test-string-quantitys_increase.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_quantitys_increase__works(void **state) {

  const int length = 5;
  f_string_quantitys_t data = f_string_quantitys_t_initialize;

  {
    const f_status_t status = f_string_quantitys_resize(length, &data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    data.used = length;

    const f_status_t status = f_string_quantitys_increase(length, &data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, length);
    assert_in_range(data.size, length + 1, length + 1 + F_memory_default_allocation_small_d);
  }

  free((void *) data.array);
}

void test__f_string_quantitys_increase__returns_data_not(void **state) {

  const int length = 5;
  f_string_quantitys_t data = f_string_quantitys_t_initialize;

  {
    const f_status_t status = f_string_quantitys_resize(length, &data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_string_quantitys_increase(length, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_string_quantitys_increase__parameter_checking(void **state) {

  const int length = 5;
  f_string_quantitys_t data = f_string_quantitys_t_initialize;

  {
    const f_status_t status = f_string_quantitys_increase(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  free((void *) data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-type_array.h"
#include "test-type_array-array_lengths_decrease_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_array_lengths_decrease_by__parameter_checking(void **state) {

  const int length = 5;
  f_array_lengths_t data = f_array_lengths_t_initialize;

  {
    const f_status_t status = f_array_lengths_decrease_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_type_array_array_lengths_decrease_by__works(void **state) {

  const int length = 5;
  f_array_lengths_t data = f_array_lengths_t_initialize;

  {
    const f_status_t status = f_array_lengths_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_array_lengths_decrease_by(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

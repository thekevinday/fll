#include "test-type_array.h"
#include "test-type_array-int32s_decrease_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int32s_decrease_by__parameter_checking(void **state) {

  const int length = 5;
  f_int32s_t data = f_int32s_t_initialize;

  {
    const f_status_t status = f_int32s_decrease_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

void test__f_type_array_int32s_decrease_by__returns_data_not(void **state) {

  const int length = 5;
  f_int32s_t data = f_int32s_t_initialize;

  {
    const f_status_t status = f_int32s_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_int32s_decrease_by(0, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_type_array_int32s_decrease_by__works(void **state) {

  const int length = 5;
  f_int32s_t data = f_int32s_t_initialize;

  {
    const f_status_t status = f_int32s_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  {
    const f_status_t status = f_int32s_decrease_by(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

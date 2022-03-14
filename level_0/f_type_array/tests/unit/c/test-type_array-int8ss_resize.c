#include "test-type_array.h"
#include "test-type_array-int8ss_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_int8ss_resize__works(void **state) {

  const int length = 5;
  f_int8ss_t data = f_int8ss_t_initialize;

  {
    const f_status_t status = f_int8ss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_type_array_int8ss_resize__parameter_checking(void **state) {

  const int length = 5;
  f_int8ss_t data = f_int8ss_t_initialize;

  {
    const f_status_t status = f_int8ss_resize(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-type_array.h"
#include "test-type_array-uint16ss_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_uint16ss_resize__works(void **state) {

  const int length = 5;
  f_uint16ss_t data = f_uint16ss_t_initialize;

  {
    const f_status_t status = f_uint16ss_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_type_array_uint16ss_resize__fails_on_invalid_parameter(void **state) {

  const int length = 5;
  f_uint16ss_t data = f_uint16ss_t_initialize;

  {
    const f_status_t status = f_uint16ss_resize(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
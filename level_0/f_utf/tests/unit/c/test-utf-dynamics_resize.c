#include "test-utf.h"
#include "test-utf-dynamics_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_dynamics_resize__works(void **state) {

  const int length = 5;
  f_utf_string_dynamics_t data = f_utf_string_dynamics_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamics_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.array);
}

void test__f_utf_dynamics_resize__parameter_checking(void **state) {

  const int length = 5;
  f_utf_string_dynamics_t data = f_utf_string_dynamics_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamics_resize(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif

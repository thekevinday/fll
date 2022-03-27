#include "test-string.h"
#include "test-string-dynamics_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamics_append__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize("te\0st", 0, 5);
  f_string_dynamics_t destination = f_string_dynamics_t_initialize;

  {
    const f_status_t status = f_string_dynamics_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);

    assert_string_equal(destination.array[0].string, source.string);
    assert_string_equal(destination.array[0].string + 3, source.string + 3);
  }

  free((void *) destination.array[0].string);
  free((void *) destination.array);
}

void test__f_string_dynamics_append__parameter_checking(void **state) {

  const f_string_dynamic_t data = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamics_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

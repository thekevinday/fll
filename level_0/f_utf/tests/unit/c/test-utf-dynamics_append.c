#include "test-utf.h"
#include "test-utf-dynamics_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_dynamics_append__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 5);
  f_utf_string_dynamics_t destination = f_utf_string_dynamics_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamics_append(source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      assert_int_equal(destination.array[0].string[i], source.string[i]);
    } // for
  }

  free((void *) destination.array[0].string);
  free((void *) destination.array);
}

void test__f_utf_dynamics_append__parameter_checking(void **state) {

  const f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamics_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

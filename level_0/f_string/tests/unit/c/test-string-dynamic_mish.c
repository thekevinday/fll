#include "test-string.h"
#include "test-string-dynamic_mish.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_mish__works(void **state) {

  const f_string_static_t glue = macro_f_string_static_t_initialize_1(":", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\0st", 0, 5);
  const f_string_static_t expected = macro_f_string_static_t_initialize_1("te\0st:te\0st", 0, 11);
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_mish(glue, source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    assert_string_equal(destination.string, source.string);
    assert_string_equal(destination.string + 3, source.string + 3);
  }

  // Check that the glue is added.
  {
    const f_status_t status = f_string_dynamic_mish(glue, source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
    assert_string_equal(destination.string + 3, expected.string + 3);
    assert_string_equal(destination.string + 9, expected.string + 9);
  }

  free((void *) destination.string);
}

void test__f_string_dynamic_mish__parameter_checking(void **state) {

  const f_string_static_t glue = macro_f_string_static_t_initialize_1(":", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\0st", 0, 5);

  {
    const f_status_t status = f_string_dynamic_mish(glue, source, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

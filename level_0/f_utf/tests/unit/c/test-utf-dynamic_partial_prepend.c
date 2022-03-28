#include "test-utf.h"
#include "test-utf-dynamic_partial_prepend.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_dynamic_partial_prepend__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize("_te\0st_", 0, 7);
  const f_utf_string_static_t expected = macro_f_utf_string_static_t_initialize("te\0st", 0, 5);
  const f_string_range_t partial = macro_f_utf_string_range_t_initialize(1, 5);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_partial_prepend(source, partial, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
    assert_string_equal(destination.string + 3, expected.string + 3);
  }

  free((void *) destination.string);
}

void test__f_utf_dynamic_partial_prepend__parameter_checking(void **state) {

  const f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;
  const f_string_range_t partial = f_utf_string_range_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_partial_prepend(data, partial, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

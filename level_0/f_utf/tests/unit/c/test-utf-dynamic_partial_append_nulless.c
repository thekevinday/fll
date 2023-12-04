#include "test-utf.h"
#include "test-utf-dynamic_partial_append_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_dynamic_partial_append_nulless__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0_\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t\0\0\0_", 0, 7);
  const f_utf_string_static_t expected = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t", 0, 4);
  const f_range_t partial = macro_f_range_t_initialize_1(1, 5);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_partial_append_nulless(source, partial, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, expected.used);

    for (f_number_unsigned_t i = 0; i < expected.used; ++i) {
      assert_int_equal(destination.string[i], expected.string[i]);
    } // for
  }

  free((void *) destination.string);
}

void test__f_utf_string_dynamic_partial_append_nulless__parameter_checking(void **state) {

  const f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;
  const f_range_t partial = f_range_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_partial_append_nulless(data, partial, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-utf.h"
#include "test-utf-append_assure_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_append_assure_nulless__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t\0\0\0", 0, 5);
  const f_utf_string_static_t expected = macro_f_utf_string_static_t_initialize((f_utf_string_t) "t\0\0\0e\0\0\0s\0\0\0t\0\0\0", 0, 4);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_append_assure_nulless(source.string, source.used, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    for (f_array_length_t i = 0; i < expected.used; ++i) {
      assert_int_equal(destination.string[i], expected.string[i]);
    } // for
  }

  // The string already exists, so destination should be unchanged.
  {
    const f_status_t status = f_utf_string_append_assure_nulless(source.string, source.used, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    for (f_array_length_t i = 0; i < expected.used; ++i) {
      assert_int_equal(destination.string[i], expected.string[i]);
    } // for
  }

  free((void *) destination.string);
}

void test__f_utf_append_assure_nulless__parameter_checking(void **state) {

  const f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_append_assure_nulless(data.string, data.used, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

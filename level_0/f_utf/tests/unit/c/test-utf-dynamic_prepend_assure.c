#include "test-utf.h"
#include "test-utf-dynamic_prepend_assure.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_dynamic_prepend_assure__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 5);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_prepend_assure(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    for (f_array_length_t i = 0; i < source.used; ++i) {
      assert_int_equal(destination.string[i], source.string[i]);
    } // for
  }

  // The string already exists, so destination should be unchanged.
  {
    const f_status_t status = f_utf_string_dynamic_prepend_assure(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    for (f_array_length_t i = 0; i < source.used; ++i) {
      assert_int_equal(destination.string[i], source.string[i]);
    } // for
  }

  free((void *) destination.string);
}

void test__f_utf_dynamic_prepend_assure__parameter_checking(void **state) {

  const f_utf_string_dynamic_t data = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_prepend_assure(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

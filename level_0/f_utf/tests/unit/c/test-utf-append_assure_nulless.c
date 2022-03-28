#include "test-utf.h"
#include "test-utf-append_assure_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_append_assure_nulless__works(void **state) {

  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize("te\0st", 0, 5);
  const f_utf_string_static_t expected = macro_f_utf_string_static_t_initialize("test", 0, 4);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_append_assure_nulless(source.string, source.used, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
  }

  // The string already exists, so destination should be unchanged.
  {
    const f_status_t status = f_utf_string_append_assure_nulless(source.string, source.used, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
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

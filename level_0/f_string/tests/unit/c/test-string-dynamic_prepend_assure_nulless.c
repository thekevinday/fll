#include "test-string.h"
#include "test-string-dynamic_prepend_assure_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_prepend_assure_nulless__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\0st", 0, 5);
  const f_string_static_t expected = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_prepend_assure_nulless(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
  }

  // The string already exists, so destination should be unchanged.
  {
    const f_status_t status = f_string_dynamic_prepend_assure_nulless(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
  }

  free((void *) destination.string);
}

void test__f_string_dynamic_prepend_assure_nulless__parameter_checking(void **state) {

  const f_string_dynamic_t data = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_prepend_assure_nulless(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

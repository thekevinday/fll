#include "test-string.h"
#include "test-string-dynamic_prepend_assure.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_prepend_assure__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\0st", 0, 5);
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_prepend_assure(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    assert_string_equal(destination.string, source.string);
    assert_string_equal(destination.string + 3, source.string + 3);
  }

  // The string already exists, so destination should be unchanged.
  {
    const f_status_t status = f_string_dynamic_prepend_assure(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);

    assert_string_equal(destination.string, source.string);
    assert_string_equal(destination.string + 3, source.string + 3);
  }

  free((void *) destination.string);
}

void test__f_string_dynamic_prepend_assure__parameter_checking(void **state) {

  const f_string_dynamic_t data = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_prepend_assure(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

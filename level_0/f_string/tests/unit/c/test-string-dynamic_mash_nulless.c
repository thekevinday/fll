#include "test-string.h"
#include "test-string-dynamic_mash_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_mash_nulless__works(void **state) {

  const f_string_static_t glue = macro_f_string_static_t_initialize(":", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize("te\0st", 0, 5);
  const f_string_static_t expected1 = macro_f_string_static_t_initialize("test", 0, 4);
  const f_string_static_t expected2 = macro_f_string_static_t_initialize("test:test", 0, 9);
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_mash_nulless(glue, source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected1.used);

    assert_string_equal(destination.string, expected1.string);
  }

  // Check that the glue is added.
  {
    const f_status_t status = f_string_dynamic_mash_nulless(glue, source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected2.used);

    assert_string_equal(destination.string, expected2.string);
  }

  free((void *) destination.string);
}

void test__f_string_dynamic_mash_nulless__parameter_checking(void **state) {

  const f_string_static_t glue = macro_f_string_static_t_initialize(":", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize("te\0st", 0, 5);

  {
    const f_status_t status = f_string_dynamic_mash_nulless(glue, source, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

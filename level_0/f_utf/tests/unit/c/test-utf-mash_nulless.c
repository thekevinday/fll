#include "test-utf.h"
#include "test-utf-mash_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_mash_nulless__works(void **state) {

  const f_utf_string_static_t glue = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0:", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 5);
  const f_utf_string_static_t expected1 = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t", 0, 4);
  const f_utf_string_static_t expected2 = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0s\0\0\0t\0\0\0:\0\0\0t\0\0\0e\0\0\0s\0\0\0t", 0, 9);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_mash_nulless(glue.string, glue.used, source.string, source.used, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected1.used);

    for (f_array_length_t i = 0; i < expected1.used; ++i) {
      assert_int_equal(destination.string[i], expected1.string[i]);
    } // for
  }

  // Check that the glue is added.
  {
    const f_status_t status = f_utf_string_mash_nulless(glue.string, glue.used, source.string, source.used, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected2.used);

    for (f_array_length_t i = 0; i < expected2.used; ++i) {
      assert_int_equal(destination.string[i], expected2.string[i]);
    } // for
  }

  free((void *) destination.string);
}

void test__f_utf_mash_nulless__parameter_checking(void **state) {

  const f_utf_string_static_t glue = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0:", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 5);

  {
    const f_status_t status = f_utf_string_mash_nulless(glue.string, glue.used, source.string, source.used, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

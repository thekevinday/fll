#include "test-utf.h"
#include "test-utf-dynamic_mash.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_utf_string_dynamic_mash__works(void **state) {

  const f_utf_string_static_t glue = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0:", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 5);
  const f_utf_string_static_t expected = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t\0\0\0:\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 11);
  f_utf_string_dynamic_t destination = f_utf_string_dynamic_t_initialize;

  {
    const f_status_t status = f_utf_string_dynamic_mash(glue, source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, source.used);

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      assert_int_equal(destination.string[i], source.string[i]);
    } // for
  }

  // Check that the glue is added.
  {
    const f_status_t status = f_utf_string_dynamic_mash(glue, source, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, expected.used);

    for (f_number_unsigned_t i = 0; i < expected.used; ++i) {
      assert_int_equal(destination.string[i], expected.string[i]);
    } // for
  }

  free((void *) destination.string);
}

void test__f_utf_string_dynamic_mash__parameter_checking(void **state) {

  const f_utf_string_static_t glue = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0:", 0, 1);
  const f_utf_string_static_t source = macro_f_utf_string_static_t_initialize_1((f_utf_string_t) "\0\0\0t\0\0\0e\0\0\0\0\0\0\0s\0\0\0t", 0, 5);

  {
    const f_status_t status = f_utf_string_dynamic_mash(glue, source, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

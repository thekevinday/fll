#include "test-string.h"
#include "test-string-dynamic_partial_mash.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_partial_mash__works(void **state) {

  const f_string_static_t glue = macro_f_string_static_t_initialize_1(":", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("_te\0st_", 0, 7);
  const f_string_static_t expected1 = macro_f_string_static_t_initialize_1("te\0st", 0, 5);
  const f_string_static_t expected2 = macro_f_string_static_t_initialize_1("te\0st:te\0st", 0, 11);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(1, 5);
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_partial_mash(glue, source, partial, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, expected1.used);

    assert_string_equal(destination.string, expected1.string);
    assert_string_equal(destination.string + 3, expected1.string + 3);
  }

  // Check that the glue is added.
  {
    const f_status_t status = f_string_dynamic_partial_mash(glue, source, partial, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, expected2.used);

    assert_string_equal(destination.string, expected2.string);
    assert_string_equal(destination.string + 3, expected2.string + 3);
    assert_string_equal(destination.string + 9, expected2.string + 9);
  }

  free((void *) destination.string);
}

void test__f_string_dynamic_partial_mash__parameter_checking(void **state) {

  const f_string_static_t glue = macro_f_string_static_t_initialize_1(":", 0, 1);
  const f_string_static_t source = macro_f_string_static_t_initialize_1("te\0st", 0, 5);
  const f_string_range_t partial = f_string_range_t_initialize;

  {
    const f_status_t status = f_string_dynamic_partial_mash(glue, source, partial, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-string.h"
#include "test-string-dynamic_partial_append_assure_nulless.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_string_dynamic_partial_append_assure_nulless__works(void **state) {

  const f_string_static_t source = macro_f_string_static_t_initialize_1("_te\0st_", 0, 7);
  const f_string_static_t expected = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(1, 5);
  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_string_dynamic_append(expected, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
  }

  // The string already exists, so destination should be unchanged.
  {
    const f_status_t status = f_string_dynamic_partial_append_assure_nulless(source, partial, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, expected.used);

    assert_string_equal(destination.string, expected.string);
  }

  free((void *) destination.string);
}

void test__f_string_dynamic_partial_append_assure_nulless__parameter_checking(void **state) {

  const f_string_dynamic_t data = f_string_dynamic_t_initialize;
  const f_string_range_t partial = f_string_range_t_initialize;

  {
    const f_status_t status = f_string_dynamic_partial_append_assure_nulless(data, partial, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

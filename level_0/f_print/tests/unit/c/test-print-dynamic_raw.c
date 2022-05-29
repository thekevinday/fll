#include "test-print.h"
#include "test-print-dynamic_raw.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_dynamic_raw__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, 1);

    const f_status_t status = f_print_dynamic_raw(test, stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_dynamic_raw__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_print_dynamic_raw(test, 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_print_dynamic_raw__returns_data_not(void **state) {

  {
    const f_status_t status = f_print_dynamic_raw(f_string_empty_s, stdout);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_dynamic_raw__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, 0);

    const f_status_t status = f_print_dynamic_raw(test, stdout);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-print.h"
#include "test-print-raw_safely.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_raw_safely__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_raw_safely(test.string, test.used, stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_raw_safely__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_print_raw_safely(test.string, test.used, 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_print_raw_safely__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_print_raw_safely(f_string_empty_s.string, f_string_empty_s.used, stdout);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_raw_safely(test.string, f_string_empty_s.used, stdout);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_raw_safely(0, test.used, stdout);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_raw_safely__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_raw_safely(test.string, test.used, stdout);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

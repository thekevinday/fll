#include "test-print.h"
#include "test-print-except.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_except__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_except(test.string, 0, test.used, except, stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_except__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;

  {
    const f_status_t status = f_print_except(test.string, 0, test.used, except, 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_print_except__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;

  {
    const f_status_t status = f_print_except(f_string_empty_s.string, 0, f_string_empty_s.used, except, stdout);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_except(test.string, 0, f_string_empty_s.used, except, stdout);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_except(0, 0, test.used, except, stdout);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_except__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except(test.string, 0, test.used, except, stdout);

    assert_int_equal(status, F_none);
  }

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except(test.string, 2, test.used, except, stdout);

    assert_int_equal(status, F_none);
  }

  {
    f_array_length_t lengths[] = { 3 };
    const f_array_lengths_t except = macro_f_array_lengths_t_initialize(lengths, 0, 1);

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used - 1);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except(test.string, 1, test.used, except, stdout);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

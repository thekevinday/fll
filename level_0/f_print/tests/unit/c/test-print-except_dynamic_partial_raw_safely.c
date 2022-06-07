#include "test-print.h"
#include "test-print-except_dynamic_partial_raw_safely.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_except_dynamic_partial_raw_safely__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_string_range_t partial = macro_f_string_range_t_initialize(0, 2);

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_except_dynamic_partial_raw_safely(test, partial, except, stdout);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_except_dynamic_partial_raw_safely__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_string_range_t partial = macro_f_string_range_t_initialize(0, 2);

  {
    const f_status_t status = f_print_except_dynamic_partial_raw_safely(test, partial, except, 0);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_print_except_dynamic_partial_raw_safely__returns_data_not(void **state) {

  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_string_range_t partial = macro_f_string_range_t_initialize(0, 2);

  {
    const f_status_t status = f_print_except_dynamic_partial_raw_safely(f_string_empty_s, partial, except, stdout);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_except_dynamic_partial_raw_safely__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize(0, 2);

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except_dynamic_partial_raw_safely(test, partial, except, stdout);

    assert_int_equal(status, F_none);
  }

  {
    f_array_length_t lengths[] = { 3 };
    const f_array_lengths_t except = macro_f_array_lengths_t_initialize(lengths, 0, 1);

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except_dynamic_partial_raw_safely(test, partial, except, stdout);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

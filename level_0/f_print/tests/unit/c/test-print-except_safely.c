#include "test-print.h"
#include "test-print-except_safely.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_except_safely__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_except_safely(test.string, 0, test.used, except, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_except_safely__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_except_safely(f_string_empty_s.string, 0, f_string_empty_s.used, except, output);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_except_safely(test.string, 0, f_string_empty_s.used, except, output);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_except_safely(0, 0, test.used, except, output);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_except_safely__returns_stream_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_file_t output = macro_f_file_t_initialize_2(0, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_except_safely(test.string, 0, test.used, except, output);

    assert_int_equal(status, F_stream_not);
  }
}

void test__f_print_except_safely__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except_safely(test.string, 0, test.used, except, output);

    assert_int_equal(status, F_none);
  }

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except_safely(test.string, 2, test.used, except, output);

    assert_int_equal(status, F_none);
  }

  {
    f_array_length_t lengths[] = { 3 };
    const f_array_lengths_t except = macro_f_array_lengths_t_initialize_1(lengths, 0, 1);

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, test.used - 1);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_except_safely(test.string, 1, test.used, except, output);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-print.h"
#include "test-print-to_except_in_safely.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_to_except_in_safely__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_string_ranges_t range = f_string_ranges_t_initialize;

  int errnos[] = {
    EAGAIN,
    EBADF,
    EDESTADDRREQ,
    EDQUOT,
    EFBIG,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ENOSPC,
    EPIPE,
    EWOULDBLOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_block,
    F_file_descriptor,
    F_socket_not,
    F_filesystem_quota_block,
    F_number_overflow,
    F_buffer,
    F_interrupt,
    F_parameter,
    F_input_output,
    F_file_type_directory,
    F_space_not,
    F_pipe,
    F_block,
    F_output,
  };

  for (int i = 0; i < 14; ++i) {

    will_return(__wrap_write, true);
    will_return(__wrap_write, errnos[i]);

    const f_status_t status = f_print_to_except_in_safely(test.string, 0, test.used, except, range, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_print_to_except_in_safely__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_string_ranges_t range = f_string_ranges_t_initialize;

  {
    const f_status_t status = f_print_to_except_in_safely(test.string, 0, test.used, except, range, -1);

    assert_int_equal(F_status_set_fine(status), F_parameter);
  }
}

void test__f_print_to_except_in_safely__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  const f_array_lengths_t except = f_array_lengths_t_initialize;
  const f_string_ranges_t range = f_string_ranges_t_initialize;

  {
    const f_status_t status = f_print_to_except_in_safely(f_string_empty_s.string, 0, f_string_empty_s.used, except, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_to_except_in_safely(test.string, 0, f_string_empty_s.used, except, range, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_print_to_except_in_safely(0, 0, test.used, except, range, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_to_except_in_safely__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;
    const f_string_ranges_t range = f_string_ranges_t_initialize;

    will_return(__wrap_write, false);
    will_return(__wrap_write, test.used);

    const f_status_t status = f_print_to_except_in_safely(test.string, 0, test.used, except, range, 0);

    assert_int_equal(status, F_none);
  }

  {
    const f_array_lengths_t except = f_array_lengths_t_initialize;
    const f_string_ranges_t range = f_string_ranges_t_initialize;

    will_return(__wrap_write, false);
    will_return(__wrap_write, test.used);

    const f_status_t status = f_print_to_except_in_safely(test.string, 2, test.used, except, range, 0);

    assert_int_equal(status, F_none);
  }

  {
    f_array_length_t lengths[] = { 3 };
    f_string_range_t ranges[] = {
      macro_f_string_range_t_initialize(0, 1),
    };
    const f_array_lengths_t except = macro_f_array_lengths_t_initialize(lengths, 0, 1);
    const f_string_ranges_t range = macro_f_string_ranges_t_initialize(ranges, 0, 1);

    will_return(__wrap_write, false);
    will_return(__wrap_write, test.used);

    const f_status_t status = f_print_to_except_in_safely(test.string, 1, test.used, except, range, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

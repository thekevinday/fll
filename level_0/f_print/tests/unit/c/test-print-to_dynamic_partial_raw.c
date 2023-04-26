#include "test-print.h"
#include "test-print-to_dynamic_partial_raw.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_to_dynamic_partial_raw__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

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

    const f_status_t status = f_print_to_dynamic_partial_raw(test, partial, output);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_print_to_dynamic_partial_raw__returns_data_not(void **state) {

  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_to_dynamic_partial_raw(f_string_empty_s, partial, output);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_to_dynamic_partial_raw__returns_file_descriptor_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(0, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_to_dynamic_partial_raw(test, partial, output);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_print_to_dynamic_partial_raw__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_write, false);
    will_return(__wrap_write, test.used);

    const f_status_t status = f_print_to_dynamic_partial_raw(test, partial, output);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

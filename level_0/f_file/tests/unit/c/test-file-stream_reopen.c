#include "test-file.h"
#include "test-file-stream_reopen.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_reopen__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EAGAIN,
    EBADF,
    EFBIG,
    EDEADLK,
    EDESTADDRREQ,
    EDQUOT,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EMFILE,
    ENOLCK,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EPIPE,
    EWOULDBLOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_block,
    F_file_descriptor,
    F_file_overflow,
    F_deadlock,
    F_socket_not,
    F_space_not,
    F_buffer,
    F_interrupt,
    F_parameter,
    F_input_output,
    F_file_descriptor_max,
    F_lock,
    F_space_not,
    F_file_type_not_directory,
    F_prohibited,
    F_pipe_not,
    F_block,
    F_failure,
  };

  for (int i = 0; i < 19; ++i) {

    f_file_t file = f_file_t_initialize;

    will_return(__wrap_freopen, true);
    will_return(__wrap_freopen, errnos[i]);

    const f_status_t status = f_file_stream_reopen(path, path, &file);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  for (int i = 0; i < 19; ++i) {

    f_file_t file = f_file_t_initialize;

    will_return(__wrap_freopen, true);
    will_return(__wrap_freopen, errnos[i]);

    const f_status_t status = f_file_stream_reopen(path, f_string_empty_s, &file);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_stream_reopen__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_stream_reopen(f_string_empty_s, f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_reopen__returns_data_not(void **state) {

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_stream_reopen(f_string_empty_s, f_string_empty_s, &file);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stream_reopen__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;
    file.stream = F_type_input_d;

    will_return(__wrap_freopen, false);
    will_return(__wrap_freopen, F_type_input_d);

    const f_status_t status = f_file_stream_reopen(path, path, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.stream, F_type_input_d);
  }

  {
    f_file_t file = f_file_t_initialize;

    will_return(__wrap_freopen, false);
    will_return(__wrap_freopen, F_type_input_d);

    const f_status_t status = f_file_stream_reopen(path, f_string_empty_s, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.stream, F_type_input_d);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

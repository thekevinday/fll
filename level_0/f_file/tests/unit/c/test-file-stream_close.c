#include "test-file.h"
#include "test-file-stream_close.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_close__fails(void **state) {

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

  f_status_t status_closes[] = {
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
    F_file_close,
  };

  for (int i = 0; i < 19; ++i) {

    f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

    will_return(__wrap_fclose, true);
    will_return(__wrap_fclose, errnos[i]);

    const f_status_t status = f_file_stream_close(&file);

    assert_int_equal(F_status_set_fine(status), status_closes[i]);
    assert_int_equal(file.stream, 0);
  } // for
}

void test__f_file_stream_close__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_stream_close(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_close__returns_stream_not(void **state) {

  f_file_t file = macro_f_file_t_initialize2(0, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_stream_close(&file);

    assert_int_equal(status, F_stream_not);
  }
}

void test__f_file_stream_close__works(void **state) {

  {
    f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

    file.id = 0;
    file.stream = F_type_input_d;

    will_return(__wrap_fclose, false);
    will_return(__wrap_fclose, 0);

    const f_status_t status = f_file_stream_close(&file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.stream, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

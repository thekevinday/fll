#include "test-file.h"
#include "test-file-stream_close.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_close__fails_for_file_descriptor(void **state) {

  int errno_flushs[] = {
    EBADF,
    EDQUOT,
    EINVAL,
    EIO,
    ENOSPC,
    EROFS,
  };

  int errno_closes[] = {
    EBADF,
    EDQUOT,
    EINTR,
    EIO,
    ENOSPC,
    mock_errno_generic,
  };

  f_status_t status_flushs[] = {
    F_file_descriptor,
    F_filesystem_quota_block,
    F_supported_not,
    F_input_output,
    F_space_not,
    F_supported_not,
  };

  f_status_t status_closes[] = {
    F_file_descriptor,
    F_filesystem_quota_block,
    F_interrupt,
    F_input_output,
    F_space_not,
    F_file_close,
  };

  for (uint8_t flush = 0; flush < 2; ++flush) {

    for (int i = 0; i < 6; ++i) {

      f_file_t file = f_file_t_initialize;
      file.id = 0;
      file.stream = 0;

      if (flush) {
        if (flush == 1) {
          will_return(__wrap_fsync, true);
          will_return(__wrap_fsync, errno_flushs[i]);
        }
        else {
          will_return(__wrap_fsync, false);
          will_return(__wrap_fsync, 0);
        }

        will_return(__wrap_close, true);
        will_return(__wrap_close, errno_closes[i]);
      }
      else {
        will_return(__wrap_close, true);
        will_return(__wrap_close, errno_closes[i]);
      }

      const f_status_t status = f_file_stream_close(flush, &file);

      assert_int_equal(F_status_set_fine(status), status_closes[i]);

      assert_int_equal(file.id, -1);
      assert_int_equal(file.stream, 0);
    } // for
  } // for
}

void test__f_file_stream_close__fails_for_stream(void **state) {

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

  f_status_t status_flushs[] = {
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
    F_file_synchronize,
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

  for (uint8_t flush = 0; flush < 2; ++flush) {

    for (int i = 0; i < 19; ++i) {

      f_file_t file = f_file_t_initialize;
      file.id = 0;
      file.stream = stdout;

      if (flush) {
        if (flush == 1) {
          will_return(__wrap_fflush, true);
          will_return(__wrap_fflush, errnos[i]);
        }
        else {
          will_return(__wrap_fflush, false);
          will_return(__wrap_fflush, 0);
        }

        will_return(__wrap_fclose, true);
        will_return(__wrap_fclose, errnos[i]);
      }
      else {
        will_return(__wrap_fclose, true);
        will_return(__wrap_fclose, errnos[i]);
      }

      const f_status_t status = f_file_stream_close(flush, &file);

      assert_int_equal(F_status_set_fine(status), status_closes[i]);
      assert_int_equal(file.id, -1);
      assert_int_equal(file.stream, 0);
    } // for
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stream_close__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_stream_close(F_false, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stream_close__works(void **state) {

  {
    f_file_t file = f_file_t_initialize;

    file.id = 0;
    file.stream = stdout;

    will_return(__wrap_fclose, false);
    will_return(__wrap_fclose, 0);

    const f_status_t status = f_file_stream_close(F_false, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, -1);
    assert_int_equal(file.stream, 0);
  }

  {
    f_file_t file = f_file_t_initialize;

    file.id = 0;
    file.stream = 0;

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_stream_close(F_false, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, -1);
    assert_int_equal(file.stream, 0);
  }

  {
    f_file_t file = f_file_t_initialize;

    file.id = 0;
    file.stream = stdout;

    will_return(__wrap_fflush, false);
    will_return(__wrap_fflush, 0);

    will_return(__wrap_fclose, false);
    will_return(__wrap_fclose, 0);

    const f_status_t status = f_file_stream_close(F_true, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, -1);
    assert_int_equal(file.stream, 0);
  }

  {
    f_file_t file = f_file_t_initialize;

    file.id = 0;
    file.stream = 0;

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_stream_close(F_true, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, -1);
    assert_int_equal(file.stream, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

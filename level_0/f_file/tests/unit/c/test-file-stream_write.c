#include "test-file.h"
#include "test-file-stream_write.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_write__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EAGAIN,
    EBADF,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    EWOULDBLOCK,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_block,
    F_file_descriptor,
    F_buffer,
    F_interrupt,
    F_parameter,
    F_input_output,
    F_file_type_directory,
    F_block,
    F_file_write,
  };

  for (int i = 0; i < 9; ++i) {

    f_file_t file = f_file_t_initialize;
    file.size_read = 1;
    file.stream = F_type_input_d;

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, errnos[i]);

    will_return(__wrap_ferror_unlocked, false);
    will_return(__wrap_ferror_unlocked, 1);

    const f_status_t status = f_file_stream_write(file, path, 0);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stream_write__parameter_checking(void **state) {

    f_file_t file = f_file_t_initialize;
    file.size_write = 0;

    {
      const f_status_t status = f_file_stream_write(file, f_string_empty_s, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stream_write__returns_file_closed(void **state) {

  const f_file_t file = f_file_t_initialize;

  {
    const f_status_t status = f_file_stream_write(file, f_string_empty_s, 0);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }
}

void test__f_file_stream_write__returns_data_not(void **state) {

  f_file_t file = f_file_t_initialize;
  file.stream = F_type_input_d;

  {
    const f_status_t status = f_file_stream_write(file, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_stream_write(file, f_string_empty_s, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_stream_write__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;
    file.size_write = path.used;
    file.stream = F_type_input_d;

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, file.size_write);

    will_return(__wrap_ferror_unlocked, false);
    will_return(__wrap_ferror_unlocked, 0);

    const f_status_t status = f_file_stream_write(file, path, 0);

    assert_int_equal(status, F_none_eos);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

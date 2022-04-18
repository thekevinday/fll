#include "test-file.h"
#include "test-file-read_block.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_read_block__fails(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  file.id = 1;

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
    F_failure,
  };

  for (int i = 0; i < 9; ++i) {

    will_return(__wrap_read, true);
    will_return(__wrap_read, errnos[i]);

    const f_status_t status = f_file_read_block(file, &buffer);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for

  f_string_dynamic_resize(0, &buffer);
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_read_block__parameter_checking(void **state) {

    f_file_t file = f_file_t_initialize;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    file.id = 1;

    {
      const f_status_t status = f_file_read_block(file, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    file.size_read = 0;

    {
      const f_status_t status = f_file_read_block(file, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      f_string_dynamic_t string = f_string_dynamic_t_initialize;

      const f_status_t status = f_file_read_block(file, &string);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    f_string_dynamic_resize(0, &buffer);
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_read_block__returns_file_closed(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_read_block(file, &buffer);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_read_block__works(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  file.id = 1;
  file.size_read = 4;

  {
    will_return(__wrap_read, false);
    will_return(__wrap_read, "abcd");
    will_return(__wrap_read, 4);
    will_return(__wrap_read, 4);

    const f_status_t status = f_file_read_block(file, &buffer);

    // Ensure string ends in NULL so that assert_string_equal() can be used.
    f_string_dynamic_increase_by(1, &buffer);
    buffer.string[buffer.used] = 0;

    assert_int_equal(status, F_none);
    assert_int_equal(buffer.used, 4);
    assert_string_equal(buffer.string, "abcd");
  }

  {
    will_return(__wrap_read, false);
    will_return(__wrap_read, "");
    will_return(__wrap_read, 0);
    will_return(__wrap_read, 0);

    const f_status_t status = f_file_read_block(file, &buffer);

    assert_int_equal(status, F_none_eof);
    assert_int_equal(buffer.used, 4);
    assert_string_equal(buffer.string, "abcd");
  }

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif

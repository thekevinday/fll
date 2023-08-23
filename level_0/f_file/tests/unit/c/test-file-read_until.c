#include "test-file.h"
#include "test-file-read_until.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_read_until__fails(void **state) {

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

    const f_status_t status = f_file_read_until(file, 1, &buffer);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  free((void *) buffer.string);
}

void test__f_file_read_until__parameter_checking(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  file.id = 1;

  {
    const f_status_t status = f_file_read_until(file, 1, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  file.size_read = 0;

  {
    const f_status_t status = f_file_read_until(file, 1, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_string_dynamic_t string = f_string_dynamic_t_initialize;

    const f_status_t status = f_file_read_until(file, 1, &string);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  free((void *) buffer.string);
}

void test__f_file_read_until__returns_file_descriptor_not(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_read_until(file, 1, &buffer);

    assert_int_equal(F_status_set_fine(status), F_file_descriptor_not);
  }

  free((void *) buffer.string);
}

void test__f_file_read_until__works(void **state) {

  f_file_t file = f_file_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  file.id = 1;
  file.size_read = 4;

  {
    will_return(__wrap_read, false);
    will_return(__wrap_read, "abcd");
    will_return(__wrap_read, 4);
    will_return(__wrap_read, 4);

    will_return(__wrap_read, false);
    will_return(__wrap_read, "ef");
    will_return(__wrap_read, 2);
    will_return(__wrap_read, 2);

    const f_status_t status = f_file_read_until(file, 6, &buffer);

    // Ensure string ends in NULL so that assert_string_equal() can be used.
    f_string_dynamic_increase_by(1, &buffer);
    buffer.string[buffer.used] = 0;

    assert_int_equal(status, F_okay_stop);
    assert_int_equal(buffer.used, 6);
    assert_string_equal(buffer.string, "abcdef");
  }

  {
    buffer.used = 0;

    will_return(__wrap_read, false);
    will_return(__wrap_read, "abcd");
    will_return(__wrap_read, 4);
    will_return(__wrap_read, 4);

    will_return(__wrap_read, false);
    will_return(__wrap_read, "");
    will_return(__wrap_read, 0);
    will_return(__wrap_read, 0);

    const f_status_t status = f_file_read_until(file, 6, &buffer);

    // Ensure string ends in NULL so that assert_string_equal() can be used.
    f_string_dynamic_increase_by(1, &buffer);
    buffer.string[buffer.used] = 0;

    assert_int_equal(status, F_okay_eof);
    assert_int_equal(buffer.used, 4);
    assert_string_equal(buffer.string, "abcd");
  }

  free((void *) buffer.string);
}

#ifdef __cplusplus
} // extern "C"
#endif

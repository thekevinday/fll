#include "test-file.h"
#include "test-file-write_until.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_write_until__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

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
    file.size_write = 1;
    file.id = 0;

    will_return(__wrap_write, true);
    will_return(__wrap_write, errnos[i]);

    const f_status_t status = f_file_write_until(file, path, 1, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_write_until__parameter_checking(void **state) {

  f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  file.size_write = 0;

  {
    const f_status_t status = f_file_write_until(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_write_until__returns_file_descriptor_not(void **state) {

  f_file_t file = f_file_t_initialize;
  file.size_write = 1;

  {
    const f_status_t status = f_file_write_until(file, f_string_empty_s, 1, 0);

    assert_int_equal(F_status_set_fine(status), F_file_descriptor_not);
  }
}

void test__f_file_write_until__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  f_file_t file = f_file_t_initialize;
  file.id = 0;

  {
    const f_status_t status = f_file_write_until(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_write_until(file, path, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_write_until(file, f_string_empty_s, 1, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_write_until(file, f_string_empty_s, 0, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_write_until(file, path, 0, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }

  {
    f_array_length_t written = 1;

    const f_status_t status = f_file_write_until(file, f_string_empty_s, 1, &written);

    assert_int_equal(status, F_data_not);
    assert_int_equal(written, 0);
  }
}

void test__f_file_write_until__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;
    file.size_write = 1;
    file.id = 0;

    will_return(__wrap_write, false);
    will_return(__wrap_write, file.size_write);

    will_return(__wrap_write, false);
    will_return(__wrap_write, file.size_write);

    will_return(__wrap_write, false);
    will_return(__wrap_write, file.size_write);

    will_return(__wrap_write, false);
    will_return(__wrap_write, file.size_write);

    const f_status_t status = f_file_write_until(file, path, path.used, 0);

    assert_int_equal(status, F_none_eos);
  }

  {
    f_file_t file = f_file_t_initialize;
    file.size_write = path.used;
    file.id = 0;

    will_return(__wrap_write, false);
    will_return(__wrap_write, file.size_write);

    const f_status_t status = f_file_write_until(file, path, path.used, 0);

    assert_int_equal(status, F_none_eos);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

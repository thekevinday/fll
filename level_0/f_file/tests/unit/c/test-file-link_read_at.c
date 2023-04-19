#include "test-file.h"
#include "test-file-link.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_link_read_at__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_parameter,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_failure,
  };

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  statistics.st_size = 1;

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_fstatat, false);
    will_return(__wrap_fstatat, &statistics);
    will_return(__wrap_fstatat, 0);

    will_return(__wrap_readlinkat, true);
    will_return(__wrap_readlinkat, errnos[i]);

    const f_status_t status = f_file_link_read_at(file, path, 0, &buffer);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read_at__parameter_checking(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_link_read_at(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read_at__returns_data_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_link_read_at(file, f_string_empty_s, 0, &buffer);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read_at__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, -1, F_file_flag_write_only_d);
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_link_read_at(file, f_string_empty_s, 0, &buffer);

    assert_int_equal(status, F_file_descriptor_not);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read_at__works(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  statistics.st_size = 1;

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  char source[2] = { 'x', 0 };

  {
    will_return(__wrap_fstatat, false);
    will_return(__wrap_fstatat, &statistics);
    will_return(__wrap_fstatat, 0);

    will_return(__wrap_readlinkat, false);
    will_return(__wrap_readlinkat, source);
    will_return(__wrap_readlinkat, 0);

    const f_status_t status = f_file_link_read_at(file, path, 0, &buffer);

    assert_int_equal(status, F_none);
  }

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-size_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_size_at__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_parameter,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_number_overflow,
    F_file_stat,
  };

  for (int i = 0; i < 11; ++i) {

    off_t size = 0;

    will_return(__wrap_fstatat, true);
    will_return(__wrap_fstatat, errnos[i]);

    const f_status_t status = f_file_size_at(file, path, F_false, &size);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_size_at__parameter_checking(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_size_at(file, f_string_empty_s, F_false, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_size_at__returns_data_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    off_t size = 0;

    const f_status_t status = f_file_size_at(file, f_string_empty_s, F_false, &size);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_size_at__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    off_t size = 0;

    const f_status_t status = f_file_size_at(file, f_string_empty_s, F_false, &size);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_size_at__works(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    off_t size = 0;

    statistics.st_mode = 1 | F_file_type_link_d;
    statistics.st_size = 1;

    will_return(__wrap_fstatat, false);
    will_return(__wrap_fstatat, &statistics);
    will_return(__wrap_fstatat, 0);

    const f_status_t status = f_file_size_at(file, path, F_false, &size);

    assert_int_equal(status, F_none);
    assert_int_equal(size, statistics.st_size);
  }

  {
    off_t size = 0;

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

    will_return(__wrap_fstatat, false);
    will_return(__wrap_fstatat, &statistics);
    will_return(__wrap_fstatat, 0);

    const f_status_t status = f_file_size_at(file, path, F_true, &size);

    assert_int_equal(status, F_none);
    assert_int_equal(size, statistics.st_size);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

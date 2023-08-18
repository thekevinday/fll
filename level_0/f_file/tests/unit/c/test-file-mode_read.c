#include "test-file.h"
#include "test-file-mode_read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_mode_read__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
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

  for (int i = 0; i < 10; ++i) {

    mode_t mode = 0;

    will_return(__wrap_lstat, true);
    will_return(__wrap_lstat, errnos[i]);

    const f_status_t status = f_file_mode_read(path, F_false, &mode);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_mode_read__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_mode_read(f_string_empty_s, F_true, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_mode_read__returns_data_not(void **state) {

  {
    mode_t mode = 0;

    const f_status_t status = f_file_mode_read(f_string_empty_s, F_true, &mode);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_mode_read__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    mode_t mode = 0;

    statistics.st_mode = 1 | F_file_type_link_d;

    will_return(__wrap_lstat, false);
    will_return(__wrap_lstat, &statistics);
    will_return(__wrap_lstat, 0);

    const f_status_t status = f_file_mode_read(path, F_false, &mode);

    assert_int_equal(status, F_okay);
    assert_int_equal(mode, statistics.st_mode);
  }

  {
    mode_t mode = 0;

    statistics.st_mode = 1 | F_file_type_regular_d;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_mode_read(path, F_true, &mode);

    assert_int_equal(status, F_okay);
    assert_int_equal(mode, statistics.st_mode);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

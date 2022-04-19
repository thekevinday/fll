#include "test-file.h"
#include "test-file-exists.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_exists__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

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
    F_false,
    F_memory_not,
    F_directory_not,
    F_number_overflow,
    F_file_stat,
  };

  for (int i = 0; i < 10; ++i) {

    will_return(__wrap_lstat, true);
    will_return(__wrap_lstat, errnos[i]);

    const f_status_t status = f_file_exists(path, F_false);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for

  for (int i = 0; i < 9; ++i) {

    will_return(__wrap_stat, true);
    will_return(__wrap_stat, errnos[i]);

    const f_status_t status = f_file_exists(path, F_true);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

void test__f_file_exists__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_exists(f_string_empty_s, F_true);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_exists__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    statistics.st_mode = 1 | F_file_type_link_d;

    will_return(__wrap_lstat, false);
    will_return(__wrap_lstat, &statistics);
    will_return(__wrap_lstat, 0);

    const f_status_t status = f_file_exists(path, F_false);

    assert_int_equal(status, F_true);
  }

  {
    statistics.st_mode = 1 | F_file_type_regular_d;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_exists(path, F_true);

    assert_int_equal(status, F_true);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

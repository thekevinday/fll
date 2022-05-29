#include "test-file.h"
#include "test-file-size.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stat__fails(void **state) {

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
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_number_overflow,
    F_file_stat,
  };

  for (int i = 0; i < 10; ++i) {

    struct stat result;

    memset(&result, 0, sizeof(struct stat));

    will_return(__wrap_lstat, true);
    will_return(__wrap_lstat, errnos[i]);

    const f_status_t status = f_file_stat(path, F_false, &result);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_stat__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_stat(f_string_empty_s, F_false, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stat__returns_data_not(void **state) {

  {
    struct stat result;

    memset(&result, 0, sizeof(struct stat));

    const f_status_t status = f_file_stat(f_string_empty_s, F_false, &result);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stat__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    struct stat result;

    memset(&result, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_stat(path, F_true, &result);

    assert_int_equal(status, F_none);
    assert_int_equal(result.st_mode, statistics.st_mode);
    assert_int_equal(result.st_size, statistics.st_size);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

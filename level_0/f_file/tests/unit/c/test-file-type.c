#include "test-file.h"
#include "test-file-type.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_type__fails(void **state) {

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

    int type = 0;

    will_return(__wrap_lstat, true);
    will_return(__wrap_lstat, errnos[i]);

    const f_status_t status = f_file_type(path, F_false, &type);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_type__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_type(f_string_empty_s, F_true, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_type__returns_data_not(void **state) {

  {
    int type = 0;

    const f_status_t status = f_file_type(f_string_empty_s, F_true, &type);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_type__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    int type = 0;

    statistics.st_mode = 1 | F_file_type_link_d;

    will_return(__wrap_lstat, false);
    will_return(__wrap_lstat, &statistics);
    will_return(__wrap_lstat, 0);

    const f_status_t status = f_file_type(path, F_false, &type);

    assert_int_equal(status, F_none);
    assert_int_equal(type, F_file_type_link_d);
  }

  {
    int type = 0;

    statistics.st_mode = 1 | F_file_type_regular_d;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_type(path, F_true, &type);

    assert_int_equal(status, F_none);
    assert_int_equal(type, F_file_type_regular_d);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

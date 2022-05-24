#include "test-file.h"
#include "test-file-open.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_open__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EOPNOTSUPP,
    EOVERFLOW,
    EPERM,
    EROFS,
    ETXTBSY,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_filesystem_quota_block,
    F_file_found,
    F_buffer,
    F_number_overflow,
    F_interrupt,
    F_parameter,
    F_directory,
    F_loop,
    F_name,
    F_file_open_max,
    F_file_found_not,
    F_memory_not,
    F_space_not,
    F_file_type_not_directory,
    F_supported_not,
    F_number_overflow,
    F_prohibited,
    F_read_only,
    F_busy,
    F_failure,
  };

  for (int i = 0; i < 21; ++i) {

    f_file_t file = f_file_t_initialize;

    will_return(__wrap_open, true);
    will_return(__wrap_open, errnos[i]);

    const f_status_t status = f_file_open(path, 0, &file);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_open__parameter_checking(void **state) {

    const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

    {
      const f_status_t status = f_file_open(path, 0, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_open__returns_data_not(void **state) {

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_open(f_string_empty_s, 0, &file);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_open__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;

    will_return(__wrap_open, false);
    will_return(__wrap_open, 5);

    const f_status_t status = f_file_open(path, 0, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

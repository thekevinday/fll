#include "test-directory.h"
#include "test-directory-open.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_open__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EFAULT,
    EFBIG,
    EOVERFLOW,
    EINTR,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_buffer,
    F_number_overflow,
    F_number_overflow,
    F_interrupt,
    F_parameter,
    F_loop,
    F_name,
    F_file_open_max,
    F_directory_found_not,
    F_memory_not,
    F_space_not,
    F_file_type_not_directory,
    F_prohibited,
    F_read_only,
    F_failure,
  };

  for (int i = 0; i < 16; ++i) {

    int id = 0;

    will_return(__wrap_open, true);
    will_return(__wrap_open, errnos[i]);

    const f_status_t status = f_directory_open(path, F_false, &id);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_directory_open__parameter_checking(void **state) {

    const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

    {
      const f_status_t status = f_directory_open(path, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_directory_open__returns_data_not(void **state) {

  {
    int id = 0;

    const f_status_t status = f_directory_open(f_string_empty_s, F_false, &id);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_directory_open__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int id = 0;

    will_return(__wrap_open, false);
    will_return(__wrap_open, 5);

    const f_status_t status = f_directory_open(path, F_false, &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

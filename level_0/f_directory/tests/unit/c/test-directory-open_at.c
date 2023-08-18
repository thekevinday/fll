#include "test-directory.h"
#include "test-directory-open_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_open_at__fails(void **state) {

  const int at = 1;
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
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
    F_directory_descriptor,
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

  for (int i = 0; i < 17; ++i) {

    int id = 0;

    will_return(__wrap_openat, true);
    will_return(__wrap_openat, errnos[i]);

    const f_status_t status = f_directory_open_at(at, path, F_false, &id);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_directory_open_at__parameter_checking(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_directory_open_at(0, path, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_directory_open_at__returns_data_not(void **state) {

  const int at = 1;

  {
    int id = 0;

    const f_status_t status = f_directory_open_at(at, f_string_empty_s, F_false, &id);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_directory_open_at__works(void **state) {

  const int at = 1;

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    int id = 0;

    will_return(__wrap_openat, false);
    will_return(__wrap_openat, 5);

    const f_status_t status = f_directory_open_at(at, path, F_false, &id);

    assert_int_equal(status, F_okay);
    assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-mode_set_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_mode_set_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  const mode_t mode = 0;

  int errnos[] = {
    EACCES,
    EBADF,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_access_mode,
    F_read_only,
    F_failure,
  };

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchmodat, true);
    will_return(__wrap_fchmodat, errnos[i]);

    const f_status_t status = f_file_mode_set_at(0, path, mode);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_mode_set_at__returns_data_not(void **state) {

  const mode_t mode = 0;

  {
    const f_status_t status = f_file_mode_set_at(0, f_string_empty_s, mode);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_mode_set_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  const mode_t mode = 0;

  {
    will_return(__wrap_fchmodat, false);
    will_return(__wrap_fchmodat, 5);

    const f_status_t status = f_file_mode_set_at(0, path, mode);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

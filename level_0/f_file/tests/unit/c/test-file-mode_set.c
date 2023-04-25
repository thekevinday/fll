#include "test-file.h"
#include "test-file-mode_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_mode_set__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  const mode_t mode = 0;

  int errnos[] = {
    EACCES,
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

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_chmod, true);
    will_return(__wrap_chmod, errnos[i]);

    const f_status_t status = f_file_mode_set(path, mode);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_mode_set__returns_data_not(void **state) {

  const mode_t mode = 0;

  {
    const f_status_t status = f_file_mode_set(f_string_empty_s, mode);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_mode_set__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  const mode_t mode = 0;

  {
    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_mode_set(path, mode);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

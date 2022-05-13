#include "test-path.h"
#include "test-path-change_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_path_change_at__fails(void **state) {

  const int id = 1;

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
    F_directory,
    F_failure,
  };

  for (int i = 0; i < 10; ++i) {

    will_return(__wrap_fchdir, true);
    will_return(__wrap_fchdir, errnos[i]);

    const f_status_t status = f_path_change_at(id);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_path_change_at__works(void **state) {

  const int id = 1;

  {
    will_return(__wrap_fchdir, F_false);
    will_return(__wrap_fchdir, 0);

    const f_status_t status = f_path_change_at(id);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

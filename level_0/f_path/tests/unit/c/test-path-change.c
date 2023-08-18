#include "test-path.h"
#include "test-path-change.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_path_change__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
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
    F_buffer,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory,
    F_failure,
  };

  for (int i = 0; i < 9; ++i) {

    will_return(__wrap_chdir, true);
    will_return(__wrap_chdir, errnos[i]);

    const f_status_t status = f_path_change(path);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_path_change__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_chdir, F_false);
    will_return(__wrap_chdir, 0);

    const f_status_t status = f_path_change(path);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

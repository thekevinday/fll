#include "test-file.h"
#include "test-file-remove_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_remove_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EBUSY,
    EFAULT,
    EIO,
    EISDIR,
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
    F_busy,
    F_buffer,
    F_input_output,
    F_file_type_directory,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_prohibited,
    F_read_only,
    F_failure,
  };

  {
    for (int i = 0; i < 14; ++i) {

      will_return(__wrap_unlinkat, true);
      will_return(__wrap_unlinkat, errnos[i]);

      const f_status_t status = f_file_remove_at(0, path, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_remove_at__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_remove_at(0, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_remove_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_unlinkat, false);
    will_return(__wrap_unlinkat, 0);

    const f_status_t status = f_file_remove_at(0, path, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

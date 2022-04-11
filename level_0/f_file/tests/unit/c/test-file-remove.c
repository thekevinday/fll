#include "test-file.h"
#include "test-file-remove.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_remove__fails(void **state) {
/*
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_busy,
    F_buffer,
    F_parameter,
    F_input_output,
    F_file_type_directory,
    F_loop,
    F_file_descriptor_max,
    F_name,
    F_file_open_max,
    F_file_found_not,
    F_memory_not,
    F_file_not,
    F_file_empty_not,
    F_prohibited,
    F_read_only,
    F_failure,
  };

  {
    for (int i = 0; i < 17; ++i) {

      will_return(__wrap_remove, true);
      will_return(__wrap_remove, errnos[i]);

      const f_status_t status = f_file_remove(path);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
  */
}

void test__f_file_remove__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_remove(f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_remove__works(void **state) {
/*
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_remove, false);
    will_return(__wrap_remove, 0);

    const f_status_t status = f_file_remove(path);

    assert_int_equal(status, F_none);
  }
  */
}

#ifdef __cplusplus
} // extern "C"
#endif

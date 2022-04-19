#include "test-file.h"
#include "test-file-rename.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_rename__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBUSY,
    EDQUOT,
    EFAULT,
    EINVAL,
    EISDIR,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EEXIST,
    EPERM,
    EROFS,
    EXDEV,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_busy,
    F_filesystem_quota_block,
    F_buffer,
    F_parameter,
    F_file_type_directory,
    F_loop,
    F_link,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_space_not,
    F_directory_not,
    F_directory_empty_not,
    F_directory_empty_not,
    F_prohibited,
    F_read_only,
    F_mount,
    F_failure,
  };

  {
    for (int i = 0; i < 19; ++i) {

      will_return(__wrap_rename, true);
      will_return(__wrap_rename, errnos[i]);

      const f_status_t status = f_file_rename(path, path);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
}

void test__f_file_rename__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_file_rename(f_string_empty_s, f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_rename(path, f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_rename(f_string_empty_s, path);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_rename__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_rename, false);
    will_return(__wrap_rename, 0);

    const f_status_t status = f_file_rename(path, path);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

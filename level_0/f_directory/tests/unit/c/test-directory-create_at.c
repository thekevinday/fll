#include "test-directory.h"
#include "test-directory-create.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_create_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
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
    F_filesystem_quota_block,
    F_file_found,
    F_buffer,
    F_parameter,
    F_loop,
    F_directory_link_max,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_space_not,
    F_directory_not,
    F_prohibited,
    F_read_only,
    F_failure,
  };

  for (int i = 0; i < 16; ++i) {

    will_return(__wrap_mkdirat, true);
    will_return(__wrap_mkdirat, errnos[i]);

    const f_status_t status = f_directory_create_at(0, path, 0);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

void test__f_directory_create_at__returns_data_not(void **state) {

  {
    const f_status_t status = f_directory_create_at(0, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_directory_create_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_mkdirat, false);
    will_return(__wrap_mkdirat, 0);

    const f_status_t status = f_directory_create_at(0, path, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

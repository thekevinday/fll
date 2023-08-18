#include "test-file.h"
#include "test-file-link.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_link__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EOVERFLOW,
    EPERM,
    EROFS,
    ETXTBSY,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_filesystem_quota_block,
    F_file_found,
    F_buffer,
    F_number_overflow,
    F_interrupt,
    F_parameter,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_space_not,
    F_directory_not,
    F_number_overflow,
    F_prohibited,
    F_read_only,
    F_busy,
    F_failure,
  };

  for (int i = 0; i < 18; ++i) {

    will_return(__wrap_symlink, true);
    will_return(__wrap_symlink, errnos[i]);

    const f_status_t status = f_file_link(path, path);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_link__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_link(f_string_empty_s, f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_link(path, f_string_empty_s);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_link(f_string_empty_s, path);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_link__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_symlink, false);
    will_return(__wrap_symlink, 0);

    const f_status_t status = f_file_link(path, path);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

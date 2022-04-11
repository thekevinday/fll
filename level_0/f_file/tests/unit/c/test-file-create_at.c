#include "test-file.h"
#include "test-file-create_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_create_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int errnos[] = {
      EACCES,
      EBADF,
      EDQUOT,
      EEXIST,
      EFAULT,
      EFBIG,
      EINTR,
      EINVAL,
      EISDIR,
      ELOOP,
      ENAMETOOLONG,
      ENFILE,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EOPNOTSUPP,
      EOVERFLOW,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_directory_descriptor,
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_number_overflow,
      F_interrupt,
      F_parameter,
      F_directory,
      F_loop,
      F_name,
      F_file_open_max,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_file_type_not_directory,
      F_supported_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    for (int i = 0; i < 22; ++i) {

      will_return(__wrap_openat, true);
      will_return(__wrap_openat, errnos[i]);

      const f_status_t status = f_file_create_at(0, path, 0, F_false);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EBADF,
      EDQUOT,
      EIO,
      ENOSPC,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_synchronize,
      F_file_synchronize,
      F_file_synchronize,
      F_file_synchronize,
      F_file_synchronize,
      F_file_synchronize,
    };

    for (int i = 0; i < 6; ++i) {

      will_return(__wrap_openat, false);
      will_return(__wrap_openat, 0);

      will_return(__wrap_fsync, true);
      will_return(__wrap_fsync, errnos[i]);

      const f_status_t status = f_file_create_at(0, path, 0, F_false);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EBADF,
      EINTR,
      EIO,
      ENOSPC,
      EDQUOT,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_descriptor,
      F_interrupt,
      F_input_output,
      F_space_not,
      F_filesystem_quota_block,
      F_file_close,
    };

    for (int i = 0; i < 6; ++i) {

      will_return(__wrap_openat, false);
      will_return(__wrap_openat, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, true);
      will_return(__wrap_close, errnos[i]);

      const f_status_t status = f_file_create_at(0, path, 0, F_false);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
}

void test__f_file_create_at__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_create_at(0, f_string_empty_s, 0, F_false);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_create_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_openat, false);
    will_return(__wrap_openat, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_create_at(0, path, 0, F_false);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

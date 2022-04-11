#include "test-file.h"
#include "test-file-touch.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_touch__fails(void **state) {
/*
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      ELOOP,
      ENAMETOOLONG,
      ENOMEM,
      ENOTDIR,
      EOVERFLOW,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_loop,
      F_name,
      F_memory_not,
      F_file_not,
      F_number_overflow,
      F_file_stat,
    };

    for (int i = 0; i < 8; ++i) {

      will_return(__wrap_stat, true);
      will_return(__wrap_stat, errnos[i]);

      const f_status_t status = f_file_touch(path, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
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
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_parameter,
      F_loop,
      F_file_link_max,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_file_not,
      F_prohibited,
      F_read_only,
      F_failure,
    };

    for (int i = 0; i < 15; ++i) {

      will_return(__wrap_stat, true);
      will_return(__wrap_stat, ENOENT);
      will_return(__wrap_mkdir, true);
      will_return(__wrap_mkdir, errnos[i]);

      const f_status_t status = f_file_touch(path, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  } // for

  {
    int errnos[] = {
      EACCES,
      EBADF,
      EFAULT,
      EINVAL,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOTDIR,
      EPERM,
      EROFS,
      ESRCH,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_file_descriptor,
      F_buffer,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_file_not,
      F_prohibited,
      F_read_only,
      F_search,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof (struct stat));

    statistics.st_mode = 1 | F_file_type_directory_d;

    for (int i = 0; i < 12; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);
      will_return(__wrap_utimensat, true);
      will_return(__wrap_utimensat, errnos[i]);

      const f_status_t status = f_file_touch(path, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
  */
}

void test__f_file_touch__returns_data_not(void **state) {
/*
  {
    const f_status_t status = f_file_touch(f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }
  */
}

void test__f_file_touch__works(void **state) {
/*
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof (struct stat));

    statistics.st_mode = 1 | F_file_type_directory_d;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);
    will_return(__wrap_utimensat, false);
    will_return(__wrap_utimensat, 0);

    const f_status_t status = f_file_touch(path, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_stat, true);
    will_return(__wrap_stat, ENOENT);
    will_return(__wrap_mkdir, false);
    will_return(__wrap_mkdir, 0);

    const f_status_t status = f_file_touch(path, 0);

    assert_int_equal(status, F_none);
  }
  */
}

#ifdef __cplusplus
} // extern "C"
#endif

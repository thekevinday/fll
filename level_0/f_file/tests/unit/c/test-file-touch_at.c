#include "test-file.h"
#include "test-file-touch_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_touch_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);
  const mode_t mode = 0;

  {
    int errnos[] = {
      EACCES,
      EBADF,
      EFAULT,
      EINVAL,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EOVERFLOW,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_directory_descriptor,
      F_buffer,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_number_overflow,
      F_file_stat,
    };

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_fstatat, true);
      will_return(__wrap_fstatat, errnos[i]);

      if (statuss[i] == F_file_found_not) {
        will_return(__wrap_openat, false);
        will_return(__wrap_openat, 0);

        will_return(__wrap_fsync, false);
        will_return(__wrap_fsync, 0);

        will_return(__wrap_close, false);
        will_return(__wrap_close, 0);
      }

      const f_status_t status = f_file_touch_at(1, path, mode, 0);

      if (statuss[i] == F_file_found_not) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(F_status_set_fine(status), statuss[i]);
      }
    } // for
  }

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
      F_directory_descriptor,
      F_buffer,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_search,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_directory_d;

    for (int i = 0; i < 12; ++i) {

      will_return(__wrap_fstatat, false);
      will_return(__wrap_fstatat, &statistics);
      will_return(__wrap_fstatat, 0);

      will_return(__wrap_utimensat, true);
      will_return(__wrap_utimensat, errnos[i]);

      const f_status_t status = f_file_touch_at(1, path, mode, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
}

void test__f_file_touch_at__returns_data_not(void **state) {

  const mode_t mode = 0;

  {
    const f_status_t status = f_file_touch_at(1, f_string_empty_s, mode, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_touch_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);
  const mode_t mode = 0;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_directory_d;

    will_return(__wrap_fstatat, false);
    will_return(__wrap_fstatat, &statistics);
    will_return(__wrap_fstatat, 0);

    will_return(__wrap_utimensat, false);
    will_return(__wrap_utimensat, 0);

    const f_status_t status = f_file_touch_at(1, path, mode, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

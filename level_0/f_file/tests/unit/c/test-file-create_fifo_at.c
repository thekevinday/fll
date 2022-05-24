#include "test-file.h"
#include "test-file-create_fifo_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_create_fifo_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int errnos[] = {
      EACCES,
      EBADF,
      EDQUOT,
      EEXIST,
      ENAMETOOLONG,
      ENOENT,
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
      F_name,
      F_file_found_not,
      F_space_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_failure,
    };

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_mkfifoat, true);
      will_return(__wrap_mkfifoat, errnos[i]);

      const f_status_t status = f_file_create_fifo_at(0, path, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_create_fifo_at__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_create_fifo_at(0, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_create_fifo_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_mkfifoat, false);
    will_return(__wrap_mkfifoat, 0);

    const f_status_t status = f_file_create_fifo_at(0, path, 0);

    assert_int_equal(status, F_none);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

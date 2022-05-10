#include "test-file.h"
#include "test-file-size_by_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_size_by_id__fails(void **state) {

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
    F_file_descriptor,
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

    off_t size = 0;

    will_return(__wrap_fstat, true);
    will_return(__wrap_fstat, errnos[i]);

    const f_status_t status = f_file_size_by_id(0, &size);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_size_by_id__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_size_by_id(0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_size_by_id__returns_file_closed(void **state) {

  {
    off_t size = 0;

    const f_status_t status = f_file_size_by_id(-1, &size);

    assert_int_equal(F_status_set_fine(status), F_file_closed);
  } // for
}

void test__f_file_size_by_id__works(void **state) {

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    off_t size = 0;

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

    will_return(__wrap_fstat, false);
    will_return(__wrap_fstat, &statistics);
    will_return(__wrap_fstat, 0);

    const f_status_t status = f_file_size_by_id(0, &size);

    assert_int_equal(status, F_none);
    assert_int_equal(size, statistics.st_size);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

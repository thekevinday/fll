#include "test-file.h"
#include "test-file-seek.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_seek__fails(void **state) {

  int errnos[] = {
    EBADF,
    EINVAL,
    ENXIO,
    EOVERFLOW,
    ESPIPE,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_file_descriptor,
    F_parameter,
    F_bound_not,
    F_number_overflow,
    F_file_type_pipe,
    F_failure,
  };

  for (int i = 0; i < 6; ++i) {

    off_t seeked = 0;

    will_return(__wrap_lseek, true);
    will_return(__wrap_lseek, errnos[i]);

    const f_status_t status = f_file_seek(0, 0, 0, &seeked);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_seek__parameter_checking(void **state) {

  off_t seeked = 0;

  {
    const f_status_t status = f_file_seek(0, -1, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_file_seek(0, -1, 0, &seeked);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_file_seek(0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_seek__works(void **state) {

  {
    off_t seeked = 0;

    will_return(__wrap_lseek, false);
    will_return(__wrap_lseek, 0);

    const f_status_t status = f_file_seek(0, 0, 0, &seeked);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

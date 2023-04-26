#include "test-pipe.h"
#include "test-pipe-output_exists.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_pipe_output_exists__fails(void **state) {

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

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_fstat, true);
    will_return(__wrap_fstat, errnos[i]);

    const f_status_t status = f_pipe_output_exists();

    assert_int_equal(status, F_status_set_error(F_file_stat));
  } // for
}

void test__f_pipe_output_exists__returns_false(void **state) {

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    statistics.st_mode = 1 | S_IFREG;

    will_return(__wrap_fstat, false);
    will_return(__wrap_fstat, &statistics);
    will_return(__wrap_fstat, 0);

    const f_status_t status = f_pipe_output_exists();

    assert_int_equal(status, F_false);
  }
}

void test__f_pipe_output_exists__returns_true(void **state) {

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    statistics.st_mode = 1 | S_IFIFO;

    will_return(__wrap_fstat, false);
    will_return(__wrap_fstat, &statistics);
    will_return(__wrap_fstat, 0);

    const f_status_t status = f_pipe_output_exists();

    assert_int_equal(status, F_true);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

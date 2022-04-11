#include "test-file.h"
#include "test-file-close.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_close__fails(void **state) {

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

      int id = 0;

      will_return(__wrap_close, true);
      will_return(__wrap_close, errnos[i]);

      const f_status_t status = f_file_close(&id);

      assert_int_equal(F_status_set_fine(status), statuss[i]);

      if (errnos[i] == EBADF || errnos[i] == EINTR) {
        assert_int_equal(id, 0);
      }
      else {
        assert_int_equal(id, -1);
      }
    } // for
  }
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_close__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_close(0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_close__works(void **state) {

  {
    int id = 0;

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_close(&id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, -1);
  }
}

void test__f_file_close__works_already_closed(void **state) {

  {
    int id = -1;

    const f_status_t status = f_file_close(&id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, -1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

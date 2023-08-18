#include "test-file.h"
#include "test-file-close.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_close_id__fails(void **state) {

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

      int id = F_type_descriptor_output_d;

      will_return(__wrap_close, true);
      will_return(__wrap_close, errnos[i]);

      const f_status_t status = f_file_close_id(&id);

      assert_int_equal(status, F_status_set_error(statuss[i]));

      if (errnos[i] == EBADF || errnos[i] == EINTR) {
        assert_int_equal(id, F_type_descriptor_output_d);
      }
      else {
        assert_int_equal(id, -1);
      }
    } // for
  }
}

void test__f_file_close_id__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_close_id(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_close_id__returns_file_descriptor_not(void **state) {

  int id = -1;

  {
    const f_status_t status = f_file_close_id(&id);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_close_id__works(void **state) {

  int id = F_type_descriptor_output_d;

  {

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_close_id(&id);

    assert_int_equal(status, F_okay);
    assert_int_equal(id, -1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

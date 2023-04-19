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

      f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

      will_return(__wrap_close, true);
      will_return(__wrap_close, errnos[i]);

      const f_status_t status = f_file_close(&file);

      assert_int_equal(status, F_status_set_error(statuss[i]));

      if (errnos[i] == EBADF || errnos[i] == EINTR) {
        assert_int_equal(file.id, F_type_descriptor_output_d);
      }
      else {
        assert_int_equal(file.id, -1);
      }
    } // for
  }
}

void test__f_file_close__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_close(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_close__returns_file_descriptor_not(void **state) {

  f_file_t file = macro_f_file_t_initialize2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_close(&file);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_close__works(void **state) {

  f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_close(&file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, -1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-flush.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_flush__fails(void **state) {

  f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  int errnos[] = {
    EBADF,
    EDQUOT,
    EINVAL,
    EIO,
    ENOSPC,
    EROFS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_file_descriptor,
    F_filesystem_quota_block,
    F_support_not,
    F_input_output,
    F_space_not,
    F_support_not,
    F_file_synchronize,
  };

  for (int i = 0; i < 7; ++i) {

    will_return(__wrap_fsync, true);
    will_return(__wrap_fsync, errnos[i]);

    const f_status_t status = f_file_flush(file);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_flush__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_flush(file);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_flush__works(void **state) {

  f_file_t file = macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    const f_status_t status = f_file_flush(file);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-manipulate.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_manipulate__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    int errnos[] = {
      EACCES,
      EAGAIN,
      EBADF,
      EBUSY,
      EDEADLK,
      EFAULT,
      EINTR,
      EINVAL,
      EMFILE,
      ENOLCK,
      ENOTDIR,
      EPERM,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_again,
      F_file_descriptor,
      F_busy,
      F_deadlock,
      F_buffer,
      F_interrupt,
      F_parameter,
      F_file_descriptor_max,
      F_lock,
      F_directory_not,
      F_prohibited,
      F_failure,
    };

    for (int i = 0; i < 13; ++i) {

      will_return(__wrap_fcntl, true);
      will_return(__wrap_fcntl, errnos[i]);

      const f_status_t status = f_file_manipulate(file, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_manipulate__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_manipulate(file, 0, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_manipulate__works(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {

    will_return(__wrap_fcntl, false);

    const f_status_t status = f_file_manipulate(file, 0, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-access_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_access_at__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

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
      F_status_set_error(F_access_denied),
      F_status_set_error(F_directory_descriptor),
      F_status_set_error(F_buffer),
      F_status_set_error(F_parameter),
      F_status_set_error(F_loop),
      F_status_set_error(F_name),
      F_false,
      F_status_set_error(F_memory_not),
      F_status_set_error(F_directory_not),
      F_status_set_error(F_number_overflow),
      F_status_set_error(F_failure),
    };

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_faccessat, true);
      will_return(__wrap_faccessat, errnos[i]);

      const f_status_t status = f_file_access_at(0, path, F_file_access_mode_exist_d, 0);

      assert_int_equal(status, statuss[i]);
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
      ENOMEM,
      ENOTDIR,
      EOVERFLOW,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_false,
      F_status_set_error(F_directory_descriptor),
      F_status_set_error(F_buffer),
      F_status_set_error(F_parameter),
      F_status_set_error(F_loop),
      F_status_set_error(F_name),
      F_status_set_error(F_file_not),
      F_status_set_error(F_memory_not),
      F_status_set_error(F_directory_not),
      F_status_set_error(F_number_overflow),
      F_status_set_error(F_failure),
    };

    int modes[] = {
      F_file_access_mode_read_d,
      F_file_access_mode_write_d,
      F_file_access_mode_execute_d,
    };

    for (int j = 0; j < 3; ++j){

      for (int i = 0; i < 11; ++i) {

        will_return(__wrap_faccessat, true);
        will_return(__wrap_faccessat, errnos[i]);

        const f_status_t status = f_file_access_at(0, path, modes[j], 0);

        assert_int_equal(status, statuss[i]);
      } // for
    } // for
  }
}

void test__f_file_access_at__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_access_at(0, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_access_at__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_faccessat, false);
    will_return(__wrap_faccessat, 0);

    const f_status_t status = f_file_access_at(0, path, F_file_access_mode_exist_d, 0);

    assert_int_equal(status, F_true);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

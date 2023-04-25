#include "test-file.h"
#include "test-file-access.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_access__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    int errnos[] = {
      EACCES,
      EFAULT,
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
      F_status_set_error(F_buffer),
      F_status_set_error(F_loop),
      F_status_set_error(F_name),
      F_false,
      F_status_set_error(F_memory_not),
      F_status_set_error(F_directory_not),
      F_status_set_error(F_number_overflow),
      F_status_set_error(F_failure),
    };

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_access, true);
      will_return(__wrap_access, errnos[i]);

      const f_status_t status = f_file_access(path, F_file_access_mode_exist_d);

      assert_int_equal(status, statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
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
      F_status_set_error(F_buffer),
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

      for (int i = 0; i < 9; ++i) {

        will_return(__wrap_access, true);
        will_return(__wrap_access, errnos[i]);

        const f_status_t status = f_file_access(path, modes[j]);

        assert_int_equal(status, statuss[i]);
      } // for
    } // for
  }
}

void test__f_file_access__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_access(f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_access__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_access, false);
    will_return(__wrap_access, 0);

    const f_status_t status = f_file_access(path, F_file_access_mode_exist_d);

    assert_int_equal(status, F_true);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

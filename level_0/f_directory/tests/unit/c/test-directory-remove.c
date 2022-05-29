#include "test-directory.h"
#include "test-directory-remove.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_remove__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_busy,
    F_buffer,
    F_parameter,
    F_input_output,
    F_file_type_directory,
    F_loop,
    F_file_descriptor_max,
    F_name,
    F_file_open_max,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_directory_empty_not,
    F_prohibited,
    F_read_only,
    F_failure,
  };

  {
    for (int i = 0; i < 17; ++i) {

      will_return(__wrap_remove, true);
      will_return(__wrap_remove, errnos[i]);

      const f_status_t status = f_directory_remove(path, 0, F_false);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  {
    for (int i = 0; i < 17; ++i) {

      will_return(__wrap_nftw, false);
      will_return(__wrap_nftw, 0);
      will_return(__wrap_remove, true);
      will_return(__wrap_remove, errnos[i]);

      const f_status_t status = f_directory_remove(path, 1, F_false);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  {
    for (int i = 0; i < 17; ++i) {

      will_return(__wrap_nftw, true);
      will_return(__wrap_nftw, errnos[i]);

      const f_status_t status = f_directory_remove(path, 1, F_true);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_directory_remove__parameter_checking(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_directory_remove(path, -1, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_directory_remove__returns_data_not(void **state) {

  {
    const f_status_t status = f_directory_remove(f_string_empty_s, 0, F_false);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_directory_remove__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    will_return(__wrap_remove, false);
    will_return(__wrap_remove, 0);

    const f_status_t status = f_directory_remove(path, 0, F_false);

    assert_int_equal(status, F_none);
  }

  {
    const f_status_t status = f_directory_remove(path, 0, F_true);

    assert_int_equal(F_status_set_fine(status), F_none);
  }

  {
    will_return(__wrap_nftw, false);
    will_return(__wrap_nftw, 0);
    will_return(__wrap_remove, false);
    will_return(__wrap_remove, 0);

    const f_status_t status = f_directory_remove(path, 1, F_false);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_nftw, false);
    will_return(__wrap_nftw, 0);

    const f_status_t status = f_directory_remove(path, 1, F_true);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

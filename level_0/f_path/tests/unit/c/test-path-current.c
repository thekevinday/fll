#include "test-path.h"
#include "test-path-current.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_path_current__fails(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EINVAL,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ERANGE,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_parameter,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_buffer_too_small,
      F_failure,
    };

    for (int i = 0; i < 8; ++i) {

      will_return(__wrap_getcwd, true);
      will_return(__wrap_getcwd, errnos[i]);

      const f_status_t status = f_path_current(F_false, &destination);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  destination.used = 0;

  {
    int errnos[] = {
      EACCES,
      EINVAL,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_parameter,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory,
      F_failure,
    };

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_getcwd, false);
      will_return(__wrap_getcwd, 0);

      will_return(__wrap_realpath, true);
      will_return(__wrap_realpath, errnos[i]);

      const f_status_t status = f_path_current(F_true, &destination);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  f_string_dynamic_resize(0, &destination);
}

#ifndef _di_level_0_parameter_checking_
  void test__f_path_current__parameter_checking(void **state) {

    {
      const f_status_t status = f_path_current(F_false, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_path_current__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);
  const f_string_static_t path_real = macro_f_string_static_t_initialize("/test", 0, 5);

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    will_return(__wrap_getcwd, F_false);
    will_return(__wrap_getcwd, path.string);

    const f_status_t status = f_path_current(F_false, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, path.used);
    assert_string_equal(destination.string, path.string);
  }

  destination.used = 0;

  {
    will_return(__wrap_getcwd, F_false);
    will_return(__wrap_getcwd, path.string);

    will_return(__wrap_realpath, F_false);
    will_return(__wrap_realpath, path_real.string);

    const f_status_t status = f_path_current(F_true, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, path_real.used);
    assert_string_equal(destination.string, path_real.string);
  }

  f_string_dynamic_resize(0, &destination);
}

#ifdef __cplusplus
} // extern "C"
#endif

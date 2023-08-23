#include "test-path.h"
#include "test-path-real.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_path_real__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

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

  for (int i = 0; i < 9; ++i, destination.used = 0) {

    will_return(__wrap_realpath, true);
    will_return(__wrap_realpath, errnos[i]);

    const f_status_t status = f_path_real(path, &destination);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  free((void *) destination.string);
}

void test__f_path_real__parameter_checking(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_path_real(path, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_path_real__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_static_t path_real = macro_f_string_static_t_initialize_1("/test", 0, 5);

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    will_return(__wrap_realpath, F_false);
    will_return(__wrap_realpath, path_real.string);

    const f_status_t status = f_path_real(path, &destination);

    assert_int_equal(status, F_okay);
    assert_int_equal(destination.used, path_real.used);
    assert_string_equal(destination.string, path_real.string);
  }

  free((void *) destination.string);
}

#ifdef __cplusplus
} // extern "C"
#endif

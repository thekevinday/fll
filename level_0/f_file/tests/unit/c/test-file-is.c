#include "test-file.h"
#include "test-file-is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_is__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

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
    F_access_denied,
    F_buffer,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_false,
    F_number_overflow,
    F_file_stat,
  };

  // @todo an outer loop is needed to run this against all types.
  f_status_t types[] = {
  };

  for (int i = 0; i < 9; ++i) {

    //will_return(__wrap_stat, true);
    //will_return(__wrap_stat, errnos[i]);

    //const f_status_t status = f_file_is(path);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

void test__f_file_is__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_is(f_string_empty_s, 0, F_false);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_is__returns_false(void **state) {
/*
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof (struct stat));

  {
    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_is(path);

    assert_int_equal(status, F_false);
  }
  */
}

void test__f_file_is__returns_true(void **state) {
/*
  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof (struct stat));

  statistics.st_mode = 1 | F_file_type_directory_d;

  {
    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_is(path);

    assert_int_equal(status, F_true);
  }
  */
}

#ifdef __cplusplus
} // extern "C"
#endif

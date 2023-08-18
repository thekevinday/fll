#include "test-file.h"
#include "test-file-owner_read.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_owner_read__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

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
    F_directory_not,
    F_number_overflow,
    F_file_stat,
  };

  for (int i = 0; i < 9; ++i) {

    gid_t id = 0;

    will_return(__wrap_stat, true);
    will_return(__wrap_stat, errnos[i]);

    const f_status_t status = f_file_owner_read(path, F_true, &id);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_owner_read__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_owner_read(f_string_empty_s, F_false, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_owner_read__returns_data_not(void **state) {

  {
    gid_t id = 0;

    const f_status_t status = f_file_owner_read(f_string_empty_s, F_false, &id);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_owner_read__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    gid_t id = 0;

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_uid = 5;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    const f_status_t status = f_file_owner_read(path, F_true, &id);

    assert_int_equal(status, F_okay);
    assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

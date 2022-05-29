#include "test-file.h"
#include "test-file-link.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_link_read__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EFAULT,
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
    F_buffer,
    F_parameter,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_failure,
  };

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  statistics.st_size = 1;

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  for (int i = 0; i < 10; ++i) {

    buffer.used = 0;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_readlink, true);
    will_return(__wrap_readlink, errnos[i]);

    const f_status_t status = f_file_link_read(path, F_true, &buffer);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read__parameter_checking(void **state) {

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_link_read(f_string_empty_s, F_true, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read__returns_data_not(void **state) {


  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  statistics.st_size = 1;

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  {
    const f_status_t status = f_file_link_read(f_string_empty_s, F_true, &buffer);

    assert_int_equal(status, F_data_not);
  }

  f_string_dynamic_resize(0, &buffer);
}

void test__f_file_link_read__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  statistics.st_size = 1;

  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

  char source[2] = { 'x', 0 };

  {
    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_readlink, false);
    will_return(__wrap_readlink, source);
    will_return(__wrap_readlink, 0);

    const f_status_t status = f_file_link_read(path, F_true, &buffer);

    assert_int_equal(status, F_none);
  }

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif

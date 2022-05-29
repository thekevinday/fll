#include "test-file.h"
#include "test-file-stream_open.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stream_open__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  int errnos[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    ENAMETOOLONG,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    ELOOP,
    ENFILE,
    ENOENT,
    ENOTDIR,
    ENOMEM,
    ENOSPC,
    EPERM,
    EROFS,
    ETXTBSY,
    EISDIR,
    EOPNOTSUPP,
    EOVERFLOW,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_filesystem_quota_block,
    F_file_found,
    F_name,
    F_buffer,
    F_number_overflow,
    F_interrupt,
    F_parameter,
    F_loop,
    F_file_open_max,
    F_file_found_not,
    F_file_type_not_directory,
    F_memory_not,
    F_space_not,
    F_prohibited,
    F_read_only,
    F_busy,
    F_directory,
    F_supported_not,
    F_number_overflow,
    F_failure,
  };

  for (int i = 0; i < 21; ++i) {

    f_file_t file = f_file_t_initialize;

    will_return(__wrap_fopen, true);
    will_return(__wrap_fopen, errnos[i]);

    const f_status_t status = f_file_stream_open(path, path, &file);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  for (int i = 0; i < 21; ++i) {

    f_file_t file = f_file_t_initialize;

    will_return(__wrap_fopen, true);
    will_return(__wrap_fopen, errnos[i]);

    const f_status_t status = f_file_stream_open(path, f_string_empty_s, &file);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_stream_open__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_stream_open(f_string_empty_s, f_string_empty_s, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_stream_open__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    f_file_t file = f_file_t_initialize;

    const f_status_t status = f_file_stream_open(f_string_empty_s, path, &file);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stream_open__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);
  const int id = 1;

  {
    f_file_t file = f_file_t_initialize;

    will_return(__wrap_fopen, false);
    will_return(__wrap_fopen, F_type_output_d);

    will_return(__wrap_fileno, id);

    const f_status_t status = f_file_stream_open(path, path, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.stream, F_type_output_d);
  }

  {
    f_file_t file = f_file_t_initialize;

    will_return(__wrap_fopen, false);
    will_return(__wrap_fopen, F_type_output_d);

    will_return(__wrap_fileno, id);

    const f_status_t status = f_file_stream_open(path, f_string_empty_s, &file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.stream, F_type_output_d);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-size_by_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_size_by_id__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

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
    F_access_denied,
    F_file_descriptor,
    F_buffer,
    F_parameter,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_number_overflow,
    F_file_stat,
  };

  for (int i = 0; i < 11; ++i) {

    off_t size = 0;

    will_return(__wrap_fstat, true);
    will_return(__wrap_fstat, errnos[i]);

    const f_status_t status = f_file_size_by_id(file, &size);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_size_by_id__parameter_checking(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_size_by_id(file, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_size_by_id__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    off_t size = 0;

    const f_status_t status = f_file_size_by_id(file, &size);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_size_by_id__works(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  struct stat statistics;

  memset(&statistics, 0, sizeof(struct stat));

  {
    off_t size = 0;

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

    will_return(__wrap_fstat, false);
    will_return(__wrap_fstat, &statistics);
    will_return(__wrap_fstat, 0);

    const f_status_t status = f_file_size_by_id(file, &size);

    assert_int_equal(status, F_okay);
    assert_int_equal(size, statistics.st_size);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

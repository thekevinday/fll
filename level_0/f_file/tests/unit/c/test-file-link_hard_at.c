#include "test-file.h"
#include "test-file-link.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_link_hard_at__fails(void **state) {

  const f_file_t target = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_file_t point = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EOVERFLOW,
    EPERM,
    EROFS,
    ETXTBSY,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_file_descriptor,
    F_filesystem_quota_block,
    F_file_found,
    F_buffer,
    F_number_overflow,
    F_interrupt,
    F_parameter,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_space_not,
    F_directory_not,
    F_number_overflow,
    F_prohibited,
    F_read_only,
    F_busy,
    F_failure,
  };

  for (int i = 0; i < 19; ++i) {

    will_return(__wrap_linkat, true);
    will_return(__wrap_linkat, errnos[i]);

    const f_status_t status = f_file_link_hard_at(target, point, path, path, 0);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_link_hard_at__returns_data_not(void **state) {

  const f_file_t target = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_file_t point = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_link_hard_at(target, point, f_string_empty_s, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_link_hard_at(target, point, path, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_link_hard_at(target, point, f_string_empty_s, path, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_link_hard_at__returns_file_descriptor_not(void **state) {

  f_file_t target = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);
  f_file_t point = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_link_hard_at(target, point, path, path, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }

  {
    target.id = F_type_descriptor_output_d;
    point.id = -1;

    const f_status_t status = f_file_link_hard_at(target, point, path, path, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_link_hard_at__works(void **state) {

  const f_file_t target = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_file_t point = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_linkat, false);
    will_return(__wrap_linkat, 0);

    const f_status_t status = f_file_link_hard_at(target, point, path, path, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

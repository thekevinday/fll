#include "test-file.h"
#include "test-file-rename_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_rename_at__fails(void **state) {

  const f_file_t source = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_file_t destination = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EBUSY,
    EDQUOT,
    EFAULT,
    EINVAL,
    EISDIR,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EEXIST,
    EPERM,
    EROFS,
    EXDEV,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_directory_descriptor,
    F_busy,
    F_filesystem_quota_block,
    F_buffer,
    F_parameter,
    F_file_type_directory,
    F_loop,
    F_link,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_space_not,
    F_directory_not,
    F_directory_empty_not,
    F_directory_empty_not,
    F_prohibited,
    F_read_only,
    F_mount,
    F_failure,
  };

  {
    for (int i = 0; i < 20; ++i) {

      #ifdef _f_file_rename_use_renameat2_
        will_return(__wrap_renameat2, true);
        will_return(__wrap_renameat2, errnos[i]);
      #else
        will_return(__wrap_renameat, true);
        will_return(__wrap_renameat, errnos[i]);
      #endif // _f_file_rename_use_renameat2_

      const f_status_t status = f_file_rename_at(source, destination, path, path, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_rename_at__returns_data_not(void **state) {

  const f_file_t source = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_file_t destination = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_rename_at(source, destination, f_string_empty_s, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_rename_at(source, destination, path, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_rename_at(source, destination, f_string_empty_s, path, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_rename_at__returns_file_descriptor_not(void **state) {

  f_file_t source = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);
  f_file_t destination = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_rename_at(source, destination, path, path, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }

  {
    source.id = F_type_descriptor_output_d;
    destination.id = -1;

    const f_status_t status = f_file_rename_at(source, destination, path, path, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_rename_at__works(void **state) {

  const f_file_t source = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_file_t destination = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    #ifdef _f_file_rename_use_renameat2_
      will_return(__wrap_renameat2, false);
      will_return(__wrap_renameat2, 0);
    #else
      will_return(__wrap_renameat, false);
      will_return(__wrap_renameat, 0);
    #endif // _f_file_rename_use_renameat2_

    const f_status_t status = f_file_rename_at(source, destination, path, path, 0);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

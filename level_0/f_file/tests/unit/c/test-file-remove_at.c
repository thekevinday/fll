#include "test-file.h"
#include "test-file-remove_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_remove_at__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EBUSY,
    EFAULT,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_directory_descriptor,
    F_busy,
    F_buffer,
    F_input_output,
    F_file_type_directory,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_prohibited,
    F_read_only,
    F_failure,
  };

  {
    for (int i = 0; i < 14; ++i) {

      will_return(__wrap_unlinkat, true);
      will_return(__wrap_unlinkat, errnos[i]);

      const f_status_t status = f_file_remove_at(file, path, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_remove_at__returns_data_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_remove_at(file, f_string_empty_s, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_remove_at__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_remove_at(file, f_string_empty_s, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_remove_at__works(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_unlinkat, false);
    will_return(__wrap_unlinkat, 0);

    const f_status_t status = f_file_remove_at(file, path, 0);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

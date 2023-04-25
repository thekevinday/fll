#include "test-file.h"
#include "test-file-role_change_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_role_change_at__fails_for_dereference(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t status_owners[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_access_owner,
    F_read_only,
    F_failure,
  };

  f_status_t status_groups[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_access_group,
    F_read_only,
    F_failure,
  };

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, 0, 0, 0);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, 0, 0, 0);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, -1, 0, 0);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, 0, -1, 0);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for
}

void test__f_file_role_change_at__fails_for_reference(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EPERM,
    EROFS,
    mock_errno_generic,
  };

  f_status_t status_owners[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_access_owner,
    F_read_only,
    F_failure,
  };

  f_status_t status_groups[] = {
    F_access_denied,
    F_directory_descriptor,
    F_buffer,
    F_input_output,
    F_loop,
    F_name,
    F_file_found_not,
    F_memory_not,
    F_directory_not,
    F_access_group,
    F_read_only,
    F_failure,
  };

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, 0, 0, F_file_at_symlink_follow_no_d);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, 0, 0, F_file_at_symlink_follow_no_d);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, -1, 0, F_file_at_symlink_follow_no_d);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 12; ++i) {

    will_return(__wrap_fchownat, true);
    will_return(__wrap_fchownat, errnos[i]);

    const f_status_t status = f_file_role_change_at(file, path, 0, -1, F_file_at_symlink_follow_no_d);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for
}

void test__f_file_role_change_at__returns_data_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_role_change_at(file, f_string_empty_s, -1, -1, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_role_change_at(file, path, -1, -1, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_role_change_at(file, f_string_empty_s, 0, 0, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_role_change_at__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_role_change_at(file, path, 0, 0, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_role_change_at__works_for_dereference(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    const f_status_t status = f_file_role_change_at(file, path, 0, 0, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    const f_status_t status = f_file_role_change_at(file, path, -1, 0, 0);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    const f_status_t status = f_file_role_change_at(file, path, 0, -1, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_role_change_at__works_for_reference(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    const f_status_t status = f_file_role_change_at(file, path, 0, 0, F_file_at_symlink_follow_no_d);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    const f_status_t status = f_file_role_change_at(file, path, -1, 0, F_file_at_symlink_follow_no_d);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_fchownat, false);
    will_return(__wrap_fchownat, 0);

    const f_status_t status = f_file_role_change_at(file, path, 0, -1, F_file_at_symlink_follow_no_d);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

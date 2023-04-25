#include "test-file.h"
#include "test-file-role_change.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_role_change__fails_for_dereference(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
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

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_chown, true);
    will_return(__wrap_chown, errnos[i]);

    const f_status_t status = f_file_role_change(path, 0, 0, F_true);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_chown, false);
    will_return(__wrap_chown, 0);

    will_return(__wrap_chown, true);
    will_return(__wrap_chown, errnos[i]);

    const f_status_t status = f_file_role_change(path, 0, 0, F_true);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_chown, true);
    will_return(__wrap_chown, errnos[i]);

    const f_status_t status = f_file_role_change(path, -1, 0, F_true);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_chown, true);
    will_return(__wrap_chown, errnos[i]);

    const f_status_t status = f_file_role_change(path, 0, -1, F_true);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for
}

void test__f_file_role_change__fails_for_reference(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
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

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_lchown, true);
    will_return(__wrap_lchown, errnos[i]);

    const f_status_t status = f_file_role_change(path, 0, 0, F_false);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_lchown, false);
    will_return(__wrap_lchown, 0);

    will_return(__wrap_lchown, true);
    will_return(__wrap_lchown, errnos[i]);

    const f_status_t status = f_file_role_change(path, 0, 0, F_false);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_lchown, true);
    will_return(__wrap_lchown, errnos[i]);

    const f_status_t status = f_file_role_change(path, -1, 0, F_false);

    assert_int_equal(F_status_set_fine(status), status_groups[i]);
  } // for

  for (int i = 0; i < 11; ++i) {

    will_return(__wrap_lchown, true);
    will_return(__wrap_lchown, errnos[i]);

    const f_status_t status = f_file_role_change(path, 0, -1, F_false);

    assert_int_equal(F_status_set_fine(status), status_owners[i]);
  } // for
}

void test__f_file_role_change__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    const f_status_t status = f_file_role_change(f_string_empty_s, -1, -1, F_true);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_role_change(path, -1, -1, F_true);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_role_change(f_string_empty_s, 0, 0, F_true);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_role_change__works_for_dereference(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_chown, false);
    will_return(__wrap_chown, 0);

    will_return(__wrap_chown, false);
    will_return(__wrap_chown, 0);

    const f_status_t status = f_file_role_change(path, 0, 0, F_true);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_chown, false);
    will_return(__wrap_chown, 0);

    const f_status_t status = f_file_role_change(path, -1, 0, F_true);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_chown, false);
    will_return(__wrap_chown, 0);

    const f_status_t status = f_file_role_change(path, 0, -1, F_true);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_role_change__works_for_reference(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_lchown, false);
    will_return(__wrap_lchown, 0);

    will_return(__wrap_lchown, false);
    will_return(__wrap_lchown, 0);

    const f_status_t status = f_file_role_change(path, 0, 0, F_false);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_lchown, false);
    will_return(__wrap_lchown, 0);

    const f_status_t status = f_file_role_change(path, -1, 0, F_false);

    assert_int_equal(status, F_none);
  }

  {
    will_return(__wrap_lchown, false);
    will_return(__wrap_lchown, 0);

    const f_status_t status = f_file_role_change(path, 0, -1, F_false);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

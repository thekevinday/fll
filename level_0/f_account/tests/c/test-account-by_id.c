#include "test-account.h"
#include "test-account-by_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_account_by_id__fails(void **state) {

  const long size = 20;
  uid_t uid = 0;
  f_account_t account = f_account_t_initialize;

  int errnos[] = {
    EINTR,
    EIO,
    EMFILE,
    ENFILE,
    ENOMEM,
    ERANGE,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_interrupt,
    F_input_output,
    F_file_descriptor_max,
    F_file_open_max,
    F_memory_not,
    F_buffer_too_small,
    F_failure,
  };

  for (int i = 0; i < 7; ++i) {

    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwuid_r, true);
    will_return(__wrap_getpwuid_r, errnos[i]);

    const f_status_t status = f_account_by_id(uid, &account);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for

  macro_f_account_t_delete_simple(account);
}

void test__f_account_by_id__not_found(void **state) {

  const long size = 20;
  struct passwd password;
  uid_t uid = 0;
  f_account_t account = f_account_t_initialize;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwuid_r, false);
    will_return(__wrap_getpwuid_r, &password);
    will_return(__wrap_getpwuid_r, (struct passwd *) 0);

    const f_status_t status = f_account_by_id(uid, &account);

    assert_int_equal(status, F_exist_not);
  }

  macro_f_account_t_delete_simple(account);
}

#ifndef _di_level_0_parameter_checking_
  void test__f_account_by_id__parameter_checking(void **state) {

    {
      const f_status_t status = f_account_by_id(0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_account_by_id__works(void **state) {

  const long size = 20;
  struct passwd password;
  struct passwd pointer;
  uid_t uid = 1;
  f_account_t account = f_account_t_initialize;

  password.pw_uid = uid;
  password.pw_gid = 2;
  password.pw_dir = "pw_dir";
  password.pw_gecos = "pw_gecos";
  password.pw_name = "pw_name";
  password.pw_passwd = "pw_passwd";
  password.pw_shell = "pw_shell";

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwuid_r, false);
    will_return(__wrap_getpwuid_r, &password);
    will_return(__wrap_getpwuid_r, &pointer);

    const f_status_t status = f_account_by_id(uid, &account);

    assert_int_equal(status, F_none);
    assert_int_equal(account.id_user, password.pw_uid);
    assert_int_equal(account.id_group, password.pw_gid);
    assert_string_equal(account.home.string, password.pw_dir);
    assert_string_equal(account.label.string, password.pw_gecos);
    assert_string_equal(account.name.string, password.pw_name);
    assert_string_equal(account.password.string, password.pw_passwd);
    assert_string_equal(account.shell.string, password.pw_shell);
  }

  macro_f_account_t_delete_simple(account);
}

#ifdef __cplusplus
} // extern "C"
#endif

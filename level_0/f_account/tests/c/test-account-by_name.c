#include "test-account.h"
#include "test-account-by_name.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_account_by_name__not_found(void **state) {

  const long size = 20;
  struct passwd password;
  char *name = "the_name";
  f_account_t account = f_account_t_initialize;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwnam_r, false);
    will_return(__wrap_getpwnam_r, &password);
    will_return(__wrap_getpwnam_r, (struct passwd *) 0);

    const f_status_t status = f_account_by_name(name, &account);

    assert_int_equal(status, F_exist_not);
  }

  macro_f_account_t_delete_simple(account);
}

void test__f_account_by_name__works(void **state) {

  const long size = 20;
  struct passwd password;
  struct passwd pointer;
  char *name = "the_name";
  f_account_t account = f_account_t_initialize;

  password.pw_uid = 1;
  password.pw_gid = 2;
  password.pw_dir = "pw_dir";
  password.pw_gecos = "pw_gecos";
  password.pw_name = name;
  password.pw_passwd = "pw_passwd";
  password.pw_shell = "pw_shell";

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwnam_r, false);
    will_return(__wrap_getpwnam_r, &password);
    will_return(__wrap_getpwnam_r, &pointer);

    const f_status_t status = f_account_by_name(name, &account);

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

void test__f_account_by_name__fails(void **state) {

  const long size = 20;
  char *name = "the_name";
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
    will_return(__wrap_getpwnam_r, true);
    will_return(__wrap_getpwnam_r, errnos[i]);

    const f_status_t status = f_account_by_name(name, &account);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for

  macro_f_account_t_delete_simple(account);
}

#ifdef __cplusplus
} // extern "C"
#endif

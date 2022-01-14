#include "test-account.h"
#include "test-account-name_user_by_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_account_name_user_by_id__not_found(void **state) {

  const long size = 20;
  struct passwd password;
  uid_t uid = 0;
  f_string_dynamic_t name = f_string_dynamic_t_initialize;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwuid_r, false);
    will_return(__wrap_getpwuid_r, &password);
    will_return(__wrap_getpwuid_r, (struct passwd *) 0);

    const f_status_t status = f_account_name_user_by_id(uid, &name);

    assert_int_equal(status, F_exist_not);
  }

  f_string_dynamic_resize(0, &name);
}

void test__f_account_name_user_by_id__works(void **state) {

  const long size = 20;
  struct passwd password;
  struct passwd pointer;
  uid_t uid = 0;
  f_string_dynamic_t name = f_string_dynamic_t_initialize;

  password.pw_uid = 1;
  password.pw_gid = 2;
  password.pw_dir = "pw_dir";
  password.pw_gecos = "pw_gecos";
  password.pw_name = "the_name";
  password.pw_passwd = "pw_passwd";
  password.pw_shell = "pw_shell";

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwuid_r, false);
    will_return(__wrap_getpwuid_r, &password);
    will_return(__wrap_getpwuid_r, &pointer);

    const f_status_t status = f_account_name_user_by_id(uid, &name);

    assert_int_equal(status, F_none);
    assert_string_equal(name.string, password.pw_name);
  }

  f_string_dynamic_resize(0, &name);
}

void test__f_account_name_user_by_id__fails(void **state) {

  const long size = 20;
  uid_t uid = 0;
  f_string_dynamic_t name = f_string_dynamic_t_initialize;

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

    const f_status_t status = f_account_name_user_by_id(uid, &name);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for

  f_string_dynamic_resize(0, &name);
}

#ifdef __cplusplus
} // extern "C"
#endif

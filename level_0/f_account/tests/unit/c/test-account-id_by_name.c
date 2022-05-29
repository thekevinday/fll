#include "test-account.h"
#include "test-account-id_by_name.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_account_id_by_name__fails(void **state) {

  const long size = 20;
  uid_t uid = 0;

  f_string_t name_string = "name";
  f_string_static_t name = f_string_static_t_initialize;
  name.string = name_string;
  name.used = 4;

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

    const f_status_t status = f_account_id_by_name(name, &uid);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_account_id_by_name__not_found(void **state) {

  const long size = 20;
  struct passwd password;
  uid_t uid = 0;

  f_string_t name_string = "name";
  f_string_static_t name = f_string_static_t_initialize;
  name.string = name_string;
  name.used = 4;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwnam_r, false);
    will_return(__wrap_getpwnam_r, &password);
    will_return(__wrap_getpwnam_r, (struct passwd *) 0);

    const f_status_t status = f_account_id_by_name(name, &uid);

    assert_int_equal(status, F_exist_not);
  }
}

void test__f_account_id_by_name__parameter_checking(void **state) {

  const f_string_static_t name = f_string_static_t_initialize;

  {
    const f_status_t status = f_account_id_by_name(name, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_account_id_by_name__works(void **state) {

  const long size = 20;
  struct passwd password;
  struct passwd pointer;
  uid_t uid = 0;

  f_string_static_t name = f_string_static_t_initialize;

  password.pw_uid = 1;
  password.pw_gid = 2;
  password.pw_dir = "pw_dir";
  password.pw_gecos = "pw_gecos";
  password.pw_name = "the_name";
  password.pw_passwd = "pw_passwd";
  password.pw_shell = "pw_shell";

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getpwnam_r, false);
    will_return(__wrap_getpwnam_r, &password);
    will_return(__wrap_getpwnam_r, &pointer);

    name.string = password.pw_name;
    name.used = strlen(password.pw_name);

    const f_status_t status = f_account_id_by_name(name, &uid);

    assert_int_equal(status, F_none);
    assert_int_equal(uid, password.pw_uid);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

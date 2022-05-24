#include "test-account.h"
#include "test-account-group_id_by_name.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_account_group_id_by_name__fails(void **state) {

  const long size = 20;
  gid_t gid = 0;

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
    will_return(__wrap_getgrnam_r, true);
    will_return(__wrap_getgrnam_r, errnos[i]);

    const f_status_t status = f_account_group_id_by_name(name, &gid);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_account_group_id_by_name__not_found(void **state) {

  const long size = 20;
  struct group group_data;
  gid_t gid = 0;

  f_string_t name_string = "name";
  f_string_static_t name = f_string_static_t_initialize;
  name.string = name_string;
  name.used = 4;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getgrnam_r, false);
    will_return(__wrap_getgrnam_r, &group_data);
    will_return(__wrap_getgrnam_r, (struct group *) 0);

    const f_status_t status = f_account_group_id_by_name(name, &gid);

    assert_int_equal(status, F_exist_not);
  }
}

#ifndef _di_level_0_parameter_checking_
  void test__f_account_group_id_by_name__parameter_checking(void **state) {

    const f_string_static_t name = f_string_static_t_initialize;

    {
      const f_status_t status = f_account_group_id_by_name(name, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_account_group_id_by_name__works(void **state) {

  const long size = 20;
  struct group group_data;
  struct group pointer;
  char *pointers[] = { "gr_mem", 0 };
  gid_t gid = 0;

  f_string_static_t name = f_string_static_t_initialize;

  group_data.gr_gid = 1;
  group_data.gr_name = "gr_name";
  group_data.gr_passwd = "gr_passwd";
  group_data.gr_mem = pointers;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getgrnam_r, false);
    will_return(__wrap_getgrnam_r, &group_data);
    will_return(__wrap_getgrnam_r, &pointer);

    name.string = group_data.gr_name;
    name.used = strlen(group_data.gr_name);

    const f_status_t status = f_account_group_id_by_name(name, &gid);

    assert_int_equal(status, F_none);
    assert_int_equal(gid, group_data.gr_gid);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

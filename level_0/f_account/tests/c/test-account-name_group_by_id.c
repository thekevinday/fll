#include "test-account.h"
#include "test-account-name_group_by_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_account_name_group_by_id__not_found(void **state) {

  const long size = 20;
  struct group group_data;
  gid_t gid = 0;
  f_string_dynamic_t name = f_string_dynamic_t_initialize;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getgrgid_r, false);
    will_return(__wrap_getgrgid_r, &group_data);
    will_return(__wrap_getgrgid_r, (struct group *) 0);

    const f_status_t status = f_account_name_group_by_id(gid, &name);

    assert_int_equal(status, F_exist_not);
  }

  f_string_dynamic_resize(0, &name);
}

void test__f_account_name_group_by_id__works(void **state) {

  const long size = 20;
  struct group group_data;
  struct group pointer;
  char *pointers[] = { "gr_mem", 0 };
  gid_t gid = 0;
  f_string_dynamic_t name = f_string_dynamic_t_initialize;

  group_data.gr_gid = 1;
  group_data.gr_name = "gr_name";
  group_data.gr_passwd = "gr_passwd";
  group_data.gr_mem = pointers;

  {
    will_return(__wrap_sysconf, size);
    will_return(__wrap_getgrgid_r, false);
    will_return(__wrap_getgrgid_r, &group_data);
    will_return(__wrap_getgrgid_r, &pointer);

    const f_status_t status = f_account_name_group_by_id(gid, &name);

    assert_int_equal(status, F_none);
    assert_string_equal(name.string, group_data.gr_name);
  }

  f_string_dynamic_resize(0, &name);
}

void test__f_account_name_group_by_id__fails(void **state) {

  const long size = 20;
  gid_t gid = 0;
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
    will_return(__wrap_getgrgid_r, true);
    will_return(__wrap_getgrgid_r, errnos[i]);

    const f_status_t status = f_account_name_group_by_id(gid, &name);

    assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for

  f_string_dynamic_resize(0, &name);
}

#ifdef __cplusplus
} // extern "C"
#endif

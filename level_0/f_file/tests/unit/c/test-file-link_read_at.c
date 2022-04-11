#include "test-file.h"
#include "test-file-link_read_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_link_read_at__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_link_read_at(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_link_read_at__parameter_checking(void **state) {

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    {
      const f_status_t status = f_file_link_read_at(0, f_string_empty_s, statistics, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_link_read_at__returns_data_not(void **state) {

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

  {
    f_string_dynamic_t string = f_string_dynamic_t_initialize;

    const f_status_t status = f_file_link_read_at(0, f_string_empty_s, statistics, &string);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_link_read_at__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_link_read_at();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

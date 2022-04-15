#include "test-file.h"
#include "test-file-stat_at.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stat_at__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_stat_at(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stat_at__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_stat_at(0, f_string_empty_s, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stat_at__returns_data_not(void **state) {

  {
    struct stat statistics;

    const f_status_t status = f_file_stat_at(0, f_string_empty_s, 0, &statistics);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stat_at__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_stat_at();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
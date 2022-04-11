#include "test-file.h"
#include "test-file-stat.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_stat__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_stat(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

#ifndef _di_level_0_parameter_checking_
  void test__f_file_stat__parameter_checking(void **state) {

    {
      const f_status_t status = f_file_stat(f_string_empty_s, F_false, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_file_stat__returns_data_not(void **state) {

  {
    struct stat statistics;

    const f_status_t status = f_file_stat(f_string_empty_s, F_false, &statistics);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_stat__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_stat();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

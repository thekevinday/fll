#include "test-file.h"
#include "test-file-mode_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_mode_set__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_mode_set(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

void test__f_file_mode_set__returns_data_not(void **state) {

  {
    //const f_status_t status = f_file_mode_set(f_string_empty_s);

    //assert_int_equal(status, F_data_not);
  }
}

void test__f_file_mode_set__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_mode_set();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-file.h"
#include "test-file-umask_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_umask_get__fails(void **state) {

  int errnos[] = {
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_failure,
  };

  for (int i = 0; i < 1; ++i) {

    //will_return(__wrap_open, true);
    //will_return(__wrap_open, errnos[i]);

    //const f_status_t status = f_file_umask_get(path, F_false, &id);

    //assert_int_equal(F_status_set_fine(status), statuss[i]);
  } // for
}

void test__f_file_umask_get__returns_data_not(void **state) {

  {
    //const f_status_t status = f_file_umask_get(f_string_empty_s);

    //assert_int_equal(status, F_data_not);
  }
}

void test__f_file_umask_get__works(void **state) {

  {
    //will_return(__wrap_open, false);
    //will_return(__wrap_open, 5);

    //const f_status_t status = f_file_umask_get();

    //assert_int_equal(status, F_none);
    //assert_int_equal(id, 5);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

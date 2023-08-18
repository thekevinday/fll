#include "test-file.h"
#include "test-file-umask_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_umask_get__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_umask_get(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_umask_get__works(void **state) {

  {
    will_return(__wrap_umask, F_file_mode_all_rw_d);
    will_return(__wrap_umask, 0);

    mode_t mode = 0;

    const mode_t status = f_file_umask_get(&mode);

    assert_int_equal(status, F_okay);
    assert_int_equal(mode, F_file_mode_all_rw_d);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

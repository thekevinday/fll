#include "test-file.h"
#include "test-file-umask_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_umask_set__works(void **state) {

  {
    will_return(__wrap_umask, 0);

    const mode_t status = f_file_umask_set(F_file_mode_all_rw_d);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-environment.h"
#include "test-environment-clear.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_environment_clear__fails(void **state) {

  {
    will_return(__wrap_clearenv, -1);

    const f_status_t status = f_environment_clear();

    assert_int_equal(F_status_set_fine(status), F_failure);
  }
}

void test__f_environment_clear__works(void **state) {

  {
    will_return(__wrap_clearenv, 0);

    const f_status_t status = f_environment_clear();

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

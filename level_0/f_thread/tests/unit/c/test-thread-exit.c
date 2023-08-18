#include "test-thread.h"
#include "test-thread-exit.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_exit__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_exit(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_exit__works(void **state) {

  int result = 0;

  {
    will_return(__wrap_pthread_exit, 1);

    const f_status_t status = f_thread_exit(&result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, 1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

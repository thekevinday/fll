#include "test-thread.h"
#include "test-thread-barrier_wait.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_barrier_wait__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_barrier_wait(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_barrier_wait__works(void **state) {

  f_thread_barrier_t attribute = f_thread_barrier_t_initialize;
  int result = 0;

  {
    will_return(__wrap_pthread_barrier_wait, false);

    const f_status_t status = f_thread_barrier_wait(&attribute, &result);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

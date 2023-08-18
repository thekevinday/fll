#include "test-thread.h"
#include "test-thread-key_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_key_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_key_delete(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_key_delete__works(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;

  {
    will_return(__wrap_pthread_key_delete, false);

    const f_status_t status = f_thread_key_delete(&key);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

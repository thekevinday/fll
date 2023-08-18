#include "test-thread.h"
#include "test-thread-key_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_key_get__parameter_checking(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;

  {
    const f_status_t status = f_thread_key_get(key, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_key_get__works(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;
  int value = 0;
  int *value_ptr = &value;
  int expect = 1;

  {
    will_return(__wrap_pthread_getspecific, (void *) &expect);

    const f_status_t status = f_thread_key_get(key, (void *) &value_ptr);

    assert_int_equal(status, F_okay);
    assert_int_equal(value_ptr, &expect);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

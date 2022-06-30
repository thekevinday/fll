#include "test-thread.h"
#include "test-thread-attribute_concurrency_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_concurrency_get__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_attribute_concurrency_get(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_attribute_concurrency_get__works(void **state) {

  int level = 0;

  {
    will_return(__wrap_pthread_getconcurrency, 1);

    const f_status_t status = f_thread_attribute_concurrency_get(&level);

    assert_int_equal(status, F_none);
    assert_int_equal(level, 1);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

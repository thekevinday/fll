#include "test-thread.h"
#include "test-thread-attribute_concurrency_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_attribute_concurrency_set__fails(void **state) {

  int level = 0;

  int errnos[] = {
    EAGAIN,
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_setconcurrency, true);
    will_return(__wrap_pthread_setconcurrency, errnos[i]);

    const f_status_t status = f_thread_attribute_concurrency_set(level);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_attribute_concurrency_set__works(void **state) {

  int level = 0;

  {
    will_return(__wrap_pthread_setconcurrency, false);

    const f_status_t status = f_thread_attribute_concurrency_set(level);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "test-thread.h"
#include "test-thread-barrier_attribute_create.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_barrier_attribute_create__fails(void **state) {

  f_thread_barrier_attribute_t attribute = f_thread_barrier_attribute_t_initialize;

  int errnos[] = {
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_memory_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_barrierattr_init, true);
    will_return(__wrap_pthread_barrierattr_init, errnos[i]);

    const f_status_t status = f_thread_barrier_attribute_create(&attribute);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_barrier_attribute_create__parameter_checking(void **state) {

  {
    const f_status_t status = f_thread_barrier_attribute_create(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_barrier_attribute_create__works(void **state) {

  f_thread_barrier_attribute_t attribute = f_thread_barrier_attribute_t_initialize;

  {
    will_return(__wrap_pthread_barrierattr_init, false);

    const f_status_t status = f_thread_barrier_attribute_create(&attribute);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

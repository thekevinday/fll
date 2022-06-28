#include "test-thread.h"
#include "test-thread-barrier_create.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_barrier_create__fails(void **state) {

  f_thread_barrier_attribute_t attribute = f_thread_barrier_attribute_t_initialize;
  f_thread_barrier_t barrier = f_thread_barrier_t_initialize;
  int count = 0;

  int errnos[] = {
    EAGAIN,
    EBUSY,
    EINVAL,
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_busy,
    F_parameter,
    F_memory_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 5; ++i) {

    will_return(__wrap_pthread_barrier_init, true);
    will_return(__wrap_pthread_barrier_init, errnos[i]);

    const f_status_t status = f_thread_barrier_create(count, &attribute, &barrier);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_barrier_create__parameter_checking(void **state) {

  f_thread_barrier_attribute_t attribute = f_thread_barrier_attribute_t_initialize;
  int count = 0;

  {
    const f_status_t status = f_thread_barrier_create(count, &attribute, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_barrier_create__works(void **state) {

  f_thread_barrier_attribute_t attribute = f_thread_barrier_attribute_t_initialize;
  f_thread_barrier_t barrier = f_thread_barrier_t_initialize;
  int count = 0;

  {
    will_return(__wrap_pthread_barrier_init, false);

    const f_status_t status = f_thread_barrier_create(count, &attribute, &barrier);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

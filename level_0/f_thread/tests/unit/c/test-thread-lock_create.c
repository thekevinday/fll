#include "test-thread.h"
#include "test-thread-lock_create.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_lock_create__fails(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  f_thread_lock_t lock = f_thread_lock_t_initialize;

  int errnos[] = {
    EAGAIN,
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_resource_not,
    F_memory_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_rwlock_init, true);
    will_return(__wrap_pthread_rwlock_init, errnos[i]);

    const f_status_t status = f_thread_lock_create(&attribute, &lock);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_lock_create__parameter_checking(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;

  {
    const f_status_t status = f_thread_lock_create(&attribute, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_lock_create__works(void **state) {

  f_thread_lock_attribute_t attribute = f_thread_lock_attribute_t_initialize;
  f_thread_lock_t lock = f_thread_lock_t_initialize;

  {
    will_return(__wrap_pthread_rwlock_init, false);

    const f_status_t status = f_thread_lock_create(&attribute, &lock);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

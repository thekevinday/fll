#include "test-thread.h"
#include "test-thread-mutex_priority_ceiling_get.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_mutex_priority_ceiling_get__fails(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;
  int ceiling = 0;

  int errnos[] = {
    EINVAL,
    EPERM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_prohibited,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_mutex_getprioceiling, true);
    will_return(__wrap_pthread_mutex_getprioceiling, errnos[i]);

    const f_status_t status = f_thread_mutex_priority_ceiling_get(&mutex, &ceiling);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_mutex_priority_ceiling_get__parameter_checking(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;
  int ceiling = 0;

  {
    const f_status_t status = f_thread_mutex_priority_ceiling_get(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_mutex_priority_ceiling_get(&mutex, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_mutex_priority_ceiling_get(0, &ceiling);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_mutex_priority_ceiling_get__works(void **state) {

  f_thread_mutex_t mutex = f_thread_mutex_t_initialize;
  int ceiling = 0;

  {
    will_return(__wrap_pthread_mutex_getprioceiling, false);

    const f_status_t status = f_thread_mutex_priority_ceiling_get(&mutex, &ceiling);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

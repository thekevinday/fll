#include "test-thread.h"
#include "test-thread-key_set.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_key_set__fails(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;
  int value = 0;

  int errnos[] = {
    EINVAL,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_parameter,
    F_failure,
  };

  for (uint8_t i = 0; i < 2; ++i) {

    will_return(__wrap_pthread_setspecific, true);
    will_return(__wrap_pthread_setspecific, errnos[i]);

    const f_status_t status = f_thread_key_set(key, &value);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_key_set__parameter_checking(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;

  {
    const f_status_t status = f_thread_key_set(key, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_key_set__works(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;
  int value = 0;

  {
    will_return(__wrap_pthread_setspecific, false);

    const f_status_t status = f_thread_key_set(key, &value);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

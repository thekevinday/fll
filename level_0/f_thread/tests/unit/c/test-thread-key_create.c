#include "test-thread.h"
#include "test-thread-key_create.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_key_create__fails(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;

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

    will_return(__wrap_pthread_key_create, true);
    will_return(__wrap_pthread_key_create, errnos[i]);

    const f_status_t status = f_thread_key_create(stub_other, &key);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_key_create__parameter_checking(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;

  {
    const f_status_t status = f_thread_key_create(0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_key_create(stub_other, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_thread_key_create(0, &key);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_key_create__works(void **state) {

  f_thread_key_t key = f_thread_key_t_initialize;

  {
    will_return(__wrap_pthread_key_create, false);

    const f_status_t status = f_thread_key_create(stub_other, &key);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

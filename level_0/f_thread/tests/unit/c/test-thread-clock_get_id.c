#include "test-thread.h"
#include "test-thread-clock_get_id.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_clock_get_id__fails(void **state) {

  f_thread_id_t id_thread = f_thread_id_t_initialize;
  clockid_t id_clock;

  memset(&id_clock, 0, sizeof(clockid_t));

  int errnos[] = {
    ENOENT,
    ESRCH,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_support_not,
    F_found_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 3; ++i) {

    will_return(__wrap_pthread_getcpuclockid, true);
    will_return(__wrap_pthread_getcpuclockid, errnos[i]);

    const f_status_t status = f_thread_clock_get_id(id_thread, &id_clock);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_clock_get_id__parameter_checking(void **state) {

  f_thread_id_t id_thread = f_thread_id_t_initialize;

  {
    const f_status_t status = f_thread_clock_get_id(id_thread, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_clock_get_id__works(void **state) {

  f_thread_id_t id_thread = f_thread_id_t_initialize;
  clockid_t id_clock;

  memset(&id_clock, 0, sizeof(clockid_t));

  {
    will_return(__wrap_pthread_getcpuclockid, false);

    const f_status_t status = f_thread_clock_get_id(id_thread, &id_clock);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

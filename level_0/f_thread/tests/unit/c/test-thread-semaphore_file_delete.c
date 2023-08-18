#include "test-thread.h"
#include "test-thread-semaphore_file_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_file_delete__fails(void **state) {

  f_string_static_t name = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EINVAL,
    ENAMETOOLONG,
    ENOENT,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_status_set_error(F_access_denied),
    F_status_set_error(F_parameter),
    F_status_set_error(F_name_not),
    F_file_found_not,
    F_status_set_error(F_failure),
  };

  for (uint8_t i = 0; i < 5; ++i) {

    will_return(__wrap_sem_unlink, true);
    will_return(__wrap_sem_unlink, errnos[i]);

    const f_status_t status = f_thread_semaphore_file_delete(name);

    assert_int_equal(status, statuss[i]);
  } // for
}

void test__f_thread_semaphore_file_delete__works(void **state) {

  f_string_static_t name = macro_f_string_static_t_initialize_1("test", 0, 4);

  {
    will_return(__wrap_sem_unlink, false);

    const f_status_t status = f_thread_semaphore_file_delete(name);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

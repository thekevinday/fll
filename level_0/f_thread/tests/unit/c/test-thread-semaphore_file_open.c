#include "test-thread.h"
#include "test-thread-semaphore_file_open.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_thread_semaphore_file_open__fails(void **state) {

  f_string_static_t name = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  f_thread_semaphore_t *semaphore_ptr = &semaphore;
  int flag = 0;
  mode_t mode = 0;
  unsigned value = 0;

  int errnos[] = {
    EACCES,
    EEXIST,
    EINVAL,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOMEM,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_access_denied,
    F_file_found,
    F_parameter,
    F_file_descriptor_max,
    F_name_not,
    F_file_open_max,
    F_file_found_not,
    F_memory_not,
    F_failure,
  };

  for (uint8_t i = 0; i < 9; ++i) {

    semaphore_ptr = &semaphore;

    will_return(__wrap_sem_open, true);
    will_return(__wrap_sem_open, errnos[i]);

    const f_status_t status = f_thread_semaphore_file_open(name, flag, &mode, value, &semaphore_ptr);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  flag = O_CREAT;

  for (uint8_t i = 0; i < 9; ++i) {

    will_return(__wrap_sem_open, true);
    will_return(__wrap_sem_open, errnos[i]);

    const f_status_t status = f_thread_semaphore_file_open(name, flag, &mode, value, &semaphore_ptr);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_thread_semaphore_file_open__parameter_checking(void **state) {

  f_string_static_t name = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  f_thread_semaphore_t *semaphore_ptr = &semaphore;
  int flag = 0;
  mode_t mode = 0;
  unsigned value = 0;

  {
    const f_status_t status = f_thread_semaphore_file_open(name, flag, &mode, value, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    flag = O_CREAT;

    const f_status_t status = f_thread_semaphore_file_open(name, flag, 0, value, &semaphore_ptr);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_thread_semaphore_file_open__works(void **state) {

  f_string_static_t name = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_thread_semaphore_t semaphore = f_thread_semaphore_t_initialize;
  f_thread_semaphore_t *semaphore_ptr = &semaphore;
  int flag = 0;
  mode_t mode = 0;
  unsigned value = 0;

  {
    will_return(__wrap_sem_open, false);

    const f_status_t status = f_thread_semaphore_file_open(name, flag, &mode, value, &semaphore_ptr);

    assert_int_equal(status, F_okay);
  }

  {
    flag = O_CREAT;
    semaphore_ptr = &semaphore;

    will_return(__wrap_sem_open, false);

    const f_status_t status = f_thread_semaphore_file_open(name, flag, &mode, value, &semaphore_ptr);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif

#include "../controller.h"
#include "../private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_delete_mutex_
  void controller_lock_delete_mutex(f_thread_mutex_t *mutex) {

    const f_status_t status = f_thread_mutex_delete(mutex);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_busy) {
        if (f_thread_mutex_delete(mutex) == F_none) {
          mutex = 0;
        }
      }
    }
    else {
      mutex = 0;
    }
  }
#endif // _di_controller_lock_delete_mutex_

#ifndef _di_controller_lock_delete_rw_
  void controller_lock_delete_rw(f_thread_lock_t *lock) {

    const f_status_t status = f_thread_lock_delete(lock);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_busy) {
        if (f_thread_lock_delete(lock) == F_none) {
          lock = 0;
        }
      }
    }
    else {
      lock = 0;
    }
  }
#endif // _di_controller_lock_delete_rw_

#ifndef _di_controller_lock_delete_simple_
  void controller_lock_delete_simple(controller_lock_t *lock) {

    controller_lock_delete_mutex(&lock->print);
    controller_lock_delete_mutex(&lock->alert);

    controller_lock_delete_rw(&lock->process);
    controller_lock_delete_rw(&lock->rule);

    f_thread_condition_delete(&lock->alert_condition);
  }
#endif // _di_controller_lock_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

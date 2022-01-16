#include "../controller/controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "../lock/private-lock.h"
#include "../thread/private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_create_
  f_status_t controller_lock_create(controller_lock_t *lock) {

    f_status_t status = f_thread_mutex_create(0, &lock->print);
    if (F_status_is_error(status)) return status;

    status = f_thread_mutex_create(0, &lock->alert);
    if (F_status_is_error(status)) return status;

    status = f_thread_lock_create(0, &lock->process);
    if (F_status_is_error(status)) return status;

    status = f_thread_lock_create(0, &lock->rule);
    if (F_status_is_error(status)) return status;

    status = f_thread_condition_create(0, &lock->alert_condition);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_lock_create_

#ifndef _di_controller_lock_read_
  f_status_t controller_lock_read(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) {

    struct timespec time;

    f_status_t status = F_none;

    for (;;) {

      controller_time(controller_thread_lock_read_timeout_seconds_d, controller_thread_lock_read_timeout_nanoseconds_d, &time);

      status = f_thread_lock_read_timed(&time, lock);

      if (status == F_time) {
        if (!controller_thread_is_enabled(is_normal, thread)) {
          return F_status_set_error(F_interrupt);
        }
      }
      else {
        break;
      }
    } // for

    return status;
  }
#endif // _di_controller_lock_read_

#ifndef _di_controller_lock_read_process_
  f_status_t controller_lock_read_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_read_process_type(process->type, thread, lock);
  }
#endif // _di_controller_lock_read_process_

#ifndef _di_controller_lock_read_process_type_
  f_status_t controller_lock_read_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_read(type != controller_process_type_exit_e, thread, lock);
  }
#endif // _di_controller_lock_read_process_type_

#ifndef _di_controller_lock_write_
  f_status_t controller_lock_write(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) {

    struct timespec time;

    f_status_t status = F_none;

    for (;;) {

      controller_time(controller_thread_lock_write_timeout_seconds_d, controller_thread_lock_write_timeout_nanoseconds_d, &time);

      status = f_thread_lock_write_timed(&time, lock);

      if (status == F_time) {
        if (!controller_thread_is_enabled(is_normal, thread)) {
          return F_status_set_error(F_interrupt);
        }
      }
      else {
        break;
      }
    } // for

    return status;
  }
#endif // _di_controller_lock_write_

#ifndef _di_controller_lock_write_process_
  f_status_t controller_lock_write_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_write_process_type(process->type, thread, lock);
  }
#endif // _di_controller_lock_write_process_

#ifndef _di_controller_lock_write_process_type_
  f_status_t controller_lock_write_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_write(type != controller_process_type_exit_e, thread, lock);
  }
#endif // _di_controller_lock_write_process_type_

#ifdef __cplusplus
} // extern "C"
#endif

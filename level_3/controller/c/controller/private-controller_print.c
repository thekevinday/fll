#include "../controller.h"
#include "../common/private-common.h"
#include "private-controller_print.h"
#include "../lock/private-lock_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_
  void controller_print_error(controller_thread_t * const thread, const fl_print_t print, const f_status_t status, const f_string_t function, const uint8_t flag) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    fll_error_print(&print, status, function, flag); // @fixme the print is a const and it is being passed as a pointer; the function needs to change.

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_print_error_

#ifndef _di_controller_print_error_file_
  void controller_print_error_file(controller_thread_t * const thread, const fl_print_t print, const f_status_t status, const f_string_t function, const uint8_t flag, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    fll_error_file_print(&print, status, function, flag, name, operation, type); // @fixme the print is a const and it is being passed as a pointer; the function needs to change.

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_print_error_file_

#ifdef __cplusplus
} // extern "C"
#endif

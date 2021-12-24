#include "controller.h"
#include "private-common.h"
#include "private-lock_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_lock_print_error_critical_
  void controller_lock_print_error_critical(const fl_print_t print, const f_status_t status, const bool read, controller_thread_t *thread) {

    // A signal is not an error.
    if (status == F_interrupt) return;

    if (print.verbosity != f_console_verbosity_quiet_e) {
      controller_lock_print(print.to, thread);

      fl_print_format("%c%[%SThe pid file '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix ? print.prefix : f_string_empty_s, print.context);
      fl_print_format("%['Critical failure while attempting to establish '%]", print.to.stream, print.context, print.context);
      fl_print_format("%[%s lock%]", print.to.stream, print.notable, read ? "read" : "write", print.notable);

      if (status != F_failure) {
        fl_print_format(" %['due to%] ", print.to.stream, print.context, print.context);

        if (status == F_parameter) {
          fl_print_format("%[Invalid Parameter%]", print.to.stream, print.notable, print.notable);
        }
        else if (status == F_deadlock) {
          fl_print_format("%[Deadlock%]", print.to.stream, print.notable, print.notable);
        }
        else if (status == F_resource_not) {
          fl_print_format("%[Too Many Locks%]", print.to.stream, print.notable, print.notable);
        }
        else {
          fl_print_format("%[Unknown Error%]", print.to.stream, print.notable, print.notable);
        }
      }

      fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

      controller_unlock_print_flush(print.to, thread);
    }
  }
#endif // _di_controller_lock_print_error_critical_

#ifndef _di_controller_lock_print_
  void controller_lock_print(const f_file_t to, controller_thread_t * const thread) {

    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    flockfile(to.stream);
  }
#endif // _di_controller_lock_print_

#ifndef _di_controller_unlock_print_flush_
  void controller_unlock_print_flush(const f_file_t to, controller_thread_t * const thread) {

    fflush(to.stream);
    funlockfile(to.stream);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_unlock_print_flush_

#ifdef __cplusplus
} // extern "C"
#endif

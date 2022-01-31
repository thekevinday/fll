#include "../controller.h"
#include "../common/private-common.h"
#include "private-controller_print.h"
#include "../lock/private-lock_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_error_
  void controller_print_error(controller_thread_t * const thread, const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    fll_error_print(print, status, function, fallback);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_print_error_

#ifndef _di_controller_print_error_file_
  void controller_print_error_file(controller_thread_t * const thread, const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    fll_error_file_print(print, status, function, fallback, name, operation, type);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_print_error_file_

#ifndef _di_controller_print_signal_received_
  void controller_print_signal_received(controller_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%q%q%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s, f_string_eol_s, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%q", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_controller_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

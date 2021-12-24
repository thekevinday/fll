#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-thread.h"
#include "private-thread_entry.h"
#include "private-thread_process.h"
#include "private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_signal_
  void controller_thread_signal(const bool is_normal, controller_global_t *global) {

    if (!controller_thread_is_enabled(is_normal, global->thread)) return;

    siginfo_t information;
    struct timespec time;
    int error = 0;

    while (controller_thread_is_enabled(is_normal, global->thread)) {

      controller_time(controller_thread_exit_ready_timeout_seconds_d, controller_thread_exit_ready_timeout_nanoseconds_d, &time);

      error = sigtimedwait(&global->main->signal.set, &information, &time);

      if (error == -1) {
        if (errno == EAGAIN) continue;
      }

      if (global->setting->interruptible) {
        if (information.si_signo == F_signal_interrupt || information.si_signo == F_signal_abort || information.si_signo == F_signal_quit || information.si_signo == F_signal_termination) {
          global->thread->signal = information.si_signo;

          controller_thread_process_cancel(is_normal, controller_thread_cancel_signal_e, global, 0);

          break;
        }
      }
    } // while
  }
#endif // _di_controller_thread_signal_

#ifndef _di_controller_thread_signal_state_fss_
  f_status_t controller_thread_signal_state_fss(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    controller_state_interrupt_t *custom = (controller_state_interrupt_t *) state_ptr->custom;
    controller_thread_t *thread = custom->thread;

    if (!controller_thread_is_enabled(custom->is_normal, thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (thread->signal == F_signal_interrupt || thread->signal == F_signal_abort || thread->signal == F_signal_quit || thread->signal == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_controller_thread_signal_state_fss_

#ifndef _di_controller_thread_signal_state_iki_
  f_status_t controller_thread_signal_state_iki(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    controller_state_interrupt_t *custom = (controller_state_interrupt_t *) state_ptr->custom;
    controller_thread_t *thread = custom->thread;

    if (!controller_thread_is_enabled(custom->is_normal, thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (thread->signal == F_signal_interrupt || thread->signal == F_signal_abort || thread->signal == F_signal_quit || thread->signal == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_controller_thread_signal_state_iki_

#ifndef _di_controller_thread_signal_normal_
  void * controller_thread_signal_normal(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal(F_true, (controller_global_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_signal_normal_

#ifndef _di_controller_thread_signal_other_
  void * controller_thread_signal_other(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal(F_false, (controller_global_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif

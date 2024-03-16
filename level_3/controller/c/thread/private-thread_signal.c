#include "../controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "private-thread.h"
#include "private-thread_entry.h"
#include "private-thread_process.h"
#include "private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_signal_
  void controller_thread_signal(controller_global_t * const global, const bool is_normal) {

    if (!controller_thread_is_enabled(is_normal, global->thread)) return;

    siginfo_t information;
    struct timespec time;
    int error = 0;

    while (controller_thread_is_enabled(is_normal, global->thread)) {

      controller_time(controller_thread_exit_ready_timeout_seconds_d, controller_thread_exit_ready_timeout_nanoseconds_d, &time);

      error = sigtimedwait(&global->main->program.signal.set, &information, &time);

      if (error == -1) {
        if (errno == EAGAIN) continue;
      }

      if (global->setting->flag & controller_setting_flag_interruptible_e) {
        if (information.si_signo == F_signal_interrupt || information.si_signo == F_signal_abort || information.si_signo == F_signal_quit || information.si_signo == F_signal_termination) {
          global->thread->signal = information.si_signo;

          controller_thread_process_cancel(*global, is_normal, controller_thread_cancel_signal_e);

          break;
        }
      }
    } // while
  }
#endif // _di_controller_thread_signal_

#ifndef _di_controller_thread_signal_state_fss_
  void controller_thread_signal_state_fss(f_state_t * const state, void * const internal) {

    if (!state || !state->custom) return;

    controller_global_t * const global = (controller_global_t *) state->custom;

    /*if (!controller_thread_is_enabled(custom->is_normal, global->thread)) {
      global->main->program.signal_received = F_signal_abort;
      global->main->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (global->thread->signal == F_signal_interrupt || global->thread->signal == F_signal_abort || global->thread->signal == F_signal_quit || global->thread->signal == F_signal_termination) {
      global->main->program.signal_received = F_signal_abort;
      global->main->setting.state.status = F_status_set_error(F_interrupt);
    }*/
  }
#endif // _di_controller_thread_signal_state_fss_

#ifndef _di_controller_thread_signal_state_iki_
  void controller_thread_signal_state_iki(f_state_t * const state, void * const internal) {

    if (!state || !state->custom) return;

    controller_global_t * const global = (controller_global_t *) state->custom;

    /*if (!controller_thread_is_enabled(custom->is_normal, global->thread)) {
      global->main->program.signal_received = F_signal_abort;
      global->main->setting.state.status = F_status_set_error(F_interrupt);
    }
    else if (global->thread->signal == F_signal_interrupt || global->thread->signal == F_signal_abort || global->thread->signal == F_signal_quit || global->thread->signal == F_signal_termination) {
      global->main->program.signal_received = F_signal_abort;
      global->main->setting.state.status = F_status_set_error(F_interrupt);
    }*/
  }
#endif // _di_controller_thread_signal_state_iki_

#ifndef _di_controller_thread_signal_normal_
  void * controller_thread_signal_normal(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal((controller_global_t *) arguments, F_true);

    return 0;
  }
#endif // _di_controller_thread_signal_normal_

#ifndef _di_controller_thread_signal_other_
  void * controller_thread_signal_other(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal((controller_global_t *) arguments, F_false);

    return 0;
  }
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif

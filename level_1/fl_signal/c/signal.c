#include "signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_signal_state_interrupt_
  f_status_t fl_signal_state_interrupt(void *state, void *internal) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_status_set_error(F_parameter);
    }

    fl_signal_interrupt_t *signal_interrupt = (fl_signal_interrupt_t *) state_ptr->custom;

    if (!signal_interrupt || !signal_interrupt->signal.id) {
      return F_enable_not;
    }

    if (!signal_interrupt->interrupts.used) {
      return F_interrupt_not;
    }

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    const f_status_t status = f_signal_read(signal_interrupt->signal, &information);

    if (status == F_signal) {
      for (f_array_length_t i = 0; i < signal_interrupt->interrupts.used; ++i) {

        if (information.ssi_signo == signal_interrupt->interrupts.array[i]) {
          signal_interrupt->trigger = information.ssi_signo;

          return F_status_set_error(F_interrupt);
        }
      } // for
    }

    return F_interrupt_not;
  }
#endif // _di_fl_signal_state_interrupt_

#ifdef __cplusplus
} // extern "C"
#endif

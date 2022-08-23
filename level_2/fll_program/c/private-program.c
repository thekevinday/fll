#include "program.h"
#include "private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_state_)
  f_status_t private_fll_program_standard_signal_received(fll_program_data_t * const main) {

    if (main->signal.id == -1) return 0;

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(main->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          main->signal_received = information.ssi_signo;

          return information.ssi_signo;
      }
    }

    return 0;
  }
#endif // !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_state_)

#ifdef __cplusplus
} // extern "C"
#endif

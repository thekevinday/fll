#include "fss_extended_list_write.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_write_print_signal_received_
  void fss_extended_list_write_print_signal_received(fss_extended_list_write_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%c%c%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s[0], f_string_eol_s[0], main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%c", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s[0]);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fss_extended_list_write_print_signal_received_

#ifndef _di_fss_extended_list_write_signal_received_
  f_status_t fss_extended_list_write_signal_received(fss_extended_list_write_main_t * const main) {

    if (!main->signal.id) {
      return F_false;
    }

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
          fss_extended_list_write_print_signal_received(main, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_fss_extended_list_write_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#include "fss_basic_list_write.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_write_print_signal_received_
  void fss_basic_list_write_print_signal_received(fll_program_data_t * const main) {

    if (main->warning.verbosity != f_console_verbosity_verbose_e && main->warning.verbosity != f_console_verbosity_debug_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s, f_string_eol_s, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, main->signal_received, main->context.set.notable);
    fl_print_format("%[.%]%r", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fss_basic_list_write_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#include "fss_embedded_list_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_data_delete_
  f_status_t fss_embedded_list_read_data_delete(fss_embedded_list_read_data_t * const data) {

    macro_f_fss_nest_t_delete_simple(data->nest);

    f_string_dynamic_resize(0, &data->buffer);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_data_delete_

#ifndef _di_fss_embedded_list_read_print_signal_received_
  void fss_embedded_list_read_print_signal_received(fss_embedded_list_read_data_t * const data) {

    if (data->main->warning.verbosity != f_console_verbosity_verbose_e && data->main->warning.verbosity != f_console_verbosity_debug_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(data->main->warning.to.stream);

    flockfile(data->main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", data->main->warning.to.stream, data->main->context.set.reset, f_string_eol_s, f_string_eol_s, data->main->context.set.warning, data->main->context.set.warning);
    fl_print_format("%[%i%]", data->main->warning.to.stream, data->main->context.set.notable, data->main->signal_received, data->main->context.set.notable);
    fl_print_format("%[.%]%r", data->main->warning.to.stream, data->main->context.set.warning, data->main->context.set.warning, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_fss_embedded_list_read_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

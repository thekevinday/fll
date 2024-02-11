#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_warning_show_option_unknown_
  f_status_t firewall_print_warning_show_option_unknown(fl_print_t * const print, const f_string_static_t option) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(firewall_operation_show_s.string, print->to, print->notable, option, print->notable);
    fl_print_format(" %[option '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, option, print->notable);
    fl_print_format("%[' is not known.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);
    f_file_stream_flush(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_warning_show_option_unknown_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_debug_tool_
  f_status_t firewall_print_debug_tool(fl_print_t * const print, const f_string_static_t tool, const f_string_statics_t arguments) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity != f_console_verbosity_debug_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%Q", print->to, print->context, tool);

    for (f_number_unsigned_t i = 0; i < arguments.used; ++i) {
      fl_print_format(" %Q", print->to, arguments.array[i]);
    } // for

    fl_print_format("%]%r", print->to, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_debug_tool_

#ifdef __cplusplus
} // extern "C"
#endif

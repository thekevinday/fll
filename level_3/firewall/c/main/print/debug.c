#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_debug_tool_
  void firewall_print_debug_tool(const fl_print_t output, const f_string_static_t tool, const f_string_statics_t arguments) {

    if (output.verbosity != f_console_verbosity_debug_e) return;

    f_file_stream_lock(output.to);

    fl_print_format("%[%r", output.to, output.context, tool);

    for (f_number_unsigned_t i = 0; i < arguments.used; ++i) {
      fl_print_format(" %Q", output.to, arguments.array[i]);
    } // for

    fl_print_format("%]%r", output.to, output.context, f_string_eol_s);

    f_file_stream_unlock(output.to);
  }
#endif // _di_firewall_print_debug_tool_

#ifdef __cplusplus
} // extern "C"
#endif

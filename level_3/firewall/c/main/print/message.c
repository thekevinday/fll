#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_message_help_
  f_status_t firewall_print_message_help(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, firewall_program_name_long_s, firewall_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_operations(print);

    fll_program_print_help_option_other(print, firewall_operation_lock_s, "   Switch to rules intended to prevent all communication.");
    fll_program_print_help_option_other(print, firewall_operation_restart_s, "Turn off and then turn on the firewall.");
    fll_program_print_help_option_other(print, firewall_operation_show_s, "   Show the active firewall settings.");
    fll_program_print_help_option_other(print, firewall_operation_start_s, "  Turn on the firewall.");
    fll_program_print_help_option_other(print, firewall_operation_stop_s, "   Turn off the firewall.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, firewall_program_name_s, firewall_program_help_commands_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_message_help_

#ifndef _di_firewall_print_message_show_header_
  f_status_t firewall_print_message_show_header(fl_print_t * const print, const f_string_static_t left, const f_string_static_t header, const f_string_static_t right) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    if (left.used) {
      fl_print_format("%[%Q%] ", print->to, print->set.standout, left, print->set.standout);
    }

    fll_print_format("%[%Q%]", print->to, print->set.standout, print->set.standout, print->set.title, print->set.title, print->set.standout, print->set.standout, f_string_eol_s);

    if (left.used) {
      fl_print_format(" %[%Q%]", print->to, print->set.standout, right, print->set.standout);
    }

    f_print_dynamic_raw(f_string_eol_s, print->to);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);
  }
#endif // _di_firewall_print_message_show_header_

#ifdef __cplusplus
} // extern "C"
#endif

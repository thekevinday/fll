#include "firewall.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_help_
  f_status_t firewall_print_help(firewall_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    fll_program_print_help_header(print, firewall_program_name_long_s, firewall_program_version_s);

    fll_program_print_help_option_standard(print);

    fl_print_format("%r%r %[Commands:%] ", print.to, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important);
    fl_print_format("%r  %[%r%]    Turn on the firewall.", print.to, f_string_eol_s, print.set->standout, firewall_command_start_s, print.set->standout);
    fl_print_format("%r  %[%r%]     Turn off the firewall.", print.to, f_string_eol_s, print.set->standout, firewall_command_stop_s, print.set->standout);
    fl_print_format("%r  %[%r%]  Turn off and then turn on the firewall.", print.to, f_string_eol_s, print.set->standout, firewall_command_restart_s, print.set->standout);
    fl_print_format("%r  %[%r%]     Prevent all communication.", print.to, f_string_eol_s, print.set->standout, firewall_command_lock_s, print.set->standout);
    fl_print_format("%r  %[%r%]     Show active firewall settings.", print.to, f_string_eol_s, print.set->standout, firewall_command_show_s, print.set->standout);

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, firewall_program_name_s, firewall_program_help_parameters_s);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_okay;
  }
#endif // _di_firewall_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

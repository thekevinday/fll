#include "firewall.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_help_
  f_status_t firewall_print_help(utf8_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    fll_program_print_help_header(print, firewall_program_name_long_s, firewall_program_version_s);

    fll_program_print_help_option_standard(print);

    fl_print_format("%r%r %[Commands:%] ", print.to.stream, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important);
    fl_print_format("%r  %[%r%]    Turn on the firewall.", print.to.stream, f_string_eol_s, print.set->standout, firewall_command_start_s, print.set->standout);
    fl_print_format("%r  %[%r%]     Turn off the firewall.", print.to.stream, f_string_eol_s, print.set->standout, firewall_command_stop_s, print.set->standout);
    fl_print_format("%r  %[%r%]  Turn off and then turn on the firewall.", print.to.stream, f_string_eol_s, print.set->standout, firewall_command_restart_s, print.set->standout);
    fl_print_format("%r  %[%r%]     Prevent all communication.", print.to.stream, f_string_eol_s, print.set->standout, firewall_command_lock_s, print.set->standout);
    fl_print_format("%r  %[%r%]     Show active firewall settings.", print.to.stream, f_string_eol_s, print.set->standout, firewall_command_show_s, print.set->standout);

    fll_program_print_help_usage(print, firewall_program_name_s, firewall_program_help_parameters_s);

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_print_line_first_
  void firewall_print_line_first(firewall_setting_t * const setting, const fl_print_t print, const bool lock) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    if (lock) {
      fll_print_dynamic_raw(setting->line_first, print.to.stream);
    }
    else {
      f_print_dynamic_raw(setting->line_first, print.to.stream);
    }
  }
#endif // _di_firewall_print_line_first_

#ifndef _di_firewall_print_line_last_
  void firewall_print_line_last(firewall_setting_t * const setting, const fl_print_t print, const bool lock) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (print.verbosity == f_console_verbosity_error_e && !F_status_is_error(setting->status)) return;
    if (setting->flag & firewall_main_flag_verify_e) return;
    if ((setting->flag & firewall_main_flag_file_to_e) && !F_status_is_error(setting->status)) return;

    if (lock) {
      fll_print_dynamic_raw(setting->line_last, print.to.stream);
    }
    else {
      f_print_dynamic_raw(setting->line_last, print.to.stream);
    }
  }
#endif // _di_firewall_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif

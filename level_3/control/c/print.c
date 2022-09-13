#include "control.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_help_
  f_status_t control_print_help(control_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    fll_program_print_help_header(print, control_program_name_long_s, control_program_version_s);

    fll_program_print_help_option_standard(main->output.to, context);

    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);

    fll_program_print_help_option(print, control_short_name_s, control_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Specify the name of the controller socket file.");
    fll_program_print_help_option(print, control_short_return_s, control_long_return_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print a message about the response packet.");
    fll_program_print_help_option(print, control_short_settings_s, control_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Specify a directory path or a full path to the control settings file.");
    fll_program_print_help_option(print, control_short_socket_s, control_long_socket_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Specify a directory path or a full path to the controller socket file.");

    fll_program_print_help_usage(print, control_program_name_s, control_action_s);

    fl_print_format("%r  When the %[%r%r%] parameter represents a directory path then the file name is generated from either the", print.to.stream, f_string_eol_s, print.set->notable, f_console_symbol_long_enable_s, control_long_socket_s, print.set->notable);
    fl_print_format(" %[%r%r%] parameter or from the control settings file.%r%r", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, control_long_name_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  A rule action allows for either the full rule path, such as '%[boot/root%]'", print.to.stream, print.set->notable, print.set->notable);
    fl_print_format(" as a single parameter or two parameters with the first representing the rule directory path '%[boot%]'", print.to.stream, print.set->notable, print.set->notable);
    fl_print_format(" and the second representing the rule base name '%[root%]'.%r%r", print.to.stream, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] parameter is intended to be used for scripting and is of the form \"response [type] [action] [status]\".%r", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, control_long_return_s, print.set->notable, f_string_eol_s);
    fl_print_format("  Be sure to use the %[%r%r%] parameter to suppress output when using this in scripting.%r", print.to.stream, print.set->notable, f_console_symbol_long_disable_s, f_console_standard_long_quiet_s, print.set->notable, f_string_eol_s);
    fl_print_format("  No response is returned on program errors, especially those errors that prevent communicating to the controller.%r", print.to.stream, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_control_print_help_

#ifndef _di_control_print_line_first_locked_
  f_status_t control_print_line_first_locked(control_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (setting->flag & control_main_flag_verify_e) return;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & control_main_flag_file_to_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    return F_none;
  }
#endif // _di_control_print_line_first_locked_

#ifndef _di_control_print_line_first_unlocked_
  f_status_t control_print_line_first_unlocked(control_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (setting->flag & control_main_flag_verify_e) return;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & control_main_flag_file_to_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to.stream);

    return F_none;
  }
#endif // _di_control_print_line_first_unlocked_

#ifndef _di_control_print_line_last_locked_
  f_status_t control_print_line_last_locked(control_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (setting->flag & control_main_flag_verify_e) return;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & control_main_flag_file_to_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to.stream);

    return F_none;
  }
#endif // _di_control_print_line_last_locked_

#ifndef _di_control_print_line_last_unlocked_
  f_status_t control_print_line_last_unlocked(control_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (setting->flag & control_main_flag_verify_e) return;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & control_main_flag_file_to_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    return F_none;
  }
#endif // _di_control_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif

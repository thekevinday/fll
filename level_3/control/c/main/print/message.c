#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_message_help_
  f_status_t control_print_message_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, control_program_name_long_s, control_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, control_short_name_s, control_long_name_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Specify the name of the controller socket file.");
    fll_program_print_help_option(print, control_short_return_s, control_long_return_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Print a message about the response packet.");
    fll_program_print_help_option(print, control_short_settings_s, control_long_settings_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Specify a directory path or a full path to the control settings file.");
    fll_program_print_help_option(print, control_short_socket_s, control_long_socket_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Specify a directory path or a full path to the controller socket file.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, control_program_name_s, control_action_s);

    fl_print_format("%r  When the %[%r%r%] parameter represents a directory path then the file name is generated from either the", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, control_long_socket_s, print->set->notable);
    fl_print_format(" %[%r%r%] parameter or from the control settings file.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, control_long_name_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  A rule action allows for either the full rule path, such as '%[boot/root%]'", print->to, print->set->notable, print->set->notable);
    fl_print_format(" as a single parameter or two parameters with the first representing the rule directory path '%[boot%]'", print->to, print->set->notable, print->set->notable);
    fl_print_format(" and the second representing the rule base name '%[root%]'.%r%r", print->to, print->set->notable, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] parameter is intended to be used for scripting and is of the form \"response [type] [action] [status]\".%r", print->to, print->set->notable, f_console_symbol_long_normal_s, control_long_return_s, print->set->notable, f_string_eol_s);
    fl_print_format("  Be sure to use the %[%r%r%] parameter to suppress output when using this in scripting.%r", print->to, print->set->notable, f_console_symbol_long_inverse_s, f_console_standard_long_quiet_s, print->set->notable, f_string_eol_s);
    fl_print_format("  No response is returned on program errors, especially those errors that prevent communicating to the controller.%r", print->to, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_control_print_message_help_

#ifndef _di_control_print_message_packet_response_
  f_status_t control_print_message_packet_response(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    control_main_t * const main = (control_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("The action '", print->to);
    fl_print_format("%[%q%]", print->to, print->set->notable, control_action_type_name(header.action), print->set->notable);

    if (header.status == F_done) {
      fl_print_format("' is performed", print->to);
    }
    else {
      fl_print_format("' is successfully performed", print->to);
    }

    if (header.length) {
      fl_print_format(": %/Q%r", print->to, main->cache.large, main->cache.packet_contents.array[main->cache.packet_contents.used - 1].array[0], f_string_eol_s);
    }
    else {
      fl_print_format(".%r", print->to, f_string_eol_s);
    }

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_control_print_message_packet_response_

#ifdef __cplusplus
} // extern "C"
#endif

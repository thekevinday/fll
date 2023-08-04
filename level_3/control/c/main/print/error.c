#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_error_
  f_status_t control_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((control_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_control_print_error_

#ifndef _di_control_print_error_file_
  f_status_t control_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    control_main_t * const main = (control_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_none;
  }
#endif // _di_control_print_error_file_

#ifndef _di_control_print_error_packet_response_
  f_status_t control_print_error_packet_response(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    control_main_t * const main = (control_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QReceived error response for " CONTROL_action_s " '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%q%]", print->to, print->set->notable, control_action_type_name(header.action), print->set->notable);
    fl_print_format("%[' with status '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, string_status, print->set->notable);
    fl_print_format("%[' (%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%ui%]", print->to, print->set->notable, header.status, print->set->notable);

    if (header.length) {
      fl_print_format("%[): %/Q%]%r", print->to, print->set->error, print->set->error, main->cache.large, main->cache.packet_contents.array[main->cache.packet_contents.used - 1].array[0], f_string_eol_s);
    }
    else {
      fl_print_format("%[).%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);
    }

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_packet_response_

#ifndef _di_control_print_error_packet_response_failure_
  f_status_t control_print_error_packet_response_failure(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    control_main_t * const main = (control_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, control_action_type_name(header.action), print->set->notable);
    fl_print_format("%[' failed with status '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, string_status, print->set->notable);
    fl_print_format("%[' (%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%ui%]", print->to, print->set->notable, header.status, print->set->notable);

    if (header.length) {
      fl_print_format("%[): %/Q%]%r", print->to, print->set->error, print->set->error, main->cache.large, main->cache.packet_contents.array[main->cache.packet_contents.used - 1].array[0], f_string_eol_s);
    }
    else {
      fl_print_format("%[).%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);
    }

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_packet_response_failure_

#ifndef _di_control_print_error_parameter_actions_none_
  f_status_t control_print_error_parameter_actions_none(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo actions provided.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_control_print_error_parameter_actions_none_

#ifndef _di_control_print_error_parameter_action_not_
  f_status_t control_print_error_parameter_action_not(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' is not a known controller action.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_not_

#ifndef _di_control_print_error_parameter_action_rule_basename_empty_
  f_status_t control_print_error_parameter_action_rule_basename_empty(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' a rule base name cannot be an empty string.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_basename_empty_

#ifndef _di_control_print_error_parameter_action_rule_directory_empty_
  f_status_t control_print_error_parameter_action_rule_directory_empty(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' a rule directory path cannot be an empty string.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_directory_empty_

#ifndef _di_control_print_error_parameter_action_rule_empty_
  f_status_t control_print_error_parameter_action_rule_empty(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' a rule name cannot be an empty string.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_empty_

#ifndef _di_control_print_error_parameter_action_rule_not_
  f_status_t control_print_error_parameter_action_rule_not(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' requires either a full rule name or a rule directory path along with the rule base name.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_not_

#ifndef _di_control_print_error_parameter_action_rule_too_few_
  f_status_t control_print_error_parameter_action_rule_too_few(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' has too few arguments.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_too_few_

#ifndef _di_control_print_error_parameter_action_rule_too_few_with_
  f_status_t control_print_error_parameter_action_rule_too_few_with(fl_print_t * const print, const f_string_static_t action, const f_string_static_t with) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' when used with '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%Q%]", print->to, print->set->notable, with, print->set->notable);
    fl_print_format("%[' has too few arguments.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_too_few_with_

#ifndef _di_control_print_error_parameter_action_rule_too_many_
  f_status_t control_print_error_parameter_action_rule_too_many(fl_print_t * const print, const f_string_static_t action) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' has too many arguments.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_too_many_

#ifndef _di_control_print_error_parameter_action_rule_too_many_with_
  f_status_t control_print_error_parameter_action_rule_too_many_with(fl_print_t * const print, const f_string_static_t action, const f_string_static_t with) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' when used with '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%Q%]", print->to, print->set->notable, with, print->set->notable);
    fl_print_format("%[' has too many arguments.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_too_many_with_

#ifndef _di_control_print_error_parameter_action_rule_with_unknown_
  f_status_t control_print_error_parameter_action_rule_with_unknown(fl_print_t * const print, const f_string_static_t action, const f_string_static_t with) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, action, print->set->notable);
    fl_print_format("%[' does not know the argument '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%Q%]", print->to, print->set->notable, with, print->set->notable);
    fl_print_format("%['.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_action_rule_with_unknown_

#ifndef _di_control_print_error_parameter_value_empty_
  f_status_t control_print_error_parameter_value_empty(fl_print_t * const print, const f_string_static_t parameter) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value for the parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, parameter, print->set->notable);
    fl_print_format("%[' must not be an empty string.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_value_empty_

#ifndef _di_control_print_error_parameter_value_not_
  f_status_t control_print_error_parameter_value_not(fl_print_t * const print, const f_string_static_t parameter) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, parameter, print->set->notable);
    fl_print_format("%[' is specified, but no value is given.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_parameter_value_not_

#ifndef _di_control_print_error_pipe_supported_not_
  f_status_t control_print_error_pipe_supported_not(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QPipe input is not supported by this program.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_control_print_error_pipe_supported_not_

#ifndef _di_control_print_error_response_packet_valid_not_
  f_status_t control_print_error_response_packet_valid_not(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QThe received response is not a valid or supported packet.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_control_print_error_response_packet_valid_not_

#ifndef _di_control_print_error_request_packet_too_large_
  f_status_t control_print_error_request_packet_too_large(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QThe generated packet is too large, cannot send packet.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_control_print_error_request_packet_too_large_

#ifndef _di_control_print_error_socket_file_failed_
  f_status_t control_print_error_socket_file_failed(fl_print_t * const print, const f_string_static_t path_socket) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QFailed to connect to the socket file '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, path_socket, print->set->notable);
    fl_print_format("%['.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_socket_file_failed_

#ifndef _di_control_print_error_socket_file_missing_
  f_status_t control_print_error_socket_file_missing(fl_print_t * const print, const f_string_static_t path_socket) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe controller socket file '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, path_socket, print->set->notable);
    fl_print_format("%[' could not be found and is required.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_socket_file_missing_

#ifndef _di_control_print_error_socket_file_not_
  f_status_t control_print_error_socket_file_not(fl_print_t * const print, const f_string_static_t path_socket) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe controller socket file '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, path_socket, print->set->notable);
    fl_print_format("%[' is not a socket file.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_error_socket_file_not_

#ifdef __cplusplus
} // extern "C"
#endif

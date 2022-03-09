#include "control.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_error_parameter_commands_none_
  void control_print_error_parameter_commands_none(fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QNo commands provided.%]%r", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_parameter_commands_none_

#ifndef _di_control_print_error_parameter_command_not_
  void control_print_error_parameter_command_not(fll_program_data_t * const main, const f_string_static_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' is not a known controller command.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_not_

#ifndef _di_control_print_error_parameter_command_rule_basename_empty_
  void control_print_error_parameter_command_rule_basename_empty(fll_program_data_t * const main, const f_string_static_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe command parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' a rule base name cannot be an empty string.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_basename_empty_

#ifndef _di_control_print_error_parameter_command_rule_directory_empty_
  void control_print_error_parameter_command_rule_directory_empty(fll_program_data_t * const main, const f_string_static_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe command parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' a rule directory path cannot be an empty string.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_directory_empty_

#ifndef _di_control_print_error_parameter_command_rule_empty_
  void control_print_error_parameter_command_rule_empty(fll_program_data_t * const main, const f_string_static_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe command parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' a rule name cannot be an empty string.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_empty_

#ifndef _di_control_print_error_parameter_command_rule_not_
  void control_print_error_parameter_command_rule_not(fll_program_data_t * const main, const f_string_static_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe command parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' requires either a full rule name or a rule directory path along with the rule base name.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_not_

#ifndef _di_control_print_error_parameter_command_rule_too_many_
  void control_print_error_parameter_command_rule_too_many(fll_program_data_t * const main, const f_string_static_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe command parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' has too many arguments.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_too_many_

#ifndef _di_control_print_error_parameter_value_empty_
  void control_print_error_parameter_value_empty(fll_program_data_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' must not be an empty string.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_value_empty_

#ifndef _di_control_print_error_parameter_value_not_
  void control_print_error_parameter_value_not(fll_program_data_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_value_not_

#ifndef _di_control_print_error_pipe_supported_not_
  void control_print_error_pipe_supported_not(fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QPipe input is not supported by this program.%]%r", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_pipe_supported_not_

#ifndef _di_control_print_error_response_packet_valid_not_
  void control_print_error_response_packet_valid_not(fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QThe received response is not a valid or supported packet.'%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
  }
#endif // _di_control_print_error_response_packet_valid_not_

#ifndef _di_control_print_error_request_packet_too_large_
  void control_print_error_request_packet_too_large(fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QThe generated packet is too large, cannot send packet.'%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
  }
#endif // _di_control_print_error_request_packet_too_large_

#ifndef _di_control_print_error_socket_file_failed_
  void control_print_error_socket_file_failed(fll_program_data_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QFailed to connect to the socket file '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%['.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_socket_file_failed_

#ifndef _di_control_print_error_socket_file_missing_
  void control_print_error_socket_file_missing(fll_program_data_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe controller socket file '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%[' could not be found and is required.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_socket_file_missing_

#ifndef _di_control_print_error_socket_file_not_
  void control_print_error_socket_file_not(fll_program_data_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe controller socket file '%]", main->error.to.stream, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%[' is not a socket file.%]%r", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_socket_file_not_

#ifndef _di_control_print_signal_received_
  void control_print_signal_received(fll_program_data_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s, f_string_eol_s, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%r", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_control_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

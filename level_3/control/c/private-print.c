#include "control.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_error_parameter_command_not_
  void control_print_error_parameter_command_not(control_main_t * const main, const f_string_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' is not a known controller command.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_not_

#ifndef _di_control_print_error_parameter_command_rule_basename_empty_
  void control_print_error_parameter_command_rule_basename_empty(control_main_t * const main, const f_string_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe command parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' a rule base name cannot be an empty string.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_basename_empty_

#ifndef _di_control_print_error_parameter_command_rule_directory_empty_
  void control_print_error_parameter_command_rule_directory_empty(control_main_t * const main, const f_string_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe command parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' a rule directory path cannot be an empty string.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_directory_empty_

#ifndef _di_control_print_error_parameter_command_rule_empty_
  void control_print_error_parameter_command_rule_empty(control_main_t * const main, const f_string_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe command parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' a rule name cannot be an empty string.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_empty_

#ifndef _di_control_print_error_parameter_command_rule_not_
  void control_print_error_parameter_command_rule_not(control_main_t * const main, const f_string_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe command parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' requires either a full rule name or a rule directory path along with the rule base name.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_not_

#ifndef _di_control_print_error_parameter_command_rule_too_many_
  void control_print_error_parameter_command_rule_too_many(control_main_t * const main, const f_string_t command) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe command parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, command, main->context.set.notable);
    fl_print_format("%[' has too many arguments.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_command_rule_too_many_

#ifndef _di_control_print_error_commands_none_
  void control_print_error_commands_none(control_main_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%[%QNo commands are provided.%]%q", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_commands_none_

#ifndef _di_control_print_error_parameter_value_empty_
  void control_print_error_parameter_value_empty(control_main_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe value for the parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%q%q%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' must not be an empty string.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_value_empty_

#ifndef _di_control_print_error_parameter_value_not_
  void control_print_error_parameter_value_not(control_main_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe parameter '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%q%q%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' is specified, but no value is given.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_parameter_value_not_

#ifndef _di_control_print_error_pipe_supported_not_
  void control_print_error_pipe_supported_not(control_main_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%[%QPipe input is not supported by this program.%]%q", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_pipe_supported_not_

#ifndef _di_control_print_error_socket_file_failed_
  void control_print_error_socket_file_failed(control_main_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QFailed to connect to the socket file '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%['.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_socket_file_failed_

#ifndef _di_control_print_error_socket_file_missing_
  void control_print_error_socket_file_missing(control_main_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe controller socket file '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%[' could not be found and is required.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_socket_file_missing_

#ifndef _di_control_print_error_socket_file_not_
  void control_print_error_socket_file_not(control_main_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    flockfile(main->error.to.stream);

    fl_print_format("%[%QThe controller socket file '%]", main->error.to.stream, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to.stream, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%[' is not a socket file.%]%q", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_control_print_error_socket_file_not_

#ifndef _di_control_print_signal_received_
  void control_print_signal_received(control_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%q%q%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s, f_string_eol_s, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%q", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_control_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

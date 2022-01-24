/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_control_print_h
#define _PRIVATE_control_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print an error message about the given parameter not matching the known set of controller commands.
 *
 * @param main
 *   The main program data.
 * @param command
 *   The parameter representing a command.
 */
#ifndef _di_control_print_error_parameter_command_not_
  extern void control_print_error_parameter_command_not(control_main_t * const main, const f_string_t command) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_command_not_

/**
 * Print an error message about the given parameter being a rule command having an empty rule basename.
 *
 * @param main
 *   The main program data.
 * @param command
 *   The parameter representing a command.
 */
#ifndef _di_control_print_error_parameter_command_rule_basename_empty_
  extern void control_print_error_parameter_command_rule_basename_empty(control_main_t * const main, const f_string_t command) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_command_rule_basename_empty_

/**
 * Print an error message about the given parameter being a rule command having an empty rule directory path.
 *
 * @param main
 *   The main program data.
 * @param command
 *   The parameter representing a command.
 */
#ifndef _di_control_print_error_parameter_command_rule_directory_empty_
  extern void control_print_error_parameter_command_rule_directory_empty(control_main_t * const main, const f_string_t command) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_command_rule_directory_empty_

/**
 * Print an error message about the given parameter being a rule command having an empty rule name.
 *
 * @param main
 *   The main program data.
 * @param command
 *   The parameter representing a command.
 */
#ifndef _di_control_print_error_parameter_command_rule_empty_
  extern void control_print_error_parameter_command_rule_empty(control_main_t * const main, const f_string_t command) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_command_rule_empty_

/**
 * Print an error message about the given parameter being a rule command but no rule name is specified.
 *
 * @param main
 *   The main program data.
 * @param command
 *   The parameter representing a command.
 */
#ifndef _di_control_print_error_parameter_command_rule_not_
  extern void control_print_error_parameter_command_rule_not(control_main_t * const main, const f_string_t command) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_command_rule_not_

/**
 * Print an error message about the given parameter being a rule command having too many arguments passed.
 *
 * @param main
 *   The main program data.
 * @param command
 *   The parameter representing a command.
 */
#ifndef _di_control_print_error_parameter_command_rule_too_many_
  extern void control_print_error_parameter_command_rule_too_many(control_main_t * const main, const f_string_t command) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_command_rule_too_many_

/**
 * Print an error message about no commands being provided.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_control_print_error_commands_none_
  extern void control_print_error_commands_none(control_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_commands_none_

/**
 * Print an error message about the parameter's associated value being an empty string.
 *
 * @param main
 *   The main program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_control_print_error_parameter_value_empty_
  extern void control_print_error_parameter_value_empty(control_main_t * const main, const f_string_static_t parameter) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_value_empty_

/**
 * Print an error message about the parameter missings its associated value.
 *
 * @param main
 *   The main program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_control_print_error_parameter_value_not_
  extern void control_print_error_parameter_value_not(control_main_t * const main, const f_string_static_t parameter) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_value_not_

/**
 * Print an error message about a pipe input being unsupported.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_control_print_error_pipe_supported_not_
  extern void control_print_error_pipe_supported_not(control_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_pipe_supported_not_

/**
 * Print an error message about failure to connect to the socket file.
 *
 * @param main
 *   The main program data.
 * @param path_socket
 *   The socket file path.
 */
#ifndef _di_control_print_error_socket_file_failed_
  extern void control_print_error_socket_file_failed(control_main_t * const main, const f_string_static_t path_socket) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_socket_file_failed_

/**
 * Print an error message about the socket file not being found.
 *
 * @param main
 *   The main program data.
 * @param path_socket
 *   The socket file path.
 */
#ifndef _di_control_print_error_socket_file_missing_
  extern void control_print_error_socket_file_missing(control_main_t * const main, const f_string_static_t path_socket) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_socket_file_missing_

/**
 * Print an error message about the socket file not actually being a socket file.
 *
 * @param main
 *   The main program data.
 * @param path_socket
 *   The socket file path.
 */
#ifndef _di_control_print_error_socket_file_not_
  extern void control_print_error_socket_file_not(control_main_t * const main, const f_string_static_t path_socket) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_socket_file_not_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_control_print_signal_received_
  extern void control_print_signal_received(control_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_control_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_print_h

/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_print_error_h
#define _control_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function associated with the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_control_print_error_
  extern f_status_t control_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_control_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_control_print_error_file_
  extern f_status_t control_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_control_print_error_file_

/**
 * Print an error from the packet response.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param header
 *   The control payload packet header data.
 * @param status
 *   A string representing the name of the status code from header.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_packet_response_
  extern f_status_t control_print_error_packet_response(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t status);
#endif // _di_control_print_error_packet_response_

/**
 * Print a error about a packet response failure.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param header
 *   The control payload packet header data.
 * @param status
 *   A string representing the name of the status code from header.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_packet_response_failure_
  extern f_status_t control_print_error_packet_response_failure(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status);
#endif // _di_control_print_error_packet_response_failure_
/**
 * Print an error message about no actions being provided.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_actions_none_
  extern f_status_t control_print_error_parameter_actions_none(fl_print_t * const print);
#endif // _di_control_print_error_parameter_actions_none_

/**
 * Print an error message about the given parameter not matching the known set of controller actions.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_not_
  extern f_status_t control_print_error_parameter_action_not(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_not_

/**
 * Print an error message about the given parameter being a rule action having an empty rule basename.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_basename_empty_
  extern f_status_t control_print_error_parameter_action_rule_basename_empty(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_rule_basename_empty_

/**
 * Print an error message about the given parameter being a rule action having an empty rule directory path.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_directory_empty_
  extern f_status_t control_print_error_parameter_action_rule_directory_empty(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_rule_directory_empty_

/**
 * Print an error message about the given parameter being a rule action having an empty rule name.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_empty_
  extern f_status_t control_print_error_parameter_action_rule_empty(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_rule_empty_

/**
 * Print an error message about the given parameter being a rule action but no rule name is specified.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_not_
  extern f_status_t control_print_error_parameter_action_rule_not(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_rule_not_

/**
 * Print an error message about the given parameter being a rule action having too few arguments passed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_few_
  extern f_status_t control_print_error_parameter_action_rule_too_few(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_rule_too_few_

/**
 * Print an error message about the given parameter being a rule action having few many arguments passed for a given "with".
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 * @param with
 *   The additional parameter in which is requiring additional arguments that are not met.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_few_with_
  extern f_status_t control_print_error_parameter_action_rule_too_few_with(fl_print_t * const print, const f_string_static_t action, const f_string_static_t with);
#endif // _di_control_print_error_parameter_action_rule_too_few_with_

/**
 * Print an error message about the given parameter being a rule action having too many arguments passed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_many_
  extern f_status_t control_print_error_parameter_action_rule_too_many(fl_print_t * const print, const f_string_static_t action);
#endif // _di_control_print_error_parameter_action_rule_too_many_

/**
 * Print an error message about the given parameter being a rule action having too many arguments passed for a given "with".
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 * @param with
 *   The additional parameter in which is requiring additional arguments that are not met.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_many_with_
  extern f_status_t control_print_error_parameter_action_rule_too_many_with(fl_print_t * const print, const f_string_static_t action, const f_string_static_t with);
#endif // _di_control_print_error_parameter_action_rule_too_many_with_
/**
 * Print an error message about the given parameter being unknown for the use with the given action.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The parameter representing an action.
 * @param with
 *   The additional parameter in which is requiring additional arguments that are not met.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_action_rule_with_unknown_
  extern f_status_t control_print_error_parameter_action_rule_with_unknown(fl_print_t * const print, const f_string_static_t action, const f_string_static_t with);
#endif // _di_control_print_error_parameter_action_rule_with_unknown_

/**
 * Print an error message about the parameter's associated value being an empty string.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param parameter
 *   The parameter name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_value_empty_
  extern f_status_t control_print_error_parameter_value_empty(fl_print_t * const print, const f_string_static_t parameter);
#endif // _di_control_print_error_parameter_value_empty_

/**
 * Print an error message about the parameter missings its associated value.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param parameter
 *   The parameter name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_parameter_value_not_
  extern f_status_t control_print_error_parameter_value_not(fl_print_t * const print, const f_string_static_t parameter);
#endif // _di_control_print_error_parameter_value_not_

/**
 * Print an error message about a pipe input being unsupported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_pipe_supported_not_
  extern f_status_t control_print_error_pipe_supported_not(fl_print_t * const print);
#endif // _di_control_print_error_pipe_supported_not_

/**
 * Print an error message about the response packet format either being invalid or not supported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_response_packet_valid_not_
  extern f_status_t control_print_error_response_packet_valid_not(fl_print_t * const print);
#endif // _di_control_print_error_response_packet_valid_not_

/**
 * Print an error message about the request packet being too large.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_request_packet_too_large_
  extern f_status_t control_print_error_request_packet_too_large(fl_print_t * const print);
#endif // _di_control_print_error_request_packet_too_large_

/**
 * Print an error message about failure to connect to the socket file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path_socket
 *   The socket file path.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_socket_file_failed_
  extern f_status_t control_print_error_socket_file_failed(fl_print_t * const print, const f_string_static_t path_socket);
#endif // _di_control_print_error_socket_file_failed_

/**
 * Print an error message about the socket file not being found.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path_socket
 *   The socket file path.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_socket_file_missing_
  extern f_status_t control_print_error_socket_file_missing(fl_print_t * const print, const f_string_static_t path_socket);
#endif // _di_control_print_error_socket_file_missing_

/**
 * Print an error message about the socket file not actually being a socket file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path_socket
 *   The socket file path.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_control_print_error_socket_file_not_
  extern f_status_t control_print_error_socket_file_not(fl_print_t * const print, const f_string_static_t path_socket);
#endif // _di_control_print_error_socket_file_not_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_print_error_h

/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_control_print_h
#define _PRIVATE_control_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about a packet response.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param header
 *   The control payload packet header data.
 * @param status
 *   A string representing the name of the status code from header.status.
 */
#ifndef _di_control_print_controller_packet_response_
  extern void control_print_controller_packet_response(const fll_program_data_t * const main, control_data_t * const data, const control_payload_header_t header, const f_string_static_t string_status) F_attribute_visibility_internal_d;
#endif // _di_control_print_controller_packet_response_

/**
 * Print a message displaying the object and content for some packet header.
 *
 * @param main
 *   The main program data.
 * @param object
 *   The object string.
 * @param content
 *   The content string.
 * @param content_range
 *   The range representing the content where the content is found within the content string.
 */
#ifndef _di_control_print_debug_packet_header_object_and_content_
  extern void control_print_debug_packet_header_object_and_content(const fll_program_data_t * const main, const f_string_static_t object, const f_string_static_t content, const f_string_range_t content_range) F_attribute_visibility_internal_d;
#endif // _di_control_print_debug_packet_header_object_and_content_

/**
 * Print a debug message regarding some packet.
 *
 * @param main
 *   The main program data.
 * @param message
 *   The message to print.
 *
 *   A single "%[" followed by a single "%]" is supported in the message and is replaced with "notable" context.
 * @param buffer
 *   (optional) An additonal message to print (this is syntax highlighted).
 *   Set to NULL to not use.
 * @param range
 *   (optional) The range within the buffer to print rather than printing the entire buffer.
 *   Set to NULL to not use.
 *   This is ignored when buffer is NULL.
 * @param status
 *   (optional) A status code that triggered the failure (this is syntax highlighted).
 *   Set to NULL to not use.
 */
#ifndef _di_control_print_debug_packet_message_
  extern void control_print_debug_packet_message(const fll_program_data_t * const main, const f_string_t message, const f_string_static_t *buffer, const f_string_range_t *range, const f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_control_print_debug_packet_message_

/**
 * Print an error from the packet response.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The control data.
 * @param header
 *   The control payload packet header data.
 * @param status
 *   A string representing the name of the status code from header.status.
 */
#ifndef _di_control_print_error_packet_response_
  extern void control_print_error_packet_response(const fll_program_data_t * const main, control_data_t * const data, const control_payload_header_t header, const f_string_static_t status) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_packet_response_
/**
 * Print an error message about no actions being provided.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_control_print_error_parameter_actions_none_
  extern void control_print_error_parameter_actions_none(const fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_actions_none_

/**
 * Print an error message about the given parameter not matching the known set of controller actions.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_not_
  extern void control_print_error_parameter_action_not(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_not_

/**
 * Print an error message about the given parameter being a rule action having an empty rule basename.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_rule_basename_empty_
  extern void control_print_error_parameter_action_rule_basename_empty(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_basename_empty_

/**
 * Print an error message about the given parameter being a rule action having an empty rule directory path.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_rule_directory_empty_
  extern void control_print_error_parameter_action_rule_directory_empty(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_directory_empty_

/**
 * Print an error message about the given parameter being a rule action having an empty rule name.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_rule_empty_
  extern void control_print_error_parameter_action_rule_empty(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_empty_

/**
 * Print an error message about the given parameter being a rule action but no rule name is specified.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_rule_not_
  extern void control_print_error_parameter_action_rule_not(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_not_

/**
 * Print an error message about the given parameter being a rule action having too few arguments passed.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_few_
  extern void control_print_error_parameter_action_rule_too_few(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_too_few_

/**
 * Print an error message about the given parameter being a rule action having few many arguments passed for a given "with".
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 * @param with
 *   The additional parameter in which is requiring additional arguments that are not met.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_few_with_
  extern void control_print_error_parameter_action_rule_too_few_with(const fll_program_data_t * const main, const f_string_static_t action, const f_string_static_t with) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_too_few_with_

/**
 * Print an error message about the given parameter being a rule action having too many arguments passed.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_many_
  extern void control_print_error_parameter_action_rule_too_many(const fll_program_data_t * const main, const f_string_static_t action) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_too_many_

/**
 * Print an error message about the given parameter being a rule action having too many arguments passed for a given "with".
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 * @param with
 *   The additional parameter in which is requiring additional arguments that are not met.
 */
#ifndef _di_control_print_error_parameter_action_rule_too_many_with_
  extern void control_print_error_parameter_action_rule_too_many_with(const fll_program_data_t * const main, const f_string_static_t action, const f_string_static_t with) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_too_many_with_
/**
 * Print an error message about the given parameter being unknown for the use with the given action.
 *
 * @param main
 *   The main program data.
 * @param action
 *   The parameter representing an action.
 * @param with
 *   The additional parameter in which is requiring additional arguments that are not met.
 */
#ifndef _di_control_print_error_parameter_action_rule_with_unknown_
  extern void control_print_error_parameter_action_rule_with_unknown(const fll_program_data_t * const main, const f_string_static_t action, const f_string_static_t with) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_action_rule_with_unknown_

/**
 * Print an error message about the parameter's associated value being an empty string.
 *
 * @param main
 *   The main program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_control_print_error_parameter_value_empty_
  extern void control_print_error_parameter_value_empty(const fll_program_data_t * const main, const f_string_static_t parameter) F_attribute_visibility_internal_d;
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
  extern void control_print_error_parameter_value_not(const fll_program_data_t * const main, const f_string_static_t parameter) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_parameter_value_not_

/**
 * Print an error message about a pipe input being unsupported.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_control_print_error_pipe_supported_not_
  extern void control_print_error_pipe_supported_not(const fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_pipe_supported_not_

/**
 * Print an error message about the response packet format either being invalid or not supported.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_control_print_error_response_packet_valid_not_
  extern void control_print_error_response_packet_valid_not(const fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_response_packet_valid_not_

/**
 * Print an error message about the request packet being too large.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_control_print_error_request_packet_too_large_
  void extern control_print_error_request_packet_too_large(const fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_print_error_request_packet_too_large_

/**
 * Print an error message about failure to connect to the socket file.
 *
 * @param main
 *   The main program data.
 * @param path_socket
 *   The socket file path.
 */
#ifndef _di_control_print_error_socket_file_failed_
  extern void control_print_error_socket_file_failed(const fll_program_data_t * const main, const f_string_static_t path_socket) F_attribute_visibility_internal_d;
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
  extern void control_print_error_socket_file_missing(const fll_program_data_t * const main, const f_string_static_t path_socket) F_attribute_visibility_internal_d;
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
  extern void control_print_error_socket_file_not(const fll_program_data_t * const main, const f_string_static_t path_socket) F_attribute_visibility_internal_d;
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
  extern void control_print_signal_received(const fll_program_data_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_control_print_signal_received_

/**
 * Print a warning message about a response header being repeated (when debugging).
 *
 * This program currently does not support multiple headers for any given valid header Object.
 *
 * @param main
 *   The main program data.
 * @param response_header
 *   The repeated response header.
 */
#ifndef _di_control_print_warning_packet_header_duplicate_object_
  extern void control_print_warning_packet_header_duplicate_object(const fll_program_data_t * const main, const f_string_static_t response_header) F_attribute_visibility_internal_d;
#endif // _di_control_print_warning_packet_header_duplicate_object_

/**
 * Print a warning message about a failure when calling f_status_string_to().
 *
 * @param main
 *   The main program data.
 * @param status_of
 *   The status code to be translating to a string.
 * @param status_error
 *   The status code representing the failure status returned by f_status_string_to().
 *
 * @see f_status_string_to()
 */
#ifndef _di_control_print_warning_packet_process_string_to_failed_
  extern void control_print_warning_packet_process_string_to_failed(const fll_program_data_t * const main, const f_status_t status_of, const f_status_t status_error) F_attribute_visibility_internal_d;
#endif // _di_control_print_warning_packet_process_string_to_failed_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_control_print_h

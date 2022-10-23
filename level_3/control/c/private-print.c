#include "control.h"
#include "private-common.h"
#include "private-control.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_controller_packet_response_
  void control_print_controller_packet_response(const fll_program_data_t * const main, control_data_t * const data, const control_payload_header_t header, const f_string_static_t string_status) {

    if (header.status == F_failure) {
      if (main->error.verbosity == f_console_verbosity_quiet_e) return;

      f_file_stream_lock(main->error.to);

      fl_print_format("%r%[%QThe action '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
      fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, control_action_type_name(header.action), main->context.set.notable);
      fl_print_format("%[' failed with status '%]", main->error.to, main->context.set.error, main->context.set.error);
      fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, string_status, main->context.set.notable);
      fl_print_format("%[' (%]", main->error.to, main->context.set.error, main->context.set.error);
      fl_print_format("%[%ui%]", main->error.to, main->context.set.notable, header.status, main->context.set.notable);

      if (header.length) {
        fl_print_format("%[): %/Q%]%r", main->error.to, main->context.set.error, main->context.set.error, data->cache.large, data->cache.packet_contents.array[data->cache.packet_contents.used - 1].array[0], f_string_eol_s);
      }
      else {
        fl_print_format("%[).%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
      }

      f_file_stream_unlock(main->error.to);

      return;
    }

    if (header.status == F_busy) {
      if (main->warning.verbosity == f_console_verbosity_quiet_e) return;

      f_file_stream_lock(main->warning.to);

      fl_print_format("%r%[%QThe action '%]", main->warning.to, f_string_eol_s, main->context.set.warning, main->warning.prefix, main->context.set.warning);
      fl_print_format("%[%q%]", main->warning.to, main->context.set.notable, control_action_type_name(header.action), main->context.set.notable);
      fl_print_format("%[' could not be performed because the service is busy.%]%r", main->warning.to, main->context.set.warning, main->context.set.warning, f_string_eol_s);

      f_file_stream_unlock(main->warning.to);

      return;
    }

    if (main->output.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->output.to);

    fl_print_format("%rThe action '", main->output.to, f_string_eol_s);
    fl_print_format("%[%q%]", main->output.to, main->context.set.notable, control_action_type_name(header.action), main->context.set.notable);

    if (header.status == F_done) {
      fl_print_format("' is performed", main->output.to);
    }
    else {
      fl_print_format("' is successfully performed", main->output.to);
    }

    if (header.length) {
      fl_print_format(": %/Q%r", main->output.to, data->cache.large, data->cache.packet_contents.array[data->cache.packet_contents.used - 1].array[0], f_string_eol_s);
    }
    else {
      fl_print_format(".%r", main->output.to, f_string_eol_s);
    }

    f_file_stream_unlock(main->output.to);
  }
#endif // _di_control_print_controller_packet_response_

#ifndef _di_control_print_debug_packet_header_object_and_content_
  void control_print_debug_packet_header_object_and_content(const fll_program_data_t * const main, const f_string_static_t object, const f_string_static_t content, const f_string_range_t content_range) {

    if (main->output.verbosity == f_console_verbosity_debug_e) return;

    f_file_stream_lock(main->output.to);

    fl_print_format("%rPacket header Object '%[%Q%]", main->output.to, f_string_eol_s, main->context.set.notable, object, main->context.set.notable);
    fl_print_format("' has value '%[%/Q%]'.%r", main->output.to, main->context.set.notable, content, content_range, main->context.set.notable, f_string_eol_s);

    f_file_stream_unlock(main->output.to);
  }
#endif // _di_control_print_debug_packet_header_object_and_content_

#ifndef _di_control_print_debug_packet_message_
  void control_print_debug_packet_message(const fll_program_data_t * const main, const f_string_t message, const f_string_static_t *buffer, const f_string_range_t *range, const f_status_t *status) {

    if (main->output.verbosity == f_console_verbosity_debug_e) return;

    f_file_stream_lock(main->output.to);

    fl_print_format("%r%s", main->output.to, f_string_eol_s, message, main->context.set.notable, main->context.set.notable);

    if (buffer) {
      if (range) {
        fl_print_format("'%[%/Q%]'", main->output.to, main->context.set.notable, *buffer, *range, main->context.set.notable);
      }
      else {
        fl_print_format("'%[%/Q%]'", main->output.to, main->context.set.notable, *buffer, main->context.set.notable);
      }
    }

    if (status) {
      fl_print_format(", with status code %[%ui%]'", main->output.to, main->context.set.notable, *status, main->context.set.notable);
    }

    fl_print_format(".%r", main->output.to, f_string_eol_s);

    f_file_stream_unlock(main->output.to);
  }
#endif // _di_control_print_debug_packet_message_

#ifndef _di_control_print_error_packet_response_
  void control_print_error_packet_response(const fll_program_data_t * const main, control_data_t * const data, const control_payload_header_t header, const f_string_static_t string_status) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QReceived error response for " CONTROL_action_s " '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%q%]", main->error.to, main->context.set.notable, control_action_type_name(header.action), main->context.set.notable);
    fl_print_format("%[' with status '%]", main->error.to, main->context.set.error, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, string_status, main->context.set.notable);
    fl_print_format("%[' (%]", main->error.to, main->context.set.error, main->context.set.error);
    fl_print_format("%[%ui%]", main->error.to, main->context.set.notable, header.status, main->context.set.notable);

    if (header.length) {
      fl_print_format("%[): %/Q%]%r", main->error.to, main->context.set.error, main->context.set.error, data->cache.large, data->cache.packet_contents.array[data->cache.packet_contents.used - 1].array[0], f_string_eol_s);
    }
    else {
      fl_print_format("%[).%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_packet_response_

#ifndef _di_control_print_error_parameter_actions_none_
  void control_print_error_parameter_actions_none(const fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QNo actions provided.%]%r", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_parameter_actions_none_

#ifndef _di_control_print_error_parameter_action_not_
  void control_print_error_parameter_action_not(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' is not a known controller action.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_not_

#ifndef _di_control_print_error_parameter_action_rule_basename_empty_
  void control_print_error_parameter_action_rule_basename_empty(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' a rule base name cannot be an empty string.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_basename_empty_

#ifndef _di_control_print_error_parameter_action_rule_directory_empty_
  void control_print_error_parameter_action_rule_directory_empty(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' a rule directory path cannot be an empty string.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_directory_empty_

#ifndef _di_control_print_error_parameter_action_rule_empty_
  void control_print_error_parameter_action_rule_empty(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' a rule name cannot be an empty string.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_empty_

#ifndef _di_control_print_error_parameter_action_rule_not_
  void control_print_error_parameter_action_rule_not(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' requires either a full rule name or a rule directory path along with the rule base name.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_not_

#ifndef _di_control_print_error_parameter_action_rule_too_few_
  void control_print_error_parameter_action_rule_too_few(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' has too few arguments.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_too_few_

#ifndef _di_control_print_error_parameter_action_rule_too_few_with_
  void control_print_error_parameter_action_rule_too_few_with(const fll_program_data_t * const main, const f_string_static_t action, const f_string_static_t with) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' when used with '%]", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, with, main->context.set.notable);
    fl_print_format("%[' has too few arguments.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_too_few_with_

#ifndef _di_control_print_error_parameter_action_rule_too_many_
  void control_print_error_parameter_action_rule_too_many(const fll_program_data_t * const main, const f_string_static_t action) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' has too many arguments.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_too_many_

#ifndef _di_control_print_error_parameter_action_rule_too_many_with_
  void control_print_error_parameter_action_rule_too_many_with(const fll_program_data_t * const main, const f_string_static_t action, const f_string_static_t with) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' when used with '%]", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, with, main->context.set.notable);
    fl_print_format("%[' has too many arguments.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_too_many_with_

#ifndef _di_control_print_error_parameter_action_rule_with_unknown_
  void control_print_error_parameter_action_rule_with_unknown(const fll_program_data_t * const main, const f_string_static_t action, const f_string_static_t with) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe action parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, action, main->context.set.notable);
    fl_print_format("%[' does not know the argument '%]", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, with, main->context.set.notable);
    fl_print_format("%['.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_action_rule_with_unknown_

#ifndef _di_control_print_error_parameter_value_empty_
  void control_print_error_parameter_value_empty(const fll_program_data_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' must not be an empty string.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_value_empty_

#ifndef _di_control_print_error_parameter_value_not_
  void control_print_error_parameter_value_not(const fll_program_data_t * const main, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%r%r%]", main->error.to, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_parameter_value_not_

#ifndef _di_control_print_error_pipe_supported_not_
  void control_print_error_pipe_supported_not(const fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QPipe input is not supported by this program.%]%r", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_pipe_supported_not_

#ifndef _di_control_print_error_response_packet_valid_not_
  void control_print_error_response_packet_valid_not(const fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QThe received response is not a valid or supported packet.%]%r", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_response_packet_valid_not_

#ifndef _di_control_print_error_request_packet_too_large_
  void control_print_error_request_packet_too_large(const fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    fll_print_format("%r%[%QThe generated packet is too large, cannot send packet.%]%r", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error, f_string_eol_s);
  }
#endif // _di_control_print_error_request_packet_too_large_

#ifndef _di_control_print_error_socket_file_failed_
  void control_print_error_socket_file_failed(const fll_program_data_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QFailed to connect to the socket file '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%['.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_socket_file_failed_

#ifndef _di_control_print_error_socket_file_missing_
  void control_print_error_socket_file_missing(const fll_program_data_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe controller socket file '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%[' could not be found and is required.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_socket_file_missing_

#ifndef _di_control_print_error_socket_file_not_
  void control_print_error_socket_file_not(const fll_program_data_t * const main, const f_string_static_t path_socket) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(main->error.to);

    fl_print_format("%r%[%QThe controller socket file '%]", main->error.to, f_string_eol_s, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, path_socket, main->context.set.notable);
    fl_print_format("%[' is not a socket file.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);
  }
#endif // _di_control_print_error_socket_file_not_

#ifndef _di_control_print_warning_packet_header_duplicate_object_
  void control_print_warning_packet_header_duplicate_object(const fll_program_data_t * const main, const f_string_static_t response_header) {

    if (main->warning.verbosity == f_console_verbosity_debug_e) return;

    f_file_stream_lock(main->warning.to);

    fl_print_format("%r%[%QThe received response header '%]", main->warning.to, f_string_eol_s, main->context.set.warning, main->warning.prefix, main->context.set.warning);
    fl_print_format("%[%Q%]", main->warning.to, main->context.set.notable, response_header, main->context.set.notable);
    fl_print_format("%[' is repeated.%]%r", main->warning.to, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    f_file_stream_unlock(main->warning.to);
  }
#endif // _di_control_print_warning_packet_header_duplicate_object_

#ifndef _di_control_print_warning_packet_process_string_to_failed_
  void control_print_warning_packet_process_string_to_failed(const fll_program_data_t * const main, const f_status_t status_of, const f_status_t status_error) {

    if (main->warning.verbosity == f_console_verbosity_debug_e) return;

    f_file_stream_lock(main->warning.to);

    fl_print_format("%r%[%QFailed while calling f_status_string_to() for status%] ", main->output.to, f_string_eol_s, main->context.set.warning, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%ui%]", main->output.to, main->context.set.notable, status_of, main->context.set.notable);
    fl_print_format("%[, failing with status code%] ", main->output.to, main->context.set.warning, status_error, main->context.set.warning);
    fl_print_format("%[%ui%]", main->output.to, main->context.set.notable, status_error, main->context.set.notable);
    fl_print_format("%[.%]%r", main->output.to, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    f_file_stream_unlock(main->warning.to);
  }
#endif // _di_control_print_warning_packet_process_string_to_failed_

#ifdef __cplusplus
} // extern "C"
#endif

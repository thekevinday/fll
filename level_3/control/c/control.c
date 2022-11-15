#include "control.h"
#include "private-common.h"
#include "private-control.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_main_
  f_status_t control_main(fll_program_data_t * const main, control_setting_t * const setting) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { control_parameter_no_color_e, control_parameter_light_e, control_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          control_print_line_first_locked(setting, main->error)
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);
          control_print_line_last_locked(setting, main->error);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { control_parameter_verbosity_quiet_e, control_parameter_verbosity_error_e, control_parameter_verbosity_verbose_e, control_parameter_verbosity_debug_e, control_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          control_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);
          control_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    status = F_none;

    if (main->parameters.array[control_parameter_help_e].result == f_console_result_found_e) {
      control_print_help(main);

      return F_none;
    }

    if (main->parameters.array[control_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->message, control_program_version_s);

      return F_none;
    }

    {
      uint8_t ids[] = {
        control_parameter_name_e,
        control_parameter_settings_e,
        control_parameter_socket_e
      };

      f_string_static_t names[] = {
        control_long_name_s,
        control_long_settings_s,
        control_long_socket_s
      };

      f_array_length_t index = f_array_length_t_initialize;

      for (uint8_t i = 0; i < 3; ++i) {

        if (main->parameters.array[ids[i]].result == f_console_result_found_e) {
          control_print_error_parameter_value_not(main, names[i]);

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters.array[ids[i]].result == f_console_result_additional_e) {
          index = main->parameters.array[ids[i]].values.array[main->parameters.array[ids[i]].values.used - 1];

          if (!main->parameters.arguments.array[index].used) {
            control_print_error_parameter_value_empty(main, names[i]);

            status = F_status_set_error(F_parameter);
          }
        }
      } // for
    }

    if (F_status_is_error_not(status)) {
      if (main->pipe & fll_program_data_pipe_input_e) {
        control_print_error_pipe_supported_not(main);

        status = F_status_set_error(F_supported_not);
      }
      else if (main->parameters.remaining.used) {
        control_data_t data = control_data_t_initialize;
        data.argv = main->parameters.arguments.array;

        data.action = control_action_type_identify(data.argv[main->parameters.remaining.array[0]]);

        if (data.action) {
          status = control_action_verify(main, &data);
        }
        else {
          control_print_error_parameter_action_not(main, data.argv[main->parameters.remaining.array[0]]);

          status = F_status_set_error(F_parameter);
        }

        if (F_status_is_error_not(status)) {
          struct sockaddr_un socket_address;

          memset(&socket_address, 0, sizeof(struct sockaddr_un));

          data.socket.address = (struct sockaddr *) &socket_address;
          data.socket.domain = f_socket_domain_file_d;
          data.socket.type = f_socket_type_stream_d;
          data.socket.length = sizeof(struct sockaddr_un);

          status = control_settings_load(main, &data);

          if (F_status_is_error_not(status)) {
            status = control_packet_build(main, &data);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_too_large) {
                control_print_error_request_packet_too_large(main);
              }
              else {
                fll_error_print(main->error, F_status_set_fine(status), "control_packet_build", F_true);
              }
            }
          }

          if (F_status_is_error_not(status)) {
            status = control_packet_send(main, &data);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "control_packet_send", F_true);
            }
          }

          if (F_status_is_error_not(status)) {
            control_payload_header_t header = control_payload_header_t_initialize;

            status = control_packet_receive(main, &data, &header);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_too_large) {
                control_print_error_response_packet_valid_not(main);
              }
              else {
                fll_error_print(main->error, F_status_set_fine(status), "control_packet_receive", F_true);
              }
            }
            else {
              status = control_packet_process(main, &data, &header);

              // Print the error message only if the error message is not already printed.
              if (F_status_is_error(status)) {
                if (header.type != control_payload_type_error_e && (header.type != control_payload_type_controller_e || F_status_set_fine(status) != header.status || (header.status != F_failure && header.status != F_busy))) {
                  fll_error_print(main->error, F_status_set_fine(status), "control_packet_process", F_true);
                }
              }
            }
          }

          if (data.socket.id != -1) {
            f_socket_disconnect(&data.socket, f_socket_close_fast_e);
          }
        }

        control_data_delete(&data);
      }
      else {
        control_print_error_parameter_actions_none(main);

        status = F_status_set_error(F_data_not);
      }
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        f_file_stream_flush(main->output.to);
        f_file_stream_flush(main->error.to);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to);
      }
    }

    return status;
  }
#endif // _di_control_main_

#ifdef __cplusplus
} // extern "C"
#endif

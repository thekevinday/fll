#include "control.h"
#include "private-common.h"
#include "private-control.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_help_
  f_status_t control_print_help(control_main_t * const main) {

    flockfile(main->output.to.stream);

    fll_program_print_help_header(main->output.to, main->context, control_program_name_long_s, control_program_version_s);

    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not main->output.to in color.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic(f_string_eol_s, main->output.to.stream);

    fll_program_print_help_option(main->output.to, main->context, control_short_name_s, control_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Specify the name of the controller socket file.");
    fll_program_print_help_option(main->output.to, main->context, control_short_settings_s, control_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Specify a directory path or a full path to the control settings file.");
    fll_program_print_help_option(main->output.to, main->context, control_short_socket_s, control_long_socket_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Specify a directory path or a full path to the controller socket file.");

    fll_program_print_help_usage(main->output.to, main->context, control_program_name_s, control_command_s);

    fl_print_format("  When the %[%q%q%] parameter represents a directory path then the file name is generated from either the", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, control_long_socket_s, main->context.set.notable);
    fl_print_format(" %[%q%q%] parameter or from the control settings file.%q%q", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, control_long_name_s, main->context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  A rule action allows for either the full rule path, such as '%[boot/root%]'", main->output.to.stream, main->context.set.notable, main->context.set.notable);
    fl_print_format(" as a single parameter or two parameters with the first representing the rule directory path '%[boot%]'", main->output.to.stream, main->context.set.notable, main->context.set.notable);
    fl_print_format(" and the second representing the rule base name '%[root%]'.%q%q", main->output.to.stream, main->context.set.notable, main->context.set.notable, f_string_eol_s, f_string_eol_s);

    fflush(main->output.to.stream);
    funlockfile(main->output.to.stream);

    return F_none;
  }
#endif // _di_control_print_help_

#ifndef _di_control_main_
  f_status_t control_main(control_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    f_console_parameter_t parameters[] = control_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = control_total_parameters_d;

    {
      f_console_parameter_id_t ids[3] = { control_parameter_no_color_e, control_parameter_light_e, control_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->remaining, &main->context);

      main->output.set = &main->context.set;
      main->error.set = &main->context.set;
      main->warning.set = &main->context.set;

      if (main->context.set.error.before) {
        main->output.context = f_color_set_empty_s;
        main->output.notable = main->context.set.notable;

        main->error.context = main->context.set.error;
        main->error.notable = main->context.set.notable;

        main->warning.context = main->context.set.warning;
        main->warning.notable = main->context.set.notable;
      }
      else {
        f_color_set_t *sets[] = { &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

        fll_program_parameter_process_empty(&main->context, sets);
      }

      if (F_status_is_error(status)) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
          fll_print_dynamic(f_string_eol_s, main->error.to.stream);
        }

        control_main_delete(main);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { control_parameter_verbosity_quiet_e, control_parameter_verbosity_normal_e, control_parameter_verbosity_verbose_e, control_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        control_main_delete(main);

        return status;
      }

      if (choice == control_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == control_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == control_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == control_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    status = F_none;

    if (main->parameters.array[control_parameter_help_e].result == f_console_result_found_e) {
      control_print_help(main);

      control_main_delete(main);

      return F_none;
    }

    if (main->parameters.array[control_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, control_program_version_s);

      control_main_delete(main);

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
      if (main->process_pipe) {
        control_print_error_pipe_supported_not(main);

        status = F_status_set_error(F_supported_not);
      }
      else if (main->remaining.used) {
        control_data_t data = control_data_t_initialize;
        data.argv = main->parameters.arguments.array;

        // Verify commands before attempting to connect to the socket.
        if (control_command_identify(main, &data, data.argv[main->remaining.array[0]]) == F_found) {
          status = control_command_verify(main, &data);
        }
        else {
          control_print_error_parameter_command_not(main, data.argv[main->remaining.array[0]]);

          status = F_status_set_error(F_parameter);
        }

        if (F_status_is_error_not(status)) {
          struct sockaddr_un socket_address;

          memset(&socket_address, 0, sizeof(struct sockaddr_un));

          data.socket.address = (struct sockaddr *) &socket_address;
          data.socket.domain = f_socket_domain_file_d;
          data.socket.type = f_socket_type_datagram_d;
          data.socket.length = sizeof(struct sockaddr_un);

          status = control_settings_load(main, &data);

          if (F_status_is_error_not(status)) {
            // @todo construct the packet, send the packet to the controller, and process the response.
          }

          if (data.socket.id != -1) {
            f_socket_disconnect(&data.socket, f_socket_close_fast_e);
          }
        }

        control_data_delete(&data);
      }
      else {
        control_print_error_commands_none(main);

        status = F_status_set_error(F_data_not);
      }
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        fflush(main->output.to.stream);
        fflush(main->error.to.stream);

        fll_print_dynamic(f_string_eol_s, main->output.to.stream);
      }
    }

    control_main_delete(main);

    return status;
  }
#endif // _di_control_main_

#ifdef __cplusplus
} // extern "C"
#endif

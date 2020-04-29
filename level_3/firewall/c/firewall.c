/**
 * FLL - Level 3
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#include <level_3/firewall.h>
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_help_
  f_return_status firewall_print_help(const fl_color_context context) {
    fll_program_print_help_header(context, firewall_name_long, firewall_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    #ifdef _en_firewall_debug_
      fll_program_print_help_option(context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging.");
    #endif // _en_firewall_debug_

    printf("%c%c", f_string_eol, f_string_eol);
    fl_color_print(f_standard_output, context.important, context.reset, " Available Commands: ");

    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, firewall_command_start);
    printf("    Turn on the firewall");

    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, firewall_command_stop);
    printf("     Turn off the firewall");

    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, firewall_command_restart);
    printf("  Turn off and then turn on the firewall");

    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, firewall_command_lock);
    printf("     Prevent all communication");

    printf("%c  ", f_string_eol);
    fl_color_print(f_standard_output, context.standout, context.reset, firewall_command_show);
    printf("     Show active firewall settings");

    fll_program_print_help_usage(context, firewall_name, "command");

    return f_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_return_status firewall_main(const f_console_arguments arguments, firewall_data *data) {
    f_status status = f_none;

    {
      f_console_parameters parameters = { data->parameters, firewall_total_parameters };
      f_console_parameter_id ids[3] = { firewall_parameter_no_color, firewall_parameter_light, firewall_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

      status = fll_program_parameter_process(arguments, parameters, choices, &data->remaining, &data->context);
    }

    if (f_status_is_error(status)) {
      firewall_delete_data(data);
      return f_status_set_error(status);
    }

    status = f_none;

    if (data->parameters[firewall_parameter_help].result == f_console_result_found) {
      firewall_print_help(data->context);
    }
    else if (data->parameters[firewall_parameter_version].result == f_console_result_found) {
      fll_program_print_version(firewall_version);
    }
    else {
      // now determine which command was placed first
      bool found_command = f_false;
      unsigned int command = 0;

      if (data->parameters[firewall_parameter_command_start].result == f_console_result_found) {
        command = firewall_parameter_command_start;
        found_command = f_true;
      }

      if (data->parameters[firewall_parameter_command_stop].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_stop].additional.array[0]) {
            command = firewall_parameter_command_stop;
          }
        }
        else {
          command = firewall_parameter_command_stop;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_restart].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_restart].additional.array[0]) {
            command = firewall_parameter_command_restart;
          }
        }
        else {
          command = firewall_parameter_command_restart;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_lock].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_lock].additional.array[0]) {
            command = firewall_parameter_command_lock;
          }
        }
        else {
          command = firewall_parameter_command_lock;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_show].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_show].additional.array[0]) {
            command = firewall_parameter_command_show;
          }
        }
        else {
          command = firewall_parameter_command_show;
          found_command = f_true;
        }
      }

      if (found_command) {
        firewall_local_data local = firewall_local_data_initialize;
        firewall_reserved_chains reserved = firewall_reserved_chains_initialize;
        f_string_location input = f_string_location_initialize;

        if (command == firewall_parameter_command_show) {
          // Warning: these are hardcoded print commands (I am not certain how I am going to implement external 'show' rules as the default-firewall setting file is the wrong place to put this)
          bool show_nat = f_true;
          bool show_mangle = f_true;
          bool show_ports = f_true;

          f_string_dynamics parameters = f_string_dynamics_initialize;
          int results = 0;

          if (data->remaining.used > 0) {
            show_nat = f_false;
            show_mangle = f_false;
            show_ports = f_false;

            f_string_length counter = 0;

            for (; counter < data->remaining.used; counter++) {
              if (strncmp("nat", arguments.argv[data->remaining.array[counter]], 4) != 0) {
                if (strncmp("mangle",  arguments.argv[data->remaining.array[counter]], 7) != 0) {
                  if (strncmp("ports",  arguments.argv[data->remaining.array[counter]], 6) != 0) {
                    fl_color_print_line(f_standard_warning, data->context.warning, data->context.reset, "WARNING: '%s' is not a valid show option", arguments.argv[data->remaining.array[counter]]);
                  }
                  else {
                    show_ports = f_true;
                  }
                }
                else {
                  show_mangle = f_true;
                }
              }
              else {
                show_nat = f_true;
              }
            } // for
          }

          f_macro_string_dynamics_resize(status, parameters, 7);

          if (f_status_is_error(status)) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: Unable to allocate memory.");
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          if (show_nat) {
            fl_color_print(f_standard_output, data->context.standout, data->context.reset, "=========================== ");
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "NAT");
            fl_color_print_line(f_standard_output, data->context.standout, data->context.reset, " ============================");
            fflush(f_standard_output);

            parameters.used = 6;

            parameters.array[0].string = (f_string) "-x";
            parameters.array[1].string = (f_string) "-v";
            parameters.array[2].string = (f_string) "-t";
            parameters.array[3].string = (f_string) "nat";
            parameters.array[4].string = (f_string) "--numeric";
            parameters.array[5].string = (f_string) "--list";

            parameters.array[0].used = 2;
            parameters.array[1].used = 2;
            parameters.array[2].used = 2;
            parameters.array[3].used = 3;
            parameters.array[4].used = 9;
            parameters.array[5].used = 6;

            status = fll_execute_program((f_string) firewall_tool_iptables, parameters, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (f_status_is_not_error(status) && show_mangle) {
            fl_color_print(f_standard_output, data->context.standout, data->context.reset, "========================== ");
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "MANGLE");
            fl_color_print_line(f_standard_output, data->context.standout, data->context.reset, " ==========================");
            fflush(f_standard_output);

            parameters.used = 6;

            parameters.array[0].string = (f_string) "-x";
            parameters.array[1].string = (f_string) "-v";
            parameters.array[2].string = (f_string) "-t";
            parameters.array[3].string = (f_string) "mangle";
            parameters.array[4].string = (f_string) "--numeric";
            parameters.array[5].string = (f_string) "--list";

            parameters.array[0].used = 2;
            parameters.array[1].used = 2;
            parameters.array[2].used = 2;
            parameters.array[3].used = 6;
            parameters.array[4].used = 9;
            parameters.array[5].used = 6;

            status = fll_execute_program((f_string) firewall_tool_iptables, parameters, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (f_status_is_not_error(status) && show_ports) {
            fl_color_print(f_standard_output, data->context.standout, data->context.reset, "========================== ");
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "FILTER");
            fl_color_print_line(f_standard_output, data->context.standout, data->context.reset, " ==========================");
            fflush(f_standard_output);

            parameters.used = 4;

            parameters.array[0].string = (f_string) "-x";
            parameters.array[1].string = (f_string) "-v";
            parameters.array[2].string = (f_string) "--numeric";
            parameters.array[3].string = (f_string) "--list";

            parameters.array[0].used = 2;
            parameters.array[1].used = 2;
            parameters.array[2].used = 9;
            parameters.array[3].used = 6;

            status = fll_execute_program((f_string) firewall_tool_iptables, parameters, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (f_status_is_error(status)) {
            status = f_status_set_fine(status);

            if (status == f_error_allocation || status == f_error_reallocation) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: Unable to allocate memory.");
            }
            else {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_tool_iptables);
              fprintf(f_standard_error, "  ");

              f_string_length i = 0;

              fl_color_print_code(f_standard_error, data->context.error);

              fprintf(f_standard_error, "%s ", firewall_tool_iptables);
              for (; i < parameters.used; i++) {
                fprintf(f_standard_error, "%s ", parameters.array[i].string);
              } // for

              fl_color_print_code(f_standard_error, data->context.reset);
              fprintf(f_standard_error, "\n");
            }

            status = f_status_set_error(status);
          }

          parameters.array[0].string = 0;
          parameters.array[1].string = 0;
          parameters.array[2].string = 0;
          parameters.array[3].string = 0;
          parameters.array[4].string = 0;
          parameters.array[5].string = 0;
          parameters.array[6].string = 0;
          parameters.array[0].used = 0;
          parameters.array[1].used = 0;
          parameters.array[2].used = 0;
          parameters.array[3].used = 0;
          parameters.array[4].used = 0;
          parameters.array[5].used = 0;
          parameters.array[6].used = 0;

          f_macro_string_dynamics_delete_simple( parameters);
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        // load all network devices
        status = fl_directory_list((f_string) network_devices, 0, alphasort, &data->devices);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_error_allocation || status == f_error_reallocation) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: Unable to allocate memory.");
          }
          else if (status == f_no_data) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: could not find any network devices");
          }
          else if (status == f_failure) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to read the device directory '%s'", network_devices);
          }

          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return f_status_set_error(status);
        }

        // remove "lo" (loopback) from the device listing
        {
          f_string_length i = 0;

          for (; i < data->devices.used; i++) {
            if (fl_string_compare((f_string) firewall_device_loop, data->devices.array[i].string, firewall_device_loop_length + 1, data->devices.array[i].used) == f_equal_to) {
              f_string_dynamic swap_string = data->devices.array[i];

              data->devices.used--;

              for (; i < data->devices.used; i++) {
                data->devices.array[i] = data->devices.array[i+1];
              } // for

              data->devices.array[data->devices.used] = swap_string;
            }
          } // for
        }

        if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart || command == firewall_parameter_command_lock) {
          status = firewall_buffer_rules(network_path firewall_file_other, f_false, &local, data);

          if (f_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          {
            f_array_length i = 0;
            f_string_length length = 0;

            for (; i < local.chain_objects.used; i++) {
              length = local.chain_objects.array[i].stop - local.chain_objects.array[i].start + 1;

              if (!reserved.has_stop && fl_string_compare((f_string) firewall_group_stop, local.buffer.string + local.chain_objects.array[i].start, firewall_group_stop_length, length) == f_equal_to) {
                reserved.stop_at = i;
                reserved.has_stop = f_true;
              }
              else if (!reserved.has_lock && fl_string_compare((f_string) firewall_group_lock, local.buffer.string + local.chain_objects.array[i].start, firewall_group_lock_length, length) == f_equal_to) {
                reserved.lock_at = i;
                reserved.has_lock = f_true;
              }
            } // for
          }

          if (command == firewall_parameter_command_lock) {
            if (reserved.has_lock) {
              status = firewall_delete_chains(*data);

              if (f_status_is_not_error(status)) {
                status = firewall_default_lock(*data);
              }

              if (f_status_is_error(status)) {
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }

              local.is_main = f_false;
              local.is_stop = f_false;
              local.is_lock = f_true;
              local.chain = reserved.lock_at;

              input.start = local.chain_contents.array[reserved.lock_at].array[0].start;
              input.stop = local.chain_contents.array[reserved.lock_at].array[0].stop;

              status = firewall_process_rules(&input, &local, data);

              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }
            else {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform lock request because the lock instructions are missing from: %s.", network_path firewall_file_other);

              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return f_status_set_error(f_invalid_data);
            }
          }

          if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart) {
            if (reserved.has_stop) {
              status = firewall_delete_chains(*data);

              if (f_status_is_not_error(status)) {
                status = firewall_default_lock(*data);
              }

              if (f_status_is_error(status)) {
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }

              local.is_global = f_true;
              local.is_main = f_false;
              local.is_stop = f_true;
              local.is_lock = f_false;
              local.chain = reserved.stop_at;

              input.start = local.chain_contents.array[reserved.stop_at].array[0].start;
              input.stop = local.chain_contents.array[reserved.stop_at].array[0].stop;

              status = firewall_process_rules(&input, &local, data);

              if (f_status_is_error(status) || command == firewall_parameter_command_stop) {
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }
            }
            else {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform stop request because the lock instructions are missing from: %s.", network_path firewall_file_other);

              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return f_status_set_error(f_invalid_data);
            }
          }

          firewall_delete_local_data(&local);
        }

        if (command == firewall_parameter_command_start || command == firewall_parameter_command_restart) {
          status = firewall_buffer_rules(network_path firewall_file_first, f_false, &local, data);

          if (f_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          if (command == firewall_parameter_command_start) {
            status = firewall_delete_chains(*data);

            if (f_status_is_not_error(status)) {
              status = firewall_default_lock(*data);
            }

            if (f_status_is_error(status)) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }
          }

          status = firewall_create_custom_chains(&reserved, &local, data);

          if (f_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          f_array_length i = 0;

          local.is_global = f_true;
          local.is_stop = f_false;
          local.is_lock = f_false;

          while (i < local.chain_contents.used) {
            input.start = local.chain_contents.array[i].array[0].start;
            input.stop = local.chain_contents.array[i].array[0].stop;

            local.is_main = reserved.has_main && i == reserved.main_at ? f_true : f_false;
            local.chain = i;

            status = firewall_process_rules(&input, &local, data);

            if (f_status_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            i++;
          } // while

          firewall_delete_local_data(&local);

          for (i = 0; i < data->devices.used; i++) {
            local.device = i;

            {
              f_string_dynamic file_path = f_string_dynamic_initialize;

              f_macro_string_dynamic_resize(status, file_path, network_path_length + data->devices.array[i].used + firewall_file_suffix_length + 1);

              if (f_status_is_error(status)) {
                fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: Unable to allocate memory.");
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }

              memcpy((void *)file_path.string, network_path, network_path_length);
              memcpy((void *)(file_path.string + network_path_length), data->devices.array[i].string, data->devices.array[i].used);
              memcpy((void *)(file_path.string + network_path_length + data->devices.array[i].used), firewall_file_suffix, firewall_file_suffix_length);

              file_path.used = network_path_length + data->devices.array[i].used + firewall_file_suffix_length;
              file_path.string[file_path.used] = 0;

              status = firewall_buffer_rules(file_path.string, f_true, &local, data);

              f_macro_string_dynamic_delete_simple(file_path);
            }

            if (f_status_is_error(status)) {
              status = f_status_set_fine(status);

              firewall_delete_local_data(&local);

              if (status == f_file_not_found || status == f_file_error_open || status == f_file_error_descriptor || status == fl_fss_found_object_no_content) {
                status = f_status_set_error(status);
                continue;
              }

              firewall_delete_data(data);
              return f_status_set_error(status);
            }

            status = firewall_create_custom_chains(&reserved, &local, data);

            if (f_status_is_error(status)) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            f_array_length j = 0;

            local.is_global = f_false;
            local.is_stop = f_false;
            local.is_lock = f_false;

            for (; j < local.chain_contents.used; j++) {
              input.start = local.chain_contents.array[j].array[0].start;
              input.stop = local.chain_contents.array[j].array[0].stop;

              local.is_main = reserved.has_main && j == reserved.main_at ? f_true : f_false;
              local.chain = j;

              status = firewall_process_rules(&input, &local, data);

              if (f_status_is_error(status) || command == firewall_parameter_command_stop) {
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }
            } // for

            firewall_delete_local_data(&local);
          } // for

          status = firewall_buffer_rules(network_path firewall_file_last, f_false, &local, data);

          if (f_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          status = firewall_create_custom_chains(&reserved, &local, data);

          if (f_status_is_error(status)) {
            f_status status2 = f_none;

            firewall_macro_delete_fss_buffers(status2, local.buffer, local.chain_objects, local.chain_contents)
            firewall_delete_data(data);
            return status;
          }

          i = 0;

          local.is_global = f_true;
          local.is_stop = f_false;
          local.is_lock = f_false;

          while (i < local.chain_contents.used) {
            input.start = local.chain_contents.array[i].array[0].start;
            input.stop = local.chain_contents.array[i].array[0].stop;

            local.is_main = reserved.has_main && i == reserved.main_at ? f_true : f_false;
            local.chain = i;

            status = firewall_process_rules(&input, &local, data);

            if (f_status_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            i++;
          } // while
        }

        // cleanup
        firewall_delete_local_data(&local);
      }
      else {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: You did not pass a command");
        status = f_status_set_error(f_invalid_parameter);
      }
    }

    firewall_delete_data(data);
    return status;
  }
#endif // _di_firewall_main_

#ifndef _di_firewall_delete_data_
  f_return_status firewall_delete_data(firewall_data *data) {
    f_string_length i = 0;

    while (i < firewall_total_parameters) {
      f_macro_string_lengths_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_dynamics_delete_simple(data->chains);
    f_macro_string_lengths_delete_simple(data->remaining);
    f_macro_string_dynamics_delete_simple(data->devices);

    fl_macro_color_context_delete_simple(data->context);

    return f_none;
  }
#endif // _di_firewall_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

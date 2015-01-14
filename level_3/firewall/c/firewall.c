/* FLL - Level 3
 * Project:       Firewall
 * Version:       0.4.2
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_3/firewall.h>
#include "private-firewall.h"

#ifdef __cplusplus
extern "C"{
#endif

// version printed may be used by scripts, so this will only print the version number and a newline, no extra information or colors
#ifndef _di_firewall_print_version_
  f_return_status firewall_print_version(const firewall_data data) {
    printf("%s\n", firewall_version);

    return f_none;
  }
#endif // _firewall_print_version_

#ifndef _di_firewall_print_help_
  f_return_status firewall_print_help(const firewall_data data) {
    printf("\n");
    fl_print_color(f_standard_output, data.context.title, data.context.reset, " %s", firewall_name_long);

    printf("\n");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "  Version %s", firewall_version);

    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Available Options: ");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_help);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_help);
    printf("      Print this help message");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_light);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_light);
    printf("     Output using colors that show up better on light backgrounds");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_no_color);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_no_color);
    printf("  Do not output in color");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_version);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_version);
    printf("   Print only the version number");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_debug);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_debug);
    printf("   Enable debugging");

    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Available Commands: ");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_start);
    printf("    Turn on the firewall");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_stop);
    printf("     Turn off the firewall");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_restart);
    printf("  Turn off and then turn on the firewall");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_lock);
    printf("     Prevent all communication");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_show);
    printf("     Show active firewall settings");

    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Usage: ");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_name);

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" options ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" command ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("\n\n");

    return f_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_return_status firewall_main(const f_s_int argc, const f_string argv[], firewall_data *data) {
    f_status status  = f_none;
    f_status status2 = f_none;

    status = fl_process_parameters(argc, argv, data->parameters, firewall_total_parameters, &data->remaining);

    // load colors when not told to show no colors
    if (data->parameters[firewall_parameter_no_color].result == f_console_result_none) {
      fl_new_color_context(status2, data->context);

      if (status2 == f_none) {
        fll_colors_load_context(&data->context, data->parameters[firewall_parameter_light].result == f_console_result_found);
      } else {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        firewall_delete_data(data);
        return status2;
      }
    }

    if (f_error_is_error(status)) {
      status = f_error_set_fine(status);

      if (status == f_no_data) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      } else if (f_macro_test_for_allocation_errors(status)) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
      } else if (f_error_set_fine(status) == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_process_parameters()");
      } else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_process_parameters()", f_error_set_error(status));
      }

      firewall_delete_data(data);
      return f_error_set_error(status);
    }

    // execute parameter results
    if (data->parameters[firewall_parameter_help].result == f_console_result_found) {
      firewall_print_help(*data);
    } else if (data->parameters[firewall_parameter_version].result == f_console_result_found) {
      firewall_print_version(*data);
    } else {
      // now determine which command was placed first
      f_bool  found_command = f_false;
      f_u_int command       = 0;

      if (data->parameters[firewall_parameter_command_start].result == f_console_result_found) {
        command       = firewall_parameter_command_start;
        found_command = f_true;
      }

      if (data->parameters[firewall_parameter_command_stop].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_stop].additional.array[0]) {
            command = firewall_parameter_command_stop;
          }
        } else {
          command       = firewall_parameter_command_stop;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_restart].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_restart].additional.array[0]) {
            command = firewall_parameter_command_restart;
          }
        } else {
          command       = firewall_parameter_command_restart;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_lock].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_lock].additional.array[0]) {
            command = firewall_parameter_command_lock;
          }
        } else {
          command       = firewall_parameter_command_lock;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_show].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_show].additional.array[0]) {
            command = firewall_parameter_command_show;
          }
        } else {
          command       = firewall_parameter_command_show;
          found_command = f_true;
        }
      }

      if (found_command) {
        firewall_local_data local = firewall_local_data_initialize;
        firewall_reserved_chains reserved = firewall_reserved_chains_initialize;
        f_string_location input = f_string_location_initialize;

        if (command == firewall_parameter_command_show) {
          // Warning: these are hardcoded print commands (I am not certain how I am going to implement external 'show' rules as the default-firewall setting file is the wrong place to put this)
          f_bool show_nat    = f_true;
          f_bool show_mangle = f_true;
          f_bool show_ports  = f_true;

          f_dynamic_strings arguments = f_dynamic_strings_initialize;
          f_s_int           results   = 0;

          if (data->remaining.used > 0) {
            show_nat    = f_false;
            show_mangle = f_false;
            show_ports  = f_false;

            f_string_length counter = 0;

            for (; counter < data->remaining.used; counter++) {
              if (strncmp("nat", argv[data->remaining.array[counter]], 4) != 0) {
                if (strncmp("mangle",  argv[data->remaining.array[counter]], 7) != 0) {
                  if (strncmp("ports",  argv[data->remaining.array[counter]], 6) != 0) {
                    fl_print_color_line(f_standard_warning, data->context.warning, data->context.reset, "WARNING: '%s' is not a valid show option", argv[data->remaining.array[counter]]);
                  } else {
                    show_ports = f_true;
                  }
                } else {
                  show_mangle = f_true;
                }
              } else {
                show_nat = f_true;
              }
            } // for
          }

          f_resize_dynamic_strings(status, arguments, 7);

          if (f_error_is_error(status)) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          if (show_nat) {
            fl_print_color(f_standard_output, data->context.standout, data->context.reset, "=========================== ");
            fl_print_color(f_standard_output, data->context.title, data->context.reset, "NAT");
            fl_print_color_line(f_standard_output, data->context.standout, data->context.reset, " ============================");
            fflush(f_standard_output);

            arguments.used = 7;

            arguments.array[0].string = (f_string) firewall_tool_iptables;
            arguments.array[1].string = (f_string) "-x";
            arguments.array[2].string = (f_string) "-v";
            arguments.array[3].string = (f_string) "-t";
            arguments.array[4].string = (f_string) "nat";
            arguments.array[5].string = (f_string) "--numeric";
            arguments.array[6].string = (f_string) "--list";

            arguments.array[0].used = firewall_tool_iptables_length;
            arguments.array[1].used = 2;
            arguments.array[2].used = 2;
            arguments.array[3].used = 2;
            arguments.array[4].used = 3;
            arguments.array[5].used = 9;
            arguments.array[6].used = 6;

            status = fll_execute_program((f_string) firewall_tool_iptables, arguments, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (f_error_is_not_error(status) && show_mangle) {
            fl_print_color(f_standard_output, data->context.standout, data->context.reset, "========================== ");
            fl_print_color(f_standard_output, data->context.title, data->context.reset, "MANGLE");
            fl_print_color_line(f_standard_output, data->context.standout, data->context.reset, " ==========================");
            fflush(f_standard_output);

            arguments.used = 7;

            arguments.array[0].string = (f_string) firewall_tool_iptables;
            arguments.array[1].string = (f_string) "-x";
            arguments.array[2].string = (f_string) "-v";
            arguments.array[3].string = (f_string) "-t";
            arguments.array[4].string = (f_string) "mangle";
            arguments.array[5].string = (f_string) "--numeric";
            arguments.array[6].string = (f_string) "--list";

            arguments.array[0].used = firewall_tool_iptables_length;
            arguments.array[1].used = 2;
            arguments.array[2].used = 2;
            arguments.array[3].used = 2;
            arguments.array[4].used = 3;
            arguments.array[5].used = 9;
            arguments.array[6].used = 6;

            status = fll_execute_program((f_string) firewall_tool_iptables, arguments, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (f_error_is_not_error(status) && show_ports) {
            fl_print_color(f_standard_output, data->context.standout, data->context.reset, "========================== ");
            fl_print_color(f_standard_output, data->context.title, data->context.reset, "PORTS");
            fl_print_color_line(f_standard_output, data->context.standout, data->context.reset, " ===========================");
            fflush(f_standard_output);

            arguments.used = 5;

            arguments.array[0].string = (f_string) firewall_tool_iptables;
            arguments.array[1].string = (f_string) "-x";
            arguments.array[2].string = (f_string) "-v";
            arguments.array[3].string = (f_string) "--numeric";
            arguments.array[4].string = (f_string) "--list";

            arguments.array[0].used = firewall_tool_iptables_length;
            arguments.array[1].used = 2;
            arguments.array[2].used = 2;
            arguments.array[3].used = 9;
            arguments.array[4].used = 6;

            status = fll_execute_program((f_string) firewall_tool_iptables, arguments, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (f_error_is_error(status)) {
            status = f_error_set_fine(status);

            if (f_macro_test_for_allocation_errors(status)) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
            } else {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_tool_iptables);
              fprintf(f_standard_error, "  ");

              f_string_length i = 0;

              fl_print_color_code(f_standard_error, data->context.error);

              for (; i < arguments.used; i++) {
                fprintf(f_standard_error, "%s ", arguments.array[i].string);
              }

              fl_print_color_code(f_standard_error, data->context.reset);
              fprintf(f_standard_error, "\n");
            }

            status = f_error_set_error(status);
          }

          arguments.array[0].string = 0;
          arguments.array[1].string = 0;
          arguments.array[2].string = 0;
          arguments.array[3].string = 0;
          arguments.array[4].string = 0;
          arguments.array[5].string = 0;
          arguments.array[6].string = 0;
          arguments.array[0].used = 0;
          arguments.array[1].used = 0;
          arguments.array[2].used = 0;
          arguments.array[3].used = 0;
          arguments.array[4].used = 0;
          arguments.array[5].used = 0;
          arguments.array[6].used = 0;

          f_delete_dynamic_strings(status, arguments);
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        // load all network devices
        status = fl_directory_list((f_string) network_devices, &data->devices);

        if (f_error_is_error(status)) {
          status = f_error_set_fine(status);

          if (f_macro_test_for_allocation_errors(status)) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
          } else if (status == f_no_data) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: could not find any network devices");
          } else if (status == f_failure) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to read the device directory '%s'", network_devices);
          }

          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return f_error_set_error(status);
        }

        // remove "lo" (loopback) from the device listing
        {
          f_string_length i = 0;

          for (; i < data->devices.used; i++) {
            if (fl_compare_strings((f_string) firewall_device_loop, data->devices.array[i].string, firewall_device_loop_length + 1, data->devices.array[i].used) == f_equal_to) {
              f_dynamic_string swap_string = data->devices.array[i];

              data->devices.used--;

              for (; i < data->devices.used; i++) {
                data->devices.array[i] = data->devices.array[i+1];
              }

              data->devices.array[data->devices.used] = swap_string;
            }
          }
        }

        if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart || command == firewall_parameter_command_lock) {
          status = firewall_buffer_rules(network_path firewall_file_other, f_false, &local, data);

          if (f_error_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          {
            f_array_length i = 0;
            f_string_length length = 0;

            for (; i < local.chain_objects.used; i++) {
              length = local.chain_objects.array[i].stop - local.chain_objects.array[i].start + 1;

              if (!reserved.has_stop && fl_compare_strings((f_string) firewall_group_stop, local.buffer.string + local.chain_objects.array[i].start, firewall_group_stop_length, length) == f_equal_to) {
                reserved.stop_at = i;
                reserved.has_stop = f_true;
              } else if (!reserved.has_lock && fl_compare_strings((f_string) firewall_group_lock, local.buffer.string + local.chain_objects.array[i].start, firewall_group_lock_length, length) == f_equal_to) {
                reserved.lock_at = i;
                reserved.has_lock = f_true;
              }
            } // for
          }

          if (command == firewall_parameter_command_lock) {
            if (reserved.has_lock) {
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
            } else {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform lock request because the lock instructions are missing from: %s.", network_path firewall_file_other);

              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return f_invalid_data;
            }
          }

          if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart) {
            if (reserved.has_stop) {
              local.is_global = f_true;
              local.is_main = f_false;
              local.is_stop = f_true;
              local.is_lock = f_false;
              local.chain = reserved.stop_at;

              input.start = local.chain_contents.array[reserved.stop_at].array[0].start;
              input.stop = local.chain_contents.array[reserved.stop_at].array[0].stop;

              status = firewall_process_rules(&input, &local, data);

              if (f_error_is_error(status) || command == firewall_parameter_command_stop) {
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }
            } else {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform stop request because the lock instructions are missing from: %s.", network_path firewall_file_other);

              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return f_invalid_data;
            }
          }

          firewall_delete_local_data(&local);
        }

        if (command == firewall_parameter_command_start || command == firewall_parameter_command_restart) {
          status = firewall_buffer_rules(network_path firewall_file_first, f_false, &local, data);

          if (f_error_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          };

          status = firewall_create_custom_chains(&reserved, &local, data);

          if (f_error_is_error(status)) {
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

            if (f_error_is_error(status) || command == firewall_parameter_command_stop) {
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
              f_dynamic_string file_path = f_dynamic_string_initialize;

              f_resize_dynamic_string(status, file_path, network_path_length + data->devices.array[i].used  + firewall_file_suffix_length + 1);

              if (f_error_is_error(status)) {
                fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory.");
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }

              strncat(file_path.string, network_path, network_path_length);
              strncat(file_path.string + network_path_length, data->devices.array[i].string, data->devices.array[i].used);
              strncat(file_path.string, firewall_file_suffix, firewall_file_suffix_length);
              file_path.used = file_path.size;
              file_path.string[file_path.used] = 0;

              status = firewall_buffer_rules(file_path.string, f_true, &local, data);

              f_delete_dynamic_string(status2, file_path);
            }

            if (f_error_is_error(status)) {
              status = f_error_set_fine(status);

              firewall_delete_local_data(&local);

              if (status == f_file_not_found || status == f_file_open_error || status == f_file_descriptor_error || status == fl_fss_found_object_no_content) {
                status = f_error_set_error(status);
                continue;
              }

              firewall_delete_data(data);
              return f_error_set_error(status);
            }

            status = firewall_create_custom_chains(&reserved, &local, data);

            if (f_error_is_error(status)) {
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

              if (f_error_is_error(status) || command == firewall_parameter_command_stop) {
                firewall_delete_local_data(&local);
                firewall_delete_data(data);
                return status;
              }
            } // for

            firewall_delete_local_data(&local);
          } // for

          status = firewall_buffer_rules(network_path firewall_file_last, f_false, &local, data);

          if (f_error_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          status = firewall_create_custom_chains(&reserved, &local, data);

          if (f_error_is_error(status)) {
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

            if (f_error_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            i++;
          } // while
        }

        // cleanup
        firewall_delete_local_data(&local);
      } else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: You did not pass a command");
        status = f_error_set_error(f_invalid_parameter);
      }
    }

    firewall_delete_data(data);
    return status;
  }
#endif // _di_firewall_main_

#ifndef _di_firewall_delete_data_
  f_return_status firewall_delete_data(firewall_data *data) {
    f_status        status = f_none;
    f_string_length i      = 0;

    while (i < firewall_total_parameters) {
      f_delete_string_lengths(status, data->parameters[i].additional);
      i++;
    } // while

    f_delete_dynamic_strings(status, data->chains);
    f_delete_string_lengths(status, data->remaining);
    f_delete_dynamic_strings(status, data->devices);

    fl_delete_color_context(status, data->context);

    return f_none;
  }
#endif // _di_firewall_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

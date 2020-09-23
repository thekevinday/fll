/**
 * FLL - Level 3
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#include "firewall.h"
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_help_
  f_return_status firewall_print_help(const int id, const f_color_context_t context) {

    fll_program_print_help_header(id, context, firewall_name_long, firewall_version);

    fll_program_print_help_option(id, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(id, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(id, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(id, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(id, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(id, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(id, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");

    #ifdef _en_firewall_debug_
      fll_program_print_help_option(id, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    #endif // _en_firewall_debug_

    fll_program_print_help_option(id, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    #ifdef _en_firewall_debug_
      fll_program_print_help_option(id, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging.");
    #endif // _en_firewall_debug_

    printf("%c%c", f_string_eol[0], f_string_eol[0]);
    fl_color_print(f_type_output, context.set.important, " Available Commands: ");

    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.set.standout, firewall_command_start);
    printf("    Turn on the firewall");

    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.set.standout, firewall_command_stop);
    printf("     Turn off the firewall");

    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.set.standout, firewall_command_restart);
    printf("  Turn off and then turn on the firewall");

    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.set.standout, firewall_command_lock);
    printf("     Prevent all communication");

    printf("%c  ", f_string_eol[0]);
    fl_color_print(f_type_output, context.set.standout, firewall_command_show);
    printf("     Show active firewall settings");

    fll_program_print_help_usage(id, context, firewall_name, "command");

    return F_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_return_status firewall_main(const f_console_arguments_t arguments, firewall_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

      {
        f_console_parameter_id_t ids[3] = { firewall_parameter_no_color, firewall_parameter_light, firewall_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);
        const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, firewall_total_parameters);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (F_status_is_error(status)) {
          firewall_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { firewall_parameter_verbosity_quiet, firewall_parameter_verbosity_normal, firewall_parameter_verbosity_verbose, firewall_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          firewall_delete_data(data);
          return status;
        }

        if (choice == firewall_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == firewall_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == firewall_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == firewall_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[firewall_parameter_help].result == f_console_result_found) {
      firewall_print_help(data->output, data->context);

      firewall_delete_data(data);
      return F_none;
    }

    if (data->parameters[firewall_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, firewall_version);

      firewall_delete_data(data);
      return F_none;
    }

    // now determine which command was placed first
    bool found_command = F_false;
    unsigned int command = 0;

    if (data->parameters[firewall_parameter_command_start].result == f_console_result_found) {
      command = firewall_parameter_command_start;
      found_command = F_true;
    }

    if (data->parameters[firewall_parameter_command_stop].result == f_console_result_found) {
      if (found_command) {
        if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_stop].additional.array[0]) {
          command = firewall_parameter_command_stop;
        }
      }
      else {
        command = firewall_parameter_command_stop;
        found_command = F_true;
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
        found_command = F_true;
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
        found_command = F_true;
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
        found_command = F_true;
      }
    }

    if (found_command) {
      firewall_local_data_t local = firewall_local_data_t_initialize;
      firewall_reserved_chains_t reserved = firewall_reserved_chains_t_initialize;
      f_string_range_t input = f_string_range_t_initialize;

      if (command == firewall_parameter_command_show) {
        // Warning: these are hardcoded print commands (I am not certain how I am going to implement external 'show' rules as the default-firewall setting file is the wrong place to put this)
        bool show_nat = F_true;
        bool show_mangle = F_true;
        bool show_ports = F_true;

        f_string_dynamics_t parameters = f_string_dynamics_t_initialize;
        int return_code = 0;

        if (data->remaining.used > 0) {
          show_nat = F_false;
          show_mangle = F_false;
          show_ports = F_false;

          f_string_length_t counter = 0;

          for (; counter < data->remaining.used; counter++) {

            if (strncmp("nat", arguments.argv[data->remaining.array[counter]], 4) != 0) {
              if (strncmp("mangle",  arguments.argv[data->remaining.array[counter]], 7) != 0) {
                if (strncmp("ports",  arguments.argv[data->remaining.array[counter]], 6) != 0) {
                  fl_color_print(f_type_warning, data->context.set.warning, "WARNING: '%s' is not a valid show option%c", arguments.argv[data->remaining.array[counter]], f_string_eol[0]);
                }
                else {
                  show_ports = F_true;
                }
              }
              else {
                show_mangle = F_true;
              }
            }
            else {
              show_nat = F_true;
            }
          } // for
        }

        f_macro_string_dynamics_resize(status, parameters, 7);

        if (F_status_is_error(status)) {
          fl_color_print_to(data->error.to, data->context.set.error, "CRITICAL ERROR: Unable to allocate memory.%c", f_string_eol[0]);
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        if (show_nat) {
          fl_color_print(f_type_output, data->context.set.standout, "=========================== ");
          fl_color_print(f_type_output, data->context.set.title, "NAT");
          fl_color_print(f_type_output, data->context.set.standout, " ============================%c", f_string_eol[0]);
          fflush(f_type_output);

          parameters.used = 6;

          parameters.array[0].string = (f_string_t) "-x";
          parameters.array[1].string = (f_string_t) "-v";
          parameters.array[2].string = (f_string_t) "-t";
          parameters.array[3].string = (f_string_t) "nat";
          parameters.array[4].string = (f_string_t) "--numeric";
          parameters.array[5].string = (f_string_t) "--list";

          parameters.array[0].used = 2;
          parameters.array[1].used = 2;
          parameters.array[2].used = 2;
          parameters.array[3].used = 3;
          parameters.array[4].used = 9;
          parameters.array[5].used = 6;

          status = fll_execute_program((f_string_t) firewall_tool_iptables, parameters, 0, &return_code);

          fprintf(f_type_output, "\n");
          fflush(f_type_output);
        }

        if (F_status_is_error_not(status) && show_mangle) {
          fl_color_print(f_type_output, data->context.set.standout, "========================== ");
          fl_color_print(f_type_output, data->context.set.title, "MANGLE");
          fl_color_print(f_type_output, data->context.set.standout, " ==========================%c", f_string_eol[0]);
          fflush(f_type_output);

          parameters.used = 6;

          parameters.array[0].string = (f_string_t) "-x";
          parameters.array[1].string = (f_string_t) "-v";
          parameters.array[2].string = (f_string_t) "-t";
          parameters.array[3].string = (f_string_t) "mangle";
          parameters.array[4].string = (f_string_t) "--numeric";
          parameters.array[5].string = (f_string_t) "--list";

          parameters.array[0].used = 2;
          parameters.array[1].used = 2;
          parameters.array[2].used = 2;
          parameters.array[3].used = 6;
          parameters.array[4].used = 9;
          parameters.array[5].used = 6;

          status = fll_execute_program((f_string_t) firewall_tool_iptables, parameters, 0, &return_code);

          fprintf(f_type_output, "\n");
          fflush(f_type_output);
        }

        if (F_status_is_error_not(status) && show_ports) {
          fl_color_print(f_type_output, data->context.set.standout, "========================== ");
          fl_color_print(f_type_output, data->context.set.title, "FILTER");
          fl_color_print(f_type_output, data->context.set.standout, " ==========================%c", f_string_eol[0]);
          fflush(f_type_output);

          parameters.used = 4;

          parameters.array[0].string = (f_string_t) "-x";
          parameters.array[1].string = (f_string_t) "-v";
          parameters.array[2].string = (f_string_t) "--numeric";
          parameters.array[3].string = (f_string_t) "--list";

          parameters.array[0].used = 2;
          parameters.array[1].used = 2;
          parameters.array[2].used = 9;
          parameters.array[3].used = 6;

          status = fll_execute_program((f_string_t) firewall_tool_iptables, parameters, 0, &return_code);

          fprintf(f_type_output, "\n");
          fflush(f_type_output);
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_memory_allocation || status == F_memory_reallocation) {
            fl_color_print_to(data->error.to, data->context.set.error, "CRITICAL ERROR: Unable to allocate memory.%c", f_string_eol[0]);
          }
          else {
            fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Failed to perform requested %s operation:%c", firewall_tool_iptables, f_string_eol[0]);
            fprintf(f_type_error, "  ");

            f_string_length_t i = 0;

            fl_color_print_code(f_type_error, data->context.error);

            fprintf(f_type_error, "%s ", firewall_tool_iptables);
            for (; i < parameters.used; i++) {
              fprintf(f_type_error, "%s ", parameters.array[i].string);
            } // for

            fl_color_print_code(f_type_error, data->context.reset);
            fprintf(f_type_error, "\n");
          }

          status = F_status_set_error(status);
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

        f_macro_string_dynamics_t_delete_simple( parameters);
        firewall_delete_local_data(&local);
        firewall_delete_data(data);
        return status;
      }

      // load all network devices
      status = f_directory_list((f_string_t) network_devices, 0, alphasort, &data->devices);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_memory_allocation || status == F_memory_reallocation) {
          fl_color_print_to(data->error.to, data->context.set.error, "CRITICAL ERROR: Unable to allocate memory.%c", f_string_eol[0]);
        }
        else if (status == F_data_not) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Could not find any network devices%c", f_string_eol[0]);
        }
        else if (status == F_failure) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Failed to read the device directory '%s'%c", network_devices, f_string_eol[0]);
        }

        firewall_delete_local_data(&local);
        firewall_delete_data(data);
        return F_status_set_error(status);
      }

      // remove "lo" (loopback) from the device listing
      {
        f_string_length_t i = 0;

        for (; i < data->devices.used; i++) {
          if (fl_string_compare((f_string_t) firewall_device_loop, data->devices.array[i].string, firewall_device_loop_length + 1, data->devices.array[i].used) == F_equal_to) {
            f_string_dynamic_t swap_string = data->devices.array[i];

            data->devices.used--;

            for (; i < data->devices.used; i++) {
              data->devices.array[i] = data->devices.array[i+1];
            } // for

            data->devices.array[data->devices.used] = swap_string;
          }
        } // for
      }

      if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart || command == firewall_parameter_command_lock) {
        status = firewall_buffer_rules(network_path firewall_file_other, F_false, &local, data);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        {
          f_array_length_t i = 0;
          f_string_length_t length = 0;

          for (; i < local.chain_objects.used; i++) {
            length = local.chain_objects.array[i].stop - local.chain_objects.array[i].start + 1;

            if (!reserved.has_stop && fl_string_compare((f_string_t) firewall_group_stop, local.buffer.string + local.chain_objects.array[i].start, firewall_group_stop_length, length) == F_equal_to) {
              reserved.stop_at = i;
              reserved.has_stop = F_true;
            }
            else if (!reserved.has_lock && fl_string_compare((f_string_t) firewall_group_lock, local.buffer.string + local.chain_objects.array[i].start, firewall_group_lock_length, length) == F_equal_to) {
              reserved.lock_at = i;
              reserved.has_lock = F_true;
            }
          } // for
        }

        if (command == firewall_parameter_command_lock) {
          if (reserved.has_lock) {
            status = firewall_delete_chains(*data);

            if (F_status_is_error_not(status)) {
              status = firewall_default_lock(*data);
            }

            if (F_status_is_error(status)) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            local.is_main = F_false;
            local.is_stop = F_false;
            local.is_lock = F_true;
            local.chain = reserved.lock_at;

            input.start = local.chain_contents.array[reserved.lock_at].array[0].start;
            input.stop = local.chain_contents.array[reserved.lock_at].array[0].stop;

            status = firewall_process_rules(&input, &local, data);

            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }
          else {
            fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Failed to perform lock request because the lock instructions are missing from: %s.%c", network_path firewall_file_other, f_string_eol[0]);

            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return F_status_set_error(F_data);
          }
        }

        if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart) {
          if (reserved.has_stop) {
            status = firewall_delete_chains(*data);

            if (F_status_is_error_not(status)) {
              status = firewall_default_lock(*data);
            }

            if (F_status_is_error(status)) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            local.is_global = F_true;
            local.is_main = F_false;
            local.is_stop = F_true;
            local.is_lock = F_false;
            local.chain = reserved.stop_at;

            input.start = local.chain_contents.array[reserved.stop_at].array[0].start;
            input.stop = local.chain_contents.array[reserved.stop_at].array[0].stop;

            status = firewall_process_rules(&input, &local, data);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }
          }
          else {
            fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Failed to perform stop request because the lock instructions are missing from: %s.", network_path firewall_file_other, f_string_eol[0]);

            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return F_status_set_error(F_data);
          }
        }

        firewall_delete_local_data(&local);
      }

      if (command == firewall_parameter_command_start || command == firewall_parameter_command_restart) {
        status = firewall_buffer_rules(network_path firewall_file_first, F_false, &local, data);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        if (command == firewall_parameter_command_start) {
          status = firewall_delete_chains(*data);

          if (F_status_is_error_not(status)) {
            status = firewall_default_lock(*data);
          }

          if (F_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }
        }

        status = firewall_create_custom_chains(&reserved, &local, data);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        f_array_length_t i = 0;

        local.is_global = F_true;
        local.is_stop = F_false;
        local.is_lock = F_false;

        while (i < local.chain_contents.used) {

          input.start = local.chain_contents.array[i].array[0].start;
          input.stop = local.chain_contents.array[i].array[0].stop;

          local.is_main = reserved.has_main && i == reserved.main_at ? F_true : F_false;
          local.chain = i;

          status = firewall_process_rules(&input, &local, data);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
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
            f_string_dynamic_t file_path = f_string_dynamic_t_initialize;

            f_macro_string_dynamic_t_resize(status, file_path, network_path_length + data->devices.array[i].used + firewall_file_suffix_length + 1);

            if (F_status_is_error(status)) {
              fl_color_print_to(data->error.to, data->context.set.error, "CRITICAL ERROR: Unable to allocate memory.%c", f_string_eol[0]);
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }

            memcpy((void *)file_path.string, network_path, network_path_length);
            memcpy((void *)(file_path.string + network_path_length), data->devices.array[i].string, data->devices.array[i].used);
            memcpy((void *)(file_path.string + network_path_length + data->devices.array[i].used), firewall_file_suffix, firewall_file_suffix_length);

            file_path.used = network_path_length + data->devices.array[i].used + firewall_file_suffix_length;
            file_path.string[file_path.used] = 0;

            status = firewall_buffer_rules(file_path.string, F_true, &local, data);

            f_macro_string_dynamic_t_delete_simple(file_path);
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            firewall_delete_local_data(&local);

            if (status == F_file_found_not || status == F_file_open || status == F_file_descriptor || status == FL_fss_found_object_content_not) {
              status = F_status_set_error(status);
              continue;
            }

            firewall_delete_data(data);
            return F_status_set_error(status);
          }

          status = firewall_create_custom_chains(&reserved, &local, data);

          if (F_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_delete_data(data);
            return status;
          }

          f_array_length_t j = 0;

          local.is_global = F_false;
          local.is_stop = F_false;
          local.is_lock = F_false;

          for (; j < local.chain_contents.used; j++) {

            input.start = local.chain_contents.array[j].array[0].start;
            input.stop = local.chain_contents.array[j].array[0].stop;

            local.is_main = reserved.has_main && j == reserved.main_at ? F_true : F_false;
            local.chain = j;

            status = firewall_process_rules(&input, &local, data);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_delete_data(data);
              return status;
            }
          } // for

          firewall_delete_local_data(&local);
        } // for

        status = firewall_buffer_rules(network_path firewall_file_last, F_false, &local, data);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_delete_data(data);
          return status;
        }

        status = firewall_create_custom_chains(&reserved, &local, data);

        if (F_status_is_error(status)) {
          f_status_t status2 = F_none;

          firewall_macro_delete_fss_buffers(status2, local.buffer, local.chain_objects, local.chain_contents)
          firewall_delete_data(data);
          return status;
        }

        i = 0;

        local.is_global = F_true;
        local.is_stop = F_false;
        local.is_lock = F_false;

        while (i < local.chain_contents.used) {

          input.start = local.chain_contents.array[i].array[0].start;
          input.stop = local.chain_contents.array[i].array[0].stop;

          local.is_main = reserved.has_main && i == reserved.main_at ? F_true : F_false;
          local.chain = i;

          status = firewall_process_rules(&input, &local, data);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
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
      fl_color_print_to(data->error.to, data->context.set.error, "ERROR: You did not pass a command%c", f_string_eol[0]);
      status = F_status_set_error(F_parameter);
    }

    firewall_delete_data(data);
    return status;
  }
#endif // _di_firewall_main_

#ifndef _di_firewall_delete_data_
  f_return_status firewall_delete_data(firewall_data_t *data) {
    f_string_length_t i = 0;

    while (i < firewall_total_parameters) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_dynamics_t_delete_simple(data->chains);
    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_string_dynamics_t_delete_simple(data->devices);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_firewall_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * FLL - Level 3
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#include "firewall.h"
#include "private-common.h"
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_help_
  f_status_t firewall_print_help(const f_file_t output, const f_color_context_t context) {

    flockfile(output.stream);

    fll_program_print_help_header(output, context, firewall_name_long, firewall_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fl_print_format("%c%c %[Available Commands:%] ", output.stream, f_string_eol_s[0], f_string_eol_s[0], context.set.important, context.set.important);
    fl_print_format("%c  %[%s%]  Turn on the firewall.", output.stream, context.set.standout, firewall_command_start, context.set.standout);
    fl_print_format("%c  %[%s%]  Turn off the firewall.", output.stream, context.set.standout, firewall_command_stop, context.set.standout);
    fl_print_format("%c  %[%s%]  Turn off and then turn on the firewall.", output.stream, context.set.standout, firewall_command_restart, context.set.standout);
    fl_print_format("%c  %[%s%]  Prevent all communication.", output.stream, context.set.standout, firewall_command_lock, context.set.standout);
    fl_print_format("%c  %[%s%]  Show active firewall settings.", output.stream, context.set.standout, firewall_command_show, context.set.standout);

    fll_program_print_help_usage(output, context, firewall_name, "command");

    funlockfile(output.stream);

    return F_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_status_t firewall_main(const f_console_arguments_t arguments, firewall_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, firewall_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { firewall_parameter_no_color, firewall_parameter_light, firewall_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;

          main->warning.context = main->context.set.warning;
          main->warning.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          firewall_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { firewall_parameter_verbosity_quiet, firewall_parameter_verbosity_normal, firewall_parameter_verbosity_verbose, firewall_parameter_verbosity_debug };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);
        f_console_parameter_id_t choice = 0;

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          firewall_main_delete(main);
          return status;
        }

        if (choice == firewall_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == firewall_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == firewall_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == firewall_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[firewall_parameter_help].result == f_console_result_found) {
      firewall_print_help(main->output, main->context);

      firewall_main_delete(main);
      return F_none;
    }

    if (main->parameters[firewall_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, firewall_version);

      firewall_main_delete(main);
      return F_none;
    }

    // now determine which command was placed first
    bool found_command = F_false;
    unsigned int command = 0;

    if (main->parameters[firewall_parameter_command_start].result == f_console_result_found) {
      command = firewall_parameter_command_start;
      found_command = F_true;
    }

    if (main->parameters[firewall_parameter_command_stop].result == f_console_result_found) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_stop].values.array[0]) {
          command = firewall_parameter_command_stop;
        }
      }
      else {
        command = firewall_parameter_command_stop;
        found_command = F_true;
      }
    }

    if (main->parameters[firewall_parameter_command_restart].result == f_console_result_found) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_restart].values.array[0]) {
          command = firewall_parameter_command_restart;
        }
      }
      else {
        command = firewall_parameter_command_restart;
        found_command = F_true;
      }
    }

    if (main->parameters[firewall_parameter_command_lock].result == f_console_result_found) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_lock].values.array[0]) {
          command = firewall_parameter_command_lock;
        }
      }
      else {
        command = firewall_parameter_command_lock;
        found_command = F_true;
      }
    }

    if (main->parameters[firewall_parameter_command_show].result == f_console_result_found) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_show].values.array[0]) {
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

        if (main->remaining.used > 0) {
          show_nat = F_false;
          show_mangle = F_false;
          show_ports = F_false;

          f_array_length_t counter = 0;

          for (; counter < main->remaining.used; ++counter) {

            if (strncmp("nat", arguments.argv[main->remaining.array[counter]], 4) != 0) {
              if (strncmp("mangle",  arguments.argv[main->remaining.array[counter]], 7) != 0) {
                if (strncmp("ports",  arguments.argv[main->remaining.array[counter]], 6) != 0) {
                  flockfile(main->warning.to.stream);

                  fl_print_format("%c%[%S'%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
                  fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, arguments.argv[main->remaining.array[counter]], main->warning.notable);
                  fl_print_format("%[' is not a valid show option.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

                  funlockfile(main->warning.to.stream);
                  fflush(main->warning.to.stream);
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

        macro_f_string_dynamics_t_resize(status, parameters, 7);

        if (F_status_is_error(status)) {
          firewall_print_error_on_allocation_failure(main->error);

          firewall_delete_local_data(&local);
          firewall_main_delete(main);
          return status;
        }

        if (show_nat) {
          fll_print_format("%[===========================%] %[NAT%] %[============================%]%c", main->output.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s[0]);
          fflush(main->output.stream);

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

          status = fll_execute_program((f_string_t) firewall_tool_iptables, parameters, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          fll_print_character(f_string_eol_s[0], main->output.stream);
          fflush(main->output.stream);
        }

        if (F_status_is_error_not(status) && show_mangle) {
          fll_print_format("%[==========================%] %[MANGLE%] %[==========================%]%c", main->output.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s[0]);
          fflush(main->output.stream);

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

          status = fll_execute_program((f_string_t) firewall_tool_iptables, parameters, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          fll_print_character(f_string_eol_s[0], main->output.stream);
          fflush(main->output.stream);
        }

        if (F_status_is_error_not(status) && show_ports) {
          fll_print_format("%[==========================%] %[FILTER%] %[==========================%]%c", main->output.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s[0]);
          fflush(main->output.stream);

          parameters.used = 4;

          parameters.array[0].string = (f_string_t) "-x";
          parameters.array[1].string = (f_string_t) "-v";
          parameters.array[2].string = (f_string_t) "--numeric";
          parameters.array[3].string = (f_string_t) "--list";

          parameters.array[0].used = 2;
          parameters.array[1].used = 2;
          parameters.array[2].used = 9;
          parameters.array[3].used = 6;

          status = fll_execute_program((f_string_t) firewall_tool_iptables, parameters, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          fll_print_character(f_string_eol_s[0], main->output.stream);
          fflush(main->output.stream);
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_memory_not) {
            firewall_print_error_on_allocation_failure(main->error);
          }
          else {
            firewall_print_error_on_operation(main->error, firewall_tool_iptables, parameters);
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

        macro_f_string_dynamics_t_delete_simple( parameters);
        firewall_delete_local_data(&local);
        firewall_main_delete(main);
        return status;
      }

      // load all network devices
      status = f_directory_list((f_string_t) network_devices, 0, alphasort, &main->devices);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (main->error.verbosity != f_console_verbosity_quiet) {
          if (status == F_memory_not) {
            firewall_print_error_on_allocation_failure(main->error);
          }
          else if (status == F_data_not) {
            fll_print_format("%c%[%sCould not find any network devices.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0]);
          }
          else if (status == F_failure) {
            fll_print_format("%c%[%sFailed to read the device directory '%s'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, network_devices, main->error.context, f_string_eol_s[0]);
          }
        }

        firewall_delete_local_data(&local);
        firewall_main_delete(main);
        return F_status_set_error(status);
      }

      // remove "lo" (loopback) from the device listing
      {
        f_array_length_t i = 0;

        for (; i < main->devices.used; ++i) {

          if (fl_string_compare((f_string_t) firewall_device_loop, main->devices.array[i].string, firewall_device_loop_length + 1, main->devices.array[i].used) == F_equal_to) {
            f_string_dynamic_t swap_string = main->devices.array[i];

            --main->devices.used;

            for (; i < main->devices.used; ++i) {
              main->devices.array[i] = main->devices.array[i+1];
            } // for

            main->devices.array[main->devices.used] = swap_string;
          }
        } // for
      }

      if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart || command == firewall_parameter_command_lock) {
        status = firewall_buffer_rules(network_path firewall_file_other, F_false, &local, main);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_main_delete(main);
          return status;
        }

        {
          f_array_length_t i = 0;
          f_array_length_t length = 0;

          for (; i < local.chain_objects.used; ++i) {
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
            status = firewall_delete_chains(*main);

            if (F_status_is_error_not(status)) {
              status = firewall_default_lock(*main);
            }

            if (F_status_is_error(status)) {
              firewall_delete_local_data(&local);
              firewall_main_delete(main);
              return status;
            }

            local.is_main = F_false;
            local.is_stop = F_false;
            local.is_lock = F_true;
            local.chain = reserved.lock_at;

            input.start = local.chain_contents.array[reserved.lock_at].array[0].start;
            input.stop = local.chain_contents.array[reserved.lock_at].array[0].stop;

            status = firewall_process_rules(&input, &local, main);

            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return status;
          }
          else {

            if (main->error.verbosity != f_console_verbosity_quiet) {
              fll_print_format("%c%[%sFailed to perform lock request because the lock instructions are missing from: %s.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, network_path firewall_file_other, main->error.context, f_string_eol_s[0]);
            }

            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return F_status_set_error(F_data);
          }
        }

        if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart) {
          if (reserved.has_stop) {
            status = firewall_delete_chains(*main);

            if (F_status_is_error_not(status)) {
              status = firewall_default_lock(*main);
            }

            if (F_status_is_error(status)) {
              firewall_delete_local_data(&local);
              firewall_main_delete(main);
              return status;
            }

            local.is_global = F_true;
            local.is_main = F_false;
            local.is_stop = F_true;
            local.is_lock = F_false;
            local.chain = reserved.stop_at;

            input.start = local.chain_contents.array[reserved.stop_at].array[0].start;
            input.stop = local.chain_contents.array[reserved.stop_at].array[0].stop;

            status = firewall_process_rules(&input, &local, main);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_main_delete(main);
              return status;
            }
          }
          else {
            if (main->error.verbosity != f_console_verbosity_quiet) {
              fll_print_format("%c%[%sFailed to perform stop request because the lock instructions are missing from: %s.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, network_path firewall_file_other, main->error.context, f_string_eol_s[0]);
            }

            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return F_status_set_error(F_data);
          }
        }

        firewall_delete_local_data(&local);
      }

      if (command == firewall_parameter_command_start || command == firewall_parameter_command_restart) {
        status = firewall_buffer_rules(network_path firewall_file_first, F_false, &local, main);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_main_delete(main);
          return status;
        }

        if (command == firewall_parameter_command_start) {
          status = firewall_delete_chains(*main);

          if (F_status_is_error_not(status)) {
            status = firewall_default_lock(*main);
          }

          if (F_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return status;
          }
        }

        status = firewall_create_custom_chains(&reserved, &local, main);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_main_delete(main);
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

          status = firewall_process_rules(&input, &local, main);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return status;
          }

          ++i;
        } // while

        firewall_delete_local_data(&local);

        for (i = 0; i < main->devices.used; ++i) {
          local.device = i;

          {
            f_string_dynamic_t file_path = f_string_dynamic_t_initialize;

            macro_f_string_dynamic_t_resize(status, file_path, network_path_length + main->devices.array[i].used + firewall_file_suffix_length + 1);

            if (F_status_is_error(status)) {
              firewall_print_error_on_allocation_failure(main->error);

              firewall_delete_local_data(&local);
              firewall_main_delete(main);
              return status;
            }

            memcpy((void *)file_path.string, network_path, network_path_length);
            memcpy((void *)(file_path.string + network_path_length), main->devices.array[i].string, main->devices.array[i].used);
            memcpy((void *)(file_path.string + network_path_length + main->devices.array[i].used), firewall_file_suffix, firewall_file_suffix_length);

            file_path.used = network_path_length + main->devices.array[i].used + firewall_file_suffix_length;
            file_path.string[file_path.used] = 0;

            status = firewall_buffer_rules(file_path.string, F_true, &local, main);

            macro_f_string_dynamic_t_delete_simple(file_path);
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            firewall_delete_local_data(&local);

            if (status == F_file_found_not || status == F_file_open || status == F_file_descriptor || status == FL_fss_found_object_content_not) {
              status = F_status_set_error(status);
              continue;
            }

            firewall_main_delete(main);
            return F_status_set_error(status);
          }

          status = firewall_create_custom_chains(&reserved, &local, main);

          if (F_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return status;
          }

          f_array_length_t j = 0;

          local.is_global = F_false;
          local.is_stop = F_false;
          local.is_lock = F_false;

          for (; j < local.chain_contents.used; ++j) {

            input.start = local.chain_contents.array[j].array[0].start;
            input.stop = local.chain_contents.array[j].array[0].stop;

            local.is_main = reserved.has_main && j == reserved.main_at ? F_true : F_false;
            local.chain = j;

            status = firewall_process_rules(&input, &local, main);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
              firewall_delete_local_data(&local);
              firewall_main_delete(main);
              return status;
            }
          } // for

          firewall_delete_local_data(&local);
        } // for

        status = firewall_buffer_rules(network_path firewall_file_last, F_false, &local, main);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_main_delete(main);
          return status;
        }

        status = firewall_create_custom_chains(&reserved, &local, main);

        if (F_status_is_error(status)) {
          f_status_t status2 = F_none;

          macro_firewall_delete_fss_buffers(status2, local.buffer, local.chain_objects, local.chain_contents)
          firewall_main_delete(main);
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

          status = firewall_process_rules(&input, &local, main);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop) {
            firewall_delete_local_data(&local);
            firewall_main_delete(main);
            return status;
          }

          ++i;
        } // while
      }

      // cleanup
      firewall_delete_local_data(&local);
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet) {
        fll_print_format("%c%[%sYou did not pass a command.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    firewall_main_delete(main);
    return status;
  }
#endif // _di_firewall_main_

#ifndef _di_firewall_main_delete_
  f_status_t firewall_main_delete(firewall_main_t *main) {

    for (f_array_length_t i = 0; i < firewall_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_string_dynamics_t_delete_simple(main->chains);
    macro_f_array_lengths_t_delete_simple(main->remaining);
    macro_f_string_dynamics_t_delete_simple(main->devices);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_firewall_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * FLL - Level 3
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#include "firewall.h"
#include "private-common.h"
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_program_version_
  const f_string_static_t firewall_program_version_s = macro_f_string_static_t_initialize2(FIREWALL_program_version_s, 0, FIREWALL_program_version_s_length);
#endif // _di_firewall_program_version_

#ifndef _di_firewall_program_name_
  const f_string_static_t firewall_program_name_s = macro_f_string_static_t_initialize2(FIREWALL_program_name_s, 0, FIREWALL_program_name_s_length);
  const f_string_static_t firewall_program_name_long_s = macro_f_string_static_t_initialize2(FIREWALL_program_name_long_s, 0, FIREWALL_program_name_long_s_length);
#endif // _di_firewall_program_name_

#ifndef _di_firewall_print_help_
  f_status_t firewall_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, firewall_program_name_long_s, firewall_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fl_print_format("%q%q %[Available Commands:%] ", file.stream, f_string_eol_s, f_string_eol_s, context.set.important, context.set.important);
    fl_print_format("%q  %[%s%]    Turn on the firewall.", file.stream, f_string_eol_s, context.set.standout, firewall_command_start_s, context.set.standout);
    fl_print_format("%q  %[%s%]     Turn off the firewall.", file.stream, f_string_eol_s, context.set.standout, firewall_command_stop_s, context.set.standout);
    fl_print_format("%q  %[%s%]  Turn off and then turn on the firewall.", file.stream, f_string_eol_s, context.set.standout, firewall_command_restart_s, context.set.standout);
    fl_print_format("%q  %[%s%]     Prevent all communication.", file.stream, f_string_eol_s, context.set.standout, firewall_command_lock_s, context.set.standout);
    fl_print_format("%q  %[%s%]     Show active firewall settings.", file.stream, f_string_eol_s, context.set.standout, firewall_command_show_s, context.set.standout);

    fll_program_print_help_usage(file, context, firewall_program_name_s, "command");

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_status_t firewall_main(firewall_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, firewall_total_parameters_d);

      {
        f_console_parameter_id_t ids[3] = { firewall_parameter_no_color_e, firewall_parameter_light_e, firewall_parameter_dark_e };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(*arguments, parameters, choices, F_true, &main->remaining, &main->context);

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
          firewall_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { firewall_parameter_verbosity_quiet_e, firewall_parameter_verbosity_normal_e, firewall_parameter_verbosity_verbose_e, firewall_parameter_verbosity_debug_e };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);
        f_console_parameter_id_t choice = 0;

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          firewall_main_delete(main);

          return status;
        }

        if (choice == firewall_parameter_verbosity_quiet_e) {
          main->output.verbosity = f_console_verbosity_quiet_e;
          main->error.verbosity = f_console_verbosity_quiet_e;
          main->warning.verbosity = f_console_verbosity_quiet_e;
        }
        else if (choice == firewall_parameter_verbosity_normal_e) {
          main->output.verbosity = f_console_verbosity_normal_e;
          main->error.verbosity = f_console_verbosity_normal_e;
          main->warning.verbosity = f_console_verbosity_normal_e;
        }
        else if (choice == firewall_parameter_verbosity_verbose_e) {
          main->output.verbosity = f_console_verbosity_verbose_e;
          main->error.verbosity = f_console_verbosity_verbose_e;
          main->warning.verbosity = f_console_verbosity_verbose_e;
        }
        else if (choice == firewall_parameter_verbosity_debug_e) {
          main->output.verbosity = f_console_verbosity_debug_e;
          main->error.verbosity = f_console_verbosity_debug_e;
          main->warning.verbosity = f_console_verbosity_debug_e;
        }
      }

      status = F_none;
    }

    if (main->parameters[firewall_parameter_help_e].result == f_console_result_found_e) {
      firewall_print_help(main->output.to, main->context);

      firewall_main_delete(main);

      return F_none;
    }

    if (main->parameters[firewall_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, firewall_version_s);

      firewall_main_delete(main);

      return F_none;
    }

    // now determine which command was placed first
    bool found_command = F_false;
    unsigned int command = 0;

    if (main->parameters[firewall_parameter_command_start_e].result == f_console_result_found_e) {
      command = firewall_parameter_command_start_e;
      found_command = F_true;
    }

    if (main->parameters[firewall_parameter_command_stop_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_stop_e].values.array[0]) {
          command = firewall_parameter_command_stop_e;
        }
      }
      else {
        command = firewall_parameter_command_stop_e;
        found_command = F_true;
      }
    }

    if (main->parameters[firewall_parameter_command_restart_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_restart_e].values.array[0]) {
          command = firewall_parameter_command_restart_e;
        }
      }
      else {
        command = firewall_parameter_command_restart_e;
        found_command = F_true;
      }
    }

    if (main->parameters[firewall_parameter_command_lock_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_lock_e].values.array[0]) {
          command = firewall_parameter_command_lock_e;
        }
      }
      else {
        command = firewall_parameter_command_lock_e;
        found_command = F_true;
      }
    }

    if (main->parameters[firewall_parameter_command_show_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters[command].values.array[0] > main->parameters[firewall_parameter_command_show_e].values.array[0]) {
          command = firewall_parameter_command_show_e;
        }
      }
      else {
        command = firewall_parameter_command_show_e;
        found_command = F_true;
      }
    }

    if (found_command) {
      firewall_local_data_t local = firewall_local_data_t_initialize;
      firewall_reserved_chains_t reserved = firewall_reserved_chains_t_initialize;
      f_string_range_t input = f_string_range_t_initialize;

      if (command == firewall_parameter_command_show_e) {

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

            if (strncmp("nat", arguments->argv[main->remaining.array[counter]], 4) != 0) {
              if (strncmp("mangle",  arguments->argv[main->remaining.array[counter]], 7) != 0) {
                if (strncmp("ports",  arguments->argv[main->remaining.array[counter]], 6) != 0) {
                  flockfile(main->warning.to.stream);

                  fl_print_format("%q%[%Q'%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
                  fl_print_format("%[%S%]", main->warning.to.stream, main->warning.notable, arguments->argv[main->remaining.array[counter]], main->warning.notable);
                  fl_print_format("%[' is not a valid show option.%]%q", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

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
          fll_print_format("%[===========================%] %[NAT%] %[============================%]%q", main->output.to.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          fflush(main->output.to.stream);

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

          status = fll_execute_program((f_string_t) firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          fll_print_dynamic(f_string_eol_s, main->output.to.stream);
          fflush(main->output.to.stream);
        }

        if (F_status_is_error_not(status) && show_mangle) {
          fll_print_format("%[==========================%] %[MANGLE%] %[==========================%]%q", main->output.to.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          fflush(main->output.to.stream);

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

          status = fll_execute_program((f_string_t) firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          fll_print_dynamic(f_string_eol_s, main->output.to.stream);
          fflush(main->output.to.stream);
        }

        if (F_status_is_error_not(status) && show_ports) {
          fll_print_format("%[==========================%] %[FILTER%] %[==========================%]%q", main->output.to.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          fflush(main->output.to.stream);

          parameters.used = 4;

          parameters.array[0].string = (f_string_t) "-x";
          parameters.array[1].string = (f_string_t) "-v";
          parameters.array[2].string = (f_string_t) "--numeric";
          parameters.array[3].string = (f_string_t) "--list";

          parameters.array[0].used = 2;
          parameters.array[1].used = 2;
          parameters.array[2].used = 9;
          parameters.array[3].used = 6;

          status = fll_execute_program((f_string_t) firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          fll_print_dynamic(f_string_eol_s, main->output.to.stream);
          fflush(main->output.to.stream);
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_memory_not) {
            firewall_print_error_on_allocation_failure(main->error);
          }
          else {
            firewall_print_error_on_operation(main->error, firewall_tool_iptables_s, parameters);
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

        f_string_dynamics_resize(0, & parameters);
        firewall_delete_local_data(&local);
        firewall_main_delete(main);

        return status;
      }

      // load all network devices
      status = f_directory_list((f_string_t) network_devices_s, 0, alphasort, &main->devices);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          if (status == F_memory_not) {
            firewall_print_error_on_allocation_failure(main->error);
          }
          else if (status == F_data_not) {
            fll_print_format("%q%[%QCould not find any network devices.%]%q", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
          }
          else if (status == F_failure) {
            fll_print_format("%q%[%QFailed to read the device directory '%s'.%]%q", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, network_devices_s, main->error.context, f_string_eol_s);
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

          if (fl_string_compare((f_string_t) firewall_device_loop_s, main->devices.array[i].string, firewall_device_loop_s_length + 1, main->devices.array[i].used) == F_equal_to) {
            f_string_dynamic_t swap_string = main->devices.array[i];

            --main->devices.used;

            for (; i < main->devices.used; ++i) {
              main->devices.array[i] = main->devices.array[i+1];
            } // for

            main->devices.array[main->devices.used] = swap_string;
          }
        } // for
      }

      if (command == firewall_parameter_command_stop_e || command == firewall_parameter_command_restart_e || command == firewall_parameter_command_lock_e) {
        status = firewall_buffer_rules(main, network_path_s firewall_file_other_s, F_false, &local);

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

            if (!reserved.has_stop && fl_string_compare((f_string_t) firewall_group_stop_s, local.buffer.string + local.chain_objects.array[i].start, firewall_group_stop_s_length, length) == F_equal_to) {
              reserved.stop_at = i;
              reserved.has_stop = F_true;
            }
            else if (!reserved.has_lock && fl_string_compare((f_string_t) firewall_group_lock_s, local.buffer.string + local.chain_objects.array[i].start, firewall_group_lock_s_length, length) == F_equal_to) {
              reserved.lock_at = i;
              reserved.has_lock = F_true;
            }
          } // for
        }

        if (command == firewall_parameter_command_lock_e) {
          if (reserved.has_lock) {
            status = firewall_delete_chains(main);

            if (F_status_is_error_not(status)) {
              status = firewall_default_lock(main);
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

            status = firewall_process_rules(main, &input, &local);

            firewall_delete_local_data(&local);
            firewall_main_delete(main);

            return status;
          }
          else {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              fll_print_format("%q%[%QFailed to perform lock request because the lock instructions are missing from: %s.%]%q", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, network_path_s firewall_file_other_s, main->error.context, f_string_eol_s);
            }

            firewall_delete_local_data(&local);
            firewall_main_delete(main);

            return F_status_set_error(F_data);
          }
        }

        if (command == firewall_parameter_command_stop_e || command == firewall_parameter_command_restart_e) {
          if (reserved.has_stop) {
            status = firewall_delete_chains(main);

            if (F_status_is_error_not(status)) {
              status = firewall_default_lock(main);
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

            status = firewall_process_rules(main, &input, &local);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop_e) {
              firewall_delete_local_data(&local);
              firewall_main_delete(main);

              return status;
            }
          }
          else {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              fll_print_format("%q%[%QFailed to perform stop request because the lock instructions are missing from: %s.%]%q", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, network_path_s firewall_file_other_s, main->error.context, f_string_eol_s);
            }

            firewall_delete_local_data(&local);
            firewall_main_delete(main);

            return F_status_set_error(F_data);
          }
        }

        firewall_delete_local_data(&local);
      }

      if (command == firewall_parameter_command_start_e || command == firewall_parameter_command_restart_e) {
        status = firewall_buffer_rules(main, network_path_s firewall_file_first_s, F_false, &local);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_main_delete(main);

          return status;
        }

        if (command == firewall_parameter_command_start_e) {
          status = firewall_delete_chains(main);

          if (F_status_is_error_not(status)) {
            status = firewall_default_lock(main);
          }

          if (F_status_is_error(status)) {
            firewall_delete_local_data(&local);
            firewall_main_delete(main);

            return status;
          }
        }

        status = firewall_create_custom_chains(main, &reserved, &local);

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

          status = firewall_process_rules(main, &input, &local);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop_e) {
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

            macro_f_string_dynamic_t_resize(status, file_path, network_path_s_length + main->devices.array[i].used + firewall_file_suffix_s_length + 1);

            if (F_status_is_error(status)) {
              firewall_print_error_on_allocation_failure(main->error);

              firewall_delete_local_data(&local);
              firewall_main_delete(main);

              return status;
            }

            memcpy((void *)file_path.string, network_path_s, network_path_s_length);
            memcpy((void *)(file_path.string + network_path_s_length), main->devices.array[i].string, main->devices.array[i].used);
            memcpy((void *)(file_path.string + network_path_s_length + main->devices.array[i].used), firewall_file_suffix_s, firewall_file_suffix_s_length);

            file_path.used = network_path_s_length + main->devices.array[i].used + firewall_file_suffix_s_length;
            file_path.string[file_path.used] = 0;

            status = firewall_buffer_rules(main, file_path.string, F_true, &local);

            f_string_dynamic_resize(0, &file_path);
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            firewall_delete_local_data(&local);

            if (status == F_file_found_not || status == F_file_open || status == F_file_descriptor || status == F_fss_found_object_content_not) {
              status = F_status_set_error(status);
              continue;
            }

            firewall_main_delete(main);

            return F_status_set_error(status);
          }

          status = firewall_create_custom_chains(main, &reserved, &local);

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

            status = firewall_process_rules(main, &input, &local);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop_e) {
              firewall_delete_local_data(&local);
              firewall_main_delete(main);

              return status;
            }
          } // for

          firewall_delete_local_data(&local);
        } // for

        status = firewall_buffer_rules(main, network_path_s firewall_file_last_s, F_false, &local);

        if (F_status_is_error(status)) {
          firewall_delete_local_data(&local);
          firewall_main_delete(main);

          return status;
        }

        status = firewall_create_custom_chains(main, &reserved, &local);

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

          status = firewall_process_rules(main, &input, &local);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop_e) {
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
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_print_format("%q%[%QYou did not pass a command.%]%q", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      }

      status = F_status_set_error(F_parameter);
    }

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);

        fll_print_dynamic(f_string_eol_s, main->output.to.stream);
      }
    }

    firewall_main_delete(main);

    return status;
  }
#endif // _di_firewall_main_

#ifndef _di_firewall_main_delete_
  f_status_t firewall_main_delete(firewall_main_t * const main) {

    for (f_array_length_t i = 0; i < firewall_total_parameters_d; ++i) {

      f_type_array_lengths_resize(0, &main->parameters[i].locations);
      f_type_array_lengths_resize(0, &main->parameters[i].locations_sub);
      f_type_array_lengths_resize(0, &main->parameters[i].values);
    } // for

    f_string_dynamics_resize(0, &main->chains);
    f_type_array_lengths_resize(0, &main->remaining);
    f_string_dynamics_resize(0, &main->devices);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_firewall_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

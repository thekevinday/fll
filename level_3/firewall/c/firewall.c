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

#ifndef _di_firewall_print_copyright_
  f_status_t firewall_print_copyright(const f_file_t file, const bool full) {

    flockfile(file.stream);

    fl_print_format("%rCopyright © 2007-2023 Kevin Day.%r", file.stream, f_string_eol_s, f_string_eol_s);

    #ifndef _di_detailed_copyright_
      if (full) {
        fl_print_format("%rThis program comes with ABSOLUTELY NO WARRANTY.%r", file.stream, f_string_eol_s, f_string_eol_s);
        fl_print_format("This is free software, and you are welcome to modify or redistribute in accordance to the license.%r", file.stream, f_string_eol_s);
      }
    #endif // _di_detailed_copyright_

    fl_print_format("%rSource code license lgpl-2.1-or-later.%r", file.stream, f_string_eol_s, f_string_eol_s);
    fl_print_format("Standard and specification license open-standard-license-1.0.%r", file.stream, f_string_eol_s);
    fl_print_format("Documentation license cc-by-sa-4.0.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_firewall_print_copyright_

#ifndef _di_firewall_print_help_
  f_status_t firewall_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, firewall_program_name_long_s, firewall_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_copyright_s, f_console_standard_long_copyright_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Print the copyright.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "     Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Do not print using color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, using only error output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Print only the version number.");

    fl_print_format("%r%r %[Commands:%] ", file.stream, f_string_eol_s, f_string_eol_s, context.set.important, context.set.important);
    fl_print_format("%r  %[%r%]    Turn on the firewall.", file.stream, f_string_eol_s, context.set.standout, firewall_command_start_s, context.set.standout);
    fl_print_format("%r  %[%r%]     Turn off the firewall.", file.stream, f_string_eol_s, context.set.standout, firewall_command_stop_s, context.set.standout);
    fl_print_format("%r  %[%r%]  Turn off and then turn on the firewall.", file.stream, f_string_eol_s, context.set.standout, firewall_command_restart_s, context.set.standout);
    fl_print_format("%r  %[%r%]     Prevent all communication.", file.stream, f_string_eol_s, context.set.standout, firewall_command_lock_s, context.set.standout);
    fl_print_format("%r  %[%r%]     Show active firewall settings.", file.stream, f_string_eol_s, context.set.standout, firewall_command_show_s, context.set.standout);

    fll_program_print_help_usage(file, context, firewall_program_name_s, firewall_program_help_parameters_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_status_t firewall_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    main->child = 0;

    {
      f_console_parameter_id_t ids[3] = { firewall_parameter_no_color_e, firewall_parameter_light_e, firewall_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->context);

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

      if (F_status_is_error(status)) return status;
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { firewall_parameter_verbosity_quiet_e, firewall_parameter_verbosity_error_e, firewall_parameter_verbosity_normal_e, firewall_parameter_verbosity_verbose_e, firewall_parameter_verbosity_debug_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);
      f_console_parameter_id_t choice = 0;

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);
      if (F_status_is_error(status)) return status;

      if (choice == firewall_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == firewall_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
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

    if (main->parameters.array[firewall_parameter_help_e].result == f_console_result_found_e) {
      firewall_print_help(main->output.to, main->context);

      return F_none;
    }

    if (main->parameters.array[firewall_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, firewall_program_version_s);

      return F_none;
    }

    if (main->parameters.array[firewall_parameter_copyright_e].result == f_console_result_found_e) {
      firewall_print_copyright(main->output.to, main->output.verbosity > f_console_verbosity_error_e);

      return F_none;
    }

    status = F_none;

    firewall_data_t data = firewall_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    // Now determine which command was placed first
    bool found_command = F_false;
    unsigned int command = 0;

    if (main->parameters.array[firewall_parameter_command_start_e].result == f_console_result_found_e) {
      command = firewall_parameter_command_start_e;
      found_command = F_true;
    }

    if (main->parameters.array[firewall_parameter_command_stop_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters.array[command].values.array[0] > main->parameters.array[firewall_parameter_command_stop_e].values.array[0]) {
          command = firewall_parameter_command_stop_e;
        }
      }
      else {
        command = firewall_parameter_command_stop_e;
        found_command = F_true;
      }
    }

    if (main->parameters.array[firewall_parameter_command_restart_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters.array[command].values.array[0] > main->parameters.array[firewall_parameter_command_restart_e].values.array[0]) {
          command = firewall_parameter_command_restart_e;
        }
      }
      else {
        command = firewall_parameter_command_restart_e;
        found_command = F_true;
      }
    }

    if (main->parameters.array[firewall_parameter_command_lock_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters.array[command].values.array[0] > main->parameters.array[firewall_parameter_command_lock_e].values.array[0]) {
          command = firewall_parameter_command_lock_e;
        }
      }
      else {
        command = firewall_parameter_command_lock_e;
        found_command = F_true;
      }
    }

    if (main->parameters.array[firewall_parameter_command_show_e].result == f_console_result_found_e) {
      if (found_command) {
        if (main->parameters.array[command].values.array[0] > main->parameters.array[firewall_parameter_command_show_e].values.array[0]) {
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

        // Warning: these are hardcoded print commands.
        bool show_nat = F_true;
        bool show_mangle = F_true;
        bool show_ports = F_true;

        int return_code = 0;

        if (main->parameters.remaining.used) {
          show_nat = F_false;
          show_mangle = F_false;
          show_ports = F_false;

          f_array_length_t index = 0;

          for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

            index = main->parameters.remaining.array[i];

            if (fl_string_dynamic_compare(firewall_show_nat_s, data.argv[index]) == F_equal_to) {
              show_nat = F_true;
            }
            else {
              if (fl_string_dynamic_compare(firewall_show_mangle_s, data.argv[index]) == F_equal_to) {
                show_mangle = F_true;
              }
              else {
                if (fl_string_dynamic_compare(firewall_show_ports_s, data.argv[index]) == F_equal_to) {
                  show_ports = F_true;
                }
                else {
                  flockfile(main->warning.to.stream);

                  fl_print_format("%r%[%Q'%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
                  fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, data.argv[index], main->warning.notable);
                  fl_print_format("%[' is not a valid show option.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

                  funlockfile(main->warning.to.stream);
                  fflush(main->warning.to.stream);
                }
              }
            }
          } // for
        }

        f_string_statics_t parameters = f_string_statics_t_initialize;
        parameters.used = 6;

        f_string_static_t parameters_array[parameters.used];
        parameters.array = parameters_array;

        parameters_array[0] = firewall_show_parameter_exact_s;
        parameters_array[1] = firewall_show_parameter_verbose_s;
        parameters_array[2] = firewall_show_parameter_table_s;
        parameters_array[3] = firewall_show_nat_s;
        parameters_array[4] = firewall_show_parameter_numeric_s;
        parameters_array[5] = firewall_show_parameter_list_s;

        if (show_nat) {
          fll_print_format("%[===========================%] %[NAT%] %[============================%]%r", main->output.to.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          fflush(main->output.to.stream);

          status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          if (status == F_child) {
            main->child = return_code;

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          fflush(main->output.to.stream);
        }

        if (F_status_is_error_not(status) && show_mangle) {
          fll_print_format("%[==========================%] %[MANGLE%] %[==========================%]%r", main->output.to.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          fflush(main->output.to.stream);

          parameters_array[3] = firewall_show_mangle_s;

          status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          if (status == F_child) {
            main->child = return_code;

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          fflush(main->output.to.stream);
        }

        if (F_status_is_error_not(status) && show_ports) {
          fll_print_format("%[==========================%] %[FILTER%] %[==========================%]%r", main->output.to.stream, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          fflush(main->output.to.stream);

          parameters_array[0] = firewall_show_parameter_exact_s;
          parameters_array[1] = firewall_show_parameter_verbose_s;
          parameters_array[2] = firewall_show_parameter_numeric_s;
          parameters_array[3] = firewall_show_parameter_list_s;
          parameters.used = 4;

          status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          if (status == F_child) {
            main->child = return_code;

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
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

        firewall_delete_local_data(&local);
        firewall_data_delete(&data);

        return status;
      }

      // Load all network devices.
      status = f_directory_list(firewall_network_devices_s, 0, alphasort, &data.devices);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          if (status == F_memory_not) {
            firewall_print_error_on_allocation_failure(main->error);
          }
          else if (status == F_data_not) {
            fll_print_format("%r%[%QCould not find any network devices.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
          }
          else if (status == F_failure) {
            fll_print_format("%r%[%QFailed to read the device directory '%r'.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, firewall_network_devices_s, main->error.context, f_string_eol_s);
          }
        }

        firewall_delete_local_data(&local);
        firewall_data_delete(&data);

        return F_status_set_error(status);
      }

      // Remove "lo" (loopback) from the device listing.
      {
        f_array_length_t i = 0;

        for (; i < data.devices.used; ++i) {

          if (fl_string_dynamic_compare(firewall_device_loop_s, data.devices.array[i]) == F_equal_to) {
            f_string_static_t swap_string = data.devices.array[i];

            --data.devices.used;

            for (; i < data.devices.used; ++i) {
              data.devices.array[i] = data.devices.array[i + 1];
            } // for

            data.devices.array[data.devices.used] = swap_string;
          }
        } // for
      }

      if (command == firewall_parameter_command_stop_e || command == firewall_parameter_command_restart_e || command == firewall_parameter_command_lock_e) {
        f_string_static_t path_file_other = f_string_static_t_initialize;
        path_file_other.used = firewall_network_path_s.used + firewall_file_other_s.used;

        f_char_t path_file_other_string[path_file_other.used + 1];
        path_file_other.string = path_file_other_string;
        path_file_other_string[path_file_other.used] = 0;

        memcpy(path_file_other_string, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
        memcpy(path_file_other_string + firewall_network_path_s.used, firewall_file_other_s.string, sizeof(f_char_t) * firewall_file_other_s.used);

        status = firewall_buffer_rules(&data, path_file_other, F_false, &local);

        if (F_status_is_error(status) || status == F_child) {
          firewall_delete_local_data(&local);
          firewall_data_delete(&data);

          return status;
        }

        for (f_array_length_t i = 0; i < local.chain_objects.used; ++i) {

          if (!reserved.has_stop && fl_string_dynamic_partial_compare_string(firewall_group_stop_s.string, local.buffer, firewall_group_stop_s.used, local.chain_objects.array[i]) == F_equal_to) {
            reserved.stop_at = i;
            reserved.has_stop = F_true;
          }
          else if (!reserved.has_lock && fl_string_dynamic_partial_compare_string(firewall_group_lock_s.string, local.buffer, firewall_group_lock_s.used, local.chain_objects.array[i]) == F_equal_to) {
            reserved.lock_at = i;
            reserved.has_lock = F_true;
          }
        } // for

        if (command == firewall_parameter_command_lock_e) {
          if (reserved.has_lock) {
            status = firewall_delete_chains(&data);

            if (F_status_is_error_not(status) && status != F_child) {
              status = firewall_default_lock(&data);
            }

            if (F_status_is_error(status) || status == F_child) {
              firewall_delete_local_data(&local);
              firewall_data_delete(&data);

              return status;
            }

            local.is_main = F_false;
            local.is_stop = F_false;
            local.is_lock = F_true;
            local.chain = reserved.lock_at;

            input.start = local.chain_contents.array[reserved.lock_at].array[0].start;
            input.stop = local.chain_contents.array[reserved.lock_at].array[0].stop;

            status = firewall_process_rules(&data, &input, &local);

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_print_format("%r%[%QFailed to perform lock request because the lock instructions are missing from: %r.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, path_file_other, main->error.context, f_string_eol_s);
          }

          firewall_delete_local_data(&local);

          return F_status_set_error(F_data);
        }

        if (command == firewall_parameter_command_stop_e || command == firewall_parameter_command_restart_e) {
          if (reserved.has_stop) {
            status = firewall_delete_chains(&data);

            if (F_status_is_error_not(status) && status != F_child) {
              status = firewall_default_lock(&data);
            }

            if (F_status_is_error(status) || status == F_child) {
              firewall_delete_local_data(&local);
              firewall_data_delete(&data);

              return status;
            }

            local.is_global = F_true;
            local.is_main = F_false;
            local.is_stop = F_true;
            local.is_lock = F_false;
            local.chain = reserved.stop_at;

            input.start = local.chain_contents.array[reserved.stop_at].array[0].start;
            input.stop = local.chain_contents.array[reserved.stop_at].array[0].stop;

            status = firewall_process_rules(&data, &input, &local);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop_e || status == F_child) {
              firewall_delete_local_data(&local);

              return status;
            }
          }
          else {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              fll_print_format("%r%[%QFailed to perform stop request because the stop instructions are missing from: %r.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, path_file_other, main->error.context, f_string_eol_s);
            }

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return F_status_set_error(F_data);
          }
        }

        firewall_delete_local_data(&local);
      }

      if (command == firewall_parameter_command_start_e || command == firewall_parameter_command_restart_e) {
        f_string_static_t path_file_first = f_string_static_t_initialize;
        path_file_first.used = firewall_network_path_s.used + firewall_file_first_s.used;

        f_char_t path_file_first_string[path_file_first.used + 1];
        path_file_first.string = path_file_first_string;
        path_file_first_string[path_file_first.used] = 0;

        memcpy(path_file_first_string, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
        memcpy(path_file_first_string + firewall_network_path_s.used, firewall_file_first_s.string, sizeof(f_char_t) * firewall_file_first_s.used);

        status = firewall_buffer_rules(&data, path_file_first, F_false, &local);

        if (F_status_is_error(status) || status == F_child) {
          firewall_delete_local_data(&local);
          firewall_data_delete(&data);

          return status;
        }

        if (command == firewall_parameter_command_start_e) {
          status = firewall_delete_chains(&data);

          if (F_status_is_error_not(status) && status != F_child) {
            status = firewall_default_lock(&data);
          }

          if (F_status_is_error(status) || status == F_child) {
            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }
        }

        status = firewall_create_custom_chains(&data, &reserved, &local);

        if (F_status_is_error(status) || status == F_child) {
          firewall_delete_local_data(&local);
          firewall_data_delete(&data);

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

          status = firewall_process_rules(&data, &input, &local);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop_e || status == F_child) {
            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          ++i;
        } // while

        firewall_delete_local_data(&local);

        {
          f_string_dynamic_t path_file = f_string_dynamic_t_initialize;
          f_array_length_t j = 0;

          for (i = 0; i < data.devices.used; ++i) {

            path_file.used = 0;
            local.device = i;

            status = f_string_dynamic_increase_by(firewall_network_path_s.used + data.devices.array[i].used + firewall_file_suffix_s.used + 1, &path_file);

            if (F_status_is_error_not(status)) {
              status = f_string_dynamic_append(firewall_network_path_s, &path_file);
            }

            if (F_status_is_error_not(status)) {
              status = f_string_dynamic_append(data.devices.array[i], &path_file);
            }

            if (F_status_is_error_not(status)) {
              status = f_string_dynamic_append(firewall_file_suffix_s, &path_file);
            }

            if (F_status_is_error(status)) {
              firewall_print_error_on_allocation_failure(main->error);

              firewall_delete_local_data(&local);
              firewall_data_delete(&data);

              return status;
            }

            status = firewall_buffer_rules(&data, path_file, F_true, &local);

            if (status == F_child) {
              firewall_delete_local_data(&local);
              firewall_data_delete(&data);

              f_string_dynamic_resize(0, &path_file);

              return status;
            }

            if (F_status_is_error(status)) {
              status = F_status_set_fine(status);

              firewall_delete_local_data(&local);

              if (status == F_file_found_not || status == F_file_open || status == F_file_descriptor || status == F_fss_found_object_content_not) {
                status = F_status_set_error(status);

                continue;
              }

              f_string_dynamic_resize(0, &path_file);
              firewall_data_delete(&data);

              return F_status_set_error(status);
            }

            status = firewall_create_custom_chains(&data, &reserved, &local);

            if (F_status_is_error(status) || status == F_child) {
              firewall_delete_local_data(&local);
              firewall_data_delete(&data);

              return status;
            }

            local.is_global = F_false;
            local.is_stop = F_false;
            local.is_lock = F_false;

            for (j = 0; j < local.chain_contents.used; ++j) {

              input.start = local.chain_contents.array[j].array[0].start;
              input.stop = local.chain_contents.array[j].array[0].stop;

              local.is_main = reserved.has_main && j == reserved.main_at ? F_true : F_false;
              local.chain = j;

              status = firewall_process_rules(&data, &input, &local);

              if (F_status_is_error(status) || command == firewall_parameter_command_stop_e || status == F_child) {
                f_string_dynamic_resize(0, &path_file);

                firewall_delete_local_data(&local);
                firewall_data_delete(&data);

                return status;
              }
            } // for

            firewall_delete_local_data(&local);
          } // for

          path_file.used = 0;

          status = f_string_dynamic_append(firewall_network_path_s, &path_file);

          if (F_status_is_error_not(status)) {
            status = f_string_dynamic_append(firewall_file_last_s, &path_file);
          }

          if (F_status_is_error_not(status)) {
            status = firewall_buffer_rules(&data, path_file, F_false, &local);
          }

          if (F_status_is_error(status) || status == F_child) {
            f_string_dynamic_resize(0, &path_file);

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          status = firewall_create_custom_chains(&data, &reserved, &local);

          if (F_status_is_error(status) || status == F_child) {
            f_string_dynamic_resize(0, &path_file);

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

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

            status = firewall_process_rules(&data, &input, &local);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop_e || status == F_child) {
              f_string_dynamic_resize(0, &path_file);

              firewall_delete_local_data(&local);
              firewall_data_delete(&data);

              return status;
            }

            ++i;
          } // while

          f_string_dynamic_resize(0, &path_file);
        }
      }

      firewall_delete_local_data(&local);
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_print_format("%r%[%QNo command given.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      }

      status = F_status_set_error(F_parameter);
    }

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    firewall_data_delete(&data);

    return status;
  }
#endif // _di_firewall_main_

#ifdef __cplusplus
} // extern "C"
#endif

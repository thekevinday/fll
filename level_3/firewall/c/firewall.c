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

#ifndef _di_firewall_main_
  f_status_t firewall_main(fll_program_data_t * const main, firewall_setting_t * const setting) {

    f_status_t status = F_none;

    main->child = 0;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { firewall_parameter_no_color_e, firewall_parameter_light_e, firewall_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          firewall_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);
          firewall_print_line_last_locked(setting, main->error);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { firewall_parameter_verbosity_quiet_e, firewall_parameter_verbosity_error_e, firewall_parameter_verbosity_verbose_e, firewall_parameter_verbosity_debug_e, firewall_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          firewall_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);
          firewall_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    firewall_data_t data = firewall_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[firewall_parameter_help_e].result & f_console_result_found_e) {
      firewall_print_help(setting, main->message);

      return F_none;
    }

    if (main->parameters.array[firewall_parameter_version_e].result & f_console_result_found_e) {
      fll_program_print_version(main->message, firewall_program_version_s);

      return F_none;
    }

    // now determine which command was placed first
    bool found_command = F_false;
    unsigned int command = 0;

    if (main->parameters.array[firewall_parameter_command_start_e].result & f_console_result_found_e) {
      command = firewall_parameter_command_start_e;
      found_command = F_true;
    }

    if (main->parameters.array[firewall_parameter_command_stop_e].result & f_console_result_found_e) {
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

    if (main->parameters.array[firewall_parameter_command_restart_e].result & f_console_result_found_e) {
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

    if (main->parameters.array[firewall_parameter_command_lock_e].result & f_console_result_found_e) {
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

    if (main->parameters.array[firewall_parameter_command_show_e].result & f_console_result_found_e) {
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
                  f_file_stream_lock(main->warning.to);

                  fl_print_format("%r%[%Q'%]", main->warning.to, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
                  fl_print_format("%[%Q%]", main->warning.to, main->warning.notable, data.argv[index], main->warning.notable);
                  fl_print_format("%[' is not a valid show option.%]%r", main->warning.to, main->warning.context, main->warning.context, f_string_eol_s);

                  f_file_stream_unlock(main->warning.to);
                  f_file_stream_flush(main->warning.to);
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
          fll_print_format("%[===========================%] %[NAT%] %[============================%]%r", main->output.to, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          f_file_stream_flush(main->output.to);

          status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          if (status == F_child) {
            main->child = return_code;

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          fll_print_dynamic_raw(f_string_eol_s, main->output.to);
          f_file_stream_flush(main->output.to);
        }

        if (F_status_is_error_not(status) && show_mangle) {
          fll_print_format("%[==========================%] %[MANGLE%] %[==========================%]%r", main->output.to, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          f_file_stream_flush(main->output.to);

          parameters_array[3] = firewall_show_mangle_s;

          status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

          if (status == F_child) {
            main->child = return_code;

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          fll_print_dynamic_raw(f_string_eol_s, main->output.to);
          f_file_stream_flush(main->output.to);
        }

        if (F_status_is_error_not(status) && show_ports) {
          fll_print_format("%[==========================%] %[FILTER%] %[==========================%]%r", main->output.to, main->context.set.standout, main->context.set.standout, main->context.set.title, main->context.set.title, main->context.set.standout, main->context.set.standout, f_string_eol_s);
          f_file_stream_flush(main->output.to);

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

          fll_print_dynamic_raw(f_string_eol_s, main->output.to);
          f_file_stream_flush(main->output.to);
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

        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          if (status == F_memory_not) {
            firewall_print_error_on_allocation_failure(main->error);
          }
          else if (status == F_data_not) {
            fll_print_format("%r%[%QCould not find any network devices.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
          }
          else if (status == F_failure) {
            fll_print_format("%r%[%QFailed to read the device directory '%r'.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, firewall_network_devices_s, main->error.context, f_string_eol_s);
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

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_print_format("%r%[%QFailed to perform lock request because the lock instructions are missing from: %r.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, path_file_other, main->error.context, f_string_eol_s);
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
            if (main->error.verbosity > f_console_verbosity_quiet_e) {
              fll_print_format("%r%[%QFailed to perform stop request because the lock instructions are missing from: %r.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, path_file_other, main->error.context, f_string_eol_s);
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
      if (main->error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_format("%r%[%QNo command given.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      }

      status = F_status_set_error(F_parameter);
    }

    if (main->error.verbosity > f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        f_file_stream_flush(main->output.to);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to);
      }
    }

    firewall_data_delete(&data);

    return status;
  }
#endif // _di_firewall_main_

#ifdef __cplusplus
} // extern "C"
#endif

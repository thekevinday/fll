#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_
  void firewall_operate(firewall_main_t * const main) {

    if (!main) return;

    main->data.is = firewall_data_is_global_e;

    if (main->setting.flag & firewall_main_flag_operation_show_e) {
      int return_code = 0;

      f_string_statics_t parameters = f_string_statics_t_initialize;
      parameters.used = 6;

      f_string_static_t show_nats[] = {
        firewall_show_parameter_exact_s,
        firewall_show_parameter_verbose_s,
        firewall_show_parameter_table_s,
        firewall_show_nat_s,
        firewall_show_parameter_numeric_s,
        firewall_show_parameter_list_s,
      };

      f_string_static_t show_mangles[] = {
        firewall_show_parameter_exact_s,
        firewall_show_parameter_verbose_s,
        firewall_show_parameter_table_s,
        firewall_show_mangle_s,
        firewall_show_parameter_numeric_s,
        firewall_show_parameter_list_s,
      };

      f_string_static_t show_filters[] = {
        firewall_show_parameter_exact_s,
        firewall_show_parameter_verbose_s,
        firewall_show_parameter_numeric_s,
        firewall_show_parameter_list_s,
      };

      const f_string_static_t show_arrays[][] = {
        show_nats,
        show_mangles,
        show_filters,
      };

      const f_number_unsigned_t show_lengths[] = {
        6,
        6,
        4,
      };

      const f_string_static_t show_lefts[] = {
        firewall_show_bars_27_s,
        firewall_show_bars_26_s,
        firewall_show_bars_26_s,
      };

      const f_string_static_t show_headers[] = {
        firewall_show_nat_s,
        firewall_show_mangle_s,
        firewall_show_filter_s,
      };

      const f_string_static_t show_rights[] = {
        firewall_show_bars_28_s,
        firewall_show_bars_26_s,
        firewall_show_bars_26_s,
      };

      const uint16_t show_flags[] = {
        firewall_main_flag_operation_show_nat_e,
        firewall_main_flag_operation_show_mangle_e,
        firewall_main_flag_operation_show_filter_e,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (!show_flags[i]) continue;

        parameters.array = show_arrays[i];
        parameters.used = show_lengths[i];

        firewall_print_message_show_header(&main->output, show_lefts[i], show_headers[i], show_rights[i]);

        main->setting.status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

        if (status == F_child) {
          main->child = return_code;

          return;
        }

        fll_print_dynamic_raw(f_string_eol_s, main->output.to);
        f_file_stream_flush(main->output.to);

        if (F_status_is_error(main->setting.status)) {
          firewall_print_error(&main->error
          firewall_print_error_operation(&main->error, firewall_tool_iptables_s, parameters);

          return;
        }
      } // for

      return;
    }

    main->setting.state.status = f_directory_list(firewall_network_devices_s, 0, alphasort, &main->data.devices);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_data_not) {
        firewall_print_error_network_device_none(&main->program.error);
      }
      else if (F_status_set_fine(main->setting.state.status) == F_failure) {
        firewall_print_error_directory_read(&main->program.error, firewall_network_devices_s);
      }
      else {
        firewall_print_error(&main->program.error, macro_firewall_f(f_console_parameter_process));
      }

      return;
    }

    f_number_unsigned_t i = 0;
    f_string_static_t buffer = f_string_static_t_initialize;

    // Remove "lo" (loopback) from the device listing.
    for (; i < data.devices.used; ++i) {

      if (f_compare_dynamic(firewall_device_loop_s, data.devices.array[i]) == F_equal_to) {
        buffer = data.devices.array[i];

        for (--data.devices.used; i < data.devices.used; ++i) {
          data.devices.array[i] = data.devices.array[i + 1];
        } // for

        data.devices.array[data.devices.used] = buffer;
      }
    } // for

    if (main->setting.flag & firewall_main_flag_operation_stop_restart_lock_e) {
      buffer.used = firewall_network_path_s.used + firewall_file_other_s.used;

      f_char_t path_file_other[buffer.used + 1];
      buffer.string = path_file_other;
      buffer[buffer.used] = 0;

      memcpy(path_file_other, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
      memcpy(path_file_other + firewall_network_path_s.used, firewall_file_other_s.string, sizeof(f_char_t) * firewall_file_other_s.used);

      firewall_operate_buffer_rules(&main, buffer, F_false);
      if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;

      for (i = 0; i < main->data.chain_objects.used; ++i) {

        if (!(main->data.has & firewall_data_has_stop_e) && f_compare_dynamic_partial_string(firewall_group_stop_s.string, main->data.buffer, firewall_group_stop_s.used, main->data.chain_objects.array[i]) == F_equal_to) {
          main->data.stop = i;
          main->data.has |= firewall_data_has_stop_e;
        }
        else if (!(main->data.has & firewall_data_has_lock_e) && f_compare_dynamic_partial_string(firewall_group_lock_s.string, main->data.buffer, firewall_group_lock_s.used, main->data.chain_objects.array[i]) == F_equal_to) {
          main->data.lock = i;
          main->data.has |= firewall_data_has_lock_e;
        }
      } // for

      if (main->setting.flag & firewall_main_flag_operation_lock_e) {
        if (main->data.has & firewall_data_has_lock_e) {
          firewall_operate_delete_chains(main);

          if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_child) {
            firewall_operate_default_lock(main);
          }

          if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;

          //main->data.chain = main->data.lock; // @fixme
          main->data.is = firewall_data_is_lock_e;
          main->data.range.start = local.chain_contents.array[main->data.lock].array[0].start;
          main->data.range.stop = local.chain_contents.array[main->data.lock].array[0].stop;

          firewall_operate_load_rules(main);
          firewall_operate_process_rules(main);
        }
        else {
          main->setting.state.status = F_status_set_error(F_data);

          firewall_print_error_operation_files_missing(&main->error, firewall_operation_lock_s, path_file_other);
        }

        return;
      }

      if (main->data.has & firewall_main_flag_operation_stop_restart_e) {
        if (main->data.has & firewall_data_has_stop_e) {
          firewall_operate_delete_chains(main);

          if (F_status_is_error_not(main->setting.status) && main->setting.status != F_child) {
            firewall_operate_default_lock(main);
          }

          if (F_status_is_error(status) || status == F_child) return;

          local.is_global = F_true;
          local.is_main = F_false;
          local.is_stop = F_true;
          local.is_lock = F_false;
          local.chain = main->data.stop;

          main->data.range.start = local.chain_contents.array[main->data.stop].array[0].start;
          main->data.range.stop = local.chain_contents.array[main->data.stop].array[0].stop;

          firewall_operate_load_rules(&main);
          if (F_status_is_error(main->setting.state.status) || (main->data.has & firewall_main_flag_operation_stop_e) || main->setting.state.status == F_child) return;
        }
        else {
          main->setting.state.status = F_status_set_error(F_data);

          firewall_print_error_operation_files_missing(&main->error, firewall_operation_stop_s, path_file_other);

          return;
        }
      }
    }

    /*
    if (main->setting.flag & firewall_main_flag_operation_start_restart_e) {
      f_string_static_t path_file_first = f_string_static_t_initialize;
      path_file_first.used = firewall_network_path_s.used + firewall_file_first_s.used;

      f_char_t path_file_first_string[path_file_first.used + 1];
      path_file_first.string = path_file_first_string;
      path_file_first_string[path_file_first.used] = 0;

      memcpy(path_file_first_string, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
      memcpy(path_file_first_string + firewall_network_path_s.used, firewall_file_first_s.string, sizeof(f_char_t) * firewall_file_first_s.used);

      status = firewall_operate_buffer_rules(&data, path_file_first, F_false, &local);

      if (F_status_is_error(status) || status == F_child) {
        firewall_delete_local_data(&local);
        firewall_data_delete(&data);

        return status;
      }

      if (command == firewall_parameter_command_start_e) {
        status = firewall_operate_delete_chains(&data);

        if (F_status_is_error_not(status) && status != F_child) {
          status = firewall_operate_default_lock(&data);
        }

        if (F_status_is_error(status) || status == F_child) {
          firewall_delete_local_data(&local);
          firewall_data_delete(&data);

          return status;
        }
      }

      status = firewall_operate_create_custom_chains(&data, &reserved, &local);

      if (F_status_is_error(status) || status == F_child) {
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

        local.is_main = reserved.has_main && i == main->data.main ? F_true : F_false;
        local.chain = i;

        status = firewall_operate_load_rules(&data, &input, &local);

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
        f_number_unsigned_t j = 0;

        for (i = 0; i < data.devices.used; ++i) {

          path_file.used = 0;
          local.device = i;

          status = f_memory_array_increase_by(firewall_network_path_s.used + data.devices.array[i].used + firewall_file_suffix_s.used + 1, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

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

          status = firewall_operate_buffer_rules(&data, path_file, F_true, &local);

          if (status == F_child) {
            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

            return status;
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            firewall_delete_local_data(&local);

            if (status == F_file_found_not || status == F_file_open || status == F_file_descriptor || status == F_fss_found_object_content_not) {
              status = F_status_set_error(status);

              continue;
            }

            f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);
            firewall_data_delete(&data);

            return F_status_set_error(status);
          }

          status = firewall_operate_create_custom_chains(&data, &reserved, &local);

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

            local.is_main = reserved.has_main && j == main->data.main ? F_true : F_false;
            local.chain = j;

            status = firewall_operate_load_rules(&data, &input, &local);

            if (F_status_is_error(status) || command == firewall_parameter_command_stop_e || status == F_child) {
              f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

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
          status = firewall_operate_buffer_rules(&data, path_file, F_false, &local);
        }

        if (F_status_is_error(status) || status == F_child) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

          firewall_delete_local_data(&local);
          firewall_data_delete(&data);

          return status;
        }

        status = firewall_operate_create_custom_chains(&data, &reserved, &local);

        if (F_status_is_error(status) || status == F_child) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

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

          local.is_main = reserved.has_main && i == main->data.main ? F_true : F_false;
          local.chain = i;

          status = firewall_operate_load_rules(&data, &input, &local);

          if (F_status_is_error(status) || command == firewall_parameter_command_stop_e || status == F_child) {
            f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

            firewall_delete_local_data(&local);
            firewall_data_delete(&data);

            return status;
          }

          ++i;
        } // while

        f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);
      }
    }
    */
  }
#endif // _di_firewall_operate_

#ifdef __cplusplus
} // extern "C"
#endif

#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_
  void firewall_operate(firewall_main_t * const main) {

    if (!main) return;

    main->data.is = firewall_data_is_global_e;

    if (main->setting.flag & firewall_main_flag_operation_show_e) {
      firewall_operate_show(main);

      return;
    }

    main->setting.state.status = f_directory_list(firewall_network_devices_s, 0, alphasort, &main->setting.devices);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_data_not) {
        firewall_print_error_network_device_none(&main->program.error);
      }
      else if (F_status_set_fine(main->setting.state.status) == F_failure) {
        firewall_print_error_file(&main->program.error, macro_firewall_f(f_directory_list), firewall_network_devices_s, f_file_operation_read_s, fll_error_file_type_directory_e);
      }
      else {
        firewall_print_error(&main->program.error, macro_firewall_f(f_console_parameter_process));
      }

      return;
    }

    f_number_unsigned_t i = 0;
    f_string_static_t buffer = f_string_static_t_initialize;

    // Remove "lo" (loopback) from the device listing.
    for (; i < main->setting.devices.used; ++i) {

      if (firewall_signal_check(main)) return;

      if (f_compare_dynamic(firewall_device_loop_s, main->setting.devices.array[i]) == F_equal_to) {
        buffer = main->setting.devices.array[i];

        for (--main->setting.devices.used; i < main->setting.devices.used; ++i) {
          main->setting.devices.array[i] = main->setting.devices.array[i + 1];
        } // for

        main->setting.devices.array[main->setting.devices.used] = buffer;
      }
    } // for

    if (main->setting.flag & firewall_main_flag_operation_stop_restart_lock_e) {
      buffer.used = firewall_network_path_s.used + firewall_file_other_s.used;

      f_char_t path_file_other[buffer.used + 1];
      buffer.string = path_file_other;
      path_file_other[buffer.used] = 0;

      memcpy(path_file_other, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
      memcpy(path_file_other + firewall_network_path_s.used, firewall_file_other_s.string, sizeof(f_char_t) * firewall_file_other_s.used);

      firewall_operate_buffer_chain(main, buffer, F_false);
      if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;

      for (i = 0; i < main->data.chain_objects.used; ++i) {

        if (firewall_signal_check(main)) return;

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

          firewall_operate_default_lock(main);

          if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;

          main->data.chain = main->data.lock;
          main->data.is = firewall_data_is_lock_e;
          main->data.range.start = main->data.chain_contents.array[main->data.lock].array[0].start;
          main->data.range.stop = main->data.chain_contents.array[main->data.lock].array[0].stop;

          firewall_operate_buffer_rules(main);

          firewall_operate_rules(main);
        }
        else {
          main->setting.state.status = F_status_set_error(F_data);

          firewall_print_error_operation_files_missing(&main->program.error, firewall_operation_lock_s, buffer);
        }

        return;
      }

      if (main->data.has & firewall_main_flag_operation_stop_restart_e) {
        if (main->data.has & firewall_data_has_stop_e) {
          firewall_operate_delete_chains(main);

          firewall_operate_default_lock(main);

          if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;

          main->data.chain = main->data.stop;
          main->data.is = firewall_data_is_global_e | firewall_data_is_stop_e;
          main->data.range.start = main->data.chain_contents.array[main->data.stop].array[0].start;
          main->data.range.stop = main->data.chain_contents.array[main->data.stop].array[0].stop;

          firewall_operate_buffer_rules(main);

          firewall_operate_rules(main);

          if (F_status_is_error(main->setting.state.status) || (main->data.has & firewall_main_flag_operation_stop_e) || main->setting.state.status == F_child) return;
        }
        else {
          main->setting.state.status = F_status_set_error(F_data);

          firewall_print_error_operation_files_missing(&main->program.error, firewall_operation_stop_s, buffer);

          return;
        }
      }
    }

    if (main->setting.flag & firewall_main_flag_operation_start_restart_e) {
      buffer.used = firewall_network_path_s.used + firewall_file_first_s.used;

      f_char_t path_file_first[buffer.used + 1];
      buffer.string = path_file_first;
      path_file_first[buffer.used] = 0;

      memcpy(path_file_first, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
      memcpy(path_file_first + firewall_network_path_s.used, firewall_file_first_s.string, sizeof(f_char_t) * firewall_file_first_s.used);

      firewall_operate_buffer_chain(main, buffer, F_false);

      if (main->setting.flag & firewall_main_flag_operation_start_e) {
        firewall_operate_delete_chains(main);

        firewall_operate_default_lock(main);
      }

      firewall_operate_create_custom_chains(main);

      main->data.is = firewall_data_is_global_e;

      firewall_operate_chains(main);

      if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child || (main->setting.flag & firewall_main_flag_operation_stop_e)) return;

      {
        for (f_number_unsigned_t j = 0; j < main->setting.devices.used; ++j) {

          if (firewall_signal_check(main)) return;

          main->cache.path_file.used = 0;
          main->data.device = j;

          main->setting.state.status = f_memory_array_increase_by(firewall_network_path_s.used + main->setting.devices.array[j].used + firewall_file_suffix_s.used + 1, sizeof(f_char_t), (void **) &main->cache.path_file.string, &main->cache.path_file.used, &main->cache.path_file.size);

          if (F_status_is_error(main->setting.state.status)) {
            firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase_by));

            return;
          }

          main->setting.state.status = f_string_dynamic_append(firewall_network_path_s, &main->cache.path_file);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append(main->setting.devices.array[j], &main->cache.path_file);
          }

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append(firewall_file_suffix_s, &main->cache.path_file);
          }

          if (F_status_is_error(main->setting.state.status)) {
            firewall_print_error(&main->program.error, macro_firewall_f(f_string_dynamic_append));

            return;
          }

          firewall_operate_buffer_chain(main, main->cache.path_file, F_true);

          firewall_operate_create_custom_chains(main);

          main->data.is = 0;

          firewall_operate_chains(main);
          if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child || (main->setting.flag & firewall_main_flag_operation_stop_e)) return;
        } // for

        main->cache.path_file.used = 0;

        main->setting.state.status = f_string_dynamic_append(firewall_network_path_s, &main->cache.path_file);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(firewall_file_last_s, &main->cache.path_file);
        }

        if (F_status_is_error(main->setting.state.status)) {
          firewall_print_error(&main->program.error, macro_firewall_f(f_string_dynamic_append));

          return;
        }

        firewall_operate_buffer_chain(main, main->cache.path_file, F_false);

        firewall_operate_create_custom_chains(main);

        main->data.is = firewall_data_is_global_e;

        firewall_operate_chains(main);
        if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;
      }
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_

#ifndef _di_firewall_operate_chains_
  void firewall_operate_chains(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    for (f_number_unsigned_t i = 0; i < main->data.chain_contents.used; ++i) {

      main->data.range = main->data.chain_contents.array[i].array[0];

      if ((main->data.has & firewall_data_has_main_e) && i == main->data.main) {
        main->data.is |= firewall_data_is_main_e;
      }
      else {
        main->data.is &= ~firewall_data_is_main_e;
      }

      main->data.chain = i;

      firewall_operate_buffer_rules(main);

      firewall_operate_rules(main);

      if (F_status_is_error(main->setting.state.status) || (main->setting.flag & firewall_main_flag_operation_stop_e) || main->setting.state.status == F_child) return;
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_chains_

#ifndef _di_firewall_operate_rules_
  void firewall_operate_rules(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    firewall_operate_process_rules(main);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) != F_failure) {
        firewall_print_error_unhandled(&main->program.error, macro_firewall_f(firewall_operate_process_rules), f_string_empty_s);
      }

      return;
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_rules_

#ifndef _di_firewall_operate_show_
  void firewall_operate_show(firewall_main_t * const main) {

    if (!main) return;

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

    f_string_static_t * const show_arrays[] = {
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
      firewall_print_show_bars_27_s,
      firewall_print_show_bars_26_s,
      firewall_print_show_bars_26_s,
    };

    const f_string_static_t show_headers[] = {
      firewall_print_show_nat_s,
      firewall_print_show_mangle_s,
      firewall_print_show_filter_s,
    };

    const f_string_static_t show_rights[] = {
      firewall_print_show_bars_28_s,
      firewall_print_show_bars_26_s,
      firewall_print_show_bars_26_s,
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
      return_code = 0;

      firewall_print_message_show_header(&main->program.output, show_lefts[i], show_headers[i], show_rights[i]);

      main->setting.state.status = fll_execute_program(firewall_tool_iptables_s, parameters, 0, 0, (void *) &return_code);

      if (main->setting.state.status == F_child) {
        main->program.child = return_code;

        return;
      }

      fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
      f_file_stream_flush(main->program.output.to);

      if (F_status_is_error(main->setting.state.status)) {
        firewall_print_error_operation(&main->program.error, firewall_tool_iptables_s, parameters);

        return;
      }
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_show_

#ifdef __cplusplus
} // extern "C"
#endif

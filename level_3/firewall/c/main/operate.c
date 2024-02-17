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

    // Remove "lo" (loopback) from the device listing.
    for (; i < main->setting.devices.used; ++i) {

      if (firewall_signal_check(main)) return;

      if (f_compare_dynamic(firewall_device_loop_s, main->setting.devices.array[i]) == F_equal_to) {
        main->data.file = main->setting.devices.array[i];

        for (--main->setting.devices.used; i < main->setting.devices.used; ++i) {
          main->setting.devices.array[i] = main->setting.devices.array[i + 1];
        } // for

        main->setting.devices.array[main->setting.devices.used] = main->data.file;
      }
    } // for

    main->data.file.string = 0;
    main->data.file.used = 0;

    if (main->setting.flag & firewall_main_flag_operation_stop_restart_lock_e) {
      main->data.file.used = firewall_network_path_s.used + firewall_file_other_s.used;

      f_char_t path_file_other[main->data.file.used + 1];
      main->data.file.string = path_file_other;
      path_file_other[main->data.file.used] = 0;

      memcpy(path_file_other, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
      memcpy(path_file_other + firewall_network_path_s.used, firewall_file_other_s.string, sizeof(f_char_t) * firewall_file_other_s.used);

      firewall_operate_buffer_chain(main, main->data.file, F_false);
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

          firewall_print_error_operation_files_missing(&main->program.error, firewall_operation_lock_s, main->data.file);
        }

        return;
      }

      if (main->setting.flag & firewall_main_flag_operation_stop_restart_e) {
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

          firewall_print_error_operation_files_missing(&main->program.error, firewall_operation_stop_s, main->data.file);

          return;
        }
      }

      main->data.file.string = 0;
      main->data.file.used = 0;
    }

    if (main->setting.flag & firewall_main_flag_operation_start_restart_e) {
      main->data.file.used = firewall_network_path_s.used + firewall_file_first_s.used;

      f_char_t path_file_first[main->data.file.used + 1];
      main->data.file.string = path_file_first;
      path_file_first[main->data.file.used] = 0;

      memcpy(path_file_first, firewall_network_path_s.string, sizeof(f_char_t) * firewall_network_path_s.used);
      memcpy(path_file_first + firewall_network_path_s.used, firewall_file_first_s.string, sizeof(f_char_t) * firewall_file_first_s.used);

      firewall_operate_buffer_chain(main, main->data.file, F_false);

      if (main->setting.flag & firewall_main_flag_operation_start_e) {
        firewall_operate_delete_chains(main);

        firewall_operate_default_lock(main);
      }

      firewall_operate_create_custom_chains(main);

      main->data.is = firewall_data_is_global_e;

      firewall_operate_chains(main);

      if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child || (main->setting.flag & firewall_main_flag_operation_stop_e)) return;

      for (f_number_unsigned_t j = 0; j < main->setting.devices.used; ++j) {

        if (firewall_signal_check(main)) return;

        main->cache.path_file.used = 0;
        main->data.device = j;

        main->setting.state.status = f_memory_array_increase_by(firewall_network_path_s.used + main->setting.devices.array[j].used + firewall_file_suffix_s.used + 1, sizeof(f_char_t), (void **) &main->cache.path_file.string, &main->cache.path_file.used, &main->cache.path_file.size);

        if (F_status_is_error(main->setting.state.status)) {
          firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase_by));

          return;
        }

        main->data.file = main->cache.path_file;

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

      main->data.file.used = main->cache.path_file.used;

      firewall_operate_buffer_chain(main, main->cache.path_file, F_false);

      firewall_operate_create_custom_chains(main);

      main->data.is = firewall_data_is_global_e;

      firewall_operate_chains(main);
      if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_child) return;

      main->data.file.string = 0;
      main->data.file.used = 0;
    }

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_

#ifdef __cplusplus
} // extern "C"
#endif

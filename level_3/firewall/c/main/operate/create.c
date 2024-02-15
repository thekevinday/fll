#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_create_custom_chains_
  void firewall_operate_create_custom_chains(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    bool new_chain = F_false;
    bool create_chain = F_false;

    int return_code = 0;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t length = 0;

    f_string_static_t tool = firewall_tool_iptables_s;

    main->cache.chain_ids.used = 0;
    main->cache.arguments.used = 0;

    main->setting.state.status = f_memory_array_increase_by(2, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = f_memory_array_increase_by(main->cache.chain_objects.used, sizeof(f_number_unsigned_t), (void **) &main->cache.chain_ids.array, &main->cache.chain_ids.used, &main->cache.chain_ids.size);
    }

    if (F_status_is_error(main->setting.state.status)) {
      firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase_by));

      return;
    }

    main->cache.chain_ids.used = main->cache.chain_objects.used;
    memset(main->cache.chain_ids.array, 0, sizeof(f_number_unsigned_t) * main->cache.chain_ids.used);

    main->setting.state.status = f_string_dynamic_append(firewall_chain_create_command_s, &main->cache.arguments.array[0]);

    if (F_status_is_error(main->setting.state.status)) {
      firewall_print_error(&main->program.error, macro_firewall_f(f_string_dynamic_append));

      return;
    }

    main->setting.state.status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_char_t), (void **) &main->cache.arguments.array[1].string, &main->cache.arguments.array[1].used, &main->cache.arguments.array[1].size);

    if (F_status_is_error(main->setting.state.status)) {
      firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase));

      return;
    }

    main->cache.arguments.used = 2;
    main->data.has = 0;

    for (; i < main->cache.chain_objects.used; ++i) {

      if (firewall_signal_check(main)) return;

      new_chain = F_true;
      j = 0;

      // Skip globally reserved chain name: main.
      if (f_compare_dynamic_partial_string(firewall_group_main_s.string, main->cache.buffer, firewall_group_main_s.used, main->cache.chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
        main->data.has |= firewall_data_has_main_e;
        main->data.main = i;
      }

      // Skip globally reserved chain name: stop.
      if (f_compare_dynamic_partial_string(firewall_group_stop_s.string, main->cache.buffer, firewall_group_stop_s.used, main->cache.chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
        main->data.has |= firewall_data_has_stop_e;
        main->data.stop = i;
      }

      // Skip globally reserved chain name: lock.
      if (f_compare_dynamic_partial_string(firewall_group_lock_s.string, main->cache.buffer, firewall_group_lock_s.used, main->cache.chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
        main->data.has |= firewall_data_has_lock_e;
        main->data.lock = i;
      }

      // Skip globally reserved chain name: none.
      if (f_compare_dynamic_partial_string(firewall_chain_none_s.string, main->cache.buffer, firewall_chain_none_s.used, main->cache.chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
      }

      if (new_chain) {
        for (; j < main->data.chains.used; ++j) {

          if (f_compare_dynamic_partial_string(main->data.chains.array[j].string, main->cache.buffer, main->data.chains.array[j].used, main->cache.chain_objects.array[i]) == F_equal_to) {
            new_chain = F_false;
            main->cache.chain_ids.array[i] = j;

            break;
          }
        } // for
      }

      if (new_chain) {
        main->setting.state.status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &main->data.chains.array, &main->data.chains.used, &main->data.chains.size);

        if (F_status_is_error(main->setting.state.status)) {
          firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase));

          return;
        }

        create_chain = F_true;
        length = (main->data.chain_objects.array[i].stop - main->data.chain_objects.array[i].start) + 1;

        main->cache.arguments.array[1].used = 0;

        main->setting.state.status = f_memory_array_increase_by(length + 1, sizeof(f_char_t), (void **) &main->cache.arguments.array[1].string, &main->cache.arguments.array[1].used, &main->cache.arguments.array[1].size);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_memory_array_increase_by(length + 1, sizeof(f_char_t), (void **) &main->data.chains.array[main->data.chains.used].string, &main->data.chains.array[main->data.chains.used].used, &main->data.chains.array[main->data.chains.used].size);
        }

        if (F_status_is_error(main->setting.state.status)) {
          firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase_by));

          return;
        }

        main->data.chains.array[main->data.chains.used].used = 0;
        main->data.chain_ids.array[i] = main->data.chains.used;

        // Copy the string character by character, ignoring placeholders.
        for (j = main->data.chain_objects.array[i].start; j <= main->data.chain_objects.array[i].stop; ++j) {

          if (main->data.buffer.string[j] == f_fss_placeholder_s.string[0]) continue;

          main->data.chains.array[main->data.chains.used].string[main->data.chains.array[main->data.chains.used].used++] = main->data.buffer.string[j];
          main->cache.arguments.array[1].string[main->cache.arguments.array[1].used++] = main->data.buffer.string[j];
        } // for

        main->cache.arguments.array[1].string[main->cache.arguments.array[1].used] = 0;
        main->data.chains.array[main->data.chains.used].string[main->data.chains.array[main->data.chains.used].used] = 0;

        if (f_compare_dynamic(main->cache.arguments.array[1], firewall_chain_forward_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(main->cache.arguments.array[1], firewall_chain_input_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(main->cache.arguments.array[1], firewall_chain_output_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(main->cache.arguments.array[1], firewall_chain_postrouting_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(main->cache.arguments.array[1], firewall_chain_prerouting_s) == F_equal_to) {
          create_chain = F_false;
        }

        if (create_chain) {
          firewall_print_debug_tool(main->program->warning, firewall_tool_iptables_s, main->cache.arguments);

          tool = firewall_tool_iptables_s;

          main->setting.state.status = fll_execute_program(firewall_tool_iptables_s, main->cache.arguments, 0, 0, (void *) &return_code);

          if (main->setting.state.status == F_child) {
            main->program->child = return_code;

            return;
          }

          if (firewall_signal_check(main)) return;

          if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_child) {
            tool = firewall_tool_ip6tables_s;

            firewall_print_debug_tool(main->program->warning, firewall_tool_ip6tables_s, main->cache.arguments);

            main->setting.state.status = fll_execute_program(firewall_tool_ip6tables_s, main->cache.arguments, 0, 0, (void *) &return_code);
          }

          if (main->setting.state.status == F_child) {
            main->program->child = return_code;

            return;
          }

          if (firewall_signal_check(main)) return;

          if (F_status_is_error(main->setting.state.status)) {
            if (F_status_set_fine(main->setting.state.status) == F_failure) {
              firewall_print_error_operation(main->program->error, tool, main->cache.arguments);
            }
            else {
              firewall_print_error(&main->program.error, macro_firewall_f(fll_execute_program));
            }

            return;
          }
        }

        ++main->data.chains.used;
      }
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_create_custom_chains_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_create_custom_chains_
  f_status_t firewall_operate_create_custom_chains(firewall_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    f_status_t status = F_okay;

    uint8_t tool = firewall_program_iptables_e;
    bool new_chain = F_false;
    bool create_chain = F_false;
    int return_code = 0;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    f_number_unsigned_t length = 0;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    local->chain_ids.used = local->chain_objects.used;

    status = f_memory_arrays_resize(2, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);
    if (F_status_is_error(status)) return status;

    status = f_memory_array_increase_by(local->chain_objects.used, sizeof(f_number_unsigned_t), (void **) &local->chain_ids.array, &local->chain_ids.used, &local->chain_ids.size);
    if (F_status_is_error(status)) return status;

    memset(local->chain_ids.array, 0, sizeof(f_number_unsigned_t) * local->chain_ids.used);

    status = f_string_dynamic_append(firewall_chain_create_command_s, &arguments.array[0]);

    if (F_status_is_error_not(status)) {
      status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_char_t), (void **) &arguments.array[1].string, &arguments.array[1].used, &arguments.array[1].size);
    }
    else {
      f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);

      return status;
    }

    arguments.used = 2;

    reserved->has_lock = F_false;
    reserved->has_stop = F_false;
    reserved->has_main = F_false;

    for (; i < local->chain_objects.used; ++i) {

      new_chain = F_true;
      j = 0;

      if (!((++data->main->signal_check) % firewall_signal_check_d)) {
        if (firewall_signal_received(data)) break;
      }

      // Skip globally reserved chain name: main.
      if (f_compare_dynamic_partial_string(firewall_group_main_s.string, local->buffer, firewall_group_main_s.used, local->chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
        reserved->has_main = F_true;
        reserved->main_at = i;
      }

      // Skip globally reserved chain name: stop.
      if (f_compare_dynamic_partial_string(firewall_group_stop_s.string, local->buffer, firewall_group_stop_s.used, local->chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
        reserved->has_stop = F_true;
        reserved->stop_at = i;
      }

      // Skip globally reserved chain name: lock.
      if (f_compare_dynamic_partial_string(firewall_group_lock_s.string, local->buffer, firewall_group_lock_s.used, local->chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
        reserved->has_lock = F_true;
        reserved->lock_at = i;
      }

      // Skip globally reserved chain name: none.
      if (f_compare_dynamic_partial_string(firewall_chain_none_s.string, local->buffer, firewall_chain_none_s.used, local->chain_objects.array[i]) == F_equal_to) {
        new_chain = F_false;
      }

      if (new_chain) {
        for (; j < data->chains.used; ++j) {

          if (f_compare_dynamic_partial_string(data->chains.array[j].string, local->buffer, data->chains.array[j].used, local->chain_objects.array[i]) == F_equal_to) {
            new_chain = F_false;
            local->chain_ids.array[i] = j;

            break;
          }
        } // for
      }

      if (new_chain) {
        status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &data->chains.array, &data->chains.used, &data->chains.size);
        if (F_status_is_error(status)) break;

        create_chain = F_true;
        length = (local->chain_objects.array[i].stop - local->chain_objects.array[i].start) + 1;

        arguments.array[1].used = 0;

        status = f_memory_array_increase_by(length + 1, sizeof(f_char_t), (void **) &arguments.array[1].string, &arguments.array[1].used, &arguments.array[1].size);
        if (F_status_is_error(status)) break;

        status = f_memory_array_increase_by(length + 1, sizeof(f_char_t), (void **) &data->chains.array[data->chains.used].string, &data->chains.array[data->chains.used].used, &data->chains.array[data->chains.used].size);
        if (F_status_is_error(status)) break;

        data->chains.array[data->chains.used].used = 0;
        local->chain_ids.array[i] = data->chains.used;

        // Copy the string character by character, ignoring placeholders.
        for (j = local->chain_objects.array[i].start; j <= local->chain_objects.array[i].stop; ++j) {

          if (local->buffer.string[j] == f_fss_placeholder_s.string[0]) continue;

          data->chains.array[data->chains.used].string[data->chains.array[data->chains.used].used++] = local->buffer.string[j];
          arguments.array[1].string[arguments.array[1].used++] = local->buffer.string[j];
        } // for

        arguments.array[1].string[arguments.array[1].used] = 0;
        data->chains.array[data->chains.used].string[data->chains.array[data->chains.used].used] = 0;

        if (f_compare_dynamic(arguments.array[1], firewall_chain_forward_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(arguments.array[1], firewall_chain_input_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(arguments.array[1], firewall_chain_output_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(arguments.array[1], firewall_chain_postrouting_s) == F_equal_to) {
          create_chain = F_false;
        }
        else if (f_compare_dynamic(arguments.array[1], firewall_chain_prerouting_s) == F_equal_to) {
          create_chain = F_false;
        }

        if (create_chain) {
          firewall_print_debug_tool(data->main->warning, firewall_tool_iptables_s, arguments);

          tool = firewall_program_iptables_e;
          status = fll_execute_program(firewall_tool_iptables_s, arguments, 0, 0, (void *) &return_code);

          if (status == F_child) {
            data->main->child = return_code;

            break;
          }

          if (F_status_is_error_not(status)) {
            if (firewall_signal_received(data)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            firewall_print_debug_tool(data->main->warning, firewall_tool_ip6tables_s, arguments);

            tool = firewall_program_ip6tables_e;
            status = fll_execute_program(firewall_tool_ip6tables_s, arguments, 0, 0, (void *) &return_code);

            if (status == F_child) {
              data->main->child = return_code;

              break;
            }
          }

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_failure) {
              firewall_print_error_operation(data->main->error, tool == firewall_program_iptables_e ? firewall_tool_iptables_s : firewall_tool_ip6tables_s, arguments);
            }
            else if (F_status_set_fine(status) == F_parameter) {
              firewall_print_error_on_invalid_parameter(data->main->error, "fll_execute_program");
            }
            else {
              firewall_print_error_on_unhandled(data->main->error, "fll_execute_program", F_status_set_fine(status));
            }

            break;
          }
        }

        ++data->chains.used;
      }
    } // for

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);

    return status;
  }
#endif // _di_firewall_operate_create_custom_chains_

#ifdef __cplusplus
} // extern "C"
#endif

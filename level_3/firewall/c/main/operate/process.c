#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_process_rules_perform_
  void firewall_operate_process_rules(firewall_main_t * const main) {

    if (!main || F_status_is_error_not(main->setting.state.status) && main->setting.state.status == F_child) return;

    bool valid = F_true;
    bool is_ip_list = F_false;
    bool ip_list_direction = F_false; // false = source, true = destination.
    bool use_protocol = F_false;
    uint8_t chain = firewall_chain_none_e;
    uint8_t direction = firewall_direction_none_e;
    uint8_t action = firewall_action_append_e;

    int return_code = 0;
    f_number_unsigned_t at = 0;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t repeat = 2;

    f_string_static_t tool = firewall_tool_iptables_s;
    f_ranges_t * const rule_objects = &main->data.rule_objects;
    f_rangess_t * const rule_contents = &main->data.rule_contents;

    if (!(main->data.is & firewall_data_is_global_e)) {
      if (main->setting.devices.array[main->data.device].used) {
        main->cache.device.used = 0;

        main->setting.state.status = f_string_dynamic_append(main->setting.devices.array[main->data.device], &main->cache.device);
        if (F_status_is_error(main->setting.state.status)) return;
      }
    }

    // For custom chains, the chain command may not be specified.
    if (!(main->data.is & firewall_data_is_stop_main_lock_e)) {
      chain = firewall_chain_custom_e;
    }

    for (; i < rule_objects->used; ++i) {

      if (firewall_signal_check(main)) return;

      valid = F_true;
      is_ip_list = F_false;
      ip_list_direction = F_false;

      main->cache.ip_list.used = 0;

      // Process chain rule.
      if (f_compare_dynamic_partial_string(firewall_chain_s.string, main->data.buffer, firewall_chain_s.used, rule_objects->array[i]) == F_equal_to) {
        if (chain == firewall_chain_custom_e) {

          // Custom chains can only apply to themselves, so silently ignore chain commands specified within a custom chain.
          firewall_print_warning_chain_meaningless_line(&main->program.warning, i);

          continue;
        }

        if (rule_contents->array[i].used != 1) {
          valid = F_false;
        }
        else if (f_compare_dynamic_partial_string(firewall_chain_input_s.string, main->data.buffer, firewall_chain_input_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          chain = firewall_chain_input_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_chain_output_s.string, main->data.buffer, firewall_chain_output_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          chain = firewall_chain_output_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_chain_forward_s.string, main->data.buffer, firewall_chain_forward_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          chain = firewall_chain_forward_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_chain_postrouting_s.string, main->data.buffer, firewall_chain_postrouting_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          chain = firewall_chain_postrouting_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_chain_prerouting_s.string, main->data.buffer, firewall_chain_prerouting_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          chain = firewall_chain_prerouting_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_chain_none_s.string, main->data.buffer, firewall_chain_none_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          chain = firewall_chain_none_e;
        }
        else {
          valid = F_false;
        }

        if (valid) continue;
      }

      // Process direction rule
      else if (f_compare_dynamic_partial_string(firewall_direction_s.string, main->data.buffer, firewall_direction_s.used, rule_objects->array[i]) == F_equal_to) {
        if (rule_contents->array[i].used != 1) {
          valid = F_false;
        }
        else if (f_compare_dynamic_partial_string(firewall_direction_input_s.string, main->data.buffer, firewall_direction_input_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          direction = firewall_direction_input_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_direction_output_s.string, main->data.buffer, firewall_direction_output_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          direction = firewall_direction_output_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_direction_none_s.string, main->data.buffer, firewall_direction_none_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          direction = firewall_direction_none_e;
        }
        else {

          // Direction must be specified, and no custom directions are allowed.
          valid = F_false;
        }

        if (valid) continue;
      }

      // Process device rule.
      else if (f_compare_dynamic_partial_string(firewall_device_s.string, main->data.buffer, firewall_device_s.used, rule_objects->array[i]) == F_equal_to) {
        if (rule_contents->array[i].used != 1) {
          valid = F_false;
        }
        else if (f_compare_dynamic_partial_string(firewall_device_all_s.string, main->data.buffer, firewall_device_all_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          main->cache.device.used = 0;

          continue;
        }
        else if (f_compare_dynamic_partial_string(firewall_device_this_s.string, main->data.buffer, firewall_device_this_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          if (main->setting.devices.array[main->data.device].used) {
            main->setting.state.status = f_string_dynamic_append(main->setting.devices.array[main->data.device], &main->cache.device);
          }
          else {
            main->cache.device.used = 0;
          }

          if (F_status_is_error(main->setting.state.status)) return;

          continue;
        }

        if (valid) {
          main->cache.device.used = 0;

          main->setting.state.status = f_string_dynamic_partial_append(main->data.buffer, rule_contents->array[i].array[0], &main->cache.device);
          if (F_status_is_error(main->setting.state.status)) return;

          continue;
        }
      }

      // Process action rule.
      else if (f_compare_dynamic_partial_string(firewall_action_s.string, main->data.buffer, firewall_action_s.used, rule_objects->array[i]) == F_equal_to) {
        if (rule_contents->array[i].used != 1) {
          valid = F_false;
        }
        else if (f_compare_dynamic_partial_string(firewall_action_append_s.string, main->data.buffer, firewall_action_append_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          action = firewall_action_append_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_action_insert_s.string, main->data.buffer, firewall_action_insert_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          action = firewall_action_insert_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_action_policy_s.string, main->data.buffer, firewall_action_policy_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          action = firewall_action_policy_e;
        }
        else if (f_compare_dynamic_partial_string(firewall_action_none_s.string, main->data.buffer, firewall_action_none_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          action = firewall_action_none_e;
        }
        else {
          valid = F_false;
        }

        if (valid) continue;
      }

      // Process ip_list rule.
      else if (f_compare_dynamic_partial_string(firewall_ip_list.string, main->data.buffer, firewall_ip_list.used, rule_objects->array[i]) == F_equal_to) {
        is_ip_list = F_true;

        if (f_compare_dynamic_partial_string(firewall_ip_list_source_s.string, main->data.buffer, firewall_ip_list_source_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          ip_list_direction = F_false;
        }
        else if (f_compare_dynamic_partial_string(firewall_ip_list_destination_s.string, main->data.buffer, firewall_ip_list_destination_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
          ip_list_direction = F_true;
        }
        else {
          valid = F_false;
        }
      }

      // Process protocol rule.
      else if (f_compare_dynamic_partial_string(firewall_protocol_s.string, main->data.buffer, firewall_protocol_s.used, rule_objects->array[i]) == F_equal_to) {
        if (rule_contents->array[i].used != 1) {
          valid = F_false;
        }
        else {
          if (f_compare_dynamic_partial_string(firewall_protocol_none_s.string, main->data.buffer, firewall_protocol_none_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
            use_protocol = F_false;
          }
          else if (rule_contents->array[i].array[0].start <= rule_contents->array[i].array[0].stop) {
            main->cache.protocol.used = 0;

            main->setting.state.status = f_string_dynamic_partial_append(main->data.buffer, rule_contents->array[i].array[0], &main->cache.protocol);
            if (F_status_is_error(main->setting.state.status)) return;

            use_protocol = F_true;
          }
          else {
            use_protocol = F_false;
          }

          continue;
        }
      }

      // Process tool rule.
      else if (f_compare_dynamic_partial_string(firewall_tool_s.string, main->data.buffer, firewall_tool_s.used, rule_objects->array[i]) == F_equal_to) {
        if (rule_contents->array[i].used != 1) {
          valid = F_false;
        }
        else {
          if (f_compare_dynamic_partial_string(firewall_tool_iptables_s.string, main->data.buffer, firewall_tool_iptables_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
            tool = firewall_tool_iptables_s;
            repeat = 1;
          }
          else if (f_compare_dynamic_partial_string(firewall_tool_ip6tables_s.string, main->data.buffer, firewall_tool_ip6tables_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
            tool = firewall_tool_ip6tables_s;
            repeat = 1;
          }
          else if (f_compare_dynamic_partial_string(firewall_tool_ip46tables_s.string, main->data.buffer, firewall_tool_ip46tables_s.used, rule_contents->array[i].array[0]) == F_equal_to) {
            tool = firewall_tool_iptables_s;
            repeat = 2;
          }
          else {
            valid = F_false;
          }

          if (valid) continue;
        }
      }

      // If the remaining rule does not match as firewall_rule_s, then it is an invalid rule.
      else if (f_compare_dynamic_partial_string(firewall_rule_s.string, main->data.buffer, firewall_rule_s.used, rule_objects->array[i]) == F_equal_to_not) {
        firewall_print_warning_object_invalid_missing_line(&main->program.warning, i, main->data.buffer, main->data.rule_objects.array[i]);

        continue;
      }

      if (!valid) {
        firewall_print_warning_content_invalid_missing_line(&main->program.warning, i, main->data.buffer, main->data.rule_objects.array[i]);

        continue;
      }

      for (j = repeat; j; --j) {

        if (firewall_signal_check(main)) return;

        // First add the program name.
        main->cache.arguments.used = 0;

        main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
        if (F_status_is_error(main->setting.state.status)) return;

        if (tool.string == firewall_tool_ip46tables_s.string) {
          tool = (j == 2) ? firewall_tool_iptables_s : firewall_tool_ip6tables_s;
        }

        // Process the action when a non-none chain is specified.
        if (chain != firewall_chain_none_e && action != firewall_action_none_e) {
          main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
          if (F_status_is_error(main->setting.state.status)) return;

          main->cache.arguments.array[main->cache.arguments.used].used = 0;

          if (action == firewall_action_append_e) {
            main->setting.state.status = f_string_dynamic_append(firewall_action_append_operation_s, &main->cache.arguments.array[main->cache.arguments.used]);
          }
          else if (action == firewall_action_insert_e) {
            main->setting.state.status = f_string_dynamic_append(firewall_action_insert_operation_s, &main->cache.arguments.array[main->cache.arguments.used]);
          }
          else if (action == firewall_action_policy_e) {
            main->setting.state.status = f_string_dynamic_append(firewall_action_policy_operation_s, &main->cache.arguments.array[main->cache.arguments.used]);
          }

          if (F_status_is_error(main->setting.state.status)) return;

          if (action == firewall_action_append_e || action == firewall_action_insert_e || action == firewall_action_policy_e) {
            ++main->cache.arguments.used;

            main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
            if (F_status_is_error(main->setting.state.status)) return;

            main->cache.arguments.array[main->cache.arguments.used].used = 0;
            main->setting.state.status = F_data_not;

            // Process the chain, which is required by the action.
            if (chain == firewall_chain_custom_e) {
              main->setting.state.status = f_string_dynamic_append(main->setting.chains.array[main->data.chain_ids.array[main->data.chain]], &main->cache.arguments.array[main->cache.arguments.used]);
            }
            else if (chain == firewall_chain_forward_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_chain_forward_s, &main->cache.arguments.array[main->cache.arguments.used]);
            }
            else if (chain == firewall_chain_postrouting_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_chain_postrouting_s, &main->cache.arguments.array[main->cache.arguments.used]);
            }
            else if (chain == firewall_chain_prerouting_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_chain_prerouting_s, &main->cache.arguments.array[main->cache.arguments.used]);
            }
            else if (chain == firewall_chain_input_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_chain_input_s, &main->cache.arguments.array[main->cache.arguments.used]);
            }
            else if (chain == firewall_chain_output_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_chain_output_s, &main->cache.arguments.array[main->cache.arguments.used]);
            }

            if (F_status_is_error(main->setting.state.status)) return;

            if (main->setting.state.status == F_data_not) {
              main->setting.state.status = F_okay;
            }
            else {
              ++main->cache.arguments.used;
            }
          }
        }

        // Add the device if and only if a non-none direction is specified.
        if (main->cache.device.used && (direction == firewall_direction_input_e || direction == firewall_direction_output_e)) {
          if (f_compare_dynamic_partial_string(firewall_device_all_s.string, main->data.buffer, firewall_device_all_s.used, rule_contents->array[i].array[0]) == F_equal_to_not) {
            main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
            if (F_status_is_error(main->setting.state.status)) return;

            main->cache.arguments.array[main->cache.arguments.used].used = 0;

            if (direction == firewall_direction_input_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_device_input_operation_s, &main->cache.arguments.array[main->cache.arguments.used]);
              if (F_status_is_error(main->setting.state.status)) return;

              ++main->cache.arguments.used;
            }
            else if (direction == firewall_direction_output_e) {
              main->setting.state.status = f_string_dynamic_append(firewall_device_output_operation_s, &main->cache.arguments.array[main->cache.arguments.used]);
              if (F_status_is_error(main->setting.state.status)) return;

              ++main->cache.arguments.used;
            }
          }

          // Add the device.
          if (main->cache.device.used) {
            main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
            if (F_status_is_error(main->setting.state.status)) return;

            main->cache.arguments.array[main->cache.arguments.used].used = 0;

            main->setting.state.status = f_string_dynamic_append(main->cache.device, &main->cache.arguments.array[main->cache.arguments.used]);
            if (F_status_is_error(main->setting.state.status)) return;

            ++main->cache.arguments.used;
          }
        }

        if (use_protocol) {
          main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
          if (F_status_is_error(main->setting.state.status)) return;

          main->cache.arguments.array[main->cache.arguments.used].used = 0;

          main->setting.state.status = f_string_dynamic_append(firewall_protocol_operation_s, &main->cache.arguments.array[main->cache.arguments.used]);
          if (F_status_is_error(main->setting.state.status)) return;

          ++main->cache.arguments.used;

          if (main->cache.protocol.used) {
            main->setting.state.status = f_memory_array_increase(firewall_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
            if (F_status_is_error(main->setting.state.status)) return;

            main->cache.arguments.array[main->cache.arguments.used].used = 0;

            main->setting.state.status = f_string_dynamic_append(main->cache.protocol, &main->cache.arguments.array[main->cache.arguments.used]);
            if (F_status_is_error(main->setting.state.status)) return;

            ++main->cache.arguments.used;
          }
        }

        // Last up is the "rule".
        if ((!is_ip_list && rule_contents->array[i].used > 0) || (is_ip_list && rule_contents->array[i].used > 1)) {
          at = 0;

          if (is_ip_list) {

            // Skip past the chain.
            ++at;

            if (rule_contents->array[i].array[at].start <= rule_contents->array[i].array[at].stop) {
              main->cache.ip_list.used = 0;

              main->setting.state.status = f_string_dynamic_partial_append(main->data.buffer, rule_contents->array[i].array[at], &main->cache.ip_list);

              if (F_status_is_error(main->setting.state.status)) {

                // Prevent the loop below from being processed.
                at = rule_contents->array[i].used;
              }
              else {
                ++at;
              }
            }
          }

          main->setting.state.status = f_memory_array_increase_by(rule_contents->array[i].used, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);
          if (F_status_is_error(main->setting.state.status)) return;

          for (; at < rule_contents->array[i].used; ++at) {

            if (firewall_signal_check(main)) return;

            if (rule_contents->array[i].array[at].start <= rule_contents->array[i].array[at].stop) {
              main->cache.arguments.array[main->cache.arguments.used].used = 0;

              main->setting.state.status = f_string_dynamic_partial_append(main->data.buffer, rule_contents->array[i].array[at], &main->cache.arguments.array[main->cache.arguments.used]);
              if (F_status_is_error(main->setting.state.status)) return;

              ++main->cache.arguments.used;
            }
          } // for
        }
        else {
          firewall_print_warning_content_invalid_missing_line(&main->program.warning, i, main->data.buffer, main->data.rule_objects.array[i]);

          break;
        }

        // Now execute the generated commands.
        if (main->cache.arguments.used > 1) {
          if (is_ip_list) {
            main->cache.basic_objects.used = 0;
            main->cache.basic_contents.used = 0;
            main->cache.buffer.used = 0;
            main->cache.delimits.used = 0;
            main->cache.path_file_specific.used = 0;

            main->setting.state.status = f_string_dynamic_append(firewall_network_path_s, &main->cache.path_file_specific);

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_string_dynamic_append(main->cache.ip_list, &main->cache.path_file_specific);
            }

            if (F_status_is_error(main->setting.state.status)) {
              firewall_print_error(&main->program.error, macro_firewall_f(f_string_dynamic_append));

              return;
            }

            main->setting.state.status = f_file_open(main->cache.path_file_specific, 0, &main->cache.file);

            if (F_status_is_error(main->setting.state.status)) {
              firewall_print_error_file(&main->program.error, macro_firewall_f(f_file_open), main->cache.path_file_specific, f_file_operation_open_s, fll_error_file_type_file_e);

              f_file_stream_close(&main->cache.file);

              return;
            }

            main->setting.state.status = f_file_read(main->cache.file, &main->cache.buffer);

            f_file_stream_close(&main->cache.file);

            if (F_status_is_error(main->setting.state.status)) {
              firewall_print_error_file(&main->program.error, macro_firewall_f(f_file_read), main->cache.path_file_specific, f_file_operation_read_s, fll_error_file_type_file_e);

              return;
            }

            main->cache.delimits.used = 0;

            if (main->cache.buffer.used) {
              main->data.range.start = 0;
              main->data.range.stop = main->cache.buffer.used - 1;
            }
            else {
              main->data.range.start = 1;
              main->data.range.stop = 0;
            }

            fll_fss_basic_read(main->cache.buffer, &main->data.range, &main->cache.basic_objects, &main->cache.basic_contents, 0, &main->cache.delimits, 0, &main->setting.state);

            if (F_status_is_error(main->setting.state.status)) {
              if (F_status_set_fine(main->setting.state.status) == F_data_not_eos || F_status_set_fine(main->setting.state.status) == F_data_not || F_status_set_fine(main->setting.state.status) == F_data_not_stop) {
                // Empty files are to be silently ignored.
              }
              else {
                firewall_print_error_file(&main->program.error, macro_firewall_f(fll_fss_basic_read), main->cache.path_file_specific, f_file_operation_read_s, fll_error_file_type_file_e);

                return;
              }
            }

            f_fss_apply_delimit(main->cache.delimits, &main->cache.buffer, &main->setting.state);

            if (F_status_is_error(main->setting.state.status)) {
              firewall_print_error(&main->program.error, macro_firewall_f(f_fss_apply_delimit));
            }

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_memory_array_increase_by(2, sizeof(f_string_dynamic_t), (void **) &main->cache.arguments.array, &main->cache.arguments.used, &main->cache.arguments.size);

              if (F_status_is_error(main->setting.state.status)) {
                firewall_print_error(&main->program.error, macro_firewall_f(f_memory_array_increase_by));

                return;
              }

              main->cache.arguments.array[main->cache.arguments.used].used = 0;

              main->setting.state.status = f_string_dynamic_append(ip_list_direction ? firewall_ip_list_destination_action_s : firewall_ip_list_source_action_s, &main->cache.arguments.array[main->cache.arguments.used]);

              if (F_status_is_error(main->setting.state.status)) {
                firewall_print_error(&main->program.error, macro_firewall_f(f_string_dynamic_append));

                return;
              }

              ++main->cache.arguments.used;

              // The ip_list file contains objects and no content, all objects are what matter an nothing else.
              for (at = 0; at < main->cache.basic_objects.used; ++at) {

                if (firewall_signal_check(main)) return;

                main->cache.arguments.array[main->cache.arguments.used].used = 0;

                main->setting.state.status = f_string_dynamic_partial_append(main->cache.buffer, main->cache.basic_objects.array[at], &main->cache.arguments.array[main->cache.arguments.used]);

                if (F_status_is_error(main->setting.state.status)) {
                  firewall_print_error(&main->program.error, macro_firewall_f(f_string_dynamic_partial_append));

                  return;
                }

                ++main->cache.arguments.used;

                firewall_print_debug_tool(&main->program.warning, tool, main->cache.arguments);

                main->setting.state.status = fll_execute_program(tool, main->cache.arguments, 0, 0, (void *) &return_code);

                if (main->setting.state.status == F_child) {
                  main->program.child = return_code;

                  return;
                }

                // Remove ip_argument from arguments string.
                --main->cache.arguments.used;

                if (F_status_is_error(main->setting.state.status)) {
                  if (F_status_set_fine(main->setting.state.status) == F_failure) {
                    firewall_print_error_operation(&main->program.error, tool, main->cache.arguments);
                  }
                  else {
                    firewall_print_error(&main->program.error, macro_firewall_f(fll_execute_program));
                  }

                  return;
                }
              } // for

              // Remove ip_list_action from arguments string.
              --main->cache.arguments.used;
            }

            if (F_status_set_fine(main->setting.state.status) == F_failure || F_status_set_fine(main->setting.state.status) == F_parameter) return;
          }
          else {
            firewall_print_debug_tool(&main->program.warning, tool, main->cache.arguments);

            main->setting.state.status = fll_execute_program(tool, main->cache.arguments, 0, 0, (void *) &return_code);

            if (main->setting.state.status == F_child) {
              main->program.child = return_code;

              return;
            }

            if (F_status_is_error(main->setting.state.status)) {
              if (F_status_set_fine(main->setting.state.status) == F_failure) {
                firewall_print_error_operation(&main->program.error, tool, main->cache.arguments);
              }
              else {
                firewall_print_error(&main->program.error, macro_firewall_f(fll_execute_program));
              }

              return;
            }
          }
        }
      } // for
    } // for

    main->setting.state.status = F_okay;
  }
#endif // _di_firewall_operate_process_rules_perform_

#ifdef __cplusplus
} // extern "C"
#endif

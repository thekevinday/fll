#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_operate_process_rules_
  void firewall_operate_process_rules(firewall_main_t * const main) {

    if (!main || F_status_is_error(main->setting.state.status)) return;

    firewall_operate_process_rules_perform(main);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) != F_failure) {
        firewall_print_error_unhandled(&main->error, macro_firewall_f(firewall_operate_process_rules_perform));
      }
    }
    else {
      main->setting.state.status = F_okay;
    }
  }
#endif // _di_firewall_operate_process_rules_

#ifndef _di_firewall_operate_process_rules_perform_
  void firewall_operate_process_rules_perform(firewall_main_t * const main) {

    if (!main) return;

    bool invalid = F_false;
    bool is_ip_list = F_false;

    // Iptables command arguments
    bool ip_list_direction = F_false; // false = source, true = destination.
    bool use_protocol = F_false;
    uint8_t tool = firewall_program_ip46tables_e;
    uint8_t chain = firewall_chain_none_id_e;

    int return_code = 0;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t r = 0;
    f_number_unsigned_t repeat = 2;
    f_number_unsigned_t length = 0;

    f_string_static_t current_tool = firewall_tool_iptables_s;

    uint8_t direction = firewall_direction_none_id_e;
    uint8_t action = firewall_action_append_id_e;

    f_string_dynamic_t ip_list = f_string_dynamic_t_initialize;
    f_string_dynamic_t device = f_string_dynamic_t_initialize;
    f_string_dynamic_t protocol = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    if (!local->is_global) {
      if (data->devices.array[local->device].used) {
        device.used = 0;

        status = f_string_dynamic_append(data->devices.array[local->device], &device);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not) {
            firewall_print_error_on_allocation_failure(data->main->error);
          }

          return status;
        }
      }
    }

    // For custom chains, the chain command may not be specified.
    if (!(local->is_main || local->is_stop || local->is_lock)) {
      chain = firewall_chain_custom_id_e;
    }

    for (; F_status_is_error_not(status) && i < local->rule_objects.used; ++i) {

      if (!((++data->main->signal_check) % firewall_signal_check_d)) {
        if (firewall_signal_received(data)) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &ip_list.string, &ip_list.used, &ip_list.size);
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &protocol.string, &protocol.used, &protocol.size);

          f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);

          return F_status_set_error(F_interrupt);
        }

        data->main->signal_check = 0;
      }

      length = (local->rule_objects.array[i].stop - local->rule_objects.array[i].start) + 1;
      invalid = F_false;

      is_ip_list = F_false;
      ip_list_direction = F_false;

      ip_list.used = 0;

      // Process chain rule.
      if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_chain_s, length) == F_equal_to) {
        if (chain == firewall_chain_custom_id_e) {

          // Custom chains can only apply to themselves, so silently ignore chain commands specified within a custom chain.
          fll_print_format("%r%[%QAt line %ul, the chain option is meaningless inside of a custom chain.%]%r", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, f_string_eol_s);

          continue;
        }

        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

        if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
          invalid = F_true;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_input_s, length) == F_equal_to) {
          chain = firewall_chain_input_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_output_s, length) == F_equal_to) {
          chain = firewall_chain_output_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_forward_s, length) == F_equal_to) {
          chain = firewall_chain_forward_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_postrouting_s, length) == F_equal_to) {
          chain = firewall_chain_postrouting_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_prerouting_s, length) == F_equal_to) {
          chain = firewall_chain_prerouting_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_none_s, length) == F_equal_to) {
          chain = firewall_chain_none_id_e;
        }
        else {
          invalid = F_true;
        }

        if (!invalid) continue;
      }

      // Process direction rule
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_direction_s, length) == F_equal_to) {
        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

        if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
          invalid = F_true;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_direction_input_s, length) == F_equal_to) {
          direction = firewall_direction_input_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_direction_output_s, length) == F_equal_to) {
          direction = firewall_direction_output_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_direction_none_s, length) == F_equal_to) {
          direction = firewall_direction_none_id_e;
        }
        else {

          // Direction must be specified, and no custom directions are allowed.
          invalid = F_true;
        }

        if (!invalid) continue;
      }

      // Process device rule.
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_device_s, length) == F_equal_to) {
        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

        if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
          invalid = F_true;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_device_all_s, length) == F_equal_to) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);

          continue;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_device_this_s, length) == F_equal_to) {
          if (data->devices.array[local->device].used) {
            status = f_memory_array_increase_by(data->devices.array[local->device].used, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);
            if (F_status_is_error(status)) break;

            memcpy(device.string, data->devices.array[local->device].string, sizeof(f_char_t) * data->devices.array[local->device].used);

            device.used = data->devices.array[local->device].used;
          }
          else {
            f_memory_array_resize(0, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);
          }

          continue;
        }

        if (!invalid) {
          device.used = 0;

          if (length) {
            status = f_string_dynamic_partial_append(local->buffer, local->rule_contents.array[i].array[0], &device);

            if (F_status_is_error(status)) break;
          }

          continue;
        }
      }

      // Process action rule.
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_action_s, length) == F_equal_to) {
        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

        if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
          invalid = F_true;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_append_s, length) == F_equal_to) {
          action = firewall_action_append_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_insert_s, length) == F_equal_to) {
          action = firewall_action_insert_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_policy_s, length) == F_equal_to) {
          action = firewall_action_policy_id_e;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_none_s, length) == F_equal_to) {
          action = firewall_action_none_id_e;
        }
        else {
          invalid = F_true;
        }

        if (!invalid) continue;
      }

      // Process ip_list rule.
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_ip_list, length) == F_equal_to) {
        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;
        is_ip_list = F_true;

        if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_ip_list_source_s, length) == F_equal_to) {
          ip_list_direction = F_false;
        }
        else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_ip_list_destination_s, length) == F_equal_to) {
          ip_list_direction = F_true;
        }
        else {
          invalid = F_true;
        }
      }
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_protocol_s, length) == F_equal_to) {
        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

        if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
          invalid = F_true;
        }
        else {
          if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_protocol_none_s, length) == F_equal_to) {
            use_protocol = F_false;
          }
          else if (length) {
            protocol.used = 0;

            status = f_string_dynamic_partial_append(local->buffer, local->rule_contents.array[i].array[0], &protocol);

            if (F_status_is_error(status)) break;

            use_protocol = F_true;
          }
          else {
            use_protocol = F_false;
          }

          continue;
        }
      }

      // Process tool rule.
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_tool_s, length) == F_equal_to) {
        length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

        if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
          invalid = F_true;
        }
        else {
          if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_tool_iptables_s, length) == F_equal_to) {
            tool = firewall_program_iptables_e;
            current_tool = firewall_tool_iptables_s;
            repeat = 1;
          }
          else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_tool_ip6tables_s, length) == F_equal_to) {
            tool = firewall_program_ip6tables_e;
            current_tool = firewall_tool_ip6tables_s;
            repeat = 1;
          }
          else if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_tool_ip46tables_s, length) == F_equal_to) {
            tool = firewall_program_ip46tables_e;
            current_tool = firewall_tool_iptables_s;
            repeat = 2;
          }
          else {
            invalid = F_true;
          }

          if (!invalid) continue;
        }
      }

      // If the remaining rule does not match as firewall_rule_s, then it is an invalid rule.
      else if (f_compare_dynamic_string(local->buffer.string + local->rule_objects.array[i].start, firewall_rule_s, length) == F_equal_to_not) {
        if (length) {
          f_file_stream_lock(data->main->warning.to);

          fl_print_format("%r%[%QAt line %ul, the object '%]", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, data->main->warning.notable);
          fl_print_format(f_string_format_Q_range_single_s.string, data->main->warning.to, data->main->warning.notable, local->buffer, local->rule_objects.array[i], data->main->warning.notable);
          fl_print_format("%[' is invalid.%]%r", data->main->warning.to, data->main->warning.context, data->main->warning.context, f_string_eol_s);

          f_file_stream_unlock(data->main->warning.to);
        }
        else {
          fll_print_format("%r%[%QAt line %ul, the object is missing.%]%r", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, f_string_eol_s);
        }

        continue;
      }

      if (invalid) {
        length = (local->rule_objects.array[i].stop - local->rule_objects.array[i].start) + 1;

        if (length) {
          f_file_stream_lock(data->main->warning.to);

          fl_print_format("%r%[%QAt line %ul, the object '%]", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context);
          fl_print_format(f_string_format_Q_range_single_s.string, data->main->warning.to, data->main->warning.notable, local->buffer, local->rule_objects.array[i], data->main->warning.notable);
          fl_print_format("%[' has invalid content '%]", data->main->warning.to, data->main->warning.context, data->main->warning.context);
          fl_print_format(f_string_format_Q_range_single_s.string, data->main->warning.to, data->main->warning.notable, local->buffer, local->rule_contents.array[i].array[0], data->main->warning.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, data->main->warning.to, data->main->warning.context, data->main->warning.context, f_string_eol_s);

          f_file_stream_unlock(data->main->warning.to);
        }
        else {
          fll_print_format("%r%[%QAt line %ul, the object has no content.%]%r", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, f_string_eol_s);
        }

        continue;
      }

      for (r = repeat; F_status_is_error_not(status) && r; --r) {

        arguments.used = 0;

        // First add the program name.
        status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
        if (F_status_is_error(status)) break;

        if (tool == firewall_program_ip46tables_e) {
          if (r == 2) {
            current_tool = firewall_tool_iptables_s;
          }
          else {
            current_tool = firewall_tool_ip6tables_s;
          }
        }

        // Process the action when a non-none chain is specified.
        if (chain != firewall_chain_none_id_e && action != firewall_action_none_id_e) {
          status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
          if (F_status_is_error(status)) break;

          arguments.array[arguments.used].used = 0;

          if (action == firewall_action_append_id_e) {
            status = f_string_dynamic_append(firewall_action_append_command_s, &arguments.array[arguments.used]);
          }
          else if (action == firewall_action_insert_id_e) {
            status = f_string_dynamic_append(firewall_action_insert_command_s, &arguments.array[arguments.used]);
          }
          else if (action == firewall_action_policy_id_e) {
            status = f_string_dynamic_append(firewall_action_policy_command_s, &arguments.array[arguments.used]);
          }

          if (F_status_is_error(status)) break;

          if (action == firewall_action_append_id_e || action == firewall_action_insert_id_e || action == firewall_action_policy_id_e) {
            ++arguments.used;

            status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
            if (F_status_is_error(status)) break;

            arguments.array[arguments.used].used = 0;
            status = F_data_not;

            // Process the chain, which is required by the action.
            if (chain == firewall_chain_custom_id_e) {
              status = f_string_dynamic_append(data->chains.array[local->chain_ids.array[local->chain]], &arguments.array[arguments.used]);
            }
            else if (chain == firewall_chain_forward_id_e) {
              status = f_string_dynamic_append(firewall_chain_forward_s, &arguments.array[arguments.used]);
            }
            else if (chain == firewall_chain_postrouting_id_e) {
              status = f_string_dynamic_append(firewall_chain_postrouting_s, &arguments.array[arguments.used]);
            }
            else if (chain == firewall_chain_prerouting_id_e) {
              status = f_string_dynamic_append(firewall_chain_prerouting_s, &arguments.array[arguments.used]);
            }
            else if (chain == firewall_chain_input_id_e) {
              status = f_string_dynamic_append(firewall_chain_input_s, &arguments.array[arguments.used]);
            }
            else if (chain == firewall_chain_output_id_e) {
              status = f_string_dynamic_append(firewall_chain_output_s, &arguments.array[arguments.used]);
            }

            if (F_status_is_error(status)) break;

            if (status == F_data_not) {
              status = F_okay;
            }
            else {
              ++arguments.used;
            }
          }
        }

        // Add the device if and only if a non-none direction is specified.
        if (device.used && (direction == firewall_direction_input_id_e || direction == firewall_direction_output_id_e)) {
          if (f_compare_dynamic_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_device_all_s, length) == F_equal_to_not) {

            status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
            if (F_status_is_error(status)) break;

            arguments.array[arguments.used].used = 0;

            if (direction == firewall_direction_input_id_e) {
              status = f_string_dynamic_append(firewall_device_input_command_s, &arguments.array[arguments.used]);

              if (F_status_is_error(status)) break;

              ++arguments.used;
            }
            else if (direction == firewall_direction_output_id_e) {
              status = f_string_dynamic_append(firewall_device_output_command_s, &arguments.array[arguments.used]);

              if (F_status_is_error(status)) break;

              ++arguments.used;
            }
          }

          // Add the device.
          if (device.used) {
            status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
            if (F_status_is_error(status)) break;

            arguments.array[arguments.used].used = 0;

            status = f_string_dynamic_append(device, &arguments.array[arguments.used]);

            if (F_status_is_error(status)) break;

            ++arguments.used;
          }
        }

        if (use_protocol) {
          status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
          if (F_status_is_error(status)) break;

          arguments.array[arguments.used].used = 0;

          status = f_string_dynamic_append(firewall_protocol_command_s, &arguments.array[arguments.used]);

          if (F_status_is_error(status)) break;

          ++arguments.used;

          if (protocol.used) {
            status = f_memory_array_increase(firewall_default_allocation_step_d, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
            if (F_status_is_error(status)) break;

            arguments.array[arguments.used].used = 0;

            status = f_string_dynamic_append(protocol, &arguments.array[arguments.used]);

            if (F_status_is_error(status)) break;

            ++arguments.used;
          }
        }

        // Last up is the "rule".
        if ((!is_ip_list && local->rule_contents.array[i].used > 0) || (is_ip_list && local->rule_contents.array[i].used > 1)) {
          f_number_unsigned_t subcounter = 0;

          if (is_ip_list) {

            // Skip past the chain.
            ++subcounter;

            length = (local->rule_contents.array[i].array[subcounter].stop - local->rule_contents.array[i].array[subcounter].start) + 1;

            if (length) {
              ip_list.used = 0;

              status = f_string_dynamic_partial_append(local->buffer, local->rule_contents.array[i].array[subcounter], &ip_list);

              if (F_status_is_error(status)) {

                // Prevent the loop below from being processed.
                subcounter = local->rule_contents.array[i].used;
              }
              else {
                ++subcounter;
              }
            }
          }

          status = f_memory_array_increase_by(local->rule_contents.array[i].used, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);
          if (F_status_is_error(status)) break;

          for (; subcounter < local->rule_contents.array[i].used; ++subcounter) {

            length = (local->rule_contents.array[i].array[subcounter].stop - local->rule_contents.array[i].array[subcounter].start) + 1;

            if (length) {
              arguments.array[arguments.used].used = 0;

              status = f_string_dynamic_partial_append(local->buffer, local->rule_contents.array[i].array[subcounter], &arguments.array[arguments.used]);
              if (F_status_is_error(status)) break;

              ++arguments.used;
            }
          } // for
        }
        else {
          length = (local->rule_objects.array[i].stop - local->rule_objects.array[i].start) + 1;

          f_file_stream_lock(data->main->warning.to);

          fl_print_format("%r%[%QAt line %ul, the object '%]", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context);
          fl_print_format(f_string_format_Q_range_single_s.string, data->main->warning.to, data->main->warning.notable, local->buffer, local->rule_objects.array[i], data->main->warning.notable);
          fl_print_format("%]%[' has no content.%]%r", data->main->warning.to, data->main->warning.context, data->main->warning.context, f_string_eol_s);

          f_file_stream_unlock(data->main->warning.to);

          break;
        }

        // Now execute the generated commands.
        if (arguments.used > 1) {
          if (is_ip_list) {
            f_file_t file = f_file_t_initialize;
            f_string_dynamic_t path_file = f_string_dynamic_t_initialize;
            f_string_dynamic_t local_buffer = f_string_dynamic_t_initialize;

            f_ranges_t basic_objects = f_ranges_t_initialize;
            f_rangess_t basic_contents = f_ranges_t_initialize;

            status = f_string_dynamic_append(firewall_network_path_s, &path_file);

            if (F_status_is_error_not(status)) {
              status = f_string_dynamic_append(ip_list, &path_file);
            }

            if (F_status_is_error_not(status)) {
              status = f_file_open(path_file, 0, &file);
            }

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_parameter) {
                if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
                  firewall_print_error_on_invalid_parameter(data->main->error, "f_file_open");
                }
              }
              else if (F_status_set_fine(status) == F_file_found_not) {

                // The file does not have to exist
                if (data->main->error.verbosity != f_console_verbosity_verbose_e || data->main->error.verbosity == f_console_verbosity_debug_e) {
                  fll_print_format("%r%[%QCannot find the file '%Q'.%]%r", data->main->warning.to, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, path_file, data->main->warning.context, f_string_eol_s);
                }

                status = F_okay;
              }
              else if (F_status_set_fine(status) == F_file_open) {
                if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
                  fll_print_format("%r%[%QUnable to open the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                }
              }
              else if (F_status_set_fine(status) == F_file_descriptor) {
                if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
                  fll_print_format("%r%[%QFile descriptor error while trying to open the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                }
              }
              else if (F_status_set_fine(status) == F_memory_not) {
                firewall_print_error_on_allocation_failure(data->main->error);
              }
              else {
                firewall_print_error_on_unhandled(data->main->error, "f_file_open", F_status_set_fine(status));
              }

              f_file_stream_flush(file);
              f_file_stream_close(&file);
            }
            else {
              status = f_file_read(file, &local_buffer);

              f_file_stream_flush(file);
              f_file_stream_close(&file);

              if (F_status_is_error(status)) {
                if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
                  if (F_status_set_fine(status) == F_parameter) {
                    firewall_print_error_on_invalid_parameter(data->main->error, "f_file_read");
                  }
                  else if (F_status_set_fine(status) == F_number_overflow) {
                    fll_print_format("%r%[%QInteger overflow while trying to buffer the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                  }
                  else if (F_status_set_fine(status) == F_file_closed) {
                    fll_print_format("%r%[%QThe file '%Q' is no longer open.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                  }
                  else if (F_status_set_fine(status) == F_file_seek) {
                    fll_print_format("%r%[%QA seek error occurred while accessing the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                  }
                  else if (F_status_set_fine(status) == F_file_read) {
                    fll_print_format("%r%[%QA read error occurred while accessing the file '%Q'.%]%r", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                  }
                  else if (F_status_set_fine(status) != F_memory_not) {
                    firewall_print_error_on_unhandled(data->main->error, "f_file_read", F_status_set_fine(status));
                  }
                }
              }
              else {
                f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

                {
                  f_state_t state = f_state_t_initialize;
                  f_range_t input = macro_f_range_t_initialize_2(local_buffer.used);

                  status = fll_fss_basic_read(local_buffer, state, &input, &basic_objects, &basic_contents, 0, &delimits, 0);
                }

                if (F_status_set_error(status)) {
                  status = F_status_set_fine(status);

                  if (status == F_parameter) {
                    firewall_print_error_on_invalid_parameter_for_file(data->main->error, "fll_fss_basic_read", path_file.used ? path_file : f_string_empty_s);
                  }
                  else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
                    // Empty files are to be silently ignored.
                  }
                  else if (status != F_memory_not) {
                    firewall_print_error_on_unhandled_for_file(data->main->error, "fll_fss_basic_read", status, path_file.used ? path_file : f_string_empty_s);
                  }

                  status = F_status_set_error(status);
                }

                if (F_status_is_error_not(status)) {
                  f_state_t state = f_state_t_initialize;

                  status = f_fss_apply_delimit(state, delimits, &local_buffer);

                  if (F_status_is_error(status)) {
                    fll_error_print(data->main->error, F_status_set_fine(status), "f_fss_apply_delimit", fll_error_file_flag_fallback_e);
                  }
                }

                if (F_status_is_error_not(status)) {
                  status = f_memory_array_increase_by(2, sizeof(f_string_dynamic_t), (void **) &arguments.array, &arguments.used, &arguments.size);

                  if (F_status_is_error_not(status)) {
                    arguments.array[arguments.used].used = 0;

                    if (ip_list_direction) {
                      status = f_string_dynamic_append(firewall_ip_list_destination_action_s, &arguments.array[arguments.used]);
                    }
                    else {
                      status = f_string_dynamic_append(firewall_ip_list_source_action_s, &arguments.array[arguments.used]);
                    }
                  }

                  if (F_status_is_error(status)) {
                    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);

                    break;
                  }

                  ++arguments.used;

                  // The ip_list file contains objects and no content, all objects are what matter an nothing else.
                  for (f_number_unsigned_t at = 0; at < basic_objects.used; ++at) {

                    arguments.array[arguments.used].used = 0;

                    status = f_string_dynamic_partial_append(local_buffer, basic_objects.array[at], &arguments.array[arguments.used]);
                    if (F_status_is_error(status)) break;

                    ++arguments.used;

                    firewall_print_debug_tool(data->main->warning, current_tool, arguments);

                    status = fll_execute_program(current_tool, arguments, 0, 0, (void *) &return_code);

                    if (status == F_child) {
                      f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);
                      f_memory_array_resize(0, sizeof(f_char_t), (void **) &ip_list.string, &ip_list.used, &ip_list.size);
                      f_memory_array_resize(0, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);
                      f_memory_array_resize(0, sizeof(f_char_t), (void **) &protocol.string, &protocol.used, &protocol.size);

                      f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);

                      data->main->child = return_code;

                      return status;
                    }

                    // Remove ip_argument from arguments string.
                    --arguments.used;

                    if (F_status_is_error(status)) {
                      if (F_status_set_fine(status) == F_failure) {
                        firewall_print_error_operation(data->main->error, current_tool, arguments);
                      }
                      else if (F_status_set_fine(status) == F_parameter) {
                        firewall_print_error_on_invalid_parameter(data->main->error, "fll_execute_program");
                      }
                      else {
                        firewall_print_error_on_unhandled(data->main->error, "fll_execute_program", F_status_set_fine(status));
                      }

                      break;
                    }
                  } // for

                  // Remove ip_list_action from arguments string.
                  --arguments.used;
                }

                f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);
              }
            }

            f_memory_array_resize(0, sizeof(f_char_t), (void **) &local_buffer.string, &local_buffer.used, &local_buffer.size);
            f_memory_array_resize(0, sizeof(f_char_t), (void **) &path_file.string, &path_file.used, &path_file.size);

            f_memory_array_resize(0, sizeof(f_range_t), (void **) &basic_objects.array, &basic_objects.used, &basic_objects.size);
            f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &basic_contents.array, &basic_contents.used, &basic_contents.size, &f_rangess_delete_callback);

            if (F_status_set_fine(status) == F_failure || F_status_set_fine(status) == F_parameter) break;
          }
          else {
            firewall_print_debug_tool(data->main->warning, current_tool, arguments);

            status = fll_execute_program(current_tool, arguments, 0, 0, (void *) &return_code);

            if (status == F_child) {
              f_memory_array_resize(0, sizeof(f_char_t), (void **) &ip_list.string, &ip_list.used, &ip_list.size);
              f_memory_array_resize(0, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);
              f_memory_array_resize(0, sizeof(f_char_t), (void **) &protocol.string, &protocol.used, &protocol.size);

              f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);

              data->main->child = return_code;

              return status;
            }

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_failure) {
                firewall_print_error_operation(data->main->error, current_tool, arguments);
              }
              else if (F_status_set_fine(status) == F_parameter) {
                firewall_print_error_on_invalid_parameter(data->main->error, "fll_execute_program");
              }
              else if (F_status_set_fine(status) != F_memory_not) {
                firewall_print_error_on_unhandled(data->main->error, "fll_execute_program", F_status_set_fine(status));
              }

              break;
            }
          }
        }
      } // for
    } // for

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_memory_not) {
        firewall_print_error_on_allocation_failure(data->main->error);
      }
    }

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &ip_list.string, &ip_list.used, &ip_list.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &device.string, &device.used, &device.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &protocol.string, &protocol.used, &protocol.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &arguments.string, &arguments.used, &arguments.size, &f_string_dynamics_delete_callback);

    return status;
  }
#endif // _di_firewall_operate_process_rules_perform_

#ifdef __cplusplus
} // extern "C"
#endif

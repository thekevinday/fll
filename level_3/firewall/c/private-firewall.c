#include <level_3/firewall.h>
#include "private-firewall.h"

f_return_status firewall_perform_commands(const firewall_local_data local, const firewall_data data) {
  f_status status = f_none;
  f_status status2 = f_none;

  f_string_length i = 0;
  f_dynamic_strings arguments = f_dynamic_strings_initialize;
  f_dynamic_string argument = f_dynamic_string_initialize;

  f_s_int results = 0;
  f_string_length length = 0;
  f_bool invalid = f_false;
  f_bool is_ip_list = f_false;
  f_dynamic_string ip_list = f_dynamic_string_initialize;

  // iptables command arguments
  f_bool device_all = f_false;
  f_bool ip_list_direction = f_false; // false = source, true = destination
  f_bool use_protocol = f_false;
  uint8_t tool = firewall_program_ip46tables;
  uint8_t chain = firewall_chain_none_id;

  f_array_length repeat = 2;
  f_array_length r = 0;

  f_string current_tool = firewall_tool_iptables;
  f_string_length current_tool_length = firewall_tool_iptables_length;

  f_string_length direction = firewall_direction_none_id;
  f_dynamic_string device = f_dynamic_string_initialize;
  f_string_length action = firewall_action_append_id;
  f_dynamic_string protocol = f_dynamic_string_initialize;

  if (local.is_global) {
    device_all = f_true;
  }
  else {
    if (data.devices.array[local.device].used > 0) {
      f_new_dynamic_string(status, device, data.devices.array[local.device].used);

      if (f_error_is_error(status)) {
        f_delete_dynamic_string(status2, device);

        return status;
      }

      firewall_macro_concat_string(device.string, data.devices.array[local.device].string, data.devices.array[local.device].used);
      device.used = data.devices.array[local.device].used;
    }
  }

  // for custom chains, the chain command may not be specified.
  if (!(local.is_main || local.is_stop || local.is_lock)) {
    chain = firewall_chain_custom_id;
  }

  for (; i < local.rule_objects.used; i++) {
    length  = firewall_macro_structure_size(local.rule_objects, i);
    invalid = f_false;

    is_ip_list = f_false;
    ip_list_direction = f_false;

    f_delete_dynamic_string(status2, ip_list);

    // process chain rule
    if (length >= firewall_chain_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_chain, length, firewall_chain_length) == f_equal_to) {
      if (chain == firewall_chain_custom_id) {
        // custom chains can only apply to themselves, so silently ignore chain commands specified within a custom chain.
        fprintf(f_standard_warning, "WARNING: At line %i, the chain option is meaningle ss inside of a custom chain.", i);
        continue;
      }

      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);

      if (firewall_macro_rule_contents_has_incorrect_items(i, 1)) {
        invalid = f_true;
      }
      else if (length >= firewall_chain_input_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_chain_input, length, firewall_chain_input_length) == f_equal_to) {
        chain = firewall_chain_input_id;
      }
      else if (length >= firewall_chain_output_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_chain_output, length, firewall_chain_output_length) == f_equal_to) {
        chain = firewall_chain_output_id;
      }
      else if (length >= firewall_chain_forward_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_chain_forward, length, firewall_chain_forward_length) == f_equal_to) {
        chain = firewall_chain_forward_id;
      }
      else if (length >= firewall_chain_postrouting_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_chain_postrouting, length, firewall_chain_postrouting_length) == f_equal_to) {
        chain = firewall_chain_postrouting_id;
      }
      else if (length >= firewall_chain_prerouting_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_chain_prerouting, length, firewall_chain_prerouting_length) == f_equal_to) {
        chain = firewall_chain_prerouting_id;
      }
      else if (length >= firewall_chain_none_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_chain_none, length, firewall_chain_none_length) == f_equal_to) {
        chain = firewall_chain_none_id;
      }
      else {
        invalid = f_true;
      }

      if (!invalid) continue;
    }
    // process direction rule
    else if (length >= firewall_direction_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_direction, length, firewall_direction_length) == f_equal_to) {
      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);

      if (firewall_macro_rule_contents_has_incorrect_items(i, 1)) {
        invalid = f_true;
      }
      else if (length >= firewall_direction_input_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_direction_input, length, firewall_direction_input_length) == f_equal_to) {
        direction = firewall_direction_input_id;
      }
      else if (length >= firewall_direction_output_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_direction_output, length, firewall_direction_output_length) == f_equal_to) {
        direction = firewall_direction_output_id;
      }
      else if (length >= firewall_direction_none_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_direction_none, length, firewall_direction_none_length) == f_equal_to) {
        direction = firewall_direction_none_id;
      }
      else {
        // direction must be specified, and no custom directions are allowed.
        invalid = f_true;
      }

      if (!invalid) continue;
    }
    // process device rule.
    else if (length >= firewall_device_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_device, length, firewall_device_length) == f_equal_to) {
      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);

      if (firewall_macro_rule_contents_has_incorrect_items(i, 1)) {
        invalid = f_true;
      }
      else if (length >= firewall_device_all_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_device_all, length, firewall_device_all_length) == f_equal_to) {
        f_delete_dynamic_string(status, device);
        device_all = f_true;
        continue;
      }
      else if (length >= firewall_device_this_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_device_this, length, firewall_device_this_length) == f_equal_to) {
        if (data.devices.array[local.device].used > 0) {
          if (data.devices.array[local.device].used > device.size) {
            f_resize_dynamic_string(status, device, data.devices.array[local.device].used);

            if (f_error_is_error(status)) break;
          }

          firewall_macro_concat_string(device.string, data.devices.array[local.device].string, data.devices.array[local.device].used);

          device.used = data.devices.array[local.device].used;
        }
        else {
          f_delete_dynamic_string(status, device);
        }

        device_all = f_false;
        continue;
      }

      if (!invalid) {
        if (length > 0) {
          if (length > device.size) {
            f_resize_dynamic_string(status, device, length);

            if (f_error_is_error(status)) break;
          }

          firewall_macro_concat_string(device.string, local.buffer.string + local.rule_contents.array[i].array[0].start, length);
          device.used = length;
        }
        else {
          f_delete_dynamic_string(status, device);
        }

        device_all = f_false;
        continue;
      }
    }
    // process action rule.
    else if (length >= firewall_action_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_action, length, firewall_action_length) == f_equal_to) {
      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);

      if (firewall_macro_rule_contents_has_incorrect_items(i, 1)) {
        invalid = f_true;
      }
      else if (length >= firewall_action_append_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_action_append, length, firewall_action_append_length) == f_equal_to) {
        action = firewall_action_append_id;
      }
      else if (length >= firewall_action_insert_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_action_insert, length, firewall_action_insert_length) == f_equal_to) {
        action = firewall_action_insert_id;
      }
      else if (length >= firewall_action_policy_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_action_policy, length, firewall_action_policy_length) == f_equal_to) {
        action = firewall_action_policy_id;
      }
      else if (length >= firewall_action_none_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_action_none, length, firewall_action_none_length) == f_equal_to) {
        action = firewall_action_none_id;
      }
      else {
        invalid = f_true;
      }

      if (!invalid) continue;
    }
    // process ip_list rule.
    else if (length >= firewall_ip_list_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_ip_list, length, firewall_ip_list_length) == f_equal_to) {
      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);
      is_ip_list = f_true;

      if (length >= firewall_ip_list_source_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_ip_list_source, length, firewall_ip_list_source_length) == f_equal_to) {
        ip_list_direction = f_false;
      }
      else if (length >= firewall_ip_list_destination_length && fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_ip_list_destination, length, firewall_ip_list_destination_length) == f_equal_to) {
        ip_list_direction = f_true;
      }
      else {
        invalid = f_true;
      }
    }
    else if (length >= firewall_protocol_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_protocol, length, firewall_protocol_length) == f_equal_to) {
      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);

      if (firewall_macro_rule_contents_has_incorrect_items(i, 1)) {
        invalid = f_true;
      }
      else {
        if (fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_protocol_none, length, firewall_protocol_none_length) == f_equal_to) {
          use_protocol = f_false;
        }
        else if (length > 0) {
          f_delete_dynamic_string(status, protocol);
          f_new_dynamic_string(status, protocol, length);

          if (f_error_is_error(status)) break;

          firewall_macro_concat_string(protocol.string, local.buffer.string + local.rule_contents.array[i].array[0].start, length);
          protocol.used = length;
          use_protocol = f_true;
        }
        else {
          use_protocol = f_false;
        }

        continue;
      }
    }
    // process tool rule.
    else if (length >= firewall_tool_length && fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_tool, length, firewall_tool_length) == f_equal_to) {
      length = firewall_macro_structure_size(local.rule_contents.array[i], 0);

      if (firewall_macro_rule_contents_has_incorrect_items(i, 1)) {
        invalid = f_true;
      }
      else {
        if (fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_tool_iptables, length, firewall_tool_iptables_length) == f_equal_to) {
          tool = firewall_program_iptables;
          current_tool = firewall_tool_iptables;
          current_tool_length = firewall_tool_iptables_length;
          repeat = 1;
        }
        else if (fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_tool_ip6tables, length, firewall_tool_ip6tables_length) == f_equal_to) {
          tool = firewall_program_ip6tables;
          current_tool = firewall_tool_ip6tables;
          current_tool_length = firewall_tool_ip6tables_length;
          repeat = 1;
        }
        else if (fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_tool_ip46tables, length, firewall_tool_ip46tables_length) == f_equal_to) {
          tool = firewall_program_ip46tables;
          current_tool = firewall_tool_iptables;
          current_tool_length = firewall_tool_iptables_length;
          repeat = 2;
        }
        else {
          invalid = f_true;
        }

        if (!invalid) continue;
      }
    }
    // process rule rule, if the remaining rule does not match as firewall_rule, then it is an invalid rule.
    else if (length < firewall_rule_length || fl_compare_strings(local.buffer.string + local.rule_objects.array[i].start, (f_string) firewall_rule, length, firewall_rule_length) == f_not_equal_to) {
      if (length > 0) {
        fl_print_color_code(f_standard_warning, data.context.warning);
        fprintf(f_standard_warning, "WARNING: At line %i, the object '", i);
        f_print_string(f_standard_warning, local.buffer.string + local.rule_objects.array[i].start, length);
        fprintf(f_standard_warning, "' is invalid");
        fl_print_color_code(f_standard_warning, data.context.reset);
      }
      else {
        fprintf(f_standard_warning, "WARNING: At line %i, the object is missing", i);
      }

      fprintf(f_standard_warning, "\n");
      continue;
    }

    if (invalid) {
      length = firewall_macro_structure_size(local.rule_objects, i);

      if (length > 0) {
        fl_print_color_code(f_standard_warning, data.context.warning);
        fprintf(f_standard_warning, "WARNING: At line %i, the object '", i);
        f_print_string(f_standard_warning, local.buffer.string + local.rule_objects.array[i].start, length);
        fprintf(f_standard_warning, "' has invalid content '");
        f_print_string(f_standard_warning, local.buffer.string + local.rule_contents.array[i].array[0].start, firewall_macro_structure_size(local.rule_contents.array[i], 0));
        fprintf(f_standard_warning, "'");
        fl_print_color_code(f_standard_warning, data.context.reset);
        fprintf(f_standard_warning, "\n");
      }
      else {
        fl_print_color_line(f_standard_warning, data.context.warning, data.context.reset, "WARNING: At line %i, the object has no content", i);
      }

      continue;
    }

    for (r = repeat; r > 0; r--) {
      // first add the program name
      f_delete_dynamic_strings(status, arguments);
      f_new_dynamic_strings(status, arguments, firewall_default_allocation_step);

      if (f_error_is_error(status)) break;

      if (tool == firewall_program_ip46tables) {
        if (r == 2) {
          current_tool = firewall_tool_iptables;
          current_tool_length = firewall_tool_iptables_length;
        }
        else {
          current_tool = firewall_tool_ip6tables;
          current_tool_length = firewall_tool_ip6tables_length;
        }
      }

      f_delete_dynamic_string(status, argument);

      if (f_error_is_error(status)) break;

      // process the action when a non-none chain is specified.
      if (chain != firewall_chain_none_id && action != firewall_action_none_id) {
        if (action == firewall_action_append_id) {
          f_new_dynamic_string(status, argument, firewall_action_append_command_length);

          if (f_error_is_error(status)) break;

          firewall_macro_concat_string(argument.string, firewall_action_append_command, firewall_action_append_command_length);
          argument.used = firewall_action_append_command_length;
        }
        else if (action == firewall_action_insert_id) {
          f_new_dynamic_string(status, argument, firewall_action_insert_command_length);

          if (f_error_is_error(status)) break;

          firewall_macro_concat_string(argument.string, firewall_action_insert_command, firewall_action_insert_command_length);
          argument.used = firewall_action_insert_command_length;
        }
        else if (action == firewall_action_policy_id) {
          f_new_dynamic_string(status, argument, firewall_action_policy_command_length);

          if (f_error_is_error(status)) break;

          firewall_macro_concat_string(argument.string, firewall_action_policy_command, firewall_action_policy_command_length);
          argument.used = firewall_action_policy_command_length;
        }

        if (argument.used > 0) {
          firewall_macro_append_argument_to_arguments(status, arguments, argument)
          if (f_error_is_error(status)) {
            f_delete_dynamic_string(status2, argument);
            break;
          }

          // process the chain, which is required by the action.
          if (chain == firewall_chain_custom_id) {
            if (data.chains.array[local.chain_ids.array[local.chain]].used > 0) {
              f_new_dynamic_string(status, argument, data.chains.array[local.chain_ids.array[local.chain]].used);

              if (f_error_is_error(status)) break;

              firewall_macro_concat_string(argument.string, data.chains.array[local.chain_ids.array[local.chain]].string, data.chains.array[local.chain_ids.array[local.chain]].used);
              argument.used = data.chains.array[local.chain_ids.array[local.chain]].used;
            }
          }
          else if (chain == firewall_chain_forward_id) {
            f_new_dynamic_string(status, argument, firewall_chain_forward_length);

            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_chain_forward, firewall_chain_forward_length);
            argument.used = firewall_chain_forward_length;
          }
          else if (chain == firewall_chain_postrouting_id) {
            f_new_dynamic_string(status, argument, firewall_chain_postrouting_length);

            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_chain_postrouting, firewall_chain_postrouting_length);
            argument.used += firewall_chain_postrouting_length;
          }
          else if (chain == firewall_chain_prerouting_id) {
            f_new_dynamic_string(status, argument, firewall_chain_prerouting_length);

            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_chain_prerouting, firewall_chain_prerouting_length);
            argument.used = firewall_chain_prerouting_length;
          }
          else if (chain == firewall_chain_input_id) {
            f_new_dynamic_string(status, argument, firewall_chain_input_length);

            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_chain_input, firewall_chain_input_length);
            argument.used = firewall_chain_input_length;
          }
          else if (chain == firewall_chain_output_id) {
            f_new_dynamic_string(status, argument, firewall_chain_output_length);

            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_chain_output, firewall_chain_output_length);
            argument.used = firewall_chain_output_length;
          }

          if (argument.used > 0) {
            firewall_macro_append_argument_to_arguments(status, arguments, argument)
            if (f_error_is_error(status)) {
              break;
            }
          }
        }
      }

      // add the device if and only if a non-none direction is specified.
      if (device.used > 0 && (direction == firewall_direction_input_id || direction == firewall_direction_output_id)) {
        if (length < firewall_device_all_length || fl_compare_strings(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string) firewall_device_all, length, firewall_device_all_length) == f_not_equal_to) {
          if (direction == firewall_direction_input_id) {
            f_new_dynamic_string(status, argument, firewall_device_input_command_length);
            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_device_input_command, firewall_device_input_command_length);
            argument.used = firewall_device_input_command_length;
          }
          else if (direction == firewall_direction_output_id) {
            f_new_dynamic_string(status, argument, firewall_device_output_command_length);
            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, firewall_device_output_command, firewall_device_output_command_length);
            argument.used = firewall_device_output_command_length;
          }

          if (argument.used > 0) {
            firewall_macro_append_argument_to_arguments(status, arguments, argument)
            if (f_error_is_error(status)) {
              break;
            }
          }
        }

        // add the device.
        if (device.used > 0) {
          f_new_dynamic_string(status, argument, device.used);

          if (f_error_is_error(status)) break;

          firewall_macro_concat_string(argument.string, device.string, device.used);
          argument.used = device.used;

          firewall_macro_append_argument_to_arguments(status, arguments, argument)
          if (f_error_is_error(status)) {
            break;
          }
        }
      }

      if (use_protocol) {
        f_new_dynamic_string(status, argument, firewall_protocol_command_length);

        if (f_error_is_error(status)) break;

        firewall_macro_concat_string(argument.string, firewall_protocol_command, firewall_protocol_command_length);
        argument.used = firewall_protocol_command_length;

        firewall_macro_append_argument_to_arguments(status, arguments, argument)
        if (f_error_is_error(status)) {
          break;
        }

        if (protocol.used > 0) {
          f_new_dynamic_string(status, argument, protocol.used);

          if (f_error_is_error(status)) break;

          firewall_macro_concat_string(argument.string, protocol.string, protocol.used);
          argument.used = protocol.used;

          firewall_macro_append_argument_to_arguments(status, arguments, argument)
          if (f_error_is_error(status)) {
            break;
          }
        }
      }

      // last up is the "rule"
      if ((!is_ip_list && local.rule_contents.array[i].used > 0) || (is_ip_list && local.rule_contents.array[i].used > 1)) {
        f_string_length subcounter = 0;

        if (is_ip_list) {
          // skip past the chain
          subcounter++;

          length = firewall_macro_structure_size(local.rule_contents.array[i], subcounter);

          if (length > 0) {
            f_new_dynamic_string(status, ip_list, length);

            if (f_error_is_error(status)) {
              // prevent the loop below from being processed.
              subcounter = local.rule_contents.array[i].used;
            }
            else {
              firewall_macro_concat_string(ip_list.string, local.buffer.string + local.rule_contents.array[i].array[subcounter].start, length);
              ip_list.used = length;

              subcounter++;
            }
          }
        }

        for (; subcounter < local.rule_contents.array[i].used; subcounter++) {
          length = firewall_macro_structure_size(local.rule_contents.array[i], subcounter);

          if (length > 0) {
            f_new_dynamic_string(status, argument, length);

            if (f_error_is_error(status)) break;

            firewall_macro_concat_string(argument.string, local.buffer.string + local.rule_contents.array[i].array[subcounter].start, length);
            argument.used = length;

            firewall_macro_append_argument_to_arguments(status, arguments, argument)
            if (f_error_is_error(status)) {
              break;
            }
          }
        } // for
      }
      else {
        length = firewall_macro_structure_size(local.rule_objects, i);

        fl_print_color_code(f_standard_warning, data.context.warning);
        fprintf(f_standard_warning, "WARNING: At line %i, the object '", i);
        f_print_string(f_standard_warning, local.buffer.string + local.rule_objects.array[i].start, length);
        fprintf(f_standard_warning, "' has no content");
        fl_print_color_code(f_standard_warning, data.context.reset);
        fprintf(f_standard_warning, "\n");

        break;
      }

      // now execute the generated commands.
      if (arguments.used > 1) {
        if (is_ip_list) {
          f_file file = f_file_initialize;
          f_dynamic_string file_path = f_dynamic_string_initialize;
          f_dynamic_string local_buffer = f_dynamic_string_initialize;
          f_file_position file_position = f_file_position_initialize;

          f_fss_objects basic_objects = f_fss_objects_initialize;
          f_fss_contents basic_contents = f_fss_objects_initialize;

          f_new_dynamic_string(status, file_path, network_path_length + ip_list.used + firewall_default_allocation_step);

          if (status == f_none) {
            firewall_macro_concat_string(file_path.string, network_path, network_path_length);
            firewall_macro_concat_string(file_path.string + network_path_length, ip_list.string, ip_list.used);
            file_path.used = file_path.size;
            file_path.string[file_path.used] = 0;

            status = f_file_open(&file, file_path.string);
          }

          if (f_error_is_error(status)) {
            status = f_error_set_fine(status);

            if (status == f_invalid_parameter) {
              fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
            }
            else if (status == f_file_not_found) {
              // the file does not have to exist
              fl_print_color_line(f_standard_warning, data.context.warning, data.context.reset, "WARNING: Cannot find the file '%.*s'", file_path.used, file_path.string);
              status = f_none;
            }
            else if (status == f_file_open_error) {
              fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Unable to open the file '%.*s'", file_path.used, file_path.string);
            }
            else if (status == f_file_descriptor_error) {
              fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: File descriptor error while trying to open the file '%.*s'", file_path.used, file_path.string);
            }
            else if (f_macro_test_for_allocation_errors(status)) {
              fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: unable to allocate memory");
            }
            else {
              fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", f_error_set_error(status));
            }

            if (status != f_file_not_found) {
              status = f_error_set_error(status);
            }

            f_file_close(&file);
          }
          else {
            if (file_position.total_elements == 0) {
              fseek(file.file, 0, SEEK_END);
              file_position.total_elements = ftell(file.file);
              fseek(file.file, 0, SEEK_SET);
            }

            status = fl_file_read(file, file_position, &local_buffer);

            f_file_close(&file);

            if (f_error_is_error(status)) {
              status = f_error_set_fine(status);

              if (status == f_invalid_parameter) {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read()");
              }
              else if (status == f_overflow) {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Integer overflow while trying to buffer the file '%.*s'", file_path.used, file_path.string);
              }
              else if (status == f_file_not_open) {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: The file '%.*s' is no longer open", file_path.used, file_path.string);
              }
              else if (status == f_file_seek_error) {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: A seek error occurred while accessing the file '%.*s'", file_path.used, file_path.string);
              }
              else if (status == f_file_read_error) {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: A read error occurred while accessing the file '%.*s'", file_path.used, file_path.string);
              }
              else if (f_macro_test_for_allocation_errors(status)) {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: unable to allocate memory");
              }
              else {
                fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read()", f_error_set_error(status));
              }

              status = f_error_set_error(status);
            }
            else {
              {
                f_string_location input = f_string_location_initialize;

                input.stop = local_buffer.used - 1;

                status = fll_fss_basic_read(&local_buffer, &input, &basic_objects, &basic_contents);
              }

              if (f_error_set_error(status)) {
                status = f_error_set_fine(status);

                if (status == f_invalid_parameter) {
                  fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_read() for the file '%.*s'", file_path.used, file_path.string);
                }
                else if (status == f_no_data_on_eos || status == f_no_data || status == f_no_data_on_stop) {
                  // empty files are to be silently ignored
                }
                else if (f_macro_test_for_allocation_errors(status)) {
                  fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: unable to allocate memory");
                }
                else {
                  fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_basic_read() for the file '%.*s'", f_error_set_error(status), file_path.used, file_path.string);
                }

                status = f_error_set_error(status);
              }
              else {
                f_string_length buffer_counter = 0;
                f_string_length ip_length = 0;
                f_dynamic_string ip_list_action = f_dynamic_string_initialize;

                if (ip_list_direction) {
                  f_resize_dynamic_string(status, ip_list_action, firewall_ip_list_destination_action_length);

                  if (f_error_is_error(status)) break;

                  firewall_macro_concat_string(ip_list_action.string, firewall_ip_list_destination_action, firewall_ip_list_destination_action_length);
                  ip_list_action.used = firewall_ip_list_destination_action_length;
                }
                else {
                  f_resize_dynamic_string(status, ip_list_action, firewall_ip_list_source_action_length);

                  if (f_error_is_error(status)) break;

                  firewall_macro_concat_string(ip_list_action.string, firewall_ip_list_source_action, firewall_ip_list_source_action_length);
                  ip_list_action.used = firewall_ip_list_source_action_length;
                }

                status = f_none;
                if (arguments.used + 2 > arguments.size) {
                  f_resize_dynamic_strings(status, arguments, arguments.size + 2);
                }

                if (f_error_is_error(status)) {
                  fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: unable to allocate memory");

                  f_delete_dynamic_string(status2, ip_list_action);
                }
                else {
                  f_dynamic_string ip_argument = f_dynamic_string_initialize;

                  firewall_macro_append_argument_to_arguments(status, arguments, ip_list_action)
                  if (f_error_is_error(status)) {
                    f_delete_dynamic_string(status2, ip_argument);
                    break;
                  }

                  // the ip_list file contains objects and no content, all objects are what matter an nothing else
                  for (; buffer_counter < basic_objects.used; buffer_counter++) {
                    ip_length = firewall_macro_structure_size(basic_objects, buffer_counter);

                    f_new_dynamic_string(status, ip_argument, ip_length);

                    if (f_error_is_error(status)) {
                      fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: unable to allocate memory");
                      break;
                    }

                    firewall_macro_concat_string(ip_argument.string, local_buffer.string + basic_objects.array[buffer_counter].start, ip_length);
                    ip_argument.used = ip_length;

                    firewall_macro_append_argument_to_arguments(status, arguments, ip_argument)
                    if (f_error_is_error(status)) break;

                    // print command when debugging.
                    #ifdef _en_firewall_debug_
                      if (data.parameters[firewall_parameter_debug].result == f_console_result_found) {
                        fl_print_color_code(f_standard_debug, data.context.warning);
                        fprintf(f_standard_debug, "%s ", current_tool);

                        for (f_string_length i = 0; i < arguments.used; i++) {
                          fprintf(f_standard_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
                        } // for

                        fl_print_color_code(f_standard_debug, data.context.reset);
                        fprintf(f_standard_debug, "\n");
                      }
                    #endif // _en_firewall_debug_

                    status = fll_execute_program((f_string) current_tool, arguments, &results);

                    if (status == f_failure) {
                      fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to perform requested %s operation:", current_tool);
                      fprintf(f_standard_error, "  ");

                      fl_print_color_code(f_standard_error, data.context.error);

                      fprintf(f_standard_error, "%s ", current_tool);
                      for (f_string_length i = 0; i < arguments.used; i++) {
                        fprintf(f_standard_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
                      } // for

                      fl_print_color_code(f_standard_error, data.context.reset);
                      fprintf(f_standard_error, "\n");

                      // remove ip_argument from arguments string.
                      f_delete_dynamic_string(status2, arguments.array[arguments.used]);
                      arguments.used--;

                      break;
                    }
                    else if (status == f_invalid_parameter) {
                      fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_execute_program()");

                      // remove ip_argument from arguments string.
                      f_delete_dynamic_string(status2, arguments.array[arguments.used]);
                      arguments.used--;

                      break;
                    }

                    // remove ip_argument from arguments string.
                    f_delete_dynamic_string(status2, arguments.array[arguments.used]);
                    arguments.used--;
                  } // for

                  f_delete_dynamic_string(status2, ip_argument);

                  // remove ip_list_action from arguments string.
                  f_delete_dynamic_string(status2, arguments.array[arguments.used]);
                  arguments.used--;
                }
              }
            }
          }

          f_delete_dynamic_string(status2, local_buffer);
          f_delete_dynamic_string(status2, file_path);
          f_delete_fss_objects(status2, basic_objects);
          f_delete_fss_contents(status2, basic_contents);

          if (status == f_failure || status == f_invalid_parameter) break;
        }
        else {
          // print command when debugging.
          #ifdef _en_firewall_debug_
            if (data.parameters[firewall_parameter_debug].result == f_console_result_found) {
              fl_print_color_code(f_standard_debug, data.context.warning);
              fprintf(f_standard_debug, "%s ", current_tool);

              for (f_string_length i = 0; i < arguments.used; i++) {
                fprintf(f_standard_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
              } // for

              fl_print_color_code(f_standard_debug, data.context.reset);
              fprintf(f_standard_debug, "\n");
            }
          #endif // _en_firewall_debug_

          status = fll_execute_program(current_tool, arguments, &results);

          if (status == f_failure) {
            fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to perform requested %s operation:", current_tool);
            fprintf(f_standard_error, "  ");
            fl_print_color_code(f_standard_error, data.context.error);

            fprintf(f_standard_error, "%s ", current_tool);
            for (f_string_length i = 0; i < arguments.used; i++) {
              fprintf(f_standard_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            fl_print_color_code(f_standard_error, data.context.reset);
            fprintf(f_standard_error, "\n");

            break;
          }
          else if (status == f_invalid_parameter) {
            fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_execute_program()");
            break;
          }
        }
      }
    } // for
  } // for

  f_delete_dynamic_string(status2, ip_list);
  f_delete_dynamic_string(status2, argument);
  f_delete_dynamic_strings(status2, arguments);
  f_delete_dynamic_string(status2, device);
  f_delete_dynamic_string(status2, protocol);

  return status;
}

f_return_status firewall_create_custom_chains(firewall_reserved_chains *reserved, firewall_local_data *local, firewall_data *data) {
  f_status status = f_none;
  f_status status2 = f_none;

  uint8_t tool = firewall_program_iptables;
  f_bool new_chain = f_false;
  f_bool create_chain = f_false;
  f_s_int results = 0;

  f_array_length i = 0;
  f_array_length j = 0;

  f_string_length length = 0;
  f_string_location location = f_string_location_initialize;
  f_dynamic_strings arguments = f_dynamic_strings_initialize;

  f_dynamic_string fixed_string = f_dynamic_string_initialize;

  f_delete_array_lengths(status, local->chain_ids);
  f_new_array_lengths(status, local->chain_ids, local->chain_objects.used);

  if (f_error_is_error(status)) {
    return status;
  }

  f_new_dynamic_strings(status, arguments, 2);

  if (f_error_is_error(status)) {
    return status;
  }

  f_new_dynamic_string(status, arguments.array[0], firewall_chain_create_command_length);

  if (f_error_is_error(status)) {
    f_delete_dynamic_strings(status2, arguments);

    return status;
  }

  firewall_macro_concat_string(arguments.array[0].string, firewall_chain_create_command, firewall_chain_create_command_length);

  arguments.array[0].used = firewall_chain_create_command_length;

  f_new_dynamic_string(status, arguments.array[1], firewall_default_allocation_step);

  if (f_error_is_error(status)) {
    arguments.used = 1;
    f_delete_dynamic_strings(status2, arguments);

    return status;
  }

  arguments.used = 2;

  reserved->has_lock = f_false;
  reserved->has_stop = f_false;
  reserved->has_main = f_false;

  while (i < local->chain_objects.used) {
    new_chain = f_true;
    j = 0;

    // skip globally reserved chain name: main
    location.start = 0;
    location.stop = firewall_group_main_length - 1;
    fixed_string.string = firewall_group_main;
    fixed_string.used = firewall_group_main_length;
    if (fl_compare_dynamic_strings_partial(local->buffer, fixed_string, local->chain_objects.array[i], location) == f_equal_to) {
      new_chain = f_false;
      reserved->has_main = f_true;
      reserved->main_at = i;
    }

    // skip globally reserved chain name: stop
    location.start = 0;
    location.stop = firewall_group_stop_length - 1;
    fixed_string.string = firewall_group_stop;
    fixed_string.used = firewall_group_stop_length;
    if (fl_compare_dynamic_strings_partial(local->buffer, fixed_string, local->chain_objects.array[i], location) == f_equal_to) {
      new_chain = f_false;
      reserved->has_stop = f_true;
      reserved->stop_at = i;
    }

    // skip globally reserved chain name: lock
    location.start = 0;
    location.stop = firewall_group_lock_length - 1;
    fixed_string.string = firewall_group_lock;
    fixed_string.used = firewall_group_lock_length;
    if (fl_compare_dynamic_strings_partial(local->buffer, fixed_string, local->chain_objects.array[i], location) == f_equal_to) {
      new_chain = f_false;
      reserved->has_lock = f_true;
      reserved->lock_at = i;
    }

    // skip globally reserved chain name: none
    location.start = 0;
    location.stop = firewall_group_lock_length - 1;
    fixed_string.string = firewall_chain_none;
    fixed_string.used = firewall_chain_none_length;
    if (fl_compare_dynamic_strings_partial(local->buffer, fixed_string, local->chain_objects.array[i], location) == f_equal_to) {
      new_chain = f_false;
    }

    f_clear_dynamic_string(fixed_string);

    if (new_chain) {
      while (j < data->chains.used) {
        location.start = 0;
        location.stop = data->chains.array[j].used - 1;

        if (fl_compare_dynamic_strings_partial(local->buffer, data->chains.array[j], local->chain_objects.array[i], location) == f_equal_to) {
          new_chain = f_false;
          local->chain_ids.array[i] = j;

          break;
        }

        j++;
      } // while
    }

    if (new_chain) {
      if (data->chains.used >= data->chains.size) {
        f_resize_dynamic_strings(status, data->chains, data->chains.used + firewall_default_allocation_step);

        if (f_error_is_error(status)) {
          f_delete_dynamic_strings(status2, arguments);

          return status;
        }
      }

      create_chain = f_true;
      length = firewall_macro_structure_size(local->chain_objects, i);

      arguments.array[1].used = 0;
      if (length > arguments.array[1].size) {
        f_resize_dynamic_string(status, arguments.array[1], length);

        if (f_error_is_error(status)) {
          f_delete_dynamic_strings(status2, arguments);

          return status;
        }
      }

      f_new_dynamic_string(status, data->chains.array[data->chains.used], length);

      if (f_error_is_error(status)) {
        f_delete_dynamic_strings(status2, arguments);

        return status;
      }

      data->chains.array[data->chains.used].used = 0;
      local->chain_ids.array[i] = data->chains.used;
      arguments.array[1].used = 0;
      j = local->chain_objects.array[i].start;

      // copy the string character by character, ignoring placeholders.
      while (j <= local->chain_objects.array[i].stop) {
        if (local->buffer.string[j] == f_fss_delimit_placeholder) {
          j++;
          continue;
        }

        data->chains.array[data->chains.used].string[data->chains.array[data->chains.used].used] = local->buffer.string[j];
        data->chains.array[data->chains.used].used++;
        arguments.array[1].string[arguments.array[1].used] = local->buffer.string[j];
        arguments.array[1].used++;
        j++;
      } // while

      if (fl_compare_strings(arguments.array[1].string, firewall_chain_forward, arguments.array[1].used, firewall_chain_forward_length) == f_equal_to) {
        create_chain = f_false;
      }
      else if (fl_compare_strings(arguments.array[1].string, firewall_chain_input, arguments.array[1].used, firewall_chain_input_length) == f_equal_to) {
        create_chain = f_false;
      }
      else if (fl_compare_strings(arguments.array[1].string, firewall_chain_output, arguments.array[1].used, firewall_chain_output_length) == f_equal_to) {
        create_chain = f_false;
      }
      else if (fl_compare_strings(arguments.array[1].string, firewall_chain_postrouting, arguments.array[1].used, firewall_chain_postrouting_length) == f_equal_to) {
        create_chain = f_false;
      }
      else if (fl_compare_strings(arguments.array[1].string, firewall_chain_prerouting, arguments.array[1].used, firewall_chain_prerouting_length) == f_equal_to) {
        create_chain = f_false;
      }

      if (create_chain) {
        // print command when debugging.
        #ifdef _en_firewall_debug_
          if (data->parameters[firewall_parameter_debug].result == f_console_result_found) {
            fl_print_color_code(f_standard_debug, data->context.warning);
            fprintf(f_standard_debug, "%s ", firewall_tool_iptables);

            for (f_string_length i = 0; i < arguments.used; i++) {
              fprintf(f_standard_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            fl_print_color_code(f_standard_debug, data->context.reset);
            fprintf(f_standard_debug, "\n");
          }
        #endif // _en_firewall_debug_

        tool = firewall_program_iptables;
        status = fll_execute_program((f_string) firewall_tool_iptables, arguments, &results);

        if (f_error_is_not_error(status)) {
          // print command when debugging.
          #ifdef _en_firewall_debug_
            if (data->parameters[firewall_parameter_debug].result == f_console_result_found) {
              fl_print_color_code(f_standard_debug, data->context.warning);
              fprintf(f_standard_debug, "%s ", firewall_tool_ip6tables);

              for (f_string_length i = 0; i < arguments.used; i++) {
                fprintf(f_standard_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
              } // for

              fl_print_color_code(f_standard_debug, data->context.reset);
              fprintf(f_standard_debug, "\n");
            }
          #endif // _en_firewall_debug_

          tool = firewall_program_ip6tables;
          status = fll_execute_program((f_string) firewall_tool_ip6tables, arguments, &results);
        }

        if (f_error_is_error(status)) {
          status = f_error_set_fine(status);

          if (status == f_failure) {
            if (tool == firewall_program_iptables) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_tool_iptables);
            }
            else if (tool == firewall_program_ip6tables) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_tool_ip6tables);
            }

            fprintf(f_standard_error, "  ");
            fl_print_color_code(f_standard_error, data->context.error);

            if (tool == firewall_program_iptables) {
              fprintf(f_standard_error, "%s ", firewall_tool_iptables);
            }
            else if (tool == firewall_program_ip6tables) {
              fprintf(f_standard_error, "%s ", firewall_tool_ip6tables);
            }

            for (f_string_length i = 0; i < arguments.used; i++) {
              fprintf(f_standard_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            fl_print_color_code(f_standard_error, data->context.reset);
            fprintf(f_standard_error, "\n");
          }
          else if (status == f_invalid_parameter) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_execute_program()");
          }
          else {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_execute_program()", f_error_set_error(status));
          }

          f_delete_dynamic_strings(status2, arguments);
          return status;
        }
      }

      data->chains.used++;
    }

    i++;
  } // while

  f_delete_dynamic_strings(status2, arguments);

  return status;
}

f_return_status firewall_delete_chains(const firewall_data data) {
  const f_string tools[2] = { firewall_tool_iptables, firewall_tool_ip6tables };
  f_status status = f_none;

  for (f_string_length i = 0; i < 2; i++) {
    f_dynamic_strings arguments = f_dynamic_strings_initialize;
    f_dynamic_string argument[1] = f_dynamic_string_initialize;
    f_s_int results = 0;

    argument[0].string = (f_string) "-F";
    argument[0].size = 2;
    argument[0].used = 2;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    // print command when debugging.
    #ifdef _en_firewall_debug_
      if (data.parameters[firewall_parameter_debug].result == f_console_result_found) {
        fl_print_color_code(f_standard_debug, data.context.warning);
        fprintf(f_standard_debug, "%s ", tools[i]);

        for (f_string_length i = 0; i < arguments.used; i++) {
          fprintf(f_standard_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
        } // for

        fl_print_color_code(f_standard_debug, data.context.reset);
        fprintf(f_standard_debug, "\n");
      }
    #endif // _en_firewall_debug_

    status = fll_execute_program(tools[i], arguments, &results);

    if (f_error_is_error(status)) {
      status = f_error_set_fine(status);

      if (status == f_failure) {
        fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to perform requested %s operation:", tools[i]);

        fprintf(f_standard_error, "  ");
        fl_print_color_code(f_standard_error, data.context.error);

        fprintf(f_standard_error, "%s ", tools[i]);
        for (f_string_length i = 0; i < arguments.used; i++) {
          fprintf(f_standard_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
        } // for

        fl_print_color_code(f_standard_error, data.context.reset);
        fprintf(f_standard_error, "\n");
      }
      else if (status == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_execute_program()");
      }
      else {
        fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_execute_program()", f_error_set_error(status));
      }

      return status;
    }
  } // for

  for (f_string_length i = 0; i < 2; i++) {
    f_dynamic_strings arguments = f_dynamic_strings_initialize;
    f_dynamic_string argument[1] = f_dynamic_string_initialize;
    f_s_int results = 0;

    argument[0].string = (f_string) firewall_chain_delete_command;
    argument[0].size = firewall_chain_delete_command_length;
    argument[0].used = firewall_chain_delete_command_length;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    // print command when debugging.
    #ifdef _en_firewall_debug_
      if (data.parameters[firewall_parameter_debug].result == f_console_result_found) {
        fl_print_color_code(f_standard_debug, data.context.warning);
        fprintf(f_standard_debug, "%s ", tools[i]);

        for (f_string_length j = 0; j < arguments.used; j++) {
          fprintf(f_standard_debug, "%.*s ", arguments.array[j].used, arguments.array[j].string);
        } // for

        fl_print_color_code(f_standard_debug, data.context.reset);
        fprintf(f_standard_debug, "\n");
      }
    #endif // _en_firewall_debug_

    status = fll_execute_program(tools[i], arguments, &results);

    if (f_error_is_error(status)) {
      status = f_error_set_fine(status);

      if (status == f_failure) {
        fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to perform requested %s operation:", tools[i]);

        fprintf(f_standard_error, "  ");
        fl_print_color_code(f_standard_error, data.context.error);

        fprintf(f_standard_error, "%s ", tools[i]);
        for (f_string_length j = 0; j < arguments.used; j++) {
          fprintf(f_standard_error, "%.*s ", arguments.array[j].used, arguments.array[j].string);
        } // for

        fl_print_color_code(f_standard_error, data.context.reset);
        fprintf(f_standard_error, "\n");
      }
      else if (status == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_execute_program()");
      }
      else {
        fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_execute_program()", f_error_set_error(status));
      }

      return status;
    }
  } // for

  return status;
}

f_return_status firewall_default_lock(const firewall_data data) {
  const f_string chains[3] = { firewall_chain_input, firewall_chain_output, firewall_chain_forward };
  const f_string tools[2] = { firewall_tool_iptables, firewall_tool_ip6tables };

  const f_string_length lengths[3] = { firewall_chain_input_length, firewall_chain_output_length, firewall_chain_forward_length };

  f_status status = f_none;

  for (f_string_length i = 0; i < 3; i++) {
    f_dynamic_strings arguments = f_dynamic_strings_initialize;
    f_dynamic_string argument[3];

    arguments.array = argument;
    arguments.used = 3;
    arguments.size = arguments.used;

    arguments.array[0].string = (f_string) firewall_action_policy_command;
    arguments.array[1].string = (f_string) chains[i];
    arguments.array[2].string = (f_string) "DROP";

    arguments.array[0].used = firewall_action_append_command_length;
    arguments.array[1].used = lengths[i];
    arguments.array[2].used = 4;

    arguments.array[0].size = arguments.array[0].used;
    arguments.array[1].size = arguments.array[1].used;
    arguments.array[2].size = arguments.array[2].used;

    for (f_string_length j = 0; j < 2; j++) {
      f_s_int results = 0;

      // print command when debugging.
      #ifdef _en_firewall_debug_
        if (data.parameters[firewall_parameter_debug].result == f_console_result_found) {
          fl_print_color_code(f_standard_debug, data.context.warning);
          fprintf(f_standard_debug, "%s ", tools[j]);

          for (f_string_length k = 0; k < arguments.used; k++) {
            fprintf(f_standard_debug, "%.*s ", arguments.array[k].used, arguments.array[k].string);
          } // for

          fl_print_color_code(f_standard_debug, data.context.reset);
          fprintf(f_standard_debug, "\n");
        }
      #endif // _en_firewall_debug_

      status = fll_execute_program(tools[j], arguments, &results);

      if (f_error_is_error(status)) {
        status = f_error_set_fine(status);

        if (status == f_failure) {
          fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "ERROR: Failed to perform requested %s operation:", tools[j]);

          fprintf(f_standard_error, "  ");
          fl_print_color_code(f_standard_error, data.context.error);

          fprintf(f_standard_error, "%s ", tools[j]);
          for (f_string_length k = 0; k < arguments.used; k++) {
            fprintf(f_standard_error, "%.*s ", arguments.array[k].used, arguments.array[k].string);
          } // for

          fl_print_color_code(f_standard_error, data.context.reset);
          fprintf(f_standard_error, "\n");
        }
        else if (status == f_invalid_parameter) {
          fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_execute_program()");
        }
        else {
          fl_print_color_line(f_standard_error, data.context.error, data.context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_execute_program()", f_error_set_error(status));
        }

        return status;
      }
    } // for
  } // for

  return status;
}

f_return_status firewall_buffer_rules(const f_string filename, const f_bool optional, firewall_local_data *local, firewall_data *data) {
  f_file file = f_file_initialize;
  f_status status = f_none;

  status = f_file_open(&file, filename);

  if (f_error_is_error(status)) {
    status = f_error_set_fine(status);

    if (optional) {
      if (status == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open().");
      }
      else if (status != f_file_not_found && status != f_file_open_error && status != f_file_descriptor_error) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open().", f_error_set_error(status));
      }
    } else {
      if (status == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open().");
      }
      else if (status == f_file_not_found) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'.", filename);
      }
      else if (status == f_file_open_error) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'.", filename);
      }
      else if (status == f_file_descriptor_error) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'.", filename);
      }
      else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open().", f_error_set_error(status));
      }
    }

    return status;
  }

  f_macro_file_reset_position(local->file_position, file)

  fflush(stdout);
  status = fl_file_read(file, local->file_position, &local->buffer);

  f_file_close(&file);

  if (f_error_is_error(status)) {
    status = f_error_set_fine(status);

    if (status == f_invalid_parameter) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read().");
    }
    else if (status == f_overflow) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Integer overflow while trying to buffer the file '%s'.", filename);
    }
    else if (status == f_file_not_open) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: The file '%s' is no longer open.", filename);
    }
    else if (status == f_file_seek_error) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A seek error occurred while accessing the file '%s'.", filename);
    }
    else if (status == f_file_read_error) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A read error occurred while accessing the file '%s'.", filename);
    }
    else if (f_macro_test_for_allocation_errors(status)) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory.");
    }
    else {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read().", f_error_set_error(status));
    }

    return status;
  }
  else {
    f_string_location input = f_string_location_initialize;

    input.stop = local->buffer.used - 1;

    status = fll_fss_basic_list_read(&local->buffer, &input, &local->chain_objects, &local->chain_contents);
  }

  if (f_error_is_error(status)) {
    status = f_error_set_fine(status);

    if (status == f_invalid_parameter) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_list_read() for the file '%s'.", filename);
    }
    else if (status == f_no_data_on_eos || status == f_no_data || status == f_no_data_on_stop) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: No relevant data was found within the file '%s'.", filename);
    }
    else if (f_macro_test_for_allocation_errors(status)) {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory.");
    }
    else {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_basic_list_read() for the file '%s'.", f_error_set_error(status), filename);
    }

    return status;
  }

  return status;
}

f_return_status firewall_process_rules(f_string_location *input, firewall_local_data *local, firewall_data *data) {
  f_status status = f_none;
  f_status status2 = f_none;

  status = fll_fss_extended_read(&local->buffer, input, &local->rule_objects, &local->rule_contents);

  if (f_error_is_not_error(status)) {
    status = firewall_perform_commands(*local, *data);

    if (f_error_is_error(status)) {
      status = f_error_set_fine(status);

      if (f_macro_test_for_allocation_errors(status)) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory.");
      }
      else if (status == f_failure) {
        // the error message has already been displayed.
      }
      else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands().", f_error_set_error(status));
      }

      f_delete_fss_objects(status2, local->rule_objects);
      f_delete_fss_contents(status2, local->rule_contents);
      return status;
    }
  }

  f_delete_fss_objects(status2, local->rule_objects);
  f_delete_fss_contents(status2, local->rule_contents);
  return status;
}

f_return_status firewall_delete_local_data(firewall_local_data *local) {
  f_status status = f_none;

  local->is_global = f_true;
  local->is_main = f_false;
  local->is_stop = f_false;
  local->is_lock = f_false;

  local->file_position.buffer_start = 0;
  local->file_position.file_start = 0;
  local->file_position.total_elements = 0;

  local->device = 0;
  local->chain = 0;

  f_delete_dynamic_string(status, local->buffer);
  f_delete_array_lengths(status, local->chain_ids);
  f_delete_fss_objects(status, local->chain_objects);
  f_delete_fss_contents(status, local->chain_contents);
  f_delete_fss_objects(status, local->rule_objects);
  f_delete_fss_contents(status, local->rule_contents);

  return f_none;
}

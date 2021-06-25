#include "firewall.h"
#include "private-common.h"
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

f_status_t firewall_perform_commands(const firewall_local_data_t local, const firewall_main_t main) {
  f_status_t status = F_none;

  f_array_length_t i = 0;
  f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
  f_string_dynamic_t argument = f_string_dynamic_t_initialize;

  int return_code = 0;
  f_array_length_t length = 0;
  bool invalid = F_false;
  bool is_ip_list = F_false;
  f_string_dynamic_t ip_list = f_string_dynamic_t_initialize;

  // iptables command arguments
  bool device_all = F_false;
  bool ip_list_direction = F_false; // false = source, true = destination
  bool use_protocol = F_false;
  uint8_t tool = firewall_program_ip46tables;
  uint8_t chain = firewall_chain_none_id;

  f_array_length_t repeat = 2;
  f_array_length_t r = 0;

  f_string_t current_tool = firewall_tool_iptables;
  f_array_length_t current_tool_length = firewall_tool_iptables_length;

  f_array_length_t direction = firewall_direction_none_id;
  f_string_dynamic_t device = f_string_dynamic_t_initialize;
  f_array_length_t action = firewall_action_append_id;
  f_string_dynamic_t protocol = f_string_dynamic_t_initialize;

  if (local.is_global) {
    device_all = F_true;
  }
  else {
    if (main.devices.array[local.device].used > 0) {
       macro_f_string_dynamic_t_resize(status, device, main.devices.array[local.device].used);

      if (F_status_is_error(status)) {
        macro_f_string_dynamic_t_delete_simple(device);

        return status;
      }

      macro_firewall_concat_string(device.string, main.devices.array[local.device].string, main.devices.array[local.device].used);
      device.used = main.devices.array[local.device].used;
    }
  }

  // for custom chains, the chain command may not be specified.
  if (!(local.is_main || local.is_stop || local.is_lock)) {
    chain = firewall_chain_custom_id;
  }

  for (; i < local.rule_objects.used; ++i) {
    length  = macro_firewall_structure_size(local.rule_objects, i);
    invalid = F_false;

    is_ip_list = F_false;
    ip_list_direction = F_false;

    macro_f_string_dynamic_t_delete_simple(ip_list);

    // process chain rule
    if (length >= firewall_chain_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_chain, length, firewall_chain_length) == F_equal_to) {
      if (chain == firewall_chain_custom_id) {
        // custom chains can only apply to themselves, so silently ignore chain commands specified within a custom chain.
        fprintf(f_type_warning, "%sAt line %llu, the chain option is meaningle ss inside of a custom chain.", fll_error_print_warning, i);
        continue;
      }

      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_chain_input_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_input, length, firewall_chain_input_length) == F_equal_to) {
        chain = firewall_chain_input_id;
      }
      else if (length >= firewall_chain_output_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_output, length, firewall_chain_output_length) == F_equal_to) {
        chain = firewall_chain_output_id;
      }
      else if (length >= firewall_chain_forward_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_forward, length, firewall_chain_forward_length) == F_equal_to) {
        chain = firewall_chain_forward_id;
      }
      else if (length >= firewall_chain_postrouting_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_postrouting, length, firewall_chain_postrouting_length) == F_equal_to) {
        chain = firewall_chain_postrouting_id;
      }
      else if (length >= firewall_chain_prerouting_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_prerouting, length, firewall_chain_prerouting_length) == F_equal_to) {
        chain = firewall_chain_prerouting_id;
      }
      else if (length >= firewall_chain_none_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_none, length, firewall_chain_none_length) == F_equal_to) {
        chain = firewall_chain_none_id;
      }
      else {
        invalid = F_true;
      }

      if (!invalid) continue;
    }
    // process direction rule
    else if (length >= firewall_direction_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_direction, length, firewall_direction_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_direction_input_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_direction_input, length, firewall_direction_input_length) == F_equal_to) {
        direction = firewall_direction_input_id;
      }
      else if (length >= firewall_direction_output_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_direction_output, length, firewall_direction_output_length) == F_equal_to) {
        direction = firewall_direction_output_id;
      }
      else if (length >= firewall_direction_none_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_direction_none, length, firewall_direction_none_length) == F_equal_to) {
        direction = firewall_direction_none_id;
      }
      else {
        // direction must be specified, and no custom directions are allowed.
        invalid = F_true;
      }

      if (!invalid) continue;
    }
    // process device rule.
    else if (length >= firewall_device_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_device, length, firewall_device_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_device_all_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_device_all, length, firewall_device_all_length) == F_equal_to) {
        macro_f_string_dynamic_t_delete_simple(device);
        device_all = F_true;
        continue;
      }
      else if (length >= firewall_device_this_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_device_this, length, firewall_device_this_length) == F_equal_to) {
        if (main.devices.array[local.device].used > 0) {
          if (main.devices.array[local.device].used > device.size) {
            macro_f_string_dynamic_t_resize(status, device, main.devices.array[local.device].used);

            if (F_status_is_error(status)) break;
          }

          macro_firewall_concat_string(device.string, main.devices.array[local.device].string, main.devices.array[local.device].used);

          device.used = main.devices.array[local.device].used;
        }
        else {
          macro_f_string_dynamic_t_delete_simple(device);
        }

        device_all = F_false;
        continue;
      }

      if (!invalid) {
        if (length > 0) {
          if (length > device.size) {
            macro_f_string_dynamic_t_resize(status, device, length);

            if (F_status_is_error(status)) break;
          }

          macro_firewall_concat_string(device.string, local.buffer.string + local.rule_contents.array[i].array[0].start, length);
          device.used = length;
        }
        else {
          macro_f_string_dynamic_t_delete_simple(device);
        }

        device_all = F_false;
        continue;
      }
    }
    // process action rule.
    else if (length >= firewall_action_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_action, length, firewall_action_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_action_append_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_append, length, firewall_action_append_length) == F_equal_to) {
        action = firewall_action_append_id;
      }
      else if (length >= firewall_action_insert_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_insert, length, firewall_action_insert_length) == F_equal_to) {
        action = firewall_action_insert_id;
      }
      else if (length >= firewall_action_policy_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_policy, length, firewall_action_policy_length) == F_equal_to) {
        action = firewall_action_policy_id;
      }
      else if (length >= firewall_action_none_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_none, length, firewall_action_none_length) == F_equal_to) {
        action = firewall_action_none_id;
      }
      else {
        invalid = F_true;
      }

      if (!invalid) continue;
    }
    // process ip_list rule.
    else if (length >= firewall_ip_list_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_ip_list, length, firewall_ip_list_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);
      is_ip_list = F_true;

      if (length >= firewall_ip_list_source_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_ip_list_source, length, firewall_ip_list_source_length) == F_equal_to) {
        ip_list_direction = F_false;
      }
      else if (length >= firewall_ip_list_destination_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_ip_list_destination, length, firewall_ip_list_destination_length) == F_equal_to) {
        ip_list_direction = F_true;
      }
      else {
        invalid = F_true;
      }
    }
    else if (length >= firewall_protocol_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_protocol, length, firewall_protocol_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else {
        if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_protocol_none, length, firewall_protocol_none_length) == F_equal_to) {
          use_protocol = F_false;
        }
        else if (length > 0) {
          macro_f_string_dynamic_t_delete_simple(protocol);
           macro_f_string_dynamic_t_resize(status, protocol, length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(protocol.string, local.buffer.string + local.rule_contents.array[i].array[0].start, length);
          protocol.used = length;
          use_protocol = F_true;
        }
        else {
          use_protocol = F_false;
        }

        continue;
      }
    }
    // process tool rule.
    else if (length >= firewall_tool_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_tool, length, firewall_tool_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else {
        if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_tool_iptables, length, firewall_tool_iptables_length) == F_equal_to) {
          tool = firewall_program_iptables;
          current_tool = firewall_tool_iptables;
          current_tool_length = firewall_tool_iptables_length;
          repeat = 1;
        }
        else if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_tool_ip6tables, length, firewall_tool_ip6tables_length) == F_equal_to) {
          tool = firewall_program_ip6tables;
          current_tool = firewall_tool_ip6tables;
          current_tool_length = firewall_tool_ip6tables_length;
          repeat = 1;
        }
        else if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_tool_ip46tables, length, firewall_tool_ip46tables_length) == F_equal_to) {
          tool = firewall_program_ip46tables;
          current_tool = firewall_tool_iptables;
          current_tool_length = firewall_tool_iptables_length;
          repeat = 2;
        }
        else {
          invalid = F_true;
        }

        if (!invalid) continue;
      }
    }
    // process rule rule, if the remaining rule does not match as firewall_rule, then it is an invalid rule.
    else if (length < firewall_rule_length || fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_rule, length, firewall_rule_length) == F_equal_to_not) {
      if (length > 0) {
        f_color_print_code(f_type_warning, main.context.warning);
        fprintf(f_type_warning, "%sAt line %llu, the object '", fll_error_print_warning, i);
        f_print(f_type_warning, local.buffer.string + local.rule_objects.array[i].start, length);
        fprintf(f_type_warning, "' is invalid");
        f_color_print_code(f_type_warning, main.context.reset);
      }
      else {
        fprintf(f_type_warning, "%sAt line %llu, the object is missing", fll_error_print_warning, i);
      }

      fprintf(f_type_warning, "\n");
      continue;
    }

    if (invalid) {
      length = macro_firewall_structure_size(local.rule_objects, i);

      if (length > 0) {
        f_color_print_code(f_type_warning, main.context.warning);
        fprintf(f_type_warning, "%sAt line %llu, the object '", fll_error_print_warning, i);
        f_print(f_type_warning, local.buffer.string + local.rule_objects.array[i].start, length);
        fprintf(f_type_warning, "' has invalid content '");
        f_print(f_type_warning, local.buffer.string + local.rule_contents.array[i].array[0].start, macro_firewall_structure_size(local.rule_contents.array[i], 0));
        fprintf(f_type_warning, "'");
        f_color_print_code(f_type_warning, main.context.reset);
        fprintf(f_type_warning, "\n");
      }
      else {
        f_color_print(f_type_warning, main.context.set.warning, "%sAt line %llu, the object has no content%c", fll_error_print_warning, i, f_string_eol_s[0]);
      }

      continue;
    }

    for (r = repeat; r > 0; --r) {

      // first add the program name
      f_string_dynamics_resize(0, &arguments);

      status = f_string_dynamics_increase(f_memory_default_allocation_small, &arguments);
      if (F_status_is_error(status)) break;

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

      macro_f_string_dynamic_t_delete_simple(argument);

      if (F_status_is_error(status)) break;

      // process the action when a non-none chain is specified.
      if (chain != firewall_chain_none_id && action != firewall_action_none_id) {
        if (action == firewall_action_append_id) {
           macro_f_string_dynamic_t_resize(status, argument, firewall_action_append_command_length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, firewall_action_append_command, firewall_action_append_command_length);
          argument.used = firewall_action_append_command_length;
        }
        else if (action == firewall_action_insert_id) {
           macro_f_string_dynamic_t_resize(status, argument, firewall_action_insert_command_length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, firewall_action_insert_command, firewall_action_insert_command_length);
          argument.used = firewall_action_insert_command_length;
        }
        else if (action == firewall_action_policy_id) {
           macro_f_string_dynamic_t_resize(status, argument, firewall_action_policy_command_length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, firewall_action_policy_command, firewall_action_policy_command_length);
          argument.used = firewall_action_policy_command_length;
        }

        if (argument.used > 0) {
          macro_firewall_append_argument_to_arguments(status, arguments, argument)
          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(argument);
            break;
          }

          // process the chain, which is required by the action.
          if (chain == firewall_chain_custom_id) {
            if (main.chains.array[local.chain_ids.array[local.chain]].used > 0) {
               macro_f_string_dynamic_t_resize(status, argument, main.chains.array[local.chain_ids.array[local.chain]].used);

              if (F_status_is_error(status)) break;

              macro_firewall_concat_string(argument.string, main.chains.array[local.chain_ids.array[local.chain]].string, main.chains.array[local.chain_ids.array[local.chain]].used);
              argument.used = main.chains.array[local.chain_ids.array[local.chain]].used;
            }
          }
          else if (chain == firewall_chain_forward_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_forward_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_forward, firewall_chain_forward_length);
            argument.used = firewall_chain_forward_length;
          }
          else if (chain == firewall_chain_postrouting_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_postrouting_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_postrouting, firewall_chain_postrouting_length);
            argument.used += firewall_chain_postrouting_length;
          }
          else if (chain == firewall_chain_prerouting_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_prerouting_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_prerouting, firewall_chain_prerouting_length);
            argument.used = firewall_chain_prerouting_length;
          }
          else if (chain == firewall_chain_input_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_input_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_input, firewall_chain_input_length);
            argument.used = firewall_chain_input_length;
          }
          else if (chain == firewall_chain_output_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_output_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_output, firewall_chain_output_length);
            argument.used = firewall_chain_output_length;
          }

          if (argument.used > 0) {
            macro_firewall_append_argument_to_arguments(status, arguments, argument)
            if (F_status_is_error(status)) {
              break;
            }
          }
        }
      }

      // add the device if and only if a non-none direction is specified.
      if (device.used > 0 && (direction == firewall_direction_input_id || direction == firewall_direction_output_id)) {
        if (length < firewall_device_all_length || fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_device_all, length, firewall_device_all_length) == F_equal_to_not) {
          if (direction == firewall_direction_input_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_device_input_command_length);
            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_device_input_command, firewall_device_input_command_length);
            argument.used = firewall_device_input_command_length;
          }
          else if (direction == firewall_direction_output_id) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_device_output_command_length);
            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_device_output_command, firewall_device_output_command_length);
            argument.used = firewall_device_output_command_length;
          }

          if (argument.used > 0) {
            macro_firewall_append_argument_to_arguments(status, arguments, argument)
            if (F_status_is_error(status)) {
              break;
            }
          }
        }

        // add the device.
        if (device.used > 0) {
           macro_f_string_dynamic_t_resize(status, argument, device.used);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, device.string, device.used);
          argument.used = device.used;

          macro_firewall_append_argument_to_arguments(status, arguments, argument)
          if (F_status_is_error(status)) {
            break;
          }
        }
      }

      if (use_protocol) {
         macro_f_string_dynamic_t_resize(status, argument, firewall_protocol_command_length);

        if (F_status_is_error(status)) break;

        macro_firewall_concat_string(argument.string, firewall_protocol_command, firewall_protocol_command_length);
        argument.used = firewall_protocol_command_length;

        macro_firewall_append_argument_to_arguments(status, arguments, argument)
        if (F_status_is_error(status)) {
          break;
        }

        if (protocol.used > 0) {
           macro_f_string_dynamic_t_resize(status, argument, protocol.used);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, protocol.string, protocol.used);
          argument.used = protocol.used;

          macro_firewall_append_argument_to_arguments(status, arguments, argument)
          if (F_status_is_error(status)) {
            break;
          }
        }
      }

      // last up is the "rule"
      if ((!is_ip_list && local.rule_contents.array[i].used > 0) || (is_ip_list && local.rule_contents.array[i].used > 1)) {
        f_array_length_t subcounter = 0;

        if (is_ip_list) {

          // skip past the chain
          ++subcounter;

          length = macro_firewall_structure_size(local.rule_contents.array[i], subcounter);

          if (length > 0) {
             macro_f_string_dynamic_t_resize(status, ip_list, length);

            if (F_status_is_error(status)) {
              // prevent the loop below from being processed.
              subcounter = local.rule_contents.array[i].used;
            }
            else {
              macro_firewall_concat_string(ip_list.string, local.buffer.string + local.rule_contents.array[i].array[subcounter].start, length);
              ip_list.used = length;

              ++subcounter;
            }
          }
        }

        for (; subcounter < local.rule_contents.array[i].used; ++subcounter) {

          length = macro_firewall_structure_size(local.rule_contents.array[i], subcounter);

          if (length > 0) {
             macro_f_string_dynamic_t_resize(status, argument, length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, local.buffer.string + local.rule_contents.array[i].array[subcounter].start, length);
            argument.used = length;

            macro_firewall_append_argument_to_arguments(status, arguments, argument)
            if (F_status_is_error(status)) {
              break;
            }
          }
        } // for
      }
      else {
        length = macro_firewall_structure_size(local.rule_objects, i);

        f_color_print_code(f_type_warning, main.context.warning);
        fprintf(f_type_warning, "%sAt line %llu, the object '", fll_error_print_warning, i);
        f_print(f_type_warning, local.buffer.string + local.rule_objects.array[i].start, length);
        fprintf(f_type_warning, "' has no content");
        f_color_print_code(f_type_warning, main.context.reset);
        fprintf(f_type_warning, "\n");

        break;
      }

      // now execute the generated commands.
      if (arguments.used > 1) {
        if (is_ip_list) {
          f_file_t file = f_file_t_initialize;
          f_string_dynamic_t file_path = f_string_dynamic_t_initialize;
          f_string_dynamic_t local_buffer = f_string_dynamic_t_initialize;

          f_fss_objects_t basic_objects = f_fss_objects_t_initialize;
          f_fss_contents_t basic_contents = f_fss_objects_t_initialize;

           macro_f_string_dynamic_t_resize(status, file_path, network_path_length + ip_list.used + firewall_default_allocation_step);

          if (status == F_none) {
            macro_firewall_concat_string(file_path.string, network_path, network_path_length);
            macro_firewall_concat_string(file_path.string + network_path_length, ip_list.string, ip_list.used);
            file_path.used = file_path.size;
            file_path.string[file_path.used] = 0;

            status = f_file_open(file_path.string, 0, &file);
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_parameter) {
              f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling f_file_open()%c", fll_error_print_error, f_string_eol_s[0]);
            }
            else if (status == F_file_found_not) {
              // the file does not have to exist
              f_color_print(f_type_warning, main.context.set.warning, "%sCannot find the file '%.*s'%c", fll_error_print_warning, file_path.used, file_path.string, f_string_eol_s[0]);
              status = F_none;
            }
            else if (status == F_file_open) {
              f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to open the file '%.*s'%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
            }
            else if (status == F_file_descriptor) {
              f_color_print(main.error.to.stream, main.context.set.error, "%sFile descriptor error while trying to open the file '%.*s'%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
            }
            else if (status == F_memory_not) {
              f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
            }
            else {
              f_color_print(main.error.to.stream, main.context.set.error, "%sAn unhandled error (%u) has occurred while calling f_file_open()%c", fll_error_print_error, status, f_string_eol_s[0]);
            }

            if (status != F_file_found_not) {
              status = F_status_set_error(status);
            }

            f_file_stream_close(F_true, &file);
          }
          else {
            status = f_file_read(file, &local_buffer);

            f_file_stream_close(F_true, &file);

            if (F_status_is_error(status)) {
              status = F_status_set_fine(status);

              if (status == F_parameter) {
                f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling f_file_read()%c", fll_error_print_error, f_string_eol_s[0]);
              }
              else if (status == F_number_overflow) {
                f_color_print(main.error.to.stream, main.context.set.error, "%sInteger overflow while trying to buffer the file '%.*s'%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
              }
              else if (status == F_file_closed) {
                f_color_print(main.error.to.stream, main.context.set.error, "%sThe file '%.*s' is no longer open%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
              }
              else if (status == F_file_seek) {
                f_color_print(main.error.to.stream, main.context.set.error, "%sA seek error occurred while accessing the file '%.*s'%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
              }
              else if (status == F_file_read) {
                f_color_print(main.error.to.stream, main.context.set.error, "%sA read error occurred while accessing the file '%.*s'%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
              }
              else if (status == F_memory_not) {
                f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
              }
              else {
                f_color_print(main.error.to.stream, main.context.set.error, "%sAn unhandled error (%u) has occurred while calling f_file_read()%c", fll_error_print_error, status, f_string_eol_s[0]);
              }

              status = F_status_set_error(status);
            }
            else {
              f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

              {
                f_state_t state = f_state_t_initialize;
                f_string_range_t input = macro_f_string_range_t_initialize(local_buffer.used);

                status = fll_fss_basic_read(local_buffer, state, &input, &basic_objects, &basic_contents, 0, &delimits, 0);
              }

              if (F_status_set_error(status)) {
                status = F_status_set_fine(status);

                if (status == F_parameter) {
                  f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling fll_fss_basic_read() for the file '%.*s'%c", fll_error_print_error, file_path.used, file_path.string, f_string_eol_s[0]);
                }
                else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
                  // empty files are to be silently ignored
                }
                else if (status == F_memory_not) {
                  f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
                }
                else {
                  f_color_print(main.error.to.stream, main.context.set.error, "%sAn unhandled error (%u) has occurred while calling fll_fss_basic_read() for the file '%.*s'%c", fll_error_print_error, status, file_path.used, file_path.string, f_string_eol_s[0]);
                }

                status = F_status_set_error(status);
              }

              if (F_status_is_error_not(status)) {
                status = fl_fss_apply_delimit(delimits, &local_buffer);

                if (F_status_is_error(status)) {
                  fll_error_print(main.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
                }
              }

              if (F_status_is_error_not(status)) {
                f_array_length_t buffer_counter = 0;
                f_array_length_t ip_length = 0;
                f_string_dynamic_t ip_list_action = f_string_dynamic_t_initialize;

                if (ip_list_direction) {
                  macro_f_string_dynamic_t_resize(status, ip_list_action, firewall_ip_list_destination_action_length);

                  if (F_status_is_error(status)) break;

                  macro_firewall_concat_string(ip_list_action.string, firewall_ip_list_destination_action, firewall_ip_list_destination_action_length);
                  ip_list_action.used = firewall_ip_list_destination_action_length;
                }
                else {
                  macro_f_string_dynamic_t_resize(status, ip_list_action, firewall_ip_list_source_action_length);

                  if (F_status_is_error(status)) break;

                  macro_firewall_concat_string(ip_list_action.string, firewall_ip_list_source_action, firewall_ip_list_source_action_length);
                  ip_list_action.used = firewall_ip_list_source_action_length;
                }

                status = F_none;
                if (arguments.used + 2 > arguments.size) {
                  macro_f_string_dynamics_t_resize(status, arguments, arguments.size + 2);
                }

                if (F_status_is_error(status)) {
                  f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);

                  macro_f_string_dynamic_t_delete_simple(ip_list_action);
                }
                else {
                  f_string_dynamic_t ip_argument = f_string_dynamic_t_initialize;

                  macro_firewall_append_argument_to_arguments(status, arguments, ip_list_action)
                  if (F_status_is_error(status)) {
                    macro_f_string_dynamic_t_delete_simple(ip_argument);
                    break;
                  }

                  // the ip_list file contains objects and no content, all objects are what matter an nothing else
                  for (; buffer_counter < basic_objects.used; ++buffer_counter) {

                    ip_length = macro_firewall_structure_size(basic_objects, buffer_counter);

                     macro_f_string_dynamic_t_resize(status, ip_argument, ip_length);

                    if (F_status_is_error(status)) {
                      f_color_print(main.error.to.stream, main.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
                      break;
                    }

                    macro_firewall_concat_string(ip_argument.string, local_buffer.string + basic_objects.array[buffer_counter].start, ip_length);
                    ip_argument.used = ip_length;

                    macro_firewall_append_argument_to_arguments(status, arguments, ip_argument)
                    if (F_status_is_error(status)) break;

                    if (main.error.verbosity == f_console_verbosity_debug) {
                      f_color_print_code(f_type_debug, main.context.warning);
                      fprintf(f_type_debug, "%s ", current_tool);

                      for (f_array_length_t i = 0; i < arguments.used; ++i) {
                        fprintf(f_type_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
                      } // for

                      f_color_print_code(f_type_debug, main.context.reset);
                      fprintf(f_type_debug, "\n");
                    }

                    status = fll_execute_program((f_string_t) current_tool, arguments, 0, 0, (void *) &return_code);

                    // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
                    if (status == F_child) {
                      exit(return_code);
                    }

                    if (status == F_failure) {
                      f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, current_tool, f_string_eol_s[0]);
                      fprintf(f_type_error, "  ");

                      f_color_print_code(f_type_error, main.context.error);

                      fprintf(f_type_error, "%s ", current_tool);
                      for (f_array_length_t i = 0; i < arguments.used; ++i) {
                        fprintf(f_type_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
                      } // for

                      f_color_print_code(f_type_error, main.context.reset);
                      fprintf(f_type_error, "\n");

                      // remove ip_argument from arguments string.
                      macro_f_string_dynamic_t_delete_simple(arguments.array[arguments.used--]);

                      break;
                    }
                    else if (status == F_parameter) {
                      f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling fll_execute_program()%c", fll_error_print_error, f_string_eol_s[0]);

                      // remove ip_argument from arguments string.
                      macro_f_string_dynamic_t_delete_simple(arguments.array[arguments.used--]);

                      break;
                    }

                    // remove ip_argument from arguments string.
                    macro_f_string_dynamic_t_delete_simple(arguments.array[arguments.used--]);
                  } // for

                  macro_f_string_dynamic_t_delete_simple(ip_argument);

                  // remove ip_list_action from arguments string.
                  macro_f_string_dynamic_t_delete_simple(arguments.array[arguments.used--]);
                }
              }

              macro_f_fss_delimits_t_delete_simple(delimits);
            }
          }

          macro_f_string_dynamic_t_delete_simple(local_buffer);
          macro_f_string_dynamic_t_delete_simple(file_path);
          macro_f_fss_objects_t_delete_simple(basic_objects);
          macro_f_fss_contents_t_delete_simple(basic_contents);

          if (status == F_failure || status == F_parameter) break;
        }
        else {
          if (main.error.verbosity == f_console_verbosity_debug) {
            f_color_print_code(f_type_debug, main.context.warning);
            fprintf(f_type_debug, "%s ", current_tool);

            for (f_array_length_t i = 0; i < arguments.used; ++i) {
              fprintf(f_type_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            f_color_print_code(f_type_debug, main.context.reset);
            fprintf(f_type_debug, "\n");
          }

          status = fll_execute_program(current_tool, arguments, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }

          if (status == F_failure) {
            f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, current_tool, f_string_eol_s[0]);
            fprintf(f_type_error, "  ");
            f_color_print_code(f_type_error, main.context.error);

            fprintf(f_type_error, "%s ", current_tool);
            for (f_array_length_t i = 0; i < arguments.used; ++i) {
              fprintf(f_type_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            f_color_print_code(f_type_error, main.context.reset);
            fprintf(f_type_error, "\n");

            break;
          }
          else if (status == F_parameter) {
            f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling fll_execute_program()%c", fll_error_print_error, f_string_eol_s[0]);
            break;
          }
        }
      }
    } // for
  } // for

  macro_f_string_dynamic_t_delete_simple(ip_list);
  macro_f_string_dynamic_t_delete_simple(argument);
  macro_f_string_dynamics_t_delete_simple(arguments);
  macro_f_string_dynamic_t_delete_simple(device);
  macro_f_string_dynamic_t_delete_simple(protocol);

  return status;
}

f_status_t firewall_create_custom_chains(firewall_reserved_chains_t *reserved, firewall_local_data_t *local, firewall_main_t *main) {
  f_status_t status = F_none;

  uint8_t tool = firewall_program_iptables;
  bool new_chain = F_false;
  bool create_chain = F_false;
  int return_code = 0;

  f_array_length_t i = 0;
  f_array_length_t j = 0;

  f_array_length_t length = 0;
  f_string_range_t range = f_string_range_t_initialize;
  f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

  f_string_dynamic_t fixed_string = f_string_dynamic_t_initialize;

  macro_f_array_lengths_t_delete_simple(local->chain_ids);
  macro_f_array_lengths_t_resize(status, local->chain_ids, local->chain_objects.used);

  if (F_status_is_error(status)) {
    return status;
  }

  status = f_string_dynamics_resize(2, &arguments);
  if (F_status_is_error(status)) return status;

  status = f_string_dynamic_resize(firewall_chain_create_command_length, &arguments.array[0]);

  if (F_status_is_error(status)) {
    macro_f_string_dynamics_t_delete_simple(arguments);

    return status;
  }

  macro_firewall_concat_string(arguments.array[0].string, firewall_chain_create_command, firewall_chain_create_command_length);

  arguments.array[0].used = firewall_chain_create_command_length;

  status = f_string_dynamic_increase(f_memory_default_allocation_small, &arguments.array[1]);

  if (F_status_is_error(status)) {
    arguments.used = 1;
    macro_f_string_dynamics_t_delete_simple(arguments);

    return status;
  }

  arguments.used = 2;

  reserved->has_lock = F_false;
  reserved->has_stop = F_false;
  reserved->has_main = F_false;

  while (i < local->chain_objects.used) {
    new_chain = F_true;
    j = 0;

    // skip globally reserved chain name: main
    range.start = 0;
    range.stop = firewall_group_main_length - 1;
    fixed_string.string = firewall_group_main;
    fixed_string.used = firewall_group_main_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
      reserved->has_main = F_true;
      reserved->main_at = i;
    }

    // skip globally reserved chain name: stop
    range.start = 0;
    range.stop = firewall_group_stop_length - 1;
    fixed_string.string = firewall_group_stop;
    fixed_string.used = firewall_group_stop_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
      reserved->has_stop = F_true;
      reserved->stop_at = i;
    }

    // skip globally reserved chain name: lock
    range.start = 0;
    range.stop = firewall_group_lock_length - 1;
    fixed_string.string = firewall_group_lock;
    fixed_string.used = firewall_group_lock_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
      reserved->has_lock = F_true;
      reserved->lock_at = i;
    }

    // skip globally reserved chain name: none
    range.start = 0;
    range.stop = firewall_group_lock_length - 1;
    fixed_string.string = firewall_chain_none;
    fixed_string.used = firewall_chain_none_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
    }

    macro_f_string_dynamic_t_clear(fixed_string);

    if (new_chain) {
      while (j < main->chains.used) {
        range.start = 0;
        range.stop = main->chains.array[j].used - 1;

        if (fl_string_dynamic_partial_compare(local->buffer, main->chains.array[j], local->chain_objects.array[i], range) == F_equal_to) {
          new_chain = F_false;
          local->chain_ids.array[i] = j;

          break;
        }

        ++j;
      } // while
    }

    if (new_chain) {
      if (main->chains.used == main->chains.size) {
        macro_f_string_dynamics_t_resize(status, main->chains, main->chains.used + firewall_default_allocation_step);

        if (F_status_is_error(status)) {
          macro_f_string_dynamics_t_delete_simple(arguments);

          return status;
        }
      }

      create_chain = F_true;
      length = macro_firewall_structure_size(local->chain_objects, i);

      arguments.array[1].used = 0;
      if (length > arguments.array[1].size) {
        macro_f_string_dynamic_t_resize(status, arguments.array[1], length);

        if (F_status_is_error(status)) {
          macro_f_string_dynamics_t_delete_simple(arguments);

          return status;
        }
      }

       macro_f_string_dynamic_t_resize(status, main->chains.array[main->chains.used], length);

      if (F_status_is_error(status)) {
        macro_f_string_dynamics_t_delete_simple(arguments);

        return status;
      }

      main->chains.array[main->chains.used].used = 0;
      local->chain_ids.array[i] = main->chains.used;
      arguments.array[1].used = 0;
      j = local->chain_objects.array[i].start;

      // copy the string character by character, ignoring placeholders.
      while (j <= local->chain_objects.array[i].stop) {

        if (local->buffer.string[j] == f_fss_delimit_placeholder) {
          ++j;
          continue;
        }

        main->chains.array[main->chains.used].string[main->chains.array[main->chains.used].used++] = local->buffer.string[j];
        arguments.array[1].string[arguments.array[1].used++] = local->buffer.string[j];
        ++j;
      } // while

      if (fl_string_compare(arguments.array[1].string, firewall_chain_forward, arguments.array[1].used, firewall_chain_forward_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_input, arguments.array[1].used, firewall_chain_input_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_output, arguments.array[1].used, firewall_chain_output_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_postrouting, arguments.array[1].used, firewall_chain_postrouting_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_prerouting, arguments.array[1].used, firewall_chain_prerouting_length) == F_equal_to) {
        create_chain = F_false;
      }

      if (create_chain) {
        if (main->error.verbosity == f_console_verbosity_debug) {
          f_color_print_code(f_type_debug, main->context.warning);
          fprintf(f_type_debug, "%s ", firewall_tool_iptables);

          for (f_array_length_t i = 0; i < arguments.used; ++i) {
            fprintf(f_type_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
          } // for

          f_color_print_code(f_type_debug, main->context.reset);
          fprintf(f_type_debug, "\n");
        }

        tool = firewall_program_iptables;
        status = fll_execute_program((f_string_t) firewall_tool_iptables, arguments, 0, 0, (void *) &return_code);

        // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
        if (status == F_child) {
          exit(return_code);
        }

        if (F_status_is_error_not(status)) {
          if (main->error.verbosity == f_console_verbosity_debug) {
            f_color_print_code(f_type_debug, main->context.warning);
            fprintf(f_type_debug, "%s ", firewall_tool_ip6tables);

            for (f_array_length_t i = 0; i < arguments.used; ++i) {
              fprintf(f_type_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            f_color_print_code(f_type_debug, main->context.reset);
            fprintf(f_type_debug, "\n");
          }

          tool = firewall_program_ip6tables;
          status = fll_execute_program((f_string_t) firewall_tool_ip6tables, arguments, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            exit(return_code);
          }
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_failure) {
            if (tool == firewall_program_iptables) {
              f_color_print(main->error.to.stream, main->context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, firewall_tool_iptables, f_string_eol_s[0]);
            }
            else if (tool == firewall_program_ip6tables) {
              f_color_print(main->error.to.stream, main->context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, firewall_tool_ip6tables, f_string_eol_s[0]);
            }

            fprintf(f_type_error, "  ");
            f_color_print_code(f_type_error, main->context.error);

            if (tool == firewall_program_iptables) {
              fprintf(f_type_error, "%s ", firewall_tool_iptables);
            }
            else if (tool == firewall_program_ip6tables) {
              fprintf(f_type_error, "%s ", firewall_tool_ip6tables);
            }

            for (f_array_length_t i = 0; i < arguments.used; ++i) {
              fprintf(f_type_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
            } // for

            f_color_print_code(f_type_error, main->context.reset);
            fprintf(f_type_error, "\n");
          }
          else if (status == F_parameter) {
            f_color_print(main->error.to.stream, main->context.set.error, "%sInvalid parameter when calling fll_execute_program()%c", fll_error_print_error, f_string_eol_s[0]);
          }
          else {
            f_color_print(main->error.to.stream, main->context.set.error, "%sAn unhandled error (%u) has occurred while calling fll_execute_program()%c", fll_error_print_error, status, f_string_eol_s[0]);
          }

          macro_f_string_dynamics_t_delete_simple(arguments);
          return status;
        }
      }

      ++main->chains.used;
    }

    ++i;
  } // while

  macro_f_string_dynamics_t_delete_simple(arguments);

  return status;
}

f_status_t firewall_delete_chains(const firewall_main_t main) {
  const f_string_t tools[2] = { firewall_tool_iptables, firewall_tool_ip6tables };
  f_status_t status = F_none;

  for (f_array_length_t i = 0; i < 2; ++i) {
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_dynamic_t argument[1] = f_string_dynamic_t_initialize;
    int return_code = 0;

    argument[0].string = (f_string_t) "-F";
    argument[0].size = 2;
    argument[0].used = 2;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    if (main.error.verbosity == f_console_verbosity_debug) {
      f_color_print_code(f_type_debug, main.context.warning);
      fprintf(f_type_debug, "%s ", tools[i]);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {
        fprintf(f_type_debug, "%.*s ", arguments.array[i].used, arguments.array[i].string);
      } // for

      f_color_print_code(f_type_debug, main.context.reset);
      fprintf(f_type_debug, "\n");
    }

    status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

    // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
    if (status == F_child) {
      exit(return_code);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_failure) {
        f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, tools[i], f_string_eol_s[0]);

        fprintf(f_type_error, "  ");
        f_color_print_code(f_type_error, main.context.error);

        fprintf(f_type_error, "%s ", tools[i]);
        for (f_array_length_t i = 0; i < arguments.used; ++i) {
          fprintf(f_type_error, "%.*s ", arguments.array[i].used, arguments.array[i].string);
        } // for

        f_color_print_code(f_type_error, main.context.reset);
        fprintf(f_type_error, "\n");
      }
      else if (status == F_parameter) {
        f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling fll_execute_program()%c", fll_error_print_error, f_string_eol_s[0]);
      }
      else {
        f_color_print(main.error.to.stream, main.context.set.error, "%sAn unhandled error (%u) has occurred while calling fll_execute_program()%c", fll_error_print_error, status, f_string_eol_s[0]);
      }

      return status;
    }
  } // for

  for (f_array_length_t i = 0; i < 2; ++i) {
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_dynamic_t argument[1] = f_string_dynamic_t_initialize;
    int return_code = 0;

    argument[0].string = (f_string_t) firewall_chain_delete_command;
    argument[0].size = firewall_chain_delete_command_length;
    argument[0].used = firewall_chain_delete_command_length;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    if (main.error.verbosity == f_console_verbosity_debug) {
      f_color_print_code(f_type_debug, main.context.warning);
      fprintf(f_type_debug, "%s ", tools[i]);

      for (f_array_length_t j = 0; j < arguments.used; ++j) {
        fprintf(f_type_debug, "%.*s ", arguments.array[j].used, arguments.array[j].string);
      } // for

      f_color_print_code(f_type_debug, main.context.reset);
      fprintf(f_type_debug, "\n");
    }

    status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

    // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
    if (status == F_child) {
      exit(return_code);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_failure) {
        f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, tools[i], f_string_eol_s[0]);

        fprintf(f_type_error, "  ");
        f_color_print_code(f_type_error, main.context.error);

        fprintf(f_type_error, "%s ", tools[i]);
        for (f_array_length_t j = 0; j < arguments.used; ++j) {
          fprintf(f_type_error, "%.*s ", arguments.array[j].used, arguments.array[j].string);
        } // for

        f_color_print_code(f_type_error, main.context.reset);
        fprintf(f_type_error, "\n");
      }
      else if (status == F_parameter) {
        f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling fll_execute_program()%c", fll_error_print_error, f_string_eol_s[0]);
      }
      else {
        f_color_print(main.error.to.stream, main.context.set.error, "%sAn unhandled error (%u) has occurred while calling fll_execute_program()%c", fll_error_print_error, status, f_string_eol_s[0]);
      }

      return status;
    }
  } // for

  return status;
}

f_status_t firewall_default_lock(const firewall_main_t main) {
  const f_string_t chains[3] = { firewall_chain_input, firewall_chain_output, firewall_chain_forward };
  const f_string_t tools[2] = { firewall_tool_iptables, firewall_tool_ip6tables };

  const f_array_length_t lengths[3] = { firewall_chain_input_length, firewall_chain_output_length, firewall_chain_forward_length };

  f_status_t status = F_none;

  for (f_array_length_t i = 0; i < 3; ++i) {
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_dynamic_t argument[3];

    arguments.array = argument;
    arguments.used = 3;
    arguments.size = arguments.used;

    arguments.array[0].string = (f_string_t) firewall_action_policy_command;
    arguments.array[1].string = (f_string_t) chains[i];
    arguments.array[2].string = (f_string_t) "DROP";

    arguments.array[0].used = firewall_action_append_command_length;
    arguments.array[1].used = lengths[i];
    arguments.array[2].used = 4;

    arguments.array[0].size = arguments.array[0].used;
    arguments.array[1].size = arguments.array[1].used;
    arguments.array[2].size = arguments.array[2].used;

    for (f_array_length_t j = 0; j < 2; ++j) {
      int return_code = 0;

      // print command when debugging.
      if (main.error.verbosity == f_console_verbosity_debug) {
        f_color_print_code(f_type_debug, main.context.warning);
        fprintf(f_type_debug, "%s ", tools[j]);

        for (f_array_length_t k = 0; k < arguments.used; k++) {
          fprintf(f_type_debug, "%.*s ", arguments.array[k].used, arguments.array[k].string);
        } // for

        f_color_print_code(f_type_debug, main.context.reset);
        fprintf(f_type_debug, "\n");
      }

      status = fll_execute_program(tools[j], arguments, 0, 0, (void *) &return_code);

      // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
      if (status == F_child) {
        exit(return_code);
      }

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_failure) {
          f_color_print(main.error.to.stream, main.context.set.error, "%sFailed to perform requested %s operation:%c", fll_error_print_error, tools[j], f_string_eol_s[0]);

          fprintf(f_type_error, "  ");
          f_color_print_code(f_type_error, main.context.error);

          fprintf(f_type_error, "%s ", tools[j]);
          for (f_array_length_t k = 0; k < arguments.used; k++) {
            fprintf(f_type_error, "%.*s ", arguments.array[k].used, arguments.array[k].string);
          } // for

          f_color_print_code(f_type_error, main.context.reset);
          fprintf(f_type_error, "\n");
        }
        else if (status == F_parameter) {
          f_color_print(main.error.to.stream, main.context.set.error, "%sInvalid parameter when calling fll_execute_program()%c", fll_error_print_error, f_string_eol_s[0]);
        }
        else {
          f_color_print(main.error.to.stream, main.context.set.error, "%sAn unhandled error (%u) has occurred while calling fll_execute_program()%c", fll_error_print_error, status, f_string_eol_s[0]);
        }

        return status;
      }
    } // for
  } // for

  return status;
}

f_status_t firewall_buffer_rules(const f_string_t filename, const bool optional, firewall_local_data_t *local, firewall_main_t *main) {
  f_file_t file = f_file_t_initialize;

  f_status_t status = f_file_open(filename, 0, &file);

  if (F_status_is_error(status)) {
    status = F_status_set_fine(status);

    if (optional) {
      if (status == F_parameter) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sInvalid parameter when calling f_file_open().%c", fll_error_print_error, f_string_eol_s[0]);
      }
      else if (status != F_file_found_not && status != F_file_open && status != F_file_descriptor) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sAn unhandled error (%u) has occurred while calling f_file_open().%c", fll_error_print_error, status, f_string_eol_s[0]);
      }
    } else {
      if (status == F_parameter) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sInvalid parameter when calling f_file_open().%c", fll_error_print_error, f_string_eol_s[0]);
      }
      else if (status == F_file_found_not) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sUnable to find the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
      }
      else if (status == F_file_open) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sUnable to open the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
      }
      else if (status == F_file_descriptor) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sFile descriptor error while trying to open the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
      }
      else {
        f_color_print(main->error.to.stream, main->context.set.error, "%sAn unhandled error (%u) has occurred while calling f_file_open().%c", fll_error_print_error, status, f_string_eol_s[0]);
      }
    }

    return status;
  }

  status = f_file_read(file, &local->buffer);

  f_file_stream_close(F_true, &file);

  if (F_status_is_error(status)) {
    status = F_status_set_fine(status);

    if (status == F_parameter) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sInvalid parameter when calling f_file_read().%c", fll_error_print_error, f_string_eol_s[0]);
    }
    else if (status == F_number_overflow) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sInteger overflow while trying to buffer the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
    }
    else if (status == F_file_closed) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sThe file '%s' is no longer open.%c", fll_error_print_error, filename, f_string_eol_s[0]);
    }
    else if (status == F_file_seek) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sA seek error occurred while accessing the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
    }
    else if (status == F_file_read) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sA read error occurred while accessing the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
    }
    else if (status == F_memory_not) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
    }
    else {
      f_color_print(main->error.to.stream, main->context.set.error, "%sAn unhandled error (%u) has occurred while calling f_file_read().%c", fll_error_print_error, status, f_string_eol_s[0]);
    }

    return status;
  }

  f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
  f_fss_comments_t comments = f_fss_comments_t_initialize;

  {
    f_state_t state = f_state_t_initialize;
    f_string_range_t input = macro_f_string_range_t_initialize(local->buffer.used);

    status = fll_fss_basic_list_read(local->buffer, state, &input, &local->chain_objects, &local->chain_contents, &delimits, 0, &comments);
  }

  if (F_status_is_error(status)) {
    status = F_status_set_fine(status);

    if (status == F_parameter) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sInvalid parameter when calling fll_fss_basic_list_read() for the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
    }
    else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sNo relevant main was found within the file '%s'.%c", fll_error_print_error, filename, f_string_eol_s[0]);
    }
    else if (status == F_memory_not) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
    }
    else {
      f_color_print(main->error.to.stream, main->context.set.error, "%sAn unhandled error (%u) has occurred while calling fll_fss_basic_list_read() for the file '%s'.%c", fll_error_print_error, status, filename, f_string_eol_s[0]);
    }
  }
  else {
    status = fl_fss_apply_delimit(delimits, &local->buffer);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
    }
  }

  macro_f_fss_delimits_t_delete_simple(delimits);
  macro_f_fss_comments_t_delete_simple(comments);

  return status;
}

f_status_t firewall_process_rules(f_string_range_t *range, firewall_local_data_t *local, firewall_main_t *main) {

  f_status_t status = F_none;
  f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

  {
    f_state_t state = f_state_t_initialize;

    status = fll_fss_extended_read(local->buffer, state, range, &local->rule_objects, &local->rule_contents, 0, 0, &delimits, 0);
  }

  if (F_status_is_error_not(status)) {
    status = fl_fss_apply_delimit(delimits, &local->buffer);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
    }
  }

  macro_f_fss_delimits_t_delete_simple(delimits);

  if (F_status_is_error_not(status)) {
    status = firewall_perform_commands(*local, *main);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_memory_not) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
      }
      else if (status == F_failure) {
        // the error message has already been displayed.
      }
      else {
        f_color_print(main->error.to.stream, main->context.set.error, "%sAn unhandled error (%u) has occurred while calling firewall_perform_commands().%c", fll_error_print_error, status, f_string_eol_s[0]);
      }

      macro_f_fss_objects_t_delete_simple(local->rule_objects);
      macro_f_fss_contents_t_delete_simple(local->rule_contents);
      return status;
    }
  }

  macro_f_fss_objects_t_delete_simple(local->rule_objects);
  macro_f_fss_contents_t_delete_simple(local->rule_contents);
  return status;
}

f_status_t firewall_delete_local_data(firewall_local_data_t *local) {
  f_status_t status = F_none;

  local->is_global = F_true;
  local->is_main = F_false;
  local->is_stop = F_false;
  local->is_lock = F_false;

  local->device = 0;
  local->chain = 0;

  macro_f_string_dynamic_t_delete_simple(local->buffer);
  macro_f_array_lengths_t_delete_simple(local->chain_ids);
  macro_f_fss_objects_t_delete_simple(local->chain_objects);
  macro_f_fss_contents_t_delete_simple(local->chain_contents);
  macro_f_fss_objects_t_delete_simple(local->rule_objects);
  macro_f_fss_contents_t_delete_simple(local->rule_contents);

  return F_none;
}

#ifdef __cplusplus
} // extern "C"
#endif

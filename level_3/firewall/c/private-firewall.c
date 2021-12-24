#include "firewall.h"
#include "private-common.h"
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

f_status_t firewall_perform_commands(firewall_main_t * const main, const firewall_local_data_t local) {

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
  uint8_t tool = firewall_program_ip46tables_e;
  uint8_t chain = firewall_chain_none_id_e;

  f_array_length_t repeat = 2;
  f_array_length_t r = 0;

  f_string_t current_tool = firewall_tool_iptables_s;
  f_array_length_t current_tool_length = firewall_tool_iptables_s_length;

  f_array_length_t direction = firewall_direction_none_id_e;
  f_string_dynamic_t device = f_string_dynamic_t_initialize;
  f_array_length_t action = firewall_action_append_id_e;
  f_string_dynamic_t protocol = f_string_dynamic_t_initialize;

  if (local.is_global) {
    device_all = F_true;
  }
  else {
    if (main->devices.array[local.device].used > 0) {
       macro_f_string_dynamic_t_resize(status, device, main->devices.array[local.device].used);

      if (F_status_is_error(status)) {
        macro_f_string_dynamic_t_delete_simple(device);

        return status;
      }

      macro_firewall_concat_string(device.string, main->devices.array[local.device].string, main->devices.array[local.device].used);
      device.used = main->devices.array[local.device].used;
    }
  }

  // for custom chains, the chain command may not be specified.
  if (!(local.is_main || local.is_stop || local.is_lock)) {
    chain = firewall_chain_custom_id_e;
  }

  for (uint16_t signal_check = 0; i < local.rule_objects.used; ++i) {

    if (!((++signal_check) % firewall_signal_check_d)) {
      if (firewall_signal_received(main)) {
        macro_f_string_dynamic_t_delete_simple(ip_list);
        macro_f_string_dynamic_t_delete_simple(argument);
        macro_f_string_dynamics_t_delete_simple(arguments);
        macro_f_string_dynamic_t_delete_simple(device);
        macro_f_string_dynamic_t_delete_simple(protocol);

        return F_status_set_error(F_interrupt);
      }

      signal_check = 0;
    }

    length  = macro_firewall_structure_size(local.rule_objects, i);
    invalid = F_false;

    is_ip_list = F_false;
    ip_list_direction = F_false;

    macro_f_string_dynamic_t_delete_simple(ip_list);

    // process chain rule
    if (length >= firewall_chain_length_s && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_chain_s, length, firewall_chain_length_s) == F_equal_to) {
      if (chain == firewall_chain_custom_id_e) {

        // custom chains can only apply to themselves, so silently ignore chain commands specified within a custom chain.
        fll_print_format("%c%[%sAt line %ul, the chain option is meaningless inside of a custom chain.%]%c", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, i, main->warning.context, f_string_eol_s[0]);
        continue;
      }

      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_chain_input_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_input_s, length, firewall_chain_input_s_length) == F_equal_to) {
        chain = firewall_chain_input_id_e;
      }
      else if (length >= firewall_chain_output_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_output_s, length, firewall_chain_output_s_length) == F_equal_to) {
        chain = firewall_chain_output_id_e;
      }
      else if (length >= firewall_chain_forward_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_forward_s, length, firewall_chain_forward_s_length) == F_equal_to) {
        chain = firewall_chain_forward_id_e;
      }
      else if (length >= firewall_chain_postrouting_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_postrouting_s, length, firewall_chain_postrouting_s_length) == F_equal_to) {
        chain = firewall_chain_postrouting_id_e;
      }
      else if (length >= firewall_chain_prerouting_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_prerouting_s, length, firewall_chain_prerouting_s_length) == F_equal_to) {
        chain = firewall_chain_prerouting_id_e;
      }
      else if (length >= firewall_chain_none_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_chain_none_s, length, firewall_chain_none_s_length) == F_equal_to) {
        chain = firewall_chain_none_id_e;
      }
      else {
        invalid = F_true;
      }

      if (!invalid) continue;
    }
    // process direction rule
    else if (length >= firewall_direction_s_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_direction_s, length, firewall_direction_s_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_direction_input_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_direction_input_s, length, firewall_direction_input_s_length) == F_equal_to) {
        direction = firewall_direction_input_id_e;
      }
      else if (length >= firewall_direction_output_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_direction_output_s, length, firewall_direction_output_s_length) == F_equal_to) {
        direction = firewall_direction_output_id_e;
      }
      else if (length >= firewall_direction_none_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_direction_none_s, length, firewall_direction_none_s_length) == F_equal_to) {
        direction = firewall_direction_none_id_e;
      }
      else {
        // direction must be specified, and no custom directions are allowed.
        invalid = F_true;
      }

      if (!invalid) continue;
    }
    // process device rule.
    else if (length >= firewall_device_s_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_device_s, length, firewall_device_s_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_device_all_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_device_all_s, length, firewall_device_all_s_length) == F_equal_to) {
        macro_f_string_dynamic_t_delete_simple(device);
        device_all = F_true;
        continue;
      }
      else if (length >= firewall_device_this_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_device_this_s, length, firewall_device_this_s_length) == F_equal_to) {
        if (main->devices.array[local.device].used > 0) {
          if (main->devices.array[local.device].used > device.size) {
            macro_f_string_dynamic_t_resize(status, device, main->devices.array[local.device].used);

            if (F_status_is_error(status)) break;
          }

          macro_firewall_concat_string(device.string, main->devices.array[local.device].string, main->devices.array[local.device].used);

          device.used = main->devices.array[local.device].used;
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
    else if (length >= firewall_action_length_s && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_action_s, length, firewall_action_length_s) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else if (length >= firewall_action_append_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_append_s, length, firewall_action_append_s_length) == F_equal_to) {
        action = firewall_action_append_id_e;
      }
      else if (length >= firewall_action_insert_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_insert_s, length, firewall_action_insert_s_length) == F_equal_to) {
        action = firewall_action_insert_id_e;
      }
      else if (length >= firewall_action_policy_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_policy_s, length, firewall_action_policy_s_length) == F_equal_to) {
        action = firewall_action_policy_id_e;
      }
      else if (length >= firewall_action_none_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_action_none_s, length, firewall_action_none_s_length) == F_equal_to) {
        action = firewall_action_none_id_e;
      }
      else {
        invalid = F_true;
      }

      if (!invalid) continue;
    }
    // process ip_list rule.
    else if (length >= firewall_ip_list_length_s && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_ip_list, length, firewall_ip_list_length_s) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);
      is_ip_list = F_true;

      if (length >= firewall_ip_list_source_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_ip_list_source_s, length, firewall_ip_list_source_s_length) == F_equal_to) {
        ip_list_direction = F_false;
      }
      else if (length >= firewall_ip_list_destination_s_length && fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_ip_list_destination_s, length, firewall_ip_list_destination_s_length) == F_equal_to) {
        ip_list_direction = F_true;
      }
      else {
        invalid = F_true;
      }
    }
    else if (length >= firewall_protocol_s_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_protocol_s, length, firewall_protocol_s_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else {
        if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_protocol_none_s, length, firewall_protocol_none_s_length) == F_equal_to) {
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
    else if (length >= firewall_tool_s_length && fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_tool_s, length, firewall_tool_s_length) == F_equal_to) {
      length = macro_firewall_structure_size(local.rule_contents.array[i], 0);

      if (macro_firewall_rule_contents_has_incorrect_items(i, 1)) {
        invalid = F_true;
      }
      else {
        if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_tool_iptables_s, length, firewall_tool_iptables_s_length) == F_equal_to) {
          tool = firewall_program_iptables_e;
          current_tool = firewall_tool_iptables_s;
          current_tool_length = firewall_tool_iptables_s_length;
          repeat = 1;
        }
        else if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_tool_ip6tables_s, length, firewall_tool_ip6tables_s_length) == F_equal_to) {
          tool = firewall_program_ip6tables_e;
          current_tool = firewall_tool_ip6tables_s;
          current_tool_length = firewall_tool_ip6tables_s_length;
          repeat = 1;
        }
        else if (fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_tool_ip46tables_s, length, firewall_tool_ip46tables_s_length) == F_equal_to) {
          tool = firewall_program_ip46tables_e;
          current_tool = firewall_tool_iptables_s;
          current_tool_length = firewall_tool_iptables_s_length;
          repeat = 2;
        }
        else {
          invalid = F_true;
        }

        if (!invalid) continue;
      }
    }
    // process rule rule, if the remaining rule does not match as firewall_rule_s, then it is an invalid rule.
    else if (length < firewall_rule_s_length || fl_string_compare(local.buffer.string + local.rule_objects.array[i].start, (f_string_t) firewall_rule_s, length, firewall_rule_s_length) == F_equal_to_not) {
      if (length) {
        flockfile(main->warning.to.stream);

        fl_print_format("%c%[%sAt line %ul, the object '%]%[", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, i, main->warning.context, main->warning.notable);
        f_print(local.buffer.string + local.rule_objects.array[i].start, length, main->warning.to.stream);
        fl_print_format("%]%[' is invalid.%]%c", main->warning.to.stream, main->warning.notable, main->warning.context, main->warning.context, f_string_eol_s[0]);

        funlockfile(main->warning.to.stream);
      }
      else {
        fll_print_format("%c%[%sAt line %ul, the object is missing.%]%c", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, i, main->warning.context, f_string_eol_s[0]);
      }

      continue;
    }

    if (invalid) {
      length = macro_firewall_structure_size(local.rule_objects, i);

      if (length) {
        flockfile(main->warning.to.stream);

        fl_print_format("%c%[%sAt line %ul, the object '%]%[", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, i, main->warning.context, main->warning.notable);
        f_print(local.buffer.string + local.rule_objects.array[i].start, length, main->warning.to.stream);
        fl_print_format("%]%[' has invalid content '%]%[", main->warning.to.stream, main->warning.notable, main->warning.context, main->warning.context, main->warning.notable);
        f_print(local.buffer.string + local.rule_contents.array[i].array[0].start, macro_firewall_structure_size(local.rule_contents.array[i], 0), main->warning.to.stream);
        fl_print_format("%]%['.%]%c", main->warning.to.stream, main->warning.notable, main->warning.context, main->warning.context, f_string_eol_s[0]);

        funlockfile(main->warning.to.stream);
      }
      else {
        fll_print_format("%c%[%sAt line %ul, the object has no content.%]%c", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, i, main->warning.context, f_string_eol_s[0]);
      }

      continue;
    }

    for (r = repeat; r > 0; --r) {

      // first add the program name
      f_string_dynamics_resize(0, &arguments);

      status = f_string_dynamics_increase(F_memory_default_allocation_small_d, &arguments);
      if (F_status_is_error(status)) break;

      if (tool == firewall_program_ip46tables_e) {
        if (r == 2) {
          current_tool = firewall_tool_iptables_s;
          current_tool_length = firewall_tool_iptables_s_length;
        }
        else {
          current_tool = firewall_tool_ip6tables_s;
          current_tool_length = firewall_tool_ip6tables_s_length;
        }
      }

      macro_f_string_dynamic_t_delete_simple(argument);

      if (F_status_is_error(status)) break;

      // process the action when a non-none chain is specified.
      if (chain != firewall_chain_none_id_e && action != firewall_action_none_id_e) {
        if (action == firewall_action_append_id_e) {
           macro_f_string_dynamic_t_resize(status, argument, firewall_action_append_command_s_length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, firewall_action_append_command_s, firewall_action_append_command_s_length);
          argument.used = firewall_action_append_command_s_length;
        }
        else if (action == firewall_action_insert_id_e) {
           macro_f_string_dynamic_t_resize(status, argument, firewall_action_insert_command_s_length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, firewall_action_insert_command_s, firewall_action_insert_command_s_length);
          argument.used = firewall_action_insert_command_s_length;
        }
        else if (action == firewall_action_policy_id_e) {
           macro_f_string_dynamic_t_resize(status, argument, firewall_action_policy_command_s_length);

          if (F_status_is_error(status)) break;

          macro_firewall_concat_string(argument.string, firewall_action_policy_command_s, firewall_action_policy_command_s_length);
          argument.used = firewall_action_policy_command_s_length;
        }

        if (argument.used > 0) {
          macro_firewall_append_argument_to_arguments(status, arguments, argument)
          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(argument);
            break;
          }

          // process the chain, which is required by the action.
          if (chain == firewall_chain_custom_id_e) {
            if (main->chains.array[local.chain_ids.array[local.chain]].used > 0) {
               macro_f_string_dynamic_t_resize(status, argument, main->chains.array[local.chain_ids.array[local.chain]].used);

              if (F_status_is_error(status)) break;

              macro_firewall_concat_string(argument.string, main->chains.array[local.chain_ids.array[local.chain]].string, main->chains.array[local.chain_ids.array[local.chain]].used);
              argument.used = main->chains.array[local.chain_ids.array[local.chain]].used;
            }
          }
          else if (chain == firewall_chain_forward_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_forward_s_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_forward_s, firewall_chain_forward_s_length);
            argument.used = firewall_chain_forward_s_length;
          }
          else if (chain == firewall_chain_postrouting_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_postrouting_s_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_postrouting_s, firewall_chain_postrouting_s_length);
            argument.used += firewall_chain_postrouting_s_length;
          }
          else if (chain == firewall_chain_prerouting_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_prerouting_s_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_prerouting_s, firewall_chain_prerouting_s_length);
            argument.used = firewall_chain_prerouting_s_length;
          }
          else if (chain == firewall_chain_input_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_input_s_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_input_s, firewall_chain_input_s_length);
            argument.used = firewall_chain_input_s_length;
          }
          else if (chain == firewall_chain_output_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_chain_output_s_length);

            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_chain_output_s, firewall_chain_output_s_length);
            argument.used = firewall_chain_output_s_length;
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
      if (device.used > 0 && (direction == firewall_direction_input_id_e || direction == firewall_direction_output_id_e)) {
        if (length < firewall_device_all_s_length || fl_string_compare(local.buffer.string + local.rule_contents.array[i].array[0].start, (f_string_t) firewall_device_all_s, length, firewall_device_all_s_length) == F_equal_to_not) {
          if (direction == firewall_direction_input_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_device_input_command_length_s);
            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_device_input_command_s, firewall_device_input_command_length_s);
            argument.used = firewall_device_input_command_length_s;
          }
          else if (direction == firewall_direction_output_id_e) {
             macro_f_string_dynamic_t_resize(status, argument, firewall_device_output_command_length_s);
            if (F_status_is_error(status)) break;

            macro_firewall_concat_string(argument.string, firewall_device_output_command_s, firewall_device_output_command_length_s);
            argument.used = firewall_device_output_command_length_s;
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
         macro_f_string_dynamic_t_resize(status, argument, firewall_protocol_command_s_length);

        if (F_status_is_error(status)) break;

        macro_firewall_concat_string(argument.string, firewall_protocol_command_s, firewall_protocol_command_s_length);
        argument.used = firewall_protocol_command_s_length;

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

        flockfile(main->warning.to.stream);

        fl_print_format("%c%[%sAt line %ul, the object '%]%[", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, i, main->warning.context, main->warning.notable);
        f_print(local.buffer.string + local.rule_objects.array[i].start, length, main->warning.to.stream);
        fl_print_format("%]%[' has no content.%]%c", main->warning.to.stream, main->warning.notable, main->warning.context, main->warning.context, f_string_eol_s[0]);

        funlockfile(main->warning.to.stream);

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

           macro_f_string_dynamic_t_resize(status, file_path, network_path_s_length + ip_list.used + firewall_default_allocation_step_d);

          if (status == F_none) {
            macro_firewall_concat_string(file_path.string, network_path_s, network_path_s_length);
            macro_firewall_concat_string(file_path.string + network_path_s_length, ip_list.string, ip_list.used);
            file_path.used = file_path.size;
            file_path.string[file_path.used] = 0;

            status = f_file_open(file_path.string, 0, &file);
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_parameter) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                firewall_print_error_on_invalid_parameter(main->error, "f_file_open");
              }
            }
            else if (status == F_file_found_not) {

              // the file does not have to exist
              if (main->error.verbosity != f_console_verbosity_verbose_e || main->error.verbosity == f_console_verbosity_debug_e) {
                fll_print_format("%c%[%sCannot find the file '%Q'.%]%c", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, file_path, main->warning.context, f_string_eol_s[0]);
              }

              status = F_none;
            }
            else if (status == F_file_open) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%c%[%sUnable to open the file '%Q'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, file_path, main->error.context, f_string_eol_s[0]);
              }
            }
            else if (status == F_file_descriptor) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%c%[%sFile descriptor error while trying to open the file '%Q'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, file_path, main->error.context, f_string_eol_s[0]);
              }
            }
            else if (status == F_memory_not) {
              firewall_print_error_on_allocation_failure(main->error);
            }
            else {
              firewall_print_error_on_unhandled(main->error, "f_file_open", status);
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

              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                if (status == F_parameter) {
                  firewall_print_error_on_invalid_parameter(main->error, "f_file_read");
                }
                else if (status == F_number_overflow) {
                  fll_print_format("%c%[%sInteger overflow while trying to buffer the file '%Q'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, file_path, main->error.context, f_string_eol_s[0]);
                }
                else if (status == F_file_closed) {
                  fll_print_format("%c%[%sThe file '%Q' is no longer open.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, file_path, main->error.context, f_string_eol_s[0]);
                }
                else if (status == F_file_seek) {
                  fll_print_format("%c%[%sA seek error occurred while accessing the file '%Q'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, file_path, main->error.context, f_string_eol_s[0]);
                }
                else if (status == F_file_read) {
                  fll_print_format("%c%[%sA read error occurred while accessing the file '%Q'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, file_path, main->error.context, f_string_eol_s[0]);
                }
                else if (status == F_memory_not) {
                  firewall_print_error_on_allocation_failure(main->error);
                }
                else {
                  firewall_print_error_on_unhandled(main->error, "f_file_read", status);
                }
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
                  firewall_print_error_on_invalid_parameter_for_file(main->error, "fll_fss_basic_read", file_path.used ? file_path.string : "");
                }
                else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
                  // empty files are to be silently ignored
                }
                else if (status == F_memory_not) {
                  firewall_print_error_on_allocation_failure(main->error);
                }
                else {
                  firewall_print_error_on_unhandled_for_file(main->error, "fll_fss_basic_read", status, file_path.used ? file_path.string : "");
                }

                status = F_status_set_error(status);
              }

              if (F_status_is_error_not(status)) {
                status = fl_fss_apply_delimit(delimits, &local_buffer);

                if (F_status_is_error(status)) {
                  fll_error_print(main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
                }
              }

              if (F_status_is_error_not(status)) {
                f_array_length_t buffer_counter = 0;
                f_array_length_t ip_length = 0;
                f_string_dynamic_t ip_list_action = f_string_dynamic_t_initialize;

                if (ip_list_direction) {
                  macro_f_string_dynamic_t_resize(status, ip_list_action, firewall_ip_list_destination_action_s_length);

                  if (F_status_is_error(status)) break;

                  macro_firewall_concat_string(ip_list_action.string, firewall_ip_list_destination_action_s, firewall_ip_list_destination_action_s_length);
                  ip_list_action.used = firewall_ip_list_destination_action_s_length;
                }
                else {
                  macro_f_string_dynamic_t_resize(status, ip_list_action, firewall_ip_list_source_action_s_length);

                  if (F_status_is_error(status)) break;

                  macro_firewall_concat_string(ip_list_action.string, firewall_ip_list_source_action_s, firewall_ip_list_source_action_s_length);
                  ip_list_action.used = firewall_ip_list_source_action_s_length;
                }

                status = F_none;
                if (arguments.used + 2 > arguments.size) {
                  macro_f_string_dynamics_t_resize(status, arguments, arguments.size + 2);
                }

                if (F_status_is_error(status)) {
                  firewall_print_error_on_allocation_failure(main->error);

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
                      firewall_print_error_on_allocation_failure(main->error);

                      break;
                    }

                    macro_firewall_concat_string(ip_argument.string, local_buffer.string + basic_objects.array[buffer_counter].start, ip_length);
                    ip_argument.used = ip_length;

                    macro_firewall_append_argument_to_arguments(status, arguments, ip_argument)
                    if (F_status_is_error(status)) break;

                    firewall_print_debug_tool(main->warning, current_tool, arguments);

                    status = fll_execute_program((f_string_t) current_tool, arguments, 0, 0, (void *) &return_code);

                    // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
                    if (status == F_child) {
                      macro_f_string_dynamic_t_delete_simple(ip_list);
                      macro_f_string_dynamic_t_delete_simple(argument);
                      macro_f_string_dynamics_t_delete_simple(arguments);
                      macro_f_string_dynamic_t_delete_simple(device);
                      macro_f_string_dynamic_t_delete_simple(protocol);

                      exit(return_code);
                    }

                    if (F_status_is_error(status)) {
                      if (F_status_set_fine(status) == F_failure) {
                        firewall_print_error_on_operation(main->error, current_tool, arguments);
                      }
                      else if (F_status_set_fine(status) == F_parameter) {
                        firewall_print_error_on_invalid_parameter(main->error, "fll_execute_program");
                      }
                      else {
                        firewall_print_error_on_unhandled(main->error, "fll_execute_program", status);
                      }

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

          if (F_status_set_fine(status) == F_failure || F_status_set_fine(status) == F_parameter) break;
        }
        else {
          firewall_print_debug_tool(main->warning, current_tool, arguments);

          status = fll_execute_program(current_tool, arguments, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            macro_f_string_dynamic_t_delete_simple(ip_list);
            macro_f_string_dynamic_t_delete_simple(argument);
            macro_f_string_dynamics_t_delete_simple(arguments);
            macro_f_string_dynamic_t_delete_simple(device);
            macro_f_string_dynamic_t_delete_simple(protocol);

            exit(return_code);
          }

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_failure) {
              firewall_print_error_on_operation(main->error, current_tool, arguments);
            }
            else if (F_status_set_fine(status) == F_parameter) {
              firewall_print_error_on_invalid_parameter(main->error, "fll_execute_program");
            }
            else {
              firewall_print_error_on_unhandled(main->error, "fll_execute_program", status);
            }

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

f_status_t firewall_create_custom_chains(firewall_main_t * const main, firewall_reserved_chains_t *reserved, firewall_local_data_t *local) {

  f_status_t status = F_none;

  uint8_t tool = firewall_program_iptables_e;
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

  status = f_string_dynamic_resize(firewall_chain_create_command_s_length + 1, &arguments.array[0]);

  if (F_status_is_error(status)) {
    macro_f_string_dynamics_t_delete_simple(arguments);

    return status;
  }

  macro_firewall_concat_string(arguments.array[0].string, firewall_chain_create_command_s, firewall_chain_create_command_s_length);

  arguments.array[0].used = firewall_chain_create_command_s_length;
  arguments.array[0].string[firewall_chain_create_command_s_length] = 0;

  status = f_string_dynamic_increase(F_memory_default_allocation_small_d, &arguments.array[1]);

  if (F_status_is_error(status)) {
    arguments.used = 1;
    macro_f_string_dynamics_t_delete_simple(arguments);

    return status;
  }

  arguments.used = 2;

  reserved->has_lock = F_false;
  reserved->has_stop = F_false;
  reserved->has_main = F_false;

  for (uint16_t signal_check = 0; i < local->chain_objects.used; ) {

    new_chain = F_true;
    j = 0;

    if (!((++signal_check) % firewall_signal_check_d)) {
      if (firewall_signal_received(main)) {
        macro_f_string_dynamics_t_delete_simple(arguments);

        return F_status_set_error(F_interrupt);
      }
    }

    // skip globally reserved chain name: main
    range.start = 0;
    range.stop = firewall_group_main_s_length - 1;
    fixed_string.string = firewall_group_main_s;
    fixed_string.used = firewall_group_main_s_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
      reserved->has_main = F_true;
      reserved->main_at = i;
    }

    // skip globally reserved chain name: stop
    range.start = 0;
    range.stop = firewall_group_stop_s_length - 1;
    fixed_string.string = firewall_group_stop_s;
    fixed_string.used = firewall_group_stop_s_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
      reserved->has_stop = F_true;
      reserved->stop_at = i;
    }

    // skip globally reserved chain name: lock
    range.start = 0;
    range.stop = firewall_group_lock_s_length - 1;
    fixed_string.string = firewall_group_lock_s;
    fixed_string.used = firewall_group_lock_s_length;
    if (fl_string_dynamic_partial_compare(local->buffer, fixed_string, local->chain_objects.array[i], range) == F_equal_to) {
      new_chain = F_false;
      reserved->has_lock = F_true;
      reserved->lock_at = i;
    }

    // skip globally reserved chain name: none
    range.start = 0;
    range.stop = firewall_group_lock_s_length - 1;
    fixed_string.string = firewall_chain_none_s;
    fixed_string.used = firewall_chain_none_s_length;
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
        macro_f_string_dynamics_t_resize(status, main->chains, main->chains.used + firewall_default_allocation_step_d);

        if (F_status_is_error(status)) {
          macro_f_string_dynamics_t_delete_simple(arguments);

          return status;
        }
      }

      create_chain = F_true;
      length = macro_firewall_structure_size(local->chain_objects, i);

      arguments.array[1].used = 0;
      if (length > arguments.array[1].size) {
        macro_f_string_dynamic_t_resize(status, arguments.array[1], length + 1);

        if (F_status_is_error(status)) {
          macro_f_string_dynamics_t_delete_simple(arguments);

          return status;
        }
      }

       macro_f_string_dynamic_t_resize(status, main->chains.array[main->chains.used], length + 1);

      if (F_status_is_error(status)) {
        macro_f_string_dynamics_t_delete_simple(arguments);

        return status;
      }

      main->chains.array[main->chains.used].used = 0;
      local->chain_ids.array[i] = main->chains.used;
      j = local->chain_objects.array[i].start;

      // copy the string character by character, ignoring placeholders.
      while (j <= local->chain_objects.array[i].stop) {

        if (local->buffer.string[j] == F_fss_delimit_placeholder_s) {
          ++j;
          continue;
        }

        main->chains.array[main->chains.used].string[main->chains.array[main->chains.used].used++] = local->buffer.string[j];
        arguments.array[1].string[arguments.array[1].used++] = local->buffer.string[j];
        ++j;
      } // while

      arguments.array[1].string[arguments.array[1].used] = 0;
      main->chains.array[main->chains.used].string[main->chains.array[main->chains.used].used] = 0;

      if (fl_string_compare(arguments.array[1].string, firewall_chain_forward_s, arguments.array[1].used, firewall_chain_forward_s_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_input_s, arguments.array[1].used, firewall_chain_input_s_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_output_s, arguments.array[1].used, firewall_chain_output_s_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_postrouting_s, arguments.array[1].used, firewall_chain_postrouting_s_length) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_compare(arguments.array[1].string, firewall_chain_prerouting_s, arguments.array[1].used, firewall_chain_prerouting_s_length) == F_equal_to) {
        create_chain = F_false;
      }

      if (create_chain) {
        firewall_print_debug_tool(main->warning, firewall_tool_iptables_s, arguments);

        tool = firewall_program_iptables_e;
        status = fll_execute_program((f_string_t) firewall_tool_iptables_s, arguments, 0, 0, (void *) &return_code);

        // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
        if (status == F_child) {
          macro_f_string_dynamics_t_delete_simple(arguments);

          exit(return_code);
        }

        if (F_status_is_error_not(status)) {
          status = firewall_signal_received(main);

          if (status) {
            macro_f_string_dynamics_t_delete_simple(arguments);

            return F_status_set_error(F_interrupt);
          }

          firewall_print_debug_tool(main->warning, firewall_tool_ip6tables_s, arguments);

          tool = firewall_program_ip6tables_e;
          status = fll_execute_program((f_string_t) firewall_tool_ip6tables_s, arguments, 0, 0, (void *) &return_code);

          // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
          if (status == F_child) {
            macro_f_string_dynamics_t_delete_simple(arguments);

            exit(return_code);
          }
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_failure) {
            firewall_print_error_on_operation(main->error, tool == firewall_program_iptables_e ? firewall_tool_iptables_s : firewall_tool_ip6tables_s, arguments);
          }
          else if (status == F_parameter) {
            firewall_print_error_on_invalid_parameter(main->error, "fll_execute_program");
          }
          else {
            firewall_print_error_on_unhandled(main->error, "fll_execute_program", status);
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

f_status_t firewall_delete_chains(firewall_main_t * const main) {

  const f_string_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };
  f_status_t status = F_none;

  for (f_array_length_t i = 0; i < 2; ++i) {

    if (firewall_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_dynamic_t argument[1] = f_string_dynamic_t_initialize;
    int return_code = 0;

    argument[0].string = (f_string_t) "-F";
    argument[0].size = 2;
    argument[0].used = 2;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    firewall_print_debug_tool(main->warning, tools[i], arguments);

    status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

    // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
    if (status == F_child) {
      exit(return_code);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_failure) {
        firewall_print_error_on_operation(main->error, tools[i], arguments);
      }
      else if (status == F_parameter) {
        firewall_print_error_on_invalid_parameter(main->error, "fll_execute_program");
      }
      else {
        firewall_print_error_on_unhandled(main->error, "fll_execute_program", status);
      }

      return status;
    }
  } // for

  for (f_array_length_t i = 0; i < 2; ++i) {

    if (firewall_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_dynamic_t argument[1] = f_string_dynamic_t_initialize;
    int return_code = 0;

    argument[0].string = (f_string_t) firewall_chain_delete_command_s;
    argument[0].size = firewall_chain_delete_command_s_length;
    argument[0].used = firewall_chain_delete_command_s_length;

    arguments.array = argument;
    arguments.size = 1;
    arguments.used = 1;

    firewall_print_debug_tool(main->warning, tools[i], arguments);

    status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

    // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
    if (status == F_child) {
      exit(return_code);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_failure) {
        firewall_print_error_on_operation(main->error, tools[i], arguments);
      }
      else if (status == F_parameter) {
        firewall_print_error_on_invalid_parameter(main->error, "fll_execute_program");
      }
      else {
        firewall_print_error_on_unhandled(main->error, "fll_execute_program", status);
      }

      return status;
    }
  } // for

  return status;
}

f_status_t firewall_default_lock(firewall_main_t * const main) {

  const f_string_t chains[3] = { firewall_chain_input_s, firewall_chain_output_s, firewall_chain_forward_s };
  const f_string_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };

  const f_array_length_t lengths[3] = { firewall_chain_input_s_length, firewall_chain_output_s_length, firewall_chain_forward_s_length };

  f_status_t status = F_none;

  int return_code = 0;

  for (f_array_length_t i = 0; i < 3; ++i) {

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_string_dynamic_t argument[3];

    arguments.array = argument;
    arguments.used = 3;
    arguments.size = arguments.used;

    arguments.array[0].string = (f_string_t) firewall_action_policy_command_s;
    arguments.array[1].string = (f_string_t) chains[i];
    arguments.array[2].string = (f_string_t) "DROP";

    arguments.array[0].used = firewall_action_append_command_s_length;
    arguments.array[1].used = lengths[i];
    arguments.array[2].used = 4;

    arguments.array[0].size = arguments.array[0].used;
    arguments.array[1].size = arguments.array[1].used;
    arguments.array[2].size = arguments.array[2].used;

    for (f_array_length_t j = 0; j < 2; ++j) {

      firewall_print_debug_tool(main->warning, tools[j], arguments);

      return_code = 0;

      status = fll_execute_program(tools[j], arguments, 0, 0, (void *) &return_code);

      // immediately exit child process, @todo this may require additional memory deallocation and relating changes.
      if (status == F_child) {
        exit(return_code);
      }

      if (firewall_signal_received(main)) {
        return F_status_set_error(F_interrupt);
      }

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_failure) {
          firewall_print_error_on_operation(main->error, tools[j], arguments);
        }
        else if (status == F_parameter) {
          firewall_print_error_on_invalid_parameter(main->error, "fll_execute_program");
        }
        else {
          firewall_print_error_on_unhandled(main->error, "fll_execute_program", status);
        }

        return status;
      }
    } // for
  } // for

  return status;
}

f_status_t firewall_buffer_rules(firewall_main_t * const main, const f_string_t filename, const bool optional, firewall_local_data_t *local) {

  f_file_t file = f_file_t_initialize;

  f_status_t status = f_file_open(filename, 0, &file);

  if (F_status_is_error(status)) {
    status = F_status_set_fine(status);

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (optional) {
        if (status == F_parameter) {
          firewall_print_error_on_invalid_parameter(main->error, "f_file_open");
        }
        else if (status != F_file_found_not && status != F_file_open && status != F_file_descriptor) {
          firewall_print_error_on_unhandled(main->error, "f_file_open", status);
        }
      } else {
        if (status == F_parameter) {
          firewall_print_error_on_invalid_parameter(main->error, "f_file_open");
        }
        else if (status == F_file_found_not) {
          fll_print_format("%c%[%sUnable to find the file '%S'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
        }
        else if (status == F_file_open) {
          fll_print_format("%c%[%sUnable to open the file '%S'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
        }
        else if (status == F_file_descriptor) {
          fll_print_format("%c%[%sFile descriptor error while trying to open the file '%S'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
        }
        else {
          firewall_print_error_on_unhandled(main->error, "f_file_open", status);
        }
      }
    }

    return status;
  }

  status = f_file_read(file, &local->buffer);

  f_file_stream_close(F_true, &file);

  if (F_status_is_error(status)) {
    status = F_status_set_fine(status);

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (status == F_parameter) {
        firewall_print_error_on_invalid_parameter(main->error, "f_file_read");
      }
      else if (status == F_number_overflow) {
        fll_print_format("%c%[%sInteger overflow while trying to buffer the file '%S'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
      }
      else if (status == F_file_closed) {
        fll_print_format("%c%[%sThe file '%S' is no longer open.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
      }
      else if (status == F_file_seek) {
        fll_print_format("%c%[%sA seek error occurred while accessing the file '%S'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
      }
      else if (status == F_file_read) {
        fll_print_format("%c%[%sA read error occurred while accessing the file '%S'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
      }
      else if (status == F_memory_not) {
        firewall_print_error_on_allocation_failure(main->error);
      }
      else {
        firewall_print_error_on_unhandled(main->error, "f_file_read", status);
      }
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

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (status == F_parameter) {
        firewall_print_error_on_invalid_parameter_for_file(main->error, "fll_fss_basic_list_read", filename);
      }
      else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
        fll_print_format("%c%[%sNo relevant main was found within the file '%s'.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, filename, main->error.context, f_string_eol_s[0]);
      }
      else if (status == F_memory_not) {
        firewall_print_error_on_allocation_failure(main->error);
      }
      else {
        firewall_print_error_on_unhandled_for_file(main->error, "fll_fss_basic_read", status, filename);
      }
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

f_status_t firewall_process_rules(firewall_main_t * const main, f_string_range_t *range, firewall_local_data_t *local) {

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
    status = firewall_perform_commands(main, *local);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_memory_not) {
        firewall_print_error_on_allocation_failure(main->error);
      }
      else if (status == F_failure) {
        // the error message has already been displayed.
      }
      else {
        firewall_print_error_on_unhandled(main->error, "firewall_perform_commands", status);
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

f_status_t firewall_delete_local_data(firewall_local_data_t * const local) {

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

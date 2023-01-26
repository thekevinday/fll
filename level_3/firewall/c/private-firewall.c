#include "firewall.h"
#include "private-common.h"
#include "private-firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

f_status_t firewall_perform_commands(firewall_data_t * const data, firewall_local_data_t * const local) {

  if (!data || !local || local->device >= data->devices.used) return F_status_set_error(F_parameter);

  f_status_t status = F_none;

  bool invalid = F_false;
  bool is_ip_list = F_false;

  // Iptables command arguments
  bool ip_list_direction = F_false; // false = source, true = destination.
  bool use_protocol = F_false;
  uint8_t tool = firewall_program_ip46tables_e;
  uint8_t chain = firewall_chain_none_id_e;

  int return_code = 0;

  f_array_length_t i = 0;
  f_array_length_t r = 0;
  f_array_length_t repeat = 2;
  f_array_length_t length = 0;

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
        f_string_dynamic_resize(0, &ip_list);
        f_string_dynamics_resize(0, &arguments);
        f_string_dynamic_resize(0, &device);
        f_string_dynamic_resize(0, &protocol);

        return F_status_set_error(F_interrupt);
      }

      data->main->signal_check = 0;
    }

    length = (local->rule_objects.array[i].stop - local->rule_objects.array[i].start) + 1;
    invalid = F_false;

    is_ip_list = F_false;
    ip_list_direction = F_false;

    ip_list.used = 0;

    // Process chain rule
    if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_chain_s, length) == F_equal_to) {
      if (chain == firewall_chain_custom_id_e) {

        // Custom chains can only apply to themselves, so silently ignore chain commands specified within a custom chain.
        fll_print_format("%r%[%QAt line %ul, the chain option is meaningless inside of a custom chain.%]%r", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, f_string_eol_s);

        continue;
      }

      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

      if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
        invalid = F_true;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_input_s, length) == F_equal_to) {
        chain = firewall_chain_input_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_output_s, length) == F_equal_to) {
        chain = firewall_chain_output_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_forward_s, length) == F_equal_to) {
        chain = firewall_chain_forward_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_postrouting_s, length) == F_equal_to) {
        chain = firewall_chain_postrouting_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_prerouting_s, length) == F_equal_to) {
        chain = firewall_chain_prerouting_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_chain_none_s, length) == F_equal_to) {
        chain = firewall_chain_none_id_e;
      }
      else {
        invalid = F_true;
      }

      if (!invalid) continue;
    }

    // Process direction rule
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_direction_s, length) == F_equal_to) {
      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

      if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
        invalid = F_true;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_direction_input_s, length) == F_equal_to) {
        direction = firewall_direction_input_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_direction_output_s, length) == F_equal_to) {
        direction = firewall_direction_output_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_direction_none_s, length) == F_equal_to) {
        direction = firewall_direction_none_id_e;
      }
      else {

        // Direction must be specified, and no custom directions are allowed.
        invalid = F_true;
      }

      if (!invalid) continue;
    }

    // Process device rule.
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_device_s, length) == F_equal_to) {
      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

      if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
        invalid = F_true;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_device_all_s, length) == F_equal_to) {
        f_string_dynamic_resize(0, &device);

        continue;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_device_this_s, length) == F_equal_to) {
        if (data->devices.array[local->device].used) {
          if (data->devices.array[local->device].used > device.size) {
            status = f_string_dynamic_resize(data->devices.array[local->device].used, &device);
            if (F_status_is_error(status)) break;
          }

          memcpy(device.string, data->devices.array[local->device].string, sizeof(f_char_t) * data->devices.array[local->device].used);

          device.used = data->devices.array[local->device].used;
        }
        else {
          f_string_dynamic_resize(0, &device);
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
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_action_s, length) == F_equal_to) {
      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

      if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
        invalid = F_true;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_append_s, length) == F_equal_to) {
        action = firewall_action_append_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_insert_s, length) == F_equal_to) {
        action = firewall_action_insert_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_policy_s, length) == F_equal_to) {
        action = firewall_action_policy_id_e;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_action_none_s, length) == F_equal_to) {
        action = firewall_action_none_id_e;
      }
      else {
        invalid = F_true;
      }

      if (!invalid) continue;
    }

    // Process ip_list rule.
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_ip_list, length) == F_equal_to) {
      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;
      is_ip_list = F_true;

      if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_ip_list_source_s, length) == F_equal_to) {
        ip_list_direction = F_false;
      }
      else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_ip_list_destination_s, length) == F_equal_to) {
        ip_list_direction = F_true;
      }
      else {
        invalid = F_true;
      }
    }
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_protocol_s, length) == F_equal_to) {
      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

      if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
        invalid = F_true;
      }
      else {
        if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_protocol_none_s, length) == F_equal_to) {
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
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_tool_s, length) == F_equal_to) {
      length = (local->rule_contents.array[i].array[0].stop - local->rule_contents.array[i].array[0].start) + 1;

      if (local->rule_contents.array[i].used <= 0 || local->rule_contents.array[i].used > 1) {
        invalid = F_true;
      }
      else {
        if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_tool_iptables_s, length) == F_equal_to) {
          tool = firewall_program_iptables_e;
          current_tool = firewall_tool_iptables_s;
          repeat = 1;
        }
        else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_tool_ip6tables_s, length) == F_equal_to) {
          tool = firewall_program_ip6tables_e;
          current_tool = firewall_tool_ip6tables_s;
          repeat = 1;
        }
        else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_tool_ip46tables_s, length) == F_equal_to) {
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
    else if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_objects.array[i].start, firewall_rule_s, length) == F_equal_to_not) {
      if (length) {
        flockfile(data->main->warning.to.stream);

        fl_print_format("%r%[%QAt line %ul, the object '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, data->main->warning.notable);
        fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, local->buffer, local->rule_objects.array[i], data->main->warning.notable);
        fl_print_format("%[' is invalid.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

        funlockfile(data->main->warning.to.stream);
      }
      else {
        fll_print_format("%r%[%QAt line %ul, the object is missing.%]%r", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, f_string_eol_s);
      }

      continue;
    }

    if (invalid) {
      length = (local->rule_objects.array[i].stop - local->rule_objects.array[i].start) + 1;

      if (length) {
        flockfile(data->main->warning.to.stream);

        fl_print_format("%r%[%QAt line %ul, the object '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context);
        fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, local->buffer, local->rule_objects.array[i], data->main->warning.notable);
        fl_print_format("%[' has invalid content '%]", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
        fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, local->buffer, local->rule_contents.array[i].array[0], data->main->warning.notable);
        fl_print_format("%['.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

        funlockfile(data->main->warning.to.stream);
      }
      else {
        fll_print_format("%r%[%QAt line %ul, the object has no content.%]%r", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context, f_string_eol_s);
      }

      continue;
    }

    for (r = repeat; F_status_is_error_not(status) && r; --r) {

      arguments.used = 0;

      // First add the program name.
      status = f_string_dynamics_increase(F_memory_default_allocation_small_d, &arguments);
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
        status = f_string_dynamics_increase(firewall_default_allocation_step_d, &arguments);
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

          status = f_string_dynamics_increase(firewall_default_allocation_step_d, &arguments);
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
            status = F_none;
          }
          else {
            ++arguments.used;
          }
        }
      }

      // Add the device if and only if a non-none direction is specified.
      if (device.used && (direction == firewall_direction_input_id_e || direction == firewall_direction_output_id_e)) {
        if (fl_string_dynamic_compare_string(local->buffer.string + local->rule_contents.array[i].array[0].start, firewall_device_all_s, length) == F_equal_to_not) {

          status = f_string_dynamics_increase(firewall_default_allocation_step_d, &arguments);
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
          status = f_string_dynamics_increase(firewall_default_allocation_step_d, &arguments);
          if (F_status_is_error(status)) break;

          arguments.array[arguments.used].used = 0;

          status = f_string_dynamic_append(device, &arguments.array[arguments.used]);

          if (F_status_is_error(status)) break;

          ++arguments.used;
        }
      }

      if (use_protocol) {
        status = f_string_dynamics_increase(firewall_default_allocation_step_d, &arguments);
        if (F_status_is_error(status)) break;

        arguments.array[arguments.used].used = 0;

        status = f_string_dynamic_append(firewall_protocol_command_s, &arguments.array[arguments.used]);

        if (F_status_is_error(status)) break;

        ++arguments.used;

        if (protocol.used) {
          status = f_string_dynamics_increase(firewall_default_allocation_step_d, &arguments);
          if (F_status_is_error(status)) break;

          arguments.array[arguments.used].used = 0;

          status = f_string_dynamic_append(protocol, &arguments.array[arguments.used]);

          if (F_status_is_error(status)) break;

          ++arguments.used;
        }
      }

      // Last up is the "rule".
      if ((!is_ip_list && local->rule_contents.array[i].used > 0) || (is_ip_list && local->rule_contents.array[i].used > 1)) {
        f_array_length_t subcounter = 0;

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

        status = f_string_dynamics_increase_by(local->rule_contents.array[i].used, &arguments);
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

        flockfile(data->main->warning.to.stream);

        fl_print_format("%r%[%QAt line %ul, the object '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, i, data->main->warning.context);
        fl_print_format("%[%/Q%]", data->main->warning.to.stream, data->main->warning.notable, local->buffer, local->rule_objects.array[i], data->main->warning.notable);
        fl_print_format("%]%[' has no content.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

        funlockfile(data->main->warning.to.stream);

        break;
      }

      // Now execute the generated commands.
      if (arguments.used > 1) {
        if (is_ip_list) {
          f_file_t file = f_file_t_initialize;
          f_string_dynamic_t path_file = f_string_dynamic_t_initialize;
          f_string_dynamic_t local_buffer = f_string_dynamic_t_initialize;

          f_fss_objects_t basic_objects = f_fss_objects_t_initialize;
          f_fss_contents_t basic_contents = f_fss_objects_t_initialize;

          status = f_string_dynamic_append(firewall_network_path_s, &path_file);

          if (F_status_is_error_not(status)) {
            status = f_string_dynamic_append(ip_list, &path_file);
          }

          if (F_status_is_error_not(status)) {
            status = f_file_open(path_file, 0, &file);
          }

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_parameter) {
              if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
                firewall_print_error_on_invalid_parameter(data->main->error, "f_file_open");
              }
            }
            else if (F_status_set_fine(status) == F_file_found_not) {

              // The file does not have to exist
              if (data->main->error.verbosity != f_console_verbosity_verbose_e || data->main->error.verbosity == f_console_verbosity_debug_e) {
                fll_print_format("%r%[%QCannot find the file '%Q'.%]%r", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, path_file, data->main->warning.context, f_string_eol_s);
              }

              status = F_none;
            }
            else if (F_status_set_fine(status) == F_file_open) {
              if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QUnable to open the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
              }
            }
            else if (F_status_set_fine(status) == F_file_descriptor) {
              if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QFile descriptor error while trying to open the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
              }
            }
            else if (F_status_set_fine(status) == F_memory_not) {
              firewall_print_error_on_allocation_failure(data->main->error);
            }
            else {
              firewall_print_error_on_unhandled(data->main->error, "f_file_open", F_status_set_fine(status));
            }

            f_file_stream_close(F_true, &file);
          }
          else {
            status = f_file_read(file, &local_buffer);

            f_file_stream_close(F_true, &file);

            if (F_status_is_error(status)) {
              if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
                if (F_status_set_fine(status) == F_parameter) {
                  firewall_print_error_on_invalid_parameter(data->main->error, "f_file_read");
                }
                else if (F_status_set_fine(status) == F_number_overflow) {
                  fll_print_format("%r%[%QInteger overflow while trying to buffer the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                }
                else if (F_status_set_fine(status) == F_file_closed) {
                  fll_print_format("%r%[%QThe file '%Q' is no longer open.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                }
                else if (F_status_set_fine(status) == F_file_seek) {
                  fll_print_format("%r%[%QA seek error occurred while accessing the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                }
                else if (F_status_set_fine(status) == F_file_read) {
                  fll_print_format("%r%[%QA read error occurred while accessing the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, path_file, data->main->error.context, f_string_eol_s);
                }
                else if (F_status_set_fine(status) != F_memory_not) {
                  firewall_print_error_on_unhandled(data->main->error, "f_file_read", F_status_set_fine(status));
                }
              }
            }
            else {
              f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

              {
                f_state_t state = f_state_t_initialize;
                f_string_range_t input = macro_f_string_range_t_initialize2(local_buffer.used);

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
                  fll_error_print(data->main->error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);
                }
              }

              if (F_status_is_error_not(status)) {
                status = f_string_dynamics_increase_by(2, &arguments);

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
                  f_array_lengths_resize(0, &delimits);

                  break;
                }

                ++arguments.used;

                // The ip_list file contains objects and no content, all objects are what matter an nothing else.
                for (f_array_length_t at = 0; at < basic_objects.used; ++at) {

                  arguments.array[arguments.used].used = 0;

                  status = f_string_dynamic_partial_append(local_buffer, basic_objects.array[at], &arguments.array[arguments.used]);
                  if (F_status_is_error(status)) break;

                  ++arguments.used;

                  firewall_print_debug_tool(data->main->warning, current_tool, arguments);

                  status = fll_execute_program(current_tool, arguments, 0, 0, (void *) &return_code);

                  if (status == F_child) {
                    f_array_lengths_resize(0, &delimits);

                    f_string_dynamic_resize(0, &ip_list);
                    f_string_dynamics_resize(0, &arguments);
                    f_string_dynamic_resize(0, &device);
                    f_string_dynamic_resize(0, &protocol);

                    data->main->child = return_code;

                    return status;
                  }

                  // Remove ip_argument from arguments string.
                  --arguments.used;

                  if (F_status_is_error(status)) {
                    if (F_status_set_fine(status) == F_failure) {
                      firewall_print_error_on_operation(data->main->error, current_tool, arguments);
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

              f_array_lengths_resize(0, &delimits);
            }
          }

          f_string_dynamic_resize(0, &local_buffer);
          f_string_dynamic_resize(0, &path_file);

          f_string_ranges_resize(0, &basic_objects);
          f_string_rangess_resize(0, &basic_contents);

          if (F_status_set_fine(status) == F_failure || F_status_set_fine(status) == F_parameter) break;
        }
        else {
          firewall_print_debug_tool(data->main->warning, current_tool, arguments);

          status = fll_execute_program(current_tool, arguments, 0, 0, (void *) &return_code);

          if (status == F_child) {
            f_string_dynamic_resize(0, &ip_list);
            f_string_dynamics_resize(0, &arguments);
            f_string_dynamic_resize(0, &device);
            f_string_dynamic_resize(0, &protocol);

            data->main->child = return_code;

            return status;
          }

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_failure) {
              firewall_print_error_on_operation(data->main->error, current_tool, arguments);
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

  f_string_dynamic_resize(0, &ip_list);
  f_string_dynamics_resize(0, &arguments);
  f_string_dynamic_resize(0, &device);
  f_string_dynamic_resize(0, &protocol);

  return status;
}

f_status_t firewall_create_custom_chains(firewall_data_t * const data, firewall_reserved_chains_t * const reserved, firewall_local_data_t * const local) {

  if (!data || !local) return F_status_set_error(F_parameter);

  f_status_t status = F_none;

  uint8_t tool = firewall_program_iptables_e;
  bool new_chain = F_false;
  bool create_chain = F_false;
  int return_code = 0;

  f_array_length_t i = 0;
  f_array_length_t j = 0;

  f_array_length_t length = 0;
  f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

  local->chain_ids.used = local->chain_objects.used;

  status = f_string_dynamics_resize(2, &arguments);
  if (F_status_is_error(status)) return status;

  status = f_array_lengths_increase_by(local->chain_objects.used, &local->chain_ids);
  if (F_status_is_error(status)) return status;

  memset(local->chain_ids.array, 0, sizeof(f_array_length_t) * local->chain_ids.used);

  status = f_string_dynamic_append(firewall_chain_create_command_s, &arguments.array[0]);

  if (F_status_is_error_not(status)) {
    status = f_string_dynamic_increase(F_memory_default_allocation_small_d, &arguments.array[1]);
  }
  else {
    f_string_dynamics_resize(0, &arguments);

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
    if (fl_string_dynamic_partial_compare_string(firewall_group_main_s.string, local->buffer, firewall_group_main_s.used, local->chain_objects.array[i]) == F_equal_to) {
      new_chain = F_false;
      reserved->has_main = F_true;
      reserved->main_at = i;
    }

    // Skip globally reserved chain name: stop.
    if (fl_string_dynamic_partial_compare_string(firewall_group_stop_s.string, local->buffer, firewall_group_stop_s.used, local->chain_objects.array[i]) == F_equal_to) {
      new_chain = F_false;
      reserved->has_stop = F_true;
      reserved->stop_at = i;
    }

    // Skip globally reserved chain name: lock.
    if (fl_string_dynamic_partial_compare_string(firewall_group_lock_s.string, local->buffer, firewall_group_lock_s.used, local->chain_objects.array[i]) == F_equal_to) {
      new_chain = F_false;
      reserved->has_lock = F_true;
      reserved->lock_at = i;
    }

    // Skip globally reserved chain name: none.
    if (fl_string_dynamic_partial_compare_string(firewall_chain_none_s.string, local->buffer, firewall_chain_none_s.used, local->chain_objects.array[i]) == F_equal_to) {
      new_chain = F_false;
    }

    if (new_chain) {
      for (; j < data->chains.used; ++j) {

        if (fl_string_dynamic_partial_compare_string(data->chains.array[j].string, local->buffer, data->chains.array[j].used, local->chain_objects.array[i]) == F_equal_to) {
          new_chain = F_false;
          local->chain_ids.array[i] = j;

          break;
        }
      } // for
    }

    if (new_chain) {
      status = f_string_dynamics_increase(firewall_default_allocation_step_d, &data->chains);
      if (F_status_is_error(status)) break;

      create_chain = F_true;
      length = (local->chain_objects.array[i].stop - local->chain_objects.array[i].start) + 1;

      arguments.array[1].used = 0;

      status = f_string_dynamic_increase_by(length + 1, &arguments.array[1]);
      if (F_status_is_error(status)) break;

      status = f_string_dynamic_increase_by(length + 1, &data->chains.array[data->chains.used]);
      if (F_status_is_error(status)) break;

      data->chains.array[data->chains.used].used = 0;
      local->chain_ids.array[i] = data->chains.used;

      // Copy the string character by character, ignoring placeholders.
      for (j = local->chain_objects.array[i].start; j <= local->chain_objects.array[i].stop; ++j) {

        if (local->buffer.string[j] == f_fss_delimit_placeholder_s.string[0]) continue;

        data->chains.array[data->chains.used].string[data->chains.array[data->chains.used].used++] = local->buffer.string[j];
        arguments.array[1].string[arguments.array[1].used++] = local->buffer.string[j];
      } // for

      arguments.array[1].string[arguments.array[1].used] = 0;
      data->chains.array[data->chains.used].string[data->chains.array[data->chains.used].used] = 0;

      if (fl_string_dynamic_compare(arguments.array[1], firewall_chain_forward_s) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_dynamic_compare(arguments.array[1], firewall_chain_input_s) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_dynamic_compare(arguments.array[1], firewall_chain_output_s) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_dynamic_compare(arguments.array[1], firewall_chain_postrouting_s) == F_equal_to) {
        create_chain = F_false;
      }
      else if (fl_string_dynamic_compare(arguments.array[1], firewall_chain_prerouting_s) == F_equal_to) {
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
            firewall_print_error_on_operation(data->main->error, tool == firewall_program_iptables_e ? firewall_tool_iptables_s : firewall_tool_ip6tables_s, arguments);
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

  f_string_dynamics_resize(0, &arguments);

  return status;
}

f_status_t firewall_delete_chains(firewall_data_t * const data) {

  if (!data) return F_status_set_error(F_parameter);

  const f_string_static_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };
  f_status_t status = F_none;

  for (f_array_length_t i = 0; i < 2; ++i) {

    if (firewall_signal_received(data)) {
      return F_status_set_error(F_interrupt);
    }

    f_string_statics_t arguments = f_string_statics_t_initialize;
    arguments.used = 1;

    f_string_static_t arguments_array[arguments.used];
    arguments_array[0] = firewall_chain_flush_command_s;
    arguments.array = arguments_array;

    int return_code = 0;

    firewall_print_debug_tool(data->main->warning, tools[i], arguments);

    status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

    if (status == F_child) {
      data->main->child = return_code;

      return status;
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_failure) {
        firewall_print_error_on_operation(data->main->error, tools[i], arguments);
      }
      else if (F_status_set_fine(status) == F_parameter) {
        firewall_print_error_on_invalid_parameter(data->main->error, "fll_execute_program");
      }
      else {
        firewall_print_error_on_unhandled(data->main->error, "fll_execute_program", F_status_set_fine(status));
      }

      return status;
    }
  } // for

  int return_code = 0;

  f_string_statics_t arguments = f_string_statics_t_initialize;
  arguments.used = 1;

  f_string_static_t argument_array[arguments.used];
  arguments.array = argument_array;
  argument_array[0] = firewall_chain_delete_command_s;

  for (f_array_length_t i = 0; i < 2; ++i) {

    firewall_print_debug_tool(data->main->warning, tools[i], arguments);

    return_code = 0;

    status = fll_execute_program(tools[i], arguments, 0, 0, (void *) &return_code);

    if (status == F_child) {
      data->main->child = return_code;

      break;
    }

    if (firewall_signal_received(data)) {
      status = F_status_set_error(F_interrupt);

      break;
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_failure) {
        firewall_print_error_on_operation(data->main->error, tools[i], arguments);
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

  return status;
}

f_status_t firewall_default_lock(firewall_data_t * const data) {

  if (!data) return F_status_set_error(F_parameter);

  const f_string_static_t chains[3] = { firewall_chain_input_s, firewall_chain_output_s, firewall_chain_forward_s };
  const f_string_static_t tools[2] = { firewall_tool_iptables_s, firewall_tool_ip6tables_s };

  f_status_t status = F_none;

  int return_code = 0;

  f_string_statics_t arguments = f_string_statics_t_initialize;
  arguments.used = 3;

  f_string_static_t argument_array[arguments.used];
  arguments.array = argument_array;
  arguments.array[0] = firewall_action_policy_command_s;
  arguments.array[2] = firewall_chain_drop_s;

  f_array_length_t i = 0;
  f_array_length_t j = 0;

  for (; i < 3; ++i) {

    arguments.array[1] = chains[i];

    for (j = 0; j < 2; ++j) {

      firewall_print_debug_tool(data->main->warning, tools[j], arguments);

      return_code = 0;

      status = fll_execute_program(tools[j], arguments, 0, 0, (void *) &return_code);

      if (status == F_child) {
        data->main->child = return_code;

        break;
      }

      if (firewall_signal_received(data)) {
        status = F_status_set_error(F_interrupt);

        break;
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_failure) {
          firewall_print_error_on_operation(data->main->error, tools[j], arguments);
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
  } // for

  return status;
}

f_status_t firewall_buffer_rules(firewall_data_t * const data, const f_string_static_t filename, const bool optional, firewall_local_data_t * const local) {

  if (!data || !local) return F_status_set_error(F_parameter);

  f_file_t file = f_file_t_initialize;

  f_status_t status = f_file_open(filename, 0, &file);

  if (F_status_is_error(status)) {
    if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
      if (optional) {
        if (F_status_set_fine(status) == F_parameter) {
          firewall_print_error_on_invalid_parameter(data->main->error, "f_file_open");
        }
        else if (F_status_set_fine(status) != F_file_found_not && F_status_set_fine(status) != F_file_open && F_status_set_fine(status) != F_file_descriptor) {
          firewall_print_error_on_unhandled(data->main->error, "f_file_open", F_status_set_fine(status));
        }
      } else {
        if (F_status_set_fine(status) == F_parameter) {
          firewall_print_error_on_invalid_parameter(data->main->error, "f_file_open");
        }
        else if (F_status_set_fine(status) == F_file_found_not) {
          fll_print_format("%r%[%QUnable to find the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (F_status_set_fine(status) == F_file_open) {
          fll_print_format("%r%[%QUnable to open the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else if (F_status_set_fine(status) == F_file_descriptor) {
          fll_print_format("%r%[%QFile descriptor error while trying to open the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
        }
        else {
          firewall_print_error_on_unhandled(data->main->error, "f_file_open", F_status_set_fine(status));
        }
      }
    }

    return status;
  }

  status = f_file_read(file, &local->buffer);

  f_file_stream_close(F_true, &file);

  if (F_status_is_error(status)) {
    if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_parameter) {
        firewall_print_error_on_invalid_parameter(data->main->error, "f_file_read");
      }
      else if (F_status_set_fine(status) == F_number_overflow) {
        fll_print_format("%r%[%QInteger overflow while trying to buffer the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
      }
      else if (F_status_set_fine(status) == F_file_closed) {
        fll_print_format("%r%[%QThe file '%Q' is no longer open.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
      }
      else if (F_status_set_fine(status) == F_file_seek) {
        fll_print_format("%r%[%QA seek error occurred while accessing the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
      }
      else if (F_status_set_fine(status) == F_file_read) {
        fll_print_format("%r%[%QA read error occurred while accessing the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
      }
      else if (F_status_set_fine(status) == F_memory_not) {
        firewall_print_error_on_allocation_failure(data->main->error);
      }
      else {
        firewall_print_error_on_unhandled(data->main->error, "f_file_read", F_status_set_fine(status));
      }
    }

    return status;
  }

  f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
  f_fss_comments_t comments = f_fss_comments_t_initialize;
  f_state_t state = f_state_t_initialize;

  {
    f_string_range_t input = macro_f_string_range_t_initialize2(local->buffer.used);

    status = fll_fss_basic_list_read(local->buffer, state, &input, &local->chain_objects, &local->chain_contents, &delimits, 0, &comments);
  }

  if (F_status_is_error(status)) {
    status = F_status_set_fine(status);

    if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
      if (status == F_parameter) {
        firewall_print_error_on_invalid_parameter_for_file(data->main->error, "fll_fss_basic_list_read", filename);
      }
      else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
        fll_print_format("%r%[%QNo relevant main was found within the file '%Q'.%]%r", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, filename, data->main->error.context, f_string_eol_s);
      }
      else if (status == F_memory_not) {
        firewall_print_error_on_allocation_failure(data->main->error);
      }
      else {
        firewall_print_error_on_unhandled_for_file(data->main->error, "fll_fss_basic_read", status, filename);
      }
    }
  }
  else {
    status = f_fss_apply_delimit(state, delimits, &local->buffer);

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);
    }
  }

  macro_f_fss_delimits_t_delete_simple(delimits);
  macro_f_fss_comments_t_delete_simple(comments);

  return status;
}

f_status_t firewall_process_rules(firewall_data_t * const data, f_string_range_t * const range, firewall_local_data_t * const local) {

  if (!data || !range || !local) return F_status_set_error(F_parameter);

  f_status_t status = F_none;
  f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
  f_state_t state = f_state_t_initialize;

  status = fll_fss_extended_read(local->buffer, state, range, &local->rule_objects, &local->rule_contents, 0, 0, &delimits, 0);

  if (F_status_is_error_not(status)) {
    status = f_fss_apply_delimit(state, delimits, &local->buffer);

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);
    }
  }

  macro_f_fss_delimits_t_delete_simple(delimits);

  if (F_status_is_error_not(status)) {
    status = firewall_perform_commands(data, local);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_memory_not) {
        firewall_print_error_on_allocation_failure(data->main->error);
      }
      else if (F_status_set_fine(status) == F_failure) {
        // The error message has already been displayed.
      }
      else {
        firewall_print_error_on_unhandled(data->main->error, "firewall_perform_commands", F_status_set_fine(status));
      }
    }
  }

  f_string_ranges_resize(0, &local->rule_objects);
  f_string_rangess_resize(0, &local->rule_contents);

  return status;
}

f_status_t firewall_delete_local_data(firewall_local_data_t * const local) {

  if (!local) return F_status_set_error(F_parameter);

  local->is_global = F_true;
  local->is_main = F_false;
  local->is_stop = F_false;
  local->is_lock = F_false;

  local->device = 0;
  local->chain = 0;

  f_string_dynamic_resize(0, &local->buffer);
  f_array_lengths_resize(0, &local->chain_ids);

  f_string_ranges_resize(0, &local->chain_objects);
  f_string_rangess_resize(0, &local->chain_contents);

  f_string_ranges_resize(0, &local->rule_objects);
  f_string_rangess_resize(0, &local->rule_contents);

  return F_none;
}

#ifdef __cplusplus
} // extern "C"
#endif

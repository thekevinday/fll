#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_program_version_
  const f_string_static_t firewall_program_version_s = macro_f_string_static_t_initialize(FIREWALL_program_version_s, 0, FIREWALL_program_version_s_length);
#endif // _di_firewall_program_version_

#ifndef _di_firewall_program_name_
  const f_string_static_t firewall_program_name_s = macro_f_string_static_t_initialize(FIREWALL_program_name_s, 0, FIREWALL_program_name_s_length);
  const f_string_static_t firewall_program_name_long_s = macro_f_string_static_t_initialize(FIREWALL_program_name_long_s, 0, FIREWALL_program_name_long_s_length);
#endif // _di_firewall_program_name_

#ifndef _di_firewall_program_help_parameters_
  const f_string_static_t firewall_program_help_parameters_s = macro_f_string_static_t_initialize(FIREWALL_program_help_parameters_s, 0, FIREWALL_program_help_parameters_s_length);
#endif // _di_firewall_program_help_parameters_

#ifndef _di_firewall_paths_
  const f_string_static_t firewall_file_first_s = macro_f_string_static_t_initialize(FIREWALL_file_first_s, 0, FIREWALL_file_first_s_length);
  const f_string_static_t firewall_file_last_s = macro_f_string_static_t_initialize(FIREWALL_file_last_s, 0, FIREWALL_file_last_s_length);
  const f_string_static_t firewall_file_other_s = macro_f_string_static_t_initialize(FIREWALL_file_other_s, 0, FIREWALL_file_other_s_length);
  const f_string_static_t firewall_file_suffix_s = macro_f_string_static_t_initialize(FIREWALL_file_suffix_s, 0, FIREWALL_file_suffix_s_length);

  const f_string_static_t firewall_network_path_s = macro_f_string_static_t_initialize(FIREWALL_network_path_s, 0, FIREWALL_network_path_s_length);
  const f_string_static_t firewall_network_devices_s = macro_f_string_static_t_initialize(FIREWALL_network_devices_s, 0, FIREWALL_network_devices_s_length);
#endif // _di_firewall_paths_

#ifndef _di_firewall_defines_
  const f_string_static_t firewall_action_s = macro_f_string_static_t_initialize(FIREWALL_action_s, 0, FIREWALL_action_s_length);
  const f_string_static_t firewall_action_append_s = macro_f_string_static_t_initialize(FIREWALL_action_append_s, 0, FIREWALL_action_append_s_length);
  const f_string_static_t firewall_action_insert_s = macro_f_string_static_t_initialize(FIREWALL_action_insert_s, 0, FIREWALL_action_insert_s_length);
  const f_string_static_t firewall_action_policy_s = macro_f_string_static_t_initialize(FIREWALL_action_policy_s, 0, FIREWALL_action_policy_s_length);
  const f_string_static_t firewall_action_none_s = macro_f_string_static_t_initialize(FIREWALL_action_none_s, 0, FIREWALL_action_none_s_length);

  const f_string_static_t firewall_action_append_command_s = macro_f_string_static_t_initialize(FIREWALL_action_append_command_s, 0, FIREWALL_action_append_command_s_length);
  const f_string_static_t firewall_action_insert_command_s = macro_f_string_static_t_initialize(FIREWALL_action_insert_command_s, 0, FIREWALL_action_insert_command_s_length);
  const f_string_static_t firewall_action_policy_command_s = macro_f_string_static_t_initialize(FIREWALL_action_policy_command_s, 0, FIREWALL_action_policy_command_s_length);

  const f_string_static_t firewall_chain_s = macro_f_string_static_t_initialize(FIREWALL_chain_s, 0, FIREWALL_chain_s_length);
  const f_string_static_t firewall_chain_forward_s = macro_f_string_static_t_initialize(FIREWALL_chain_forward_s, 0, FIREWALL_chain_forward_s_length);
  const f_string_static_t firewall_chain_drop_s = macro_f_string_static_t_initialize(FIREWALL_chain_drop_s, 0, FIREWALL_chain_drop_s_length);
  const f_string_static_t firewall_chain_input_s = macro_f_string_static_t_initialize(FIREWALL_chain_input_s, 0, FIREWALL_chain_input_s_length);
  const f_string_static_t firewall_chain_none_s = macro_f_string_static_t_initialize(FIREWALL_chain_none_s, 0, FIREWALL_chain_none_s_length);
  const f_string_static_t firewall_chain_output_s = macro_f_string_static_t_initialize(FIREWALL_chain_output_s, 0, FIREWALL_chain_output_s_length);
  const f_string_static_t firewall_chain_postrouting_s = macro_f_string_static_t_initialize(FIREWALL_chain_postrouting_s, 0, FIREWALL_chain_postrouting_s_length);
  const f_string_static_t firewall_chain_prerouting_s = macro_f_string_static_t_initialize(FIREWALL_chain_prerouting_s, 0, FIREWALL_chain_prerouting_s_length);

  const f_string_static_t firewall_chain_create_command_s = macro_f_string_static_t_initialize(FIREWALL_chain_create_command_s, 0, FIREWALL_chain_create_command_s_length);
  const f_string_static_t firewall_chain_delete_command_s = macro_f_string_static_t_initialize(FIREWALL_chain_delete_command_s, 0, FIREWALL_chain_delete_command_s_length);
  const f_string_static_t firewall_chain_flush_command_s = macro_f_string_static_t_initialize(FIREWALL_chain_flush_command_s, 0, FIREWALL_chain_flush_command_s_length);

  const f_string_static_t firewall_command_start_s = macro_f_string_static_t_initialize(FIREWALL_command_start_s, 0, FIREWALL_command_start_s_length);
  const f_string_static_t firewall_command_stop_s = macro_f_string_static_t_initialize(FIREWALL_command_stop_s, 0, FIREWALL_command_stop_s_length);
  const f_string_static_t firewall_command_restart_s = macro_f_string_static_t_initialize(FIREWALL_command_restart_s, 0, FIREWALL_command_restart_s_length);
  const f_string_static_t firewall_command_lock_s = macro_f_string_static_t_initialize(FIREWALL_command_lock_s, 0, FIREWALL_command_lock_s_length);
  const f_string_static_t firewall_command_show_s = macro_f_string_static_t_initialize(FIREWALL_command_show_s, 0, FIREWALL_command_show_s_length);

  const f_string_static_t firewall_device_s = macro_f_string_static_t_initialize(FIREWALL_device_s, 0, FIREWALL_device_s_length);
  const f_string_static_t firewall_device_all_s = macro_f_string_static_t_initialize(FIREWALL_device_all_s, 0, FIREWALL_device_all_s_length);
  const f_string_static_t firewall_device_this_s = macro_f_string_static_t_initialize(FIREWALL_device_this_s, 0, FIREWALL_device_this_s_length);
  const f_string_static_t firewall_device_loop_s = macro_f_string_static_t_initialize(FIREWALL_device_loop_s, 0, FIREWALL_device_loop_s_length);

  const f_string_static_t firewall_device_input_command_s = macro_f_string_static_t_initialize(FIREWALL_device_input_command_s, 0, FIREWALL_device_input_command_s_length);
  const f_string_static_t firewall_device_output_command_s = macro_f_string_static_t_initialize(FIREWALL_device_output_command_s, 0, FIREWALL_device_output_command_s_length);

  const f_string_static_t firewall_direction_s = macro_f_string_static_t_initialize(FIREWALL_direction_s, 0, FIREWALL_direction_s_length);
  const f_string_static_t firewall_direction_input_s = macro_f_string_static_t_initialize(FIREWALL_direction_input_s, 0, FIREWALL_direction_input_s_length);
  const f_string_static_t firewall_direction_output_s = macro_f_string_static_t_initialize(FIREWALL_direction_output_s, 0, FIREWALL_direction_output_s_length);
  const f_string_static_t firewall_direction_none_s = macro_f_string_static_t_initialize(FIREWALL_direction_none_s, 0, FIREWALL_direction_none_s_length);

  const f_string_static_t firewall_group_stop_s = macro_f_string_static_t_initialize(FIREWALL_group_stop_s, 0, FIREWALL_group_stop_s_length);
  const f_string_static_t firewall_group_lock_s = macro_f_string_static_t_initialize(FIREWALL_group_lock_s, 0, FIREWALL_group_lock_s_length);
  const f_string_static_t firewall_group_main_s = macro_f_string_static_t_initialize(FIREWALL_group_main_s, 0, FIREWALL_group_main_s_length);

  const f_string_static_t firewall_ip_list = macro_f_string_static_t_initialize(FIREWALL_ip_list_s, 0, FIREWALL_ip_list_s_length);
  const f_string_static_t firewall_ip_list_source_s = macro_f_string_static_t_initialize(FIREWALL_ip_list_source_s, 0, FIREWALL_ip_list_source_s_length);
  const f_string_static_t firewall_ip_list_source_action_s = macro_f_string_static_t_initialize(FIREWALL_ip_list_source_action_s, 0, FIREWALL_ip_list_source_action_s_length);
  const f_string_static_t firewall_ip_list_destination_s = macro_f_string_static_t_initialize(FIREWALL_ip_list_destination_s, 0, FIREWALL_ip_list_destination_s_length);
  const f_string_static_t firewall_ip_list_destination_action_s = macro_f_string_static_t_initialize(FIREWALL_ip_list_destination_action_s, 0, FIREWALL_ip_list_destination_action_s_length);

  const f_string_static_t firewall_protocol_s = macro_f_string_static_t_initialize(FIREWALL_protocol_s, 0, FIREWALL_protocol_s_length);
  const f_string_static_t firewall_protocol_command_s = macro_f_string_static_t_initialize(FIREWALL_protocol_command_s, 0, FIREWALL_protocol_command_s_length);
  const f_string_static_t firewall_protocol_none_s = macro_f_string_static_t_initialize(FIREWALL_protocol_none_s, 0, FIREWALL_protocol_none_s_length);

  const f_string_static_t firewall_rule_s = macro_f_string_static_t_initialize(FIREWALL_rule_s, 0, FIREWALL_rule_s_length);

  const f_string_static_t firewall_show_mangle_s = macro_f_string_static_t_initialize(FIREWALL_show_mangle_s, 0, FIREWALL_show_mangle_s_length);
  const f_string_static_t firewall_show_nat_s = macro_f_string_static_t_initialize(FIREWALL_show_nat_s, 0, FIREWALL_show_nat_s_length);
  const f_string_static_t firewall_show_ports_s = macro_f_string_static_t_initialize(FIREWALL_show_ports_s, 0, FIREWALL_show_ports_s_length);

  const f_string_static_t firewall_show_parameter_exact_s = macro_f_string_static_t_initialize(FIREWALL_show_parameter_exact_s, 0, FIREWALL_show_parameter_exact_s_length);
  const f_string_static_t firewall_show_parameter_verbose_s = macro_f_string_static_t_initialize(FIREWALL_show_parameter_verbose_s, 0, FIREWALL_show_parameter_verbose_s_length);
  const f_string_static_t firewall_show_parameter_table_s = macro_f_string_static_t_initialize(FIREWALL_show_parameter_table_s, 0, FIREWALL_show_parameter_table_s_length);
  const f_string_static_t firewall_show_parameter_numeric_s = macro_f_string_static_t_initialize(FIREWALL_show_parameter_numeric_s, 0, FIREWALL_show_parameter_numeric_s_length);
  const f_string_static_t firewall_show_parameter_list_s = macro_f_string_static_t_initialize(FIREWALL_show_parameter_list_s, 0, FIREWALL_show_parameter_list_s_length);

  const f_string_static_t firewall_tool_s = macro_f_string_static_t_initialize(FIREWALL_tool_s, 0, FIREWALL_tool_s_length);
  const f_string_static_t firewall_tool_iptables_s = macro_f_string_static_t_initialize(FIREWALL_tool_iptables_s, 0, FIREWALL_tool_iptables_s_length);
  const f_string_static_t firewall_tool_ip6tables_s = macro_f_string_static_t_initialize(FIREWALL_tool_ip6tables_s, 0, FIREWALL_tool_ip6tables_s_length);
  const f_string_static_t firewall_tool_ip46tables_s = macro_f_string_static_t_initialize(FIREWALL_tool_ip46tables_s, 0, FIREWALL_tool_ip46tables_s_length);
  const f_string_static_t firewall_tool_ipset_s = macro_f_string_static_t_initialize(FIREWALL_tool_ipset_s, 0, FIREWALL_tool_ipset_s_length);
#endif // _di_firewall_defines_

#ifndef _di_firewall_setting_delete_
  f_status_t firewall_setting_delete(firewall_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_firewall_setting_delete_

#ifndef _di_firewall_setting_load_
  void firewall_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, firewall_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { firewall_parameter_no_color_e, firewall_parameter_light_e, firewall_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          firewall_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      if (main->parameters.array[firewall_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[firewall_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { firewall_parameter_verbosity_quiet_e, firewall_parameter_verbosity_error_e, firewall_parameter_verbosity_verbose_e, firewall_parameter_verbosity_debug_e, firewall_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          firewall_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }

      if (main->parameters.array[firewall_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= firewall_main_flag_help_e;

        return;
      }

      if (main->parameters.array[firewall_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= firewall_main_flag_version_e;

        return;
      }

      // Identify and prioritize "from" mode parameters.
      {
        uint16_t choices_array[2] = { firewall_parameter_from_bytesequence_e, firewall_parameter_from_codepoint_e };
        choices.array = choices_array;
        choices.used = 2;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          firewall_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);

          return;
        }

        if (choices.array[choice] == firewall_parameter_from_bytesequence_e) {
          if (setting->mode & firewall_mode_from_codepoint_e) {
            setting->mode -= firewall_mode_from_codepoint_e;
          }

          setting->mode |= firewall_mode_from_bytesequence_e;
        }
        else if (choices.array[choice] == firewall_parameter_from_codepoint_e) {
          if (setting->mode & firewall_mode_from_bytesequence_e) {
            setting->mode -= firewall_mode_from_bytesequence_e;
          }

          setting->mode |= firewall_mode_from_codepoint_e;
        }
      }

      // Identify and prioritize "to" mode parameters.
      {
        uint16_t choices_array[4] = { firewall_parameter_to_bytesequence_e, firewall_parameter_to_codepoint_e, firewall_parameter_to_combining_e, firewall_parameter_to_width_e };
        choices.array = choices_array;
        choices.used = 4;
        choice = 1;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          firewall_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);

          return;
        }

        if (choices.array[choice] == firewall_parameter_to_bytesequence_e) {
          if (setting->mode & firewall_mode_to_codepoint_e) {
            setting->mode -= firewall_mode_to_codepoint_e;
          }

          if (setting->mode & firewall_mode_to_combining_e) {
            setting->mode -= firewall_mode_to_combining_e;
          }

          if (setting->mode & firewall_mode_to_width_e) {
            setting->mode -= firewall_mode_to_width_e;
          }

          setting->mode |= firewall_mode_to_bytesequence_e;
        }
        else if (choices.array[choice] == firewall_parameter_to_codepoint_e) {
          if (setting->mode & firewall_mode_to_bytesequence_e) {
            setting->mode -= firewall_mode_to_bytesequence_e;
          }

          if (setting->mode & firewall_mode_to_combining_e) {
            setting->mode -= firewall_mode_to_combining_e;
          }

          if (setting->mode & firewall_mode_to_width_e) {
            setting->mode -= firewall_mode_to_width_e;
          }

          setting->mode |= firewall_mode_to_codepoint_e;
        }
        else if (choices.array[choice] == firewall_parameter_to_combining_e) {
          if (setting->mode & firewall_mode_to_bytesequence_e) {
            setting->mode -= firewall_mode_to_bytesequence_e;
          }

          if (setting->mode & firewall_mode_to_codepoint_e) {
            setting->mode -= firewall_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[firewall_parameter_to_width_e].result == f_console_result_found_e) {
            setting->mode |= firewall_mode_to_width_e;
          }

          setting->mode |= firewall_mode_to_combining_e;
        }
        else if (choices.array[choice] == firewall_parameter_to_width_e) {
          if (setting->mode & firewall_mode_to_bytesequence_e) {
            setting->mode -= firewall_mode_to_bytesequence_e;
          }

          if (setting->mode & firewall_mode_to_codepoint_e) {
            setting->mode -= firewall_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[firewall_parameter_to_combining_e].result == f_console_result_found_e) {
            setting->mode |= firewall_mode_to_combining_e;
          }

          setting->mode |= firewall_mode_to_width_e;
        }
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[firewall_parameter_to_file_e].result == f_console_result_additional_e) {
      if (main->parameters.array[firewall_parameter_to_file_e].values.used > 1) {
        firewall_print_error_parameter_file_to_too_many(main, setting);

        setting->status = F_status_set_error(F_parameter);

        return;
      }

      if (args[main->parameters.array[firewall_parameter_to_file_e].values.array[0]].used) {
        setting->path_files_to.used = 0;

        setting->status = f_string_dynamics_increase_by(1, &setting->path_files_to);
        if (F_status_is_error(setting->status)) return;

        setting->path_files_to.array[setting->path_files_to.used].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[main->parameters.array[firewall_parameter_to_file_e].values.array[0]], &setting->path_files_to.array[0]);
        if (F_status_is_error(setting->status)) return;

        ++setting->path_files_to.used;

        setting->status = f_file_stream_open(args[main->parameters.array[firewall_parameter_to_file_e].values.array[0]], f_file_open_mode_append_s, &main->output.to);

        if (F_status_is_error(setting->status)) {
          fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_stream_open", F_true, args[main->parameters.array[firewall_parameter_to_file_e].values.array[0]], f_file_operation_open_s, fll_error_file_type_file_e);

          return;
        }

        setting->flag |= firewall_main_flag_file_to_e;
      }
      else {
        firewall_print_error_parameter_file_name_empty(main, setting, main->parameters.array[firewall_parameter_to_file_e].values.array[0]);

        setting->status = F_status_set_error(F_parameter);

        return;
      }
    }
    else if (main->parameters.array[firewall_parameter_to_file_e].result == f_console_result_found_e) {
      firewall_print_error_no_value(main, setting, firewall_long_to_file_s);

      setting->status = F_status_set_error(F_parameter);

      return;
    }
    else {
      main->output.to = main->message.to;

      if (setting->flag & firewall_main_flag_file_to_e) {
        setting->flag -= firewall_main_flag_file_to_e;
      }
    }

    if (main->parameters.array[firewall_parameter_from_file_e].result == f_console_result_additional_e) {
      setting->path_files_from.used = 0;

      setting->status = f_string_dynamics_increase_by(main->parameters.array[firewall_parameter_from_file_e].values.used, &setting->path_files_from);
      if (F_status_is_error(setting->status)) return;

      setting->path_files_from.used = main->parameters.array[firewall_parameter_from_file_e].values.used;

      f_array_length_t i = 0;
      f_array_length_t index = 0;

      for (; i < setting->path_files_from.used; ++i) {

        index = main->parameters.array[firewall_parameter_from_file_e].values.array[i];
        setting->path_files_from.array[i].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &setting->path_files_from.array[i]);
        if (F_status_is_error(setting->status)) return;

        if (args[index].used) {
          if (f_file_exists(args[index], F_true) != F_true) {
            firewall_print_error_parameter_file_not_found(main, setting, F_true, args[index]);

            if (F_status_is_error_not(setting->status)) {
              setting->status = F_status_set_error(F_file_found_not);
            }
          }
        }
        else {
          firewall_print_error_parameter_file_name_empty(main, setting, index);

          if (F_status_is_error_not(setting->status)) {
            setting->status = F_status_set_error(F_parameter);
          }
        }
      } // for

      if (F_status_is_error(setting->status)) return;

      setting->flag |= firewall_main_flag_file_from_e;
    }
    else if (main->parameters.array[firewall_parameter_from_file_e].result == f_console_result_found_e) {
      firewall_print_error_no_value(main, setting, firewall_long_from_file_s);

      setting->status = F_status_set_error(F_parameter);

      return;
    }
    else {
      if (setting->flag & firewall_main_flag_file_from_e) {
        setting->flag -= firewall_main_flag_file_from_e;
      }
    }

    if (F_status_is_error(setting->status)) return;

    if (main->parameters.array[firewall_parameter_from_file_e].result == f_console_result_none_e && !((main->pipe & fll_program_data_pipe_input_e) || main->parameters.remaining.used)) {
      firewall_print_error_no_from(main, setting);

      setting->status = F_status_set_error(F_parameter);
    }

    if (!(setting->mode & firewall_mode_to_bytesequence_e)) {
      if (main->parameters.array[firewall_parameter_separate_e].result == f_console_result_found_e || main->parameters.array[firewall_parameter_headers_e].result == f_console_result_found_e) {
        setting->prepend = firewall_string_prepend_padding_s;
        setting->append = f_string_eol_s;
      }
      else {
        setting->prepend = f_string_space_s;
      }
    }

    if (main->parameters.array[firewall_parameter_headers_e].result == f_console_result_found_e) {
      setting->flag |= firewall_main_flag_header_e;
    }

    if (main->parameters.array[firewall_parameter_separate_e].result == f_console_result_found_e) {
      setting->flag |= firewall_main_flag_separate_e;
    }

    if (main->parameters.array[firewall_parameter_strip_invalid_e].result == f_console_result_found_e) {
      setting->flag |= firewall_main_flag_strip_invalid_e;
    }

    setting->valid_not = main->message.set->error;
  }
#endif // _di_firewall_setting_load_

#ifndef _di_firewall_setting_unload_
  f_status_t firewall_setting_unload(fll_program_data_t * const main, firewall_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    firewall_setting_delete(setting);

    return F_none;
  }
#endif // _di_firewall_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

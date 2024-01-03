#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_program_version_s_
  const f_string_static_t firewall_program_version_s = macro_f_string_static_t_initialize_1(FIREWALL_program_version_s, 0, FIREWALL_program_version_s_length);
#endif // _di_firewall_program_version_s_

#ifndef _di_firewall_program_name_s_
  const f_string_static_t firewall_program_name_s = macro_f_string_static_t_initialize_1(FIREWALL_program_name_s, 0, FIREWALL_program_name_s_length);
  const f_string_static_t firewall_program_name_long_s = macro_f_string_static_t_initialize_1(FIREWALL_program_name_long_s, 0, FIREWALL_program_name_long_s_length);
#endif // _di_firewall_program_name_s_

#ifndef _di_firewall_program_help_parameters_s_
  const f_string_static_t firewall_program_help_parameters_s = macro_f_string_static_t_initialize_1(FIREWALL_program_help_parameters_s, 0, FIREWALL_program_help_parameters_s_length);
#endif // _di_firewall_program_help_parameters_s_

#ifndef _di_firewall_path_s_
  const f_string_static_t firewall_file_first_s = macro_f_string_static_t_initialize_1(FIREWALL_file_first_s, 0, FIREWALL_file_first_s_length);
  const f_string_static_t firewall_file_last_s = macro_f_string_static_t_initialize_1(FIREWALL_file_last_s, 0, FIREWALL_file_last_s_length);
  const f_string_static_t firewall_file_other_s = macro_f_string_static_t_initialize_1(FIREWALL_file_other_s, 0, FIREWALL_file_other_s_length);
  const f_string_static_t firewall_file_suffix_s = macro_f_string_static_t_initialize_1(FIREWALL_file_suffix_s, 0, FIREWALL_file_suffix_s_length);

  const f_string_static_t firewall_network_path_s = macro_f_string_static_t_initialize_1(FIREWALL_network_path_s, 0, FIREWALL_network_path_s_length);
  const f_string_static_t firewall_network_devices_s = macro_f_string_static_t_initialize_1(FIREWALL_network_devices_s, 0, FIREWALL_network_devices_s_length);
#endif // _di_firewall_path_s_

#ifndef _di_firewall_d_
  const f_string_static_t firewall_action_s = macro_f_string_static_t_initialize_1(FIREWALL_action_s, 0, FIREWALL_action_s_length);
  const f_string_static_t firewall_action_append_s = macro_f_string_static_t_initialize_1(FIREWALL_action_append_s, 0, FIREWALL_action_append_s_length);
  const f_string_static_t firewall_action_insert_s = macro_f_string_static_t_initialize_1(FIREWALL_action_insert_s, 0, FIREWALL_action_insert_s_length);
  const f_string_static_t firewall_action_policy_s = macro_f_string_static_t_initialize_1(FIREWALL_action_policy_s, 0, FIREWALL_action_policy_s_length);
  const f_string_static_t firewall_action_none_s = macro_f_string_static_t_initialize_1(FIREWALL_action_none_s, 0, FIREWALL_action_none_s_length);

  const f_string_static_t firewall_action_append_command_s = macro_f_string_static_t_initialize_1(FIREWALL_action_append_command_s, 0, FIREWALL_action_append_command_s_length);
  const f_string_static_t firewall_action_insert_command_s = macro_f_string_static_t_initialize_1(FIREWALL_action_insert_command_s, 0, FIREWALL_action_insert_command_s_length);
  const f_string_static_t firewall_action_policy_command_s = macro_f_string_static_t_initialize_1(FIREWALL_action_policy_command_s, 0, FIREWALL_action_policy_command_s_length);

  const f_string_static_t firewall_chain_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_s, 0, FIREWALL_chain_s_length);
  const f_string_static_t firewall_chain_forward_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_forward_s, 0, FIREWALL_chain_forward_s_length);
  const f_string_static_t firewall_chain_drop_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_drop_s, 0, FIREWALL_chain_drop_s_length);
  const f_string_static_t firewall_chain_input_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_input_s, 0, FIREWALL_chain_input_s_length);
  const f_string_static_t firewall_chain_none_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_none_s, 0, FIREWALL_chain_none_s_length);
  const f_string_static_t firewall_chain_output_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_output_s, 0, FIREWALL_chain_output_s_length);
  const f_string_static_t firewall_chain_postrouting_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_postrouting_s, 0, FIREWALL_chain_postrouting_s_length);
  const f_string_static_t firewall_chain_prerouting_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_prerouting_s, 0, FIREWALL_chain_prerouting_s_length);

  const f_string_static_t firewall_chain_create_command_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_create_command_s, 0, FIREWALL_chain_create_command_s_length);
  const f_string_static_t firewall_chain_delete_command_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_delete_command_s, 0, FIREWALL_chain_delete_command_s_length);
  const f_string_static_t firewall_chain_flush_command_s = macro_f_string_static_t_initialize_1(FIREWALL_chain_flush_command_s, 0, FIREWALL_chain_flush_command_s_length);

  const f_string_static_t firewall_command_start_s = macro_f_string_static_t_initialize_1(FIREWALL_command_start_s, 0, FIREWALL_command_start_s_length);
  const f_string_static_t firewall_command_stop_s = macro_f_string_static_t_initialize_1(FIREWALL_command_stop_s, 0, FIREWALL_command_stop_s_length);
  const f_string_static_t firewall_command_restart_s = macro_f_string_static_t_initialize_1(FIREWALL_command_restart_s, 0, FIREWALL_command_restart_s_length);
  const f_string_static_t firewall_command_lock_s = macro_f_string_static_t_initialize_1(FIREWALL_command_lock_s, 0, FIREWALL_command_lock_s_length);
  const f_string_static_t firewall_command_show_s = macro_f_string_static_t_initialize_1(FIREWALL_command_show_s, 0, FIREWALL_command_show_s_length);

  const f_string_static_t firewall_device_s = macro_f_string_static_t_initialize_1(FIREWALL_device_s, 0, FIREWALL_device_s_length);
  const f_string_static_t firewall_device_all_s = macro_f_string_static_t_initialize_1(FIREWALL_device_all_s, 0, FIREWALL_device_all_s_length);
  const f_string_static_t firewall_device_this_s = macro_f_string_static_t_initialize_1(FIREWALL_device_this_s, 0, FIREWALL_device_this_s_length);
  const f_string_static_t firewall_device_loop_s = macro_f_string_static_t_initialize_1(FIREWALL_device_loop_s, 0, FIREWALL_device_loop_s_length);

  const f_string_static_t firewall_device_input_command_s = macro_f_string_static_t_initialize_1(FIREWALL_device_input_command_s, 0, FIREWALL_device_input_command_s_length);
  const f_string_static_t firewall_device_output_command_s = macro_f_string_static_t_initialize_1(FIREWALL_device_output_command_s, 0, FIREWALL_device_output_command_s_length);

  const f_string_static_t firewall_direction_s = macro_f_string_static_t_initialize_1(FIREWALL_direction_s, 0, FIREWALL_direction_s_length);
  const f_string_static_t firewall_direction_input_s = macro_f_string_static_t_initialize_1(FIREWALL_direction_input_s, 0, FIREWALL_direction_input_s_length);
  const f_string_static_t firewall_direction_output_s = macro_f_string_static_t_initialize_1(FIREWALL_direction_output_s, 0, FIREWALL_direction_output_s_length);
  const f_string_static_t firewall_direction_none_s = macro_f_string_static_t_initialize_1(FIREWALL_direction_none_s, 0, FIREWALL_direction_none_s_length);

  const f_string_static_t firewall_group_stop_s = macro_f_string_static_t_initialize_1(FIREWALL_group_stop_s, 0, FIREWALL_group_stop_s_length);
  const f_string_static_t firewall_group_lock_s = macro_f_string_static_t_initialize_1(FIREWALL_group_lock_s, 0, FIREWALL_group_lock_s_length);
  const f_string_static_t firewall_group_main_s = macro_f_string_static_t_initialize_1(FIREWALL_group_main_s, 0, FIREWALL_group_main_s_length);

  const f_string_static_t firewall_ip_list = macro_f_string_static_t_initialize_1(FIREWALL_ip_list_s, 0, FIREWALL_ip_list_s_length);
  const f_string_static_t firewall_ip_list_source_s = macro_f_string_static_t_initialize_1(FIREWALL_ip_list_source_s, 0, FIREWALL_ip_list_source_s_length);
  const f_string_static_t firewall_ip_list_source_action_s = macro_f_string_static_t_initialize_1(FIREWALL_ip_list_source_action_s, 0, FIREWALL_ip_list_source_action_s_length);
  const f_string_static_t firewall_ip_list_destination_s = macro_f_string_static_t_initialize_1(FIREWALL_ip_list_destination_s, 0, FIREWALL_ip_list_destination_s_length);
  const f_string_static_t firewall_ip_list_destination_action_s = macro_f_string_static_t_initialize_1(FIREWALL_ip_list_destination_action_s, 0, FIREWALL_ip_list_destination_action_s_length);

  const f_string_static_t firewall_protocol_s = macro_f_string_static_t_initialize_1(FIREWALL_protocol_s, 0, FIREWALL_protocol_s_length);
  const f_string_static_t firewall_protocol_command_s = macro_f_string_static_t_initialize_1(FIREWALL_protocol_command_s, 0, FIREWALL_protocol_command_s_length);
  const f_string_static_t firewall_protocol_none_s = macro_f_string_static_t_initialize_1(FIREWALL_protocol_none_s, 0, FIREWALL_protocol_none_s_length);

  const f_string_static_t firewall_rule_s = macro_f_string_static_t_initialize_1(FIREWALL_rule_s, 0, FIREWALL_rule_s_length);

  const f_string_static_t firewall_show_mangle_s = macro_f_string_static_t_initialize_1(FIREWALL_show_mangle_s, 0, FIREWALL_show_mangle_s_length);
  const f_string_static_t firewall_show_nat_s = macro_f_string_static_t_initialize_1(FIREWALL_show_nat_s, 0, FIREWALL_show_nat_s_length);
  const f_string_static_t firewall_show_ports_s = macro_f_string_static_t_initialize_1(FIREWALL_show_ports_s, 0, FIREWALL_show_ports_s_length);

  const f_string_static_t firewall_show_parameter_exact_s = macro_f_string_static_t_initialize_1(FIREWALL_show_parameter_exact_s, 0, FIREWALL_show_parameter_exact_s_length);
  const f_string_static_t firewall_show_parameter_verbose_s = macro_f_string_static_t_initialize_1(FIREWALL_show_parameter_verbose_s, 0, FIREWALL_show_parameter_verbose_s_length);
  const f_string_static_t firewall_show_parameter_table_s = macro_f_string_static_t_initialize_1(FIREWALL_show_parameter_table_s, 0, FIREWALL_show_parameter_table_s_length);
  const f_string_static_t firewall_show_parameter_numeric_s = macro_f_string_static_t_initialize_1(FIREWALL_show_parameter_numeric_s, 0, FIREWALL_show_parameter_numeric_s_length);
  const f_string_static_t firewall_show_parameter_list_s = macro_f_string_static_t_initialize_1(FIREWALL_show_parameter_list_s, 0, FIREWALL_show_parameter_list_s_length);

  const f_string_static_t firewall_tool_s = macro_f_string_static_t_initialize_1(FIREWALL_tool_s, 0, FIREWALL_tool_s_length);
  const f_string_static_t firewall_tool_iptables_s = macro_f_string_static_t_initialize_1(FIREWALL_tool_iptables_s, 0, FIREWALL_tool_iptables_s_length);
  const f_string_static_t firewall_tool_ip6tables_s = macro_f_string_static_t_initialize_1(FIREWALL_tool_ip6tables_s, 0, FIREWALL_tool_ip6tables_s_length);
  const f_string_static_t firewall_tool_ip46tables_s = macro_f_string_static_t_initialize_1(FIREWALL_tool_ip46tables_s, 0, FIREWALL_tool_ip46tables_s_length);
  const f_string_static_t firewall_tool_ipset_s = macro_f_string_static_t_initialize_1(FIREWALL_tool_ipset_s, 0, FIREWALL_tool_ipset_s_length);
#endif // _di_firewall_d_

#ifndef _di_firewall_setting_delete_
  f_status_t firewall_setting_delete(firewall_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_okay;
  }
#endif // _di_firewall_setting_delete_

#ifndef _di_firewall_setting_load_
  void firewall_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, firewall_setting_t * const setting, f_state_t * const state) {

    if (!main) return;

    main->setting.flag = 0;

    main->setting.state.status = f_console_parameter_process(state, arguments, &main->program.parameters, &main->setting.state, 0);

    // Identify and process first/last parameters.
    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~firewall_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= firewall_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~firewall_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= firewall_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_console_parameter_process", fll_error_file_flag_fallback_e);

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error);
      }

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "fll_program_parameter_process_context_standard", fll_error_file_flag_fallback_e);

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error);
      }

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "fll_program_parameter_process_verbosity_standard", fll_error_file_flag_fallback_e);

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error);
      }

      return;
    }

    main->program.output.to.id = F_type_descriptor_output_d;
    main->program.output.to.stream = F_type_output_d;
    main->program.output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= firewall_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= firewall_main_flag_version_e;

      return;
    }

    f_string_static_t * const args = main->program.parameters.arguments.array;

    if (main->program.parameters.array[firewall_parameter_strip_invalid_e].result & f_console_result_found_e) {
      main->setting.flag |= firewall_main_flag_strip_invalid_e;
    }
  }
#endif // _di_firewall_setting_load_

#ifndef _di_firewall_setting_unload_
  f_status_t firewall_setting_unload(firewall_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    firewall_setting_delete(&main->setting);

    return F_okay;
  }
#endif // _di_firewall_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

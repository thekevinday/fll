#include "firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_program_version_
  const f_string_static_t firewall_program_version_s = macro_f_string_static_t_initialize(FIREWALL_version_s, 0, FIREWALL_version_s_length);
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

  const f_string_static_t firewall_ip_list = macro_f_string_static_t_initialize(FIREWALL_ip_list, 0, FIREWALL_ip_list_length);
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

#ifndef _di_firewall_main_delete_
  f_status_t firewall_main_delete(firewall_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_string_dynamics_resize(0, &main->chains);
    f_type_array_lengths_resize(0, &main->remaining);
    f_string_dynamics_resize(0, &main->devices);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_firewall_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

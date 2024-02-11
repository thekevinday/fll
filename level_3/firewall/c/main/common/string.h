/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_common_string_h
#define _firewall_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_firewall_program_version_s_
  #define FIREWALL_program_version_major_s F_string_ascii_0_s
  #define FIREWALL_program_version_minor_s F_string_ascii_7_s
  #define FIREWALL_program_version_micro_s F_string_ascii_0_s

  #define FIREWALL_program_version_major_s_length F_string_ascii_0_s_length
  #define FIREWALL_program_version_minor_s_length F_string_ascii_7_s_length
  #define FIREWALL_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(FIREWALL_program_version_nano_prefix_s) && defined(FIREWALL_program_version_nano_prefix_s_length))
    #define FIREWALL_program_version_nano_prefix_s
    #define FIREWALL_program_version_nano_prefix_s_length 0
  #endif // !(defined(FIREWALL_program_version_nano_prefix_s) && defined(FIREWALL_program_version_nano_prefix_s_length))

  #if !(defined(FIREWALL_program_version_nano_s) && defined(FIREWALL_program_version_nano_s_length))
    #define FIREWALL_program_version_nano_s
    #define FIREWALL_program_version_nano_s_length 0
  #endif // !(defined(FIREWALL_program_version_nano_s) && defined(FIREWALL_program_version_nano_s_length))

  #define FIREWALL_program_version_s FIREWALL_program_version_major_s F_string_ascii_period_s FIREWALL_program_version_minor_s F_string_ascii_period_s FIREWALL_program_version_micro_s FIREWALL_program_version_nano_prefix_s FIREWALL_program_version_nano_s

  #define FIREWALL_program_version_s_length FIREWALL_program_version_major_s_length + F_string_ascii_period_s_length + FIREWALL_program_version_minor_s_length + F_string_ascii_period_s_length + FIREWALL_program_version_micro_s_length + FIREWALL_program_version_nano_prefix_s_length + FIREWALL_program_version_nano_s_length

  extern const f_string_static_t firewall_program_version_s;
#endif // _di_firewall_program_version_s_

/**
 * The program name.
 */
#ifndef _di_firewall_program_name_s_
  #define FIREWALL_program_name_s      "firewall"
  #define FIREWALL_program_name_long_s "Kevux Firewall Manager"

  #define FIREWALL_program_name_s_length      8
  #define FIREWALL_program_name_long_s_length 22

  extern const f_string_static_t firewall_program_name_s;
  extern const f_string_static_t firewall_program_name_long_s;
#endif // _di_firewall_program_name_s_

/**
 * The program help related data.
 */
#ifndef _di_firewall_program_help_parameters_s_
  #define FIREWALL_program_help_parameters_s "operation"
  #define FIREWALL_program_help_parameters_s_length 9

  extern const f_string_static_t firewall_program_help_parameters_s;
#endif // _di_firewall_program_help_parameters_s_

/**
 * The firewall strings.
 */
#ifndef _di_firewall_s_
  #define FIREWALL_action_s        "action"
  #define FIREWALL_action_append_s "append"
  #define FIREWALL_action_insert_s "insert"
  #define FIREWALL_action_policy_s "policy"
  #define FIREWALL_action_none_s   "none"

  #define FIREWALL_action_append_operation_s "-A"
  #define FIREWALL_action_insert_operation_s "-I"
  #define FIREWALL_action_policy_operation_s "-P"

  #define FIREWALL_chain_s             "chain"
  #define FIREWALL_chain_forward_s     "FORWARD"
  #define FIREWALL_chain_drop_s        "DROP"
  #define FIREWALL_chain_input_s       "INPUT"
  #define FIREWALL_chain_none_s        "none"
  #define FIREWALL_chain_output_s      "OUTPUT"
  #define FIREWALL_chain_postrouting_s "POSTROUTING"
  #define FIREWALL_chain_prerouting_s  "PREROUTING"

  #define FIREWALL_chain_create_operation_s "-N"
  #define FIREWALL_chain_delete_operation_s "-X"
  #define FIREWALL_chain_flush_operation_s  "-F"

  #define FIREWALL_operation_start_s   "start"
  #define FIREWALL_operation_stop_s    "stop"
  #define FIREWALL_operation_restart_s "restart"
  #define FIREWALL_operation_lock_s    "lock"
  #define FIREWALL_operation_show_s    "show"

  #define FIREWALL_device_s      "device"
  #define FIREWALL_device_all_s  "all"
  #define FIREWALL_device_this_s "this"
  #define FIREWALL_device_loop_s "lo"

  #define FIREWALL_device_input_operation_s  "-i"
  #define FIREWALL_device_output_operation_s "-o"

  #define FIREWALL_direction_s        "direction"
  #define FIREWALL_direction_input_s  "input"
  #define FIREWALL_direction_output_s "output"
  #define FIREWALL_direction_none_s   "none"

  #define FIREWALL_group_stop_s "stop"
  #define FIREWALL_group_lock_s "lock"
  #define FIREWALL_group_main_s "main"

  #define FIREWALL_ip_list_s                    "ip_list"
  #define FIREWALL_ip_list_source_s             "source"
  #define FIREWALL_ip_list_source_action_s      "-s"
  #define FIREWALL_ip_list_destination_s        "destination"
  #define FIREWALL_ip_list_destination_action_s "-d"

  #define FIREWALL_protocol_s         "protocol"
  #define FIREWALL_protocol_operation_s "-p"
  #define FIREWALL_protocol_none_s    "none"

  #define FIREWALL_rule_s "rule"

  #define FIREWALL_show_filter_s "filter"
  #define FIREWALL_show_mangle_s "mangle"
  #define FIREWALL_show_nat_s    "nat"

  #define FIREWALL_show_parameter_exact_s   "-x"
  #define FIREWALL_show_parameter_verbose_s "-v"
  #define FIREWALL_show_parameter_table_s   "-t"
  #define FIREWALL_show_parameter_numeric_s "--numeric"
  #define FIREWALL_show_parameter_list_s    "--list"

  #define FIREWALL_tool_s            "tool"
  #define FIREWALL_tool_iptables_s   "iptables"
  #define FIREWALL_tool_ip6tables_s  "ip6tables"
  #define FIREWALL_tool_ip46tables_s "ip46tables"
  #define FIREWALL_tool_ipset_s      "ipset"

  #define FIREWALL_action_s_length        6
  #define FIREWALL_action_append_s_length 6
  #define FIREWALL_action_insert_s_length 6
  #define FIREWALL_action_policy_s_length 6
  #define FIREWALL_action_none_s_length   4

  #define FIREWALL_action_append_operation_s_length 2
  #define FIREWALL_action_insert_operation_s_length 2
  #define FIREWALL_action_policy_operation_s_length 2

  #define FIREWALL_chain_s_length             5
  #define FIREWALL_chain_forward_s_length     7
  #define FIREWALL_chain_drop_s_length        4
  #define FIREWALL_chain_input_s_length       5
  #define FIREWALL_chain_none_s_length        4
  #define FIREWALL_chain_output_s_length      6
  #define FIREWALL_chain_postrouting_s_length 12
  #define FIREWALL_chain_prerouting_s_length  11

  #define FIREWALL_chain_create_operation_s_length 2
  #define FIREWALL_chain_delete_operation_s_length 2
  #define FIREWALL_chain_flush_operation_s_length  2

  #define FIREWALL_operation_start_s_length   5
  #define FIREWALL_operation_stop_s_length    4
  #define FIREWALL_operation_restart_s_length 7
  #define FIREWALL_operation_lock_s_length    4
  #define FIREWALL_operation_show_s_length    4

  #define FIREWALL_device_s_length      6
  #define FIREWALL_device_all_s_length  3
  #define FIREWALL_device_this_s_length 4
  #define FIREWALL_device_loop_s_length 2

  #define FIREWALL_device_input_operation_s_length  2
  #define FIREWALL_device_output_operation_s_length 2

  #define FIREWALL_direction_s_length        9
  #define FIREWALL_direction_input_s_length  5
  #define FIREWALL_direction_output_s_length 6
  #define FIREWALL_direction_none_s_length   4

  #define FIREWALL_group_stop_s_length  4
  #define FIREWALL_group_lock_s_length  4
  #define FIREWALL_group_main_s_length  4

  #define FIREWALL_ip_list_s_length                    7
  #define FIREWALL_ip_list_source_s_length             6
  #define FIREWALL_ip_list_source_action_s_length      2
  #define FIREWALL_ip_list_destination_s_length        11
  #define FIREWALL_ip_list_destination_action_s_length 2

  #define FIREWALL_protocol_s_length         8
  #define FIREWALL_protocol_operation_s_length 2
  #define FIREWALL_protocol_none_s_length    4

  #define FIREWALL_rule_s_length 4

  #define FIREWALL_show_filter_s_length 6
  #define FIREWALL_show_mangle_s_length 6
  #define FIREWALL_show_nat_s_length    3

  #define FIREWALL_show_parameter_exact_s_length   2
  #define FIREWALL_show_parameter_verbose_s_length 2
  #define FIREWALL_show_parameter_table_s_length   2
  #define FIREWALL_show_parameter_numeric_s_length 9
  #define FIREWALL_show_parameter_list_s_length    6

  #define FIREWALL_tool_s_length            4
  #define FIREWALL_tool_iptables_s_length   8
  #define FIREWALL_tool_ip6tables_s_length  9
  #define FIREWALL_tool_ip46tables_s_length 10
  #define FIREWALL_tool_ipset_s_length      5

  extern const f_string_static_t firewall_action_s;
  extern const f_string_static_t firewall_action_append_s;
  extern const f_string_static_t firewall_action_insert_s;
  extern const f_string_static_t firewall_action_policy_s;
  extern const f_string_static_t firewall_action_none_s;

  extern const f_string_static_t firewall_action_append_operation_s;
  extern const f_string_static_t firewall_action_insert_operation_s;
  extern const f_string_static_t firewall_action_policy_operation_s;

  extern const f_string_static_t firewall_chain_s;
  extern const f_string_static_t firewall_chain_forward_s;
  extern const f_string_static_t firewall_chain_drop_s;
  extern const f_string_static_t firewall_chain_input_s;
  extern const f_string_static_t firewall_chain_none_s;
  extern const f_string_static_t firewall_chain_output_s;
  extern const f_string_static_t firewall_chain_postrouting_s;
  extern const f_string_static_t firewall_chain_prerouting_s;

  extern const f_string_static_t firewall_chain_create_operation_s;
  extern const f_string_static_t firewall_chain_delete_operation_s;
  extern const f_string_static_t firewall_chain_flush_operation_s;

  extern const f_string_static_t firewall_operation_start_s;
  extern const f_string_static_t firewall_operation_stop_s;
  extern const f_string_static_t firewall_operation_restart_s;
  extern const f_string_static_t firewall_operation_lock_s;
  extern const f_string_static_t firewall_operation_show_s;

  extern const f_string_static_t firewall_device_s;
  extern const f_string_static_t firewall_device_all_s;
  extern const f_string_static_t firewall_device_this_s;
  extern const f_string_static_t firewall_device_loop_s;

  extern const f_string_static_t firewall_device_input_operation_s;
  extern const f_string_static_t firewall_device_output_operation_s;

  extern const f_string_static_t firewall_direction_s;
  extern const f_string_static_t firewall_direction_input_s;
  extern const f_string_static_t firewall_direction_output_s;
  extern const f_string_static_t firewall_direction_none_s;

  extern const f_string_static_t firewall_group_stop_s;
  extern const f_string_static_t firewall_group_lock_s;
  extern const f_string_static_t firewall_group_main_s;

  extern const f_string_static_t firewall_ip_list;
  extern const f_string_static_t firewall_ip_list_source_s;
  extern const f_string_static_t firewall_ip_list_source_action_s;
  extern const f_string_static_t firewall_ip_list_destination_s;
  extern const f_string_static_t firewall_ip_list_destination_action_s;

  extern const f_string_static_t firewall_protocol_s;
  extern const f_string_static_t firewall_protocol_operation_s;
  extern const f_string_static_t firewall_protocol_none_s;

  extern const f_string_static_t firewall_rule_s;

  extern const f_string_static_t firewall_show_filter_s;
  extern const f_string_static_t firewall_show_mangle_s;
  extern const f_string_static_t firewall_show_nat_s;

  extern const f_string_static_t firewall_show_parameter_exact_s;
  extern const f_string_static_t firewall_show_parameter_verbose_s;
  extern const f_string_static_t firewall_show_parameter_table_s;
  extern const f_string_static_t firewall_show_parameter_numeric_s;
  extern const f_string_static_t firewall_show_parameter_list_s;

  extern const f_string_static_t firewall_tool_s;
  extern const f_string_static_t firewall_tool_iptables_s;
  extern const f_string_static_t firewall_tool_ip6tables_s;
  extern const f_string_static_t firewall_tool_ip46tables_s;
  extern const f_string_static_t firewall_tool_ipset_s;
#endif // _di_firewall_s_

/**
 * The main program operations.
 */
#ifndef _di_firewall_operation_s_
  #define FIREWALL_operation_start_s   "start"
  #define FIREWALL_operation_stop_s    "stop"
  #define FIREWALL_operation_restart_s "restart"
  #define FIREWALL_operation_lock_s    "lock"
  #define FIREWALL_operation_show_s    "show"

  #define FIREWALL_operation_start_s_length   5
  #define FIREWALL_operation_stop_s_length    4
  #define FIREWALL_operation_restart_s_length 7
  #define FIREWALL_operation_lock_s_length    4
  #define FIREWALL_operation_show_s_length    4

  extern const f_string_static_t firewall_operation_start_s;
  extern const f_string_static_t firewall_operation_stop_s;
  extern const f_string_static_t firewall_operation_restart_s;
  extern const f_string_static_t firewall_operation_lock_s;
  extern const f_string_static_t firewall_operation_show_s;
#endif // _di_firewall_operation_s_

/**
 * The program paths.
 */
#ifndef _di_firewall_path_s_
  #define FIREWALL_file_first_s  "firewall-first"
  #define FIREWALL_file_last_s   "firewall-last"
  #define FIREWALL_file_other_s  "firewall-other"
  #define FIREWALL_file_suffix_s "-firewall"

  #define FIREWALL_network_path_s    "/etc/network/"
  #define FIREWALL_network_devices_s "/sys/class/net/"

  #define FIREWALL_file_first_s_length   14
  #define FIREWALL_file_last_s_length    13
  #define FIREWALL_file_other_s_length   14
  #define FIREWALL_file_suffix_s_length  9

  #define FIREWALL_network_path_s_length    13
  #define FIREWALL_network_devices_s_length 15

  extern const f_string_static_t firewall_file_first_s;
  extern const f_string_static_t firewall_file_last_s;
  extern const f_string_static_t firewall_file_other_s;
  extern const f_string_static_t firewall_file_suffix_s;

  extern const f_string_static_t firewall_network_path_s;
  extern const f_string_static_t firewall_network_devices_s;
#endif // _di_firewall_path_s_

/**
 * The show option related strings.
 */
#ifndef _di_firewall_show_s_
  #define FIREWALL_show_filter_s "FILTER"
  #define FIREWALL_show_mangle_s "MANGLE"
  #define FIREWALL_show_nat_s    "NAT"

  #define FIREWALL_show_bars_26_s "=========================="
  #define FIREWALL_show_bars_27_s "============================"
  #define FIREWALL_show_bars_28_s "============================"

  #define FIREWALL_show_filter_s_length 6
  #define FIREWALL_show_mangle_s_length 6
  #define FIREWALL_show_nat_s_length    3

  #define FIREWALL_show_bars_26_s_length 26
  #define FIREWALL_show_bars_27_s_length 27
  #define FIREWALL_show_bars_28_s_length 28

  extern const f_string_static_t firewall_show_filter_s;
  extern const f_string_static_t firewall_show_mangle_s;
  extern const f_string_static_t firewall_show_nat_s;

  extern const f_string_static_t firewall_show_bars_26_s;
  extern const f_string_static_t firewall_show_bars_27_s;
  extern const f_string_static_t firewall_show_bars_28_s;
#endif // _di_firewall_show_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_common_string_h

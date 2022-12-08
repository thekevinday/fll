/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_common_h
#define _firewall_common_h

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
  #define FIREWALL_program_help_parameters_s "command"
  #define FIREWALL_program_help_parameters_s_length 7

  extern const f_string_static_t firewall_program_help_parameters_s;
#endif // _di_firewall_program_help_parameters_s_

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
 * Default allocations.
 */
#ifndef _di_firewall_default_d_
  #define firewall_default_allocation_step_d F_memory_default_allocation_small_d
#endif // _di_firewall_default_d_

/**
 * The program defines.
 */
#ifndef _di_firewall_d_
  #define firewall_signal_check_d 20000
#endif // _di_firewall_d_

/**
 * The main program parameters.
 */
#ifndef _di_firewall_parameter_d_
  #define FIREWALL_action_s        "action"
  #define FIREWALL_action_append_s "append"
  #define FIREWALL_action_insert_s "insert"
  #define FIREWALL_action_policy_s "policy"
  #define FIREWALL_action_none_s   "none"

  #define FIREWALL_action_append_command_s "-A"
  #define FIREWALL_action_insert_command_s "-I"
  #define FIREWALL_action_policy_command_s "-P"

  #define FIREWALL_chain_s             "chain"
  #define FIREWALL_chain_forward_s     "FORWARD"
  #define FIREWALL_chain_drop_s        "DROP"
  #define FIREWALL_chain_input_s       "INPUT"
  #define FIREWALL_chain_none_s        "none"
  #define FIREWALL_chain_output_s      "OUTPUT"
  #define FIREWALL_chain_postrouting_s "POSTROUTING"
  #define FIREWALL_chain_prerouting_s  "PREROUTING"

  #define FIREWALL_chain_create_command_s "-N"
  #define FIREWALL_chain_delete_command_s "-X"
  #define FIREWALL_chain_flush_command_s  "-F"

  #define FIREWALL_command_start_s   "start"
  #define FIREWALL_command_stop_s    "stop"
  #define FIREWALL_command_restart_s "restart"
  #define FIREWALL_command_lock_s    "lock"
  #define FIREWALL_command_show_s    "show"

  #define FIREWALL_device_s      "device"
  #define FIREWALL_device_all_s  "all"
  #define FIREWALL_device_this_s "this"
  #define FIREWALL_device_loop_s "lo"

  #define FIREWALL_device_input_command_s  "-i"
  #define FIREWALL_device_output_command_s "-o"

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
  #define FIREWALL_protocol_command_s "-p"
  #define FIREWALL_protocol_none_s    "none"

  #define FIREWALL_rule_s "rule"

  #define FIREWALL_show_mangle_s "mangle"
  #define FIREWALL_show_nat_s    "nat"
  #define FIREWALL_show_ports_s  "ports"

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

  #define FIREWALL_action_append_command_s_length 2
  #define FIREWALL_action_insert_command_s_length 2
  #define FIREWALL_action_policy_command_s_length 2

  #define FIREWALL_chain_s_length             5
  #define FIREWALL_chain_forward_s_length     7
  #define FIREWALL_chain_drop_s_length        4
  #define FIREWALL_chain_input_s_length       5
  #define FIREWALL_chain_none_s_length        4
  #define FIREWALL_chain_output_s_length      6
  #define FIREWALL_chain_postrouting_s_length 12
  #define FIREWALL_chain_prerouting_s_length  11

  #define FIREWALL_chain_create_command_s_length 2
  #define FIREWALL_chain_delete_command_s_length 2
  #define FIREWALL_chain_flush_command_s_length  2

  #define FIREWALL_command_start_s_length   5
  #define FIREWALL_command_stop_s_length    4
  #define FIREWALL_command_restart_s_length 7
  #define FIREWALL_command_lock_s_length    4
  #define FIREWALL_command_show_s_length    4

  #define FIREWALL_device_s_length      6
  #define FIREWALL_device_all_s_length  3
  #define FIREWALL_device_this_s_length 4
  #define FIREWALL_device_loop_s_length 2

  #define FIREWALL_device_input_command_s_length  2
  #define FIREWALL_device_output_command_s_length 2

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
  #define FIREWALL_protocol_command_s_length 2
  #define FIREWALL_protocol_none_s_length    4

  #define FIREWALL_rule_s_length 4

  #define FIREWALL_show_mangle_s_length 6
  #define FIREWALL_show_nat_s_length    3
  #define FIREWALL_show_ports_s_length  5

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

  extern const f_string_static_t firewall_action_append_command_s;
  extern const f_string_static_t firewall_action_insert_command_s;
  extern const f_string_static_t firewall_action_policy_command_s;

  extern const f_string_static_t firewall_chain_s;
  extern const f_string_static_t firewall_chain_forward_s;
  extern const f_string_static_t firewall_chain_drop_s;
  extern const f_string_static_t firewall_chain_input_s;
  extern const f_string_static_t firewall_chain_none_s;
  extern const f_string_static_t firewall_chain_output_s;
  extern const f_string_static_t firewall_chain_postrouting_s;
  extern const f_string_static_t firewall_chain_prerouting_s;

  extern const f_string_static_t firewall_chain_create_command_s;
  extern const f_string_static_t firewall_chain_delete_command_s;
  extern const f_string_static_t firewall_chain_flush_command_s;

  extern const f_string_static_t firewall_command_start_s;
  extern const f_string_static_t firewall_command_stop_s;
  extern const f_string_static_t firewall_command_restart_s;
  extern const f_string_static_t firewall_command_lock_s;
  extern const f_string_static_t firewall_command_show_s;

  extern const f_string_static_t firewall_device_s;
  extern const f_string_static_t firewall_device_all_s;
  extern const f_string_static_t firewall_device_this_s;
  extern const f_string_static_t firewall_device_loop_s;

  extern const f_string_static_t firewall_device_input_command_s;
  extern const f_string_static_t firewall_device_output_command_s;

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
  extern const f_string_static_t firewall_protocol_command_s;
  extern const f_string_static_t firewall_protocol_none_s;

  extern const f_string_static_t firewall_rule_s;

  extern const f_string_static_t firewall_show_mangle_s;
  extern const f_string_static_t firewall_show_nat_s;
  extern const f_string_static_t firewall_show_ports_s;

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

  enum {
    firewall_program_none_e = 1,
    firewall_program_iptables_e,
    firewall_program_ip6tables_e,
    firewall_program_ip46tables_e,
    firewall_program_ipset_e,
  }; // enum

  enum {
    firewall_parameter_help_e,
    firewall_parameter_light_e,
    firewall_parameter_dark_e,
    firewall_parameter_no_color_e,
    firewall_parameter_verbosity_quiet_e,
    firewall_parameter_verbosity_error_e,
    firewall_parameter_verbosity_normal_e,
    firewall_parameter_verbosity_verbose_e,
    firewall_parameter_verbosity_debug_e,
    firewall_parameter_version_e,
    firewall_parameter_line_first_no_e,
    firewall_parameter_line_last_no_e,

    firewall_parameter_command_start_e,
    firewall_parameter_command_stop_e,
    firewall_parameter_command_restart_e,
    firewall_parameter_command_lock_e,
    firewall_parameter_command_show_e,

    firewall_direction_input_id_e,
    firewall_direction_output_id_e,
    firewall_direction_none_id_e,

    firewall_chain_forward_id_e,
    firewall_chain_custom_id_e,
    firewall_chain_input_id_e,
    firewall_chain_none_id_e,
    firewall_chain_output_id_e,
    firewall_chain_postrouting_id_e,
    firewall_chain_prerouting_id_e,

    firewall_action_append_id_e,
    firewall_action_insert_id_e,
    firewall_action_policy_id_e,
    firewall_action_none_id_e,
  }; // enum

  #define firewall_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize4(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize2(0, 0, firewall_command_start_s.string, F_false, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize2(0, 0, firewall_command_stop_s.string, F_false, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize2(0, 0, firewall_command_restart_s.string, F_false, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize2(0, 0, firewall_command_lock_s.string, F_false, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize2(0, 0, firewall_command_show_s.string, F_false, f_console_flag_simple_e), \
    }

  #define firewall_total_parameters_d 17
#endif // _di_firewall_parameter_d_

/**
 * Flags used to represent flags passed to the main function.
 *
 * firewall_main_flag_*_e:
 *   - none:          No modes in use.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file.
 *   - help:          Print help.
 *   - header:        Enable printing of headers.
 *   - separate:      Enable printing of separators.
 *   - strip_invalid: Using strip invalid character mode.
 *   - verify:        Using verify mode.
 *   - version:       Print version.
 */
#ifndef _di_firewall_main_flag_e_
  enum {
    firewall_main_flag_none_e          = 0x0,
    firewall_main_flag_file_from_e     = 0x1,
    firewall_main_flag_file_to_e       = 0x2,
    firewall_main_flag_header_e        = 0x4,
    firewall_main_flag_help_e          = 0x8,
    firewall_main_flag_separate_e      = 0x10,
    firewall_main_flag_strip_invalid_e = 0x20,
    firewall_main_flag_verify_e        = 0x40,
    firewall_main_flag_version_e       = 0x80,
  }; // enum
#endif // _di_firewall_main_flag_e_

/**
 * The firewall main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status: The main status code, generally used by the load settings and main functions.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 */
#ifndef _di_firewall_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;
  } firewall_setting_t;

  #define firewall_setting_t_initialize \
    { \
      firewall_main_flag_none_e, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }
#endif // _di_firewall_setting_t_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_firewall_setting_delete_
  extern f_status_t firewall_setting_delete(firewall_setting_t * const setting);
#endif // _di_firewall_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately retuns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_firewall_setting_load_
  extern void firewall_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, firewall_setting_t * const setting);
#endif // _di_firewall_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_firewall_setting_unload_
  extern f_status_t firewall_setting_unload(fll_program_data_t * const main, firewall_setting_t * const setting);
#endif // _di_firewall_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_common_h

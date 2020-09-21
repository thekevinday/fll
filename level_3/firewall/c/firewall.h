/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the Kevux Operating System Firewall program.
 * This program utilizes the Featureless Linux Library.
 * This program processes firewall commands and passes them to iptables from netfiler.org.
 */
#ifndef _firewall_h

// libc includes
#include <dirent.h>
#include <stdio.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/type_array.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/execute.h>
#include <level_2/fss_basic.h>
#include <level_2/fss_basic_list.h>
#include <level_2/fss_extended.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_version_
  #define firewall_major_version "0"
  #define firewall_minor_version "5"
  #define firewall_micro_version "1"
  #define firewall_version firewall_major_version "." firewall_minor_version "." firewall_micro_version
#endif // _di_firewall_version_

#ifndef _di_firewall_name_
  #define firewall_name      "firewall"
  #define firewall_name_long "Kevux Firewall Manager"
#endif // _di_firewall_name_

#ifndef _di_firewall_paths_
  #define network_path          "/etc/network/" // TODO: this should be moved to a network project library, possibly the Paths project in fot the network project
  #define network_devices       "/sys/class/net/" // TODO: this should also be moved to a network project library
  #define firewall_file_first   "firewall-first"
  #define firewall_file_last    "firewall-last"
  #define firewall_file_other   "firewall-other"
  #define firewall_file_suffix  "-firewall"

  #define network_path_length          13
  #define network_devices_length       15
  #define firewall_file_first_length   14
  #define firewall_file_last_length    13
  #define firewall_file_other_length   14
  #define firewall_file_suffix_length  9
#endif // _di_firewall_paths_

#ifndef _di_firewall_default_allocation_step_
  #define firewall_default_allocation_step f_memory_default_allocation_step
#endif // _di_firewall_default_allocation_step_

#ifndef _di_firewall_defines_
  #define firewall_tool            "tool"
  #define firewall_tool_iptables   "iptables"
  #define firewall_tool_ip6tables  "ip6tables"
  #define firewall_tool_ip46tables "ip46tables"
  #define firewall_tool_ipset      "ipset"

  #define firewall_tool_length            4
  #define firewall_tool_iptables_length   8
  #define firewall_tool_ip6tables_length  9
  #define firewall_tool_ip46tables_length 10
  #define firewall_tool_ipset_length      5

  #define firewall_group_stop "stop"
  #define firewall_group_lock "lock"
  #define firewall_group_main "main"

  #define firewall_group_stop_length  4
  #define firewall_group_lock_length  4
  #define firewall_group_main_length  4

  #define firewall_command_start   "start"
  #define firewall_command_stop    "stop"
  #define firewall_command_restart "restart"
  #define firewall_command_lock    "lock"
  #define firewall_command_show    "show"

  #define firewall_ip_list                    "ip_list"
  #define firewall_ip_list_source             "source"
  #define firewall_ip_list_source_action      "-s"
  #define firewall_ip_list_destination        "destination"
  #define firewall_ip_list_destination_action "-d"

  #define firewall_ip_list_length                    7
  #define firewall_ip_list_source_length             6
  #define firewall_ip_list_source_action_length      2
  #define firewall_ip_list_destination_length        11
  #define firewall_ip_list_destination_action_length 2

  #define firewall_rule        "rule"
  #define firewall_rule_length 4

  #define firewall_chain             "chain"
  #define firewall_chain_forward     "FORWARD"
  #define firewall_chain_input       "INPUT"
  #define firewall_chain_none        "none"
  #define firewall_chain_output      "OUTPUT"
  #define firewall_chain_postrouting "POSTROUTING"
  #define firewall_chain_prerouting  "PREROUTING"

  #define firewall_chain_length             5
  #define firewall_chain_forward_length     7
  #define firewall_chain_input_length       5
  #define firewall_chain_none_length        4
  #define firewall_chain_output_length      6
  #define firewall_chain_postrouting_length 12
  #define firewall_chain_prerouting_length  11

  #define firewall_direction        "direction"
  #define firewall_direction_input  "input"
  #define firewall_direction_output "output"
  #define firewall_direction_none   "none"

  #define firewall_direction_length        9
  #define firewall_direction_input_length  5
  #define firewall_direction_output_length 6
  #define firewall_direction_none_length   4

  #define firewall_action        "action"
  #define firewall_action_append "append"
  #define firewall_action_insert "insert"
  #define firewall_action_policy "policy"
  #define firewall_action_none   "none"

  #define firewall_action_length        6
  #define firewall_action_append_length 6
  #define firewall_action_insert_length 6
  #define firewall_action_policy_length 6
  #define firewall_action_none_length   4

  #define firewall_action_append_command "-A"
  #define firewall_action_insert_command "-I"
  #define firewall_action_policy_command "-P"

  #define firewall_action_append_command_length 2
  #define firewall_action_insert_command_length 2
  #define firewall_action_policy_command_length 2

  #define firewall_device      "device"
  #define firewall_device_all  "all"
  #define firewall_device_this "this"
  #define firewall_device_loop "lo"

  #define firewall_device_length      6
  #define firewall_device_all_length  3
  #define firewall_device_this_length 4
  #define firewall_device_loop_length 2

  #define firewall_device_input_command  "-i"
  #define firewall_device_output_command "-o"

  #define firewall_device_input_command_length  2
  #define firewall_device_output_command_length 2

  #define firewall_protocol      "protocol"
  #define firewall_protocol_none "none"

  #define firewall_protocol_length      8
  #define firewall_protocol_none_length 4

  #define firewall_protocol_command        "-p"
  #define firewall_protocol_command_length 2

  #define firewall_chain_create_command "-N"
  #define firewall_chain_delete_command "-X"

  #define firewall_chain_create_command_length 2
  #define firewall_chain_delete_command_length 2

  enum {
    firewall_program_none = 1,
    firewall_program_iptables,
    firewall_program_ip6tables,
    firewall_program_ip46tables,
    firewall_program_ipset,
  };

  enum {
    firewall_parameter_help,
    firewall_parameter_light,
    firewall_parameter_dark,
    firewall_parameter_no_color,
    firewall_parameter_version,

    #ifdef _en_firewall_debug_
      firewall_parameter_debug,
    #endif // _en_firewall_debug_

    firewall_parameter_command_start,
    firewall_parameter_command_stop,
    firewall_parameter_command_restart,
    firewall_parameter_command_lock,
    firewall_parameter_command_show,

    firewall_direction_input_id,
    firewall_direction_output_id,
    firewall_direction_none_id,

    firewall_chain_forward_id,
    firewall_chain_custom_id,
    firewall_chain_input_id,
    firewall_chain_none_id,
    firewall_chain_output_id,
    firewall_chain_postrouting_id,
    firewall_chain_prerouting_id,

    firewall_action_append_id,
    firewall_action_insert_id,
    firewall_action_policy_id,
    firewall_action_none_id,
  };

  #ifdef _en_firewall_debug_
    #define firewall_console_parameter_t_initialize \
      { \
        f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, F_false, f_console_type_normal), \
        f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(0, 0, firewall_command_start, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_stop, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_restart, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_lock, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_show, F_false, f_console_type_other), \
      }

    #define firewall_total_parameters 11
  #else
    #define firewall_console_parameter_t_initialize \
      { \
        f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, F_false, f_console_type_normal), \
        f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, F_false, f_console_type_inverse), \
        f_console_parameter_t_initialize(0, 0, firewall_command_start, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_stop, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_restart, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_lock, F_false, f_console_type_other), \
        f_console_parameter_t_initialize(0, 0, firewall_command_show, F_false, f_console_type_other), \
      }

    #define firewall_total_parameters 10
  #endif // _en_firewall_debug_
#endif // _di_firewall_defines_

#ifndef _di_firewall_data_t_
  typedef struct {
    f_console_parameter_t parameters[firewall_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    uint8_t verbosity;

    f_string_dynamics_t chains;
    f_string_dynamics_t devices;

    f_color_context_t context;
  } firewall_data_t;

  #define firewall_data_t_initialize \
    { \
      firewall_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_console_verbosity_normal, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_firewall_data_t_

/**
 * Print help to standard output.
 *
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_firewall_print_help_
  extern f_return_status firewall_print_help(const f_color_context_t context);
#endif // _di_firewall_print_help_

/**
 * Execute main program.
 *
 * Be sure to call firewall_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see firewall_delete_data()
 */
#ifndef _di_firewall_main_
  extern f_return_status firewall_main(const f_console_arguments_t arguments, firewall_data_t *data);
#endif // _di_firewall_main_

/**
 * De-allocate data.
 *
 * Be sure to call this after executing firewall_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see firewall_main()
 */
#ifndef _di_firewall_delete_data_
  extern f_return_status firewall_delete_data(firewall_data_t *data);
#endif // _di_firewall_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_h

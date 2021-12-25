/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
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
#include <unistd.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/string.h>
#include <fll/level_1/print.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/fss_basic.h>
#include <fll/level_2/fss_basic_list.h>
#include <fll/level_2/fss_extended.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_program_version_
  #define firewall_program_version_major_s F_string_ascii_0_s
  #define firewall_program_version_minor_s F_string_ascii_5_s
  #define firewall_program_version_micro_s F_string_ascii_8_s

  #ifndef firewall_program_version_nano_prefix_s
    #define firewall_program_version_nano_prefix_s
  #endif

  #ifndef firewall_program_version_nano_s
    #define firewall_program_version_nano_s
  #endif

  #define firewall_version_s firewall_program_version_major_s F_string_ascii_period_s firewall_program_version_minor_s F_string_ascii_period_s firewall_program_version_micro_s firewall_program_version_nano_prefix_s firewall_program_version_nano_s
#endif // _di_firewall_program_version_

#ifndef _di_firewall_program_name_
  #define firewall_program_name_s      "firewall"
  #define firewall_program_name_long_s "Kevux Firewall Manager"
#endif // _di_firewall_program_name_

#ifndef _di_firewall_paths_
  #define network_path_s          "/etc/network/" // TODO: this should be moved to a network project library, possibly the Paths project in fot the network project
  #define network_devices_s       "/sys/class/net/" // TODO: this should also be moved to a network project library
  #define firewall_file_first_s   "firewall-first"
  #define firewall_file_last_s    "firewall-last"
  #define firewall_file_other_s   "firewall-other"
  #define firewall_file_suffix_s  "-firewall"

  #define network_path_s_length          13
  #define network_devices_s_length       15
  #define firewall_file_first_s_length   14
  #define firewall_file_last_s_length    13
  #define firewall_file_other_s_length   14
  #define firewall_file_suffix_s_length  9
#endif // _di_firewall_paths_

#ifndef _di_firewall_default_allocation_step_
  #define firewall_default_allocation_step_d F_memory_default_allocation_small_d
#endif // _di_firewall_default_allocation_step_

#ifndef _di_firewall_defines_
  #define firewall_signal_check_d 10000

  #define firewall_tool_s            "tool"
  #define firewall_tool_iptables_s   "iptables"
  #define firewall_tool_ip6tables_s  "ip6tables"
  #define firewall_tool_ip46tables_s "ip46tables"
  #define firewall_tool_ipset_s      "ipset"

  #define firewall_tool_s_length            4
  #define firewall_tool_iptables_s_length   8
  #define firewall_tool_ip6tables_s_length  9
  #define firewall_tool_ip46tables_s_length 10
  #define firewall_tool_ipset_s_length      5

  #define firewall_group_stop_s "stop"
  #define firewall_group_lock_s "lock"
  #define firewall_group_main_s "main"

  #define firewall_group_stop_s_length  4
  #define firewall_group_lock_s_length  4
  #define firewall_group_main_s_length  4

  #define firewall_command_start_s   "start"
  #define firewall_command_stop_s    "stop"
  #define firewall_command_restart_s "restart"
  #define firewall_command_lock_s    "lock"
  #define firewall_command_show_s    "show"

  #define firewall_command_start_s_length   5
  #define firewall_command_stop_s_length    4
  #define firewall_command_restart_s_length 7
  #define firewall_command_lock_s_length    4
  #define firewall_command_show_s_length    4

  #define firewall_ip_list                    "ip_list"
  #define firewall_ip_list_source_s             "source"
  #define firewall_ip_list_source_action_s      "-s"
  #define firewall_ip_list_destination_s        "destination"
  #define firewall_ip_list_destination_action_s "-d"

  #define firewall_ip_list_length_s                    7
  #define firewall_ip_list_source_s_length             6
  #define firewall_ip_list_source_action_s_length      2
  #define firewall_ip_list_destination_s_length        11
  #define firewall_ip_list_destination_action_s_length 2

  #define firewall_rule_s        "rule"
  #define firewall_rule_s_length 4

  #define firewall_chain_s             "chain"
  #define firewall_chain_forward_s     "FORWARD"
  #define firewall_chain_input_s       "INPUT"
  #define firewall_chain_none_s        "none"
  #define firewall_chain_output_s      "OUTPUT"
  #define firewall_chain_postrouting_s "POSTROUTING"
  #define firewall_chain_prerouting_s  "PREROUTING"

  #define firewall_chain_length_s             5
  #define firewall_chain_forward_s_length     7
  #define firewall_chain_input_s_length       5
  #define firewall_chain_none_s_length        4
  #define firewall_chain_output_s_length      6
  #define firewall_chain_postrouting_s_length 12
  #define firewall_chain_prerouting_s_length  11

  #define firewall_direction_s        "direction"
  #define firewall_direction_input_s  "input"
  #define firewall_direction_output_s "output"
  #define firewall_direction_none_s   "none"

  #define firewall_direction_s_length        9
  #define firewall_direction_input_s_length  5
  #define firewall_direction_output_s_length 6
  #define firewall_direction_none_s_length   4

  #define firewall_action_s        "action"
  #define firewall_action_append_s "append"
  #define firewall_action_insert_s "insert"
  #define firewall_action_policy_s "policy"
  #define firewall_action_none_s   "none"

  #define firewall_action_length_s        6
  #define firewall_action_append_s_length 6
  #define firewall_action_insert_s_length 6
  #define firewall_action_policy_s_length 6
  #define firewall_action_none_s_length   4

  #define firewall_action_append_command_s "-A"
  #define firewall_action_insert_command_s "-I"
  #define firewall_action_policy_command_s "-P"

  #define firewall_action_append_command_s_length 2
  #define firewall_action_insert_command_s_length 2
  #define firewall_action_policy_command_s_length 2

  #define firewall_device_s      "device"
  #define firewall_device_all_s  "all"
  #define firewall_device_this_s "this"
  #define firewall_device_loop_s "lo"

  #define firewall_device_s_length      6
  #define firewall_device_all_s_length  3
  #define firewall_device_this_s_length 4
  #define firewall_device_loop_s_length 2

  #define firewall_device_input_command_s  "-i"
  #define firewall_device_output_command_s "-o"

  #define firewall_device_input_command_length_s  2
  #define firewall_device_output_command_length_s 2

  #define firewall_protocol_s      "protocol"
  #define firewall_protocol_none_s "none"

  #define firewall_protocol_s_length      8
  #define firewall_protocol_none_s_length 4

  #define firewall_protocol_command_s        "-p"
  #define firewall_protocol_command_s_length 2

  #define firewall_chain_create_command_s "-N"
  #define firewall_chain_delete_command_s "-X"

  #define firewall_chain_create_command_s_length 2
  #define firewall_chain_delete_command_s_length 2

  enum {
    firewall_program_none_e = 1,
    firewall_program_iptables_e,
    firewall_program_ip6tables_e,
    firewall_program_ip46tables_e,
    firewall_program_ipset_e,
  };

  enum {
    firewall_parameter_help_e,
    firewall_parameter_light_e,
    firewall_parameter_dark_e,
    firewall_parameter_no_color_e,
    firewall_parameter_verbosity_quiet_e,
    firewall_parameter_verbosity_normal_e,
    firewall_parameter_verbosity_verbose_e,
    firewall_parameter_verbosity_debug_e,
    firewall_parameter_version_e,

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
  };

  #define firewall_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal_e), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse_e), \
      f_console_parameter_t_initialize(0, 0, firewall_command_start_s, F_false, f_console_type_other_e), \
      f_console_parameter_t_initialize(0, 0, firewall_command_stop_s, F_false, f_console_type_other_e), \
      f_console_parameter_t_initialize(0, 0, firewall_command_restart_s, F_false, f_console_type_other_e), \
      f_console_parameter_t_initialize(0, 0, firewall_command_lock_s, F_false, f_console_type_other_e), \
      f_console_parameter_t_initialize(0, 0, firewall_command_show_s, F_false, f_console_type_other_e), \
    }

  #define firewall_total_parameters_d 14
#endif // _di_firewall_defines_

#ifndef _di_firewall_main_t_
  typedef struct {
    f_console_parameter_t parameters[firewall_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_string_dynamics_t chains;
    f_string_dynamics_t devices;

    f_color_context_t context;
  } firewall_main_t;

  #define firewall_main_t_initialize \
    { \
      firewall_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_firewall_main_t_

/**
 * Print help.
 *
 * @param file
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_firewall_print_help_
  extern f_status_t firewall_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_firewall_print_help_

/**
 * Execute main program.
 *
 * Be sure to call firewall_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 * - F_signal_abort
 * - F_signal_broken_pipe
 * - F_signal_hangup
 * - F_signal_interrupt
 * - F_signal_quit
 * - F_signal_termination
 *
 * @param data
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see firewall_main_delete()
 */
#ifndef _di_firewall_main_
  extern f_status_t firewall_main(firewall_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_firewall_main_

/**
 * De-allocate data.
 *
 * Be sure to call this after executing firewall_main().
 *
 * @param data
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see firewall_main()
 */
#ifndef _di_firewall_main_delete_
  extern f_status_t firewall_main_delete(firewall_main_t * const data);
#endif // _di_firewall_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_h

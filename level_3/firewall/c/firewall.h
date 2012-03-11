/* FLL - Level 3
 * Project:       Firewall
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This is the Kevux Operating System Firewall program.
 * This program utilizes the Featureless Linux Library.
 * This program processes firewall commands and passes them to iptables from netfiler.org
 */
#ifndef _firewall_h

// libc includes
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>
#include <level_0/file.h>
#include <level_0/console.h>
#include <level_0/output.h>

// fll-1 includes
#include <level_1/colors.h>
#include <level_1/console.h>
#include <level_1/file.h>
#include <level_1/strings.h>
#include <level_1/directory.h>

// fll-2 includes
#include <level_2/execute.h>
#include <level_2/fss_basic.h>
#include <level_2/fss_basic_list.h>
#include <level_2/fss_extended.h>
#include <level_2/colors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_firewall_version_
  #define firewall_major_version "0"
  #define firewall_minor_version "3"
  #define firewall_micro_version "0"
  #define firewall_version firewall_major_version "." firewall_minor_version "." firewall_micro_version
#endif // _di_firewall_version_

#ifndef _di_firewall_name_
  #define firewall_name "firewall"
  #define firewall_name_long "Kevux Firewall Manager"
#endif // _di_firewall_name_

#ifndef _di_firewall_paths_
  #define network_path          "/etc/network/" // TODO: this should be moved to a network project library, possibly the Paths project in fot the network project
  #define network_devices       "/sys/class/net/" // TODO: this should also be moved to a network project library
  #define firewall_file_default "default-firewall"
  #define firewall_file_suffix  "-firewall"
  #define firewall_program_name "iptables"

  #define network_path_length          13
  #define network_devices_length       15
  #define firewall_file_default_length 16
  #define firewall_file_suffix_length  9
  #define firewall_program_length      8
  #define firewall_program_name_length 8
#endif // _di_firewall_paths_

#ifndef _di_firewall_defines_
  #define firewall_group_first "first"
  #define firewall_group_last "last"
  #define firewall_group_stop "stop"
  #define firewall_group_lock "lock"
  #define firewall_group_main "main"

  #define firewall_group_first_length 5
  #define firewall_group_last_length  4
  #define firewall_group_stop_length  4
  #define firewall_group_lock_length  4
  #define firewall_group_main_length  4

  #define firewall_command_start   "start"
  #define firewall_command_stop    "stop"
  #define firewall_command_restart "restart"
  #define firewall_command_lock    "lock"
  #define firewall_command_show    "show"

  #define firewall_command_start_length   5
  #define firewall_command_stop_length    4
  #define firewall_command_restart_length 7
  #define firewall_command_lock_length    4
  #define firewall_command_show_length    4

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

  #define firewall_direction             "direction"
  #define firewall_direction_input       "input"
  #define firewall_direction_output      "output"
  #define firewall_direction_forward     "forward"
  #define firewall_direction_postrouting "postrouting"
  #define firewall_direction_prerouting  "prerouting"
  #define firewall_direction_none        "none"

  #define firewall_direction_length             9
  #define firewall_direction_input_length       5
  #define firewall_direction_output_length      6
  #define firewall_direction_forward_length     7
  #define firewall_direction_postrouting_length 12
  #define firewall_direction_prerouting_length  11
  #define firewall_direction_none_length        4

  #define firewall_direction_forward_input      "forward-input"
  #define firewall_direction_forward_output     "forward-output"
  #define firewall_direction_postrouting_input  "postrouting-input"
  #define firewall_direction_postrouting_output "postrouting-output"
  #define firewall_direction_prerouting_input   "prerouting-input"
  #define firewall_direction_prerouting_output  "prerouting-output"

  #define firewall_direction_forward_input_length      13
  #define firewall_direction_forward_output_length     14
  #define firewall_direction_postrouting_input_length  17
  #define firewall_direction_postrouting_output_length 18
  #define firewall_direction_prerouting_input_length   16
  #define firewall_direction_prerouting_output_length  17

  #define firewall_direction_input_command       "INPUT"
  #define firewall_direction_output_command      "OUTPUT"
  #define firewall_direction_forward_command     "FORWARD"
  #define firewall_direction_postrouting_command "POSTROUTING"
  #define firewall_direction_prerouting_command  "PREROUTING"

  #define firewall_direction_input_command_length       5
  #define firewall_direction_output_command_length      6
  #define firewall_direction_forward_command_length     7
  #define firewall_direction_postrouting_command_length 12
  #define firewall_direction_prerouting_command_length  11

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

  #define firewall_device_length      6
  #define firewall_device_all_length  3
  #define firewall_device_this_length 4

  #define firewall_device_input_command  "-i"
  #define firewall_device_output_command "-o"

  #define firewall_device_input_command_length  2
  #define firewall_device_output_command_length 2

  enum {
    firewall_parameter_help,
    firewall_parameter_light,
    firewall_parameter_no_color,
    firewall_parameter_version,
    firewall_parameter_command_start,
    firewall_parameter_command_stop,
    firewall_parameter_command_restart,
    firewall_parameter_command_lock,
    firewall_parameter_command_show,

    firewall_direction_forward_id,
    firewall_direction_postrouting_id,
    firewall_direction_prerouting_id,
    firewall_direction_none_id,

    firewall_action_append_id,
    firewall_action_insert_id,
    firewall_action_policy_id,
    firewall_action_none_id,
  };

  #define f_console_parameter_initialize_firewall \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_false, f_console_type_inverse, 0), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_false, f_console_type_normal, 0), \
      f_console_parameter_initialize(0, 0, 0, firewall_command_start, f_false, f_console_type_other, firewall_command_start_length), \
      f_console_parameter_initialize(0, 0, 0, firewall_command_stop, f_false, f_console_type_other, firewall_command_stop_length), \
      f_console_parameter_initialize(0, 0, 0, firewall_command_restart, f_false, f_console_type_other, firewall_command_restart_length), \
      f_console_parameter_initialize(0, 0, 0, firewall_command_lock, f_false, f_console_type_other, firewall_command_lock_length), \
      f_console_parameter_initialize(0, 0, 0, firewall_command_show, f_false, f_console_type_other, firewall_command_show_length), \
    }

  #define firewall_total_parameters 9
#endif // _di_firewall_defines_

#ifndef _di_firewall_data_
  typedef struct {
    f_console_parameter parameters[firewall_total_parameters];

    f_dynamic_string  buffer;
    f_fss_objects     objects;
    f_fss_contents    contents;
    f_file_position   file_position;
    f_string_lengths  remaining;
    f_dynamic_strings devices;

    fll_color_context context;
  } firewall_data;

  #define firewall_data_initialize \
    { \
      f_console_parameter_initialize_firewall, \
      f_dynamic_string_initialize, \
      f_fss_objects_initialize, \
      f_fss_contents_initialize, \
      f_file_position_initialize, \
      f_string_lengths_initialize, \
      f_dynamic_strings_initialize, \
      fll_color_context_initialize, \
    }
#endif // _di_firewall_data_

#ifndef _di_firewall_print_version_
  extern f_return_status firewall_print_version(const firewall_data data);
#endif // _di_firewall_print_version_

#ifndef _di_firewall_print_help_
  extern f_return_status firewall_print_help(const firewall_data data);
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  extern f_return_status firewall_main(const f_s_int argc, const f_string argv[], firewall_data *data);
#endif // _di_firewall_main_

#ifndef _di_firewall_delete_data_
  extern f_return_status firewall_delete_data(firewall_data *data);
#endif // _di_firewall_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_h

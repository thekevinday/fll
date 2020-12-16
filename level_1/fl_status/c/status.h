/**
 * FLL - Level 1
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides status code functions, such as those that translate status codes into strings.
 */
#ifndef _FL_status_h
#define _FL_status_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_FL_status_string_
  #ifndef _di_F_status_boolean_
    #define FL_status_string_false "F_false"
    #define FL_status_string_true  "F_true"

    #define FL_status_string_false_length 7
    #define FL_status_string_true_length  6
  #endif // _di_F_status_boolean_

  #ifndef _di_F_status_signal_
    #define FL_status_string_signal_hangup               "F_signal_hangup"
    #define FL_status_string_signal_interrupt            "F_signal_interrupt"
    #define FL_status_string_signal_quit                 "F_signal_quit"
    #define FL_status_string_signal_illegal              "F_signal_illegal"
    #define FL_status_string_signal_trap                 "F_signal_trap"
    #define FL_status_string_signal_abort                "F_signal_abort"
    #define FL_status_string_signal_bus_error            "F_signal_bus_error"
    #define FL_status_string_signal_floating_point_error "F_signal_floating_point_error"
    #define FL_status_string_signal_kill                 "F_signal_kill"
    #define FL_status_string_signal_user_1               "F_signal_user_1"
    #define FL_status_string_signal_segmentation_fault   "F_signal_segmentation_fault"
    #define FL_status_string_signal_user_2               "F_signal_user_2"
    #define FL_status_string_signal_broken_pipe          "F_signal_broken_pipe"
    #define FL_status_string_signal_alarm_clock          "F_signal_alarm_clock"
    #define FL_status_string_signal_termination          "F_signal_termination"
    #define FL_status_string_signal_stack_fault          "F_signal_stack_fault"
    #define FL_status_string_signal_child                "F_signal_child"
    #define FL_status_string_signal_continue             "F_signal_continue"
    #define FL_status_string_signal_stop                 "F_signal_stop"
    #define FL_status_string_signal_keyboard_stop        "F_signal_keyboard_stop"
    #define FL_status_string_signal_tty_in               "F_signal_tty_in"
    #define FL_status_string_signal_tty_out              "F_signal_tty_out"
    #define FL_status_string_signal_urgent               "F_signal_urgent"
    #define FL_status_string_signal_cpu_limit            "F_signal_cpu_limit"
    #define FL_status_string_signal_file_size_limit      "F_signal_file_size_limit"
    #define FL_status_string_signal_virtual_alarm_clock  "F_signal_virtual_alarm_clock"
    #define FL_status_string_signal_profile_alarm_clock  "F_signal_profile_alarm_clock"
    #define FL_status_string_signal_window_size_change   "F_signal_window_size_change"
    #define FL_status_string_signal_pollable_event       "F_signal_pollable_event"
    #define FL_status_string_signal_power_failure        "F_signal_power_failure"
    #define FL_status_string_signal_bad_system_call      "F_signal_bad_system_call"
    #define FL_status_string_signal_reserved_32          "F_signal_reserved_32"
    #define FL_status_string_signal_reserved_33          "F_signal_reserved_33"
    #define FL_status_string_signal_reserved_34          "F_signal_reserved_34"
    #define FL_status_string_signal_reserved_35          "F_signal_reserved_35"
    #define FL_status_string_signal_reserved_36          "F_signal_reserved_36"
    #define FL_status_string_signal_reserved_37          "F_signal_reserved_37"
    #define FL_status_string_signal_reserved_38          "F_signal_reserved_38"
    #define FL_status_string_signal_reserved_39          "F_signal_reserved_39"
    #define FL_status_string_signal_reserved_40          "F_signal_reserved_40"
    #define FL_status_string_signal_reserved_41          "F_signal_reserved_41"
    #define FL_status_string_signal_reserved_42          "F_signal_reserved_42"
    #define FL_status_string_signal_reserved_43          "F_signal_reserved_43"
    #define FL_status_string_signal_reserved_44          "F_signal_reserved_44"
    #define FL_status_string_signal_reserved_45          "F_signal_reserved_45"
    #define FL_status_string_signal_reserved_46          "F_signal_reserved_46"
    #define FL_status_string_signal_reserved_47          "F_signal_reserved_47"
    #define FL_status_string_signal_reserved_48          "F_signal_reserved_48"
    #define FL_status_string_signal_reserved_49          "F_signal_reserved_49"
    #define FL_status_string_signal_reserved_50          "F_signal_reserved_50"
    #define FL_status_string_signal_reserved_51          "F_signal_reserved_51"
    #define FL_status_string_signal_reserved_52          "F_signal_reserved_52"
    #define FL_status_string_signal_reserved_53          "F_signal_reserved_53"
    #define FL_status_string_signal_reserved_54          "F_signal_reserved_54"
    #define FL_status_string_signal_reserved_55          "F_signal_reserved_55"
    #define FL_status_string_signal_reserved_56          "F_signal_reserved_56"
    #define FL_status_string_signal_reserved_57          "F_signal_reserved_57"
    #define FL_status_string_signal_reserved_58          "F_signal_reserved_58"
    #define FL_status_string_signal_reserved_59          "F_signal_reserved_59"
    #define FL_status_string_signal_reserved_60          "F_signal_reserved_60"
    #define FL_status_string_signal_reserved_61          "F_signal_reserved_61"
    #define FL_status_string_signal_reserved_62          "F_signal_reserved_62"
    #define FL_status_string_signal_reserved_63          "F_signal_reserved_63"
    #define FL_status_string_signal_reserved_64          "F_signal_reserved_64"

    #define FL_status_string_signal_hangup_length               15
    #define FL_status_string_signal_interrupt_length            18
    #define FL_status_string_signal_quit_length                 13
    #define FL_status_string_signal_illegal_length              16
    #define FL_status_string_signal_trap_length                 13
    #define FL_status_string_signal_abort_length                14
    #define FL_status_string_signal_bus_error_length            17
    #define FL_status_string_signal_floating_point_error_length 33
    #define FL_status_string_signal_kill_length                 13
    #define FL_status_string_signal_user_1_length               15
    #define FL_status_string_signal_segmentation_fault_length   27
    #define FL_status_string_signal_user_2_length               15
    #define FL_status_string_signal_broken_pipe_length          20
    #define FL_status_string_signal_alarm_clock_length          20
    #define FL_status_string_signal_termination_length          20
    #define FL_status_string_signal_stack_fault_length          20
    #define FL_status_string_signal_child_length                14
    #define FL_status_string_signal_continue_length             17
    #define FL_status_string_signal_stop_length                 13
    #define FL_status_string_signal_keyboard_stop_length        22
    #define FL_status_string_signal_tty_in_length               15
    #define FL_status_string_signal_tty_out_length              16
    #define FL_status_string_signal_urgent_length               15
    #define FL_status_string_signal_cpu_limit_length            18
    #define FL_status_string_signal_file_size_limit_length      24
    #define FL_status_string_signal_virtual_alarm_clock_length  28
    #define FL_status_string_signal_profile_alarm_clock_length  28
    #define FL_status_string_signal_window_size_change_length   27
    #define FL_status_string_signal_pollable_event_length       23
    #define FL_status_string_signal_power_failure_length        22
    #define FL_status_string_signal_bad_system_call_length      24
    #define FL_status_string_signal_reserved_32_length          20
    #define FL_status_string_signal_reserved_33_length          20
    #define FL_status_string_signal_reserved_34_length          20
    #define FL_status_string_signal_reserved_35_length          20
    #define FL_status_string_signal_reserved_36_length          20
    #define FL_status_string_signal_reserved_37_length          20
    #define FL_status_string_signal_reserved_38_length          20
    #define FL_status_string_signal_reserved_39_length          20
    #define FL_status_string_signal_reserved_40_length          20
    #define FL_status_string_signal_reserved_41_length          20
    #define FL_status_string_signal_reserved_42_length          20
    #define FL_status_string_signal_reserved_43_length          20
    #define FL_status_string_signal_reserved_44_length          20
    #define FL_status_string_signal_reserved_45_length          20
    #define FL_status_string_signal_reserved_46_length          20
    #define FL_status_string_signal_reserved_47_length          20
    #define FL_status_string_signal_reserved_48_length          20
    #define FL_status_string_signal_reserved_49_length          20
    #define FL_status_string_signal_reserved_50_length          20
    #define FL_status_string_signal_reserved_51_length          20
    #define FL_status_string_signal_reserved_52_length          20
    #define FL_status_string_signal_reserved_53_length          20
    #define FL_status_string_signal_reserved_54_length          20
    #define FL_status_string_signal_reserved_55_length          20
    #define FL_status_string_signal_reserved_56_length          20
    #define FL_status_string_signal_reserved_57_length          20
    #define FL_status_string_signal_reserved_58_length          20
    #define FL_status_string_signal_reserved_59_length          20
    #define FL_status_string_signal_reserved_60_length          20
    #define FL_status_string_signal_reserved_61_length          20
    #define FL_status_string_signal_reserved_62_length          20
    #define FL_status_string_signal_reserved_63_length          20
    #define FL_status_string_signal_reserved_64_length          20
  #endif // _di_F_status_signal_

  #ifndef _di_F_status_basic_
    #define FL_status_string_none             "F_none"
    #define FL_status_string_absolute         "F_absolute"
    #define FL_status_string_absolute_not     "F_absolute_not"
    #define FL_status_string_address          "F_address"
    #define FL_status_string_address_not      "F_address_not"
    #define FL_status_string_block            "F_block"
    #define FL_status_string_block_not        "F_block_not"
    #define FL_status_string_bound            "F_bound"
    #define FL_status_string_bound_not        "F_bound_not"
    #define FL_status_string_child            "F_child"
    #define FL_status_string_child_not        "F_child_not"
    #define FL_status_string_complete         "F_complete"
    #define FL_status_string_complete_not     "F_complete_not"
    #define FL_status_string_connected        "F_connected"
    #define FL_status_string_connected_not    "F_connected_not"
    #define FL_status_string_critical         "F_critical"
    #define FL_status_string_critical_not     "F_critical_not"
    #define FL_status_string_deadlock         "F_deadlock"
    #define FL_status_string_deadlock_not     "F_deadlock_not"
    #define FL_status_string_descriptor       "F_descriptor"
    #define FL_status_string_descriptor_not   "F_descriptor_not"
    #define FL_status_string_device           "F_device"
    #define FL_status_string_device_not       "F_device_not"
    #define FL_status_string_dummy            "F_dummy"
    #define FL_status_string_dummy_not        "F_dummy_not"
    #define FL_status_string_encoding         "F_encoding"
    #define FL_status_string_encoding_not     "F_encoding_not"
    #define FL_status_string_eof              "F_eof"
    #define FL_status_string_eof_not          "F_eof_not"
    #define FL_status_string_eol              "F_eol"
    #define FL_status_string_eol_not          "F_eol_not"
    #define FL_status_string_eos              "F_eos"
    #define FL_status_string_eos_not          "F_eos_not"
    #define FL_status_string_exist            "F_exist"
    #define FL_status_string_exist_not        "F_exist_not"
    #define FL_status_string_failure          "F_failure"
    #define FL_status_string_failure_not      "F_failure_not"
    #define FL_status_string_fork             "F_fork"
    #define FL_status_string_fork_not         "F_fork_not"
    #define FL_status_string_found            "F_found"
    #define FL_status_string_found_not        "F_found_not"
    #define FL_status_string_input            "F_input"
    #define FL_status_string_input_not        "F_input_not"
    #define FL_status_string_input_output     "F_input_output"
    #define FL_status_string_interrupt        "F_interrupt"
    #define FL_status_string_interrupt_not    "F_interrupt_not"
    #define FL_status_string_known            "F_known"
    #define FL_status_string_known_not        "F_known_not"
    #define FL_status_string_link             "F_link"
    #define FL_status_string_link_not         "F_link_not"
    #define FL_status_string_lock             "F_lock"
    #define FL_status_string_lock_not         "F_lock_not"
    #define FL_status_string_loop             "F_loop"
    #define FL_status_string_loop_not         "F_loop_not"
    #define FL_status_string_maybe            "F_maybe"
    #define FL_status_string_maybe_not        "F_maybe_not"
    #define FL_status_string_minor            "F_minor"
    #define FL_status_string_minor_not        "F_minor_not"
    #define FL_status_string_moderate         "F_moderate"
    #define FL_status_string_moderate_not     "F_moderate_not"
    #define FL_status_string_mount            "F_mount"
    #define FL_status_string_mount_not        "F_mount_not"
    #define FL_status_string_name             "F_name"
    #define FL_status_string_name_not         "F_name_not"
    #define FL_status_string_optional         "F_optional"
    #define FL_status_string_optional_not     "F_optional_not"
    #define FL_status_string_output           "F_output"
    #define FL_status_string_output_not       "F_output_not"
    #define FL_status_string_parameter        "F_parameter"
    #define FL_status_string_parameter_not    "F_parameter_not"
    #define FL_status_string_parent           "F_parent"
    #define FL_status_string_parent_not       "F_parent_not"
    #define FL_status_string_pipe             "F_pipe"
    #define FL_status_string_pipe_not         "F_pipe_not"
    #define FL_status_string_port             "F_port"
    #define FL_status_string_port_not         "F_port_not"
    #define FL_status_string_prohibited       "F_prohibited"
    #define FL_status_string_prohibited_not   "F_prohibited_not"
    #define FL_status_string_range            "F_range"
    #define FL_status_string_range_not        "F_range_not"
    #define FL_status_string_read             "F_read"
    #define FL_status_string_read_not         "F_read_not"
    #define FL_status_string_read_only        "F_read_only"
    #define FL_status_string_ready            "F_ready"
    #define FL_status_string_ready_not        "F_ready_not"
    #define FL_status_string_recurse          "F_recurse"
    #define FL_status_string_recurse_not      "F_recurse_not"
    #define FL_status_string_relative         "F_relative"
    #define FL_status_string_relative_not     "F_relative_not"
    #define FL_status_string_require          "F_require"
    #define FL_status_string_require_not      "F_require_not"
    #define FL_status_string_resource         "F_resource"
    #define FL_status_string_resource_not     "F_resource_not"
    #define FL_status_string_search           "F_search"
    #define FL_status_string_search_not       "F_search_not"
    #define FL_status_string_signal           "F_signal"
    #define FL_status_string_signal_not       "F_signal_not"
    #define FL_status_string_space            "F_space"
    #define FL_status_string_space_not        "F_space_not"
    #define FL_status_string_stop             "F_stop"
    #define FL_status_string_stop_not         "F_stop_not"
    #define FL_status_string_string           "F_string"
    #define FL_status_string_string_not       "F_string_not"
    #define FL_status_string_string_too_large "F_string_too_large"
    #define FL_status_string_string_too_small "F_string_too_small"
    #define FL_status_string_syntax           "F_syntax"
    #define FL_status_string_syntax_not       "F_syntax_not"
    #define FL_status_string_supported        "F_supported"
    #define FL_status_string_supported_not    "F_supported_not"
    #define FL_status_string_utf              "F_utf"
    #define FL_status_string_utf_not          "F_utf_not"
    #define FL_status_string_valid            "F_valid"
    #define FL_status_string_valid_not        "F_valid_not"
    #define FL_status_string_value            "F_value"
    #define FL_status_string_value_not        "F_value_not"
    #define FL_status_string_wait             "F_wait"
    #define FL_status_string_wait_not         "F_wait_not"
    #define FL_status_string_warn             "F_warn"
    #define FL_status_string_warn_not         "F_warn_not"
    #define FL_status_string_write            "F_write"
    #define FL_status_string_write_not        "F_write_not"
    #define FL_status_string_write_only       "F_write_only"

    #define FL_status_string_none_length             6
    #define FL_status_string_absolute_length         10
    #define FL_status_string_absolute_not_length     14
    #define FL_status_string_address_length          9
    #define FL_status_string_address_not_length      13
    #define FL_status_string_block_length            7
    #define FL_status_string_block_not_length        11
    #define FL_status_string_bound_length            7
    #define FL_status_string_bound_not_length        11
    #define FL_status_string_child_length            7
    #define FL_status_string_child_not_length        11
    #define FL_status_string_complete_length         10
    #define FL_status_string_complete_not_length     14
    #define FL_status_string_connected_length        11
    #define FL_status_string_connected_not_length    15
    #define FL_status_string_critical_length         10
    #define FL_status_string_critical_not_length     14
    #define FL_status_string_deadlock_length         10
    #define FL_status_string_deadlock_not_length     14
    #define FL_status_string_descriptor_length       12
    #define FL_status_string_descriptor_not_length   16
    #define FL_status_string_device_length           8
    #define FL_status_string_device_not_length       12
    #define FL_status_string_dummy_length            7
    #define FL_status_string_dummy_not_length        11
    #define FL_status_string_encoding_length         10
    #define FL_status_string_encoding_not_length     14
    #define FL_status_string_eof_length              5
    #define FL_status_string_eof_not_length          9
    #define FL_status_string_eol_length              5
    #define FL_status_string_eol_not_length          9
    #define FL_status_string_eos_length              5
    #define FL_status_string_eos_not_length          9
    #define FL_status_string_exist_length            7
    #define FL_status_string_exist_not_length        11
    #define FL_status_string_failure_length          9
    #define FL_status_string_failure_not_length      13
    #define FL_status_string_fork_length             6
    #define FL_status_string_fork_not_length         10
    #define FL_status_string_found_length            7
    #define FL_status_string_found_not_length        11
    #define FL_status_string_input_length            7
    #define FL_status_string_input_not_length        11
    #define FL_status_string_input_output_length     14
    #define FL_status_string_interrupt_length        11
    #define FL_status_string_interrupt_not_length    15
    #define FL_status_string_known_length            7
    #define FL_status_string_known_not_length        11
    #define FL_status_string_link_length             6
    #define FL_status_string_link_not_length         10
    #define FL_status_string_lock_length             6
    #define FL_status_string_lock_not_length         10
    #define FL_status_string_loop_length             6
    #define FL_status_string_loop_not_length         10
    #define FL_status_string_maybe_length            7
    #define FL_status_string_maybe_not_length        11
    #define FL_status_string_minor_length            7
    #define FL_status_string_minor_not_length        11
    #define FL_status_string_moderate_length         10
    #define FL_status_string_moderate_not_length     14
    #define FL_status_string_mount_length            7
    #define FL_status_string_mount_not_length        11
    #define FL_status_string_name_length             6
    #define FL_status_string_name_not_length         10
    #define FL_status_string_optional_length         10
    #define FL_status_string_optional_not_length     14
    #define FL_status_string_output_length           8
    #define FL_status_string_output_not_length       12
    #define FL_status_string_parameter_length        11
    #define FL_status_string_parameter_not_length    15
    #define FL_status_string_parent_length           8
    #define FL_status_string_parent_not_length       12
    #define FL_status_string_pipe_length             6
    #define FL_status_string_pipe_not_length         10
    #define FL_status_string_port_length             6
    #define FL_status_string_port_not_length         10
    #define FL_status_string_prohibited_length       12
    #define FL_status_string_prohibited_not_length   16
    #define FL_status_string_range_length            7
    #define FL_status_string_range_not_length        11
    #define FL_status_string_read_length             6
    #define FL_status_string_read_not_length         10
    #define FL_status_string_read_only_length        11
    #define FL_status_string_ready_length            7
    #define FL_status_string_ready_not_length        11
    #define FL_status_string_recurse_length          9
    #define FL_status_string_recurse_not_length      13
    #define FL_status_string_relative_length         10
    #define FL_status_string_relative_not_length     14
    #define FL_status_string_require_length          9
    #define FL_status_string_require_not_length      13
    #define FL_status_string_resource_length         10
    #define FL_status_string_resource_not_length     14
    #define FL_status_string_search_length           8
    #define FL_status_string_search_not_length       12
    #define FL_status_string_signal_length           8
    #define FL_status_string_signal_not_length       12
    #define FL_status_string_space_length            7
    #define FL_status_string_space_not_length        11
    #define FL_status_string_stop_length             6
    #define FL_status_string_stop_not_length         10
    #define FL_status_string_string_length           8
    #define FL_status_string_string_not_length       12
    #define FL_status_string_string_too_large_length 18
    #define FL_status_string_string_too_small_length 18
    #define FL_status_string_supported_length        11
    #define FL_status_string_supported_not_length    15
    #define FL_status_string_syntax_length           8
    #define FL_status_string_syntax_not_length       12
    #define FL_status_string_utf_length              5
    #define FL_status_string_utf_not_length          9
    #define FL_status_string_valid_length            7
    #define FL_status_string_valid_not_length        11
    #define FL_status_string_value_length            7
    #define FL_status_string_value_not_length        11
    #define FL_status_string_wait_length             6
    #define FL_status_string_wait_not_length         10
    #define FL_status_string_warn_length             6
    #define FL_status_string_warn_not_length         10
    #define FL_status_string_write_length            7
    #define FL_status_string_write_not_length        11
    #define FL_status_string_write_only_length       12
  #endif // _di_F_status_basic_

  #ifndef _di_F_status_array_
    #define FL_status_string_array           "F_array"
    #define FL_status_string_array_not       "F_array_not"
    #define FL_status_string_array_too_large "F_array_too_large"
    #define FL_status_string_array_too_small "F_array_too_small"

    #define FL_status_string_array_length           7
    #define FL_status_string_array_not_length       11
    #define FL_status_string_array_too_large_length 17
    #define FL_status_string_array_too_small_length 17
  #endif // _di_F_status_array_

  #ifndef _di_F_status_available_
    #define FL_status_string_available             "F_available"
    #define FL_status_string_available_not         "F_available_not"
    #define FL_status_string_available_not_address "F_available_not_address"
    #define FL_status_string_available_not_buffer  "F_available_not_buffer"
    #define FL_status_string_available_not_device  "F_available_not_device"
    #define FL_status_string_available_not_pipe    "F_available_not_pipe"
    #define FL_status_string_available_not_port    "F_available_not_port"
    #define FL_status_string_available_not_process "F_available_not_process"
    #define FL_status_string_available_not_socket  "F_available_not_socket"

    #define FL_status_string_available_length             11
    #define FL_status_string_available_not_length         15
    #define FL_status_string_available_not_address_length 23
    #define FL_status_string_available_not_buffer_length  22
    #define FL_status_string_available_not_device_length  22
    #define FL_status_string_available_not_pipe_length    20
    #define FL_status_string_available_not_port_length    20
    #define FL_status_string_available_not_process_length 23
    #define FL_status_string_available_not_socket_length  22
  #endif // _di_F_status_available_

  #ifndef _di_F_status_busy_
    #define FL_status_string_busy         "F_busy"
    #define FL_status_string_busy_address "F_busy_address"
    #define FL_status_string_busy_buffer  "F_busy_buffer"
    #define FL_status_string_busy_device  "F_busy_device"
    #define FL_status_string_busy_not     "F_busy_not"
    #define FL_status_string_busy_pipe    "F_busy_pipe"
    #define FL_status_string_busy_port    "F_busy_port"
    #define FL_status_string_busy_process "F_busy_process"
    #define FL_status_string_busy_socket  "F_busy_socket"

    #define FL_status_string_busy_length         6
    #define FL_status_string_busy_address_length 14
    #define FL_status_string_busy_buffer_length  13
    #define FL_status_string_busy_device_length  13
    #define FL_status_string_busy_not_length     10
    #define FL_status_string_busy_pipe_length    11
    #define FL_status_string_busy_port_length    11
    #define FL_status_string_busy_process_length 14
    #define FL_status_string_busy_socket_length  13
  #endif // _di_F_status_busy_

  #ifndef _di_F_status_number_
    #define FL_status_string_number                "F_number"
    #define FL_status_string_number_decimal        "F_number_decimal"
    #define FL_status_string_number_decimal_not    "F_number_decimal_not"
    #define FL_status_string_number_divide_by_zero "F_number_divide_by_zero"
    #define FL_status_string_number_negative       "F_number_negative"
    #define FL_status_string_number_negative_not   "F_number_negative_not"
    #define FL_status_string_number_not            "F_number_not"
    #define FL_status_string_number_overflow       "F_number_overflow"
    #define FL_status_string_number_positive       "F_number_positive"
    #define FL_status_string_number_positive_not   "F_number_positive_not"
    #define FL_status_string_number_underflow      "F_number_underflow"
    #define FL_status_string_number_whole          "F_number_whole"
    #define FL_status_string_number_whole_not      "F_number_whole_not"
    #define FL_status_string_number_zero           "F_number_zero"
    #define FL_status_string_number_zero_not       "F_number_zero_not"

    #define FL_status_string_number_length                8
    #define FL_status_string_number_decimal_length        16
    #define FL_status_string_number_decimal_not_length    20
    #define FL_status_string_number_divide_by_zero_length 23
    #define FL_status_string_number_negative_length       17
    #define FL_status_string_number_negative_not_length   21
    #define FL_status_string_number_not_length            12
    #define FL_status_string_number_overflow_length       17
    #define FL_status_string_number_positive_length       17
    #define FL_status_string_number_positive_not_length   21
    #define FL_status_string_number_underflow_length      18
    #define FL_status_string_number_whole_length          14
    #define FL_status_string_number_whole_not_length      18
    #define FL_status_string_number_zero_length           13
    #define FL_status_string_number_zero_not_length       17
  #endif // _di_F_status_number_

  #ifndef _di_F_status_buffer_
    #define FL_status_string_buffer                     "F_buffer"
    #define FL_status_string_buffer_not                 "F_buffer_not"
    #define FL_status_string_buffer_too_large           "F_buffer_too_large"
    #define FL_status_string_buffer_too_small           "F_buffer_too_small"
    #define FL_status_string_complete_not_utf           "F_complete_not_utf"
    #define FL_status_string_complete_not_utf_block     "F_complete_not_utf_block"
    #define FL_status_string_complete_not_utf_eof       "F_complete_not_utf_eof"
    #define FL_status_string_complete_not_utf_eol       "F_complete_not_utf_eol"
    #define FL_status_string_complete_not_utf_eos       "F_complete_not_utf_eos"
    #define FL_status_string_complete_not_utf_stop      "F_complete_not_utf_stop"
    #define FL_status_string_none_block                 "F_none_block"
    #define FL_status_string_none_eof                   "F_none_eof"
    #define FL_status_string_none_eol                   "F_none_eol"
    #define FL_status_string_none_eos                   "F_none_eos"
    #define FL_status_string_none_not                   "F_none_not"
    #define FL_status_string_none_stop                  "F_none_stop"
    #define FL_status_string_data                       "F_data"
    #define FL_status_string_data_not                   "F_data_not"
    #define FL_status_string_data_not_block             "F_data_not_block"
    #define FL_status_string_data_not_eof               "F_data_not_eof"
    #define FL_status_string_data_not_eol               "F_data_not_eol"
    #define FL_status_string_data_not_eos               "F_data_not_eos"
    #define FL_status_string_data_not_stop              "F_data_not_stop"
    #define FL_status_string_terminated                 "F_terminated"
    #define FL_status_string_terminated_not             "F_terminated_not"
    #define FL_status_string_terminated_not_block       "F_terminated_not_block"
    #define FL_status_string_terminated_not_eof         "F_terminated_not_eof"
    #define FL_status_string_terminated_not_eol         "F_terminated_not_eol"
    #define FL_status_string_terminated_not_eos         "F_terminated_not_eos"
    #define FL_status_string_terminated_not_stop        "F_terminated_not_stop"
    #define FL_status_string_terminated_not_group       "F_terminated_not_group"
    #define FL_status_string_terminated_not_group_block "F_terminated_not_group_block"
    #define FL_status_string_terminated_not_group_eof   "F_terminated_not_group_eof"
    #define FL_status_string_terminated_not_group_eol   "F_terminated_not_group_eol"
    #define FL_status_string_terminated_not_group_eos   "F_terminated_not_group_eos"
    #define FL_status_string_terminated_not_group_stop  "F_terminated_not_group_stop"
    #define FL_status_string_terminated_not_nest        "F_terminated_not_nest"
    #define FL_status_string_terminated_not_nest_block  "F_terminated_not_nest_block"
    #define FL_status_string_terminated_not_nest_eof    "F_terminated_not_nest_eof"
    #define FL_status_string_terminated_not_nest_eol    "F_terminated_not_nest_eol"
    #define FL_status_string_terminated_not_nest_eos    "F_terminated_not_nest_eos"
    #define FL_status_string_terminated_not_nest_stop   "F_terminated_not_nest_stop"

    #define FL_status_string_buffer_length                     8
    #define FL_status_string_buffer_not_length                 12
    #define FL_status_string_buffer_too_large_length           18
    #define FL_status_string_buffer_too_small_length           18
    #define FL_status_string_complete_not_utf_length           18
    #define FL_status_string_complete_not_utf_block_length     24
    #define FL_status_string_complete_not_utf_eof_length       22
    #define FL_status_string_complete_not_utf_eol_length       22
    #define FL_status_string_complete_not_utf_eos_length       22
    #define FL_status_string_complete_not_utf_stop_length      23
    #define FL_status_string_none_block_length                 12
    #define FL_status_string_none_eof_length                   10
    #define FL_status_string_none_eol_length                   10
    #define FL_status_string_none_eos_length                   10
    #define FL_status_string_none_stop_length                  11
    #define FL_status_string_data_length                       6
    #define FL_status_string_data_not_length                   10
    #define FL_status_string_data_not_block_length             16
    #define FL_status_string_data_not_eof_length               14
    #define FL_status_string_data_not_eol_length               14
    #define FL_status_string_data_not_eos_length               14
    #define FL_status_string_data_not_stop_length              15
    #define FL_status_string_terminated_length                 12
    #define FL_status_string_terminated_not_length             16
    #define FL_status_string_terminated_not_block_length       22
    #define FL_status_string_terminated_not_eof_length         20
    #define FL_status_string_terminated_not_eol_length         20
    #define FL_status_string_terminated_not_eos_length         20
    #define FL_status_string_terminated_not_stop_length        21
    #define FL_status_string_terminated_not_group_length       22
    #define FL_status_string_terminated_not_group_block_length 28
    #define FL_status_string_terminated_not_group_eof_length   25
    #define FL_status_string_terminated_not_group_eol_length   25
    #define FL_status_string_terminated_not_group_eos_length   25
    #define FL_status_string_terminated_not_group_stop_length  26
    #define FL_status_string_terminated_not_nest_length        21
    #define FL_status_string_terminated_not_nest_block_length  26
    #define FL_status_string_terminated_not_nest_eof_length    25
    #define FL_status_string_terminated_not_nest_eol_length    25
    #define FL_status_string_terminated_not_nest_eos_length    25
    #define FL_status_string_terminated_not_nest_stop_length   26
  #endif // _di_F_status_buffer_

  #ifndef _di_F_status_memory_
    #define FL_status_string_memory              "F_memory"
    #define FL_status_string_memory_allocation   "F_memory_allocation"
    #define FL_status_string_memory_deallocation "F_memory_deallocation"
    #define FL_status_string_memory_not          "F_memory_not"
    #define FL_status_string_memory_reallocation "F_memory_reallocation"

    #define FL_status_string_memory_length              8
    #define FL_status_string_memory_allocation_length   19
    #define FL_status_string_memory_deallocation_length 21
    #define FL_status_string_memory_not_length          12
    #define FL_status_string_memory_reallocation_length 21

  #endif // _di_F_status_memory_

  #ifndef _di_F_status_process_
    #define FL_status_string_process          "F_process"
    #define FL_status_string_process_not      "F_process_not"
    #define FL_status_string_process_too_many "F_process_too_many"

    #define FL_status_string_process_length          9
    #define FL_status_string_process_not_length      13
    #define FL_status_string_process_too_many_length 18
  #endif // _di_F_status_process_

  #ifndef _di_F_status_file_
    #define FL_status_string_file                    "F_file"
    #define FL_status_string_file_allocation         "F_file_allocation"
    #define FL_status_string_file_close              "F_file_close"
    #define FL_status_string_file_closed             "F_file_closed"
    #define FL_status_string_file_deallocation       "F_file_deallocation"
    #define FL_status_string_file_descriptor         "F_file_descriptor"
    #define FL_status_string_file_descriptor_max     "F_file_descriptor_max"
    #define FL_status_string_file_empty              "F_file_empty"
    #define FL_status_string_file_flush              "F_file_flush"
    #define FL_status_string_file_found              "F_file_found"
    #define FL_status_string_file_found_not          "F_file_found_not"
    #define FL_status_string_file_not                "F_file_not"
    #define FL_status_string_file_open               "F_file_open"
    #define FL_status_string_file_open_max           "F_file_open_max"
    #define FL_status_string_file_opened             "F_file_opened"
    #define FL_status_string_file_purge              "F_file_purge"
    #define FL_status_string_file_read               "F_file_read"
    #define FL_status_string_file_reallocation       "F_file_reallocation"
    #define FL_status_string_file_seek               "F_file_seek"
    #define FL_status_string_file_stat               "F_file_stat"
    #define FL_status_string_file_synchronize        "F_file_synchronize"
    #define FL_status_string_file_type_block         "F_file_type_block"
    #define FL_status_string_file_type_character     "F_file_type_character"
    #define FL_status_string_file_type_directory     "F_file_type_directory"
    #define FL_status_string_file_type_fifo          "F_file_type_fifo"
    #define FL_status_string_file_type_link          "F_file_type_link"
    #define FL_status_string_file_type_not_block     "F_file_type_not_block"
    #define FL_status_string_file_type_not_character "F_file_type_not_character"
    #define FL_status_string_file_type_not_directory "F_file_type_not_directory"
    #define FL_status_string_file_type_not_fifo      "F_file_type_not_fifo"
    #define FL_status_string_file_type_not_link      "F_file_type_not_link"
    #define FL_status_string_file_type_not_pipe      "F_file_type_not_pipe"
    #define FL_status_string_file_type_not_regular   "F_file_type_not_regular"
    #define FL_status_string_file_type_not_socket    "F_file_type_not_socket"
    #define FL_status_string_file_type_not_unknown   "F_file_type_not_unknown"
    #define FL_status_string_file_type_pipe          "F_file_type_pipe"
    #define FL_status_string_file_type_regular       "F_file_type_regular"
    #define FL_status_string_file_type_socket        "F_file_type_socket"
    #define FL_status_string_file_type_unknown       "F_file_type_unknown"
    #define FL_status_string_file_utf                "F_file_utf"
    #define FL_status_string_file_utf_not            "F_file_utf_not"
    #define FL_status_string_file_write              "F_file_write"

    #define FL_status_string_file_length                     6
    #define FL_status_string_file_allocation_length          17
    #define FL_status_string_file_close_length               12
    #define FL_status_string_file_closed_length              13
    #define FL_status_string_file_deallocation_length        19
    #define FL_status_string_file_descriptor_length          17
    #define FL_status_string_file_descriptor_max_length      21
    #define FL_status_string_file_empty_length               12
    #define FL_status_string_file_flush_length               12
    #define FL_status_string_file_found_length               12
    #define FL_status_string_file_found_not_length           16
    #define FL_status_string_file_not_length                 10
    #define FL_status_string_file_open_length                11
    #define FL_status_string_file_open_max_length            15
    #define FL_status_string_file_opened_length              13
    #define FL_status_string_file_purge_length               12
    #define FL_status_string_file_read_length                11
    #define FL_status_string_file_reallocation_length        19
    #define FL_status_string_file_seek_length                11
    #define FL_status_string_file_stat_length                11
    #define FL_status_string_file_synchronize_length         18
    #define FL_status_string_file_type_block_length          17
    #define FL_status_string_file_type_character_length      21
    #define FL_status_string_file_type_directory_length      21
    #define FL_status_string_file_type_fifo_length           16
    #define FL_status_string_file_type_link_length           16
    #define FL_status_string_file_type_not_block_length      21
    #define FL_status_string_file_type_not_character_length  25
    #define FL_status_string_file_type_not_directory_length  25
    #define FL_status_string_file_type_not_fifo_length       20
    #define FL_status_string_file_type_not_link_length       20
    #define FL_status_string_file_type_not_pipe_length       20
    #define FL_status_string_file_type_not_regular_length    23
    #define FL_status_string_file_type_not_socket_length     22
    #define FL_status_string_file_type_not_unknown_length    23
    #define FL_status_string_file_type_pipe_length           16
    #define FL_status_string_file_type_regular_length        19
    #define FL_status_string_file_type_socket_length         18
    #define FL_status_string_file_type_unknown_length        19
    #define FL_status_string_file_utf_length                 10
    #define FL_status_string_file_utf_not_length             14
    #define FL_status_string_file_write_length               12
  #endif // _di_F_status_file_

  #ifndef _di_F_status_filesystem_
    #define FL_status_string_filesystem               "F_filesystem"
    #define FL_status_string_filesystem_not           "F_filesystem_not"
    #define FL_status_string_filesystem_quota_block   "F_filesystem_quota_block"
    #define FL_status_string_filesystem_quota_reached "F_filesystem_quota_reached"

    #define FL_status_string_filesystem_length               12
    #define FL_status_string_filesystem_not_length           16
    #define FL_status_string_filesystem_quota_block_length   24
    #define FL_status_string_filesystem_quota_reached_length 26
  #endif // _di_F_status_filesystem_

  #ifndef _di_F_status_directory_
    #define FL_status_string_directory             "F_directory"
    #define FL_status_string_directory_close       "F_directory_close"
    #define FL_status_string_directory_closed      "F_directory_closed"
    #define FL_status_string_directory_descriptor  "F_directory_descriptor"
    #define FL_status_string_directory_empty       "F_directory_empty"
    #define FL_status_string_directory_empty_not   "F_directory_empty_not"
    #define FL_status_string_directory_found       "F_directory_found"
    #define FL_status_string_directory_found_not   "F_directory_found_not"
    #define FL_status_string_directory_flush       "F_directory_flush"
    #define FL_status_string_directory_link_max    "F_directory_link_max"
    #define FL_status_string_directory_not         "F_directory_not"
    #define FL_status_string_directory_open        "F_directory_open"
    #define FL_status_string_directory_purge       "F_directory_purge"
    #define FL_status_string_directory_read        "F_directory_read"
    #define FL_status_string_directory_stream      "F_directory_stream"
    #define FL_status_string_directory_synchronize "F_directory_synchronize"
    #define FL_status_string_directory_unsupported "F_directory_unsupported"
    #define FL_status_string_directory_utf         "F_directory_utf"
    #define FL_status_string_directory_utf_not     "F_directory_utf_not"
    #define FL_status_string_directory_write       "F_directory_write"

    #define FL_status_string_directory_length             11
    #define FL_status_string_directory_close_length       17
    #define FL_status_string_directory_closed_length      18
    #define FL_status_string_directory_descriptor_length  22
    #define FL_status_string_directory_empty_length       17
    #define FL_status_string_directory_empty_not_length   21
    #define FL_status_string_directory_found_length       17
    #define FL_status_string_directory_found_not_length   21
    #define FL_status_string_directory_flush_length       17
    #define FL_status_string_directory_link_max_length    20
    #define FL_status_string_directory_not_length         15
    #define FL_status_string_directory_open_length        16
    #define FL_status_string_directory_purge_length       17
    #define FL_status_string_directory_read_length        16
    #define FL_status_string_directory_stream_length      18
    #define FL_status_string_directory_synchronize_length 23
    #define FL_status_string_directory_unsupported_length 23
    #define FL_status_string_directory_utf_length         15
    #define FL_status_string_directory_utf_not_length     19
    #define FL_status_string_directory_write_length       17
  #endif // _di_F_status_directory_

  #ifndef _di_F_status_socket_
    #define FL_status_string_socket         "F_socket"
    #define FL_status_string_socket_client  "F_socket_client"
    #define FL_status_string_socket_not     "F_socket_not"
    #define FL_status_string_socket_receive "F_socket_receive"
    #define FL_status_string_socket_send    "F_socket_send"
    #define FL_status_string_socket_target  "F_socket_target"

    #define FL_status_string_socket_length         8
    #define FL_status_string_socket_client_length  15
    #define FL_status_string_socket_not_length     12
    #define FL_status_string_socket_receive_length 16
    #define FL_status_string_socket_send_length    13
    #define FL_status_string_socket_target_length  15
  #endif // _di_F_status_socket_

  #ifndef _di_F_status_compare_
    #define FL_status_string_equal_to     "F_equal_to"
    #define FL_status_string_equal_to_not "F_equal_to_not"
    #define FL_status_string_than_greater "F_than_greater"
    #define FL_status_string_than_less    "F_than_less"

    #define FL_status_string_equal_to_length     10
    #define FL_status_string_equal_to_not_length 14
    #define FL_status_string_than_greater_length 14
    #define FL_status_string_than_less_length    11
  #endif // _di_F_status_compare_

  #ifndef _di_F_status_access_
    #define FL_status_string_access                 "F_access"
    #define FL_status_string_access_denied          "F_access_denied"
    #define FL_status_string_access_denied_user     "F_access_denied_user"
    #define FL_status_string_access_denied_group    "F_access_denied_group"
    #define FL_status_string_access_denied_world    "F_access_denied_world"
    #define FL_status_string_access_denied_read     "F_access_denied_read"
    #define FL_status_string_access_denied_write    "F_access_denied_write"
    #define FL_status_string_access_denied_execute  "F_access_denied_execute"
    #define FL_status_string_access_denied_super    "F_access_denied_super"
    #define FL_status_string_access_granted         "F_access_granted"
    #define FL_status_string_access_granted_user    "F_access_granted_user"
    #define FL_status_string_access_granted_group   "F_access_granted_group"
    #define FL_status_string_access_granted_world   "F_access_granted_world"
    #define FL_status_string_access_granted_read    "F_access_granted_read"
    #define FL_status_string_access_granted_write   "F_access_granted_write"
    #define FL_status_string_access_granted_execute "F_access_granted_execute"
    #define FL_status_string_access_granted_super   "F_access_granted_super"
    #define FL_status_string_access_group           "F_access_group"
    #define FL_status_string_access_mode            "F_access_mode"
    #define FL_status_string_access_not             "F_access_not"
    #define FL_status_string_access_owner           "F_access_owner"

    #define FL_status_string_access_length                 8
    #define FL_status_string_access_denied_length          15
    #define FL_status_string_access_denied_user_length     20
    #define FL_status_string_access_denied_group_length    21
    #define FL_status_string_access_denied_world_length    21
    #define FL_status_string_access_denied_read_length     20
    #define FL_status_string_access_denied_write_length    21
    #define FL_status_string_access_denied_execute_length  23
    #define FL_status_string_access_denied_super_length    21
    #define FL_status_string_access_granted_length         16
    #define FL_status_string_access_granted_user_length    21
    #define FL_status_string_access_granted_group_length   22
    #define FL_status_string_access_granted_world_length   22
    #define FL_status_string_access_granted_read_length    21
    #define FL_status_string_access_granted_write_length   22
    #define FL_status_string_access_granted_execute_length 24
    #define FL_status_string_access_granted_super_length   22
    #define FL_status_string_access_group_length           14
    #define FL_status_string_access_mode_length            13
    #define FL_status_string_access_not_length             12
    #define FL_status_string_access_owner_length           14
  #endif // _di_F_status_access_

  #define FL_status_string_status_code_last "F_status_code_last"

  #define FL_status_string_status_code_last_length 18
#endif // _di_FL_status_string_

/**
 * Convert status codes to their string representation.
 *
 * The error, warning, and signal bits are ignored.
 *
 * @param code
 *   The status code to process.
 * @param string
 *   The processed code code.
 *
 * @return
 *   F_none on success.
 *   F_data (with error bit) if there status is unknown.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_status_to_string_
  extern f_return_status fl_status_to_string(const f_status_t code, f_string_t *string);
#endif // _di_fl_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_status_h

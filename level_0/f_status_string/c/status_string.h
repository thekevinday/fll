/**
 * FLL - Level 0
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides status code functions, such as those that translate status codes into strings.
 */
#ifndef _F_status_string_h
#define _F_status_string_h

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_F_status_string_
  #ifndef _di_F_status_boolean_
    #define F_status_false_s "F_false"
    #define F_status_true_s  "F_true"

    #define F_status_false_s_length 7
    #define F_status_true_s_length  6

    extern const f_string_t f_status_false_s;
    extern const f_string_t f_status_true_s;
  #endif // _di_F_status_boolean_

  #ifndef _di_F_status_signal_
    #define F_status_signal_hangup_s               "F_signal_hangup"
    #define F_status_signal_interrupt_s            "F_signal_interrupt"
    #define F_status_signal_quit_s                 "F_signal_quit"
    #define F_status_signal_illegal_s              "F_signal_illegal"
    #define F_status_signal_trap_s                 "F_signal_trap"
    #define F_status_signal_abort_s                "F_signal_abort"
    #define F_status_signal_bus_error_s            "F_signal_bus_error"
    #define F_status_signal_floating_point_error_s "F_signal_floating_point_error"
    #define F_status_signal_kill_s                 "F_signal_kill"
    #define F_status_signal_user_1_s               "F_signal_user_1"
    #define F_status_signal_segmentation_fault_s   "F_signal_segmentation_fault"
    #define F_status_signal_user_2_s               "F_signal_user_2"
    #define F_status_signal_broken_pipe_s          "F_signal_broken_pipe"
    #define F_status_signal_alarm_clock_s          "F_signal_alarm_clock"
    #define F_status_signal_termination_s          "F_signal_termination"
    #define F_status_signal_stack_fault_s          "F_signal_stack_fault"
    #define F_status_signal_child_s                "F_signal_child"
    #define F_status_signal_continue_s             "F_signal_continue"
    #define F_status_signal_stop_s                 "F_signal_stop"
    #define F_status_signal_keyboard_stop_s        "F_signal_keyboard_stop"
    #define F_status_signal_tty_in_s               "F_signal_tty_in"
    #define F_status_signal_tty_out_s              "F_signal_tty_out"
    #define F_status_signal_urgent_s               "F_signal_urgent"
    #define F_status_signal_cpu_limit_s            "F_signal_cpu_limit"
    #define F_status_signal_file_size_limit_s      "F_signal_file_size_limit"
    #define F_status_signal_virtual_alarm_clock_s  "F_signal_virtual_alarm_clock"
    #define F_status_signal_profile_alarm_clock_s  "F_signal_profile_alarm_clock"
    #define F_status_signal_window_size_change_s   "F_signal_window_size_change"
    #define F_status_signal_pollable_event_s       "F_signal_pollable_event"
    #define F_status_signal_power_failure_s        "F_signal_power_failure"
    #define F_status_signal_bad_system_call_s      "F_signal_bad_system_call"
    #define F_status_signal_reserved_32_s          "F_signal_reserved_32"
    #define F_status_signal_reserved_33_s          "F_signal_reserved_33"
    #define F_status_signal_reserved_34_s          "F_signal_reserved_34"
    #define F_status_signal_reserved_35_s          "F_signal_reserved_35"
    #define F_status_signal_reserved_36_s          "F_signal_reserved_36"
    #define F_status_signal_reserved_37_s          "F_signal_reserved_37"
    #define F_status_signal_reserved_38_s          "F_signal_reserved_38"
    #define F_status_signal_reserved_39_s          "F_signal_reserved_39"
    #define F_status_signal_reserved_40_s          "F_signal_reserved_40"
    #define F_status_signal_reserved_41_s          "F_signal_reserved_41"
    #define F_status_signal_reserved_42_s          "F_signal_reserved_42"
    #define F_status_signal_reserved_43_s          "F_signal_reserved_43"
    #define F_status_signal_reserved_44_s          "F_signal_reserved_44"
    #define F_status_signal_reserved_45_s          "F_signal_reserved_45"
    #define F_status_signal_reserved_46_s          "F_signal_reserved_46"
    #define F_status_signal_reserved_47_s          "F_signal_reserved_47"
    #define F_status_signal_reserved_48_s          "F_signal_reserved_48"
    #define F_status_signal_reserved_49_s          "F_signal_reserved_49"
    #define F_status_signal_reserved_50_s          "F_signal_reserved_50"
    #define F_status_signal_reserved_51_s          "F_signal_reserved_51"
    #define F_status_signal_reserved_52_s          "F_signal_reserved_52"
    #define F_status_signal_reserved_53_s          "F_signal_reserved_53"
    #define F_status_signal_reserved_54_s          "F_signal_reserved_54"
    #define F_status_signal_reserved_55_s          "F_signal_reserved_55"
    #define F_status_signal_reserved_56_s          "F_signal_reserved_56"
    #define F_status_signal_reserved_57_s          "F_signal_reserved_57"
    #define F_status_signal_reserved_58_s          "F_signal_reserved_58"
    #define F_status_signal_reserved_59_s          "F_signal_reserved_59"
    #define F_status_signal_reserved_60_s          "F_signal_reserved_60"
    #define F_status_signal_reserved_61_s          "F_signal_reserved_61"
    #define F_status_signal_reserved_62_s          "F_signal_reserved_62"
    #define F_status_signal_reserved_63_s          "F_signal_reserved_63"
    #define F_status_signal_reserved_64_s          "F_signal_reserved_64"

    #define F_status_signal_hangup_s_length             15
    #define F_status_signal_interrupt_s_length            18
    #define F_status_signal_quit_s_length                 13
    #define F_status_signal_illegal_s_length              16
    #define F_status_signal_trap_s_length                 13
    #define F_status_signal_abort_s_length                14
    #define F_status_signal_bus_error_s_length            17
    #define F_status_signal_floating_point_error_s_length 33
    #define F_status_signal_kill_s_length                 13
    #define F_status_signal_user_1_s_length               15
    #define F_status_signal_segmentation_fault_s_length   27
    #define F_status_signal_user_2_s_length               15
    #define F_status_signal_broken_pipe_s_length          20
    #define F_status_signal_alarm_clock_s_length          20
    #define F_status_signal_termination_s_length          20
    #define F_status_signal_stack_fault_s_length          20
    #define F_status_signal_child_s_length                14
    #define F_status_signal_continue_s_length             17
    #define F_status_signal_stop_s_length                 13
    #define F_status_signal_keyboard_stop_s_length        22
    #define F_status_signal_tty_in_s_length               15
    #define F_status_signal_tty_out_s_length              16
    #define F_status_signal_urgent_s_length               15
    #define F_status_signal_cpu_limit_s_length            18
    #define F_status_signal_file_size_limit_s_length      24
    #define F_status_signal_virtual_alarm_clock_s_length  28
    #define F_status_signal_profile_alarm_clock_s_length  28
    #define F_status_signal_window_size_change_s_length   27
    #define F_status_signal_pollable_event_s_length       23
    #define F_status_signal_power_failure_s_length        22
    #define F_status_signal_bad_system_call_s_length      24
    #define F_status_signal_reserved_32_s_length          20
    #define F_status_signal_reserved_33_s_length          20
    #define F_status_signal_reserved_34_s_length          20
    #define F_status_signal_reserved_35_s_length          20
    #define F_status_signal_reserved_36_s_length          20
    #define F_status_signal_reserved_37_s_length          20
    #define F_status_signal_reserved_38_s_length          20
    #define F_status_signal_reserved_39_s_length          20
    #define F_status_signal_reserved_40_s_length          20
    #define F_status_signal_reserved_41_s_length          20
    #define F_status_signal_reserved_42_s_length          20
    #define F_status_signal_reserved_43_s_length          20
    #define F_status_signal_reserved_44_s_length          20
    #define F_status_signal_reserved_45_s_length          20
    #define F_status_signal_reserved_46_s_length          20
    #define F_status_signal_reserved_47_s_length          20
    #define F_status_signal_reserved_48_s_length          20
    #define F_status_signal_reserved_49_s_length          20
    #define F_status_signal_reserved_50_s_length          20
    #define F_status_signal_reserved_51_s_length          20
    #define F_status_signal_reserved_52_s_length          20
    #define F_status_signal_reserved_53_s_length          20
    #define F_status_signal_reserved_54_s_length          20
    #define F_status_signal_reserved_55_s_length          20
    #define F_status_signal_reserved_56_s_length          20
    #define F_status_signal_reserved_57_s_length          20
    #define F_status_signal_reserved_58_s_length          20
    #define F_status_signal_reserved_59_s_length          20
    #define F_status_signal_reserved_60_s_length          20
    #define F_status_signal_reserved_61_s_length          20
    #define F_status_signal_reserved_62_s_length          20
    #define F_status_signal_reserved_63_s_length          20
    #define F_status_signal_reserved_64_s_length          20

    extern const f_string_t f_status_signal_hangup_s;
    extern const f_string_t f_status_signal_interrupt_s;
    extern const f_string_t f_status_signal_quit_s;
    extern const f_string_t f_status_signal_illegal_s;
    extern const f_string_t f_status_signal_trap_s;
    extern const f_string_t f_status_signal_abort_s;
    extern const f_string_t f_status_signal_bus_error_s;
    extern const f_string_t f_status_signal_floating_point_error_s;
    extern const f_string_t f_status_signal_kill_s;
    extern const f_string_t f_status_signal_user_1_s;
    extern const f_string_t f_status_signal_segmentation_fault_s;
    extern const f_string_t f_status_signal_user_2_s;
    extern const f_string_t f_status_signal_broken_pipe_s;
    extern const f_string_t f_status_signal_alarm_clock_s;
    extern const f_string_t f_status_signal_termination_s;
    extern const f_string_t f_status_signal_stack_fault_s;
    extern const f_string_t f_status_signal_child_s;
    extern const f_string_t f_status_signal_continue_s;
    extern const f_string_t f_status_signal_stop_s;
    extern const f_string_t f_status_signal_keyboard_stop_s;
    extern const f_string_t f_status_signal_tty_in_s;
    extern const f_string_t f_status_signal_tty_out_s;
    extern const f_string_t f_status_signal_urgent_s;
    extern const f_string_t f_status_signal_cpu_limit_s;
    extern const f_string_t f_status_signal_file_size_limit_s;
    extern const f_string_t f_status_signal_virtual_alarm_clock_s;
    extern const f_string_t f_status_signal_profile_alarm_clock_s;
    extern const f_string_t f_status_signal_window_size_change_s;
    extern const f_string_t f_status_signal_pollable_event_s;
    extern const f_string_t f_status_signal_power_failure_s;
    extern const f_string_t f_status_signal_bad_system_call_s;
    extern const f_string_t f_status_signal_reserved_32_s;
    extern const f_string_t f_status_signal_reserved_33_s;
    extern const f_string_t f_status_signal_reserved_34_s;
    extern const f_string_t f_status_signal_reserved_35_s;
    extern const f_string_t f_status_signal_reserved_36_s;
    extern const f_string_t f_status_signal_reserved_37_s;
    extern const f_string_t f_status_signal_reserved_38_s;
    extern const f_string_t f_status_signal_reserved_39_s;
    extern const f_string_t f_status_signal_reserved_40_s;
    extern const f_string_t f_status_signal_reserved_41_s;
    extern const f_string_t f_status_signal_reserved_42_s;
    extern const f_string_t f_status_signal_reserved_43_s;
    extern const f_string_t f_status_signal_reserved_44_s;
    extern const f_string_t f_status_signal_reserved_45_s;
    extern const f_string_t f_status_signal_reserved_46_s;
    extern const f_string_t f_status_signal_reserved_47_s;
    extern const f_string_t f_status_signal_reserved_48_s;
    extern const f_string_t f_status_signal_reserved_49_s;
    extern const f_string_t f_status_signal_reserved_50_s;
    extern const f_string_t f_status_signal_reserved_51_s;
    extern const f_string_t f_status_signal_reserved_52_s;
    extern const f_string_t f_status_signal_reserved_53_s;
    extern const f_string_t f_status_signal_reserved_54_s;
    extern const f_string_t f_status_signal_reserved_55_s;
    extern const f_string_t f_status_signal_reserved_56_s;
    extern const f_string_t f_status_signal_reserved_57_s;
    extern const f_string_t f_status_signal_reserved_58_s;
    extern const f_string_t f_status_signal_reserved_59_s;
    extern const f_string_t f_status_signal_reserved_60_s;
    extern const f_string_t f_status_signal_reserved_61_s;
    extern const f_string_t f_status_signal_reserved_62_s;
    extern const f_string_t f_status_signal_reserved_63_s;
    extern const f_string_t f_status_signal_reserved_64_s;
  #endif // _di_F_status_signal_

  #ifndef _di_F_status_basic_
    #define F_status_none_s              "F_none"
    #define F_status_abort_s             "F_abort"
    #define F_status_abort_not_s         "F_abort_not"
    #define F_status_absolute_s          "F_absolute"
    #define F_status_absolute_not_s      "F_absolute_not"
    #define F_status_address_s           "F_address"
    #define F_status_address_not_s       "F_address_not"
    #define F_status_ascii_s             "F_ascii"
    #define F_status_ascii_not_s         "F_ascii_not"
    #define F_status_atomic_s            "F_atomic"
    #define F_status_atomic_not_s        "F_atomic_not"
    #define F_status_begin_s             "F_begin"
    #define F_status_begin_not_s         "F_begin_not"
    #define F_status_block_s             "F_block"
    #define F_status_block_not_s         "F_block_not"
    #define F_status_body_s              "F_body"
    #define F_status_body_not_s          "F_body_not"
    #define F_status_bound_s             "F_bound"
    #define F_status_bound_not_s         "F_bound_not"
    #define F_status_capability_s        "F_capability"
    #define F_status_capability_not_s    "F_capability_not"
    #define F_status_child_s             "F_child"
    #define F_status_child_not_s         "F_child_not"
    #define F_status_complete_s          "F_complete"
    #define F_status_complete_not_s      "F_complete_not"
    #define F_status_connect_s           "F_connect"
    #define F_status_connect_not_s       "F_connect_not"
    #define F_status_connect_refuse_s    "F_connect_refuse"
    #define F_status_connect_reset_s     "F_connect_reset"
    #define F_status_container_s         "F_container"
    #define F_status_container_not_s     "F_container_not"
    #define F_status_content_s           "F_content"
    #define F_status_content_not_s       "F_content_not"
    #define F_status_continue_s          "F_continue"
    #define F_status_continue_not_s      "F_continue_not"
    #define F_status_control_s           "F_control"
    #define F_status_control_not_s       "F_control_not"
    #define F_status_control_group_s     "F_control_group"
    #define F_status_control_group_not_s "F_control_group_not"
    #define F_status_critical_s          "F_critical"
    #define F_status_critical_not_s      "F_critical_not"
    #define F_status_dead_s              "F_dead"
    #define F_status_dead_not_s          "F_dead_not"
    #define F_status_deadlock_s          "F_deadlock"
    #define F_status_deadlock_not_s      "F_deadlock_not"
    #define F_status_descriptor_s        "F_descriptor"
    #define F_status_descriptor_not_s    "F_descriptor_not"
    #define F_status_device_s            "F_device"
    #define F_status_device_not_s        "F_device_not"
    #define F_status_disable_s           "F_disable"
    #define F_status_disable_not_s       "F_disable_not"
    #define F_status_domain_s            "F_domain"
    #define F_status_domain_not_s        "F_domain_not"
    #define F_status_done_s              "F_done"
    #define F_status_done_not_s          "F_done_not"
    #define F_status_dummy_s             "F_dummy"
    #define F_status_dummy_not_s         "F_dummy_not"
    #define F_status_empty_s             "F_empty"
    #define F_status_empty_not_s         "F_empty_not"
    #define F_status_enable_s            "F_enable"
    #define F_status_enable_not_s        "F_enable_not"
    #define F_status_encoding_s          "F_encoding"
    #define F_status_encoding_not_s      "F_encoding_not"
    #define F_status_end_s               "F_end"
    #define F_status_end_not_s           "F_end_not"
    #define F_status_eoa_s               "F_eoa"
    #define F_status_eoa_not_s           "F_eoa_not"
    #define F_status_eof_s               "F_eof"
    #define F_status_eof_not_s           "F_eof_not"
    #define F_status_eol_s               "F_eol"
    #define F_status_eol_not_s           "F_eol_not"
    #define F_status_eos_s               "F_eos"
    #define F_status_eos_not_s           "F_eos_not"
    #define F_status_execute_s           "F_execute"
    #define F_status_execute_not_s       "F_execute_not"
    #define F_status_exist_s             "F_exist"
    #define F_status_exist_not_s         "F_exist_not"
    #define F_status_failure_s           "F_failure"
    #define F_status_failure_not_s       "F_failure_not"
    #define F_status_family_s            "F_family"
    #define F_status_family_not_s        "F_family_not"
    #define F_status_first_s             "F_first"
    #define F_status_first_not_s         "F_first_not"
    #define F_status_footer_s            "F_footer"
    #define F_status_footer_not_s        "F_footer_not"
    #define F_status_fork_s              "F_fork"
    #define F_status_fork_not_s          "F_fork_not"
    #define F_status_format_s            "F_format"
    #define F_status_format_not_s        "F_format_not"
    #define F_status_found_s             "F_found"
    #define F_status_found_not_s         "F_found_not"
    #define F_status_full_s              "F_full"
    #define F_status_full_not_s          "F_full_not"
    #define F_status_group_s             "F_group"
    #define F_status_group_not_s         "F_group_not"
    #define F_status_header_s            "F_header"
    #define F_status_header_not_s        "F_header_not"
    #define F_status_ignore_s            "F_ignore"
    #define F_status_ignore_not_s        "F_ignore_not"
    #define F_status_implemented_s       "F_implemented"
    #define F_status_implemented_not_s   "F_implemented_not"
    #define F_status_input_s             "F_input"
    #define F_status_input_not_s         "F_input_not"
    #define F_status_input_output_s      "F_input_output"
    #define F_status_interrupt_s         "F_interrupt"
    #define F_status_interrupt_not_s     "F_interrupt_not"
    #define F_status_known_s             "F_known"
    #define F_status_known_not_s         "F_known_not"
    #define F_status_last_s              "F_last"
    #define F_status_last_not_s          "F_last_not"
    #define F_status_limit_s             "F_limit"
    #define F_status_limit_not_s         "F_limit_not"
    #define F_status_link_s              "F_link"
    #define F_status_link_not_s          "F_link_not"
    #define F_status_live_s              "F_live"
    #define F_status_live_not_s          "F_live_not"
    #define F_status_lock_s              "F_lock"
    #define F_status_lock_not_s          "F_lock_not"
    #define F_status_loop_s              "F_loop"
    #define F_status_loop_not_s          "F_loop_not"
    #define F_status_maybe_s             "F_maybe"
    #define F_status_maybe_not_s         "F_maybe_not"
    #define F_status_memory_s            "F_memory"
    #define F_status_memory_not_s        "F_memory_not"
    #define F_status_message_s           "F_message"
    #define F_status_message_not_s       "F_message_not"
    #define F_status_minor_s             "F_minor"
    #define F_status_minor_not_s         "F_minor_not"
    #define F_status_moderate_s          "F_moderate"
    #define F_status_moderate_not_s      "F_moderate_not"
    #define F_status_mount_s             "F_mount"
    #define F_status_mount_not_s         "F_mount_not"
    #define F_status_name_s              "F_name"
    #define F_status_name_not_s          "F_name_not"
    #define F_status_next_s              "F_next"
    #define F_status_next_not_s          "F_next_not"
    #define F_status_nice_s              "F_nice"
    #define F_status_nice_not_s          "F_nice_not"
    #define F_status_object_s            "F_object"
    #define F_status_object_not_s        "F_object_not"
    #define F_status_option_s            "F_option"
    #define F_status_option_not_s        "F_option_not"
    #define F_status_output_s            "F_output"
    #define F_status_output_not_s        "F_output_not"
    #define F_status_packet_s            "F_packet"
    #define F_status_packet_not_s        "F_packet_not"
    #define F_status_parameter_s         "F_parameter"
    #define F_status_parameter_not_s     "F_parameter_not"
    #define F_status_parent_s            "F_parent"
    #define F_status_parent_not_s        "F_parent_not"
    #define F_status_payload_s           "F_payload"
    #define F_status_payload_not_s       "F_payload_not"
    #define F_status_pipe_s              "F_pipe"
    #define F_status_pipe_not_s          "F_pipe_not"
    #define F_status_port_s              "F_port"
    #define F_status_port_not_s          "F_port_not"
    #define F_status_previous_s          "F_previous"
    #define F_status_previous_not_s      "F_previous_not"
    #define F_status_processor_s         "F_processor"
    #define F_status_processor_not_s     "F_processor_not"
    #define F_status_progress_s          "F_progress"
    #define F_status_progress_not_s      "F_progress_not"
    #define F_status_prohibited_s        "F_prohibited"
    #define F_status_prohibited_not_s    "F_prohibited_not"
    #define F_status_property_s          "F_property"
    #define F_status_property_not_s      "F_property_not"
    #define F_status_protocol_s          "F_protocol"
    #define F_status_protocol_not_s      "F_protocol_not"
    #define F_status_range_s             "F_range"
    #define F_status_range_not_s         "F_range_not"
    #define F_status_read_s              "F_read"
    #define F_status_read_not_s          "F_read_not"
    #define F_status_read_only_s         "F_read_only"
    #define F_status_ready_s             "F_ready"
    #define F_status_ready_not_s         "F_ready_not"
    #define F_status_recover_s           "F_recover"
    #define F_status_recover_not_s       "F_recover_not"
    #define F_status_recurse_s           "F_recurse"
    #define F_status_recurse_not_s       "F_recurse_not"
    #define F_status_relative_s          "F_relative"
    #define F_status_relative_not_s      "F_relative_not"
    #define F_status_require_s           "F_require"
    #define F_status_require_not_s       "F_require_not"
    #define F_status_resource_s          "F_resource"
    #define F_status_resource_not_s      "F_resource_not"
    #define F_status_search_s            "F_search"
    #define F_status_search_not_s        "F_search_not"
    #define F_status_schedule_s          "F_schedule"
    #define F_status_schedule_not_s      "F_schedule_not"
    #define F_status_size_s              "F_size"
    #define F_status_size_not_s          "F_size_not"
    #define F_status_signal_s            "F_signal"
    #define F_status_signal_not_s        "F_signal_not"
    #define F_status_space_s             "F_space"
    #define F_status_space_not_s         "F_space_not"
    #define F_status_start_s             "F_start"
    #define F_status_start_not_s         "F_start_not"
    #define F_status_stop_s              "F_stop"
    #define F_status_stop_not_s          "F_stop_not"
    #define F_status_stream_s            "F_stream"
    #define F_status_stream_not_s        "F_stream_not"
    #define F_status_string_s            "F_string"
    #define F_status_string_not_s        "F_string_not"
    #define F_status_string_too_large_s  "F_string_too_large"
    #define F_status_string_too_small_s  "F_string_too_small"
    #define F_status_syntax_s            "F_syntax"
    #define F_status_syntax_not_s        "F_syntax_not"
    #define F_status_thread_s            "F_thread"
    #define F_status_thread_not_s        "F_thread_not"
    #define F_status_time_s              "F_time"
    #define F_status_time_not_s          "F_time_not"
    #define F_status_time_out_s          "F_time_out"
    #define F_status_too_large_s         "F_too_large"
    #define F_status_too_small_s         "F_too_small"
    #define F_status_type_s              "F_type"
    #define F_status_type_not_s          "F_type_not"
    #define F_status_success_s           "F_success"
    #define F_status_success_not_s       "F_success_not"
    #define F_status_supported_s         "F_supported"
    #define F_status_supported_not_s     "F_supported_not"
    #define F_status_user_s              "F_user"
    #define F_status_user_not_s          "F_user_not"
    #define F_status_utf_s               "F_utf"
    #define F_status_utf_fragment_s      "F_utf_fragment"
    #define F_status_utf_fragment_not_s  "F_utf_fragment_not"
    #define F_status_utf_not_s           "F_utf_not"
    #define F_status_valid_s             "F_valid"
    #define F_status_valid_not_s         "F_valid_not"
    #define F_status_value_s             "F_value"
    #define F_status_value_not_s         "F_value_not"
    #define F_status_wait_s              "F_wait"
    #define F_status_wait_not_s          "F_wait_not"
    #define F_status_warn_s              "F_warn"
    #define F_status_warn_not_s          "F_warn_not"
    #define F_status_world_s             "F_world"
    #define F_status_world_not_s         "F_world_not"
    #define F_status_write_s             "F_write"
    #define F_status_write_not_s         "F_write_not"
    #define F_status_write_only_s        "F_write_only"

    #define F_status_none_s_length              6
    #define F_status_abort_s_length             7
    #define F_status_abort_not_s_length         11
    #define F_status_absolute_s_length          10
    #define F_status_absolute_not_s_length      14
    #define F_status_address_s_length           9
    #define F_status_address_not_s_length       13
    #define F_status_ascii_s_length             7
    #define F_status_ascii_not_s_length         11
    #define F_status_atomic_s_length            8
    #define F_status_atomic_not_s_length        12
    #define F_status_begin_s_length             7
    #define F_status_begin_not_s_length         11
    #define F_status_block_s_length             7
    #define F_status_block_not_s_length         11
    #define F_status_body_s_length              6
    #define F_status_body_not_s_length          10
    #define F_status_bound_s_length             7
    #define F_status_bound_not_s_length         11
    #define F_status_capability_s_length        12
    #define F_status_capability_not_s_length    16
    #define F_status_child_s_length             7
    #define F_status_child_not_s_length         11
    #define F_status_complete_s_length          10
    #define F_status_complete_not_s_length      14
    #define F_status_connect_s_length           9
    #define F_status_connect_not_s_length       13
    #define F_status_connect_refuse_s_length    16
    #define F_status_connect_reset_s_length     15
    #define F_status_container_s_length         11
    #define F_status_container_not_s_length     15
    #define F_status_content_s_length           9
    #define F_status_content_not_s_length       13
    #define F_status_continue_s_length          10
    #define F_status_continue_not_s_length      14
    #define F_status_control_s_length           9
    #define F_status_control_not_s_length       13
    #define F_status_control_group_s_length     15
    #define F_status_control_group_not_s_length 19
    #define F_status_critical_s_length          10
    #define F_status_critical_not_s_length      14
    #define F_status_dead_s_length              6
    #define F_status_dead_not_s_length          10
    #define F_status_deadlock_s_length          10
    #define F_status_deadlock_not_s_length      14
    #define F_status_descriptor_s_length        12
    #define F_status_descriptor_not_s_length    16
    #define F_status_device_s_length            8
    #define F_status_device_not_s_length        12
    #define F_status_disable_s_length           9
    #define F_status_disable_not_s_length       13
    #define F_status_domain_s_length            8
    #define F_status_domain_not_s_length        12
    #define F_status_done_s_length              6
    #define F_status_done_not_s_length          10
    #define F_status_dummy_s_length             7
    #define F_status_dummy_not_s_length         11
    #define F_status_empty_s_length             7
    #define F_status_empty_not_s_length         11
    #define F_status_enable_s_length            8
    #define F_status_enable_not_s_length        12
    #define F_status_encoding_s_length          10
    #define F_status_encoding_not_s_length      14
    #define F_status_end_s_length               5
    #define F_status_end_not_s_length           9
    #define F_status_eoa_s_length               5
    #define F_status_eoa_not_s_length           9
    #define F_status_eof_s_length               5
    #define F_status_eof_not_s_length           9
    #define F_status_eol_s_length               5
    #define F_status_eol_not_s_length           9
    #define F_status_eos_s_length               5
    #define F_status_eos_not_s_length           9
    #define F_status_execute_s_length           9
    #define F_status_execute_not_s_length       13
    #define F_status_exist_s_length             7
    #define F_status_exist_not_s_length         11
    #define F_status_failure_s_length           9
    #define F_status_failure_not_s_length       13
    #define F_status_family_s_length            8
    #define F_status_family_not_s_length        12
    #define F_status_first_s_length             7
    #define F_status_first_not_s_length         11
    #define F_status_footer_s_length            8
    #define F_status_footer_not_s_length        12
    #define F_status_fork_s_length              6
    #define F_status_fork_not_s_length          10
    #define F_status_format_s_length            8
    #define F_status_format_not_s_length        12
    #define F_status_found_s_length             7
    #define F_status_found_not_s_length         11
    #define F_status_full_s_length              6
    #define F_status_full_not_s_length          10
    #define F_status_group_s_length             7
    #define F_status_group_not_s_length         11
    #define F_status_header_s_length            8
    #define F_status_header_not_s_length        12
    #define F_status_ignore_s_length            8
    #define F_status_ignore_not_s_length        12
    #define F_status_implemented_s_length       13
    #define F_status_implemented_not_s_length   17
    #define F_status_input_s_length             7
    #define F_status_input_not_s_length         11
    #define F_status_input_output_s_length      14
    #define F_status_interrupt_s_length         11
    #define F_status_interrupt_not_s_length     15
    #define F_status_known_s_length             7
    #define F_status_known_not_s_length         11
    #define F_status_last_s_length              6
    #define F_status_last_not_s_length          10
    #define F_status_limit_s_length             7
    #define F_status_limit_not_s_length         11
    #define F_status_link_s_length              6
    #define F_status_link_not_s_length          10
    #define F_status_live_s_length              6
    #define F_status_live_not_s_length          10
    #define F_status_lock_s_length              6
    #define F_status_lock_not_s_length          10
    #define F_status_loop_s_length              6
    #define F_status_loop_not_s_length          10
    #define F_status_maybe_s_length             7
    #define F_status_maybe_not_s_length         11
    #define F_status_memory_s_length            8
    #define F_status_memory_not_s_length        12
    #define F_status_message_s_length           9
    #define F_status_message_not_s_length       13
    #define F_status_minor_s_length             7
    #define F_status_minor_not_s_length         11
    #define F_status_moderate_s_length          10
    #define F_status_moderate_not_s_length      14
    #define F_status_mount_s_length             7
    #define F_status_mount_not_s_length         11
    #define F_status_name_s_length              6
    #define F_status_name_not_s_length          10
    #define F_status_next_s_length              6
    #define F_status_next_not_s_length          10
    #define F_status_nice_s_length              6
    #define F_status_nice_not_s_length          10
    #define F_status_object_s_length            8
    #define F_status_object_not_s_length        12
    #define F_status_option_s_length            8
    #define F_status_option_not_s_length        12
    #define F_status_output_s_length            8
    #define F_status_output_not_s_length        12
    #define F_status_packet_s_length            8
    #define F_status_packet_not_s_length        12
    #define F_status_parameter_s_length         11
    #define F_status_parameter_not_s_length     15
    #define F_status_parent_s_length            8
    #define F_status_parent_not_s_length        12
    #define F_status_payload_s_length           9
    #define F_status_payload_not_s_length       13
    #define F_status_pipe_s_length              6
    #define F_status_pipe_not_s_length          10
    #define F_status_port_s_length              6
    #define F_status_port_not_s_length          10
    #define F_status_previous_s_length          10
    #define F_status_previous_not_s_length      14
    #define F_status_processor_s_length         11
    #define F_status_processor_not_s_length     15
    #define F_status_progress_s_length          10
    #define F_status_progress_not_s_length      14
    #define F_status_prohibited_s_length        12
    #define F_status_prohibited_not_s_length    16
    #define F_status_property_s_length          10
    #define F_status_property_not_s_length      14
    #define F_status_protocol_s_length          10
    #define F_status_protocol_not_s_length      14
    #define F_status_range_s_length             7
    #define F_status_range_not_s_length         11
    #define F_status_read_s_length              6
    #define F_status_read_not_s_length          10
    #define F_status_read_only_s_length         11
    #define F_status_ready_s_length             7
    #define F_status_ready_not_s_length         11
    #define F_status_recover_s_length           9
    #define F_status_recover_not_s_length       13
    #define F_status_recurse_s_length           9
    #define F_status_recurse_not_s_length       13
    #define F_status_relative_s_length          10
    #define F_status_relative_not_s_length      14
    #define F_status_require_s_length           9
    #define F_status_require_not_s_length       13
    #define F_status_resource_s_length          10
    #define F_status_resource_not_s_length      14
    #define F_status_search_s_length            8
    #define F_status_search_not_s_length        12
    #define F_status_schedule_s_length          10
    #define F_status_schedule_not_s_length      14
    #define F_status_size_s_length              6
    #define F_status_size_not_s_length          10
    #define F_status_signal_s_length            8
    #define F_status_signal_not_s_length        12
    #define F_status_space_s_length             7
    #define F_status_space_not_s_length         11
    #define F_status_start_s_length             7
    #define F_status_start_not_s_length         11
    #define F_status_stop_s_length              6
    #define F_status_stop_not_s_length          10
    #define F_status_stream_s_length            8
    #define F_status_stream_not_s_length        12
    #define F_status_string_s_length            8
    #define F_status_string_not_s_length        12
    #define F_status_string_too_large_s_length  18
    #define F_status_string_too_small_s_length  18
    #define F_status_success_s_length           9
    #define F_status_success_not_s_length       13
    #define F_status_supported_s_length         11
    #define F_status_supported_not_s_length     15
    #define F_status_syntax_s_length            8
    #define F_status_syntax_not_s_length        12
    #define F_status_thread_s_length            8
    #define F_status_thread_not_s_length        12
    #define F_status_time_s_length              6
    #define F_status_time_not_s_length          10
    #define F_status_time_out_s_length          10
    #define F_status_too_large_s_length         11
    #define F_status_too_small_s_length         11
    #define F_status_type_s_length              6
    #define F_status_type_not_s_length          10
    #define F_status_user_s_length              6
    #define F_status_user_not_s_length          10
    #define F_status_utf_s_length               5
    #define F_status_utf_fragment_s_length      14
    #define F_status_utf_fragment_not_s_length  18
    #define F_status_utf_not_s_length           9
    #define F_status_valid_s_length             7
    #define F_status_valid_not_s_length         11
    #define F_status_value_s_length             7
    #define F_status_value_not_s_length         11
    #define F_status_wait_s_length              6
    #define F_status_wait_not_s_length          10
    #define F_status_warn_s_length              6
    #define F_status_warn_not_s_length          10
    #define F_status_world_s_length             7
    #define F_status_world_not_s_length         11
    #define F_status_write_s_length             7
    #define F_status_write_not_s_length         11
    #define F_status_write_only_s_length        12

    extern const f_string_t f_status_none_s;
    extern const f_string_t f_status_abort_s;
    extern const f_string_t f_status_abort_not_s;
    extern const f_string_t f_status_absolute_s;
    extern const f_string_t f_status_absolute_not_s;
    extern const f_string_t f_status_address_s;
    extern const f_string_t f_status_address_not_s;
    extern const f_string_t f_status_ascii_s;
    extern const f_string_t f_status_ascii_not_s;
    extern const f_string_t f_status_atomic_s;
    extern const f_string_t f_status_atomic_not_s;
    extern const f_string_t f_status_begin_s;
    extern const f_string_t f_status_begin_not_s;
    extern const f_string_t f_status_block_s;
    extern const f_string_t f_status_block_not_s;
    extern const f_string_t f_status_body_s;
    extern const f_string_t f_status_body_not_s;
    extern const f_string_t f_status_bound_s;
    extern const f_string_t f_status_bound_not_s;
    extern const f_string_t f_status_capability_s;
    extern const f_string_t f_status_capability_not_s;
    extern const f_string_t f_status_child_s;
    extern const f_string_t f_status_child_not_s;
    extern const f_string_t f_status_complete_s;
    extern const f_string_t f_status_complete_not_s;
    extern const f_string_t f_status_connect_s;
    extern const f_string_t f_status_connect_not_s;
    extern const f_string_t f_status_connect_refuse_s;
    extern const f_string_t f_status_connect_reset_s;
    extern const f_string_t f_status_container_s;
    extern const f_string_t f_status_container_not_s;
    extern const f_string_t f_status_content_s;
    extern const f_string_t f_status_content_not_s;
    extern const f_string_t f_status_continue_s;
    extern const f_string_t f_status_continue_not_s;
    extern const f_string_t f_status_control_s;
    extern const f_string_t f_status_control_not_s;
    extern const f_string_t f_status_control_group_s;
    extern const f_string_t f_status_control_group_not_s;
    extern const f_string_t f_status_critical_s;
    extern const f_string_t f_status_critical_not_s;
    extern const f_string_t f_status_dead_s;
    extern const f_string_t f_status_dead_not_s;
    extern const f_string_t f_status_deadlock_s;
    extern const f_string_t f_status_deadlock_not_s;
    extern const f_string_t f_status_descriptor_s;
    extern const f_string_t f_status_descriptor_not_s;
    extern const f_string_t f_status_device_s;
    extern const f_string_t f_status_device_not_s;
    extern const f_string_t f_status_disable_s;
    extern const f_string_t f_status_disable_not_s;
    extern const f_string_t f_status_domain_s;
    extern const f_string_t f_status_domain_not_s;
    extern const f_string_t f_status_done_s;
    extern const f_string_t f_status_done_not_s;
    extern const f_string_t f_status_dummy_s;
    extern const f_string_t f_status_dummy_not_s;
    extern const f_string_t f_status_empty_s;
    extern const f_string_t f_status_empty_not_s;
    extern const f_string_t f_status_enable_s;
    extern const f_string_t f_status_enable_not_s;
    extern const f_string_t f_status_encoding_s;
    extern const f_string_t f_status_encoding_not_s;
    extern const f_string_t f_status_end_s;
    extern const f_string_t f_status_end_not_s;
    extern const f_string_t f_status_eoa_s;
    extern const f_string_t f_status_eoa_not_s;
    extern const f_string_t f_status_eof_s;
    extern const f_string_t f_status_eof_not_s;
    extern const f_string_t f_status_eol_s;
    extern const f_string_t f_status_eol_not_s;
    extern const f_string_t f_status_eos_s;
    extern const f_string_t f_status_eos_not_s;
    extern const f_string_t f_status_execute_s;
    extern const f_string_t f_status_execute_not_s;
    extern const f_string_t f_status_exist_s;
    extern const f_string_t f_status_exist_not_s;
    extern const f_string_t f_status_failure_s;
    extern const f_string_t f_status_failure_not_s;
    extern const f_string_t f_status_family_s;
    extern const f_string_t f_status_family_not_s;
    extern const f_string_t f_status_first_s;
    extern const f_string_t f_status_first_not_s;
    extern const f_string_t f_status_footer_s;
    extern const f_string_t f_status_footer_not_s;
    extern const f_string_t f_status_fork_s;
    extern const f_string_t f_status_fork_not_s;
    extern const f_string_t f_status_format_s;
    extern const f_string_t f_status_format_not_s;
    extern const f_string_t f_status_found_s;
    extern const f_string_t f_status_found_not_s;
    extern const f_string_t f_status_full_s;
    extern const f_string_t f_status_full_not_s;
    extern const f_string_t f_status_group_s;
    extern const f_string_t f_status_group_not_s;
    extern const f_string_t f_status_header_s;
    extern const f_string_t f_status_header_not_s;
    extern const f_string_t f_status_ignore_s;
    extern const f_string_t f_status_ignore_not_s;
    extern const f_string_t f_status_implemented_s;
    extern const f_string_t f_status_implemented_not_s;
    extern const f_string_t f_status_input_s;
    extern const f_string_t f_status_input_not_s;
    extern const f_string_t f_status_input_output_s;
    extern const f_string_t f_status_interrupt_s;
    extern const f_string_t f_status_interrupt_not_s;
    extern const f_string_t f_status_known_s;
    extern const f_string_t f_status_known_not_s;
    extern const f_string_t f_status_last_s;
    extern const f_string_t f_status_last_not_s;
    extern const f_string_t f_status_limit_s;
    extern const f_string_t f_status_limit_not_s;
    extern const f_string_t f_status_link_s;
    extern const f_string_t f_status_link_not_s;
    extern const f_string_t f_status_live_s;
    extern const f_string_t f_status_live_not_s;
    extern const f_string_t f_status_lock_s;
    extern const f_string_t f_status_lock_not_s;
    extern const f_string_t f_status_loop_s;
    extern const f_string_t f_status_loop_not_s;
    extern const f_string_t f_status_maybe_s;
    extern const f_string_t f_status_maybe_not_s;
    extern const f_string_t f_status_memory_s;
    extern const f_string_t f_status_memory_not_s;
    extern const f_string_t f_status_message_s;
    extern const f_string_t f_status_message_not_s;
    extern const f_string_t f_status_minor_s;
    extern const f_string_t f_status_minor_not_s;
    extern const f_string_t f_status_moderate_s;
    extern const f_string_t f_status_moderate_not_s;
    extern const f_string_t f_status_mount_s;
    extern const f_string_t f_status_mount_not_s;
    extern const f_string_t f_status_name_s;
    extern const f_string_t f_status_name_not_s;
    extern const f_string_t f_status_next_s;
    extern const f_string_t f_status_next_not_s;
    extern const f_string_t f_status_nice_s;
    extern const f_string_t f_status_nice_not_s;
    extern const f_string_t f_status_object_s;
    extern const f_string_t f_status_object_not_s;
    extern const f_string_t f_status_option_s;
    extern const f_string_t f_status_option_not_s;
    extern const f_string_t f_status_output_s;
    extern const f_string_t f_status_output_not_s;
    extern const f_string_t f_status_packet_s;
    extern const f_string_t f_status_packet_not_s;
    extern const f_string_t f_status_parameter_s;
    extern const f_string_t f_status_parameter_not_s;
    extern const f_string_t f_status_parent_s;
    extern const f_string_t f_status_parent_not_s;
    extern const f_string_t f_status_payload_s;
    extern const f_string_t f_status_payload_not_s;
    extern const f_string_t f_status_previous_s;
    extern const f_string_t f_status_previous_not_s;
    extern const f_string_t f_status_pipe_s;
    extern const f_string_t f_status_pipe_not_s;
    extern const f_string_t f_status_port_s;
    extern const f_string_t f_status_port_not_s;
    extern const f_string_t f_status_processor_s;
    extern const f_string_t f_status_processor_not_s;
    extern const f_string_t f_status_progress_s;
    extern const f_string_t f_status_progress_not_s;
    extern const f_string_t f_status_prohibited_s;
    extern const f_string_t f_status_prohibited_not_s;
    extern const f_string_t f_status_property_s;
    extern const f_string_t f_status_property_not_s;
    extern const f_string_t f_status_protocol_s;
    extern const f_string_t f_status_protocol_not_s;
    extern const f_string_t f_status_range_s;
    extern const f_string_t f_status_range_not_s;
    extern const f_string_t f_status_read_s;
    extern const f_string_t f_status_read_not_s;
    extern const f_string_t f_status_read_only_s;
    extern const f_string_t f_status_ready_s;
    extern const f_string_t f_status_ready_not_s;
    extern const f_string_t f_status_recover_s;
    extern const f_string_t f_status_recover_not_s;
    extern const f_string_t f_status_recurse_s;
    extern const f_string_t f_status_recurse_not_s;
    extern const f_string_t f_status_relative_s;
    extern const f_string_t f_status_relative_not_s;
    extern const f_string_t f_status_require_s;
    extern const f_string_t f_status_require_not_s;
    extern const f_string_t f_status_resource_s;
    extern const f_string_t f_status_resource_not_s;
    extern const f_string_t f_status_search_s;
    extern const f_string_t f_status_search_not_s;
    extern const f_string_t f_status_schedule_s;
    extern const f_string_t f_status_schedule_not_s;
    extern const f_string_t f_status_size_s;
    extern const f_string_t f_status_size_not_s;
    extern const f_string_t f_status_signal_s;
    extern const f_string_t f_status_signal_not_s;
    extern const f_string_t f_status_space_s;
    extern const f_string_t f_status_space_not_s;
    extern const f_string_t f_status_start_s;
    extern const f_string_t f_status_start_not_s;
    extern const f_string_t f_status_stop_s;
    extern const f_string_t f_status_stop_not_s;
    extern const f_string_t f_status_stream_s;
    extern const f_string_t f_status_stream_not_s;
    extern const f_string_t f_status_string_s;
    extern const f_string_t f_status_string_not_s;
    extern const f_string_t f_status_string_too_large_s;
    extern const f_string_t f_status_string_too_small_s;
    extern const f_string_t f_status_syntax_s;
    extern const f_string_t f_status_syntax_not_s;
    extern const f_string_t f_status_thread_s;
    extern const f_string_t f_status_thread_not_s;
    extern const f_string_t f_status_time_s;
    extern const f_string_t f_status_time_not_s;
    extern const f_string_t f_status_time_out_s;
    extern const f_string_t f_status_too_large_s;
    extern const f_string_t f_status_too_small_s;
    extern const f_string_t f_status_type_s;
    extern const f_string_t f_status_type_not_s;
    extern const f_string_t f_status_success_s;
    extern const f_string_t f_status_success_not_s;
    extern const f_string_t f_status_supported_s;
    extern const f_string_t f_status_supported_not_s;
    extern const f_string_t f_status_user_s;
    extern const f_string_t f_status_user_not_s;
    extern const f_string_t f_status_utf_s;
    extern const f_string_t f_status_utf_fragment_s;
    extern const f_string_t f_status_utf_fragment_not_s;
    extern const f_string_t f_status_utf_not_s;
    extern const f_string_t f_status_valid_s;
    extern const f_string_t f_status_valid_not_s;
    extern const f_string_t f_status_value_s;
    extern const f_string_t f_status_value_not_s;
    extern const f_string_t f_status_wait_s;
    extern const f_string_t f_status_wait_not_s;
    extern const f_string_t f_status_warn_s;
    extern const f_string_t f_status_warn_not_s;
    extern const f_string_t f_status_world_s;
    extern const f_string_t f_status_world_not_s;
    extern const f_string_t f_status_write_s;
    extern const f_string_t f_status_write_not_s;
    extern const f_string_t f_status_write_only_s;
  #endif // _di_F_status_basic_

  #ifndef _di_F_status_array_
    #define F_status_array_s           "F_array"
    #define F_status_array_not_s       "F_array_not"
    #define F_status_array_too_large_s "F_array_too_large"
    #define F_status_array_too_small_s "F_array_too_small"

    #define F_status_array_s_length           7
    #define F_status_array_not_s_length       11
    #define F_status_array_too_large_s_length 17
    #define F_status_array_too_small_s_length 17

    extern const f_string_t f_status_array_s;
    extern const f_string_t f_status_array_not_s;
    extern const f_string_t f_status_array_too_large_s;
    extern const f_string_t f_status_array_too_small_s;
  #endif // _di_F_status_array_

  #ifndef _di_F_status_available_
    #define F_status_available_s             "F_available"
    #define F_status_available_not_s         "F_available_not"
    #define F_status_available_not_address_s "F_available_not_address"
    #define F_status_available_not_buffer_s  "F_available_not_buffer"
    #define F_status_available_not_device_s  "F_available_not_device"
    #define F_status_available_not_pipe_s    "F_available_not_pipe"
    #define F_status_available_not_port_s    "F_available_not_port"
    #define F_status_available_not_process_s "F_available_not_process"
    #define F_status_available_not_socket_s  "F_available_not_socket"

    #define F_status_available_s_length             11
    #define F_status_available_not_s_length         15
    #define F_status_available_not_address_s_length 23
    #define F_status_available_not_buffer_s_length  22
    #define F_status_available_not_device_s_length  22
    #define F_status_available_not_pipe_s_length    20
    #define F_status_available_not_port_s_length    20
    #define F_status_available_not_process_s_length 23
    #define F_status_available_not_socket_s_length  22

    extern const f_string_t f_status_available_s;
    extern const f_string_t f_status_available_not_s;
    extern const f_string_t f_status_available_not_address_s;
    extern const f_string_t f_status_available_not_buffer_s;
    extern const f_string_t f_status_available_not_device_s;
    extern const f_string_t f_status_available_not_pipe_s;
    extern const f_string_t f_status_available_not_port_s;
    extern const f_string_t f_status_available_not_process_s;
    extern const f_string_t f_status_available_not_socket_s;
  #endif // _di_F_status_available_

  #ifndef _di_F_status_busy_
    #define F_status_busy_s         "F_busy"
    #define F_status_busy_address_s "F_busy_address"
    #define F_status_busy_buffer_s  "F_busy_buffer"
    #define F_status_busy_device_s  "F_busy_device"
    #define F_status_busy_not_s     "F_busy_not"
    #define F_status_busy_pipe_s    "F_busy_pipe"
    #define F_status_busy_port_s    "F_busy_port"
    #define F_status_busy_process_s "F_busy_process"
    #define F_status_busy_socket_s  "F_busy_socket"

    #define F_status_busy_s_length         6
    #define F_status_busy_address_s_length 14
    #define F_status_busy_buffer_s_length  13
    #define F_status_busy_device_s_length  13
    #define F_status_busy_not_s_length     10
    #define F_status_busy_pipe_s_length    11
    #define F_status_busy_port_s_length    11
    #define F_status_busy_process_s_length 14
    #define F_status_busy_socket_s_length  13

    extern const f_string_t f_status_busy_s;
    extern const f_string_t f_status_busy_address_s;
    extern const f_string_t f_status_busy_buffer_s;
    extern const f_string_t f_status_busy_device_s;
    extern const f_string_t f_status_busy_not_s;
    extern const f_string_t f_status_busy_pipe_s;
    extern const f_string_t f_status_busy_port_s;
    extern const f_string_t f_status_busy_process_s;
    extern const f_string_t f_status_busy_socket_s;
  #endif // _di_F_status_busy_

  #ifndef _di_F_status_network_
    #define F_status_network_s                  "F_network"
    #define F_status_network_busy_s             "F_network_busy"
    #define F_status_network_busy_not_s         "F_network_busy_not"
    #define F_status_network_client_s           "F_network_client"
    #define F_status_network_client_not_s       "F_network_client_not"
    #define F_status_network_device_s           "F_network_device"
    #define F_status_network_device_not_s       "F_network_device_not"
    #define F_status_network_found_s            "F_network_found"
    #define F_status_network_found_not_s        "F_network_found_not"
    #define F_status_network_lost_s             "F_network_lost"
    #define F_status_network_lost_not_s         "F_network_lost_not"
    #define F_status_network_not_s              "F_network_not"
    #define F_status_network_reach_s            "F_network_reach"
    #define F_status_network_reach_client_s     "F_network_reach_client"
    #define F_status_network_reach_client_not_s "F_network_reach_client_not"
    #define F_status_network_reach_not_s        "F_network_reach_not"
    #define F_status_network_reach_server_s     "F_network_reach_server"
    #define F_status_network_reach_server_not_s "F_network_reach_server_not"
    #define F_status_network_server_s           "F_network_server"
    #define F_status_network_server_not_s       "F_network_server_not"
    #define F_status_network_time_s             "F_network_time"
    #define F_status_network_time_not_s         "F_network_time_not"

    #define F_status_network_s_length                  9
    #define F_status_network_busy_s_length             14
    #define F_status_network_busy_not_s_length         18
    #define F_status_network_client_s_length           16
    #define F_status_network_client_not_s_length       20
    #define F_status_network_device_s_length           16
    #define F_status_network_device_not_s_length       20
    #define F_status_network_found_s_length            15
    #define F_status_network_found_not_s_length        19
    #define F_status_network_lost_s_length             14
    #define F_status_network_lost_not_s_length         18
    #define F_status_network_not_s_length              13
    #define F_status_network_reach_s_length            15
    #define F_status_network_reach_client_s_length     22
    #define F_status_network_reach_client_not_s_length 26
    #define F_status_network_reach_not_s_length        19
    #define F_status_network_reach_server_s_length     22
    #define F_status_network_reach_server_not_s_length 26
    #define F_status_network_server_s_length           16
    #define F_status_network_server_not_s_length       20
    #define F_status_network_time_s_length             14
    #define F_status_network_time_not_s_length         18

    extern const f_string_t f_status_network_s;
    extern const f_string_t f_status_network_busy_s;
    extern const f_string_t f_status_network_busy_not_s;
    extern const f_string_t f_status_network_client_s;
    extern const f_string_t f_status_network_client_not_s;
    extern const f_string_t f_status_network_device_s;
    extern const f_string_t f_status_network_device_not_s;
    extern const f_string_t f_status_network_found_s;
    extern const f_string_t f_status_network_found_not_s;
    extern const f_string_t f_status_network_lost_s;
    extern const f_string_t f_status_network_lost_not_s;
    extern const f_string_t f_status_network_not_s;
    extern const f_string_t f_status_network_reach_s;
    extern const f_string_t f_status_network_reach_client_s;
    extern const f_string_t f_status_network_reach_client_not_s;
    extern const f_string_t f_status_network_reach_not_s;
    extern const f_string_t f_status_network_reach_server_s;
    extern const f_string_t f_status_network_reach_server_not_s;
    extern const f_string_t f_status_network_server_s;
    extern const f_string_t f_status_network_server_not_s;
    extern const f_string_t f_status_network_time_s;
    extern const f_string_t f_status_network_time_not_s;
  #endif // _di_F_status_network_

  #ifndef _di_F_status_number_
    #define F_status_number_s                "F_number"
    #define F_status_number_decimal_s        "F_number_decimal"
    #define F_status_number_decimal_not_s    "F_number_decimal_not"
    #define F_status_number_divide_by_zero_s "F_number_divide_by_zero"
    #define F_status_number_negative_s       "F_number_negative"
    #define F_status_number_negative_not_s   "F_number_negative_not"
    #define F_status_number_not_s            "F_number_not"
    #define F_status_number_overflow_s       "F_number_overflow"
    #define F_status_number_positive_s       "F_number_positive"
    #define F_status_number_positive_not_s   "F_number_positive_not"
    #define F_status_number_too_large_s      "F_number_too_large"
    #define F_status_number_too_small_s      "F_number_too_small"
    #define F_status_number_underflow_s      "F_number_underflow"
    #define F_status_number_whole_s          "F_number_whole"
    #define F_status_number_whole_not_s      "F_number_whole_not"
    #define F_status_number_zero_s           "F_number_zero"
    #define F_status_number_zero_not_s       "F_number_zero_not"

    #define F_status_number_s_length                8
    #define F_status_number_decimal_s_length        16
    #define F_status_number_decimal_not_s_length    20
    #define F_status_number_divide_by_zero_s_length 23
    #define F_status_number_negative_s_length       17
    #define F_status_number_negative_not_s_length   21
    #define F_status_number_not_s_length            12
    #define F_status_number_overflow_s_length       17
    #define F_status_number_positive_s_length       17
    #define F_status_number_positive_not_s_length   21
    #define F_status_number_too_large_s_length      18
    #define F_status_number_too_small_s_length      18
    #define F_status_number_underflow_s_length      18
    #define F_status_number_whole_s_length          14
    #define F_status_number_whole_not_s_length      18
    #define F_status_number_zero_s_length           13
    #define F_status_number_zero_not_s_length       17

    extern const f_string_t f_status_number_s;
    extern const f_string_t f_status_number_decimal_s;
    extern const f_string_t f_status_number_decimal_not_s;
    extern const f_string_t f_status_number_divide_by_zero_s;
    extern const f_string_t f_status_number_negative_s;
    extern const f_string_t f_status_number_negative_not_s;
    extern const f_string_t f_status_number_not_s;
    extern const f_string_t f_status_number_overflow_s;
    extern const f_string_t f_status_number_positive_s;
    extern const f_string_t f_status_number_positive_not_s;
    extern const f_string_t f_status_number_too_large_s;
    extern const f_string_t f_status_number_too_small_s;
    extern const f_string_t f_status_number_underflow_s;
    extern const f_string_t f_status_number_whole_s;
    extern const f_string_t f_status_number_whole_not_s;
    extern const f_string_t f_status_number_zero_s;
    extern const f_string_t f_status_number_zero_not_s;
  #endif // _di_F_status_number_

  #ifndef _di_F_status_buffer_
    #define F_status_buffer_s                     "F_buffer"
    #define F_status_buffer_not_s                 "F_buffer_not"
    #define F_status_buffer_too_large_s           "F_buffer_too_large"
    #define F_status_buffer_too_small_s           "F_buffer_too_small"
    #define F_status_complete_not_utf_s           "F_complete_not_utf"
    #define F_status_complete_not_utf_block_s     "F_complete_not_utf_block"
    #define F_status_complete_not_utf_eoa_s       "F_complete_not_utf_eoa"
    #define F_status_complete_not_utf_eof_s       "F_complete_not_utf_eof"
    #define F_status_complete_not_utf_eol_s       "F_complete_not_utf_eol"
    #define F_status_complete_not_utf_eos_s       "F_complete_not_utf_eos"
    #define F_status_complete_not_utf_stop_s      "F_complete_not_utf_stop"
    #define F_status_none_block_s                 "F_none_block"
    #define F_status_none_eoa_s                   "F_none_eoa"
    #define F_status_none_eof_s                   "F_none_eof"
    #define F_status_none_eol_s                   "F_none_eol"
    #define F_status_none_eos_s                   "F_none_eos"
    #define F_status_none_not_s                   "F_none_not"
    #define F_status_none_stop_s                  "F_none_stop"
    #define F_status_data_s                       "F_data"
    #define F_status_data_not_s                   "F_data_not"
    #define F_status_data_not_block_s             "F_data_not_block"
    #define F_status_data_not_eoa_s               "F_data_not_eoa"
    #define F_status_data_not_eof_s               "F_data_not_eof"
    #define F_status_data_not_eol_s               "F_data_not_eol"
    #define F_status_data_not_eos_s               "F_data_not_eos"
    #define F_status_data_not_stop_s              "F_data_not_stop"
    #define F_status_terminated_s                 "F_terminated"
    #define F_status_terminated_not_s             "F_terminated_not"
    #define F_status_terminated_not_block_s       "F_terminated_not_block"
    #define F_status_terminated_not_eoa_s         "F_terminated_not_eoa"
    #define F_status_terminated_not_eof_s         "F_terminated_not_eof"
    #define F_status_terminated_not_eol_s         "F_terminated_not_eol"
    #define F_status_terminated_not_eos_s         "F_terminated_not_eos"
    #define F_status_terminated_not_stop_s        "F_terminated_not_stop"
    #define F_status_terminated_not_group_s       "F_terminated_not_group"
    #define F_status_terminated_not_group_block_s "F_terminated_not_group_block"
    #define F_status_terminated_not_group_eoa_s   "F_terminated_not_group_eoa"
    #define F_status_terminated_not_group_eof_s   "F_terminated_not_group_eof"
    #define F_status_terminated_not_group_eol_s   "F_terminated_not_group_eol"
    #define F_status_terminated_not_group_eos_s   "F_terminated_not_group_eos"
    #define F_status_terminated_not_group_stop_s  "F_terminated_not_group_stop"
    #define F_status_terminated_not_nest_s        "F_terminated_not_nest"
    #define F_status_terminated_not_nest_block_s  "F_terminated_not_nest_block"
    #define F_status_terminated_not_nest_eoa_s    "F_terminated_not_nest_eoa"
    #define F_status_terminated_not_nest_eof_s    "F_terminated_not_nest_eof"
    #define F_status_terminated_not_nest_eol_s    "F_terminated_not_nest_eol"
    #define F_status_terminated_not_nest_eos_s    "F_terminated_not_nest_eos"
    #define F_status_terminated_not_nest_stop_s   "F_terminated_not_nest_stop"

    #define F_status_buffer_s_length                     8
    #define F_status_buffer_not_s_length                 12
    #define F_status_buffer_too_large_s_length           18
    #define F_status_buffer_too_small_s_length           18
    #define F_status_complete_not_utf_s_length           18
    #define F_status_complete_not_utf_block_s_length     24
    #define F_status_complete_not_utf_eoa_s_length       22
    #define F_status_complete_not_utf_eof_s_length       22
    #define F_status_complete_not_utf_eol_s_length       22
    #define F_status_complete_not_utf_eos_s_length       22
    #define F_status_complete_not_utf_stop_s_length      23
    #define F_status_none_block_s_length                 12
    #define F_status_none_eoa_s_length                   10
    #define F_status_none_eof_s_length                   10
    #define F_status_none_eol_s_length                   10
    #define F_status_none_eos_s_length                   10
    #define F_status_none_stop_s_length                  11
    #define F_status_data_s_length                       6
    #define F_status_data_not_s_length                   10
    #define F_status_data_not_block_s_length             16
    #define F_status_data_not_eoa_s_length               14
    #define F_status_data_not_eof_s_length               14
    #define F_status_data_not_eol_s_length               14
    #define F_status_data_not_eos_s_length               14
    #define F_status_data_not_stop_s_length              15
    #define F_status_terminated_s_length                 12
    #define F_status_terminated_not_s_length             16
    #define F_status_terminated_not_block_s_length       22
    #define F_status_terminated_not_eoa_s_length         20
    #define F_status_terminated_not_eof_s_length         20
    #define F_status_terminated_not_eol_s_length         20
    #define F_status_terminated_not_eos_s_length         20
    #define F_status_terminated_not_stop_s_length        21
    #define F_status_terminated_not_group_s_length       22
    #define F_status_terminated_not_group_block_s_length 28
    #define F_status_terminated_not_group_eoa_s_length   25
    #define F_status_terminated_not_group_eof_s_length   25
    #define F_status_terminated_not_group_eol_s_length   25
    #define F_status_terminated_not_group_eos_s_length   25
    #define F_status_terminated_not_group_stop_s_length  26
    #define F_status_terminated_not_nest_s_length        21
    #define F_status_terminated_not_nest_block_s_length  26
    #define F_status_terminated_not_nest_eoa_s_length    25
    #define F_status_terminated_not_nest_eof_s_length    25
    #define F_status_terminated_not_nest_eol_s_length    25
    #define F_status_terminated_not_nest_eos_s_length    25
    #define F_status_terminated_not_nest_stop_s_length   26

    extern const f_string_t f_status_buffer_s;
    extern const f_string_t f_status_buffer_not_s;
    extern const f_string_t f_status_buffer_too_large_s;
    extern const f_string_t f_status_buffer_too_small_s;
    extern const f_string_t f_status_complete_not_utf_s;
    extern const f_string_t f_status_complete_not_utf_block_s;
    extern const f_string_t f_status_complete_not_utf_eoa_s;
    extern const f_string_t f_status_complete_not_utf_eof_s;
    extern const f_string_t f_status_complete_not_utf_eol_s;
    extern const f_string_t f_status_complete_not_utf_eos_s;
    extern const f_string_t f_status_complete_not_utf_stop_s;
    extern const f_string_t f_status_none_block_s;
    extern const f_string_t f_status_none_eoa_s;
    extern const f_string_t f_status_none_eof_s;
    extern const f_string_t f_status_none_eol_s;
    extern const f_string_t f_status_none_eos_s;
    extern const f_string_t f_status_none_not_s;
    extern const f_string_t f_status_none_stop_s;
    extern const f_string_t f_status_data_s;
    extern const f_string_t f_status_data_not_s;
    extern const f_string_t f_status_data_not_block_s;
    extern const f_string_t f_status_data_not_eoa_s;
    extern const f_string_t f_status_data_not_eof_s;
    extern const f_string_t f_status_data_not_eol_s;
    extern const f_string_t f_status_data_not_eos_s;
    extern const f_string_t f_status_data_not_stop_s;
    extern const f_string_t f_status_terminated_s;
    extern const f_string_t f_status_terminated_not_s;
    extern const f_string_t f_status_terminated_not_block_s;
    extern const f_string_t f_status_terminated_not_eoa_s;
    extern const f_string_t f_status_terminated_not_eof_s;
    extern const f_string_t f_status_terminated_not_eol_s;
    extern const f_string_t f_status_terminated_not_eos_s;
    extern const f_string_t f_status_terminated_not_stop_s;
    extern const f_string_t f_status_terminated_not_group_s;
    extern const f_string_t f_status_terminated_not_group_block_s;
    extern const f_string_t f_status_terminated_not_group_eoa_s;
    extern const f_string_t f_status_terminated_not_group_eof_s;
    extern const f_string_t f_status_terminated_not_group_eol_s;
    extern const f_string_t f_status_terminated_not_group_eos_s;
    extern const f_string_t f_status_terminated_not_group_stop_s;
    extern const f_string_t f_status_terminated_not_nest_s;
    extern const f_string_t f_status_terminated_not_nest_block_s;
    extern const f_string_t f_status_terminated_not_nest_eoa_s;
    extern const f_string_t f_status_terminated_not_nest_eof_s;
    extern const f_string_t f_status_terminated_not_nest_eol_s;
    extern const f_string_t f_status_terminated_not_nest_eos_s;
    extern const f_string_t f_status_terminated_not_nest_stop_s;
  #endif // _di_F_status_buffer_

  #ifndef _di_F_status_process_
    #define F_status_process_s          "F_process"
    #define F_status_process_not_s      "F_process_not"
    #define F_status_process_too_many_s "F_process_too_many"

    #define F_status_process_s_length          9
    #define F_status_process_not_s_length      13
    #define F_status_process_too_many_s_length 18

    extern const f_string_t f_status_process_s;
    extern const f_string_t f_status_process_not_s;
    extern const f_string_t f_status_process_too_many_s;
  #endif // _di_F_status_process_

  #ifndef _di_F_status_file_
    #define F_status_file_s                    "F_file"
    #define F_status_file_close_s              "F_file_close"
    #define F_status_file_closed_s             "F_file_closed"
    #define F_status_file_descriptor_s         "F_file_descriptor"
    #define F_status_file_descriptor_max_s     "F_file_descriptor_max"
    #define F_status_file_descriptor_not_s     "F_file_descriptor_not"
    #define F_status_file_empty_s              "F_file_empty"
    #define F_status_file_flush_s              "F_file_flush"
    #define F_status_file_found_s              "F_file_found"
    #define F_status_file_found_not_s          "F_file_found_not"
    #define F_status_file_not_s                "F_file_not"
    #define F_status_file_open_s               "F_file_open"
    #define F_status_file_open_max_s           "F_file_open_max"
    #define F_status_file_opened_s             "F_file_opened"
    #define F_status_file_overflow_s           "F_file_overflow"
    #define F_status_file_purge_s              "F_file_purge"
    #define F_status_file_read_s               "F_file_read"
    #define F_status_file_reallocation_s       "F_file_reallocation"
    #define F_status_file_seek_s               "F_file_seek"
    #define F_status_file_stat_s               "F_file_stat"
    #define F_status_file_synchronize_s        "F_file_synchronize"
    #define F_status_file_type_block_s         "F_file_type_block"
    #define F_status_file_type_character_s     "F_file_type_character"
    #define F_status_file_type_directory_s     "F_file_type_directory"
    #define F_status_file_type_fifo_s          "F_file_type_fifo"
    #define F_status_file_type_link_s          "F_file_type_link"
    #define F_status_file_type_not_block_s     "F_file_type_not_block"
    #define F_status_file_type_not_character_s "F_file_type_not_character"
    #define F_status_file_type_not_directory_s "F_file_type_not_directory"
    #define F_status_file_type_not_fifo_s      "F_file_type_not_fifo"
    #define F_status_file_type_not_link_s      "F_file_type_not_link"
    #define F_status_file_type_not_pipe_s      "F_file_type_not_pipe"
    #define F_status_file_type_not_regular_s   "F_file_type_not_regular"
    #define F_status_file_type_not_socket_s    "F_file_type_not_socket"
    #define F_status_file_type_not_unknown_s   "F_file_type_not_unknown"
    #define F_status_file_type_pipe_s          "F_file_type_pipe"
    #define F_status_file_type_regular_s       "F_file_type_regular"
    #define F_status_file_type_socket_s        "F_file_type_socket"
    #define F_status_file_type_unknown_s       "F_file_type_unknown"
    #define F_status_file_underflow_s          "F_file_underflow"
    #define F_status_file_utf_s                "F_file_utf"
    #define F_status_file_utf_not_s            "F_file_utf_not"
    #define F_status_file_write_s              "F_file_write"

    #define F_status_file_s_length                    6
    #define F_status_file_close_s_length              12
    #define F_status_file_closed_s_length             13
    #define F_status_file_descriptor_s_length         17
    #define F_status_file_descriptor_max_s_length     21
    #define F_status_file_descriptor_not_s_length     21
    #define F_status_file_empty_s_length              12
    #define F_status_file_flush_s_length              12
    #define F_status_file_found_s_length              12
    #define F_status_file_found_not_s_length          16
    #define F_status_file_not_s_length                10
    #define F_status_file_open_s_length               11
    #define F_status_file_open_max_s_length           15
    #define F_status_file_opened_s_length             13
    #define F_status_file_overflow_s_length           15
    #define F_status_file_purge_s_length              12
    #define F_status_file_read_s_length               11
    #define F_status_file_reallocation_s_length       19
    #define F_status_file_seek_s_length               11
    #define F_status_file_stat_s_length               11
    #define F_status_file_synchronize_s_length        18
    #define F_status_file_type_block_s_length         17
    #define F_status_file_type_character_s_length     21
    #define F_status_file_type_directory_s_length     21
    #define F_status_file_type_fifo_s_length          16
    #define F_status_file_type_link_s_length          16
    #define F_status_file_type_not_block_s_length     21
    #define F_status_file_type_not_character_s_length 25
    #define F_status_file_type_not_directory_s_length 25
    #define F_status_file_type_not_fifo_s_length      20
    #define F_status_file_type_not_link_s_length      20
    #define F_status_file_type_not_pipe_s_length      20
    #define F_status_file_type_not_regular_s_length   23
    #define F_status_file_type_not_socket_s_length    22
    #define F_status_file_type_not_unknown_s_length   23
    #define F_status_file_type_pipe_s_length          16
    #define F_status_file_type_regular_s_length       19
    #define F_status_file_type_socket_s_length        18
    #define F_status_file_type_unknown_s_length       19
    #define F_status_file_underflow_s_length          16
    #define F_status_file_utf_s_length                10
    #define F_status_file_utf_not_s_length            14
    #define F_status_file_write_s_length              12

    extern const f_string_t f_status_file_s;
    extern const f_string_t f_status_file_close_s;
    extern const f_string_t f_status_file_closed_s;
    extern const f_string_t f_status_file_descriptor_s;
    extern const f_string_t f_status_file_descriptor_max_s;
    extern const f_string_t f_status_file_descriptor_not_s;
    extern const f_string_t f_status_file_empty_s;
    extern const f_string_t f_status_file_flush_s;
    extern const f_string_t f_status_file_found_s;
    extern const f_string_t f_status_file_found_not_s;
    extern const f_string_t f_status_file_not_s;
    extern const f_string_t f_status_file_open_s;
    extern const f_string_t f_status_file_open_max_s;
    extern const f_string_t f_status_file_opened_s;
    extern const f_string_t f_status_file_overflow_s;
    extern const f_string_t f_status_file_purge_s;
    extern const f_string_t f_status_file_read_s;
    extern const f_string_t f_status_file_reallocation_s;
    extern const f_string_t f_status_file_seek_s;
    extern const f_string_t f_status_file_stat_s;
    extern const f_string_t f_status_file_synchronize_s;
    extern const f_string_t f_status_file_type_block_s;
    extern const f_string_t f_status_file_type_character_s;
    extern const f_string_t f_status_file_type_directory_s;
    extern const f_string_t f_status_file_type_fifo_s;
    extern const f_string_t f_status_file_type_link_s;
    extern const f_string_t f_status_file_type_not_block_s;
    extern const f_string_t f_status_file_type_not_character_s;
    extern const f_string_t f_status_file_type_not_directory_s;
    extern const f_string_t f_status_file_type_not_fifo_s;
    extern const f_string_t f_status_file_type_not_link_s;
    extern const f_string_t f_status_file_type_not_pipe_s;
    extern const f_string_t f_status_file_type_not_regular_s;
    extern const f_string_t f_status_file_type_not_socket_s;
    extern const f_string_t f_status_file_type_not_unknown_s;
    extern const f_string_t f_status_file_type_pipe_s;
    extern const f_string_t f_status_file_type_regular_s;
    extern const f_string_t f_status_file_type_socket_s;
    extern const f_string_t f_status_file_type_unknown_s;
    extern const f_string_t f_status_file_underflow_s;
    extern const f_string_t f_status_file_utf_s;
    extern const f_string_t f_status_file_utf_not_s;
    extern const f_string_t f_status_file_write_s;
  #endif // _di_F_status_file_

  #ifndef _di_F_status_filesystem_
    #define F_status_filesystem_s               "F_filesystem"
    #define F_status_filesystem_not_s           "F_filesystem_not"
    #define F_status_filesystem_quota_block_s   "F_filesystem_quota_block"
    #define F_status_filesystem_quota_reached_s "F_filesystem_quota_reached"

    #define F_status_filesystem_s_length               12
    #define F_status_filesystem_not_s_length           16
    #define F_status_filesystem_quota_block_s_length   24
    #define F_status_filesystem_quota_reached_s_length 26

    extern const f_string_t f_status_filesystem_s;
    extern const f_string_t f_status_filesystem_not_s;
    extern const f_string_t f_status_filesystem_quota_block_s;
    extern const f_string_t f_status_filesystem_quota_reached_s;
  #endif // _di_F_status_filesystem_

  #ifndef _di_F_status_directory_
    #define F_status_directory_s               "F_directory"
    #define F_status_directory_close_s         "F_directory_close"
    #define F_status_directory_closed_s        "F_directory_closed"
    #define F_status_directory_descriptor_s    "F_directory_descriptor"
    #define F_status_directory_empty_s         "F_directory_empty"
    #define F_status_directory_empty_not_s     "F_directory_empty_not"
    #define F_status_directory_found_s         "F_directory_found"
    #define F_status_directory_found_not_s     "F_directory_found_not"
    #define F_status_directory_flush_s         "F_directory_flush"
    #define F_status_directory_link_max_s      "F_directory_link_max"
    #define F_status_directory_not_s           "F_directory_not"
    #define F_status_directory_open_s          "F_directory_open"
    #define F_status_directory_purge_s         "F_directory_purge"
    #define F_status_directory_read_s          "F_directory_read"
    #define F_status_directory_stream_s        "F_directory_stream"
    #define F_status_directory_supported_not_s "F_directory_supported_not"
    #define F_status_directory_synchronize_s   "F_directory_synchronize"
    #define F_status_directory_utf_s           "F_directory_utf"
    #define F_status_directory_utf_not_s       "F_directory_utf_not"
    #define F_status_directory_write_s         "F_directory_write"

    #define F_status_directory_s_length               11
    #define F_status_directory_close_s_length         17
    #define F_status_directory_closed_s_length        18
    #define F_status_directory_descriptor_s_length    22
    #define F_status_directory_empty_s_length         17
    #define F_status_directory_empty_not_s_length     21
    #define F_status_directory_found_s_length         17
    #define F_status_directory_found_not_s_length     21
    #define F_status_directory_flush_s_length         17
    #define F_status_directory_link_max_s_length      20
    #define F_status_directory_not_s_length           15
    #define F_status_directory_open_s_length          16
    #define F_status_directory_purge_s_length         17
    #define F_status_directory_read_s_length          16
    #define F_status_directory_stream_s_length        18
    #define F_status_directory_supported_not_s_length 25
    #define F_status_directory_synchronize_s_length   23
    #define F_status_directory_utf_s_length           15
    #define F_status_directory_utf_not_s_length       19
    #define F_status_directory_write_s_length         17

    extern const f_string_t f_status_directory_s;
    extern const f_string_t f_status_directory_close_s;
    extern const f_string_t f_status_directory_closed_s;
    extern const f_string_t f_status_directory_descriptor_s;
    extern const f_string_t f_status_directory_empty_s;
    extern const f_string_t f_status_directory_empty_not_s;
    extern const f_string_t f_status_directory_found_s;
    extern const f_string_t f_status_directory_found_not_s;
    extern const f_string_t f_status_directory_flush_s;
    extern const f_string_t f_status_directory_link_max_s;
    extern const f_string_t f_status_directory_not_s;
    extern const f_string_t f_status_directory_open_s;
    extern const f_string_t f_status_directory_purge_s;
    extern const f_string_t f_status_directory_read_s;
    extern const f_string_t f_status_directory_stream_s;
    extern const f_string_t f_status_directory_supported_not_s;
    extern const f_string_t f_status_directory_synchronize_s;
    extern const f_string_t f_status_directory_utf_s;
    extern const f_string_t f_status_directory_utf_not_s;
    extern const f_string_t f_status_directory_write_s;
  #endif // _di_F_status_directory_

  #ifndef _di_F_status_socket_
    #define F_status_socket_s         "F_socket"
    #define F_status_socket_client_s  "F_socket_client"
    #define F_status_socket_not_s     "F_socket_not"
    #define F_status_socket_receive_s "F_socket_receive"
    #define F_status_socket_send_s    "F_socket_send"
    #define F_status_socket_target_s  "F_socket_target"

    #define F_status_socket_s_length         8
    #define F_status_socket_client_s_length  15
    #define F_status_socket_not_s_length     12
    #define F_status_socket_receive_s_length 16
    #define F_status_socket_send_s_length    13
    #define F_status_socket_target_s_length  15

    extern const f_string_t f_status_socket_s;
    extern const f_string_t f_status_socket_client_s;
    extern const f_string_t f_status_socket_not_s;
    extern const f_string_t f_status_socket_receive_s;
    extern const f_string_t f_status_socket_send_s;
    extern const f_string_t f_status_socket_target_s;
  #endif // _di_F_status_socket_

  #ifndef _di_F_status_compare_
    #define F_status_equal_to_s     "F_equal_to"
    #define F_status_equal_to_not_s "F_equal_to_not"
    #define F_status_than_greater_s "F_than_greater"
    #define F_status_than_less_s    "F_than_less"

    #define F_status_equal_to_s_length     10
    #define F_status_equal_to_not_s_length 14
    #define F_status_than_greater_s_length 14
    #define F_status_than_less_s_length    11

    extern const f_string_t f_status_equal_to_s;
    extern const f_string_t f_status_equal_to_not_s;
    extern const f_string_t f_status_than_greater_s;
    extern const f_string_t f_status_than_less_s;
  #endif // _di_F_status_compare_

  #ifndef _di_F_status_access_
    #define F_status_access_s                 "F_access"
    #define F_status_access_denied_s          "F_access_denied"
    #define F_status_access_denied_user_s     "F_access_denied_user"
    #define F_status_access_denied_group_s    "F_access_denied_group"
    #define F_status_access_denied_world_s    "F_access_denied_world"
    #define F_status_access_denied_read_s     "F_access_denied_read"
    #define F_status_access_denied_write_s    "F_access_denied_write"
    #define F_status_access_denied_execute_s  "F_access_denied_execute"
    #define F_status_access_denied_super_s    "F_access_denied_super"
    #define F_status_access_granted_s         "F_access_granted"
    #define F_status_access_granted_user_s    "F_access_granted_user"
    #define F_status_access_granted_group_s   "F_access_granted_group"
    #define F_status_access_granted_world_s   "F_access_granted_world"
    #define F_status_access_granted_read_s    "F_access_granted_read"
    #define F_status_access_granted_write_s   "F_access_granted_write"
    #define F_status_access_granted_execute_s "F_access_granted_execute"
    #define F_status_access_granted_super_s   "F_access_granted_super"
    #define F_status_access_group_s           "F_access_group"
    #define F_status_access_mode_s            "F_access_mode"
    #define F_status_access_not_s             "F_access_not"
    #define F_status_access_owner_s           "F_access_owner"

    #define F_status_access_s_length                 8
    #define F_status_access_denied_s_length          15
    #define F_status_access_denied_user_s_length     20
    #define F_status_access_denied_group_s_length    21
    #define F_status_access_denied_world_s_length    21
    #define F_status_access_denied_read_s_length     20
    #define F_status_access_denied_write_s_length    21
    #define F_status_access_denied_execute_s_length  23
    #define F_status_access_denied_super_s_length    21
    #define F_status_access_granted_s_length         16
    #define F_status_access_granted_user_s_length    21
    #define F_status_access_granted_group_s_length   22
    #define F_status_access_granted_world_s_length   22
    #define F_status_access_granted_read_s_length    21
    #define F_status_access_granted_write_s_length   22
    #define F_status_access_granted_execute_s_length 24
    #define F_status_access_granted_super_s_length   22
    #define F_status_access_group_s_length           14
    #define F_status_access_mode_s_length            13
    #define F_status_access_not_s_length             12
    #define F_status_access_owner_s_length           14

    extern const f_string_t f_status_access_s;
    extern const f_string_t f_status_access_denied_s;
    extern const f_string_t f_status_access_denied_user_s;
    extern const f_string_t f_status_access_denied_group_s;
    extern const f_string_t f_status_access_denied_world_s;
    extern const f_string_t f_status_access_denied_read_s;
    extern const f_string_t f_status_access_denied_write_s;
    extern const f_string_t f_status_access_denied_execute_s;
    extern const f_string_t f_status_access_denied_super_s;
    extern const f_string_t f_status_access_granted_s;
    extern const f_string_t f_status_access_granted_user_s;
    extern const f_string_t f_status_access_granted_group_s;
    extern const f_string_t f_status_access_granted_world_s;
    extern const f_string_t f_status_access_granted_read_s;
    extern const f_string_t f_status_access_granted_write_s;
    extern const f_string_t f_status_access_granted_execute_s;
    extern const f_string_t f_status_access_granted_super_s;
    extern const f_string_t f_status_access_group_s;
    extern const f_string_t f_status_access_mode_s;
    extern const f_string_t f_status_access_not_s;
    extern const f_string_t f_status_access_owner_s;
  #endif // _di_F_status_access_

  #ifndef _di_F_status_terminal_
    #define F_status_terminal_s            "F_terminal"
    #define F_status_terminal_access_s     "F_terminal_access"
    #define F_status_terminal_known_s      "F_terminal_known"
    #define F_status_terminal_known_not_s  "F_terminal_known_not"
    #define F_status_terminal_not_s        "F_terminal_not"
    #define F_status_terminal_prohibited_s "F_terminal_prohibited"
    #define F_status_terminal_read_s       "F_terminal_read"
    #define F_status_terminal_valid_s      "F_terminal_valid"
    #define F_status_terminal_valid_not_s  "F_terminal_valid_not"
    #define F_status_terminal_write_s      "F_terminal_write"

    #define F_status_terminal_s_length            10
    #define F_status_terminal_access_s_length     17
    #define F_status_terminal_known_s_length      16
    #define F_status_terminal_known_not_s_length  20
    #define F_status_terminal_not_s_length        14
    #define F_status_terminal_prohibited_s_length 21
    #define F_status_terminal_read_s_length       15
    #define F_status_terminal_valid_s_length      16
    #define F_status_terminal_valid_not_s_length  20
    #define F_status_terminal_write_s_length      16

    extern const f_string_t f_status_terminal_s;
    extern const f_string_t f_status_terminal_access_s;
    extern const f_string_t f_status_terminal_known_s;
    extern const f_string_t f_status_terminal_known_not_s;
    extern const f_string_t f_status_terminal_not_s;
    extern const f_string_t f_status_terminal_prohibited_s;
    extern const f_string_t f_status_terminal_read_s;
    extern const f_string_t f_status_terminal_valid_s;
    extern const f_string_t f_status_terminal_valid_not_s;
    extern const f_string_t f_status_terminal_write_s;
  #endif // _di_F_status_terminal_

  #define F_status_status_code_last_s "F_status_code_last"

  extern const f_string_t f_status_status_code_last_s;

  #define F_status_status_code_last_s_length 18
#endif // _di_F_status_string_

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
 *
 *   F_data (with error bit) if there status is unknown.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_status_string_to_
  extern f_status_t f_status_string_to(const f_status_t code, f_string_t *string);
#endif // _di_f_status_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_string_h

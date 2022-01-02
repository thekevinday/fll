#include "status_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_F_status_string_
  #ifndef _di_F_status_boolean_
    const f_string_t f_status_false_s = F_status_false_s;
    const f_string_t f_status_true_s  = F_status_true_s;
  #endif // _di_F_status_boolean_

  #ifndef _di_F_status_signal_
    const f_string_t f_status_signal_hangup_s = F_status_signal_hangup_s;
    const f_string_t f_status_signal_interrupt_s = F_status_signal_interrupt_s;
    const f_string_t f_status_signal_quit_s = F_status_signal_quit_s;
    const f_string_t f_status_signal_illegal_s = F_status_signal_illegal_s;
    const f_string_t f_status_signal_trap_s = F_status_signal_trap_s;
    const f_string_t f_status_signal_abort_s = F_status_signal_abort_s;
    const f_string_t f_status_signal_bus_error_s = F_status_signal_bus_error_s;
    const f_string_t f_status_signal_floating_point_error_s = F_status_signal_floating_point_error_s;
    const f_string_t f_status_signal_kill_s = F_status_signal_kill_s;
    const f_string_t f_status_signal_user_1_s = F_status_signal_user_1_s;
    const f_string_t f_status_signal_segmentation_fault_s = F_status_signal_segmentation_fault_s;
    const f_string_t f_status_signal_user_2_s = F_status_signal_user_2_s;
    const f_string_t f_status_signal_broken_pipe_s = F_status_signal_broken_pipe_s;
    const f_string_t f_status_signal_alarm_clock_s = F_status_signal_alarm_clock_s;
    const f_string_t f_status_signal_termination_s = F_status_signal_termination_s;
    const f_string_t f_status_signal_stack_fault_s = F_status_signal_stack_fault_s;
    const f_string_t f_status_signal_child_s = F_status_signal_child_s;
    const f_string_t f_status_signal_continue_s = F_status_signal_continue_s;
    const f_string_t f_status_signal_stop_s = F_status_signal_stop_s;
    const f_string_t f_status_signal_keyboard_stop_s = F_status_signal_keyboard_stop_s;
    const f_string_t f_status_signal_tty_in_s = F_status_signal_tty_in_s;
    const f_string_t f_status_signal_tty_out_s = F_status_signal_tty_out_s;
    const f_string_t f_status_signal_urgent_s = F_status_signal_urgent_s;
    const f_string_t f_status_signal_cpu_limit_s = F_status_signal_cpu_limit_s;
    const f_string_t f_status_signal_file_size_limit_s = F_status_signal_file_size_limit_s;
    const f_string_t f_status_signal_virtual_alarm_clock_s = F_status_signal_virtual_alarm_clock_s;
    const f_string_t f_status_signal_profile_alarm_clock_s = F_status_signal_profile_alarm_clock_s;
    const f_string_t f_status_signal_window_size_change_s = F_status_signal_window_size_change_s;
    const f_string_t f_status_signal_pollable_event_s = F_status_signal_pollable_event_s;
    const f_string_t f_status_signal_power_failure_s = F_status_signal_power_failure_s;
    const f_string_t f_status_signal_bad_system_call_s = F_status_signal_bad_system_call_s;
    const f_string_t f_status_signal_reserved_32_s = F_status_signal_reserved_32_s;
    const f_string_t f_status_signal_reserved_33_s = F_status_signal_reserved_33_s;
    const f_string_t f_status_signal_reserved_34_s = F_status_signal_reserved_34_s;
    const f_string_t f_status_signal_reserved_35_s = F_status_signal_reserved_35_s;
    const f_string_t f_status_signal_reserved_36_s = F_status_signal_reserved_36_s;
    const f_string_t f_status_signal_reserved_37_s = F_status_signal_reserved_37_s;
    const f_string_t f_status_signal_reserved_38_s = F_status_signal_reserved_38_s;
    const f_string_t f_status_signal_reserved_39_s = F_status_signal_reserved_39_s;
    const f_string_t f_status_signal_reserved_40_s = F_status_signal_reserved_40_s;
    const f_string_t f_status_signal_reserved_41_s = F_status_signal_reserved_41_s;
    const f_string_t f_status_signal_reserved_42_s = F_status_signal_reserved_42_s;
    const f_string_t f_status_signal_reserved_43_s = F_status_signal_reserved_43_s;
    const f_string_t f_status_signal_reserved_44_s = F_status_signal_reserved_44_s;
    const f_string_t f_status_signal_reserved_45_s = F_status_signal_reserved_45_s;
    const f_string_t f_status_signal_reserved_46_s = F_status_signal_reserved_46_s;
    const f_string_t f_status_signal_reserved_47_s = F_status_signal_reserved_47_s;
    const f_string_t f_status_signal_reserved_48_s = F_status_signal_reserved_48_s;
    const f_string_t f_status_signal_reserved_49_s = F_status_signal_reserved_49_s;
    const f_string_t f_status_signal_reserved_50_s = F_status_signal_reserved_50_s;
    const f_string_t f_status_signal_reserved_51_s = F_status_signal_reserved_51_s;
    const f_string_t f_status_signal_reserved_52_s = F_status_signal_reserved_52_s;
    const f_string_t f_status_signal_reserved_53_s = F_status_signal_reserved_53_s;
    const f_string_t f_status_signal_reserved_54_s = F_status_signal_reserved_54_s;
    const f_string_t f_status_signal_reserved_55_s = F_status_signal_reserved_55_s;
    const f_string_t f_status_signal_reserved_56_s = F_status_signal_reserved_56_s;
    const f_string_t f_status_signal_reserved_57_s = F_status_signal_reserved_57_s;
    const f_string_t f_status_signal_reserved_58_s = F_status_signal_reserved_58_s;
    const f_string_t f_status_signal_reserved_59_s = F_status_signal_reserved_59_s;
    const f_string_t f_status_signal_reserved_60_s = F_status_signal_reserved_60_s;
    const f_string_t f_status_signal_reserved_61_s = F_status_signal_reserved_61_s;
    const f_string_t f_status_signal_reserved_62_s = F_status_signal_reserved_62_s;
    const f_string_t f_status_signal_reserved_63_s = F_status_signal_reserved_63_s;
    const f_string_t f_status_signal_reserved_64_s = F_status_signal_reserved_64_s;
  #endif // _di_F_status_signal_

  #ifndef _di_F_status_basic_
    const f_string_t f_status_none_s = F_status_none_s;
    const f_string_t f_status_abort_s = F_status_abort_s;
    const f_string_t f_status_abort_not_s = F_status_abort_not_s;
    const f_string_t f_status_absolute_s = F_status_absolute_s;
    const f_string_t f_status_absolute_not_s = F_status_absolute_not_s;
    const f_string_t f_status_address_s = F_status_address_s;
    const f_string_t f_status_address_not_s = F_status_address_not_s;
    const f_string_t f_status_ascii_s = F_status_ascii_s;
    const f_string_t f_status_ascii_not_s = F_status_ascii_not_s;
    const f_string_t f_status_begin_s = F_status_begin_s;
    const f_string_t f_status_begin_not_s = F_status_begin_not_s;
    const f_string_t f_status_block_s = F_status_block_s;
    const f_string_t f_status_block_not_s = F_status_block_not_s;
    const f_string_t f_status_bound_s = F_status_bound_s;
    const f_string_t f_status_bound_not_s = F_status_bound_not_s;
    const f_string_t f_status_capability_s = F_status_capability_s;
    const f_string_t f_status_capability_not_s = F_status_capability_not_s;
    const f_string_t f_status_child_s = F_status_child_s;
    const f_string_t f_status_child_not_s = F_status_child_not_s;
    const f_string_t f_status_complete_s = F_status_complete_s;
    const f_string_t f_status_complete_not_s = F_status_complete_not_s;
    const f_string_t f_status_connect_s = F_status_connect_s;
    const f_string_t f_status_connect_not_s = F_status_connect_not_s;
    const f_string_t f_status_connect_refuse_s = F_status_connect_refuse_s;
    const f_string_t f_status_container_s = F_status_container_s;
    const f_string_t f_status_container_not_s = F_status_container_not_s;
    const f_string_t f_status_continue_s = F_status_continue_s;
    const f_string_t f_status_continue_not_s = F_status_continue_not_s;
    const f_string_t f_status_control_s = F_status_control_s;
    const f_string_t f_status_control_not_s = F_status_control_not_s;
    const f_string_t f_status_control_group_s = F_status_control_group_s;
    const f_string_t f_status_control_group_not_s = F_status_control_group_not_s;
    const f_string_t f_status_critical_s = F_status_critical_s;
    const f_string_t f_status_critical_not_s = F_status_critical_not_s;
    const f_string_t f_status_dead_s = F_status_dead_s;
    const f_string_t f_status_dead_not_s = F_status_dead_not_s;
    const f_string_t f_status_deadlock_s = F_status_deadlock_s;
    const f_string_t f_status_deadlock_not_s = F_status_deadlock_not_s;
    const f_string_t f_status_descriptor_s = F_status_descriptor_s;
    const f_string_t f_status_descriptor_not_s = F_status_descriptor_not_s;
    const f_string_t f_status_device_s = F_status_device_s;
    const f_string_t f_status_device_not_s = F_status_device_not_s;
    const f_string_t f_status_disable_s = F_status_disable_s;
    const f_string_t f_status_disable_not_s = F_status_disable_not_s;
    const f_string_t f_status_domain_s = F_status_domain_s;
    const f_string_t f_status_domain_not_s = F_status_domain_not_s;
    const f_string_t f_status_done_s = F_status_done_s;
    const f_string_t f_status_done_not_s = F_status_done_not_s;
    const f_string_t f_status_dummy_s = F_status_dummy_s;
    const f_string_t f_status_dummy_not_s = F_status_dummy_not_s;
    const f_string_t f_status_empty_s = F_status_empty_s;
    const f_string_t f_status_empty_not_s = F_status_empty_not_s;
    const f_string_t f_status_enable_s = F_status_enable_s;
    const f_string_t f_status_enable_not_s = F_status_enable_not_s;
    const f_string_t f_status_encoding_s = F_status_encoding_s;
    const f_string_t f_status_encoding_not_s = F_status_encoding_not_s;
    const f_string_t f_status_end_s = F_status_end_s;
    const f_string_t f_status_end_not_s = F_status_end_not_s;
    const f_string_t f_status_eoa_s = F_status_eoa_s;
    const f_string_t f_status_eoa_not_s = F_status_eoa_not_s;
    const f_string_t f_status_eof_s = F_status_eof_s;
    const f_string_t f_status_eof_not_s = F_status_eof_not_s;
    const f_string_t f_status_eol_s = F_status_eol_s;
    const f_string_t f_status_eol_not_s = F_status_eol_not_s;
    const f_string_t f_status_eos_s = F_status_eos_s;
    const f_string_t f_status_eos_not_s = F_status_eos_not_s;
    const f_string_t f_status_execute_s = F_status_execute_s;
    const f_string_t f_status_execute_not_s = F_status_execute_not_s;
    const f_string_t f_status_exist_s = F_status_exist_s;
    const f_string_t f_status_exist_not_s = F_status_exist_not_s;
    const f_string_t f_status_failure_s = F_status_failure_s;
    const f_string_t f_status_failure_not_s = F_status_failure_not_s;
    const f_string_t f_status_family_s = F_status_family_s;
    const f_string_t f_status_family_not_s = F_status_family_not_s;
    const f_string_t f_status_first_s = F_status_first_s;
    const f_string_t f_status_first_not_s = F_status_first_not_s;
    const f_string_t f_status_fork_s = F_status_fork_s;
    const f_string_t f_status_fork_not_s = F_status_fork_not_s;
    const f_string_t f_status_format_s = F_status_format_s;
    const f_string_t f_status_format_not_s = F_status_format_not_s;
    const f_string_t f_status_found_s = F_status_found_s;
    const f_string_t f_status_found_not_s = F_status_found_not_s;
    const f_string_t f_status_full_s = F_status_full_s;
    const f_string_t f_status_full_not_s = F_status_full_not_s;
    const f_string_t f_status_group_s = F_status_group_s;
    const f_string_t f_status_group_not_s = F_status_group_not_s;
    const f_string_t f_status_ignore_s = F_status_ignore_s;
    const f_string_t f_status_ignore_not_s = F_status_ignore_not_s;
    const f_string_t f_status_implemented_s = F_status_implemented_s;
    const f_string_t f_status_implemented_not_s = F_status_implemented_not_s;
    const f_string_t f_status_input_s = F_status_input_s;
    const f_string_t f_status_input_not_s = F_status_input_not_s;
    const f_string_t f_status_input_output_s = F_status_input_output_s;
    const f_string_t f_status_interrupt_s = F_status_interrupt_s;
    const f_string_t f_status_interrupt_not_s = F_status_interrupt_not_s;
    const f_string_t f_status_known_s = F_status_known_s;
    const f_string_t f_status_known_not_s = F_status_known_not_s;
    const f_string_t f_status_last_s = F_status_last_s;
    const f_string_t f_status_last_not_s = F_status_last_not_s;
    const f_string_t f_status_limit_s = F_status_limit_s;
    const f_string_t f_status_limit_not_s = F_status_limit_not_s;
    const f_string_t f_status_link_s = F_status_link_s;
    const f_string_t f_status_link_not_s = F_status_link_not_s;
    const f_string_t f_status_live_s = F_status_live_s;
    const f_string_t f_status_live_not_s = F_status_live_not_s;
    const f_string_t f_status_lock_s = F_status_lock_s;
    const f_string_t f_status_lock_not_s = F_status_lock_not_s;
    const f_string_t f_status_loop_s = F_status_loop_s;
    const f_string_t f_status_loop_not_s = F_status_loop_not_s;
    const f_string_t f_status_maybe_s = F_status_maybe_s;
    const f_string_t f_status_maybe_not_s = F_status_maybe_not_s;
    const f_string_t f_status_memory_s = F_status_memory_s;
    const f_string_t f_status_memory_not_s = F_status_memory_not_s;
    const f_string_t f_status_minor_s = F_status_minor_s;
    const f_string_t f_status_minor_not_s = F_status_minor_not_s;
    const f_string_t f_status_moderate_s = F_status_moderate_s;
    const f_string_t f_status_moderate_not_s = F_status_moderate_not_s;
    const f_string_t f_status_mount_s = F_status_mount_s;
    const f_string_t f_status_mount_not_s = F_status_mount_not_s;
    const f_string_t f_status_name_s = F_status_name_s;
    const f_string_t f_status_name_not_s = F_status_name_not_s;
    const f_string_t f_status_next_s = F_status_next_s;
    const f_string_t f_status_next_not_s = F_status_next_not_s;
    const f_string_t f_status_nice_s = F_status_nice_s;
    const f_string_t f_status_nice_not_s = F_status_nice_not_s;
    const f_string_t f_status_option_s = F_status_option_s;
    const f_string_t f_status_option_not_s = F_status_option_not_s;
    const f_string_t f_status_output_s = F_status_output_s;
    const f_string_t f_status_output_not_s = F_status_output_not_s;
    const f_string_t f_status_parameter_s = F_status_parameter_s;
    const f_string_t f_status_parameter_not_s = F_status_parameter_not_s;
    const f_string_t f_status_parent_s = F_status_parent_s;
    const f_string_t f_status_parent_not_s = F_status_parent_not_s;
    const f_string_t f_status_pipe_s = F_status_pipe_s;
    const f_string_t f_status_pipe_not_s = F_status_pipe_not_s;
    const f_string_t f_status_port_s = F_status_port_s;
    const f_string_t f_status_port_not_s = F_status_port_not_s;
    const f_string_t f_status_previous_s = F_status_previous_s;
    const f_string_t f_status_previous_not_s = F_status_previous_not_s;
    const f_string_t f_status_processor_s = F_status_processor_s;
    const f_string_t f_status_processor_not_s = F_status_processor_not_s;
    const f_string_t f_status_progress_s = F_status_progress_s;
    const f_string_t f_status_progress_not_s = F_status_progress_not_s;
    const f_string_t f_status_prohibited_s = F_status_prohibited_s;
    const f_string_t f_status_prohibited_not_s = F_status_prohibited_not_s;
    const f_string_t f_status_property_s = F_status_property_s;
    const f_string_t f_status_property_not_s = F_status_property_not_s;
    const f_string_t f_status_protocol_s = F_status_protocol_s;
    const f_string_t f_status_protocol_not_s = F_status_protocol_not_s;
    const f_string_t f_status_range_s = F_status_range_s;
    const f_string_t f_status_range_not_s = F_status_range_not_s;
    const f_string_t f_status_read_s = F_status_read_s;
    const f_string_t f_status_read_not_s = F_status_read_not_s;
    const f_string_t f_status_read_only_s = F_status_read_only_s;
    const f_string_t f_status_ready_s = F_status_ready_s;
    const f_string_t f_status_ready_not_s = F_status_ready_not_s;
    const f_string_t f_status_recover_s = F_status_recover_s;
    const f_string_t f_status_recover_not_s = F_status_recover_not_s;
    const f_string_t f_status_recurse_s = F_status_recurse_s;
    const f_string_t f_status_recurse_not_s = F_status_recurse_not_s;
    const f_string_t f_status_relative_s = F_status_relative_s;
    const f_string_t f_status_relative_not_s = F_status_relative_not_s;
    const f_string_t f_status_require_s = F_status_require_s;
    const f_string_t f_status_require_not_s = F_status_require_not_s;
    const f_string_t f_status_resource_s = F_status_resource_s;
    const f_string_t f_status_resource_not_s = F_status_resource_not_s;
    const f_string_t f_status_search_s = F_status_search_s;
    const f_string_t f_status_search_not_s = F_status_search_not_s;
    const f_string_t f_status_schedule_s = F_status_schedule_s;
    const f_string_t f_status_schedule_not_s = F_status_schedule_not_s;
    const f_string_t f_status_signal_s = F_status_signal_s;
    const f_string_t f_status_signal_not_s = F_status_signal_not_s;
    const f_string_t f_status_space_s = F_status_space_s;
    const f_string_t f_status_space_not_s = F_status_space_not_s;
    const f_string_t f_status_start_s = F_status_start_s;
    const f_string_t f_status_start_not_s = F_status_start_not_s;
    const f_string_t f_status_stop_s = F_status_stop_s;
    const f_string_t f_status_stop_not_s = F_status_stop_not_s;
    const f_string_t f_status_stream_s = F_status_stream_s;
    const f_string_t f_status_stream_not_s = F_status_stream_not_s;
    const f_string_t f_status_string_s = F_status_string_s;
    const f_string_t f_status_string_not_s = F_status_string_not_s;
    const f_string_t f_status_string_too_large_s = F_status_string_too_large_s;
    const f_string_t f_status_string_too_small_s = F_status_string_too_small_s;
    const f_string_t f_status_syntax_s = F_status_syntax_s;
    const f_string_t f_status_syntax_not_s = F_status_syntax_not_s;
    const f_string_t f_status_thread_s = F_status_thread_s;
    const f_string_t f_status_thread_not_s = F_status_thread_not_s;
    const f_string_t f_status_time_s = F_status_time_s;
    const f_string_t f_status_time_not_s = F_status_time_not_s;
    const f_string_t f_status_time_out_s = F_status_time_out_s;
    const f_string_t f_status_too_large_s = F_status_too_large_s;
    const f_string_t f_status_too_small_s = F_status_too_small_s;
    const f_string_t f_status_type_s = F_status_type_s;
    const f_string_t f_status_type_not_s = F_status_type_not_s;
    const f_string_t f_status_success_s = F_status_success_s;
    const f_string_t f_status_success_not_s = F_status_success_not_s;
    const f_string_t f_status_supported_s = F_status_supported_s;
    const f_string_t f_status_supported_not_s = F_status_supported_not_s;
    const f_string_t f_status_user_s = F_status_user_s;
    const f_string_t f_status_user_not_s = F_status_user_not_s;
    const f_string_t f_status_utf_s = F_status_utf_s;
    const f_string_t f_status_utf_fragment_s = F_status_utf_fragment_s;
    const f_string_t f_status_utf_fragment_not_s = F_status_utf_fragment_not_s;
    const f_string_t f_status_utf_not_s = F_status_utf_not_s;
    const f_string_t f_status_valid_s = F_status_valid_s;
    const f_string_t f_status_valid_not_s = F_status_valid_not_s;
    const f_string_t f_status_value_s = F_status_value_s;
    const f_string_t f_status_value_not_s = F_status_value_not_s;
    const f_string_t f_status_wait_s = F_status_wait_s;
    const f_string_t f_status_wait_not_s = F_status_wait_not_s;
    const f_string_t f_status_warn_s = F_status_warn_s;
    const f_string_t f_status_warn_not_s = F_status_warn_not_s;
    const f_string_t f_status_world_s = F_status_world_s;
    const f_string_t f_status_world_not_s = F_status_world_not_s;
    const f_string_t f_status_write_s = F_status_write_s;
    const f_string_t f_status_write_not_s = F_status_write_not_s;
    const f_string_t f_status_write_only_s = F_status_write_only_s;
  #endif // _di_F_status_basic_

  #ifndef _di_F_status_array_
    const f_string_t f_status_array_s = F_status_array_s;
    const f_string_t f_status_array_not_s = F_status_array_not_s;
    const f_string_t f_status_array_too_large_s = F_status_array_too_large_s;
    const f_string_t f_status_array_too_small_s = F_status_array_too_small_s;
  #endif // _di_F_status_array_

  #ifndef _di_F_status_available_
    const f_string_t f_status_available_s = F_status_available_s;
    const f_string_t f_status_available_not_s = F_status_available_not_s;
    const f_string_t f_status_available_not_address_s = F_status_available_not_address_s;
    const f_string_t f_status_available_not_buffer_s = F_status_available_not_buffer_s;
    const f_string_t f_status_available_not_device_s = F_status_available_not_device_s;
    const f_string_t f_status_available_not_pipe_s = F_status_available_not_pipe_s;
    const f_string_t f_status_available_not_port_s = F_status_available_not_port_s;
    const f_string_t f_status_available_not_process_s = F_status_available_not_process_s;
    const f_string_t f_status_available_not_socket_s = F_status_available_not_socket_s;
  #endif // _di_F_status_available_

  #ifndef _di_F_status_busy_
    const f_string_t f_status_busy_s = F_status_busy_s;
    const f_string_t f_status_busy_address_s = F_status_busy_address_s;
    const f_string_t f_status_busy_buffer_s = F_status_busy_buffer_s;
    const f_string_t f_status_busy_device_s = F_status_busy_device_s;
    const f_string_t f_status_busy_not_s = F_status_busy_not_s;
    const f_string_t f_status_busy_pipe_s = F_status_busy_pipe_s;
    const f_string_t f_status_busy_port_s = F_status_busy_port_s;
    const f_string_t f_status_busy_process_s = F_status_busy_process_s;
    const f_string_t f_status_busy_socket_s = F_status_busy_socket_s;
  #endif // _di_F_status_busy_

  #ifndef _di_F_status_network_
    const f_string_t f_status_network_s = F_status_network_s;
    const f_string_t f_status_network_busy_s = F_status_network_busy_s;
    const f_string_t f_status_network_busy_not_s = F_status_network_busy_not_s;
    const f_string_t f_status_network_found_s = F_status_network_found_s;
    const f_string_t f_status_network_found_not_s = F_status_network_found_not_s;
    const f_string_t f_status_network_lost_s = F_status_network_lost_s;
    const f_string_t f_status_network_lost_not_s = F_status_network_lost_not_s;
    const f_string_t f_status_network_not_s = F_status_network_not_s;
    const f_string_t f_status_network_reach_s = F_status_network_reach_s;
    const f_string_t f_status_network_reach_not_s = F_status_network_reach_not_s;
    const f_string_t f_status_network_time_s = F_status_network_time_s;
    const f_string_t f_status_network_time_not_s = F_status_network_time_not_s;
  #endif // _di_F_status_network_

  #ifndef _di_F_status_number_
    const f_string_t f_status_number_s = F_status_number_s;
    const f_string_t f_status_number_decimal_s = F_status_number_decimal_s;
    const f_string_t f_status_number_decimal_not_s = F_status_number_decimal_not_s;
    const f_string_t f_status_number_divide_by_zero_s = F_status_number_divide_by_zero_s;
    const f_string_t f_status_number_negative_s = F_status_number_negative_s;
    const f_string_t f_status_number_negative_not_s = F_status_number_negative_not_s;
    const f_string_t f_status_number_not_s = F_status_number_not_s;
    const f_string_t f_status_number_overflow_s = F_status_number_overflow_s;
    const f_string_t f_status_number_positive_s = F_status_number_positive_s;
    const f_string_t f_status_number_positive_not_s = F_status_number_positive_not_s;
    const f_string_t f_status_number_too_large_s = F_status_number_too_large_s;
    const f_string_t f_status_number_too_small_s = F_status_number_too_small_s;
    const f_string_t f_status_number_underflow_s = F_status_number_underflow_s;
    const f_string_t f_status_number_whole_s = F_status_number_whole_s;
    const f_string_t f_status_number_whole_not_s = F_status_number_whole_not_s;
    const f_string_t f_status_number_zero_s = F_status_number_zero_s;
    const f_string_t f_status_number_zero_not_s = F_status_number_zero_not_s;
  #endif // _di_F_status_number_

  #ifndef _di_F_status_buffer_
    const f_string_t f_status_buffer_s = F_status_buffer_s;
    const f_string_t f_status_buffer_not_s = F_status_buffer_not_s;
    const f_string_t f_status_buffer_too_large_s = F_status_buffer_too_large_s;
    const f_string_t f_status_buffer_too_small_s = F_status_buffer_too_small_s;
    const f_string_t f_status_complete_not_utf_s = F_status_complete_not_utf_s;
    const f_string_t f_status_complete_not_utf_block_s = F_status_complete_not_utf_block_s;
    const f_string_t f_status_complete_not_utf_eoa_s = F_status_complete_not_utf_eoa_s;
    const f_string_t f_status_complete_not_utf_eof_s = F_status_complete_not_utf_eof_s;
    const f_string_t f_status_complete_not_utf_eol_s = F_status_complete_not_utf_eol_s;
    const f_string_t f_status_complete_not_utf_eos_s = F_status_complete_not_utf_eos_s;
    const f_string_t f_status_complete_not_utf_stop_s = F_status_complete_not_utf_stop_s;
    const f_string_t f_status_none_block_s = F_status_none_block_s;
    const f_string_t f_status_none_eoa_s = F_status_none_eoa_s;
    const f_string_t f_status_none_eof_s = F_status_none_eof_s;
    const f_string_t f_status_none_eol_s = F_status_none_eol_s;
    const f_string_t f_status_none_eos_s = F_status_none_eos_s;
    const f_string_t f_status_none_not_s = F_status_none_not_s;
    const f_string_t f_status_none_stop_s = F_status_none_stop_s;
    const f_string_t f_status_data_s = F_status_data_s;
    const f_string_t f_status_data_not_s = F_status_data_not_s;
    const f_string_t f_status_data_not_block_s = F_status_data_not_block_s;
    const f_string_t f_status_data_not_eoa_s = F_status_data_not_eoa_s;
    const f_string_t f_status_data_not_eof_s = F_status_data_not_eof_s;
    const f_string_t f_status_data_not_eol_s = F_status_data_not_eol_s;
    const f_string_t f_status_data_not_eos_s = F_status_data_not_eos_s;
    const f_string_t f_status_data_not_stop_s = F_status_data_not_stop_s;
    const f_string_t f_status_terminated_s = F_status_terminated_s;
    const f_string_t f_status_terminated_not_s = F_status_terminated_not_s;
    const f_string_t f_status_terminated_not_block_s = F_status_terminated_not_block_s;
    const f_string_t f_status_terminated_not_eoa_s = F_status_terminated_not_eoa_s;
    const f_string_t f_status_terminated_not_eof_s = F_status_terminated_not_eof_s;
    const f_string_t f_status_terminated_not_eol_s = F_status_terminated_not_eol_s;
    const f_string_t f_status_terminated_not_eos_s = F_status_terminated_not_eos_s;
    const f_string_t f_status_terminated_not_stop_s = F_status_terminated_not_stop_s;
    const f_string_t f_status_terminated_not_group_s = F_status_terminated_not_group_s;
    const f_string_t f_status_terminated_not_group_block_s = F_status_terminated_not_group_block_s;
    const f_string_t f_status_terminated_not_group_eoa_s = F_status_terminated_not_group_eoa_s;
    const f_string_t f_status_terminated_not_group_eof_s = F_status_terminated_not_group_eof_s;
    const f_string_t f_status_terminated_not_group_eol_s = F_status_terminated_not_group_eol_s;
    const f_string_t f_status_terminated_not_group_eos_s = F_status_terminated_not_group_eos_s;
    const f_string_t f_status_terminated_not_group_stop_s = F_status_terminated_not_group_stop_s;
    const f_string_t f_status_terminated_not_nest_s = F_status_terminated_not_nest_s;
    const f_string_t f_status_terminated_not_nest_block_s = F_status_terminated_not_nest_block_s;
    const f_string_t f_status_terminated_not_nest_eoa_s = F_status_terminated_not_nest_eoa_s;
    const f_string_t f_status_terminated_not_nest_eof_s = F_status_terminated_not_nest_eof_s;
    const f_string_t f_status_terminated_not_nest_eol_s = F_status_terminated_not_nest_eol_s;
    const f_string_t f_status_terminated_not_nest_eos_s = F_status_terminated_not_nest_eos_s;
    const f_string_t f_status_terminated_not_nest_stop_s = F_status_terminated_not_nest_stop_s;
  #endif // _di_F_status_buffer_

  #ifndef _di_F_status_process_
    const f_string_t f_status_process_s = F_status_process_s;
    const f_string_t f_status_process_not_s = F_status_process_not_s;
    const f_string_t f_status_process_too_many_s = F_status_process_too_many_s;
  #endif // _di_F_status_process_

  #ifndef _di_F_status_file_
    const f_string_t f_status_file_s = F_status_file_s;
    const f_string_t f_status_file_close_s = F_status_file_close_s;
    const f_string_t f_status_file_closed_s = F_status_file_closed_s;
    const f_string_t f_status_file_descriptor_s = F_status_file_descriptor_s;
    const f_string_t f_status_file_descriptor_max_s = F_status_file_descriptor_max_s;
    const f_string_t f_status_file_descriptor_not_s = F_status_file_descriptor_not_s;
    const f_string_t f_status_file_empty_s = F_status_file_empty_s;
    const f_string_t f_status_file_flush_s = F_status_file_flush_s;
    const f_string_t f_status_file_found_s = F_status_file_found_s;
    const f_string_t f_status_file_found_not_s = F_status_file_found_not_s;
    const f_string_t f_status_file_not_s = F_status_file_not_s;
    const f_string_t f_status_file_open_s = F_status_file_open_s;
    const f_string_t f_status_file_open_max_s = F_status_file_open_max_s;
    const f_string_t f_status_file_opened_s = F_status_file_opened_s;
    const f_string_t f_status_file_overflow_s = F_status_file_overflow_s;
    const f_string_t f_status_file_purge_s = F_status_file_purge_s;
    const f_string_t f_status_file_read_s = F_status_file_read_s;
    const f_string_t f_status_file_reallocation_s = F_status_file_reallocation_s;
    const f_string_t f_status_file_seek_s = F_status_file_seek_s;
    const f_string_t f_status_file_stat_s = F_status_file_stat_s;
    const f_string_t f_status_file_synchronize_s = F_status_file_synchronize_s;
    const f_string_t f_status_file_type_block_s = F_status_file_type_block_s;
    const f_string_t f_status_file_type_character_s = F_status_file_type_character_s;
    const f_string_t f_status_file_type_directory_s = F_status_file_type_directory_s;
    const f_string_t f_status_file_type_fifo_s = F_status_file_type_fifo_s;
    const f_string_t f_status_file_type_link_s = F_status_file_type_link_s;
    const f_string_t f_status_file_type_not_block_s = F_status_file_type_not_block_s;
    const f_string_t f_status_file_type_not_character_s = F_status_file_type_not_character_s;
    const f_string_t f_status_file_type_not_directory_s = F_status_file_type_not_directory_s;
    const f_string_t f_status_file_type_not_fifo_s = F_status_file_type_not_fifo_s;
    const f_string_t f_status_file_type_not_link_s = F_status_file_type_not_link_s;
    const f_string_t f_status_file_type_not_pipe_s = F_status_file_type_not_pipe_s;
    const f_string_t f_status_file_type_not_regular_s = F_status_file_type_not_regular_s;
    const f_string_t f_status_file_type_not_socket_s = F_status_file_type_not_socket_s;
    const f_string_t f_status_file_type_not_unknown_s = F_status_file_type_not_unknown_s;
    const f_string_t f_status_file_type_pipe_s = F_status_file_type_pipe_s;
    const f_string_t f_status_file_type_regular_s = F_status_file_type_regular_s;
    const f_string_t f_status_file_type_socket_s = F_status_file_type_socket_s;
    const f_string_t f_status_file_type_unknown_s = F_status_file_type_unknown_s;
    const f_string_t f_status_file_underflow_s = F_status_file_underflow_s;
    const f_string_t f_status_file_utf_s = F_status_file_utf_s;
    const f_string_t f_status_file_utf_not_s = F_status_file_utf_not_s;
    const f_string_t f_status_file_write_s = F_status_file_write_s;
  #endif // _di_F_status_file_

  #ifndef _di_F_status_filesystem_
    const f_string_t f_status_filesystem_s = F_status_filesystem_s;
    const f_string_t f_status_filesystem_not_s = F_status_filesystem_not_s;
    const f_string_t f_status_filesystem_quota_block_s = F_status_filesystem_quota_block_s;
    const f_string_t f_status_filesystem_quota_reached_s = F_status_filesystem_quota_reached_s;
  #endif // _di_F_status_filesystem_

  #ifndef _di_F_status_directory_
    const f_string_t f_status_directory_s = F_status_directory_s;
    const f_string_t f_status_directory_close_s = F_status_directory_close_s;
    const f_string_t f_status_directory_closed_s = F_status_directory_closed_s;
    const f_string_t f_status_directory_descriptor_s = F_status_directory_descriptor_s;
    const f_string_t f_status_directory_empty_s = F_status_directory_empty_s;
    const f_string_t f_status_directory_empty_not_s = F_status_directory_empty_not_s;
    const f_string_t f_status_directory_found_s = F_status_directory_found_s;
    const f_string_t f_status_directory_found_not_s = F_status_directory_found_not_s;
    const f_string_t f_status_directory_flush_s = F_status_directory_flush_s;
    const f_string_t f_status_directory_link_max_s = F_status_directory_link_max_s;
    const f_string_t f_status_directory_not_s = F_status_directory_not_s;
    const f_string_t f_status_directory_open_s = F_status_directory_open_s;
    const f_string_t f_status_directory_purge_s = F_status_directory_purge_s;
    const f_string_t f_status_directory_read_s = F_status_directory_read_s;
    const f_string_t f_status_directory_stream_s = F_status_directory_stream_s;
    const f_string_t f_status_directory_supported_not_s = F_status_directory_supported_not_s;
    const f_string_t f_status_directory_synchronize_s = F_status_directory_synchronize_s;
    const f_string_t f_status_directory_utf_s = F_status_directory_utf_s;
    const f_string_t f_status_directory_utf_not_s = F_status_directory_utf_not_s;
    const f_string_t f_status_directory_write_s = F_status_directory_write_s;
  #endif // _di_F_status_directory_

  #ifndef _di_F_status_socket_
    const f_string_t f_status_socket_s = F_status_socket_s;
    const f_string_t f_status_socket_client_s = F_status_socket_client_s;
    const f_string_t f_status_socket_not_s = F_status_socket_not_s;
    const f_string_t f_status_socket_receive_s = F_status_socket_receive_s;
    const f_string_t f_status_socket_send_s = F_status_socket_send_s;
    const f_string_t f_status_socket_target_s = F_status_socket_target_s;
  #endif // _di_F_status_socket_

  #ifndef _di_F_status_compare_
    const f_string_t f_status_equal_to_s = F_status_equal_to_s;
    const f_string_t f_status_equal_to_not_s = F_status_equal_to_not_s;
    const f_string_t f_status_than_greater_s = F_status_than_greater_s;
    const f_string_t f_status_than_less_s = F_status_than_less_s;
  #endif // _di_F_status_compare_

  #ifndef _di_F_status_access_
    const f_string_t f_status_access_s = F_status_access_s;
    const f_string_t f_status_access_denied_s = F_status_access_denied_s;
    const f_string_t f_status_access_denied_user_s = F_status_access_denied_user_s;
    const f_string_t f_status_access_denied_group_s = F_status_access_denied_group_s;
    const f_string_t f_status_access_denied_world_s = F_status_access_denied_world_s;
    const f_string_t f_status_access_denied_read_s = F_status_access_denied_read_s;
    const f_string_t f_status_access_denied_write_s = F_status_access_denied_write_s;
    const f_string_t f_status_access_denied_execute_s = F_status_access_denied_execute_s;
    const f_string_t f_status_access_denied_super_s = F_status_access_denied_super_s;
    const f_string_t f_status_access_granted_s = F_status_access_granted_s;
    const f_string_t f_status_access_granted_user_s = F_status_access_granted_user_s;
    const f_string_t f_status_access_granted_group_s = F_status_access_granted_group_s;
    const f_string_t f_status_access_granted_world_s = F_status_access_granted_world_s;
    const f_string_t f_status_access_granted_read_s = F_status_access_granted_read_s;
    const f_string_t f_status_access_granted_write_s = F_status_access_granted_write_s;
    const f_string_t f_status_access_granted_execute_s = F_status_access_granted_execute_s;
    const f_string_t f_status_access_granted_super_s = F_status_access_granted_super_s;
    const f_string_t f_status_access_group_s = F_status_access_group_s;
    const f_string_t f_status_access_mode_s = F_status_access_mode_s;
    const f_string_t f_status_access_not_s = F_status_access_not_s;
    const f_string_t f_status_access_owner_s = F_status_access_owner_s;
  #endif // _di_F_status_access_

  #ifndef _di_F_status_terminal_
    const f_string_t f_status_terminal_s = F_status_terminal_s;
    const f_string_t f_status_terminal_access_s = F_status_terminal_access_s;
    const f_string_t f_status_terminal_known_s = F_status_terminal_known_s;
    const f_string_t f_status_terminal_known_not_s = F_status_terminal_known_not_s;
    const f_string_t f_status_terminal_not_s = F_status_terminal_not_s;
    const f_string_t f_status_terminal_prohibited_s = F_status_terminal_prohibited_s;
    const f_string_t f_status_terminal_read_s = F_status_terminal_read_s;
    const f_string_t f_status_terminal_valid_s = F_status_terminal_valid_s;
    const f_string_t f_status_terminal_valid_not_s = F_status_terminal_valid_not_s;
    const f_string_t f_status_terminal_write_s = F_status_terminal_write_s;
  #endif // _di_F_status_terminal_

  const f_string_t f_status_status_code_last_s = F_status_status_code_last_s;
#endif // _di_F_status_string_

#ifndef _di_f_status_string_to_
  f_status_t f_status_string_to(const f_status_t code, f_string_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_F_status_boolean_
        case F_false:
          *string = f_status_false_s;
          break;

        case F_true:
          *string = f_status_true_s;
          break;
      #endif // _di_F_status_boolean_

      #ifndef _di_F_status_signal_

        // F_signal_hangup is not used because it has the same code as F_true.
        case F_signal_interrupt:
          *string = f_status_signal_interrupt_s;
          break;

        case F_signal_quit:
          *string = f_status_signal_quit_s;
          break;

        case F_signal_illegal:
          *string = f_status_signal_illegal_s;
          break;

        case F_signal_trap:
          *string = f_status_signal_trap_s;
          break;

        case F_signal_abort:
          *string = f_status_signal_abort_s;
          break;

        case F_signal_bus_error:
          *string = f_status_signal_bus_error_s;
          break;

        case F_signal_floating_point_error:
          *string = f_status_signal_floating_point_error_s;
          break;

        case F_signal_kill:
          *string = f_status_signal_kill_s;
          break;

        case F_signal_user_1:
          *string = f_status_signal_user_1_s;
          break;

        case F_signal_segmentation_fault:
          *string = f_status_signal_segmentation_fault_s;
          break;

        case F_signal_user_2:
          *string = f_status_signal_user_2_s;
          break;

        case F_signal_broken_pipe:
          *string = f_status_signal_broken_pipe_s;
          break;

        case F_signal_alarm_clock:
          *string = f_status_signal_alarm_clock_s;
          break;

        case F_signal_termination:
          *string = f_status_signal_termination_s;
          break;

        case F_signal_stack_fault:
          *string = f_status_signal_stack_fault_s;
          break;

        case F_signal_child:
          *string = f_status_signal_child_s;
          break;

        case F_signal_continue:
          *string = f_status_signal_continue_s;
          break;

        case F_signal_stop:
          *string = f_status_signal_stop_s;
          break;

        case F_signal_keyboard_stop:
          *string = f_status_signal_keyboard_stop_s;
          break;

        case F_signal_tty_in:
          *string = f_status_signal_tty_in_s;
          break;

        case F_signal_tty_out:
          *string = f_status_signal_tty_out_s;
          break;

        case F_signal_urgent:
          *string = f_status_signal_urgent_s;
          break;

        case F_signal_cpu_limit:
          *string = f_status_signal_cpu_limit_s;
          break;

        case F_signal_file_size_limit:
          *string = f_status_signal_file_size_limit_s;
          break;

        case F_signal_virtual_alarm_clock:
          *string = f_status_signal_virtual_alarm_clock_s;
          break;

        case F_signal_profile_alarm_clock:
          *string = f_status_signal_profile_alarm_clock_s;
          break;

        case F_signal_window_size_change:
          *string = f_status_signal_window_size_change_s;
          break;

        case F_signal_pollable_event:
          *string = f_status_signal_pollable_event_s;
          break;

        case F_signal_power_failure:
          *string = f_status_signal_power_failure_s;
          break;

        case F_signal_bad_system_call:
          *string = f_status_signal_bad_system_call_s;
          break;

        case F_signal_reserved_32:
          *string = f_status_signal_reserved_32_s;
          break;

        case F_signal_reserved_33:
          *string = f_status_signal_reserved_33_s;
          break;

        case F_signal_reserved_34:
          *string = f_status_signal_reserved_34_s;
          break;

        case F_signal_reserved_35:
          *string = f_status_signal_reserved_35_s;
          break;

        case F_signal_reserved_36:
          *string = f_status_signal_reserved_36_s;
          break;

        case F_signal_reserved_37:
          *string = f_status_signal_reserved_37_s;
          break;

        case F_signal_reserved_38:
          *string = f_status_signal_reserved_38_s;
          break;

        case F_signal_reserved_39:
          *string = f_status_signal_reserved_39_s;
          break;

        case F_signal_reserved_40:
          *string = f_status_signal_reserved_40_s;
          break;

        case F_signal_reserved_41:
          *string = f_status_signal_reserved_41_s;
          break;

        case F_signal_reserved_42:
          *string = f_status_signal_reserved_42_s;
          break;

        case F_signal_reserved_43:
          *string = f_status_signal_reserved_43_s;
          break;

        case F_signal_reserved_44:
          *string = f_status_signal_reserved_44_s;
          break;

        case F_signal_reserved_45:
          *string = f_status_signal_reserved_45_s;
          break;

        case F_signal_reserved_46:
          *string = f_status_signal_reserved_46_s;
          break;

        case F_signal_reserved_47:
          *string = f_status_signal_reserved_47_s;
          break;

        case F_signal_reserved_48:
          *string = f_status_signal_reserved_48_s;
          break;

        case F_signal_reserved_49:
          *string = f_status_signal_reserved_49_s;
          break;

        case F_signal_reserved_50:
          *string = f_status_signal_reserved_50_s;
          break;

        case F_signal_reserved_51:
          *string = f_status_signal_reserved_51_s;
          break;

        case F_signal_reserved_52:
          *string = f_status_signal_reserved_52_s;
          break;

        case F_signal_reserved_53:
          *string = f_status_signal_reserved_53_s;
          break;

        case F_signal_reserved_54:
          *string = f_status_signal_reserved_54_s;
          break;

        case F_signal_reserved_55:
          *string = f_status_signal_reserved_55_s;
          break;

        case F_signal_reserved_56:
          *string = f_status_signal_reserved_56_s;
          break;

        case F_signal_reserved_57:
          *string = f_status_signal_reserved_57_s;
          break;

        case F_signal_reserved_58:
          *string = f_status_signal_reserved_58_s;
          break;

        case F_signal_reserved_59:
          *string = f_status_signal_reserved_59_s;
          break;

        case F_signal_reserved_60:
          *string = f_status_signal_reserved_60_s;
          break;

        case F_signal_reserved_61:
          *string = f_status_signal_reserved_61_s;
          break;

        case F_signal_reserved_62:
          *string = f_status_signal_reserved_62_s;
          break;

        case F_signal_reserved_63:
          *string = f_status_signal_reserved_63_s;
          break;

        case F_signal_reserved_64:
          *string = f_status_signal_reserved_64_s;
          break;
      #endif // _di_F_status_signal_

      #ifndef _di_F_status_basic_
        case F_none:
          *string = f_status_none_s;
          break;

        case F_abort:
          *string = f_status_abort_s;
          break;

        case F_abort_not:
          *string = f_status_abort_not_s;
          break;

        case F_absolute:
          *string = f_status_absolute_s;
          break;

        case F_absolute_not:
          *string = f_status_absolute_not_s;
          break;

        case F_address:
          *string = f_status_address_s;
          break;

        case F_address_not:
          *string = f_status_address_not_s;
          break;

        case F_ascii:
          *string = f_status_ascii_s;
          break;

        case F_ascii_not:
          *string = f_status_ascii_not_s;
          break;

        case F_begin:
          *string = f_status_begin_s;
          break;

        case F_begin_not:
          *string = f_status_begin_not_s;
          break;

        case F_block:
          *string = f_status_block_s;
          break;

        case F_block_not:
          *string = f_status_block_not_s;
          break;

        case F_bound:
          *string = f_status_bound_s;
          break;

        case F_bound_not:
          *string = f_status_bound_not_s;
          break;

        case F_capability:
          *string = f_status_capability_s;
          break;

        case F_capability_not:
          *string = f_status_capability_not_s;
          break;

        case F_child:
          *string = f_status_child_s;
          break;

        case F_child_not:
          *string = f_status_child_not_s;
          break;

        case F_complete:
          *string = f_status_complete_s;
          break;

        case F_complete_not:
          *string = f_status_complete_not_s;
          break;

        case F_connect:
          *string = f_status_connect_s;
          break;

        case F_connect_not:
          *string = f_status_connect_not_s;
          break;

        case F_connect_refuse:
          *string = f_status_connect_refuse_s;
          break;

        case F_continue:
          *string = f_status_continue_s;
          break;

        case F_continue_not:
          *string = f_status_continue_not_s;
          break;

        case F_container:
          *string = f_status_container_s;
          break;

        case F_container_not:
          *string = f_status_container_not_s;
          break;

        case F_control:
          *string = f_status_control_s;
          break;

        case F_control_not:
          *string = f_status_control_not_s;
          break;

        case F_control_group:
          *string = f_status_control_group_s;
          break;

        case F_control_group_not:
          *string = f_status_control_group_not_s;
          break;

        case F_critical:
          *string = f_status_critical_s;
          break;

        case F_critical_not:
          *string = f_status_critical_not_s;
          break;

        case F_dead:
          *string = f_status_dead_s;
          break;

        case F_dead_not:
          *string = f_status_dead_not_s;
          break;

        case F_deadlock:
          *string = f_status_deadlock_s;
          break;

        case F_deadlock_not:
          *string = f_status_deadlock_not_s;
          break;

        case F_descriptor:
          *string = f_status_descriptor_s;
          break;

        case F_descriptor_not:
          *string = f_status_descriptor_not_s;
          break;

        case F_device:
          *string = f_status_device_s;
          break;

        case F_device_not:
          *string = f_status_device_not_s;
          break;

        case F_disable:
          *string = f_status_disable_s;
          break;

        case F_disable_not:
          *string = f_status_disable_not_s;
          break;

        case F_domain:
          *string = f_status_domain_s;
          break;

        case F_domain_not:
          *string = f_status_domain_not_s;
          break;

        case F_done:
          *string = f_status_done_s;
          break;

        case F_done_not:
          *string = f_status_done_not_s;
          break;

        case F_dummy:
          *string = f_status_dummy_s;
          break;

        case F_dummy_not:
          *string = f_status_dummy_not_s;
          break;

        case F_empty:
          *string = f_status_empty_s;
          break;

        case F_empty_not:
          *string = f_status_empty_not_s;
          break;

        case F_enable:
          *string = f_status_enable_s;
          break;

        case F_enable_not:
          *string = f_status_enable_not_s;
          break;

        case F_encoding:
          *string = f_status_encoding_s;
          break;

        case F_encoding_not:
          *string = f_status_encoding_not_s;
          break;

        case F_end:
          *string = f_status_end_s;
          break;

        case F_end_not:
          *string = f_status_end_not_s;
          break;

        case F_eoa:
          *string = f_status_eoa_s;
          break;

        case F_eoa_not:
          *string = f_status_eoa_not_s;
          break;

        case F_eof:
          *string = f_status_eof_s;
          break;

        case F_eof_not:
          *string = f_status_eof_not_s;
          break;

        case F_eol:
          *string = f_status_eol_s;
          break;

        case F_eol_not:
          *string = f_status_eol_not_s;
          break;

        case F_eos:
          *string = f_status_eos_s;
          break;

        case F_eos_not:
          *string = f_status_eos_not_s;
          break;

        case F_execute:
          *string = f_status_execute_s;
          break;

        case F_execute_not:
          *string = f_status_execute_not_s;
          break;

        case F_exist:
          *string = f_status_exist_s;
          break;

        case F_exist_not:
          *string = f_status_exist_not_s;
          break;

        case F_failure:
          *string = f_status_failure_s;
          break;

        case F_failure_not:
          *string = f_status_failure_not_s;
          break;

        case F_family:
          *string = f_status_family_s;
          break;

        case F_family_not:
          *string = f_status_family_not_s;
          break;

        case F_first:
          *string = f_status_first_s;
          break;

        case F_first_not:
          *string = f_status_first_not_s;
          break;

        case F_fork:
          *string = f_status_fork_s;
          break;

        case F_fork_not:
          *string = f_status_fork_not_s;
          break;

        case F_format:
          *string = f_status_format_s;
          break;

        case F_format_not:
          *string = f_status_format_not_s;
          break;

        case F_found:
          *string = f_status_found_s;
          break;

        case F_found_not:
          *string = f_status_found_not_s;
          break;

        case F_full:
          *string = f_status_full_s;
          break;

        case F_full_not:
          *string = f_status_full_not_s;
          break;

        case F_group:
          *string = f_status_group_s;
          break;

        case F_group_not:
          *string = f_status_group_not_s;
          break;

        case F_ignore:
          *string = f_status_ignore_s;
          break;

        case F_ignore_not:
          *string = f_status_ignore_not_s;
          break;

        case F_implemented:
          *string = f_status_implemented_s;
          break;

        case F_implemented_not:
          *string = f_status_implemented_not_s;
          break;

        case F_input:
          *string = f_status_input_s;
          break;

        case F_input_not:
          *string = f_status_input_not_s;
          break;

        case F_input_output:
          *string = f_status_input_output_s;
          break;

        case F_interrupt:
          *string = f_status_interrupt_s;
          break;

        case F_interrupt_not:
          *string = f_status_interrupt_not_s;
          break;

        case F_last:
          *string = f_status_last_s;
          break;

        case F_last_not:
          *string = f_status_last_not_s;
          break;

        case F_limit:
          *string = f_status_limit_s;
          break;

        case F_limit_not:
          *string = f_status_limit_not_s;
          break;

        case F_link:
          *string = f_status_link_s;
          break;

        case F_link_not:
          *string = f_status_link_not_s;
          break;

        case F_live:
          *string = f_status_live_s;
          break;

        case F_live_not:
          *string = f_status_live_not_s;
          break;

        case F_lock:
          *string = f_status_lock_s;
          break;

        case F_lock_not:
          *string = f_status_lock_not_s;
          break;

        case F_loop:
          *string = f_status_loop_s;
          break;

        case F_loop_not:
          *string = f_status_loop_not_s;
          break;

        case F_maybe:
          *string = f_status_maybe_s;
          break;

        case F_maybe_not:
          *string = f_status_maybe_not_s;
          break;

        case F_memory:
          *string = f_status_memory_s;
          break;

        case F_memory_not:
          *string = f_status_memory_not_s;
          break;

        case F_minor:
          *string = f_status_minor_s;
          break;

        case F_minor_not:
          *string = f_status_minor_not_s;
          break;

        case F_moderate:
          *string = f_status_moderate_s;
          break;

        case F_moderate_not:
          *string = f_status_moderate_not_s;
          break;

        case F_mount:
          *string = f_status_mount_s;
          break;

        case F_mount_not:
          *string = f_status_mount_not_s;
          break;

        case F_name:
          *string = f_status_name_s;
          break;

        case F_name_not:
          *string = f_status_name_not_s;
          break;

        case F_next:
          *string = f_status_next_s;
          break;

        case F_next_not:
          *string = f_status_next_not_s;
          break;

        case F_nice:
          *string = f_status_nice_s;
          break;

        case F_nice_not:
          *string = f_status_nice_not_s;
          break;

        case F_option:
          *string = f_status_option_s;
          break;

        case F_option_not:
          *string = f_status_option_not_s;
          break;

        case F_output:
          *string = f_status_output_s;
          break;

        case F_output_not:
          *string = f_status_output_not_s;
          break;

        case F_parameter:
          *string = f_status_parameter_s;
          break;

        case F_parameter_not:
          *string = f_status_parameter_not_s;
          break;

        case F_parent:
          *string = f_status_parent_s;
          break;

        case F_parent_not:
          *string = f_status_parent_not_s;
          break;

        case F_pipe:
          *string = f_status_pipe_s;
          break;

        case F_pipe_not:
          *string = f_status_pipe_not_s;
          break;

        case F_port:
          *string = f_status_port_s;
          break;

        case F_port_not:
          *string = f_status_port_not_s;
          break;

        case F_previous:
          *string = f_status_previous_s;
          break;

        case F_previous_not:
          *string = f_status_previous_not_s;
          break;

        case F_processor:
          *string = f_status_processor_s;
          break;

        case F_processor_not:
          *string = f_status_processor_not_s;
          break;

        case F_progress:
          *string = f_status_progress_s;
          break;

        case F_progress_not:
          *string = f_status_progress_not_s;
          break;

        case F_prohibited:
          *string = f_status_prohibited_s;
          break;

        case F_prohibited_not:
          *string = f_status_prohibited_not_s;
          break;

        case F_property:
          *string = f_status_property_s;
          break;

        case F_property_not:
          *string = f_status_property_not_s;
          break;

        case F_protocol:
          *string = f_status_protocol_s;
          break;

        case F_protocol_not:
          *string = f_status_protocol_not_s;
          break;

        case F_range:
          *string = f_status_range_s;
          break;

        case F_range_not:
          *string = f_status_range_not_s;
          break;

        case F_read:
          *string = f_status_read_s;
          break;

        case F_read_not:
          *string = f_status_read_not_s;
          break;

        case F_read_only:
          *string = f_status_read_only_s;
          break;

        case F_ready:
          *string = f_status_ready_s;
          break;

        case F_ready_not:
          *string = f_status_ready_not_s;
          break;

        case F_recover:
          *string = f_status_recover_s;
          break;

        case F_recover_not:
          *string = f_status_recover_not_s;
          break;

        case F_recurse:
          *string = f_status_recurse_s;
          break;

        case F_recurse_not:
          *string = f_status_recurse_not_s;
          break;

        case F_relative:
          *string = f_status_relative_s;
          break;

        case F_relative_not:
          *string = f_status_relative_not_s;
          break;

        case F_require:
          *string = f_status_require_s;
          break;

        case F_require_not:
          *string = f_status_require_not_s;
          break;

        case F_resource:
          *string = f_status_resource_s;
          break;

        case F_resource_not:
          *string = f_status_resource_not_s;
          break;

        case F_search:
          *string = f_status_search_s;
          break;

        case F_search_not:
          *string = f_status_search_not_s;
          break;

        case F_schedule:
          *string = f_status_schedule_s;
          break;

        case F_schedule_not:
          *string = f_status_schedule_not_s;
          break;

        case F_signal:
          *string = f_status_signal_s;
          break;

        case F_signal_not:
          *string = f_status_signal_not_s;
          break;

        case F_space:
          *string = f_status_space_s;
          break;

        case F_space_not:
          *string = f_status_space_not_s;
          break;

        case F_start:
          *string = f_status_start_s;
          break;

        case F_start_not:
          *string = f_status_start_not_s;
          break;

        case F_stop:
          *string = f_status_stop_s;
          break;

        case F_stop_not:
          *string = f_status_stop_not_s;
          break;

        case F_stream:
          *string = f_status_stream_s;
          break;

        case F_stream_not:
          *string = f_status_stream_not_s;
          break;

        case F_string:
          *string = f_status_string_s;
          break;

        case F_string_not:
          *string = f_status_string_not_s;
          break;

        case F_string_too_large:
          *string = f_status_too_large_s;
          break;

        case F_string_too_small:
          *string = f_status_too_small_s;
          break;

        case F_syntax:
          *string = f_status_syntax_s;
          break;

        case F_syntax_not:
          *string = f_status_syntax_not_s;
          break;

        case F_thread:
          *string = f_status_thread_s;
          break;

        case F_thread_not:
          *string = f_status_thread_not_s;
          break;

        case F_time:
          *string = f_status_time_s;
          break;

        case F_time_not:
          *string = f_status_time_not_s;
          break;

        case F_time_out:
          *string = f_status_time_out_s;
          break;

        case F_too_large:
          *string = f_status_too_large_s;
          break;

        case F_too_small:
          *string = f_status_too_small_s;
          break;

        case F_type:
          *string = f_status_type_s;
          break;

        case F_type_not:
          *string = f_status_type_not_s;
          break;

        case F_known:
          *string = f_status_known_s;
          break;

        case F_known_not:
          *string = f_status_known_not_s;
          break;

        case F_success:
          *string = f_status_success_s;
          break;

        case F_success_not:
          *string = f_status_success_not_s;
          break;

        case F_supported:
          *string = f_status_supported_s;
          break;

        case F_supported_not:
          *string = f_status_supported_not_s;
          break;

        case F_user:
          *string = f_status_user_s;
          break;

        case F_user_not:
          *string = f_status_user_not_s;
          break;

        case F_utf:
          *string = f_status_utf_s;
          break;

        case F_utf_fragment:
          *string = f_status_utf_fragment_s;
          break;

        case F_utf_fragment_not:
          *string = f_status_utf_fragment_not_s;
          break;

        case F_utf_not:
          *string = f_status_utf_not_s;
          break;

        case F_valid:
          *string = f_status_valid_s;
          break;

        case F_valid_not:
          *string = f_status_valid_not_s;
          break;

        case F_value:
          *string = f_status_value_s;
          break;

        case F_value_not:
          *string = f_status_value_not_s;
          break;

        case F_wait:
          *string = f_status_wait_s;
          break;

        case F_wait_not:
          *string = f_status_wait_not_s;
          break;

        case F_warn:
          *string = f_status_warn_s;
          break;

        case F_warn_not:
          *string = f_status_warn_not_s;
          break;

        case F_world:
          *string = f_status_world_s;
          break;

        case F_world_not:
          *string = f_status_world_not_s;
          break;

        case F_write:
          *string = f_status_write_s;
          break;

        case F_write_not:
          *string = f_status_write_not_s;
          break;

        case F_write_only:
          *string = f_status_write_only_s;
          break;
      #endif // _di_F_status_basic_

      #ifndef _di_F_status_array_
        case F_array:
          *string = f_status_array_s;
          break;

        case F_array_not:
          *string = f_status_array_not_s;
          break;

        case F_array_too_large:
          *string = f_status_array_too_large_s;
          break;

        case F_array_too_small:
          *string = f_status_array_too_small_s;
          break;
      #endif // _di_F_status_array_

      #ifndef _di_F_status_available_
        case F_available:
          *string = f_status_available_s;
          break;

        case F_available_not:
          *string = f_status_available_not_s;
          break;

        case F_available_not_address:
          *string = f_status_available_not_address_s;
          break;

        case F_available_not_buffer:
          *string = f_status_available_not_buffer_s;
          break;

        case F_available_not_device:
          *string = f_status_available_not_device_s;
          break;

        case F_available_not_pipe:
          *string = f_status_available_not_pipe_s;
          break;

        case F_available_not_port:
          *string = f_status_available_not_port_s;
          break;

        case F_available_not_process:
          *string = f_status_available_not_process_s;
          break;

        case F_available_not_socket:
          *string = f_status_available_not_socket_s;
          break;
      #endif // _di_F_status_available_

      #ifndef _di_F_status_busy_
        case F_busy:
          *string = f_status_busy_s;
          break;

        case F_busy_address:
          *string = f_status_busy_address_s;
          break;

        case F_busy_buffer:
          *string = f_status_busy_buffer_s;
          break;

        case F_busy_device:
          *string = f_status_busy_device_s;
          break;

        case F_busy_not:
          *string = f_status_busy_not_s;
          break;

        case F_busy_pipe:
          *string = f_status_busy_pipe_s;
          break;

        case F_busy_port:
          *string = f_status_busy_port_s;
          break;

        case F_busy_process:
          *string = f_status_busy_process_s;
          break;

        case F_busy_socket:
          *string = f_status_busy_socket_s;
          break;
      #endif // _di_F_status_busy_

      #ifndef _di_F_status_network_
        case F_network:
          *string = f_status_network_s;
          break;

        case F_network_busy:
          *string = f_status_network_busy_s;
          break;

        case F_network_busy_not:
          *string = f_status_network_busy_not_s;
          break;

        case F_network_found:
          *string = f_status_network_found_s;
          break;

        case F_network_found_not:
          *string = f_status_network_found_not_s;
          break;

        case F_network_lost:
          *string = f_status_network_lost_s;
          break;

        case F_network_lost_not:
          *string = f_status_network_lost_not_s;
          break;

        case F_network_not:
          *string = f_status_network_not_s;
          break;

        case F_network_reach:
          *string = f_status_network_reach_s;
          break;

        case F_network_reach_not:
          *string = f_status_network_reach_not_s;
          break;

        case F_network_time:
          *string = f_status_network_time_s;
          break;

        case F_network_time_not:
          *string = f_status_network_time_not_s;
          break;
      #endif // _di_F_status_network_

      #ifndef _di_F_status_number_
        case F_number:
          *string = f_status_number_s;
          break;

        case F_number_decimal:
          *string = f_status_number_decimal_s;
          break;

        case F_number_decimal_not:
          *string = f_status_number_decimal_not_s;
          break;

        case F_number_divide_by_zero:
          *string = f_status_number_divide_by_zero_s;
          break;

        case F_number_negative:
          *string = f_status_number_negative_s;
          break;

        case F_number_negative_not:
          *string = f_status_number_negative_not_s;
          break;

        case F_number_not:
          *string = f_status_number_not_s;
          break;

        case F_number_overflow:
          *string = f_status_number_overflow_s;
          break;

        case F_number_positive:
          *string = f_status_number_positive_s;
          break;

        case F_number_positive_not:
          *string = f_status_number_positive_not_s;
          break;

        case F_number_too_large:
          *string = f_status_number_too_large_s;
          break;

        case F_number_too_small:
          *string = f_status_number_too_small_s;
          break;

        case F_number_underflow:
          *string = f_status_number_underflow_s;
          break;

        case F_number_whole:
          *string = f_status_number_whole_s;
          break;

        case F_number_whole_not:
          *string = f_status_number_whole_not_s;
          break;

        case F_number_zero:
          *string = f_status_number_zero_s;
          break;

        case F_number_zero_not:
          *string = f_status_number_zero_not_s;
          break;
      #endif // _di_F_status_number_

      #ifndef _di_F_status_buffers_
        case F_buffer:
          *string = f_status_buffer_s;
          break;

        case F_buffer_not:
          *string = f_status_buffer_not_s;
          break;

        case F_buffer_too_large:
          *string = f_status_buffer_too_large_s;
          break;

        case F_buffer_too_small:
          *string = f_status_buffer_too_small_s;
          break;

        case F_complete_not_utf_block:
          *string = f_status_complete_not_utf_block_s;
          break;

        case F_complete_not_utf_eoa:
          *string = f_status_complete_not_utf_eoa_s;
          break;

        case F_complete_not_utf_eof:
          *string = f_status_complete_not_utf_eof_s;
          break;

        case F_complete_not_utf_eol:
          *string = f_status_complete_not_utf_eol_s;
          break;

        case F_complete_not_utf_eos:
          *string = f_status_complete_not_utf_eos_s;
          break;

        case F_complete_not_utf_stop:
          *string = f_status_complete_not_utf_stop_s;
          break;

        case F_none_block:
          *string = f_status_none_block_s;
          break;

        case F_none_eoa:
          *string = f_status_none_eoa_s;
          break;

        case F_none_eof:
          *string = f_status_none_eof_s;
          break;

        case F_none_eol:
          *string = f_status_none_eol_s;
          break;

        case F_none_eos:
          *string = f_status_none_eos_s;
          break;

        case F_none_stop:
          *string = f_status_none_stop_s;
          break;

        case F_data:
          *string = f_status_data_s;
          break;

        case F_data_not:
          *string = f_status_data_not_s;
          break;

        case F_data_not_block:
          *string = f_status_data_not_block_s;
          break;

        case F_data_not_eoa:
          *string = f_status_data_not_eoa_s;
          break;

        case F_data_not_eof:
          *string = f_status_data_not_eof_s;
          break;

        case F_data_not_eol:
          *string = f_status_data_not_eol_s;
          break;

        case F_data_not_eos:
          *string = f_status_data_not_eos_s;
          break;

        case F_data_not_stop:
          *string = f_status_data_not_stop_s;
          break;

        case F_terminated:
          *string = f_status_terminated_s;
          break;

        case F_terminated_not:
          *string = f_status_terminated_not_s;
          break;

        case F_terminated_not_block:
          *string = f_status_terminated_not_block_s;
          break;

        case F_terminated_not_eoa:
          *string = f_status_terminated_not_eoa_s;
          break;

        case F_terminated_not_eof:
          *string = f_status_terminated_not_eof_s;
          break;

        case F_terminated_not_eol:
          *string = f_status_terminated_not_eol_s;
          break;

        case F_terminated_not_eos:
          *string = f_status_terminated_not_eos_s;
          break;

        case F_terminated_not_group:
          *string = f_status_terminated_not_group_s;
          break;

        case F_terminated_not_group_block:
          *string = f_status_terminated_not_group_block_s;
          break;

        case F_terminated_not_group_eoa:
          *string = f_status_terminated_not_group_eoa_s;
          break;

        case F_terminated_not_group_eof:
          *string = f_status_terminated_not_group_eof_s;
          break;

        case F_terminated_not_group_eol:
          *string = f_status_terminated_not_group_eol_s;
          break;

        case F_terminated_not_group_eos:
          *string = f_status_terminated_not_group_eos_s;
          break;

        case F_terminated_not_group_stop:
          *string = f_status_terminated_not_group_stop_s;
          break;

        case F_terminated_not_nest:
          *string = f_status_terminated_not_nest_s;
          break;

        case F_terminated_not_nest_block:
          *string = f_status_terminated_not_nest_block_s;
          break;

        case F_terminated_not_nest_eoa:
          *string = f_status_terminated_not_nest_eoa_s;
          break;

        case F_terminated_not_nest_eof:
          *string = f_status_terminated_not_nest_eof_s;
          break;

        case F_terminated_not_nest_eol:
          *string = f_status_terminated_not_nest_eol_s;
          break;

        case F_terminated_not_nest_eos:
          *string = f_status_terminated_not_nest_eos_s;
          break;

        case F_terminated_not_nest_stop:
          *string = f_status_terminated_not_nest_stop_s;
          break;

        case F_terminated_not_stop:
          *string = f_status_terminated_not_stop_s;
          break;
      #endif // _di_F_status_buffers_

      #ifndef _di_F_status_process_
        case F_process:
          *string = f_status_process_s;
          break;

        case F_process_not:
          *string = f_status_process_not_s;
          break;

        case F_process_too_many:
          *string = f_status_process_too_many_s;
          break;
      #endif // _di_F_status_process_

      #ifndef _di_F_status_file_
        case F_file:
          *string = f_status_file_s;
          break;

        case F_file_close:
          *string = f_status_file_close_s;
          break;

        case F_file_closed:
          *string = f_status_file_closed_s;
          break;

        case F_file_descriptor:
          *string = f_status_file_descriptor_s;
          break;

        case F_file_descriptor_max:
          *string = f_status_file_descriptor_max_s;
          break;

        case F_file_descriptor_not:
          *string = f_status_file_descriptor_not_s;
          break;

        case F_file_empty:
          *string = f_status_file_empty_s;
          break;

        case F_file_flush:
          *string = f_status_file_flush_s;
          break;

        case F_file_found:
          *string = f_status_file_found_s;
          break;

        case F_file_found_not:
          *string = f_status_file_found_not_s;
          break;

        case F_file_not:
          *string = f_status_file_not_s;
          break;

        case F_file_open:
          *string = f_status_file_open_s;
          break;

        case F_file_open_max:
          *string = f_status_file_open_max_s;
          break;

        case F_file_opened:
          *string = f_status_file_opened_s;
          break;

        case F_file_overflow:
          *string = f_status_file_overflow_s;
          break;

        case F_file_purge:
          *string = f_status_file_purge_s;
          break;

        case F_file_read:
          *string = f_status_file_read_s;
          break;

        case F_file_reallocation:
          *string = f_status_file_reallocation_s;
          break;

        case F_file_seek:
          *string = f_status_file_seek_s;
          break;

        case F_file_stat:
          *string = f_status_file_stat_s;
          break;

        case F_file_synchronize:
          *string = f_status_file_synchronize_s;
          break;

        case F_file_type_block:
          *string = f_status_file_type_block_s;
          break;

        case F_file_type_character:
          *string = f_status_file_type_character_s;
          break;

        case F_file_type_directory:
          *string = f_status_file_type_directory_s;
          break;

        case F_file_type_fifo:
          *string = f_status_file_type_fifo_s;
          break;

        case F_file_type_link:
          *string = f_status_file_type_link_s;
          break;

        case F_file_type_not_character:
          *string = f_status_file_type_not_character_s;
          break;

        case F_file_type_not_directory:
          *string = f_status_file_type_not_directory_s;
          break;

        case F_file_type_not_fifo:
          *string = f_status_file_type_not_fifo_s;
          break;

        case F_file_type_not_link:
          *string = f_status_file_type_not_link_s;
          break;

        case F_file_type_not_pipe:
          *string = f_status_file_type_not_pipe_s;
          break;

        case F_file_type_not_regular:
          *string = f_status_file_type_not_regular_s;
          break;

        case F_file_type_not_socket:
          *string = f_status_file_type_not_socket_s;
          break;

        case F_file_type_not_unknown:
          *string = f_status_file_type_not_unknown_s;
          break;

        case F_file_type_pipe:
          *string = f_status_file_type_pipe_s;
          break;

        case F_file_type_regular:
          *string = f_status_file_type_regular_s;
          break;

        case F_file_type_socket:
          *string = f_status_file_type_socket_s;
          break;

        case F_file_type_unknown:
          *string = f_status_file_type_unknown_s;
          break;

        case F_file_underflow:
          *string = f_status_file_underflow_s;
          break;

        case F_file_utf:
          *string = f_status_file_utf_s;
          break;

        case F_file_utf_not:
          *string = f_status_file_utf_not_s;
          break;

        case F_file_write:
          *string = f_status_file_write_s;
          break;
      #endif // _di_F_status_file_

      #ifndef _di_F_status_filesystem_
        case F_filesystem:
          *string = f_status_filesystem_s;
          break;

        case F_filesystem_not:
          *string = f_status_filesystem_not_s;
          break;

        case F_filesystem_quota_block:
          *string = f_status_filesystem_quota_block_s;
          break;

        case F_filesystem_quota_reached:
          *string = f_status_filesystem_quota_reached_s;
          break;
      #endif // _di_F_status_filesystem_

      #ifndef _di_F_status_directory_
        case F_directory:
          *string = f_status_directory_s;
          break;

        case F_directory_close:
          *string = f_status_directory_close_s;
          break;

        case F_directory_closed:
          *string = f_status_directory_closed_s;
          break;

        case F_directory_descriptor:
          *string = f_status_directory_descriptor_s;
          break;

        case F_directory_empty:
          *string = f_status_directory_empty_s;
          break;

        case F_directory_empty_not:
          *string = f_status_directory_empty_not_s;
          break;

        case F_directory_found:
          *string = f_status_directory_found_s;
          break;

        case F_directory_found_not:
          *string = f_status_directory_found_not_s;
          break;

        case F_directory_flush:
          *string = f_status_directory_flush_s;
          break;

        case F_directory_link_max:
          *string = f_status_directory_link_max_s;
          break;

        case F_directory_not:
          *string = f_status_directory_not_s;
          break;

        case F_directory_open:
          *string = f_status_directory_open_s;
          break;

        case F_directory_purge:
          *string = f_status_directory_purge_s;
          break;

        case F_directory_read:
          *string = f_status_directory_read_s;
          break;

        case F_directory_stream:
          *string = f_status_directory_stream_s;
          break;

        case F_directory_synchronize:
          *string = f_status_directory_synchronize_s;
          break;

        case F_directory_supported_not:
          *string = f_status_directory_supported_not_s;
          break;

        case F_directory_utf:
          *string = f_status_directory_utf_s;
          break;

        case F_directory_utf_not:
          *string = f_status_directory_utf_not_s;
          break;

        case F_directory_write:
          *string = f_status_directory_utf_not_s;
          break;
      #endif // _di_F_status_directory_

      #ifndef _di_F_status_socket_
        case F_socket:
          *string = f_status_socket_s;
          break;

        case F_socket_client:
          *string = f_status_socket_client_s;
          break;

        case F_socket_not:
          *string = f_status_socket_not_s;
          break;

        case F_socket_receive:
          *string = f_status_socket_receive_s;
          break;

        case F_socket_send:
          *string = f_status_socket_send_s;
          break;

        case F_socket_target:
          *string = f_status_socket_target_s;
          break;
      #endif // _di_F_status_socket_

      #ifndef _di_F_error_compare_
        case F_equal_to:
          *string = f_status_equal_to_s;
          break;

        case F_equal_to_not:
          *string = f_status_equal_to_not_s;
          break;

        case F_than_greater:
          *string = f_status_than_greater_s;
          break;

        case F_than_less:
          *string = f_status_than_less_s;
          break;
      #endif // _di_F_status_compare_

      #ifndef _di_F_status_access_
        case F_access:
          *string = f_status_access_s;
          break;

        case F_access_denied:
          *string = f_status_access_denied_s;
          break;

        case F_access_denied_user:
          *string = f_status_access_denied_user_s;
          break;

        case F_access_denied_group:
          *string = f_status_access_denied_group_s;
          break;

        case F_access_denied_world:
          *string = f_status_access_denied_world_s;
          break;

        case F_access_denied_read:
          *string = f_status_access_denied_read_s;
          break;

        case F_access_denied_write:
          *string = f_status_access_denied_write_s;
          break;

        case F_access_denied_execute:
          *string = f_status_access_denied_execute_s;
          break;

        case F_access_denied_super:
          *string = f_status_access_denied_super_s;
          break;

        case F_access_granted:
          *string = f_status_access_granted_s;
          break;

        case F_access_granted_user:
          *string = f_status_access_granted_user_s;
          break;

        case F_access_granted_group:
          *string = f_status_access_granted_group_s;
          break;

        case F_access_granted_world:
          *string = f_status_access_granted_world_s;
          break;

        case F_access_granted_read:
          *string = f_status_access_granted_read_s;
          break;

        case F_access_granted_write:
          *string = f_status_access_granted_write_s;
          break;

        case F_access_granted_execute:
          *string = f_status_access_granted_execute_s;
          break;

        case F_access_granted_super:
          *string = f_status_access_granted_super_s;
          break;

        case F_access_group:
          *string = f_status_access_group_s;
          break;

        case F_access_mode:
          *string = f_status_access_mode_s;
          break;

        case F_access_not:
          *string = f_status_access_not_s;
          break;

        case F_access_owner:
          *string = f_status_access_owner_s;
          break;
      #endif // _di_F_status_access_

      #ifndef _di_F_status_terminal_
        case F_terminal:
          *string = f_status_terminal_s;
          break;

        case F_terminal_access:
          *string = f_status_terminal_access_s;
          break;

        case F_terminal_known:
          *string = f_status_terminal_known_s;
          break;

        case F_terminal_known_not:
          *string = f_status_terminal_known_not_s;
          break;

        case F_terminal_not:
          *string = f_status_terminal_not_s;
          break;

        case F_terminal_prohibited:
          *string = f_status_terminal_prohibited_s;
          break;

        case F_terminal_read:
          *string = f_status_terminal_read_s;
          break;

        case F_terminal_valid:
          *string = f_status_terminal_valid_s;
          break;

        case F_terminal_valid_not:
          *string = f_status_terminal_valid_not_s;
          break;

        case F_terminal_write:
          *string = f_status_terminal_write_s;
          break;
      #endif // _di_F_status_terminal_

      case F_status_code_last:
        *string = f_status_status_code_last_s;
        break;

      default:
        *string = 0;

        return F_status_set_error(F_data);
    }

    return F_none;
  }
#endif // _di_f_status_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

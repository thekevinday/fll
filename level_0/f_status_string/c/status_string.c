#include "status_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_status_string_
  #ifndef _di_f_status_boolean_
    const f_string_static_t f_status_false_s = macro_f_string_static_t_initialize(F_status_false_s, 0, F_status_false_s_length);
    const f_string_static_t f_status_true_s = macro_f_string_static_t_initialize(F_status_true_s, 0, F_status_true_s_length);
  #endif // _di_f_status_boolean_

  #ifndef _di_f_status_signal_
    const f_string_static_t f_status_signal_hangup_s = macro_f_string_static_t_initialize(F_status_signal_hangup_s, 0, F_status_signal_hangup_s_length);
    const f_string_static_t f_status_signal_interrupt_s = macro_f_string_static_t_initialize(F_status_signal_interrupt_s, 0, F_status_signal_interrupt_s_length);
    const f_string_static_t f_status_signal_quit_s = macro_f_string_static_t_initialize(F_status_signal_quit_s, 0, F_status_signal_quit_s_length);
    const f_string_static_t f_status_signal_illegal_s = macro_f_string_static_t_initialize(F_status_signal_illegal_s, 0, F_status_signal_illegal_s_length);
    const f_string_static_t f_status_signal_trap_s = macro_f_string_static_t_initialize(F_status_signal_trap_s, 0, F_status_signal_trap_s_length);
    const f_string_static_t f_status_signal_abort_s = macro_f_string_static_t_initialize(F_status_signal_abort_s, 0, F_status_signal_abort_s_length);
    const f_string_static_t f_status_signal_bus_error_s = macro_f_string_static_t_initialize(F_status_signal_bus_error_s, 0, F_status_signal_bus_error_s_length);
    const f_string_static_t f_status_signal_floating_point_error_s = macro_f_string_static_t_initialize(F_status_signal_floating_point_error_s, 0, F_status_signal_floating_point_error_s_length);
    const f_string_static_t f_status_signal_kill_s = macro_f_string_static_t_initialize(F_status_signal_kill_s, 0, F_status_signal_kill_s_length);
    const f_string_static_t f_status_signal_user_1_s = macro_f_string_static_t_initialize(F_status_signal_user_1_s, 0, F_status_signal_user_1_s_length);
    const f_string_static_t f_status_signal_segmentation_fault_s = macro_f_string_static_t_initialize(F_status_signal_segmentation_fault_s, 0, F_status_signal_segmentation_fault_s_length);
    const f_string_static_t f_status_signal_user_2_s = macro_f_string_static_t_initialize(F_status_signal_user_2_s, 0, F_status_signal_user_2_s_length);
    const f_string_static_t f_status_signal_broken_pipe_s = macro_f_string_static_t_initialize(F_status_signal_broken_pipe_s, 0, F_status_signal_broken_pipe_s_length);
    const f_string_static_t f_status_signal_alarm_clock_s = macro_f_string_static_t_initialize(F_status_signal_alarm_clock_s, 0, F_status_signal_alarm_clock_s_length);
    const f_string_static_t f_status_signal_termination_s = macro_f_string_static_t_initialize(F_status_signal_termination_s, 0, F_status_signal_termination_s_length);
    const f_string_static_t f_status_signal_stack_fault_s = macro_f_string_static_t_initialize(F_status_signal_stack_fault_s, 0, F_status_signal_stack_fault_s_length);
    const f_string_static_t f_status_signal_child_s = macro_f_string_static_t_initialize(F_status_signal_child_s, 0, F_status_signal_child_s_length);
    const f_string_static_t f_status_signal_continue_s = macro_f_string_static_t_initialize(F_status_signal_continue_s, 0, F_status_signal_continue_s_length);
    const f_string_static_t f_status_signal_stop_s = macro_f_string_static_t_initialize(F_status_signal_stop_s, 0, F_status_signal_stop_s_length);
    const f_string_static_t f_status_signal_keyboard_stop_s = macro_f_string_static_t_initialize(F_status_signal_keyboard_stop_s, 0, F_status_signal_keyboard_stop_s_length);
    const f_string_static_t f_status_signal_tty_in_s = macro_f_string_static_t_initialize(F_status_signal_tty_in_s, 0, F_status_signal_tty_in_s_length);
    const f_string_static_t f_status_signal_tty_out_s = macro_f_string_static_t_initialize(F_status_signal_tty_out_s, 0, F_status_signal_tty_out_s_length);
    const f_string_static_t f_status_signal_urgent_s = macro_f_string_static_t_initialize(F_status_signal_urgent_s, 0, F_status_signal_urgent_s_length);
    const f_string_static_t f_status_signal_cpu_limit_s = macro_f_string_static_t_initialize(F_status_signal_cpu_limit_s, 0, F_status_signal_cpu_limit_s_length);
    const f_string_static_t f_status_signal_file_size_limit_s = macro_f_string_static_t_initialize(F_status_signal_file_size_limit_s, 0, F_status_signal_file_size_limit_s_length);
    const f_string_static_t f_status_signal_virtual_alarm_clock_s = macro_f_string_static_t_initialize(F_status_signal_virtual_alarm_clock_s, 0, F_status_signal_virtual_alarm_clock_s_length);
    const f_string_static_t f_status_signal_profile_alarm_clock_s = macro_f_string_static_t_initialize(F_status_signal_profile_alarm_clock_s, 0, F_status_signal_profile_alarm_clock_s_length);
    const f_string_static_t f_status_signal_window_size_change_s = macro_f_string_static_t_initialize(F_status_signal_window_size_change_s, 0, F_status_signal_window_size_change_s_length);
    const f_string_static_t f_status_signal_pollable_event_s = macro_f_string_static_t_initialize(F_status_signal_pollable_event_s, 0, F_status_signal_pollable_event_s_length);
    const f_string_static_t f_status_signal_power_failure_s = macro_f_string_static_t_initialize(F_status_signal_power_failure_s, 0, F_status_signal_power_failure_s_length);
    const f_string_static_t f_status_signal_bad_system_call_s = macro_f_string_static_t_initialize(F_status_signal_bad_system_call_s, 0, F_status_signal_bad_system_call_s_length);
    const f_string_static_t f_status_signal_reserved_32_s = macro_f_string_static_t_initialize(F_status_signal_reserved_32_s, 0, F_status_signal_reserved_32_s_length);
    const f_string_static_t f_status_signal_reserved_33_s = macro_f_string_static_t_initialize(F_status_signal_reserved_33_s, 0, F_status_signal_reserved_33_s_length);
    const f_string_static_t f_status_signal_reserved_34_s = macro_f_string_static_t_initialize(F_status_signal_reserved_34_s, 0, F_status_signal_reserved_34_s_length);
    const f_string_static_t f_status_signal_reserved_35_s = macro_f_string_static_t_initialize(F_status_signal_reserved_35_s, 0, F_status_signal_reserved_35_s_length);
    const f_string_static_t f_status_signal_reserved_36_s = macro_f_string_static_t_initialize(F_status_signal_reserved_36_s, 0, F_status_signal_reserved_36_s_length);
    const f_string_static_t f_status_signal_reserved_37_s = macro_f_string_static_t_initialize(F_status_signal_reserved_37_s, 0, F_status_signal_reserved_37_s_length);
    const f_string_static_t f_status_signal_reserved_38_s = macro_f_string_static_t_initialize(F_status_signal_reserved_38_s, 0, F_status_signal_reserved_38_s_length);
    const f_string_static_t f_status_signal_reserved_39_s = macro_f_string_static_t_initialize(F_status_signal_reserved_39_s, 0, F_status_signal_reserved_39_s_length);
    const f_string_static_t f_status_signal_reserved_40_s = macro_f_string_static_t_initialize(F_status_signal_reserved_40_s, 0, F_status_signal_reserved_40_s_length);
    const f_string_static_t f_status_signal_reserved_41_s = macro_f_string_static_t_initialize(F_status_signal_reserved_41_s, 0, F_status_signal_reserved_41_s_length);
    const f_string_static_t f_status_signal_reserved_42_s = macro_f_string_static_t_initialize(F_status_signal_reserved_42_s, 0, F_status_signal_reserved_42_s_length);
    const f_string_static_t f_status_signal_reserved_43_s = macro_f_string_static_t_initialize(F_status_signal_reserved_43_s, 0, F_status_signal_reserved_43_s_length);
    const f_string_static_t f_status_signal_reserved_44_s = macro_f_string_static_t_initialize(F_status_signal_reserved_44_s, 0, F_status_signal_reserved_44_s_length);
    const f_string_static_t f_status_signal_reserved_45_s = macro_f_string_static_t_initialize(F_status_signal_reserved_45_s, 0, F_status_signal_reserved_45_s_length);
    const f_string_static_t f_status_signal_reserved_46_s = macro_f_string_static_t_initialize(F_status_signal_reserved_46_s, 0, F_status_signal_reserved_46_s_length);
    const f_string_static_t f_status_signal_reserved_47_s = macro_f_string_static_t_initialize(F_status_signal_reserved_47_s, 0, F_status_signal_reserved_47_s_length);
    const f_string_static_t f_status_signal_reserved_48_s = macro_f_string_static_t_initialize(F_status_signal_reserved_48_s, 0, F_status_signal_reserved_48_s_length);
    const f_string_static_t f_status_signal_reserved_49_s = macro_f_string_static_t_initialize(F_status_signal_reserved_49_s, 0, F_status_signal_reserved_49_s_length);
    const f_string_static_t f_status_signal_reserved_50_s = macro_f_string_static_t_initialize(F_status_signal_reserved_50_s, 0, F_status_signal_reserved_50_s_length);
    const f_string_static_t f_status_signal_reserved_51_s = macro_f_string_static_t_initialize(F_status_signal_reserved_51_s, 0, F_status_signal_reserved_51_s_length);
    const f_string_static_t f_status_signal_reserved_52_s = macro_f_string_static_t_initialize(F_status_signal_reserved_52_s, 0, F_status_signal_reserved_52_s_length);
    const f_string_static_t f_status_signal_reserved_53_s = macro_f_string_static_t_initialize(F_status_signal_reserved_53_s, 0, F_status_signal_reserved_53_s_length);
    const f_string_static_t f_status_signal_reserved_54_s = macro_f_string_static_t_initialize(F_status_signal_reserved_54_s, 0, F_status_signal_reserved_54_s_length);
    const f_string_static_t f_status_signal_reserved_55_s = macro_f_string_static_t_initialize(F_status_signal_reserved_55_s, 0, F_status_signal_reserved_55_s_length);
    const f_string_static_t f_status_signal_reserved_56_s = macro_f_string_static_t_initialize(F_status_signal_reserved_56_s, 0, F_status_signal_reserved_56_s_length);
    const f_string_static_t f_status_signal_reserved_57_s = macro_f_string_static_t_initialize(F_status_signal_reserved_57_s, 0, F_status_signal_reserved_57_s_length);
    const f_string_static_t f_status_signal_reserved_58_s = macro_f_string_static_t_initialize(F_status_signal_reserved_58_s, 0, F_status_signal_reserved_58_s_length);
    const f_string_static_t f_status_signal_reserved_59_s = macro_f_string_static_t_initialize(F_status_signal_reserved_59_s, 0, F_status_signal_reserved_59_s_length);
    const f_string_static_t f_status_signal_reserved_60_s = macro_f_string_static_t_initialize(F_status_signal_reserved_60_s, 0, F_status_signal_reserved_60_s_length);
    const f_string_static_t f_status_signal_reserved_61_s = macro_f_string_static_t_initialize(F_status_signal_reserved_61_s, 0, F_status_signal_reserved_61_s_length);
    const f_string_static_t f_status_signal_reserved_62_s = macro_f_string_static_t_initialize(F_status_signal_reserved_62_s, 0, F_status_signal_reserved_62_s_length);
    const f_string_static_t f_status_signal_reserved_63_s = macro_f_string_static_t_initialize(F_status_signal_reserved_63_s, 0, F_status_signal_reserved_63_s_length);
    const f_string_static_t f_status_signal_reserved_64_s = macro_f_string_static_t_initialize(F_status_signal_reserved_64_s, 0, F_status_signal_reserved_64_s_length);
  #endif // _di_f_status_signal_

  #ifndef _di_f_status_basic_
    const f_string_static_t f_status_none_s = macro_f_string_static_t_initialize(F_status_none_s, 0, F_status_none_s_length);
    const f_string_static_t f_status_abort_s = macro_f_string_static_t_initialize(F_status_abort_s, 0, F_status_abort_s_length);
    const f_string_static_t f_status_abort_not_s = macro_f_string_static_t_initialize(F_status_abort_not_s, 0, F_status_abort_not_s_length);
    const f_string_static_t f_status_absolute_s = macro_f_string_static_t_initialize(F_status_absolute_s, 0, F_status_absolute_s_length);
    const f_string_static_t f_status_absolute_not_s = macro_f_string_static_t_initialize(F_status_absolute_not_s, 0, F_status_absolute_not_s_length);
    const f_string_static_t f_status_address_s = macro_f_string_static_t_initialize(F_status_address_s, 0, F_status_address_s_length);
    const f_string_static_t f_status_address_not_s = macro_f_string_static_t_initialize(F_status_address_not_s, 0, F_status_address_not_s_length);
    const f_string_static_t f_status_ascii_s = macro_f_string_static_t_initialize(F_status_ascii_s, 0, F_status_ascii_s_length);
    const f_string_static_t f_status_ascii_not_s = macro_f_string_static_t_initialize(F_status_ascii_not_s, 0, F_status_ascii_not_s_length);
    const f_string_static_t f_status_atomic_s = macro_f_string_static_t_initialize(F_status_atomic_s, 0, F_status_atomic_s_length);
    const f_string_static_t f_status_atomic_not_s = macro_f_string_static_t_initialize(F_status_atomic_not_s, 0, F_status_atomic_not_s_length);
    const f_string_static_t f_status_base_s = macro_f_string_static_t_initialize(F_status_base_s, 0, F_status_base_s_length);
    const f_string_static_t f_status_base_not_s = macro_f_string_static_t_initialize(F_status_base_not_s, 0, F_status_base_not_s_length);
    const f_string_static_t f_status_begin_s = macro_f_string_static_t_initialize(F_status_begin_s, 0, F_status_begin_s_length);
    const f_string_static_t f_status_begin_not_s = macro_f_string_static_t_initialize(F_status_begin_not_s, 0, F_status_begin_not_s_length);
    const f_string_static_t f_status_block_s = macro_f_string_static_t_initialize(F_status_block_s, 0, F_status_block_s_length);
    const f_string_static_t f_status_block_not_s = macro_f_string_static_t_initialize(F_status_block_not_s, 0, F_status_block_not_s_length);
    const f_string_static_t f_status_body_s = macro_f_string_static_t_initialize(F_status_body_s, 0, F_status_body_s_length);
    const f_string_static_t f_status_body_not_s = macro_f_string_static_t_initialize(F_status_body_not_s, 0, F_status_body_not_s_length);
    const f_string_static_t f_status_bound_s = macro_f_string_static_t_initialize(F_status_bound_s, 0, F_status_bound_s_length);
    const f_string_static_t f_status_bound_not_s = macro_f_string_static_t_initialize(F_status_bound_not_s, 0, F_status_bound_not_s_length);
    const f_string_static_t f_status_break_s = macro_f_string_static_t_initialize(F_status_break_s, 0, F_status_break_s_length);
    const f_string_static_t f_status_break_not_s = macro_f_string_static_t_initialize(F_status_break_not_s, 0, F_status_break_not_s_length);
    const f_string_static_t f_status_call_s = macro_f_string_static_t_initialize(F_status_call_s, 0, F_status_call_s_length);
    const f_string_static_t f_status_call_not_s = macro_f_string_static_t_initialize(F_status_call_not_s, 0, F_status_call_not_s_length);
    const f_string_static_t f_status_capability_s = macro_f_string_static_t_initialize(F_status_capability_s, 0, F_status_capability_s_length);
    const f_string_static_t f_status_capability_not_s = macro_f_string_static_t_initialize(F_status_capability_not_s, 0, F_status_capability_not_s_length);
    const f_string_static_t f_status_child_s = macro_f_string_static_t_initialize(F_status_child_s, 0, F_status_child_s_length);
    const f_string_static_t f_status_child_not_s = macro_f_string_static_t_initialize(F_status_child_not_s, 0, F_status_child_not_s_length);
    const f_string_static_t f_status_complete_s = macro_f_string_static_t_initialize(F_status_complete_s, 0, F_status_complete_s_length);
    const f_string_static_t f_status_complete_not_s = macro_f_string_static_t_initialize(F_status_complete_not_s, 0, F_status_complete_not_s_length);
    const f_string_static_t f_status_connect_s = macro_f_string_static_t_initialize(F_status_connect_s, 0, F_status_connect_s_length);
    const f_string_static_t f_status_connect_not_s = macro_f_string_static_t_initialize(F_status_connect_not_s, 0, F_status_connect_not_s_length);
    const f_string_static_t f_status_connect_refuse_s = macro_f_string_static_t_initialize(F_status_connect_refuse_s, 0, F_status_connect_refuse_s_length);
    const f_string_static_t f_status_connect_reset_s = macro_f_string_static_t_initialize(F_status_connect_reset_s, 0, F_status_connect_reset_s_length);
    const f_string_static_t f_status_container_s = macro_f_string_static_t_initialize(F_status_container_s, 0, F_status_container_s_length);
    const f_string_static_t f_status_container_not_s = macro_f_string_static_t_initialize(F_status_container_not_s, 0, F_status_container_not_s_length);
    const f_string_static_t f_status_content_s = macro_f_string_static_t_initialize(F_status_content_s, 0, F_status_content_s_length);
    const f_string_static_t f_status_content_not_s = macro_f_string_static_t_initialize(F_status_content_not_s, 0, F_status_content_not_s_length);
    const f_string_static_t f_status_continue_s = macro_f_string_static_t_initialize(F_status_continue_s, 0, F_status_continue_s_length);
    const f_string_static_t f_status_continue_not_s = macro_f_string_static_t_initialize(F_status_continue_not_s, 0, F_status_continue_not_s_length);
    const f_string_static_t f_status_control_s = macro_f_string_static_t_initialize(F_status_control_s, 0, F_status_control_s_length);
    const f_string_static_t f_status_control_not_s = macro_f_string_static_t_initialize(F_status_control_not_s, 0, F_status_control_not_s_length);
    const f_string_static_t f_status_control_group_s = macro_f_string_static_t_initialize(F_status_control_group_s, 0, F_status_control_group_s_length);
    const f_string_static_t f_status_control_group_not_s = macro_f_string_static_t_initialize(F_status_control_group_not_s, 0, F_status_control_group_not_s_length);
    const f_string_static_t f_status_critical_s = macro_f_string_static_t_initialize(F_status_critical_s, 0, F_status_critical_s_length);
    const f_string_static_t f_status_critical_not_s = macro_f_string_static_t_initialize(F_status_critical_not_s, 0, F_status_critical_not_s_length);
    const f_string_static_t f_status_dead_s = macro_f_string_static_t_initialize(F_status_dead_s, 0, F_status_dead_s_length);
    const f_string_static_t f_status_dead_not_s = macro_f_string_static_t_initialize(F_status_dead_not_s, 0, F_status_dead_not_s_length);
    const f_string_static_t f_status_deadlock_s = macro_f_string_static_t_initialize(F_status_deadlock_s, 0, F_status_deadlock_s_length);
    const f_string_static_t f_status_deadlock_not_s = macro_f_string_static_t_initialize(F_status_deadlock_not_s, 0, F_status_deadlock_not_s_length);
    const f_string_static_t f_status_descriptor_s = macro_f_string_static_t_initialize(F_status_descriptor_s, 0, F_status_descriptor_s_length);
    const f_string_static_t f_status_descriptor_not_s = macro_f_string_static_t_initialize(F_status_descriptor_not_s, 0, F_status_descriptor_not_s_length);
    const f_string_static_t f_status_desire_s = macro_f_string_static_t_initialize(F_status_desire_s, 0, F_status_desire_s_length);
    const f_string_static_t f_status_desire_not_s = macro_f_string_static_t_initialize(F_status_desire_not_s, 0, F_status_desire_not_s_length);
    const f_string_static_t f_status_device_s = macro_f_string_static_t_initialize(F_status_device_s, 0, F_status_device_s_length);
    const f_string_static_t f_status_device_not_s = macro_f_string_static_t_initialize(F_status_device_not_s, 0, F_status_device_not_s_length);
    const f_string_static_t f_status_disable_s = macro_f_string_static_t_initialize(F_status_disable_s, 0, F_status_disable_s_length);
    const f_string_static_t f_status_disable_not_s = macro_f_string_static_t_initialize(F_status_disable_not_s, 0, F_status_disable_not_s_length);
    const f_string_static_t f_status_discard_s = macro_f_string_static_t_initialize(F_status_discard_s, 0, F_status_discard_s_length);
    const f_string_static_t f_status_discard_not_s = macro_f_string_static_t_initialize(F_status_discard_not_s, 0, F_status_discard_not_s_length);
    const f_string_static_t f_status_domain_s = macro_f_string_static_t_initialize(F_status_domain_s, 0, F_status_domain_s_length);
    const f_string_static_t f_status_domain_not_s = macro_f_string_static_t_initialize(F_status_domain_not_s, 0, F_status_domain_not_s_length);
    const f_string_static_t f_status_done_s = macro_f_string_static_t_initialize(F_status_done_s, 0, F_status_done_s_length);
    const f_string_static_t f_status_done_not_s = macro_f_string_static_t_initialize(F_status_done_not_s, 0, F_status_done_not_s_length);
    const f_string_static_t f_status_drop_s = macro_f_string_static_t_initialize(F_status_drop_s, 0, F_status_drop_s_length);
    const f_string_static_t f_status_drop_not_s = macro_f_string_static_t_initialize(F_status_drop_not_s, 0, F_status_drop_not_s_length);
    const f_string_static_t f_status_dummy_s = macro_f_string_static_t_initialize(F_status_dummy_s, 0, F_status_dummy_s_length);
    const f_string_static_t f_status_dummy_not_s = macro_f_string_static_t_initialize(F_status_dummy_not_s, 0, F_status_dummy_not_s_length);
    const f_string_static_t f_status_empty_s = macro_f_string_static_t_initialize(F_status_empty_s, 0, F_status_empty_s_length);
    const f_string_static_t f_status_empty_not_s = macro_f_string_static_t_initialize(F_status_empty_not_s, 0, F_status_empty_not_s_length);
    const f_string_static_t f_status_enable_s = macro_f_string_static_t_initialize(F_status_enable_s, 0, F_status_enable_s_length);
    const f_string_static_t f_status_enable_not_s = macro_f_string_static_t_initialize(F_status_enable_not_s, 0, F_status_enable_not_s_length);
    const f_string_static_t f_status_encoding_s = macro_f_string_static_t_initialize(F_status_encoding_s, 0, F_status_encoding_s_length);
    const f_string_static_t f_status_encoding_not_s = macro_f_string_static_t_initialize(F_status_encoding_not_s, 0, F_status_encoding_not_s_length);
    const f_string_static_t f_status_endian_s = macro_f_string_static_t_initialize(F_status_endian_s, 0, F_status_endian_s_length);
    const f_string_static_t f_status_endian_big_s = macro_f_string_static_t_initialize(F_status_endian_big_s, 0, F_status_endian_big_s_length);
    const f_string_static_t f_status_endian_little_s = macro_f_string_static_t_initialize(F_status_endian_little_s, 0, F_status_endian_little_s_length);
    const f_string_static_t f_status_endian_not_s = macro_f_string_static_t_initialize(F_status_endian_not_s, 0, F_status_endian_not_s_length);
    const f_string_static_t f_status_eoa_s = macro_f_string_static_t_initialize(F_status_eoa_s, 0, F_status_eoa_s_length);
    const f_string_static_t f_status_eoa_not_s = macro_f_string_static_t_initialize(F_status_eoa_not_s, 0, F_status_eoa_not_s_length);
    const f_string_static_t f_status_eof_s = macro_f_string_static_t_initialize(F_status_eof_s, 0, F_status_eof_s_length);
    const f_string_static_t f_status_eof_not_s = macro_f_string_static_t_initialize(F_status_eof_not_s, 0, F_status_eof_not_s_length);
    const f_string_static_t f_status_eol_s = macro_f_string_static_t_initialize(F_status_eol_s, 0, F_status_eol_s_length);
    const f_string_static_t f_status_eol_not_s = macro_f_string_static_t_initialize(F_status_eol_not_s, 0, F_status_eol_not_s_length);
    const f_string_static_t f_status_eos_s = macro_f_string_static_t_initialize(F_status_eos_s, 0, F_status_eos_s_length);
    const f_string_static_t f_status_eos_not_s = macro_f_string_static_t_initialize(F_status_eos_not_s, 0, F_status_eos_not_s_length);
    const f_string_static_t f_status_execute_s = macro_f_string_static_t_initialize(F_status_execute_s, 0, F_status_execute_s_length);
    const f_string_static_t f_status_execute_not_s = macro_f_string_static_t_initialize(F_status_execute_not_s, 0, F_status_execute_not_s_length);
    const f_string_static_t f_status_exist_s = macro_f_string_static_t_initialize(F_status_exist_s, 0, F_status_exist_s_length);
    const f_string_static_t f_status_exist_not_s = macro_f_string_static_t_initialize(F_status_exist_not_s, 0, F_status_exist_not_s_length);
    const f_string_static_t f_status_exit_s = macro_f_string_static_t_initialize(F_status_exit_s, 0, F_status_exit_s_length);
    const f_string_static_t f_status_exit_not_s = macro_f_string_static_t_initialize(F_status_exit_not_s, 0, F_status_exit_not_s_length);
    const f_string_static_t f_status_failure_s = macro_f_string_static_t_initialize(F_status_failure_s, 0, F_status_failure_s_length);
    const f_string_static_t f_status_failure_not_s = macro_f_string_static_t_initialize(F_status_failure_not_s, 0, F_status_failure_not_s_length);
    const f_string_static_t f_status_family_s = macro_f_string_static_t_initialize(F_status_family_s, 0, F_status_family_s_length);
    const f_string_static_t f_status_family_not_s = macro_f_string_static_t_initialize(F_status_family_not_s, 0, F_status_family_not_s_length);
    const f_string_static_t f_status_first_s = macro_f_string_static_t_initialize(F_status_first_s, 0, F_status_first_s_length);
    const f_string_static_t f_status_first_not_s = macro_f_string_static_t_initialize(F_status_first_not_s, 0, F_status_first_not_s_length);
    const f_string_static_t f_status_footer_s = macro_f_string_static_t_initialize(F_status_footer_s, 0, F_status_footer_s_length);
    const f_string_static_t f_status_footer_not_s = macro_f_string_static_t_initialize(F_status_footer_not_s, 0, F_status_footer_not_s_length);
    const f_string_static_t f_status_fork_s = macro_f_string_static_t_initialize(F_status_fork_s, 0, F_status_fork_s_length);
    const f_string_static_t f_status_fork_not_s = macro_f_string_static_t_initialize(F_status_fork_not_s, 0, F_status_fork_not_s_length);
    const f_string_static_t f_status_format_s = macro_f_string_static_t_initialize(F_status_format_s, 0, F_status_format_s_length);
    const f_string_static_t f_status_format_not_s = macro_f_string_static_t_initialize(F_status_format_not_s, 0, F_status_format_not_s_length);
    const f_string_static_t f_status_found_s = macro_f_string_static_t_initialize(F_status_found_s, 0, F_status_found_s_length);
    const f_string_static_t f_status_found_not_s = macro_f_string_static_t_initialize(F_status_found_not_s, 0, F_status_found_not_s_length);
    const f_string_static_t f_status_full_s = macro_f_string_static_t_initialize(F_status_full_s, 0, F_status_full_s_length);
    const f_string_static_t f_status_full_not_s = macro_f_string_static_t_initialize(F_status_full_not_s, 0, F_status_full_not_s_length);
    const f_string_static_t f_status_group_s = macro_f_string_static_t_initialize(F_status_group_s, 0, F_status_group_s_length);
    const f_string_static_t f_status_group_not_s = macro_f_string_static_t_initialize(F_status_group_not_s, 0, F_status_group_not_s_length);
    const f_string_static_t f_status_halt_s = macro_f_string_static_t_initialize(F_status_halt_s, 0, F_status_halt_s_length);
    const f_string_static_t f_status_halt_not_s = macro_f_string_static_t_initialize(F_status_halt_not_s, 0, F_status_halt_not_s_length);
    const f_string_static_t f_status_header_s = macro_f_string_static_t_initialize(F_status_header_s, 0, F_status_header_s_length);
    const f_string_static_t f_status_header_not_s = macro_f_string_static_t_initialize(F_status_header_not_s, 0, F_status_header_not_s_length);
    const f_string_static_t f_status_help_s = macro_f_string_static_t_initialize(F_status_help_s, 0, F_status_help_s_length);
    const f_string_static_t f_status_help_not_s = macro_f_string_static_t_initialize(F_status_help_not_s, 0, F_status_help_not_s_length);
    const f_string_static_t f_status_ignore_s = macro_f_string_static_t_initialize(F_status_ignore_s, 0, F_status_ignore_s_length);
    const f_string_static_t f_status_ignore_not_s = macro_f_string_static_t_initialize(F_status_ignore_not_s, 0, F_status_ignore_not_s_length);
    const f_string_static_t f_status_implemented_s = macro_f_string_static_t_initialize(F_status_implemented_s, 0, F_status_implemented_s_length);
    const f_string_static_t f_status_implemented_not_s = macro_f_string_static_t_initialize(F_status_implemented_not_s, 0, F_status_implemented_not_s_length);
    const f_string_static_t f_status_input_s = macro_f_string_static_t_initialize(F_status_input_s, 0, F_status_input_s_length);
    const f_string_static_t f_status_input_not_s = macro_f_string_static_t_initialize(F_status_input_not_s, 0, F_status_input_not_s_length);
    const f_string_static_t f_status_input_output_s = macro_f_string_static_t_initialize(F_status_input_output_s, 0, F_status_input_output_s_length);
    const f_string_static_t f_status_interrupt_s = macro_f_string_static_t_initialize(F_status_interrupt_s, 0, F_status_interrupt_s_length);
    const f_string_static_t f_status_interrupt_not_s = macro_f_string_static_t_initialize(F_status_interrupt_not_s, 0, F_status_interrupt_not_s_length);
    const f_string_static_t f_status_keep_s = macro_f_string_static_t_initialize(F_status_keep_s, 0, F_status_keep_s_length);
    const f_string_static_t f_status_keep_not_s = macro_f_string_static_t_initialize(F_status_keep_not_s, 0, F_status_keep_not_s_length);
    const f_string_static_t f_status_known_s = macro_f_string_static_t_initialize(F_status_known_s, 0, F_status_known_s_length);
    const f_string_static_t f_status_known_not_s = macro_f_string_static_t_initialize(F_status_known_not_s, 0, F_status_known_not_s_length);
    const f_string_static_t f_status_last_s = macro_f_string_static_t_initialize(F_status_last_s, 0, F_status_last_s_length);
    const f_string_static_t f_status_last_not_s = macro_f_string_static_t_initialize(F_status_last_not_s, 0, F_status_last_not_s_length);
    const f_string_static_t f_status_limit_s = macro_f_string_static_t_initialize(F_status_limit_s, 0, F_status_limit_s_length);
    const f_string_static_t f_status_limit_not_s = macro_f_string_static_t_initialize(F_status_limit_not_s, 0, F_status_limit_not_s_length);
    const f_string_static_t f_status_link_s = macro_f_string_static_t_initialize(F_status_link_s, 0, F_status_link_s_length);
    const f_string_static_t f_status_link_not_s = macro_f_string_static_t_initialize(F_status_link_not_s, 0, F_status_link_not_s_length);
    const f_string_static_t f_status_live_s = macro_f_string_static_t_initialize(F_status_live_s, 0, F_status_live_s_length);
    const f_string_static_t f_status_live_not_s = macro_f_string_static_t_initialize(F_status_live_not_s, 0, F_status_live_not_s_length);
    const f_string_static_t f_status_local_s = macro_f_string_static_t_initialize(F_status_local_s, 0, F_status_local_s_length);
    const f_string_static_t f_status_local_not_s = macro_f_string_static_t_initialize(F_status_local_not_s, 0, F_status_local_not_s_length);
    const f_string_static_t f_status_lock_s = macro_f_string_static_t_initialize(F_status_lock_s, 0, F_status_lock_s_length);
    const f_string_static_t f_status_lock_not_s = macro_f_string_static_t_initialize(F_status_lock_not_s, 0, F_status_lock_not_s_length);
    const f_string_static_t f_status_loop_s = macro_f_string_static_t_initialize(F_status_loop_s, 0, F_status_loop_s_length);
    const f_string_static_t f_status_loop_not_s = macro_f_string_static_t_initialize(F_status_loop_not_s, 0, F_status_loop_not_s_length);
    const f_string_static_t f_status_maybe_s = macro_f_string_static_t_initialize(F_status_maybe_s, 0, F_status_maybe_s_length);
    const f_string_static_t f_status_maybe_not_s = macro_f_string_static_t_initialize(F_status_maybe_not_s, 0, F_status_maybe_not_s_length);
    const f_string_static_t f_status_memory_s = macro_f_string_static_t_initialize(F_status_memory_s, 0, F_status_memory_s_length);
    const f_string_static_t f_status_memory_not_s = macro_f_string_static_t_initialize(F_status_memory_not_s, 0, F_status_memory_not_s_length);
    const f_string_static_t f_status_message_s = macro_f_string_static_t_initialize(F_status_message_s, 0, F_status_message_s_length);
    const f_string_static_t f_status_message_not_s = macro_f_string_static_t_initialize(F_status_message_not_s, 0, F_status_message_not_s_length);
    const f_string_static_t f_status_minor_s = macro_f_string_static_t_initialize(F_status_minor_s, 0, F_status_minor_s_length);
    const f_string_static_t f_status_minor_not_s = macro_f_string_static_t_initialize(F_status_minor_not_s, 0, F_status_minor_not_s_length);
    const f_string_static_t f_status_moderate_s = macro_f_string_static_t_initialize(F_status_moderate_s, 0, F_status_moderate_s_length);
    const f_string_static_t f_status_moderate_not_s = macro_f_string_static_t_initialize(F_status_moderate_not_s, 0, F_status_moderate_not_s_length);
    const f_string_static_t f_status_mount_s = macro_f_string_static_t_initialize(F_status_mount_s, 0, F_status_mount_s_length);
    const f_string_static_t f_status_mount_not_s = macro_f_string_static_t_initialize(F_status_mount_not_s, 0, F_status_mount_not_s_length);
    const f_string_static_t f_status_name_s = macro_f_string_static_t_initialize(F_status_name_s, 0, F_status_name_s_length);
    const f_string_static_t f_status_name_not_s = macro_f_string_static_t_initialize(F_status_name_not_s, 0, F_status_name_not_s_length);
    const f_string_static_t f_status_need_s = macro_f_string_static_t_initialize(F_status_need_s, 0, F_status_need_s_length);
    const f_string_static_t f_status_need_not_s = macro_f_string_static_t_initialize(F_status_need_not_s, 0, F_status_need_not_s_length);
    const f_string_static_t f_status_next_s = macro_f_string_static_t_initialize(F_status_next_s, 0, F_status_next_s_length);
    const f_string_static_t f_status_next_not_s = macro_f_string_static_t_initialize(F_status_next_not_s, 0, F_status_next_not_s_length);
    const f_string_static_t f_status_nice_s = macro_f_string_static_t_initialize(F_status_nice_s, 0, F_status_nice_s_length);
    const f_string_static_t f_status_nice_not_s = macro_f_string_static_t_initialize(F_status_nice_not_s, 0, F_status_nice_not_s_length);
    const f_string_static_t f_status_no_s = macro_f_string_static_t_initialize(F_status_no_s, 0, F_status_no_s_length);
    const f_string_static_t f_status_no_not_s = macro_f_string_static_t_initialize(F_status_no_not_s, 0, F_status_no_not_s_length);
    const f_string_static_t f_status_object_s = macro_f_string_static_t_initialize(F_status_object_s, 0, F_status_object_s_length);
    const f_string_static_t f_status_object_not_s = macro_f_string_static_t_initialize(F_status_object_not_s, 0, F_status_object_not_s_length);
    const f_string_static_t f_status_okay_s = macro_f_string_static_t_initialize(F_status_okay_s, 0, F_status_okay_s_length);
    const f_string_static_t f_status_okay_not_s = macro_f_string_static_t_initialize(F_status_okay_not_s, 0, F_status_okay_not_s_length);
    const f_string_static_t f_status_once_s = macro_f_string_static_t_initialize(F_status_once_s, 0, F_status_once_s_length);
    const f_string_static_t f_status_once_not_s = macro_f_string_static_t_initialize(F_status_once_not_s, 0, F_status_once_not_s_length);
    const f_string_static_t f_status_option_s = macro_f_string_static_t_initialize(F_status_option_s, 0, F_status_option_s_length);
    const f_string_static_t f_status_option_not_s = macro_f_string_static_t_initialize(F_status_option_not_s, 0, F_status_option_not_s_length);
    const f_string_static_t f_status_output_s = macro_f_string_static_t_initialize(F_status_output_s, 0, F_status_output_s_length);
    const f_string_static_t f_status_output_not_s = macro_f_string_static_t_initialize(F_status_output_not_s, 0, F_status_output_not_s_length);
    const f_string_static_t f_status_packet_s = macro_f_string_static_t_initialize(F_status_packet_s, 0, F_status_packet_s_length);
    const f_string_static_t f_status_packet_not_s = macro_f_string_static_t_initialize(F_status_packet_not_s, 0, F_status_packet_not_s_length);
    const f_string_static_t f_status_parameter_s = macro_f_string_static_t_initialize(F_status_parameter_s, 0, F_status_parameter_s_length);
    const f_string_static_t f_status_parameter_not_s = macro_f_string_static_t_initialize(F_status_parameter_not_s, 0, F_status_parameter_not_s_length);
    const f_string_static_t f_status_parent_s = macro_f_string_static_t_initialize(F_status_parent_s, 0, F_status_parent_s_length);
    const f_string_static_t f_status_parent_not_s = macro_f_string_static_t_initialize(F_status_parent_not_s, 0, F_status_parent_not_s_length);
    const f_string_static_t f_status_payload_s = macro_f_string_static_t_initialize(F_status_payload_s, 0, F_status_payload_s_length);
    const f_string_static_t f_status_payload_not_s = macro_f_string_static_t_initialize(F_status_payload_not_s, 0, F_status_payload_not_s_length);
    const f_string_static_t f_status_pipe_s = macro_f_string_static_t_initialize(F_status_pipe_s, 0, F_status_pipe_s_length);
    const f_string_static_t f_status_pipe_not_s = macro_f_string_static_t_initialize(F_status_pipe_not_s, 0, F_status_pipe_not_s_length);
    const f_string_static_t f_status_port_s = macro_f_string_static_t_initialize(F_status_port_s, 0, F_status_port_s_length);
    const f_string_static_t f_status_port_not_s = macro_f_string_static_t_initialize(F_status_port_not_s, 0, F_status_port_not_s_length);
    const f_string_static_t f_status_previous_s = macro_f_string_static_t_initialize(F_status_previous_s, 0, F_status_previous_s_length);
    const f_string_static_t f_status_previous_not_s = macro_f_string_static_t_initialize(F_status_previous_not_s, 0, F_status_previous_not_s_length);
    const f_string_static_t f_status_processor_s = macro_f_string_static_t_initialize(F_status_processor_s, 0, F_status_processor_s_length);
    const f_string_static_t f_status_processor_not_s = macro_f_string_static_t_initialize(F_status_processor_not_s, 0, F_status_processor_not_s_length);
    const f_string_static_t f_status_progress_s = macro_f_string_static_t_initialize(F_status_progress_s, 0, F_status_progress_s_length);
    const f_string_static_t f_status_progress_not_s = macro_f_string_static_t_initialize(F_status_progress_not_s, 0, F_status_progress_not_s_length);
    const f_string_static_t f_status_prohibited_s = macro_f_string_static_t_initialize(F_status_prohibited_s, 0, F_status_prohibited_s_length);
    const f_string_static_t f_status_prohibited_not_s = macro_f_string_static_t_initialize(F_status_prohibited_not_s, 0, F_status_prohibited_not_s_length);
    const f_string_static_t f_status_property_s = macro_f_string_static_t_initialize(F_status_property_s, 0, F_status_property_s_length);
    const f_string_static_t f_status_property_not_s = macro_f_string_static_t_initialize(F_status_property_not_s, 0, F_status_property_not_s_length);
    const f_string_static_t f_status_protocol_s = macro_f_string_static_t_initialize(F_status_protocol_s, 0, F_status_protocol_s_length);
    const f_string_static_t f_status_protocol_not_s = macro_f_string_static_t_initialize(F_status_protocol_not_s, 0, F_status_protocol_not_s_length);
    const f_string_static_t f_status_range_s = macro_f_string_static_t_initialize(F_status_range_s, 0, F_status_range_s_length);
    const f_string_static_t f_status_range_not_s = macro_f_string_static_t_initialize(F_status_range_not_s, 0, F_status_range_not_s_length);
    const f_string_static_t f_status_read_s = macro_f_string_static_t_initialize(F_status_read_s, 0, F_status_read_s_length);
    const f_string_static_t f_status_read_not_s = macro_f_string_static_t_initialize(F_status_read_not_s, 0, F_status_read_not_s_length);
    const f_string_static_t f_status_read_only_s = macro_f_string_static_t_initialize(F_status_read_only_s, 0, F_status_read_only_s_length);
    const f_string_static_t f_status_ready_s = macro_f_string_static_t_initialize(F_status_ready_s, 0, F_status_ready_s_length);
    const f_string_static_t f_status_ready_not_s = macro_f_string_static_t_initialize(F_status_ready_not_s, 0, F_status_ready_not_s_length);
    const f_string_static_t f_status_receive_s = macro_f_string_static_t_initialize(F_status_receive_s, 0, F_status_receive_s_length);
    const f_string_static_t f_status_receive_not_s = macro_f_string_static_t_initialize(F_status_receive_not_s, 0, F_status_receive_not_s_length);
    const f_string_static_t f_status_recover_s = macro_f_string_static_t_initialize(F_status_recover_s, 0, F_status_recover_s_length);
    const f_string_static_t f_status_recover_not_s = macro_f_string_static_t_initialize(F_status_recover_not_s, 0, F_status_recover_not_s_length);
    const f_string_static_t f_status_recurse_s = macro_f_string_static_t_initialize(F_status_recurse_s, 0, F_status_recurse_s_length);
    const f_string_static_t f_status_recurse_not_s = macro_f_string_static_t_initialize(F_status_recurse_not_s, 0, F_status_recurse_not_s_length);
    const f_string_static_t f_status_relative_s = macro_f_string_static_t_initialize(F_status_relative_s, 0, F_status_relative_s_length);
    const f_string_static_t f_status_relative_not_s = macro_f_string_static_t_initialize(F_status_relative_not_s, 0, F_status_relative_not_s_length);
    const f_string_static_t f_status_remote_s = macro_f_string_static_t_initialize(F_status_remote_s, 0, F_status_remote_s_length);
    const f_string_static_t f_status_remote_not_s = macro_f_string_static_t_initialize(F_status_remote_not_s, 0, F_status_remote_not_s_length);
    const f_string_static_t f_status_repeat_s = macro_f_string_static_t_initialize(F_status_repeat_s, 0, F_status_repeat_s_length);
    const f_string_static_t f_status_repeat_not_s = macro_f_string_static_t_initialize(F_status_repeat_not_s, 0, F_status_repeat_not_s_length);
    const f_string_static_t f_status_require_s = macro_f_string_static_t_initialize(F_status_require_s, 0, F_status_require_s_length);
    const f_string_static_t f_status_require_not_s = macro_f_string_static_t_initialize(F_status_require_not_s, 0, F_status_require_not_s_length);
    const f_string_static_t f_status_resource_s = macro_f_string_static_t_initialize(F_status_resource_s, 0, F_status_resource_s_length);
    const f_string_static_t f_status_resource_not_s = macro_f_string_static_t_initialize(F_status_resource_not_s, 0, F_status_resource_not_s_length);
    const f_string_static_t f_status_restart_s = macro_f_string_static_t_initialize(F_status_restart_s, 0, F_status_restart_s_length);
    const f_string_static_t f_status_restart_not_s = macro_f_string_static_t_initialize(F_status_restart_not_s, 0, F_status_restart_not_s_length);
    const f_string_static_t f_status_restore_s = macro_f_string_static_t_initialize(F_status_restore_s, 0, F_status_restore_s_length);
    const f_string_static_t f_status_restore_not_s = macro_f_string_static_t_initialize(F_status_restore_not_s, 0, F_status_restore_not_s_length);
    const f_string_static_t f_status_revert_s = macro_f_string_static_t_initialize(F_status_revert_s, 0, F_status_revert_s_length);
    const f_string_static_t f_status_revert_not_s = macro_f_string_static_t_initialize(F_status_revert_not_s, 0, F_status_revert_not_s_length);
    const f_string_static_t f_status_schedule_s = macro_f_string_static_t_initialize(F_status_schedule_s, 0, F_status_schedule_s_length);
    const f_string_static_t f_status_schedule_not_s = macro_f_string_static_t_initialize(F_status_schedule_not_s, 0, F_status_schedule_not_s_length);
    const f_string_static_t f_status_search_s = macro_f_string_static_t_initialize(F_status_search_s, 0, F_status_search_s_length);
    const f_string_static_t f_status_search_not_s = macro_f_string_static_t_initialize(F_status_search_not_s, 0, F_status_search_not_s_length);
    const f_string_static_t f_status_send_s = macro_f_string_static_t_initialize(F_status_send_s, 0, F_status_send_s_length);
    const f_string_static_t f_status_send_not_s = macro_f_string_static_t_initialize(F_status_send_not_s, 0, F_status_send_not_s_length);
    const f_string_static_t f_status_size_s = macro_f_string_static_t_initialize(F_status_size_s, 0, F_status_size_s_length);
    const f_string_static_t f_status_size_not_s = macro_f_string_static_t_initialize(F_status_size_not_s, 0, F_status_size_not_s_length);
    const f_string_static_t f_status_signal_s = macro_f_string_static_t_initialize(F_status_signal_s, 0, F_status_signal_s_length);
    const f_string_static_t f_status_signal_not_s = macro_f_string_static_t_initialize(F_status_signal_not_s, 0, F_status_signal_not_s_length);
    const f_string_static_t f_status_skip_s = macro_f_string_static_t_initialize(F_status_skip_s, 0, F_status_skip_s_length);
    const f_string_static_t f_status_skip_not_s = macro_f_string_static_t_initialize(F_status_skip_not_s, 0, F_status_skip_not_s_length);
    const f_string_static_t f_status_space_s = macro_f_string_static_t_initialize(F_status_space_s, 0, F_status_space_s_length);
    const f_string_static_t f_status_space_not_s = macro_f_string_static_t_initialize(F_status_space_not_s, 0, F_status_space_not_s_length);
    const f_string_static_t f_status_start_s = macro_f_string_static_t_initialize(F_status_start_s, 0, F_status_start_s_length);
    const f_string_static_t f_status_start_not_s = macro_f_string_static_t_initialize(F_status_start_not_s, 0, F_status_start_not_s_length);
    const f_string_static_t f_status_status_s = macro_f_string_static_t_initialize(F_status_status_s, 0, F_status_status_s_length);
    const f_string_static_t f_status_status_not_s = macro_f_string_static_t_initialize(F_status_status_not_s, 0, F_status_status_not_s_length);
    const f_string_static_t f_status_stop_s = macro_f_string_static_t_initialize(F_status_stop_s, 0, F_status_stop_s_length);
    const f_string_static_t f_status_stop_not_s = macro_f_string_static_t_initialize(F_status_stop_not_s, 0, F_status_stop_not_s_length);
    const f_string_static_t f_status_store_s = macro_f_string_static_t_initialize(F_status_store_s, 0, F_status_store_s_length);
    const f_string_static_t f_status_store_not_s = macro_f_string_static_t_initialize(F_status_store_not_s, 0, F_status_store_not_s_length);
    const f_string_static_t f_status_stream_s = macro_f_string_static_t_initialize(F_status_stream_s, 0, F_status_stream_s_length);
    const f_string_static_t f_status_stream_not_s = macro_f_string_static_t_initialize(F_status_stream_not_s, 0, F_status_stream_not_s_length);
    const f_string_static_t f_status_string_s = macro_f_string_static_t_initialize(F_status_string_s, 0, F_status_string_s_length);
    const f_string_static_t f_status_string_not_s = macro_f_string_static_t_initialize(F_status_string_not_s, 0, F_status_string_not_s_length);
    const f_string_static_t f_status_string_too_large_s = macro_f_string_static_t_initialize(F_status_string_too_large_s, 0, F_status_string_too_large_s_length);
    const f_string_static_t f_status_string_too_small_s = macro_f_string_static_t_initialize(F_status_string_too_small_s, 0, F_status_string_too_small_s_length);
    const f_string_static_t f_status_syntax_s = macro_f_string_static_t_initialize(F_status_syntax_s, 0, F_status_syntax_s_length);
    const f_string_static_t f_status_syntax_not_s = macro_f_string_static_t_initialize(F_status_syntax_not_s, 0, F_status_syntax_not_s_length);
    const f_string_static_t f_status_terminate_s = macro_f_string_static_t_initialize(F_status_terminate_s, 0, F_status_terminate_s_length);
    const f_string_static_t f_status_terminate_not_s = macro_f_string_static_t_initialize(F_status_terminate_not_s, 0, F_status_terminate_not_s_length);
    const f_string_static_t f_status_thread_s = macro_f_string_static_t_initialize(F_status_thread_s, 0, F_status_thread_s_length);
    const f_string_static_t f_status_thread_not_s = macro_f_string_static_t_initialize(F_status_thread_not_s, 0, F_status_thread_not_s_length);
    const f_string_static_t f_status_time_s = macro_f_string_static_t_initialize(F_status_time_s, 0, F_status_time_s_length);
    const f_string_static_t f_status_time_not_s = macro_f_string_static_t_initialize(F_status_time_not_s, 0, F_status_time_not_s_length);
    const f_string_static_t f_status_time_out_s = macro_f_string_static_t_initialize(F_status_time_out_s, 0, F_status_time_out_s_length);
    const f_string_static_t f_status_too_large_s = macro_f_string_static_t_initialize(F_status_too_large_s, 0, F_status_too_large_s_length);
    const f_string_static_t f_status_too_small_s = macro_f_string_static_t_initialize(F_status_too_small_s, 0, F_status_too_small_s_length);
    const f_string_static_t f_status_type_s = macro_f_string_static_t_initialize(F_status_type_s, 0, F_status_type_s_length);
    const f_string_static_t f_status_type_not_s = macro_f_string_static_t_initialize(F_status_type_not_s, 0, F_status_type_not_s_length);
    const f_string_static_t f_status_success_s = macro_f_string_static_t_initialize(F_status_success_s, 0, F_status_success_s_length);
    const f_string_static_t f_status_success_not_s = macro_f_string_static_t_initialize(F_status_success_not_s, 0, F_status_success_not_s_length);
    const f_string_static_t f_status_support_s = macro_f_string_static_t_initialize(F_status_support_s, 0, F_status_support_s_length);
    const f_string_static_t f_status_support_not_s = macro_f_string_static_t_initialize(F_status_support_not_s, 0, F_status_support_not_s_length);
    const f_string_static_t f_status_user_s = macro_f_string_static_t_initialize(F_status_user_s, 0, F_status_user_s_length);
    const f_string_static_t f_status_user_not_s = macro_f_string_static_t_initialize(F_status_user_not_s, 0, F_status_user_not_s_length);
    const f_string_static_t f_status_utf_s = macro_f_string_static_t_initialize(F_status_utf_s, 0, F_status_utf_s_length);
    const f_string_static_t f_status_utf_fragment_s = macro_f_string_static_t_initialize(F_status_utf_fragment_s, 0, F_status_utf_fragment_s_length);
    const f_string_static_t f_status_utf_fragment_not_s = macro_f_string_static_t_initialize(F_status_utf_fragment_not_s, 0, F_status_utf_fragment_not_s_length);
    const f_string_static_t f_status_utf_not_s = macro_f_string_static_t_initialize(F_status_utf_not_s, 0, F_status_utf_not_s_length);
    const f_string_static_t f_status_valid_s = macro_f_string_static_t_initialize(F_status_valid_s, 0, F_status_valid_s_length);
    const f_string_static_t f_status_valid_not_s = macro_f_string_static_t_initialize(F_status_valid_not_s, 0, F_status_valid_not_s_length);
    const f_string_static_t f_status_value_s = macro_f_string_static_t_initialize(F_status_value_s, 0, F_status_value_s_length);
    const f_string_static_t f_status_value_not_s = macro_f_string_static_t_initialize(F_status_value_not_s, 0, F_status_value_not_s_length);
    const f_string_static_t f_status_wait_s = macro_f_string_static_t_initialize(F_status_wait_s, 0, F_status_wait_s_length);
    const f_string_static_t f_status_wait_not_s = macro_f_string_static_t_initialize(F_status_wait_not_s, 0, F_status_wait_not_s_length);
    const f_string_static_t f_status_want_s = macro_f_string_static_t_initialize(F_status_want_s, 0, F_status_want_s_length);
    const f_string_static_t f_status_want_not_s = macro_f_string_static_t_initialize(F_status_want_not_s, 0, F_status_want_not_s_length);
    const f_string_static_t f_status_wish_s = macro_f_string_static_t_initialize(F_status_wish_s, 0, F_status_wish_s_length);
    const f_string_static_t f_status_wish_not_s = macro_f_string_static_t_initialize(F_status_wish_not_s, 0, F_status_wish_not_s_length);
    const f_string_static_t f_status_world_s = macro_f_string_static_t_initialize(F_status_world_s, 0, F_status_world_s_length);
    const f_string_static_t f_status_world_not_s = macro_f_string_static_t_initialize(F_status_world_not_s, 0, F_status_world_not_s_length);
    const f_string_static_t f_status_write_s = macro_f_string_static_t_initialize(F_status_write_s, 0, F_status_write_s_length);
    const f_string_static_t f_status_write_not_s = macro_f_string_static_t_initialize(F_status_write_not_s, 0, F_status_write_not_s_length);
    const f_string_static_t f_status_write_only_s = macro_f_string_static_t_initialize(F_status_write_only_s, 0, F_status_write_only_s_length);
    const f_string_static_t f_status_yes_s = macro_f_string_static_t_initialize(F_status_yes_s, 0, F_status_yes_s_length);
    const f_string_static_t f_status_yes_not_s = macro_f_string_static_t_initialize(F_status_yes_not_s, 0, F_status_yes_not_s_length);
  #endif // _di_f_status_basic_

  #ifndef _di_f_status_return_
    const f_string_static_t f_status_debug_s = macro_f_string_static_t_initialize(F_status_debug_s, 0, F_status_debug_s_length);
    const f_string_static_t f_status_debug_not_s = macro_f_string_static_t_initialize(F_status_debug_not_s, 0, F_status_debug_not_s_length);
    const f_string_static_t f_status_error_s = macro_f_string_static_t_initialize(F_status_error_s, 0, F_status_error_s_length);
    const f_string_static_t f_status_error_not_s = macro_f_string_static_t_initialize(F_status_error_not_s, 0, F_status_error_not_s_length);
    const f_string_static_t f_status_fine_s = macro_f_string_static_t_initialize(F_status_fine_s, 0, F_status_fine_s_length);
    const f_string_static_t f_status_fine_not_s = macro_f_string_static_t_initialize(F_status_fine_not_s, 0, F_status_fine_not_s_length);
    const f_string_static_t f_status_warning_s = macro_f_string_static_t_initialize(F_status_warning_s, 0, F_status_warning_s_length);
    const f_string_static_t f_status_warning_not_s = macro_f_string_static_t_initialize(F_status_warning_not_s, 0, F_status_warning_not_s_length);
  #endif // _di_f_status_return_

  #ifndef _di_f_status_array_
    const f_string_static_t f_status_array_s = macro_f_string_static_t_initialize(F_status_array_s, 0, F_status_array_s_length);
    const f_string_static_t f_status_array_not_s = macro_f_string_static_t_initialize(F_status_array_not_s, 0, F_status_array_not_s_length);
    const f_string_static_t f_status_array_too_large_s = macro_f_string_static_t_initialize(F_status_array_too_large_s, 0, F_status_array_too_large_s_length);
    const f_string_static_t f_status_array_too_small_s = macro_f_string_static_t_initialize(F_status_array_too_small_s, 0, F_status_array_too_small_s_length);
  #endif // _di_f_status_array_

  #ifndef _di_f_status_available_
    const f_string_static_t f_status_available_s = macro_f_string_static_t_initialize(F_status_available_s, 0, F_status_available_s_length);
    const f_string_static_t f_status_available_not_s = macro_f_string_static_t_initialize(F_status_available_not_s, 0, F_status_available_not_s_length);
    const f_string_static_t f_status_available_not_address_s = macro_f_string_static_t_initialize(F_status_available_not_address_s, 0, F_status_available_not_address_s_length);
    const f_string_static_t f_status_available_not_buffer_s = macro_f_string_static_t_initialize(F_status_available_not_buffer_s, 0, F_status_available_not_buffer_s_length);
    const f_string_static_t f_status_available_not_device_s = macro_f_string_static_t_initialize(F_status_available_not_device_s, 0, F_status_available_not_device_s_length);
    const f_string_static_t f_status_available_not_pipe_s = macro_f_string_static_t_initialize(F_status_available_not_pipe_s, 0, F_status_available_not_pipe_s_length);
    const f_string_static_t f_status_available_not_port_s = macro_f_string_static_t_initialize(F_status_available_not_port_s, 0, F_status_available_not_port_s_length);
    const f_string_static_t f_status_available_not_process_s = macro_f_string_static_t_initialize(F_status_available_not_process_s, 0, F_status_available_not_process_s_length);
    const f_string_static_t f_status_available_not_socket_s = macro_f_string_static_t_initialize(F_status_available_not_socket_s, 0, F_status_available_not_socket_s_length);
  #endif // _di_f_status_available_

  #ifndef _di_f_status_busy_
    const f_string_static_t f_status_busy_s = macro_f_string_static_t_initialize(F_status_busy_s, 0, F_status_busy_s_length);
    const f_string_static_t f_status_busy_address_s = macro_f_string_static_t_initialize(F_status_busy_address_s, 0, F_status_busy_address_s_length);
    const f_string_static_t f_status_busy_buffer_s = macro_f_string_static_t_initialize(F_status_busy_buffer_s, 0, F_status_busy_buffer_s_length);
    const f_string_static_t f_status_busy_device_s = macro_f_string_static_t_initialize(F_status_busy_device_s, 0, F_status_busy_device_s_length);
    const f_string_static_t f_status_busy_not_s = macro_f_string_static_t_initialize(F_status_busy_not_s, 0, F_status_busy_not_s_length);
    const f_string_static_t f_status_busy_pipe_s = macro_f_string_static_t_initialize(F_status_busy_pipe_s, 0, F_status_busy_pipe_s_length);
    const f_string_static_t f_status_busy_port_s = macro_f_string_static_t_initialize(F_status_busy_port_s, 0, F_status_busy_port_s_length);
    const f_string_static_t f_status_busy_process_s = macro_f_string_static_t_initialize(F_status_busy_process_s, 0, F_status_busy_process_s_length);
    const f_string_static_t f_status_busy_socket_s = macro_f_string_static_t_initialize(F_status_busy_socket_s, 0, F_status_busy_socket_s_length);
  #endif // _di_f_status_busy_

  #ifndef _di_f_status_network_
    const f_string_static_t f_status_network_s = macro_f_string_static_t_initialize(F_status_network_s, 0, F_status_network_s_length);
    const f_string_static_t f_status_network_busy_s = macro_f_string_static_t_initialize(F_status_network_busy_s, 0, F_status_network_busy_s_length);
    const f_string_static_t f_status_network_busy_not_s = macro_f_string_static_t_initialize(F_status_network_busy_not_s, 0, F_status_network_busy_not_s_length);
    const f_string_static_t f_status_network_client_s = macro_f_string_static_t_initialize(F_status_network_client_s, 0, F_status_network_client_s_length);
    const f_string_static_t f_status_network_client_not_s = macro_f_string_static_t_initialize(F_status_network_client_not_s, 0, F_status_network_client_not_s_length);
    const f_string_static_t f_status_network_device_s = macro_f_string_static_t_initialize(F_status_network_device_s, 0, F_status_network_device_s_length);
    const f_string_static_t f_status_network_device_not_s = macro_f_string_static_t_initialize(F_status_network_device_not_s, 0, F_status_network_device_not_s_length);
    const f_string_static_t f_status_network_found_s = macro_f_string_static_t_initialize(F_status_network_found_s, 0, F_status_network_found_s_length);
    const f_string_static_t f_status_network_found_not_s = macro_f_string_static_t_initialize(F_status_network_found_not_s, 0, F_status_network_found_not_s_length);
    const f_string_static_t f_status_network_lost_s = macro_f_string_static_t_initialize(F_status_network_lost_s, 0, F_status_network_lost_s_length);
    const f_string_static_t f_status_network_lost_not_s = macro_f_string_static_t_initialize(F_status_network_lost_not_s, 0, F_status_network_lost_not_s_length);
    const f_string_static_t f_status_network_not_s = macro_f_string_static_t_initialize(F_status_network_not_s, 0, F_status_network_not_s_length);
    const f_string_static_t f_status_network_reach_s = macro_f_string_static_t_initialize(F_status_network_reach_s, 0, F_status_network_reach_s_length);
    const f_string_static_t f_status_network_reach_client_s = macro_f_string_static_t_initialize(F_status_network_reach_client_s, 0, F_status_network_reach_client_s_length);
    const f_string_static_t f_status_network_reach_client_not_s = macro_f_string_static_t_initialize(F_status_network_reach_client_not_s, 0, F_status_network_reach_client_not_s_length);
    const f_string_static_t f_status_network_reach_not_s = macro_f_string_static_t_initialize(F_status_network_reach_not_s, 0, F_status_network_reach_not_s_length);
    const f_string_static_t f_status_network_reach_server_s = macro_f_string_static_t_initialize(F_status_network_reach_server_s, 0, F_status_network_reach_server_s_length);
    const f_string_static_t f_status_network_reach_server_not_s = macro_f_string_static_t_initialize(F_status_network_reach_server_not_s, 0, F_status_network_reach_server_not_s_length);
    const f_string_static_t f_status_network_server_s = macro_f_string_static_t_initialize(F_status_network_server_s, 0, F_status_network_server_s_length);
    const f_string_static_t f_status_network_server_not_s = macro_f_string_static_t_initialize(F_status_network_server_not_s, 0, F_status_network_server_not_s_length);
    const f_string_static_t f_status_network_time_s = macro_f_string_static_t_initialize(F_status_network_time_s, 0, F_status_network_time_s_length);
    const f_string_static_t f_status_network_time_not_s = macro_f_string_static_t_initialize(F_status_network_time_not_s, 0, F_status_network_time_not_s_length);
  #endif // _di_f_status_network_

  #ifndef _di_f_status_number_
    const f_string_static_t f_status_number_s = macro_f_string_static_t_initialize(F_status_number_s, 0, F_status_number_s_length);
    const f_string_static_t f_status_number_decimal_s = macro_f_string_static_t_initialize(F_status_number_decimal_s, 0, F_status_number_decimal_s_length);
    const f_string_static_t f_status_number_decimal_not_s = macro_f_string_static_t_initialize(F_status_number_decimal_not_s, 0, F_status_number_decimal_not_s_length);
    const f_string_static_t f_status_number_divide_by_zero_s = macro_f_string_static_t_initialize(F_status_number_divide_by_zero_s, 0, F_status_number_divide_by_zero_s_length);
    const f_string_static_t f_status_number_negative_s = macro_f_string_static_t_initialize(F_status_number_negative_s, 0, F_status_number_negative_s_length);
    const f_string_static_t f_status_number_negative_not_s = macro_f_string_static_t_initialize(F_status_number_negative_not_s, 0, F_status_number_negative_not_s_length);
    const f_string_static_t f_status_number_not_s = macro_f_string_static_t_initialize(F_status_number_not_s, 0, F_status_number_not_s_length);
    const f_string_static_t f_status_number_overflow_s = macro_f_string_static_t_initialize(F_status_number_overflow_s, 0, F_status_number_overflow_s_length);
    const f_string_static_t f_status_number_positive_s = macro_f_string_static_t_initialize(F_status_number_positive_s, 0, F_status_number_positive_s_length);
    const f_string_static_t f_status_number_positive_not_s = macro_f_string_static_t_initialize(F_status_number_positive_not_s, 0, F_status_number_positive_not_s_length);
    const f_string_static_t f_status_number_too_large_s = macro_f_string_static_t_initialize(F_status_number_too_large_s, 0, F_status_number_too_large_s_length);
    const f_string_static_t f_status_number_too_small_s = macro_f_string_static_t_initialize(F_status_number_too_small_s, 0, F_status_number_too_small_s_length);
    const f_string_static_t f_status_number_underflow_s = macro_f_string_static_t_initialize(F_status_number_underflow_s, 0, F_status_number_underflow_s_length);
    const f_string_static_t f_status_number_whole_s = macro_f_string_static_t_initialize(F_status_number_whole_s, 0, F_status_number_whole_s_length);
    const f_string_static_t f_status_number_whole_not_s = macro_f_string_static_t_initialize(F_status_number_whole_not_s, 0, F_status_number_whole_not_s_length);
    const f_string_static_t f_status_number_zero_s = macro_f_string_static_t_initialize(F_status_number_zero_s, 0, F_status_number_zero_s_length);
    const f_string_static_t f_status_number_zero_not_s = macro_f_string_static_t_initialize(F_status_number_zero_not_s, 0, F_status_number_zero_not_s_length);
  #endif // _di_f_status_number_

  #ifndef _di_f_status_buffer_
    const f_string_static_t f_status_buffer_s = macro_f_string_static_t_initialize(F_status_buffer_s, 0, F_status_buffer_s_length);
    const f_string_static_t f_status_buffer_not_s = macro_f_string_static_t_initialize(F_status_buffer_not_s, 0, F_status_buffer_not_s_length);
    const f_string_static_t f_status_buffer_overflow_s = macro_f_string_static_t_initialize(F_status_buffer_overflow_s, 0, F_status_buffer_overflow_s_length);
    const f_string_static_t f_status_buffer_too_large_s = macro_f_string_static_t_initialize(F_status_buffer_too_large_s, 0, F_status_buffer_too_large_s_length);
    const f_string_static_t f_status_buffer_too_small_s = macro_f_string_static_t_initialize(F_status_buffer_too_small_s, 0, F_status_buffer_too_small_s_length);
    const f_string_static_t f_status_buffer_underflow_s = macro_f_string_static_t_initialize(F_status_buffer_underflow_s, 0, F_status_buffer_underflow_s_length);
    const f_string_static_t f_status_complete_not_utf_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_s, 0, F_status_complete_not_utf_s_length);
    const f_string_static_t f_status_complete_not_utf_block_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_block_s, 0, F_status_complete_not_utf_block_s_length);
    const f_string_static_t f_status_complete_not_utf_eoa_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_eoa_s, 0, F_status_complete_not_utf_eoa_s_length);
    const f_string_static_t f_status_complete_not_utf_eof_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_eof_s, 0, F_status_complete_not_utf_eof_s_length);
    const f_string_static_t f_status_complete_not_utf_eol_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_eol_s, 0, F_status_complete_not_utf_eol_s_length);
    const f_string_static_t f_status_complete_not_utf_eos_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_eos_s, 0, F_status_complete_not_utf_eos_s_length);
    const f_string_static_t f_status_complete_not_utf_start_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_start_s, 0, F_status_complete_not_utf_start_s_length);
    const f_string_static_t f_status_complete_not_utf_stop_s = macro_f_string_static_t_initialize(F_status_complete_not_utf_stop_s, 0, F_status_complete_not_utf_stop_s_length);
    const f_string_static_t f_status_none_block_s = macro_f_string_static_t_initialize(F_status_none_block_s, 0, F_status_none_block_s_length);
    const f_string_static_t f_status_none_eoa_s = macro_f_string_static_t_initialize(F_status_none_eoa_s, 0, F_status_none_eoa_s_length);
    const f_string_static_t f_status_none_eof_s = macro_f_string_static_t_initialize(F_status_none_eof_s, 0, F_status_none_eof_s_length);
    const f_string_static_t f_status_none_eol_s = macro_f_string_static_t_initialize(F_status_none_eol_s, 0, F_status_none_eol_s_length);
    const f_string_static_t f_status_none_eos_s = macro_f_string_static_t_initialize(F_status_none_eos_s, 0, F_status_none_eos_s_length);
    const f_string_static_t f_status_none_not_s = macro_f_string_static_t_initialize(F_status_none_not_s, 0, F_status_none_not_s_length);
    const f_string_static_t f_status_none_start_s = macro_f_string_static_t_initialize(F_status_none_start_s, 0, F_status_none_start_s_length);
    const f_string_static_t f_status_none_stop_s = macro_f_string_static_t_initialize(F_status_none_stop_s, 0, F_status_none_stop_s_length);
    const f_string_static_t f_status_data_s = macro_f_string_static_t_initialize(F_status_data_s, 0, F_status_data_s_length);
    const f_string_static_t f_status_data_not_s = macro_f_string_static_t_initialize(F_status_data_not_s, 0, F_status_data_not_s_length);
    const f_string_static_t f_status_data_not_block_s = macro_f_string_static_t_initialize(F_status_data_not_block_s, 0, F_status_data_not_block_s_length);
    const f_string_static_t f_status_data_not_eoa_s = macro_f_string_static_t_initialize(F_status_data_not_eoa_s, 0, F_status_data_not_eoa_s_length);
    const f_string_static_t f_status_data_not_eof_s = macro_f_string_static_t_initialize(F_status_data_not_eof_s, 0, F_status_data_not_eof_s_length);
    const f_string_static_t f_status_data_not_eol_s = macro_f_string_static_t_initialize(F_status_data_not_eol_s, 0, F_status_data_not_eol_s_length);
    const f_string_static_t f_status_data_not_eos_s = macro_f_string_static_t_initialize(F_status_data_not_eos_s, 0, F_status_data_not_eos_s_length);
    const f_string_static_t f_status_data_not_start_s = macro_f_string_static_t_initialize(F_status_data_not_start_s, 0, F_status_data_not_start_s_length);
    const f_string_static_t f_status_data_not_stop_s = macro_f_string_static_t_initialize(F_status_data_not_stop_s, 0, F_status_data_not_stop_s_length);
  #endif // _di_f_status_buffer_

  #ifndef _di_f_status_end_
    const f_string_static_t f_status_end_s = macro_f_string_static_t_initialize(F_status_end_s, 0, F_status_end_s_length);
    const f_string_static_t f_status_end_not_s = macro_f_string_static_t_initialize(F_status_end_not_s, 0, F_status_end_not_s_length);
    const f_string_static_t f_status_end_not_block_s = macro_f_string_static_t_initialize(F_status_end_not_block_s, 0, F_status_end_not_block_s_length);
    const f_string_static_t f_status_end_not_eoa_s = macro_f_string_static_t_initialize(F_status_end_not_eoa_s, 0, F_status_end_not_eoa_s_length);
    const f_string_static_t f_status_end_not_eof_s = macro_f_string_static_t_initialize(F_status_end_not_eof_s, 0, F_status_end_not_eof_s_length);
    const f_string_static_t f_status_end_not_eol_s = macro_f_string_static_t_initialize(F_status_end_not_eol_s, 0, F_status_end_not_eol_s_length);
    const f_string_static_t f_status_end_not_eos_s = macro_f_string_static_t_initialize(F_status_end_not_eos_s, 0, F_status_end_not_eos_s_length);
    const f_string_static_t f_status_end_not_start_s = macro_f_string_static_t_initialize(F_status_end_not_start_s, 0, F_status_end_not_start_s_length);
    const f_string_static_t f_status_end_not_stop_s = macro_f_string_static_t_initialize(F_status_end_not_stop_s, 0, F_status_end_not_stop_s_length);
    const f_string_static_t f_status_end_not_group_s = macro_f_string_static_t_initialize(F_status_end_not_group_s, 0, F_status_end_not_group_s_length);
    const f_string_static_t f_status_end_not_group_block_s = macro_f_string_static_t_initialize(F_status_end_not_group_block_s, 0, F_status_end_not_group_block_s_length);
    const f_string_static_t f_status_end_not_group_eoa_s = macro_f_string_static_t_initialize(F_status_end_not_group_eoa_s, 0, F_status_end_not_group_eoa_s_length);
    const f_string_static_t f_status_end_not_group_eof_s = macro_f_string_static_t_initialize(F_status_end_not_group_eof_s, 0, F_status_end_not_group_eof_s_length);
    const f_string_static_t f_status_end_not_group_eol_s = macro_f_string_static_t_initialize(F_status_end_not_group_eol_s, 0, F_status_end_not_group_eol_s_length);
    const f_string_static_t f_status_end_not_group_eos_s = macro_f_string_static_t_initialize(F_status_end_not_group_eos_s, 0, F_status_end_not_group_eos_s_length);
    const f_string_static_t f_status_end_not_group_start_s = macro_f_string_static_t_initialize(F_status_end_not_group_start_s, 0, F_status_end_not_group_start_s_length);
    const f_string_static_t f_status_end_not_group_stop_s = macro_f_string_static_t_initialize(F_status_end_not_group_stop_s, 0, F_status_end_not_group_stop_s_length);
    const f_string_static_t f_status_end_not_nest_s = macro_f_string_static_t_initialize(F_status_end_not_nest_s, 0, F_status_end_not_nest_s_length);
    const f_string_static_t f_status_end_not_nest_block_s = macro_f_string_static_t_initialize(F_status_end_not_nest_block_s, 0, F_status_end_not_nest_block_s_length);
    const f_string_static_t f_status_end_not_nest_eoa_s = macro_f_string_static_t_initialize(F_status_end_not_nest_eoa_s, 0, F_status_end_not_nest_eoa_s_length);
    const f_string_static_t f_status_end_not_nest_eof_s = macro_f_string_static_t_initialize(F_status_end_not_nest_eof_s, 0, F_status_end_not_nest_eof_s_length);
    const f_string_static_t f_status_end_not_nest_eol_s = macro_f_string_static_t_initialize(F_status_end_not_nest_eol_s, 0, F_status_end_not_nest_eol_s_length);
    const f_string_static_t f_status_end_not_nest_eos_s = macro_f_string_static_t_initialize(F_status_end_not_nest_eos_s, 0, F_status_end_not_nest_eos_s_length);
    const f_string_static_t f_status_end_not_nest_start_s = macro_f_string_static_t_initialize(F_status_end_not_nest_start_s, 0, F_status_end_not_nest_start_s_length);
    const f_string_static_t f_status_end_not_nest_stop_s = macro_f_string_static_t_initialize(F_status_end_not_nest_stop_s, 0, F_status_end_not_nest_stop_s_length);
  #endif // _di_f_status_end_

  #ifndef _di_f_status_process_
    const f_string_static_t f_status_process_s = macro_f_string_static_t_initialize(F_status_process_s, 0, F_status_process_s_length);
    const f_string_static_t f_status_process_not_s = macro_f_string_static_t_initialize(F_status_process_not_s, 0, F_status_process_not_s_length);
    const f_string_static_t f_status_process_too_many_s = macro_f_string_static_t_initialize(F_status_process_too_many_s, 0, F_status_process_too_many_s_length);
  #endif // _di_f_status_process_

  #ifndef _di_f_status_file_
    const f_string_static_t f_status_file_s = macro_f_string_static_t_initialize(F_status_file_s, 0, F_status_file_s_length);
    const f_string_static_t f_status_file_close_s = macro_f_string_static_t_initialize(F_status_file_close_s, 0, F_status_file_close_s_length);
    const f_string_static_t f_status_file_closed_s = macro_f_string_static_t_initialize(F_status_file_closed_s, 0, F_status_file_closed_s_length);
    const f_string_static_t f_status_file_descriptor_s = macro_f_string_static_t_initialize(F_status_file_descriptor_s, 0, F_status_file_descriptor_s_length);
    const f_string_static_t f_status_file_descriptor_max_s = macro_f_string_static_t_initialize(F_status_file_descriptor_max_s, 0, F_status_file_descriptor_max_s_length);
    const f_string_static_t f_status_file_descriptor_not_s = macro_f_string_static_t_initialize(F_status_file_descriptor_not_s, 0, F_status_file_descriptor_not_s_length);
    const f_string_static_t f_status_file_empty_s = macro_f_string_static_t_initialize(F_status_file_empty_s, 0, F_status_file_empty_s_length);
    const f_string_static_t f_status_file_flush_s = macro_f_string_static_t_initialize(F_status_file_flush_s, 0, F_status_file_flush_s_length);
    const f_string_static_t f_status_file_found_s = macro_f_string_static_t_initialize(F_status_file_found_s, 0, F_status_file_found_s_length);
    const f_string_static_t f_status_file_found_not_s = macro_f_string_static_t_initialize(F_status_file_found_not_s, 0, F_status_file_found_not_s_length);
    const f_string_static_t f_status_file_not_s = macro_f_string_static_t_initialize(F_status_file_not_s, 0, F_status_file_not_s_length);
    const f_string_static_t f_status_file_open_s = macro_f_string_static_t_initialize(F_status_file_open_s, 0, F_status_file_open_s_length);
    const f_string_static_t f_status_file_open_max_s = macro_f_string_static_t_initialize(F_status_file_open_max_s, 0, F_status_file_open_max_s_length);
    const f_string_static_t f_status_file_opened_s = macro_f_string_static_t_initialize(F_status_file_opened_s, 0, F_status_file_opened_s_length);
    const f_string_static_t f_status_file_overflow_s = macro_f_string_static_t_initialize(F_status_file_overflow_s, 0, F_status_file_overflow_s_length);
    const f_string_static_t f_status_file_purge_s = macro_f_string_static_t_initialize(F_status_file_purge_s, 0, F_status_file_purge_s_length);
    const f_string_static_t f_status_file_read_s = macro_f_string_static_t_initialize(F_status_file_read_s, 0, F_status_file_read_s_length);
    const f_string_static_t f_status_file_reallocation_s = macro_f_string_static_t_initialize(F_status_file_reallocation_s, 0, F_status_file_reallocation_s_length);
    const f_string_static_t f_status_file_seek_s = macro_f_string_static_t_initialize(F_status_file_seek_s, 0, F_status_file_seek_s_length);
    const f_string_static_t f_status_file_stat_s = macro_f_string_static_t_initialize(F_status_file_stat_s, 0, F_status_file_stat_s_length);
    const f_string_static_t f_status_file_synchronize_s = macro_f_string_static_t_initialize(F_status_file_synchronize_s, 0, F_status_file_synchronize_s_length);
    const f_string_static_t f_status_file_type_block_s = macro_f_string_static_t_initialize(F_status_file_type_block_s, 0, F_status_file_type_block_s_length);
    const f_string_static_t f_status_file_type_character_s = macro_f_string_static_t_initialize(F_status_file_type_character_s, 0, F_status_file_type_character_s_length);
    const f_string_static_t f_status_file_type_directory_s = macro_f_string_static_t_initialize(F_status_file_type_directory_s, 0, F_status_file_type_directory_s_length);
    const f_string_static_t f_status_file_type_fifo_s = macro_f_string_static_t_initialize(F_status_file_type_fifo_s, 0, F_status_file_type_fifo_s_length);
    const f_string_static_t f_status_file_type_link_s = macro_f_string_static_t_initialize(F_status_file_type_link_s, 0, F_status_file_type_link_s_length);
    const f_string_static_t f_status_file_type_not_block_s = macro_f_string_static_t_initialize(F_status_file_type_not_block_s, 0, F_status_file_type_not_block_s_length);
    const f_string_static_t f_status_file_type_not_character_s = macro_f_string_static_t_initialize(F_status_file_type_not_character_s, 0, F_status_file_type_not_character_s_length);
    const f_string_static_t f_status_file_type_not_directory_s = macro_f_string_static_t_initialize(F_status_file_type_not_directory_s, 0, F_status_file_type_not_directory_s_length);
    const f_string_static_t f_status_file_type_not_fifo_s = macro_f_string_static_t_initialize(F_status_file_type_not_fifo_s, 0, F_status_file_type_not_fifo_s_length);
    const f_string_static_t f_status_file_type_not_link_s = macro_f_string_static_t_initialize(F_status_file_type_not_link_s, 0, F_status_file_type_not_link_s_length);
    const f_string_static_t f_status_file_type_not_pipe_s = macro_f_string_static_t_initialize(F_status_file_type_not_pipe_s, 0, F_status_file_type_not_pipe_s_length);
    const f_string_static_t f_status_file_type_not_regular_s = macro_f_string_static_t_initialize(F_status_file_type_not_regular_s, 0, F_status_file_type_not_regular_s_length);
    const f_string_static_t f_status_file_type_not_socket_s = macro_f_string_static_t_initialize(F_status_file_type_not_socket_s, 0, F_status_file_type_not_socket_s_length);
    const f_string_static_t f_status_file_type_not_unknown_s = macro_f_string_static_t_initialize(F_status_file_type_not_unknown_s, 0, F_status_file_type_not_unknown_s_length);
    const f_string_static_t f_status_file_type_pipe_s = macro_f_string_static_t_initialize(F_status_file_type_pipe_s, 0, F_status_file_type_pipe_s_length);
    const f_string_static_t f_status_file_type_regular_s = macro_f_string_static_t_initialize(F_status_file_type_regular_s, 0, F_status_file_type_regular_s_length);
    const f_string_static_t f_status_file_type_socket_s = macro_f_string_static_t_initialize(F_status_file_type_socket_s, 0, F_status_file_type_socket_s_length);
    const f_string_static_t f_status_file_type_unknown_s = macro_f_string_static_t_initialize(F_status_file_type_unknown_s, 0, F_status_file_type_unknown_s_length);
    const f_string_static_t f_status_file_underflow_s = macro_f_string_static_t_initialize(F_status_file_underflow_s, 0, F_status_file_underflow_s_length);
    const f_string_static_t f_status_file_utf_s = macro_f_string_static_t_initialize(F_status_file_utf_s, 0, F_status_file_utf_s_length);
    const f_string_static_t f_status_file_utf_not_s = macro_f_string_static_t_initialize(F_status_file_utf_not_s, 0, F_status_file_utf_not_s_length);
    const f_string_static_t f_status_file_write_s = macro_f_string_static_t_initialize(F_status_file_write_s, 0, F_status_file_write_s_length);
  #endif // _di_f_status_file_

  #ifndef _di_f_status_filesystem_
    const f_string_static_t f_status_filesystem_s = macro_f_string_static_t_initialize(F_status_filesystem_s, 0, F_status_filesystem_s_length);
    const f_string_static_t f_status_filesystem_not_s = macro_f_string_static_t_initialize(F_status_filesystem_not_s, 0, F_status_filesystem_not_s_length);
    const f_string_static_t f_status_filesystem_quota_block_s = macro_f_string_static_t_initialize(F_status_filesystem_quota_block_s, 0, F_status_filesystem_quota_block_s_length);
    const f_string_static_t f_status_filesystem_quota_reached_s = macro_f_string_static_t_initialize(F_status_filesystem_quota_reached_s, 0, F_status_filesystem_quota_reached_s_length);
  #endif // _di_f_status_filesystem_

  #ifndef _di_f_status_directory_
    const f_string_static_t f_status_directory_s = macro_f_string_static_t_initialize(F_status_directory_s, 0, F_status_directory_s_length);
    const f_string_static_t f_status_directory_close_s = macro_f_string_static_t_initialize(F_status_directory_close_s, 0, F_status_directory_close_s_length);
    const f_string_static_t f_status_directory_closed_s = macro_f_string_static_t_initialize(F_status_directory_closed_s, 0, F_status_directory_closed_s_length);
    const f_string_static_t f_status_directory_descriptor_s = macro_f_string_static_t_initialize(F_status_directory_descriptor_s, 0, F_status_directory_descriptor_s_length);
    const f_string_static_t f_status_directory_empty_s = macro_f_string_static_t_initialize(F_status_directory_empty_s, 0, F_status_directory_empty_s_length);
    const f_string_static_t f_status_directory_empty_not_s = macro_f_string_static_t_initialize(F_status_directory_empty_not_s, 0, F_status_directory_empty_not_s_length);
    const f_string_static_t f_status_directory_found_s = macro_f_string_static_t_initialize(F_status_directory_found_s, 0, F_status_directory_found_s_length);
    const f_string_static_t f_status_directory_found_not_s = macro_f_string_static_t_initialize(F_status_directory_found_not_s, 0, F_status_directory_found_not_s_length);
    const f_string_static_t f_status_directory_flush_s = macro_f_string_static_t_initialize(F_status_directory_flush_s, 0, F_status_directory_flush_s_length);
    const f_string_static_t f_status_directory_link_max_s = macro_f_string_static_t_initialize(F_status_directory_link_max_s, 0, F_status_directory_link_max_s_length);
    const f_string_static_t f_status_directory_not_s = macro_f_string_static_t_initialize(F_status_directory_not_s, 0, F_status_directory_not_s_length);
    const f_string_static_t f_status_directory_open_s = macro_f_string_static_t_initialize(F_status_directory_open_s, 0, F_status_directory_open_s_length);
    const f_string_static_t f_status_directory_purge_s = macro_f_string_static_t_initialize(F_status_directory_purge_s, 0, F_status_directory_purge_s_length);
    const f_string_static_t f_status_directory_read_s = macro_f_string_static_t_initialize(F_status_directory_read_s, 0, F_status_directory_read_s_length);
    const f_string_static_t f_status_directory_stream_s = macro_f_string_static_t_initialize(F_status_directory_stream_s, 0, F_status_directory_stream_s_length);
    const f_string_static_t f_status_directory_supported_not_s = macro_f_string_static_t_initialize(F_status_directory_supported_not_s, 0, F_status_directory_supported_not_s_length);
    const f_string_static_t f_status_directory_synchronize_s = macro_f_string_static_t_initialize(F_status_directory_synchronize_s, 0, F_status_directory_synchronize_s_length);
    const f_string_static_t f_status_directory_utf_s = macro_f_string_static_t_initialize(F_status_directory_utf_s, 0, F_status_directory_utf_s_length);
    const f_string_static_t f_status_directory_utf_not_s = macro_f_string_static_t_initialize(F_status_directory_utf_not_s, 0, F_status_directory_utf_not_s_length);
    const f_string_static_t f_status_directory_write_s = macro_f_string_static_t_initialize(F_status_directory_write_s, 0, F_status_directory_write_s_length);
  #endif // _di_f_status_directory_

  #ifndef _di_f_status_socket_
    const f_string_static_t f_status_socket_s = macro_f_string_static_t_initialize(F_status_socket_s, 0, F_status_socket_s_length);
    const f_string_static_t f_status_socket_client_s = macro_f_string_static_t_initialize(F_status_socket_client_s, 0, F_status_socket_client_s_length);
    const f_string_static_t f_status_socket_not_s = macro_f_string_static_t_initialize(F_status_socket_not_s, 0, F_status_socket_not_s_length);
    const f_string_static_t f_status_socket_receive_s = macro_f_string_static_t_initialize(F_status_socket_receive_s, 0, F_status_socket_receive_s_length);
    const f_string_static_t f_status_socket_send_s = macro_f_string_static_t_initialize(F_status_socket_send_s, 0, F_status_socket_send_s_length);
    const f_string_static_t f_status_socket_target_s = macro_f_string_static_t_initialize(F_status_socket_target_s, 0, F_status_socket_target_s_length);
  #endif // _di_f_status_socket_

  #ifndef _di_f_status_compare_
    const f_string_static_t f_status_equal_to_s = macro_f_string_static_t_initialize(F_status_equal_to_s, 0, F_status_equal_to_s_length);
    const f_string_static_t f_status_equal_to_not_s = macro_f_string_static_t_initialize(F_status_equal_to_not_s, 0, F_status_equal_to_not_s_length);
    const f_string_static_t f_status_than_greater_s = macro_f_string_static_t_initialize(F_status_than_greater_s, 0, F_status_than_greater_s_length);
    const f_string_static_t f_status_than_less_s = macro_f_string_static_t_initialize(F_status_than_less_s, 0, F_status_than_less_s_length);
  #endif // _di_f_status_compare_

  #ifndef _di_f_status_access_
    const f_string_static_t f_status_access_s = macro_f_string_static_t_initialize(F_status_access_s, 0, F_status_access_s_length);
    const f_string_static_t f_status_access_denied_s = macro_f_string_static_t_initialize(F_status_access_denied_s, 0, F_status_access_denied_s_length);
    const f_string_static_t f_status_access_denied_user_s = macro_f_string_static_t_initialize(F_status_access_denied_user_s, 0, F_status_access_denied_user_s_length);
    const f_string_static_t f_status_access_denied_group_s = macro_f_string_static_t_initialize(F_status_access_denied_group_s, 0, F_status_access_denied_group_s_length);
    const f_string_static_t f_status_access_denied_world_s = macro_f_string_static_t_initialize(F_status_access_denied_world_s, 0, F_status_access_denied_world_s_length);
    const f_string_static_t f_status_access_denied_read_s = macro_f_string_static_t_initialize(F_status_access_denied_read_s, 0, F_status_access_denied_read_s_length);
    const f_string_static_t f_status_access_denied_write_s = macro_f_string_static_t_initialize(F_status_access_denied_write_s, 0, F_status_access_denied_write_s_length);
    const f_string_static_t f_status_access_denied_execute_s = macro_f_string_static_t_initialize(F_status_access_denied_execute_s, 0, F_status_access_denied_execute_s_length);
    const f_string_static_t f_status_access_denied_super_s = macro_f_string_static_t_initialize(F_status_access_denied_super_s, 0, F_status_access_denied_super_s_length);
    const f_string_static_t f_status_access_granted_s = macro_f_string_static_t_initialize(F_status_access_granted_s, 0, F_status_access_granted_s_length);
    const f_string_static_t f_status_access_granted_user_s = macro_f_string_static_t_initialize(F_status_access_granted_user_s, 0, F_status_access_granted_user_s_length);
    const f_string_static_t f_status_access_granted_group_s = macro_f_string_static_t_initialize(F_status_access_granted_group_s, 0, F_status_access_granted_group_s_length);
    const f_string_static_t f_status_access_granted_world_s = macro_f_string_static_t_initialize(F_status_access_granted_world_s, 0, F_status_access_granted_world_s_length);
    const f_string_static_t f_status_access_granted_read_s = macro_f_string_static_t_initialize(F_status_access_granted_read_s, 0, F_status_access_granted_read_s_length);
    const f_string_static_t f_status_access_granted_write_s = macro_f_string_static_t_initialize(F_status_access_granted_write_s, 0, F_status_access_granted_write_s_length);
    const f_string_static_t f_status_access_granted_execute_s = macro_f_string_static_t_initialize(F_status_access_granted_execute_s, 0, F_status_access_granted_execute_s_length);
    const f_string_static_t f_status_access_granted_super_s = macro_f_string_static_t_initialize(F_status_access_granted_super_s, 0, F_status_access_granted_super_s_length);
    const f_string_static_t f_status_access_group_s = macro_f_string_static_t_initialize(F_status_access_group_s, 0, F_status_access_group_s_length);
    const f_string_static_t f_status_access_mode_s = macro_f_string_static_t_initialize(F_status_access_mode_s, 0, F_status_access_mode_s_length);
    const f_string_static_t f_status_access_not_s = macro_f_string_static_t_initialize(F_status_access_not_s, 0, F_status_access_not_s_length);
    const f_string_static_t f_status_access_owner_s = macro_f_string_static_t_initialize(F_status_access_owner_s, 0, F_status_access_owner_s_length);
  #endif // _di_f_status_access_

  #ifndef _di_f_status_terminal_
    const f_string_static_t f_status_terminal_s = macro_f_string_static_t_initialize(F_status_terminal_s, 0, F_status_terminal_s_length);
    const f_string_static_t f_status_terminal_access_s = macro_f_string_static_t_initialize(F_status_terminal_access_s, 0, F_status_terminal_access_s_length);
    const f_string_static_t f_status_terminal_known_s = macro_f_string_static_t_initialize(F_status_terminal_known_s, 0, F_status_terminal_known_s_length);
    const f_string_static_t f_status_terminal_known_not_s = macro_f_string_static_t_initialize(F_status_terminal_known_not_s, 0, F_status_terminal_known_not_s_length);
    const f_string_static_t f_status_terminal_not_s = macro_f_string_static_t_initialize(F_status_terminal_not_s, 0, F_status_terminal_not_s_length);
    const f_string_static_t f_status_terminal_prohibited_s = macro_f_string_static_t_initialize(F_status_terminal_prohibited_s, 0, F_status_terminal_prohibited_s_length);
    const f_string_static_t f_status_terminal_read_s = macro_f_string_static_t_initialize(F_status_terminal_read_s, 0, F_status_terminal_read_s_length);
    const f_string_static_t f_status_terminal_valid_s = macro_f_string_static_t_initialize(F_status_terminal_valid_s, 0, F_status_terminal_valid_s_length);
    const f_string_static_t f_status_terminal_valid_not_s = macro_f_string_static_t_initialize(F_status_terminal_valid_not_s, 0, F_status_terminal_valid_not_s_length);
    const f_string_static_t f_status_terminal_write_s = macro_f_string_static_t_initialize(F_status_terminal_write_s, 0, F_status_terminal_write_s_length);
  #endif // _di_f_status_terminal_

  const f_string_static_t f_status_status_code_last_s = macro_f_string_static_t_initialize(F_status_status_code_last_s, 0, F_status_status_code_last_s_length);
#endif // _di_f_status_string_

#ifndef _di_f_status_string_to_
  f_status_t f_status_string_to(const f_status_t code, f_string_static_t * const name) {
    #ifndef _di_level_0_parameter_checking_
      if (!name) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    switch (F_status_set_fine(code)) {
      #ifndef _di_f_status_boolean_
        case F_false:
          *name = f_status_false_s;

          break;

        case F_true:
          *name = f_status_true_s;

          break;
      #endif // _di_f_status_boolean_

      #ifndef _di_f_status_signal_

        // F_signal_hangup is not used because it has the same code as F_true.
        case F_signal_interrupt:
          *name = f_status_signal_interrupt_s;

          break;

        case F_signal_quit:
          *name = f_status_signal_quit_s;

          break;

        case F_signal_illegal:
          *name = f_status_signal_illegal_s;

          break;

        case F_signal_trap:
          *name = f_status_signal_trap_s;

          break;

        case F_signal_abort:
          *name = f_status_signal_abort_s;

          break;

        case F_signal_bus_error:
          *name = f_status_signal_bus_error_s;

          break;

        case F_signal_floating_point_error:
          *name = f_status_signal_floating_point_error_s;

          break;

        case F_signal_kill:
          *name = f_status_signal_kill_s;

          break;

        case F_signal_user_1:
          *name = f_status_signal_user_1_s;

          break;

        case F_signal_segmentation_fault:
          *name = f_status_signal_segmentation_fault_s;

          break;

        case F_signal_user_2:
          *name = f_status_signal_user_2_s;

          break;

        case F_signal_broken_pipe:
          *name = f_status_signal_broken_pipe_s;

          break;

        case F_signal_alarm_clock:
          *name = f_status_signal_alarm_clock_s;

          break;

        case F_signal_termination:
          *name = f_status_signal_termination_s;

          break;

        case F_signal_stack_fault:
          *name = f_status_signal_stack_fault_s;

          break;

        case F_signal_child:
          *name = f_status_signal_child_s;

          break;

        case F_signal_continue:
          *name = f_status_signal_continue_s;

          break;

        case F_signal_stop:
          *name = f_status_signal_stop_s;

          break;

        case F_signal_keyboard_stop:
          *name = f_status_signal_keyboard_stop_s;

          break;

        case F_signal_tty_in:
          *name = f_status_signal_tty_in_s;

          break;

        case F_signal_tty_out:
          *name = f_status_signal_tty_out_s;

          break;

        case F_signal_urgent:
          *name = f_status_signal_urgent_s;

          break;

        case F_signal_cpu_limit:
          *name = f_status_signal_cpu_limit_s;

          break;

        case F_signal_file_size_limit:
          *name = f_status_signal_file_size_limit_s;

          break;

        case F_signal_virtual_alarm_clock:
          *name = f_status_signal_virtual_alarm_clock_s;

          break;

        case F_signal_profile_alarm_clock:
          *name = f_status_signal_profile_alarm_clock_s;

          break;

        case F_signal_window_size_change:
          *name = f_status_signal_window_size_change_s;

          break;

        case F_signal_pollable_event:
          *name = f_status_signal_pollable_event_s;

          break;

        case F_signal_power_failure:
          *name = f_status_signal_power_failure_s;

          break;

        case F_signal_bad_system_call:
          *name = f_status_signal_bad_system_call_s;

          break;

        case F_signal_reserved_32:
          *name = f_status_signal_reserved_32_s;

          break;

        case F_signal_reserved_33:
          *name = f_status_signal_reserved_33_s;

          break;

        case F_signal_reserved_34:
          *name = f_status_signal_reserved_34_s;

          break;

        case F_signal_reserved_35:
          *name = f_status_signal_reserved_35_s;

          break;

        case F_signal_reserved_36:
          *name = f_status_signal_reserved_36_s;

          break;

        case F_signal_reserved_37:
          *name = f_status_signal_reserved_37_s;

          break;

        case F_signal_reserved_38:
          *name = f_status_signal_reserved_38_s;

          break;

        case F_signal_reserved_39:
          *name = f_status_signal_reserved_39_s;

          break;

        case F_signal_reserved_40:
          *name = f_status_signal_reserved_40_s;

          break;

        case F_signal_reserved_41:
          *name = f_status_signal_reserved_41_s;

          break;

        case F_signal_reserved_42:
          *name = f_status_signal_reserved_42_s;

          break;

        case F_signal_reserved_43:
          *name = f_status_signal_reserved_43_s;

          break;

        case F_signal_reserved_44:
          *name = f_status_signal_reserved_44_s;

          break;

        case F_signal_reserved_45:
          *name = f_status_signal_reserved_45_s;

          break;

        case F_signal_reserved_46:
          *name = f_status_signal_reserved_46_s;

          break;

        case F_signal_reserved_47:
          *name = f_status_signal_reserved_47_s;

          break;

        case F_signal_reserved_48:
          *name = f_status_signal_reserved_48_s;

          break;

        case F_signal_reserved_49:
          *name = f_status_signal_reserved_49_s;

          break;

        case F_signal_reserved_50:
          *name = f_status_signal_reserved_50_s;

          break;

        case F_signal_reserved_51:
          *name = f_status_signal_reserved_51_s;

          break;

        case F_signal_reserved_52:
          *name = f_status_signal_reserved_52_s;

          break;

        case F_signal_reserved_53:
          *name = f_status_signal_reserved_53_s;

          break;

        case F_signal_reserved_54:
          *name = f_status_signal_reserved_54_s;

          break;

        case F_signal_reserved_55:
          *name = f_status_signal_reserved_55_s;

          break;

        case F_signal_reserved_56:
          *name = f_status_signal_reserved_56_s;

          break;

        case F_signal_reserved_57:
          *name = f_status_signal_reserved_57_s;

          break;

        case F_signal_reserved_58:
          *name = f_status_signal_reserved_58_s;

          break;

        case F_signal_reserved_59:
          *name = f_status_signal_reserved_59_s;

          break;

        case F_signal_reserved_60:
          *name = f_status_signal_reserved_60_s;

          break;

        case F_signal_reserved_61:
          *name = f_status_signal_reserved_61_s;

          break;

        case F_signal_reserved_62:
          *name = f_status_signal_reserved_62_s;

          break;

        case F_signal_reserved_63:
          *name = f_status_signal_reserved_63_s;

          break;

        case F_signal_reserved_64:
          *name = f_status_signal_reserved_64_s;

          break;
      #endif // _di_f_status_signal_

      #ifndef _di_f_status_basic_
        case F_none:
          *name = f_status_none_s;

          break;

        case F_abort:
          *name = f_status_abort_s;

          break;

        case F_abort_not:
          *name = f_status_abort_not_s;

          break;

        case F_absolute:
          *name = f_status_absolute_s;

          break;

        case F_absolute_not:
          *name = f_status_absolute_not_s;

          break;

        case F_address:
          *name = f_status_address_s;

          break;

        case F_address_not:
          *name = f_status_address_not_s;

          break;

        case F_ascii:
          *name = f_status_ascii_s;

          break;

        case F_ascii_not:
          *name = f_status_ascii_not_s;

          break;

        case F_atomic:
          *name = f_status_atomic_s;

          break;

        case F_atomic_not:
          *name = f_status_atomic_not_s;

          break;

        case F_base:
          *name = f_status_base_s;

          break;

        case F_base_not:
          *name = f_status_base_not_s;

          break;

        case F_begin:
          *name = f_status_begin_s;

          break;

        case F_begin_not:
          *name = f_status_begin_not_s;

          break;

        case F_block:
          *name = f_status_block_s;

          break;

        case F_block_not:
          *name = f_status_block_not_s;

          break;

        case F_break:
          *name = f_status_break_s;

          break;

        case F_break_not:
          *name = f_status_break_not_s;

          break;

        case F_body:
          *name = f_status_body_s;

          break;

        case F_body_not:
          *name = f_status_body_not_s;

          break;

        case F_bound:
          *name = f_status_bound_s;

          break;

        case F_bound_not:
          *name = f_status_bound_not_s;

          break;

        case F_call:
          *name = f_status_call_s;

          break;

        case F_call_not:
          *name = f_status_call_not_s;

          break;

        case F_capability:
          *name = f_status_capability_s;

          break;

        case F_capability_not:
          *name = f_status_capability_not_s;

          break;

        case F_child:
          *name = f_status_child_s;

          break;

        case F_child_not:
          *name = f_status_child_not_s;

          break;

        case F_complete:
          *name = f_status_complete_s;

          break;

        case F_complete_not:
          *name = f_status_complete_not_s;

          break;

        case F_connect:
          *name = f_status_connect_s;

          break;

        case F_connect_not:
          *name = f_status_connect_not_s;

          break;

        case F_connect_refuse:
          *name = f_status_connect_refuse_s;

          break;

        case F_connect_reset:
          *name = f_status_connect_reset_s;

          break;

        case F_content:
          *name = f_status_content_s;

          break;

        case F_content_not:
          *name = f_status_content_not_s;

          break;

        case F_continue:
          *name = f_status_continue_s;

          break;

        case F_continue_not:
          *name = f_status_continue_not_s;

          break;

        case F_container:
          *name = f_status_container_s;

          break;

        case F_container_not:
          *name = f_status_container_not_s;

          break;

        case F_control:
          *name = f_status_control_s;

          break;

        case F_control_not:
          *name = f_status_control_not_s;

          break;

        case F_control_group:
          *name = f_status_control_group_s;

          break;

        case F_control_group_not:
          *name = f_status_control_group_not_s;

          break;

        case F_critical:
          *name = f_status_critical_s;

          break;

        case F_critical_not:
          *name = f_status_critical_not_s;

          break;

        case F_dead:
          *name = f_status_dead_s;

          break;

        case F_dead_not:
          *name = f_status_dead_not_s;

          break;

        case F_deadlock:
          *name = f_status_deadlock_s;

          break;

        case F_deadlock_not:
          *name = f_status_deadlock_not_s;

          break;

        case F_descriptor:
          *name = f_status_descriptor_s;

          break;

        case F_descriptor_not:
          *name = f_status_descriptor_not_s;

          break;

        case F_desire:
          *name = f_status_desire_s;

          break;

        case F_desire_not:
          *name = f_status_desire_not_s;

          break;

        case F_device:
          *name = f_status_device_s;

          break;

        case F_device_not:
          *name = f_status_device_not_s;

          break;

        case F_disable:
          *name = f_status_disable_s;

          break;

        case F_disable_not:
          *name = f_status_disable_not_s;

          break;

        case F_discard:
          *name = f_status_discard_s;

          break;

        case F_discard_not:
          *name = f_status_discard_not_s;

          break;

        case F_domain:
          *name = f_status_domain_s;

          break;

        case F_domain_not:
          *name = f_status_domain_not_s;

          break;

        case F_done:
          *name = f_status_done_s;

          break;

        case F_done_not:
          *name = f_status_done_not_s;

          break;

        case F_drop:
          *name = f_status_drop_s;

          break;

        case F_drop_not:
          *name = f_status_drop_not_s;

          break;

        case F_dummy:
          *name = f_status_dummy_s;

          break;

        case F_dummy_not:
          *name = f_status_dummy_not_s;

          break;

        case F_empty:
          *name = f_status_empty_s;

          break;

        case F_empty_not:
          *name = f_status_empty_not_s;

          break;

        case F_enable:
          *name = f_status_enable_s;

          break;

        case F_enable_not:
          *name = f_status_enable_not_s;

          break;

        case F_encoding:
          *name = f_status_encoding_s;

          break;

        case F_encoding_not:
          *name = f_status_encoding_not_s;

          break;

        case F_endian:
          *name = f_status_endian_s;

          break;

        case F_endian_big:
          *name = f_status_endian_big_s;

          break;

        case F_endian_little:
          *name = f_status_endian_little_s;

          break;

        case F_endian_not:
          *name = f_status_endian_not_s;

          break;

        case F_eoa:
          *name = f_status_eoa_s;

          break;

        case F_eoa_not:
          *name = f_status_eoa_not_s;

          break;

        case F_eof:
          *name = f_status_eof_s;

          break;

        case F_eof_not:
          *name = f_status_eof_not_s;

          break;

        case F_eol:
          *name = f_status_eol_s;

          break;

        case F_eol_not:
          *name = f_status_eol_not_s;

          break;

        case F_eos:
          *name = f_status_eos_s;

          break;

        case F_eos_not:
          *name = f_status_eos_not_s;

          break;

        case F_execute:
          *name = f_status_execute_s;

          break;

        case F_execute_not:
          *name = f_status_execute_not_s;

          break;

        case F_exist:
          *name = f_status_exist_s;

          break;

        case F_exist_not:
          *name = f_status_exist_not_s;

          break;

        case F_exit:
          *name = f_status_exit_s;

          break;

        case F_exit_not:
          *name = f_status_exit_not_s;

          break;

        case F_failure:
          *name = f_status_failure_s;

          break;

        case F_failure_not:
          *name = f_status_failure_not_s;

          break;

        case F_family:
          *name = f_status_family_s;

          break;

        case F_family_not:
          *name = f_status_family_not_s;

          break;

        case F_first:
          *name = f_status_first_s;

          break;

        case F_first_not:
          *name = f_status_first_not_s;

          break;

        case F_footer:
          *name = f_status_footer_s;

          break;

        case F_footer_not:
          *name = f_status_footer_not_s;

          break;

        case F_fork:
          *name = f_status_fork_s;

          break;

        case F_fork_not:
          *name = f_status_fork_not_s;

          break;

        case F_format:
          *name = f_status_format_s;

          break;

        case F_format_not:
          *name = f_status_format_not_s;

          break;

        case F_found:
          *name = f_status_found_s;

          break;

        case F_found_not:
          *name = f_status_found_not_s;

          break;

        case F_full:
          *name = f_status_full_s;

          break;

        case F_full_not:
          *name = f_status_full_not_s;

          break;

        case F_group:
          *name = f_status_group_s;

          break;

        case F_group_not:
          *name = f_status_group_not_s;

          break;

        case F_halt:
          *name = f_status_halt_s;

          break;

        case F_halt_not:
          *name = f_status_halt_not_s;

          break;

        case F_header:
          *name = f_status_header_s;

          break;

        case F_header_not:
          *name = f_status_header_not_s;

          break;

        case F_ignore:
          *name = f_status_ignore_s;

          break;

        case F_ignore_not:
          *name = f_status_ignore_not_s;

          break;

        case F_implemented:
          *name = f_status_implemented_s;

          break;

        case F_implemented_not:
          *name = f_status_implemented_not_s;

          break;

        case F_input:
          *name = f_status_input_s;

          break;

        case F_input_not:
          *name = f_status_input_not_s;

          break;

        case F_input_output:
          *name = f_status_input_output_s;

          break;

        case F_interrupt:
          *name = f_status_interrupt_s;

          break;

        case F_interrupt_not:
          *name = f_status_interrupt_not_s;

          break;

        case F_keep:
          *name = f_status_keep_s;

          break;

        case F_keep_not:
          *name = f_status_keep_not_s;

          break;

        case F_last:
          *name = f_status_last_s;

          break;

        case F_last_not:
          *name = f_status_last_not_s;

          break;

        case F_limit:
          *name = f_status_limit_s;

          break;

        case F_limit_not:
          *name = f_status_limit_not_s;

          break;

        case F_link:
          *name = f_status_link_s;

          break;

        case F_link_not:
          *name = f_status_link_not_s;

          break;

        case F_live:
          *name = f_status_live_s;

          break;

        case F_live_not:
          *name = f_status_live_not_s;

          break;

        case F_local:
          *name = f_status_local_s;

          break;

        case F_local_not:
          *name = f_status_local_not_s;

          break;

        case F_lock:
          *name = f_status_lock_s;

          break;

        case F_lock_not:
          *name = f_status_lock_not_s;

          break;

        case F_loop:
          *name = f_status_loop_s;

          break;

        case F_loop_not:
          *name = f_status_loop_not_s;

          break;

        case F_maybe:
          *name = f_status_maybe_s;

          break;

        case F_maybe_not:
          *name = f_status_maybe_not_s;

          break;

        case F_memory:
          *name = f_status_memory_s;

          break;

        case F_memory_not:
          *name = f_status_memory_not_s;

          break;

        case F_message:
          *name = f_status_message_s;

          break;

        case F_message_not:
          *name = f_status_message_not_s;

          break;

        case F_minor:
          *name = f_status_minor_s;

          break;

        case F_minor_not:
          *name = f_status_minor_not_s;

          break;

        case F_moderate:
          *name = f_status_moderate_s;

          break;

        case F_moderate_not:
          *name = f_status_moderate_not_s;

          break;

        case F_mount:
          *name = f_status_mount_s;

          break;

        case F_mount_not:
          *name = f_status_mount_not_s;

          break;

        case F_name:
          *name = f_status_name_s;

          break;

        case F_name_not:
          *name = f_status_name_not_s;

          break;

        case F_need:
          *name = f_status_need_s;

          break;

        case F_need_not:
          *name = f_status_need_not_s;

          break;

        case F_next:
          *name = f_status_next_s;

          break;

        case F_next_not:
          *name = f_status_next_not_s;

          break;

        case F_nice:
          *name = f_status_nice_s;

          break;

        case F_nice_not:
          *name = f_status_nice_not_s;

          break;

        case F_no:
          *name = f_status_no_s;

          break;

        case F_no_not:
          *name = f_status_no_not_s;

          break;

        case F_object:
          *name = f_status_object_s;

          break;

        case F_object_not:
          *name = f_status_object_not_s;

          break;

        case F_okay:
          *name = f_status_okay_s;

          break;

        case F_okay_not:
          *name = f_status_okay_not_s;

          break;

        case F_once:
          *name = f_status_once_s;

          break;

        case F_once_not:
          *name = f_status_once_not_s;

          break;

        case F_option:
          *name = f_status_option_s;

          break;

        case F_option_not:
          *name = f_status_option_not_s;

          break;

        case F_output:
          *name = f_status_output_s;

          break;

        case F_output_not:
          *name = f_status_output_not_s;

          break;

        case F_packet:
          *name = f_status_packet_s;

          break;

        case F_packet_not:
          *name = f_status_packet_not_s;

          break;

        case F_parameter:
          *name = f_status_parameter_s;

          break;

        case F_parameter_not:
          *name = f_status_parameter_not_s;

          break;

        case F_parent:
          *name = f_status_parent_s;

          break;

        case F_parent_not:
          *name = f_status_parent_not_s;

          break;

        case F_payload:
          *name = f_status_payload_s;

          break;

        case F_payload_not:
          *name = f_status_payload_not_s;

          break;

        case F_pipe:
          *name = f_status_pipe_s;

          break;

        case F_pipe_not:
          *name = f_status_pipe_not_s;

          break;

        case F_port:
          *name = f_status_port_s;

          break;

        case F_port_not:
          *name = f_status_port_not_s;

          break;

        case F_previous:
          *name = f_status_previous_s;

          break;

        case F_previous_not:
          *name = f_status_previous_not_s;

          break;

        case F_processor:
          *name = f_status_processor_s;

          break;

        case F_processor_not:
          *name = f_status_processor_not_s;

          break;

        case F_progress:
          *name = f_status_progress_s;

          break;

        case F_progress_not:
          *name = f_status_progress_not_s;

          break;

        case F_prohibited:
          *name = f_status_prohibited_s;

          break;

        case F_prohibited_not:
          *name = f_status_prohibited_not_s;

          break;

        case F_property:
          *name = f_status_property_s;

          break;

        case F_property_not:
          *name = f_status_property_not_s;

          break;

        case F_protocol:
          *name = f_status_protocol_s;

          break;

        case F_protocol_not:
          *name = f_status_protocol_not_s;

          break;

        case F_range:
          *name = f_status_range_s;

          break;

        case F_range_not:
          *name = f_status_range_not_s;

          break;

        case F_read:
          *name = f_status_read_s;

          break;

        case F_read_not:
          *name = f_status_read_not_s;

          break;

        case F_read_only:
          *name = f_status_read_only_s;

          break;

        case F_ready:
          *name = f_status_ready_s;

          break;

        case F_ready_not:
          *name = f_status_ready_not_s;

          break;

        case F_receive:
          *name = f_status_receive_s;

          break;

        case F_receive_not:
          *name = f_status_receive_not_s;

          break;

        case F_recover:
          *name = f_status_recover_s;

          break;

        case F_recover_not:
          *name = f_status_recover_not_s;

          break;

        case F_recurse:
          *name = f_status_recurse_s;

          break;

        case F_recurse_not:
          *name = f_status_recurse_not_s;

          break;

        case F_relative:
          *name = f_status_relative_s;

          break;

        case F_relative_not:
          *name = f_status_relative_not_s;

          break;

        case F_remote:
          *name = f_status_remote_s;

          break;

        case F_remote_not:
          *name = f_status_remote_not_s;

          break;

        case F_repeat:
          *name = f_status_repeat_s;

          break;

        case F_repeat_not:
          *name = f_status_repeat_not_s;

          break;

        case F_require:
          *name = f_status_require_s;

          break;

        case F_require_not:
          *name = f_status_require_not_s;

          break;

        case F_resource:
          *name = f_status_resource_s;

          break;

        case F_resource_not:
          *name = f_status_resource_not_s;

          break;

        case F_restart:
          *name = f_status_restart_s;

          break;

        case F_restart_not:
          *name = f_status_restart_not_s;

          break;

        case F_restore:
          *name = f_status_restore_s;

          break;

        case F_restore_not:
          *name = f_status_restore_not_s;

          break;

        case F_revert:
          *name = f_status_revert_s;

          break;

        case F_revert_not:
          *name = f_status_revert_not_s;

          break;

        case F_schedule:
          *name = f_status_schedule_s;

          break;

        case F_schedule_not:
          *name = f_status_schedule_not_s;

          break;

        case F_search:
          *name = f_status_search_s;

          break;

        case F_search_not:
          *name = f_status_search_not_s;

          break;

        case F_send:
          *name = f_status_send_s;

          break;

        case F_send_not:
          *name = f_status_send_not_s;

          break;

        case F_size:
          *name = f_status_size_s;

          break;

        case F_size_not:
          *name = f_status_size_not_s;

          break;

        case F_signal:
          *name = f_status_signal_s;

          break;

        case F_signal_not:
          *name = f_status_signal_not_s;

          break;

        case F_skip:
          *name = f_status_skip_s;

          break;

        case F_skip_not:
          *name = f_status_skip_not_s;

          break;

        case F_space:
          *name = f_status_space_s;

          break;

        case F_space_not:
          *name = f_status_space_not_s;

          break;

        case F_start:
          *name = f_status_start_s;

          break;

        case F_start_not:
          *name = f_status_start_not_s;

          break;

        case F_status:
          *name = f_status_status_s;

          break;

        case F_status_not:
          *name = f_status_status_not_s;

          break;

        case F_stop:
          *name = f_status_stop_s;

          break;

        case F_stop_not:
          *name = f_status_stop_not_s;

          break;

        case F_store:
          *name = f_status_store_s;

          break;

        case F_store_not:
          *name = f_status_store_not_s;

          break;

        case F_stream:
          *name = f_status_stream_s;

          break;

        case F_stream_not:
          *name = f_status_stream_not_s;

          break;

        case F_string:
          *name = f_status_string_s;

          break;

        case F_string_not:
          *name = f_status_string_not_s;

          break;

        case F_string_too_large:
          *name = f_status_string_too_large_s;

          break;

        case F_string_too_small:
          *name = f_status_string_too_small_s;

          break;

        case F_syntax:
          *name = f_status_syntax_s;

          break;

        case F_syntax_not:
          *name = f_status_syntax_not_s;

          break;

        case F_terminate:
          *name = f_status_terminate_s;

          break;

        case F_terminate_not:
          *name = f_status_terminate_not_s;

          break;

        case F_thread:
          *name = f_status_thread_s;

          break;

        case F_thread_not:
          *name = f_status_thread_not_s;

          break;

        case F_time:
          *name = f_status_time_s;

          break;

        case F_time_not:
          *name = f_status_time_not_s;

          break;

        case F_time_out:
          *name = f_status_time_out_s;

          break;

        case F_too_large:
          *name = f_status_too_large_s;

          break;

        case F_too_small:
          *name = f_status_too_small_s;

          break;

        case F_type:
          *name = f_status_type_s;

          break;

        case F_type_not:
          *name = f_status_type_not_s;

          break;

        case F_known:
          *name = f_status_known_s;

          break;

        case F_known_not:
          *name = f_status_known_not_s;

          break;

        case F_success:
          *name = f_status_success_s;

          break;

        case F_success_not:
          *name = f_status_success_not_s;

          break;

        case F_support:
          *name = f_status_support_s;

          break;

        case F_support_not:
          *name = f_status_support_not_s;

          break;

        case F_user:
          *name = f_status_user_s;

          break;

        case F_user_not:
          *name = f_status_user_not_s;

          break;

        case F_utf:
          *name = f_status_utf_s;

          break;

        case F_utf_fragment:
          *name = f_status_utf_fragment_s;

          break;

        case F_utf_fragment_not:
          *name = f_status_utf_fragment_not_s;

          break;

        case F_utf_not:
          *name = f_status_utf_not_s;

          break;

        case F_valid:
          *name = f_status_valid_s;

          break;

        case F_valid_not:
          *name = f_status_valid_not_s;

          break;

        case F_value:
          *name = f_status_value_s;

          break;

        case F_value_not:
          *name = f_status_value_not_s;

          break;

        case F_wait:
          *name = f_status_wait_s;

          break;

        case F_wait_not:
          *name = f_status_wait_not_s;

          break;

        case F_want:
          *name = f_status_want_s;

          break;

        case F_want_not:
          *name = f_status_want_not_s;

          break;

        case F_wish:
          *name = f_status_wish_s;

          break;

        case F_wish_not:
          *name = f_status_wish_not_s;

          break;

        case F_world:
          *name = f_status_world_s;

          break;

        case F_world_not:
          *name = f_status_world_not_s;

          break;

        case F_write:
          *name = f_status_write_s;

          break;

        case F_write_not:
          *name = f_status_write_not_s;

          break;

        case F_write_only:
          *name = f_status_write_only_s;

          break;

        case F_yes:
          *name = f_status_yes_s;

          break;

        case F_yes_not:
          *name = f_status_yes_not_s;

          break;
      #endif // _di_f_status_basic_

      #ifndef _di_f_status_return_
        case F_debug:
          *name = f_status_debug_s;

          break;

        case F_debug_not:
          *name = f_status_debug_not_s;

          break;

        case F_error:
          *name = f_status_error_s;

          break;

        case F_error_not:
          *name = f_status_error_not_s;

          break;

        case F_fine:
          *name = f_status_fine_s;

          break;

        case F_fine_not:
          *name = f_status_fine_not_s;

          break;

        case F_warning:
          *name = f_status_warning_s;

          break;

        case F_warning_not:
          *name = f_status_warning_not_s;

          break;
      #endif // _di_f_status_return_

      #ifndef _di_f_status_array_
        case F_array:
          *name = f_status_array_s;

          break;

        case F_array_not:
          *name = f_status_array_not_s;

          break;

        case F_array_too_large:
          *name = f_status_array_too_large_s;

          break;

        case F_array_too_small:
          *name = f_status_array_too_small_s;

          break;
      #endif // _di_f_status_array_

      #ifndef _di_f_status_available_
        case F_available:
          *name = f_status_available_s;

          break;

        case F_available_not:
          *name = f_status_available_not_s;

          break;

        case F_available_not_address:
          *name = f_status_available_not_address_s;

          break;

        case F_available_not_buffer:
          *name = f_status_available_not_buffer_s;

          break;

        case F_available_not_device:
          *name = f_status_available_not_device_s;

          break;

        case F_available_not_pipe:
          *name = f_status_available_not_pipe_s;

          break;

        case F_available_not_port:
          *name = f_status_available_not_port_s;

          break;

        case F_available_not_process:
          *name = f_status_available_not_process_s;

          break;

        case F_available_not_socket:
          *name = f_status_available_not_socket_s;

          break;
      #endif // _di_f_status_available_

      #ifndef _di_f_status_busy_
        case F_busy:
          *name = f_status_busy_s;

          break;

        case F_busy_address:
          *name = f_status_busy_address_s;

          break;

        case F_busy_buffer:
          *name = f_status_busy_buffer_s;

          break;

        case F_busy_device:
          *name = f_status_busy_device_s;

          break;

        case F_busy_not:
          *name = f_status_busy_not_s;

          break;

        case F_busy_pipe:
          *name = f_status_busy_pipe_s;

          break;

        case F_busy_port:
          *name = f_status_busy_port_s;

          break;

        case F_busy_process:
          *name = f_status_busy_process_s;

          break;

        case F_busy_socket:
          *name = f_status_busy_socket_s;

          break;
      #endif // _di_f_status_busy_

      #ifndef _di_f_status_network_
        case F_network:
          *name = f_status_network_s;

          break;

        case F_network_busy:
          *name = f_status_network_busy_s;

          break;

        case F_network_busy_not:
          *name = f_status_network_busy_not_s;

          break;

        case F_network_client:
          *name = f_status_network_client_s;

          break;

        case F_network_client_not:
          *name = f_status_network_client_not_s;

          break;

        case F_network_device:
          *name = f_status_network_device_s;

          break;

        case F_network_device_not:
          *name = f_status_network_device_not_s;

          break;

        case F_network_found:
          *name = f_status_network_found_s;

          break;

        case F_network_found_not:
          *name = f_status_network_found_not_s;

          break;

        case F_network_lost:
          *name = f_status_network_lost_s;

          break;

        case F_network_lost_not:
          *name = f_status_network_lost_not_s;

          break;

        case F_network_not:
          *name = f_status_network_not_s;

          break;

        case F_network_reach:
          *name = f_status_network_reach_s;

          break;

        case F_network_reach_client:
          *name = f_status_network_reach_client_s;

          break;

        case F_network_reach_client_not:
          *name = f_status_network_reach_client_not_s;

          break;

        case F_network_reach_not:
          *name = f_status_network_reach_not_s;

          break;

        case F_network_reach_server:
          *name = f_status_network_reach_server_s;

          break;

        case F_network_reach_server_not:
          *name = f_status_network_reach_server_not_s;

          break;

        case F_network_server:
          *name = f_status_network_server_s;

          break;

        case F_network_server_not:
          *name = f_status_network_server_not_s;

          break;

        case F_network_time:
          *name = f_status_network_time_s;

          break;

        case F_network_time_not:
          *name = f_status_network_time_not_s;

          break;
      #endif // _di_f_status_network_

      #ifndef _di_f_status_number_
        case F_number:
          *name = f_status_number_s;

          break;

        case F_number_decimal:
          *name = f_status_number_decimal_s;

          break;

        case F_number_decimal_not:
          *name = f_status_number_decimal_not_s;

          break;

        case F_number_divide_by_zero:
          *name = f_status_number_divide_by_zero_s;

          break;

        case F_number_negative:
          *name = f_status_number_negative_s;

          break;

        case F_number_negative_not:
          *name = f_status_number_negative_not_s;

          break;

        case F_number_not:
          *name = f_status_number_not_s;

          break;

        case F_number_overflow:
          *name = f_status_number_overflow_s;

          break;

        case F_number_positive:
          *name = f_status_number_positive_s;

          break;

        case F_number_positive_not:
          *name = f_status_number_positive_not_s;

          break;

        case F_number_too_large:
          *name = f_status_number_too_large_s;

          break;

        case F_number_too_small:
          *name = f_status_number_too_small_s;

          break;

        case F_number_underflow:
          *name = f_status_number_underflow_s;

          break;

        case F_number_whole:
          *name = f_status_number_whole_s;

          break;

        case F_number_whole_not:
          *name = f_status_number_whole_not_s;

          break;

        case F_number_zero:
          *name = f_status_number_zero_s;

          break;

        case F_number_zero_not:
          *name = f_status_number_zero_not_s;

          break;
      #endif // _di_f_status_number_

      #ifndef _di_f_status_buffers_
        case F_buffer:
          *name = f_status_buffer_s;

          break;

        case F_buffer_not:
          *name = f_status_buffer_not_s;

          break;

        case F_buffer_overflow:
          *name = f_status_buffer_overflow_s;

          break;

        case F_buffer_too_large:
          *name = f_status_buffer_too_large_s;

          break;

        case F_buffer_too_small:
          *name = f_status_buffer_too_small_s;

          break;

        case F_buffer_underflow:
          *name = f_status_buffer_underflow_s;

          break;

        case F_complete_not_utf:
          *name = f_status_complete_not_utf_s;

          break;

        case F_complete_not_utf_block:
          *name = f_status_complete_not_utf_block_s;

          break;

        case F_complete_not_utf_eoa:
          *name = f_status_complete_not_utf_eoa_s;

          break;

        case F_complete_not_utf_eof:
          *name = f_status_complete_not_utf_eof_s;

          break;

        case F_complete_not_utf_eol:
          *name = f_status_complete_not_utf_eol_s;

          break;

        case F_complete_not_utf_eos:
          *name = f_status_complete_not_utf_eos_s;

          break;

        case F_complete_not_utf_start:
          *name = f_status_complete_not_utf_start_s;

          break;

        case F_complete_not_utf_stop:
          *name = f_status_complete_not_utf_stop_s;

          break;

        case F_none_block:
          *name = f_status_none_block_s;

          break;

        case F_none_eoa:
          *name = f_status_none_eoa_s;

          break;

        case F_none_eof:
          *name = f_status_none_eof_s;

          break;

        case F_none_eol:
          *name = f_status_none_eol_s;

          break;

        case F_none_eos:
          *name = f_status_none_eos_s;

          break;

        case F_none_start:
          *name = f_status_none_start_s;

          break;

        case F_none_stop:
          *name = f_status_none_stop_s;

          break;

        case F_data:
          *name = f_status_data_s;

          break;

        case F_data_not:
          *name = f_status_data_not_s;

          break;

        case F_data_not_block:
          *name = f_status_data_not_block_s;

          break;

        case F_data_not_eoa:
          *name = f_status_data_not_eoa_s;

          break;

        case F_data_not_eof:
          *name = f_status_data_not_eof_s;

          break;

        case F_data_not_eol:
          *name = f_status_data_not_eol_s;

          break;

        case F_data_not_eos:
          *name = f_status_data_not_eos_s;

          break;

        case F_data_not_start:
          *name = f_status_data_not_start_s;

          break;

        case F_data_not_stop:
          *name = f_status_data_not_stop_s;

          break;
      #endif // _di_f_status_buffers_

      #ifndef _di_f_status_end_
        case F_end:
          *name = f_status_end_s;

          break;

        case F_end_not:
          *name = f_status_end_not_s;

          break;

        case F_end_not_block:
          *name = f_status_end_not_block_s;

          break;

        case F_end_not_eoa:
          *name = f_status_end_not_eoa_s;

          break;

        case F_end_not_eof:
          *name = f_status_end_not_eof_s;

          break;

        case F_end_not_eol:
          *name = f_status_end_not_eol_s;

          break;

        case F_end_not_eos:
          *name = f_status_end_not_eos_s;

          break;

        case F_end_not_group:
          *name = f_status_end_not_group_s;

          break;

        case F_end_not_group_block:
          *name = f_status_end_not_group_block_s;

          break;

        case F_end_not_group_eoa:
          *name = f_status_end_not_group_eoa_s;

          break;

        case F_end_not_group_eof:
          *name = f_status_end_not_group_eof_s;

          break;

        case F_end_not_group_eol:
          *name = f_status_end_not_group_eol_s;

          break;

        case F_end_not_group_eos:
          *name = f_status_end_not_group_eos_s;

          break;

        case F_end_not_group_start:
          *name = f_status_end_not_group_start_s;

          break;

        case F_end_not_group_stop:
          *name = f_status_end_not_group_stop_s;

          break;

        case F_end_not_nest:
          *name = f_status_end_not_nest_s;

          break;

        case F_end_not_nest_block:
          *name = f_status_end_not_nest_block_s;

          break;

        case F_end_not_nest_eoa:
          *name = f_status_end_not_nest_eoa_s;

          break;

        case F_end_not_nest_eof:
          *name = f_status_end_not_nest_eof_s;

          break;

        case F_end_not_nest_eol:
          *name = f_status_end_not_nest_eol_s;

          break;

        case F_end_not_nest_eos:
          *name = f_status_end_not_nest_eos_s;

          break;

        case F_end_not_nest_start:
          *name = f_status_end_not_nest_start_s;

          break;

        case F_end_not_nest_stop:
          *name = f_status_end_not_nest_stop_s;

          break;

        case F_end_not_start:
          *name = f_status_end_not_start_s;

          break;

        case F_end_not_stop:
          *name = f_status_end_not_stop_s;

          break;
      #endif // _di_f_status_end_

      #ifndef _di_f_status_process_
        case F_process:
          *name = f_status_process_s;

          break;

        case F_process_not:
          *name = f_status_process_not_s;

          break;

        case F_process_too_many:
          *name = f_status_process_too_many_s;

          break;
      #endif // _di_f_status_process_

      #ifndef _di_f_status_file_
        case F_file:
          *name = f_status_file_s;

          break;

        case F_file_close:
          *name = f_status_file_close_s;

          break;

        case F_file_closed:
          *name = f_status_file_closed_s;

          break;

        case F_file_descriptor:
          *name = f_status_file_descriptor_s;

          break;

        case F_file_descriptor_max:
          *name = f_status_file_descriptor_max_s;

          break;

        case F_file_descriptor_not:
          *name = f_status_file_descriptor_not_s;

          break;

        case F_file_empty:
          *name = f_status_file_empty_s;

          break;

        case F_file_flush:
          *name = f_status_file_flush_s;

          break;

        case F_file_found:
          *name = f_status_file_found_s;

          break;

        case F_file_found_not:
          *name = f_status_file_found_not_s;

          break;

        case F_file_not:
          *name = f_status_file_not_s;

          break;

        case F_file_open:
          *name = f_status_file_open_s;

          break;

        case F_file_open_max:
          *name = f_status_file_open_max_s;

          break;

        case F_file_opened:
          *name = f_status_file_opened_s;

          break;

        case F_file_overflow:
          *name = f_status_file_overflow_s;

          break;

        case F_file_purge:
          *name = f_status_file_purge_s;

          break;

        case F_file_read:
          *name = f_status_file_read_s;

          break;

        case F_file_reallocation:
          *name = f_status_file_reallocation_s;

          break;

        case F_file_seek:
          *name = f_status_file_seek_s;

          break;

        case F_file_stat:
          *name = f_status_file_stat_s;

          break;

        case F_file_synchronize:
          *name = f_status_file_synchronize_s;

          break;

        case F_file_type_block:
          *name = f_status_file_type_block_s;

          break;

        case F_file_type_character:
          *name = f_status_file_type_character_s;

          break;

        case F_file_type_directory:
          *name = f_status_file_type_directory_s;

          break;

        case F_file_type_fifo:
          *name = f_status_file_type_fifo_s;

          break;

        case F_file_type_link:
          *name = f_status_file_type_link_s;

          break;

        case F_file_type_not_block:
          *name = f_status_file_type_not_block_s;

          break;

        case F_file_type_not_character:
          *name = f_status_file_type_not_character_s;

          break;

        case F_file_type_not_directory:
          *name = f_status_file_type_not_directory_s;

          break;

        case F_file_type_not_fifo:
          *name = f_status_file_type_not_fifo_s;

          break;

        case F_file_type_not_link:
          *name = f_status_file_type_not_link_s;

          break;

        case F_file_type_not_pipe:
          *name = f_status_file_type_not_pipe_s;

          break;

        case F_file_type_not_regular:
          *name = f_status_file_type_not_regular_s;

          break;

        case F_file_type_not_socket:
          *name = f_status_file_type_not_socket_s;

          break;

        case F_file_type_not_unknown:
          *name = f_status_file_type_not_unknown_s;

          break;

        case F_file_type_pipe:
          *name = f_status_file_type_pipe_s;

          break;

        case F_file_type_regular:
          *name = f_status_file_type_regular_s;

          break;

        case F_file_type_socket:
          *name = f_status_file_type_socket_s;

          break;

        case F_file_type_unknown:
          *name = f_status_file_type_unknown_s;

          break;

        case F_file_underflow:
          *name = f_status_file_underflow_s;

          break;

        case F_file_utf:
          *name = f_status_file_utf_s;

          break;

        case F_file_utf_not:
          *name = f_status_file_utf_not_s;

          break;

        case F_file_write:
          *name = f_status_file_write_s;

          break;
      #endif // _di_f_status_file_

      #ifndef _di_f_status_filesystem_
        case F_filesystem:
          *name = f_status_filesystem_s;

          break;

        case F_filesystem_not:
          *name = f_status_filesystem_not_s;

          break;

        case F_filesystem_quota_block:
          *name = f_status_filesystem_quota_block_s;

          break;

        case F_filesystem_quota_reached:
          *name = f_status_filesystem_quota_reached_s;

          break;
      #endif // _di_f_status_filesystem_

      #ifndef _di_f_status_directory_
        case F_directory:
          *name = f_status_directory_s;

          break;

        case F_directory_close:
          *name = f_status_directory_close_s;

          break;

        case F_directory_closed:
          *name = f_status_directory_closed_s;

          break;

        case F_directory_descriptor:
          *name = f_status_directory_descriptor_s;

          break;

        case F_directory_empty:
          *name = f_status_directory_empty_s;

          break;

        case F_directory_empty_not:
          *name = f_status_directory_empty_not_s;

          break;

        case F_directory_found:
          *name = f_status_directory_found_s;

          break;

        case F_directory_found_not:
          *name = f_status_directory_found_not_s;

          break;

        case F_directory_flush:
          *name = f_status_directory_flush_s;

          break;

        case F_directory_link_max:
          *name = f_status_directory_link_max_s;

          break;

        case F_directory_not:
          *name = f_status_directory_not_s;

          break;

        case F_directory_open:
          *name = f_status_directory_open_s;

          break;

        case F_directory_purge:
          *name = f_status_directory_purge_s;

          break;

        case F_directory_read:
          *name = f_status_directory_read_s;

          break;

        case F_directory_stream:
          *name = f_status_directory_stream_s;

          break;

        case F_directory_synchronize:
          *name = f_status_directory_synchronize_s;

          break;

        case F_directory_supported_not:
          *name = f_status_directory_supported_not_s;

          break;

        case F_directory_utf:
          *name = f_status_directory_utf_s;

          break;

        case F_directory_utf_not:
          *name = f_status_directory_utf_not_s;

          break;

        case F_directory_write:
          *name = f_status_directory_write_s;

          break;
      #endif // _di_f_status_directory_

      #ifndef _di_f_status_socket_
        case F_socket:
          *name = f_status_socket_s;

          break;

        case F_socket_client:
          *name = f_status_socket_client_s;

          break;

        case F_socket_not:
          *name = f_status_socket_not_s;

          break;

        case F_socket_receive:
          *name = f_status_socket_receive_s;

          break;

        case F_socket_send:
          *name = f_status_socket_send_s;

          break;

        case F_socket_target:
          *name = f_status_socket_target_s;

          break;
      #endif // _di_f_status_socket_

      #ifndef _di_f_error_compare_
        case F_equal_to:
          *name = f_status_equal_to_s;

          break;

        case F_equal_to_not:
          *name = f_status_equal_to_not_s;

          break;

        case F_than_greater:
          *name = f_status_than_greater_s;

          break;

        case F_than_less:
          *name = f_status_than_less_s;

          break;
      #endif // _di_f_status_compare_

      #ifndef _di_f_status_access_
        case F_access:
          *name = f_status_access_s;

          break;

        case F_access_denied:
          *name = f_status_access_denied_s;

          break;

        case F_access_denied_user:
          *name = f_status_access_denied_user_s;

          break;

        case F_access_denied_group:
          *name = f_status_access_denied_group_s;

          break;

        case F_access_denied_world:
          *name = f_status_access_denied_world_s;

          break;

        case F_access_denied_read:
          *name = f_status_access_denied_read_s;

          break;

        case F_access_denied_write:
          *name = f_status_access_denied_write_s;

          break;

        case F_access_denied_execute:
          *name = f_status_access_denied_execute_s;

          break;

        case F_access_denied_super:
          *name = f_status_access_denied_super_s;

          break;

        case F_access_granted:
          *name = f_status_access_granted_s;

          break;

        case F_access_granted_user:
          *name = f_status_access_granted_user_s;

          break;

        case F_access_granted_group:
          *name = f_status_access_granted_group_s;

          break;

        case F_access_granted_world:
          *name = f_status_access_granted_world_s;

          break;

        case F_access_granted_read:
          *name = f_status_access_granted_read_s;

          break;

        case F_access_granted_write:
          *name = f_status_access_granted_write_s;

          break;

        case F_access_granted_execute:
          *name = f_status_access_granted_execute_s;

          break;

        case F_access_granted_super:
          *name = f_status_access_granted_super_s;

          break;

        case F_access_group:
          *name = f_status_access_group_s;

          break;

        case F_access_mode:
          *name = f_status_access_mode_s;

          break;

        case F_access_not:
          *name = f_status_access_not_s;

          break;

        case F_access_owner:
          *name = f_status_access_owner_s;

          break;
      #endif // _di_f_status_access_

      #ifndef _di_f_status_terminal_
        case F_terminal:
          *name = f_status_terminal_s;

          break;

        case F_terminal_access:
          *name = f_status_terminal_access_s;

          break;

        case F_terminal_known:
          *name = f_status_terminal_known_s;

          break;

        case F_terminal_known_not:
          *name = f_status_terminal_known_not_s;

          break;

        case F_terminal_not:
          *name = f_status_terminal_not_s;

          break;

        case F_terminal_prohibited:
          *name = f_status_terminal_prohibited_s;

          break;

        case F_terminal_read:
          *name = f_status_terminal_read_s;

          break;

        case F_terminal_valid:
          *name = f_status_terminal_valid_s;

          break;

        case F_terminal_valid_not:
          *name = f_status_terminal_valid_not_s;

          break;

        case F_terminal_write:
          *name = f_status_terminal_write_s;

          break;
      #endif // _di_f_status_terminal_

      case F_status_code_last:
        *name = f_status_status_code_last_s;

        break;

      default:
        *name = f_string_empty_s;

        return F_status_set_error(F_data);
    }

    return F_none;
  }
#endif // _di_f_status_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

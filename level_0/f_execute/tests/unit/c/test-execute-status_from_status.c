#include "test-execute.h"
#include "test-execute-status_from_status.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_execute_status_from_status__fails(void **state) {

  for (f_status_t i = 0; i < F_status_code_last; ++i) {

    // Skip past all valid status codes.
    if (i == F_none) continue;
    if (i == F_access) continue;
    if (i == F_execute_not) continue;
    if (i == F_buffer) continue;
    if (i == F_busy) continue;
    if (i == F_capability) continue;
    if (i == F_control_group) continue;
    if (i == F_child) continue;
    if (i == F_directory_not) continue;
    if (i == F_failure) continue;
    if (i == F_file_found_not) continue;
    if (i == F_file_type_directory) continue;
    if (i == F_fork_not) continue;
    if (i == F_format_not) continue;
    if (i == F_group) continue;
    if (i == F_input_output) continue;
    if (i == F_limit) continue;
    if (i == F_loop) continue;
    if (i == F_memory_not) continue;
    if (i == F_name_not) continue;
    if (i == F_nice) continue;
    if (i == F_parameter) continue;
    if (i == F_pipe) continue;
    if (i == F_processor) continue;
    if (i == F_prohibited) continue;
    if (i == F_resource_not) continue;
    if (i == F_schedule) continue;
    if (i == F_terminal) continue;
    if (i == F_terminal_known_not) continue;
    if (i == F_terminal_not) continue;
    if (i == F_terminal_prohibited) continue;
    if (i == F_terminal_valid_not) continue;
    if (i == F_too_large) continue;
    if (i == F_user) continue;
    if (i == F_valid_not) continue;
    if (i == F_call_not) continue;
    if (i == F_found_not) continue;
    if (i == F_exit) continue;
    if (i == F_signal_hangup) continue;
    if (i == F_signal_interrupt) continue;
    if (i == F_signal_quit) continue;
    if (i == F_signal_illegal) continue;
    if (i == F_signal_trap) continue;
    if (i == F_signal_abort) continue;
    if (i == F_signal_bus_error) continue;
    if (i == F_signal_floating_point_error) continue;
    if (i == F_signal_kill) continue;
    if (i == F_signal_user_1) continue;
    if (i == F_signal_segmentation_fault) continue;
    if (i == F_signal_user_2) continue;
    if (i == F_signal_broken_pipe) continue;
    if (i == F_signal_alarm_clock) continue;
    if (i == F_signal_termination) continue;
    if (i == F_signal_stack_fault) continue;
    if (i == F_signal_child) continue;
    if (i == F_signal_continue) continue;
    if (i == F_signal_stop) continue;
    if (i == F_signal_keyboard_stop) continue;
    if (i == F_signal_tty_in) continue;
    if (i == F_signal_tty_out) continue;
    if (i == F_signal_urgent) continue;
    if (i == F_signal_cpu_limit) continue;
    if (i == F_signal_file_size_limit) continue;
    if (i == F_signal_virtual_alarm_clock) continue;
    if (i == F_signal_profile_alarm_clock) continue;
    if (i == F_signal_window_size_change) continue;
    if (i == F_signal_pollable_event) continue;
    if (i == F_signal_power_failure) continue;
    if (i == F_signal_bad_system_call) continue;
    if (i == F_signal_reserved_32) continue;
    if (i == F_signal_reserved_33) continue;
    if (i == F_signal_reserved_34) continue;
    if (i == F_signal_reserved_35) continue;
    if (i == F_signal_reserved_36) continue;
    if (i == F_signal_reserved_37) continue;
    if (i == F_signal_reserved_38) continue;
    if (i == F_signal_reserved_39) continue;
    if (i == F_signal_reserved_40) continue;
    if (i == F_signal_reserved_41) continue;
    if (i == F_signal_reserved_42) continue;
    if (i == F_signal_reserved_43) continue;
    if (i == F_signal_reserved_44) continue;
    if (i == F_signal_reserved_45) continue;
    if (i == F_signal_reserved_46) continue;
    if (i == F_signal_reserved_47) continue;
    if (i == F_signal_reserved_48) continue;
    if (i == F_signal_reserved_49) continue;
    if (i == F_signal_reserved_50) continue;
    if (i == F_signal_reserved_51) continue;
    if (i == F_signal_reserved_52) continue;
    if (i == F_signal_reserved_53) continue;
    if (i == F_signal_reserved_54) continue;
    if (i == F_signal_reserved_55) continue;
    if (i == F_signal_reserved_56) continue;
    if (i == F_signal_reserved_57) continue;
    if (i == F_signal_reserved_58) continue;
    if (i == F_signal_reserved_59) continue;
    if (i == F_signal_reserved_60) continue;
    if (i == F_signal_reserved_61) continue;
    if (i == F_signal_reserved_62) continue;
    if (i == F_signal_reserved_63) continue;
    if (i == F_signal_reserved_64) continue;

    const uint8_t execute_status = f_execute_status_from_status(i);

    assert_int_equal(execute_status, F_execute_code_last);
  } // for
}

void test__f_execute_status_from_status__works(void **state) {

  const uint8_t status_executes[] = {
    F_execute_none,
    F_execute_access,
    F_execute_bad,
    F_execute_buffer,
    F_execute_busy,
    F_execute_capability,
    F_execute_control_group,
    F_execute_child,
    F_execute_directory_not,
    F_execute_failure,
    F_execute_file_found_not,
    F_execute_file_type_directory,
    F_execute_fork_not,
    F_execute_format_not,
    F_execute_group,
    F_execute_input_output,
    F_execute_limit,
    F_execute_loop,
    F_execute_memory_not,
    F_execute_name_not,
    F_execute_nice,
    F_execute_parameter,
    F_execute_pipe,
    F_execute_processor,
    F_execute_prohibited,
    F_execute_resource_not,
    F_execute_schedule,
    F_execute_terminal,
    F_execute_terminal_known_not,
    F_execute_terminal_not,
    F_execute_terminal_prohibited,
    F_execute_terminal_valid_not,
    F_execute_too_large,
    F_execute_user,
    F_execute_valid_not,
    F_execute_invoke_not,
    F_execute_found_not,
    F_execute_exit_parameter,
    F_execute_signal_hangup,
    F_execute_signal_interrupt,
    F_execute_signal_quit,
    F_execute_signal_illegal,
    F_execute_signal_trap,
    F_execute_signal_abort,
    F_execute_signal_bus_error,
    F_execute_signal_floating_point_error,
    F_execute_signal_kill,
    F_execute_signal_user_1,
    F_execute_signal_segmentation_fault,
    F_execute_signal_user_2,
    F_execute_signal_broken_pipe,
    F_execute_signal_alarm_clock,
    F_execute_signal_termination,
    F_execute_signal_stack_fault,
    F_execute_signal_child,
    F_execute_signal_continue,
    F_execute_signal_stop,
    F_execute_signal_keyboard_stop,
    F_execute_signal_tty_in,
    F_execute_signal_tty_out,
    F_execute_signal_urgent,
    F_execute_signal_cpu_limit,
    F_execute_signal_file_size_limit,
    F_execute_signal_virtual_alarm_clock,
    F_execute_signal_profile_alarm_clock,
    F_execute_signal_window_size_change,
    F_execute_signal_pollable_event,
    F_execute_signal_power_failure,
    F_execute_signal_bad_system_call,
    F_execute_signal_reserved_32,
    F_execute_signal_reserved_33,
    F_execute_signal_reserved_34,
    F_execute_signal_reserved_35,
    F_execute_signal_reserved_36,
    F_execute_signal_reserved_37,
    F_execute_signal_reserved_38,
    F_execute_signal_reserved_39,
    F_execute_signal_reserved_40,
    F_execute_signal_reserved_41,
    F_execute_signal_reserved_42,
    F_execute_signal_reserved_43,
    F_execute_signal_reserved_44,
    F_execute_signal_reserved_45,
    F_execute_signal_reserved_46,
    F_execute_signal_reserved_47,
    F_execute_signal_reserved_48,
    F_execute_signal_reserved_49,
    F_execute_signal_reserved_50,
    F_execute_signal_reserved_51,
    F_execute_signal_reserved_52,
    F_execute_signal_reserved_53,
    F_execute_signal_reserved_54,
    F_execute_signal_reserved_55,
    F_execute_signal_reserved_56,
    F_execute_signal_reserved_57,
    F_execute_signal_reserved_58,
    F_execute_signal_reserved_59,
    F_execute_signal_reserved_60,
    F_execute_signal_reserved_61,
    F_execute_signal_reserved_62,
    F_execute_signal_reserved_63,
    F_execute_signal_reserved_64,
  };

  const f_status_t statuss[] = {
    F_none,
    F_access,
    F_execute_not,
    F_buffer,
    F_busy,
    F_capability,
    F_control_group,
    F_child,
    F_directory_not,
    F_failure,
    F_file_found_not,
    F_file_type_directory,
    F_fork_not,
    F_format_not,
    F_group,
    F_input_output,
    F_limit,
    F_loop,
    F_memory_not,
    F_name_not,
    F_nice,
    F_parameter,
    F_pipe,
    F_processor,
    F_prohibited,
    F_resource_not,
    F_schedule,
    F_terminal,
    F_terminal_known_not,
    F_terminal_not,
    F_terminal_prohibited,
    F_terminal_valid_not,
    F_too_large,
    F_user,
    F_valid_not,
    F_call_not,
    F_found_not,
    F_exit,
    F_signal_hangup,
    F_signal_interrupt,
    F_signal_quit,
    F_signal_illegal,
    F_signal_trap,
    F_signal_abort,
    F_signal_bus_error,
    F_signal_floating_point_error,
    F_signal_kill,
    F_signal_user_1,
    F_signal_segmentation_fault,
    F_signal_user_2,
    F_signal_broken_pipe,
    F_signal_alarm_clock,
    F_signal_termination,
    F_signal_stack_fault,
    F_signal_child,
    F_signal_continue,
    F_signal_stop,
    F_signal_keyboard_stop,
    F_signal_tty_in,
    F_signal_tty_out,
    F_signal_urgent,
    F_signal_cpu_limit,
    F_signal_file_size_limit,
    F_signal_virtual_alarm_clock,
    F_signal_profile_alarm_clock,
    F_signal_window_size_change,
    F_signal_pollable_event,
    F_signal_power_failure,
    F_signal_bad_system_call,
    F_signal_reserved_32,
    F_signal_reserved_33,
    F_signal_reserved_34,
    F_signal_reserved_35,
    F_signal_reserved_36,
    F_signal_reserved_37,
    F_signal_reserved_38,
    F_signal_reserved_39,
    F_signal_reserved_40,
    F_signal_reserved_41,
    F_signal_reserved_42,
    F_signal_reserved_43,
    F_signal_reserved_44,
    F_signal_reserved_45,
    F_signal_reserved_46,
    F_signal_reserved_47,
    F_signal_reserved_48,
    F_signal_reserved_49,
    F_signal_reserved_50,
    F_signal_reserved_51,
    F_signal_reserved_52,
    F_signal_reserved_53,
    F_signal_reserved_54,
    F_signal_reserved_55,
    F_signal_reserved_56,
    F_signal_reserved_57,
    F_signal_reserved_58,
    F_signal_reserved_59,
    F_signal_reserved_60,
    F_signal_reserved_61,
    F_signal_reserved_62,
    F_signal_reserved_63,
    F_signal_reserved_64,
  };

  for (uint8_t i = 0; i < 102; ++i) {

    const uint8_t execute_status = f_execute_status_from_status(statuss[i]);

    assert_int_equal(execute_status, status_executes[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

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
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_status_string_
  #ifndef _di_fl_status_booleans_
    #define fl_status_string_false "f_false"
    #define fl_status_string_false_length 8

    #define fl_status_string_true "f_true"
    #define fl_status_string_true_length 7
  #endif // _di_fl_status_booleans_

  #ifndef _di_fl_status_signals_
    #define fl_status_string_signal_hangup "f_signal_hangup"
    #define fl_status_string_signal_hangup_length 16

    #define fl_status_string_signal_interrupt "f_signal_interrupt"
    #define fl_status_string_signal_interrupt_length 19

    #define fl_status_string_signal_quit "f_signal_quit"
    #define fl_status_string_signal_quit_length 14

    #define fl_status_string_signal_illegal "f_signal_illegal"
    #define fl_status_string_signal_illegal_length 17

    #define fl_status_string_signal_trap "f_signal_trap"
    #define fl_status_string_signal_trap_length 14

    #define fl_status_string_signal_abort "f_signal_abort"
    #define fl_status_string_signal_abort_length 15

    #define fl_status_string_signal_bus_error "f_signal_bus_error"
    #define fl_status_string_signal_bus_error_length 18

    #define fl_status_string_signal_floating_point_exception "f_signal_floating_point_exception"
    #define fl_status_string_signal_floating_point_exception_length 34

    #define fl_status_string_signal_kill "f_signal_kill"
    #define fl_status_string_signal_kill_length 14

    #define fl_status_string_signal_user_1 "f_signal_user_1"
    #define fl_status_string_signal_user_1_length 16

    #define fl_status_string_signal_segmentation_fault "f_signal_segmentation_fault"
    #define fl_status_string_signal_segmentation_fault_length 28

    #define fl_status_string_signal_user_2 "f_signal_user_2"
    #define fl_status_string_signal_user_2_length 16

    #define fl_status_string_signal_broken_pipe "f_signal_broken_pipe"
    #define fl_status_string_signal_broken_pipe_length 21

    #define fl_status_string_signal_alarm_clock "f_signal_alarm_clock"
    #define fl_status_string_signal_alarm_clock_length 21

    #define fl_status_string_signal_termination "f_signal_termination"
    #define fl_status_string_signal_termination_length 21

    #define fl_status_string_signal_stack_fault "f_signal_stack_fault"
    #define fl_status_string_signal_stack_fault_length 21

    #define fl_status_string_signal_child "f_signal_child"
    #define fl_status_string_signal_child_length 15

    #define fl_status_string_signal_continue "f_signal_continue"
    #define fl_status_string_signal_continue_length 18

    #define fl_status_string_signal_stop "f_signal_stop"
    #define fl_status_string_signal_stop_length 14

    #define fl_status_string_signal_keyboard_stop "f_signal_keyboard_stop"
    #define fl_status_string_signal_keyboard_stop_length 23

    #define fl_status_string_signal_tty_in "f_signal_tty_in"
    #define fl_status_string_signal_tty_in_length 16

    #define fl_status_string_signal_tty_out "f_signal_tty_out"
    #define fl_status_string_signal_tty_out_length 17

    #define fl_status_string_signal_urgent "f_signal_urgent"
    #define fl_status_string_signal_urgent_length 16

    #define fl_status_string_signal_cpu_limit "f_signal_cpu_limit"
    #define fl_status_string_signal_cpu_limit_length 19

    #define fl_status_string_signal_file_size_limit "f_signal_file_size_limit"
    #define fl_status_string_signal_file_size_limit_length 25

    #define fl_status_string_signal_virtual_alarm_clock "f_signal_virtual_alarm_clock"
    #define fl_status_string_signal_virtual_alarm_clock_length 29

    #define fl_status_string_signal_profile_alarm_clock "f_signal_profile_alarm_clock"
    #define fl_status_string_signal_profile_alarm_clock_length 29

    #define fl_status_string_signal_window_size_change "f_signal_window_size_change"
    #define fl_status_string_signal_window_size_change_length 28

    #define fl_status_string_signal_pollable_event "f_signal_pollable_event"
    #define fl_status_string_signal_pollable_event_length 24

    #define fl_status_string_signal_power_failure "f_signal_power_failure"
    #define fl_status_string_signal_power_failure_length 23

    #define fl_status_string_signal_bad_system_call "f_signal_bad_system_call"
    #define fl_status_string_signal_bad_system_call_length 25

    #define fl_status_string_signal_reserved_32 "f_signal_reserved_32"
    #define fl_status_string_signal_reserved_32_length 21

    #define fl_status_string_signal_reserved_33 "f_signal_reserved_33"
    #define fl_status_string_signal_reserved_33_length 21

    #define fl_status_string_signal_reserved_34 "f_signal_reserved_34"
    #define fl_status_string_signal_reserved_34_length 21

    #define fl_status_string_signal_reserved_35 "f_signal_reserved_35"
    #define fl_status_string_signal_reserved_35_length 21

    #define fl_status_string_signal_reserved_36 "f_signal_reserved_36"
    #define fl_status_string_signal_reserved_36_length 21

    #define fl_status_string_signal_reserved_37 "f_signal_reserved_37"
    #define fl_status_string_signal_reserved_37_length 21

    #define fl_status_string_signal_reserved_38 "f_signal_reserved_38"
    #define fl_status_string_signal_reserved_38_length 21

    #define fl_status_string_signal_reserved_39 "f_signal_reserved_39"
    #define fl_status_string_signal_reserved_39_length 21

    #define fl_status_string_signal_reserved_40 "f_signal_reserved_40"
    #define fl_status_string_signal_reserved_40_length 21

    #define fl_status_string_signal_reserved_41 "f_signal_reserved_41"
    #define fl_status_string_signal_reserved_41_length 21

    #define fl_status_string_signal_reserved_42 "f_signal_reserved_42"
    #define fl_status_string_signal_reserved_42_length 21

    #define fl_status_string_signal_reserved_43 "f_signal_reserved_43"
    #define fl_status_string_signal_reserved_43_length 21

    #define fl_status_string_signal_reserved_44 "f_signal_reserved_44"
    #define fl_status_string_signal_reserved_44_length 21

    #define fl_status_string_signal_reserved_45 "f_signal_reserved_45"
    #define fl_status_string_signal_reserved_45_length 21

    #define fl_status_string_signal_reserved_46 "f_signal_reserved_46"
    #define fl_status_string_signal_reserved_46_length 21

    #define fl_status_string_signal_reserved_47 "f_signal_reserved_47"
    #define fl_status_string_signal_reserved_47_length 21

    #define fl_status_string_signal_reserved_48 "f_signal_reserved_48"
    #define fl_status_string_signal_reserved_48_length 21

    #define fl_status_string_signal_reserved_49 "f_signal_reserved_49"
    #define fl_status_string_signal_reserved_49_length 21

    #define fl_status_string_signal_reserved_50 "f_signal_reserved_50"
    #define fl_status_string_signal_reserved_50_length 21

    #define fl_status_string_signal_reserved_51 "f_signal_reserved_51"
    #define fl_status_string_signal_reserved_51_length 21

    #define fl_status_string_signal_reserved_52 "f_signal_reserved_52"
    #define fl_status_string_signal_reserved_52_length 21

    #define fl_status_string_signal_reserved_53 "f_signal_reserved_53"
    #define fl_status_string_signal_reserved_53_length 21

    #define fl_status_string_signal_reserved_54 "f_signal_reserved_54"
    #define fl_status_string_signal_reserved_54_length 21

    #define fl_status_string_signal_reserved_55 "f_signal_reserved_55"
    #define fl_status_string_signal_reserved_55_length 21

    #define fl_status_string_signal_reserved_56 "f_signal_reserved_56"
    #define fl_status_string_signal_reserved_56_length 21

    #define fl_status_string_signal_reserved_57 "f_signal_reserved_57"
    #define fl_status_string_signal_reserved_57_length 21

    #define fl_status_string_signal_reserved_58 "f_signal_reserved_58"
    #define fl_status_string_signal_reserved_58_length 21

    #define fl_status_string_signal_reserved_59 "f_signal_reserved_59"
    #define fl_status_string_signal_reserved_59_length 21

    #define fl_status_string_signal_reserved_60 "f_signal_reserved_60"
    #define fl_status_string_signal_reserved_60_length 21

    #define fl_status_string_signal_reserved_61 "f_signal_reserved_61"
    #define fl_status_string_signal_reserved_61_length 21

    #define fl_status_string_signal_reserved_62 "f_signal_reserved_62"
    #define fl_status_string_signal_reserved_62_length 21

    #define fl_status_string_signal_reserved_63 "f_signal_reserved_63"
    #define fl_status_string_signal_reserved_63_length 21

    #define fl_status_string_signal_reserved_64 "f_signal_reserved_64"
    #define fl_status_string_signal_reserved_64_length 21
  #endif // _di_fl_status_signals_

  #ifndef _di_fl_status_basic_
    #define fl_status_string_none "f_none"
    #define fl_status_string_none_length 7

    #define fl_status_string_maybe "f_maybe"
    #define fl_status_string_maybe_length 8

    #define fl_status_string_dummy "f_dummy"
    #define fl_status_string_dummy_length 8

    #define fl_status_string_warn "f_warn"
    #define fl_status_string_warn_length 7

    #define fl_status_string_critical "f_critical"
    #define fl_status_string_critical_length 11

    #define fl_status_string_unknown "f_unknown"
    #define fl_status_string_unknown_length 10

    #define fl_status_string_unsupported "f_unsupported"
    #define fl_status_string_unsupported_length 14

    #define fl_status_string_no_data "f_no_data"
    #define fl_status_string_no_data_length 10

    #define fl_status_string_out_of_memory "f_out_of_memory"
    #define fl_status_string_out_of_memory_length 16

    #define fl_status_string_input_error "f_error_input"
    #define fl_status_string_input_error_length 14

    #define fl_status_string_output_error "f_error_output"
    #define fl_status_string_output_error_length 15

    #define fl_status_string_input_output_error "f_error_input_output"
    #define fl_status_string_input_output_error_length 21

    #define fl_status_string_does_not_exist "f_does_not_exist"
    #define fl_status_string_does_not_exist_length 17

    #define fl_status_string_not_connected "f_not_connected"
    #define fl_status_string_not_connected_length 16

    #define fl_status_string_failure "f_failure"
    #define fl_status_string_failure_length 10

    #define fl_status_string_interrupted "f_interrupted"
    #define fl_status_string_interrupted_length 14

    #define fl_status_string_loop "f_loop"
    #define fl_status_string_loop_length 7

    #define fl_status_string_incomplete "f_incomplete"
    #define fl_status_string_incomplete_length 13
  #endif // _di_fl_status_basic_

  #ifndef _di_fl_status_invalid_
    #define fl_status_string_invalid "f_invalid"
    #define fl_status_string_invalid_length 10

    #define fl_status_string_invalid_name "f_invalid_name"
    #define fl_status_string_invalid_name_length 15

    #define fl_status_string_invalid_parameter "f_invalid_parameter"
    #define fl_status_string_invalid_parameter_length 20

    #define fl_status_string_invalid_syntax "f_invalid_syntax"
    #define fl_status_string_invalid_syntax_length 17

    #define fl_status_string_invalid_data "f_invalid_data"
    #define fl_status_string_invalid_data_length 15

    #define fl_status_string_invalid_file "f_invalid_file"
    #define fl_status_string_invalid_file_length 15

    #define fl_status_string_invalid_directory "f_invalid_directory"
    #define fl_status_string_invalid_directory_length 20

    #define fl_status_string_invalid_descriptor "f_invalid_descriptor"
    #define fl_status_string_invalid_descriptor_length 21

    #define fl_status_string_invalid_socket "f_invalid_socket"
    #define fl_status_string_invalid_socket_length 17

    #define fl_status_string_invalid_device "f_invalid_device"
    #define fl_status_string_invalid_device_length 17

    #define fl_status_string_invalid_link "f_invalid_link"
    #define fl_status_string_invalid_link_length 15

    #define fl_status_string_invalid_pipe "f_invalid_pipe"
    #define fl_status_string_invalid_pipe_length 15

    #define fl_status_string_invalid_address "f_invalid_address"
    #define fl_status_string_invalid_address_length 18

    #define fl_status_string_invalid_port "f_invalid_port"
    #define fl_status_string_invalid_port_length 15

    #define fl_status_string_invalid_value "f_invalid_value"
    #define fl_status_string_invalid_value_length 16

    #define fl_status_string_invalid_buffer "f_invalid_buffer"
    #define fl_status_string_invalid_buffer_length 17

    #define fl_status_string_invalid_process "f_invalid_process"
    #define fl_status_string_invalid_process_length 18

    #define fl_status_string_invalid_utf "f_invalid_utf"
    #define fl_status_string_invalid_utf_length 14

    #define fl_status_string_invalid_on_eof "f_invalid_on_eof"
    #define fl_status_string_invalid_on_eof_length 17

    #define fl_status_string_invalid_on_eol "f_invalid_on_eol"
    #define fl_status_string_invalid_on_eol_length 17

    #define fl_status_string_invalid_on_eos "f_invalid_on_eos"
    #define fl_status_string_invalid_on_eos_length 17

    #define fl_status_string_invalid_on_stop "f_invalid_on_stop"
    #define fl_status_string_invalid_on_stop_length 18
  #endif // _di_fl_status_invalid_

  #ifndef _di_fl_status_busy_
    #define fl_status_string_busy "f_busy"
    #define fl_status_string_busy_length 7

    #define fl_status_string_busy_address "f_busy_address"
    #define fl_status_string_busy_address_length 15

    #define fl_status_string_busy_port "f_busy_port"
    #define fl_status_string_busy_port_length 12

    #define fl_status_string_busy_socket "f_busy_socket"
    #define fl_status_string_busy_socket_length 14

    #define fl_status_string_busy_device "f_busy_device"
    #define fl_status_string_busy_device_length 14

    #define fl_status_string_busy_pipe "f_busy_pipe"
    #define fl_status_string_busy_pipe_length 12

    #define fl_status_string_busy_buffer "f_busy_buffer"
    #define fl_status_string_busy_buffer_length 14

    #define fl_status_string_busy_process "f_busy_process"
    #define fl_status_string_busy_process_length 15
  #endif // _di_fl_status_busy_

  #ifndef _di_fl_status_unavailable_
    #define fl_status_string_unavailable "f_unavailable"
    #define fl_status_string_unavailable_length 14

    #define fl_status_string_unavailable_address "f_unavailable_address"
    #define fl_status_string_unavailable_address_length 22

    #define fl_status_string_unavailable_port "f_unavailable_port"
    #define fl_status_string_unavailable_port_length 19

    #define fl_status_string_unavailable_socket "f_unavailable_socket"
    #define fl_status_string_unavailable_socket_length 21

    #define fl_status_string_unavailable_device "f_unavailable_device"
    #define fl_status_string_unavailable_device_length 21

    #define fl_status_string_unavailable_pipe "f_unavailable_pipe"
    #define fl_status_string_unavailable_pipe_length 19

    #define fl_status_string_unavailable_buffer "f_unavailable_buffer"
    #define fl_status_string_unavailable_buffer_length 21

    #define fl_status_string_unavailable_process "f_unavailable_process"
    #define fl_status_string_unavailable_process_length 22
  #endif // _di_fl_status_unavailable_

  #ifndef _di_fl_status_digits_
    #define fl_status_string_underflow "f_number_underflow"
    #define fl_status_string_underflow_length 19

    #define fl_status_string_overflow "f_number_overflow"
    #define fl_status_string_overflow_length 18

    #define fl_status_string_divide_by_zero "f_number_divide_by_zero"
    #define fl_status_string_divide_by_zero_length 24

    #define fl_status_string_negative_number "f_number_negative"
    #define fl_status_string_negative_number_length 18

    #define fl_status_string_positive_number "f_number_positive"
    #define fl_status_string_positive_number_length 18

    #define fl_status_string_zero_number "f_number_zero"
    #define fl_status_string_zero_number_length 14

    #define fl_status_string_decimal_number "f_number_decimal"
    #define fl_status_string_decimal_number_length 17

    #define fl_status_string_whole_number "f_number_whole"
    #define fl_status_string_whole_number_length 15

    #define fl_status_string_invalid_number "f_number_invalid"
    #define fl_status_string_invalid_number_length 17
  #endif // _di_fl_status_digits_

  #ifndef _di_fl_status_buffers_
    #define fl_status_string_no_data_on_eof "f_no_data_on_eof"
    #define fl_status_string_no_data_on_eof_length 17

    #define fl_status_string_no_data_on_eol "f_no_data_on_eol"
    #define fl_status_string_no_data_on_eol_length 17

    #define fl_status_string_no_data_on_eos "f_no_data_on_eos"
    #define fl_status_string_no_data_on_eos_length 17

    #define fl_status_string_none_on_eof "f_none_on_eof"
    #define fl_status_string_none_on_eof_length 14

    #define fl_status_string_no_data_on_stop "f_no_data_on_stop"
    #define fl_status_string_no_data_on_stop_length 18

    #define fl_status_string_none_on_eol "f_none_on_eol"
    #define fl_status_string_none_on_eol_length 14

    #define fl_status_string_none_on_eos "f_none_on_eos"
    #define fl_status_string_none_on_eos_length 14

    #define fl_status_string_none_on_stop "f_none_on_stop"
    #define fl_status_string_none_on_stop_length 15

    #define fl_status_string_error_on_eof "f_error_on_eof"
    #define fl_status_string_error_on_eof_length 15

    #define fl_status_string_error_on_eol "f_error_on_eol"
    #define fl_status_string_error_on_eol_length 15

    #define fl_status_string_error_on_eos "f_error_on_eos"
    #define fl_status_string_error_on_eos_length 15

    #define fl_status_string_error_on_stop "f_error_on_stop"
    #define fl_status_string_error_on_stop_length 16

    #define fl_status_string_buffer_too_small "f_buffer_too_small"
    #define fl_status_string_buffer_too_small_length 19

    #define fl_status_string_buffer_too_large "f_buffer_too_large"
    #define fl_status_string_buffer_too_large_length 19

    #define fl_status_string_string_too_small "f_string_too_small"
    #define fl_status_string_string_too_small_length 19

    #define fl_status_string_string_too_large "f_string_too_large"
    #define fl_status_string_string_too_large_length 19

    #define fl_status_string_unterminated "f_unterminated"
    #define fl_status_string_unterminated_length 15

    #define fl_status_string_unterminated_on_eof "f_unterminated_on_eof"
    #define fl_status_string_unterminated_on_eof_length 22

    #define fl_status_string_unterminated_on_eol "f_unterminated_on_eol"
    #define fl_status_string_unterminated_on_eol_length 22

    #define fl_status_string_unterminated_on_eos "f_unterminated_on_eos"
    #define fl_status_string_unterminated_on_eos_length 22

    #define fl_status_string_unterminated_on_stop "f_unterminated_on_stop"
    #define fl_status_string_unterminated_on_stop_length 23

    #define fl_status_string_unterminated_group "f_unterminated_group"
    #define fl_status_string_unterminated_group_length 21

    #define fl_status_string_unterminated_group_on_eof "f_unterminated_group_on_eof"
    #define fl_status_string_unterminated_group_on_eof_length 28

    #define fl_status_string_unterminated_group_on_eol "f_unterminated_group_on_eol"
    #define fl_status_string_unterminated_group_on_eol_length 28

    #define fl_status_string_unterminated_group_on_eos "f_unterminated_group_on_eos"
    #define fl_status_string_unterminated_group_on_eos_length 28

    #define fl_status_string_unterminated_group_on_stop "f_unterminated_group_on_stop"
    #define fl_status_string_unterminated_group_on_stop_length 29

    #define fl_status_string_unterminated_nest "f_unterminated_nest"
    #define fl_status_string_unterminated_nest_length 20

    #define fl_status_string_unterminated_nest_on_eof "f_unterminated_nest_on_eof"
    #define fl_status_string_unterminated_nest_on_eof_length 27

    #define fl_status_string_unterminated_nest_on_eol "f_unterminated_nest_on_eol"
    #define fl_status_string_unterminated_nest_on_eol_length 27

    #define fl_status_string_unterminated_nest_on_eos "f_unterminated_nest_on_eos"
    #define fl_status_string_unterminated_nest_on_eos_length 27

    #define fl_status_string_unterminated_nest_on_stop "f_unterminated_nest_on_stop"
    #define fl_status_string_unterminated_nest_on_stop_length 28

    #define fl_status_string_incomplete_utf "f_incomplete_utf"
    #define fl_status_string_incomplete_utf_length 17

    #define fl_status_string_incomplete_utf_on_eof "f_incomplete_utf_on_eof"
    #define fl_status_string_incomplete_utf_on_eof_length 24

    #define fl_status_string_incomplete_utf_on_eol "f_incomplete_utf_on_eol"
    #define fl_status_string_incomplete_utf_on_eol_length 24

    #define fl_status_string_incomplete_utf_on_eos "f_incomplete_utf_on_eos"
    #define fl_status_string_incomplete_utf_on_eos_length 24

    #define fl_status_string_incomplete_utf_on_stop "f_incomplete_utf_on_stop"
    #define fl_status_string_incomplete_utf_on_stop_length 25
  #endif // _di_fl_status_buffers_

  #ifndef _di_fl_status_allocation_
    #define fl_status_string_allocation_error "f_error_allocation"
    #define fl_status_string_allocation_error_length 19

    #define fl_status_string_reallocation_error "f_error_reallocation"
    #define fl_status_string_reallocation_error_length 21

    #define fl_status_string_deallocation_error "f_error_deallocation"
    #define fl_status_string_deallocation_error_length 21
  #endif // _di_fl_status_allocation_

  #ifndef _di_fl_status_fork_
    #define fl_status_string_fork_failed "f_fork_failed"
    #define fl_status_string_fork_failed_length 14

    #define fl_status_string_too_many_processes "f_too_many_processes"
    #define fl_status_string_too_many_processes_length 21
  #endif // _di_fl_status_fork_

  #ifndef _di_fl_status_file_
    #define fl_status_string_file_seek_error "f_file_error_seek"
    #define fl_status_string_file_seek_error_length 18

    #define fl_status_string_file_read_error "f_file_error_read"
    #define fl_status_string_file_read_error_length 18

    #define fl_status_string_file_write_error "f_file_error_write"
    #define fl_status_string_file_write_error_length 19

    #define fl_status_string_file_flush_error "f_file_error_flush"
    #define fl_status_string_file_flush_error_length 19

    #define fl_status_string_file_purge_error "f_file_error_purge"
    #define fl_status_string_file_purge_error_length 19

    #define fl_status_string_file_open_error "f_file_error_open"
    #define fl_status_string_file_open_error_length 18

    #define fl_status_string_file_close_error "f_file_error_close"
    #define fl_status_string_file_close_error_length 19

    #define fl_status_string_file_synchronize_error "f_file_error_synchronize"
    #define fl_status_string_file_synchronize_error_length 25

    #define fl_status_string_file_descriptor_error "f_file_error_descriptor"
    #define fl_status_string_file_descriptor_error_length 24

    #define fl_status_string_file_not_found "f_file_not_found"
    #define fl_status_string_file_not_found_length 17

    #define fl_status_string_file_found "f_file_found"
    #define fl_status_string_file_found_length 13

    #define fl_status_string_file_is_empty "f_file_is_empty"
    #define fl_status_string_file_is_empty_length 16

    #define fl_status_string_file_not_open "f_file_not_open"
    #define fl_status_string_file_not_open_length 16

    #define fl_status_string_file_allocation_error "f_file_error_allocation"
    #define fl_status_string_file_allocation_error_length 24

    #define fl_status_string_file_reallocation_error "f_file_error_reallocation"
    #define fl_status_string_file_reallocation_error_length 26

    #define fl_status_string_file_deallocation_error "f_file_error_deallocation"
    #define fl_status_string_file_deallocation_error_length 26

    #define fl_status_string_file_stat_error "f_file_error_stat"
    #define fl_status_string_file_stat_error_length 18

    #define fl_status_string_file_error "f_file_error"
    #define fl_status_string_file_error_length 13

    #define fl_status_string_file_not_utf "f_file_not_utf"
    #define fl_status_string_file_not_utf_length 15
  #endif // _di_fl_status_file_

  #ifndef _di_fl_status_directory_
    #define fl_status_string_directory_read_error "f_directory_error_read"
    #define fl_status_string_directory_read_error_length 23

    #define fl_status_string_directory_write_error "f_directory_error_write"
    #define fl_status_string_directory_write_error_length 24

    #define fl_status_string_directory_flush_error "f_directory_error_flush"
    #define fl_status_string_directory_flush_error_length 24

    #define fl_status_string_directory_purge_error "f_directory_error_purge"
    #define fl_status_string_directory_purge_error_length 24

    #define fl_status_string_directory_open_error "f_directory_error_open"
    #define fl_status_string_directory_open_error_length 23

    #define fl_status_string_directory_close_error "f_directory_error_close"
    #define fl_status_string_directory_close_error_length 24

    #define fl_status_string_directory_synchronize_error "f_directory_error_synchronize"
    #define fl_status_string_directory_synchronize_error_length 30

    #define fl_status_string_directory_descriptor_error "f_directory_error_descriptor"
    #define fl_status_string_directory_descriptor_error_length 29

    #define fl_status_string_directory_not_found "f_directory_not_found"
    #define fl_status_string_directory_not_found_length 22

    #define fl_status_string_directory_is_empty "f_directory_is_empty"
    #define fl_status_string_directory_is_empty_length 21

    #define fl_status_string_directory_not_open "f_directory_not_open"
    #define fl_status_string_directory_not_open_length 21

    #define fl_status_string_directory_allocation_error "f_directory_error_allocation"
    #define fl_status_string_directory_allocation_error_length 29

    #define fl_status_string_directory_reallocation_error "f_directory_error_reallocation"
    #define fl_status_string_directory_reallocation_error_length 31

    #define fl_status_string_directory_error "f_directory_error"
    #define fl_status_string_directory_error_length 18

    #define fl_status_string_directory_not_utf "f_directory_not_utf"
    #define fl_status_string_directory_not_utf_length 20
  #endif // _di_fl_status_directory_

  #ifndef _di_fl_status_socket_
    #define fl_status_string_socket_connection_client_error "f_socket_error_connection_client"
    #define fl_status_string_socket_connection_client_error_length 33

    #define fl_status_string_socket_connection_target_error "f_socket_error_connection_target"
    #define fl_status_string_socket_connection_target_error_length 33

    #define fl_status_string_socket_receive_error "f_socket_error_receive"
    #define fl_status_string_socket_receive_error_length 23

    #define fl_status_string_socket_send_error "f_socket_error_send"
    #define fl_status_string_socket_send_error_length 20
  #endif // _di_fl_status_socket_

  #ifndef _di_fl_status_non_
    #define fl_status_string_less_than "f_less_than"
    #define fl_status_string_less_than_length 12

    #define fl_status_string_equal_to "f_equal_to"
    #define fl_status_string_equal_to_length 11

    #define fl_status_string_not_equal_to "f_not_equal_to"
    #define fl_status_string_not_equal_to_length 15

    #define fl_status_string_greater_than "f_greater_than"
    #define fl_status_string_greater_than_length 15
  #endif // _di_fl_status_non_

  #ifndef _di_fl_status_access_denied_
    #define fl_status_string_access_denied "f_access_denied"
    #define fl_status_string_access_denied_length 16

    #define fl_status_string_access_denied_user "f_access_denied_user"
    #define fl_status_string_access_denied_user_length 21

    #define fl_status_string_access_denied_group "f_access_denied_group"
    #define fl_status_string_access_denied_group_length 22

    #define fl_status_string_access_denied_world "f_access_denied_world"
    #define fl_status_string_access_denied_world_length 22

    #define fl_status_string_access_denied_read "f_access_denied_read"
    #define fl_status_string_access_denied_read_length 21

    #define fl_status_string_access_denied_write "f_access_denied_write"
    #define fl_status_string_access_denied_write_length 22

    #define fl_status_string_access_denied_execute "f_access_denied_execute"
    #define fl_status_string_access_denied_execute_length 24

    #define fl_status_string_access_denied_super "f_access_denied_super"
    #define fl_status_string_access_denied_super_length 22
  #endif // _di_fl_status_access_denied_

  #define fl_status_string_status_code_last "f_status_code_last"
  #define fl_status_string_status_code_last_length 18
#endif // _di_fl_status_string_

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
 *   f_none on success.
 *   f_invalid_data (with error bit) if there status is unknown.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_status_to_string_
  extern f_return_status fl_status_to_string(const f_status code, f_string *string);
#endif // _di_fl_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_status_h

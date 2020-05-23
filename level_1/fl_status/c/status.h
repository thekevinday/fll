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
    #define fl_status_string_false "F_false"
    #define fl_status_string_false_length 7

    #define fl_status_string_true "F_true"
    #define fl_status_string_true_length 6
  #endif // _di_fl_status_booleans_

  #ifndef _di_fl_status_signals_
    #define fl_status_string_signal_hangup "F_signal_hangup"
    #define fl_status_string_signal_hangup_length 15

    #define fl_status_string_signal_interrupt "F_signal_interrupt"
    #define fl_status_string_signal_interrupt_length 18

    #define fl_status_string_signal_quit "F_signal_quit"
    #define fl_status_string_signal_quit_length 13

    #define fl_status_string_signal_illegal "F_signal_illegal"
    #define fl_status_string_signal_illegal_length 16

    #define fl_status_string_signal_trap "F_signal_trap"
    #define fl_status_string_signal_trap_length 13

    #define fl_status_string_signal_abort "F_signal_abort"
    #define fl_status_string_signal_abort_length 14

    #define fl_status_string_signal_bus_error "F_signal_bus_error"
    #define fl_status_string_signal_bus_error_length 17

    #define fl_status_string_signal_floating_point_exception "F_signal_floating_point_exception"
    #define fl_status_string_signal_floating_point_exception_length 33

    #define fl_status_string_signal_kill "F_signal_kill"
    #define fl_status_string_signal_kill_length 13

    #define fl_status_string_signal_user_1 "F_signal_user_1"
    #define fl_status_string_signal_user_1_length 15

    #define fl_status_string_signal_segmentation_fault "F_signal_segmentation_fault"
    #define fl_status_string_signal_segmentation_fault_length 27

    #define fl_status_string_signal_user_2 "F_signal_user_2"
    #define fl_status_string_signal_user_2_length 15

    #define fl_status_string_signal_broken_pipe "F_signal_broken_pipe"
    #define fl_status_string_signal_broken_pipe_length 20

    #define fl_status_string_signal_alarm_clock "F_signal_alarm_clock"
    #define fl_status_string_signal_alarm_clock_length 20

    #define fl_status_string_signal_termination "F_signal_termination"
    #define fl_status_string_signal_termination_length 20

    #define fl_status_string_signal_stack_fault "F_signal_stack_fault"
    #define fl_status_string_signal_stack_fault_length 20

    #define fl_status_string_signal_child "F_signal_child"
    #define fl_status_string_signal_child_length 14

    #define fl_status_string_signal_continue "F_signal_continue"
    #define fl_status_string_signal_continue_length 17

    #define fl_status_string_signal_stop "F_signal_stop"
    #define fl_status_string_signal_stop_length 13

    #define fl_status_string_signal_keyboard_stop "F_signal_keyboard_stop"
    #define fl_status_string_signal_keyboard_stop_length 22

    #define fl_status_string_signal_tty_in "F_signal_tty_in"
    #define fl_status_string_signal_tty_in_length 15

    #define fl_status_string_signal_tty_out "F_signal_tty_out"
    #define fl_status_string_signal_tty_out_length 16

    #define fl_status_string_signal_urgent "F_signal_urgent"
    #define fl_status_string_signal_urgent_length 15

    #define fl_status_string_signal_cpu_limit "F_signal_cpu_limit"
    #define fl_status_string_signal_cpu_limit_length 18

    #define fl_status_string_signal_file_size_limit "F_signal_file_size_limit"
    #define fl_status_string_signal_file_size_limit_length 24

    #define fl_status_string_signal_virtual_alarm_clock "F_signal_virtual_alarm_clock"
    #define fl_status_string_signal_virtual_alarm_clock_length 28

    #define fl_status_string_signal_profile_alarm_clock "F_signal_profile_alarm_clock"
    #define fl_status_string_signal_profile_alarm_clock_length 28

    #define fl_status_string_signal_window_size_change "F_signal_window_size_change"
    #define fl_status_string_signal_window_size_change_length 27

    #define fl_status_string_signal_pollable_event "F_signal_pollable_event"
    #define fl_status_string_signal_pollable_event_length 23

    #define fl_status_string_signal_power_failure "F_signal_power_failure"
    #define fl_status_string_signal_power_failure_length 22

    #define fl_status_string_signal_bad_system_call "F_signal_bad_system_call"
    #define fl_status_string_signal_bad_system_call_length 24

    #define fl_status_string_signal_reserved_32 "F_signal_reserved_32"
    #define fl_status_string_signal_reserved_32_length 20

    #define fl_status_string_signal_reserved_33 "F_signal_reserved_33"
    #define fl_status_string_signal_reserved_33_length 20

    #define fl_status_string_signal_reserved_34 "F_signal_reserved_34"
    #define fl_status_string_signal_reserved_34_length 20

    #define fl_status_string_signal_reserved_35 "F_signal_reserved_35"
    #define fl_status_string_signal_reserved_35_length 20

    #define fl_status_string_signal_reserved_36 "F_signal_reserved_36"
    #define fl_status_string_signal_reserved_36_length 20

    #define fl_status_string_signal_reserved_37 "F_signal_reserved_37"
    #define fl_status_string_signal_reserved_37_length 20

    #define fl_status_string_signal_reserved_38 "F_signal_reserved_38"
    #define fl_status_string_signal_reserved_38_length 20

    #define fl_status_string_signal_reserved_39 "F_signal_reserved_39"
    #define fl_status_string_signal_reserved_39_length 20

    #define fl_status_string_signal_reserved_40 "F_signal_reserved_40"
    #define fl_status_string_signal_reserved_40_length 20

    #define fl_status_string_signal_reserved_41 "F_signal_reserved_41"
    #define fl_status_string_signal_reserved_41_length 20

    #define fl_status_string_signal_reserved_42 "F_signal_reserved_42"
    #define fl_status_string_signal_reserved_42_length 20

    #define fl_status_string_signal_reserved_43 "F_signal_reserved_43"
    #define fl_status_string_signal_reserved_43_length 20

    #define fl_status_string_signal_reserved_44 "F_signal_reserved_44"
    #define fl_status_string_signal_reserved_44_length 20

    #define fl_status_string_signal_reserved_45 "F_signal_reserved_45"
    #define fl_status_string_signal_reserved_45_length 20

    #define fl_status_string_signal_reserved_46 "F_signal_reserved_46"
    #define fl_status_string_signal_reserved_46_length 20

    #define fl_status_string_signal_reserved_47 "F_signal_reserved_47"
    #define fl_status_string_signal_reserved_47_length 20

    #define fl_status_string_signal_reserved_48 "F_signal_reserved_48"
    #define fl_status_string_signal_reserved_48_length 20

    #define fl_status_string_signal_reserved_49 "F_signal_reserved_49"
    #define fl_status_string_signal_reserved_49_length 20

    #define fl_status_string_signal_reserved_50 "F_signal_reserved_50"
    #define fl_status_string_signal_reserved_50_length 20

    #define fl_status_string_signal_reserved_51 "F_signal_reserved_51"
    #define fl_status_string_signal_reserved_51_length 20

    #define fl_status_string_signal_reserved_52 "F_signal_reserved_52"
    #define fl_status_string_signal_reserved_52_length 20

    #define fl_status_string_signal_reserved_53 "F_signal_reserved_53"
    #define fl_status_string_signal_reserved_53_length 20

    #define fl_status_string_signal_reserved_54 "F_signal_reserved_54"
    #define fl_status_string_signal_reserved_54_length 20

    #define fl_status_string_signal_reserved_55 "F_signal_reserved_55"
    #define fl_status_string_signal_reserved_55_length 20

    #define fl_status_string_signal_reserved_56 "F_signal_reserved_56"
    #define fl_status_string_signal_reserved_56_length 20

    #define fl_status_string_signal_reserved_57 "F_signal_reserved_57"
    #define fl_status_string_signal_reserved_57_length 20

    #define fl_status_string_signal_reserved_58 "F_signal_reserved_58"
    #define fl_status_string_signal_reserved_58_length 20

    #define fl_status_string_signal_reserved_59 "F_signal_reserved_59"
    #define fl_status_string_signal_reserved_59_length 20

    #define fl_status_string_signal_reserved_60 "F_signal_reserved_60"
    #define fl_status_string_signal_reserved_60_length 20

    #define fl_status_string_signal_reserved_61 "F_signal_reserved_61"
    #define fl_status_string_signal_reserved_61_length 20

    #define fl_status_string_signal_reserved_62 "F_signal_reserved_62"
    #define fl_status_string_signal_reserved_62_length 20

    #define fl_status_string_signal_reserved_63 "F_signal_reserved_63"
    #define fl_status_string_signal_reserved_63_length 20

    #define fl_status_string_signal_reserved_64 "F_signal_reserved_64"
    #define fl_status_string_signal_reserved_64_length 20
  #endif // _di_fl_status_signals_

  #ifndef _di_fl_status_basic_
    #define fl_status_string_none "F_none"
    #define fl_status_string_none_length 6

    #define fl_status_string_maybe "F_maybe"
    #define fl_status_string_maybe_length 7

    #define fl_status_string_dummy "F_dummy"
    #define fl_status_string_dummy_length 7

    #define fl_status_string_warn "F_warn"
    #define fl_status_string_warn_length 6

    #define fl_status_string_block "F_block"
    #define fl_status_string_block_length 7

    #define fl_status_string_critical "F_critical"
    #define fl_status_string_critical_length 10

    #define fl_status_string_unknown "F_unknown"
    #define fl_status_string_unknown_length 9

    #define fl_status_string_unsupported "F_unsupported"
    #define fl_status_string_unsupported_length 13

    #define fl_status_string_no_data "F_data_not"
    #define fl_status_string_no_data_length 10

    #define fl_status_string_no_space "F_space_not"
    #define fl_status_string_no_space_length 11

    #define fl_status_string_bound_out "F_bound_out"
    #define fl_status_string_bound_out_length 11

    #define fl_status_string_memory_out "F_memory_out"
    #define fl_status_string_memory_out_length 12

    #define fl_status_string_prohibited "F_prohibited"
    #define fl_status_string_prohibited_length 12

    #define fl_status_string_read_only "F_read_only"
    #define fl_status_string_read_only_length 11

    #define fl_status_string_input "F_input"
    #define fl_status_string_input_length 7

    #define fl_status_string_output "F_output"
    #define fl_status_string_output_length 8

    #define fl_status_string_input_output "F_input_output"
    #define fl_status_string_input_output_length 14

    #define fl_status_string_exist_not "F_exist_not"
    #define fl_status_string_exist_not_length 11

    #define fl_status_string_connected_not "F_connected_not"
    #define fl_status_string_connected_not_length 15

    #define fl_status_string_failure "F_failure"
    #define fl_status_string_failure_length 9

    #define fl_status_string_interrupted "F_interrupted"
    #define fl_status_string_interrupted_length 13

    #define fl_status_string_loop "F_loop"
    #define fl_status_string_loop_length 6

    #define fl_status_string_incomplete "F_incomplete"
    #define fl_status_string_incomplete_length 12

    #define fl_status_string_write_only "F_write_only"
    #define fl_status_string_write_only_length 12
  #endif // _di_fl_status_basic_

  #ifndef _di_fl_status_invalid_
    #define fl_status_string_invalid "F_invalid"
    #define fl_status_string_length 9

    #define fl_status_string_name "F_name"
    #define fl_status_string_name_length 6

    #define fl_status_string_parameter "F_parameter"
    #define fl_status_string_parameter_length 11

    #define fl_status_string_syntax "F_syntax"
    #define fl_status_string_syntax_length 8

    #define fl_status_string_data "F_data"
    #define fl_status_string_data_length 6

    #define fl_status_string_descriptor "F_descriptor"
    #define fl_status_string_descriptor_length 12

    #define fl_status_string_socket "F_socket"
    #define fl_status_string_socket_length 8

    #define fl_status_string_device "F_device"
    #define fl_status_string_device_length 8

    #define fl_status_string_link "F_link"
    #define fl_status_string_link_length 6

    #define fl_status_string_pipe "F_pipe"
    #define fl_status_string_pipe_length 6

    #define fl_status_string_address "F_address"
    #define fl_status_string_address_length 9

    #define fl_status_string_port "F_port"
    #define fl_status_string_port_length 6

    #define fl_status_string_value "F_value"
    #define fl_status_string_value_length 7

    #define fl_status_string_buffer "F_buffer"
    #define fl_status_string_buffer_length 8

    #define fl_status_string_process "F_process"
    #define fl_status_string_process_length 9

    #define fl_status_string_utf "F_utf"
    #define fl_status_string_utf_length 5

    #define fl_status_string_eof "F_eof"
    #define fl_status_string_eof_length 5

    #define fl_status_string_eol "F_eol"
    #define fl_status_string_eol_length 5

    #define fl_status_string_eos "F_eos"
    #define fl_status_string_eos_length 5

    #define fl_status_string_stop "F_stop"
    #define fl_status_string_stop_length 6
  #endif // _di_fl_status_invalid_

  #ifndef _di_fl_status_busy_
    #define fl_status_string_busy "F_busy"
    #define fl_status_string_busy_length 6

    #define fl_status_string_busy_address "F_busy_address"
    #define fl_status_string_busy_address_length 14

    #define fl_status_string_busy_port "F_busy_port"
    #define fl_status_string_busy_port_length 11

    #define fl_status_string_busy_socket "F_busy_socket"
    #define fl_status_string_busy_socket_length 13

    #define fl_status_string_busy_device "F_busy_device"
    #define fl_status_string_busy_device_length 13

    #define fl_status_string_busy_pipe "F_busy_pipe"
    #define fl_status_string_busy_pipe_length 11

    #define fl_status_string_busy_buffer "F_busy_buffer"
    #define fl_status_string_busy_buffer_length 13

    #define fl_status_string_busy_process "F_busy_process"
    #define fl_status_string_busy_process_length 14
  #endif // _di_fl_status_busy_

  #ifndef _di_fl_status_unavailable_
    #define fl_status_string_unavailable "F_unavailable"
    #define fl_status_string_unavailable_length 13

    #define fl_status_string_unavailable_address "F_unavailable_address"
    #define fl_status_string_unavailable_address_length 21

    #define fl_status_string_unavailable_port "F_unavailable_port"
    #define fl_status_string_unavailable_port_length 18

    #define fl_status_string_unavailable_socket "F_unavailable_socket"
    #define fl_status_string_unavailable_socket_length 20

    #define fl_status_string_unavailable_device "F_unavailable_device"
    #define fl_status_string_unavailable_device_length 20

    #define fl_status_string_unavailable_pipe "F_unavailable_pipe"
    #define fl_status_string_unavailable_pipe_length 18

    #define fl_status_string_unavailable_buffer "F_unavailable_buffer"
    #define fl_status_string_unavailable_buffer_length 20

    #define fl_status_string_unavailable_process "F_unavailable_process"
    #define fl_status_string_unavailable_process_length 21
  #endif // _di_fl_status_unavailable_

  #ifndef _di_fl_status_digits_
    #define fl_status_string_underflow "F_number_underflow"
    #define fl_status_string_underflow_length 18

    #define fl_status_string_overflow "F_number_overflow"
    #define fl_status_string_overflow_length 17

    #define fl_status_string_divide_by_zero "F_number_divide_by_zero"
    #define fl_status_string_divide_by_zero_length 23

    #define fl_status_string_negative_number "F_number_negative"
    #define fl_status_string_negative_number_length 17

    #define fl_status_string_positive_number "F_number_positive"
    #define fl_status_string_positive_number_length 17

    #define fl_status_string_zero_number "F_number_zero"
    #define fl_status_string_zero_number_length 13

    #define fl_status_string_decimal_number "F_number_decimal"
    #define fl_status_string_decimal_number_length 16

    #define fl_status_string_whole_number "F_number_whole"
    #define fl_status_string_whole_number_length 14

    #define fl_status_string_number "F_number_invalid"
    #define fl_status_string_number_length 16
  #endif // _di_fl_status_digits_

  #ifndef _di_fl_status_buffers_
    #define fl_status_string_data_no_eof "F_data_no_eof"
    #define fl_status_string_data_no_eof_length 13

    #define fl_status_string_data_no_eol "F_data_no_eol"
    #define fl_status_string_data_no_eol_length 13

    #define fl_status_string_data_no_eos "F_data_no_eos"
    #define fl_status_string_data_no_eos_length 13

    #define fl_status_string_none_eof "F_none_eof"
    #define fl_status_string_none_eof_length 10

    #define fl_status_string_data_no_stop "F_data_no_stop"
    #define fl_status_string_data_no_stop_length 14

    #define fl_status_string_data_no_block "F_data_block_no"
    #define fl_status_string_data_no_block_length 15

    #define fl_status_string_none_eol "F_none_eol"
    #define fl_status_string_none_eol_length 10

    #define fl_status_string_none_eos "F_none_eos"
    #define fl_status_string_none_eos_length 10

    #define fl_status_string_none_stop "F_none_stop"
    #define fl_status_string_none_stop_length 11

    #define fl_status_string_none_block "F_none_block"
    #define fl_status_string_none_block_length 12

    #define fl_status_string_eof "F_eof"
    #define fl_status_string_eof_length 5

    #define fl_status_string_eol "F_eol"
    #define fl_status_string_eol_length 5

    #define fl_status_string_error_on_eos "F_eos"
    #define fl_status_string_error_on_eos_length 5

    #define fl_status_string_stop "F_stop"
    #define fl_status_string_stop_length 6

    #define fl_status_string_block "F_block"
    #define fl_status_string_block_length 7

    #define fl_status_string_buffer_too_small "F_buffer_too_small"
    #define fl_status_string_buffer_too_small_length 18

    #define fl_status_string_buffer_too_large "F_buffer_too_large"
    #define fl_status_string_buffer_too_large_length 18

    #define fl_status_string_string_too_small "F_string_too_small"
    #define fl_status_string_string_too_small_length 18

    #define fl_status_string_string_too_large "F_string_too_large"
    #define fl_status_string_string_too_large_length 18

    #define fl_status_string_unterminated "F_unterminated"
    #define fl_status_string_unterminated_length 14

    #define fl_status_string_unterminated_eof "F_unterminated_eof"
    #define fl_status_string_unterminated_eof_length 18

    #define fl_status_string_unterminated_eol "F_unterminated_eol"
    #define fl_status_string_unterminated_eol_length 18

    #define fl_status_string_unterminated_eos "F_unterminated_eos"
    #define fl_status_string_unterminated_eos_length 18

    #define fl_status_string_unterminated_stop "F_unterminated_stop"
    #define fl_status_string_unterminated_stop_length 19

    #define fl_status_string_unterminated_block "F_unterminated_block"
    #define fl_status_string_unterminated_block_length 20

    #define fl_status_string_unterminated_group "F_unterminated_group"
    #define fl_status_string_unterminated_group_length 20

    #define fl_status_string_unterminated_group_on_eof "F_unterminated_group_eof"
    #define fl_status_string_unterminated_group_on_eof_length 24

    #define fl_status_string_unterminated_group_on_eol "F_unterminated_group_eol"
    #define fl_status_string_unterminated_group_on_eol_length 24

    #define fl_status_string_unterminated_group_on_eos "F_unterminated_group_eos"
    #define fl_status_string_unterminated_group_on_eos_length 24

    #define fl_status_string_unterminated_group_on_stop "F_unterminated_group_stop"
    #define fl_status_string_unterminated_group_on_stop_length 25

    #define fl_status_string_unterminated_group_on_block "F_unterminated_group_block"
    #define fl_status_string_unterminated_group_on_block_length 26

    #define fl_status_string_unterminated_nest "F_unterminated_nest"
    #define fl_status_string_unterminated_nest_length 19

    #define fl_status_string_unterminated_nest_eof "F_unterminated_nest_eof"
    #define fl_status_string_unterminated_nest_eof_length 23

    #define fl_status_string_unterminated_nest_eol "F_unterminated_nest_eol"
    #define fl_status_string_unterminated_nest_eol_length 23

    #define fl_status_string_unterminated_nest_eos "F_unterminated_nest_eos"
    #define fl_status_string_unterminated_nest_eos_length 23

    #define fl_status_string_unterminated_nest_stop "F_unterminated_nest_stop"
    #define fl_status_string_unterminated_nest_stop_length 24

    #define fl_status_string_unterminated_nest_block "F_unterminated_nest_block"
    #define fl_status_string_unterminated_nest_block_length 25

    #define fl_status_string_incomplete_utf "F_incomplete_utf"
    #define fl_status_string_incomplete_utf_length 16

    #define fl_status_string_incomplete_utf_on_eof "F_incomplete_utf_eof"
    #define fl_status_string_incomplete_utf_on_eof_length 20

    #define fl_status_string_incomplete_utf_on_eol "F_incomplete_utf_eol"
    #define fl_status_string_incomplete_utf_on_eol_length 20

    #define fl_status_string_incomplete_utf_on_eos "F_incomplete_utf_eos"
    #define fl_status_string_incomplete_utf_on_eos_length 20

    #define fl_status_string_incomplete_utf_on_stop "F_incomplete_utf_stop"
    #define fl_status_string_incomplete_utf_on_stop_length 21

    #define fl_status_string_incomplete_utf_on_block "F_incomplete_utf_block"
    #define fl_status_string_incomplete_utf_on_block_length 22
  #endif // _di_fl_status_buffers_

  #ifndef _di_fl_status_allocation_
    #define fl_status_string_memory_allocation   "F_memory_allocation"
    #define fl_status_string_memory_deallocation "F_memory_deallocation"
    #define fl_status_string_memory_reallocation "F_memory_reallocation"

    #define fl_status_string_memory_allocation_length   19
    #define fl_status_string_memory_deallocation_length 21
    #define fl_status_string_memory_reallocation_length 21

  #endif // _di_fl_status_allocation_

  #ifndef _di_fl_status_fork_
    #define fl_status_string_fork             "F_fork"
    #define fl_status_string_process_too_many "F_process_too_many"

    #define fl_status_string_fork_length             6
    #define fl_status_string_process_too_many_length 20
  #endif // _di_fl_status_fork_

  #ifndef _di_fl_status_file_
    #define fl_status_string_file "F_file"
    #define fl_status_string_file_length 6

    #define fl_status_string_file_closed "F_file_closed"
    #define fl_status_string_file_closed_length 13

    #define fl_status_string_file_seek "F_file_seek"
    #define fl_status_string_file_seek_length 11

    #define fl_status_string_file_read "F_file_read"
    #define fl_status_string_file_read_length 11

    #define fl_status_string_file_write "F_file_write"
    #define fl_status_string_file_write_length 12

    #define fl_status_string_file_flush "F_file_flush"
    #define fl_status_string_file_flush_length 12

    #define fl_status_string_file_purge "F_file_purge"
    #define fl_status_string_file_purge_length 12

    #define fl_status_string_file_open "F_file_open"
    #define fl_status_string_file_open_length 11

    #define fl_status_string_file_close "F_file_close"
    #define fl_status_string_file_close_length 12

    #define fl_status_string_file_synchronize "F_file_synchronize"
    #define fl_status_string_file_synchronize_length 18

    #define fl_status_string_file_descriptor "F_file_descriptor"
    #define fl_status_string_file_descriptor_length 17

    #define fl_status_string_file_found_not "F_file_found_not"
    #define fl_status_string_file_found_not_length 16

    #define fl_status_string_file_empty "F_file_empty"
    #define fl_status_string_file_empty_length 12

    #define fl_status_string_file_found "F_file_found"
    #define fl_status_string_file_found_length 12

    #define fl_status_string_file_type_block "F_file_type_block"
    #define fl_status_string_file_type_block_length 17

    #define fl_status_string_file_type_character "F_file_type_character"
    #define fl_status_string_file_type_character_length 21

    #define fl_status_string_file_type_directory "F_file_type_directory"
    #define fl_status_string_file_type_directory_length 21

    #define fl_status_string_file_type_file "F_file_type_file"
    #define fl_status_string_file_type_file_length 16

    #define fl_status_string_file_type_link "F_file_type_link"
    #define fl_status_string_file_type_link_length 16

    #define fl_status_string_file_type_pipe "F_file_type_pipe"
    #define fl_status_string_file_type_pipe_length 16

    #define fl_status_string_file_type_socket "F_file_type_socket"
    #define fl_status_string_file_type_socket_length 18

    #define fl_status_string_file_type_unknown "F_file_type_unknown"
    #define fl_status_string_file_type_unknown_length 19

    #define fl_status_string_file_open_not "F_file_open_not"
    #define fl_status_string_file_open_not_length 15

    #define fl_status_string_file_type_not_block "F_file_type_not_block"
    #define fl_status_string_file_type_not_block_length 21

    #define fl_status_string_file_type_not_character "F_file_type_not_character"
    #define fl_status_string_file_type_not_character_length 25

    #define fl_status_string_file_not_type_directory "F_file_type_not_directory"
    #define fl_status_string_file_not_type_directory_length 25

    #define fl_status_string_file_not_type_file "F_file_type_not_file"
    #define fl_status_string_file_not_type_file_length 20

    #define fl_status_string_file_not_type_link "F_file_type_not_link"
    #define fl_status_string_file_not_type_link_length 20

    #define fl_status_string_file_not_type_pipe "F_file_type_not_pipe"
    #define fl_status_string_file_not_type_pipe_length 20

    #define fl_status_string_file_not_type_socket "F_file_type_not_socket"
    #define fl_status_string_file_not_type_socket_length 22

    #define fl_status_string_file_not_type_unknown "F_file_type_not_unknown"
    #define fl_status_string_file_not_type_unknown_length 23

    #define fl_status_string_file_allocation "F_file_allocation"
    #define fl_status_string_file_allocation_length 17

    #define fl_status_string_file_reallocation "F_file_reallocation"
    #define fl_status_string_file_reallocation_length 19

    #define fl_status_string_file_deallocation "F_file_deallocation"
    #define fl_status_string_file_deallocation_length 19

    #define fl_status_string_file_stat "F_file_stat"
    #define fl_status_string_file_stat_length 11

    #define fl_status_string_file_not_utf "F_file_not_utf"
    #define fl_status_string_file_not_utf_length 14

    #define fl_status_string_file_descriptors_max "F_file_descriptors_max"
    #define fl_status_string_file_descriptors_max_length 22

    #define fl_status_string_file_open_max "F_file_open_max"
    #define fl_status_string_file_open_max_length 15

    #define fl_status_string_file_utf "F_file_utf"
    #define fl_status_string_file_utf_length 10
  #endif // _di_fl_status_file_

  #ifndef _di_f_status_filesystem_
    #define fl_status_string_filesystem_error "F_filesystem"
    #define fl_status_string_filesystem_error_length 18

    #define fl_status_string_filesystem_quota_blocks "F_filesystem_quota_blocks"
    #define fl_status_string_filesystem_quota_blocks_length 25

    #define fl_status_string_filesystem_quota_reached "F_filesystem_quota_reached"
    #define fl_status_string_filesystem_quota_reached_length 26
  #endif // _di_f_status_filesystem_

  #ifndef _di_fl_status_directory_
    #define fl_status_string_directory_closed "F_directory_closed"
    #define fl_status_string_directory_closed_length 18

    #define fl_status_string_directory_read "F_directory_read"
    #define fl_status_string_directory_read_length 16

    #define fl_status_string_directory_write "F_directory_write"
    #define fl_status_string_directory_write_length 17

    #define fl_status_string_directory_flush "F_directory_flush"
    #define fl_status_string_directory_flush_length 17

    #define fl_status_string_directory_link_max "F_directory_link_max"
    #define fl_status_string_directory_link_max_length 20

    #define fl_status_string_directory_purge "F_directory_purge"
    #define fl_status_string_directory_purge_length 17

    #define fl_status_string_directory_open "F_directory_open"
    #define fl_status_string_directory_open_length 16

    #define fl_status_string_directory_close "F_directory_close"
    #define fl_status_string_directory_close_length 17

    #define fl_status_string_directory_synchronize "F_directory_synchronize"
    #define fl_status_string_directory_synchronize_length 23

    #define fl_status_string_directory_descriptor "F_directory_descriptor"
    #define fl_status_string_directory_descriptor_length 22

    #define fl_status_string_directory_empty "F_directory_empty"
    #define fl_status_string_directory_empty_length 17

    #define fl_status_string_directory_found "F_directory_found"
    #define fl_status_string_directory_found_length 17

    #define fl_status_string_directory_not_found "F_directory_not_found"
    #define fl_status_string_directory_not_found_length 21

    #define fl_status_string_directory_not_open "F_directory_not_open"
    #define fl_status_string_directory_not_open_length 20

    #define fl_status_string_directory "F_directory"
    #define fl_status_string_directory_length 11

    #define fl_status_string_directory_not_utf "F_directory_utf_not"
    #define fl_status_string_directory_not_utf_length 19

    #define fl_status_string_directory_unsupported "F_directory_unsupported"
    #define fl_status_string_directory_unsupported_length 23

    #define fl_status_string_directory_stream "F_directory_stream"
    #define fl_status_string_directory_stream_length 18

    #define fl_status_string_directory_utf "F_directory_utf"
    #define fl_status_string_directory_utf_length 15
  #endif // _di_fl_status_directory_

  #ifndef _di_fl_status_socket_
    #define fl_status_string_socket_connection_client "F_socket_connection_client"
    #define fl_status_string_socket_connection_client_length 26

    #define fl_status_string_socket_connection_target "F_socket_connection_target"
    #define fl_status_string_socket_connection_target_length 26

    #define fl_status_string_socket_receive "F_socket_receive"
    #define fl_status_string_socket_receive_length 16

    #define fl_status_string_socket_send "F_socket_send"
    #define fl_status_string_socket_send_length 13
  #endif // _di_fl_status_socket_

  #ifndef _di_fl_status_non_
    #define fl_status_string_than_less "F_than_less"
    #define fl_status_string_than_less_length 11

    #define fl_status_string_equal_to "F_equal_to"
    #define fl_status_string_equal_to_length 10

    #define fl_status_string_equal_to_not "F_equal_to_not"
    #define fl_status_string_equal_to_not_length 14

    #define fl_status_string_than_greater "F_than_greater"
    #define fl_status_string_than_greater_length 14
  #endif // _di_fl_status_non_

  #ifndef _di_fl_status_access_denied_
    #define fl_status_string_access_denied "F_access_denied"
    #define fl_status_string_access_denied_length 15

    #define fl_status_string_access_denied_user "F_access_denied_user"
    #define fl_status_string_access_denied_user_length 20

    #define fl_status_string_access_denied_group "F_access_denied_group"
    #define fl_status_string_access_denied_group_length 21

    #define fl_status_string_access_denied_world "F_access_denied_world"
    #define fl_status_string_access_denied_world_length 21

    #define fl_status_string_access_denied_read "F_access_denied_read"
    #define fl_status_string_access_denied_read_length 20

    #define fl_status_string_access_denied_write "F_access_denied_write"
    #define fl_status_string_access_denied_write_length 21

    #define fl_status_string_access_denied_execute "F_access_denied_execute"
    #define fl_status_string_access_denied_execute_length 23

    #define fl_status_string_access_denied_super "F_access_denied_super"
    #define fl_status_string_access_denied_super_length 21
  #endif // _di_fl_status_access_denied_

  #define fl_status_string_status_code_last "F_status_code_last"
  #define fl_status_string_status_code_last_length 17
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
 *   F_none on success.
 *   F_data (with error bit) if there status is unknown.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_status_to_string_
  extern f_return_status fl_status_to_string(const f_status code, f_string *string);
#endif // _di_fl_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_status_h

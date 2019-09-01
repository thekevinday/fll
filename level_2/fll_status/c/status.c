#include <level_2/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_status_from_string_
  f_return_status fll_status_from_string(const f_string string, f_status *code) {
    #ifndef _di_level_1_parameter_checking_
      if (code == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    f_string_length length = strlen(string);

    if (length == 0) {
      return f_no_data;
    }

    // numbers are not valid status code strings.
    if ((status = f_is_digit(string[0])) == f_true) {
      return f_invalid_data;
    }

    if (f_status_is_error(status)) {
      return status;
    }

    #ifndef _di_fll_status_booleans_
      if (fl_string_compare(string, fl_status_string_false, length, fl_status_string_false_length) == f_equal_to) {
        *code = f_false;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_true, length, fl_status_string_true_length) == f_equal_to) {
        *code = f_true;
        return f_none;
      }
    #endif // _di_fll_status_booleans_

    #ifndef _di_fll_status_signals_
      if (fl_string_compare(string, fl_status_string_signal_hangup, length, fl_status_string_signal_hangup_length) == f_equal_to) {
        *code = f_signal_hangup;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_interrupt, length, fl_status_string_signal_interrupt_length) == f_equal_to) {
        *code = f_signal_interrupt;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_quit, length, fl_status_string_signal_quit_length) == f_equal_to) {
        *code = f_signal_quit;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_illegal, length, fl_status_string_signal_illegal_length) == f_equal_to) {
        *code = f_signal_illegal;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_trap, length, fl_status_string_signal_trap_length) == f_equal_to) {
        *code = f_signal_trap;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_abort, length, fl_status_string_signal_abort_length) == f_equal_to) {
        *code = f_signal_abort;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_bus_error, length, fl_status_string_signal_bus_error_length) == f_equal_to) {
        *code = f_signal_bus_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_floating_point_exception, length, fl_status_string_signal_floating_point_exception_length) == f_equal_to) {
        *code = f_signal_floating_point_exception;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_kill, length, fl_status_string_signal_kill_length) == f_equal_to) {
        *code = f_signal_kill;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_user_1, length, fl_status_string_signal_user_1_length) == f_equal_to) {
        *code = f_signal_user_1;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_segmentation_fault, length, fl_status_string_signal_segmentation_fault_length) == f_equal_to) {
        *code = f_signal_segmentation_fault;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_user_2, length, fl_status_string_signal_user_2_length) == f_equal_to) {
        *code = f_signal_user_2;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_broken_pipe, length, fl_status_string_signal_broken_pipe_length) == f_equal_to) {
        *code = f_signal_broken_pipe;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_alarm_clock, length, fl_status_string_signal_alarm_clock_length) == f_equal_to) {
        *code = f_signal_alarm_clock;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_termination, length, fl_status_string_signal_termination_length) == f_equal_to) {
        *code = f_signal_termination;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_stack_fault, length, fl_status_string_signal_stack_fault_length) == f_equal_to) {
        *code = f_signal_stack_fault;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_child, length, fl_status_string_signal_child_length) == f_equal_to) {
        *code = f_signal_child;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_continue, length, fl_status_string_signal_continue_length) == f_equal_to) {
        *code = f_signal_continue;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_stop, length, fl_status_string_signal_stop_length) == f_equal_to) {
        *code = f_signal_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_keyboard_stop, length, fl_status_string_signal_keyboard_stop_length) == f_equal_to) {
        *code = f_signal_keyboard_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_tty_in, length, fl_status_string_signal_tty_in_length) == f_equal_to) {
        *code = f_signal_tty_in;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_tty_out, length, fl_status_string_signal_tty_out_length) == f_equal_to) {
        *code = f_signal_tty_out;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_urgent, length, fl_status_string_signal_urgent_length) == f_equal_to) {
        *code = f_signal_urgent;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_cpu_limit, length, fl_status_string_signal_cpu_limit_length) == f_equal_to) {
        *code = f_signal_cpu_limit;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_file_size_limit, length, fl_status_string_signal_file_size_limit_length) == f_equal_to) {
        *code = f_signal_file_size_limit;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_virtual_alarm_clock, length, fl_status_string_signal_virtual_alarm_clock_length) == f_equal_to) {
        *code = f_signal_virtual_alarm_clock;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_profile_alarm_clock, length, fl_status_string_signal_profile_alarm_clock_length) == f_equal_to) {
        *code = f_signal_profile_alarm_clock;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_window_size_change, length, fl_status_string_signal_window_size_change_length) == f_equal_to) {
        *code = f_signal_window_size_change;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_pollable_event, length, fl_status_string_signal_pollable_event_length) == f_equal_to) {
        *code = f_signal_pollable_event;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_power_failure, length, fl_status_string_signal_power_failure_length) == f_equal_to) {
        *code = f_signal_power_failure;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_bad_system_call, length, fl_status_string_signal_bad_system_call_length) == f_equal_to) {
        *code = f_signal_bad_system_call;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_32, length, fl_status_string_signal_reserved_32_length) == f_equal_to) {
        *code = f_signal_reserved_32;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_33, length, fl_status_string_signal_reserved_33_length) == f_equal_to) {
        *code = f_signal_reserved_33;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_34, length, fl_status_string_signal_reserved_34_length) == f_equal_to) {
        *code = f_signal_reserved_34;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_35, length, fl_status_string_signal_reserved_35_length) == f_equal_to) {
        *code = f_signal_reserved_35;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_36, length, fl_status_string_signal_reserved_36_length) == f_equal_to) {
        *code = f_signal_reserved_36;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_37, length, fl_status_string_signal_reserved_37_length) == f_equal_to) {
        *code = f_signal_reserved_37;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_38, length, fl_status_string_signal_reserved_38_length) == f_equal_to) {
        *code = f_signal_reserved_38;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_39, length, fl_status_string_signal_reserved_39_length) == f_equal_to) {
        *code = f_signal_reserved_39;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_40, length, fl_status_string_signal_reserved_40_length) == f_equal_to) {
        *code = f_signal_reserved_40;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_41, length, fl_status_string_signal_reserved_41_length) == f_equal_to) {
        *code = f_signal_reserved_41;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_42, length, fl_status_string_signal_reserved_42_length) == f_equal_to) {
        *code = f_signal_reserved_42;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_43, length, fl_status_string_signal_reserved_43_length) == f_equal_to) {
        *code = f_signal_reserved_43;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_44, length, fl_status_string_signal_reserved_44_length) == f_equal_to) {
        *code = f_signal_reserved_44;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_45, length, fl_status_string_signal_reserved_45_length) == f_equal_to) {
        *code = f_signal_reserved_45;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_46, length, fl_status_string_signal_reserved_46_length) == f_equal_to) {
        *code = f_signal_reserved_46;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_47, length, fl_status_string_signal_reserved_47_length) == f_equal_to) {
        *code = f_signal_reserved_47;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_48, length, fl_status_string_signal_reserved_48_length) == f_equal_to) {
        *code = f_signal_reserved_48;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_49, length, fl_status_string_signal_reserved_49_length) == f_equal_to) {
        *code = f_signal_reserved_49;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_50, length, fl_status_string_signal_reserved_50_length) == f_equal_to) {
        *code = f_signal_reserved_50;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_51, length, fl_status_string_signal_reserved_51_length) == f_equal_to) {
        *code = f_signal_reserved_51;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_52, length, fl_status_string_signal_reserved_52_length) == f_equal_to) {
        *code = f_signal_reserved_52;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_53, length, fl_status_string_signal_reserved_53_length) == f_equal_to) {
        *code = f_signal_reserved_53;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_54, length, fl_status_string_signal_reserved_54_length) == f_equal_to) {
        *code = f_signal_reserved_54;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_55, length, fl_status_string_signal_reserved_55_length) == f_equal_to) {
        *code = f_signal_reserved_55;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_56, length, fl_status_string_signal_reserved_56_length) == f_equal_to) {
        *code = f_signal_reserved_56;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_57, length, fl_status_string_signal_reserved_57_length) == f_equal_to) {
        *code = f_signal_reserved_57;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_58, length, fl_status_string_signal_reserved_58_length) == f_equal_to) {
        *code = f_signal_reserved_58;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_59, length, fl_status_string_signal_reserved_59_length) == f_equal_to) {
        *code = f_signal_reserved_59;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_60, length, fl_status_string_signal_reserved_60_length) == f_equal_to) {
        *code = f_signal_reserved_60;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_61, length, fl_status_string_signal_reserved_61_length) == f_equal_to) {
        *code = f_signal_reserved_61;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_62, length, fl_status_string_signal_reserved_62_length) == f_equal_to) {
        *code = f_signal_reserved_62;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_63, length, fl_status_string_signal_reserved_63_length) == f_equal_to) {
        *code = f_signal_reserved_63;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_64, length, fl_status_string_signal_reserved_64_length) == f_equal_to) {
        *code = f_signal_reserved_64;
        return f_none;
      }
    #endif // _di_fll_status_signals_

    #ifndef _di_fll_status_basic_
      if (fl_string_compare(string, fl_status_string_none, length, fl_status_string_none_length) == f_equal_to) {
        *code = f_none;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_maybe, length, fl_status_string_maybe_length) == f_equal_to) {
        *code = f_maybe;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_dummy, length, fl_status_string_dummy_length) == f_equal_to) {
        *code = f_dummy;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_warn, length, fl_status_string_warn_length) == f_equal_to) {
        *code = f_warn;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_critical, length, fl_status_string_critical_length) == f_equal_to) {
        *code = f_critical;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unknown, length, fl_status_string_unknown_length) == f_equal_to) {
        *code = f_unknown;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unsupported, length, fl_status_string_unsupported_length) == f_equal_to) {
        *code = f_unsupported;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_no_data, length, fl_status_string_no_data_length) == f_equal_to) {
        *code = f_no_data;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_out_of_memory, length, fl_status_string_out_of_memory_length) == f_equal_to) {
        *code = f_out_of_memory;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_input_error, length, fl_status_string_input_error_length) == f_equal_to) {
        *code = f_input_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_output_error, length, fl_status_string_output_error_length) == f_equal_to) {
        *code = f_output_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_input_output_error, length, fl_status_string_input_output_error_length) == f_equal_to) {
        *code = f_input_output_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_does_not_exist, length, fl_status_string_does_not_exist_length) == f_equal_to) {
        *code = f_does_not_exist;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_not_connected, length, fl_status_string_not_connected_length) == f_equal_to) {
        *code = f_not_connected;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_failure, length, fl_status_string_failure_length) == f_equal_to) {
        *code = f_failure;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_interrupted, length, fl_status_string_interrupted_length) == f_equal_to) {
        *code = f_interrupted;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_loop, length, fl_status_string_loop_length) == f_equal_to) {
        *code = f_loop;
        return f_none;
      }
    #endif // _di_fll_status_basic_

    #ifndef _di_fll_status_invalid_
      if (fl_string_compare(string, fl_status_string_invalid, length, fl_status_string_invalid_length) == f_equal_to) {
        *code = f_invalid;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_parameter, length, fl_status_string_invalid_parameter_length) == f_equal_to) {
        *code = f_invalid_parameter;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_syntax, length, fl_status_string_invalid_syntax_length) == f_equal_to) {
        *code = f_invalid_syntax;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_data, length, fl_status_string_invalid_data_length) == f_equal_to) {
        *code = f_invalid_data;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_file, length, fl_status_string_invalid_file_length) == f_equal_to) {
        *code = f_invalid_file;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_directory, length, fl_status_string_invalid_directory_length) == f_equal_to) {
        *code = f_invalid_directory;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_socket, length, fl_status_string_invalid_socket_length) == f_equal_to) {
        *code = f_invalid_socket;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_device, length, fl_status_string_invalid_device_length) == f_equal_to) {
        *code = f_invalid_device;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_link, length, fl_status_string_invalid_link_length) == f_equal_to) {
        *code = f_invalid_link;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_pipe, length, fl_status_string_invalid_pipe_length) == f_equal_to) {
        *code = f_invalid_pipe;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_address, length, fl_status_string_invalid_address_length) == f_equal_to) {
        *code = f_invalid_address;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_port, length, fl_status_string_invalid_port_length) == f_equal_to) {
        *code = f_invalid_port;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_value, length, fl_status_string_invalid_value_length) == f_equal_to) {
        *code = f_invalid_value;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_buffer, length, fl_status_string_invalid_buffer_length) == f_equal_to) {
        *code = f_invalid_buffer;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_process, length, fl_status_string_invalid_process_length) == f_equal_to) {
        *code = f_invalid_process;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_utf, length, fl_status_string_invalid_utf_length) == f_equal_to) {
        *code = f_invalid_utf;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_on_eof, length, fl_status_string_invalid_on_eof_length) == f_equal_to) {
        *code = f_invalid_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_on_eol, length, fl_status_string_invalid_on_eol_length) == f_equal_to) {
        *code = f_invalid_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_on_eos, length, fl_status_string_invalid_on_eos_length) == f_equal_to) {
        *code = f_invalid_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_invalid_on_stop, length, fl_status_string_invalid_on_stop_length) == f_equal_to) {
        *code = f_invalid_on_stop;
        return f_none;
      }
    #endif // _di_fll_status_invalid_

    #ifndef _di_fll_status_busy_
      if (fl_string_compare(string, fl_status_string_busy, length, fl_status_string_busy_length) == f_equal_to) {
        *code = f_busy;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_address, length, fl_status_string_busy_address_length) == f_equal_to) {
        *code = f_busy_address;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_port, length, fl_status_string_busy_port_length) == f_equal_to) {
        *code = f_busy_port;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_socket, length, fl_status_string_busy_socket_length) == f_equal_to) {
        *code = f_busy_socket;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_device, length, fl_status_string_busy_device_length) == f_equal_to) {
        *code = f_busy_device;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_pipe, length, fl_status_string_busy_pipe_length) == f_equal_to) {
        *code = f_busy_pipe;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_buffer, length, fl_status_string_busy_buffer_length) == f_equal_to) {
        *code = f_busy_buffer;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_process, length, fl_status_string_busy_process_length) == f_equal_to) {
        *code = f_busy_process;
        return f_none;
      }
    #endif // _di_fll_status_busy_

    #ifndef _di_fll_status_unavailable_
      if (fl_string_compare(string, fl_status_string_unavailable, length, fl_status_string_unavailable_length) == f_equal_to) {
        *code = f_unavailable;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_address, length, fl_status_string_unavailable_address_length) == f_equal_to) {
        *code = f_unavailable_address;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_port, length, fl_status_string_unavailable_port_length) == f_equal_to) {
        *code = f_unavailable_port;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_socket, length, fl_status_string_unavailable_socket_length) == f_equal_to) {
        *code = f_unavailable_socket;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_device, length, fl_status_string_unavailable_device_length) == f_equal_to) {
        *code = f_unavailable_device;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_pipe, length, fl_status_string_unavailable_pipe_length) == f_equal_to) {
        *code = f_unavailable_pipe;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_buffer, length, fl_status_string_unavailable_buffer_length) == f_equal_to) {
        *code = f_unavailable_buffer;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_process, length, fl_status_string_unavailable_process_length) == f_equal_to) {
        *code = f_unavailable_process;
        return f_none;
      }
    #endif // _di_fll_status_unavailable_

    #ifndef _di_fll_status_digits_
      if (fl_string_compare(string, fl_status_string_underflow, length, fl_status_string_underflow_length) == f_equal_to) {
        *code = f_underflow;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_overflow, length, fl_status_string_overflow_length) == f_equal_to) {
        *code = f_overflow;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_divide_by_zero, length, fl_status_string_divide_by_zero_length) == f_equal_to) {
        *code = f_divide_by_zero;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_cannot_be_negative, length, fl_status_string_cannot_be_negative_length) == f_equal_to) {
        *code = f_cannot_be_negative;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_cannot_be_positive, length, fl_status_string_cannot_be_positive_length) == f_equal_to) {
        *code = f_cannot_be_positive;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_cannot_be_zero, length, fl_status_string_cannot_be_zero_length) == f_equal_to) {
        *code = f_cannot_be_zero;
        return f_none;
      }
    #endif // _di_fll_status_digits_

    #ifndef _di_fll_status_buffers_
      if (fl_string_compare(string, fl_status_string_no_data_on_eof, length, fl_status_string_no_data_on_eof_length) == f_equal_to) {
        *code = f_no_data_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_no_data_on_eol, length, fl_status_string_no_data_on_eol_length) == f_equal_to) {
        *code = f_no_data_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_no_data_on_eos, length, fl_status_string_no_data_on_eos_length) == f_equal_to) {
        *code = f_no_data_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_no_data_on_stop, length, fl_status_string_no_data_on_stop_length) == f_equal_to) {
        *code = f_no_data_on_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_none_on_eof, length, fl_status_string_none_on_eof_length) == f_equal_to) {
        *code = f_none_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_none_on_eol, length, fl_status_string_none_on_eol_length) == f_equal_to) {
        *code = f_none_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_none_on_eos, length, fl_status_string_none_on_eos_length) == f_equal_to) {
        *code = f_none_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_none_on_stop, length, fl_status_string_none_on_stop_length) == f_equal_to) {
        *code = f_none_on_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_error_on_eof, length, fl_status_string_error_on_eof_length) == f_equal_to) {
        *code = f_error_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_error_on_eol, length, fl_status_string_error_on_eol_length) == f_equal_to) {
        *code = f_error_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_error_on_eos, length, fl_status_string_error_on_eos_length) == f_equal_to) {
        *code = f_error_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_error_on_stop, length, fl_status_string_error_on_stop_length) == f_equal_to) {
        *code = f_error_on_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_buffer_too_small, length, fl_status_string_buffer_too_small_length) == f_equal_to) {
        *code = f_buffer_too_small;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_buffer_too_large, length, fl_status_string_buffer_too_large_length) == f_equal_to) {
        *code = f_buffer_too_large;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_string_too_small, length, fl_status_string_string_too_small_length) == f_equal_to) {
        *code = f_string_too_small;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_string_too_large, length, fl_status_string_string_too_large_length) == f_equal_to) {
        *code = f_string_too_large;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest, length, fl_status_string_unterminated_nest_length) == f_equal_to) {
        *code = f_unterminated_nest;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_on_eof, length, fl_status_string_unterminated_nest_on_eof_length) == f_equal_to) {
        *code = f_unterminated_nest_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_on_eol, length, fl_status_string_unterminated_nest_on_eol_length) == f_equal_to) {
        *code = f_unterminated_nest_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_on_eos, length, fl_status_string_unterminated_nest_on_eos_length) == f_equal_to) {
        *code = f_unterminated_nest_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_on_stop, length, fl_status_string_unterminated_nest_on_stop_length) == f_equal_to) {
        *code = f_unterminated_nest_on_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group, length, fl_status_string_unterminated_group_length) == f_equal_to) {
        *code = f_unterminated_group;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_eof, length, fl_status_string_unterminated_group_on_eof_length) == f_equal_to) {
        *code = f_unterminated_group_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_eol, length, fl_status_string_unterminated_group_on_eol_length) == f_equal_to) {
        *code = f_unterminated_group_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_eos, length, fl_status_string_unterminated_group_on_eos_length) == f_equal_to) {
        *code = f_unterminated_group_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_stop, length, fl_status_string_unterminated_group_on_stop_length) == f_equal_to) {
        *code = f_unterminated_group_on_stop;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf, length, fl_status_string_incomplete_utf_length) == f_equal_to) {
        *code = f_incomplete_utf;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_eof, length, fl_status_string_incomplete_utf_on_eof_length) == f_equal_to) {
        *code = f_incomplete_utf_on_eof;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_eol, length, fl_status_string_incomplete_utf_on_eol_length) == f_equal_to) {
        *code = f_incomplete_utf_on_eol;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_eos, length, fl_status_string_incomplete_utf_on_eos_length) == f_equal_to) {
        *code = f_incomplete_utf_on_eos;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_stop, length, fl_status_string_incomplete_utf_on_stop_length) == f_equal_to) {
        *code = f_incomplete_utf_on_stop;
        return f_none;
      }
    #endif // _di_fll_status_buffers_

    #ifndef _di_fll_status_allocation_
      if (fl_string_compare(string, fl_status_string_allocation_error, length, fl_status_string_allocation_error_length) == f_equal_to) {
        *code = f_allocation_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_reallocation_error, length, fl_status_string_reallocation_error_length) == f_equal_to) {
        *code = f_reallocation_error;
        return f_none;
      }
    #endif // _di_fll_status_allocation_

    #ifndef _di_fll_status_fork_
      if (fl_string_compare(string, fl_status_string_fork_failed, length, fl_status_string_fork_failed_length) == f_equal_to) {
        *code = f_fork_failed;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_too_many_processes, length, fl_status_string_too_many_processes_length) == f_equal_to) {
        *code = f_too_many_processes;
        return f_none;
      }
    #endif // _di_fll_status_fork_

    #ifndef _di_fll_status_file_
      if (fl_string_compare(string, fl_status_string_file_seek_error, length, fl_status_string_file_seek_error_length) == f_equal_to) {
        *code = f_file_seek_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_read_error, length, fl_status_string_file_read_error_length) == f_equal_to) {
        *code = f_file_read_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_write_error, length, fl_status_string_file_write_error_length) == f_equal_to) {
        *code = f_file_write_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_flush_error, length, fl_status_string_file_flush_error_length) == f_equal_to) {
        *code = f_file_flush_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_purge_error, length, fl_status_string_file_purge_error_length) == f_equal_to) {
        *code = f_file_purge_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_open_error, length, fl_status_string_file_open_error_length) == f_equal_to) {
        *code = f_file_open_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_close_error, length, fl_status_string_file_close_error_length) == f_equal_to) {
        *code = f_file_close_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_synchronize_error, length, fl_status_string_file_synchronize_error_length) == f_equal_to) {
        *code = f_file_synchronize_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_descriptor_error, length, fl_status_string_file_descriptor_error_length) == f_equal_to) {
        *code = f_file_descriptor_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_found, length, fl_status_string_file_not_found_length) == f_equal_to) {
        *code = f_file_not_found;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_found, length, fl_status_string_file_found_length) == f_equal_to) {
        *code = f_file_found;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_is_empty, length, fl_status_string_file_is_empty_length) == f_equal_to) {
        *code = f_file_is_empty;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_open, length, fl_status_string_file_not_open_length) == f_equal_to) {
        *code = f_file_not_open;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_allocation_error, length, fl_status_string_file_allocation_error_length) == f_equal_to) {
        *code = f_file_allocation_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_reallocation_error, length, fl_status_string_file_reallocation_error_length) == f_equal_to) {
        *code = f_file_reallocation_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_stat_error, length, fl_status_string_file_stat_error_length) == f_equal_to) {
        *code = f_file_stat_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_error, length, fl_status_string_file_error_length) == f_equal_to) {
        *code = f_file_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_utf, length, fl_status_string_file_not_utf_length) == f_equal_to) {
        *code = f_file_not_utf;
        return f_none;
      }
    #endif // _di_fll_status_file_

    #ifndef _di_fll_status_directory_
      if (fl_string_compare(string, fl_status_string_directory_read_error, length, fl_status_string_directory_read_error_length) == f_equal_to) {
        *code = f_directory_read_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_write_error, length, fl_status_string_directory_write_error_length) == f_equal_to) {
        *code = f_directory_write_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_flush_error, length, fl_status_string_directory_flush_error_length) == f_equal_to) {
        *code = f_directory_flush_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_purge_error, length, fl_status_string_directory_purge_error_length) == f_equal_to) {
        *code = f_directory_purge_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_open_error, length, fl_status_string_directory_open_error_length) == f_equal_to) {
        *code = f_directory_open_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_close_error, length, fl_status_string_directory_close_error_length) == f_equal_to) {
        *code = f_directory_close_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_synchronize_error, length, fl_status_string_directory_synchronize_error_length) == f_equal_to) {
        *code = f_directory_synchronize_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_descriptor_error, length, fl_status_string_directory_descriptor_error_length) == f_equal_to) {
        *code = f_directory_descriptor_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_not_found, length, fl_status_string_directory_not_found_length) == f_equal_to) {
        *code = f_directory_not_found;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_is_empty, length, fl_status_string_directory_is_empty_length) == f_equal_to) {
        *code = f_directory_is_empty;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_not_open, length, fl_status_string_directory_not_open_length) == f_equal_to) {
        *code = f_directory_not_open;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_allocation_error, length, fl_status_string_directory_allocation_error_length) == f_equal_to) {
        *code = f_directory_allocation_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_reallocation_error, length, fl_status_string_directory_reallocation_error_length) == f_equal_to) {
        *code = f_directory_reallocation_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_error, length, fl_status_string_directory_error_length) == f_equal_to) {
        *code = f_directory_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_not_utf, length, fl_status_string_directory_not_utf_length) == f_equal_to) {
        *code = f_directory_not_utf;
        return f_none;
      }
    #endif // _di_fll_status_directory_

    #ifndef _di_fll_status_socket_
      if (fl_string_compare(string, fl_status_string_socket_connection_client_error, length, fl_status_string_socket_connection_client_error_length) == f_equal_to) {
        *code = f_socket_connection_client_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_socket_connection_target_error, length, fl_status_string_socket_connection_target_error_length) == f_equal_to) {
        *code = f_socket_connection_target_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_socket_receive_error, length, fl_status_string_socket_receive_error_length) == f_equal_to) {
        *code = f_socket_receive_error;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_socket_send_error, length, fl_status_string_socket_send_error_length) == f_equal_to) {
        *code = f_socket_send_error;
        return f_none;
      }
    #endif // _di_fll_status_socket_

    #ifndef _di_fll_status_non_
      if (fl_string_compare(string, fl_status_string_less_than, length, fl_status_string_less_than_length) == f_equal_to) {
        *code = f_less_than;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_equal_to, length, fl_status_string_equal_to_length) == f_equal_to) {
        *code = f_equal_to;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_not_equal_to, length, fl_status_string_not_equal_to_length) == f_equal_to) {
        *code = f_not_equal_to;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_greater_than, length, fl_status_string_greater_than_length) == f_equal_to) {
        *code = f_greater_than;
        return f_none;
      }
    #endif // _di_fll_status_non_

    #ifndef _di_fll_status_access_denied_
      if (fl_string_compare(string, fl_status_string_access_denied, length, fl_status_string_access_denied_length) == f_equal_to) {
        *code = f_access_denied;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_user, length, fl_status_string_access_denied_user_length) == f_equal_to) {
        *code = f_access_denied_user;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_group, length, fl_status_string_access_denied_group_length) == f_equal_to) {
        *code = f_access_denied_group;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_world, length, fl_status_string_access_denied_world_length) == f_equal_to) {
        *code = f_access_denied_world;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_read, length, fl_status_string_access_denied_read_length) == f_equal_to) {
        *code = f_access_denied_read;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_write, length, fl_status_string_access_denied_write_length) == f_equal_to) {
        *code = f_access_denied_write;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_execute, length, fl_status_string_access_denied_execute_length) == f_equal_to) {
        *code = f_access_denied_execute;
        return f_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_super, length, fl_status_string_access_denied_super_length) == f_equal_to) {
        *code = f_access_denied_super;
        return f_none;
      }
    #endif // _di_fll_status_access_denied_

    if (fl_string_compare(string, fl_status_string_last_status_code, length, fl_status_string_last_error_code_length) == f_equal_to) {
      *code = f_last_status_code;
      return f_none;
    }

    return f_invalid_data;
  }
#endif // _di_fll_status_from_string_

#ifdef __cplusplus
} // extern "C"
#endif

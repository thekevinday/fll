#include <level_2/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_status_from_string_
  f_return_status fll_status_from_string(const f_string string, f_status *code) {
    #ifndef _di_level_1_parameter_checking_
      if (code == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;
    f_string_length length = strlen(string);

    if (length == 0) {
      return F_data_not;
    }

    // Numbers are not valid status code strings.
    if ((status = f_conversion_character_is_decimal(string[0])) == F_true) {
      return F_status_set_error(F_data);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    #ifndef _di_fll_status_booleans_
      if (fl_string_compare(string, fl_status_string_false, length, fl_status_string_false_length) == F_equal_to) {
        *code = F_false;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_true, length, fl_status_string_true_length) == F_equal_to) {
        *code = F_true;
        return F_none;
      }
    #endif // _di_fll_status_booleans_

    #ifndef _di_fll_status_signals_
      if (fl_string_compare(string, fl_status_string_signal_hangup, length, fl_status_string_signal_hangup_length) == F_equal_to) {
        *code = F_signal_hangup;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_interrupt, length, fl_status_string_signal_interrupt_length) == F_equal_to) {
        *code = F_signal_interrupt;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_quit, length, fl_status_string_signal_quit_length) == F_equal_to) {
        *code = F_signal_quit;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_illegal, length, fl_status_string_signal_illegal_length) == F_equal_to) {
        *code = F_signal_illegal;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_trap, length, fl_status_string_signal_trap_length) == F_equal_to) {
        *code = F_signal_trap;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_abort, length, fl_status_string_signal_abort_length) == F_equal_to) {
        *code = F_signal_abort;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_bus_error, length, fl_status_string_signal_bus_error_length) == F_equal_to) {
        *code = F_signal_bus_error;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_floating_point_exception, length, fl_status_string_signal_floating_point_exception_length) == F_equal_to) {
        *code = F_signal_floating_point_exception;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_kill, length, fl_status_string_signal_kill_length) == F_equal_to) {
        *code = F_signal_kill;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_user_1, length, fl_status_string_signal_user_1_length) == F_equal_to) {
        *code = F_signal_user_1;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_segmentation_fault, length, fl_status_string_signal_segmentation_fault_length) == F_equal_to) {
        *code = F_signal_segmentation_fault;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_user_2, length, fl_status_string_signal_user_2_length) == F_equal_to) {
        *code = F_signal_user_2;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_broken_pipe, length, fl_status_string_signal_broken_pipe_length) == F_equal_to) {
        *code = F_signal_broken_pipe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_alarm_clock, length, fl_status_string_signal_alarm_clock_length) == F_equal_to) {
        *code = F_signal_alarm_clock;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_termination, length, fl_status_string_signal_termination_length) == F_equal_to) {
        *code = F_signal_termination;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_stack_fault, length, fl_status_string_signal_stack_fault_length) == F_equal_to) {
        *code = F_signal_stack_fault;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_child, length, fl_status_string_signal_child_length) == F_equal_to) {
        *code = F_signal_child;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_continue, length, fl_status_string_signal_continue_length) == F_equal_to) {
        *code = F_signal_continue;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_stop, length, fl_status_string_signal_stop_length) == F_equal_to) {
        *code = F_signal_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_keyboard_stop, length, fl_status_string_signal_keyboard_stop_length) == F_equal_to) {
        *code = F_signal_keyboard_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_tty_in, length, fl_status_string_signal_tty_in_length) == F_equal_to) {
        *code = F_signal_tty_in;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_tty_out, length, fl_status_string_signal_tty_out_length) == F_equal_to) {
        *code = F_signal_tty_out;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_urgent, length, fl_status_string_signal_urgent_length) == F_equal_to) {
        *code = F_signal_urgent;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_cpu_limit, length, fl_status_string_signal_cpu_limit_length) == F_equal_to) {
        *code = F_signal_cpu_limit;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_file_size_limit, length, fl_status_string_signal_file_size_limit_length) == F_equal_to) {
        *code = F_signal_file_size_limit;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_virtual_alarm_clock, length, fl_status_string_signal_virtual_alarm_clock_length) == F_equal_to) {
        *code = F_signal_virtual_alarm_clock;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_profile_alarm_clock, length, fl_status_string_signal_profile_alarm_clock_length) == F_equal_to) {
        *code = F_signal_profile_alarm_clock;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_window_size_change, length, fl_status_string_signal_window_size_change_length) == F_equal_to) {
        *code = F_signal_window_size_change;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_pollable_event, length, fl_status_string_signal_pollable_event_length) == F_equal_to) {
        *code = F_signal_pollable_event;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_power_failure, length, fl_status_string_signal_power_failure_length) == F_equal_to) {
        *code = F_signal_power_failure;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_bad_system_call, length, fl_status_string_signal_bad_system_call_length) == F_equal_to) {
        *code = F_signal_bad_system_call;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_32, length, fl_status_string_signal_reserved_32_length) == F_equal_to) {
        *code = F_signal_reserved_32;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_33, length, fl_status_string_signal_reserved_33_length) == F_equal_to) {
        *code = F_signal_reserved_33;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_34, length, fl_status_string_signal_reserved_34_length) == F_equal_to) {
        *code = F_signal_reserved_34;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_35, length, fl_status_string_signal_reserved_35_length) == F_equal_to) {
        *code = F_signal_reserved_35;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_36, length, fl_status_string_signal_reserved_36_length) == F_equal_to) {
        *code = F_signal_reserved_36;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_37, length, fl_status_string_signal_reserved_37_length) == F_equal_to) {
        *code = F_signal_reserved_37;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_38, length, fl_status_string_signal_reserved_38_length) == F_equal_to) {
        *code = F_signal_reserved_38;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_39, length, fl_status_string_signal_reserved_39_length) == F_equal_to) {
        *code = F_signal_reserved_39;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_40, length, fl_status_string_signal_reserved_40_length) == F_equal_to) {
        *code = F_signal_reserved_40;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_41, length, fl_status_string_signal_reserved_41_length) == F_equal_to) {
        *code = F_signal_reserved_41;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_42, length, fl_status_string_signal_reserved_42_length) == F_equal_to) {
        *code = F_signal_reserved_42;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_43, length, fl_status_string_signal_reserved_43_length) == F_equal_to) {
        *code = F_signal_reserved_43;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_44, length, fl_status_string_signal_reserved_44_length) == F_equal_to) {
        *code = F_signal_reserved_44;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_45, length, fl_status_string_signal_reserved_45_length) == F_equal_to) {
        *code = F_signal_reserved_45;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_46, length, fl_status_string_signal_reserved_46_length) == F_equal_to) {
        *code = F_signal_reserved_46;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_47, length, fl_status_string_signal_reserved_47_length) == F_equal_to) {
        *code = F_signal_reserved_47;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_48, length, fl_status_string_signal_reserved_48_length) == F_equal_to) {
        *code = F_signal_reserved_48;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_49, length, fl_status_string_signal_reserved_49_length) == F_equal_to) {
        *code = F_signal_reserved_49;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_50, length, fl_status_string_signal_reserved_50_length) == F_equal_to) {
        *code = F_signal_reserved_50;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_51, length, fl_status_string_signal_reserved_51_length) == F_equal_to) {
        *code = F_signal_reserved_51;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_52, length, fl_status_string_signal_reserved_52_length) == F_equal_to) {
        *code = F_signal_reserved_52;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_53, length, fl_status_string_signal_reserved_53_length) == F_equal_to) {
        *code = F_signal_reserved_53;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_54, length, fl_status_string_signal_reserved_54_length) == F_equal_to) {
        *code = F_signal_reserved_54;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_55, length, fl_status_string_signal_reserved_55_length) == F_equal_to) {
        *code = F_signal_reserved_55;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_56, length, fl_status_string_signal_reserved_56_length) == F_equal_to) {
        *code = F_signal_reserved_56;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_57, length, fl_status_string_signal_reserved_57_length) == F_equal_to) {
        *code = F_signal_reserved_57;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_58, length, fl_status_string_signal_reserved_58_length) == F_equal_to) {
        *code = F_signal_reserved_58;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_59, length, fl_status_string_signal_reserved_59_length) == F_equal_to) {
        *code = F_signal_reserved_59;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_60, length, fl_status_string_signal_reserved_60_length) == F_equal_to) {
        *code = F_signal_reserved_60;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_61, length, fl_status_string_signal_reserved_61_length) == F_equal_to) {
        *code = F_signal_reserved_61;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_62, length, fl_status_string_signal_reserved_62_length) == F_equal_to) {
        *code = F_signal_reserved_62;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_63, length, fl_status_string_signal_reserved_63_length) == F_equal_to) {
        *code = F_signal_reserved_63;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_signal_reserved_64, length, fl_status_string_signal_reserved_64_length) == F_equal_to) {
        *code = F_signal_reserved_64;
        return F_none;
      }
    #endif // _di_fll_status_signals_

    #ifndef _di_fll_status_basic_
      if (fl_string_compare(string, fl_status_string_none, length, fl_status_string_none_length) == F_equal_to) {
        *code = F_none;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_maybe, length, fl_status_string_maybe_length) == F_equal_to) {
        *code = F_maybe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_dummy, length, fl_status_string_dummy_length) == F_equal_to) {
        *code = F_dummy;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_warn, length, fl_status_string_warn_length) == F_equal_to) {
        *code = F_warn;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_block, length, fl_status_string_block_length) == F_equal_to) {
        *code = F_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_critical, length, fl_status_string_critical_length) == F_equal_to) {
        *code = F_critical;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unknown, length, fl_status_string_unknown_length) == F_equal_to) {
        *code = F_unknown;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unsupported, length, fl_status_string_unsupported_length) == F_equal_to) {
        *code = F_unsupported;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_no_data, length, fl_status_string_no_data_length) == F_equal_to) {
        *code = F_data_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_no_space, length, fl_status_string_no_space_length) == F_equal_to) {
        *code = F_space_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_bound_out, length, fl_status_string_bound_out_length) == F_equal_to) {
        *code = F_bound_out;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_memory_out, length, fl_status_string_memory_out_length) == F_equal_to) {
        *code = F_memory_out;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_prohibited, length, fl_status_string_prohibited_length) == F_equal_to) {
        *code = F_prohibited;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_read_only, length, fl_status_string_read_only_length) == F_equal_to) {
        *code = F_read_only;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_input, length, fl_status_string_input_length) == F_equal_to) {
        *code = F_input;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_output, length, fl_status_string_output_length) == F_equal_to) {
        *code = F_output;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_input_output, length, fl_status_string_input_output_length) == F_equal_to) {
        *code = F_input_output;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_exist_not, length, fl_status_string_exist_not_length) == F_equal_to) {
        *code = F_exist_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_connected_not, length, fl_status_string_connected_not_length) == F_equal_to) {
        *code = F_connected_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_failure, length, fl_status_string_failure_length) == F_equal_to) {
        *code = F_failure;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_interrupted, length, fl_status_string_interrupted_length) == F_equal_to) {
        *code = F_interrupted;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_loop, length, fl_status_string_loop_length) == F_equal_to) {
        *code = F_loop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete, length, fl_status_string_incomplete_length) == F_equal_to) {
        *code = F_incomplete;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_write_only, length, fl_status_string_write_only_length) == F_equal_to) {
        *code = F_write_only;
        return F_none;
      }
    #endif // _di_fll_status_basic_

    #ifndef _di_fll_status_invalid_
      if (fl_string_compare(string, fl_status_string_invalid, length, fl_status_string_length) == F_equal_to) {
        *code = F_invalid;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_name, length, fl_status_string_name_length) == F_equal_to) {
        *code = F_name;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_parameter, length, fl_status_string_parameter_length) == F_equal_to) {
        *code = F_parameter;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_syntax, length, fl_status_string_syntax_length) == F_equal_to) {
        *code = F_syntax;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_data, length, fl_status_string_data_length) == F_equal_to) {
        *code = F_data;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_descriptor, length, fl_status_string_descriptor_length) == F_equal_to) {
        *code = F_descriptor;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_socket, length, fl_status_string_socket_length) == F_equal_to) {
        *code = F_socket;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_device, length, fl_status_string_device_length) == F_equal_to) {
        *code = F_device;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_link, length, fl_status_string_link_length) == F_equal_to) {
        *code = F_link;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_pipe, length, fl_status_string_pipe_length) == F_equal_to) {
        *code = F_pipe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_address, length, fl_status_string_address_length) == F_equal_to) {
        *code = F_address;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_port, length, fl_status_string_port_length) == F_equal_to) {
        *code = F_port;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_value, length, fl_status_string_value_length) == F_equal_to) {
        *code = F_value;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_buffer, length, fl_status_string_buffer_length) == F_equal_to) {
        *code = F_buffer;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_process, length, fl_status_string_process_length) == F_equal_to) {
        *code = F_process;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_utf, length, fl_status_string_utf_length) == F_equal_to) {
        *code = F_utf;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_eof, length, fl_status_string_eof_length) == F_equal_to) {
        *code = F_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_eol, length, fl_status_string_eol_length) == F_equal_to) {
        *code = F_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_eos, length, fl_status_string_eos_length) == F_equal_to) {
        *code = F_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_stop, length, fl_status_string_stop_length) == F_equal_to) {
        *code = F_stop;
        return F_none;
      }
    #endif // _di_fll_status_invalid_

    #ifndef _di_fll_status_busy_
      if (fl_string_compare(string, fl_status_string_busy, length, fl_status_string_busy_length) == F_equal_to) {
        *code = F_busy;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_address, length, fl_status_string_busy_address_length) == F_equal_to) {
        *code = F_busy_address;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_port, length, fl_status_string_busy_port_length) == F_equal_to) {
        *code = F_busy_port;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_socket, length, fl_status_string_busy_socket_length) == F_equal_to) {
        *code = F_busy_socket;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_device, length, fl_status_string_busy_device_length) == F_equal_to) {
        *code = F_busy_device;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_pipe, length, fl_status_string_busy_pipe_length) == F_equal_to) {
        *code = F_busy_pipe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_buffer, length, fl_status_string_busy_buffer_length) == F_equal_to) {
        *code = F_busy_buffer;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_busy_process, length, fl_status_string_busy_process_length) == F_equal_to) {
        *code = F_busy_process;
        return F_none;
      }
    #endif // _di_fll_status_busy_

    #ifndef _di_fll_status_unavailable_
      if (fl_string_compare(string, fl_status_string_unavailable, length, fl_status_string_unavailable_length) == F_equal_to) {
        *code = F_unavailable;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_address, length, fl_status_string_unavailable_address_length) == F_equal_to) {
        *code = F_unavailable_address;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_port, length, fl_status_string_unavailable_port_length) == F_equal_to) {
        *code = F_unavailable_port;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_socket, length, fl_status_string_unavailable_socket_length) == F_equal_to) {
        *code = F_unavailable_socket;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_device, length, fl_status_string_unavailable_device_length) == F_equal_to) {
        *code = F_unavailable_device;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_pipe, length, fl_status_string_unavailable_pipe_length) == F_equal_to) {
        *code = F_unavailable_pipe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_buffer, length, fl_status_string_unavailable_buffer_length) == F_equal_to) {
        *code = F_unavailable_buffer;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unavailable_process, length, fl_status_string_unavailable_process_length) == F_equal_to) {
        *code = F_unavailable_process;
        return F_none;
      }
    #endif // _di_fll_status_unavailable_

    #ifndef _di_fll_status_digits_
      if (fl_string_compare(string, fl_status_string_underflow, length, fl_status_string_underflow_length) == F_equal_to) {
        *code = F_number_underflow;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_overflow, length, fl_status_string_overflow_length) == F_equal_to) {
        *code = F_number_overflow;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_divide_by_zero, length, fl_status_string_divide_by_zero_length) == F_equal_to) {
        *code = F_number_divide_by_zero;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_negative_number, length, fl_status_string_negative_number_length) == F_equal_to) {
        *code = F_number_negative;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_positive_number, length, fl_status_string_positive_number_length) == F_equal_to) {
        *code = F_number_positive;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_zero_number, length, fl_status_string_zero_number_length) == F_equal_to) {
        *code = F_number_zero;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_decimal_number, length, fl_status_string_decimal_number_length) == F_equal_to) {
        *code = F_number_decimal;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_whole_number, length, fl_status_string_whole_number_length) == F_equal_to) {
        *code = F_number_whole;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_number, length, fl_status_string_number_length) == F_equal_to) {
        *code = F_number_invalid;
        return F_none;
      }
    #endif // _di_fll_status_digits_

    #ifndef _di_fll_status_buffers_
      if (fl_string_compare(string, fl_status_string_data_no_eof, length, fl_status_string_data_no_eof_length) == F_equal_to) {
        *code = F_data_no_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_data_no_eol, length, fl_status_string_data_no_eol_length) == F_equal_to) {
        *code = F_data_no_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_data_no_eos, length, fl_status_string_data_no_eos_length) == F_equal_to) {
        *code = F_data_no_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_data_no_stop, length, fl_status_string_data_no_stop_length) == F_equal_to) {
        *code = F_data_no_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_data_no_block, length, fl_status_string_data_no_block_length) == F_equal_to) {
        *code = F_data_block_no;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_none_eof, length, fl_status_string_none_eof_length) == F_equal_to) {
        *code = F_none_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_none_eol, length, fl_status_string_none_eol_length) == F_equal_to) {
        *code = F_none_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_none_eos, length, fl_status_string_none_eos_length) == F_equal_to) {
        *code = F_none_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_none_stop, length, fl_status_string_none_stop_length) == F_equal_to) {
        *code = F_none_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_none_block, length, fl_status_string_none_block_length) == F_equal_to) {
        *code = F_none_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_eof, length, fl_status_string_eof_length) == F_equal_to) {
        *code = F_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_eol, length, fl_status_string_eol_length) == F_equal_to) {
        *code = F_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_error_on_eos, length, fl_status_string_error_on_eos_length) == F_equal_to) {
        *code = F_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_stop, length, fl_status_string_stop_length) == F_equal_to) {
        *code = F_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_block, length, fl_status_string_block_length) == F_equal_to) {
        *code = F_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_buffer_too_small, length, fl_status_string_buffer_too_small_length) == F_equal_to) {
        *code = F_buffer_too_small;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_buffer_too_large, length, fl_status_string_buffer_too_large_length) == F_equal_to) {
        *code = F_buffer_too_large;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_string_too_small, length, fl_status_string_string_too_small_length) == F_equal_to) {
        *code = F_string_too_small;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_string_too_large, length, fl_status_string_string_too_large_length) == F_equal_to) {
        *code = F_string_too_large;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated, length, fl_status_string_unterminated_length) == F_equal_to) {
        *code = F_unterminated;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_eof, length, fl_status_string_unterminated_eof_length) == F_equal_to) {
        *code = F_unterminated_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_eol, length, fl_status_string_unterminated_eol_length) == F_equal_to) {
        *code = F_unterminated_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_eos, length, fl_status_string_unterminated_eos_length) == F_equal_to) {
        *code = F_unterminated_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_stop, length, fl_status_string_unterminated_stop_length) == F_equal_to) {
        *code = F_unterminated_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_block, length, fl_status_string_unterminated_block_length) == F_equal_to) {
        *code = F_unterminated_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group, length, fl_status_string_unterminated_group_length) == F_equal_to) {
        *code = F_unterminated_group;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_eof, length, fl_status_string_unterminated_group_on_eof_length) == F_equal_to) {
        *code = F_unterminated_group_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_eol, length, fl_status_string_unterminated_group_on_eol_length) == F_equal_to) {
        *code = F_unterminated_group_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_eos, length, fl_status_string_unterminated_group_on_eos_length) == F_equal_to) {
        *code = F_unterminated_group_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_stop, length, fl_status_string_unterminated_group_on_stop_length) == F_equal_to) {
        *code = F_unterminated_group_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_group_on_block, length, fl_status_string_unterminated_group_on_block_length) == F_equal_to) {
        *code = F_unterminated_group_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest, length, fl_status_string_unterminated_nest_length) == F_equal_to) {
        *code = F_unterminated_nest;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_eof, length, fl_status_string_unterminated_nest_eof_length) == F_equal_to) {
        *code = F_unterminated_nest_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_eol, length, fl_status_string_unterminated_nest_eol_length) == F_equal_to) {
        *code = F_unterminated_nest_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_eos, length, fl_status_string_unterminated_nest_eos_length) == F_equal_to) {
        *code = F_unterminated_nest_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_stop, length, fl_status_string_unterminated_nest_stop_length) == F_equal_to) {
        *code = F_unterminated_nest_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_unterminated_nest_block, length, fl_status_string_unterminated_nest_block_length) == F_equal_to) {
        *code = F_unterminated_nest_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf, length, fl_status_string_incomplete_utf_length) == F_equal_to) {
        *code = F_incomplete_utf;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_eof, length, fl_status_string_incomplete_utf_on_eof_length) == F_equal_to) {
        *code = F_incomplete_utf_eof;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_eol, length, fl_status_string_incomplete_utf_on_eol_length) == F_equal_to) {
        *code = F_incomplete_utf_eol;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_eos, length, fl_status_string_incomplete_utf_on_eos_length) == F_equal_to) {
        *code = F_incomplete_utf_eos;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_stop, length, fl_status_string_incomplete_utf_on_stop_length) == F_equal_to) {
        *code = F_incomplete_utf_stop;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_incomplete_utf_on_block, length, fl_status_string_incomplete_utf_on_block_length) == F_equal_to) {
        *code = F_incomplete_utf_block;
        return F_none;
      }
    #endif // _di_fll_status_buffers_

    #ifndef _di_fll_status_allocation_
      if (fl_string_compare(string, fl_status_string_memory_allocation, length, fl_status_string_memory_allocation_length) == F_equal_to) {
        *code = F_memory_allocation;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_memory_reallocation, length, fl_status_string_memory_reallocation_length) == F_equal_to) {
        *code = F_memory_reallocation;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_memory_deallocation, length, fl_status_string_memory_deallocation_length) == F_equal_to) {
        *code = F_memory_deallocation;
        return F_none;
      }
    #endif // _di_fll_status_allocation_

    #ifndef _di_fll_status_fork_
      if (fl_string_compare(string, fl_status_string_fork, length, fl_status_string_fork_length) == F_equal_to) {
        *code = F_fork;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_process_too_many, length, fl_status_string_process_too_many_length) == F_equal_to) {
        *code = F_process_too_many;
        return F_none;
      }
    #endif // _di_fll_status_fork_

    #ifndef _di_fll_status_file_
      if (fl_string_compare(string, fl_status_string_file_closed, length, fl_status_string_file_closed_length) == F_equal_to) {
        *code = F_file_closed;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_seek, length, fl_status_string_file_seek_length) == F_equal_to) {
        *code = F_file_seek;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_read, length, fl_status_string_file_read_length) == F_equal_to) {
        *code = F_file_read;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_write, length, fl_status_string_file_write_length) == F_equal_to) {
        *code = F_file_write;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_flush, length, fl_status_string_file_flush_length) == F_equal_to) {
        *code = F_file_flush;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_purge, length, fl_status_string_file_purge_length) == F_equal_to) {
        *code = F_file_purge;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_open, length, fl_status_string_file_open_length) == F_equal_to) {
        *code = F_file_open;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_close, length, fl_status_string_file_close_length) == F_equal_to) {
        *code = F_file_close;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_synchronize, length, fl_status_string_file_synchronize_length) == F_equal_to) {
        *code = F_file_synchronize;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_descriptor, length, fl_status_string_file_descriptor_length) == F_equal_to) {
        *code = F_file_descriptor;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_found_not, length, fl_status_string_file_found_not_length) == F_equal_to) {
        *code = F_file_found_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_empty, length, fl_status_string_file_empty_length) == F_equal_to) {
        *code = F_file_empty;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_found, length, fl_status_string_file_found_length) == F_equal_to) {
        *code = F_file_found;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_block, length, fl_status_string_file_type_block_length) == F_equal_to) {
        *code = F_file_type_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_character, length, fl_status_string_file_type_character_length) == F_equal_to) {
        *code = F_file_type_character;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_directory, length, fl_status_string_file_type_directory_length) == F_equal_to) {
        *code = F_file_type_directory;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_file, length, fl_status_string_file_type_file_length) == F_equal_to) {
        *code = F_file_type_file;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_link, length, fl_status_string_file_type_link_length) == F_equal_to) {
        *code = F_file_type_link;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_pipe, length, fl_status_string_file_type_pipe_length) == F_equal_to) {
        *code = F_file_type_pipe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_socket, length, fl_status_string_file_type_socket_length) == F_equal_to) {
        *code = F_file_type_socket;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_unknown, length, fl_status_string_file_type_unknown_length) == F_equal_to) {
        *code = F_file_type_unknown;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_open_not, length, fl_status_string_file_open_not_length) == F_equal_to) {
        *code = F_file_open_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_not_block, length, fl_status_string_file_type_not_block_length) == F_equal_to) {
        *code = F_file_type_not_block;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_type_not_character, length, fl_status_string_file_type_not_character_length) == F_equal_to) {
        *code = F_file_type_not_character;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_type_directory, length, fl_status_string_file_not_type_directory_length) == F_equal_to) {
        *code = F_file_type_not_directory;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_type_file, length, fl_status_string_file_not_type_file_length) == F_equal_to) {
        *code = F_file_type_not_file;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_type_link, length, fl_status_string_file_not_type_link_length) == F_equal_to) {
        *code = F_file_type_not_link;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_type_pipe, length, fl_status_string_file_not_type_pipe_length) == F_equal_to) {
        *code = F_file_type_not_pipe;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_type_socket, length, fl_status_string_file_not_type_socket_length) == F_equal_to) {
        *code = F_file_type_not_socket;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_type_unknown, length, fl_status_string_file_not_type_unknown_length) == F_equal_to) {
        *code = F_file_type_not_unknown;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_allocation, length, fl_status_string_file_allocation_length) == F_equal_to) {
        *code = F_file_allocation;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_reallocation, length, fl_status_string_file_reallocation_length) == F_equal_to) {
        *code = F_file_reallocation;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_deallocation, length, fl_status_string_file_deallocation_length) == F_equal_to) {
        *code = F_file_deallocation;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_stat, length, fl_status_string_file_stat_length) == F_equal_to) {
        *code = F_file_stat;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file, length, fl_status_string_file_length) == F_equal_to) {
        *code = F_file_error;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_not_utf, length, fl_status_string_file_not_utf_length) == F_equal_to) {
        *code = F_file_not_utf;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_descriptors_max, length, fl_status_string_file_descriptors_max_length) == F_equal_to) {
        *code = F_file_descriptors_max;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_open_max, length, fl_status_string_file_open_max_length) == F_equal_to) {
        *code = F_file_open_max;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_file_utf, length, fl_status_string_file_utf_length) == F_equal_to) {
        *code = F_file_utf;
        return F_none;
      }
    #endif // _di_fll_status_file_

    #ifndef _di_f_status_filesystem_
      if (fl_string_compare(string, fl_status_string_filesystem_error, length, fl_status_string_filesystem_error_length) == F_equal_to) {
        *code = F_filesystem;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_filesystem_quota_blocks, length, fl_status_string_filesystem_quota_blocks_length) == F_equal_to) {
        *code = F_filesystem_quota_blocks;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_filesystem_quota_reached, length, fl_status_string_filesystem_quota_reached_length) == F_equal_to) {
        *code = F_filesystem_quota_reached;
        return F_none;
      }
    #endif // _di_f_status_filesystem_

    #ifndef _di_fll_status_directory_
      if (fl_string_compare(string, fl_status_string_directory_closed, length, fl_status_string_directory_closed_length) == F_equal_to) {
        *code = F_directory_closed;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_read, length, fl_status_string_directory_read_length) == F_equal_to) {
        *code = F_directory_read;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_write, length, fl_status_string_directory_write_length) == F_equal_to) {
        *code = F_directory_write;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_flush, length, fl_status_string_directory_flush_length) == F_equal_to) {
        *code = F_directory_flush;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_link_max, length, fl_status_string_directory_link_max_length) == F_equal_to) {
        *code = F_directory_link_max;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_purge, length, fl_status_string_directory_purge_length) == F_equal_to) {
        *code = F_directory_purge;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_open, length, fl_status_string_directory_open_length) == F_equal_to) {
        *code = F_directory_open;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_close, length, fl_status_string_directory_close_length) == F_equal_to) {
        *code = F_directory_close;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_synchronize, length, fl_status_string_directory_synchronize_length) == F_equal_to) {
        *code = F_directory_synchronize;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_descriptor, length, fl_status_string_directory_descriptor_length) == F_equal_to) {
        *code = F_directory_descriptor;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_found, length, fl_status_string_directory_found_length) == F_equal_to) {
        *code = F_directory_found;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_empty, length, fl_status_string_directory_empty_length) == F_equal_to) {
        *code = F_directory_empty;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_not_found, length, fl_status_string_directory_not_found_length) == F_equal_to) {
        *code = F_directory_not_found;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_not_open, length, fl_status_string_directory_not_open_length) == F_equal_to) {
        *code = F_directory_not_open;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory, length, fl_status_string_directory_length) == F_equal_to) {
        *code = F_directory;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_not_utf, length, fl_status_string_directory_not_utf_length) == F_equal_to) {
        *code = F_directory_utf_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_unsupported, length, fl_status_string_directory_unsupported_length) == F_equal_to) {
        *code = F_directory_unsupported;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_stream, length, fl_status_string_directory_stream_length) == F_equal_to) {
        *code = F_directory_stream;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_directory_utf, length, fl_status_string_directory_utf_length) == F_equal_to) {
        *code = F_directory_utf;
        return F_none;
      }
    #endif // _di_fll_status_directory_

    #ifndef _di_fll_status_socket_
      if (fl_string_compare(string, fl_status_string_socket_connection_client, length, fl_status_string_socket_connection_client_length) == F_equal_to) {
        *code = F_socket_connection_client;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_socket_connection_target, length, fl_status_string_socket_connection_target_length) == F_equal_to) {
        *code = F_socket_connection_target;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_socket_receive, length, fl_status_string_socket_receive_length) == F_equal_to) {
        *code = F_socket_receive;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_socket_send, length, fl_status_string_socket_send_length) == F_equal_to) {
        *code = F_socket_send;
        return F_none;
      }
    #endif // _di_fll_status_socket_

    #ifndef _di_fll_status_non_
      if (fl_string_compare(string, fl_status_string_than_less, length, fl_status_string_than_less_length) == F_equal_to) {
        *code = F_than_less;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_equal_to, length, fl_status_string_equal_to_length) == F_equal_to) {
        *code = F_equal_to;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_equal_to_not, length, fl_status_string_equal_to_not_length) == F_equal_to) {
        *code = F_equal_to_not;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_than_greater, length, fl_status_string_than_greater_length) == F_equal_to) {
        *code = F_than_greater;
        return F_none;
      }
    #endif // _di_fll_status_non_

    #ifndef _di_fll_status_access_denied_
      if (fl_string_compare(string, fl_status_string_access_denied, length, fl_status_string_access_denied_length) == F_equal_to) {
        *code = F_access_denied;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_user, length, fl_status_string_access_denied_user_length) == F_equal_to) {
        *code = F_access_denied_user;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_group, length, fl_status_string_access_denied_group_length) == F_equal_to) {
        *code = F_access_denied_group;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_world, length, fl_status_string_access_denied_world_length) == F_equal_to) {
        *code = F_access_denied_world;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_read, length, fl_status_string_access_denied_read_length) == F_equal_to) {
        *code = F_access_denied_read;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_write, length, fl_status_string_access_denied_write_length) == F_equal_to) {
        *code = F_access_denied_write;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_execute, length, fl_status_string_access_denied_execute_length) == F_equal_to) {
        *code = F_access_denied_execute;
        return F_none;
      }

      if (fl_string_compare(string, fl_status_string_access_denied_super, length, fl_status_string_access_denied_super_length) == F_equal_to) {
        *code = F_access_denied_super;
        return F_none;
      }
    #endif // _di_fll_status_access_denied_

    if (fl_string_compare(string, fl_status_string_status_code_last, length, fl_status_string_status_code_last_length) == F_equal_to) {
      *code = F_status_code_last;
      return F_none;
    }

    return F_status_set_error(F_data);
  }
#endif // _di_fll_status_from_string_

#ifdef __cplusplus
} // extern "C"
#endif

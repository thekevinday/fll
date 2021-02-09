#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_status_from_string_
  f_status_t fll_status_from_string(const f_string_t string, f_status_t *code) {
    #ifndef _di_level_2_parameter_checking_
      if (!code) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_string_length_t length = strlen(string);

    if (!length) {
      return F_data_not;
    }

    // Numbers are not valid status code strings.
    if ((status = f_conversion_character_is_decimal(string[0])) == F_true) {
      return F_status_set_error(F_data);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    #ifndef _di_F_status_boolean_
      if (fl_string_compare(string, FL_status_string_false, length, FL_status_string_false_length) == F_equal_to) {
        *code = F_false;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_true, length, FL_status_string_true_length) == F_equal_to) {
        *code = F_true;
        return F_none;
      }
    #endif // _di_F_status_boolean_

    #ifndef _di_F_status_signal_
      if (fl_string_compare(string, FL_status_string_signal_hangup, length, FL_status_string_signal_hangup_length) == F_equal_to) {
        *code = F_signal_hangup;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_interrupt, length, FL_status_string_signal_interrupt_length) == F_equal_to) {
        *code = F_signal_interrupt;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_quit, length, FL_status_string_signal_quit_length) == F_equal_to) {
        *code = F_signal_quit;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_illegal, length, FL_status_string_signal_illegal_length) == F_equal_to) {
        *code = F_signal_illegal;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_trap, length, FL_status_string_signal_trap_length) == F_equal_to) {
        *code = F_signal_trap;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_abort, length, FL_status_string_signal_abort_length) == F_equal_to) {
        *code = F_signal_abort;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_bus_error, length, FL_status_string_signal_bus_error_length) == F_equal_to) {
        *code = F_signal_bus_error;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_floating_point_error, length, FL_status_string_signal_floating_point_error_length) == F_equal_to) {
        *code = F_signal_floating_point_error;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_kill, length, FL_status_string_signal_kill_length) == F_equal_to) {
        *code = F_signal_kill;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_user_1, length, FL_status_string_signal_user_1_length) == F_equal_to) {
        *code = F_signal_user_1;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_segmentation_fault, length, FL_status_string_signal_segmentation_fault_length) == F_equal_to) {
        *code = F_signal_segmentation_fault;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_user_2, length, FL_status_string_signal_user_2_length) == F_equal_to) {
        *code = F_signal_user_2;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_broken_pipe, length, FL_status_string_signal_broken_pipe_length) == F_equal_to) {
        *code = F_signal_broken_pipe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_alarm_clock, length, FL_status_string_signal_alarm_clock_length) == F_equal_to) {
        *code = F_signal_alarm_clock;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_termination, length, FL_status_string_signal_termination_length) == F_equal_to) {
        *code = F_signal_termination;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_stack_fault, length, FL_status_string_signal_stack_fault_length) == F_equal_to) {
        *code = F_signal_stack_fault;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_child, length, FL_status_string_signal_child_length) == F_equal_to) {
        *code = F_signal_child;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_continue, length, FL_status_string_signal_continue_length) == F_equal_to) {
        *code = F_signal_continue;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_stop, length, FL_status_string_signal_stop_length) == F_equal_to) {
        *code = F_signal_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_keyboard_stop, length, FL_status_string_signal_keyboard_stop_length) == F_equal_to) {
        *code = F_signal_keyboard_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_tty_in, length, FL_status_string_signal_tty_in_length) == F_equal_to) {
        *code = F_signal_tty_in;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_tty_out, length, FL_status_string_signal_tty_out_length) == F_equal_to) {
        *code = F_signal_tty_out;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_urgent, length, FL_status_string_signal_urgent_length) == F_equal_to) {
        *code = F_signal_urgent;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_cpu_limit, length, FL_status_string_signal_cpu_limit_length) == F_equal_to) {
        *code = F_signal_cpu_limit;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_file_size_limit, length, FL_status_string_signal_file_size_limit_length) == F_equal_to) {
        *code = F_signal_file_size_limit;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_virtual_alarm_clock, length, FL_status_string_signal_virtual_alarm_clock_length) == F_equal_to) {
        *code = F_signal_virtual_alarm_clock;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_profile_alarm_clock, length, FL_status_string_signal_profile_alarm_clock_length) == F_equal_to) {
        *code = F_signal_profile_alarm_clock;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_window_size_change, length, FL_status_string_signal_window_size_change_length) == F_equal_to) {
        *code = F_signal_window_size_change;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_pollable_event, length, FL_status_string_signal_pollable_event_length) == F_equal_to) {
        *code = F_signal_pollable_event;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_power_failure, length, FL_status_string_signal_power_failure_length) == F_equal_to) {
        *code = F_signal_power_failure;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_bad_system_call, length, FL_status_string_signal_bad_system_call_length) == F_equal_to) {
        *code = F_signal_bad_system_call;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_32, length, FL_status_string_signal_reserved_32_length) == F_equal_to) {
        *code = F_signal_reserved_32;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_33, length, FL_status_string_signal_reserved_33_length) == F_equal_to) {
        *code = F_signal_reserved_33;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_34, length, FL_status_string_signal_reserved_34_length) == F_equal_to) {
        *code = F_signal_reserved_34;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_35, length, FL_status_string_signal_reserved_35_length) == F_equal_to) {
        *code = F_signal_reserved_35;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_36, length, FL_status_string_signal_reserved_36_length) == F_equal_to) {
        *code = F_signal_reserved_36;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_37, length, FL_status_string_signal_reserved_37_length) == F_equal_to) {
        *code = F_signal_reserved_37;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_38, length, FL_status_string_signal_reserved_38_length) == F_equal_to) {
        *code = F_signal_reserved_38;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_39, length, FL_status_string_signal_reserved_39_length) == F_equal_to) {
        *code = F_signal_reserved_39;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_40, length, FL_status_string_signal_reserved_40_length) == F_equal_to) {
        *code = F_signal_reserved_40;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_41, length, FL_status_string_signal_reserved_41_length) == F_equal_to) {
        *code = F_signal_reserved_41;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_42, length, FL_status_string_signal_reserved_42_length) == F_equal_to) {
        *code = F_signal_reserved_42;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_43, length, FL_status_string_signal_reserved_43_length) == F_equal_to) {
        *code = F_signal_reserved_43;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_44, length, FL_status_string_signal_reserved_44_length) == F_equal_to) {
        *code = F_signal_reserved_44;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_45, length, FL_status_string_signal_reserved_45_length) == F_equal_to) {
        *code = F_signal_reserved_45;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_46, length, FL_status_string_signal_reserved_46_length) == F_equal_to) {
        *code = F_signal_reserved_46;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_47, length, FL_status_string_signal_reserved_47_length) == F_equal_to) {
        *code = F_signal_reserved_47;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_48, length, FL_status_string_signal_reserved_48_length) == F_equal_to) {
        *code = F_signal_reserved_48;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_49, length, FL_status_string_signal_reserved_49_length) == F_equal_to) {
        *code = F_signal_reserved_49;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_50, length, FL_status_string_signal_reserved_50_length) == F_equal_to) {
        *code = F_signal_reserved_50;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_51, length, FL_status_string_signal_reserved_51_length) == F_equal_to) {
        *code = F_signal_reserved_51;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_52, length, FL_status_string_signal_reserved_52_length) == F_equal_to) {
        *code = F_signal_reserved_52;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_53, length, FL_status_string_signal_reserved_53_length) == F_equal_to) {
        *code = F_signal_reserved_53;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_54, length, FL_status_string_signal_reserved_54_length) == F_equal_to) {
        *code = F_signal_reserved_54;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_55, length, FL_status_string_signal_reserved_55_length) == F_equal_to) {
        *code = F_signal_reserved_55;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_56, length, FL_status_string_signal_reserved_56_length) == F_equal_to) {
        *code = F_signal_reserved_56;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_57, length, FL_status_string_signal_reserved_57_length) == F_equal_to) {
        *code = F_signal_reserved_57;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_58, length, FL_status_string_signal_reserved_58_length) == F_equal_to) {
        *code = F_signal_reserved_58;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_59, length, FL_status_string_signal_reserved_59_length) == F_equal_to) {
        *code = F_signal_reserved_59;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_60, length, FL_status_string_signal_reserved_60_length) == F_equal_to) {
        *code = F_signal_reserved_60;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_61, length, FL_status_string_signal_reserved_61_length) == F_equal_to) {
        *code = F_signal_reserved_61;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_62, length, FL_status_string_signal_reserved_62_length) == F_equal_to) {
        *code = F_signal_reserved_62;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_63, length, FL_status_string_signal_reserved_63_length) == F_equal_to) {
        *code = F_signal_reserved_63;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_reserved_64, length, FL_status_string_signal_reserved_64_length) == F_equal_to) {
        *code = F_signal_reserved_64;
        return F_none;
      }
    #endif // _di_F_status_signal_

    #ifndef _di_F_status_basic_
      if (fl_string_compare(string, FL_status_string_none, length, FL_status_string_none_length) == F_equal_to) {
        *code = F_none;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_absolute, length, FL_status_string_absolute_length) == F_equal_to) {
        *code = F_absolute;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_absolute_not, length, FL_status_string_absolute_not_length) == F_equal_to) {
        *code = F_absolute_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_address, length, FL_status_string_address_length) == F_equal_to) {
        *code = F_address;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_address_not, length, FL_status_string_address_not_length) == F_equal_to) {
        *code = F_address_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_block, length, FL_status_string_block_length) == F_equal_to) {
        *code = F_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_block_not, length, FL_status_string_block_not_length) == F_equal_to) {
        *code = F_block_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_bound, length, FL_status_string_bound_length) == F_equal_to) {
        *code = F_bound;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_bound_not, length, FL_status_string_bound_not_length) == F_equal_to) {
        *code = F_bound_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_capability, length, FL_status_string_capability_length) == F_equal_to) {
        *code = F_capability;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_capability_not, length, FL_status_string_capability_not_length) == F_equal_to) {
        *code = F_capability_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_child, length, FL_status_string_child_length) == F_equal_to) {
        *code = F_child;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_child_not, length, FL_status_string_child_not_length) == F_equal_to) {
        *code = F_child_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete, length, FL_status_string_complete_length) == F_equal_to) {
        *code = F_complete;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not, length, FL_status_string_complete_not_length) == F_equal_to) {
        *code = F_complete_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_connected, length, FL_status_string_connected_length) == F_equal_to) {
        *code = F_connected;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_connected_not, length, FL_status_string_connected_not_length) == F_equal_to) {
        *code = F_connected_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_container, length, FL_status_string_container_length) == F_equal_to) {
        *code = F_container;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_container_not, length, FL_status_string_container_not_length) == F_equal_to) {
        *code = F_container_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_control, length, FL_status_string_control_length) == F_equal_to) {
        *code = F_control;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_control_not, length, FL_status_string_control_not_length) == F_equal_to) {
        *code = F_control_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_control_group, length, FL_status_string_control_group_length) == F_equal_to) {
        *code = F_control_group;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_control_group_not, length, FL_status_string_control_group_not_length) == F_equal_to) {
        *code = F_control_group_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_critical, length, FL_status_string_critical_length) == F_equal_to) {
        *code = F_critical;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_critical_not, length, FL_status_string_critical_not_length) == F_equal_to) {
        *code = F_critical_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_deadlock, length, FL_status_string_deadlock_length) == F_equal_to) {
        *code = F_deadlock;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_deadlock_not, length, FL_status_string_deadlock_not_length) == F_equal_to) {
        *code = F_deadlock_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_descriptor, length, FL_status_string_descriptor_length) == F_equal_to) {
        *code = F_descriptor;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_descriptor_not, length, FL_status_string_descriptor_not_length) == F_equal_to) {
        *code = F_descriptor_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_device, length, FL_status_string_device_length) == F_equal_to) {
        *code = F_device;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_device_not, length, FL_status_string_device_not_length) == F_equal_to) {
        *code = F_device_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_dummy, length, FL_status_string_dummy_length) == F_equal_to) {
        *code = F_dummy;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_dummy_not, length, FL_status_string_dummy_not_length) == F_equal_to) {
        *code = F_dummy_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_encoding, length, FL_status_string_encoding_length) == F_equal_to) {
        *code = F_encoding;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_encoding_not, length, FL_status_string_encoding_not_length) == F_equal_to) {
        *code = F_encoding_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_eof, length, FL_status_string_eof_length) == F_equal_to) {
        *code = F_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_eof_not, length, FL_status_string_eof_not_length) == F_equal_to) {
        *code = F_eof_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_eol, length, FL_status_string_eol_length) == F_equal_to) {
        *code = F_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_eol_not, length, FL_status_string_eol_not_length) == F_equal_to) {
        *code = F_eol_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_eos, length, FL_status_string_eos_length) == F_equal_to) {
        *code = F_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_eos_not, length, FL_status_string_eos_not_length) == F_equal_to) {
        *code = F_eos_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_exist, length, FL_status_string_exist_length) == F_equal_to) {
        *code = F_exist;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_exist_not, length, FL_status_string_exist_not_length) == F_equal_to) {
        *code = F_exist_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_failure, length, FL_status_string_failure_length) == F_equal_to) {
        *code = F_failure;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_failure_not, length, FL_status_string_failure_not_length) == F_equal_to) {
        *code = F_failure_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_fork, length, FL_status_string_fork_length) == F_equal_to) {
        *code = F_fork;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_fork_not, length, FL_status_string_fork_not_length) == F_equal_to) {
        *code = F_fork_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_found, length, FL_status_string_found_length) == F_equal_to) {
        *code = F_found;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_found_not, length, FL_status_string_found_not_length) == F_equal_to) {
        *code = F_found_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_group, length, FL_status_string_group_length) == F_equal_to) {
        *code = F_group;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_group_not, length, FL_status_string_group_not_length) == F_equal_to) {
        *code = F_group_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_ignore, length, FL_status_string_ignore_length) == F_equal_to) {
        *code = F_ignore;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_ignore_not, length, FL_status_string_ignore_not_length) == F_equal_to) {
        *code = F_ignore_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_input, length, FL_status_string_input_length) == F_equal_to) {
        *code = F_input;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_input_not, length, FL_status_string_input_not_length) == F_equal_to) {
        *code = F_input_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_input_output, length, FL_status_string_input_output_length) == F_equal_to) {
        *code = F_input_output;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_interrupt, length, FL_status_string_interrupt_length) == F_equal_to) {
        *code = F_interrupt;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_interrupt_not, length, FL_status_string_interrupt_not_length) == F_equal_to) {
        *code = F_interrupt_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_known, length, FL_status_string_known_length) == F_equal_to) {
        *code = F_known;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_known_not, length, FL_status_string_known_not_length) == F_equal_to) {
        *code = F_known_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_limit, length, FL_status_string_limit_length) == F_equal_to) {
        *code = F_limit;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_limit_not, length, FL_status_string_limit_not_length) == F_equal_to) {
        *code = F_limit_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_link, length, FL_status_string_link_length) == F_equal_to) {
        *code = F_link;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_link_not, length, FL_status_string_link_not_length) == F_equal_to) {
        *code = F_link_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_lock, length, FL_status_string_lock_length) == F_equal_to) {
        *code = F_lock;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_lock_not, length, FL_status_string_lock_not_length) == F_equal_to) {
        *code = F_lock_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_loop, length, FL_status_string_loop_length) == F_equal_to) {
        *code = F_loop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_loop_not, length, FL_status_string_loop_not_length) == F_equal_to) {
        *code = F_loop_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_maybe, length, FL_status_string_maybe_length) == F_equal_to) {
        *code = F_maybe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_maybe_not, length, FL_status_string_maybe_not_length) == F_equal_to) {
        *code = F_maybe_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_memory, length, FL_status_string_memory_length) == F_equal_to) {
        *code = F_memory;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_memory_not, length, FL_status_string_memory_not_length) == F_equal_to) {
        *code = F_memory_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_minor, length, FL_status_string_minor_length) == F_equal_to) {
        *code = F_minor;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_minor_not, length, FL_status_string_minor_not_length) == F_equal_to) {
        *code = F_minor_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_moderate, length, FL_status_string_moderate_length) == F_equal_to) {
        *code = F_moderate;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_moderate_not, length, FL_status_string_moderate_not_length) == F_equal_to) {
        *code = F_moderate_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_mount, length, FL_status_string_mount_length) == F_equal_to) {
        *code = F_mount;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_mount_not, length, FL_status_string_mount_not_length) == F_equal_to) {
        *code = F_mount_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_name, length, FL_status_string_name_length) == F_equal_to) {
        *code = F_name;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_name_not, length, FL_status_string_name_not_length) == F_equal_to) {
        *code = F_name_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_nice, length, FL_status_string_nice_length) == F_equal_to) {
        *code = F_nice;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_nice_not, length, FL_status_string_nice_not_length) == F_equal_to) {
        *code = F_nice_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_optional, length, FL_status_string_optional_length) == F_equal_to) {
        *code = F_optional;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_optional_not, length, FL_status_string_optional_not_length) == F_equal_to) {
        *code = F_optional_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_output, length, FL_status_string_output_length) == F_equal_to) {
        *code = F_output;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_output_not, length, FL_status_string_output_not_length) == F_equal_to) {
        *code = F_output_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_parameter, length, FL_status_string_parameter_length) == F_equal_to) {
        *code = F_parameter;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_parameter_not, length, FL_status_string_parameter_not_length) == F_equal_to) {
        *code = F_parameter_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_parent, length, FL_status_string_parent_length) == F_equal_to) {
        *code = F_parent;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_parent_not, length, FL_status_string_parent_not_length) == F_equal_to) {
        *code = F_parent_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_pipe, length, FL_status_string_pipe_length) == F_equal_to) {
        *code = F_pipe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_pipe_not, length, FL_status_string_pipe_not_length) == F_equal_to) {
        *code = F_pipe_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_port, length, FL_status_string_port_length) == F_equal_to) {
        *code = F_port;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_port_not, length, FL_status_string_port_not_length) == F_equal_to) {
        *code = F_port_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_processor, length, FL_status_string_processor_length) == F_equal_to) {
        *code = F_processor;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_processor_not, length, FL_status_string_processor_not_length) == F_equal_to) {
        *code = F_processor_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_prohibited, length, FL_status_string_prohibited_length) == F_equal_to) {
        *code = F_prohibited;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_prohibited_not, length, FL_status_string_prohibited_not_length) == F_equal_to) {
        *code = F_prohibited_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_range, length, FL_status_string_range_length) == F_equal_to) {
        *code = F_range;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_range_not, length, FL_status_string_range_not_length) == F_equal_to) {
        *code = F_range_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_read, length, FL_status_string_read_length) == F_equal_to) {
        *code = F_read;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_read_not, length, FL_status_string_read_not_length) == F_equal_to) {
        *code = F_read_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_read_only, length, FL_status_string_read_only_length) == F_equal_to) {
        *code = F_read_only;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_ready, length, FL_status_string_ready_length) == F_equal_to) {
        *code = F_ready;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_ready_not, length, FL_status_string_ready_not_length) == F_equal_to) {
        *code = F_ready_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_recover, length, FL_status_string_recover_length) == F_equal_to) {
        *code = F_recover;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_recover_not, length, FL_status_string_recover_not_length) == F_equal_to) {
        *code = F_recover_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_recurse, length, FL_status_string_recurse_length) == F_equal_to) {
        *code = F_recurse;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_recurse_not, length, FL_status_string_recurse_not_length) == F_equal_to) {
        *code = F_recurse_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_relative, length, FL_status_string_relative_length) == F_equal_to) {
        *code = F_relative;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_relative_not, length, FL_status_string_relative_not_length) == F_equal_to) {
        *code = F_relative_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_require, length, FL_status_string_require_length) == F_equal_to) {
        *code = F_require;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_require_not, length, FL_status_string_require_not_length) == F_equal_to) {
        *code = F_require_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_resource, length, FL_status_string_resource_length) == F_equal_to) {
        *code = F_resource;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_resource_not, length, FL_status_string_resource_not_length) == F_equal_to) {
        *code = F_resource_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_search, length, FL_status_string_search_length) == F_equal_to) {
        *code = F_search;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_search_not, length, FL_status_string_search_not_length) == F_equal_to) {
        *code = F_search_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_schedule, length, FL_status_string_schedule_length) == F_equal_to) {
        *code = F_schedule;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_schedule_not, length, FL_status_string_schedule_not_length) == F_equal_to) {
        *code = F_schedule_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal, length, FL_status_string_signal_length) == F_equal_to) {
        *code = F_signal;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_signal_not, length, FL_status_string_signal_not_length) == F_equal_to) {
        *code = F_signal_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_space, length, FL_status_string_space_length) == F_equal_to) {
        *code = F_space;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_space_not, length, FL_status_string_space_not_length) == F_equal_to) {
        *code = F_space_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_stop, length, FL_status_string_stop_length) == F_equal_to) {
        *code = F_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_stop_not, length, FL_status_string_stop_not_length) == F_equal_to) {
        *code = F_stop_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_string, length, FL_status_string_string_length) == F_equal_to) {
        *code = F_string;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_string_not, length, FL_status_string_string_not_length) == F_equal_to) {
        *code = F_string_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_string_too_large, length, FL_status_string_string_too_large_length) == F_equal_to) {
        *code = F_string_too_large;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_string_too_small, length, FL_status_string_string_too_small_length) == F_equal_to) {
        *code = F_string_too_small;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_supported, length, FL_status_string_supported_length) == F_equal_to) {
        *code = F_supported;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_supported_not, length, FL_status_string_supported_not_length) == F_equal_to) {
        *code = F_supported_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_syntax, length, FL_status_string_syntax_length) == F_equal_to) {
        *code = F_syntax;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_syntax_not, length, FL_status_string_syntax_not_length) == F_equal_to) {
        *code = F_syntax_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_thread, length, FL_status_string_thread_length) == F_equal_to) {
        *code = F_thread;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_thread_not, length, FL_status_string_thread_not_length) == F_equal_to) {
        *code = F_thread_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_time, length, FL_status_string_time_length) == F_equal_to) {
        *code = F_time;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_time_not, length, FL_status_string_time_not_length) == F_equal_to) {
        *code = F_time_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_user, length, FL_status_string_user_length) == F_equal_to) {
        *code = F_user;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_user_not, length, FL_status_string_user_not_length) == F_equal_to) {
        *code = F_user_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_utf, length, FL_status_string_utf_length) == F_equal_to) {
        *code = F_utf;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_utf_not, length, FL_status_string_utf_not_length) == F_equal_to) {
        *code = F_utf_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_valid, length, FL_status_string_valid_length) == F_equal_to) {
        *code = F_valid;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_valid_not, length, FL_status_string_valid_not_length) == F_equal_to) {
        *code = F_valid_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_value, length, FL_status_string_value_length) == F_equal_to) {
        *code = F_value;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_value_not, length, FL_status_string_value_not_length) == F_equal_to) {
        *code = F_value_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_wait, length, FL_status_string_wait_length) == F_equal_to) {
        *code = F_wait;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_wait_not, length, FL_status_string_wait_not_length) == F_equal_to) {
        *code = F_wait_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_warn, length, FL_status_string_warn_length) == F_equal_to) {
        *code = F_warn;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_warn_not, length, FL_status_string_warn_not_length) == F_equal_to) {
        *code = F_warn_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_world, length, FL_status_string_world_length) == F_equal_to) {
        *code = F_world;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_world_not, length, FL_status_string_world_not_length) == F_equal_to) {
        *code = F_world_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_write, length, FL_status_string_write_length) == F_equal_to) {
        *code = F_write;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_write_not, length, FL_status_string_write_not_length) == F_equal_to) {
        *code = F_write_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_write_only, length, FL_status_string_write_only_length) == F_equal_to) {
        *code = F_write_only;
        return F_none;
      }
    #endif // _di_F_status_basic_

    #ifndef _di_F_status_array_
      if (fl_string_compare(string, FL_status_string_array, length, FL_status_string_array_length) == F_equal_to) {
        *code = F_array;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_array_not, length, FL_status_string_array_not_length) == F_equal_to) {
        *code = F_array_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_array_too_large, length, FL_status_string_array_too_large_length) == F_equal_to) {
        *code = F_array_too_large;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_array_too_small, length, FL_status_string_array_too_small_length) == F_equal_to) {
        *code = F_array_too_small;
        return F_none;
      }
    #endif // _di_F_status_array_

    #ifndef _di_F_status_available_
      if (fl_string_compare(string, FL_status_string_available, length, FL_status_string_available_length) == F_equal_to) {
        *code = F_available;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not, length, FL_status_string_available_not_length) == F_equal_to) {
        *code = F_available_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_address, length, FL_status_string_available_not_address_length) == F_equal_to) {
        *code = F_available_not_address;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_buffer, length, FL_status_string_available_not_buffer_length) == F_equal_to) {
        *code = F_available_not_buffer;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_device, length, FL_status_string_available_not_device_length) == F_equal_to) {
        *code = F_available_not_device;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_pipe, length, FL_status_string_available_not_pipe_length) == F_equal_to) {
        *code = F_available_not_pipe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_port, length, FL_status_string_available_not_port_length) == F_equal_to) {
        *code = F_available_not_port;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_process, length, FL_status_string_available_not_process_length) == F_equal_to) {
        *code = F_available_not_process;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_available_not_socket, length, FL_status_string_available_not_socket_length) == F_equal_to) {
        *code = F_available_not_socket;
        return F_none;
      }
    #endif // _di_F_status_available_

    #ifndef _di_F_status_busy_
      if (fl_string_compare(string, FL_status_string_busy, length, FL_status_string_busy_length) == F_equal_to) {
        *code = F_busy;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_address, length, FL_status_string_busy_address_length) == F_equal_to) {
        *code = F_busy_address;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_buffer, length, FL_status_string_busy_buffer_length) == F_equal_to) {
        *code = F_busy_buffer;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_device, length, FL_status_string_busy_device_length) == F_equal_to) {
        *code = F_busy_device;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_not, length, FL_status_string_busy_not_length) == F_equal_to) {
        *code = F_busy_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_pipe, length, FL_status_string_busy_pipe_length) == F_equal_to) {
        *code = F_busy_pipe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_port, length, FL_status_string_busy_port_length) == F_equal_to) {
        *code = F_busy_port;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_process, length, FL_status_string_busy_process_length) == F_equal_to) {
        *code = F_busy_process;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_busy_socket, length, FL_status_string_busy_socket_length) == F_equal_to) {
        *code = F_busy_socket;
        return F_none;
      }
    #endif // _di_F_status_busy_

    #ifndef _di_F_status_number_
      if (fl_string_compare(string, FL_status_string_number, length, FL_status_string_number_length) == F_equal_to) {
        *code = F_number;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_decimal, length, FL_status_string_number_decimal_length) == F_equal_to) {
        *code = F_number_decimal;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_decimal_not, length, FL_status_string_number_decimal_not_length) == F_equal_to) {
        *code = F_number_decimal_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_divide_by_zero, length, FL_status_string_number_divide_by_zero_length) == F_equal_to) {
        *code = F_number_divide_by_zero;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_negative, length, FL_status_string_number_negative_length) == F_equal_to) {
        *code = F_number_negative;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_negative_not, length, FL_status_string_number_negative_not_length) == F_equal_to) {
        *code = F_number_negative_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_not, length, FL_status_string_number_not_length) == F_equal_to) {
        *code = F_number_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_overflow, length, FL_status_string_number_overflow_length) == F_equal_to) {
        *code = F_number_overflow;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_positive, length, FL_status_string_number_positive_length) == F_equal_to) {
        *code = F_number_positive;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_positive_not, length, FL_status_string_number_positive_not_length) == F_equal_to) {
        *code = F_number_positive_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_too_large, length, FL_status_string_number_too_large_length) == F_equal_to) {
        *code = F_number_too_large;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_too_small, length, FL_status_string_number_too_small_length) == F_equal_to) {
        *code = F_number_too_small;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_underflow, length, FL_status_string_number_underflow_length) == F_equal_to) {
        *code = F_number_underflow;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_whole, length, FL_status_string_number_whole_length) == F_equal_to) {
        *code = F_number_whole;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_whole_not, length, FL_status_string_number_whole_not_length) == F_equal_to) {
        *code = F_number_whole_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_zero, length, FL_status_string_number_zero_length) == F_equal_to) {
        *code = F_number_zero;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_number_zero_not, length, FL_status_string_number_zero_not_length) == F_equal_to) {
        *code = F_number_zero_not;
        return F_none;
      }
    #endif // _di_F_status_number_

    #ifndef _di_F_status_buffer_
      if (fl_string_compare(string, FL_status_string_buffer, length, FL_status_string_buffer_length) == F_equal_to) {
        *code = F_buffer;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_buffer_not, length, FL_status_string_buffer_not_length) == F_equal_to) {
        *code = F_buffer_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_buffer_too_large, length, FL_status_string_buffer_too_large_length) == F_equal_to) {
        *code = F_buffer_too_large;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_buffer_too_small, length, FL_status_string_buffer_too_small_length) == F_equal_to) {
        *code = F_buffer_too_small;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not_utf, length, FL_status_string_complete_not_utf_length) == F_equal_to) {
        *code = F_complete_not_utf;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not_utf_block, length, FL_status_string_complete_not_utf_block_length) == F_equal_to) {
        *code = F_complete_not_utf_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not_utf_eof, length, FL_status_string_complete_not_utf_eof_length) == F_equal_to) {
        *code = F_complete_not_utf_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not_utf_eol, length, FL_status_string_complete_not_utf_eol_length) == F_equal_to) {
        *code = F_complete_not_utf_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not_utf_eos, length, FL_status_string_complete_not_utf_eos_length) == F_equal_to) {
        *code = F_complete_not_utf_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_complete_not_utf_stop, length, FL_status_string_complete_not_utf_stop_length) == F_equal_to) {
        *code = F_complete_not_utf_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_none_block, length, FL_status_string_none_block_length) == F_equal_to) {
        *code = F_none_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_none_eof, length, FL_status_string_none_eof_length) == F_equal_to) {
        *code = F_none_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_none_eol, length, FL_status_string_none_eol_length) == F_equal_to) {
        *code = F_none_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_none_eos, length, FL_status_string_none_eos_length) == F_equal_to) {
        *code = F_none_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_none_stop, length, FL_status_string_none_stop_length) == F_equal_to) {
        *code = F_none_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data, length, FL_status_string_data_length) == F_equal_to) {
        *code = F_data;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data_not, length, FL_status_string_data_not_length) == F_equal_to) {
        *code = F_data_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data_not_block, length, FL_status_string_data_not_block_length) == F_equal_to) {
        *code = F_data_not_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data_not_eof, length, FL_status_string_data_not_eof_length) == F_equal_to) {
        *code = F_data_not_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data_not_eol, length, FL_status_string_data_not_eol_length) == F_equal_to) {
        *code = F_data_not_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data_not_eos, length, FL_status_string_data_not_eos_length) == F_equal_to) {
        *code = F_data_not_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_data_not_stop, length, FL_status_string_data_not_stop_length) == F_equal_to) {
        *code = F_data_not_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated, length, FL_status_string_terminated_length) == F_equal_to) {
        *code = F_terminated;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not, length, FL_status_string_terminated_not_length) == F_equal_to) {
        *code = F_terminated_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_block, length, FL_status_string_terminated_not_block_length) == F_equal_to) {
        *code = F_terminated_not_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_eof, length, FL_status_string_terminated_not_eof_length) == F_equal_to) {
        *code = F_terminated_not_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_eol, length, FL_status_string_terminated_not_eol_length) == F_equal_to) {
        *code = F_terminated_not_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_eos, length, FL_status_string_terminated_not_eos_length) == F_equal_to) {
        *code = F_terminated_not_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_group, length, FL_status_string_terminated_not_group_length) == F_equal_to) {
        *code = F_terminated_not_group;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_group_block, length, FL_status_string_terminated_not_group_block_length) == F_equal_to) {
        *code = F_terminated_not_group_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_group_eof, length, FL_status_string_terminated_not_group_eof_length) == F_equal_to) {
        *code = F_terminated_not_group_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_group_eol, length, FL_status_string_terminated_not_group_eol_length) == F_equal_to) {
        *code = F_terminated_not_group_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_group_eos, length, FL_status_string_terminated_not_group_eos_length) == F_equal_to) {
        *code = F_terminated_not_group_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_group_stop, length, FL_status_string_terminated_not_group_stop_length) == F_equal_to) {
        *code = F_terminated_not_group_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_nest, length, FL_status_string_terminated_not_nest_length) == F_equal_to) {
        *code = F_terminated_not_nest;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_nest_block, length, FL_status_string_terminated_not_nest_block_length) == F_equal_to) {
        *code = F_terminated_not_nest_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_nest_eof, length, FL_status_string_terminated_not_nest_eof_length) == F_equal_to) {
        *code = F_terminated_not_nest_eof;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_nest_eol, length, FL_status_string_terminated_not_nest_eol_length) == F_equal_to) {
        *code = F_terminated_not_nest_eol;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_nest_eos, length, FL_status_string_terminated_not_nest_eos_length) == F_equal_to) {
        *code = F_terminated_not_nest_eos;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_nest_stop, length, FL_status_string_terminated_not_nest_stop_length) == F_equal_to) {
        *code = F_terminated_not_nest_stop;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_terminated_not_stop, length, FL_status_string_terminated_not_stop_length) == F_equal_to) {
        *code = F_terminated_not_stop;
        return F_none;
      }
    #endif // _di_F_status_buffer_

    #ifndef _di_F_status_process_
      if (fl_string_compare(string, FL_status_string_process, length, FL_status_string_process_length) == F_equal_to) {
        *code = F_process;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_process_not, length, FL_status_string_process_not_length) == F_equal_to) {
        *code = F_process_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_process_too_many, length, FL_status_string_process_too_many_length) == F_equal_to) {
        *code = F_process_too_many;
        return F_none;
      }
    #endif // _di_F_status_process_

    #ifndef _di_F_status_file_
      if (fl_string_compare(string, FL_status_string_file, length, FL_status_string_file_length) == F_equal_to) {
        *code = F_file;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_allocation, length, FL_status_string_file_allocation_length) == F_equal_to) {
        *code = F_file_allocation;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_close, length, FL_status_string_file_close_length) == F_equal_to) {
        *code = F_file_close;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_closed, length, FL_status_string_file_closed_length) == F_equal_to) {
        *code = F_file_closed;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_deallocation, length, FL_status_string_file_deallocation_length) == F_equal_to) {
        *code = F_file_deallocation;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_descriptor, length, FL_status_string_file_descriptor_length) == F_equal_to) {
        *code = F_file_descriptor;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_descriptor_max, length, FL_status_string_file_descriptor_max_length) == F_equal_to) {
        *code = F_file_descriptor_max;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_empty, length, FL_status_string_file_empty_length) == F_equal_to) {
        *code = F_file_empty;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_flush, length, FL_status_string_file_flush_length) == F_equal_to) {
        *code = F_file_flush;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_found, length, FL_status_string_file_found_length) == F_equal_to) {
        *code = F_file_found;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_found_not, length, FL_status_string_file_found_not_length) == F_equal_to) {
        *code = F_file_found_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_not, length, FL_status_string_file_not_length) == F_equal_to) {
        *code = F_file_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_open, length, FL_status_string_file_open_length) == F_equal_to) {
        *code = F_file_open;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_open_max, length, FL_status_string_file_open_max_length) == F_equal_to) {
        *code = F_file_open_max;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_opened, length, FL_status_string_file_opened_length) == F_equal_to) {
        *code = F_file_opened;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_purge, length, FL_status_string_file_purge_length) == F_equal_to) {
        *code = F_file_purge;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_read, length, FL_status_string_file_read_length) == F_equal_to) {
        *code = F_file_read;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_reallocation, length, FL_status_string_file_reallocation_length) == F_equal_to) {
        *code = F_file_reallocation;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_seek, length, FL_status_string_file_seek_length) == F_equal_to) {
        *code = F_file_seek;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_stat, length, FL_status_string_file_stat_length) == F_equal_to) {
        *code = F_file_stat;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_synchronize, length, FL_status_string_file_synchronize_length) == F_equal_to) {
        *code = F_file_synchronize;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_block, length, FL_status_string_file_type_block_length) == F_equal_to) {
        *code = F_file_type_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_character, length, FL_status_string_file_type_character_length) == F_equal_to) {
        *code = F_file_type_character;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_directory, length, FL_status_string_file_type_directory_length) == F_equal_to) {
        *code = F_file_type_directory;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_link, length, FL_status_string_file_type_link_length) == F_equal_to) {
        *code = F_file_type_link;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_block, length, FL_status_string_file_type_not_block_length) == F_equal_to) {
        *code = F_file_type_not_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_character, length, FL_status_string_file_type_not_character_length) == F_equal_to) {
        *code = F_file_type_not_character;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_directory, length, FL_status_string_file_type_not_directory_length) == F_equal_to) {
        *code = F_file_type_not_directory;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_fifo, length, FL_status_string_file_type_not_fifo_length) == F_equal_to) {
        *code = F_file_type_not_fifo;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_link, length, FL_status_string_file_type_not_link_length) == F_equal_to) {
        *code = F_file_type_not_link;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_pipe, length, FL_status_string_file_type_not_pipe_length) == F_equal_to) {
        *code = F_file_type_not_pipe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_regular, length, FL_status_string_file_type_not_regular_length) == F_equal_to) {
        *code = F_file_type_not_regular;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_socket, length, FL_status_string_file_type_not_socket_length) == F_equal_to) {
        *code = F_file_type_not_socket;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_not_unknown, length, FL_status_string_file_type_not_unknown_length) == F_equal_to) {
        *code = F_file_type_not_unknown;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_pipe, length, FL_status_string_file_type_pipe_length) == F_equal_to) {
        *code = F_file_type_pipe;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_regular, length, FL_status_string_file_type_regular_length) == F_equal_to) {
        *code = F_file_type_regular;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_socket, length, FL_status_string_file_type_socket_length) == F_equal_to) {
        *code = F_file_type_socket;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_type_unknown, length, FL_status_string_file_type_unknown_length) == F_equal_to) {
        *code = F_file_type_unknown;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_utf, length, FL_status_string_file_utf_length) == F_equal_to) {
        *code = F_file_utf;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_utf_not, length, FL_status_string_file_utf_not_length) == F_equal_to) {
        *code = F_file_utf_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_file_write, length, FL_status_string_file_write_length) == F_equal_to) {
        *code = F_file_write;
        return F_none;
      }
    #endif // _di_F_status_file_

    #ifndef _di_F_status_filesystem_
      if (fl_string_compare(string, FL_status_string_filesystem, length, FL_status_string_filesystem_length) == F_equal_to) {
        *code = F_filesystem;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_filesystem_not, length, FL_status_string_filesystem_not_length) == F_equal_to) {
        *code = F_filesystem_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_filesystem_quota_block, length, FL_status_string_filesystem_quota_block_length) == F_equal_to) {
        *code = F_filesystem_quota_block;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_filesystem_quota_reached, length, FL_status_string_filesystem_quota_reached_length) == F_equal_to) {
        *code = F_filesystem_quota_reached;
        return F_none;
      }
    #endif // _di_F_status_filesystem_

    #ifndef _di_F_status_directory_
      if (fl_string_compare(string, FL_status_string_directory, length, FL_status_string_directory_length) == F_equal_to) {
        *code = F_directory;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_close, length, FL_status_string_directory_close_length) == F_equal_to) {
        *code = F_directory_close;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_closed, length, FL_status_string_directory_closed_length) == F_equal_to) {
        *code = F_directory_closed;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_descriptor, length, FL_status_string_directory_descriptor_length) == F_equal_to) {
        *code = F_directory_descriptor;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_empty, length, FL_status_string_directory_empty_length) == F_equal_to) {
        *code = F_directory_empty;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_empty_not, length, FL_status_string_directory_empty_not_length) == F_equal_to) {
        *code = F_directory_empty_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_found, length, FL_status_string_directory_found_length) == F_equal_to) {
        *code = F_directory_found;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_found_not, length, FL_status_string_directory_found_not_length) == F_equal_to) {
        *code = F_directory_found_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_flush, length, FL_status_string_directory_flush_length) == F_equal_to) {
        *code = F_directory_flush;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_link_max, length, FL_status_string_directory_link_max_length) == F_equal_to) {
        *code = F_directory_link_max;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_not, length, FL_status_string_directory_not_length) == F_equal_to) {
        *code = F_directory_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_open, length, FL_status_string_directory_open_length) == F_equal_to) {
        *code = F_directory_open;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_purge, length, FL_status_string_directory_purge_length) == F_equal_to) {
        *code = F_directory_purge;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_read, length, FL_status_string_directory_read_length) == F_equal_to) {
        *code = F_directory_read;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_stream, length, FL_status_string_directory_stream_length) == F_equal_to) {
        *code = F_directory_stream;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_synchronize, length, FL_status_string_directory_synchronize_length) == F_equal_to) {
        *code = F_directory_synchronize;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_unsupported, length, FL_status_string_directory_unsupported_length) == F_equal_to) {
        *code = F_directory_unsupported;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_utf, length, FL_status_string_directory_utf_length) == F_equal_to) {
        *code = F_directory_utf;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_utf_not, length, FL_status_string_directory_utf_not_length) == F_equal_to) {
        *code = F_directory_utf_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_directory_write, length, FL_status_string_directory_write_length) == F_equal_to) {
        *code = F_directory_write;
        return F_none;
      }
    #endif // _di_F_status_directory_

    #ifndef _di_F_status_socket_
      if (fl_string_compare(string, FL_status_string_socket, length, FL_status_string_socket_length) == F_equal_to) {
        *code = F_socket;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_socket_client, length, FL_status_string_socket_client_length) == F_equal_to) {
        *code = F_socket_client;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_socket_not, length, FL_status_string_socket_not_length) == F_equal_to) {
        *code = F_socket_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_socket_receive, length, FL_status_string_socket_receive_length) == F_equal_to) {
        *code = F_socket_receive;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_socket_send, length, FL_status_string_socket_send_length) == F_equal_to) {
        *code = F_socket_send;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_socket_target, length, FL_status_string_socket_target_length) == F_equal_to) {
        *code = F_socket_target;
        return F_none;
      }
    #endif // _di_F_status_socket_

    #ifndef _di_F_status_compare_
      if (fl_string_compare(string, FL_status_string_equal_to, length, FL_status_string_equal_to_length) == F_equal_to) {
        *code = F_equal_to;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_equal_to_not, length, FL_status_string_equal_to_not_length) == F_equal_to) {
        *code = F_equal_to_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_than_greater, length, FL_status_string_than_greater_length) == F_equal_to) {
        *code = F_than_greater;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_than_less, length, FL_status_string_than_less_length) == F_equal_to) {
        *code = F_than_less;
        return F_none;
      }
    #endif // _di_F_status_compare_

    #ifndef _di_F_status_access_
      if (fl_string_compare(string, FL_status_string_access, length, FL_status_string_access_length) == F_equal_to) {
        *code = F_access;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied, length, FL_status_string_access_denied_length) == F_equal_to) {
        *code = F_access_denied;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_user, length, FL_status_string_access_denied_user_length) == F_equal_to) {
        *code = F_access_denied_user;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_group, length, FL_status_string_access_denied_group_length) == F_equal_to) {
        *code = F_access_denied_group;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_world, length, FL_status_string_access_denied_world_length) == F_equal_to) {
        *code = F_access_denied_world;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_read, length, FL_status_string_access_denied_read_length) == F_equal_to) {
        *code = F_access_denied_read;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_write, length, FL_status_string_access_denied_write_length) == F_equal_to) {
        *code = F_access_denied_write;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_execute, length, FL_status_string_access_denied_execute_length) == F_equal_to) {
        *code = F_access_denied_execute;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_denied_super, length, FL_status_string_access_denied_super_length) == F_equal_to) {
        *code = F_access_denied_super;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted, length, FL_status_string_access_granted_length) == F_equal_to) {
        *code = F_access_granted;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_user, length, FL_status_string_access_granted_user_length) == F_equal_to) {
        *code = F_access_granted_user;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_group, length, FL_status_string_access_granted_group_length) == F_equal_to) {
        *code = F_access_granted_group;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_world, length, FL_status_string_access_granted_world_length) == F_equal_to) {
        *code = F_access_granted_world;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_read, length, FL_status_string_access_granted_read_length) == F_equal_to) {
        *code = F_access_granted_read;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_write, length, FL_status_string_access_granted_write_length) == F_equal_to) {
        *code = F_access_granted_write;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_execute, length, FL_status_string_access_granted_execute_length) == F_equal_to) {
        *code = F_access_granted_execute;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_granted_super, length, FL_status_string_access_granted_super_length) == F_equal_to) {
        *code = F_access_granted_super;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_group, length, FL_status_string_access_group_length) == F_equal_to) {
        *code = F_access_mode;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_mode, length, FL_status_string_access_mode_length) == F_equal_to) {
        *code = F_access_group;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_not, length, FL_status_string_access_not_length) == F_equal_to) {
        *code = F_access_not;
        return F_none;
      }

      if (fl_string_compare(string, FL_status_string_access_owner, length, FL_status_string_access_owner_length) == F_equal_to) {
        *code = F_access_owner;
        return F_none;
      }
    #endif // _di_F_status_access_

    if (fl_string_compare(string, FL_status_string_status_code_last, length, FL_status_string_status_code_last_length) == F_equal_to) {
      *code = F_status_code_last;
      return F_none;
    }

    return F_status_set_error(F_data);
  }
#endif // _di_fll_status_from_string_

#ifdef __cplusplus
} // extern "C"
#endif

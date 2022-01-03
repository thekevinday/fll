#include "status_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_status_string_from_
  f_status_t fll_status_string_from(const f_string_t string, f_status_t *code) {
    #ifndef _di_level_2_parameter_checking_
      if (!code) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t length = strlen(string);

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
      if (fl_string_compare(string, f_status_false_s, length, F_status_false_s_length) == F_equal_to) {
        *code = F_false;

        return F_none;
      }

      if (fl_string_compare(string, f_status_true_s, length, F_status_true_s_length) == F_equal_to) {
        *code = F_true;

        return F_none;
      }
    #endif // _di_F_status_boolean_

    #ifndef _di_F_status_signal_
      if (fl_string_compare(string, f_status_signal_hangup_s, length, F_status_signal_hangup_s_length) == F_equal_to) {
        *code = F_signal_hangup;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_interrupt_s, length, F_status_signal_interrupt_s_length) == F_equal_to) {
        *code = F_signal_interrupt;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_quit_s, length, F_status_signal_quit_s_length) == F_equal_to) {
        *code = F_signal_quit;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_illegal_s, length, F_status_signal_illegal_s_length) == F_equal_to) {
        *code = F_signal_illegal;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_trap_s, length, F_status_signal_trap_s_length) == F_equal_to) {
        *code = F_signal_trap;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_abort_s, length, F_status_signal_abort_s_length) == F_equal_to) {
        *code = F_signal_abort;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_bus_error_s, length, F_status_signal_bus_error_s_length) == F_equal_to) {
        *code = F_signal_bus_error;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_floating_point_error_s, length, F_status_signal_floating_point_error_s_length) == F_equal_to) {
        *code = F_signal_floating_point_error;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_kill_s, length, F_status_signal_kill_s_length) == F_equal_to) {
        *code = F_signal_kill;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_user_1_s, length, F_status_signal_user_1_s_length) == F_equal_to) {
        *code = F_signal_user_1;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_segmentation_fault_s, length, F_status_signal_segmentation_fault_s_length) == F_equal_to) {
        *code = F_signal_segmentation_fault;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_user_2_s, length, F_status_signal_user_2_s_length) == F_equal_to) {
        *code = F_signal_user_2;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_broken_pipe_s, length, F_status_signal_broken_pipe_s_length) == F_equal_to) {
        *code = F_signal_broken_pipe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_alarm_clock_s, length, F_status_signal_alarm_clock_s_length) == F_equal_to) {
        *code = F_signal_alarm_clock;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_termination_s, length, F_status_signal_termination_s_length) == F_equal_to) {
        *code = F_signal_termination;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_stack_fault_s, length, F_status_signal_stack_fault_s_length) == F_equal_to) {
        *code = F_signal_stack_fault;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_child_s, length, F_status_signal_child_s_length) == F_equal_to) {
        *code = F_signal_child;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_continue_s, length, F_status_signal_continue_s_length) == F_equal_to) {
        *code = F_signal_continue;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_stop_s, length, F_status_signal_stop_s_length) == F_equal_to) {
        *code = F_signal_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_keyboard_stop_s, length, F_status_signal_keyboard_stop_s_length) == F_equal_to) {
        *code = F_signal_keyboard_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_tty_in_s, length, F_status_signal_tty_in_s_length) == F_equal_to) {
        *code = F_signal_tty_in;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_tty_out_s, length, F_status_signal_tty_out_s_length) == F_equal_to) {
        *code = F_signal_tty_out;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_urgent_s, length, F_status_signal_urgent_s_length) == F_equal_to) {
        *code = F_signal_urgent;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_cpu_limit_s, length, F_status_signal_cpu_limit_s_length) == F_equal_to) {
        *code = F_signal_cpu_limit;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_file_size_limit_s, length, F_status_signal_file_size_limit_s_length) == F_equal_to) {
        *code = F_signal_file_size_limit;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_virtual_alarm_clock_s, length, F_status_signal_virtual_alarm_clock_s_length) == F_equal_to) {
        *code = F_signal_virtual_alarm_clock;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_profile_alarm_clock_s, length, F_status_signal_profile_alarm_clock_s_length) == F_equal_to) {
        *code = F_signal_profile_alarm_clock;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_window_size_change_s, length, F_status_signal_window_size_change_s_length) == F_equal_to) {
        *code = F_signal_window_size_change;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_pollable_event_s, length, F_status_signal_pollable_event_s_length) == F_equal_to) {
        *code = F_signal_pollable_event;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_power_failure_s, length, F_status_signal_power_failure_s_length) == F_equal_to) {
        *code = F_signal_power_failure;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_bad_system_call_s, length, F_status_signal_bad_system_call_s_length) == F_equal_to) {
        *code = F_signal_bad_system_call;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_32_s, length, F_status_signal_reserved_32_s_length) == F_equal_to) {
        *code = F_signal_reserved_32;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_33_s, length, F_status_signal_reserved_33_s_length) == F_equal_to) {
        *code = F_signal_reserved_33;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_34_s, length, F_status_signal_reserved_34_s_length) == F_equal_to) {
        *code = F_signal_reserved_34;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_35_s, length, F_status_signal_reserved_35_s_length) == F_equal_to) {
        *code = F_signal_reserved_35;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_36_s, length, F_status_signal_reserved_36_s_length) == F_equal_to) {
        *code = F_signal_reserved_36;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_37_s, length, F_status_signal_reserved_37_s_length) == F_equal_to) {
        *code = F_signal_reserved_37;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_38_s, length, F_status_signal_reserved_38_s_length) == F_equal_to) {
        *code = F_signal_reserved_38;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_39_s, length, F_status_signal_reserved_39_s_length) == F_equal_to) {
        *code = F_signal_reserved_39;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_40_s, length, F_status_signal_reserved_40_s_length) == F_equal_to) {
        *code = F_signal_reserved_40;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_41_s, length, F_status_signal_reserved_41_s_length) == F_equal_to) {
        *code = F_signal_reserved_41;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_42_s, length, F_status_signal_reserved_42_s_length) == F_equal_to) {
        *code = F_signal_reserved_42;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_43_s, length, F_status_signal_reserved_43_s_length) == F_equal_to) {
        *code = F_signal_reserved_43;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_44_s, length, F_status_signal_reserved_44_s_length) == F_equal_to) {
        *code = F_signal_reserved_44;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_45_s, length, F_status_signal_reserved_45_s_length) == F_equal_to) {
        *code = F_signal_reserved_45;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_46_s, length, F_status_signal_reserved_46_s_length) == F_equal_to) {
        *code = F_signal_reserved_46;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_47_s, length, F_status_signal_reserved_47_s_length) == F_equal_to) {
        *code = F_signal_reserved_47;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_48_s, length, F_status_signal_reserved_48_s_length) == F_equal_to) {
        *code = F_signal_reserved_48;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_49_s, length, F_status_signal_reserved_49_s_length) == F_equal_to) {
        *code = F_signal_reserved_49;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_50_s, length, F_status_signal_reserved_50_s_length) == F_equal_to) {
        *code = F_signal_reserved_50;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_51_s, length, F_status_signal_reserved_51_s_length) == F_equal_to) {
        *code = F_signal_reserved_51;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_52_s, length, F_status_signal_reserved_52_s_length) == F_equal_to) {
        *code = F_signal_reserved_52;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_53_s, length, F_status_signal_reserved_53_s_length) == F_equal_to) {
        *code = F_signal_reserved_53;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_54_s, length, F_status_signal_reserved_54_s_length) == F_equal_to) {
        *code = F_signal_reserved_54;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_55_s, length, F_status_signal_reserved_55_s_length) == F_equal_to) {
        *code = F_signal_reserved_55;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_56_s, length, F_status_signal_reserved_56_s_length) == F_equal_to) {
        *code = F_signal_reserved_56;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_57_s, length, F_status_signal_reserved_57_s_length) == F_equal_to) {
        *code = F_signal_reserved_57;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_58_s, length, F_status_signal_reserved_58_s_length) == F_equal_to) {
        *code = F_signal_reserved_58;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_59_s, length, F_status_signal_reserved_59_s_length) == F_equal_to) {
        *code = F_signal_reserved_59;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_60_s, length, F_status_signal_reserved_60_s_length) == F_equal_to) {
        *code = F_signal_reserved_60;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_61_s, length, F_status_signal_reserved_61_s_length) == F_equal_to) {
        *code = F_signal_reserved_61;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_62_s, length, F_status_signal_reserved_62_s_length) == F_equal_to) {
        *code = F_signal_reserved_62;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_63_s, length, F_status_signal_reserved_63_s_length) == F_equal_to) {
        *code = F_signal_reserved_63;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_reserved_64_s, length, F_status_signal_reserved_64_s_length) == F_equal_to) {
        *code = F_signal_reserved_64;

        return F_none;
      }
    #endif // _di_F_status_signal_

    #ifndef _di_F_status_basic_
      if (fl_string_compare(string, f_status_none_s, length, F_status_none_s_length) == F_equal_to) {
        *code = F_none;

        return F_none;
      }

      if (fl_string_compare(string, f_status_abort_s, length, F_status_abort_s_length) == F_equal_to) {
        *code = F_abort;

        return F_none;
      }

      if (fl_string_compare(string, f_status_abort_not_s, length, F_status_abort_not_s_length) == F_equal_to) {
        *code = F_abort_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_absolute_s, length, F_status_absolute_s_length) == F_equal_to) {
        *code = F_absolute;

        return F_none;
      }

      if (fl_string_compare(string, f_status_absolute_not_s, length, F_status_absolute_not_s_length) == F_equal_to) {
        *code = F_absolute_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_address_s, length, F_status_address_s_length) == F_equal_to) {
        *code = F_address;

        return F_none;
      }

      if (fl_string_compare(string, f_status_address_not_s, length, F_status_address_not_s_length) == F_equal_to) {
        *code = F_address_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_ascii_s, length, F_status_ascii_s_length) == F_equal_to) {
        *code = F_ascii;

        return F_none;
      }

      if (fl_string_compare(string, f_status_ascii_not_s, length, F_status_ascii_not_s_length) == F_equal_to) {
        *code = F_ascii_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_atomic_s, length, F_status_atomic_s_length) == F_equal_to) {
        *code = F_atomic;

        return F_none;
      }

      if (fl_string_compare(string, f_status_atomic_not_s, length, F_status_atomic_not_s_length) == F_equal_to) {
        *code = F_atomic_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_begin_s, length, F_status_begin_s_length) == F_equal_to) {
        *code = F_begin;

        return F_none;
      }

      if (fl_string_compare(string, f_status_begin_not_s, length, F_status_begin_not_s_length) == F_equal_to) {
        *code = F_begin_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_block_s, length, F_status_block_s_length) == F_equal_to) {
        *code = F_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_block_not_s, length, F_status_block_not_s_length) == F_equal_to) {
        *code = F_block_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_bound_s, length, F_status_bound_s_length) == F_equal_to) {
        *code = F_bound;

        return F_none;
      }

      if (fl_string_compare(string, f_status_bound_not_s, length, F_status_bound_not_s_length) == F_equal_to) {
        *code = F_bound_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_capability_s, length, F_status_capability_s_length) == F_equal_to) {
        *code = F_capability;

        return F_none;
      }

      if (fl_string_compare(string, f_status_capability_not_s, length, F_status_capability_not_s_length) == F_equal_to) {
        *code = F_capability_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_child_s, length, F_status_child_s_length) == F_equal_to) {
        *code = F_child;

        return F_none;
      }

      if (fl_string_compare(string, f_status_child_not_s, length, F_status_child_not_s_length) == F_equal_to) {
        *code = F_child_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_s, length, F_status_complete_s_length) == F_equal_to) {
        *code = F_complete;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_s, length, F_status_complete_not_s_length) == F_equal_to) {
        *code = F_complete_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_connect_s, length, F_status_connect_s_length) == F_equal_to) {
        *code = F_connect;

        return F_none;
      }

      if (fl_string_compare(string, f_status_connect_not_s, length, F_status_connect_not_s_length) == F_equal_to) {
        *code = F_connect_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_connect_refuse_s, length, F_status_connect_refuse_s_length) == F_equal_to) {
        *code = F_connect_refuse;

        return F_none;
      }

      if (fl_string_compare(string, f_status_connect_reset_s, length, F_status_connect_reset_s_length) == F_equal_to) {
        *code = F_connect_reset;

        return F_none;
      }

      if (fl_string_compare(string, f_status_container_s, length, F_status_container_s_length) == F_equal_to) {
        *code = F_container;

        return F_none;
      }

      if (fl_string_compare(string, f_status_container_not_s, length, F_status_container_not_s_length) == F_equal_to) {
        *code = F_container_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_continue_s, length, F_status_continue_s_length) == F_equal_to) {
        *code = F_continue;

        return F_none;
      }

      if (fl_string_compare(string, f_status_continue_not_s, length, F_status_continue_not_s_length) == F_equal_to) {
        *code = F_continue_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_control_s, length, F_status_control_s_length) == F_equal_to) {
        *code = F_control;

        return F_none;
      }

      if (fl_string_compare(string, f_status_control_not_s, length, F_status_control_not_s_length) == F_equal_to) {
        *code = F_control_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_control_group_s, length, F_status_control_group_s_length) == F_equal_to) {
        *code = F_control_group;

        return F_none;
      }

      if (fl_string_compare(string, f_status_control_group_not_s, length, F_status_control_group_not_s_length) == F_equal_to) {
        *code = F_control_group_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_critical_s, length, F_status_critical_s_length) == F_equal_to) {
        *code = F_critical;

        return F_none;
      }

      if (fl_string_compare(string, f_status_critical_not_s, length, F_status_critical_not_s_length) == F_equal_to) {
        *code = F_critical_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_dead_s, length, F_status_dead_s_length) == F_equal_to) {
        *code = F_dead;

        return F_none;
      }

      if (fl_string_compare(string, f_status_dead_not_s, length, F_status_dead_not_s_length) == F_equal_to) {
        *code = F_dead_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_deadlock_s, length, F_status_deadlock_s_length) == F_equal_to) {
        *code = F_deadlock;

        return F_none;
      }

      if (fl_string_compare(string, f_status_deadlock_not_s, length, F_status_deadlock_not_s_length) == F_equal_to) {
        *code = F_deadlock_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_descriptor_s, length, F_status_descriptor_s_length) == F_equal_to) {
        *code = F_descriptor;

        return F_none;
      }

      if (fl_string_compare(string, f_status_descriptor_not_s, length, F_status_descriptor_not_s_length) == F_equal_to) {
        *code = F_descriptor_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_device_s, length, F_status_device_s_length) == F_equal_to) {
        *code = F_device;

        return F_none;
      }

      if (fl_string_compare(string, f_status_device_not_s, length, F_status_device_not_s_length) == F_equal_to) {
        *code = F_device_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_disable_s, length, F_status_disable_s_length) == F_equal_to) {
        *code = F_disable;

        return F_none;
      }

      if (fl_string_compare(string, f_status_disable_not_s, length, F_status_disable_not_s_length) == F_equal_to) {
        *code = F_disable_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_domain_s, length, F_status_domain_s_length) == F_equal_to) {
        *code = F_domain;

        return F_none;
      }

      if (fl_string_compare(string, f_status_domain_not_s, length, F_status_domain_not_s_length) == F_equal_to) {
        *code = F_domain_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_done_s, length, F_status_done_s_length) == F_equal_to) {
        *code = F_done;

        return F_none;
      }

      if (fl_string_compare(string, f_status_done_not_s, length, F_status_done_not_s_length) == F_equal_to) {
        *code = F_done_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_dummy_s, length, F_status_dummy_s_length) == F_equal_to) {
        *code = F_dummy;

        return F_none;
      }

      if (fl_string_compare(string, f_status_dummy_not_s, length, F_status_dummy_not_s_length) == F_equal_to) {
        *code = F_dummy_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_empty_s, length, F_status_empty_s_length) == F_equal_to) {
        *code = F_empty;

        return F_none;
      }

      if (fl_string_compare(string, f_status_empty_not_s, length, F_status_empty_not_s_length) == F_equal_to) {
        *code = F_empty_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_enable_s, length, F_status_enable_s_length) == F_equal_to) {
        *code = F_enable;

        return F_none;
      }

      if (fl_string_compare(string, f_status_enable_not_s, length, F_status_enable_not_s_length) == F_equal_to) {
        *code = F_enable_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_encoding_s, length, F_status_encoding_s_length) == F_equal_to) {
        *code = F_encoding;

        return F_none;
      }

      if (fl_string_compare(string, f_status_encoding_not_s, length, F_status_encoding_not_s_length) == F_equal_to) {
        *code = F_encoding_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_end_s, length, F_status_end_s_length) == F_equal_to) {
        *code = F_end;

        return F_none;
      }

      if (fl_string_compare(string, f_status_end_not_s, length, F_status_end_not_s_length) == F_equal_to) {
        *code = F_end_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eoa_s, length, F_status_eoa_s_length) == F_equal_to) {
        *code = F_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eoa_not_s, length, F_status_eoa_not_s_length) == F_equal_to) {
        *code = F_eoa_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eof_s, length, F_status_eof_s_length) == F_equal_to) {
        *code = F_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eof_not_s, length, F_status_eof_not_s_length) == F_equal_to) {
        *code = F_eof_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eol_s, length, F_status_eol_s_length) == F_equal_to) {
        *code = F_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eol_not_s, length, F_status_eol_not_s_length) == F_equal_to) {
        *code = F_eol_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eos_s, length, F_status_eos_s_length) == F_equal_to) {
        *code = F_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_eos_not_s, length, F_status_eos_not_s_length) == F_equal_to) {
        *code = F_eos_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_execute_s, length, F_status_execute_s_length) == F_equal_to) {
        *code = F_execute;

        return F_none;
      }

      if (fl_string_compare(string, f_status_execute_not_s, length, F_status_execute_not_s_length) == F_equal_to) {
        *code = F_execute_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_exist_s, length, F_status_exist_s_length) == F_equal_to) {
        *code = F_exist;

        return F_none;
      }

      if (fl_string_compare(string, f_status_exist_not_s, length, F_status_exist_not_s_length) == F_equal_to) {
        *code = F_exist_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_failure_s, length, F_status_failure_s_length) == F_equal_to) {
        *code = F_failure;

        return F_none;
      }

      if (fl_string_compare(string, f_status_failure_not_s, length, F_status_failure_not_s_length) == F_equal_to) {
        *code = F_failure_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_family_s, length, F_status_family_s_length) == F_equal_to) {
        *code = F_family;

        return F_none;
      }

      if (fl_string_compare(string, f_status_family_not_s, length, F_status_family_not_s_length) == F_equal_to) {
        *code = F_family_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_first_s, length, F_status_first_s_length) == F_equal_to) {
        *code = F_first;

        return F_none;
      }

      if (fl_string_compare(string, f_status_first_not_s, length, F_status_first_not_s_length) == F_equal_to) {
        *code = F_first_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_fork_s, length, F_status_fork_s_length) == F_equal_to) {
        *code = F_fork;

        return F_none;
      }

      if (fl_string_compare(string, f_status_fork_not_s, length, F_status_fork_not_s_length) == F_equal_to) {
        *code = F_fork_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_format_s, length, F_status_format_s_length) == F_equal_to) {
        *code = F_format;

        return F_none;
      }

      if (fl_string_compare(string, f_status_format_not_s, length, F_status_format_not_s_length) == F_equal_to) {
        *code = F_format_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_found_s, length, F_status_found_s_length) == F_equal_to) {
        *code = F_found;

        return F_none;
      }

      if (fl_string_compare(string, f_status_found_not_s, length, F_status_found_not_s_length) == F_equal_to) {
        *code = F_found_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_full_s, length, F_status_full_s_length) == F_equal_to) {
        *code = F_full;

        return F_none;
      }

      if (fl_string_compare(string, f_status_full_not_s, length, F_status_full_not_s_length) == F_equal_to) {
        *code = F_full_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_group_s, length, F_status_group_s_length) == F_equal_to) {
        *code = F_group;

        return F_none;
      }

      if (fl_string_compare(string, f_status_group_not_s, length, F_status_group_not_s_length) == F_equal_to) {
        *code = F_group_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_ignore_s, length, F_status_ignore_s_length) == F_equal_to) {
        *code = F_ignore;

        return F_none;
      }

      if (fl_string_compare(string, f_status_ignore_not_s, length, F_status_ignore_not_s_length) == F_equal_to) {
        *code = F_ignore_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_implemented_s, length, F_status_implemented_s_length) == F_equal_to) {
        *code = F_implemented;

        return F_none;
      }

      if (fl_string_compare(string, f_status_implemented_not_s, length, F_status_implemented_not_s_length) == F_equal_to) {
        *code = F_implemented_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_input_s, length, F_status_input_s_length) == F_equal_to) {
        *code = F_input;

        return F_none;
      }

      if (fl_string_compare(string, f_status_input_not_s, length, F_status_input_not_s_length) == F_equal_to) {
        *code = F_input_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_input_output_s, length, F_status_input_output_s_length) == F_equal_to) {
        *code = F_input_output;

        return F_none;
      }

      if (fl_string_compare(string, f_status_interrupt_s, length, F_status_interrupt_s_length) == F_equal_to) {
        *code = F_interrupt;

        return F_none;
      }

      if (fl_string_compare(string, f_status_interrupt_not_s, length, F_status_interrupt_not_s_length) == F_equal_to) {
        *code = F_interrupt_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_known_s, length, F_status_known_s_length) == F_equal_to) {
        *code = F_known;

        return F_none;
      }

      if (fl_string_compare(string, f_status_known_not_s, length, F_status_known_not_s_length) == F_equal_to) {
        *code = F_known_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_last_s, length, F_status_last_s_length) == F_equal_to) {
        *code = F_last;

        return F_none;
      }

      if (fl_string_compare(string, f_status_last_not_s, length, F_status_last_not_s_length) == F_equal_to) {
        *code = F_last_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_limit_s, length, F_status_limit_s_length) == F_equal_to) {
        *code = F_limit;

        return F_none;
      }

      if (fl_string_compare(string, f_status_limit_not_s, length, F_status_limit_not_s_length) == F_equal_to) {
        *code = F_limit_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_link_s, length, F_status_link_s_length) == F_equal_to) {
        *code = F_link;

        return F_none;
      }

      if (fl_string_compare(string, f_status_link_not_s, length, F_status_link_not_s_length) == F_equal_to) {
        *code = F_link_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_live_s, length, F_status_live_s_length) == F_equal_to) {
        *code = F_live;

        return F_none;
      }

      if (fl_string_compare(string, f_status_live_not_s, length, F_status_live_not_s_length) == F_equal_to) {
        *code = F_live_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_lock_s, length, F_status_lock_s_length) == F_equal_to) {
        *code = F_lock;

        return F_none;
      }

      if (fl_string_compare(string, f_status_lock_not_s, length, F_status_lock_not_s_length) == F_equal_to) {
        *code = F_lock_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_loop_s, length, F_status_loop_s_length) == F_equal_to) {
        *code = F_loop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_loop_not_s, length, F_status_loop_not_s_length) == F_equal_to) {
        *code = F_loop_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_maybe_s, length, F_status_maybe_s_length) == F_equal_to) {
        *code = F_maybe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_maybe_not_s, length, F_status_maybe_not_s_length) == F_equal_to) {
        *code = F_maybe_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_memory_s, length, F_status_memory_s_length) == F_equal_to) {
        *code = F_memory;

        return F_none;
      }

      if (fl_string_compare(string, f_status_memory_not_s, length, F_status_memory_not_s_length) == F_equal_to) {
        *code = F_memory_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_message_s, length, F_status_message_s_length) == F_equal_to) {
        *code = F_message;

        return F_none;
      }

      if (fl_string_compare(string, f_status_message_not_s, length, F_status_message_not_s_length) == F_equal_to) {
        *code = F_message_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_minor_s, length, F_status_minor_s_length) == F_equal_to) {
        *code = F_minor;

        return F_none;
      }

      if (fl_string_compare(string, f_status_minor_not_s, length, F_status_minor_not_s_length) == F_equal_to) {
        *code = F_minor_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_moderate_s, length, F_status_moderate_s_length) == F_equal_to) {
        *code = F_moderate;

        return F_none;
      }

      if (fl_string_compare(string, f_status_moderate_not_s, length, F_status_moderate_not_s_length) == F_equal_to) {
        *code = F_moderate_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_mount_s, length, F_status_mount_s_length) == F_equal_to) {
        *code = F_mount;

        return F_none;
      }

      if (fl_string_compare(string, f_status_mount_not_s, length, F_status_mount_not_s_length) == F_equal_to) {
        *code = F_mount_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_name_s, length, F_status_name_s_length) == F_equal_to) {
        *code = F_name;

        return F_none;
      }

      if (fl_string_compare(string, f_status_name_not_s, length, F_status_name_not_s_length) == F_equal_to) {
        *code = F_name_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_next_s, length, F_status_next_s_length) == F_equal_to) {
        *code = F_next;

        return F_none;
      }

      if (fl_string_compare(string, f_status_next_not_s, length, F_status_next_not_s_length) == F_equal_to) {
        *code = F_next_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_nice_s, length, F_status_nice_s_length) == F_equal_to) {
        *code = F_nice;

        return F_none;
      }

      if (fl_string_compare(string, f_status_nice_not_s, length, F_status_nice_not_s_length) == F_equal_to) {
        *code = F_nice_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_option_s, length, F_status_option_s_length) == F_equal_to) {
        *code = F_option;

        return F_none;
      }

      if (fl_string_compare(string, f_status_option_not_s, length, F_status_option_not_s_length) == F_equal_to) {
        *code = F_option_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_output_s, length, F_status_output_s_length) == F_equal_to) {
        *code = F_output;

        return F_none;
      }

      if (fl_string_compare(string, f_status_output_not_s, length, F_status_output_not_s_length) == F_equal_to) {
        *code = F_output_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_parameter_s, length, F_status_parameter_s_length) == F_equal_to) {
        *code = F_parameter;

        return F_none;
      }

      if (fl_string_compare(string, f_status_parameter_not_s, length, F_status_parameter_not_s_length) == F_equal_to) {
        *code = F_parameter_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_parent_s, length, F_status_parent_s_length) == F_equal_to) {
        *code = F_parent;

        return F_none;
      }

      if (fl_string_compare(string, f_status_parent_not_s, length, F_status_parent_not_s_length) == F_equal_to) {
        *code = F_parent_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_pipe_s, length, F_status_pipe_s_length) == F_equal_to) {
        *code = F_pipe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_pipe_not_s, length, F_status_pipe_not_s_length) == F_equal_to) {
        *code = F_pipe_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_port_s, length, F_status_port_s_length) == F_equal_to) {
        *code = F_port;

        return F_none;
      }

      if (fl_string_compare(string, f_status_port_not_s, length, F_status_port_not_s_length) == F_equal_to) {
        *code = F_port_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_previous_s, length, F_status_previous_s_length) == F_equal_to) {
        *code = F_previous;

        return F_none;
      }

      if (fl_string_compare(string, f_status_previous_not_s, length, F_status_previous_not_s_length) == F_equal_to) {
        *code = F_previous_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_processor_s, length, F_status_processor_s_length) == F_equal_to) {
        *code = F_processor;

        return F_none;
      }

      if (fl_string_compare(string, f_status_processor_not_s, length, F_status_processor_not_s_length) == F_equal_to) {
        *code = F_processor_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_progress_s, length, F_status_progress_s_length) == F_equal_to) {
        *code = F_progress;

        return F_none;
      }

      if (fl_string_compare(string, f_status_progress_not_s, length, F_status_progress_not_s_length) == F_equal_to) {
        *code = F_progress_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_prohibited_s, length, F_status_prohibited_s_length) == F_equal_to) {
        *code = F_prohibited;

        return F_none;
      }

      if (fl_string_compare(string, f_status_prohibited_not_s, length, F_status_prohibited_not_s_length) == F_equal_to) {
        *code = F_prohibited_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_property_s, length, F_status_property_s_length) == F_equal_to) {
        *code = F_property;

        return F_none;
      }

      if (fl_string_compare(string, f_status_property_not_s, length, F_status_property_not_s_length) == F_equal_to) {
        *code = F_property_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_protocol_s, length, F_status_protocol_s_length) == F_equal_to) {
        *code = F_protocol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_protocol_not_s, length, F_status_protocol_not_s_length) == F_equal_to) {
        *code = F_protocol_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_range_s, length, F_status_range_s_length) == F_equal_to) {
        *code = F_range;

        return F_none;
      }

      if (fl_string_compare(string, f_status_range_not_s, length, F_status_range_not_s_length) == F_equal_to) {
        *code = F_range_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_read_s, length, F_status_read_s_length) == F_equal_to) {
        *code = F_read;

        return F_none;
      }

      if (fl_string_compare(string, f_status_read_not_s, length, F_status_read_not_s_length) == F_equal_to) {
        *code = F_read_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_read_only_s, length, F_status_read_only_s_length) == F_equal_to) {
        *code = F_read_only;

        return F_none;
      }

      if (fl_string_compare(string, f_status_ready_s, length, F_status_ready_s_length) == F_equal_to) {
        *code = F_ready;

        return F_none;
      }

      if (fl_string_compare(string, f_status_ready_not_s, length, F_status_ready_not_s_length) == F_equal_to) {
        *code = F_ready_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_recover_s, length, F_status_recover_s_length) == F_equal_to) {
        *code = F_recover;

        return F_none;
      }

      if (fl_string_compare(string, f_status_recover_not_s, length, F_status_recover_not_s_length) == F_equal_to) {
        *code = F_recover_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_recurse_s, length, F_status_recurse_s_length) == F_equal_to) {
        *code = F_recurse;

        return F_none;
      }

      if (fl_string_compare(string, f_status_recurse_not_s, length, F_status_recurse_not_s_length) == F_equal_to) {
        *code = F_recurse_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_relative_s, length, F_status_relative_s_length) == F_equal_to) {
        *code = F_relative;

        return F_none;
      }

      if (fl_string_compare(string, f_status_relative_not_s, length, F_status_relative_not_s_length) == F_equal_to) {
        *code = F_relative_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_require_s, length, F_status_require_s_length) == F_equal_to) {
        *code = F_require;

        return F_none;
      }

      if (fl_string_compare(string, f_status_require_not_s, length, F_status_require_not_s_length) == F_equal_to) {
        *code = F_require_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_resource_s, length, F_status_resource_s_length) == F_equal_to) {
        *code = F_resource;

        return F_none;
      }

      if (fl_string_compare(string, f_status_resource_not_s, length, F_status_resource_not_s_length) == F_equal_to) {
        *code = F_resource_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_search_s, length, F_status_search_s_length) == F_equal_to) {
        *code = F_search;

        return F_none;
      }

      if (fl_string_compare(string, f_status_search_not_s, length, F_status_search_not_s_length) == F_equal_to) {
        *code = F_search_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_schedule_s, length, F_status_schedule_s_length) == F_equal_to) {
        *code = F_schedule;

        return F_none;
      }

      if (fl_string_compare(string, f_status_schedule_not_s, length, F_status_schedule_not_s_length) == F_equal_to) {
        *code = F_schedule_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_size_s, length, F_status_size_s_length) == F_equal_to) {
        *code = F_size;

        return F_none;
      }

      if (fl_string_compare(string, f_status_size_not_s, length, F_status_size_not_s_length) == F_equal_to) {
        *code = F_size_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_s, length, F_status_signal_s_length) == F_equal_to) {
        *code = F_signal;

        return F_none;
      }

      if (fl_string_compare(string, f_status_signal_not_s, length, F_status_signal_not_s_length) == F_equal_to) {
        *code = F_signal_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_space_s, length, F_status_space_s_length) == F_equal_to) {
        *code = F_space;

        return F_none;
      }

      if (fl_string_compare(string, f_status_space_not_s, length, F_status_space_not_s_length) == F_equal_to) {
        *code = F_space_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_start_s, length, F_status_start_s_length) == F_equal_to) {
        *code = F_start;

        return F_none;
      }

      if (fl_string_compare(string, f_status_start_not_s, length, F_status_start_not_s_length) == F_equal_to) {
        *code = F_start_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_stop_s, length, F_status_stop_s_length) == F_equal_to) {
        *code = F_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_stop_not_s, length, F_status_stop_not_s_length) == F_equal_to) {
        *code = F_stop_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_stream_s, length, F_status_stream_s_length) == F_equal_to) {
        *code = F_stream;

        return F_none;
      }

      if (fl_string_compare(string, f_status_stream_not_s, length, F_status_stream_not_s_length) == F_equal_to) {
        *code = F_stream_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_string_s, length, F_status_string_s_length) == F_equal_to) {
        *code = F_string;

        return F_none;
      }

      if (fl_string_compare(string, f_status_string_not_s, length, F_status_string_not_s_length) == F_equal_to) {
        *code = F_string_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_string_too_large_s, length, F_status_string_too_large_s_length) == F_equal_to) {
        *code = F_string_too_large;

        return F_none;
      }

      if (fl_string_compare(string, f_status_string_too_small_s, length, F_status_string_too_small_s_length) == F_equal_to) {
        *code = F_string_too_small;

        return F_none;
      }

      if (fl_string_compare(string, f_status_success_s, length, F_status_success_s_length) == F_equal_to) {
        *code = F_success;

        return F_none;
      }

      if (fl_string_compare(string, f_status_success_not_s, length, F_status_success_not_s_length) == F_equal_to) {
        *code = F_success_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_supported_s, length, F_status_supported_s_length) == F_equal_to) {
        *code = F_supported;

        return F_none;
      }

      if (fl_string_compare(string, f_status_supported_not_s, length, F_status_supported_not_s_length) == F_equal_to) {
        *code = F_supported_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_syntax_s, length, F_status_syntax_s_length) == F_equal_to) {
        *code = F_syntax;

        return F_none;
      }

      if (fl_string_compare(string, f_status_syntax_not_s, length, F_status_syntax_not_s_length) == F_equal_to) {
        *code = F_syntax_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_thread_s, length, F_status_thread_s_length) == F_equal_to) {
        *code = F_thread;

        return F_none;
      }

      if (fl_string_compare(string, f_status_thread_not_s, length, F_status_thread_not_s_length) == F_equal_to) {
        *code = F_thread_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_time_s, length, F_status_time_s_length) == F_equal_to) {
        *code = F_time;

        return F_none;
      }

      if (fl_string_compare(string, f_status_time_not_s, length, F_status_time_not_s_length) == F_equal_to) {
        *code = F_time_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_time_out_s, length, F_status_time_out_s_length) == F_equal_to) {
        *code = F_time_out;

        return F_none;
      }

      if (fl_string_compare(string, f_status_too_large_s, length, F_status_too_large_s_length) == F_equal_to) {
        *code = F_too_large;

        return F_none;
      }

      if (fl_string_compare(string, f_status_too_small_s, length, F_status_too_small_s_length) == F_equal_to) {
        *code = F_too_small;

        return F_none;
      }

      if (fl_string_compare(string, f_status_type_s, length, F_status_type_s_length) == F_equal_to) {
        *code = F_type;

        return F_none;
      }

      if (fl_string_compare(string, f_status_type_not_s, length, F_status_type_not_s_length) == F_equal_to) {
        *code = F_type_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_user_s, length, F_status_user_s_length) == F_equal_to) {
        *code = F_user;

        return F_none;
      }

      if (fl_string_compare(string, f_status_user_not_s, length, F_status_user_not_s_length) == F_equal_to) {
        *code = F_user_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_utf_s, length, F_status_utf_s_length) == F_equal_to) {
        *code = F_utf;

        return F_none;
      }

      if (fl_string_compare(string, f_status_utf_fragment_s, length, F_status_utf_fragment_s_length) == F_equal_to) {
        *code = F_utf_fragment;

        return F_none;
      }

      if (fl_string_compare(string, f_status_utf_fragment_not_s, length, F_status_utf_fragment_not_s_length) == F_equal_to) {
        *code = F_utf_fragment_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_utf_not_s, length, F_status_utf_not_s_length) == F_equal_to) {
        *code = F_utf_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_valid_s, length, F_status_valid_s_length) == F_equal_to) {
        *code = F_valid;

        return F_none;
      }

      if (fl_string_compare(string, f_status_valid_not_s, length, F_status_valid_not_s_length) == F_equal_to) {
        *code = F_valid_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_value_s, length, F_status_value_s_length) == F_equal_to) {
        *code = F_value;

        return F_none;
      }

      if (fl_string_compare(string, f_status_value_not_s, length, F_status_value_not_s_length) == F_equal_to) {
        *code = F_value_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_wait_s, length, F_status_wait_s_length) == F_equal_to) {
        *code = F_wait;

        return F_none;
      }

      if (fl_string_compare(string, f_status_wait_not_s, length, F_status_wait_not_s_length) == F_equal_to) {
        *code = F_wait_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_warn_s, length, F_status_warn_s_length) == F_equal_to) {
        *code = F_warn;

        return F_none;
      }

      if (fl_string_compare(string, f_status_warn_not_s, length, F_status_warn_not_s_length) == F_equal_to) {
        *code = F_warn_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_world_s, length, F_status_world_s_length) == F_equal_to) {
        *code = F_world;

        return F_none;
      }

      if (fl_string_compare(string, f_status_world_not_s, length, F_status_world_not_s_length) == F_equal_to) {
        *code = F_world_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_write_s, length, F_status_write_s_length) == F_equal_to) {
        *code = F_write;

        return F_none;
      }

      if (fl_string_compare(string, f_status_write_not_s, length, F_status_write_not_s_length) == F_equal_to) {
        *code = F_write_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_write_only_s, length, F_status_write_only_s_length) == F_equal_to) {
        *code = F_write_only;

        return F_none;
      }
    #endif // _di_F_status_basic_

    #ifndef _di_F_status_array_
      if (fl_string_compare(string, f_status_array_s, length, F_status_array_s_length) == F_equal_to) {
        *code = F_array;

        return F_none;
      }

      if (fl_string_compare(string, f_status_array_not_s, length, F_status_array_not_s_length) == F_equal_to) {
        *code = F_array_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_array_too_large_s, length, F_status_array_too_large_s_length) == F_equal_to) {
        *code = F_array_too_large;

        return F_none;
      }

      if (fl_string_compare(string, f_status_array_too_small_s, length, F_status_array_too_small_s_length) == F_equal_to) {
        *code = F_array_too_small;

        return F_none;
      }
    #endif // _di_F_status_array_

    #ifndef _di_F_status_available_
      if (fl_string_compare(string, f_status_available_s, length, F_status_available_s_length) == F_equal_to) {
        *code = F_available;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_s, length, F_status_available_not_s_length) == F_equal_to) {
        *code = F_available_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_address_s, length, F_status_available_not_address_s_length) == F_equal_to) {
        *code = F_available_not_address;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_buffer_s, length, F_status_available_not_buffer_s_length) == F_equal_to) {
        *code = F_available_not_buffer;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_device_s, length, F_status_available_not_device_s_length) == F_equal_to) {
        *code = F_available_not_device;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_pipe_s, length, F_status_available_not_pipe_s_length) == F_equal_to) {
        *code = F_available_not_pipe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_port_s, length, F_status_available_not_port_s_length) == F_equal_to) {
        *code = F_available_not_port;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_process_s, length, F_status_available_not_process_s_length) == F_equal_to) {
        *code = F_available_not_process;

        return F_none;
      }

      if (fl_string_compare(string, f_status_available_not_socket_s, length, F_status_available_not_socket_s_length) == F_equal_to) {
        *code = F_available_not_socket;

        return F_none;
      }
    #endif // _di_F_status_available_

    #ifndef _di_F_status_busy_
      if (fl_string_compare(string, f_status_busy_s, length, F_status_busy_s_length) == F_equal_to) {
        *code = F_busy;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_address_s, length, F_status_busy_address_s_length) == F_equal_to) {
        *code = F_busy_address;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_buffer_s, length, F_status_busy_buffer_s_length) == F_equal_to) {
        *code = F_busy_buffer;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_device_s, length, F_status_busy_device_s_length) == F_equal_to) {
        *code = F_busy_device;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_not_s, length, F_status_busy_not_s_length) == F_equal_to) {
        *code = F_busy_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_pipe_s, length, F_status_busy_pipe_s_length) == F_equal_to) {
        *code = F_busy_pipe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_port_s, length, F_status_busy_port_s_length) == F_equal_to) {
        *code = F_busy_port;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_process_s, length, F_status_busy_process_s_length) == F_equal_to) {
        *code = F_busy_process;

        return F_none;
      }

      if (fl_string_compare(string, f_status_busy_socket_s, length, F_status_busy_socket_s_length) == F_equal_to) {
        *code = F_busy_socket;

        return F_none;
      }
    #endif // _di_F_status_busy_

    #ifndef _di_F_status_network_
      if (fl_string_compare(string, f_status_network_s, length, F_status_network_s_length) == F_equal_to) {
        *code = F_network;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_busy_s, length, F_status_network_busy_s_length) == F_equal_to) {
        *code = F_network_busy;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_busy_not_s, length, F_status_network_busy_not_s_length) == F_equal_to) {
        *code = F_network_busy_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_client_s, length, F_status_network_client_s_length) == F_equal_to) {
        *code = F_network_client;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_client_not_s, length, F_status_network_client_not_s_length) == F_equal_to) {
        *code = F_network_client_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_device_s, length, F_status_network_device_s_length) == F_equal_to) {
        *code = F_network_device;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_device_not_s, length, F_status_network_device_not_s_length) == F_equal_to) {
        *code = F_network_device_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_found_s, length, F_status_network_found_s_length) == F_equal_to) {
        *code = F_network_found;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_found_not_s, length, F_status_network_found_not_s_length) == F_equal_to) {
        *code = F_network_found_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_lost_s, length, F_status_network_lost_s_length) == F_equal_to) {
        *code = F_network_lost;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_lost_not_s, length, F_status_network_lost_not_s_length) == F_equal_to) {
        *code = F_network_lost_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_not_s, length, F_status_network_not_s_length) == F_equal_to) {
        *code = F_network_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_reach_s, length, F_status_network_reach_s_length) == F_equal_to) {
        *code = F_network_reach;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_reach_client_s, length, F_status_network_reach_client_s_length) == F_equal_to) {
        *code = F_network_reach_client;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_reach_client_not_s, length, F_status_network_reach_client_not_s_length) == F_equal_to) {
        *code = F_network_reach_client_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_reach_not_s, length, F_status_network_reach_not_s_length) == F_equal_to) {
        *code = F_network_reach_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_reach_server_s, length, F_status_network_reach_server_s_length) == F_equal_to) {
        *code = F_network_reach_server;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_reach_server_not_s, length, F_status_network_reach_server_not_s_length) == F_equal_to) {
        *code = F_network_reach_server_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_server_s, length, F_status_network_server_s_length) == F_equal_to) {
        *code = F_network_server;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_server_not_s, length, F_status_network_server_not_s_length) == F_equal_to) {
        *code = F_network_server_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_time_s, length, F_status_network_time_s_length) == F_equal_to) {
        *code = F_network_time;

        return F_none;
      }

      if (fl_string_compare(string, f_status_network_time_not_s, length, F_status_network_time_not_s_length) == F_equal_to) {
        *code = F_network_time_not;

        return F_none;
      }
    #endif // _di_F_status_network_

    #ifndef _di_F_status_number_
      if (fl_string_compare(string, f_status_number_s, length, F_status_number_s_length) == F_equal_to) {
        *code = F_number;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_decimal_s, length, F_status_number_decimal_s_length) == F_equal_to) {
        *code = F_number_decimal;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_decimal_not_s, length, F_status_number_decimal_not_s_length) == F_equal_to) {
        *code = F_number_decimal_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_divide_by_zero_s, length, F_status_number_divide_by_zero_s_length) == F_equal_to) {
        *code = F_number_divide_by_zero;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_negative_s, length, F_status_number_negative_s_length) == F_equal_to) {
        *code = F_number_negative;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_negative_not_s, length, F_status_number_negative_not_s_length) == F_equal_to) {
        *code = F_number_negative_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_not_s, length, F_status_number_not_s_length) == F_equal_to) {
        *code = F_number_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_overflow_s, length, F_status_number_overflow_s_length) == F_equal_to) {
        *code = F_number_overflow;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_positive_s, length, F_status_number_positive_s_length) == F_equal_to) {
        *code = F_number_positive;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_positive_not_s, length, F_status_number_positive_not_s_length) == F_equal_to) {
        *code = F_number_positive_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_too_large_s, length, F_status_number_too_large_s_length) == F_equal_to) {
        *code = F_number_too_large;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_too_small_s, length, F_status_number_too_small_s_length) == F_equal_to) {
        *code = F_number_too_small;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_underflow_s, length, F_status_number_underflow_s_length) == F_equal_to) {
        *code = F_number_underflow;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_whole_s, length, F_status_number_whole_s_length) == F_equal_to) {
        *code = F_number_whole;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_whole_not_s, length, F_status_number_whole_not_s_length) == F_equal_to) {
        *code = F_number_whole_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_zero_s, length, F_status_number_zero_s_length) == F_equal_to) {
        *code = F_number_zero;

        return F_none;
      }

      if (fl_string_compare(string, f_status_number_zero_not_s, length, F_status_number_zero_not_s_length) == F_equal_to) {
        *code = F_number_zero_not;

        return F_none;
      }
    #endif // _di_F_status_number_

    #ifndef _di_F_status_buffer_
      if (fl_string_compare(string, f_status_buffer_s, length, F_status_buffer_s_length) == F_equal_to) {
        *code = F_buffer;

        return F_none;
      }

      if (fl_string_compare(string, f_status_buffer_not_s, length, F_status_buffer_not_s_length) == F_equal_to) {
        *code = F_buffer_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_buffer_too_large_s, length, F_status_buffer_too_large_s_length) == F_equal_to) {
        *code = F_buffer_too_large;

        return F_none;
      }

      if (fl_string_compare(string, f_status_buffer_too_small_s, length, F_status_buffer_too_small_s_length) == F_equal_to) {
        *code = F_buffer_too_small;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_s, length, F_status_complete_not_utf_s_length) == F_equal_to) {
        *code = F_complete_not_utf;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_block_s, length, F_status_complete_not_utf_block_s_length) == F_equal_to) {
        *code = F_complete_not_utf_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_eoa_s, length, F_status_complete_not_utf_eoa_s_length) == F_equal_to) {
        *code = F_complete_not_utf_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_eof_s, length, F_status_complete_not_utf_eof_s_length) == F_equal_to) {
        *code = F_complete_not_utf_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_eol_s, length, F_status_complete_not_utf_eol_s_length) == F_equal_to) {
        *code = F_complete_not_utf_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_eos_s, length, F_status_complete_not_utf_eos_s_length) == F_equal_to) {
        *code = F_complete_not_utf_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_complete_not_utf_stop_s, length, F_status_complete_not_utf_stop_s_length) == F_equal_to) {
        *code = F_complete_not_utf_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_none_block_s, length, F_status_none_block_s_length) == F_equal_to) {
        *code = F_none_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_none_eoa_s, length, F_status_none_eoa_s_length) == F_equal_to) {
        *code = F_none_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_none_eof_s, length, F_status_none_eof_s_length) == F_equal_to) {
        *code = F_none_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_none_eol_s, length, F_status_none_eol_s_length) == F_equal_to) {
        *code = F_none_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_none_eos_s, length, F_status_none_eos_s_length) == F_equal_to) {
        *code = F_none_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_none_stop_s, length, F_status_none_stop_s_length) == F_equal_to) {
        *code = F_none_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_s, length, F_status_data_s_length) == F_equal_to) {
        *code = F_data;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_s, length, F_status_data_not_s_length) == F_equal_to) {
        *code = F_data_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_block_s, length, F_status_data_not_block_s_length) == F_equal_to) {
        *code = F_data_not_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_eoa_s, length, F_status_data_not_eoa_s_length) == F_equal_to) {
        *code = F_data_not_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_eof_s, length, F_status_data_not_eof_s_length) == F_equal_to) {
        *code = F_data_not_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_eol_s, length, F_status_data_not_eol_s_length) == F_equal_to) {
        *code = F_data_not_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_eos_s, length, F_status_data_not_eos_s_length) == F_equal_to) {
        *code = F_data_not_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_data_not_stop_s, length, F_status_data_not_stop_s_length) == F_equal_to) {
        *code = F_data_not_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_s, length, F_status_terminated_s_length) == F_equal_to) {
        *code = F_terminated;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_s, length, F_status_terminated_not_s_length) == F_equal_to) {
        *code = F_terminated_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_block_s, length, F_status_terminated_not_block_s_length) == F_equal_to) {
        *code = F_terminated_not_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_eoa_s, length, F_status_terminated_not_eoa_s_length) == F_equal_to) {
        *code = F_terminated_not_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_eof_s, length, F_status_terminated_not_eof_s_length) == F_equal_to) {
        *code = F_terminated_not_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_eol_s, length, F_status_terminated_not_eol_s_length) == F_equal_to) {
        *code = F_terminated_not_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_eos_s, length, F_status_terminated_not_eos_s_length) == F_equal_to) {
        *code = F_terminated_not_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_s, length, F_status_terminated_not_group_s_length) == F_equal_to) {
        *code = F_terminated_not_group;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_block_s, length, F_status_terminated_not_group_block_s_length) == F_equal_to) {
        *code = F_terminated_not_group_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_eoa_s, length, F_status_terminated_not_group_eoa_s_length) == F_equal_to) {
        *code = F_terminated_not_group_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_eof_s, length, F_status_terminated_not_group_eof_s_length) == F_equal_to) {
        *code = F_terminated_not_group_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_eol_s, length, F_status_terminated_not_group_eol_s_length) == F_equal_to) {
        *code = F_terminated_not_group_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_eos_s, length, F_status_terminated_not_group_eos_s_length) == F_equal_to) {
        *code = F_terminated_not_group_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_group_stop_s, length, F_status_terminated_not_group_stop_s_length) == F_equal_to) {
        *code = F_terminated_not_group_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_s, length, F_status_terminated_not_nest_s_length) == F_equal_to) {
        *code = F_terminated_not_nest;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_block_s, length, F_status_terminated_not_nest_block_s_length) == F_equal_to) {
        *code = F_terminated_not_nest_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_eoa_s, length, F_status_terminated_not_nest_eoa_s_length) == F_equal_to) {
        *code = F_terminated_not_nest_eoa;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_eof_s, length, F_status_terminated_not_nest_eof_s_length) == F_equal_to) {
        *code = F_terminated_not_nest_eof;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_eol_s, length, F_status_terminated_not_nest_eol_s_length) == F_equal_to) {
        *code = F_terminated_not_nest_eol;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_eos_s, length, F_status_terminated_not_nest_eos_s_length) == F_equal_to) {
        *code = F_terminated_not_nest_eos;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_nest_stop_s, length, F_status_terminated_not_nest_stop_s_length) == F_equal_to) {
        *code = F_terminated_not_nest_stop;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminated_not_stop_s, length, F_status_terminated_not_stop_s_length) == F_equal_to) {
        *code = F_terminated_not_stop;

        return F_none;
      }
    #endif // _di_F_status_buffer_

    #ifndef _di_F_status_process_
      if (fl_string_compare(string, f_status_process_s, length, F_status_process_s_length) == F_equal_to) {
        *code = F_process;

        return F_none;
      }

      if (fl_string_compare(string, f_status_process_not_s, length, F_status_process_not_s_length) == F_equal_to) {
        *code = F_process_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_process_too_many_s, length, F_status_process_too_many_s_length) == F_equal_to) {
        *code = F_process_too_many;

        return F_none;
      }
    #endif // _di_F_status_process_

    #ifndef _di_F_status_file_
      if (fl_string_compare(string, f_status_file_s, length, F_status_file_s_length) == F_equal_to) {
        *code = F_file;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_close_s, length, F_status_file_close_s_length) == F_equal_to) {
        *code = F_file_close;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_closed_s, length, F_status_file_closed_s_length) == F_equal_to) {
        *code = F_file_closed;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_descriptor_s, length, F_status_file_descriptor_s_length) == F_equal_to) {
        *code = F_file_descriptor;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_descriptor_max_s, length, F_status_file_descriptor_max_s_length) == F_equal_to) {
        *code = F_file_descriptor_max;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_descriptor_not_s, length, F_status_file_descriptor_not_s_length) == F_equal_to) {
        *code = F_file_descriptor_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_empty_s, length, F_status_file_empty_s_length) == F_equal_to) {
        *code = F_file_empty;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_flush_s, length, F_status_file_flush_s_length) == F_equal_to) {
        *code = F_file_flush;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_found_s, length, F_status_file_found_s_length) == F_equal_to) {
        *code = F_file_found;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_found_not_s, length, F_status_file_found_not_s_length) == F_equal_to) {
        *code = F_file_found_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_not_s, length, F_status_file_not_s_length) == F_equal_to) {
        *code = F_file_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_open_s, length, F_status_file_open_s_length) == F_equal_to) {
        *code = F_file_open;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_open_max_s, length, F_status_file_open_max_s_length) == F_equal_to) {
        *code = F_file_open_max;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_opened_s, length, F_status_file_opened_s_length) == F_equal_to) {
        *code = F_file_opened;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_overflow_s, length, F_status_file_overflow_s_length) == F_equal_to) {
        *code = F_file_overflow;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_purge_s, length, F_status_file_purge_s_length) == F_equal_to) {
        *code = F_file_purge;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_read_s, length, F_status_file_read_s_length) == F_equal_to) {
        *code = F_file_read;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_reallocation_s, length, F_status_file_reallocation_s_length) == F_equal_to) {
        *code = F_file_reallocation;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_seek_s, length, F_status_file_seek_s_length) == F_equal_to) {
        *code = F_file_seek;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_stat_s, length, F_status_file_stat_s_length) == F_equal_to) {
        *code = F_file_stat;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_synchronize_s, length, F_status_file_synchronize_s_length) == F_equal_to) {
        *code = F_file_synchronize;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_block_s, length, F_status_file_type_block_s_length) == F_equal_to) {
        *code = F_file_type_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_character_s, length, F_status_file_type_character_s_length) == F_equal_to) {
        *code = F_file_type_character;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_directory_s, length, F_status_file_type_directory_s_length) == F_equal_to) {
        *code = F_file_type_directory;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_link_s, length, F_status_file_type_link_s_length) == F_equal_to) {
        *code = F_file_type_link;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_block_s, length, F_status_file_type_not_block_s_length) == F_equal_to) {
        *code = F_file_type_not_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_character_s, length, F_status_file_type_not_character_s_length) == F_equal_to) {
        *code = F_file_type_not_character;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_directory_s, length, F_status_file_type_not_directory_s_length) == F_equal_to) {
        *code = F_file_type_not_directory;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_fifo_s, length, F_status_file_type_not_fifo_s_length) == F_equal_to) {
        *code = F_file_type_not_fifo;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_link_s, length, F_status_file_type_not_link_s_length) == F_equal_to) {
        *code = F_file_type_not_link;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_pipe_s, length, F_status_file_type_not_pipe_s_length) == F_equal_to) {
        *code = F_file_type_not_pipe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_regular_s, length, F_status_file_type_not_regular_s_length) == F_equal_to) {
        *code = F_file_type_not_regular;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_socket_s, length, F_status_file_type_not_socket_s_length) == F_equal_to) {
        *code = F_file_type_not_socket;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_not_unknown_s, length, F_status_file_type_not_unknown_s_length) == F_equal_to) {
        *code = F_file_type_not_unknown;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_pipe_s, length, F_status_file_type_pipe_s_length) == F_equal_to) {
        *code = F_file_type_pipe;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_regular_s, length, F_status_file_type_regular_s_length) == F_equal_to) {
        *code = F_file_type_regular;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_socket_s, length, F_status_file_type_socket_s_length) == F_equal_to) {
        *code = F_file_type_socket;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_type_unknown_s, length, F_status_file_type_unknown_s_length) == F_equal_to) {
        *code = F_file_type_unknown;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_underflow_s, length, F_status_file_underflow_s_length) == F_equal_to) {
        *code = F_file_underflow;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_utf_s, length, F_status_file_utf_s_length) == F_equal_to) {
        *code = F_file_utf;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_utf_not_s, length, F_status_file_utf_not_s_length) == F_equal_to) {
        *code = F_file_utf_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_file_write_s, length, F_status_file_write_s_length) == F_equal_to) {
        *code = F_file_write;

        return F_none;
      }
    #endif // _di_F_status_file_

    #ifndef _di_F_status_filesystem_
      if (fl_string_compare(string, f_status_filesystem_s, length, F_status_filesystem_s_length) == F_equal_to) {
        *code = F_filesystem;

        return F_none;
      }

      if (fl_string_compare(string, f_status_filesystem_not_s, length, F_status_filesystem_not_s_length) == F_equal_to) {
        *code = F_filesystem_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_filesystem_quota_block_s, length, F_status_filesystem_quota_block_s_length) == F_equal_to) {
        *code = F_filesystem_quota_block;

        return F_none;
      }

      if (fl_string_compare(string, f_status_filesystem_quota_reached_s, length, F_status_filesystem_quota_reached_s_length) == F_equal_to) {
        *code = F_filesystem_quota_reached;

        return F_none;
      }
    #endif // _di_F_status_filesystem_

    #ifndef _di_F_status_directory_
      if (fl_string_compare(string, f_status_directory_s, length, F_status_directory_s_length) == F_equal_to) {
        *code = F_directory;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_close_s, length, F_status_directory_close_s_length) == F_equal_to) {
        *code = F_directory_close;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_closed_s, length, F_status_directory_closed_s_length) == F_equal_to) {
        *code = F_directory_closed;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_descriptor_s, length, F_status_directory_descriptor_s_length) == F_equal_to) {
        *code = F_directory_descriptor;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_empty_s, length, F_status_directory_empty_s_length) == F_equal_to) {
        *code = F_directory_empty;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_empty_not_s, length, F_status_directory_empty_not_s_length) == F_equal_to) {
        *code = F_directory_empty_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_found_s, length, F_status_directory_found_s_length) == F_equal_to) {
        *code = F_directory_found;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_found_not_s, length, F_status_directory_found_not_s_length) == F_equal_to) {
        *code = F_directory_found_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_flush_s, length, F_status_directory_flush_s_length) == F_equal_to) {
        *code = F_directory_flush;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_link_max_s, length, F_status_directory_link_max_s_length) == F_equal_to) {
        *code = F_directory_link_max;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_not_s, length, F_status_directory_not_s_length) == F_equal_to) {
        *code = F_directory_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_open_s, length, F_status_directory_open_s_length) == F_equal_to) {
        *code = F_directory_open;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_purge_s, length, F_status_directory_purge_s_length) == F_equal_to) {
        *code = F_directory_purge;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_read_s, length, F_status_directory_read_s_length) == F_equal_to) {
        *code = F_directory_read;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_stream_s, length, F_status_directory_stream_s_length) == F_equal_to) {
        *code = F_directory_stream;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_supported_not_s, length, F_status_directory_supported_not_s_length) == F_equal_to) {
        *code = F_directory_supported_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_synchronize_s, length, F_status_directory_synchronize_s_length) == F_equal_to) {
        *code = F_directory_synchronize;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_utf_s, length, F_status_directory_utf_s_length) == F_equal_to) {
        *code = F_directory_utf;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_utf_not_s, length, F_status_directory_utf_not_s_length) == F_equal_to) {
        *code = F_directory_utf_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_directory_write_s, length, F_status_directory_write_s_length) == F_equal_to) {
        *code = F_directory_write;

        return F_none;
      }
    #endif // _di_F_status_directory_

    #ifndef _di_F_status_socket_
      if (fl_string_compare(string, f_status_socket_s, length, F_status_socket_s_length) == F_equal_to) {
        *code = F_socket;

        return F_none;
      }

      if (fl_string_compare(string, f_status_socket_client_s, length, F_status_socket_client_s_length) == F_equal_to) {
        *code = F_socket_client;

        return F_none;
      }

      if (fl_string_compare(string, f_status_socket_not_s, length, F_status_socket_not_s_length) == F_equal_to) {
        *code = F_socket_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_socket_receive_s, length, F_status_socket_receive_s_length) == F_equal_to) {
        *code = F_socket_receive;

        return F_none;
      }

      if (fl_string_compare(string, f_status_socket_send_s, length, F_status_socket_send_s_length) == F_equal_to) {
        *code = F_socket_send;

        return F_none;
      }

      if (fl_string_compare(string, f_status_socket_target_s, length, F_status_socket_target_s_length) == F_equal_to) {
        *code = F_socket_target;

        return F_none;
      }
    #endif // _di_F_status_socket_

    #ifndef _di_F_status_compare_
      if (fl_string_compare(string, f_status_equal_to_s, length, F_status_equal_to_s_length) == F_equal_to) {
        *code = F_equal_to;

        return F_none;
      }

      if (fl_string_compare(string, f_status_equal_to_not_s, length, F_status_equal_to_not_s_length) == F_equal_to) {
        *code = F_equal_to_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_than_greater_s, length, F_status_than_greater_s_length) == F_equal_to) {
        *code = F_than_greater;

        return F_none;
      }

      if (fl_string_compare(string, f_status_than_less_s, length, F_status_than_less_s_length) == F_equal_to) {
        *code = F_than_less;

        return F_none;
      }
    #endif // _di_F_status_compare_

    #ifndef _di_F_status_access_
      if (fl_string_compare(string, f_status_access_s, length, F_status_access_s_length) == F_equal_to) {
        *code = F_access;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_s, length, F_status_access_denied_s_length) == F_equal_to) {
        *code = F_access_denied;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_user_s, length, F_status_access_denied_user_s_length) == F_equal_to) {
        *code = F_access_denied_user;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_group_s, length, F_status_access_denied_group_s_length) == F_equal_to) {
        *code = F_access_denied_group;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_world_s, length, F_status_access_denied_world_s_length) == F_equal_to) {
        *code = F_access_denied_world;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_read_s, length, F_status_access_denied_read_s_length) == F_equal_to) {
        *code = F_access_denied_read;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_write_s, length, F_status_access_denied_write_s_length) == F_equal_to) {
        *code = F_access_denied_write;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_execute_s, length, F_status_access_denied_execute_s_length) == F_equal_to) {
        *code = F_access_denied_execute;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_denied_super_s, length, F_status_access_denied_super_s_length) == F_equal_to) {
        *code = F_access_denied_super;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_s, length, F_status_access_granted_s_length) == F_equal_to) {
        *code = F_access_granted;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_user_s, length, F_status_access_granted_user_s_length) == F_equal_to) {
        *code = F_access_granted_user;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_group_s, length, F_status_access_granted_group_s_length) == F_equal_to) {
        *code = F_access_granted_group;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_world_s, length, F_status_access_granted_world_s_length) == F_equal_to) {
        *code = F_access_granted_world;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_read_s, length, F_status_access_granted_read_s_length) == F_equal_to) {
        *code = F_access_granted_read;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_write_s, length, F_status_access_granted_write_s_length) == F_equal_to) {
        *code = F_access_granted_write;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_execute_s, length, F_status_access_granted_execute_s_length) == F_equal_to) {
        *code = F_access_granted_execute;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_granted_super_s, length, F_status_access_granted_super_s_length) == F_equal_to) {
        *code = F_access_granted_super;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_group_s, length, F_status_access_group_s_length) == F_equal_to) {
        *code = F_access_mode;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_mode_s, length, F_status_access_mode_s_length) == F_equal_to) {
        *code = F_access_group;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_not_s, length, F_status_access_not_s_length) == F_equal_to) {
        *code = F_access_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_access_owner_s, length, F_status_access_owner_s_length) == F_equal_to) {
        *code = F_access_owner;

        return F_none;
      }
    #endif // _di_F_status_access_

    #ifndef _di_F_status_terminal_
      if (fl_string_compare(string, f_status_terminal_s, length, F_status_terminal_s_length) == F_equal_to) {
        *code = F_terminal;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_access_s, length, F_status_terminal_access_s_length) == F_equal_to) {
        *code = F_terminal_access;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_known_s, length, F_status_terminal_known_s_length) == F_equal_to) {
        *code = F_terminal_known;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_known_not_s, length, F_status_terminal_known_not_s_length) == F_equal_to) {
        *code = F_terminal_known_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_not_s, length, F_status_terminal_not_s_length) == F_equal_to) {
        *code = F_terminal_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_prohibited_s, length, F_status_terminal_prohibited_s_length) == F_equal_to) {
        *code = F_terminal_prohibited;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_read_s, length, F_status_terminal_read_s_length) == F_equal_to) {
        *code = F_terminal_read;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_valid_s, length, F_status_terminal_valid_s_length) == F_equal_to) {
        *code = F_terminal_valid;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_valid_not_s, length, F_status_terminal_valid_not_s_length) == F_equal_to) {
        *code = F_terminal_valid_not;

        return F_none;
      }

      if (fl_string_compare(string, f_status_terminal_write_s, length, F_status_terminal_write_s_length) == F_equal_to) {
        *code = F_terminal_write;

        return F_none;
      }
    #endif // _di_F_status_terminal_

    if (fl_string_compare(string, f_status_status_code_last_s, length, F_status_status_code_last_s_length) == F_equal_to) {
      *code = F_status_code_last;

      return F_none;
    }

    return F_status_set_error(F_data);
  }
#endif // _di_fll_status_string_from_

#ifdef __cplusplus
} // extern "C"
#endif

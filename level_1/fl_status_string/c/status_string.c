#include "status_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_status_string_from_
  f_status_t fl_status_string_from(const f_string_static_t name, f_status_t * const code) {
    #ifndef _di_level_2_parameter_checking_
      if (!code) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    if (!name.used) return F_data_not;

    // Numbers are not valid status code strings.
    if ((status = f_conversion_character_is_decimal(name.string[0])) == F_true) return F_status_set_error(F_data);
    if (F_status_is_error(status)) return status;

    #ifndef _di_f_status_boolean_s_
      if (f_compare_dynamic(name, f_status_false_s) == F_equal_to) {
        *code = F_false;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_true_s) == F_equal_to) {
        *code = F_true;

        return F_none;
      }
    #endif // _di_f_status_boolean_s_

    #ifndef _di_f_status_signal_s_
      if (f_compare_dynamic(name, f_status_signal_hangup_s) == F_equal_to) {
        *code = F_signal_hangup;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_interrupt_s) == F_equal_to) {
        *code = F_signal_interrupt;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_quit_s) == F_equal_to) {
        *code = F_signal_quit;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_illegal_s) == F_equal_to) {
        *code = F_signal_illegal;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_trap_s) == F_equal_to) {
        *code = F_signal_trap;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_abort_s) == F_equal_to) {
        *code = F_signal_abort;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_bus_error_s) == F_equal_to) {
        *code = F_signal_bus_error;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_floating_point_error_s) == F_equal_to) {
        *code = F_signal_floating_point_error;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_kill_s) == F_equal_to) {
        *code = F_signal_kill;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_user_1_s) == F_equal_to) {
        *code = F_signal_user_1;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_segmentation_fault_s) == F_equal_to) {
        *code = F_signal_segmentation_fault;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_user_2_s) == F_equal_to) {
        *code = F_signal_user_2;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_broken_pipe_s) == F_equal_to) {
        *code = F_signal_broken_pipe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_alarm_clock_s) == F_equal_to) {
        *code = F_signal_alarm_clock;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_termination_s) == F_equal_to) {
        *code = F_signal_termination;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_stack_fault_s) == F_equal_to) {
        *code = F_signal_stack_fault;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_child_s) == F_equal_to) {
        *code = F_signal_child;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_continue_s) == F_equal_to) {
        *code = F_signal_continue;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_stop_s) == F_equal_to) {
        *code = F_signal_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_keyboard_stop_s) == F_equal_to) {
        *code = F_signal_keyboard_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_tty_in_s) == F_equal_to) {
        *code = F_signal_tty_in;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_tty_out_s) == F_equal_to) {
        *code = F_signal_tty_out;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_urgent_s) == F_equal_to) {
        *code = F_signal_urgent;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_cpu_limit_s) == F_equal_to) {
        *code = F_signal_cpu_limit;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_file_size_limit_s) == F_equal_to) {
        *code = F_signal_file_size_limit;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_virtual_alarm_clock_s) == F_equal_to) {
        *code = F_signal_virtual_alarm_clock;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_profile_alarm_clock_s) == F_equal_to) {
        *code = F_signal_profile_alarm_clock;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_window_size_change_s) == F_equal_to) {
        *code = F_signal_window_size_change;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_pollable_event_s) == F_equal_to) {
        *code = F_signal_pollable_event;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_power_failure_s) == F_equal_to) {
        *code = F_signal_power_failure;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_bad_system_call_s) == F_equal_to) {
        *code = F_signal_bad_system_call;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_32_s) == F_equal_to) {
        *code = F_signal_reserved_32;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_33_s) == F_equal_to) {
        *code = F_signal_reserved_33;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_34_s) == F_equal_to) {
        *code = F_signal_reserved_34;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_35_s) == F_equal_to) {
        *code = F_signal_reserved_35;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_36_s) == F_equal_to) {
        *code = F_signal_reserved_36;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_37_s) == F_equal_to) {
        *code = F_signal_reserved_37;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_38_s) == F_equal_to) {
        *code = F_signal_reserved_38;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_39_s) == F_equal_to) {
        *code = F_signal_reserved_39;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_40_s) == F_equal_to) {
        *code = F_signal_reserved_40;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_41_s) == F_equal_to) {
        *code = F_signal_reserved_41;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_42_s) == F_equal_to) {
        *code = F_signal_reserved_42;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_43_s) == F_equal_to) {
        *code = F_signal_reserved_43;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_44_s) == F_equal_to) {
        *code = F_signal_reserved_44;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_45_s) == F_equal_to) {
        *code = F_signal_reserved_45;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_46_s) == F_equal_to) {
        *code = F_signal_reserved_46;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_47_s) == F_equal_to) {
        *code = F_signal_reserved_47;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_48_s) == F_equal_to) {
        *code = F_signal_reserved_48;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_49_s) == F_equal_to) {
        *code = F_signal_reserved_49;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_50_s) == F_equal_to) {
        *code = F_signal_reserved_50;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_51_s) == F_equal_to) {
        *code = F_signal_reserved_51;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_52_s) == F_equal_to) {
        *code = F_signal_reserved_52;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_53_s) == F_equal_to) {
        *code = F_signal_reserved_53;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_54_s) == F_equal_to) {
        *code = F_signal_reserved_54;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_55_s) == F_equal_to) {
        *code = F_signal_reserved_55;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_56_s) == F_equal_to) {
        *code = F_signal_reserved_56;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_57_s) == F_equal_to) {
        *code = F_signal_reserved_57;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_58_s) == F_equal_to) {
        *code = F_signal_reserved_58;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_59_s) == F_equal_to) {
        *code = F_signal_reserved_59;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_60_s) == F_equal_to) {
        *code = F_signal_reserved_60;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_61_s) == F_equal_to) {
        *code = F_signal_reserved_61;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_62_s) == F_equal_to) {
        *code = F_signal_reserved_62;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_63_s) == F_equal_to) {
        *code = F_signal_reserved_63;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_reserved_64_s) == F_equal_to) {
        *code = F_signal_reserved_64;

        return F_none;
      }
    #endif // _di_f_status_signal_s_

    #ifndef _di_f_status_basic_s_
      if (f_compare_dynamic(name, f_status_none_s) == F_equal_to) {
        *code = F_none;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_abort_s) == F_equal_to) {
        *code = F_abort;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_abort_not_s) == F_equal_to) {
        *code = F_abort_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_absolute_s) == F_equal_to) {
        *code = F_absolute;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_absolute_not_s) == F_equal_to) {
        *code = F_absolute_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_address_s) == F_equal_to) {
        *code = F_address;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_address_not_s) == F_equal_to) {
        *code = F_address_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_ascii_s) == F_equal_to) {
        *code = F_ascii;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_ascii_not_s) == F_equal_to) {
        *code = F_ascii_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_atomic_s) == F_equal_to) {
        *code = F_atomic;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_atomic_not_s) == F_equal_to) {
        *code = F_atomic_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_base_s) == F_equal_to) {
        *code = F_base;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_base_not_s) == F_equal_to) {
        *code = F_base_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_begin_s) == F_equal_to) {
        *code = F_begin;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_begin_not_s) == F_equal_to) {
        *code = F_begin_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_block_s) == F_equal_to) {
        *code = F_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_block_not_s) == F_equal_to) {
        *code = F_block_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_body_s) == F_equal_to) {
        *code = F_body;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_body_not_s) == F_equal_to) {
        *code = F_body_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_bottom_s) == F_equal_to) {
        *code = F_bottom;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_bottom_not_s) == F_equal_to) {
        *code = F_bottom_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_bound_s) == F_equal_to) {
        *code = F_bound;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_bound_not_s) == F_equal_to) {
        *code = F_bound_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_break_s) == F_equal_to) {
        *code = F_break;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_break_not_s) == F_equal_to) {
        *code = F_break_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_call_s) == F_equal_to) {
        *code = F_call;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_call_not_s) == F_equal_to) {
        *code = F_call_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_capability_s) == F_equal_to) {
        *code = F_capability;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_capability_not_s) == F_equal_to) {
        *code = F_capability_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_child_s) == F_equal_to) {
        *code = F_child;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_character_s) == F_equal_to) {
        *code = F_character;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_character_not_s) == F_equal_to) {
        *code = F_character_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_child_not_s) == F_equal_to) {
        *code = F_child_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_s) == F_equal_to) {
        *code = F_complete;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_s) == F_equal_to) {
        *code = F_complete_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_connect_s) == F_equal_to) {
        *code = F_connect;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_connect_not_s) == F_equal_to) {
        *code = F_connect_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_connect_refuse_s) == F_equal_to) {
        *code = F_connect_refuse;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_connect_reset_s) == F_equal_to) {
        *code = F_connect_reset;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_container_s) == F_equal_to) {
        *code = F_container;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_container_not_s) == F_equal_to) {
        *code = F_container_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_content_s) == F_equal_to) {
        *code = F_content;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_content_not_s) == F_equal_to) {
        *code = F_content_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_continue_s) == F_equal_to) {
        *code = F_continue;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_continue_not_s) == F_equal_to) {
        *code = F_continue_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_control_s) == F_equal_to) {
        *code = F_control;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_control_not_s) == F_equal_to) {
        *code = F_control_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_control_group_s) == F_equal_to) {
        *code = F_control_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_control_group_not_s) == F_equal_to) {
        *code = F_control_group_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_critical_s) == F_equal_to) {
        *code = F_critical;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_critical_not_s) == F_equal_to) {
        *code = F_critical_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_dead_s) == F_equal_to) {
        *code = F_dead;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_dead_not_s) == F_equal_to) {
        *code = F_dead_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_deadlock_s) == F_equal_to) {
        *code = F_deadlock;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_deadlock_not_s) == F_equal_to) {
        *code = F_deadlock_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_descriptor_s) == F_equal_to) {
        *code = F_descriptor;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_descriptor_not_s) == F_equal_to) {
        *code = F_descriptor_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_desire_s) == F_equal_to) {
        *code = F_desire;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_desire_not_s) == F_equal_to) {
        *code = F_desire_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_device_s) == F_equal_to) {
        *code = F_device;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_device_not_s) == F_equal_to) {
        *code = F_device_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_disable_s) == F_equal_to) {
        *code = F_disable;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_disable_not_s) == F_equal_to) {
        *code = F_disable_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_discard_s) == F_equal_to) {
        *code = F_discard;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_discard_not_s) == F_equal_to) {
        *code = F_discard_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_drop_s) == F_equal_to) {
        *code = F_drop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_drop_not_s) == F_equal_to) {
        *code = F_drop_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_domain_s) == F_equal_to) {
        *code = F_domain;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_domain_not_s) == F_equal_to) {
        *code = F_domain_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_done_s) == F_equal_to) {
        *code = F_done;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_done_not_s) == F_equal_to) {
        *code = F_done_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_dummy_s) == F_equal_to) {
        *code = F_dummy;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_dummy_not_s) == F_equal_to) {
        *code = F_dummy_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_empty_s) == F_equal_to) {
        *code = F_empty;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_empty_not_s) == F_equal_to) {
        *code = F_empty_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_enable_s) == F_equal_to) {
        *code = F_enable;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_enable_not_s) == F_equal_to) {
        *code = F_enable_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_encoding_s) == F_equal_to) {
        *code = F_encoding;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_encoding_not_s) == F_equal_to) {
        *code = F_encoding_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_endian_s) == F_equal_to) {
        *code = F_endian;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_endian_big_s) == F_equal_to) {
        *code = F_endian_big;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_endian_little_s) == F_equal_to) {
        *code = F_endian_little;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_endian_not_s) == F_equal_to) {
        *code = F_endian_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eoa_s) == F_equal_to) {
        *code = F_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eoa_not_s) == F_equal_to) {
        *code = F_eoa_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eof_s) == F_equal_to) {
        *code = F_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eof_not_s) == F_equal_to) {
        *code = F_eof_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eol_s) == F_equal_to) {
        *code = F_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eol_not_s) == F_equal_to) {
        *code = F_eol_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eos_s) == F_equal_to) {
        *code = F_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_eos_not_s) == F_equal_to) {
        *code = F_eos_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_execute_s) == F_equal_to) {
        *code = F_execute;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_execute_not_s) == F_equal_to) {
        *code = F_execute_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_exist_s) == F_equal_to) {
        *code = F_exist;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_exist_not_s) == F_equal_to) {
        *code = F_exist_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_exit_s) == F_equal_to) {
        *code = F_exit;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_exit_not_s) == F_equal_to) {
        *code = F_exit_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_failure_s) == F_equal_to) {
        *code = F_failure;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_failure_not_s) == F_equal_to) {
        *code = F_failure_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_family_s) == F_equal_to) {
        *code = F_family;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_family_not_s) == F_equal_to) {
        *code = F_family_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_fifo_s) == F_equal_to) {
        *code = F_fifo;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_fifo_not_s) == F_equal_to) {
        *code = F_fifo_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_first_s) == F_equal_to) {
        *code = F_first;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_first_not_s) == F_equal_to) {
        *code = F_first_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_footer_s) == F_equal_to) {
        *code = F_footer;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_footer_not_s) == F_equal_to) {
        *code = F_footer_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_fork_s) == F_equal_to) {
        *code = F_fork;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_fork_not_s) == F_equal_to) {
        *code = F_fork_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_format_s) == F_equal_to) {
        *code = F_format;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_format_not_s) == F_equal_to) {
        *code = F_format_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_found_s) == F_equal_to) {
        *code = F_found;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_found_not_s) == F_equal_to) {
        *code = F_found_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_full_s) == F_equal_to) {
        *code = F_full;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_full_not_s) == F_equal_to) {
        *code = F_full_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_group_s) == F_equal_to) {
        *code = F_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_group_not_s) == F_equal_to) {
        *code = F_group_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_halt_s) == F_equal_to) {
        *code = F_halt;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_halt_not_s) == F_equal_to) {
        *code = F_halt_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_header_s) == F_equal_to) {
        *code = F_header;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_header_not_s) == F_equal_to) {
        *code = F_header_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_help_s) == F_equal_to) {
        *code = F_help;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_help_not_s) == F_equal_to) {
        *code = F_help_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_ignore_s) == F_equal_to) {
        *code = F_ignore;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_ignore_not_s) == F_equal_to) {
        *code = F_ignore_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_implemented_s) == F_equal_to) {
        *code = F_implemented;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_implemented_not_s) == F_equal_to) {
        *code = F_implemented_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_input_s) == F_equal_to) {
        *code = F_input;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_input_not_s) == F_equal_to) {
        *code = F_input_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_input_output_s) == F_equal_to) {
        *code = F_input_output;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_interrupt_s) == F_equal_to) {
        *code = F_interrupt;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_interrupt_not_s) == F_equal_to) {
        *code = F_interrupt_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_keep_s) == F_equal_to) {
        *code = F_keep;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_keep_not_s) == F_equal_to) {
        *code = F_keep_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_known_s) == F_equal_to) {
        *code = F_known;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_known_not_s) == F_equal_to) {
        *code = F_known_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_last_s) == F_equal_to) {
        *code = F_last;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_last_not_s) == F_equal_to) {
        *code = F_last_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_limit_s) == F_equal_to) {
        *code = F_limit;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_limit_not_s) == F_equal_to) {
        *code = F_limit_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_link_s) == F_equal_to) {
        *code = F_link;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_link_not_s) == F_equal_to) {
        *code = F_link_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_live_s) == F_equal_to) {
        *code = F_live;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_live_not_s) == F_equal_to) {
        *code = F_live_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_local_s) == F_equal_to) {
        *code = F_local;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_local_not_s) == F_equal_to) {
        *code = F_local_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_lock_s) == F_equal_to) {
        *code = F_lock;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_lock_not_s) == F_equal_to) {
        *code = F_lock_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_loop_s) == F_equal_to) {
        *code = F_loop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_loop_not_s) == F_equal_to) {
        *code = F_loop_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_maybe_s) == F_equal_to) {
        *code = F_maybe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_maybe_not_s) == F_equal_to) {
        *code = F_maybe_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_memory_s) == F_equal_to) {
        *code = F_memory;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_memory_not_s) == F_equal_to) {
        *code = F_memory_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_message_s) == F_equal_to) {
        *code = F_message;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_message_not_s) == F_equal_to) {
        *code = F_message_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_middle_s) == F_equal_to) {
        *code = F_middle;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_middle_not_s) == F_equal_to) {
        *code = F_middle_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_minor_s) == F_equal_to) {
        *code = F_minor;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_minor_not_s) == F_equal_to) {
        *code = F_minor_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_moderate_s) == F_equal_to) {
        *code = F_moderate;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_moderate_not_s) == F_equal_to) {
        *code = F_moderate_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_mount_s) == F_equal_to) {
        *code = F_mount;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_mount_not_s) == F_equal_to) {
        *code = F_mount_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_name_s) == F_equal_to) {
        *code = F_name;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_name_not_s) == F_equal_to) {
        *code = F_name_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_need_s) == F_equal_to) {
        *code = F_need;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_need_not_s) == F_equal_to) {
        *code = F_need_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_next_s) == F_equal_to) {
        *code = F_next;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_next_not_s) == F_equal_to) {
        *code = F_next_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_nice_s) == F_equal_to) {
        *code = F_nice;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_nice_not_s) == F_equal_to) {
        *code = F_nice_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_no_s) == F_equal_to) {
        *code = F_no;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_no_not_s) == F_equal_to) {
        *code = F_no_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_object_s) == F_equal_to) {
        *code = F_object;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_object_not_s) == F_equal_to) {
        *code = F_object_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_okay_s) == F_equal_to) {
        *code = F_okay;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_okay_not_s) == F_equal_to) {
        *code = F_okay_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_once_s) == F_equal_to) {
        *code = F_once;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_once_not_s) == F_equal_to) {
        *code = F_once_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_option_s) == F_equal_to) {
        *code = F_option;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_option_not_s) == F_equal_to) {
        *code = F_option_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_output_s) == F_equal_to) {
        *code = F_output;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_output_not_s) == F_equal_to) {
        *code = F_output_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_packet_s) == F_equal_to) {
        *code = F_packet;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_packet_not_s) == F_equal_to) {
        *code = F_packet_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_parameter_s) == F_equal_to) {
        *code = F_parameter;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_parameter_not_s) == F_equal_to) {
        *code = F_parameter_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_parent_s) == F_equal_to) {
        *code = F_parent;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_parent_not_s) == F_equal_to) {
        *code = F_parent_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_payload_s) == F_equal_to) {
        *code = F_payload;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_payload_not_s) == F_equal_to) {
        *code = F_payload_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_pipe_s) == F_equal_to) {
        *code = F_pipe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_pipe_not_s) == F_equal_to) {
        *code = F_pipe_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_port_s) == F_equal_to) {
        *code = F_port;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_port_not_s) == F_equal_to) {
        *code = F_port_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_previous_s) == F_equal_to) {
        *code = F_previous;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_previous_not_s) == F_equal_to) {
        *code = F_previous_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_processor_s) == F_equal_to) {
        *code = F_processor;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_processor_not_s) == F_equal_to) {
        *code = F_processor_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_progress_s) == F_equal_to) {
        *code = F_progress;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_progress_not_s) == F_equal_to) {
        *code = F_progress_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_prohibited_s) == F_equal_to) {
        *code = F_prohibited;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_prohibited_not_s) == F_equal_to) {
        *code = F_prohibited_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_property_s) == F_equal_to) {
        *code = F_property;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_property_not_s) == F_equal_to) {
        *code = F_property_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_protocol_s) == F_equal_to) {
        *code = F_protocol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_protocol_not_s) == F_equal_to) {
        *code = F_protocol_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_range_s) == F_equal_to) {
        *code = F_range;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_range_not_s) == F_equal_to) {
        *code = F_range_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_read_s) == F_equal_to) {
        *code = F_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_read_not_s) == F_equal_to) {
        *code = F_read_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_read_only_s) == F_equal_to) {
        *code = F_read_only;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_ready_s) == F_equal_to) {
        *code = F_ready;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_ready_not_s) == F_equal_to) {
        *code = F_ready_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_receive_s) == F_equal_to) {
        *code = F_receive;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_receive_not_s) == F_equal_to) {
        *code = F_receive_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_recover_s) == F_equal_to) {
        *code = F_recover;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_recover_not_s) == F_equal_to) {
        *code = F_recover_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_recurse_s) == F_equal_to) {
        *code = F_recurse;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_recurse_not_s) == F_equal_to) {
        *code = F_recurse_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_regular_s) == F_equal_to) {
        *code = F_regular;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_regular_not_s) == F_equal_to) {
        *code = F_regular_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_relative_s) == F_equal_to) {
        *code = F_relative;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_relative_not_s) == F_equal_to) {
        *code = F_relative_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_remote_s) == F_equal_to) {
        *code = F_remote;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_remote_not_s) == F_equal_to) {
        *code = F_remote_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_repeat_s) == F_equal_to) {
        *code = F_repeat;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_repeat_not_s) == F_equal_to) {
        *code = F_repeat_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_require_s) == F_equal_to) {
        *code = F_require;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_require_not_s) == F_equal_to) {
        *code = F_require_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_resource_s) == F_equal_to) {
        *code = F_resource;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_resource_not_s) == F_equal_to) {
        *code = F_resource_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_restart_s) == F_equal_to) {
        *code = F_restart;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_restart_not_s) == F_equal_to) {
        *code = F_restart_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_restore_s) == F_equal_to) {
        *code = F_restore;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_restore_not_s) == F_equal_to) {
        *code = F_restore_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_revert_s) == F_equal_to) {
        *code = F_revert;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_revert_not_s) == F_equal_to) {
        *code = F_revert_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_schedule_s) == F_equal_to) {
        *code = F_schedule;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_schedule_not_s) == F_equal_to) {
        *code = F_schedule_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_search_s) == F_equal_to) {
        *code = F_search;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_search_not_s) == F_equal_to) {
        *code = F_search_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_send_s) == F_equal_to) {
        *code = F_send;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_send_not_s) == F_equal_to) {
        *code = F_send_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_size_s) == F_equal_to) {
        *code = F_size;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_size_not_s) == F_equal_to) {
        *code = F_size_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_s) == F_equal_to) {
        *code = F_signal;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_signal_not_s) == F_equal_to) {
        *code = F_signal_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_space_s) == F_equal_to) {
        *code = F_space;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_space_not_s) == F_equal_to) {
        *code = F_space_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_skip_s) == F_equal_to) {
        *code = F_skip;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_skip_not_s) == F_equal_to) {
        *code = F_skip_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_start_s) == F_equal_to) {
        *code = F_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_start_not_s) == F_equal_to) {
        *code = F_start_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_status_s) == F_equal_to) {
        *code = F_status;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_status_not_s) == F_equal_to) {
        *code = F_status_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_stop_s) == F_equal_to) {
        *code = F_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_stop_not_s) == F_equal_to) {
        *code = F_stop_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_store_s) == F_equal_to) {
        *code = F_store;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_store_not_s) == F_equal_to) {
        *code = F_store_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_stream_s) == F_equal_to) {
        *code = F_stream;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_stream_not_s) == F_equal_to) {
        *code = F_stream_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_string_s) == F_equal_to) {
        *code = F_string;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_string_not_s) == F_equal_to) {
        *code = F_string_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_string_too_large_s) == F_equal_to) {
        *code = F_string_too_large;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_string_too_small_s) == F_equal_to) {
        *code = F_string_too_small;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_success_s) == F_equal_to) {
        *code = F_success;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_success_not_s) == F_equal_to) {
        *code = F_success_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_support_s) == F_equal_to) {
        *code = F_support;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_support_not_s) == F_equal_to) {
        *code = F_support_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_syntax_s) == F_equal_to) {
        *code = F_syntax;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_syntax_not_s) == F_equal_to) {
        *code = F_syntax_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminate_s) == F_equal_to) {
        *code = F_terminate;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminate_not_s) == F_equal_to) {
        *code = F_terminate_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_thread_s) == F_equal_to) {
        *code = F_thread;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_thread_not_s) == F_equal_to) {
        *code = F_thread_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_time_s) == F_equal_to) {
        *code = F_time;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_time_not_s) == F_equal_to) {
        *code = F_time_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_time_out_s) == F_equal_to) {
        *code = F_time_out;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_too_large_s) == F_equal_to) {
        *code = F_too_large;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_too_small_s) == F_equal_to) {
        *code = F_too_small;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_top_s) == F_equal_to) {
        *code = F_top;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_top_not_s) == F_equal_to) {
        *code = F_top_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_type_s) == F_equal_to) {
        *code = F_type;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_type_not_s) == F_equal_to) {
        *code = F_type_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_user_s) == F_equal_to) {
        *code = F_user;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_user_not_s) == F_equal_to) {
        *code = F_user_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_utf_s) == F_equal_to) {
        *code = F_utf;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_utf_fragment_s) == F_equal_to) {
        *code = F_utf_fragment;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_utf_fragment_not_s) == F_equal_to) {
        *code = F_utf_fragment_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_utf_not_s) == F_equal_to) {
        *code = F_utf_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_valid_s) == F_equal_to) {
        *code = F_valid;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_valid_not_s) == F_equal_to) {
        *code = F_valid_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_value_s) == F_equal_to) {
        *code = F_value;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_value_not_s) == F_equal_to) {
        *code = F_value_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_wait_s) == F_equal_to) {
        *code = F_wait;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_wait_not_s) == F_equal_to) {
        *code = F_wait_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_want_s) == F_equal_to) {
        *code = F_want;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_want_not_s) == F_equal_to) {
        *code = F_want_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_wish_s) == F_equal_to) {
        *code = F_wish;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_wish_not_s) == F_equal_to) {
        *code = F_wish_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_world_s) == F_equal_to) {
        *code = F_world;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_world_not_s) == F_equal_to) {
        *code = F_world_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_write_s) == F_equal_to) {
        *code = F_write;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_write_not_s) == F_equal_to) {
        *code = F_write_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_write_only_s) == F_equal_to) {
        *code = F_write_only;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_yes_s) == F_equal_to) {
        *code = F_yes;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_yes_not_s) == F_equal_to) {
        *code = F_yes_not;

        return F_none;
      }
    #endif // _di_f_status_basic_s_

    #ifndef _di_f_status_return_s_
      if (f_compare_dynamic(name, f_status_debug_s) == F_equal_to) {
        *code = F_debug;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_debug_not_s) == F_equal_to) {
        *code = F_debug_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_error_s) == F_equal_to) {
        *code = F_error;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_error_not_s) == F_equal_to) {
        *code = F_error_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_fine_s) == F_equal_to) {
        *code = F_fine;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_fine_not_s) == F_equal_to) {
        *code = F_fine_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_warning_s) == F_equal_to) {
        *code = F_warning;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_warning_not_s) == F_equal_to) {
        *code = F_warning_not;

        return F_none;
      }
    #endif // _di_f_status_return_s_

    #ifndef _di_f_status_array_s_
      if (f_compare_dynamic(name, f_status_array_s) == F_equal_to) {
        *code = F_array;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_array_not_s) == F_equal_to) {
        *code = F_array_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_array_too_large_s) == F_equal_to) {
        *code = F_array_too_large;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_array_too_small_s) == F_equal_to) {
        *code = F_array_too_small;

        return F_none;
      }
    #endif // _di_f_status_array_s_

    #ifndef _di_f_status_available_s_
      if (f_compare_dynamic(name, f_status_available_s) == F_equal_to) {
        *code = F_available;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_s) == F_equal_to) {
        *code = F_available_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_address_s) == F_equal_to) {
        *code = F_available_not_address;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_buffer_s) == F_equal_to) {
        *code = F_available_not_buffer;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_device_s) == F_equal_to) {
        *code = F_available_not_device;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_pipe_s) == F_equal_to) {
        *code = F_available_not_pipe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_port_s) == F_equal_to) {
        *code = F_available_not_port;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_process_s) == F_equal_to) {
        *code = F_available_not_process;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_available_not_socket_s) == F_equal_to) {
        *code = F_available_not_socket;

        return F_none;
      }
    #endif // _di_f_status_available_s_

    #ifndef _di_f_status_busy_s_
      if (f_compare_dynamic(name, f_status_busy_s) == F_equal_to) {
        *code = F_busy;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_address_s) == F_equal_to) {
        *code = F_busy_address;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_buffer_s) == F_equal_to) {
        *code = F_busy_buffer;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_device_s) == F_equal_to) {
        *code = F_busy_device;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_not_s) == F_equal_to) {
        *code = F_busy_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_pipe_s) == F_equal_to) {
        *code = F_busy_pipe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_port_s) == F_equal_to) {
        *code = F_busy_port;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_process_s) == F_equal_to) {
        *code = F_busy_process;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_busy_socket_s) == F_equal_to) {
        *code = F_busy_socket;

        return F_none;
      }
    #endif // _di_f_status_busy_s_

    #ifndef _di_f_status_network_s_
      if (f_compare_dynamic(name, f_status_network_s) == F_equal_to) {
        *code = F_network;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_busy_s) == F_equal_to) {
        *code = F_network_busy;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_busy_not_s) == F_equal_to) {
        *code = F_network_busy_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_client_s) == F_equal_to) {
        *code = F_network_client;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_client_not_s) == F_equal_to) {
        *code = F_network_client_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_device_s) == F_equal_to) {
        *code = F_network_device;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_device_not_s) == F_equal_to) {
        *code = F_network_device_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_found_s) == F_equal_to) {
        *code = F_network_found;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_found_not_s) == F_equal_to) {
        *code = F_network_found_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_lost_s) == F_equal_to) {
        *code = F_network_lost;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_lost_not_s) == F_equal_to) {
        *code = F_network_lost_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_not_s) == F_equal_to) {
        *code = F_network_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_reach_s) == F_equal_to) {
        *code = F_network_reach;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_reach_client_s) == F_equal_to) {
        *code = F_network_reach_client;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_reach_client_not_s) == F_equal_to) {
        *code = F_network_reach_client_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_reach_not_s) == F_equal_to) {
        *code = F_network_reach_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_reach_server_s) == F_equal_to) {
        *code = F_network_reach_server;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_reach_server_not_s) == F_equal_to) {
        *code = F_network_reach_server_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_server_s) == F_equal_to) {
        *code = F_network_server;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_server_not_s) == F_equal_to) {
        *code = F_network_server_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_time_s) == F_equal_to) {
        *code = F_network_time;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_network_time_not_s) == F_equal_to) {
        *code = F_network_time_not;

        return F_none;
      }
    #endif // _di_f_status_network_s_

    #ifndef _di_f_status_number_s_
      if (f_compare_dynamic(name, f_status_number_s) == F_equal_to) {
        *code = F_number;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_decimal_s) == F_equal_to) {
        *code = F_number_decimal;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_decimal_not_s) == F_equal_to) {
        *code = F_number_decimal_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_divide_by_zero_s) == F_equal_to) {
        *code = F_number_divide_by_zero;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_negative_s) == F_equal_to) {
        *code = F_number_negative;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_negative_not_s) == F_equal_to) {
        *code = F_number_negative_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_not_s) == F_equal_to) {
        *code = F_number_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_overflow_s) == F_equal_to) {
        *code = F_number_overflow;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_positive_s) == F_equal_to) {
        *code = F_number_positive;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_positive_not_s) == F_equal_to) {
        *code = F_number_positive_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_too_large_s) == F_equal_to) {
        *code = F_number_too_large;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_too_small_s) == F_equal_to) {
        *code = F_number_too_small;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_underflow_s) == F_equal_to) {
        *code = F_number_underflow;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_whole_s) == F_equal_to) {
        *code = F_number_whole;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_whole_not_s) == F_equal_to) {
        *code = F_number_whole_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_zero_s) == F_equal_to) {
        *code = F_number_zero;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_number_zero_not_s) == F_equal_to) {
        *code = F_number_zero_not;

        return F_none;
      }
    #endif // _di_f_status_number_s_

    #ifndef _di_f_status_buffer_s_
      if (f_compare_dynamic(name, f_status_buffer_s) == F_equal_to) {
        *code = F_buffer;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_buffer_not_s) == F_equal_to) {
        *code = F_buffer_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_buffer_overflow_s) == F_equal_to) {
        *code = F_buffer_overflow;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_buffer_too_large_s) == F_equal_to) {
        *code = F_buffer_too_large;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_buffer_too_small_s) == F_equal_to) {
        *code = F_buffer_too_small;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_buffer_underflow_s) == F_equal_to) {
        *code = F_buffer_underflow;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_s) == F_equal_to) {
        *code = F_complete_not_utf;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_block_s) == F_equal_to) {
        *code = F_complete_not_utf_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_eoa_s) == F_equal_to) {
        *code = F_complete_not_utf_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_eof_s) == F_equal_to) {
        *code = F_complete_not_utf_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_eol_s) == F_equal_to) {
        *code = F_complete_not_utf_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_eos_s) == F_equal_to) {
        *code = F_complete_not_utf_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_start_s) == F_equal_to) {
        *code = F_complete_not_utf_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_complete_not_utf_stop_s) == F_equal_to) {
        *code = F_complete_not_utf_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_block_s) == F_equal_to) {
        *code = F_none_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_eoa_s) == F_equal_to) {
        *code = F_none_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_eof_s) == F_equal_to) {
        *code = F_none_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_eol_s) == F_equal_to) {
        *code = F_none_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_eos_s) == F_equal_to) {
        *code = F_none_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_start_s) == F_equal_to) {
        *code = F_none_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_none_stop_s) == F_equal_to) {
        *code = F_none_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_s) == F_equal_to) {
        *code = F_data;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_s) == F_equal_to) {
        *code = F_data_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_block_s) == F_equal_to) {
        *code = F_data_not_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_eoa_s) == F_equal_to) {
        *code = F_data_not_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_eof_s) == F_equal_to) {
        *code = F_data_not_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_eol_s) == F_equal_to) {
        *code = F_data_not_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_eos_s) == F_equal_to) {
        *code = F_data_not_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_start_s) == F_equal_to) {
        *code = F_data_not_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_data_not_stop_s) == F_equal_to) {
        *code = F_data_not_stop;

        return F_none;
      }
    #endif // _di_f_status_buffer_s_

    #ifndef _di_f_status_end_s_
      if (f_compare_dynamic(name, f_status_end_s) == F_equal_to) {
        *code = F_end;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_s) == F_equal_to) {
        *code = F_end_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_block_s) == F_equal_to) {
        *code = F_end_not_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_eoa_s) == F_equal_to) {
        *code = F_end_not_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_eof_s) == F_equal_to) {
        *code = F_end_not_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_eol_s) == F_equal_to) {
        *code = F_end_not_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_eos_s) == F_equal_to) {
        *code = F_end_not_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_s) == F_equal_to) {
        *code = F_end_not_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_block_s) == F_equal_to) {
        *code = F_end_not_group_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_eoa_s) == F_equal_to) {
        *code = F_end_not_group_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_eof_s) == F_equal_to) {
        *code = F_end_not_group_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_eol_s) == F_equal_to) {
        *code = F_end_not_group_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_eos_s) == F_equal_to) {
        *code = F_end_not_group_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_start_s) == F_equal_to) {
        *code = F_end_not_group_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_group_stop_s) == F_equal_to) {
        *code = F_end_not_group_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_s) == F_equal_to) {
        *code = F_end_not_nest;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_block_s) == F_equal_to) {
        *code = F_end_not_nest_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_eoa_s) == F_equal_to) {
        *code = F_end_not_nest_eoa;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_eof_s) == F_equal_to) {
        *code = F_end_not_nest_eof;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_eol_s) == F_equal_to) {
        *code = F_end_not_nest_eol;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_eos_s) == F_equal_to) {
        *code = F_end_not_nest_eos;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_start_s) == F_equal_to) {
        *code = F_end_not_nest_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_nest_stop_s) == F_equal_to) {
        *code = F_end_not_nest_stop;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_start_s) == F_equal_to) {
        *code = F_end_not_start;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_end_not_stop_s) == F_equal_to) {
        *code = F_end_not_stop;

        return F_none;
      }
    #endif // _di_f_status_end_s_

    #ifndef _di_f_status_process_s_
      if (f_compare_dynamic(name, f_status_process_s) == F_equal_to) {
        *code = F_process;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_process_not_s) == F_equal_to) {
        *code = F_process_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_process_too_many_s) == F_equal_to) {
        *code = F_process_too_many;

        return F_none;
      }
    #endif // _di_f_status_process_s_

    #ifndef _di_f_status_file_s_
      if (f_compare_dynamic(name, f_status_file_s) == F_equal_to) {
        *code = F_file;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_close_s) == F_equal_to) {
        *code = F_file_close;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_closed_s) == F_equal_to) {
        *code = F_file_closed;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_descriptor_s) == F_equal_to) {
        *code = F_file_descriptor;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_descriptor_max_s) == F_equal_to) {
        *code = F_file_descriptor_max;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_descriptor_not_s) == F_equal_to) {
        *code = F_file_descriptor_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_empty_s) == F_equal_to) {
        *code = F_file_empty;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_flush_s) == F_equal_to) {
        *code = F_file_flush;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_found_s) == F_equal_to) {
        *code = F_file_found;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_found_not_s) == F_equal_to) {
        *code = F_file_found_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_not_s) == F_equal_to) {
        *code = F_file_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_open_s) == F_equal_to) {
        *code = F_file_open;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_open_max_s) == F_equal_to) {
        *code = F_file_open_max;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_opened_s) == F_equal_to) {
        *code = F_file_opened;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_overflow_s) == F_equal_to) {
        *code = F_file_overflow;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_purge_s) == F_equal_to) {
        *code = F_file_purge;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_read_s) == F_equal_to) {
        *code = F_file_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_reallocation_s) == F_equal_to) {
        *code = F_file_reallocation;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_seek_s) == F_equal_to) {
        *code = F_file_seek;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_stat_s) == F_equal_to) {
        *code = F_file_stat;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_synchronize_s) == F_equal_to) {
        *code = F_file_synchronize;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_block_s) == F_equal_to) {
        *code = F_file_type_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_character_s) == F_equal_to) {
        *code = F_file_type_character;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_directory_s) == F_equal_to) {
        *code = F_file_type_directory;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_fifo_s) == F_equal_to) {
        *code = F_file_type_fifo;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_link_s) == F_equal_to) {
        *code = F_file_type_link;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_block_s) == F_equal_to) {
        *code = F_file_type_not_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_character_s) == F_equal_to) {
        *code = F_file_type_not_character;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_directory_s) == F_equal_to) {
        *code = F_file_type_not_directory;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_fifo_s) == F_equal_to) {
        *code = F_file_type_not_fifo;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_link_s) == F_equal_to) {
        *code = F_file_type_not_link;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_pipe_s) == F_equal_to) {
        *code = F_file_type_not_pipe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_regular_s) == F_equal_to) {
        *code = F_file_type_not_regular;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_socket_s) == F_equal_to) {
        *code = F_file_type_not_socket;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_not_unknown_s) == F_equal_to) {
        *code = F_file_type_not_unknown;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_pipe_s) == F_equal_to) {
        *code = F_file_type_pipe;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_regular_s) == F_equal_to) {
        *code = F_file_type_regular;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_socket_s) == F_equal_to) {
        *code = F_file_type_socket;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_type_unknown_s) == F_equal_to) {
        *code = F_file_type_unknown;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_underflow_s) == F_equal_to) {
        *code = F_file_underflow;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_utf_s) == F_equal_to) {
        *code = F_file_utf;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_utf_not_s) == F_equal_to) {
        *code = F_file_utf_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_file_write_s) == F_equal_to) {
        *code = F_file_write;

        return F_none;
      }
    #endif // _di_f_status_file_s_

    #ifndef _di_f_status_filesystem_s_
      if (f_compare_dynamic(name, f_status_filesystem_s) == F_equal_to) {
        *code = F_filesystem;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_filesystem_not_s) == F_equal_to) {
        *code = F_filesystem_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_filesystem_quota_block_s) == F_equal_to) {
        *code = F_filesystem_quota_block;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_filesystem_quota_reached_s) == F_equal_to) {
        *code = F_filesystem_quota_reached;

        return F_none;
      }
    #endif // _di_f_status_filesystem_s_

    #ifndef _di_f_status_directory_s_
      if (f_compare_dynamic(name, f_status_directory_s) == F_equal_to) {
        *code = F_directory;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_close_s) == F_equal_to) {
        *code = F_directory_close;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_closed_s) == F_equal_to) {
        *code = F_directory_closed;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_descriptor_s) == F_equal_to) {
        *code = F_directory_descriptor;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_empty_s) == F_equal_to) {
        *code = F_directory_empty;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_empty_not_s) == F_equal_to) {
        *code = F_directory_empty_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_found_s) == F_equal_to) {
        *code = F_directory_found;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_found_not_s) == F_equal_to) {
        *code = F_directory_found_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_flush_s) == F_equal_to) {
        *code = F_directory_flush;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_link_max_s) == F_equal_to) {
        *code = F_directory_link_max;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_not_s) == F_equal_to) {
        *code = F_directory_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_open_s) == F_equal_to) {
        *code = F_directory_open;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_purge_s) == F_equal_to) {
        *code = F_directory_purge;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_read_s) == F_equal_to) {
        *code = F_directory_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_stream_s) == F_equal_to) {
        *code = F_directory_stream;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_support_not_s) == F_equal_to) {
        *code = F_directory_support_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_synchronize_s) == F_equal_to) {
        *code = F_directory_synchronize;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_utf_s) == F_equal_to) {
        *code = F_directory_utf;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_utf_not_s) == F_equal_to) {
        *code = F_directory_utf_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_directory_write_s) == F_equal_to) {
        *code = F_directory_write;

        return F_none;
      }
    #endif // _di_f_status_directory_s_

    #ifndef _di_f_status_socket_s_
      if (f_compare_dynamic(name, f_status_socket_s) == F_equal_to) {
        *code = F_socket;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_socket_client_s) == F_equal_to) {
        *code = F_socket_client;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_socket_not_s) == F_equal_to) {
        *code = F_socket_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_socket_receive_s) == F_equal_to) {
        *code = F_socket_receive;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_socket_send_s) == F_equal_to) {
        *code = F_socket_send;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_socket_target_s) == F_equal_to) {
        *code = F_socket_target;

        return F_none;
      }
    #endif // _di_f_status_socket_s_

    #ifndef _di_f_status_compare_s_
      if (f_compare_dynamic(name, f_status_equal_to_s) == F_equal_to) {
        *code = F_equal_to;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_equal_to_not_s) == F_equal_to) {
        *code = F_equal_to_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_than_greater_s) == F_equal_to) {
        *code = F_than_greater;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_than_less_s) == F_equal_to) {
        *code = F_than_less;

        return F_none;
      }
    #endif // _di_f_status_compare_s_

    #ifndef _di_f_status_access_s_
      if (f_compare_dynamic(name, f_status_access_s) == F_equal_to) {
        *code = F_access;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_s) == F_equal_to) {
        *code = F_access_denied;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_user_s) == F_equal_to) {
        *code = F_access_denied_user;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_group_s) == F_equal_to) {
        *code = F_access_denied_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_world_s) == F_equal_to) {
        *code = F_access_denied_world;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_read_s) == F_equal_to) {
        *code = F_access_denied_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_write_s) == F_equal_to) {
        *code = F_access_denied_write;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_execute_s) == F_equal_to) {
        *code = F_access_denied_execute;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_denied_super_s) == F_equal_to) {
        *code = F_access_denied_super;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_s) == F_equal_to) {
        *code = F_access_granted;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_user_s) == F_equal_to) {
        *code = F_access_granted_user;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_group_s) == F_equal_to) {
        *code = F_access_granted_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_world_s) == F_equal_to) {
        *code = F_access_granted_world;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_read_s) == F_equal_to) {
        *code = F_access_granted_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_write_s) == F_equal_to) {
        *code = F_access_granted_write;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_execute_s) == F_equal_to) {
        *code = F_access_granted_execute;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_group_s) == F_equal_to) {
        *code = F_access_granted_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_read_s) == F_equal_to) {
        *code = F_access_granted_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_super_s) == F_equal_to) {
        *code = F_access_granted_super;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_granted_user_s) == F_equal_to) {
        *code = F_access_granted_user;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_group_s) == F_equal_to) {
        *code = F_access_group;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_mode_s) == F_equal_to) {
        *code = F_access_mode;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_not_s) == F_equal_to) {
        *code = F_access_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_access_owner_s) == F_equal_to) {
        *code = F_access_owner;

        return F_none;
      }
    #endif // _di_f_status_access_s_

    #ifndef _di_f_status_terminal_s_
      if (f_compare_dynamic(name, f_status_terminal_s) == F_equal_to) {
        *code = F_terminal;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_access_s) == F_equal_to) {
        *code = F_terminal_access;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_known_s) == F_equal_to) {
        *code = F_terminal_known;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_known_not_s) == F_equal_to) {
        *code = F_terminal_known_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_not_s) == F_equal_to) {
        *code = F_terminal_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_prohibited_s) == F_equal_to) {
        *code = F_terminal_prohibited;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_read_s) == F_equal_to) {
        *code = F_terminal_read;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_valid_s) == F_equal_to) {
        *code = F_terminal_valid;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_valid_not_s) == F_equal_to) {
        *code = F_terminal_valid_not;

        return F_none;
      }

      if (f_compare_dynamic(name, f_status_terminal_write_s) == F_equal_to) {
        *code = F_terminal_write;

        return F_none;
      }
    #endif // _di_f_status_terminal_s_

    if (f_compare_dynamic(name, f_status_status_code_last_s) == F_equal_to) {
      *code = F_status_code_last;

      return F_none;
    }

    return F_status_set_error(F_data);
  }
#endif // _di_fl_status_string_from_

#ifdef __cplusplus
} // extern "C"
#endif

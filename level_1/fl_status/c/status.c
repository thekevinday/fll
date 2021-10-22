#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_status_to_string_
  f_status_t fl_status_to_string(const f_status_t code, f_string_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_F_status_boolean_
        case F_false:
          *string = FL_status_string_false;
          break;
        case F_true:
          *string = FL_status_string_true;
          break;
      #endif // _di_F_status_boolean_

      #ifndef _di_F_status_signal_
        // F_signal_hangup is not used because it has the same code as F_true.
        case F_signal_interrupt:
          *string = FL_status_string_signal_interrupt;
          break;
        case F_signal_quit:
          *string = FL_status_string_signal_quit;
          break;
        case F_signal_illegal:
          *string = FL_status_string_signal_illegal;
          break;
        case F_signal_trap:
          *string = FL_status_string_signal_trap;
          break;
        case F_signal_abort:
          *string = FL_status_string_signal_abort;
          break;
        case F_signal_bus_error:
          *string = FL_status_string_signal_bus_error;
          break;
        case F_signal_floating_point_error:
          *string = FL_status_string_signal_floating_point_error;
          break;
        case F_signal_kill:
          *string = FL_status_string_signal_kill;
          break;
        case F_signal_user_1:
          *string = FL_status_string_signal_user_1;
          break;
        case F_signal_segmentation_fault:
          *string = FL_status_string_signal_segmentation_fault;
          break;
        case F_signal_user_2:
          *string = FL_status_string_signal_user_2;
          break;
        case F_signal_broken_pipe:
          *string = FL_status_string_signal_broken_pipe;
          break;
        case F_signal_alarm_clock:
          *string = FL_status_string_signal_alarm_clock;
          break;
        case F_signal_termination:
          *string = FL_status_string_signal_termination;
          break;
        case F_signal_stack_fault:
          *string = FL_status_string_signal_stack_fault;
          break;
        case F_signal_child:
          *string = FL_status_string_signal_child;
          break;
        case F_signal_continue:
          *string = FL_status_string_signal_continue;
          break;
        case F_signal_stop:
          *string = FL_status_string_signal_stop;
          break;
        case F_signal_keyboard_stop:
          *string = FL_status_string_signal_keyboard_stop;
          break;
        case F_signal_tty_in:
          *string = FL_status_string_signal_tty_in;
          break;
        case F_signal_tty_out:
          *string = FL_status_string_signal_tty_out;
          break;
        case F_signal_urgent:
          *string = FL_status_string_signal_urgent;
          break;
        case F_signal_cpu_limit:
          *string = FL_status_string_signal_cpu_limit;
          break;
        case F_signal_file_size_limit:
          *string = FL_status_string_signal_file_size_limit;
          break;
        case F_signal_virtual_alarm_clock:
          *string = FL_status_string_signal_virtual_alarm_clock;
          break;
        case F_signal_profile_alarm_clock:
          *string = FL_status_string_signal_profile_alarm_clock;
          break;
        case F_signal_window_size_change:
          *string = FL_status_string_signal_window_size_change;
          break;
        case F_signal_pollable_event:
          *string = FL_status_string_signal_pollable_event;
          break;
        case F_signal_power_failure:
          *string = FL_status_string_signal_power_failure;
          break;
        case F_signal_bad_system_call:
          *string = FL_status_string_signal_bad_system_call;
          break;
        case F_signal_reserved_32:
          *string = FL_status_string_signal_reserved_32;
          break;
        case F_signal_reserved_33:
          *string = FL_status_string_signal_reserved_33;
          break;
        case F_signal_reserved_34:
          *string = FL_status_string_signal_reserved_34;
          break;
        case F_signal_reserved_35:
          *string = FL_status_string_signal_reserved_35;
          break;
        case F_signal_reserved_36:
          *string = FL_status_string_signal_reserved_36;
          break;
        case F_signal_reserved_37:
          *string = FL_status_string_signal_reserved_37;
          break;
        case F_signal_reserved_38:
          *string = FL_status_string_signal_reserved_38;
          break;
        case F_signal_reserved_39:
          *string = FL_status_string_signal_reserved_39;
          break;
        case F_signal_reserved_40:
          *string = FL_status_string_signal_reserved_40;
          break;
        case F_signal_reserved_41:
          *string = FL_status_string_signal_reserved_41;
          break;
        case F_signal_reserved_42:
          *string = FL_status_string_signal_reserved_42;
          break;
        case F_signal_reserved_43:
          *string = FL_status_string_signal_reserved_43;
          break;
        case F_signal_reserved_44:
          *string = FL_status_string_signal_reserved_44;
          break;
        case F_signal_reserved_45:
          *string = FL_status_string_signal_reserved_45;
          break;
        case F_signal_reserved_46:
          *string = FL_status_string_signal_reserved_46;
          break;
        case F_signal_reserved_47:
          *string = FL_status_string_signal_reserved_47;
          break;
        case F_signal_reserved_48:
          *string = FL_status_string_signal_reserved_48;
          break;
        case F_signal_reserved_49:
          *string = FL_status_string_signal_reserved_49;
          break;
        case F_signal_reserved_50:
          *string = FL_status_string_signal_reserved_50;
          break;
        case F_signal_reserved_51:
          *string = FL_status_string_signal_reserved_51;
          break;
        case F_signal_reserved_52:
          *string = FL_status_string_signal_reserved_52;
          break;
        case F_signal_reserved_53:
          *string = FL_status_string_signal_reserved_53;
          break;
        case F_signal_reserved_54:
          *string = FL_status_string_signal_reserved_54;
          break;
        case F_signal_reserved_55:
          *string = FL_status_string_signal_reserved_55;
          break;
        case F_signal_reserved_56:
          *string = FL_status_string_signal_reserved_56;
          break;
        case F_signal_reserved_57:
          *string = FL_status_string_signal_reserved_57;
          break;
        case F_signal_reserved_58:
          *string = FL_status_string_signal_reserved_58;
          break;
        case F_signal_reserved_59:
          *string = FL_status_string_signal_reserved_59;
          break;
        case F_signal_reserved_60:
          *string = FL_status_string_signal_reserved_60;
          break;
        case F_signal_reserved_61:
          *string = FL_status_string_signal_reserved_61;
          break;
        case F_signal_reserved_62:
          *string = FL_status_string_signal_reserved_62;
          break;
        case F_signal_reserved_63:
          *string = FL_status_string_signal_reserved_63;
          break;
        case F_signal_reserved_64:
          *string = FL_status_string_signal_reserved_64;
          break;
      #endif // _di_F_status_signal_

      #ifndef _di_F_status_basic_
        case F_none:
          *string = FL_status_string_none;
          break;
        case F_absolute:
          *string = FL_status_string_absolute;
          break;
        case F_absolute_not:
          *string = FL_status_string_absolute_not;
          break;
        case F_address:
          *string = FL_status_string_address;
          break;
        case F_address_not:
          *string = FL_status_string_address_not;
          break;
        case F_ascii:
          *string = FL_status_string_ascii;
          break;
        case F_ascii_not:
          *string = FL_status_string_ascii_not;
          break;
        case F_block:
          *string = FL_status_string_block;
          break;
        case F_block_not:
          *string = FL_status_string_block_not;
          break;
        case F_bound:
          *string = FL_status_string_bound;
          break;
        case F_bound_not:
          *string = FL_status_string_bound_not;
          break;
        case F_capability:
          *string = FL_status_string_capability;
          break;
        case F_capability_not:
          *string = FL_status_string_capability_not;
          break;
        case F_child:
          *string = FL_status_string_child;
          break;
        case F_child_not:
          *string = FL_status_string_child_not;
          break;
        case F_complete:
          *string = FL_status_string_complete;
          break;
        case F_complete_not:
          *string = FL_status_string_complete_not;
          break;
        case F_connected:
          *string = FL_status_string_connected;
          break;
        case F_connected_not:
          *string = FL_status_string_connected_not;
          break;
        case F_container:
          *string = FL_status_string_container;
          break;
        case F_container_not:
          *string = FL_status_string_container_not;
          break;
        case F_control:
          *string = FL_status_string_control;
          break;
        case F_control_not:
          *string = FL_status_string_control_not;
          break;
        case F_control_group:
          *string = FL_status_string_control_group;
          break;
        case F_control_group_not:
          *string = FL_status_string_control_group_not;
          break;
        case F_critical:
          *string = FL_status_string_critical;
          break;
        case F_critical_not:
          *string = FL_status_string_critical_not;
          break;
        case F_dead:
          *string = FL_status_string_dead;
          break;
        case F_dead_not:
          *string = FL_status_string_dead_not;
          break;
        case F_deadlock:
          *string = FL_status_string_deadlock;
          break;
        case F_deadlock_not:
          *string = FL_status_string_deadlock_not;
          break;
        case F_descriptor:
          *string = FL_status_string_descriptor;
          break;
        case F_descriptor_not:
          *string = FL_status_string_descriptor_not;
          break;
        case F_device:
          *string = FL_status_string_device;
          break;
        case F_device_not:
          *string = FL_status_string_device_not;
          break;
        case F_disable:
          *string = FL_status_string_disable;
          break;
        case F_disable_not:
          *string = FL_status_string_disable_not;
          break;
        case F_done:
          *string = FL_status_string_done;
          break;
        case F_done_not:
          *string = FL_status_string_done_not;
          break;
        case F_dummy:
          *string = FL_status_string_dummy;
          break;
        case F_dummy_not:
          *string = FL_status_string_dummy_not;
          break;
        case F_empty:
          *string = FL_status_string_empty;
          break;
        case F_empty_not:
          *string = FL_status_string_empty_not;
          break;
        case F_enable:
          *string = FL_status_string_enable;
          break;
        case F_enable_not:
          *string = FL_status_string_enable_not;
          break;
        case F_encoding:
          *string = FL_status_string_encoding;
          break;
        case F_encoding_not:
          *string = FL_status_string_encoding_not;
          break;
        case F_eoa:
          *string = FL_status_string_eoa;
          break;
        case F_eoa_not:
          *string = FL_status_string_eoa_not;
          break;
        case F_eof:
          *string = FL_status_string_eof;
          break;
        case F_eof_not:
          *string = FL_status_string_eof_not;
          break;
        case F_eol:
          *string = FL_status_string_eol;
          break;
        case F_eol_not:
          *string = FL_status_string_eol_not;
          break;
        case F_eos:
          *string = FL_status_string_eos;
          break;
        case F_eos_not:
          *string = FL_status_string_eos_not;
          break;
        case F_execute:
          *string = FL_status_string_execute;
          break;
        case F_execute_not:
          *string = FL_status_string_execute_not;
          break;
        case F_exist:
          *string = FL_status_string_exist;
          break;
        case F_exist_not:
          *string = FL_status_string_exist_not;
          break;
        case F_failure:
          *string = FL_status_string_failure;
          break;
        case F_failure_not:
          *string = FL_status_string_failure_not;
          break;
        case F_fork:
          *string = FL_status_string_fork;
          break;
        case F_fork_not:
          *string = FL_status_string_fork_not;
          break;
        case F_format:
          *string = FL_status_string_format;
          break;
        case F_format_not:
          *string = FL_status_string_format_not;
          break;
        case F_found:
          *string = FL_status_string_found;
          break;
        case F_found_not:
          *string = FL_status_string_found_not;
          break;
        case F_full:
          *string = FL_status_string_full;
          break;
        case F_full_not:
          *string = FL_status_string_full_not;
          break;
        case F_group:
          *string = FL_status_string_group;
          break;
        case F_group_not:
          *string = FL_status_string_group_not;
          break;
        case F_ignore:
          *string = FL_status_string_ignore;
          break;
        case F_ignore_not:
          *string = FL_status_string_ignore_not;
          break;
        case F_implemented:
          *string = FL_status_string_implemented;
          break;
        case F_implemented_not:
          *string = FL_status_string_implemented_not;
          break;
        case F_input:
          *string = FL_status_string_input;
          break;
        case F_input_not:
          *string = FL_status_string_input_not;
          break;
        case F_input_output:
          *string = FL_status_string_input_output;
          break;
        case F_interrupt:
          *string = FL_status_string_interrupt;
          break;
        case F_interrupt_not:
          *string = FL_status_string_interrupt_not;
          break;
        case F_limit:
          *string = FL_status_string_limit;
          break;
        case F_limit_not:
          *string = FL_status_string_limit_not;
          break;
        case F_link:
          *string = FL_status_string_link;
          break;
        case F_link_not:
          *string = FL_status_string_link_not;
          break;
        case F_live:
          *string = FL_status_string_live;
          break;
        case F_live_not:
          *string = FL_status_string_live_not;
          break;
        case F_lock:
          *string = FL_status_string_lock;
          break;
        case F_lock_not:
          *string = FL_status_string_lock_not;
          break;
        case F_loop:
          *string = FL_status_string_loop;
          break;
        case F_loop_not:
          *string = FL_status_string_loop_not;
          break;
        case F_maybe:
          *string = FL_status_string_maybe;
          break;
        case F_maybe_not:
          *string = FL_status_string_maybe_not;
          break;
        case F_memory:
          *string = FL_status_string_memory;
          break;
        case F_memory_not:
          *string = FL_status_string_memory_not;
          break;
        case F_minor:
          *string = FL_status_string_minor;
          break;
        case F_minor_not:
          *string = FL_status_string_minor_not;
          break;
        case F_moderate:
          *string = FL_status_string_moderate;
          break;
        case F_moderate_not:
          *string = FL_status_string_moderate_not;
          break;
        case F_mount:
          *string = FL_status_string_mount;
          break;
        case F_mount_not:
          *string = FL_status_string_mount_not;
          break;
        case F_name:
          *string = FL_status_string_name;
          break;
        case F_name_not:
          *string = FL_status_string_name_not;
          break;
        case F_nice:
          *string = FL_status_string_nice;
          break;
        case F_nice_not:
          *string = FL_status_string_nice_not;
          break;
        case F_optional:
          *string = FL_status_string_optional;
          break;
        case F_optional_not:
          *string = FL_status_string_optional_not;
          break;
        case F_output:
          *string = FL_status_string_output;
          break;
        case F_output_not:
          *string = FL_status_string_output_not;
          break;
        case F_parameter:
          *string = FL_status_string_parameter;
          break;
        case F_parameter_not:
          *string = FL_status_string_parameter_not;
          break;
        case F_parent:
          *string = FL_status_string_parent;
          break;
        case F_parent_not:
          *string = FL_status_string_parent_not;
          break;
        case F_pipe:
          *string = FL_status_string_pipe;
          break;
        case F_pipe_not:
          *string = FL_status_string_pipe_not;
          break;
        case F_port:
          *string = FL_status_string_port;
          break;
        case F_port_not:
          *string = FL_status_string_port_not;
          break;
        case F_processor:
          *string = FL_status_string_processor;
          break;
        case F_processor_not:
          *string = FL_status_string_processor_not;
          break;
        case F_prohibited:
          *string = FL_status_string_prohibited;
          break;
        case F_prohibited_not:
          *string = FL_status_string_prohibited_not;
          break;
        case F_range:
          *string = FL_status_string_range;
          break;
        case F_range_not:
          *string = FL_status_string_range_not;
          break;
        case F_read:
          *string = FL_status_string_read;
          break;
        case F_read_not:
          *string = FL_status_string_read_not;
          break;
        case F_read_only:
          *string = FL_status_string_read_only;
          break;
        case F_ready:
          *string = FL_status_string_ready;
          break;
        case F_ready_not:
          *string = FL_status_string_ready_not;
          break;
        case F_recover:
          *string = FL_status_string_recover;
          break;
        case F_recover_not:
          *string = FL_status_string_recover_not;
          break;
        case F_recurse:
          *string = FL_status_string_recurse;
          break;
        case F_recurse_not:
          *string = FL_status_string_recurse_not;
          break;
        case F_relative:
          *string = FL_status_string_relative;
          break;
        case F_relative_not:
          *string = FL_status_string_relative_not;
          break;
        case F_require:
          *string = FL_status_string_require;
          break;
        case F_require_not:
          *string = FL_status_string_require_not;
          break;
        case F_resource:
          *string = FL_status_string_resource;
          break;
        case F_resource_not:
          *string = FL_status_string_resource_not;
          break;
        case F_search:
          *string = FL_status_string_search;
          break;
        case F_search_not:
          *string = FL_status_string_search_not;
          break;
        case F_schedule:
          *string = FL_status_string_schedule;
          break;
        case F_schedule_not:
          *string = FL_status_string_schedule_not;
          break;
        case F_signal:
          *string = FL_status_string_signal;
          break;
        case F_signal_not:
          *string = FL_status_string_signal_not;
          break;
        case F_space:
          *string = FL_status_string_space;
          break;
        case F_space_not:
          *string = FL_status_string_space_not;
          break;
        case F_stop:
          *string = FL_status_string_stop;
          break;
        case F_stop_not:
          *string = FL_status_string_stop_not;
          break;
        case F_string:
          *string = FL_status_string_string;
          break;
        case F_string_not:
          *string = FL_status_string_string_not;
          break;
        case F_string_too_large:
          *string = FL_status_string_string_too_large;
          break;
        case F_string_too_small:
          *string = FL_status_string_string_too_small;
          break;
        case F_syntax:
          *string = FL_status_string_syntax;
          break;
        case F_syntax_not:
          *string = FL_status_string_syntax_not;
          break;
        case F_thread:
          *string = FL_status_string_thread;
          break;
        case F_thread_not:
          *string = FL_status_string_thread_not;
          break;
        case F_time:
          *string = FL_status_string_time;
          break;
        case F_time_not:
          *string = FL_status_string_time_not;
          break;
        case F_too_large:
          *string = FL_status_string_too_large;
          break;
        case F_too_small:
          *string = FL_status_string_too_small;
          break;
        case F_known:
          *string = FL_status_string_known;
          break;
        case F_known_not:
          *string = FL_status_string_known_not;
          break;
        case F_success:
          *string = FL_status_string_success;
          break;
        case F_success_not:
          *string = FL_status_string_success_not;
          break;
        case F_supported:
          *string = FL_status_string_supported;
          break;
        case F_supported_not:
          *string = FL_status_string_supported_not;
          break;
        case F_user:
          *string = FL_status_string_user;
          break;
        case F_user_not:
          *string = FL_status_string_user_not;
          break;
        case F_utf:
          *string = FL_status_string_utf;
          break;
        case F_utf_not:
          *string = FL_status_string_utf_not;
          break;
        case F_valid:
          *string = FL_status_string_valid;
          break;
        case F_valid_not:
          *string = FL_status_string_valid_not;
          break;
        case F_value:
          *string = FL_status_string_value;
          break;
        case F_value_not:
          *string = FL_status_string_value_not;
          break;
        case F_wait:
          *string = FL_status_string_wait;
          break;
        case F_wait_not:
          *string = FL_status_string_wait_not;
          break;
        case F_warn:
          *string = FL_status_string_warn;
          break;
        case F_warn_not:
          *string = FL_status_string_warn_not;
          break;
        case F_world:
          *string = FL_status_string_world;
          break;
        case F_world_not:
          *string = FL_status_string_world_not;
          break;
        case F_write:
          *string = FL_status_string_write;
          break;
        case F_write_not:
          *string = FL_status_string_write_not;
          break;
        case F_write_only:
          *string = FL_status_string_write_only;
          break;
      #endif // _di_F_status_basic_

      #ifndef _di_F_status_array_
        case F_array:
          *string = FL_status_string_array;
          break;
        case F_array_not:
          *string = FL_status_string_array_not;
          break;
        case F_array_too_large:
          *string = FL_status_string_array_too_large;
          break;
        case F_array_too_small:
          *string = FL_status_string_array_too_small;
          break;
      #endif // _di_F_status_array_

      #ifndef _di_F_status_available_
        case F_available:
          *string = FL_status_string_available;
          break;
        case F_available_not:
          *string = FL_status_string_available_not;
          break;
        case F_available_not_address:
          *string = FL_status_string_available_not_address;
          break;
        case F_available_not_buffer:
          *string = FL_status_string_available_not_buffer;
          break;
        case F_available_not_device:
          *string = FL_status_string_available_not_device;
          break;
        case F_available_not_pipe:
          *string = FL_status_string_available_not_pipe;
          break;
        case F_available_not_port:
          *string = FL_status_string_available_not_port;
          break;
        case F_available_not_process:
          *string = FL_status_string_available_not_process;
          break;
        case F_available_not_socket:
          *string = FL_status_string_available_not_socket;
          break;
      #endif // _di_F_status_available_

      #ifndef _di_F_status_busy_
        case F_busy:
          *string = FL_status_string_busy;
          break;
        case F_busy_address:
          *string = FL_status_string_busy_address;
          break;
        case F_busy_buffer:
          *string = FL_status_string_busy_buffer;
          break;
        case F_busy_device:
          *string = FL_status_string_busy_device;
          break;
        case F_busy_not:
          *string = FL_status_string_busy_not;
          break;
        case F_busy_pipe:
          *string = FL_status_string_busy_pipe;
          break;
        case F_busy_port:
          *string = FL_status_string_busy_port;
          break;
        case F_busy_process:
          *string = FL_status_string_busy_process;
          break;
        case F_busy_socket:
          *string = FL_status_string_busy_socket;
          break;
      #endif // _di_F_status_busy_

      #ifndef _di_F_status_number_
        case F_number:
          *string = FL_status_string_number;
          break;
        case F_number_decimal:
          *string = FL_status_string_number_decimal;
          break;
        case F_number_decimal_not:
          *string = FL_status_string_number_decimal_not;
          break;
        case F_number_divide_by_zero:
          *string = FL_status_string_number_divide_by_zero;
          break;
        case F_number_negative:
          *string = FL_status_string_number_negative;
          break;
        case F_number_negative_not:
          *string = FL_status_string_number_negative_not;
          break;
        case F_number_not:
          *string = FL_status_string_number_not;
          break;
        case F_number_overflow:
          *string = FL_status_string_number_overflow;
          break;
        case F_number_positive:
          *string = FL_status_string_number_positive;
          break;
        case F_number_positive_not:
          *string = FL_status_string_number_positive_not;
          break;
        case F_number_too_large:
          *string = FL_status_string_number_too_large;
          break;
        case F_number_too_small:
          *string = FL_status_string_number_too_small;
          break;
        case F_number_underflow:
          *string = FL_status_string_number_underflow;
          break;
        case F_number_whole:
          *string = FL_status_string_number_whole;
          break;
        case F_number_whole_not:
          *string = FL_status_string_number_whole_not;
          break;
        case F_number_zero:
          *string = FL_status_string_number_zero;
          break;
        case F_number_zero_not:
          *string = FL_status_string_number_zero_not;
          break;
      #endif // _di_F_status_number_

      #ifndef _di_F_status_buffers_
        case F_buffer:
          *string = FL_status_string_buffer;
          break;
        case F_buffer_not:
          *string = FL_status_string_buffer_not;
          break;
        case F_buffer_too_large:
          *string = FL_status_string_buffer_too_large;
          break;
        case F_buffer_too_small:
          *string = FL_status_string_buffer_too_small;
          break;
        case F_complete_not_utf_block:
          *string = FL_status_string_complete_not_utf_block;
          break;
        case F_complete_not_utf_eoa:
          *string = FL_status_string_complete_not_utf_eoa;
          break;
        case F_complete_not_utf_eof:
          *string = FL_status_string_complete_not_utf_eof;
          break;
        case F_complete_not_utf_eol:
          *string = FL_status_string_complete_not_utf_eol;
          break;
        case F_complete_not_utf_eos:
          *string = FL_status_string_complete_not_utf_eos;
          break;
        case F_complete_not_utf_stop:
          *string = FL_status_string_complete_not_utf_stop;
          break;
        case F_none_block:
          *string = FL_status_string_none_block;
          break;
        case F_none_eoa:
          *string = FL_status_string_none_eoa;
          break;
        case F_none_eof:
          *string = FL_status_string_none_eof;
          break;
        case F_none_eol:
          *string = FL_status_string_none_eol;
          break;
        case F_none_eos:
          *string = FL_status_string_none_eos;
          break;
        case F_none_stop:
          *string = FL_status_string_none_stop;
          break;
        case F_data:
          *string = FL_status_string_data;
          break;
        case F_data_not:
          *string = FL_status_string_data_not;
          break;
        case F_data_not_block:
          *string = FL_status_string_data_not_block;
          break;
        case F_data_not_eoa:
          *string = FL_status_string_data_not_eoa;
          break;
        case F_data_not_eof:
          *string = FL_status_string_data_not_eof;
          break;
        case F_data_not_eol:
          *string = FL_status_string_data_not_eol;
          break;
        case F_data_not_eos:
          *string = FL_status_string_data_not_eos;
          break;
        case F_data_not_stop:
          *string = FL_status_string_data_not_stop;
          break;
        case F_terminated:
          *string = FL_status_string_terminated;
          break;
        case F_terminated_not:
          *string = FL_status_string_terminated_not;
          break;
        case F_terminated_not_block:
          *string = FL_status_string_terminated_not_block;
          break;
        case F_terminated_not_eoa:
          *string = FL_status_string_terminated_not_eoa;
          break;
        case F_terminated_not_eof:
          *string = FL_status_string_terminated_not_eof;
          break;
        case F_terminated_not_eol:
          *string = FL_status_string_terminated_not_eol;
          break;
        case F_terminated_not_eos:
          *string = FL_status_string_terminated_not_eos;
          break;
        case F_terminated_not_group:
          *string = FL_status_string_terminated_not_group;
          break;
        case F_terminated_not_group_block:
          *string = FL_status_string_terminated_not_group_block;
          break;
        case F_terminated_not_group_eoa:
          *string = FL_status_string_terminated_not_group_eoa;
          break;
        case F_terminated_not_group_eof:
          *string = FL_status_string_terminated_not_group_eof;
          break;
        case F_terminated_not_group_eol:
          *string = FL_status_string_terminated_not_group_eol;
          break;
        case F_terminated_not_group_eos:
          *string = FL_status_string_terminated_not_group_eos;
          break;
        case F_terminated_not_group_stop:
          *string = FL_status_string_terminated_not_group_stop;
          break;
        case F_terminated_not_nest:
          *string = FL_status_string_terminated_not_nest;
          break;
        case F_terminated_not_nest_block:
          *string = FL_status_string_terminated_not_nest_block;
          break;
        case F_terminated_not_nest_eoa:
          *string = FL_status_string_terminated_not_nest_eoa;
          break;
        case F_terminated_not_nest_eof:
          *string = FL_status_string_terminated_not_nest_eof;
          break;
        case F_terminated_not_nest_eol:
          *string = FL_status_string_terminated_not_nest_eol;
          break;
        case F_terminated_not_nest_eos:
          *string = FL_status_string_terminated_not_nest_eos;
          break;
        case F_terminated_not_nest_stop:
          *string = FL_status_string_terminated_not_nest_stop;
          break;
        case F_terminated_not_stop:
          *string = FL_status_string_terminated_not_stop;
          break;
      #endif // _di_F_status_buffers_

      #ifndef _di_F_status_process_
        case F_process:
          *string = FL_status_string_process;
          break;
        case F_process_not:
          *string = FL_status_string_process_not;
          break;
        case F_process_too_many:
          *string = FL_status_string_process_too_many;
          break;
      #endif // _di_F_status_process_

      #ifndef _di_F_status_file_
        case F_file:
          *string = FL_status_string_file;
          break;
        case F_file_close:
          *string = FL_status_string_file_close;
          break;
        case F_file_closed:
          *string = FL_status_string_file_closed;
          break;
        case F_file_descriptor:
          *string = FL_status_string_file_descriptor;
          break;
        case F_file_descriptor_max:
          *string = FL_status_string_file_descriptor_max;
          break;
        case F_file_descriptor_not:
          *string = FL_status_string_file_descriptor_not;
          break;
        case F_file_empty:
          *string = FL_status_string_file_empty;
          break;
        case F_file_flush:
          *string = FL_status_string_file_flush;
          break;
        case F_file_found:
          *string = FL_status_string_file_found;
          break;
        case F_file_found_not:
          *string = FL_status_string_file_found_not;
          break;
        case F_file_not:
          *string = FL_status_string_file_not;
          break;
        case F_file_open:
          *string = FL_status_string_file_open;
          break;
        case F_file_open_max:
          *string = FL_status_string_file_open_max;
          break;
        case F_file_opened:
          *string = FL_status_string_file_opened;
          break;
        case F_file_overflow:
          *string = FL_status_string_file_overflow;
          break;
        case F_file_purge:
          *string = FL_status_string_file_purge;
          break;
        case F_file_read:
          *string = FL_status_string_file_read;
          break;
        case F_file_reallocation:
          *string = FL_status_string_file_reallocation;
          break;
        case F_file_seek:
          *string = FL_status_string_file_seek;
          break;
        case F_file_stat:
          *string = FL_status_string_file_stat;
          break;
        case F_file_synchronize:
          *string = FL_status_string_file_synchronize;
          break;
        case F_file_type_block:
          *string = FL_status_string_file_type_block;
          break;
        case F_file_type_character:
          *string = FL_status_string_file_type_character;
          break;
        case F_file_type_directory:
          *string = FL_status_string_file_type_directory;
          break;
        case F_file_type_fifo:
          *string = FL_status_string_file_type_fifo;
          break;
        case F_file_type_link:
          *string = FL_status_string_file_type_link;
          break;
        case F_file_type_not_character:
          *string = FL_status_string_file_type_not_character;
          break;
        case F_file_type_not_directory:
          *string = FL_status_string_file_type_not_directory;
          break;
        case F_file_type_not_fifo:
          *string = FL_status_string_file_type_not_fifo;
          break;
        case F_file_type_not_link:
          *string = FL_status_string_file_type_not_link;
          break;
        case F_file_type_not_pipe:
          *string = FL_status_string_file_type_not_pipe;
          break;
        case F_file_type_not_regular:
          *string = FL_status_string_file_type_not_regular;
          break;
        case F_file_type_not_socket:
          *string = FL_status_string_file_type_not_socket;
          break;
        case F_file_type_not_unknown:
          *string = FL_status_string_file_type_not_unknown;
          break;
        case F_file_type_pipe:
          *string = FL_status_string_file_type_pipe;
          break;
        case F_file_type_regular:
          *string = FL_status_string_file_type_regular;
          break;
        case F_file_type_socket:
          *string = FL_status_string_file_type_socket;
          break;
        case F_file_type_unknown:
          *string = FL_status_string_file_type_unknown;
          break;
        case F_file_underflow:
          *string = FL_status_string_file_underflow;
          break;
        case F_file_utf:
          *string = FL_status_string_file_utf;
          break;
        case F_file_utf_not:
          *string = FL_status_string_file_utf_not;
          break;
        case F_file_write:
          *string = FL_status_string_file_write;
          break;
      #endif // _di_F_status_file_

      #ifndef _di_F_status_filesystem_
        case F_filesystem:
          *string = FL_status_string_filesystem;
          break;
        case F_filesystem_not:
          *string = FL_status_string_filesystem_not;
          break;
        case F_filesystem_quota_block:
          *string = FL_status_string_filesystem_quota_block;
          break;
        case F_filesystem_quota_reached:
          *string = FL_status_string_filesystem_quota_reached;
          break;
      #endif // _di_F_status_filesystem_

      #ifndef _di_F_status_directory_
        case F_directory:
          *string = FL_status_string_directory;
          break;
        case F_directory_close:
          *string = FL_status_string_directory_close;
          break;
        case F_directory_closed:
          *string = FL_status_string_directory_closed;
          break;
        case F_directory_descriptor:
          *string = FL_status_string_directory_descriptor;
          break;
        case F_directory_empty:
          *string = FL_status_string_directory_empty;
          break;
        case F_directory_empty_not:
          *string = FL_status_string_directory_empty_not;
          break;
        case F_directory_found:
          *string = FL_status_string_directory_found;
          break;
        case F_directory_found_not:
          *string = FL_status_string_directory_found_not;
          break;
        case F_directory_flush:
          *string = FL_status_string_directory_flush;
          break;
        case F_directory_link_max:
          *string = FL_status_string_directory_link_max;
          break;
        case F_directory_not:
          *string = FL_status_string_directory_not;
          break;
        case F_directory_open:
          *string = FL_status_string_directory_open;
          break;
        case F_directory_purge:
          *string = FL_status_string_directory_purge;
          break;
        case F_directory_read:
          *string = FL_status_string_directory_read;
          break;
        case F_directory_stream:
          *string = FL_status_string_directory_stream;
          break;
        case F_directory_synchronize:
          *string = FL_status_string_directory_synchronize;
          break;
        case F_directory_supported_not:
          *string = FL_status_string_directory_supported_not;
          break;
        case F_directory_utf:
          *string = FL_status_string_directory_utf;
          break;
        case F_directory_utf_not:
          *string = FL_status_string_directory_utf_not;
          break;
        case F_directory_write:
          *string = FL_status_string_directory_utf_not;
          break;
      #endif // _di_F_status_directory_

      #ifndef _di_F_status_socket_
        case F_socket:
          *string = FL_status_string_socket;
          break;
        case F_socket_client:
          *string = FL_status_string_socket_client;
          break;
        case F_socket_not:
          *string = FL_status_string_socket_not;
          break;
        case F_socket_receive:
          *string = FL_status_string_socket_receive;
          break;
        case F_socket_send:
          *string = FL_status_string_socket_send;
          break;
        case F_socket_target:
          *string = FL_status_string_socket_target;
          break;
      #endif // _di_F_status_socket_

      #ifndef _di_F_error_compare_
        case F_equal_to:
          *string = FL_status_string_equal_to;
          break;
        case F_equal_to_not:
          *string = FL_status_string_equal_to_not;
          break;
        case F_than_greater:
          *string = FL_status_string_than_greater;
          break;
        case F_than_less:
          *string = FL_status_string_than_less;
          break;
      #endif // _di_F_status_compare_

      #ifndef _di_F_status_access_
        case F_access:
          *string = FL_status_string_access;
          break;
        case F_access_denied:
          *string = FL_status_string_access_denied;
          break;
        case F_access_denied_user:
          *string = FL_status_string_access_denied_user;
          break;
        case F_access_denied_group:
          *string = FL_status_string_access_denied_group;
          break;
        case F_access_denied_world:
          *string = FL_status_string_access_denied_world;
          break;
        case F_access_denied_read:
          *string = FL_status_string_access_denied_read;
          break;
        case F_access_denied_write:
          *string = FL_status_string_access_denied_write;
          break;
        case F_access_denied_execute:
          *string = FL_status_string_access_denied_execute;
          break;
        case F_access_denied_super:
          *string = FL_status_string_access_denied_super;
          break;
        case F_access_granted:
          *string = FL_status_string_access_granted;
          break;
        case F_access_granted_user:
          *string = FL_status_string_access_granted_user;
          break;
        case F_access_granted_group:
          *string = FL_status_string_access_granted_group;
          break;
        case F_access_granted_world:
          *string = FL_status_string_access_granted_world;
          break;
        case F_access_granted_read:
          *string = FL_status_string_access_granted_read;
          break;
        case F_access_granted_write:
          *string = FL_status_string_access_granted_write;
          break;
        case F_access_granted_execute:
          *string = FL_status_string_access_granted_execute;
          break;
        case F_access_granted_super:
          *string = FL_status_string_access_granted_super;
          break;
        case F_access_group:
          *string = FL_status_string_access_group;
          break;
        case F_access_mode:
          *string = FL_status_string_access_mode;
          break;
        case F_access_not:
          *string = FL_status_string_access_not;
          break;
        case F_access_owner:
          *string = FL_status_string_access_owner;
          break;
      #endif // _di_F_status_access_

      #ifndef _di_F_status_terminal_
        case F_terminal:
          *string = FL_status_string_terminal;
          break;
        case F_terminal_access:
          *string = FL_status_string_terminal_access;
          break;
        case F_terminal_known:
          *string = FL_status_string_terminal_known;
          break;
        case F_terminal_known_not:
          *string = FL_status_string_terminal_known_not;
          break;
        case F_terminal_not:
          *string = FL_status_string_terminal_not;
          break;
        case F_terminal_prohibited:
          *string = FL_status_string_terminal_prohibited;
          break;
        case F_terminal_read:
          *string = FL_status_string_terminal_read;
          break;
        case F_terminal_valid:
          *string = FL_status_string_terminal_valid;
          break;
        case F_terminal_valid_not:
          *string = FL_status_string_terminal_valid_not;
          break;
        case F_terminal_write:
          *string = FL_status_string_terminal_write;
          break;
      #endif // _di_F_status_terminal_

      case F_status_code_last:
        *string = FL_status_string_status_code_last;
        break;

      default:
        *string = 0;

        return F_status_set_error(F_data);
    }

    return F_none;
  }
#endif // _di_fl_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

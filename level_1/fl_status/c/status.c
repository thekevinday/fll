#include <level_1/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_status_to_string_
  f_return_status fl_status_to_string(const f_status code, f_string *string) {
    #ifndef _di_level_1_parameter_checking_
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status unmasked_code = f_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_fl_status_booleans_
        case f_false:
          *string = fl_status_string_false;
          break;
        case f_true:
          *string = fl_status_string_true;
          break;
      #endif // _di_fl_status_booleans_

      #ifndef _di_fl_status_signals_
        // f_signal_hangup is not used because it has the same code as f_true.
        case f_signal_interrupt:
          *string = fl_status_string_signal_interrupt;
          break;
        case f_signal_quit:
          *string = fl_status_string_signal_quit;
          break;
        case f_signal_illegal:
          *string = fl_status_string_signal_illegal;
          break;
        case f_signal_trap:
          *string = fl_status_string_signal_trap;
          break;
        case f_signal_abort:
          *string = fl_status_string_signal_abort;
          break;
        case f_signal_bus_error:
          *string = fl_status_string_signal_bus_error;
          break;
        case f_signal_floating_point_exception:
          *string = fl_status_string_signal_floating_point_exception;
          break;
        case f_signal_kill:
          *string = fl_status_string_signal_kill;
          break;
        case f_signal_user_1:
          *string = fl_status_string_signal_user_1;
          break;
        case f_signal_segmentation_fault:
          *string = fl_status_string_signal_segmentation_fault;
          break;
        case f_signal_user_2:
          *string = fl_status_string_signal_user_2;
          break;
        case f_signal_broken_pipe:
          *string = fl_status_string_signal_broken_pipe;
          break;
        case f_signal_alarm_clock:
          *string = fl_status_string_signal_alarm_clock;
          break;
        case f_signal_termination:
          *string = fl_status_string_signal_termination;
          break;
        case f_signal_stack_fault:
          *string = fl_status_string_signal_stack_fault;
          break;
        case f_signal_child:
          *string = fl_status_string_signal_child;
          break;
        case f_signal_continue:
          *string = fl_status_string_signal_continue;
          break;
        case f_signal_stop:
          *string = fl_status_string_signal_stop;
          break;
        case f_signal_keyboard_stop:
          *string = fl_status_string_signal_keyboard_stop;
          break;
        case f_signal_tty_in:
          *string = fl_status_string_signal_tty_in;
          break;
        case f_signal_tty_out:
          *string = fl_status_string_signal_tty_out;
          break;
        case f_signal_urgent:
          *string = fl_status_string_signal_urgent;
          break;
        case f_signal_cpu_limit:
          *string = fl_status_string_signal_cpu_limit;
          break;
        case f_signal_file_size_limit:
          *string = fl_status_string_signal_file_size_limit;
          break;
        case f_signal_virtual_alarm_clock:
          *string = fl_status_string_signal_virtual_alarm_clock;
          break;
        case f_signal_profile_alarm_clock:
          *string = fl_status_string_signal_profile_alarm_clock;
          break;
        case f_signal_window_size_change:
          *string = fl_status_string_signal_window_size_change;
          break;
        case f_signal_pollable_event:
          *string = fl_status_string_signal_pollable_event;
          break;
        case f_signal_power_failure:
          *string = fl_status_string_signal_power_failure;
          break;
        case f_signal_bad_system_call:
          *string = fl_status_string_signal_bad_system_call;
          break;
        case f_signal_reserved_32:
          *string = fl_status_string_signal_reserved_32;
          break;
        case f_signal_reserved_33:
          *string = fl_status_string_signal_reserved_33;
          break;
        case f_signal_reserved_34:
          *string = fl_status_string_signal_reserved_34;
          break;
        case f_signal_reserved_35:
          *string = fl_status_string_signal_reserved_35;
          break;
        case f_signal_reserved_36:
          *string = fl_status_string_signal_reserved_36;
          break;
        case f_signal_reserved_37:
          *string = fl_status_string_signal_reserved_37;
          break;
        case f_signal_reserved_38:
          *string = fl_status_string_signal_reserved_38;
          break;
        case f_signal_reserved_39:
          *string = fl_status_string_signal_reserved_39;
          break;
        case f_signal_reserved_40:
          *string = fl_status_string_signal_reserved_40;
          break;
        case f_signal_reserved_41:
          *string = fl_status_string_signal_reserved_41;
          break;
        case f_signal_reserved_42:
          *string = fl_status_string_signal_reserved_42;
          break;
        case f_signal_reserved_43:
          *string = fl_status_string_signal_reserved_43;
          break;
        case f_signal_reserved_44:
          *string = fl_status_string_signal_reserved_44;
          break;
        case f_signal_reserved_45:
          *string = fl_status_string_signal_reserved_45;
          break;
        case f_signal_reserved_46:
          *string = fl_status_string_signal_reserved_46;
          break;
        case f_signal_reserved_47:
          *string = fl_status_string_signal_reserved_47;
          break;
        case f_signal_reserved_48:
          *string = fl_status_string_signal_reserved_48;
          break;
        case f_signal_reserved_49:
          *string = fl_status_string_signal_reserved_49;
          break;
        case f_signal_reserved_50:
          *string = fl_status_string_signal_reserved_50;
          break;
        case f_signal_reserved_51:
          *string = fl_status_string_signal_reserved_51;
          break;
        case f_signal_reserved_52:
          *string = fl_status_string_signal_reserved_52;
          break;
        case f_signal_reserved_53:
          *string = fl_status_string_signal_reserved_53;
          break;
        case f_signal_reserved_54:
          *string = fl_status_string_signal_reserved_54;
          break;
        case f_signal_reserved_55:
          *string = fl_status_string_signal_reserved_55;
          break;
        case f_signal_reserved_56:
          *string = fl_status_string_signal_reserved_56;
          break;
        case f_signal_reserved_57:
          *string = fl_status_string_signal_reserved_57;
          break;
        case f_signal_reserved_58:
          *string = fl_status_string_signal_reserved_58;
          break;
        case f_signal_reserved_59:
          *string = fl_status_string_signal_reserved_59;
          break;
        case f_signal_reserved_60:
          *string = fl_status_string_signal_reserved_60;
          break;
        case f_signal_reserved_61:
          *string = fl_status_string_signal_reserved_61;
          break;
        case f_signal_reserved_62:
          *string = fl_status_string_signal_reserved_62;
          break;
        case f_signal_reserved_63:
          *string = fl_status_string_signal_reserved_63;
          break;
        case f_signal_reserved_64:
          *string = fl_status_string_signal_reserved_64;
          break;
      #endif // _di_fl_status_signals_

      #ifndef _di_fl_status_basic_
        case f_none:
          *string = fl_status_string_none;
          break;
        case f_maybe:
          *string = fl_status_string_maybe;
          break;
        case f_dummy:
          *string = fl_status_string_dummy;
          break;
        case f_warn:
          *string = fl_status_string_warn;
          break;
        case f_critical:
          *string = fl_status_string_critical;
          break;
        case f_unknown:
          *string = fl_status_string_unknown;
          break;
        case f_unsupported:
          *string = fl_status_string_unsupported;
          break;
        case f_no_data:
          *string = fl_status_string_no_data;
          break;
        case f_out_of_memory:
          *string = fl_status_string_out_of_memory;
          break;
        case f_prohibited:
          *string = fl_status_string_prohibited;
          break;
        case f_read_only:
          *string = fl_status_string_read_only;
          break;
        case f_error_input:
          *string = fl_status_string_input_error;
          break;
        case f_error_output:
          *string = fl_status_string_output_error;
          break;
        case f_error_input_output:
          *string = fl_status_string_input_output_error;
          break;
        case f_does_not_exist:
          *string = fl_status_string_does_not_exist;
          break;
        case f_not_connected:
          *string = fl_status_string_not_connected;
          break;
        case f_failure:
          *string = fl_status_string_failure;
          break;
        case f_interrupted:
          *string = fl_status_string_interrupted;
          break;
        case f_loop:
          *string = fl_status_string_loop;
          break;
        case f_incomplete:
          *string = fl_status_string_incomplete;
          break;
        case f_write_only:
          *string = fl_status_string_write_only;
          break;
      #endif // _di_fl_status_basic_

      #ifndef _di_fl_status_invalid_
        case f_invalid:
          *string = fl_status_string_invalid;
          break;
        case f_invalid_name:
          *string = fl_status_string_invalid_name;
          break;
        case f_invalid_parameter:
          *string = fl_status_string_invalid_parameter;
          break;
        case f_invalid_syntax:
          *string = fl_status_string_invalid_syntax;
          break;
        case f_invalid_data:
          *string = fl_status_string_invalid_data;
          break;
        case f_invalid_file:
          *string = fl_status_string_invalid_file;
          break;
        case f_invalid_directory:
          *string = fl_status_string_invalid_directory;
          break;
        case f_invalid_descriptor:
          *string = fl_status_string_invalid_descriptor;
          break;
        case f_invalid_socket:
          *string = fl_status_string_invalid_socket;
          break;
        case f_invalid_device:
          *string = fl_status_string_invalid_device;
          break;
        case f_invalid_link:
          *string = fl_status_string_invalid_link;
          break;
        case f_invalid_pipe:
          *string = fl_status_string_invalid_pipe;
          break;
        case f_invalid_address:
          *string = fl_status_string_invalid_address;
          break;
        case f_invalid_port:
          *string = fl_status_string_invalid_port;
          break;
        case f_invalid_value:
          *string = fl_status_string_invalid_value;
          break;
        case f_invalid_buffer:
          *string = fl_status_string_invalid_buffer;
          break;
        case f_invalid_process:
          *string = fl_status_string_invalid_process;
          break;
        case f_invalid_utf:
          *string = fl_status_string_invalid_utf;
          break;
        case f_invalid_on_eof:
          *string = fl_status_string_invalid_on_eof;
          break;
        case f_invalid_on_eol:
          *string = fl_status_string_invalid_on_eol;
          break;
        case f_invalid_on_eos:
          *string = fl_status_string_invalid_on_eos;
          break;
        case f_invalid_on_stop:
          *string = fl_status_string_invalid_on_stop;
          break;
      #endif // _di_fl_status_invalid_

      #ifndef _di_fl_status_busy_
        case f_busy:
          *string = fl_status_string_busy;
          break;
        case f_busy_address:
          *string = fl_status_string_busy_address;
          break;
        case f_busy_port:
          *string = fl_status_string_busy_port;
          break;
        case f_busy_socket:
          *string = fl_status_string_busy_socket;
          break;
        case f_busy_device:
          *string = fl_status_string_busy_device;
          break;
        case f_busy_pipe:
          *string = fl_status_string_busy_pipe;
          break;
        case f_busy_buffer:
          *string = fl_status_string_busy_buffer;
          break;
        case f_busy_process:
          *string = fl_status_string_busy_process;
          break;
      #endif // _di_fl_status_busy_

      #ifndef _di_fl_status_unavailable_
        case f_unavailable:
          *string = fl_status_string_unavailable;
          break;
        case f_unavailable_address:
          *string = fl_status_string_unavailable_address;
          break;
        case f_unavailable_port:
          *string = fl_status_string_unavailable_port;
          break;
        case f_unavailable_socket:
          *string = fl_status_string_unavailable_socket;
          break;
        case f_unavailable_device:
          *string = fl_status_string_unavailable_device;
          break;
        case f_unavailable_pipe:
          *string = fl_status_string_unavailable_pipe;
          break;
        case f_unavailable_buffer:
          *string = fl_status_string_unavailable_buffer;
          break;
        case f_unavailable_process:
          *string = fl_status_string_unavailable_process;
          break;
      #endif // _di_fl_status_unavailable_

      #ifndef _di_fl_status_digits_
        case f_number_underflow:
          *string = fl_status_string_underflow;
          break;
        case f_number_overflow:
          *string = fl_status_string_overflow;
          break;
        case f_number_divide_by_zero:
          *string = fl_status_string_divide_by_zero;
          break;
        case f_number_negative:
          *string = fl_status_string_negative_number;
          break;
        case f_number_positive:
          *string = fl_status_string_positive_number;
          break;
        case f_number_zero:
          *string = fl_status_string_zero_number;
          break;
        case f_number_decimal:
          *string = fl_status_string_decimal_number;
          break;
        case f_number_whole:
          *string = fl_status_string_whole_number;
          break;
        case f_number_invalid:
          *string = fl_status_string_invalid_number;
          break;
      #endif // _di_fl_status_digits_

      #ifndef _di_fl_status_buffers_
        case f_no_data_on_eof:
          *string = fl_status_string_no_data_on_eof;
          break;
        case f_no_data_on_eol:
          *string = fl_status_string_no_data_on_eol;
          break;
        case f_no_data_on_eos:
          *string = fl_status_string_no_data_on_eos;
          break;
        case f_no_data_on_stop:
          *string = fl_status_string_no_data_on_stop;
          break;
        case f_none_on_eof:
          *string = fl_status_string_none_on_eof;
          break;
        case f_none_on_eol:
          *string = fl_status_string_none_on_eol;
          break;
        case f_none_on_eos:
          *string = fl_status_string_none_on_eos;
          break;
        case f_none_on_stop:
          *string = fl_status_string_none_on_stop;
          break;
        case f_error_on_eof:
          *string = fl_status_string_error_on_eof;
          break;
        case f_error_on_eol:
          *string = fl_status_string_error_on_eol;
          break;
        case f_error_on_eos:
          *string = fl_status_string_error_on_eos;
          break;
        case f_error_on_stop:
          *string = fl_status_string_error_on_stop;
          break;
        case f_buffer_too_small:
          *string = fl_status_string_buffer_too_small;
          break;
        case f_buffer_too_large:
          *string = fl_status_string_buffer_too_large;
          break;
        case f_string_too_small:
          *string = fl_status_string_string_too_small;
          break;
        case f_string_too_large:
          *string = fl_status_string_string_too_large;
          break;
        case f_unterminated:
          *string = fl_status_string_unterminated;
          break;
        case f_unterminated_on_eof:
          *string = fl_status_string_unterminated_on_eof;
          break;
        case f_unterminated_on_eol:
          *string = fl_status_string_unterminated_on_eol;
          break;
        case f_unterminated_on_eos:
          *string = fl_status_string_unterminated_on_eos;
          break;
        case f_unterminated_on_stop:
          *string = fl_status_string_unterminated_on_stop;
          break;
        case f_unterminated_group:
          *string = fl_status_string_unterminated_group;
          break;
        case f_unterminated_group_on_eof:
          *string = fl_status_string_unterminated_group_on_eof;
          break;
        case f_unterminated_group_on_eol:
          *string = fl_status_string_unterminated_group_on_eol;
          break;
        case f_unterminated_group_on_eos:
          *string = fl_status_string_unterminated_group_on_eos;
          break;
        case f_unterminated_group_on_stop:
          *string = fl_status_string_unterminated_group_on_stop;
          break;
        case f_unterminated_nest:
          *string = fl_status_string_unterminated_nest;
          break;
        case f_unterminated_nest_on_eof:
          *string = fl_status_string_unterminated_nest_on_eof;
          break;
        case f_unterminated_nest_on_eol:
          *string = fl_status_string_unterminated_nest_on_eol;
          break;
        case f_unterminated_nest_on_eos:
          *string = fl_status_string_unterminated_nest_on_eos;
          break;
        case f_unterminated_nest_on_stop:
          *string = fl_status_string_unterminated_nest_on_stop;
          break;
        case f_incomplete_utf:
          *string = fl_status_string_incomplete_utf;
          break;
        case f_incomplete_utf_on_eof:
          *string = fl_status_string_incomplete_utf_on_eof;
          break;
        case f_incomplete_utf_on_eol:
          *string = fl_status_string_incomplete_utf_on_eol;
          break;
        case f_incomplete_utf_on_eos:
          *string = fl_status_string_incomplete_utf_on_eos;
          break;
        case f_incomplete_utf_on_stop:
          *string = fl_status_string_incomplete_utf_on_stop;
          break;
      #endif // _di_fl_status_buffers_

      #ifndef _di_fl_status_allocation_
        case f_error_allocation:
          *string = fl_status_string_allocation_error;
          break;
        case f_error_reallocation:
          *string = fl_status_string_reallocation_error;
          break;
        case f_error_deallocation:
          *string = fl_status_string_deallocation_error;
          break;
      #endif // _di_fl_status_allocation_

      #ifndef _di_fl_status_fork_
        case f_fork_failed:
          *string = fl_status_string_fork_failed;
          break;
        case f_too_many_processes:
          *string = fl_status_string_too_many_processes;
          break;
      #endif // _di_fl_status_fork_

      #ifndef _di_fl_status_file_
        case f_file_error_seek:
          *string = fl_status_string_file_seek_error;
          break;
        case f_file_error_read:
          *string = fl_status_string_file_read_error;
          break;
        case f_file_error_write:
          *string = fl_status_string_file_write_error;
          break;
        case f_file_error_flush:
          *string = fl_status_string_file_flush_error;
          break;
        case f_file_error_purge:
          *string = fl_status_string_file_purge_error;
          break;
        case f_file_error_open:
          *string = fl_status_string_file_open_error;
          break;
        case f_file_error_close:
          *string = fl_status_string_file_close_error;
          break;
        case f_file_error_synchronize:
          *string = fl_status_string_file_synchronize_error;
          break;
        case f_file_error_descriptor:
          *string = fl_status_string_file_descriptor_error;
          break;
        case f_file_not_found:
          *string = fl_status_string_file_not_found;
          break;
        case f_file_found:
          *string = fl_status_string_file_found;
          break;
        case f_file_is_empty:
          *string = fl_status_string_file_is_empty;
          break;
        case f_file_is_type_block:
          *string = fl_status_string_file_is_type_block;
          break;
        case f_file_is_type_character:
          *string = fl_status_string_file_is_type_character;
          break;
        case f_file_is_type_directory:
          *string = fl_status_string_file_is_type_directory;
          break;
        case f_file_is_type_file:
          *string = fl_status_string_file_is_type_file;
          break;
        case f_file_is_type_link:
          *string = fl_status_string_file_is_type_link;
          break;
        case f_file_is_type_pipe:
          *string = fl_status_string_file_is_type_pipe;
          break;
        case f_file_is_type_socket:
          *string = fl_status_string_file_is_type_socket;
          break;
        case f_file_is_type_unknown:
          *string = fl_status_string_file_is_type_unknown;
          break;
        case f_file_not_open:
          *string = fl_status_string_file_not_open;
          break;
        case f_file_not_type_block:
          *string = fl_status_string_file_not_type_block;
          break;
        case f_file_not_type_character:
          *string = fl_status_string_file_not_type_character;
          break;
        case f_file_not_type_directory:
          *string = fl_status_string_file_not_type_directory;
          break;
        case f_file_not_type_file:
          *string = fl_status_string_file_not_type_file;
          break;
        case f_file_not_type_link:
          *string = fl_status_string_file_not_type_link;
          break;
        case f_file_not_type_pipe:
          *string = fl_status_string_file_not_type_pipe;
          break;
        case f_file_not_type_socket:
          *string = fl_status_string_file_not_type_socket;
          break;
        case f_file_not_type_unknown:
          *string = fl_status_string_file_not_type_unknown;
          break;
        case f_file_error_allocation:
          *string = fl_status_string_file_allocation_error;
          break;
        case f_file_error_reallocation:
          *string = fl_status_string_file_reallocation_error;
          break;
        case f_file_error_deallocation:
          *string = fl_status_string_file_deallocation_error;
          break;
        case f_file_error_stat:
          *string = fl_status_string_file_stat_error;
          break;
        case f_file_error:
          *string = fl_status_string_file_error;
          break;
        case f_file_not_utf:
          *string = fl_status_string_file_not_utf;
          break;
        case f_file_max_descriptors:
          *string = fl_status_string_file_max_descriptors;
          break;
        case f_file_max_open:
          *string = fl_status_string_file_max_open;
          break;
      #endif // _di_fl_status_file_

      #ifndef _di_f_status_filesystem_
        case f_filesystem_error:
          *string = fl_status_string_filesystem_error;
          break;
        case f_filesystem_quota_blocks:
          *string = fl_status_string_filesystem_quota_blocks;
          break;
        case f_filesystem_quota_reached:
          *string = fl_status_string_filesystem_quota_reached;
          break;
      #endif // _di_f_status_filesystem_

      #ifndef _di_fl_status_directory_
        case f_directory_error_read:
          *string = fl_status_string_directory_read_error;
          break;
        case f_directory_error_write:
          *string = fl_status_string_directory_write_error;
          break;
        case f_directory_error_flush:
          *string = fl_status_string_directory_flush_error;
          break;
        case f_directory_error_link_max:
          *string = fl_status_string_directory_error_link_max;
          break;
        case f_directory_error_purge:
          *string = fl_status_string_directory_purge_error;
          break;
        case f_directory_error_open:
          *string = fl_status_string_directory_open_error;
          break;
        case f_directory_error_close:
          *string = fl_status_string_directory_close_error;
          break;
        case f_directory_error_synchronize:
          *string = fl_status_string_directory_synchronize_error;
          break;
        case f_directory_error_descriptor:
          *string = fl_status_string_directory_descriptor_error;
          break;
        case f_directory_not_found:
          *string = fl_status_string_directory_not_found;
          break;
        case f_directory_is_empty:
          *string = fl_status_string_directory_is_empty;
          break;
        case f_directory_not_open:
          *string = fl_status_string_directory_not_open;
          break;
        case f_directory_error:
          *string = fl_status_string_directory_error;
          break;
        case f_directory_not_utf:
          *string = fl_status_string_directory_not_utf;
          break;
        case f_directory_error_unsupported:
          *string = fl_status_string_directory_error_unsupported;
          break;
        case f_directory_error_stream:
          *string = fl_status_string_directory_error_stream;
          break;
      #endif // _di_fl_status_directory_

      #ifndef _di_fl_status_socket_
        case f_socket_error_connection_client:
          *string = fl_status_string_socket_connection_client_error;
          break;
        case f_socket_error_connection_target:
          *string = fl_status_string_socket_connection_target_error;
          break;
        case f_socket_error_receive:
          *string = fl_status_string_socket_receive_error;
          break;
        case f_socket_error_send:
          *string = fl_status_string_socket_send_error;
          break;
      #endif // _di_fl_status_socket_

      #ifndef _di_fll_error_non_
        case f_less_than:
          *string = fl_status_string_less_than;
          break;
        case f_equal_to:
          *string = fl_status_string_equal_to;
          break;
        case f_not_equal_to:
          *string = fl_status_string_not_equal_to;
          break;
        case f_greater_than:
          *string = fl_status_string_greater_than;
          break;
      #endif // _di_fl_status_non_

      #ifndef _di_fl_status_access_denied_
        case f_access_denied:
          *string = fl_status_string_access_denied;
          break;
        case f_access_denied_user:
          *string = fl_status_string_access_denied_user;
          break;
        case f_access_denied_group:
          *string = fl_status_string_access_denied_group;
          break;
        case f_access_denied_world:
          *string = fl_status_string_access_denied_world;
          break;
        case f_access_denied_read:
          *string = fl_status_string_access_denied_read;
          break;
        case f_access_denied_write:
          *string = fl_status_string_access_denied_write;
          break;
        case f_access_denied_execute:
          *string = fl_status_string_access_denied_execute;
          break;
        case f_access_denied_super:
          *string = fl_status_string_access_denied_super;
          break;
      #endif // _di_fl_status_access_denied_

      case f_status_code_last:
        *string = fl_status_string_status_code_last;
        break;

      default:
        *string = 0;
        return f_status_set_error(f_invalid_data);
    }

    return f_none;
  }
#endif // _di_fl_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

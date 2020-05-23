#include <level_1/status.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_status_to_string_
  f_return_status fl_status_to_string(const f_status code, f_string *string) {
    #ifndef _di_level_1_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_fl_status_booleans_
        case F_false:
          *string = fl_status_string_false;
          break;
        case F_true:
          *string = fl_status_string_true;
          break;
      #endif // _di_fl_status_booleans_

      #ifndef _di_fl_status_signals_
        // F_signal_hangup is not used because it has the same code as F_true.
        case F_signal_interrupt:
          *string = fl_status_string_signal_interrupt;
          break;
        case F_signal_quit:
          *string = fl_status_string_signal_quit;
          break;
        case F_signal_illegal:
          *string = fl_status_string_signal_illegal;
          break;
        case F_signal_trap:
          *string = fl_status_string_signal_trap;
          break;
        case F_signal_abort:
          *string = fl_status_string_signal_abort;
          break;
        case F_signal_bus_error:
          *string = fl_status_string_signal_bus_error;
          break;
        case F_signal_floating_point_exception:
          *string = fl_status_string_signal_floating_point_exception;
          break;
        case F_signal_kill:
          *string = fl_status_string_signal_kill;
          break;
        case F_signal_user_1:
          *string = fl_status_string_signal_user_1;
          break;
        case F_signal_segmentation_fault:
          *string = fl_status_string_signal_segmentation_fault;
          break;
        case F_signal_user_2:
          *string = fl_status_string_signal_user_2;
          break;
        case F_signal_broken_pipe:
          *string = fl_status_string_signal_broken_pipe;
          break;
        case F_signal_alarm_clock:
          *string = fl_status_string_signal_alarm_clock;
          break;
        case F_signal_termination:
          *string = fl_status_string_signal_termination;
          break;
        case F_signal_stack_fault:
          *string = fl_status_string_signal_stack_fault;
          break;
        case F_signal_child:
          *string = fl_status_string_signal_child;
          break;
        case F_signal_continue:
          *string = fl_status_string_signal_continue;
          break;
        case F_signal_stop:
          *string = fl_status_string_signal_stop;
          break;
        case F_signal_keyboard_stop:
          *string = fl_status_string_signal_keyboard_stop;
          break;
        case F_signal_tty_in:
          *string = fl_status_string_signal_tty_in;
          break;
        case F_signal_tty_out:
          *string = fl_status_string_signal_tty_out;
          break;
        case F_signal_urgent:
          *string = fl_status_string_signal_urgent;
          break;
        case F_signal_cpu_limit:
          *string = fl_status_string_signal_cpu_limit;
          break;
        case F_signal_file_size_limit:
          *string = fl_status_string_signal_file_size_limit;
          break;
        case F_signal_virtual_alarm_clock:
          *string = fl_status_string_signal_virtual_alarm_clock;
          break;
        case F_signal_profile_alarm_clock:
          *string = fl_status_string_signal_profile_alarm_clock;
          break;
        case F_signal_window_size_change:
          *string = fl_status_string_signal_window_size_change;
          break;
        case F_signal_pollable_event:
          *string = fl_status_string_signal_pollable_event;
          break;
        case F_signal_power_failure:
          *string = fl_status_string_signal_power_failure;
          break;
        case F_signal_bad_system_call:
          *string = fl_status_string_signal_bad_system_call;
          break;
        case F_signal_reserved_32:
          *string = fl_status_string_signal_reserved_32;
          break;
        case F_signal_reserved_33:
          *string = fl_status_string_signal_reserved_33;
          break;
        case F_signal_reserved_34:
          *string = fl_status_string_signal_reserved_34;
          break;
        case F_signal_reserved_35:
          *string = fl_status_string_signal_reserved_35;
          break;
        case F_signal_reserved_36:
          *string = fl_status_string_signal_reserved_36;
          break;
        case F_signal_reserved_37:
          *string = fl_status_string_signal_reserved_37;
          break;
        case F_signal_reserved_38:
          *string = fl_status_string_signal_reserved_38;
          break;
        case F_signal_reserved_39:
          *string = fl_status_string_signal_reserved_39;
          break;
        case F_signal_reserved_40:
          *string = fl_status_string_signal_reserved_40;
          break;
        case F_signal_reserved_41:
          *string = fl_status_string_signal_reserved_41;
          break;
        case F_signal_reserved_42:
          *string = fl_status_string_signal_reserved_42;
          break;
        case F_signal_reserved_43:
          *string = fl_status_string_signal_reserved_43;
          break;
        case F_signal_reserved_44:
          *string = fl_status_string_signal_reserved_44;
          break;
        case F_signal_reserved_45:
          *string = fl_status_string_signal_reserved_45;
          break;
        case F_signal_reserved_46:
          *string = fl_status_string_signal_reserved_46;
          break;
        case F_signal_reserved_47:
          *string = fl_status_string_signal_reserved_47;
          break;
        case F_signal_reserved_48:
          *string = fl_status_string_signal_reserved_48;
          break;
        case F_signal_reserved_49:
          *string = fl_status_string_signal_reserved_49;
          break;
        case F_signal_reserved_50:
          *string = fl_status_string_signal_reserved_50;
          break;
        case F_signal_reserved_51:
          *string = fl_status_string_signal_reserved_51;
          break;
        case F_signal_reserved_52:
          *string = fl_status_string_signal_reserved_52;
          break;
        case F_signal_reserved_53:
          *string = fl_status_string_signal_reserved_53;
          break;
        case F_signal_reserved_54:
          *string = fl_status_string_signal_reserved_54;
          break;
        case F_signal_reserved_55:
          *string = fl_status_string_signal_reserved_55;
          break;
        case F_signal_reserved_56:
          *string = fl_status_string_signal_reserved_56;
          break;
        case F_signal_reserved_57:
          *string = fl_status_string_signal_reserved_57;
          break;
        case F_signal_reserved_58:
          *string = fl_status_string_signal_reserved_58;
          break;
        case F_signal_reserved_59:
          *string = fl_status_string_signal_reserved_59;
          break;
        case F_signal_reserved_60:
          *string = fl_status_string_signal_reserved_60;
          break;
        case F_signal_reserved_61:
          *string = fl_status_string_signal_reserved_61;
          break;
        case F_signal_reserved_62:
          *string = fl_status_string_signal_reserved_62;
          break;
        case F_signal_reserved_63:
          *string = fl_status_string_signal_reserved_63;
          break;
        case F_signal_reserved_64:
          *string = fl_status_string_signal_reserved_64;
          break;
      #endif // _di_fl_status_signals_

      #ifndef _di_fl_status_basic_
        case F_none:
          *string = fl_status_string_none;
          break;
        case F_maybe:
          *string = fl_status_string_maybe;
          break;
        case F_dummy:
          *string = fl_status_string_dummy;
          break;
        case F_warn:
          *string = fl_status_string_warn;
          break;
        case F_block:
          *string = fl_status_string_block;
          break;
        case F_critical:
          *string = fl_status_string_critical;
          break;
        case F_unknown:
          *string = fl_status_string_unknown;
          break;
        case F_unsupported:
          *string = fl_status_string_unsupported;
          break;
        case F_data_not:
          *string = fl_status_string_no_data;
          break;
        case F_space_not:
          *string = fl_status_string_no_space;
          break;
        case F_bound_out:
          *string = fl_status_string_bound_out;
          break;
        case F_memory_out:
          *string = fl_status_string_memory_out;
          break;
        case F_prohibited:
          *string = fl_status_string_prohibited;
          break;
        case F_read_only:
          *string = fl_status_string_read_only;
          break;
        case F_input:
          *string = fl_status_string_input;
          break;
        case F_output:
          *string = fl_status_string_output;
          break;
        case F_input_output:
          *string = fl_status_string_input_output;
          break;
        case F_exist_not:
          *string = fl_status_string_exist_not;
          break;
        case F_connected_not:
          *string = fl_status_string_connected_not;
          break;
        case F_failure:
          *string = fl_status_string_failure;
          break;
        case F_interrupted:
          *string = fl_status_string_interrupted;
          break;
        case F_loop:
          *string = fl_status_string_loop;
          break;
        case F_incomplete:
          *string = fl_status_string_incomplete;
          break;
        case F_write_only:
          *string = fl_status_string_write_only;
          break;
      #endif // _di_fl_status_basic_

      #ifndef _di_fl_status_invalid_
        case F_invalid:
          *string = fl_status_string_invalid;
          break;
        case F_name:
          *string = fl_status_string_name;
          break;
        case F_parameter:
          *string = fl_status_string_parameter;
          break;
        case F_syntax:
          *string = fl_status_string_syntax;
          break;
        case F_data:
          *string = fl_status_string_data;
          break;
        case F_descriptor:
          *string = fl_status_string_descriptor;
          break;
        case F_socket:
          *string = fl_status_string_socket;
          break;
        case F_device:
          *string = fl_status_string_device;
          break;
        case F_link:
          *string = fl_status_string_link;
          break;
        case F_pipe:
          *string = fl_status_string_pipe;
          break;
        case F_address:
          *string = fl_status_string_address;
          break;
        case F_port:
          *string = fl_status_string_port;
          break;
        case F_value:
          *string = fl_status_string_value;
          break;
        case F_buffer:
          *string = fl_status_string_buffer;
          break;
        case F_process:
          *string = fl_status_string_process;
          break;
        case F_utf:
          *string = fl_status_string_utf;
          break;
        case F_eof:
          *string = fl_status_string_eof;
          break;
        case F_eol:
          *string = fl_status_string_eol;
          break;
        case F_eos:
          *string = fl_status_string_eos;
          break;
        case F_stop:
          *string = fl_status_string_stop;
          break;
      #endif // _di_fl_status_invalid_

      #ifndef _di_fl_status_busy_
        case F_busy:
          *string = fl_status_string_busy;
          break;
        case F_busy_address:
          *string = fl_status_string_busy_address;
          break;
        case F_busy_port:
          *string = fl_status_string_busy_port;
          break;
        case F_busy_socket:
          *string = fl_status_string_busy_socket;
          break;
        case F_busy_device:
          *string = fl_status_string_busy_device;
          break;
        case F_busy_pipe:
          *string = fl_status_string_busy_pipe;
          break;
        case F_busy_buffer:
          *string = fl_status_string_busy_buffer;
          break;
        case F_busy_process:
          *string = fl_status_string_busy_process;
          break;
      #endif // _di_fl_status_busy_

      #ifndef _di_fl_status_unavailable_
        case F_unavailable:
          *string = fl_status_string_unavailable;
          break;
        case F_unavailable_address:
          *string = fl_status_string_unavailable_address;
          break;
        case F_unavailable_port:
          *string = fl_status_string_unavailable_port;
          break;
        case F_unavailable_socket:
          *string = fl_status_string_unavailable_socket;
          break;
        case F_unavailable_device:
          *string = fl_status_string_unavailable_device;
          break;
        case F_unavailable_pipe:
          *string = fl_status_string_unavailable_pipe;
          break;
        case F_unavailable_buffer:
          *string = fl_status_string_unavailable_buffer;
          break;
        case F_unavailable_process:
          *string = fl_status_string_unavailable_process;
          break;
      #endif // _di_fl_status_unavailable_

      #ifndef _di_fl_status_digits_
        case F_number_underflow:
          *string = fl_status_string_underflow;
          break;
        case F_number_overflow:
          *string = fl_status_string_overflow;
          break;
        case F_number_divide_by_zero:
          *string = fl_status_string_divide_by_zero;
          break;
        case F_number_negative:
          *string = fl_status_string_negative_number;
          break;
        case F_number_positive:
          *string = fl_status_string_positive_number;
          break;
        case F_number_zero:
          *string = fl_status_string_zero_number;
          break;
        case F_number_decimal:
          *string = fl_status_string_decimal_number;
          break;
        case F_number_whole:
          *string = fl_status_string_whole_number;
          break;
        case F_number_invalid:
          *string = fl_status_string_number;
          break;
      #endif // _di_fl_status_digits_

      #ifndef _di_fl_status_buffers_
        case F_data_no_eof:
          *string = fl_status_string_data_no_eof;
          break;
        case F_data_no_eol:
          *string = fl_status_string_data_no_eol;
          break;
        case F_data_no_eos:
          *string = fl_status_string_data_no_eos;
          break;
        case F_data_no_stop:
          *string = fl_status_string_data_no_stop;
          break;
        case F_data_block_no:
          *string = fl_status_string_data_no_block;
          break;
        case F_none_eof:
          *string = fl_status_string_none_eof;
          break;
        case F_none_eol:
          *string = fl_status_string_none_eol;
          break;
        case F_none_eos:
          *string = fl_status_string_none_eos;
          break;
        case F_none_stop:
          *string = fl_status_string_none_stop;
          break;
        case F_none_block:
          *string = fl_status_string_none_block;
          break;
        case F_buffer_too_small:
          *string = fl_status_string_buffer_too_small;
          break;
        case F_buffer_too_large:
          *string = fl_status_string_buffer_too_large;
          break;
        case F_string_too_small:
          *string = fl_status_string_string_too_small;
          break;
        case F_string_too_large:
          *string = fl_status_string_string_too_large;
          break;
        case F_unterminated:
          *string = fl_status_string_unterminated;
          break;
        case F_unterminated_eof:
          *string = fl_status_string_unterminated_eof;
          break;
        case F_unterminated_eol:
          *string = fl_status_string_unterminated_eol;
          break;
        case F_unterminated_eos:
          *string = fl_status_string_unterminated_eos;
          break;
        case F_unterminated_stop:
          *string = fl_status_string_unterminated_stop;
          break;
        case F_unterminated_block:
          *string = fl_status_string_unterminated_block;
          break;
        case F_unterminated_group:
          *string = fl_status_string_unterminated_group;
          break;
        case F_unterminated_group_eof:
          *string = fl_status_string_unterminated_group_on_eof;
          break;
        case F_unterminated_group_eol:
          *string = fl_status_string_unterminated_group_on_eol;
          break;
        case F_unterminated_group_eos:
          *string = fl_status_string_unterminated_group_on_eos;
          break;
        case F_unterminated_group_stop:
          *string = fl_status_string_unterminated_group_on_stop;
          break;
        case F_unterminated_group_block:
          *string = fl_status_string_unterminated_group_on_block;
          break;
        case F_unterminated_nest:
          *string = fl_status_string_unterminated_nest;
          break;
        case F_unterminated_nest_eof:
          *string = fl_status_string_unterminated_nest_eof;
          break;
        case F_unterminated_nest_eol:
          *string = fl_status_string_unterminated_nest_eol;
          break;
        case F_unterminated_nest_eos:
          *string = fl_status_string_unterminated_nest_eos;
          break;
        case F_unterminated_nest_stop:
          *string = fl_status_string_unterminated_nest_stop;
          break;
        case F_unterminated_nest_block:
          *string = fl_status_string_unterminated_nest_block;
          break;
        case F_incomplete_utf:
          *string = fl_status_string_incomplete_utf;
          break;
        case F_incomplete_utf_eof:
          *string = fl_status_string_incomplete_utf_on_eof;
          break;
        case F_incomplete_utf_eol:
          *string = fl_status_string_incomplete_utf_on_eol;
          break;
        case F_incomplete_utf_eos:
          *string = fl_status_string_incomplete_utf_on_eos;
          break;
        case F_incomplete_utf_stop:
          *string = fl_status_string_incomplete_utf_on_stop;
          break;
        case F_incomplete_utf_block:
          *string = fl_status_string_incomplete_utf_on_block;
          break;
      #endif // _di_fl_status_buffers_

      #ifndef _di_fl_status_allocation_
        case F_memory_allocation:
          *string = fl_status_string_memory_allocation;
          break;
        case F_memory_reallocation:
          *string = fl_status_string_memory_reallocation;
          break;
        case F_memory_deallocation:
          *string = fl_status_string_memory_deallocation;
          break;
      #endif // _di_fl_status_allocation_

      #ifndef _di_fl_status_fork_
        case F_fork:
          *string = fl_status_string_fork;
          break;
        case F_process_too_many:
          *string = fl_status_string_process_too_many;
          break;
      #endif // _di_fl_status_fork_

      #ifndef _di_fl_status_file_
        case F_file_closed:
          *string = fl_status_string_file_closed;
          break;
        case F_file_seek:
          *string = fl_status_string_file_seek;
          break;
        case F_file_read:
          *string = fl_status_string_file_read;
          break;
        case F_file_write:
          *string = fl_status_string_file_write;
          break;
        case F_file_flush:
          *string = fl_status_string_file_flush;
          break;
        case F_file_purge:
          *string = fl_status_string_file_purge;
          break;
        case F_file_open:
          *string = fl_status_string_file_open;
          break;
        case F_file_close:
          *string = fl_status_string_file_close;
          break;
        case F_file_synchronize:
          *string = fl_status_string_file_synchronize;
          break;
        case F_file_descriptor:
          *string = fl_status_string_file_descriptor;
          break;
        case F_file_found_not:
          *string = fl_status_string_file_found_not;
          break;
        case F_file_empty:
          *string = fl_status_string_file_empty;
          break;
        case F_file_found:
          *string = fl_status_string_file_found;
          break;
        case F_file_type_block:
          *string = fl_status_string_file_type_block;
          break;
        case F_file_type_character:
          *string = fl_status_string_file_type_character;
          break;
        case F_file_type_directory:
          *string = fl_status_string_file_type_directory;
          break;
        case F_file_type_file:
          *string = fl_status_string_file_type_file;
          break;
        case F_file_type_link:
          *string = fl_status_string_file_type_link;
          break;
        case F_file_type_pipe:
          *string = fl_status_string_file_type_pipe;
          break;
        case F_file_type_socket:
          *string = fl_status_string_file_type_socket;
          break;
        case F_file_type_unknown:
          *string = fl_status_string_file_type_unknown;
          break;
        case F_file_open_not:
          *string = fl_status_string_file_open_not;
          break;
        case F_file_type_not_block:
          *string = fl_status_string_file_type_not_block;
          break;
        case F_file_type_not_character:
          *string = fl_status_string_file_type_not_character;
          break;
        case F_file_type_not_directory:
          *string = fl_status_string_file_not_type_directory;
          break;
        case F_file_type_not_file:
          *string = fl_status_string_file_not_type_file;
          break;
        case F_file_type_not_link:
          *string = fl_status_string_file_not_type_link;
          break;
        case F_file_type_not_pipe:
          *string = fl_status_string_file_not_type_pipe;
          break;
        case F_file_type_not_socket:
          *string = fl_status_string_file_not_type_socket;
          break;
        case F_file_type_not_unknown:
          *string = fl_status_string_file_not_type_unknown;
          break;
        case F_file_allocation:
          *string = fl_status_string_file_allocation;
          break;
        case F_file_reallocation:
          *string = fl_status_string_file_reallocation;
          break;
        case F_file_deallocation:
          *string = fl_status_string_file_deallocation;
          break;
        case F_file_stat:
          *string = fl_status_string_file_stat;
          break;
        case F_file_error:
          *string = fl_status_string_file;
          break;
        case F_file_not_utf:
          *string = fl_status_string_file_not_utf;
          break;
        case F_file_descriptors_max:
          *string = fl_status_string_file_descriptors_max;
          break;
        case F_file_open_max:
          *string = fl_status_string_file_open_max;
          break;
        case F_file_utf:
          *string = fl_status_string_file_utf;
          break;
      #endif // _di_fl_status_file_

      #ifndef _di_f_status_filesystem_
        case F_filesystem:
          *string = fl_status_string_filesystem_error;
          break;
        case F_filesystem_quota_blocks:
          *string = fl_status_string_filesystem_quota_blocks;
          break;
        case F_filesystem_quota_reached:
          *string = fl_status_string_filesystem_quota_reached;
          break;
      #endif // _di_f_status_filesystem_

      #ifndef _di_fl_status_directory_
        case F_directory_read:
          *string = fl_status_string_directory_read;
          break;
        case F_directory_write:
          *string = fl_status_string_directory_write;
          break;
        case F_directory_flush:
          *string = fl_status_string_directory_flush;
          break;
        case F_directory_link_max:
          *string = fl_status_string_directory_link_max;
          break;
        case F_directory_purge:
          *string = fl_status_string_directory_purge;
          break;
        case F_directory_open:
          *string = fl_status_string_directory_open;
          break;
        case F_directory_close:
          *string = fl_status_string_directory_close;
          break;
        case F_directory_synchronize:
          *string = fl_status_string_directory_synchronize;
          break;
        case F_directory_descriptor:
          *string = fl_status_string_directory_descriptor;
          break;
        case F_directory_closed:
          *string = fl_status_string_directory_closed;
          break;
        case F_directory_empty:
          *string = fl_status_string_directory_empty;
          break;
        case F_directory_found:
          *string = fl_status_string_directory_found;
          break;
        case F_directory_not_found:
          *string = fl_status_string_directory_not_found;
          break;
        case F_directory_not_open:
          *string = fl_status_string_directory_not_open;
          break;
        case F_directory:
          *string = fl_status_string_directory;
          break;
        case F_directory_utf_not:
          *string = fl_status_string_directory_not_utf;
          break;
        case F_directory_unsupported:
          *string = fl_status_string_directory_unsupported;
          break;
        case F_directory_stream:
          *string = fl_status_string_directory_stream;
          break;
        case F_directory_utf:
          *string = fl_status_string_directory_utf;
          break;
      #endif // _di_fl_status_directory_

      #ifndef _di_fl_status_socket_
        case F_socket_connection_client:
          *string = fl_status_string_socket_connection_client;
          break;
        case F_socket_connection_target:
          *string = fl_status_string_socket_connection_target;
          break;
        case F_socket_receive:
          *string = fl_status_string_socket_receive;
          break;
        case F_socket_send:
          *string = fl_status_string_socket_send;
          break;
      #endif // _di_fl_status_socket_

      #ifndef _di_fll_error_non_
        case F_than_less:
          *string = fl_status_string_than_less;
          break;
        case F_equal_to:
          *string = fl_status_string_equal_to;
          break;
        case F_equal_to_not:
          *string = fl_status_string_equal_to_not;
          break;
        case F_than_greater:
          *string = fl_status_string_than_greater;
          break;
      #endif // _di_fl_status_non_

      #ifndef _di_fl_status_access_denied_
        case F_access_denied:
          *string = fl_status_string_access_denied;
          break;
        case F_access_denied_user:
          *string = fl_status_string_access_denied_user;
          break;
        case F_access_denied_group:
          *string = fl_status_string_access_denied_group;
          break;
        case F_access_denied_world:
          *string = fl_status_string_access_denied_world;
          break;
        case F_access_denied_read:
          *string = fl_status_string_access_denied_read;
          break;
        case F_access_denied_write:
          *string = fl_status_string_access_denied_write;
          break;
        case F_access_denied_execute:
          *string = fl_status_string_access_denied_execute;
          break;
        case F_access_denied_super:
          *string = fl_status_string_access_denied_super;
          break;
      #endif // _di_fl_status_access_denied_

      case F_status_code_last:
        *string = fl_status_string_status_code_last;
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

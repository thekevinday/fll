#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_status_to_string_
  f_return_status fl_status_to_string(const f_status_t code, f_string_t *string) {
    #ifndef _di_level_1_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t unmasked_code = F_status_set_fine(code);

    switch (unmasked_code) {
      #ifndef _di_F_status_boolean_
        case F_false:
          *string = FL_status_string_false; break;
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
        case F_address:
          *string = FL_status_string_address;
          break;
        case F_block:
          *string = FL_status_string_block;
          break;
        case F_bound_out:
          *string = FL_status_string_bound_out;
          break;
        case F_connected:
          *string = FL_status_string_connected;
          break;
        case F_connected_not:
          *string = FL_status_string_connected_not;
          break;
        case F_critical:
          *string = FL_status_string_critical;
          break;
        case F_descriptor:
          *string = FL_status_string_descriptor;
          break;
        case F_device:
          *string = FL_status_string_device;
          break;
        case F_dummy:
          *string = FL_status_string_dummy;
          break;
        case F_eof:
          *string = FL_status_string_eof;
          break;
        case F_eol:
          *string = FL_status_string_eol;
          break;
        case F_eos:
          *string = FL_status_string_eos;
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
        case F_fork:
          *string = FL_status_string_fork;
          break;
        case F_found:
          *string = FL_status_string_found;
          break;
        case F_incomplete:
          *string = FL_status_string_incomplete;
          break;
        case F_input:
          *string = FL_status_string_input;
          break;
        case F_input_output:
          *string = FL_status_string_input_output;
          break;
        case F_interrupted:
          *string = FL_status_string_interrupted;
          break;
        case F_invalid:
          *string = FL_status_string_invalid;
          break;
        case F_output:
          *string = FL_status_string_output;
          break;
        case F_link:
          *string = FL_status_string_link;
          break;
        case F_loop:
          *string = FL_status_string_loop;
          break;
        case F_maybe:
          *string = FL_status_string_maybe;
          break;
        case F_memory_out:
          *string = FL_status_string_memory_out;
          break;
        case F_mount:
          *string = FL_status_string_mount;
          break;
        case F_name:
          *string = FL_status_string_name;
          break;
        case F_parameter:
          *string = FL_status_string_parameter;
          break;
        case F_pipe:
          *string = FL_status_string_pipe;
          break;
        case F_port:
          *string = FL_status_string_port;
          break;
        case F_process:
          *string = FL_status_string_process;
          break;
        case F_process_too_many:
          *string = FL_status_string_process_too_many;
          break;
        case F_prohibited:
          *string = FL_status_string_prohibited;
          break;
        case F_read_only:
          *string = FL_status_string_read_only;
          break;
        case F_recurse:
          *string = FL_status_string_recurse;
          break;
        case F_relative:
          *string = FL_status_string_relative;
          break;
        case F_search:
          *string = FL_status_string_search;
          break;
        case F_signal:
          *string = FL_status_string_signal;
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
        case F_syntax:
          *string = FL_status_string_syntax;
          break;
        case F_unknown:
          *string = FL_status_string_unknown;
          break;
        case F_unsupported:
          *string = FL_status_string_unsupported;
          break;
        case F_utf:
          *string = FL_status_string_utf;
          break;
        case F_value:
          *string = FL_status_string_value;
          break;
        case F_value_not:
          *string = FL_status_string_value_not;
          break;
        case F_warn:
          *string = FL_status_string_warn;
          break;
        case F_write_only:
          *string = FL_status_string_write_only;
          break;
      #endif // _di_F_status_basic_

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

      #ifndef _di_F_status_unavailable_
        case F_unavailable:
          *string = FL_status_string_unavailable;
          break;
        case F_unavailable_address:
          *string = FL_status_string_unavailable_address;
          break;
        case F_unavailable_buffer:
          *string = FL_status_string_unavailable_buffer;
          break;
        case F_unavailable_device:
          *string = FL_status_string_unavailable_device;
          break;
        case F_unavailable_pipe:
          *string = FL_status_string_unavailable_pipe;
          break;
        case F_unavailable_port:
          *string = FL_status_string_unavailable_port;
          break;
        case F_unavailable_process:
          *string = FL_status_string_unavailable_process;
          break;
        case F_unavailable_socket:
          *string = FL_status_string_unavailable_socket;
          break;
      #endif // _di_F_status_unavailable_

      #ifndef _di_F_status_number_
        case F_number:
          *string = FL_status_string_number;
          break;
        case F_number_decimal:
          *string = FL_status_string_number_decimal;
          break;
        case F_number_divide_by_zero:
          *string = FL_status_string_number_divide_by_zero;
          break;
        case F_number_negative:
          *string = FL_status_string_number_negative;
          break;
        case F_number_overflow:
          *string = FL_status_string_number_overflow;
          break;
        case F_number_positive:
          *string = FL_status_string_number_positive;
          break;
        case F_number_underflow:
          *string = FL_status_string_number_underflow;
          break;
        case F_number_whole:
          *string = FL_status_string_number_whole;
          break;
        case F_number_zero:
          *string = FL_status_string_number_zero;
          break;
      #endif // _di_F_status_number_

      #ifndef _di_F_status_buffers_
        case F_buffer:
          *string = FL_status_string_buffer;
          break;
        case F_buffer_too_small:
          *string = FL_status_string_buffer_too_small;
          break;
        case F_buffer_too_large:
          *string = FL_status_string_buffer_too_large;
          break;
        case F_incomplete_utf:
          *string = FL_status_string_incomplete_utf;
          break;
        case F_incomplete_utf_block:
          *string = FL_status_string_incomplete_utf_block;
          break;
        case F_incomplete_utf_eof:
          *string = FL_status_string_incomplete_utf_eof;
          break;
        case F_incomplete_utf_eol:
          *string = FL_status_string_incomplete_utf_eol;
          break;
        case F_incomplete_utf_eos:
          *string = FL_status_string_incomplete_utf_eos;
          break;
        case F_incomplete_utf_stop:
          *string = FL_status_string_incomplete_utf_stop;
          break;
        case F_none_block:
          *string = FL_status_string_none_block;
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
        case F_string_too_small:
          *string = FL_status_string_string_too_small;
          break;
        case F_string_too_large:
          *string = FL_status_string_string_too_large;
          break;
        case F_unterminated:
          *string = FL_status_string_unterminated;
          break;
        case F_unterminated_block:
          *string = FL_status_string_unterminated_block;
          break;
        case F_unterminated_eof:
          *string = FL_status_string_unterminated_eof;
          break;
        case F_unterminated_eol:
          *string = FL_status_string_unterminated_eol;
          break;
        case F_unterminated_eos:
          *string = FL_status_string_unterminated_eos;
          break;
        case F_unterminated_stop:
          *string = FL_status_string_unterminated_stop;
          break;
        case F_unterminated_group:
          *string = FL_status_string_unterminated_group;
          break;
        case F_unterminated_group_block:
          *string = FL_status_string_unterminated_group_block;
          break;
        case F_unterminated_group_eof:
          *string = FL_status_string_unterminated_group_eof;
          break;
        case F_unterminated_group_eol:
          *string = FL_status_string_unterminated_group_eol;
          break;
        case F_unterminated_group_eos:
          *string = FL_status_string_unterminated_group_eos;
          break;
        case F_unterminated_group_stop:
          *string = FL_status_string_unterminated_group_stop;
          break;
        case F_unterminated_nest:
          *string = FL_status_string_unterminated_nest;
          break;
        case F_unterminated_nest_block:
          *string = FL_status_string_unterminated_nest_block;
          break;
        case F_unterminated_nest_eof:
          *string = FL_status_string_unterminated_nest_eof;
          break;
        case F_unterminated_nest_eol:
          *string = FL_status_string_unterminated_nest_eol;
          break;
        case F_unterminated_nest_eos:
          *string = FL_status_string_unterminated_nest_eos;
          break;
        case F_unterminated_nest_stop:
          *string = FL_status_string_unterminated_nest_stop;
          break;
      #endif // _di_F_status_buffers_

      #ifndef _di_F_status_allocation_
        case F_memory_allocation:
          *string = FL_status_string_memory_allocation;
          break;
        case F_memory_deallocation:
          *string = FL_status_string_memory_deallocation;
          break;
        case F_memory_reallocation:
          *string = FL_status_string_memory_reallocation;
          break;
      #endif // _di_F_status_allocation_

      #ifndef _di_F_status_file_
        case F_file:
          *string = FL_status_string_file;
          break;
        case F_file_allocation:
          *string = FL_status_string_file_allocation;
          break;
        case F_file_close:
          *string = FL_status_string_file_close;
          break;
        case F_file_closed:
          *string = FL_status_string_file_closed;
          break;
        case F_file_deallocation:
          *string = FL_status_string_file_deallocation;
          break;
        case F_file_descriptor:
          *string = FL_status_string_file_descriptor;
          break;
        case F_file_descriptor_max:
          *string = FL_status_string_file_descriptor_max;
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
        case F_file_open:
          *string = FL_status_string_file_open;
          break;
        case F_file_open_max:
          *string = FL_status_string_file_open_max;
          break;
        case F_file_opened:
          *string = FL_status_string_file_opened;
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
          *string =FL_status_string_directory_descriptor;
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
        case F_directory_unsupported:
          *string = FL_status_string_directory_unsupported;
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
        case F_access_owner:
          *string = FL_status_string_access_owner;
          break;
      #endif // _di_F_status_access_

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

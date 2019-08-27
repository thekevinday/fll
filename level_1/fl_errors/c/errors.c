#include <level_1/errors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_errors_to_string_
  f_return_status fl_errors_to_string(const f_status error, f_string *string) {
    #ifndef _di_level_1_parameter_checking_
      if (string == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status umasked_error = f_error_set_fine(error);

    switch (umasked_error) {
      #ifndef _di_fl_errors_booleans_
        case f_false:
          *string = "f_false";
          break;
        case f_true:
          *string = "f_true";
          break;
      #endif // _di_fl_errors_booleans_

      #ifndef _di_fl_errors_signals_
        // f_signal_hangup is not used because it has the same code as f_true.
        case f_signal_interrupt:
          *string = "f_signal_interrupt";
          break;
        case f_signal_quit:
          *string = "f_signal_quit";
          break;
        case f_signal_illegal:
          *string = "f_signal_illegal";
          break;
        case f_signal_trap:
          *string = "f_signal_trap";
          break;
        case f_signal_abort:
          *string = "f_signal_abort";
          break;
        case f_signal_bus_error:
          *string = "f_signal_bus_error";
          break;
        case f_signal_floating_point_exception:
          *string = "f_signal_floating_point_exception";
          break;
        case f_signal_kill:
          *string = "f_signal_kill";
          break;
        case f_signal_user_1:
          *string = "f_signal_user_1";
          break;
        case f_signal_segmentation_fault:
          *string = "f_signal_segmentation_fault";
          break;
        case f_signal_user_2:
          *string = "f_signal_user_2";
          break;
        case f_signal_broken_pipe:
          *string = "f_signal_broken_pipe";
          break;
        case f_signal_alarm_clock:
          *string = "f_signal_alarm_clock";
          break;
        case f_signal_termination:
          *string = "f_signal_termination";
          break;
        case f_signal_stack_fault:
          *string = "f_signal_stack_fault";
          break;
        case f_signal_child:
          *string = "f_signal_child";
          break;
        case f_signal_continue:
          *string = "f_signal_continue";
          break;
        case f_signal_stop:
          *string = "f_signal_stop";
          break;
        case f_signal_keyboard_stop:
          *string = "f_signal_keyboard_stop";
          break;
        case f_signal_tty_in:
          *string = "f_signal_tty_in";
          break;
        case f_signal_tty_out:
          *string = "f_signal_tty_out";
          break;
        case f_signal_urgent:
          *string = "f_signal_urgent";
          break;
        case f_signal_cpu_limit:
          *string = "f_signal_cpu_limit";
          break;
        case f_signal_file_size_limit:
          *string = "f_signal_file_size_limit";
          break;
        case f_signal_virtual_alarm_clock:
          *string = "f_signal_virtual_alarm_clock";
          break;
        case f_signal_profile_alarm_clock:
          *string = "f_signal_profile_alarm_clock";
          break;
        case f_signal_window_size_change:
          *string = "f_signal_window_size_change";
          break;
        case f_signal_pollable_event:
          *string = "f_signal_pollable_event";
          break;
        case f_signal_power_failure:
          *string = "f_signal_power_failure";
          break;
        case f_signal_bad_system_call:
          *string = "f_signal_bad_system_call";
          break;
        case f_signal_reserved_32:
          *string = "f_signal_reserved_32";
          break;
        case f_signal_reserved_33:
          *string = "f_signal_reserved_33";
          break;
        case f_signal_reserved_34:
          *string = "f_signal_reserved_34";
          break;
        case f_signal_reserved_35:
          *string = "f_signal_reserved_35";
          break;
        case f_signal_reserved_36:
          *string = "f_signal_reserved_36";
          break;
        case f_signal_reserved_37:
          *string = "f_signal_reserved_37";
          break;
        case f_signal_reserved_38:
          *string = "f_signal_reserved_38";
          break;
        case f_signal_reserved_39:
          *string = "f_signal_reserved_39";
          break;
        case f_signal_reserved_40:
          *string = "f_signal_reserved_40";
          break;
        case f_signal_reserved_41:
          *string = "f_signal_reserved_41";
          break;
        case f_signal_reserved_42:
          *string = "f_signal_reserved_42";
          break;
        case f_signal_reserved_43:
          *string = "f_signal_reserved_43";
          break;
        case f_signal_reserved_44:
          *string = "f_signal_reserved_44";
          break;
        case f_signal_reserved_45:
          *string = "f_signal_reserved_45";
          break;
        case f_signal_reserved_46:
          *string = "f_signal_reserved_46";
          break;
        case f_signal_reserved_47:
          *string = "f_signal_reserved_47";
          break;
        case f_signal_reserved_48:
          *string = "f_signal_reserved_48";
          break;
        case f_signal_reserved_49:
          *string = "f_signal_reserved_49";
          break;
        case f_signal_reserved_50:
          *string = "f_signal_reserved_50";
          break;
        case f_signal_reserved_51:
          *string = "f_signal_reserved_51";
          break;
        case f_signal_reserved_52:
          *string = "f_signal_reserved_52";
          break;
        case f_signal_reserved_53:
          *string = "f_signal_reserved_53";
          break;
        case f_signal_reserved_54:
          *string = "f_signal_reserved_54";
          break;
        case f_signal_reserved_55:
          *string = "f_signal_reserved_55";
          break;
        case f_signal_reserved_56:
          *string = "f_signal_reserved_56";
          break;
        case f_signal_reserved_57:
          *string = "f_signal_reserved_57";
          break;
        case f_signal_reserved_58:
          *string = "f_signal_reserved_58";
          break;
        case f_signal_reserved_59:
          *string = "f_signal_reserved_59";
          break;
        case f_signal_reserved_60:
          *string = "f_signal_reserved_60";
          break;
        case f_signal_reserved_61:
          *string = "f_signal_reserved_61";
          break;
        case f_signal_reserved_62:
          *string = "f_signal_reserved_62";
          break;
        case f_signal_reserved_63:
          *string = "f_signal_reserved_63";
          break;
        case f_signal_reserved_64:
          *string = "f_signal_reserved_64";
          break;
      #endif // _di_fl_errors_signals_

      #ifndef _di_fl_errors_basic_
        case f_none:
          *string = "f_none";
          break;
        case f_maybe:
          *string = "f_maybe";
          break;
        case f_dummy:
          *string = "f_dummy";
          break;
        case f_warn:
          *string = "f_warn";
          break;
        case f_critical:
          *string = "f_critical";
          break;
        case f_unknown:
          *string = "f_unknown";
          break;
        case f_unsupported:
          *string = "f_unsupported";
          break;
        case f_no_data:
          *string = "f_no_data";
          break;
        case f_out_of_memory:
          *string = "f_out_of_memory";
          break;
        case f_input_error:
          *string = "f_input_error";
          break;
        case f_output_error:
          *string = "f_output_error";
          break;
        case f_input_output_error:
          *string = "f_input_output_error";
          break;
        case f_does_not_exist:
          *string = "f_does_not_exist";
          break;
        case f_not_connected:
          *string = "f_not_connected";
          break;
        case f_failure:
          *string = "f_failure";
          break;
        case f_interrupted:
          *string = "f_interrupted";
          break;
        case f_loop:
          *string = "f_loop";
          break;
      #endif // _di_fl_errors_basic_

      #ifdef _di_fl_errors_invalid_
        case f_invalid:
          *string = "f_invalid";
          break;
        case f_invalid_parameter:
          *string = "f_invalid_parameter";
          break;
        case f_invalid_syntax:
          *string = "f_invalid_syntax";
          break;
        case f_invalid_data:
          *string = "f_invalid_data";
          break;
        case f_invalid_file:
          *string = "f_invalid_file";
          break;
        case f_invalid_directory:
          *string = "f_invalid_directory";
          break;
        case f_invalid_socket:
          *string = "f_invalid_socket";
          break;
        case f_invalid_device:
          *string = "f_invalid_device";
          break;
        case f_invalid_link:
          *string = "f_invalid_link";
          break;
        case f_invalid_pipe:
          *string = "f_invalid_pipe";
          break;
        case f_invalid_address:
          *string = "f_invalid_address";
          break;
        case f_invalid_port:
          *string = "f_invalid_port";
          break;
        case f_invalid_value:
          *string = "f_invalid_value";
          break;
        case f_invalid_buffer:
          *string = "f_invalid_buffer";
          break;
        case f_invalid_process:
          *string = "f_invalid_process";
          break;
        case f_invalid_utf:
          *string = "f_invalid_utf";
          break;
      #endif // _di_fl_errors_invalid_

      #ifndef _di_fl_errors_busy_
        case f_busy:
          *string = "f_busy";
          break;
        case f_busy_address:
          *string = "f_busy_address";
          break;
        case f_busy_port:
          *string = "f_busy_port";
          break;
        case f_busy_socket:
          *string = "f_busy_socket";
          break;
        case f_busy_device:
          *string = "f_busy_device";
          break;
        case f_busy_pipe:
          *string = "f_busy_pipe";
          break;
        case f_busy_buffer:
          *string = "f_busy_buffer";
          break;
        case f_busy_process:
          *string = "f_busy_process";
          break;
      #endif // _di_fl_errors_busy_

      #ifndef _di_fl_errors_unavailable_
        case f_unavailable:
          *string = "f_unavailable";
          break;
        case f_unavailable_address:
          *string = "f_unavailable_address";
          break;
        case f_unavailable_port:
          *string = "f_unavailable_port";
          break;
        case f_unavailable_socket:
          *string = "f_unavailable_socket";
          break;
        case f_unavailable_device:
          *string = "f_unavailable_device";
          break;
        case f_unavailable_pipe:
          *string = "f_unavailable_pipe";
          break;
        case f_unavailable_buffer:
          *string = "f_unavailable_buffer";
          break;
        case f_unavailable_process:
          *string = "f_unavailable_process";
          break;
      #endif // _di_fl_errors_unavailable_

      #ifndef _di_fl_errors_digits_
        case f_underflow:
          *string = "f_underflow";
          break;
        case f_overflow:
          *string = "f_overflow";
          break;
        case f_divide_by_zero:
          *string = "f_divide_by_zero";
          break;
        case f_cannot_be_negative:
          *string = "f_cannot_be_negative";
          break;
        case f_cannot_be_positive:
          *string = "f_cannot_be_positive";
          break;
        case f_cannot_be_zero:
          *string = "f_cannot_be_zero";
          break;
      #endif // _di_fl_errors_digits_

      #ifndef _di_fl_errors_buffers_
        case f_no_data_on_eof:
          *string = "f_no_data_on_eof";
          break;
        case f_no_data_on_eol:
          *string = "f_no_data_on_eol";
          break;
        case f_no_data_on_eos:
          *string = "f_no_data_on_eos";
          break;
        case f_no_data_on_stop:
          *string = "f_no_data_on_stop";
          break;
        case f_none_on_eof:
          *string = "f_none_on_eof";
          break;
        case f_none_on_eol:
          *string = "f_none_on_eol";
          break;
        case f_none_on_eos:
          *string = "f_none_on_eos";
          break;
        case f_none_on_stop:
          *string = "f_none_on_stop";
          break;
        case f_error_on_eof:
          *string = "f_error_on_eof";
          break;
        case f_error_on_eol:
          *string = "f_error_on_eol";
          break;
        case f_error_on_eos:
          *string = "f_error_on_eos";
          break;
        case f_error_on_stop:
          *string = "f_error_on_stop";
          break;
        case f_buffer_too_small:
          *string = "f_buffer_too_small";
          break;
        case f_buffer_too_large:
          *string = "f_buffer_too_large";
          break;
        case f_string_too_small:
          *string = "f_string_too_small";
          break;
        case f_string_too_large:
          *string = "f_string_too_large";
          break;
        case f_unterminated_nest:
          *string = "f_unterminated_nest";
          break;
        case f_unterminated_nest_on_eof:
          *string = "f_unterminated_nest_on_eof";
          break;
        case f_unterminated_nest_on_eol:
          *string = "f_unterminated_nest_on_eol";
          break;
        case f_unterminated_nest_on_eos:
          *string = "f_unterminated_nest_on_eos";
          break;
        case f_unterminated_nest_on_stop:
          *string = "f_unterminated_nest_on_stop";
          break;
        case f_unterminated_group:
          *string = "f_unterminated_group";
          break;
        case f_unterminated_group_on_eof:
          *string = "f_unterminated_group_on_eof";
          break;
        case f_unterminated_group_on_eol:
          *string = "f_unterminated_group_on_eol";
          break;
        case f_unterminated_group_on_eos:
          *string = "f_unterminated_group_on_eos";
          break;
        case f_unterminated_group_on_stop:
          *string = "f_unterminated_group_on_stop";
          break;
        case f_incomplete_utf_on_eos:
          *string = "f_incomplete_utf_on_eos";
          break;
        case f_incomplete_utf_on_stop:
          *string = "f_incomplete_utf_on_stop";
          break;
      #endif // _di_fl_errors_buffers_

      #ifndef _di_fl_errors_allocation_
        case f_allocation_error:
          *string = "f_allocation_error";
          break;
        case f_reallocation_error:
          *string = "f_reallocation_error";
          break;
      #endif // _di_fl_errors_allocation_

      #ifndef _di_fl_errors_fork_
        case f_fork_failed:
          *string = "f_fork_failed";
          break;
        case f_too_many_processes:
          *string = "f_too_many_processes";
          break;
      #endif // _di_fl_errors_fork_

      #ifndef _di_fl_errors_file_
        case f_file_seek_error:
          *string = "f_file_seek_error";
          break;
        case f_file_read_error:
          *string = "f_file_read_error";
          break;
        case f_file_write_error:
          *string = "f_file_write_error";
          break;
        case f_file_flush_error:
          *string = "f_file_flush_error";
          break;
        case f_file_purge_error:
          *string = "f_file_purge_error";
          break;
        case f_file_open_error:
          *string = "f_file_open_error";
          break;
        case f_file_close_error:
          *string = "f_file_close_error";
          break;
        case f_file_synchronize_error:
          *string = "f_file_synchronize_error";
          break;
        case f_file_descriptor_error:
          *string = "f_file_descriptor_error";
          break;
        case f_file_not_found:
          *string = "f_file_not_found";
          break;
        case f_file_found:
          *string = "f_file_found";
          break;
        case f_file_is_empty:
          *string = "f_file_is_empty";
          break;
        case f_file_not_open:
          *string = "f_file_not_open";
          break;
        case f_file_allocation_error:
          *string = "f_file_allocation_error";
          break;
        case f_file_reallocation_error:
          *string = "f_file_reallocation_error";
          break;
        case f_file_stat_error:
          *string = "f_file_stat_error";
          break;
        case f_file_error:
          *string = "f_file_error";
          break;
        case f_file_not_utf:
          *string = "f_file_not_utf";
          break;
      #endif // _di_fl_errors_file_

      // most of these are a guess until I get around to researching & implementing linux directory I/O
      #ifndef _di_fl_errors_directory_
        case f_directory_read_error:
          *string = "f_directory_read_error";
          break;
        case f_directory_write_error:
          *string = "f_directory_write_error";
          break;
        case f_directory_flush_error:
          *string = "f_directory_flush_error";
          break;
        case f_directory_purge_error:
          *string = "f_directory_purge_error";
          break;
        case f_directory_open_error:
          *string = "f_directory_open_error";
          break;
        case f_directory_close_error:
          *string = "f_directory_close_error";
          break;
        case f_directory_synchronize_error:
          *string = "f_directory_synchronize_error";
          break;
        case f_directory_descriptor_error:
          *string = "f_directory_descriptor_error";
          break;
        case f_directory_not_found:
          *string = "f_directory_not_found";
          break;
        case f_directory_is_empty:
          *string = "f_directory_is_empty";
          break;
        case f_directory_not_open:
          *string = "f_directory_not_open";
          break;
        case f_directory_allocation_error:
          *string = "f_directory_allocation_error";
          break;
        case f_directory_reallocation_error:
          *string = "f_directory_reallocation_error";
          break;
        case f_directory_error:
          *string = "f_directory_error";
          break;
        case f_directory_not_utf:
          *string = "f_directory_not_utf";
          break;
      #endif // _di_fl_errors_directory_

      #ifndef _di_fll_error_non_
        case f_less_than:
          *string = "f_less_than";
          break;
        case f_equal_to:
          *string = "f_equal_to";
          break;
        case f_not_equal_to:
          *string = "f_not_equal_to";
          break;
        case f_greater_than:
          *string = "f_greater_than";
          break;
      #endif // _di_fl_errors_non_

      #ifndef _di_fl_errors_access_denied_
        case f_access_denied:
          *string = "f_access_denied";
          break;
        case f_access_denied_user:
          *string = "f_access_denied_user";
          break;
        case f_access_denied_group:
          *string = "f_access_denied_group";
          break;
        case f_access_denied_world:
          *string = "f_access_denied_world";
          break;
        case f_access_denied_read:
          *string = "f_access_denied_read";
          break;
        case f_access_denied_write:
          *string = "f_access_denied_write";
          break;
        case f_access_denied_execute:
          *string = "f_access_denied_execute";
          break;
        case f_access_denied_super:
          *string = "f_access_denied_super";
          break;
      #endif // _di_fl_errors_access_denied_

      case f_last_error_code:
        *string = "f_last_error_code";
        break;

      default:
        *string = 0;
        return f_invalid_data;
    }

    return f_none;
  }
#endif // _di_fl_errors_to_string_

#ifndef _di_fl_errors_is_error_
  f_return_status fl_errors_is_error(const f_status error) {
    if (fl_errors_is_fine(error) == f_true) {
      return f_false;
    }
    else if (fl_errors_is_warning(error) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_fl_errors_is_error_

#ifndef _di_fl_errors_is_warning_
  f_return_status fl_errors_is_warning(const f_status error) {
    switch (error) {
      #ifndef _di_fl_errors_basic_
        case f_no_data:
          return f_true;
      #endif // _di_fl_errors_basic_

      #ifndef _di_f_errors_buffers_
        case f_no_data_on_eof:
          return f_true;
        case f_no_data_on_eol:
          return f_true;
        case f_no_data_on_eos:
          return f_true;
        case f_no_data_on_stop:
          return f_true;
        case f_none_on_eof:
          return f_true;
        case f_none_on_eol:
          return f_true;
        case f_none_on_eos:
          return f_true;
        case f_none_on_stop:
          return f_true;
      #endif // _di_f_errors_buffers_
    }

    return f_false;
  }
#endif // _di_fl_errors_is_warning_

#ifndef _di_fl_errors_is_fine_
  f_return_status fl_errors_is_fine(const f_status error) {
    switch (error) {
      #ifndef _di_fl_errors_booleans_
        case f_false:
          return f_true;
        case f_true:
          return f_true;
      #endif // _di_fl_errors_booleans_

      #ifndef _di_fl_errors_basic_
        case f_none:
          return f_true;
        case f_dummy:
          return f_true;
      #endif // _di_fl_errors_basic_

      #ifndef _di_fll_error_non_
        case f_less_than:
          return f_true;
        case f_equal_to:
          return f_true;
        case f_not_equal_to:
          return f_true;
        case f_greater_than:
          return f_true;
      #endif // _di_fl_errors_non_
    }

    return f_false;
  }
#endif // _di_fl_errors_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif

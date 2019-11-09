/**
 * FLL - Level 0
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides status code definitions.
 *
 * Warning: changing error codes will break ABI, so recompile every file that includes and uses these error codes when this gets changed.
 */
#ifndef _F_status_h
#define _F_status_h

// libc includes
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Status masks.
 */
#ifndef _di_f_status_masks_
  // f_status is required to be exactly 16 bits, the first two high order bits represent error and warning respectively.
  #define f_status_bit_error   0x8000 // 1000 0000 0000 0000
  #define f_status_bit_signal  0xc000 // 1100 0000 0000 0000
  #define f_status_bit_warning 0x4000 // 0100 0000 0000 0000

  #define f_status_mask_fine 0x3fff // 0011 1111 1111 1111
  #define f_status_mask_code 0xc000 // 1100 0000 0000 0000

  #define f_status_is_error(status)   (status & f_status_bit_error)
  #define f_status_is_fine(status)    ((status & f_status_mask_code) == 0)
  #define f_status_is_problem(status) ((status & f_status_bit_error) || (status & f_status_bit_warning))
  #define f_status_is_signal(status)  (status & f_status_bit_signal)
  #define f_status_is_warning(status) (status & f_status_bit_warning)

  #define f_status_is_not_error(status)   ((status & f_status_bit_error) == 0)
  #define f_status_is_not_signal(status)  ((status & f_status_bit_signal) == 0)
  #define f_status_is_not_warning(status) ((status & f_status_bit_warning) == 0)

  #define f_status_set_error(status)   (status | f_status_bit_error)
  #define f_status_set_signal(status)  (status | f_status_bit_signal)
  #define f_status_set_warning(status) (status | f_status_bit_warning)

  // use f_status_set_fine to remove the error, warning, and signal bits
  #define f_status_set_fine(status) (status & f_status_mask_fine)
#endif // _di_f_status_masks_

/**
 * All standard/core status codes.
 *
 * The code f_last_status_code is intended to be used as the starting point for anything extending this and povided its own status codes.
 */
enum {
  #ifndef _di_f_status_booleans_
    f_false = 0,
    f_true,
  #endif // _di_f_status_booleans_

  #ifndef _di_f_status_signals_
    f_signal_hangup = 1,
    f_signal_interrupt,
    f_signal_quit,
    f_signal_illegal,
    f_signal_trap,
    f_signal_abort,
    f_signal_bus_error,
    f_signal_floating_point_exception,
    f_signal_kill, // unblockable
    f_signal_user_1,
    f_signal_segmentation_fault,
    f_signal_user_2,
    f_signal_broken_pipe,
    f_signal_alarm_clock,
    f_signal_termination,
    f_signal_stack_fault,
    f_signal_child,
    f_signal_continue,
    f_signal_stop, // unblockable
    f_signal_keyboard_stop,
    f_signal_tty_in,
    f_signal_tty_out,
    f_signal_urgent,
    f_signal_cpu_limit,
    f_signal_file_size_limit,
    f_signal_virtual_alarm_clock,
    f_signal_profile_alarm_clock,
    f_signal_window_size_change,
    f_signal_pollable_event,
    f_signal_power_failure,
    f_signal_bad_system_call,
    f_signal_reserved_32,
    f_signal_reserved_33,
    f_signal_reserved_34,
    f_signal_reserved_35,
    f_signal_reserved_36,
    f_signal_reserved_37,
    f_signal_reserved_38,
    f_signal_reserved_39,
    f_signal_reserved_40,
    f_signal_reserved_41,
    f_signal_reserved_42,
    f_signal_reserved_43,
    f_signal_reserved_44,
    f_signal_reserved_45,
    f_signal_reserved_46,
    f_signal_reserved_47,
    f_signal_reserved_48,
    f_signal_reserved_49,
    f_signal_reserved_50,
    f_signal_reserved_51,
    f_signal_reserved_52,
    f_signal_reserved_53,
    f_signal_reserved_54,
    f_signal_reserved_55,
    f_signal_reserved_56,
    f_signal_reserved_57,
    f_signal_reserved_58,
    f_signal_reserved_59,
    f_signal_reserved_60,
    f_signal_reserved_61,
    f_signal_reserved_62,
    f_signal_reserved_63,
    f_signal_reserved_64,
  #endif // _di_f_status_signals_

  #ifndef _di_f_status_basic_
    f_none = 197,          // start at 197 to allow compatibility with the reserved bash return codes (keep in mind fss return codes can be larger than 255).
    f_maybe,
    f_dummy,               // to only be used as a placeholder
    f_warn,                // warning
    f_critical,
    f_unknown,             // For the "code should never get here" errors. (this is an EMERGENCY error)
    f_unsupported,
    f_no_data,             // warning
    f_out_of_memory,
    f_input_error,
    f_output_error,
    f_input_output_error,
    f_does_not_exist,
    f_not_connected,
    f_failure,
    f_interrupted,         // usually by a signal.
    f_loop,                // such as infinite recursion.
  #endif // _di_f_status_basic_

  #ifndef _di_f_status_invalid_
    f_invalid,
    f_invalid_name,
    f_invalid_parameter,
    f_invalid_syntax,
    f_invalid_data,
    f_invalid_file,
    f_invalid_directory,
    f_invalid_descriptor,
    f_invalid_socket,
    f_invalid_device,
    f_invalid_link,
    f_invalid_pipe,
    f_invalid_address,
    f_invalid_port,
    f_invalid_value,      // similar to f_invalid_parameter, but the parameter value is invalid (example: an integer value representing aboolean and having a 3 as a value).
    f_invalid_buffer,
    f_invalid_process,
    f_invalid_utf,
    f_invalid_on_eof,
    f_invalid_on_eol,
    f_invalid_on_eos,
    f_invalid_on_stop,
  #endif // _di_f_status_invalid_

  #ifndef _di_f_status_busy_
    f_busy,          // such as address in use, or port in use.
    f_busy_address,
    f_busy_port,
    f_busy_socket,
    f_busy_device,
    f_busy_pipe,
    f_busy_buffer,
    f_busy_process,
  #endif // _di_f_status_busy_

  #ifndef _di_f_status_unavailable_
    f_unavailable,
    f_unavailable_address,
    f_unavailable_port,
    f_unavailable_socket,
    f_unavailable_device,
    f_unavailable_pipe,
    f_unavailable_buffer,
    f_unavailable_process,
  #endif // _di_f_status_unavailable_

  #ifndef _di_f_status_digits_
    f_underflow,
    f_overflow,
    f_divide_by_zero,
    f_negative_number,
    f_positive_number,
    f_zero_number,
    f_decimal_number,
    f_invalid_number,
  #endif // _di_f_status_digits_

  #ifndef _di_f_status_buffers_
    f_no_data_on_eof,             // warning
    f_no_data_on_eol,             // warning
    f_no_data_on_eos,             // warning
    f_no_data_on_stop,            // warning
    f_none_on_eof,                // warning
    f_none_on_eol,                // warning
    f_none_on_eos,                // warning
    f_none_on_stop,               // "stop" location was reached
    f_error_on_eof,
    f_error_on_eol,
    f_error_on_eos,
    f_error_on_stop,
    f_buffer_too_small,
    f_buffer_too_large,
    f_string_too_small,
    f_string_too_large,
    f_unterminated_nest,
    f_unterminated_nest_on_eof,
    f_unterminated_nest_on_eol,
    f_unterminated_nest_on_eos,
    f_unterminated_nest_on_stop,
    f_unterminated_group,
    f_unterminated_group_on_eof,
    f_unterminated_group_on_eol,
    f_unterminated_group_on_eos,
    f_unterminated_group_on_stop,
    f_incomplete_utf,
    f_incomplete_utf_on_eof,
    f_incomplete_utf_on_eol,
    f_incomplete_utf_on_eos,
    f_incomplete_utf_on_stop,
  #endif // _di_f_status_buffers_

  #ifndef _di_f_status_allocation_
    f_allocation_error,
    f_reallocation_error,
  #endif // _di_f_status_allocation_

  #ifndef _di_f_status_fork_
    f_fork_failed,
    f_too_many_processes,
  #endif // _di_f_status_fork_

  #ifndef _di_f_status_file_
    f_file_seek_error,
    f_file_read_error,
    f_file_write_error,
    f_file_flush_error,
    f_file_purge_error,
    f_file_open_error,
    f_file_close_error,
    f_file_synchronize_error,
    f_file_descriptor_error,
    f_file_not_found,
    f_file_found,
    f_file_is_empty,
    f_file_not_open,
    f_file_allocation_error,
    f_file_reallocation_error,
    f_file_stat_error,
    f_file_error,
    f_file_not_utf,
  #endif // _di_f_status_file_

  // most of these are a guess until I get around to researching & implementing linux directory I/O
  #ifndef _di_f_status_directory_
    f_directory_read_error,
    f_directory_write_error,
    f_directory_flush_error,
    f_directory_purge_error,
    f_directory_open_error,
    f_directory_close_error,
    f_directory_synchronize_error,
    f_directory_descriptor_error,
    f_directory_not_found,
    f_directory_is_empty,
    f_directory_not_open,
    f_directory_allocation_error,
    f_directory_reallocation_error,
    f_directory_error,
    f_directory_not_utf,
  #endif // _di_f_status_directory_

  #ifndef _di_f_status_socket_
    f_socket_connection_client_error,
    f_socket_connection_target_error,
    f_socket_receive_error,
    f_socket_send_error,
  #endif // _di_f_status_socket_

  #ifndef _di_f_status_non_
    f_less_than,
    f_equal_to,
    f_not_equal_to,
    f_greater_than,
  #endif // _di_f_status_non_

  #ifndef _di_f_status_access_denied_
    f_access_denied,
    f_access_denied_user,
    f_access_denied_group,
    f_access_denied_world,
    f_access_denied_read,
    f_access_denied_write,
    f_access_denied_execute,
    f_access_denied_super,    // not super user (aka: not root).
  #endif // _di_f_status_access_denied_

  // required
  f_last_status_code
}; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_h

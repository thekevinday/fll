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

  // Use f_status_set_fine to remove the error, warning, and signal bits.
  #define f_status_set_fine(status) (status & f_status_mask_fine)

  // Maximum size of the status code.
  #define f_status_size_max             0x3fff
  #define f_status_size_max_with_signal 0x10000
#endif // _di_f_status_masks_

/**
 * All standard/core status codes.
 *
 * The code f_status_code_last is intended to be used as the starting point for anything extending this and povided its own status codes.
 */
#ifndef _di_f_status_codes_
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
      f_none = 197, // Start at 197 to allow compatibility with the reserved bash return codes (keep in mind fss return codes can be larger than 255).
      f_critical,
      f_does_not_exist,
      f_dummy,
      f_error_input,
      f_error_output,
      f_error_input_output,
      f_failure,
      f_incomplete,
      f_interrupted,
      f_loop,
      f_maybe,
      f_not_connected,
      f_no_data,
      f_out_of_memory,
      f_prohibited,
      f_read_only,
      f_unknown,
      f_unsupported,
      f_warn,
      f_write_only,
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
      f_invalid_value,
      f_invalid_buffer,
      f_invalid_process,
      f_invalid_utf,
      f_invalid_on_eof,
      f_invalid_on_eol,
      f_invalid_on_eos,
      f_invalid_on_stop,
    #endif // _di_f_status_invalid_

    #ifndef _di_f_status_busy_
      f_busy,
      f_busy_address,
      f_busy_buffer,
      f_busy_device,
      f_busy_pipe,
      f_busy_port,
      f_busy_process,
      f_busy_socket,
    #endif // _di_f_status_busy_

    #ifndef _di_f_status_unavailable_
      f_unavailable,
      f_unavailable_address,
      f_unavailable_buffer,
      f_unavailable_device,
      f_unavailable_pipe,
      f_unavailable_port,
      f_unavailable_process,
      f_unavailable_socket,
    #endif // _di_f_status_unavailable_

    #ifndef _di_f_status_digits_
      f_number_decimal,
      f_number_divide_by_zero,
      f_number_invalid,
      f_number_negative,
      f_number_overflow,
      f_number_positive,
      f_number_underflow,
      f_number_whole,
      f_number_zero,
    #endif // _di_f_status_digits_

    #ifndef _di_f_status_buffers_
      f_buffer_too_small,
      f_buffer_too_large,
      f_error_on_eof,
      f_error_on_eol,
      f_error_on_eos,
      f_error_on_stop,
      f_incomplete_utf,
      f_incomplete_utf_on_eof,
      f_incomplete_utf_on_eol,
      f_incomplete_utf_on_eos,
      f_incomplete_utf_on_stop,
      f_none_on_eof,
      f_none_on_eol,
      f_none_on_eos,
      f_none_on_stop,
      f_no_data_on_eof,
      f_no_data_on_eol,
      f_no_data_on_eos,
      f_no_data_on_stop,
      f_string_too_small,
      f_string_too_large,
      f_unterminated,
      f_unterminated_on_eof,
      f_unterminated_on_eol,
      f_unterminated_on_eos,
      f_unterminated_on_stop,
      f_unterminated_group,
      f_unterminated_group_on_eof,
      f_unterminated_group_on_eol,
      f_unterminated_group_on_eos,
      f_unterminated_group_on_stop,
      f_unterminated_nest,
      f_unterminated_nest_on_eof,
      f_unterminated_nest_on_eol,
      f_unterminated_nest_on_eos,
      f_unterminated_nest_on_stop,
    #endif // _di_f_status_buffers_

    #ifndef _di_f_status_allocation_
      f_error_allocation,
      f_error_deallocation,
      f_error_reallocation,
    #endif // _di_f_status_allocation_

    #ifndef _di_f_status_fork_
      f_fork_failed,
      f_too_many_processes,
    #endif // _di_f_status_fork_

    #ifndef _di_f_status_file_
      f_file_error,
      f_file_error_allocation,
      f_file_error_close,
      f_file_error_deallocation,
      f_file_error_descriptor,
      f_file_error_flush,
      f_file_error_open,
      f_file_error_purge,
      f_file_error_read,
      f_file_error_reallocation,
      f_file_error_seek,
      f_file_error_stat,
      f_file_error_synchronize,
      f_file_error_write,
      f_file_found,
      f_file_is_empty,
      f_file_is_type_block,
      f_file_is_type_character,
      f_file_is_type_directory,
      f_file_is_type_file,
      f_file_is_type_link,
      f_file_is_type_pipe,
      f_file_is_type_socket,
      f_file_is_type_unknown,
      f_file_not_found,
      f_file_not_open,
      f_file_not_type_block,
      f_file_not_type_character,
      f_file_not_type_directory,
      f_file_not_type_file,
      f_file_not_type_link,
      f_file_not_type_pipe,
      f_file_not_type_socket,
      f_file_not_type_unknown,
      f_file_not_utf,
      f_file_max_descriptors,
      f_file_max_open,
    #endif // _di_f_status_file_

    #ifndef _di_f_status_filesystem_
      f_filesystem_error,
      f_filesystem_quota_blocks,
      f_filesystem_quota_reached,
    #endif // _di_f_status_filesystem_

    // Most of these are a guess until I get around to researching & implementing linux directory I/O.
    #ifndef _di_f_status_directory_
      f_directory_error,
      f_directory_error_allocation,
      f_directory_error_close,
      f_directory_error_descriptor,
      f_directory_error_flush,
      f_directory_error_link_max,
      f_directory_error_open,
      f_directory_error_purge,
      f_directory_error_read,
      f_directory_error_reallocation,
      f_directory_error_stream,
      f_directory_error_synchronize,
      f_directory_error_unsupported,
      f_directory_error_write,
      f_directory_is_empty,
      f_directory_not_found,
      f_directory_not_open,
      f_directory_not_utf,
    #endif // _di_f_status_directory_

    #ifndef _di_f_status_socket_
      f_socket_error_connection_client,
      f_socket_error_connection_target,
      f_socket_error_receive,
      f_socket_error_send,
    #endif // _di_f_status_socket_

    #ifndef _di_f_status_non_
      f_less_than,
      f_equal_to,
      f_not_equal_to,
      f_greater_than,
    #endif // _di_f_status_non_

    #ifndef _di_f_status_access_denied_
      f_access_denied,
      f_access_denied_execute,
      f_access_denied_group,
      f_access_denied_read,
      f_access_denied_super, // "super" as in super user (root user).
      f_access_denied_user,
      f_access_denied_world,
      f_access_denied_write,
    #endif // _di_f_status_access_denied_

    // Required.
    f_status_code_last
  }; // enum
#endif // _di_f_status_codes_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_h

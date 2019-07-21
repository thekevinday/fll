/* FLL - Level 0
 * Project:       Errors
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides error definitions.
 *
 * Warning: changing error codes will break abi, so recompile every file that includes and uses these error codes when this gets changed.
 */
#ifndef _F_errors_h
#define _F_errors_h

// libc includes
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_macro_test_for_basic_errors_
  #define f_macro_test_for_basic_errors(potential_error) \
    ( potential_error == f_critical          || \
      potential_error == f_unknown           || \
      potential_error == f_unsupported       || \
      potential_error == f_invalid_parameter || \
      potential_error == f_invalid_syntax    || \
      potential_error == f_invalid_data      || \
      potential_error == f_output_error      || \
      potential_error == f_does_not_exist    || \
      potential_error == f_failure)
#endif // _di_f_macro_test_for_basic_errors_

#ifndef _di_f_macro_test_for_allocation_errors_
  // FIXME: invalid_parameter was temporarily added here so that parameter checking could be corrected for all allocations and deallocations
  #define f_macro_test_for_allocation_errors(potential_error) \
    ( potential_error == f_allocation_error           || \
      potential_error == f_reallocation_error         || \
      potential_error == f_file_allocation_error      || \
      potential_error == f_file_reallocation_error    || \
      potential_error == f_directory_allocation_error || \
      potential_error == f_invalid_parameter || \
      potential_error == f_directory_reallocation_error )
#endif // _di_f_macro_test_for_allocation_errors_

#ifndef _di_f_macro_test_for_non_errors_
  #define f_macro_test_for_non_errors(potential_error) \
    ( potential_error == f_true                     || \
      potential_error == f_false                    || \
      potential_error == f_warn                     || \
      potential_error == f_no_data                  || \
      potential_error == f_no_data_on_eos           || \
      potential_error == f_no_data_on_eof           || \
      potential_error == f_no_data_on_stop          || \
      potential_error == f_none_on_eof              || \
      potential_error == f_none_on_eos              || \
      potential_error == f_none_on_stop             || \
      potential_error == f_less_than                || \
      potential_error == f_equal_to                 || \
      potential_error == f_not_equal_to             || \
      potential_error == f_greater_than             || \
      potential_error == f_none )
#endif // _di_f_macro_test_for_non_errors_

#ifndef _di_macro_f_test_for_file_errors_
  #define f_macro_test_for_file_errors(potential_error) \
    ( potential_error == f_file_seek_error        || \
      potential_error == f_file_read_error        || \
      potential_error == f_file_write_error       || \
      potential_error == f_file_flush_error       || \
      potential_error == f_file_purge_error       || \
      potential_error == f_file_open_error        || \
      potential_error == f_file_close_error       || \
      potential_error == f_file_synchronize_error || \
      potential_error == f_file_descriptor_error  || \
      potential_error == f_file_not_found         || \
      potential_error == f_file_is_empty          || \
      potential_error == f_file_not_open )
#endif // _di_f_macro_test_for_file_errors_

#ifndef _di_f_macro_test_for_directory_errors_
  #define f_macro_test_for_directory_errors(parameter) \
    ( potential_error == f_directory_seek_error        || \
      potential_error == f_directory_read_error        || \
      potential_error == f_directory_write_error       || \
      potential_error == f_directory_flush_error       || \
      potential_error == f_directory_purge_error       || \
      potential_error == f_directory_open_error        || \
      potential_error == f_directory_close_error       || \
      potential_error == f_directory_synchronize_error || \
      potential_error == f_directory_descriptor_error  || \
      potential_error == f_directory_not_found         || \
      potential_error == f_directory_is_empty          || \
      potential_error == f_directory_not_open )
#endif // _di_f_macro_test_for_directory_errors_

#ifndef _di_f_macro_test_for_none_errors_
  #define f_macro_test_for_none_errors(potential_error) \
    ( potential_error == f_none        || \
      potential_error == f_none_on_eof || \
      potential_error == f_none_on_eol || \
      potential_error == f_none_on_eos || \
      potential_error == f_none_on_stop)
#endif // _di_f_macro_test_for_none_errors_

#ifndef _di_f_macro_test_for_no_data_errors_
  #define f_macro_test_for_no_data_errors(potential_error) \
    ( potential_error == f_no_data        || \
      potential_error == f_no_data_on_eof || \
      potential_error == f_no_data_on_eol || \
      potential_error == f_no_data_on_eos || \
      potential_error == f_no_data_on_stop)
#endif // _di_f_macro_test_for_no_data_errors_

#ifndef _di_f_macro_test_for_on_errors_
  #define f_macro_test_for_on_errors(potential_error) \
    ( potential_error == f_error_on_eof || \
      potential_error == f_error_on_eol || \
      potential_error == f_error_on_eos || \
      potential_error == f_error_on_stop)
#endif // _di_f_macro_test_for_on_errors_

#ifndef _di_f_macro_test_for_unterminated_nest_errors_
  #define f_macro_test_for_unterminated_nest_errors(potential_error) \
    ( potential_error == f_unterminated_nest        || \
      potential_error == f_unterminated_nest_on_eof || \
      potential_error == f_unterminated_nest_on_eol || \
      potential_error == f_unterminated_nest_on_eos || \
      potential_error == f_unterminated_nest_on_stop)
#endif // _di_f_macro_test_for_unterminated_nest_errors_

#ifndef _di_f_macro_test_for_unterminated_group_errors_
  #define f_macro_test_for_unterminated_group_errors(potential_error) \
    ( potential_error == f_unterminated_group        || \
      potential_error == f_unterminated_group_on_eof || \
      potential_error == f_unterminated_group_on_eol || \
      potential_error == f_unterminated_group_on_eos || \
      potential_error == f_unterminated_group_on_stop)
#endif // _di_f_macro_test_for_unterminated_group_errors_

#ifndef _di_f_error_masks_
  // f_status is required to be exactly 16 bits, the first two high order bits represent error and warning respectively.
  #define f_error_bit_error    32768
  #define f_error_bit_warning  16384
  #define f_error_bit_mask     49152
  #define f_error_bit_fine     16383
  #define f_error_bit_signal   49152

  #define f_error_is_error(status)       status & f_error_bit_error
  #define f_error_is_warning(status)     status & f_error_bit_warning
  #define f_error_is_problem(status)     status & f_error_bit_mask
  #define f_error_is_fine(status)        (status & f_error_bit_mask) == 0
  #define f_error_is_not_error(status)   (status & f_error_bit_error) == 0
  #define f_error_is_not_warning(status) (status & f_error_bit_warning) == 0
  #define f_error_is_not_signal(status)  (status & f_error_bit_signal) == 0

  // use both error and warning bits to designate that the response is a signal.
  #define f_error_is_signal(status) (status & f_error_bit_signal) == f_error_bit_signal

  #define f_error_set_error(status)   status | f_error_bit_error
  #define f_error_set_warning(status) status | f_error_bit_warning
  #define f_error_set_signal(status)  status | f_error_bit_signal

  // use f_error_set_fine to remove the error, warning, and signal bits
  #define f_error_set_fine(status) status & f_error_bit_fine
#endif // _di_f_error_masks_

// use of an enumerator makes more sense here than explicitly defining every error code
enum {
  #ifndef _di_f_errors_booleans_
    f_false = 0,
    f_true,
  #endif // _di_f_errors_booleans_

  #ifndef _di_f_errors_signals_
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

    // these will be renamed if new names are given for the remaining system calls (up to 64).
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
  #endif // _di_f_errors_signals_

  #ifndef _di_f_errors_basic_
    f_none = 197,          // start at 197 to allow compatibility with the reserved bash return codes (keep in mind fss return codes can be larger than 255).
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
  #endif // _di_f_errors_basic_

  #ifndef _di_f_errors_invalid_
    f_invalid,
    f_invalid_parameter,
    f_invalid_syntax,
    f_invalid_data,
    f_invalid_file,
    f_invalid_directory,
    f_invalid_socket,
    f_invalid_device,
    f_invalid_link,
    f_invalid_pipe,
    f_invalid_address,
    f_invalid_port,
    f_invalid_value,      // similar to f_invalid_parameter, but the parameter value is invalid (example: an integer value representing aboolean and having a 3 as a value).
    f_invalid_buffer,
    f_invalid_process,
  #endif // _di_f_errors_invalid_

  #ifndef _di_f_errors_busy_
    f_busy,          // such as address in use, or port in use.
    f_busy_address,
    f_busy_port,
    f_busy_socket,
    f_busy_device,
    f_busy_pipe,
    f_busy_buffer,
    f_busy_process,
  #endif // _di_f_errors_busy_

  #ifndef _di_f_errors_unavailable_
    f_unavailable,
    f_unavailable_address,
    f_unavailable_port,
    f_unavailable_socket,
    f_unavailable_device,
    f_unavailable_pipe,
    f_unavailable_buffer,
    f_unavailable_process,
  #endif // _di_f_errors_unavailable_

  #ifndef _di_f_errors_digits_
    f_underflow,
    f_overflow,
    f_divide_by_zero,
    f_cannot_be_negative,
    f_cannot_be_positive,
    f_cannot_be_zero,
  #endif // _di_f_errors_digits_

  #ifndef _di_f_errors_buffers_
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
  #endif // _di_f_errors_buffers_

  #ifndef _di_f_errors_allocation_
    f_allocation_error,
    f_reallocation_error,
  #endif // _di_f_errors_allocation_

  #ifndef _di_f_errors_fork_
    f_fork_failed,
    f_too_many_processes,
  #endif // _di_f_errors_fork_

  #ifndef _di_f_errors_file_
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
  #endif // _di_f_errors_file_

  // most of these are a guess until I get around to researching & implementing linux directory I/O
  #ifndef _di_f_errors_directory_
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
  #endif // _di_f_errors_directory_

  #ifndef _di_f_errors_socket_
    f_socket_connection_client_error,
    f_socket_connection_target_error,
    f_socket_receive_error,
    f_socket_send_error,
  #endif // _di_f_errors_socket_

  #ifndef _di_f_errors_non_
    f_less_than,
    f_equal_to,
    f_not_equal_to,
    f_greater_than,
  #endif // _di_f_errors_non_

  #ifndef _di_f_errors_access_denied_
    f_access_denied,
    f_access_denied_user,
    f_access_denied_group,
    f_access_denied_world,
    f_access_denied_read,
    f_access_denied_write,
    f_access_denied_execute,
    f_access_denied_super,    // not super user (aka: not root).
  #endif // _di_f_errors_access_denied_

  // required
  f_last_error_code
}; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_errors_h

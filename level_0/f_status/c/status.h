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
#ifndef _di_F_status_masks_
  // f_status_t is required to be exactly 16 bits, the first two high order bits represent error and warning respectively.
  #define F_status_bit_error   0x8000 // 1000 0000 0000 0000
  #define F_status_bit_signal  0xc000 // 1100 0000 0000 0000
  #define F_status_bit_warning 0x4000 // 0100 0000 0000 0000

  #define F_status_mask_fine 0x3fff // 0011 1111 1111 1111
  #define F_status_mask_code 0xc000 // 1100 0000 0000 0000

  #define F_status_is_error(status)   (status & F_status_bit_error)
  #define F_status_is_fine(status)    ((status & F_status_mask_code) == 0)
  #define F_status_is_problem(status) ((status & F_status_bit_error) || (status & F_status_bit_warning))
  #define F_status_is_signal(status)  (status & F_status_bit_signal)
  #define F_status_is_warning(status) (status & F_status_bit_warning)

  #define F_status_is_error_not(status)   ((status & F_status_bit_error) == 0)
  #define F_status_is_fine_not(status)    (status & F_status_mask_code)
  #define F_status_is_signal_not(status)  ((status & F_status_bit_signal) == 0)
  #define F_status_is_warning_not(status) ((status & F_status_bit_warning) == 0)

  #define F_status_set_error(status)   (status | F_status_bit_error)
  #define F_status_set_signal(status)  (status | F_status_bit_signal)
  #define F_status_set_warning(status) (status | F_status_bit_warning)

  // Use F_status_set_fine to remove the error, warning, and signal bits.
  #define F_status_set_fine(status) (status & F_status_mask_fine)

  // Maximum size of the status code.
  #define F_status_size_max             0x3fff
  #define F_status_size_max_with_signal 0x10000
#endif // _di_F_status_masks_

/**
 * All standard/core status codes.
 *
 * The code F_status_code_last is intended to be used as the starting point for anything extending this and povided its own status codes.
 *
 * Most codes are sorted alphabetically, within their respective groups.
 * There are special case codes that are expected to be in specific positions.
 * 1) F_false, must always evaluate to 0.
 * 2) F_true, must always evaluate to 1 and will conflict with F_signal_hangup.
 * 3) All f_signal_*, these numbers must map directly to the standard signal codes.
 * 4) F_none, this is intended to be the default return code and the return code representing the standard start code.
 * 5) F_status_code_last, this is intended to designate the last code provided by level_0 status project.
 *    All code sets started by another project (such as FSS status codes) must start at this number + 1 with a code start map.
 */
#ifndef _di_F_status_codes_
  enum {
    #ifndef _di_F_status_boolean_
      F_false = 0,
      F_true,
    #endif // _di_F_status_boolean_

    #ifndef _di_F_status_signal_
      F_signal_hangup = 1,
      F_signal_interrupt,
      F_signal_quit,
      F_signal_illegal,
      F_signal_trap,
      F_signal_abort,
      F_signal_bus_error,
      F_signal_floating_point_error,
      F_signal_kill, // unblockable
      F_signal_user_1,
      F_signal_segmentation_fault,
      F_signal_user_2,
      F_signal_broken_pipe,
      F_signal_alarm_clock,
      F_signal_termination,
      F_signal_stack_fault,
      F_signal_child,
      F_signal_continue,
      F_signal_stop, // unblockable
      F_signal_keyboard_stop,
      F_signal_tty_in,
      F_signal_tty_out,
      F_signal_urgent,
      F_signal_cpu_limit,
      F_signal_file_size_limit,
      F_signal_virtual_alarm_clock,
      F_signal_profile_alarm_clock,
      F_signal_window_size_change,
      F_signal_pollable_event,
      F_signal_power_failure,
      F_signal_bad_system_call,
      F_signal_reserved_32,
      F_signal_reserved_33,
      F_signal_reserved_34,
      F_signal_reserved_35,
      F_signal_reserved_36,
      F_signal_reserved_37,
      F_signal_reserved_38,
      F_signal_reserved_39,
      F_signal_reserved_40,
      F_signal_reserved_41,
      F_signal_reserved_42,
      F_signal_reserved_43,
      F_signal_reserved_44,
      F_signal_reserved_45,
      F_signal_reserved_46,
      F_signal_reserved_47,
      F_signal_reserved_48,
      F_signal_reserved_49,
      F_signal_reserved_50,
      F_signal_reserved_51,
      F_signal_reserved_52,
      F_signal_reserved_53,
      F_signal_reserved_54,
      F_signal_reserved_55,
      F_signal_reserved_56,
      F_signal_reserved_57,
      F_signal_reserved_58,
      F_signal_reserved_59,
      F_signal_reserved_60,
      F_signal_reserved_61,
      F_signal_reserved_62,
      F_signal_reserved_63,
      F_signal_reserved_64,
    #endif // _di_F_status_signal_

    // Start at 197 to allow compatibility with the reserved bash return codes (keep in mind fss return codes can be larger than 255).
    #ifndef _di_F_status_basic_
      F_none = 197,
      F_absolute,
      F_absolute_not,
      F_address,
      F_address_not,
      F_block,
      F_block_not,
      F_bound,
      F_bound_not,
      F_capability,
      F_capability_not,
      F_child,
      F_child_not,
      F_complete,
      F_complete_not,
      F_connected,
      F_connected_not,
      F_container,
      F_container_not,
      F_control,
      F_control_not,
      F_control_group,
      F_control_group_not,
      F_critical,
      F_critical_not,
      F_dead,
      F_dead_not,
      F_deadlock,
      F_deadlock_not,
      F_descriptor,
      F_descriptor_not,
      F_device,
      F_device_not,
      F_done,
      F_done_not,
      F_dummy,
      F_dummy_not,
      F_empty,
      F_empty_not,
      F_encoding,
      F_encoding_not,
      F_eoa,
      F_eoa_not,
      F_eof,
      F_eof_not,
      F_eol,
      F_eol_not,
      F_eos,
      F_eos_not,
      F_exist,
      F_exist_not,
      F_failure,
      F_failure_not,
      F_fork,
      F_fork_not,
      F_found,
      F_found_not,
      F_full,
      F_full_not,
      F_group,
      F_group_not,
      F_ignore,
      F_ignore_not,
      F_implemented,
      F_implemented_not,
      F_input,
      F_input_not,
      F_input_output,
      F_interrupt,
      F_interrupt_not,
      F_known,
      F_known_not,
      F_limit,
      F_limit_not,
      F_link,
      F_link_not,
      F_live,
      F_live_not,
      F_lock,
      F_lock_not,
      F_loop,
      F_loop_not,
      F_maybe,
      F_maybe_not,
      F_memory,
      F_memory_not,
      F_minor,
      F_minor_not,
      F_moderate,
      F_moderate_not,
      F_mount,
      F_mount_not,
      F_name,
      F_name_not,
      F_nice,
      F_nice_not,
      F_optional,
      F_optional_not,
      F_output,
      F_output_not,
      F_parameter,
      F_parameter_not,
      F_parent,
      F_parent_not,
      F_pipe,
      F_pipe_not,
      F_port,
      F_port_not,
      F_processor,
      F_processor_not,
      F_prohibited,
      F_prohibited_not,
      F_range,
      F_range_not,
      F_read,
      F_read_not,
      F_read_only,
      F_ready,
      F_ready_not,
      F_recover,
      F_recover_not,
      F_recurse,
      F_recurse_not,
      F_relative,
      F_relative_not,
      F_require,
      F_require_not,
      F_resource,
      F_resource_not,
      F_search,
      F_search_not,
      F_schedule,
      F_schedule_not,
      F_signal,
      F_signal_not,
      F_space,
      F_space_not,
      F_stop,
      F_stop_not,
      F_string,
      F_string_not,
      F_string_too_large,
      F_string_too_small,
      F_supported,
      F_supported_not,
      F_syntax,
      F_syntax_not,
      F_thread,
      F_thread_not,
      F_time,
      F_time_not,
      F_user,
      F_user_not,
      F_utf,
      F_utf_not,
      F_valid,
      F_valid_not,
      F_value,
      F_value_not,
      F_wait,
      F_wait_not,
      F_warn,
      F_warn_not,
      F_world,
      F_world_not,
      F_write,
      F_write_not,
      F_write_only,
    #endif // _di_F_status_basic_

    #ifndef _di_F_status_array_
      F_array,
      F_array_not,
      F_array_too_large,
      F_array_too_small,
    #endif // _di_F_status_array_

    #ifndef _di_F_status_available_
      F_available,
      F_available_not,
      F_available_not_address,
      F_available_not_buffer,
      F_available_not_device,
      F_available_not_pipe,
      F_available_not_port,
      F_available_not_process,
      F_available_not_socket,
    #endif // _di_F_status_available_

    #ifndef _di_F_status_busy_
      F_busy,
      F_busy_address,
      F_busy_buffer,
      F_busy_device,
      F_busy_not,
      F_busy_pipe,
      F_busy_port,
      F_busy_process,
      F_busy_socket,
    #endif // _di_F_status_busy_

    #ifndef _di_F_status_number_
      F_number,
      F_number_decimal,
      F_number_decimal_not,
      F_number_divide_by_zero,
      F_number_negative,
      F_number_negative_not,
      F_number_not,
      F_number_overflow,
      F_number_positive,
      F_number_positive_not,
      F_number_too_large,
      F_number_too_small,
      F_number_underflow,
      F_number_whole,
      F_number_whole_not,
      F_number_zero,
      F_number_zero_not,
    #endif // _di_F_status_number_

    #ifndef _di_F_status_buffer_
      F_buffer,
      F_buffer_not,
      F_buffer_too_large,
      F_buffer_too_small,
      F_complete_not_utf,
      F_complete_not_utf_block,
      F_complete_not_utf_eoa,
      F_complete_not_utf_eof,
      F_complete_not_utf_eol,
      F_complete_not_utf_eos,
      F_complete_not_utf_stop,
      F_none_block,
      F_none_eoa,
      F_none_eof,
      F_none_eol,
      F_none_eos,
      F_none_stop,
      F_data,
      F_data_not,
      F_data_not_block,
      F_data_not_eoa,
      F_data_not_eof,
      F_data_not_eol,
      F_data_not_eos,
      F_data_not_stop,
      F_terminated,
      F_terminated_not,
      F_terminated_not_block,
      F_terminated_not_eoa,
      F_terminated_not_eof,
      F_terminated_not_eol,
      F_terminated_not_eos,
      F_terminated_not_group,
      F_terminated_not_group_block,
      F_terminated_not_group_eoa,
      F_terminated_not_group_eof,
      F_terminated_not_group_eol,
      F_terminated_not_group_eos,
      F_terminated_not_group_stop,
      F_terminated_not_nest,
      F_terminated_not_nest_block,
      F_terminated_not_nest_eoa,
      F_terminated_not_nest_eof,
      F_terminated_not_nest_eol,
      F_terminated_not_nest_eos,
      F_terminated_not_nest_stop,
      F_terminated_not_stop,
    #endif // _di_F_status_buffer_

    #ifndef _di_F_status_process_
      F_process,
      F_process_not,
      F_process_too_many,
    #endif // _di_F_status_process_

    #ifndef _di_F_status_file_
      F_file,
      F_file_close,
      F_file_closed,
      F_file_descriptor,
      F_file_descriptor_max,
      F_file_descriptor_not,
      F_file_empty,
      F_file_flush,
      F_file_found,
      F_file_found_not,
      F_file_not,
      F_file_open,
      F_file_opened,
      F_file_open_max,
      F_file_overflow,
      F_file_purge,
      F_file_read,
      F_file_reallocation,
      F_file_seek,
      F_file_stat,
      F_file_synchronize,
      F_file_type_block,
      F_file_type_character,
      F_file_type_directory,
      F_file_type_fifo,
      F_file_type_link,
      F_file_type_not_block,
      F_file_type_not_character,
      F_file_type_not_directory,
      F_file_type_not_fifo,
      F_file_type_not_link,
      F_file_type_not_pipe,
      F_file_type_not_regular,
      F_file_type_not_socket,
      F_file_type_not_unknown,
      F_file_type_pipe,
      F_file_type_regular,
      F_file_type_socket,
      F_file_type_unknown,
      F_file_underflow,
      F_file_utf,
      F_file_utf_not,
      F_file_write,
    #endif // _di_F_status_file_

    #ifndef _di_F_status_filesystem_
      F_filesystem,
      F_filesystem_not,
      F_filesystem_quota_block,
      F_filesystem_quota_reached,
    #endif // _di_F_status_filesystem_

    #ifndef _di_F_status_directory_
      F_directory,
      F_directory_close,
      F_directory_closed,
      F_directory_descriptor,
      F_directory_empty,
      F_directory_empty_not,
      F_directory_found,
      F_directory_found_not,
      F_directory_flush,
      F_directory_link_max,
      F_directory_not,
      F_directory_open,
      F_directory_purge,
      F_directory_read,
      F_directory_stream,
      F_directory_supported_not,
      F_directory_synchronize,
      F_directory_utf,
      F_directory_utf_not,
      F_directory_write,
    #endif // _di_F_status_directory_

    #ifndef _di_F_status_socket_
      F_socket,
      F_socket_client,
      F_socket_not,
      F_socket_receive,
      F_socket_send,
      F_socket_target,
    #endif // _di_F_status_socket_

    #ifndef _di_F_status_compare_
      F_equal_to,
      F_equal_to_not,
      F_than_greater,
      F_than_less,
    #endif // _di_F_status_compare_

    #ifndef _di_F_status_access_
      F_access,
      F_access_denied,
      F_access_denied_execute,
      F_access_denied_group,
      F_access_denied_read,
      F_access_denied_super, // "super" as in super user (root user).
      F_access_denied_user,
      F_access_denied_world,
      F_access_denied_write,
      F_access_granted,
      F_access_granted_execute,
      F_access_granted_group,
      F_access_granted_read,
      F_access_granted_super, // "super" as in super user (root user).
      F_access_granted_user,
      F_access_granted_world,
      F_access_granted_write,
      F_access_group,
      F_access_mode,
      F_access_not,
      F_access_owner,
    #endif // _di_F_status_access_

    // Required.
    F_status_code_last
  }; // enum
#endif // _di_F_status_codes_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_h

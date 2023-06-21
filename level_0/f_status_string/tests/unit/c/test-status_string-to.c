#include "test-status_string.h"
#include "test-status_string-to.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_status_string_to__fails(void **state) {

  {
    f_string_static_t result = f_string_static_t_initialize;

    const f_status_t status = f_status_string_to(F_status_code_last + 1, &result);

    assert_int_equal(status, F_status_set_error(F_data));
    assert_int_equal(result.used, f_string_empty_s.used);
    assert_string_equal(result.string, f_string_empty_s.string);
  }
}

void test__f_status_string_to__parameter_checking(void **state) {

  {
    const f_status_t status = f_status_string_to(F_false, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_status_string_to__works(void **state) {

  const f_status_t statuss[] = {
    F_false,
    F_true,
    F_signal_hangup,
    F_signal_interrupt,
    F_signal_quit,
    F_signal_illegal,
    F_signal_trap,
    F_signal_abort,
    F_signal_bus_error,
    F_signal_floating_point_error,
    F_signal_kill,
    F_signal_user_1,
    F_signal_segmentation_fault,
    F_signal_user_2,
    F_signal_broken_pipe,
    F_signal_alarm_clock,
    F_signal_termination,
    F_signal_stack_fault,
    F_signal_child,
    F_signal_continue,
    F_signal_stop,
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
    F_none,
    F_abort,
    F_abort_not,
    F_absolute,
    F_absolute_not,
    F_address,
    F_address_not,
    F_again,
    F_again_not,
    F_ascii,
    F_ascii_not,
    F_atomic,
    F_atomic_not,
    F_base,
    F_base_not,
    F_begin,
    F_begin_not,
    F_block,
    F_block_not,
    F_body,
    F_body_not,
    F_bottom,
    F_bottom_not,
    F_bound,
    F_bound_not,
    F_break,
    F_break_not,
    F_call,
    F_call_not,
    F_capability,
    F_capability_not,
    F_character,
    F_character_not,
    F_child,
    F_child_not,
    F_complete,
    F_complete_not,
    F_connect,
    F_connect_not,
    F_connect_refuse,
    F_connect_reset,
    F_container,
    F_container_not,
    F_content,
    F_content_not,
    F_continue,
    F_continue_not,
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
    F_desire,
    F_desire_not,
    F_device,
    F_device_not,
    F_disable,
    F_disable_not,
    F_discard,
    F_discard_not,
    F_domain,
    F_domain_not,
    F_done,
    F_done_not,
    F_drop,
    F_drop_not,
    F_dummy,
    F_dummy_not,
    F_empty,
    F_empty_not,
    F_enable,
    F_enable_not,
    F_encoding,
    F_encoding_not,
    F_endian,
    F_endian_big,
    F_endian_little,
    F_endian_not,
    F_eoa,
    F_eoa_not,
    F_eof,
    F_eof_not,
    F_eol,
    F_eol_not,
    F_eos,
    F_eos_not,
    F_execute,
    F_execute_not,
    F_exist,
    F_exist_not,
    F_exit,
    F_exit_not,
    F_failure,
    F_failure_not,
    F_family,
    F_family_not,
    F_fifo,
    F_fifo_not,
    F_first,
    F_first_not,
    F_footer,
    F_footer_not,
    F_fork,
    F_fork_not,
    F_format,
    F_format_not,
    F_found,
    F_found_not,
    F_full,
    F_full_not,
    F_group,
    F_group_not,
    F_halt,
    F_halt_not,
    F_header,
    F_header_not,
    F_help,
    F_help_not,
    F_ignore,
    F_ignore_not,
    F_implement,
    F_implement_not,
    F_input,
    F_input_not,
    F_input_output,
    F_interrupt,
    F_interrupt_not,
    F_keep,
    F_keep_not,
    F_known,
    F_known_not,
    F_last,
    F_last_not,
    F_limit,
    F_limit_not,
    F_link,
    F_link_not,
    F_live,
    F_live_not,
    F_local,
    F_local_not,
    F_lock,
    F_lock_not,
    F_loop,
    F_loop_not,
    F_maybe,
    F_maybe_not,
    F_memory,
    F_memory_not,
    F_message,
    F_message_not,
    F_middle,
    F_middle_not,
    F_minor,
    F_minor_not,
    F_moderate,
    F_moderate_not,
    F_mount,
    F_mount_not,
    F_name,
    F_name_not,
    F_need,
    F_need_not,
    F_next,
    F_next_not,
    F_nice,
    F_nice_not,
    F_no,
    F_no_not,
    F_object,
    F_object_not,
    F_okay,
    F_okay_not,
    F_once,
    F_once_not,
    F_option,
    F_option_not,
    F_output,
    F_output_not,
    F_packet,
    F_packet_not,
    F_parameter,
    F_parameter_not,
    F_parent,
    F_parent_not,
    F_payload,
    F_payload_not,
    F_pipe,
    F_pipe_not,
    F_port,
    F_port_not,
    F_previous,
    F_previous_not,
    F_processor,
    F_processor_not,
    F_progress,
    F_progress_not,
    F_prohibited,
    F_prohibited_not,
    F_property,
    F_property_not,
    F_protocol,
    F_protocol_not,
    F_range,
    F_range_not,
    F_read,
    F_read_not,
    F_read_only,
    F_ready,
    F_ready_not,
    F_receive,
    F_receive_not,
    F_recover,
    F_recover_not,
    F_recurse,
    F_recurse_not,
    F_regular,
    F_regular_not,
    F_relative,
    F_relative_not,
    F_remote,
    F_remote_not,
    F_repeat,
    F_repeat_not,
    F_require,
    F_require_not,
    F_resource,
    F_resource_not,
    F_restart,
    F_restart_not,
    F_restore,
    F_restore_not,
    F_revert,
    F_revert_not,
    F_schedule,
    F_schedule_not,
    F_search,
    F_search_not,
    F_send,
    F_send_not,
    F_signal,
    F_signal_not,
    F_size,
    F_size_not,
    F_skip,
    F_skip_not,
    F_space,
    F_space_not,
    F_start,
    F_start_not,
    F_status,
    F_status_not,
    F_stop,
    F_stop_not,
    F_store,
    F_store_not,
    F_stream,
    F_stream_not,
    F_string,
    F_string_not,
    F_string_too_large,
    F_string_too_small,
    F_success,
    F_success_not,
    F_support,
    F_support_not,
    F_syntax,
    F_syntax_not,
    F_terminate,
    F_terminate_not,
    F_thread,
    F_thread_not,
    F_time,
    F_time_not,
    F_time_out,
    F_too_large,
    F_too_small,
    F_top,
    F_top_not,
    F_type,
    F_type_not,
    F_user,
    F_user_not,
    F_utf,
    F_utf_fragment,
    F_utf_fragment_not,
    F_utf_not,
    F_valid,
    F_valid_not,
    F_value,
    F_value_not,
    F_wait,
    F_wait_not,
    F_want,
    F_want_not,
    F_wish,
    F_wish_not,
    F_world,
    F_world_not,
    F_write,
    F_write_not,
    F_write_only,
    F_yes,
    F_yes_not,
    F_debug,
    F_debug_not,
    F_error,
    F_error_not,
    F_fine,
    F_fine_not,
    F_warning,
    F_warning_not,
    F_array,
    F_array_not,
    F_array_too_large,
    F_array_too_small,
    F_available,
    F_available_not,
    F_available_not_address,
    F_available_not_buffer,
    F_available_not_device,
    F_available_not_pipe,
    F_available_not_port,
    F_available_not_process,
    F_available_not_socket,
    F_busy,
    F_busy_address,
    F_busy_buffer,
    F_busy_device,
    F_busy_not,
    F_busy_pipe,
    F_busy_port,
    F_busy_process,
    F_busy_socket,
    F_network,
    F_network_busy,
    F_network_busy_not,
    F_network_client,
    F_network_client_not,
    F_network_device,
    F_network_device_not,
    F_network_found,
    F_network_found_not,
    F_network_lost,
    F_network_lost_not,
    F_network_not,
    F_network_reach,
    F_network_reach_client,
    F_network_reach_client_not,
    F_network_reach_not,
    F_network_reach_server,
    F_network_reach_server_not,
    F_network_server,
    F_network_server_not,
    F_network_time,
    F_network_time_not,
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
    F_buffer,
    F_buffer_not,
    F_buffer_overflow,
    F_buffer_too_large,
    F_buffer_too_small,
    F_buffer_underflow,
    F_complete_not_utf,
    F_complete_not_utf_block,
    F_complete_not_utf_eoa,
    F_complete_not_utf_eof,
    F_complete_not_utf_eol,
    F_complete_not_utf_eos,
    F_complete_not_utf_start,
    F_complete_not_utf_stop,
    F_none_block,
    F_none_eoa,
    F_none_eof,
    F_none_eol,
    F_none_eos,
    F_none_start,
    F_none_stop,
    F_data,
    F_data_not,
    F_data_not_block,
    F_data_not_eoa,
    F_data_not_eof,
    F_data_not_eol,
    F_data_not_eos,
    F_data_not_start,
    F_data_not_stop,
    F_end,
    F_end_not,
    F_end_not_block,
    F_end_not_eoa,
    F_end_not_eof,
    F_end_not_eol,
    F_end_not_eos,
    F_end_not_group,
    F_end_not_group_block,
    F_end_not_group_eoa,
    F_end_not_group_eof,
    F_end_not_group_eol,
    F_end_not_group_eos,
    F_end_not_group_start,
    F_end_not_group_stop,
    F_end_not_nest,
    F_end_not_nest_block,
    F_end_not_nest_eoa,
    F_end_not_nest_eof,
    F_end_not_nest_eol,
    F_end_not_nest_eos,
    F_end_not_nest_start,
    F_end_not_nest_stop,
    F_end_not_start,
    F_end_not_stop,
    F_process,
    F_process_not,
    F_process_too_many,
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
    F_filesystem,
    F_filesystem_not,
    F_filesystem_quota_block,
    F_filesystem_quota_reached,
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
    F_directory_support_not,
    F_directory_synchronize,
    F_directory_utf,
    F_directory_utf_not,
    F_directory_write,
    F_socket,
    F_socket_client,
    F_socket_not,
    F_socket_receive,
    F_socket_send,
    F_socket_target,
    F_equal_to,
    F_equal_to_not,
    F_than_greater,
    F_than_less,
    F_access,
    F_access_denied,
    F_access_denied_execute,
    F_access_denied_group,
    F_access_denied_read,
    F_access_denied_super,
    F_access_denied_user,
    F_access_denied_world,
    F_access_denied_write,
    F_access_granted,
    F_access_granted_execute,
    F_access_granted_group,
    F_access_granted_read,
    F_access_granted_super,
    F_access_granted_user,
    F_access_granted_world,
    F_access_granted_write,
    F_access_group,
    F_access_mode,
    F_access_not,
    F_access_owner,
    F_terminal,
    F_terminal_access,
    F_terminal_known,
    F_terminal_known_not,
    F_terminal_not,
    F_terminal_prohibited,
    F_terminal_read,
    F_terminal_valid,
    F_terminal_valid_not,
    F_terminal_write,
    F_status_code_last,
  };

  const f_string_static_t status_strings[] = {
    f_status_false_s,
    f_status_true_s,
    f_status_true_s, // This is F_signal_hangup, but it overlaps and falls back to F_true.
    f_status_signal_interrupt_s,
    f_status_signal_quit_s,
    f_status_signal_illegal_s,
    f_status_signal_trap_s,
    f_status_signal_abort_s,
    f_status_signal_bus_error_s,
    f_status_signal_floating_point_error_s,
    f_status_signal_kill_s,
    f_status_signal_user_1_s,
    f_status_signal_segmentation_fault_s,
    f_status_signal_user_2_s,
    f_status_signal_broken_pipe_s,
    f_status_signal_alarm_clock_s,
    f_status_signal_termination_s,
    f_status_signal_stack_fault_s,
    f_status_signal_child_s,
    f_status_signal_continue_s,
    f_status_signal_stop_s,
    f_status_signal_keyboard_stop_s,
    f_status_signal_tty_in_s,
    f_status_signal_tty_out_s,
    f_status_signal_urgent_s,
    f_status_signal_cpu_limit_s,
    f_status_signal_file_size_limit_s,
    f_status_signal_virtual_alarm_clock_s,
    f_status_signal_profile_alarm_clock_s,
    f_status_signal_window_size_change_s,
    f_status_signal_pollable_event_s,
    f_status_signal_power_failure_s,
    f_status_signal_bad_system_call_s,
    f_status_signal_reserved_32_s,
    f_status_signal_reserved_33_s,
    f_status_signal_reserved_34_s,
    f_status_signal_reserved_35_s,
    f_status_signal_reserved_36_s,
    f_status_signal_reserved_37_s,
    f_status_signal_reserved_38_s,
    f_status_signal_reserved_39_s,
    f_status_signal_reserved_40_s,
    f_status_signal_reserved_41_s,
    f_status_signal_reserved_42_s,
    f_status_signal_reserved_43_s,
    f_status_signal_reserved_44_s,
    f_status_signal_reserved_45_s,
    f_status_signal_reserved_46_s,
    f_status_signal_reserved_47_s,
    f_status_signal_reserved_48_s,
    f_status_signal_reserved_49_s,
    f_status_signal_reserved_50_s,
    f_status_signal_reserved_51_s,
    f_status_signal_reserved_52_s,
    f_status_signal_reserved_53_s,
    f_status_signal_reserved_54_s,
    f_status_signal_reserved_55_s,
    f_status_signal_reserved_56_s,
    f_status_signal_reserved_57_s,
    f_status_signal_reserved_58_s,
    f_status_signal_reserved_59_s,
    f_status_signal_reserved_60_s,
    f_status_signal_reserved_61_s,
    f_status_signal_reserved_62_s,
    f_status_signal_reserved_63_s,
    f_status_signal_reserved_64_s,
    f_status_none_s,
    f_status_abort_s,
    f_status_abort_not_s,
    f_status_absolute_s,
    f_status_absolute_not_s,
    f_status_address_s,
    f_status_address_not_s,
    f_status_again_s,
    f_status_again_not_s,
    f_status_ascii_s,
    f_status_ascii_not_s,
    f_status_atomic_s,
    f_status_atomic_not_s,
    f_status_base_s,
    f_status_base_not_s,
    f_status_begin_s,
    f_status_begin_not_s,
    f_status_block_s,
    f_status_block_not_s,
    f_status_body_s,
    f_status_body_not_s,
    f_status_bottom_s,
    f_status_bottom_not_s,
    f_status_bound_s,
    f_status_bound_not_s,
    f_status_break_s,
    f_status_break_not_s,
    f_status_call_s,
    f_status_call_not_s,
    f_status_capability_s,
    f_status_capability_not_s,
    f_status_character_s,
    f_status_character_not_s,
    f_status_child_s,
    f_status_child_not_s,
    f_status_complete_s,
    f_status_complete_not_s,
    f_status_connect_s,
    f_status_connect_not_s,
    f_status_connect_refuse_s,
    f_status_connect_reset_s,
    f_status_container_s,
    f_status_container_not_s,
    f_status_content_s,
    f_status_content_not_s,
    f_status_continue_s,
    f_status_continue_not_s,
    f_status_control_s,
    f_status_control_not_s,
    f_status_control_group_s,
    f_status_control_group_not_s,
    f_status_critical_s,
    f_status_critical_not_s,
    f_status_dead_s,
    f_status_dead_not_s,
    f_status_deadlock_s,
    f_status_deadlock_not_s,
    f_status_descriptor_s,
    f_status_descriptor_not_s,
    f_status_desire_s,
    f_status_desire_not_s,
    f_status_device_s,
    f_status_device_not_s,
    f_status_disable_s,
    f_status_disable_not_s,
    f_status_discard_s,
    f_status_discard_not_s,
    f_status_domain_s,
    f_status_domain_not_s,
    f_status_done_s,
    f_status_done_not_s,
    f_status_drop_s,
    f_status_drop_not_s,
    f_status_dummy_s,
    f_status_dummy_not_s,
    f_status_empty_s,
    f_status_empty_not_s,
    f_status_enable_s,
    f_status_enable_not_s,
    f_status_encoding_s,
    f_status_encoding_not_s,
    f_status_endian_s,
    f_status_endian_big_s,
    f_status_endian_little_s,
    f_status_endian_not_s,
    f_status_eoa_s,
    f_status_eoa_not_s,
    f_status_eof_s,
    f_status_eof_not_s,
    f_status_eol_s,
    f_status_eol_not_s,
    f_status_eos_s,
    f_status_eos_not_s,
    f_status_execute_s,
    f_status_execute_not_s,
    f_status_exist_s,
    f_status_exist_not_s,
    f_status_exit_s,
    f_status_exit_not_s,
    f_status_failure_s,
    f_status_failure_not_s,
    f_status_family_s,
    f_status_family_not_s,
    f_status_fifo_s,
    f_status_fifo_not_s,
    f_status_first_s,
    f_status_first_not_s,
    f_status_footer_s,
    f_status_footer_not_s,
    f_status_fork_s,
    f_status_fork_not_s,
    f_status_format_s,
    f_status_format_not_s,
    f_status_found_s,
    f_status_found_not_s,
    f_status_full_s,
    f_status_full_not_s,
    f_status_group_s,
    f_status_group_not_s,
    f_status_halt_s,
    f_status_halt_not_s,
    f_status_header_s,
    f_status_header_not_s,
    f_status_help_s,
    f_status_help_not_s,
    f_status_ignore_s,
    f_status_ignore_not_s,
    f_status_implement_s,
    f_status_implement_not_s,
    f_status_input_s,
    f_status_input_not_s,
    f_status_input_output_s,
    f_status_interrupt_s,
    f_status_interrupt_not_s,
    f_status_keep_s,
    f_status_keep_not_s,
    f_status_known_s,
    f_status_known_not_s,
    f_status_last_s,
    f_status_last_not_s,
    f_status_limit_s,
    f_status_limit_not_s,
    f_status_link_s,
    f_status_link_not_s,
    f_status_live_s,
    f_status_live_not_s,
    f_status_local_s,
    f_status_local_not_s,
    f_status_lock_s,
    f_status_lock_not_s,
    f_status_loop_s,
    f_status_loop_not_s,
    f_status_maybe_s,
    f_status_maybe_not_s,
    f_status_memory_s,
    f_status_memory_not_s,
    f_status_message_s,
    f_status_message_not_s,
    f_status_middle_s,
    f_status_middle_not_s,
    f_status_minor_s,
    f_status_minor_not_s,
    f_status_moderate_s,
    f_status_moderate_not_s,
    f_status_mount_s,
    f_status_mount_not_s,
    f_status_name_s,
    f_status_name_not_s,
    f_status_need_s,
    f_status_need_not_s,
    f_status_next_s,
    f_status_next_not_s,
    f_status_nice_s,
    f_status_nice_not_s,
    f_status_no_s,
    f_status_no_not_s,
    f_status_object_s,
    f_status_object_not_s,
    f_status_okay_s,
    f_status_okay_not_s,
    f_status_once_s,
    f_status_once_not_s,
    f_status_option_s,
    f_status_option_not_s,
    f_status_output_s,
    f_status_output_not_s,
    f_status_packet_s,
    f_status_packet_not_s,
    f_status_parameter_s,
    f_status_parameter_not_s,
    f_status_parent_s,
    f_status_parent_not_s,
    f_status_payload_s,
    f_status_payload_not_s,
    f_status_pipe_s,
    f_status_pipe_not_s,
    f_status_port_s,
    f_status_port_not_s,
    f_status_previous_s,
    f_status_previous_not_s,
    f_status_processor_s,
    f_status_processor_not_s,
    f_status_progress_s,
    f_status_progress_not_s,
    f_status_prohibited_s,
    f_status_prohibited_not_s,
    f_status_property_s,
    f_status_property_not_s,
    f_status_protocol_s,
    f_status_protocol_not_s,
    f_status_range_s,
    f_status_range_not_s,
    f_status_read_s,
    f_status_read_not_s,
    f_status_read_only_s,
    f_status_ready_s,
    f_status_ready_not_s,
    f_status_receive_s,
    f_status_receive_not_s,
    f_status_recover_s,
    f_status_recover_not_s,
    f_status_recurse_s,
    f_status_recurse_not_s,
    f_status_regular_s,
    f_status_regular_not_s,
    f_status_relative_s,
    f_status_relative_not_s,
    f_status_remote_s,
    f_status_remote_not_s,
    f_status_repeat_s,
    f_status_repeat_not_s,
    f_status_require_s,
    f_status_require_not_s,
    f_status_resource_s,
    f_status_resource_not_s,
    f_status_restart_s,
    f_status_restart_not_s,
    f_status_restore_s,
    f_status_restore_not_s,
    f_status_revert_s,
    f_status_revert_not_s,
    f_status_schedule_s,
    f_status_schedule_not_s,
    f_status_search_s,
    f_status_search_not_s,
    f_status_send_s,
    f_status_send_not_s,
    f_status_signal_s,
    f_status_signal_not_s,
    f_status_size_s,
    f_status_size_not_s,
    f_status_skip_s,
    f_status_skip_not_s,
    f_status_space_s,
    f_status_space_not_s,
    f_status_start_s,
    f_status_start_not_s,
    f_status_status_s,
    f_status_status_not_s,
    f_status_stop_s,
    f_status_stop_not_s,
    f_status_store_s,
    f_status_store_not_s,
    f_status_stream_s,
    f_status_stream_not_s,
    f_status_string_s,
    f_status_string_not_s,
    f_status_string_too_large_s,
    f_status_string_too_small_s,
    f_status_success_s,
    f_status_success_not_s,
    f_status_support_s,
    f_status_support_not_s,
    f_status_syntax_s,
    f_status_syntax_not_s,
    f_status_terminate_s,
    f_status_terminate_not_s,
    f_status_thread_s,
    f_status_thread_not_s,
    f_status_time_s,
    f_status_time_not_s,
    f_status_time_out_s,
    f_status_too_large_s,
    f_status_too_small_s,
    f_status_top_s,
    f_status_top_not_s,
    f_status_type_s,
    f_status_type_not_s,
    f_status_user_s,
    f_status_user_not_s,
    f_status_utf_s,
    f_status_utf_fragment_s,
    f_status_utf_fragment_not_s,
    f_status_utf_not_s,
    f_status_valid_s,
    f_status_valid_not_s,
    f_status_value_s,
    f_status_value_not_s,
    f_status_wait_s,
    f_status_wait_not_s,
    f_status_want_s,
    f_status_want_not_s,
    f_status_wish_s,
    f_status_wish_not_s,
    f_status_world_s,
    f_status_world_not_s,
    f_status_write_s,
    f_status_write_not_s,
    f_status_write_only_s,
    f_status_yes_s,
    f_status_yes_not_s,
    f_status_debug_s,
    f_status_debug_not_s,
    f_status_error_s,
    f_status_error_not_s,
    f_status_fine_s,
    f_status_fine_not_s,
    f_status_warning_s,
    f_status_warning_not_s,
    f_status_array_s,
    f_status_array_not_s,
    f_status_array_too_large_s,
    f_status_array_too_small_s,
    f_status_available_s,
    f_status_available_not_s,
    f_status_available_not_address_s,
    f_status_available_not_buffer_s,
    f_status_available_not_device_s,
    f_status_available_not_pipe_s,
    f_status_available_not_port_s,
    f_status_available_not_process_s,
    f_status_available_not_socket_s,
    f_status_busy_s,
    f_status_busy_address_s,
    f_status_busy_buffer_s,
    f_status_busy_device_s,
    f_status_busy_not_s,
    f_status_busy_pipe_s,
    f_status_busy_port_s,
    f_status_busy_process_s,
    f_status_busy_socket_s,
    f_status_network_s,
    f_status_network_busy_s,
    f_status_network_busy_not_s,
    f_status_network_client_s,
    f_status_network_client_not_s,
    f_status_network_device_s,
    f_status_network_device_not_s,
    f_status_network_found_s,
    f_status_network_found_not_s,
    f_status_network_lost_s,
    f_status_network_lost_not_s,
    f_status_network_not_s,
    f_status_network_reach_s,
    f_status_network_reach_client_s,
    f_status_network_reach_client_not_s,
    f_status_network_reach_not_s,
    f_status_network_reach_server_s,
    f_status_network_reach_server_not_s,
    f_status_network_server_s,
    f_status_network_server_not_s,
    f_status_network_time_s,
    f_status_network_time_not_s,
    f_status_number_s,
    f_status_number_decimal_s,
    f_status_number_decimal_not_s,
    f_status_number_divide_by_zero_s,
    f_status_number_negative_s,
    f_status_number_negative_not_s,
    f_status_number_not_s,
    f_status_number_overflow_s,
    f_status_number_positive_s,
    f_status_number_positive_not_s,
    f_status_number_too_large_s,
    f_status_number_too_small_s,
    f_status_number_underflow_s,
    f_status_number_whole_s,
    f_status_number_whole_not_s,
    f_status_number_zero_s,
    f_status_number_zero_not_s,
    f_status_buffer_s,
    f_status_buffer_not_s,
    f_status_buffer_overflow_s,
    f_status_buffer_too_large_s,
    f_status_buffer_too_small_s,
    f_status_buffer_underflow_s,
    f_status_complete_not_utf_s,
    f_status_complete_not_utf_block_s,
    f_status_complete_not_utf_eoa_s,
    f_status_complete_not_utf_eof_s,
    f_status_complete_not_utf_eol_s,
    f_status_complete_not_utf_eos_s,
    f_status_complete_not_utf_start_s,
    f_status_complete_not_utf_stop_s,
    f_status_none_block_s,
    f_status_none_eoa_s,
    f_status_none_eof_s,
    f_status_none_eol_s,
    f_status_none_eos_s,
    f_status_none_start_s,
    f_status_none_stop_s,
    f_status_data_s,
    f_status_data_not_s,
    f_status_data_not_block_s,
    f_status_data_not_eoa_s,
    f_status_data_not_eof_s,
    f_status_data_not_eol_s,
    f_status_data_not_eos_s,
    f_status_data_not_start_s,
    f_status_data_not_stop_s,
    f_status_end_s,
    f_status_end_not_s,
    f_status_end_not_block_s,
    f_status_end_not_eoa_s,
    f_status_end_not_eof_s,
    f_status_end_not_eol_s,
    f_status_end_not_eos_s,
    f_status_end_not_group_s,
    f_status_end_not_group_block_s,
    f_status_end_not_group_eoa_s,
    f_status_end_not_group_eof_s,
    f_status_end_not_group_eol_s,
    f_status_end_not_group_eos_s,
    f_status_end_not_group_start_s,
    f_status_end_not_group_stop_s,
    f_status_end_not_nest_s,
    f_status_end_not_nest_block_s,
    f_status_end_not_nest_eoa_s,
    f_status_end_not_nest_eof_s,
    f_status_end_not_nest_eol_s,
    f_status_end_not_nest_eos_s,
    f_status_end_not_nest_start_s,
    f_status_end_not_nest_stop_s,
    f_status_end_not_start_s,
    f_status_end_not_stop_s,
    f_status_process_s,
    f_status_process_not_s,
    f_status_process_too_many_s,
    f_status_file_s,
    f_status_file_close_s,
    f_status_file_closed_s,
    f_status_file_descriptor_s,
    f_status_file_descriptor_max_s,
    f_status_file_descriptor_not_s,
    f_status_file_empty_s,
    f_status_file_flush_s,
    f_status_file_found_s,
    f_status_file_found_not_s,
    f_status_file_not_s,
    f_status_file_open_s,
    f_status_file_opened_s,
    f_status_file_open_max_s,
    f_status_file_overflow_s,
    f_status_file_purge_s,
    f_status_file_read_s,
    f_status_file_reallocation_s,
    f_status_file_seek_s,
    f_status_file_stat_s,
    f_status_file_synchronize_s,
    f_status_file_type_block_s,
    f_status_file_type_character_s,
    f_status_file_type_directory_s,
    f_status_file_type_fifo_s,
    f_status_file_type_link_s,
    f_status_file_type_not_block_s,
    f_status_file_type_not_character_s,
    f_status_file_type_not_directory_s,
    f_status_file_type_not_fifo_s,
    f_status_file_type_not_link_s,
    f_status_file_type_not_pipe_s,
    f_status_file_type_not_regular_s,
    f_status_file_type_not_socket_s,
    f_status_file_type_not_unknown_s,
    f_status_file_type_pipe_s,
    f_status_file_type_regular_s,
    f_status_file_type_socket_s,
    f_status_file_type_unknown_s,
    f_status_file_underflow_s,
    f_status_file_utf_s,
    f_status_file_utf_not_s,
    f_status_file_write_s,
    f_status_filesystem_s,
    f_status_filesystem_not_s,
    f_status_filesystem_quota_block_s,
    f_status_filesystem_quota_reached_s,
    f_status_directory_s,
    f_status_directory_close_s,
    f_status_directory_closed_s,
    f_status_directory_descriptor_s,
    f_status_directory_empty_s,
    f_status_directory_empty_not_s,
    f_status_directory_found_s,
    f_status_directory_found_not_s,
    f_status_directory_flush_s,
    f_status_directory_link_max_s,
    f_status_directory_not_s,
    f_status_directory_open_s,
    f_status_directory_purge_s,
    f_status_directory_read_s,
    f_status_directory_stream_s,
    f_status_directory_support_not_s,
    f_status_directory_synchronize_s,
    f_status_directory_utf_s,
    f_status_directory_utf_not_s,
    f_status_directory_write_s,
    f_status_socket_s,
    f_status_socket_client_s,
    f_status_socket_not_s,
    f_status_socket_receive_s,
    f_status_socket_send_s,
    f_status_socket_target_s,
    f_status_equal_to_s,
    f_status_equal_to_not_s,
    f_status_than_greater_s,
    f_status_than_less_s,
    f_status_access_s,
    f_status_access_denied_s,
    f_status_access_denied_execute_s,
    f_status_access_denied_group_s,
    f_status_access_denied_read_s,
    f_status_access_denied_super_s,
    f_status_access_denied_user_s,
    f_status_access_denied_world_s,
    f_status_access_denied_write_s,
    f_status_access_granted_s,
    f_status_access_granted_execute_s,
    f_status_access_granted_group_s,
    f_status_access_granted_read_s,
    f_status_access_granted_super_s,
    f_status_access_granted_user_s,
    f_status_access_granted_world_s,
    f_status_access_granted_write_s,
    f_status_access_group_s,
    f_status_access_mode_s,
    f_status_access_not_s,
    f_status_access_owner_s,
    f_status_terminal_s,
    f_status_terminal_access_s,
    f_status_terminal_known_s,
    f_status_terminal_known_not_s,
    f_status_terminal_not_s,
    f_status_terminal_prohibited_s,
    f_status_terminal_read_s,
    f_status_terminal_valid_s,
    f_status_terminal_valid_not_s,
    f_status_terminal_write_s,
    f_status_status_code_last_s,
  };

  for (uint16_t i = 0; i < 613; ++i) {

    f_string_static_t result = f_string_static_t_initialize;

    const f_status_t status = f_status_string_to(statuss[i], &result);

    assert_int_equal(status, F_none);
    assert_int_equal(result.used, status_strings[i].used);
    assert_string_equal(result.string, status_strings[i].string);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif

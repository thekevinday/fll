#include "../file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_types_
  const f_string_static_t f_file_type_name_block_s = macro_f_string_static_t_initialize(F_file_type_name_block_s, 0, F_file_type_name_block_s_length);
  const f_string_static_t f_file_type_name_character_s = macro_f_string_static_t_initialize(F_file_type_name_character_s, 0, F_file_type_name_character_s_length);
  const f_string_static_t f_file_type_name_directory_s = macro_f_string_static_t_initialize(F_file_type_name_directory_s, 0, F_file_type_name_directory_s_length);
  const f_string_static_t f_file_type_name_fifo_s = macro_f_string_static_t_initialize(F_file_type_name_fifo_s, 0, F_file_type_name_fifo_s_length);
  const f_string_static_t f_file_type_name_link_s = macro_f_string_static_t_initialize(F_file_type_name_link_s, 0, F_file_type_name_link_s_length);
  const f_string_static_t f_file_type_name_regular_s = macro_f_string_static_t_initialize(F_file_type_name_regular_s, 0, F_file_type_name_regular_s_length);
  const f_string_static_t f_file_type_name_socket_s = macro_f_string_static_t_initialize(F_file_type_name_socket_s, 0, F_file_type_name_socket_s_length);
#endif // _di_f_file_types_

#ifndef _di_f_file_open_modes_
  const f_string_static_t f_file_open_mode_append_s = macro_f_string_static_t_initialize(F_file_open_mode_append_s, 0, F_file_open_mode_append_s_length);
  const f_string_static_t f_file_open_mode_read_s = macro_f_string_static_t_initialize(F_file_open_mode_read_s, 0, F_file_open_mode_read_s_length);
  const f_string_static_t f_file_open_mode_read_append_s = macro_f_string_static_t_initialize(F_file_open_mode_read_append_s, 0, F_file_open_mode_read_append_s_length);
  const f_string_static_t f_file_open_mode_read_truncate_s = macro_f_string_static_t_initialize(F_file_open_mode_read_truncate_s, 0, F_file_open_mode_read_truncate_s_length);
  const f_string_static_t f_file_open_mode_read_write_s = macro_f_string_static_t_initialize(F_file_open_mode_read_write_s, 0, F_file_open_mode_read_write_s_length);
  const f_string_static_t f_file_open_mode_truncate_s = macro_f_string_static_t_initialize(F_file_open_mode_truncate_s, 0, F_file_open_mode_truncate_s_length);
#endif // _di_f_file_open_modes_

#ifndef _di_f_file_operation_strings_
  const f_string_static_t f_file_operation_access_s = macro_f_string_static_t_initialize(F_file_operation_access_s, 0, F_file_operation_access_s_length);
  const f_string_static_t f_file_operation_analyze_s = macro_f_string_static_t_initialize(F_file_operation_analyze_s, 0, F_file_operation_analyze_s_length);
  const f_string_static_t f_file_operation_append_s = macro_f_string_static_t_initialize(F_file_operation_append_s, 0, F_file_operation_append_s_length);
  const f_string_static_t f_file_operation_change_group_s = macro_f_string_static_t_initialize(F_file_operation_change_group_s, 0, F_file_operation_change_group_s_length);
  const f_string_static_t f_file_operation_change_mode_s = macro_f_string_static_t_initialize(F_file_operation_change_mode_s, 0, F_file_operation_change_mode_s_length);
  const f_string_static_t f_file_operation_change_owner_s = macro_f_string_static_t_initialize(F_file_operation_change_owner_s, 0, F_file_operation_change_owner_s_length);
  const f_string_static_t f_file_operation_change_type_s = macro_f_string_static_t_initialize(F_file_operation_change_type_s, 0, F_file_operation_change_type_s_length);
  const f_string_static_t f_file_operation_clone_s = macro_f_string_static_t_initialize(F_file_operation_clone_s, 0, F_file_operation_clone_s_length);
  const f_string_static_t f_file_operation_close_s = macro_f_string_static_t_initialize(F_file_operation_close_s, 0, F_file_operation_close_s_length);
  const f_string_static_t f_file_operation_concatenate_s = macro_f_string_static_t_initialize(F_file_operation_concatenate_s, 0, F_file_operation_concatenate_s_length);
  const f_string_static_t f_file_operation_connect_s = macro_f_string_static_t_initialize(F_file_operation_connect_s, 0, F_file_operation_connect_s_length);
  const f_string_static_t f_file_operation_copy_s = macro_f_string_static_t_initialize(F_file_operation_copy_s, 0, F_file_operation_copy_s_length);
  const f_string_static_t f_file_operation_create_s = macro_f_string_static_t_initialize(F_file_operation_create_s, 0, F_file_operation_create_s_length);
  const f_string_static_t f_file_operation_decrypt_s = macro_f_string_static_t_initialize(F_file_operation_decrypt_s, 0, F_file_operation_decrypt_s_length);
  const f_string_static_t f_file_operation_delete_s = macro_f_string_static_t_initialize(F_file_operation_delete_s, 0, F_file_operation_delete_s_length);
  const f_string_static_t f_file_operation_disconnect_s = macro_f_string_static_t_initialize(F_file_operation_disconnect_s, 0, F_file_operation_disconnect_s_length);
  const f_string_static_t f_file_operation_encrypt_s = macro_f_string_static_t_initialize(F_file_operation_encrypt_s, 0, F_file_operation_encrypt_s_length);
  const f_string_static_t f_file_operation_find_s = macro_f_string_static_t_initialize(F_file_operation_find_s, 0, F_file_operation_find_s_length);
  const f_string_static_t f_file_operation_from_s = macro_f_string_static_t_initialize(F_file_operation_from_s, 0, F_file_operation_from_s_length);
  const f_string_static_t f_file_operation_flush_s = macro_f_string_static_t_initialize(F_file_operation_flush_s, 0, F_file_operation_flush_s_length);
  const f_string_static_t f_file_operation_get_group_s = macro_f_string_static_t_initialize(F_file_operation_get_group_s, 0, F_file_operation_get_group_s_length);
  const f_string_static_t f_file_operation_get_mode_s = macro_f_string_static_t_initialize(F_file_operation_get_mode_s, 0, F_file_operation_get_mode_s_length);
  const f_string_static_t f_file_operation_get_owner_s = macro_f_string_static_t_initialize(F_file_operation_get_owner_s, 0, F_file_operation_get_owner_s_length);
  const f_string_static_t f_file_operation_get_type_s = macro_f_string_static_t_initialize(F_file_operation_get_type_s, 0, F_file_operation_get_type_s_length);
  const f_string_static_t f_file_operation_identify_s = macro_f_string_static_t_initialize(F_file_operation_identify_s, 0, F_file_operation_identify_s_length);
  const f_string_static_t f_file_operation_link_s = macro_f_string_static_t_initialize(F_file_operation_link_s, 0, F_file_operation_link_s_length);
  const f_string_static_t f_file_operation_list_s = macro_f_string_static_t_initialize(F_file_operation_list_s, 0, F_file_operation_list_s_length);
  const f_string_static_t f_file_operation_move_s = macro_f_string_static_t_initialize(F_file_operation_move_s, 0, F_file_operation_move_s_length);
  const f_string_static_t f_file_operation_open_s = macro_f_string_static_t_initialize(F_file_operation_open_s, 0, F_file_operation_open_s_length);
  const f_string_static_t f_file_operation_pipe_s = macro_f_string_static_t_initialize(F_file_operation_pipe_s, 0, F_file_operation_pipe_s_length);
  const f_string_static_t f_file_operation_process_s = macro_f_string_static_t_initialize(F_file_operation_process_s, 0, F_file_operation_process_s_length);
  const f_string_static_t f_file_operation_read_s = macro_f_string_static_t_initialize(F_file_operation_read_s, 0, F_file_operation_read_s_length);
  const f_string_static_t f_file_operation_receive_s = macro_f_string_static_t_initialize(F_file_operation_receive_s, 0, F_file_operation_receive_s_length);
  const f_string_static_t f_file_operation_rename_s = macro_f_string_static_t_initialize(F_file_operation_rename_s, 0, F_file_operation_rename_s_length);
  const f_string_static_t f_file_operation_send_s = macro_f_string_static_t_initialize(F_file_operation_send_s, 0, F_file_operation_send_s_length);
  const f_string_static_t f_file_operation_shred_s = macro_f_string_static_t_initialize(F_file_operation_shred_s, 0, F_file_operation_shred_s_length);
  const f_string_static_t f_file_operation_stat_s = macro_f_string_static_t_initialize(F_file_operation_stat_s, 0, F_file_operation_stat_s_length);
  const f_string_static_t f_file_operation_to_s = macro_f_string_static_t_initialize(F_file_operation_to_s, 0, F_file_operation_to_s_length);
  const f_string_static_t f_file_operation_touch_s = macro_f_string_static_t_initialize(F_file_operation_touch_s, 0, F_file_operation_touch_s_length);
  const f_string_static_t f_file_operation_truncate_s = macro_f_string_static_t_initialize(F_file_operation_truncate_s, 0, F_file_operation_truncate_s_length);
  const f_string_static_t f_file_operation_unlink_s = macro_f_string_static_t_initialize(F_file_operation_unlink_s, 0, F_file_operation_unlink_s_length);
  const f_string_static_t f_file_operation_verify_s = macro_f_string_static_t_initialize(F_file_operation_verify_s, 0, F_file_operation_verify_s_length);
  const f_string_static_t f_file_operation_wipe_s = macro_f_string_static_t_initialize(F_file_operation_wipe_s, 0, F_file_operation_wipe_s_length);
  const f_string_static_t f_file_operation_write_s = macro_f_string_static_t_initialize(F_file_operation_write_s, 0, F_file_operation_write_s_length);
#endif // _di_f_file_operation_strings_

#ifdef __cplusplus
} // extern "C"
#endif

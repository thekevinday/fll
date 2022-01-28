#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_type_
  const f_string_static_t f_file_type_name_blocks_s = macro_f_string_static_t_initialize2(F_file_type_name_block_s, 0, F_file_type_name_block_s_length);
  const f_string_static_t f_file_type_name_character_s = macro_f_string_static_t_initialize2(F_file_type_name_character_s, 0, F_file_type_name_character_s_length);
  const f_string_static_t f_file_type_name_directory_s = macro_f_string_static_t_initialize2(F_file_type_name_directory_s, 0, F_file_type_name_directory_s_length);
  const f_string_static_t f_file_type_name_link_s = macro_f_string_static_t_initialize2(F_file_type_name_link_s, 0, F_file_type_name_link_s_length);
  const f_string_static_t f_file_type_name_regular_s = macro_f_string_static_t_initialize2(F_file_type_name_regular_s, 0, F_file_type_name_regular_s_length);
  const f_string_static_t f_file_type_name_socket_s = macro_f_string_static_t_initialize2(F_file_type_name_socket_s, 0, F_file_type_name_socket_s_length);

  const f_string_static_t f_file_open_mode_append_s = macro_f_string_static_t_initialize2(F_file_open_mode_append_s, 0, F_file_open_mode_append_s_length);
  const f_string_static_t f_file_open_mode_read_s = macro_f_string_static_t_initialize2(F_file_open_mode_read_s, 0, F_file_open_mode_read_s_length);
  const f_string_static_t f_file_open_mode_read_append_s = macro_f_string_static_t_initialize2(F_file_open_mode_read_append_s, 0, F_file_open_mode_read_append_s_length);
  const f_string_static_t f_file_open_mode_read_truncate_s = macro_f_string_static_t_initialize2(F_file_open_mode_read_truncate_s, 0, F_file_open_mode_read_truncate_s_length);
  const f_string_static_t f_file_open_mode_read_write_s = macro_f_string_static_t_initialize2(F_file_open_mode_read_write_s, 0, F_file_open_mode_read_write_s_length);
  const f_string_static_t f_file_open_mode_truncate_s = macro_f_string_static_t_initialize2(F_file_open_mode_truncate_s, 0, F_file_open_mode_truncate_s_length);
#endif // _di_f_file_type_

#ifdef __cplusplus
} // extern "C"
#endif

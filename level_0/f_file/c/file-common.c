#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_type_
  const f_string_t f_file_type_name_blocks_s = F_file_type_name_block_s;
  const f_string_t f_file_type_name_character_s = F_file_type_name_character_s;
  const f_string_t f_file_type_name_directory_s = F_file_type_name_directory_s;
  const f_string_t f_file_type_name_link_s = F_file_type_name_link_s;
  const f_string_t f_file_type_name_regular_s = F_file_type_name_regular_s;
  const f_string_t f_file_type_name_socket_s = F_file_type_name_socket_s;

  const f_string_t f_file_open_mode_append_s = F_file_open_mode_append_s;
  const f_string_t f_file_open_mode_read_s = F_file_open_mode_read_s;
  const f_string_t f_file_open_mode_read_append_s = F_file_open_mode_read_append_s;
  const f_string_t f_file_open_mode_read_truncate_s = F_file_open_mode_read_truncate_s;
  const f_string_t f_file_open_mode_read_write_s = F_file_open_mode_read_write_s;
  const f_string_t f_file_open_mode_truncate_s = F_file_open_mode_truncate_s;
#endif // _di_f_file_type_

#ifdef __cplusplus
} // extern "C"
#endif

#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_type_
  const f_string_t f_file_type_name_blocks = f_file_type_name_block;
  const f_string_t f_file_type_name_character_s = f_file_type_name_character;
  const f_string_t f_file_type_name_directory_s = f_file_type_name_directory;
  const f_string_t f_file_type_name_link_s = f_file_type_name_link;
  const f_string_t f_file_type_name_regular_s = f_file_type_name_regular;
  const f_string_t f_file_type_name_socket_s = f_file_type_name_socket;

  const f_string_t f_file_open_mode_append_s = f_macro_file_open_mode_append;
  const f_string_t f_file_open_mode_read_s = f_macro_file_open_mode_read;
  const f_string_t f_file_open_mode_read_append_s = f_macro_file_open_mode_read_append;
  const f_string_t f_file_open_mode_read_truncate_s = f_macro_file_open_mode_read_truncate;
  const f_string_t f_file_open_mode_read_write_s = f_macro_file_open_mode_read_write;
  const f_string_t f_file_open_mode_truncate_s = f_macro_file_open_mode_truncate;
#endif // _di_f_file_type_

#ifdef __cplusplus
} // extern "C"
#endif

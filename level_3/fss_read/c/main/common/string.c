#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_program_version_s_
  const f_string_static_t fss_read_program_version_s = macro_f_string_static_t_initialize_1(FSS_READ_program_version_s, 0, FSS_READ_program_version_s_length);
#endif // _di_fss_read_program_version_s_

#ifndef _di_fss_read_program_name_s_
  const f_string_static_t fss_read_program_name_s = macro_f_string_static_t_initialize_1(FSS_READ_program_name_s, 0, FSS_READ_program_name_s_length);
  const f_string_static_t fss_read_program_name_long_s = macro_f_string_static_t_initialize_1(FSS_READ_program_name_long_s, 0, FSS_READ_program_name_long_s_length);
#endif // _di_fss_read_program_name_s_

#ifndef _di_fss_read_pipe_s_
  const f_string_static_t fss_read_pipe_content_end_s = macro_f_string_static_t_initialize_1(FSS_READ_pipe_content_end_s, 0, FSS_READ_pipe_content_end_s_length);
  const f_string_static_t fss_read_pipe_content_ignore_s = macro_f_string_static_t_initialize_1(FSS_READ_pipe_content_ignore_s, 0, FSS_READ_pipe_content_ignore_s_length);
  const f_string_static_t fss_read_pipe_content_start_s = macro_f_string_static_t_initialize_1(FSS_READ_pipe_content_start_s, 0, FSS_READ_pipe_content_start_s_length);
#endif // _di_fss_read_pipe_s_

#ifndef _di_fss_read_s_
  const f_string_static_t fss_read_string_two_s = macro_f_string_static_t_initialize_1(FSS_READ_string_two_s, 0, FSS_READ_string_two_s_length);
#endif // _di_fss_read_s_

#ifndef _di_fss_read_delimit_mode_s_
  const f_string_static_t fss_read_delimit_mode_name_none_s = macro_f_string_static_t_initialize_1(FSS_READ_delimit_mode_name_none_s, 0, FSS_READ_delimit_mode_name_none_s_length);
  const f_string_static_t fss_read_delimit_mode_name_all_s = macro_f_string_static_t_initialize_1(FSS_READ_delimit_mode_name_all_s, 0, FSS_READ_delimit_mode_name_all_s_length);
  const f_string_static_t fss_read_delimit_mode_name_object_s = macro_f_string_static_t_initialize_1(FSS_READ_delimit_mode_name_object_s, 0, FSS_READ_delimit_mode_name_object_s_length);
  const f_string_static_t fss_read_delimit_mode_name_greater_s = macro_f_string_static_t_initialize_1(FSS_READ_delimit_mode_name_greater_s, 0, FSS_READ_delimit_mode_name_greater_s_length);
  const f_string_static_t fss_read_delimit_mode_name_lesser_s = macro_f_string_static_t_initialize_1(FSS_READ_delimit_mode_name_lesser_s, 0, FSS_READ_delimit_mode_name_lesser_s_length);
#endif // _di_fss_read_delimit_mode_s_

#ifndef _di_fss_read_parameter_s_
  const f_string_static_t fss_read_short_at_s = macro_f_string_static_t_initialize_1(FSS_READ_short_at_s, 0, FSS_READ_short_at_s_length);
  const f_string_static_t fss_read_short_content_s = macro_f_string_static_t_initialize_1(FSS_READ_short_content_s, 0, FSS_READ_short_content_s_length);
  const f_string_static_t fss_read_short_columns_s = macro_f_string_static_t_initialize_1(FSS_READ_short_columns_s, 0, FSS_READ_short_columns_s_length);
  const f_string_static_t fss_read_short_delimit_s = macro_f_string_static_t_initialize_1(FSS_READ_short_delimit_s, 0, FSS_READ_short_delimit_s_length);
  const f_string_static_t fss_read_short_depth_s = macro_f_string_static_t_initialize_1(FSS_READ_short_depth_s, 0, FSS_READ_short_depth_s_length);
  const f_string_static_t fss_read_short_empty_s = macro_f_string_static_t_initialize_1(FSS_READ_short_empty_s, 0, FSS_READ_short_empty_s_length);
  const f_string_static_t fss_read_short_line_s = macro_f_string_static_t_initialize_1(FSS_READ_short_line_s, 0, FSS_READ_short_line_s_length);
  const f_string_static_t fss_read_short_name_s = macro_f_string_static_t_initialize_1(FSS_READ_short_name_s, 0, FSS_READ_short_name_s_length);
  const f_string_static_t fss_read_short_object_s = macro_f_string_static_t_initialize_1(FSS_READ_short_object_s, 0, FSS_READ_short_object_s_length);
  const f_string_static_t fss_read_short_pipe_s = macro_f_string_static_t_initialize_1(FSS_READ_short_pipe_s, 0, FSS_READ_short_pipe_s_length);
  const f_string_static_t fss_read_short_original_s = macro_f_string_static_t_initialize_1(FSS_READ_short_original_s, 0, FSS_READ_short_original_s_length);
  const f_string_static_t fss_read_short_select_s = macro_f_string_static_t_initialize_1(FSS_READ_short_select_s, 0, FSS_READ_short_select_s_length);
  const f_string_static_t fss_read_short_total_s = macro_f_string_static_t_initialize_1(FSS_READ_short_total_s, 0, FSS_READ_short_total_s_length);
  const f_string_static_t fss_read_short_trim_s = macro_f_string_static_t_initialize_1(FSS_READ_short_trim_s, 0, FSS_READ_short_trim_s_length);

  const f_string_static_t fss_read_long_at_s = macro_f_string_static_t_initialize_1(FSS_READ_long_at_s, 0, FSS_READ_long_at_s_length);
  const f_string_static_t fss_read_long_content_s = macro_f_string_static_t_initialize_1(FSS_READ_long_content_s, 0, FSS_READ_long_content_s_length);
  const f_string_static_t fss_read_long_columns_s = macro_f_string_static_t_initialize_1(FSS_READ_long_columns_s, 0, FSS_READ_long_columns_s_length);
  const f_string_static_t fss_read_long_delimit_s = macro_f_string_static_t_initialize_1(FSS_READ_long_delimit_s, 0, FSS_READ_long_delimit_s_length);
  const f_string_static_t fss_read_long_depth_s = macro_f_string_static_t_initialize_1(FSS_READ_long_depth_s, 0, FSS_READ_long_depth_s_length);
  const f_string_static_t fss_read_long_empty_s = macro_f_string_static_t_initialize_1(FSS_READ_long_empty_s, 0, FSS_READ_long_empty_s_length);
  const f_string_static_t fss_read_long_line_s = macro_f_string_static_t_initialize_1(FSS_READ_long_line_s, 0, FSS_READ_long_line_s_length);
  const f_string_static_t fss_read_long_name_s = macro_f_string_static_t_initialize_1(FSS_READ_long_name_s, 0, FSS_READ_long_name_s_length);
  const f_string_static_t fss_read_long_object_s = macro_f_string_static_t_initialize_1(FSS_READ_long_object_s, 0, FSS_READ_long_object_s_length);
  const f_string_static_t fss_read_long_pipe_s = macro_f_string_static_t_initialize_1(FSS_READ_long_pipe_s, 0, FSS_READ_long_pipe_s_length);
  const f_string_static_t fss_read_long_original_s = macro_f_string_static_t_initialize_1(FSS_READ_long_original_s, 0, FSS_READ_long_original_s_length);
  const f_string_static_t fss_read_long_select_s = macro_f_string_static_t_initialize_1(FSS_READ_long_select_s, 0, FSS_READ_long_select_s_length);
  const f_string_static_t fss_read_long_total_s = macro_f_string_static_t_initialize_1(FSS_READ_long_total_s, 0, FSS_READ_long_total_s_length);
  const f_string_static_t fss_read_long_trim_s = macro_f_string_static_t_initialize_1(FSS_READ_long_trim_s, 0, FSS_READ_long_trim_s_length);
#endif // _di_fss_read_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

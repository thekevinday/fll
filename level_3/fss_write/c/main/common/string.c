#include "../fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_program_version_s_
  const f_string_static_t fss_write_program_version_s = macro_f_string_static_t_initialize(FSS_WRITE_program_version_s, 0, FSS_WRITE_program_version_s_length);
#endif // _di_fss_write_program_version_s_

#ifndef _di_fss_write_program_name_s_
  const f_string_static_t fss_write_program_name_s = macro_f_string_static_t_initialize(FSS_WRITE_program_name_s, 0, FSS_WRITE_program_name_s_length);
  const f_string_static_t fss_write_program_name_long_s = macro_f_string_static_t_initialize(FSS_WRITE_program_name_long_s, 0, FSS_WRITE_program_name_long_s_length);
#endif // _di_fss_write_program_name_s_

#ifndef _di_fss_write_pipe_s_
  const f_string_static_t fss_write_pipe_content_end_s = macro_f_string_static_t_initialize(FSS_WRITE_pipe_content_end_s, 0, FSS_WRITE_pipe_content_end_s_length);
  const f_string_static_t fss_write_pipe_content_ignore_s = macro_f_string_static_t_initialize(FSS_WRITE_pipe_content_ignore_s, 0, FSS_WRITE_pipe_content_ignore_s_length);
  const f_string_static_t fss_write_pipe_content_start_s = macro_f_string_static_t_initialize(FSS_WRITE_pipe_content_start_s, 0, FSS_WRITE_pipe_content_start_s_length);
#endif // _di_fss_write_pipe_s_

#ifndef _di_fss_write_s_
  const f_string_static_t fss_write_string_two_s = macro_f_string_static_t_initialize(FSS_WRITE_string_two_s, 0, FSS_WRITE_string_two_s_length);
#endif // _di_fss_write_s_

#ifndef _di_fss_write_parameter_s_
  const f_string_static_t fss_write_short_as_s = macro_f_string_static_t_initialize(FSS_WRITE_short_as_s, 0, FSS_WRITE_short_as_s_length);
  const f_string_static_t fss_write_short_backtick_s = macro_f_string_static_t_initialize(FSS_WRITE_short_backtick_s, 0, FSS_WRITE_short_backtick_s_length);
  const f_string_static_t fss_write_short_content_s = macro_f_string_static_t_initialize(FSS_WRITE_short_content_s, 0, FSS_WRITE_short_content_s_length);
  const f_string_static_t fss_write_short_content_end_s = macro_f_string_static_t_initialize(FSS_WRITE_short_content_end_s, 0, FSS_WRITE_short_content_end_s_length);
  const f_string_static_t fss_write_short_content_next_s = macro_f_string_static_t_initialize(FSS_WRITE_short_content_next_s, 0, FSS_WRITE_short_content_next_s_length);
  const f_string_static_t fss_write_short_double_s = macro_f_string_static_t_initialize(FSS_WRITE_short_double_s, 0, FSS_WRITE_short_double_s_length);
  const f_string_static_t fss_write_short_file_s = macro_f_string_static_t_initialize(FSS_WRITE_short_file_s, 0, FSS_WRITE_short_file_s_length);
  const f_string_static_t fss_write_short_ignore_s = macro_f_string_static_t_initialize(FSS_WRITE_short_ignore_s, 0, FSS_WRITE_short_ignore_s_length);
  const f_string_static_t fss_write_short_object_s = macro_f_string_static_t_initialize(FSS_WRITE_short_object_s, 0, FSS_WRITE_short_object_s_length);
  const f_string_static_t fss_write_short_object_open_s = macro_f_string_static_t_initialize(FSS_WRITE_short_object_open_s, 0, FSS_WRITE_short_object_open_s_length);
  const f_string_static_t fss_write_short_partial_s = macro_f_string_static_t_initialize(FSS_WRITE_short_partial_s, 0, FSS_WRITE_short_partial_s_length);
  const f_string_static_t fss_write_short_prepend_s = macro_f_string_static_t_initialize(FSS_WRITE_short_prepend_s, 0, FSS_WRITE_short_prepend_s_length);
  const f_string_static_t fss_write_short_single_s = macro_f_string_static_t_initialize(FSS_WRITE_short_single_s, 0, FSS_WRITE_short_single_s_length);
  const f_string_static_t fss_write_short_trim_s = macro_f_string_static_t_initialize(FSS_WRITE_short_trim_s, 0, FSS_WRITE_short_trim_s_length);

  const f_string_static_t fss_write_long_as_s = macro_f_string_static_t_initialize(FSS_WRITE_long_as_s, 0, FSS_WRITE_long_as_s_length);
  const f_string_static_t fss_write_long_backtick_s = macro_f_string_static_t_initialize(FSS_WRITE_long_backtick_s, 0, FSS_WRITE_long_backtick_s_length);
  const f_string_static_t fss_write_long_content_s = macro_f_string_static_t_initialize(FSS_WRITE_long_content_s, 0, FSS_WRITE_long_content_s_length);
  const f_string_static_t fss_write_long_content_end_s = macro_f_string_static_t_initialize(FSS_WRITE_long_content_end_s, 0, FSS_WRITE_long_content_end_s_length);
  const f_string_static_t fss_write_long_content_next_s = macro_f_string_static_t_initialize(FSS_WRITE_long_content_next_s, 0, FSS_WRITE_long_content_next_s_length);
  const f_string_static_t fss_write_long_double_s = macro_f_string_static_t_initialize(FSS_WRITE_long_double_s, 0, FSS_WRITE_long_double_s_length);
  const f_string_static_t fss_write_long_file_s = macro_f_string_static_t_initialize(FSS_WRITE_long_file_s, 0, FSS_WRITE_long_file_s_length);
  const f_string_static_t fss_write_long_ignore_s = macro_f_string_static_t_initialize(FSS_WRITE_long_ignore_s, 0, FSS_WRITE_long_ignore_s_length);
  const f_string_static_t fss_write_long_object_s = macro_f_string_static_t_initialize(FSS_WRITE_long_object_s, 0, FSS_WRITE_long_object_s_length);
  const f_string_static_t fss_write_long_object_open_s = macro_f_string_static_t_initialize(FSS_WRITE_long_object_open_s, 0, FSS_WRITE_long_object_open_s_length);
  const f_string_static_t fss_write_long_partial_s = macro_f_string_static_t_initialize(FSS_WRITE_long_partial_s, 0, FSS_WRITE_long_partial_s_length);
  const f_string_static_t fss_write_long_prepend_s = macro_f_string_static_t_initialize(FSS_WRITE_long_prepend_s, 0, FSS_WRITE_long_prepend_s_length);
  const f_string_static_t fss_write_long_single_s = macro_f_string_static_t_initialize(FSS_WRITE_long_single_s, 0, FSS_WRITE_long_single_s_length);
  const f_string_static_t fss_write_long_trim_s = macro_f_string_static_t_initialize(FSS_WRITE_long_trim_s, 0, FSS_WRITE_long_trim_s_length);
#endif // _di_fss_write_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#include "fss_extended_list_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_write_program_version_
  const f_string_static_t fss_extended_list_write_program_version_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_program_version_s, 0, FSS_EXTENDED_LIST_WRITE_program_version_s_length);
#endif // _di_fss_extended_list_write_program_version_

#ifndef _di_fss_extended_list_write_program_name_
  const f_string_static_t fss_extended_list_write_program_name_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_program_name_s, 0, FSS_EXTENDED_LIST_WRITE_program_name_s_length);
  const f_string_static_t fss_extended_list_write_program_name_long_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_program_name_long_s, 0, FSS_EXTENDED_LIST_WRITE_program_name_long_s_length);
#endif // _di_fss_extended_list_write_program_name_

#ifndef _di_fss_extended_list_write_defines_
  const f_string_static_t fss_extended_list_write_pipe_name_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_pipe_name_s, 0, FSS_EXTENDED_LIST_WRITE_pipe_name_s_length);
  const f_string_static_t fss_extended_list_write_pipe_content_end_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_pipe_content_end_s, 0, FSS_EXTENDED_LIST_WRITE_pipe_content_end_s_length);
  const f_string_static_t fss_extended_list_write_pipe_content_ignore_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_pipe_content_ignore_s, 0, FSS_EXTENDED_LIST_WRITE_pipe_content_ignore_s_length);
  const f_string_static_t fss_extended_list_write_pipe_content_start_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_pipe_content_start_s, 0, FSS_EXTENDED_LIST_WRITE_pipe_content_start_s_length);
#endif // _di_fss_extended_list_write_defines_

#ifndef _di_fss_extended_list_write_parameters_
  const f_string_static_t fss_extended_list_write_short_file_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_file_s, 0, FSS_EXTENDED_LIST_WRITE_short_file_s_length);
  const f_string_static_t fss_extended_list_write_short_content_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_content_s, 0, FSS_EXTENDED_LIST_WRITE_short_content_s_length);
  const f_string_static_t fss_extended_list_write_short_double_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_double_s, 0, FSS_EXTENDED_LIST_WRITE_short_double_s_length);
  const f_string_static_t fss_extended_list_write_short_ignore_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_ignore_s, 0, FSS_EXTENDED_LIST_WRITE_short_ignore_s_length);
  const f_string_static_t fss_extended_list_write_short_object_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_object_s, 0, FSS_EXTENDED_LIST_WRITE_short_object_s_length);
  const f_string_static_t fss_extended_list_write_short_partial_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_partial_s, 0, FSS_EXTENDED_LIST_WRITE_short_partial_s_length);
  const f_string_static_t fss_extended_list_write_short_prepend_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_prepend_s, 0, FSS_EXTENDED_LIST_WRITE_short_prepend_s_length);
  const f_string_static_t fss_extended_list_write_short_single_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_single_s, 0, FSS_EXTENDED_LIST_WRITE_short_single_s_length);
  const f_string_static_t fss_extended_list_write_short_trim_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_short_trim_s, 0, FSS_EXTENDED_LIST_WRITE_short_trim_s_length);

  const f_string_static_t fss_extended_list_write_long_file_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_file_s, 0, FSS_EXTENDED_LIST_WRITE_long_file_s_length);
  const f_string_static_t fss_extended_list_write_long_content_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_content_s, 0, FSS_EXTENDED_LIST_WRITE_long_content_s_length);
  const f_string_static_t fss_extended_list_write_long_double_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_double_s, 0, FSS_EXTENDED_LIST_WRITE_long_double_s_length);
  const f_string_static_t fss_extended_list_write_long_ignore_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_ignore_s, 0, FSS_EXTENDED_LIST_WRITE_long_ignore_s_length);
  const f_string_static_t fss_extended_list_write_long_object_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_object_s, 0, FSS_EXTENDED_LIST_WRITE_long_object_s_length);
  const f_string_static_t fss_extended_list_write_long_partial_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_partial_s, 0, FSS_EXTENDED_LIST_WRITE_long_partial_s_length);
  const f_string_static_t fss_extended_list_write_long_prepend_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_prepend_s, 0, FSS_EXTENDED_LIST_WRITE_long_prepend_s_length);
  const f_string_static_t fss_extended_list_write_long_single_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_single_s, 0, FSS_EXTENDED_LIST_WRITE_long_single_s_length);
  const f_string_static_t fss_extended_list_write_long_trim_s = macro_f_string_static_t_initialize(FSS_EXTENDED_LIST_WRITE_long_trim_s, 0, FSS_EXTENDED_LIST_WRITE_long_trim_s_length);
#endif // _di_fss_extended_list_write_parameters_

#ifndef _di_fss_extended_list_write_main_delete_
  f_status_t fss_extended_list_write_main_delete(fll_program_data_t *main) {

    return fll_program_data_delete(main);
  }
#endif // _di_fss_extended_list_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

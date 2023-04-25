#include "../iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_program_version_s_
  const f_string_static_t iki_read_program_version_s = macro_f_string_static_t_initialize_1(IKI_READ_program_version_s, 0, IKI_READ_program_version_s_length);
#endif // _di_iki_read_program_version_s_

#ifndef _di_iki_read_program_name_s_
  const f_string_static_t iki_read_program_name_s = macro_f_string_static_t_initialize_1(IKI_READ_program_name_s, 0, IKI_READ_program_name_s_length);
  const f_string_static_t iki_read_program_name_long_s = macro_f_string_static_t_initialize_1(IKI_READ_program_name_long_s, 0, IKI_READ_program_name_long_s_length);
#endif // _di_iki_read_program_name_s_

#ifndef _di_iki_read_s_
  const f_string_static_t iki_read_string_two_s = macro_f_string_static_t_initialize_1(IKI_READ_string_two_s, 0, IKI_READ_string_two_s_length);
  const f_string_static_t iki_read_string_three_s = macro_f_string_static_t_initialize_1(IKI_READ_string_three_s, 0, IKI_READ_string_three_s_length);
#endif // _di_iki_read_s_

#ifndef _di_iki_read_substitution_s_
  const f_string_static_t iki_read_substitution_after_s = macro_f_string_static_t_initialize_1(IKI_READ_substitution_after_s, 0, IKI_READ_substitution_after_s_length);
  const f_string_static_t iki_read_substitution_before_s = macro_f_string_static_t_initialize_1(IKI_READ_substitution_before_s, 0, IKI_READ_substitution_before_s_length);
  const f_string_static_t iki_read_substitution_replace_s = macro_f_string_static_t_initialize_1(IKI_READ_substitution_replace_s, 0, IKI_READ_substitution_replace_s_length);
  const f_string_static_t iki_read_substitution_vocabulary_s = macro_f_string_static_t_initialize_1(IKI_READ_substitution_vocabulary_s, 0, IKI_READ_substitution_vocabulary_s_length);
  const f_string_static_t iki_read_substitution_with_s = macro_f_string_static_t_initialize_1(IKI_READ_substitution_with_s, 0, IKI_READ_substitution_with_s_length);
#endif // _di_iki_read_substitution_s_

#ifndef _di_iki_read_parameter_s_
  const f_string_static_t iki_read_short_at_s = macro_f_string_static_t_initialize_1(IKI_READ_short_at_s, 0, IKI_READ_short_at_s_length);
  const f_string_static_t iki_read_short_content_s = macro_f_string_static_t_initialize_1(IKI_READ_short_content_s, 0, IKI_READ_short_content_s_length);
  const f_string_static_t iki_read_short_line_s = macro_f_string_static_t_initialize_1(IKI_READ_short_line_s, 0, IKI_READ_short_line_s_length);
  const f_string_static_t iki_read_short_literal_s = macro_f_string_static_t_initialize_1(IKI_READ_short_literal_s, 0, IKI_READ_short_literal_s_length);
  const f_string_static_t iki_read_short_name_s = macro_f_string_static_t_initialize_1(IKI_READ_short_name_s, 0, IKI_READ_short_name_s_length);
  const f_string_static_t iki_read_short_object_s = macro_f_string_static_t_initialize_1(IKI_READ_short_object_s, 0, IKI_READ_short_object_s_length);
  const f_string_static_t iki_read_short_reassign_s = macro_f_string_static_t_initialize_1(IKI_READ_short_reassign_s, 0, IKI_READ_short_reassign_s_length);
  const f_string_static_t iki_read_short_replace_s = macro_f_string_static_t_initialize_1(IKI_READ_short_replace_s, 0, IKI_READ_short_replace_s_length);
  const f_string_static_t iki_read_short_substitute_s = macro_f_string_static_t_initialize_1(IKI_READ_short_substitute_s, 0, IKI_READ_short_substitute_s_length);
  const f_string_static_t iki_read_short_total_s = macro_f_string_static_t_initialize_1(IKI_READ_short_total_s, 0, IKI_READ_short_total_s_length);
  const f_string_static_t iki_read_short_whole_s = macro_f_string_static_t_initialize_1(IKI_READ_short_whole_s, 0, IKI_READ_short_whole_s_length);
  const f_string_static_t iki_read_short_wrap_s = macro_f_string_static_t_initialize_1(IKI_READ_short_wrap_s, 0, IKI_READ_short_wrap_s_length);

  const f_string_static_t iki_read_long_at_s = macro_f_string_static_t_initialize_1(IKI_READ_long_at_s, 0, IKI_READ_long_at_s_length);
  const f_string_static_t iki_read_long_content_s = macro_f_string_static_t_initialize_1(IKI_READ_long_content_s, 0, IKI_READ_long_content_s_length);
  const f_string_static_t iki_read_long_line_s = macro_f_string_static_t_initialize_1(IKI_READ_long_line_s, 0, IKI_READ_long_line_s_length);
  const f_string_static_t iki_read_long_literal_s = macro_f_string_static_t_initialize_1(IKI_READ_long_literal_s, 0, IKI_READ_long_literal_s_length);
  const f_string_static_t iki_read_long_name_s = macro_f_string_static_t_initialize_1(IKI_READ_long_name_s, 0, IKI_READ_long_name_s_length);
  const f_string_static_t iki_read_long_object_s = macro_f_string_static_t_initialize_1(IKI_READ_long_object_s, 0, IKI_READ_long_object_s_length);
  const f_string_static_t iki_read_long_reassign_s = macro_f_string_static_t_initialize_1(IKI_READ_long_reassign_s, 0, IKI_READ_long_reassign_s_length);
  const f_string_static_t iki_read_long_replace_s = macro_f_string_static_t_initialize_1(IKI_READ_long_replace_s, 0, IKI_READ_long_replace_s_length);
  const f_string_static_t iki_read_long_substitute_s = macro_f_string_static_t_initialize_1(IKI_READ_long_substitute_s, 0, IKI_READ_long_substitute_s_length);
  const f_string_static_t iki_read_long_total_s = macro_f_string_static_t_initialize_1(IKI_READ_long_total_s, 0, IKI_READ_long_total_s_length);
  const f_string_static_t iki_read_long_whole_s = macro_f_string_static_t_initialize_1(IKI_READ_long_whole_s, 0, IKI_READ_long_whole_s_length);
  const f_string_static_t iki_read_long_wrap_s = macro_f_string_static_t_initialize_1(IKI_READ_long_wrap_s, 0, IKI_READ_long_wrap_s_length);
#endif // _di_iki_read_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

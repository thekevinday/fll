#include "../utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_program_version_s_
  const f_string_static_t utf8_program_version_s = macro_f_string_static_t_initialize(UTF8_program_version_s, 0, UTF8_program_version_s_length);
#endif // _di_utf8_program_version_s_

#ifndef _di_utf8_program_name_s_
  const f_string_static_t utf8_program_name_s = macro_f_string_static_t_initialize(UTF8_program_name_s, 0, UTF8_program_name_s_length);
  const f_string_static_t utf8_program_name_long_s = macro_f_string_static_t_initialize(UTF8_program_name_long_s, 0, UTF8_program_name_long_s_length);
#endif // _di_utf8_program_name_s_

#ifndef _di_utf8_program_help_parameters_s_
  const f_string_static_t utf8_program_help_parameters_s = macro_f_string_static_t_initialize(UTF8_program_help_parameters_s, 0, UTF8_program_help_parameters_s_length);
#endif // _di_utf8_program_help_parameters_s_

#ifndef _di_utf8_s_
  const f_string_static_t utf8_string_combining_is_s = macro_f_string_static_t_initialize(UTF8_string_combining_is_s, 0, UTF8_string_combining_is_s_length);
  const f_string_static_t utf8_string_combining_not_s = macro_f_string_static_t_initialize(UTF8_string_combining_not_s, 0, UTF8_string_combining_not_s_length);
  const f_string_static_t utf8_string_unknown_s = macro_f_string_static_t_initialize(UTF8_string_unknown_s, 0, UTF8_string_unknown_s_length);

  const f_string_static_t utf8_string_from_s = macro_f_string_static_t_initialize(UTF8_string_from_s, 0, UTF8_string_from_s_length);
  const f_string_static_t utf8_string_to_s = macro_f_string_static_t_initialize(UTF8_string_to_s, 0, UTF8_string_to_s_length);

  const f_string_static_t utf8_string_prepend_padding_s = macro_f_string_static_t_initialize(UTF8_string_prepend_padding_s, 0, UTF8_string_prepend_padding_s_length);

  const f_string_static_t utf8_string_valid_not_s = macro_f_string_static_t_initialize(UTF8_string_valid_not_s, 0, UTF8_string_valid_not_s_length);

  const f_string_static_t utf8_string_verified_valid_s = macro_f_string_static_t_initialize(UTF8_string_verified_valid_s, 0, UTF8_string_verified_valid_s_length);
  const f_string_static_t utf8_string_verified_valid_not_s = macro_f_string_static_t_initialize(UTF8_string_verified_valid_not_s, 0, UTF8_string_verified_valid_not_s_length);

  const f_string_static_t utf8_string_width_0_s = macro_f_string_static_t_initialize(UTF8_string_width_0_s, 0, UTF8_string_width_0_s_length);
  const f_string_static_t utf8_string_width_1_s = macro_f_string_static_t_initialize(UTF8_string_width_1_s, 0, UTF8_string_width_1_s_length);
  const f_string_static_t utf8_string_width_2_s = macro_f_string_static_t_initialize(UTF8_string_width_2_s, 0, UTF8_string_width_2_s_length);
  const f_string_static_t utf8_string_width_3_s = macro_f_string_static_t_initialize(UTF8_string_width_3_s, 0, UTF8_string_width_3_s_length);
  const f_string_static_t utf8_string_width_4_s = macro_f_string_static_t_initialize(UTF8_string_width_4_s, 0, UTF8_string_width_4_s_length);
#endif // _di_utf8_s_

#ifndef _di_utf8_parameter_s_
  const f_string_static_t utf8_short_from_bytesequence_s = macro_f_string_static_t_initialize(UTF8_short_from_bytesequence_s, 0, UTF8_short_from_bytesequence_s_length);
  const f_string_static_t utf8_short_from_codepoint_s = macro_f_string_static_t_initialize(UTF8_short_from_codepoint_s, 0, UTF8_short_from_codepoint_s_length);
  const f_string_static_t utf8_short_from_file_s = macro_f_string_static_t_initialize(UTF8_short_from_file_s, 0, UTF8_short_from_file_s_length);

  const f_string_static_t utf8_short_headers_s = macro_f_string_static_t_initialize(UTF8_short_headers_s, 0, UTF8_short_headers_s_length);
  const f_string_static_t utf8_short_separate_s = macro_f_string_static_t_initialize(UTF8_short_separate_s, 0, UTF8_short_separate_s_length);
  const f_string_static_t utf8_short_strip_invalid_s = macro_f_string_static_t_initialize(UTF8_short_strip_invalid_s, 0, UTF8_short_strip_invalid_s_length);
  const f_string_static_t utf8_short_verify_s = macro_f_string_static_t_initialize(UTF8_short_verify_s, 0, UTF8_short_verify_s_length);

  const f_string_static_t utf8_short_to_bytesequence_s = macro_f_string_static_t_initialize(UTF8_short_to_bytesequence_s, 0, UTF8_short_to_bytesequence_s_length);
  const f_string_static_t utf8_short_to_codepoint_s = macro_f_string_static_t_initialize(UTF8_short_to_codepoint_s, 0, UTF8_short_to_codepoint_s_length);
  const f_string_static_t utf8_short_to_combining_s = macro_f_string_static_t_initialize(UTF8_short_to_combining_s, 0, UTF8_short_to_combining_s_length);
  const f_string_static_t utf8_short_to_file_s = macro_f_string_static_t_initialize(UTF8_short_to_file_s, 0, UTF8_short_to_file_s_length);
  const f_string_static_t utf8_short_to_width_s = macro_f_string_static_t_initialize(UTF8_short_to_width_s, 0, UTF8_short_to_width_s_length);

  const f_string_static_t utf8_long_from_bytesequence_s = macro_f_string_static_t_initialize(UTF8_long_from_bytesequence_s, 0, UTF8_long_from_bytesequence_s_length);
  const f_string_static_t utf8_long_from_codepoint_s = macro_f_string_static_t_initialize(UTF8_long_from_codepoint_s, 0, UTF8_long_from_codepoint_s_length);
  const f_string_static_t utf8_long_from_file_s = macro_f_string_static_t_initialize(UTF8_long_from_file_s, 0, UTF8_long_from_file_s_length);

  const f_string_static_t utf8_long_headers_s = macro_f_string_static_t_initialize(UTF8_long_headers_s, 0, UTF8_long_headers_s_length);
  const f_string_static_t utf8_long_separate_s = macro_f_string_static_t_initialize(UTF8_long_separate_s, 0, UTF8_long_separate_s_length);
  const f_string_static_t utf8_long_strip_invalid_s = macro_f_string_static_t_initialize(UTF8_long_strip_invalid_s, 0, UTF8_long_strip_invalid_s_length);
  const f_string_static_t utf8_long_verify_s = macro_f_string_static_t_initialize(UTF8_long_verify_s, 0, UTF8_long_verify_s_length);

  const f_string_static_t utf8_long_to_bytesequence_s = macro_f_string_static_t_initialize(UTF8_long_to_bytesequence_s, 0, UTF8_long_to_bytesequence_s_length);
  const f_string_static_t utf8_long_to_codepoint_s = macro_f_string_static_t_initialize(UTF8_long_to_codepoint_s, 0, UTF8_long_to_codepoint_s_length);
  const f_string_static_t utf8_long_to_combining_s = macro_f_string_static_t_initialize(UTF8_long_to_combining_s, 0, UTF8_long_to_combining_s_length);
  const f_string_static_t utf8_long_to_file_s = macro_f_string_static_t_initialize(UTF8_long_to_file_s, 0, UTF8_long_to_file_s_length);
  const f_string_static_t utf8_long_to_width_s = macro_f_string_static_t_initialize(UTF8_long_to_width_s, 0, UTF8_long_to_width_s_length);
#endif // _di_utf8_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

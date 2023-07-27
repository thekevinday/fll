#include "../byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_program_version_d_
  const f_string_static_t byte_dump_program_version_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_program_version_s, 0, BYTE_DUMP_program_version_s_length);
#endif // _di_byte_dump_program_version_d_

#ifndef _di_byte_dump_program_name_s_
  const f_string_static_t byte_dump_program_name_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_program_name_s, 0, BYTE_DUMP_program_name_s_length);
  const f_string_static_t byte_dump_program_name_long_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_program_name_long_s, 0, BYTE_DUMP_program_name_long_s_length);
#endif // _di_byte_dump_program_name_s_

#ifndef _di_byte_dump_s_
  const f_string_static_t byte_dump_hexidecimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_hexidecimal_s, 0, BYTE_DUMP_hexidecimal_s_length);
  const f_string_static_t byte_dump_duodecimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_duodecimal_s, 0, BYTE_DUMP_duodecimal_s_length);
  const f_string_static_t byte_dump_octal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_octal_s, 0, BYTE_DUMP_octal_s_length);
  const f_string_static_t byte_dump_binary_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_binary_s, 0, BYTE_DUMP_binary_s_length);
  const f_string_static_t byte_dump_decimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_decimal_s, 0, BYTE_DUMP_decimal_s_length);

  const f_string_static_t byte_dump_character_wall_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_character_wall_s, 0, BYTE_DUMP_character_wall_s_length);
  const f_string_static_t byte_dump_character_placeholder_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_character_placeholder_s, 0, BYTE_DUMP_character_placeholder_s_length);
  const f_string_static_t byte_dump_character_incomplete_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_character_incomplete_s, 0, BYTE_DUMP_character_incomplete_s_length);
  const f_string_static_t byte_dump_character_unused_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_character_unused_s, 0, BYTE_DUMP_character_unused_s_length);

  const f_string_static_t byte_dump_format_raw_context_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_format_raw_context_s, 0, BYTE_DUMP_format_raw_context_s_length);
#endif // _di_byte_dump_s_

#ifndef _di_byte_dump_padding_s_
  const f_string_static_t byte_dump_padding_3_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_3_s, 0, BYTE_DUMP_padding_3_s_length);
  const f_string_static_t byte_dump_padding_4_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_4_s, 0, BYTE_DUMP_padding_4_s_length);
  const f_string_static_t byte_dump_padding_5_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_5_s, 0, BYTE_DUMP_padding_5_s_length);
  const f_string_static_t byte_dump_padding_6_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_6_s, 0, BYTE_DUMP_padding_6_s_length);
  const f_string_static_t byte_dump_padding_8_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_8_s, 0, BYTE_DUMP_padding_8_s_length);
  const f_string_static_t byte_dump_padding_9_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_9_s, 0, BYTE_DUMP_padding_9_s_length);

  #ifdef _clang_not_a_compile_time_constant_workaround_
    const f_string_static_t byte_dump_padding_s[6] = {
      macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_9_s, 0, BYTE_DUMP_padding_9_s_length),
      macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_3_s, 0, BYTE_DUMP_padding_3_s_length),
      macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_4_s, 0, BYTE_DUMP_padding_4_s_length),
      macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_4_s, 0, BYTE_DUMP_padding_4_s_length),
      macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_9_s, 0, BYTE_DUMP_padding_9_s_length),
      macro_f_string_static_t_initialize_1(BYTE_DUMP_padding_4_s, 0, BYTE_DUMP_padding_4_s_length),
    };
  #else
    const f_string_static_t byte_dump_padding_s[] = {
      byte_dump_padding_9_s,
      byte_dump_padding_3_s,
      byte_dump_padding_4_s,
      byte_dump_padding_4_s,
      byte_dump_padding_9_s,
      byte_dump_padding_4_s,
    };
  #endif
#endif // _di_byte_dump_padding_s_

#ifndef _di_byte_dump_parameter_d_
  const f_string_static_t byte_dump_short_binary_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_binary_s, 0, BYTE_DUMP_short_binary_s_length);
  const f_string_static_t byte_dump_short_decimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_decimal_s, 0, BYTE_DUMP_short_decimal_s_length);
  const f_string_static_t byte_dump_short_duodecimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_duodecimal_s, 0, BYTE_DUMP_short_duodecimal_s_length);
  const f_string_static_t byte_dump_short_hexidecimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_hexidecimal_s, 0, BYTE_DUMP_short_hexidecimal_s_length);
  const f_string_static_t byte_dump_short_octal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_octal_s, 0, BYTE_DUMP_short_octal_s_length);
  const f_string_static_t byte_dump_short_unicode_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_unicode_s, 0, BYTE_DUMP_short_unicode_s_length);

  const f_string_static_t byte_dump_short_first_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_first_s, 0, BYTE_DUMP_short_first_s_length);
  const f_string_static_t byte_dump_short_last_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_last_s, 0, BYTE_DUMP_short_last_s_length);

  const f_string_static_t byte_dump_short_narrow_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_narrow_s, 0, BYTE_DUMP_short_narrow_s_length);
  const f_string_static_t byte_dump_short_placeholder_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_placeholder_s, 0, BYTE_DUMP_short_placeholder_s_length);
  const f_string_static_t byte_dump_short_text_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_text_s, 0, BYTE_DUMP_short_text_s_length);
  const f_string_static_t byte_dump_short_wide_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_wide_s, 0, BYTE_DUMP_short_wide_s_length);
  const f_string_static_t byte_dump_short_width_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_short_width_s, 0, BYTE_DUMP_short_width_s_length);

  const f_string_static_t byte_dump_long_binary_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_binary_s, 0, BYTE_DUMP_long_binary_s_length);
  const f_string_static_t byte_dump_long_decimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_decimal_s, 0, BYTE_DUMP_long_decimal_s_length);
  const f_string_static_t byte_dump_long_duodecimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_duodecimal_s, 0, BYTE_DUMP_long_duodecimal_s_length);
  const f_string_static_t byte_dump_long_hexidecimal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_hexidecimal_s, 0, BYTE_DUMP_long_hexidecimal_s_length);
  const f_string_static_t byte_dump_long_octal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_octal_s, 0, BYTE_DUMP_long_octal_s_length);
  const f_string_static_t byte_dump_long_unicode_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_unicode_s, 0, BYTE_DUMP_long_unicode_s_length);

  const f_string_static_t byte_dump_long_first_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_first_s, 0, BYTE_DUMP_long_first_s_length);
  const f_string_static_t byte_dump_long_last_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_last_s, 0, BYTE_DUMP_long_last_s_length);

  const f_string_static_t byte_dump_long_narrow_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_narrow_s, 0, BYTE_DUMP_long_narrow_s_length);
  const f_string_static_t byte_dump_long_placeholder_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_placeholder_s, 0, BYTE_DUMP_long_placeholder_s_length);
  const f_string_static_t byte_dump_long_text_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_text_s, 0, BYTE_DUMP_long_text_s_length);
  const f_string_static_t byte_dump_long_wide_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_wide_s, 0, BYTE_DUMP_long_wide_s_length);
  const f_string_static_t byte_dump_long_width_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_width_s, 0, BYTE_DUMP_long_width_s_length);

  const f_string_static_t byte_dump_long_normal_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_normal_s, 0, BYTE_DUMP_long_normal_s_length);
  const f_string_static_t byte_dump_long_simple_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_simple_s, 0, BYTE_DUMP_long_simple_s_length);
  const f_string_static_t byte_dump_long_classic_s = macro_f_string_static_t_initialize_1(BYTE_DUMP_long_classic_s, 0, BYTE_DUMP_long_classic_s_length);
#endif // _di_byte_dump_parameter_d_

#ifdef __cplusplus
} // extern "C"
#endif

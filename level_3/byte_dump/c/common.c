#include "byte_dump.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_program_version_
  const f_string_static_t byte_dump_program_version_s = macro_f_string_static_t_initialize(BYTE_DUMP_program_version_s, 0, BYTE_DUMP_program_version_s_length);
#endif // _di_byte_dump_program_version_

#ifndef _di_byte_dump_program_name_
  const f_string_static_t byte_dump_program_name_s = macro_f_string_static_t_initialize(BYTE_DUMP_program_name_s, 0, BYTE_DUMP_program_name_s_length);
  const f_string_static_t byte_dump_program_name_long_s = macro_f_string_static_t_initialize(BYTE_DUMP_program_name_long_s, 0, BYTE_DUMP_program_name_long_s_length);
#endif // _di_byte_dump_program_name_

#ifndef _di_byte_dump_print_strings_
  const f_string_static_t byte_dump_print_strings_hexidecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_hexidecimal_s, 0, BYTE_DUMP_print_strings_hexidecimal_s_length);
  const f_string_static_t byte_dump_print_strings_duodecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_duodecimal_s, 0, BYTE_DUMP_print_strings_duodecimal_s_length);
  const f_string_static_t byte_dump_print_strings_octal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_octal_s, 0, BYTE_DUMP_print_strings_octal_s_length);
  const f_string_static_t byte_dump_print_strings_binary_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_binary_s, 0, BYTE_DUMP_print_strings_binary_s_length);
  const f_string_static_t byte_dump_print_strings_decimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_decimal_s, 0, BYTE_DUMP_print_strings_decimal_s_length);
#endif // _di_byte_dump_print_strings_

#ifndef _di_byte_dump_defines_
  const f_string_static_t byte_dump_character_wall_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_wall_s, 0, BYTE_DUMP_character_wall_s_length);
  const f_string_static_t byte_dump_character_placeholder_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_placeholder_s, 0, BYTE_DUMP_character_placeholder_s_length);
  const f_string_static_t byte_dump_character_incomplete_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_incomplete_s, 0, BYTE_DUMP_character_incomplete_s_length);
  const f_string_static_t byte_dump_character_unused_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_unused_s, 0, BYTE_DUMP_character_unused_s_length);
#endif // _di_byte_dump_defines_

#ifndef _di_byte_dump_parameters_
  const f_string_static_t byte_dump_short_binary_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_binary_s, 0, BYTE_DUMP_short_binary_s_length);
  const f_string_static_t byte_dump_short_decimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_decimal_s, 0, BYTE_DUMP_short_decimal_s_length);
  const f_string_static_t byte_dump_short_duodecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_duodecimal_s, 0, BYTE_DUMP_short_duodecimal_s_length);
  const f_string_static_t byte_dump_short_hexidecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_hexidecimal_s, 0, BYTE_DUMP_short_hexidecimal_s_length);
  const f_string_static_t byte_dump_short_octal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_octal_s, 0, BYTE_DUMP_short_octal_s_length);
  const f_string_static_t byte_dump_short_unicode_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_unicode_s, 0, BYTE_DUMP_short_unicode_s_length);

  const f_string_static_t byte_dump_short_first_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_first_s, 0, BYTE_DUMP_short_first_s_length);
  const f_string_static_t byte_dump_short_last_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_last_s, 0, BYTE_DUMP_short_last_s_length);

  const f_string_static_t byte_dump_short_narrow_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_narrow_s, 0, BYTE_DUMP_short_narrow_s_length);
  const f_string_static_t byte_dump_short_placeholder_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_placeholder_s, 0, BYTE_DUMP_short_placeholder_s_length);
  const f_string_static_t byte_dump_short_text_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_text_s, 0, BYTE_DUMP_short_text_s_length);
  const f_string_static_t byte_dump_short_wide_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_wide_s, 0, BYTE_DUMP_short_wide_s_length);
  const f_string_static_t byte_dump_short_width_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_width_s, 0, BYTE_DUMP_short_width_s_length);

  const f_string_static_t byte_dump_long_binary_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_binary_s, 0, BYTE_DUMP_long_binary_s_length);
  const f_string_static_t byte_dump_long_decimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_decimal_s, 0, BYTE_DUMP_long_decimal_s_length);
  const f_string_static_t byte_dump_long_duodecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_duodecimal_s, 0, BYTE_DUMP_long_duodecimal_s_length);
  const f_string_static_t byte_dump_long_hexidecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_hexidecimal_s, 0, BYTE_DUMP_long_hexidecimal_s_length);
  const f_string_static_t byte_dump_long_octal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_octal_s, 0, BYTE_DUMP_long_octal_s_length);
  const f_string_static_t byte_dump_long_unicode_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_unicode_s, 0, BYTE_DUMP_long_unicode_s_length);

  const f_string_static_t byte_dump_long_first_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_first_s, 0, BYTE_DUMP_long_first_s_length);
  const f_string_static_t byte_dump_long_last_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_last_s, 0, BYTE_DUMP_long_last_s_length);

  const f_string_static_t byte_dump_long_narrow_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_narrow_s, 0, BYTE_DUMP_long_narrow_s_length);
  const f_string_static_t byte_dump_long_placeholder_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_placeholder_s, 0, BYTE_DUMP_long_placeholder_s_length);
  const f_string_static_t byte_dump_long_text_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_text_s, 0, BYTE_DUMP_long_text_s_length);
  const f_string_static_t byte_dump_long_wide_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_wide_s, 0, BYTE_DUMP_long_wide_s_length);
  const f_string_static_t byte_dump_long_width_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_width_s, 0, BYTE_DUMP_long_width_s_length);

  const f_string_static_t byte_dump_long_normal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_normal_s, 0, BYTE_DUMP_long_normal_s_length);
  const f_string_static_t byte_dump_long_simple_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_simple_s, 0, BYTE_DUMP_long_simple_s_length);
  const f_string_static_t byte_dump_long_classic_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_classic_s, 0, BYTE_DUMP_long_classic_s_length);
#endif // _di_byte_dump_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

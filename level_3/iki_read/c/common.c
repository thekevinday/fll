#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_program_version_
  const f_string_static_t iki_read_program_version_s = macro_f_string_static_t_initialize(IKI_READ_program_version_s, 0, IKI_READ_program_version_s_length);
#endif // _di_iki_read_program_version_

#ifndef _di_iki_read_program_name_
  const f_string_static_t iki_read_program_name_s = macro_f_string_static_t_initialize(IKI_READ_program_name_s, 0, IKI_READ_program_name_s_length);
  const f_string_static_t iki_read_program_name_long_s = macro_f_string_static_t_initialize(IKI_READ_program_name_long_s, 0, IKI_READ_program_name_long_s_length);
#endif // _di_iki_read_program_name_

#ifndef _di_iki_read_parameters_
  const f_string_static_t iki_read_short_at_s = macro_f_string_static_t_initialize(IKI_READ_short_at_s, 0, IKI_READ_short_at_s_length);
  const f_string_static_t iki_read_short_content_s = macro_f_string_static_t_initialize(IKI_READ_short_content_s, 0, IKI_READ_short_content_s_length);
  const f_string_static_t iki_read_short_line_s = macro_f_string_static_t_initialize(IKI_READ_short_line_s, 0, IKI_READ_short_line_s_length);
  const f_string_static_t iki_read_short_literal_s = macro_f_string_static_t_initialize(IKI_READ_short_literal_s, 0, IKI_READ_short_literal_s_length);
  const f_string_static_t iki_read_short_name_s = macro_f_string_static_t_initialize(IKI_READ_short_name_s, 0, IKI_READ_short_name_s_length);
  const f_string_static_t iki_read_short_object_s = macro_f_string_static_t_initialize(IKI_READ_short_object_s, 0, IKI_READ_short_object_s_length);
  const f_string_static_t iki_read_short_substitute_s = macro_f_string_static_t_initialize(IKI_READ_short_substitute_s, 0, IKI_READ_short_substitute_s_length);
  const f_string_static_t iki_read_short_total_s = macro_f_string_static_t_initialize(IKI_READ_short_total_s, 0, IKI_READ_short_total_s_length);
  const f_string_static_t iki_read_short_whole_s = macro_f_string_static_t_initialize(IKI_READ_short_whole_s, 0, IKI_READ_short_whole_s_length);

  const f_string_static_t iki_read_long_at_s = macro_f_string_static_t_initialize(IKI_READ_long_at_s, 0, IKI_READ_long_at_s_length);
  const f_string_static_t iki_read_long_content_s = macro_f_string_static_t_initialize(IKI_READ_long_content_s, 0, IKI_READ_long_content_s_length);
  const f_string_static_t iki_read_long_line_s = macro_f_string_static_t_initialize(IKI_READ_long_line_s, 0, IKI_READ_long_line_s_length);
  const f_string_static_t iki_read_long_literal_s = macro_f_string_static_t_initialize(IKI_READ_long_literal_s, 0, IKI_READ_long_literal_s_length);
  const f_string_static_t iki_read_long_name_s = macro_f_string_static_t_initialize(IKI_READ_long_name_s, 0, IKI_READ_long_name_s_length);
  const f_string_static_t iki_read_long_object_s = macro_f_string_static_t_initialize(IKI_READ_long_object_s, 0, IKI_READ_long_object_s_length);
  const f_string_static_t iki_read_long_substitute_s = macro_f_string_static_t_initialize(IKI_READ_long_substitute_s, 0, IKI_READ_long_substitute_s_length);
  const f_string_static_t iki_read_long_total_s = macro_f_string_static_t_initialize(IKI_READ_long_total_s, 0, IKI_READ_long_total_s_length);
  const f_string_static_t iki_read_long_whole_s = macro_f_string_static_t_initialize(IKI_READ_long_whole_s, 0, IKI_READ_long_whole_s_length);
#endif // _di_iki_read_parameters_

#ifndef _di_iki_read_main_delete_
  f_status_t iki_read_main_delete(iki_read_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_string_dynamic_resize(0, &main->buffer);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_iki_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

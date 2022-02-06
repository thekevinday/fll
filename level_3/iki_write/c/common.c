#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_program_version_
  const f_string_static_t iki_write_program_version_s = macro_f_string_static_t_initialize(IKI_WRITE_program_version_s, 0, IKI_WRITE_program_version_s_length);
#endif // _di_iki_write_program_version_

#ifndef _di_iki_write_program_name_
  const f_string_static_t iki_write_program_name_s = macro_f_string_static_t_initialize(IKI_WRITE_program_name_s, 0, IKI_WRITE_program_name_s_length);
  const f_string_static_t iki_write_program_name_long_s = macro_f_string_static_t_initialize(IKI_WRITE_program_name_long_s, 0, IKI_WRITE_program_name_long_s_length);
#endif // _di_iki_write_program_name_

#ifndef _di_iki_write_parameters_
  const f_string_static_t iki_write_short_file_s = macro_f_string_static_t_initialize(IKI_WRITE_short_file_s, 0, IKI_WRITE_short_file_s_length);
  const f_string_static_t iki_write_short_content_s = macro_f_string_static_t_initialize(IKI_WRITE_short_content_s, 0, IKI_WRITE_short_content_s_length);
  const f_string_static_t iki_write_short_double_s = macro_f_string_static_t_initialize(IKI_WRITE_short_double_s, 0, IKI_WRITE_short_double_s_length);
  const f_string_static_t iki_write_short_object_s = macro_f_string_static_t_initialize(IKI_WRITE_short_object_s, 0, IKI_WRITE_short_object_s_length);
  const f_string_static_t iki_write_short_single_s = macro_f_string_static_t_initialize(IKI_WRITE_short_single_s, 0, IKI_WRITE_short_single_s_length);

  const f_string_static_t iki_write_long_file_s = macro_f_string_static_t_initialize(IKI_WRITE_long_file_s, 0, IKI_WRITE_long_file_s_length);
  const f_string_static_t iki_write_long_content_s = macro_f_string_static_t_initialize(IKI_WRITE_long_content_s, 0, IKI_WRITE_long_content_s_length);
  const f_string_static_t iki_write_long_double_s = macro_f_string_static_t_initialize(IKI_WRITE_long_double_s, 0, IKI_WRITE_long_double_s_length);
  const f_string_static_t iki_write_long_object_s = macro_f_string_static_t_initialize(IKI_WRITE_long_object_s, 0, IKI_WRITE_long_object_s_length);
  const f_string_static_t iki_write_long_single_s = macro_f_string_static_t_initialize(IKI_WRITE_long_single_s, 0, IKI_WRITE_long_single_s_length);
#endif // _di_iki_write_parameters_

#ifndef _di_iki_write_main_delete_
  f_status_t iki_write_main_delete(iki_write_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_string_dynamic_resize(0, &main->buffer);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_iki_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

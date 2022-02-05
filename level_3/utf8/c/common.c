#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_program_version_
  const f_string_static_t utf8_program_version_s = macro_f_string_static_t_initialize(UTF8_program_version_s, 0, UTF8_program_version_s_length);
#endif // _di_utf8_program_version_

#ifndef _di_utf8_program_name_
  const f_string_static_t utf8_program_name_s = macro_f_string_static_t_initialize(UTF8_program_name_s, 0, UTF8_program_name_s_length);
  const f_string_static_t utf8_program_name_long_s = macro_f_string_static_t_initialize(UTF8_program_name_long_s, 0, UTF8_program_name_long_s_length);
#endif // _di_utf8_program_name_

#ifndef _di_utf8_main_delete_
  f_status_t utf8_main_delete(utf8_main_t *main) {

    f_console_parameters_delete(&main->parameters);

    f_type_array_lengths_resize(0, &main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_utf8_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

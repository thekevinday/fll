#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_
  const f_string_static_t control_program_version_s = macro_f_string_static_t_initialize(CONTROL_program_version_s, 0, CONTROL_program_version_s_length);
#endif // _di_control_program_version_

#ifndef _di_control_program_name_
  const f_string_static_t control_program_name_s = macro_f_string_static_t_initialize(CONTROL_program_name_s, 0, CONTROL_program_name_s_length);
  const f_string_static_t control_program_name_long_s = macro_f_string_static_t_initialize(CONTROL_program_name_long_s, 0, CONTROL_program_name_long_s_length);
#endif // _di_control_program_name_

#ifndef _di_control_defines_
  const f_string_static_t control_short_name_s = macro_f_string_static_t_initialize(CONTROL_short_name_s, 0, CONTROL_short_name_s_length);
  const f_string_static_t control_short_settings_s = macro_f_string_static_t_initialize(CONTROL_short_settings_s, 0, CONTROL_short_settings_s_length);
  const f_string_static_t control_short_socket_s = macro_f_string_static_t_initialize(CONTROL_short_socket_s, 0, CONTROL_short_socket_s_length);

  const f_string_static_t control_long_name_s = macro_f_string_static_t_initialize(CONTROL_long_name_s, 0, CONTROL_long_name_s_length);
  const f_string_static_t control_long_settings_s = macro_f_string_static_t_initialize(CONTROL_long_settings_s, 0, CONTROL_long_settings_s_length);
  const f_string_static_t control_long_socket_s = macro_f_string_static_t_initialize(CONTROL_long_socket_s, 0, CONTROL_long_socket_s_length);
#endif // _di_control_defines_

#ifndef _di_control_main_delete_
  f_status_t control_main_delete(control_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_type_array_lengths_resize(0, &main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

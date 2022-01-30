#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_
  const f_string_static_t control_program_version_s = macro_f_string_static_t_initialize2(CONTROL_program_version_s, 0, CONTROL_program_version_s_length);
#endif // _di_control_program_version_

#ifndef _di_control_program_name_
  const f_string_static_t control_program_name_s = macro_f_string_static_t_initialize2(CONTROL_program_name_s, 0, CONTROL_program_name_s_length);
  const f_string_static_t control_program_name_long_s = macro_f_string_static_t_initialize2(CONTROL_program_name_long_s, 0, CONTROL_program_name_long_s_length);
#endif // _di_control_program_name_

#ifndef _di_control_defines_
  const f_string_static_t control_short_name_s = macro_f_string_static_t_initialize2(CONTROL_short_name_s, 0, CONTROL_short_name_s_length);
  const f_string_static_t control_short_settings_s = macro_f_string_static_t_initialize2(CONTROL_short_settings_s, 0, CONTROL_short_settings_s_length);
  const f_string_static_t control_short_socket_s = macro_f_string_static_t_initialize2(CONTROL_short_socket_s, 0, CONTROL_short_socket_s_length);

  const f_string_static_t control_long_name_s = macro_f_string_static_t_initialize2(CONTROL_long_name_s, 0, CONTROL_long_name_s_length);
  const f_string_static_t control_long_settings_s = macro_f_string_static_t_initialize2(CONTROL_long_settings_s, 0, CONTROL_long_settings_s_length);
  const f_string_static_t control_long_socket_s = macro_f_string_static_t_initialize2(CONTROL_long_socket_s, 0, CONTROL_long_socket_s_length);
#endif // _di_control_defines_

#ifndef _di_control_main_delete_
  f_status_t control_main_delete(control_main_t * const main) {

    for (f_array_length_t i = 0; i < control_total_parameters_d; ++i) {

      f_type_array_lengths_resize(0, &main->parameters[i].locations);
      f_type_array_lengths_resize(0, &main->parameters[i].locations_sub);
      f_type_array_lengths_resize(0, &main->parameters[i].values);
    } // for

    f_type_array_lengths_resize(0, &main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

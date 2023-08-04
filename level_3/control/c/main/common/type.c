#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_main_delete_
  void control_main_delete(control_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    control_setting_delete(&main->setting);

    f_string_dynamic_resize(0, &main->cache.large);
    f_string_dynamic_resize(0, &main->cache.small);
    f_string_dynamic_resize(0, &main->cache.packet);

    f_string_ranges_resize(0, &main->cache.objects);
    f_string_rangess_resize(0, &main->cache.contents);

    f_string_ranges_resize(0, &main->cache.packet_objects);
    f_string_rangess_resize(0, &main->cache.packet_contents);

    f_string_ranges_resize(0, &main->cache.header_objects);
    f_string_rangess_resize(0, &main->cache.header_contents);

    f_number_unsigneds_resize(0, &main->cache.delimits);
  }
#endif // _di_control_main_delete_

#ifndef _di_control_setting_delete_
  f_status_t control_setting_delete(control_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->name_socket);
    f_string_dynamic_resize(0, &setting->path_settings);
    f_string_dynamic_resize(0, &setting->path_socket);

    f_string_dynamics_resize(0, &setting->actions);

    return F_none;
  }
#endif // _di_control_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

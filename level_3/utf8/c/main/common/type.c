#include "../utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_main_data_delete_
  void utf8_main_delete(utf8_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    utf8_setting_delete(&main->setting);
  }
#endif // _di_utf8_main_data_delete_

#ifndef _di_utf8_setting_delete_
  f_status_t utf8_setting_delete(utf8_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->text);

    f_string_dynamics_resize(0, &setting->path_files_from);
    f_string_dynamics_resize(0, &setting->path_files_to);
    f_string_dynamics_resize(0, &setting->remaining);

    return F_none;
  }
#endif // _di_utf8_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_main_data_delete_
  void iki_write_main_delete(iki_write_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    iki_write_setting_delete(&main->setting);
  }
#endif // _di_iki_write_main_data_delete_

#ifndef _di_iki_write_setting_delete_
  f_status_t iki_write_setting_delete(iki_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->escaped);
    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->object);
    f_string_dynamic_resize(0, &setting->content);

    f_string_dynamics_resize(0, &setting->objects);
    f_string_dynamics_resize(0, &setting->contents);

    return F_none;
  }
#endif // _di_iki_write_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

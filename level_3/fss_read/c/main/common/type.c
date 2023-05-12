#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_depth_delete_
  void fss_read_depth_delete(fss_read_depth_t * const depth) {

    if (!depth) return;

    f_string_dynamic_resize(0, &depth->value_name);
  }
#endif // _di_fss_read_depth_delete_

#ifndef _di_fss_read_main_data_delete_
  void fss_read_main_delete(fss_read_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fss_read_setting_delete(&main->setting);
  }
#endif // _di_fss_read_main_data_delete_

#ifndef _di_fss_read_setting_delete_
  f_status_t fss_read_setting_delete(fss_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->escaped);
    f_string_dynamic_resize(0, &setting->block);
    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->prepend);

    f_string_rangess_resize(0, &setting->ignoress);
    f_string_dynamics_resize(0, &setting->objects);
    f_string_dynamicss_resize(0, &setting->contentss);

    return F_none;
  }
#endif // _di_fss_read_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_main_delete_
  void fss_identify_main_delete(fss_identify_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fss_identify_setting_delete(&main->setting);
  }
#endif // _di_fss_identify_main_delete_

#ifndef _di_fss_identify_setting_delete_
  f_status_t fss_identify_setting_delete(fss_identify_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);

    f_memory_array_resize(0, sizeof(f_fll_id_t), (void **) &setting->ids.array, &setting->ids.used, &setting->ids.size);

    f_string_dynamics_resize(0, &setting->names);
    f_string_dynamics_resize(0, &setting->files);

    return F_okay;
  }
#endif // _di_fss_identify_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

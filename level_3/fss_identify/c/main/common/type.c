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
  void fss_identify_setting_delete(fss_identify_setting_t * const setting) {

    if (!setting) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);
    f_memory_array_resize(0, sizeof(f_fll_id_t), (void **) &setting->ids.array, &setting->ids.used, &setting->ids.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->names.array, &setting->names.used, &setting->names.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->files.array, &setting->files.used, &setting->files.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_fss_identify_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

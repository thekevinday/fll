#include "../fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_main_delete_
  void fss_write_main_delete(fss_write_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fss_write_setting_delete(&main->setting);
  }
#endif // _di_fss_write_main_delete_

#ifndef _di_fss_write_setting_delete_
  void fss_write_setting_delete(fss_write_setting_t * const setting) {

    if (!setting) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->block.string, &setting->block.used, &setting->block.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->prepend.string, &setting->prepend.used, &setting->prepend.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->ignoress.array, &setting->ignoress.used, &setting->ignoress.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->objects.array, &setting->objects.used, &setting->objects.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->contentss.array, &setting->contentss.used, &setting->contentss.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_fss_write_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

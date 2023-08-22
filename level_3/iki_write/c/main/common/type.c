#include "../iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_main_delete_
  void iki_write_main_delete(iki_write_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    iki_write_setting_delete(&main->setting);
  }
#endif // _di_iki_write_main_delete_

#ifndef _di_iki_write_setting_delete_
  f_status_t iki_write_setting_delete(iki_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->escaped.string, &setting->escaped.used, &setting->escaped.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->object.string, &setting->object.used, &setting->object.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->content.string, &setting->content.used, &setting->content.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->objects.array, &setting->objects.used, &setting->objects.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->contents.array, &setting->contents.used, &setting->contents.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_iki_write_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

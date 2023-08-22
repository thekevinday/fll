#include "../iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_main_delete_
  void iki_read_main_delete(iki_read_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    iki_read_setting_delete(&main->setting);
  }
#endif // _di_iki_read_main_delete_

#ifndef _di_iki_read_setting_delete_
  f_status_t iki_read_setting_delete(iki_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->names.array, &setting->names.used, &setting->names.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->files.array, &setting->files.used, &setting->files.size, &f_string_dynamics_delete_callback);

    f_string_maps_resize(0, &setting->replace);
    f_string_triples_resize(0, &setting->reassign);
    f_string_triples_resize(0, &setting->substitute);
    f_string_triples_resize(0, &setting->wrap);

    f_iki_data_delete(&setting->data);

    return F_okay;
  }
#endif // _di_iki_read_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

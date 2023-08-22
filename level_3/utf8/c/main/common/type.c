#include "../utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_main_delete_
  void utf8_main_delete(utf8_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    utf8_setting_delete(&main->setting);
  }
#endif // _di_utf8_main_delete_

#ifndef _di_utf8_setting_delete_
  f_status_t utf8_setting_delete(utf8_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->text.string, &setting->text.used, &setting->text.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->path_files_from.array, &setting->path_files_from.used, &setting->path_files_from.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->path_files_to.array, &setting->path_files_to.used, &setting->path_files_to.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->remaining.array, &setting->remaining.used, &setting->remaining.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_utf8_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

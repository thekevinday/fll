#include "../byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_main_delete_
  void byte_dump_main_delete(byte_dump_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    byte_dump_setting_delete(&main->setting);
  }
#endif // _di_byte_dump_main_delete_

#ifndef _di_byte_dump_setting_delete_
  f_status_t byte_dump_setting_delete(byte_dump_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->files.array, &setting->files.used, &setting->files.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_byte_dump_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

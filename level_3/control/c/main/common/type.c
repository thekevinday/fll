#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_main_delete_
  void control_main_delete(control_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    control_setting_delete(&main->setting);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache.large.string, &main->cache.large.used, &main->cache.large.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache.small.string, &main->cache.small.used, &main->cache.small.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache.packet.string, &main->cache.packet.used, &main->cache.packet.size);

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &main->cache.objects.array, &main->cache.objects.used, &main->cache.objects.size);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &main->cache.contents.array, &main->cache.contents.used, &main->cache.contents.size, &f_rangess_delete_callback);

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &main->cache.packet_objects.array, &main->cache.packet_objects.used, &main->cache.packet_objects.size);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &main->cache.packet_contents.array, &main->cache.packet_contents.used, &main->cache.packet_contents.size, &f_rangess_delete_callback);

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &main->cache.header_objects.array, &main->cache.header_objects.used, &main->cache.header_objects.size);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &main->cache.header_contents.array, &main->cache.header_contents.used, &main->cache.header_contents.size, &f_rangess_delete_callback);

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &main->cache.delimits.array, &main->cache.delimits.used, &main->cache.delimits.size);
  }
#endif // _di_control_main_delete_

#ifndef _di_control_setting_delete_
  f_status_t control_setting_delete(control_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->name_socket.string, &setting->name_socket.used, &setting->name_socket.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_settings.string, &setting->path_settings.used, &setting->path_settings.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_socket.string, &setting->path_socket.used, &setting->path_socket.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->actions.array, &setting->actions.used, &setting->actions.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_control_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

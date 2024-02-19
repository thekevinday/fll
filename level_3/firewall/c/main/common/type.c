#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_cache_delete_
  void firewall_cache_delete(firewall_cache_t * const cache) {

    if (!cache) return;

    f_file_close(&cache->file);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer.string, &cache->buffer.used, &cache->buffer.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->device.string, &cache->device.used, &cache->device.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->ip_list.string, &cache->ip_list.used, &cache->ip_list.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->path_file.string, &cache->path_file.used, &cache->path_file.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->path_file_specific.string, &cache->path_file_specific.used, &cache->path_file_specific.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->protocol.string, &cache->protocol.used, &cache->protocol.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &cache->arguments.array, &cache->arguments.used, &cache->arguments.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &cache->delimits.array, &cache->delimits.used, &cache->delimits.size);

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &cache->basic_objects.array, &cache->basic_objects.used, &cache->basic_objects.size);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &cache->basic_contents.array, &cache->basic_contents.used, &cache->basic_contents.size, &f_rangess_delete_callback);
  }
#endif // _di_firewall_cache_delete_

#ifndef _di_firewall_data_delete_
  void firewall_data_delete(firewall_data_t * const data) {

    if (!data) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->buffer.string, &data->buffer.used, &data->buffer.size);

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &data->chain_ids.array, &data->chain_ids.used, &data->chain_ids.size);

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &data->comments.array, &data->comments.used, &data->comments.size);
    f_memory_array_resize(0, sizeof(f_range_t), (void **) &data->chain_objects.array, &data->chain_objects.used, &data->chain_objects.size);
    f_memory_array_resize(0, sizeof(f_range_t), (void **) &data->rule_objects.array, &data->rule_objects.used, &data->rule_objects.size);

    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &data->chain_contents.array, &data->chain_contents.used, &data->chain_contents.size, &f_rangess_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &data->rule_contents.array, &data->rule_contents.used, &data->rule_contents.size, &f_rangess_delete_callback);
  }
#endif // _di_firewall_data_delete_

#ifndef _di_firewall_main_delete_
  void firewall_main_delete(firewall_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);

    firewall_setting_delete(&main->setting);
    firewall_data_delete(&main->data);
    firewall_cache_delete(&main->cache);
  }
#endif // _di_firewall_main_delete_

#ifndef _di_firewall_setting_delete_
  void firewall_setting_delete(firewall_setting_t * const setting) {

    if (!setting) return;

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->chains.array, &setting->chains.used, &setting->chains.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->devices.array, &setting->devices.used, &setting->devices.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_firewall_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

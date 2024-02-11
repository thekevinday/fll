#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_data_delete_
  void firewall_data_delete(firewall_data_t * const data) {

    if (!data) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->buffer.string, &data->buffer.used, &data->buffer.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &data->chain_ids.string, &data->chain_ids.used, &data->chain_ids.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &data->delimits.string, &data->delimits.used, &data->delimits.size);
    f_memory_array_resize(0, sizeof(f_range_t), (void **) &data->chain_objects.string, &data->chain_objects.used, &data->chain_objects.size);
    f_memory_array_resize(0, sizeof(f_range_t), (void **) &data->rule_objects.string, &data->rule_objects.used, &data->rule_objects.size);

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
  }
#endif // _di_firewall_main_delete_

#ifndef _di_firewall_setting_delete_
  f_status_t firewall_setting_delete(firewall_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->chains.array, &setting->chains.used, &setting->chains.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->devices.array, &setting->devices.used, &setting->devices.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_firewall_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

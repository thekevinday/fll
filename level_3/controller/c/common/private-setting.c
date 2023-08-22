#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_setting_delete_simple_
  void controller_setting_delete_simple(controller_setting_t * const setting) {

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->name_entry.string, &setting->name_entry.used, &setting->name_entry.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_cgroup.string, &setting->path_cgroup.used, &setting->path_cgroup.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_control.string, &setting->path_control.used, &setting->path_control.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_current.string, &setting->path_current.used, &setting->path_current.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_pid.string, &setting->path_pid.used, &setting->path_pid.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_setting.string, &setting->path_setting.used, &setting->path_setting.size);

    controller_control_delete_simple(&setting->control);

    f_string_maps_resize(0, &setting->entry.define);
    f_string_maps_resize(0, &setting->entry.parameter);

    f_string_maps_resize(0, &setting->exit.define);
    f_string_maps_resize(0, &setting->exit.parameter);

    controller_entry_items_delete_simple(&setting->entry.items);
    controller_entry_items_delete_simple(&setting->exit.items);

    controller_rules_delete_simple(&setting->rules);
  }
#endif // _di_controller_setting_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

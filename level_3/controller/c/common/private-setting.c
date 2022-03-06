#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_setting_delete_simple_
  void controller_setting_delete_simple(controller_setting_t * const setting) {

    f_string_dynamic_resize(0, &setting->name_entry);

    f_string_dynamic_resize(0, &setting->path_cgroup);
    f_string_dynamic_resize(0, &setting->path_control);
    f_string_dynamic_resize(0, &setting->path_current);
    f_string_dynamic_resize(0, &setting->path_pid);
    f_string_dynamic_resize(0, &setting->path_setting);

    controller_control_delete_simple(&setting->control);

    controller_entry_items_delete_simple(&setting->entry.items);
    controller_entry_items_delete_simple(&setting->exit.items);

    controller_rules_delete_simple(&setting->rules);
  }
#endif // _di_controller_setting_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#include "control_group.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_control_group_prepare_
  f_status_t fll_control_group_prepare(const f_control_group_t control_group) {
    f_status_t status = F_none;

    if (control_group.path.used) {
      status = f_directory_exists(control_group.path.string);
      if (F_status_is_error(status)) return status;

      if (status == F_false) {
        return F_status_set_error(F_directory_not);
      }
    }

    f_string_length_t length = 0;

    for (f_array_length_t i = 0; i < control_group.groups.used; ++i) {

      if (!control_group.groups.array[i].used) continue;

      length = control_group.path.used + control_group.groups.array[i].used;

      char path[length + 1];

      if (control_group.path.used) {
        memcpy(path, control_group.path.string, control_group.path.used);
      }

      memcpy(path + control_group.path.used, control_group.groups.array[i].string, control_group.groups.array[i].used);
      path[length] = 0;

      status = fl_directory_create(path, length, f_file_mode_all_rwx);
      if (F_status_is_error(status)) break;
    } // for

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_fll_control_group_prepare_

#ifdef __cplusplus
} // extern "C"
#endif

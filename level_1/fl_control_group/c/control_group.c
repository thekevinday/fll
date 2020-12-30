#include "control_group.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_control_group_apply_
  f_return_status fl_control_group_apply(const f_control_group_t control_group, const pid_t id) {
    #ifndef _di_level_1_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (control_group.as_new) {
      if (unshare(CLONE_NEWCGROUP) < 0) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ENOSPC) return F_status_set_error(F_space_not);
        if (errno == EPERM) return F_status_set_error(F_prohibited);

        return F_status_set_error(F_failure);
      }
    }

    f_file_t file = f_macro_file_t_initialize2(0, -1, f_file_flag_write_only);
    f_status_t status = F_none;
    f_string_length_t length = 0;

    for (f_array_length_t i = 0; i < control_group.groups.used; ++i) {

      if (!control_group.groups.array[i].used) continue;

      length = control_group.path.used + control_group.groups.array[i].used + f_control_group_path_system_suffix_length;

      char path[length + 1];

      if (control_group.path.used) {
        memcpy(path, control_group.path.string, control_group.path.used);
      }

      memcpy(path + control_group.path.used, control_group.groups.array[i].string, control_group.groups.array[i].used);
      memcpy(path + control_group.path.used + f_control_group_path_system_default_length, f_control_group_path_system_suffix, f_control_group_path_system_suffix_length);

      path[length] = 0;

      status = f_file_stream_open(path, 0, &file);
      if (F_status_is_error(status)) break;

      fprintf(file.stream, "%llu", id);
      fflush(file.stream);

      f_file_stream_close(F_true, &file);
      if (F_status_is_error(status)) break;
    } // for

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_fl_control_group_apply_

#ifndef _di_fl_control_group_delete_
  f_return_status fl_control_group_delete(f_control_group_t *control_group) {
    f_status_t status = F_none;

    f_macro_control_group_t_delete(status, (*control_group));

    return status;
  }
#endif // _di_fl_control_group_delete_

#ifdef __cplusplus
} // extern "C"
#endif

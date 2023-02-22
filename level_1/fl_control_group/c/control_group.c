#include "control_group.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_control_group_apply_
  f_status_t fl_control_group_apply(const f_control_group_t control_group, const pid_t id) {
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

    f_file_t file = macro_f_file_t_initialize2(0, -1, F_file_flag_write_only_d);
    f_status_t status = F_none;
    f_string_static_t path = f_string_static_t_initialize;

    for (f_array_length_t i = 0; i < control_group.groups.used; ++i) {

      if (!control_group.groups.array[i].used) continue;

      path.used = control_group.path.used + control_group.groups.array[i].used + f_control_group_path_system_suffix_s.used;

      f_char_t path_string[path.used + 1];
      path.string = path_string;

      if (control_group.path.used) {
        memcpy(path.string, control_group.path.string, sizeof(f_char_t) * control_group.path.used);
      }

      memcpy(path.string + control_group.path.used, control_group.groups.array[i].string, sizeof(f_char_t) * control_group.groups.array[i].used);
      memcpy(path.string + control_group.path.used + control_group.groups.array[i].used, f_control_group_path_system_suffix_s.string, sizeof(f_char_t) * f_control_group_path_system_suffix_s.used);

      path.string[path.used] = 0;

      status = f_file_stream_open(path, f_string_empty_s, &file);
      if (F_status_is_error(status)) break;

      fprintf(file.stream, "%d", id);
      fflush(file.stream);

      status = f_file_stream_close(F_true, &file);
      if (F_status_is_error(status)) break;
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fl_control_group_apply_

#ifdef __cplusplus
} // extern "C"
#endif

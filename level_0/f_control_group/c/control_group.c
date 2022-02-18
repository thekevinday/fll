#include "control_group.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_control_group_copy_
  f_status_t f_control_group_copy(const f_control_group_t source, f_control_group_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    destination->as_new = source.as_new;
    destination->path.used = 0;
    destination->groups.used = 0;

    f_status_t status = F_none;

    if (source.path.used) {
      status = f_string_dynamic_append(source.path, &destination->path);
      if (F_status_is_error(status)) return status;
    }

    if (source.groups.used) {
      status = f_string_dynamics_append(source.groups, &destination->groups);
      if (F_status_is_error(status)) return status;
    }

    return F_none;
  }
#endif // _di_f_control_group_copy_

#ifdef __cplusplus
} // extern "C"
#endif

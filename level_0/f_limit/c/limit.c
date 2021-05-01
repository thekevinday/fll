#include "limit.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_limit_process_
  f_status_t f_limit_process(const pid_t id, const int type, const f_limit_value_t *value_next, f_limit_value_t *value_current) {
    #ifndef _di_level_0_parameter_checking_
      if (!value_next && !value_current) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (prlimit(id, type, value_next, value_current) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_address_not);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_limit_process_

#ifndef _di_f_limit_sets_copy_
  f_status_t f_limit_sets_copy(const f_limit_sets_t source, f_limit_sets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    destination->used = 0;

    if (source.used > destination->size) {
      f_status_t status = F_none;

      macro_f_memory_structure_resize(status, (*destination), f_limit_set_t, source.used)
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[i].type = source.array[i].type;
      destination->array[i].value = source.array[i].value;
    } // for

    return F_none;
  }
#endif // _di_f_limit_sets_copy_

#ifndef _di_f_limit_values_copy_
  f_status_t f_limit_values_copy(const f_limit_values_t source, f_limit_values_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    destination->used = 0;

    if (source.used > destination->size) {
      f_status_t status = F_none;

      macro_f_memory_structure_resize(status, (*destination), f_limit_value_t, source.used)
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[i].rlim_cur = source.array[i].rlim_cur;
      destination->array[i].rlim_max = source.array[i].rlim_max;
    } // for

    return F_none;
  }
#endif // _di_f_limit_values_copy_

#ifdef __cplusplus
} // extern "C"
#endif

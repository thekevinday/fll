#include "limit.h"
#include "private-limit.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_limit_process_
  f_return_status f_limit_process(const pid_t id, const int type, const f_limit_value_t *value_next, f_limit_value_t *value_current) {
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

#ifndef _di_f_limit_sets_decrease_
  f_return_status f_limit_sets_decrease(f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->size > 1) {
      return private_f_limit_sets_resize(sets->size - 1, sets);
    }

    return private_f_limit_sets_delete(sets);
  }
#endif // _di_f_limit_sets_decrease_

#ifndef _di_f_limit_sets_decrease_by_
  f_return_status f_limit_sets_decrease_by(const f_array_length_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->size - amount > 0) {
      return private_f_limit_sets_resize(sets->size - amount, sets);
    }

    return private_f_limit_sets_delete(sets);
  }
#endif // _di_f_limit_sets_decrease_by_

#ifndef _di_f_limit_sets_delete_
  f_return_status f_limit_sets_delete(f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_sets_delete(sets);
  }
#endif // _di_f_limit_sets_delete_

#ifndef _di_f_limit_sets_increase_
  f_return_status f_limit_sets_increase(f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->used + 1 > sets->size) {
      f_array_length_t size = sets->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (sets->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_limit_sets_resize(size, sets);
    }

    return F_none;
  }
#endif // _di_f_limit_sets_increase_

#ifndef _di_f_limit_sets_increase_by_
  f_return_status f_limit_sets_increase_by(const f_array_length_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->used + amount > sets->size) {
      if (sets->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_limit_sets_resize(sets->used + amount, sets);
    }

    return F_none;
  }
#endif // _di_f_limit_sets_increase_by_

#ifndef _di_f_limit_values_decrease_
  f_return_status f_limit_values_decrease(f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (values->size > 1) {
      return private_f_limit_values_resize(values->size - 1, values);
    }

    return private_f_limit_values_delete(values);
  }
#endif // _di_f_limit_values_decrease_

#ifndef _di_f_limit_values_decrease_by_
  f_return_status f_limit_values_decrease_by(const f_array_length_t amount, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (values->size - amount > 0) {
      return private_f_limit_values_resize(values->size - amount, values);
    }

    return private_f_limit_values_delete(values);
  }
#endif // _di_f_limit_values_decrease_by_

#ifndef _di_f_limit_values_delete_
  f_return_status f_limit_values_delete(f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_values_delete(values);
  }
#endif // _di_f_limit_values_delete_

#ifndef _di_f_limit_values_increase_
  f_return_status f_limit_values_increase(f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (values->used + 1 > values->size) {
      f_array_length_t size = values->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (values->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_limit_values_resize(size, values);
    }

    return F_none;
  }
#endif // _di_f_limit_values_increase_

#ifndef _di_f_limit_values_increase_by_
  f_return_status f_limit_values_increase_by(const f_array_length_t amount, f_limit_values_t *values) {
    #ifndef _di_level_0_parameter_checking_
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (values->used + amount > values->size) {
      if (values->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_limit_values_resize(values->used + amount, values);
    }

    return F_none;
  }
#endif // _di_f_limit_values_increase_by_


#ifdef __cplusplus
} // extern "C"
#endif

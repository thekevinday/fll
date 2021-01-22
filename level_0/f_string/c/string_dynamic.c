#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_static_empty_s_
  const f_string_static_t f_string_static_empty_s = f_macro_string_static_t_initialize("", 0);
#endif // _di_f_string_static_empty_s_

#ifndef _di_f_string_dynamic_adjust_
  f_status_t f_string_dynamic_adjust(const f_string_length_t length, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_adjust(length, dynamic);
  }
#endif // _di_f_string_dynamic_adjust_

#ifndef _di_f_string_dynamic_decimate_by_
  f_status_t f_string_dynamic_decimate_by(const f_string_length_t amount, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->size - amount > 0) {
      return private_f_string_dynamic_adjust(dynamic->size - amount, dynamic);
    }

    return private_f_string_dynamic_adjust(0, dynamic);
  }
#endif // _di_f_string_dynamic_decimate_by_

#ifndef _di_f_string_dynamic_decrease_by_
  f_status_t f_string_dynamic_decrease_by(const f_string_length_t amount, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->size - amount > 0) {
      return private_f_string_dynamic_resize(dynamic->size - amount, dynamic);
    }

    return private_f_string_dynamic_resize(0, dynamic);
  }
#endif // _di_f_string_dynamic_decrease_by_

#ifndef _di_f_string_dynamic_increase_
  f_status_t f_string_dynamic_increase(f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamic->used + 1 > dynamic->size) {
      f_array_length_t size = dynamic->used + f_memory_default_allocation_step;

      if (size > f_string_length_t_size) {
        if (dynamic->used + 1 > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        size = f_string_length_t_size;
      }

      return private_f_string_dynamic_resize(size, dynamic);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamic_increase_

#ifndef _di_f_string_dynamic_increase_by_
  f_status_t f_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_increase_by(amount, dynamic);
  }
#endif // _di_f_string_dynamic_increase_by_

#ifndef _di_f_string_dynamic_resize_
  f_status_t f_string_dynamic_resize(const f_string_length_t length, f_string_dynamic_t *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamic) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_resize(length, dynamic);
  }
#endif // _di_f_string_dynamic_resize_

#ifndef _di_f_string_dynamics_adjust_
  f_status_t f_string_dynamics_adjust(const f_array_length_t length, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_adjust(length, dynamics);
  }
#endif // _di_f_string_dynamics_adjust_

#ifndef _di_f_string_dynamics_decimate_by_
  f_status_t f_string_dynamics_decimate_by(const f_array_length_t amount, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->size - amount > 0) {
      return private_f_string_dynamics_adjust(dynamics->size - amount, dynamics);
    }

    return private_f_string_dynamics_adjust(0, dynamics);
  }
#endif // _di_f_string_dynamics_decimate_by_

#ifndef _di_f_string_dynamics_decrease_by_
  f_status_t f_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->size - amount > 0) {
      return private_f_string_dynamics_resize(dynamics->size - amount, dynamics);
    }

    return private_f_string_dynamics_resize(0, dynamics);
  }
#endif // _di_f_string_dynamics_decrease_by_

#ifndef _di_f_string_dynamics_increase_
  f_status_t f_string_dynamics_increase(f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + 1 > dynamics->size) {
      f_array_length_t size = dynamics->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (dynamics->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_dynamics_resize(size, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamics_increase_

#ifndef _di_f_string_dynamics_increase_by_
  f_status_t f_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + amount > dynamics->size) {
      if (dynamics->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_dynamics_resize(dynamics->used + amount, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamics_increase_by_

#ifndef _di_f_string_dynamics_resize_
  f_status_t f_string_dynamics_resize(const f_array_length_t length, f_string_dynamics_t *dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_resize(length, dynamics);
  }
#endif // _di_f_string_dynamics_resize_

#ifdef __cplusplus
} // extern "C"
#endif

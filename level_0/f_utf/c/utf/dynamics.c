#include "../utf.h"
#include "../private-utf.h"
#include "static.h"
#include "private-dynamic.h"
#include "private-dynamics.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_dynamics_adjust_
  f_status_t f_utf_string_dynamics_adjust(const f_number_unsigned_t length, f_utf_string_dynamics_t * const dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamics_adjust(length, dynamics);
  }
#endif // _di_f_utf_string_dynamics_adjust_

#ifndef _di_f_utf_string_dynamics_append_
  f_status_t f_utf_string_dynamics_append(const f_utf_string_dynamic_t source, f_utf_string_dynamics_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_dynamics_append(source, destination);
  }
#endif // _di_f_utf_string_dynamics_append_

#ifndef _di_f_utf_string_dynamics_append_all_
  f_status_t f_utf_string_dynamics_append_all(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_dynamics_append_all(source, destination);
  }
#endif // _di_f_utf_string_dynamics_append_all_

#ifndef _di_f_utf_string_dynamics_decimate_by_
  f_status_t f_utf_string_dynamics_decimate_by(const f_number_unsigned_t amount, f_utf_string_dynamics_t * const dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (dynamics->size > amount) {
      return private_f_utf_string_dynamics_adjust(dynamics->size - amount, dynamics);
    }

    return private_f_utf_string_dynamics_adjust(0, dynamics);
  }
#endif // _di_f_utf_string_dynamics_decimate_by_

#ifndef _di_f_utf_string_dynamics_decrease_by_
  f_status_t f_utf_string_dynamics_decrease_by(const f_number_unsigned_t amount, f_utf_string_dynamics_t * const dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (dynamics->size > amount) {
      return private_f_utf_string_dynamics_resize(dynamics->size - amount, dynamics);
    }

    return private_f_utf_string_dynamics_resize(0, dynamics);
  }
#endif // _di_f_utf_string_dynamics_decrease_by_

#ifndef _di_f_utf_string_dynamics_increase_
  f_status_t f_utf_string_dynamics_increase(const f_number_unsigned_t step, f_utf_string_dynamics_t * const dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!step) return F_data_not;

    if (dynamics->used + 1 > dynamics->size) {
      f_number_unsigned_t size = dynamics->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (dynamics->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_utf_string_dynamics_resize(size, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_dynamics_increase_

#ifndef _di_f_utf_string_dynamics_increase_by_
  f_status_t f_utf_string_dynamics_increase_by(const f_number_unsigned_t amount, f_utf_string_dynamics_t * const dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (dynamics->used + amount > dynamics->size) {
      if (dynamics->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_utf_string_dynamics_resize(dynamics->used + amount, dynamics);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_dynamics_increase_by_

#ifndef _di_f_utf_string_dynamics_resize_
  f_status_t f_utf_string_dynamics_resize(const f_number_unsigned_t length, f_utf_string_dynamics_t * const dynamics) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamics) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_dynamics_resize(length, dynamics);
  }
#endif // _di_f_utf_string_dynamics_resize_

#ifdef __cplusplus
} // extern "C"
#endif

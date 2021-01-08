#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_static_empty_s_
  const f_string_static_t f_string_static_empty_s = f_macro_string_static_t_initialize("", 0);
#endif // _di_f_string_static_empty_s_

#ifndef _di_f_string_dynamic_adjust_
  f_status_t f_string_dynamic_adjust(const f_string_length_t length, f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_adjust(length, string);
  }
#endif // _di_f_string_dynamic_adjust_

#ifndef _di_f_string_dynamic_decimate_
  f_status_t f_string_dynamic_decimate(f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string->size > 1) {
      return private_f_string_dynamic_adjust(string->size - 1, string);
    }

    return private_f_string_dynamic_destroy(string);
  }
#endif // _di_f_string_dynamic_decimate_

#ifndef _di_f_string_dynamic_decimate_by_
  f_status_t f_string_dynamic_decimate_by(const f_string_length_t amount, f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string->size - amount > 0) {
      return private_f_string_dynamic_adjust(string->size - amount, string);
    }

    return private_f_string_dynamic_destroy(string);
  }
#endif // _di_f_string_dynamic_decimate_by_

#ifndef _di_f_string_dynamic_decrease_
  f_status_t f_string_dynamic_decrease(f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string->size > 1) {
      return private_f_string_dynamic_resize(string->size - 1, string);
    }

    return private_f_string_dynamic_delete(string);
  }
#endif // _di_f_string_dynamic_decrease_

#ifndef _di_f_string_dynamic_decrease_by_
  f_status_t f_string_dynamic_decrease_by(const f_string_length_t amount, f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string->size - amount > 0) {
      return private_f_string_dynamic_resize(string->size - amount, string);
    }

    return private_f_string_dynamic_delete(string);
  }
#endif // _di_f_string_dynamic_decrease_by_

#ifndef _di_f_string_dynamic_delete_
  f_status_t f_string_dynamic_delete(f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_delete(string);
  }
#endif // _di_f_string_dynamic_delete_

#ifndef _di_f_string_dynamic_destroy_
  f_status_t f_string_dynamic_destroy(f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_destroy(string);
  }
#endif // _di_f_string_dynamic_destroy_

#ifndef _di_f_string_dynamic_increase_
  f_status_t f_string_dynamic_increase(f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (string->used + 1 > string->size) {
      f_array_length_t size = string->used + f_memory_default_allocation_step;

      if (size > f_string_length_t_size) {
        if (string->used + 1 > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        size = f_string_length_t_size;
      }

      return private_f_string_dynamic_resize(size, string);
    }

    return F_none;
  }
#endif // _di_f_string_dynamic_increase_

#ifndef _di_f_string_dynamic_increase_by_
  f_status_t f_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_increase_by(amount, string);
  }
#endif // _di_f_string_dynamic_increase_by_

#ifndef _di_f_string_dynamic_resize_
  f_status_t f_string_dynamic_resize(const f_string_length_t length, f_string_dynamic_t *string) {
    #ifndef _di_level_0_parameter_checking_
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamic_resize(length, string);
  }
#endif // _di_f_string_dynamic_resize_

#ifndef _di_f_string_dynamics_adjust_
  f_status_t f_string_dynamics_adjust(const f_string_length_t length, f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_adjust(length, strings);
  }
#endif // _di_f_string_dynamics_adjust_

#ifndef _di_f_string_dynamics_decimate_
  f_status_t f_string_dynamics_decimate(f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (strings->size > 1) {
      return private_f_string_dynamics_adjust(strings->size - 1, strings);
    }

    return private_f_string_dynamics_destroy(strings);
  }
#endif // _di_f_string_dynamics_decimate_

#ifndef _di_f_string_dynamics_decimate_by_
  f_status_t f_string_dynamics_decimate_by(const f_array_length_t amount, f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (strings->size - amount > 0) {
      return private_f_string_dynamics_adjust(strings->size - amount, strings);
    }

    return private_f_string_dynamics_destroy(strings);
  }
#endif // _di_f_string_dynamics_decimate_by_

#ifndef _di_f_string_dynamics_decrease_
  f_status_t f_string_dynamics_decrease(f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (strings->size > 1) {
      return private_f_string_dynamics_resize(strings->size - 1, strings);
    }

    return private_f_string_dynamics_delete(strings);
  }
#endif // _di_f_string_dynamics_decrease_

#ifndef _di_f_string_dynamics_decrease_by_
  f_status_t f_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (strings->size - amount > 0) {
      return private_f_string_dynamics_resize(strings->size - amount, strings);
    }

    return private_f_string_dynamics_delete(strings);
  }
#endif // _di_f_string_dynamics_decrease_by_

#ifndef _di_f_string_dynamics_delete_
  f_status_t f_string_dynamics_delete(f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_delete(strings);
  }
#endif // _di_f_string_dynamics_delete_

#ifndef _di_f_string_dynamics_destroy_
  f_status_t f_string_dynamics_destroy(f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamics_destroy(strings);
  }
#endif // _di_f_string_dynamics_destroy_

#ifndef _di_f_string_dynamics_increase_
  f_status_t f_string_dynamics_increase(f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (strings->used + 1 > strings->size) {
      f_array_length_t size = strings->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (strings->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_dynamics_resize(size, strings);
    }

    return F_none;
  }
#endif // _di_f_string_dynamics_increase_

#ifndef _di_f_string_dynamics_increase_by_
  f_status_t f_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (!strings) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (strings->used + amount > strings->size) {
      if (strings->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_dynamics_resize(strings->used + amount, strings);
    }

    return F_none;
  }
#endif // _di_f_string_dynamics_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_quantitys_adjust_
  f_status_t f_string_quantitys_adjust(const f_string_length_t length, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_adjust(length, quantitys);
  }
#endif // _di_f_string_quantitys_adjust_

#ifndef _di_f_string_quantitys_decimate_
  f_status_t f_string_quantitys_decimate(f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->size > 1) {
      return private_f_string_quantitys_adjust(quantitys->size - 1, quantitys);
    }

    return private_f_string_quantitys_destroy(quantitys);
  }
#endif // _di_f_string_quantitys_decimate_

#ifndef _di_f_string_quantitys_decimate_by_
  f_status_t f_string_quantitys_decimate_by(const f_array_length_t amount, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->size - amount > 0) {
      return private_f_string_quantitys_adjust(quantitys->size - amount, quantitys);
    }

    return private_f_string_quantitys_destroy(quantitys);
  }
#endif // _di_f_string_quantitys_decimate_by_

#ifndef _di_f_string_quantitys_decrease_
  f_status_t f_string_quantitys_decrease(f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->size > 1) {
      return private_f_string_quantitys_resize(quantitys->size - 1, quantitys);
    }

    return private_f_string_quantitys_delete(quantitys);
  }
#endif // _di_f_string_quantitys_decrease_

#ifndef _di_f_string_quantitys_decrease_by_
  f_status_t f_string_quantitys_decrease_by(const f_array_length_t amount, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->size - amount > 0) {
      return private_f_string_quantitys_resize(quantitys->size - amount, quantitys);
    }

    return private_f_string_quantitys_delete(quantitys);
  }
#endif // _di_f_string_quantitys_decrease_by_

#ifndef _di_f_string_quantitys_delete_
  f_status_t f_string_quantitys_delete(f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_delete(quantitys);
  }
#endif // _di_f_string_quantitys_delete_

#ifndef _di_f_string_quantitys_destroy_
  f_status_t f_string_quantitys_destroy(f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_destroy(quantitys);
  }
#endif // _di_f_string_quantitys_destroy_

#ifndef _di_f_string_quantitys_increase_
  f_status_t f_string_quantitys_increase(f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->used + 1 > quantitys->size) {
      f_array_length_t size = quantitys->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (quantitys->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_quantitys_resize(size, quantitys);
    }

    return F_none;
  }
#endif // _di_f_string_quantitys_increase_

#ifndef _di_f_string_quantitys_increase_by_
  f_status_t f_string_quantitys_increase_by(const f_array_length_t amount, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->used + amount > quantitys->size) {
      if (quantitys->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_quantitys_resize(quantitys->used + amount, quantitys);
    }

    return F_none;
  }
#endif // _di_f_string_quantitys_increase_by_

#ifndef _di_f_string_quantitys_resize_
  f_status_t f_string_quantitys_resize(const f_string_length_t length, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_resize(length, quantitys);
  }
#endif // _di_f_string_quantitys_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_nameds_adjust_
  f_status_t f_fss_nameds_adjust(const f_string_length_t length, f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nameds_adjust(length, nameds);
  }
#endif // _di_f_fss_nameds_adjust_

#ifndef _di_f_fss_nameds_decimate_by_
  f_status_t f_fss_nameds_decimate_by(const f_array_length_t amount, f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nameds->size - amount > 0) {
      return private_f_fss_nameds_adjust(nameds->size - amount, nameds);
    }

    return private_f_fss_nameds_adjust(0, nameds);
  }
#endif // _di_f_fss_nameds_decimate_by_

#ifndef _di_f_fss_nameds_decrease_by_
  f_status_t f_fss_nameds_decrease_by(const f_array_length_t amount, f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nameds->size - amount > 0) {
      return private_f_fss_nameds_resize(nameds->size - amount, nameds);
    }

    return private_f_fss_nameds_resize(0, nameds);
  }
#endif // _di_f_fss_nameds_decrease_by_

#ifndef _di_f_fss_nameds_delete_
  f_status_t f_fss_nameds_delete(f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nameds_resize(0, nameds);
  }
#endif // _di_f_fss_nameds_delete_

#ifndef _di_f_fss_nameds_destroy_
  f_status_t f_fss_nameds_destroy(f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nameds_adjust(0, nameds);
  }
#endif // _di_f_fss_nameds_destroy_

#ifndef _di_f_fss_nameds_increase_
  f_status_t f_fss_nameds_increase(f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nameds->used + 1 > nameds->size) {
      f_array_length_t size = nameds->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (nameds->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_nameds_resize(size, nameds);
    }

    return F_none;
  }
#endif // _di_f_fss_nameds_increase_

#ifndef _di_f_fss_nameds_increase_by_
  f_status_t f_fss_nameds_increase_by(const f_array_length_t amount, f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nameds->used + amount > nameds->size) {
      if (nameds->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_nameds_resize(nameds->used + amount, nameds);
    }

    return F_none;
  }
#endif // _di_f_fss_nameds_increase_by_

#ifndef _di_f_fss_nameds_resize_
  f_status_t f_fss_nameds_resize(const f_string_length_t length, f_fss_nameds_t *nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nameds_resize(length, nameds);
  }
#endif // _di_f_fss_nameds_resize_

#ifdef __cplusplus
} // extern "C"
#endif

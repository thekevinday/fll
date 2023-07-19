#include "../fss.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_set_adjust_
  f_status_t f_fss_set_adjust(const f_number_unsigned_t length, f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_adjust(length, set);
  }
#endif // _di_f_fss_set_adjust_

#ifndef _di_f_fss_set_decimate_by_
  f_status_t f_fss_set_decimate_by(const f_number_unsigned_t amount, f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_set_adjust((set->objects.size - amount > 0) ? set->objects.size - amount : 0, set);
  }
#endif // _di_f_fss_set_decimate_by_

#ifndef _di_f_fss_set_decrease_by_
  f_status_t f_fss_set_decrease_by(const f_number_unsigned_t amount, f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_set_resize((set->objects.size - amount > 0) ? set->objects.size - amount : 0, set);
  }
#endif // _di_f_fss_set_decrease_by_

#ifndef _di_f_fss_set_increase_
  f_status_t f_fss_set_increase(const f_number_unsigned_t step, f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && set->objects.used + 1 > set->objects.size) {
      if (set->objects.used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t size = set->objects.used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (set->objects.used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        size = F_number_t_size_unsigned_d;
      }

      return private_f_fss_set_resize(size, set);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_increase_

#ifndef _di_f_fss_set_increase_by_
  f_status_t f_fss_set_increase_by(const f_number_unsigned_t amount, f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (set->objects.used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = set->objects.used + amount;

      if (length > set->objects.size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_fss_set_resize(length, set);
      }
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_increase_by_

#ifndef _di_f_fss_set_resize_
  f_status_t f_fss_set_resize(const f_number_unsigned_t length, f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_resize(length, set);
  }
#endif // _di_f_fss_set_resize_

#ifndef _di_f_fss_sets_adjust_
  f_status_t f_fss_sets_adjust(const f_number_unsigned_t length, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_sets_adjust(length, sets);
  }
#endif // _di_f_fss_sets_adjust_

#ifndef _di_f_fss_sets_decimate_by_
  f_status_t f_fss_sets_decimate_by(const f_number_unsigned_t amount, f_fss_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_sets_adjust((sets->size > amount) ? sets->size - amount : 0, sets);
  }
#endif // _di_f_fss_sets_decimate_by_

#ifndef _di_f_fss_sets_decrease_by_
  f_status_t f_fss_sets_decrease_by(const f_number_unsigned_t amount, f_fss_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_sets_resize((sets->size > amount) ? sets->size - amount : 0, sets);
  }
#endif // _di_f_fss_sets_decrease_by_

#ifndef _di_f_fss_sets_increase_
  f_status_t f_fss_sets_increase(const f_number_unsigned_t step, f_fss_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_fss_sets_increase_

#ifndef _di_f_fss_sets_increase_by_
  f_status_t f_fss_sets_increase_by(const f_number_unsigned_t amount, f_fss_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // _di_f_fss_sets_increase_by_

#ifndef _di_f_fss_sets_resize_
  f_status_t f_fss_sets_resize(const f_number_unsigned_t length, f_fss_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_sets_resize(length, sets);
  }
#endif // _di_f_fss_sets_resize_

#ifdef __cplusplus
} // extern "C"
#endif

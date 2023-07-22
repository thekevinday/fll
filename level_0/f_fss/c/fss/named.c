#include "../fss.h"
#include "private-named.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_named_adjust_
  f_status_t f_fss_named_adjust(const f_number_unsigned_t length, f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_named_adjust(length, named);
  }
#endif // _di_f_fss_named_adjust_

#ifndef _di_f_fss_named_decimate_by_
  f_status_t f_fss_named_decimate_by(const f_number_unsigned_t amount, f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_named_adjust((named->objects.size - amount > 0) ? named->objects.size - amount : 0, named);
  }
#endif // _di_f_fss_named_decimate_by_

#ifndef _di_f_fss_named_decrease_by_
  f_status_t f_fss_named_decrease_by(const f_number_unsigned_t amount, f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_named_resize((named->objects.size - amount > 0) ? named->objects.size - amount : 0, named);
  }
#endif // _di_f_fss_named_decrease_by_

#ifndef _di_f_fss_named_increase_
  f_status_t f_fss_named_increase(const f_number_unsigned_t step, f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && named->objects.used + 1 > named->objects.size) {
      if (named->objects.used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = named->objects.used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (named->objects.used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_fss_named_resize(length, named);
    }

    return F_data_not;
  }
#endif // _di_f_fss_named_increase_

#ifndef _di_f_fss_named_increase_by_
  f_status_t f_fss_named_increase_by(const f_number_unsigned_t amount, f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (named->objects.used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = named->objects.used + amount;

      if (length > named->objects.size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_fss_named_resize(length, named);
      }
    }

    return F_data_not;
  }
#endif // _di_f_fss_named_increase_by_

#ifndef _di_f_fss_named_resize_
  f_status_t f_fss_named_resize(const f_number_unsigned_t length, f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_named_resize(length, named);
  }
#endif // _di_f_fss_named_resize_

#ifndef _di_f_fss_nameds_adjust_
  f_status_t f_fss_nameds_adjust(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nameds_adjust(length, nameds);
  }
#endif // _di_f_fss_nameds_adjust_

#ifndef _di_f_fss_nameds_decimate_by_
  f_status_t f_fss_nameds_decimate_by(const f_number_unsigned_t amount, f_fss_nameds_t * const nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_nameds_adjust((nameds->size > amount) ? nameds->size - amount : 0, nameds);
  }
#endif // _di_f_fss_nameds_decimate_by_

#ifndef _di_f_fss_nameds_decrease_by_
  f_status_t f_fss_nameds_decrease_by(const f_number_unsigned_t amount, f_fss_nameds_t * const nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_nameds_resize((nameds->size > amount) ? nameds->size - amount : 0, nameds);
  }
#endif // _di_f_fss_nameds_decrease_by_

#ifndef _di_f_fss_nameds_increase_
  f_status_t f_fss_nameds_increase(const f_number_unsigned_t step, f_fss_nameds_t * const nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_named_t), (void **) &nameds->array, &nameds->used, &nameds->size);
  }
#endif // _di_f_fss_nameds_increase_

#ifndef _di_f_fss_nameds_increase_by_
  f_status_t f_fss_nameds_increase_by(const f_number_unsigned_t amount, f_fss_nameds_t * const nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_named_t), (void **) &nameds->array, &nameds->used, &nameds->size);
  }
#endif // _di_f_fss_nameds_increase_by_

#ifndef _di_f_fss_nameds_resize_
  f_status_t f_fss_nameds_resize(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) {
    #ifndef _di_level_0_parameter_checking_
      if (!nameds) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nameds_resize(length, nameds);
  }
#endif // _di_f_fss_nameds_resize_

#ifdef __cplusplus
} // extern "C"
#endif

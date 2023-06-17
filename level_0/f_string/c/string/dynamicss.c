#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-dynamics.h"
#include "private-dynamicss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_dynamicss_adjust_
  f_status_t f_string_dynamicss_adjust(const f_number_unsigned_t length, f_string_dynamicss_t * const dynamicss) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamicss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamicss_adjust(length, dynamicss);
  }
#endif // _di_f_string_dynamicss_adjust_

#ifndef _di_f_string_dynamicss_append_
  f_status_t f_string_dynamicss_append(const f_string_dynamics_t source, f_string_dynamicss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_string_dynamicss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_string_dynamics_append_all(source, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // _di_f_string_dynamicss_append_

#ifndef _di_f_string_dynamicss_append_all_
  f_status_t f_string_dynamicss_append_all(const f_string_dynamicss_t source, f_string_dynamicss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_dynamicss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_string_dynamics_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_string_dynamicss_append_all_

#ifndef _di_f_string_dynamicss_decimate_by_
  f_status_t f_string_dynamicss_decimate_by(const f_number_unsigned_t amount, f_string_dynamicss_t * const dynamicss) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamicss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (dynamicss->size > amount) {
      return private_f_string_dynamicss_adjust(dynamicss->size - amount, dynamicss);
    }

    return private_f_string_dynamicss_adjust(0, dynamicss);
  }
#endif // _di_f_string_dynamicss_decimate_by_

#ifndef _di_f_string_dynamicss_decrease_by_
  f_status_t f_string_dynamicss_decrease_by(const f_number_unsigned_t amount, f_string_dynamicss_t * const dynamicss) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamicss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (dynamicss->size > amount) {
      return private_f_string_dynamicss_resize(dynamicss->size - amount, dynamicss);
    }

    return private_f_string_dynamicss_resize(0, dynamicss);
  }
#endif // _di_f_string_dynamicss_decrease_by_

#ifndef _di_f_string_dynamicss_increase_
  f_status_t f_string_dynamicss_increase(const f_number_unsigned_t step, f_string_dynamicss_t * const dynamicss) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamicss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!step) return F_data_not;

    if (dynamicss->used + 1 > dynamicss->size) {
      f_number_unsigned_t size = dynamicss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (dynamicss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_string_dynamicss_resize(size, dynamicss);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamicss_increase_

#ifndef _di_f_string_dynamicss_increase_by_
  f_status_t f_string_dynamicss_increase_by(const f_number_unsigned_t amount, f_string_dynamicss_t * const dynamicss) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamicss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (dynamicss->used + amount > dynamicss->size) {
      if (dynamicss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_dynamicss_resize(dynamicss->used + amount, dynamicss);
    }

    return F_data_not;
  }
#endif // _di_f_string_dynamicss_increase_by_

#ifndef _di_f_string_dynamicss_resize_
  f_status_t f_string_dynamicss_resize(const f_number_unsigned_t length, f_string_dynamicss_t * const dynamicss) {
    #ifndef _di_level_0_parameter_checking_
      if (!dynamicss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_dynamicss_resize(length, dynamicss);
  }
#endif // _di_f_string_dynamicss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

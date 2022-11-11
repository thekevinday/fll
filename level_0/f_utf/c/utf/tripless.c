#include "../utf.h"
#include "../private-utf.h"
#include "private-string.h"
#include "private-triples.h"
#include "private-tripless.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_tripless_append_
  f_status_t f_utf_string_tripless_append(const f_utf_string_triples_t source, f_utf_string_tripless_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_utf_string_tripless_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_utf_string_triples_append_all(source, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // _di_f_utf_string_tripless_append_

#ifndef _di_f_utf_string_tripless_append_all_
  f_status_t f_utf_string_tripless_append_all(const f_utf_string_tripless_t source, f_utf_string_tripless_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_utf_string_tripless_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_utf_string_triples_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_utf_string_tripless_append_all_

#ifndef _di_f_utf_string_tripless_adjust_
  f_status_t f_utf_string_tripless_adjust(const f_array_length_t length, f_utf_string_tripless_t * const tripless) {
    #ifndef _di_level_0_parameter_checking_
      if (!tripless) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_tripless_adjust(length, tripless);
  }
#endif // _di_f_utf_string_tripless_adjust_

#ifndef _di_f_utf_string_tripless_decimate_by_
  f_status_t f_utf_string_tripless_decimate_by(const f_array_length_t amount, f_utf_string_tripless_t * const tripless) {
    #ifndef _di_level_0_parameter_checking_
      if (!tripless) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (tripless->size > amount) {
      return private_f_utf_string_tripless_adjust(tripless->size - amount, tripless);
    }

    return private_f_utf_string_tripless_adjust(0, tripless);
  }
#endif // _di_f_utf_string_tripless_decimate_by_

#ifndef _di_f_utf_string_tripless_decrease_by_
  f_status_t f_utf_string_tripless_decrease_by(const f_array_length_t amount, f_utf_string_tripless_t * const tripless) {
    #ifndef _di_level_0_parameter_checking_
      if (!tripless) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (tripless->size > amount) {
      return private_f_utf_string_tripless_resize(tripless->size - amount, tripless);
    }

    return private_f_utf_string_tripless_resize(0, tripless);
  }
#endif // _di_f_utf_string_tripless_decrease_by_

#ifndef _di_f_utf_string_tripless_increase_
  f_status_t f_utf_string_tripless_increase(const f_array_length_t step, f_utf_string_tripless_t * const tripless) {
    #ifndef _di_level_0_parameter_checking_
      if (!tripless) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && tripless->used + 1 > tripless->size) {
      f_array_length_t size = tripless->used + step;

      if (size > F_array_length_t_size_d) {
        if (tripless->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_utf_string_tripless_resize(size, tripless);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_tripless_increase_

#ifndef _di_f_utf_string_tripless_increase_by_
  f_status_t f_utf_string_tripless_increase_by(const f_array_length_t amount, f_utf_string_tripless_t * const tripless) {
    #ifndef _di_level_0_parameter_checking_
      if (!tripless) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (tripless->used + amount > tripless->size) {
      if (tripless->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_utf_string_tripless_resize(tripless->used + amount, tripless);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_tripless_increase_by_

#ifndef _di_f_utf_string_tripless_resize_
  f_status_t f_utf_string_tripless_resize(const f_array_length_t length, f_utf_string_tripless_t * const tripless) {
    #ifndef _di_level_0_parameter_checking_
      if (!tripless) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_tripless_resize(length, tripless);
  }
#endif // _di_f_utf_string_tripless_resize_

#ifdef __cplusplus
} // extern "C"
#endif

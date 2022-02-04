#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_triples_adjust_
  f_status_t f_string_triples_adjust(const f_array_length_t length, f_string_triples_t * const triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_triples_adjust(length, triples);
  }
#endif // _di_f_string_triples_adjust_

#ifndef _di_f_string_triples_append_
  f_status_t f_string_triples_append(const f_string_triples_t source, f_string_triples_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) {
      return F_data_not;
    }

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_triples_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].one.used = 0;
      destination->array[destination->used].two.used = 0;
      destination->array[destination->used].three.used = 0;

      if (source.array[i].one.used) {
        status = private_f_string_append(source.array[i].one.string, source.array[i].one.used, &destination->array[destination->used].one);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].two.used) {
        status = private_f_string_append(source.array[i].two.string, source.array[i].two.used, &destination->array[destination->used].two);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].three.used) {
        status = private_f_string_append(source.array[i].three.string, source.array[i].three.used, &destination->array[destination->used].three);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_string_triples_append_

#ifndef _di_f_string_triples_decimate_by_
  f_status_t f_string_triples_decimate_by(const f_array_length_t amount, f_string_triples_t * const triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (triples->size - amount > 0) {
      return private_f_string_triples_adjust(triples->size - amount, triples);
    }

    return private_f_string_triples_adjust(0, triples);
  }
#endif // _di_f_string_triples_decimate_by_

#ifndef _di_f_string_triples_decrease_by_
  f_status_t f_string_triples_decrease_by(const f_array_length_t amount, f_string_triples_t * const triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (triples->size - amount > 0) {
      return private_f_string_triples_resize(triples->size - amount, triples);
    }

    return private_f_string_triples_resize(0, triples);
  }
#endif // _di_f_string_triples_decrease_by_

#ifndef _di_f_string_triples_increase_
  f_status_t f_string_triples_increase(const uint16_t step, f_string_triples_t * const triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (triples->used + 1 > triples->size) {
      f_array_length_t size = triples->used + F_memory_default_allocation_small_d;

      if (size > F_array_length_t_size_d) {
        if (triples->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_string_triples_resize(size, triples);
    }

    return F_data_not;
  }
#endif // _di_f_string_triples_increase_

#ifndef _di_f_string_triples_increase_by_
  f_status_t f_string_triples_increase_by(const f_array_length_t amount, f_string_triples_t * const triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (triples->used + amount > triples->size) {
      if (triples->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_triples_resize(triples->used + amount, triples);
    }

    return F_data_not;
  }
#endif // _di_f_string_triples_increase_by_

#ifndef _di_f_string_triples_resize_
  f_status_t f_string_triples_resize(const f_array_length_t length, f_string_triples_t * const triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_triples_resize(length, triples);
  }
#endif // _di_f_string_triples_resize_

#ifdef __cplusplus
} // extern "C"
#endif

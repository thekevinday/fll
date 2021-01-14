#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_triples_adjust_
  f_status_t f_string_triples_adjust(const f_string_length_t length, f_string_triples_t *triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_triples_adjust(length, triples);
  }
#endif // _di_f_string_triples_adjust_

#ifndef _di_f_string_triples_decimate_by_
  f_status_t f_string_triples_decimate_by(const f_array_length_t amount, f_string_triples_t *triples) {
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
  f_status_t f_string_triples_decrease_by(const f_array_length_t amount, f_string_triples_t *triples) {
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
  f_status_t f_string_triples_increase(f_string_triples_t *triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (triples->used + 1 > triples->size) {
      f_array_length_t size = triples->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (triples->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_triples_resize(size, triples);
    }

    return F_data_not;
  }
#endif // _di_f_string_triples_increase_

#ifndef _di_f_string_triples_increase_by_
  f_status_t f_string_triples_increase_by(const f_array_length_t amount, f_string_triples_t *triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (triples->used + amount > triples->size) {
      if (triples->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_triples_resize(triples->used + amount, triples);
    }

    return F_data_not;
  }
#endif // _di_f_string_triples_increase_by_

#ifndef _di_f_string_triples_resize_
  f_status_t f_string_triples_resize(const f_string_length_t length, f_string_triples_t *triples) {
    #ifndef _di_level_0_parameter_checking_
      if (!triples) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_triples_resize(length, triples);
  }
#endif // _di_f_string_triples_resize_

#ifdef __cplusplus
} // extern "C"
#endif

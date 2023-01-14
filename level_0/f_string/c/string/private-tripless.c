#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-triples.h"
#include "private-tripless.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)
  f_status_t private_f_string_tripless_adjust(const f_array_length_t length, f_string_tripless_t * const tripless) {

    if (tripless->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < tripless->size; ++i) {

      status = private_f_string_triples_adjust(0, &tripless->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(tripless->size, length, sizeof(f_string_triples_t), (void **) & tripless->array);
    if (F_status_is_error(status)) return status;

    tripless->size = length;

    if (tripless->used > tripless->size) {
      tripless->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)

#if !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_)
  f_status_t private_f_string_tripless_resize(const f_array_length_t length, f_string_tripless_t * const tripless) {

    if (tripless->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < tripless->size; ++i) {

      status = private_f_string_triples_resize(0, &tripless->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(tripless->size, length, sizeof(f_string_triples_t), (void **) & tripless->array);
    if (F_status_is_error(status)) return status;

    tripless->size = length;

    if (tripless->used > tripless->size) {
      tripless->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

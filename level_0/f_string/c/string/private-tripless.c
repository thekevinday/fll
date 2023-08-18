#include "../string.h"
#include "../private-string.h"
#include "private-triples.h"
#include "private-tripless.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)
  f_status_t private_f_string_tripless_adjust(const f_number_unsigned_t length, f_string_tripless_t * const structure) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_string_triples_adjust(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_triples_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)

#if !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_)
  f_status_t private_f_string_tripless_resize(const f_number_unsigned_t length, f_string_tripless_t * const structure) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_string_triples_resize(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_triples_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

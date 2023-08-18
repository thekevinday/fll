#include "../string.h"
#include "../private-string.h"
#include "private-ranges.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_)
  f_status_t private_f_string_ranges_append_all(const f_string_ranges_t source, f_string_ranges_t * const destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_string_range_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start = source.array[i].start;
      destination->array[destination->used++].stop = source.array[i].stop;
    } // for

    return F_okay;
  }
#endif // !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

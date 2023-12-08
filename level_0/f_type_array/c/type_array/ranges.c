#include "../type_array.h"
#include "ranges.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_ranges_append_
  f_status_t f_ranges_append(const f_range_t source, f_ranges_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_range_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].start = source.start;
    destination->array[destination->used++].stop = source.stop;

    return F_okay;
  }
#endif // _di_f_ranges_append_

#ifndef _di_f_ranges_append_all_
  f_status_t f_ranges_append_all(const f_ranges_t source, f_ranges_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_range_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start = source.array[i].start;
      destination->array[destination->used++].stop = source.array[i].stop;
    } // for

    return F_okay;
  }
#endif // _di_f_ranges_append_all_

#ifdef __cplusplus
} // extern "C"
#endif
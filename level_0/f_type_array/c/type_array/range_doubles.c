#include "../type_array.h"
#include "range_doubles.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_range_doubles_append_
  f_status_t f_range_doubles_append(const f_range_double_t source, f_range_doubles_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_range_double_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].start_1 = source.start_1;
    destination->array[destination->used].stop_1 = source.stop_1;
    destination->array[destination->used].start_2 = source.start_2;
    destination->array[destination->used++].stop_2 = source.stop_2;

    return F_okay;
  }
#endif // _di_f_range_doubles_append_

#ifndef _di_f_range_doubles_append_all_
  f_status_t f_range_doubles_append_all(const f_range_doubles_t source, f_range_doubles_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_range_double_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start_1 = source.array[i].start_1;
      destination->array[destination->used].stop_1 = source.array[i].stop_1;
      destination->array[destination->used].start_2 = source.array[i].start_2;
      destination->array[destination->used++].stop_2 = source.array[i].stop_2;
    } // for

    return F_okay;
  }
#endif // _di_f_range_doubles_append_all_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../string.h"
#include "../private-string.h"
#include "private-ranges.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_ranges_adjust_
  f_status_t f_string_ranges_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_string_range_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_ranges_adjust_

#ifndef _di_f_string_ranges_append_
  f_status_t f_string_ranges_append(const f_string_range_t source, f_string_ranges_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_range_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].start = source.start;
    destination->array[destination->used++].stop = source.stop;

    return F_none;
  }
#endif // _di_f_string_ranges_append_

#ifndef _di_f_string_ranges_append_all_
  f_status_t f_string_ranges_append_all(const f_string_ranges_t source, f_string_ranges_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_string_range_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start = source.array[i].start;
      destination->array[destination->used++].stop = source.array[i].stop;
    } // for

    return F_none;
  }
#endif // _di_f_string_ranges_append_all_

#ifndef _di_f_string_ranges_decimate_by_
  f_status_t f_string_ranges_decimate_by(const f_number_unsigned_t amount, f_string_ranges_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return f_memory_array_decimate_by(amount, sizeof(f_string_range_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_ranges_decimate_by_

#ifndef _di_f_string_ranges_decrease_by_
  f_status_t f_string_ranges_decrease_by(const f_number_unsigned_t amount, f_string_ranges_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_string_range_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_ranges_decrease_by_

#ifndef _di_f_string_ranges_increase_
  f_status_t f_string_ranges_increase(const f_number_unsigned_t step, f_string_ranges_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_string_range_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_ranges_increase_

#ifndef _di_f_string_ranges_increase_by_
  f_status_t f_string_ranges_increase_by(const f_number_unsigned_t amount, f_string_ranges_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_string_range_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_ranges_increase_by_

#ifndef _di_f_string_ranges_resize_
  f_status_t f_string_ranges_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_string_range_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_ranges_resize_

#ifdef __cplusplus
} // extern "C"
#endif

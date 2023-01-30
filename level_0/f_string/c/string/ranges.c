#include "../string.h"
#include "../private-string.h"
#include "private-ranges.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_ranges_adjust_
  f_status_t f_string_ranges_adjust(const f_array_length_t length, f_string_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_ranges_adjust(length, ranges);
  }
#endif // _di_f_string_ranges_adjust_

#ifndef _di_f_string_ranges_append_
  f_status_t f_string_ranges_append(const f_string_range_t source, f_string_ranges_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_string_ranges_resize(destination->used + F_memory_default_allocation_small_d, destination);
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

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_string_ranges_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start = source.array[i].start;
      destination->array[destination->used++].stop = source.array[i].stop;
    } // for

    return F_none;
  }
#endif // _di_f_string_ranges_append_all_

#ifndef _di_f_string_ranges_decimate_by_
  f_status_t f_string_ranges_decimate_by(const f_array_length_t amount, f_string_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (ranges->size > amount) {
      return private_f_string_ranges_adjust(ranges->size - amount, ranges);
    }

    return private_f_string_ranges_adjust(0, ranges);
  }
#endif // _di_f_string_ranges_decimate_by_

#ifndef _di_f_string_ranges_decrease_by_
  f_status_t f_string_ranges_decrease_by(const f_array_length_t amount, f_string_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (ranges->size > amount) {
      return private_f_string_ranges_resize(ranges->size - amount, ranges);
    }

    return private_f_string_ranges_resize(0, ranges);
  }
#endif // _di_f_string_ranges_decrease_by_

#ifndef _di_f_string_ranges_increase_
  f_status_t f_string_ranges_increase(const f_array_length_t step, f_string_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && ranges->used + 1 > ranges->size) {
      f_array_length_t size = ranges->used + step;

      if (size > F_array_length_t_size_d) {
        if (ranges->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_string_ranges_resize(size, ranges);
    }

    return F_data_not;
  }
#endif // _di_f_string_ranges_increase_

#ifndef _di_f_string_ranges_increase_by_
  f_status_t f_string_ranges_increase_by(const f_array_length_t amount, f_string_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (ranges->used + amount > ranges->size) {
      if (ranges->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_ranges_resize(ranges->used + amount, ranges);
    }

    return F_data_not;
  }
#endif // _di_f_string_ranges_increase_by_

#ifndef _di_f_string_ranges_resize_
  f_status_t f_string_ranges_resize(const f_array_length_t length, f_string_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_ranges_resize(length, ranges);
  }
#endif // _di_f_string_ranges_resize_

#ifdef __cplusplus
} // extern "C"
#endif
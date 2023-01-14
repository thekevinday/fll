#include "../string.h"
#include "../private-string.h"
#include "private-range.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_ranges_adjust_) || !defined(_di_f_string_ranges_decimate_by_)
  f_status_t private_f_string_ranges_adjust(const f_array_length_t length, f_string_ranges_t * const ranges) {

    if (ranges->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_adjust(ranges->size, length, sizeof(f_string_range_t), (void **) & ranges->array);
    if (F_status_is_error(status)) return status;

    ranges->size = length;

    if (ranges->used > ranges->size) {
      ranges->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_ranges_adjust_) || !defined(_di_f_string_ranges_decimate_by_)

#if !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_)
  f_status_t private_f_string_ranges_append_all(const f_string_ranges_t source, f_string_ranges_t * const destination) {

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
#endif // !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_)

#if !defined(_di_f_string_ranges_append_) || !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_resize_)
  f_status_t private_f_string_ranges_resize(const f_array_length_t length, f_string_ranges_t * const ranges) {

    if (ranges->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_resize(ranges->size, length, sizeof(f_string_range_t), (void **) & ranges->array);
    if (F_status_is_error(status)) return status;

    ranges->size = length;

    if (ranges->used > ranges->size) {
      ranges->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_ranges_append_) || !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_resize_)

#if !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)
  f_status_t private_f_string_rangess_adjust(const f_array_length_t length, f_string_rangess_t * const rangess) {

    if (rangess->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < rangess->size; ++i) {

      status = private_f_string_ranges_adjust(0, &rangess->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(rangess->size, length, sizeof(f_string_ranges_t), (void **) & rangess->array);
    if (F_status_is_error(status)) return status;

    rangess->size = length;

    if (rangess->used > rangess->size) {
      rangess->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)

#if !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_) || !defined(_di_f_string_rangess_resize_)
  f_status_t private_f_string_rangess_resize(const f_array_length_t length, f_string_rangess_t * const rangess) {

    if (rangess->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < rangess->size; ++i) {

      status = private_f_string_ranges_resize(0, &rangess->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(rangess->size, length, sizeof(f_string_ranges_t), (void **) & rangess->array);
    if (F_status_is_error(status)) return status;

    rangess->size = length;

    if (rangess->used > rangess->size) {
      rangess->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_) || !defined(_di_f_string_rangess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

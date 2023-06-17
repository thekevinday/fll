#include "../string.h"
#include "../private-string.h"
#include "private-ranges.h"
#include "private-rangess.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)
  f_status_t private_f_string_rangess_adjust(const f_number_unsigned_t length, f_string_rangess_t * const rangess) {

    if (rangess->used + length > F_number_t_size_unsigned_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < rangess->size; ++i) {

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

#if !defined(_di_f_string_ranges_append_) || !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_resize_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_)
  f_status_t private_f_string_rangess_resize(const f_number_unsigned_t length, f_string_rangess_t * const rangess) {

    if (rangess->used + length > F_number_t_size_unsigned_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < rangess->size; ++i) {

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
#endif // !defined(_di_f_string_ranges_append_) || !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_resize_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

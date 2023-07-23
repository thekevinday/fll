#include "../string.h"
#include "../private-string.h"
#include "private-ranges.h"
#include "private-rangess.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)
  f_status_t private_f_string_rangess_adjust(const f_number_unsigned_t length, f_string_rangess_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_ranges_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)

#if !defined(_di_f_string_ranges_append_) || !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_resize_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_)
  f_status_t private_f_string_rangess_resize(const f_number_unsigned_t length, f_string_rangess_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_ranges_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_ranges_append_) || !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_resize_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_) || !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

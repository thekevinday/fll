#include "../fss.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)
  f_status_t private_f_fss_set_adjust(const f_number_unsigned_t length, f_fss_set_t * const set) {

    f_status_t status = f_string_ranges_adjust(length, &set->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_adjust(length, &set->contents);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)

#if !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)
  f_status_t private_f_fss_set_resize(const f_number_unsigned_t length, f_fss_set_t *set) {

    f_status_t status = f_string_ranges_resize(length, &set->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_resize(length, &set->contents);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)

#if !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)
  f_status_t private_f_fss_sets_adjust(const f_number_unsigned_t length, f_fss_sets_t * const sets) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < sets->size; ++i) {

        status = f_string_ranges_adjust(0, &sets->array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_adjust(0, &sets->array[i].contents);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_fss_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)

#if !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_resize_)
  f_status_t private_f_fss_sets_resize(const f_number_unsigned_t length, f_fss_sets_t * const sets) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < sets->size; ++i) {

        status = f_string_ranges_resize(0, &sets->array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_resize(0, &sets->array[i].contents);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_fss_set_t), (void **) &sets->array, &sets->used, &sets->size);
  }
#endif // !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

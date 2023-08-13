#include "../fss.h"
#include "private-named.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  f_status_t private_f_fss_named_adjust(const f_number_unsigned_t length, f_fss_named_t * const named) {

    f_status_t status = f_string_ranges_adjust(length, &named->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_adjust(length, &named->contents);
    if (F_status_is_error(status)) return status;

    status = f_memory_arrays_adjust(length, sizeof(f_uint8s_t), (void **) &named->quotess.array, &named->quotess.used, &named->quotess.size, &f_uint8s_delete_callback);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_named_increase_) || !defined(_di_f_fss_named_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_named_resize(const f_number_unsigned_t length, f_fss_named_t * const named) {

    f_status_t status = f_string_ranges_resize(length, &named->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_resize(length, &named->contents);
    if (F_status_is_error(status)) return status;

    status = f_memory_arrays_resize(length, sizeof(f_uint8s_t), (void **) &named->quotess.array, &named->quotess.used, &named->quotess.size, &f_uint8s_delete_callback);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_named_increase_) || !defined(_di_f_fss_named_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  f_status_t private_f_fss_nameds_adjust(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) {

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < nameds->size; ++i) {

        status = private_f_fss_named_adjust(0, &nameds->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_fss_named_t), (void **) &nameds->array, &nameds->used, &nameds->size);
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_nameds_resize(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) {

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < nameds->size; ++i) {

        status = private_f_fss_named_resize(0, &nameds->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_fss_named_t), (void **) &nameds->array, &nameds->used, &nameds->size);
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

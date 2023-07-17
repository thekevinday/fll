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

    status = f_uint8ss_adjust(length, &named->quotess);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_named_resize(const f_number_unsigned_t length, f_fss_named_t * const named) {

    f_status_t status = f_string_ranges_resize(length, &named->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_resize(length, &named->contents);
    if (F_status_is_error(status)) return status;

    status = f_uint8ss_resize(length, &named->quotess);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  f_status_t private_f_fss_nameds_adjust(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < nameds->size; ++i) {

      status = private_f_fss_named_adjust(0, &nameds->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(nameds->size, length, sizeof(f_fss_named_t), (void **) & nameds->array);
    if (F_status_is_error(status)) return status;

    nameds->size = length;

    if (nameds->used > nameds->size) {
      nameds->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_nameds_resize(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < nameds->size; ++i) {

      status = private_f_fss_named_resize(0, &nameds->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(nameds->size, length, sizeof(f_fss_named_t), (void **) & nameds->array);
    if (F_status_is_error(status)) return status;

    nameds->size = length;

    if (nameds->used > nameds->size) {
      nameds->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

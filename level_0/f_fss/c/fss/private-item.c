#include "../fss.h"
#include "private-item.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_) || !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)
  f_status_t private_f_fss_items_adjust(const f_number_unsigned_t length, f_fss_items_t * const items) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < items->size; ++i) {

      status = f_string_ranges_adjust(0, &items->array[i].content);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_fss_item_t), (void **) &items->array, &items->used, &items->size);
  }
#endif // !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_) || !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)

#if !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_resize_) || !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_resize_)
  f_status_t private_f_fss_items_resize(const f_number_unsigned_t length, f_fss_items_t * const items) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < items->size; ++i) {

      status = f_string_ranges_resize(0, &items->array[i].content);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_fss_item_t), (void **) &items->array, &items->used, &items->size);
  }
#endif // !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_resize_) || !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

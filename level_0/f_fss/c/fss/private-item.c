#include "../fss.h"
#include "private-item.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_)
  f_status_t private_f_fss_items_adjust(const f_number_unsigned_t length, f_fss_items_t * const items) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < items->size; ++i) {

      status = f_string_ranges_adjust(0, &items->array[i].content);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(items->size, length, sizeof(f_fss_item_t), (void **) & items->array);
    if (F_status_is_error(status)) return status;

    items->size = length;

    if (items->used > items->size) {
      items->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_)

#if !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)
  f_status_t private_f_fss_items_resize(const f_number_unsigned_t length, f_fss_items_t * const items) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < items->size; ++i) {

      status = f_string_ranges_resize(0, &items->array[i].content);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(items->size, length, sizeof(f_fss_item_t), (void **) & items->array);
    if (F_status_is_error(status)) return status;

    items->size = length;

    if (items->used > items->size) {
      items->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../string.h"
#include "../private-string.h"
#include "private-quantitys.h"
#include "private-quantityss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_quantityss_adjust_) || !defined(_di_f_string_quantityss_decimate_by_)
  f_status_t private_f_string_quantityss_adjust(const f_number_unsigned_t length, f_string_quantityss_t * const quantityss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < quantityss->size; ++i) {

      status = f_memory_array_adjust(length, sizeof(f_string_quantitys_t), (void **) &quantityss->array[i].array, &quantityss->array[i].used, &quantityss->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_quantitys_t), (void **) &quantityss->array, &quantityss->used, &quantityss->size);
  }
#endif // !defined(_di_f_string_quantityss_adjust_) || !defined(_di_f_string_quantityss_decimate_by_)

#if !defined(_di_f_string_quantityss_decrease_by_) || !defined(_di_f_string_quantityss_increase_) || !defined(_di_f_string_quantityss_increase_by_)
  f_status_t private_f_string_quantityss_resize(const f_number_unsigned_t length, f_string_quantityss_t * const quantityss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < quantityss->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_string_quantity_t), (void **) &quantityss->array[i].array, &quantityss->array[i].used, &quantityss->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_quantitys_t), (void **) &quantityss->array, &quantityss->used, &quantityss->size);
  }
#endif // !defined(_di_f_string_quantityss_decrease_by_) || !defined(_di_f_string_quantityss_increase_) || !defined(_di_f_string_quantityss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

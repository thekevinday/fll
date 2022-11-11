#include "../string.h"
#include "../private-string.h"
#include "private-quantitys.h"
#include "private-quantityss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_quantityss_adjust_) || !defined(_di_f_string_quantityss_decimate_by_)
  f_status_t private_f_string_quantityss_adjust(const f_array_length_t length, f_string_quantityss_t * const quantityss) {

    if (quantityss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < quantityss->size; ++i) {

      status = private_f_string_quantitys_adjust(0, &quantityss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(quantityss->size, length, sizeof(f_string_quantitys_t), (void **) & quantityss->array);
    if (F_status_is_error(status)) return status;

    quantityss->size = length;

    if (quantityss->used > quantityss->size) {
      quantityss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_quantityss_adjust_) || !defined(_di_f_string_quantityss_decimate_by_)

#if !defined(_di_f_string_quantityss_decrease_) || !defined(_di_f_string_quantityss_decrease_by_) || !defined(_di_f_string_quantityss_increase_) || !defined(_di_f_string_quantityss_increase_by_) || !defined(_di_f_string_quantityss_terminate_) || !defined(_di_f_string_quantityss_terminate_after_)
  f_status_t private_f_string_quantityss_resize(const f_array_length_t length, f_string_quantityss_t * const quantityss) {

    if (quantityss->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < quantityss->size; ++i) {

      status = private_f_string_quantitys_resize(0, &quantityss->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(quantityss->size, length, sizeof(f_string_quantitys_t), (void **) & quantityss->array);
    if (F_status_is_error(status)) return status;

    quantityss->size = length;

    if (quantityss->used > quantityss->size) {
      quantityss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_quantityss_decrease_) || !defined(_di_f_string_quantityss_decrease_by_) || !defined(_di_f_string_quantityss_increase_) || !defined(_di_f_string_quantityss_increase_by_) || !defined(_di_f_string_quantityss_terminate_) || !defined(_di_f_string_quantityss_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

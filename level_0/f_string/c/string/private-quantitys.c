#include "../string.h"
#include "../private-string.h"
#include "private-quantitys.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_quantitys_adjust_) || !defined(_di_f_string_quantitys_decimate_by_)
  f_status_t private_f_string_quantitys_adjust(const f_array_length_t length, f_string_quantitys_t * const quantitys) {

    if (quantitys->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_adjust(quantitys->size, length, sizeof(f_string_quantity_t), (void **) & quantitys->array);
    if (F_status_is_error(status)) return status;

    quantitys->size = length;

    if (quantitys->used > quantitys->size) {
      quantitys->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_quantitys_adjust_) || !defined(_di_f_string_quantitys_decimate_by_)

#if !defined(_di_f_string_quantitys_append_all_) || !defined(_di_f_string_quantityss_append_) || !defined(_di_f_string_quantityss_append_all_)
  f_status_t private_f_string_quantitys_append_all(const f_string_quantitys_t source, f_string_quantitys_t * const destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_string_quantitys_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start = source.array[i].start;
      destination->array[destination->used++].total = source.array[i].total;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_quantitys_append_all_) || !defined(_di_f_string_quantityss_append_) || !defined(_di_f_string_quantityss_append_all_)

#if !defined(_di_f_string_quantitys_decrease_) || !defined(_di_f_string_quantitys_decrease_by_) || !defined(_di_f_string_quantitys_increase_) || !defined(_di_f_string_quantitys_increase_by_)
  f_status_t private_f_string_quantitys_resize(const f_array_length_t length, f_string_quantitys_t * const quantitys) {

    if (quantitys->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    const f_status_t status = f_memory_resize(quantitys->size, length, sizeof(f_string_quantity_t), (void **) & quantitys->array);
    if (F_status_is_error(status)) return status;

    quantitys->size = length;

    if (quantitys->used > quantitys->size) {
      quantitys->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_quantitys_decrease_) || !defined(_di_f_string_quantitys_decrease_by_) || !defined(_di_f_string_quantitys_increase_) || !defined(_di_f_string_quantitys_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

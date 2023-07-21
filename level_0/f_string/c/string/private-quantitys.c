#include "../string.h"
#include "../private-string.h"
#include "private-quantitys.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_quantitys_append_all_) || !defined(_di_f_string_quantityss_append_) || !defined(_di_f_string_quantityss_append_all_)
  f_status_t private_f_string_quantitys_append_all(const f_string_quantitys_t source, f_string_quantitys_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_string_quantity_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].start = source.array[i].start;
      destination->array[destination->used++].total = source.array[i].total;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_quantitys_append_all_) || !defined(_di_f_string_quantityss_append_) || !defined(_di_f_string_quantityss_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

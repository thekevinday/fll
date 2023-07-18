#include "../limit.h"
#include "set.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_setss_append_)
  extern f_status_t private_f_limit_sets_append(const f_limit_set_t source, f_limit_sets_t *destination) {

    const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_limit_set_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_setss_append_)

#if !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_sets_append_all_) || !defined(_di_f_limit_setss_append_all_)
  extern f_status_t private_f_limit_sets_append_all(const f_limit_sets_t source, f_limit_sets_t *destination) {

    const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_limit_set_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_limit_sets_append_) || !defined(_di_f_limit_sets_append_all_) || !defined(_di_f_limit_setss_append_all_)

#if !defined(_di_f_limit_setss_adjust_) || !defined(_di_f_limit_setss_decimate_by_)
  f_status_t private_f_limit_setss_adjust(const f_number_unsigned_t length, f_limit_setss_t *setss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < setss->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_limit_set_t), (void **) &setss->array[i].array, &setss->array[i].used, &setss->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_limit_sets_t), (void **) &setss->array, &setss->used, &setss->size);
  }
#endif // !defined(_di_f_limit_setss_adjust_) || !defined(_di_f_limit_setss_decimate_by_)

#if !defined(_di_f_limit_setss_decrease_by_) || !defined(_di_f_limit_setss_increase_) || !defined(_di_f_limit_setss_increase_by_) || !defined(_di_f_limit_setss_resize_)
  f_status_t private_f_limit_setss_resize(const f_number_unsigned_t length, f_limit_setss_t *setss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < setss->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_limit_set_t), (void **) &setss->array[i].array, &setss->array[i].used, &setss->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_limit_sets_t), (void **) &setss->array, &setss->used, &setss->size);
  }
#endif // !defined(_di_f_limit_setss_decrease_by_) || !defined(_di_f_limit_setss_increase_) || !defined(_di_f_limit_setss_increase_by_) || !defined(_di_f_limit_setss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

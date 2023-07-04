#include "../type_array.h"
#include "private-number_unsigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_number_unsigneds_adjust_) || !defined(_di_f_number_unsigneds_decimate_by_)
  f_status_t private_f_number_unsigneds_adjust(const f_number_unsigned_t length, f_number_unsigneds_t * const number_unsigneds) {

    const f_status_t status = f_memory_adjust(number_unsigneds->size, length, sizeof(f_number_unsigned_t), (void **) & number_unsigneds->array);
    if (F_status_is_error(status)) return status;

    number_unsigneds->size = length;

    if (number_unsigneds->used > number_unsigneds->size) {
      number_unsigneds->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_number_unsigneds_adjust_) || !defined(_di_f_number_unsigneds_decimate_by_)

#if !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsignedss_append_)
  extern f_status_t private_f_number_unsigneds_append(const f_number_unsigned_t source, f_number_unsigneds_t * const destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_number_unsigneds_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsignedss_append_)

#if !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_append_all_) || !defined(_di_f_number_unsignedss_append_all_)
  extern f_status_t private_f_number_unsigneds_append_all(const f_number_unsigneds_t source, f_number_unsigneds_t * const destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_number_unsigneds_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_append_all_) || !defined(_di_f_number_unsignedss_append_all_)

#if !defined(_di_f_number_unsigneds_resize_) || !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_decrease_by_) || !defined(_di_f_number_unsignedss_append_)
  f_status_t private_f_number_unsigneds_resize(const f_number_unsigned_t length, f_number_unsigneds_t * const lengths) {

    const f_status_t status = f_memory_resize(lengths->size, length, sizeof(f_number_unsigned_t), (void **) & lengths->array);
    if (F_status_is_error(status)) return status;

    lengths->size = length;

    if (lengths->used > lengths->size) {
      lengths->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_number_unsigneds_resize_) || !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_decrease_by_) || !defined(_di_f_number_unsignedss_append_)

#if !defined(_di_f_number_unsignedss_adjust_) || !defined(_di_f_number_unsignedss_decimate_by_)
  f_status_t private_f_number_unsignedss_adjust(const f_number_unsigned_t length, f_number_unsignedss_t * const lengthss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < lengthss->size; ++i) {

      status = f_memory_destroy(lengthss->array[i].size, sizeof(f_number_unsigneds_t), (void **) & lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      lengthss->array[i].size = 0;
      lengthss->array[i].used = 0;
    } // for

    status = f_memory_adjust(lengthss->size, length, sizeof(f_number_unsigneds_t), (void **) & lengthss->array);
    if (F_status_is_error(status)) return status;

    lengthss->size = length;

    if (lengthss->used > lengthss->size) {
      lengthss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_number_unsignedss_adjust_) || !defined(_di_f_number_unsignedss_decimate_by_)

#if !defined(_di_f_number_unsignedss_decrease_by_) || !defined(_di_f_number_unsignedss_increase_) || !defined(_di_f_number_unsignedss_increase_by_) || !defined(_di_f_number_unsignedss_resize_)
  f_status_t private_f_number_unsignedss_resize(const f_number_unsigned_t length, f_number_unsignedss_t * const lengthss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < lengthss->size; ++i) {

      status = f_memory_delete(lengthss->array[i].size, sizeof(f_number_unsigneds_t), (void **) & lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      lengthss->array[i].size = 0;
      lengthss->array[i].used = 0;
    } // for

    status = f_memory_resize(lengthss->size, length, sizeof(f_number_unsigneds_t), (void **) & lengthss->array);
    if (F_status_is_error(status)) return status;

    lengthss->size = length;

    if (lengthss->used > lengthss->size) {
      lengthss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_number_unsignedss_decrease_by_) || !defined(_di_f_number_unsignedss_increase_) || !defined(_di_f_number_unsignedss_increase_by_) || !defined(_di_f_number_unsignedss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../type_array.h"
#include "private-uint16.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_uint16s_adjust_) || !defined(_di_f_uint16s_decimate_by_)
  f_status_t private_f_uint16s_adjust(const f_number_unsigned_t length, f_uint16s_t * const uint16s) {

    const f_status_t status = f_memory_adjust(uint16s->size, length, sizeof(uint16_t), (void **) & uint16s->array);
    if (F_status_is_error(status)) return status;

    uint16s->size = length;

    if (uint16s->used > uint16s->size) {
      uint16s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint16s_adjust_) || !defined(_di_f_uint16s_decimate_by_)

#if !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16ss_append_)
  extern f_status_t private_f_uint16s_append(const uint16_t source, f_uint16s_t * const destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_uint16s_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16ss_append_)

#if !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_append_all_) || !defined(_di_f_uint16ss_append_all_)
  extern f_status_t private_f_uint16s_append_all(const f_uint16s_t source, f_uint16s_t * const destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_uint16s_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_append_all_) || !defined(_di_f_uint16ss_append_all_)

#if !defined(_di_f_uint16s_resize_) || !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_decrease_by_) || !defined(_di_f_uint16ss_append_)
  f_status_t private_f_uint16s_resize(const f_number_unsigned_t length, f_uint16s_t * const uint16s) {

    const f_status_t status = f_memory_resize(uint16s->size, length, sizeof(uint16_t), (void **) & uint16s->array);
    if (F_status_is_error(status)) return status;

    uint16s->size = length;

    if (uint16s->used > uint16s->size) {
      uint16s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint16s_resize_) || !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_decrease_by_) || !defined(_di_f_uint16ss_append_)

#if !defined(_di_f_uint16ss_adjust_) || !defined(_di_f_uint16ss_decimate_by_)
  f_status_t private_f_uint16ss_adjust(const f_number_unsigned_t length, f_uint16ss_t * const uint16ss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_destroy(uint16ss->array[i].size, sizeof(f_uint16s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint16ss->size, length, sizeof(f_uint16s_t), (void **) & uint16ss->array);
    if (F_status_is_error(status)) return status;

    uint16ss->size = length;

    if (uint16ss->used > uint16ss->size) {
      uint16ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint16ss_adjust_) || !defined(_di_f_uint16ss_decimate_by_)

#if !defined(_di_f_uint16ss_decrease_by_) || !defined(_di_f_uint16ss_increase_) || !defined(_di_f_uint16ss_increase_by_) || !defined(_di_f_uint16ss_resize_)
  f_status_t private_f_uint16ss_resize(const f_number_unsigned_t length, f_uint16ss_t * const uint16ss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_delete(uint16ss->array[i].size, sizeof(f_uint16s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint16ss->size, length, sizeof(f_uint16s_t), (void **) & uint16ss->array);
    if (F_status_is_error(status)) return status;

    uint16ss->size = length;

    if (uint16ss->used > uint16ss->size) {
      uint16ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint16ss_decrease_by_) || !defined(_di_f_uint16ss_increase_) || !defined(_di_f_uint16ss_increase_by_) || !defined(_di_f_uint16ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

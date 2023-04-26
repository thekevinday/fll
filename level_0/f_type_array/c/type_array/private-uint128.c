#include "../type_array.h"
#include "private-uint128.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_uint128s_adjust_) || !defined(_di_f_uint128s_decimate_by_)
  f_status_t private_f_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s) {

    const f_status_t status = f_memory_adjust(uint128s->size, length, sizeof(f_uint128s_t), (void **) & uint128s->array);
    if (F_status_is_error(status)) return status;

    uint128s->size = length;

    if (uint128s->used > uint128s->size) {
      uint128s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint128s_adjust_) || !defined(_di_f_uint128s_decimate_by_)

#if !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128ss_append_)
  extern f_status_t private_f_uint128s_append(const uint128_t source, f_uint128s_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_uint128s_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128ss_append_)

#if !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_append_all_) || !defined(_di_f_uint128ss_append_all_)
  extern f_status_t private_f_uint128s_append_all(const f_uint128s_t source, f_uint128s_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_uint128s_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_append_all_) || !defined(_di_f_uint128ss_append_all_)

#if !defined(_di_f_uint128s_resize_) || !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_decrease_by_) || !defined(_di_f_uint128ss_append_)
  f_status_t private_f_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) {

    const f_status_t status = f_memory_resize(uint128s->size, length, sizeof(f_uint128s_t), (void **) & uint128s->array);
    if (F_status_is_error(status)) return status;

    uint128s->size = length;

    if (uint128s->used > uint128s->size) {
      uint128s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint128s_resize_) || !defined(_di_f_uint128s_append_) || !defined(_di_f_uint128s_decrease_by_) || !defined(_di_f_uint128ss_append_)

#if !defined(_di_f_uint128ss_adjust_) || !defined(_di_f_uint128ss_decimate_by_)
  f_status_t private_f_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint128ss->size; ++i) {

      status = f_memory_destroy(uint128ss->array[i].size, sizeof(f_uint128s_t), (void **) & uint128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint128ss->array[i].size = 0;
      uint128ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint128ss->size, length, sizeof(f_uint128s_t), (void **) & uint128ss->array);
    if (F_status_is_error(status)) return status;

    uint128ss->size = length;

    if (uint128ss->used > uint128ss->size) {
      uint128ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint128ss_adjust_) || !defined(_di_f_uint128ss_decimate_by_)

#if !defined(_di_f_uint128ss_decrease_by_) || !defined(_di_f_uint128ss_increase_) || !defined(_di_f_uint128ss_increase_by_) || !defined(_di_f_uint128ss_resize_)
  f_status_t private_f_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint128ss->size; ++i) {

      status = f_memory_delete(uint128ss->array[i].size, sizeof(f_uint128s_t), (void **) & uint128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint128ss->array[i].size = 0;
      uint128ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint128ss->size, length, sizeof(f_uint128s_t), (void **) & uint128ss->array);
    if (F_status_is_error(status)) return status;

    uint128ss->size = length;

    if (uint128ss->used > uint128ss->size) {
      uint128ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint128ss_decrease_by_) || !defined(_di_f_uint128ss_increase_) || !defined(_di_f_uint128ss_increase_by_) || !defined(_di_f_uint128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

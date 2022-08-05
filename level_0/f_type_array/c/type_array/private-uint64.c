#include "../type_array.h"
#include "private-uint64.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_uint64s_adjust_) || !defined(_di_f_uint64s_decimate_by_)
  f_status_t private_f_uint64s_adjust(const f_array_length_t length, f_uint64s_t *uint64s) {

    const f_status_t status = f_memory_adjust(uint64s->size, length, sizeof(uint64_t), (void **) & uint64s->array);
    if (F_status_is_error(status)) return status;

    uint64s->size = length;

    if (uint64s->used > uint64s->size) {
      uint64s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint64s_adjust_) || !defined(_di_f_uint64s_decimate_by_)

#if !defined(_di_f_uint64s_append_) || !defined(_di_f_uint64ss_append_)
  extern f_status_t private_f_uint64s_append(const uint64_t source, f_uint64s_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_uint64s_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_uint64s_append_) || !defined(_di_f_uint64ss_append_)

#if !defined(_di_f_uint64s_append_) || !defined(_di_f_uint64s_append_all_) || !defined(_di_f_uint64ss_append_all_)
  extern f_status_t private_f_uint64s_append_all(const f_uint64s_t source, f_uint64s_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_uint64s_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_uint64s_append_) || !defined(_di_f_uint64s_append_all_) || !defined(_di_f_uint64ss_append_all_)

#if !defined(_di_f_uint64s_resize_) || !defined(_di_f_uint64s_append_) || !defined(_di_f_uint64s_decimate_by_) || !defined(_di_f_uint64ss_append_)
  f_status_t private_f_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s) {

    const f_status_t status = f_memory_resize(uint64s->size, length, sizeof(uint64_t), (void **) & uint64s->array);
    if (F_status_is_error(status)) return status;

    uint64s->size = length;

    if (uint64s->used > uint64s->size) {
      uint64s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint64s_resize_) || !defined(_di_f_uint64s_append_) || !defined(_di_f_uint64s_decimate_by_) || !defined(_di_f_uint64ss_append_)

#if !defined(_di_f_uint64ss_adjust_) || !defined(_di_f_uint64ss_decimate_by_)
  f_status_t private_f_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint64ss->size; ++i) {

      status = f_memory_destroy(uint64ss->array[i].size, sizeof(f_uint64s_t), (void **) & uint64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint64ss->array[i].size = 0;
      uint64ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint64ss->size, length, sizeof(f_uint64s_t), (void **) & uint64ss->array);
    if (F_status_is_error(status)) return status;

    uint64ss->size = length;

    if (uint64ss->used > uint64ss->size) {
      uint64ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint64ss_adjust_) || !defined(_di_f_uint64ss_decimate_by_)

#if !defined(_di_f_uint64ss_decrease_by_) || !defined(_di_f_uint64ss_increase_) || !defined(_di_f_uint64ss_increase_by_) || !defined(_di_f_uint64ss_resize_)
  f_status_t private_f_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint64ss->size; ++i) {

      status = f_memory_delete(uint64ss->array[i].size, sizeof(f_uint64s_t), (void **) & uint64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint64ss->array[i].size = 0;
      uint64ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint64ss->size, length, sizeof(f_uint64s_t), (void **) & uint64ss->array);
    if (F_status_is_error(status)) return status;

    uint64ss->size = length;

    if (uint64ss->used > uint64ss->size) {
      uint64ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint64ss_decrease_by_) || !defined(_di_f_uint64ss_increase_) || !defined(_di_f_uint64ss_increase_by_) || !defined(_di_f_uint64ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

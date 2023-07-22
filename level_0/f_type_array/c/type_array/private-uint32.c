#include "../type_array.h"
#include "private-uint32.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_uint32s_adjust_) || !defined(_di_f_uint32s_decimate_by_)
  f_status_t private_f_uint32s_adjust(const f_array_length_t length, f_uint32s_t *uint32s) {

    const f_status_t status = f_memory_adjust(uint32s->size, length, sizeof(uint32_t), (void **) & uint32s->array);
    if (F_status_is_error(status)) return status;

    uint32s->size = length;

    if (uint32s->used > uint32s->size) {
      uint32s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint32s_adjust_) || !defined(_di_f_uint32s_decimate_by_)

#if !defined(_di_f_uint32s_append_) || !defined(_di_f_uint32ss_append_)
  extern f_status_t private_f_uint32s_append(const uint32_t source, f_uint32s_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_uint32s_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_uint32s_append_) || !defined(_di_f_uint32ss_append_)

#if !defined(_di_f_uint32s_append_) || !defined(_di_f_uint32s_append_all_) || !defined(_di_f_uint32ss_append_all_)
  extern f_status_t private_f_uint32s_append_all(const f_uint32s_t source, f_uint32s_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_uint32s_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_uint32s_append_) || !defined(_di_f_uint32s_append_all_) || !defined(_di_f_uint32ss_append_all_)

#if !defined(_di_f_uint32s_resize_) || !defined(_di_f_uint32s_append_) || !defined(_di_f_uint32s_decimate_by_) || !defined(_di_f_uint32ss_append_)
  f_status_t private_f_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s) {

    const f_status_t status = f_memory_resize(uint32s->size, length, sizeof(uint32_t), (void **) & uint32s->array);
    if (F_status_is_error(status)) return status;

    uint32s->size = length;

    if (uint32s->used > uint32s->size) {
      uint32s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint32s_resize_) || !defined(_di_f_uint32s_append_) || !defined(_di_f_uint32s_decimate_by_) || !defined(_di_f_uint32ss_append_)

#if !defined(_di_f_uint32ss_adjust_) || !defined(_di_f_uint32ss_decimate_by_)
  f_status_t private_f_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint32ss->size; ++i) {

      status = f_memory_destroy(uint32ss->array[i].size, sizeof(uint32_t), (void **) & uint32ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint32ss->array[i].size = 0;
      uint32ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint32ss->size, length, sizeof(f_uint32s_t), (void **) & uint32ss->array);
    if (F_status_is_error(status)) return status;

    uint32ss->size = length;

    if (uint32ss->used > uint32ss->size) {
      uint32ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint32ss_adjust_) || !defined(_di_f_uint32ss_decimate_by_)

#if !defined(_di_f_uint32ss_decrease_by_) || !defined(_di_f_uint32ss_increase_) || !defined(_di_f_uint32ss_increase_by_) || !defined(_di_f_uint32ss_resize_)
  f_status_t private_f_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint32ss->size; ++i) {

      status = f_memory_delete(uint32ss->array[i].size, sizeof(uint32_t), (void **) & uint32ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint32ss->array[i].size = 0;
      uint32ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint32ss->size, length, sizeof(f_uint32s_t), (void **) & uint32ss->array);
    if (F_status_is_error(status)) return status;

    uint32ss->size = length;

    if (uint32ss->used > uint32ss->size) {
      uint32ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_uint32ss_decrease_by_) || !defined(_di_f_uint32ss_increase_) || !defined(_di_f_uint32ss_increase_by_) || !defined(_di_f_uint32ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

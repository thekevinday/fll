#include "../type_array.h"
#include "private-int64.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_int64s_adjust_) || !defined(_di_f_int64s_decimate_by_)
  f_status_t private_f_int64s_adjust(const f_array_length_t length, f_int64s_t *int64s) {

    const f_status_t status = f_memory_adjust(int64s->size, length, sizeof(int64_t), (void **) & int64s->array);
    if (F_status_is_error(status)) return status;

    int64s->size = length;

    if (int64s->used > int64s->size) {
      int64s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int64s_adjust_) || !defined(_di_f_int64s_decimate_by_)

#if !defined(_di_f_int64s_append_) || !defined(_di_f_int64ss_append_)
  extern f_status_t private_f_int64s_append(const int64_t source, f_int64s_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_int64s_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_int64s_append_) || !defined(_di_f_int64ss_append_)

#if !defined(_di_f_int64s_append_) || !defined(_di_f_int64s_append_all_) || !defined(_di_f_int64ss_append_all_)
  extern f_status_t private_f_int64s_append_all(const f_int64s_t source, f_int64s_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_int64s_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_int64s_append_) || !defined(_di_f_int64s_append_all_) || !defined(_di_f_int64ss_append_all_)

#if !defined(_di_f_int64s_resize_) || !defined(_di_f_int64s_append_) || !defined(_di_f_int64s_decimate_by_) || !defined(_di_f_int64ss_append_)
  f_status_t private_f_int64s_resize(const f_array_length_t length, f_int64s_t *int64s) {

    const f_status_t status = f_memory_resize(int64s->size, length, sizeof(int64_t), (void **) & int64s->array);
    if (F_status_is_error(status)) return status;

    int64s->size = length;

    if (int64s->used > int64s->size) {
      int64s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int64s_resize_) || !defined(_di_f_int64s_append_) || !defined(_di_f_int64s_decimate_by_) || !defined(_di_f_int64ss_append_)

#if !defined(_di_f_int64ss_adjust_) || !defined(_di_f_int64ss_decimate_by_)
  f_status_t private_f_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int64ss->size; ++i) {

      status = f_memory_destroy(int64ss->array[i].size, sizeof(f_int64s_t), (void **) & int64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int64ss->array[i].size = 0;
      int64ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int64ss->size, length, sizeof(f_int64s_t), (void **) & int64ss->array);
    if (F_status_is_error(status)) return status;

    int64ss->size = length;

    if (int64ss->used > int64ss->size) {
      int64ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int64ss_adjust_) || !defined(_di_f_int64ss_decimate_by_)

#if !defined(_di_f_int64ss_decrease_by_) || !defined(_di_f_int64ss_increase_) || !defined(_di_f_int64ss_increase_by_) || !defined(_di_f_int64ss_resize_)
  f_status_t private_f_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int64ss->size; ++i) {

      status = f_memory_delete(int64ss->array[i].size, sizeof(f_int64s_t), (void **) & int64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int64ss->array[i].size = 0;
      int64ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int64ss->size, length, sizeof(f_int64s_t), (void **) & int64ss->array);
    if (F_status_is_error(status)) return status;

    int64ss->size = length;

    if (int64ss->used > int64ss->size) {
      int64ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int64ss_decrease_by_) || !defined(_di_f_int64ss_increase_) || !defined(_di_f_int64ss_increase_by_) || !defined(_di_f_int64ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

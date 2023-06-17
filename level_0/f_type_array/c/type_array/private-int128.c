#include "../type_array.h"
#include "private-int128.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_int128s_adjust_) || !defined(_di_f_int128s_decimate_by_)
  f_status_t private_f_int128s_adjust(const f_number_unsigned_t length, f_int128s_t *int128s) {

    const f_status_t status = f_memory_adjust(int128s->size, length, sizeof(f_int128s_t), (void **) & int128s->array);
    if (F_status_is_error(status)) return status;

    int128s->size = length;

    if (int128s->used > int128s->size) {
      int128s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int128s_adjust_) || !defined(_di_f_int128s_decimate_by_)

#if !defined(_di_f_int128s_append_) || !defined(_di_f_int128ss_append_)
  extern f_status_t private_f_int128s_append(const int128_t source, f_int128s_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_int128s_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_int128s_append_) || !defined(_di_f_int128ss_append_)

#if !defined(_di_f_int128s_append_) || !defined(_di_f_int128s_append_all_) || !defined(_di_f_int128ss_append_all_)
  extern f_status_t private_f_int128s_append_all(const f_int128s_t source, f_int128s_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_int128s_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_int128s_append_) || !defined(_di_f_int128s_append_all_) || !defined(_di_f_int128ss_append_all_)

#if !defined(_di_f_int128s_resize_) || !defined(_di_f_int128s_append_) || !defined(_di_f_int128s_decrease_by_) || !defined(_di_f_int128ss_append_)
  f_status_t private_f_int128s_resize(const f_number_unsigned_t length, f_int128s_t *int128s) {

    const f_status_t status = f_memory_resize(int128s->size, length, sizeof(f_int128s_t), (void **) & int128s->array);
    if (F_status_is_error(status)) return status;

    int128s->size = length;

    if (int128s->used > int128s->size) {
      int128s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int128s_resize_) || !defined(_di_f_int128s_append_) || !defined(_di_f_int128s_decrease_by_) || !defined(_di_f_int128ss_append_)

#if !defined(_di_f_int128ss_adjust_) || !defined(_di_f_int128ss_decimate_by_)
  f_status_t private_f_int128ss_adjust(const f_number_unsigned_t length, f_int128ss_t *int128ss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < int128ss->size; ++i) {

      status = f_memory_destroy(int128ss->array[i].size, sizeof(f_int128s_t), (void **) & int128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int128ss->array[i].size = 0;
      int128ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int128ss->size, length, sizeof(f_int128s_t), (void **) & int128ss->array);
    if (F_status_is_error(status)) return status;

    int128ss->size = length;

    if (int128ss->used > int128ss->size) {
      int128ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int128ss_adjust_) || !defined(_di_f_int128ss_decimate_by_)

#if !defined(_di_f_int128ss_decrease_by_) || !defined(_di_f_int128ss_increase_) || !defined(_di_f_int128ss_increase_by_) || !defined(_di_f_int128ss_resize_)
  f_status_t private_f_int128ss_resize(const f_number_unsigned_t length, f_int128ss_t *int128ss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < int128ss->size; ++i) {

      status = f_memory_delete(int128ss->array[i].size, sizeof(f_int128s_t), (void **) & int128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int128ss->array[i].size = 0;
      int128ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int128ss->size, length, sizeof(f_int128s_t), (void **) & int128ss->array);
    if (F_status_is_error(status)) return status;

    int128ss->size = length;

    if (int128ss->used > int128ss->size) {
      int128ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int128ss_decrease_by_) || !defined(_di_f_int128ss_increase_) || !defined(_di_f_int128ss_increase_by_) || !defined(_di_f_int128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

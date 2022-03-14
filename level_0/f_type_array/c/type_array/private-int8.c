#include "../type_array.h"
#include "private-int8.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_int8s_adjust_) || !defined(_di_f_int8s_decimate_by_)
  f_status_t private_f_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s) {

    const f_status_t status = f_memory_adjust(int8s->size, length, sizeof(int8_t), (void **) & int8s->array);
    if (F_status_is_error(status)) return status;

    int8s->size = length;

    if (int8s->used > int8s->size) {
      int8s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int8s_adjust_) || !defined(_di_f_int8s_decimate_by_)

#if !defined(_di_f_int8s_append_) || !defined(_di_f_int8ss_append_)
  extern f_status_t private_f_int8s_append(const int8_t source, f_int8s_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_int8s_adjust(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_int8s_append_) || !defined(_di_f_int8ss_append_)

#if !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_append_all_) || !defined(_di_f_int8ss_append_all_)
  extern f_status_t private_f_int8s_append_all(const f_int8s_t source, f_int8s_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_int8s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_append_all_) || !defined(_di_f_int8ss_append_all_)

#if !defined(_di_f_int8s_resize_) || !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_decimate_by_) || !defined(_di_f_int8ss_append_)
  f_status_t private_f_int8s_resize(const f_array_length_t length, f_int8s_t *int8s) {

    const f_status_t status = f_memory_resize(int8s->size, length, sizeof(int8_t), (void **) & int8s->array);
    if (F_status_is_error(status)) return status;

    int8s->size = length;

    if (int8s->used > int8s->size) {
      int8s->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int8s_resize_) || !defined(_di_f_int8s_append_) || !defined(_di_f_int8s_decimate_by_) || !defined(_di_f_int8ss_append_)

#if !defined(_di_f_int8ss_adjust_) || !defined(_di_f_int8ss_decimate_by_)
  f_status_t private_f_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int8ss->size; ++i) {

      status = f_memory_destroy(int8ss->array[i].size, sizeof(f_int8s_t), (void **) & int8ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int8ss->array[i].size = 0;
      int8ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int8ss->size, length, sizeof(f_int8s_t), (void **) & int8ss->array);
    if (F_status_is_error(status)) return status;

    int8ss->size = length;

    if (int8ss->used > int8ss->size) {
      int8ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int8ss_adjust_) || !defined(_di_f_int8ss_decimate_by_)

#if !defined(_di_f_int8ss_decrease_by_) || !defined(_di_f_int8ss_increase_) || !defined(_di_f_int8ss_increase_by_) || !defined(_di_f_int8ss_resize_)
  f_status_t private_f_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int8ss->size; ++i) {

      status = f_memory_delete(int8ss->array[i].size, sizeof(f_int8s_t), (void **) & int8ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int8ss->array[i].size = 0;
      int8ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int8ss->size, length, sizeof(f_int8s_t), (void **) & int8ss->array);
    if (F_status_is_error(status)) return status;

    int8ss->size = length;

    if (int8ss->used > int8ss->size) {
      int8ss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_int8ss_decrease_by_) || !defined(_di_f_int8ss_increase_) || !defined(_di_f_int8ss_increase_by_) || !defined(_di_f_int8ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

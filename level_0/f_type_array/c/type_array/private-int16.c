#include "../type_array.h"
#include "private-int16.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_int16s_adjust_) || !defined(_di_f_int16s_decimate_by_)
  f_status_t private_f_int16s_adjust(const f_array_length_t length, f_int16s_t *int16s) {

    const f_status_t status = f_memory_adjust(int16s->size, length, sizeof(int16_t), (void **) & int16s->array);

    if (F_status_is_error_not(status)) {
      int16s->size = length;

      if (int16s->used > int16s->size) {
        int16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_int16s_adjust_) || !defined(_di_f_int16s_decimate_by_)

#if !defined(_di_f_int16s_append_) || !defined(_di_f_int16ss_append_)
  extern f_status_t private_f_int16s_append(const f_int16s_t source, f_int16s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_int16s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_int16s_append_) || !defined(_di_f_int16ss_append_)

#if !defined(_di_f_int16s_resize_) || !defined(_di_f_int16s_append_) || !defined(_di_f_int16s_decimate_by_) || !defined(_di_f_int16ss_append_)
  f_status_t private_f_int16s_resize(const f_array_length_t length, f_int16s_t *int16s) {

    const f_status_t status = f_memory_resize(int16s->size, length, sizeof(int16_t), (void **) & int16s->array);

    if (F_status_is_error_not(status)) {
      int16s->size = length;

      if (int16s->used > int16s->size) {
        int16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_int16s_resize_) || !defined(_di_f_int16s_append_) || !defined(_di_f_int16s_decimate_by_) || !defined(_di_f_int16ss_append_)

#if !defined(_di_f_int16ss_adjust_) || !defined(_di_f_int16ss_decimate_by_)
  f_status_t private_f_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int16ss->size; ++i) {

      status = f_memory_destroy(int16ss->array[i].size, sizeof(f_int16s_t), (void **) & int16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int16ss->array[i].size = 0;
      int16ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int16ss->size, length, sizeof(f_int16s_t), (void **) & int16ss->array);

    if (F_status_is_error_not(status)) {
      int16ss->size = length;

      if (int16ss->used > int16ss->size) {
        int16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_int16ss_adjust_) || !defined(_di_f_int16ss_decimate_by_)

#if !defined(_di_f_int16ss_decrease_by_) || !defined(_di_f_int16ss_increase_) || !defined(_di_f_int16ss_increase_by_) || !defined(_di_f_int16ss_resize_)
  f_status_t private_f_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int16ss->size; ++i) {

      status = f_memory_delete(int16ss->array[i].size, sizeof(f_int16s_t), (void **) & int16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int16ss->array[i].size = 0;
      int16ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int16ss->size, length, sizeof(f_int16s_t), (void **) & int16ss->array);

    if (F_status_is_error_not(status)) {
      int16ss->size = length;

      if (int16ss->used > int16ss->size) {
        int16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_int16ss_decrease_by_) || !defined(_di_f_int16ss_increase_) || !defined(_di_f_int16ss_increase_by_) || !defined(_di_f_int16ss_resize_)

#if !defined(_di_f_uint16s_adjust_) || !defined(_di_f_uint16s_decimate_by_)
  f_status_t private_f_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s) {

    const f_status_t status = f_memory_adjust(uint16s->size, length, sizeof(uint16_t), (void **) & uint16s->array);

    if (F_status_is_error_not(status)) {
      uint16s->size = length;

      if (uint16s->used > uint16s->size) {
        uint16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_uint16s_adjust_) || !defined(_di_f_uint16s_decimate_by_)

#if !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16ss_append_)
  extern f_status_t private_f_uint16s_append(const f_uint16s_t source, f_uint16s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint16s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16ss_append_)

#if !defined(_di_f_uint16s_resize_) || !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_decimate_by_) || !defined(_di_f_uint16ss_append_)
  f_status_t private_f_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) {

    const f_status_t status = f_memory_resize(uint16s->size, length, sizeof(uint16_t), (void **) & uint16s->array);

    if (F_status_is_error_not(status)) {
      uint16s->size = length;

      if (uint16s->used > uint16s->size) {
        uint16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_uint16s_resize_) || !defined(_di_f_uint16s_append_) || !defined(_di_f_uint16s_decimate_by_) || !defined(_di_f_uint16ss_append_)

#if !defined(_di_f_uint16ss_adjust_) || !defined(_di_f_uint16ss_decimate_by_)
  f_status_t private_f_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_destroy(uint16ss->array[i].size, sizeof(f_uint16s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint16ss->size, length, sizeof(f_uint16s_t), (void **) & uint16ss->array);

    if (F_status_is_error_not(status)) {
      uint16ss->size = length;

      if (uint16ss->used > uint16ss->size) {
        uint16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_uint16ss_adjust_) || !defined(_di_f_uint16ss_decimate_by_)

#if !defined(_di_f_uint16ss_decrease_by_) || !defined(_di_f_uint16ss_increase_) || !defined(_di_f_uint16ss_increase_by_) || !defined(_di_f_uint16ss_resize_)
  f_status_t private_f_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_delete(uint16ss->array[i].size, sizeof(f_uint16s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint16ss->size, length, sizeof(f_uint16s_t), (void **) & uint16ss->array);

    if (F_status_is_error_not(status)) {
      uint16ss->size = length;

      if (uint16ss->used > uint16ss->size) {
        uint16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_uint16ss_decrease_by_) || !defined(_di_f_uint16ss_increase_) || !defined(_di_f_uint16ss_increase_by_) || !defined(_di_f_uint16ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../type_array.h"
#include "private-array_length.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_array_lengths_adjust_) || !defined(_di_f_array_lengths_decimate_by_)
  f_status_t private_f_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *array_lengths) {

    const f_status_t status = f_memory_adjust(array_lengths->size, length, sizeof(f_array_length_t), (void **) & array_lengths->array);

    if (F_status_is_error_not(status)) {
      array_lengths->size = length;

      if (array_lengths->used > array_lengths->size) {
        array_lengths->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_array_lengths_adjust_) || !defined(_di_f_array_lengths_decimate_by_)

#if !defined(_di_f_array_lengths_append_) || !defined(_di_f_array_lengthss_append_)
  extern f_status_t private_f_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_array_lengths_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_array_lengths_append_) || !defined(_di_f_array_lengthss_append_)

#if !defined(_di_f_array_lengths_resize_) || !defined(_di_f_array_lengths_append_) || !defined(_di_f_array_lengths_decimate_by_) || !defined(_di_f_array_lengthss_append_)
  f_status_t private_f_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) {

    const f_status_t status = f_memory_resize(lengths->size, length, sizeof(f_array_length_t), (void **) & lengths->array);

    if (F_status_is_error_not(status)) {
      lengths->size = length;

      if (lengths->used > lengths->size) {
        lengths->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_array_lengths_resize_) || !defined(_di_f_array_lengths_append_) || !defined(_di_f_array_lengths_decimate_by_) || !defined(_di_f_array_lengthss_append_)

#if !defined(_di_f_array_lengthss_adjust_) || !defined(_di_f_array_lengthss_decimate_by_)
  f_status_t private_f_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < lengthss->size; ++i) {

      status = f_memory_destroy(lengthss->array[i].size, sizeof(f_array_lengths_t), (void **) & lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      lengthss->array[i].size = 0;
      lengthss->array[i].used = 0;
    } // for

    status = f_memory_adjust(lengthss->size, length, sizeof(f_array_lengths_t), (void **) & lengthss->array);

    if (F_status_is_error_not(status)) {
      lengthss->size = length;

      if (lengthss->used > lengthss->size) {
        lengthss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_array_lengthss_adjust_) || !defined(_di_f_array_lengthss_decimate_by_)

#if !defined(_di_f_array_lengthss_decrease_by_) || !defined(_di_f_array_lengthss_increase_) || !defined(_di_f_array_lengthss_increase_by_) || !defined(_di_f_array_lengthss_resize_)
  f_status_t private_f_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < lengthss->size; ++i) {

      status = f_memory_delete(lengthss->array[i].size, sizeof(f_array_lengths_t), (void **) & lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      lengthss->array[i].size = 0;
      lengthss->array[i].used = 0;
    } // for

    status = f_memory_resize(lengthss->size, length, sizeof(f_array_lengths_t), (void **) & lengthss->array);

    if (F_status_is_error_not(status)) {
      lengthss->size = length;

      if (lengthss->used > lengthss->size) {
        lengthss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_array_lengthss_decrease_by_) || !defined(_di_f_array_lengthss_increase_) || !defined(_di_f_array_lengthss_increase_by_) || !defined(_di_f_array_lengthss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

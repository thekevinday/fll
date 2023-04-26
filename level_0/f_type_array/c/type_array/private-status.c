#include "../type_array.h"
#include "private-status.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_statuss_adjust_) || !defined(_di_f_statuss_decimate_by_)
  f_status_t private_f_statuss_adjust(const f_array_length_t length, f_statuss_t *statuss) {

    const f_status_t status = f_memory_adjust(statuss->size, length, sizeof(f_status_t), (void **) & statuss->array);
    if (F_status_is_error(status)) return status;

    statuss->size = length;

    if (statuss->used > statuss->size) {
      statuss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_statuss_adjust_) || !defined(_di_f_statuss_decimate_by_)

#if !defined(_di_f_statuss_append_) || !defined(_di_f_statusss_append_)
  extern f_status_t private_f_statuss_append(const f_status_t source, f_statuss_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_statuss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_statuss_append_) || !defined(_di_f_statusss_append_)

#if !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_append_all_) || !defined(_di_f_statusss_append_all_)
  extern f_status_t private_f_statuss_append_all(const f_statuss_t source, f_statuss_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_statuss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_append_all_) || !defined(_di_f_statusss_append_all_)

#if !defined(_di_f_statuss_resize_) || !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_decrease_by_) || !defined(_di_f_statusss_append_)
  f_status_t private_f_statuss_resize(const f_array_length_t length, f_statuss_t *statuss) {

    const f_status_t status = f_memory_resize(statuss->size, length, sizeof(f_status_t), (void **) & statuss->array);
    if (F_status_is_error(status)) return status;

    statuss->size = length;

    if (statuss->used > statuss->size) {
      statuss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_statuss_resize_) || !defined(_di_f_statuss_append_) || !defined(_di_f_statuss_decrease_by_) || !defined(_di_f_statusss_append_)

#if !defined(_di_f_statusss_adjust_) || !defined(_di_f_statusss_decimate_by_)
  f_status_t private_f_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statusss->size; ++i) {

      status = f_memory_destroy(statusss->array[i].size, sizeof(f_statuss_t), (void **) & statusss->array[i].array);
      if (F_status_is_error(status)) return status;

      statusss->array[i].size = 0;
      statusss->array[i].used = 0;
    } // for

    status = f_memory_adjust(statusss->size, length, sizeof(f_statuss_t), (void **) & statusss->array);
    if (F_status_is_error(status)) return status;

    statusss->size = length;

    if (statusss->used > statusss->size) {
      statusss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_statusss_adjust_) || !defined(_di_f_statusss_decimate_by_)

#if !defined(_di_f_statusss_decrease_by_) || !defined(_di_f_statusss_increase_) || !defined(_di_f_statusss_increase_by_) || !defined(_di_f_statusss_resize_)
  f_status_t private_f_statusss_resize(const f_array_length_t length, f_statusss_t *statusss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statusss->size; ++i) {

      status = f_memory_delete(statusss->array[i].size, sizeof(f_statuss_t), (void **) & statusss->array[i].array);
      if (F_status_is_error(status)) return status;

      statusss->array[i].size = 0;
      statusss->array[i].used = 0;
    } // for

    status = f_memory_resize(statusss->size, length, sizeof(f_statuss_t), (void **) & statusss->array);
    if (F_status_is_error(status)) return status;

    statusss->size = length;

    if (statusss->used > statusss->size) {
      statusss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_statusss_decrease_by_) || !defined(_di_f_statusss_increase_) || !defined(_di_f_statusss_increase_by_) || !defined(_di_f_statusss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#include "../type_array.h"
#include "../type_array_file.h"
#include "private-poll.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_polls_adjust_) || !defined(_di_f_polls_decimate_by_)
  f_status_t private_f_polls_adjust(const f_number_unsigned_t length, f_polls_t *polls) {

    const f_status_t status = f_memory_adjust(polls->size, length, sizeof(f_poll_t), (void **) & polls->array);
    if (F_status_is_error(status)) return status;

    polls->size = length;

    if (polls->used > polls->size) {
      polls->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_polls_adjust_) || !defined(_di_f_polls_decimate_by_)

#if !defined(_di_f_polls_append_) || !defined(_di_f_pollss_append_)
  extern f_status_t private_f_polls_append(const f_poll_t source, f_polls_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_polls_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_polls_append_) || !defined(_di_f_pollss_append_)

#if !defined(_di_f_polls_append_) || !defined(_di_f_polls_append_all_) || !defined(_di_f_pollss_append_all_)
  extern f_status_t private_f_polls_append_all(const f_polls_t source, f_polls_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_polls_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_polls_append_) || !defined(_di_f_polls_append_all_) || !defined(_di_f_pollss_append_all_)

#if !defined(_di_f_polls_resize_) || !defined(_di_f_polls_append_) || !defined(_di_f_polls_decrease_by_) || !defined(_di_f_pollss_append_)
  f_status_t private_f_polls_resize(const f_number_unsigned_t length, f_polls_t *polls) {

    const f_status_t status = f_memory_resize(polls->size, length, sizeof(f_poll_t), (void **) & polls->array);
    if (F_status_is_error(status)) return status;

    polls->size = length;

    if (polls->used > polls->size) {
      polls->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_polls_resize_) || !defined(_di_f_polls_append_) || !defined(_di_f_polls_decrease_by_) || !defined(_di_f_pollss_append_)

#if !defined(_di_f_pollss_adjust_) || !defined(_di_f_pollss_decimate_by_)
  f_status_t private_f_pollss_adjust(const f_number_unsigned_t length, f_pollss_t *pollss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < pollss->size; ++i) {

      status = f_memory_destroy(pollss->array[i].size, sizeof(f_polls_t), (void **) & pollss->array[i].array);
      if (F_status_is_error(status)) return status;

      pollss->array[i].size = 0;
      pollss->array[i].used = 0;
    } // for

    status = f_memory_adjust(pollss->size, length, sizeof(f_polls_t), (void **) & pollss->array);
    if (F_status_is_error(status)) return status;

    pollss->size = length;

    if (pollss->used > pollss->size) {
      pollss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_pollss_adjust_) || !defined(_di_f_pollss_decimate_by_)

#if !defined(_di_f_pollss_decrease_by_) || !defined(_di_f_pollss_increase_) || !defined(_di_f_pollss_increase_by_) || !defined(_di_f_pollss_resize_)
  f_status_t private_f_pollss_resize(const f_number_unsigned_t length, f_pollss_t *pollss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < pollss->size; ++i) {

      status = f_memory_delete(pollss->array[i].size, sizeof(f_polls_t), (void **) & pollss->array[i].array);
      if (F_status_is_error(status)) return status;

      pollss->array[i].size = 0;
      pollss->array[i].used = 0;
    } // for

    status = f_memory_resize(pollss->size, length, sizeof(f_polls_t), (void **) & pollss->array);
    if (F_status_is_error(status)) return status;

    pollss->size = length;

    if (pollss->used > pollss->size) {
      pollss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_pollss_decrease_by_) || !defined(_di_f_pollss_increase_) || !defined(_di_f_pollss_increase_by_) || !defined(_di_f_pollss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

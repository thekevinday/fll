#include "../type_array.h"
#include "private-state.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_states_adjust_) || !defined(_di_f_states_decimate_by_)
  f_status_t private_f_states_adjust(const f_array_length_t length, f_states_t *states) {

    const f_status_t status = f_memory_adjust(states->size, length, sizeof(f_state_t), (void **) & states->array);

    if (F_status_is_error_not(status)) {
      states->size = length;

      if (states->used > states->size) {
        states->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_states_adjust_) || !defined(_di_f_states_decimate_by_)

#if !defined(_di_f_states_append_) || !defined(_di_f_statess_append_)
  extern f_status_t private_f_states_append(const f_states_t source, f_states_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_states_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_states_append_) || !defined(_di_f_statess_append_)

#if !defined(_di_f_states_resize_) || !defined(_di_f_states_append_) || !defined(_di_f_states_decimate_by_) || !defined(_di_f_statess_append_)
  f_status_t private_f_states_resize(const f_array_length_t length, f_states_t *states) {

    const f_status_t status = f_memory_resize(states->size, length, sizeof(f_state_t), (void **) & states->array);

    if (F_status_is_error_not(status)) {
      states->size = length;

      if (states->used > states->size) {
        states->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_states_resize_) || !defined(_di_f_states_append_) || !defined(_di_f_states_decimate_by_) || !defined(_di_f_statess_append_)

#if !defined(_di_f_statess_adjust_) || !defined(_di_f_statess_decimate_by_)
  f_status_t private_f_statess_adjust(const f_array_length_t length, f_statess_t *statess) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statess->size; ++i) {

      status = f_memory_destroy(statess->array[i].size, sizeof(f_states_t), (void **) & statess->array[i].array);
      if (F_status_is_error(status)) return status;

      statess->array[i].size = 0;
      statess->array[i].used = 0;
    } // for

    status = f_memory_adjust(statess->size, length, sizeof(f_states_t), (void **) & statess->array);

    if (F_status_is_error_not(status)) {
      statess->size = length;

      if (statess->used > statess->size) {
        statess->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_statess_adjust_) || !defined(_di_f_statess_decimate_by_)

#if !defined(_di_f_statess_decrease_by_) || !defined(_di_f_statess_increase_) || !defined(_di_f_statess_increase_by_) || !defined(_di_f_statess_resize_)
  f_status_t private_f_statess_resize(const f_array_length_t length, f_statess_t *statess) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statess->size; ++i) {

      status = f_memory_delete(statess->array[i].size, sizeof(f_states_t), (void **) & statess->array[i].array);
      if (F_status_is_error(status)) return status;

      statess->array[i].size = 0;
      statess->array[i].used = 0;
    } // for

    status = f_memory_resize(statess->size, length, sizeof(f_states_t), (void **) & statess->array);

    if (F_status_is_error_not(status)) {
      statess->size = length;

      if (statess->used > statess->size) {
        statess->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_statess_decrease_by_) || !defined(_di_f_statess_increase_) || !defined(_di_f_statess_increase_by_) || !defined(_di_f_statess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

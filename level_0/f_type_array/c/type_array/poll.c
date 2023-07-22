#include "../type_array.h"
#include "../type_array_file.h"
#include "poll.h"
#include "private-poll.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_polls_adjust_
  f_status_t f_polls_adjust(const f_number_unsigned_t length, f_polls_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_poll_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_polls_adjust_

#ifndef _di_f_polls_append_
  f_status_t f_polls_append(const f_poll_t source, f_polls_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_polls_append(source, destination);
  }
#endif // _di_f_polls_append_

#ifndef _di_f_polls_append_all_
  f_status_t f_polls_append_all(const f_polls_t source, f_polls_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_polls_append_all(source, destination);
  }
#endif // _di_f_polls_append_all_

#ifndef _di_f_polls_decimate_by_
  f_status_t f_polls_decimate_by(const f_number_unsigned_t amount, f_polls_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_poll_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_polls_decimate_by_

#ifndef _di_f_polls_decrease_by_
  f_status_t f_polls_decrease_by(const f_number_unsigned_t amount, f_polls_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_poll_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_polls_decrease_by_

#ifndef _di_f_polls_increase_
  f_status_t f_polls_increase(const f_number_unsigned_t step, f_polls_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_poll_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_polls_increase_

#ifndef _di_f_polls_increase_by_
  f_status_t f_polls_increase_by(const f_number_unsigned_t amount, f_polls_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_poll_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_polls_increase_by_

#ifndef _di_f_polls_resize_
  f_status_t f_polls_resize(const f_number_unsigned_t length, f_polls_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_poll_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_polls_resize_

#ifndef _di_f_pollss_adjust_
  f_status_t f_pollss_adjust(const f_number_unsigned_t length, f_pollss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_pollss_adjust(length, structure);
  }
#endif // _di_f_pollss_adjust_

#ifndef _di_f_pollss_append_
  f_status_t f_pollss_append(const f_polls_t source, f_pollss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_polls_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_polls_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_pollss_append_

#ifndef _di_f_pollss_append_all_
  f_status_t f_pollss_append_all(const f_pollss_t source, f_pollss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_polls_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_polls_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_pollss_append_all_

#ifndef _di_f_pollss_decimate_by_
  f_status_t f_pollss_decimate_by(const f_number_unsigned_t amount, f_pollss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_pollss_adjust((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_pollss_decimate_by_

#ifndef _di_f_pollss_decrease_by_
  f_status_t f_pollss_decrease_by(const f_number_unsigned_t amount, f_pollss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_pollss_resize((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_pollss_decrease_by_

#ifndef _di_f_pollss_increase_
  f_status_t f_pollss_increase(const f_number_unsigned_t step, f_pollss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_pollss_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_pollss_increase_

#ifndef _di_f_pollss_increase_by_
  f_status_t f_pollss_increase_by(const f_number_unsigned_t amount, f_pollss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_pollss_resize(structure->used + amount, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_pollss_increase_by_

#ifndef _di_f_pollss_resize_
  f_status_t f_pollss_resize(const f_number_unsigned_t length, f_pollss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_pollss_resize(length, structure);
  }
#endif // _di_f_pollss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

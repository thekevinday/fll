#include "../type_array.h"
#include "../type_array_file.h"
#include "poll.h"
#include "private-poll.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_polls_adjust_
  f_status_t f_polls_adjust(const f_number_unsigned_t length, f_polls_t * const polls) {
    #ifndef _di_level_0_parameter_checking_
      if (!polls) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_polls_adjust(length, polls);
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
  f_status_t f_polls_decimate_by(const f_number_unsigned_t amount, f_polls_t * const polls) {
    #ifndef _di_level_0_parameter_checking_
      if (!polls) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (polls->size - amount > 0) return private_f_polls_adjust(polls->size - amount, polls);

    return private_f_polls_adjust(0, polls);
  }
#endif // _di_f_polls_decimate_by_

#ifndef _di_f_polls_decrease_by_
  f_status_t f_polls_decrease_by(const f_number_unsigned_t amount, f_polls_t * const polls) {
    #ifndef _di_level_0_parameter_checking_
      if (!polls) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (polls->size - amount > 0) return private_f_polls_resize(polls->size - amount, polls);

    return private_f_polls_resize(0, polls);
  }
#endif // _di_f_polls_decrease_by_

#ifndef _di_f_polls_increase_
  f_status_t f_polls_increase(const f_number_unsigned_t step, f_polls_t * const polls) {
    #ifndef _di_level_0_parameter_checking_
      if (!polls) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && polls->used + 1 > polls->size) {
      f_number_unsigned_t size = polls->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (polls->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        size = F_number_t_size_unsigned_d;
      }

      return private_f_polls_resize(size, polls);
    }

    return F_data_not;
  }
#endif // _di_f_polls_increase_

#ifndef _di_f_polls_increase_by_
  f_status_t f_polls_increase_by(const f_number_unsigned_t amount, f_polls_t * const polls) {
    #ifndef _di_level_0_parameter_checking_
      if (!polls) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (polls->used + amount > polls->size) {
      if (polls->used + amount > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      return private_f_polls_resize(polls->used + amount, polls);
    }

    return F_data_not;
  }
#endif // _di_f_polls_increase_by_

#ifndef _di_f_polls_resize_
  f_status_t f_polls_resize(const f_number_unsigned_t length, f_polls_t * const polls) {
    #ifndef _di_level_0_parameter_checking_
      if (!polls) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_polls_resize(length, polls);
  }
#endif // _di_f_polls_resize_

#ifndef _di_f_pollss_adjust_
  f_status_t f_pollss_adjust(const f_number_unsigned_t length, f_pollss_t * const pollss) {
    #ifndef _di_level_0_parameter_checking_
      if (!pollss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_pollss_adjust(length, pollss);
  }
#endif // _di_f_pollss_adjust_

#ifndef _di_f_pollss_append_
  f_status_t f_pollss_append(const f_polls_t source, f_pollss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_pollss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

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

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_pollss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

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
  f_status_t f_pollss_decimate_by(const f_number_unsigned_t amount, f_pollss_t * const pollss) {
    #ifndef _di_level_0_parameter_checking_
      if (!pollss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (pollss->size - amount > 0) return private_f_pollss_adjust(pollss->size - amount, pollss);

    return private_f_pollss_adjust(0, pollss);
  }
#endif // _di_f_pollss_decimate_by_

#ifndef _di_f_pollss_decrease_by_
  f_status_t f_pollss_decrease_by(const f_number_unsigned_t amount, f_pollss_t * const pollss) {
    #ifndef _di_level_0_parameter_checking_
      if (!pollss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (pollss->size - amount > 0) return private_f_pollss_resize(pollss->size - amount, pollss);

    return private_f_pollss_resize(0, pollss);
  }
#endif // _di_f_pollss_decrease_by_

#ifndef _di_f_pollss_increase_
  f_status_t f_pollss_increase(const f_number_unsigned_t step, f_pollss_t * const pollss) {
    #ifndef _di_level_0_parameter_checking_
      if (!pollss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && pollss->used + 1 > pollss->size) {
      f_number_unsigned_t size = pollss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (pollss->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        size = F_number_t_size_unsigned_d;
      }

      return private_f_pollss_resize(size, pollss);
    }

    return F_data_not;
  }
#endif // _di_f_pollss_increase_

#ifndef _di_f_pollss_increase_by_
  f_status_t f_pollss_increase_by(const f_number_unsigned_t amount, f_pollss_t * const pollss) {
    #ifndef _di_level_0_parameter_checking_
      if (!pollss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (pollss->used + amount > pollss->size) {
      if (pollss->used + amount > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      return private_f_pollss_resize(pollss->used + amount, pollss);
    }

    return F_data_not;
  }
#endif // _di_f_pollss_increase_by_

#ifndef _di_f_pollss_resize_
  f_status_t f_pollss_resize(const f_number_unsigned_t length, f_pollss_t * const pollss) {
    #ifndef _di_level_0_parameter_checking_
      if (!pollss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_pollss_resize(length, pollss);
  }
#endif // _di_f_pollss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

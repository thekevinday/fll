#include "../thread.h"
#include "../private-thread.h"
#include "set.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_sets_adjust_
  f_status_t f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_sets_adjust(length, sets);
  }
#endif // _di_f_thread_sets_adjust_

#ifndef _di_f_thread_sets_decimate_by_
  f_status_t f_thread_sets_decimate_by(const f_array_length_t amount, f_thread_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sets->size > amount) {
      return private_f_thread_sets_adjust(sets->size - amount, sets);
    }

    return private_f_thread_sets_adjust(0, sets);
  }
#endif // _di_f_thread_sets_decimate_by_

#ifndef _di_f_thread_sets_decrease_by_
  f_status_t f_thread_sets_decrease_by(const f_array_length_t amount, f_thread_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sets->size > amount) {
      return private_f_thread_sets_resize(sets->size - amount, sets);
    }

    return private_f_thread_sets_resize(0, sets);
  }
#endif // _di_f_thread_sets_decrease_by_

#ifndef _di_f_thread_sets_increase_
  f_status_t f_thread_sets_increase(const f_array_length_t step, f_thread_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && sets->used + 1 > sets->size) {
      f_array_length_t size = sets->used + step;

      if (size > F_array_length_t_size_d) {
        if (sets->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_thread_sets_resize(size, sets);
    }

    return F_data_not;
  }
#endif // _di_f_thread_sets_increase_

#ifndef _di_f_thread_sets_increase_by_
  f_status_t f_thread_sets_increase_by(const f_array_length_t amount, f_thread_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sets->used + amount > sets->size) {
      if (sets->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_sets_resize(sets->used + amount, sets);
    }

    return F_data_not;
  }
#endif // _di_f_thread_sets_increase_by_

#ifndef _di_f_thread_sets_resize_
  f_status_t f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t * const sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_sets_resize(length, sets);
  }
#endif // _di_f_thread_sets_resize_

#ifdef __cplusplus
} // extern "C"
#endif

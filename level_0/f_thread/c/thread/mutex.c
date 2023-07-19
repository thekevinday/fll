#include "../thread.h"
#include "../private-thread.h"
#include "mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_mutexs_adjust_
  f_status_t f_thread_mutexs_adjust(const f_number_unsigned_t length, f_thread_mutexs_t * const mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutexs_adjust(length, mutexs);
  }
#endif // _di_f_thread_mutexs_adjust_

#ifndef _di_f_thread_mutexs_decimate_by_
  f_status_t f_thread_mutexs_decimate_by(const f_number_unsigned_t amount, f_thread_mutexs_t * const mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (mutexs->size > amount) {
      return private_f_thread_mutexs_adjust(mutexs->size - amount, mutexs);
    }

    return private_f_thread_mutexs_adjust(0, mutexs);
  }
#endif // _di_f_thread_mutexs_decimate_by_

#ifndef _di_f_thread_mutexs_decrease_by_
  f_status_t f_thread_mutexs_decrease_by(const f_number_unsigned_t amount, f_thread_mutexs_t * const mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (mutexs->size > amount) {
      return private_f_thread_mutexs_resize(mutexs->size - amount, mutexs);
    }

    return private_f_thread_mutexs_resize(0, mutexs);
  }
#endif // _di_f_thread_mutexs_decrease_by_

#ifndef _di_f_thread_mutexs_increase_
  f_status_t f_thread_mutexs_increase(const f_number_unsigned_t step, f_thread_mutexs_t * const mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && mutexs->used + 1 > mutexs->size) {
      f_number_unsigned_t size = mutexs->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (mutexs->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_mutexs_resize(size, mutexs);
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutexs_increase_

#ifndef _di_f_thread_mutexs_increase_by_
  f_status_t f_thread_mutexs_increase_by(const f_number_unsigned_t amount, f_thread_mutexs_t * const mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (mutexs->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = mutexs->used + amount;

      if (length > mutexs->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_mutexs_resize(length, mutexs);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutexs_increase_by_

#ifndef _di_f_thread_mutexs_resize_
  f_status_t f_thread_mutexs_resize(const f_number_unsigned_t length, f_thread_mutexs_t * const mutexs) {
    #ifndef _di_level_0_parameter_checking_
      if (!mutexs) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_mutexs_resize(length, mutexs);
  }
#endif // _di_f_thread_mutexs_resize_

#ifdef __cplusplus
} // extern "C"
#endif

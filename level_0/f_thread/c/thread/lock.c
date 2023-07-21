#include "../thread.h"
#include "private-lock.h"
#include "lock.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_locks_adjust_
  f_status_t f_thread_locks_adjust(const f_number_unsigned_t length, f_thread_locks_t * const locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_locks_adjust(length, locks);
  }
#endif // _di_f_thread_locks_adjust_

#ifndef _di_f_thread_locks_decimate_by_
  f_status_t f_thread_locks_decimate_by(const f_number_unsigned_t amount, f_thread_locks_t * const locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (locks->size > amount) {
      return private_f_thread_locks_adjust(locks->size - amount, locks);
    }

    return private_f_thread_locks_adjust(0, locks);
  }
#endif // _di_f_thread_locks_decimate_by_

#ifndef _di_f_thread_locks_decrease_by_
  f_status_t f_thread_locks_decrease_by(const f_number_unsigned_t amount, f_thread_locks_t * const locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (locks->size > amount) {
      return private_f_thread_locks_resize(locks->size - amount, locks);
    }

    return private_f_thread_locks_resize(0, locks);
  }
#endif // _di_f_thread_locks_decrease_by_

#ifndef _di_f_thread_locks_increase_
  f_status_t f_thread_locks_increase(const f_number_unsigned_t step, f_thread_locks_t * const locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && locks->used + 1 > locks->size) {
      f_number_unsigned_t size = locks->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (locks->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_locks_resize(size, locks);
    }

    return F_data_not;
  }
#endif // _di_f_thread_locks_increase_

#ifndef _di_f_thread_locks_increase_by_
  f_status_t f_thread_locks_increase_by(const f_number_unsigned_t amount, f_thread_locks_t * const locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (locks->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = locks->used + amount;

      if (length > locks->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_locks_resize(length, locks);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_locks_increase_by_

#ifndef _di_f_thread_locks_resize_
  f_status_t f_thread_locks_resize(const f_number_unsigned_t length, f_thread_locks_t * const locks) {
    #ifndef _di_level_0_parameter_checking_
      if (!locks) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_locks_resize(length, locks);
  }
#endif // _di_f_thread_locks_resize_

#ifdef __cplusplus
} // extern "C"
#endif

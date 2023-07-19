#include "../thread.h"
#include "../private-thread.h"
#include "semaphore.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_semaphores_adjust_
  f_status_t f_thread_semaphores_adjust(const f_number_unsigned_t length, f_thread_semaphores_t * const semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_semaphores_adjust(length, semaphores);
  }
#endif // _di_f_thread_semaphores_adjust_

#ifndef _di_f_thread_semaphores_decimate_by_
  f_status_t f_thread_semaphores_decimate_by(const f_number_unsigned_t amount, f_thread_semaphores_t * const semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (semaphores->size > amount) {
      return private_f_thread_semaphores_adjust(semaphores->size - amount, semaphores);
    }

    return private_f_thread_semaphores_adjust(0, semaphores);
  }
#endif // _di_f_thread_semaphores_decimate_by_

#ifndef _di_f_thread_semaphores_decrease_by_
  f_status_t f_thread_semaphores_decrease_by(const f_number_unsigned_t amount, f_thread_semaphores_t * const semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (semaphores->size > amount) {
      return private_f_thread_semaphores_resize(semaphores->size - amount, semaphores);
    }

    return private_f_thread_semaphores_resize(0, semaphores);
  }
#endif // _di_f_thread_semaphores_decrease_by_

#ifndef _di_f_thread_semaphores_increase_
  f_status_t f_thread_semaphores_increase(const f_number_unsigned_t step, f_thread_semaphores_t * const semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && semaphores->used + 1 > semaphores->size) {
      f_number_unsigned_t size = semaphores->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (semaphores->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_semaphores_resize(size, semaphores);
    }

    return F_data_not;
  }
#endif // _di_f_thread_semaphores_increase_

#ifndef _di_f_thread_semaphores_increase_by_
  f_status_t f_thread_semaphores_increase_by(const f_number_unsigned_t amount, f_thread_semaphores_t * const semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (semaphores->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = semaphores->used + amount;

      if (length > semaphores->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_semaphores_resize(length, semaphores);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_semaphores_increase_by_

#ifndef _di_f_thread_semaphores_resize_
  f_status_t f_thread_semaphores_resize(const f_number_unsigned_t length, f_thread_semaphores_t * const semaphores) {
    #ifndef _di_level_0_parameter_checking_
      if (!semaphores) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_semaphores_resize(length, semaphores);
  }
#endif // _di_f_thread_semaphores_resize_

#ifdef __cplusplus
} // extern "C"
#endif

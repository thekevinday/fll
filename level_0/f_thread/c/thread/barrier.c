#include "../thread.h"
#include "../private-thread.h"
#include "barrier.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_barriers_adjust_
  f_status_t f_thread_barriers_adjust(const f_number_unsigned_t length, f_thread_barriers_t * const barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barriers_adjust(length, barriers);
  }
#endif // _di_f_thread_barriers_adjust_

#ifndef _di_f_thread_barriers_decimate_by_
  f_status_t f_thread_barriers_decimate_by(const f_number_unsigned_t amount, f_thread_barriers_t * const barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (barriers->size > amount) {
      return private_f_thread_barriers_adjust(barriers->size - amount, barriers);
    }

    return private_f_thread_barriers_adjust(0, barriers);
  }
#endif // _di_f_thread_barriers_decimate_by_

#ifndef _di_f_thread_barriers_decrease_by_
  f_status_t f_thread_barriers_decrease_by(const f_number_unsigned_t amount, f_thread_barriers_t * const barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (barriers->size > amount) {
      return private_f_thread_barriers_resize(barriers->size - amount, barriers);
    }

    return private_f_thread_barriers_resize(0, barriers);
  }
#endif // _di_f_thread_barriers_decrease_by_

#ifndef _di_f_thread_barriers_increase_
  f_status_t f_thread_barriers_increase(const f_number_unsigned_t step, f_thread_barriers_t * const barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && barriers->used + 1 > barriers->size) {
      f_number_unsigned_t size = barriers->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (barriers->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_barriers_resize(size, barriers);
    }

    return F_data_not;
  }
#endif // _di_f_thread_barriers_increase_

#ifndef _di_f_thread_barriers_increase_by_
  f_status_t f_thread_barriers_increase_by(const f_number_unsigned_t amount, f_thread_barriers_t * const barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (barriers->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = barriers->used + amount;

      if (length > barriers->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_barriers_resize(barriers->used + amount, barriers);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_barriers_increase_by_

#ifndef _di_f_thread_barriers_resize_
  f_status_t f_thread_barriers_resize(const f_number_unsigned_t length, f_thread_barriers_t * const barriers) {
    #ifndef _di_level_0_parameter_checking_
      if (!barriers) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_barriers_resize(length, barriers);
  }
#endif // _di_f_thread_barriers_resize_

#ifdef __cplusplus
} // extern "C"
#endif

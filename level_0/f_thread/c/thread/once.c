#include "../thread.h"
#include "../private-thread.h"
#include "once.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_onces_adjust_
  f_status_t f_thread_onces_adjust(const f_number_unsigned_t length, f_thread_onces_t * const onces) {
    #ifndef _di_level_0_parameter_checking_
      if (!onces) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_onces_adjust(length, onces);
  }
#endif // _di_f_thread_onces_adjust_

#ifndef _di_f_thread_onces_decimate_by_
  f_status_t f_thread_onces_decimate_by(const f_number_unsigned_t amount, f_thread_onces_t * const onces) {
    #ifndef _di_level_0_parameter_checking_
      if (!onces) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (onces->size > amount) {
      return private_f_thread_onces_adjust(onces->size - amount, onces);
    }

    return private_f_thread_onces_adjust(0, onces);
  }
#endif // _di_f_thread_onces_decimate_by_

#ifndef _di_f_thread_onces_decrease_by_
  f_status_t f_thread_onces_decrease_by(const f_number_unsigned_t amount, f_thread_onces_t * const onces) {
    #ifndef _di_level_0_parameter_checking_
      if (!onces) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (onces->size > amount) {
      return private_f_thread_onces_resize(onces->size - amount, onces);
    }

    return private_f_thread_onces_resize(0, onces);
  }
#endif // _di_f_thread_onces_decrease_by_

#ifndef _di_f_thread_onces_increase_
  f_status_t f_thread_onces_increase(const f_number_unsigned_t step, f_thread_onces_t * const onces) {
    #ifndef _di_level_0_parameter_checking_
      if (!onces) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && onces->used + 1 > onces->size) {
      f_number_unsigned_t size = onces->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (onces->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_onces_resize(size, onces);
    }

    return F_data_not;
  }
#endif // _di_f_thread_onces_increase_

#ifndef _di_f_thread_onces_increase_by_
  f_status_t f_thread_onces_increase_by(const f_number_unsigned_t amount, f_thread_onces_t * const onces) {
    #ifndef _di_level_0_parameter_checking_
      if (!onces) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (onces->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = onces->used + amount;

      if (length > onces->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_onces_resize(length, onces);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_onces_increase_by_

#ifndef _di_f_thread_onces_resize_
  f_status_t f_thread_onces_resize(const f_number_unsigned_t length, f_thread_onces_t * const onces) {
    #ifndef _di_level_0_parameter_checking_
      if (!onces) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_onces_resize(length, onces);
  }
#endif // _di_f_thread_onces_resize_

#ifdef __cplusplus
} // extern "C"
#endif

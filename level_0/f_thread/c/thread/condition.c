#include "../thread.h"
#include "../private-thread.h"
#include "condition.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_conditions_adjust_
  f_status_t f_thread_conditions_adjust(const f_number_unsigned_t length, f_thread_conditions_t * const conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_conditions_adjust(length, conditions);
  }
#endif // _di_f_thread_conditions_adjust_

#ifndef _di_f_thread_conditions_decimate_by_
  f_status_t f_thread_conditions_decimate_by(const f_number_unsigned_t amount, f_thread_conditions_t * const conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (conditions->size > amount) {
      return private_f_thread_conditions_adjust(conditions->size - amount, conditions);
    }

    return private_f_thread_conditions_adjust(0, conditions);
  }
#endif // _di_f_thread_conditions_decimate_by_

#ifndef _di_f_thread_conditions_decrease_by_
  f_status_t f_thread_conditions_decrease_by(const f_number_unsigned_t amount, f_thread_conditions_t * const conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (conditions->size > amount) {
      return private_f_thread_conditions_resize(conditions->size - amount, conditions);
    }

    return private_f_thread_conditions_resize(0, conditions);
  }
#endif // _di_f_thread_conditions_decrease_by_

#ifndef _di_f_thread_conditions_increase_
  f_status_t f_thread_conditions_increase(const f_number_unsigned_t step, f_thread_conditions_t * const conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && conditions->used + 1 > conditions->size) {
      f_number_unsigned_t size = conditions->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (conditions->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_conditions_resize(size, conditions);
    }

    return F_data_not;
  }
#endif // _di_f_thread_conditions_increase_

#ifndef _di_f_thread_conditions_increase_by_
  f_status_t f_thread_conditions_increase_by(const f_number_unsigned_t amount, f_thread_conditions_t * const conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (conditions->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = conditions->used + amount;

      if (length > conditions->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_conditions_resize(conditions->used + amount, conditions);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_conditions_increase_by_

#ifndef _di_f_thread_conditions_resize_
  f_status_t f_thread_conditions_resize(const f_number_unsigned_t length, f_thread_conditions_t * const conditions) {
    #ifndef _di_level_0_parameter_checking_
      if (!conditions) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_conditions_resize(length, conditions);
  }
#endif // _di_f_thread_conditions_resize_

#ifdef __cplusplus
} // extern "C"
#endif

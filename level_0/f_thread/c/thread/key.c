#include "../thread.h"
#include "private-key.h"
#include "key.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_keys_adjust_
  f_status_t f_thread_keys_adjust(const f_number_unsigned_t length, f_thread_keys_t * const keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_keys_adjust(length, keys);
  }
#endif // _di_f_thread_keys_adjust_

#ifndef _di_f_thread_keys_decimate_by_
  f_status_t f_thread_keys_decimate_by(const f_number_unsigned_t amount, f_thread_keys_t * const keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (keys->size > amount) {
      return private_f_thread_keys_adjust(keys->size - amount, keys);
    }

    return private_f_thread_keys_adjust(0, keys);
  }
#endif // _di_f_thread_keys_decimate_by_

#ifndef _di_f_thread_keys_decrease_by_
  f_status_t f_thread_keys_decrease_by(const f_number_unsigned_t amount, f_thread_keys_t * const keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (keys->size > amount) {
      return private_f_thread_keys_resize(keys->size - amount, keys);
    }

    return private_f_thread_keys_resize(0, keys);
  }
#endif // _di_f_thread_keys_decrease_by_

#ifndef _di_f_thread_keys_increase_
  f_status_t f_thread_keys_increase(const f_number_unsigned_t step, f_thread_keys_t * const keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && keys->used + 1 > keys->size) {
      f_number_unsigned_t size = keys->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (keys->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_keys_resize(size, keys);
    }

    return F_data_not;
  }
#endif // _di_f_thread_keys_increase_

#ifndef _di_f_thread_keys_increase_by_
  f_status_t f_thread_keys_increase_by(const f_number_unsigned_t amount, f_thread_keys_t * const keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (keys->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = keys->used + amount;

      if (length > keys->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_keys_resize(length, keys);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_keys_increase_by_

#ifndef _di_f_thread_keys_resize_
  f_status_t f_thread_keys_resize(const f_number_unsigned_t length, f_thread_keys_t * const keys) {
    #ifndef _di_level_0_parameter_checking_
      if (!keys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_keys_resize(length, keys);
  }
#endif // _di_f_thread_keys_resize_

#ifdef __cplusplus
} // extern "C"
#endif

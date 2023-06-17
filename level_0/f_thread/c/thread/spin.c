#include "../thread.h"
#include "../private-thread.h"
#include "spin.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_spins_adjust_
  f_status_t f_thread_spins_adjust(const f_number_unsigned_t length, f_thread_spins_t * const spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_spins_adjust(length, spins);
  }
#endif // _di_f_thread_spins_adjust_

#ifndef _di_f_thread_spins_decimate_by_
  f_status_t f_thread_spins_decimate_by(const f_number_unsigned_t amount, f_thread_spins_t * const spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (spins->size > amount) {
      return private_f_thread_spins_adjust(spins->size - amount, spins);
    }

    return private_f_thread_spins_adjust(0, spins);
  }
#endif // _di_f_thread_spins_decimate_by_

#ifndef _di_f_thread_spins_decrease_by_
  f_status_t f_thread_spins_decrease_by(const f_number_unsigned_t amount, f_thread_spins_t * const spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (spins->size > amount) {
      return private_f_thread_spins_resize(spins->size - amount, spins);
    }

    return private_f_thread_spins_resize(0, spins);
  }
#endif // _di_f_thread_spins_decrease_by_

#ifndef _di_f_thread_spins_increase_
  f_status_t f_thread_spins_increase(const f_number_unsigned_t step, f_thread_spins_t * const spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && spins->used + 1 > spins->size) {
      f_number_unsigned_t size = spins->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (spins->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_spins_resize(size, spins);
    }

    return F_data_not;
  }
#endif // _di_f_thread_spins_increase_

#ifndef _di_f_thread_spins_increase_by_
  f_status_t f_thread_spins_increase_by(const f_number_unsigned_t amount, f_thread_spins_t * const spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (spins->used + amount > spins->size) {
      if (spins->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_spins_resize(spins->used + amount, spins);
    }

    return F_data_not;
  }
#endif // _di_f_thread_spins_increase_by_

#ifndef _di_f_thread_spins_resize_
  f_status_t f_thread_spins_resize(const f_number_unsigned_t length, f_thread_spins_t * const spins) {
    #ifndef _di_level_0_parameter_checking_
      if (!spins) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_spins_resize(length, spins);
  }
#endif // _di_f_thread_spins_resize_

#ifdef __cplusplus
} // extern "C"
#endif

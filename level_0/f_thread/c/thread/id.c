#include "../thread.h"
#include "../private-thread.h"
#include "id.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_ids_adjust_
  f_status_t f_thread_ids_adjust(const f_number_unsigned_t length, f_thread_ids_t * const ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_ids_adjust(length, ids);
  }
#endif // _di_f_thread_ids_adjust_

#ifndef _di_f_thread_ids_decimate_by_
  f_status_t f_thread_ids_decimate_by(const f_number_unsigned_t amount, f_thread_ids_t * const ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (ids->size > amount) {
      return private_f_thread_ids_adjust(ids->size - amount, ids);
    }

    return private_f_thread_ids_adjust(0, ids);
  }
#endif // _di_f_thread_ids_decimate_by_

#ifndef _di_f_thread_ids_decrease_by_
  f_status_t f_thread_ids_decrease_by(const f_number_unsigned_t amount, f_thread_ids_t * const ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (ids->size > amount) {
      return private_f_thread_ids_resize(ids->size - amount, ids);
    }

    return private_f_thread_ids_resize(0, ids);
  }
#endif // _di_f_thread_ids_decrease_by_

#ifndef _di_f_thread_ids_increase_
  f_status_t f_thread_ids_increase(const f_number_unsigned_t step, f_thread_ids_t * const ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && ids->used + 1 > ids->size) {
      f_number_unsigned_t size = ids->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (ids->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_ids_resize(size, ids);
    }

    return F_data_not;
  }
#endif // _di_f_thread_ids_increase_

#ifndef _di_f_thread_ids_increase_by_
  f_status_t f_thread_ids_increase_by(const f_number_unsigned_t amount, f_thread_ids_t * const ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (ids->used + amount > ids->size) {
      if (ids->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_ids_resize(ids->used + amount, ids);
    }

    return F_data_not;
  }
#endif // _di_f_thread_ids_increase_by_

#ifndef _di_f_thread_ids_resize_
  f_status_t f_thread_ids_resize(const f_number_unsigned_t length, f_thread_ids_t * const ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_ids_resize(length, ids);
  }
#endif // _di_f_thread_ids_resize_

#ifdef __cplusplus
} // extern "C"
#endif

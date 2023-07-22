#include "../thread.h"
#include "private-key.h"
#include "key.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_keys_adjust_
  f_status_t f_thread_keys_adjust(const f_number_unsigned_t length, f_thread_keys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_keys_adjust(length, structure);
  }
#endif // _di_f_thread_keys_adjust_

#ifndef _di_f_thread_keys_decimate_by_
  f_status_t f_thread_keys_decimate_by(const f_number_unsigned_t amount, f_thread_keys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_thread_keys_adjust((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_thread_keys_decimate_by_

#ifndef _di_f_thread_keys_decrease_by_
  f_status_t f_thread_keys_decrease_by(const f_number_unsigned_t amount, f_thread_keys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_thread_keys_resize((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_thread_keys_decrease_by_

#ifndef _di_f_thread_keys_increase_
  f_status_t f_thread_keys_increase(const f_number_unsigned_t step, f_thread_keys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_thread_keys_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_thread_keys_increase_

#ifndef _di_f_thread_keys_increase_by_
  f_status_t f_thread_keys_increase_by(const f_number_unsigned_t amount, f_thread_keys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_thread_keys_resize(length, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_keys_increase_by_

#ifndef _di_f_thread_keys_resize_
  f_status_t f_thread_keys_resize(const f_number_unsigned_t length, f_thread_keys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_keys_resize(length, structure);
  }
#endif // _di_f_thread_keys_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../thread.h"
#include "../private-thread.h"
#include "attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_attributes_adjust_
  f_status_t f_thread_attributes_adjust(const f_number_unsigned_t length, f_thread_attributes_t * const attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_attributes_adjust(length, attributes);
  }
#endif // _di_f_thread_attributes_adjust_

#ifndef _di_f_thread_attributes_decimate_by_
  f_status_t f_thread_attributes_decimate_by(const f_number_unsigned_t amount, f_thread_attributes_t * const attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (attributes->size > amount) {
      return private_f_thread_attributes_adjust(attributes->size - amount, attributes);
    }

    return private_f_thread_attributes_adjust(0, attributes);
  }
#endif // _di_f_thread_attributes_decimate_by_

#ifndef _di_f_thread_attributes_decrease_by_
  f_status_t f_thread_attributes_decrease_by(const f_number_unsigned_t amount, f_thread_attributes_t * const attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (attributes->size > amount) {
      return private_f_thread_attributes_resize(attributes->size - amount, attributes);
    }

    return private_f_thread_attributes_resize(0, attributes);
  }
#endif // _di_f_thread_attributes_decrease_by_

#ifndef _di_f_thread_attributes_increase_
  f_status_t f_thread_attributes_increase(const f_number_unsigned_t step, f_thread_attributes_t * const attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && attributes->used + 1 > attributes->size) {
      f_number_unsigned_t size = attributes->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (attributes->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_thread_attributes_resize(size, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_attributes_increase_

#ifndef _di_f_thread_attributes_increase_by_
  f_status_t f_thread_attributes_increase_by(const f_number_unsigned_t amount, f_thread_attributes_t * const attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (attributes->used + amount > attributes->size) {
      if (attributes->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_thread_attributes_resize(attributes->used + amount, attributes);
    }

    return F_data_not;
  }
#endif // _di_f_thread_attributes_increase_by_

#ifndef _di_f_thread_attributes_resize_
  f_status_t f_thread_attributes_resize(const f_number_unsigned_t length, f_thread_attributes_t * const attributes) {
    #ifndef _di_level_0_parameter_checking_
      if (!attributes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_thread_attributes_resize(length, attributes);
  }
#endif // _di_f_thread_attributes_resize_

#ifdef __cplusplus
} // extern "C"
#endif

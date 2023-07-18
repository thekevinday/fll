#include "../memory.h"
#include "private-array.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_array_adjust_
  f_status_t f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    return private_f_memory_array_adjust(length, width, array, used, size);
  }
#endif // _di_f_memory_array_adjust_

#ifndef _di_f_memory_array_decimate_by_
  f_status_t f_memory_array_decimate_by(const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (*size > amount) return private_f_memory_array_adjust(*size - amount, width, array, used, size);

    return private_f_memory_array_adjust(0, width, array, used, size);
  }
#endif // _di_f_memory_array_decimate_by_

#ifndef _di_f_memory_array_decrease_by_
  f_status_t f_memory_array_decrease_by(const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (*size > amount) return private_f_memory_array_resize(*size - amount, width, array, used, size);

    return private_f_memory_array_resize(0, width, array, used, size);
  }
#endif // _di_f_memory_array_decrease_by_

#ifndef _di_f_memory_array_increase_
  f_status_t f_memory_array_increase(const f_number_unsigned_t step, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && *used + 1 > *size) {
      f_number_unsigned_t length = *used + step;

      if (step > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      if (*size > F_number_t_size_unsigned_d) {
        if (*used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);
        if (*used + length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_memory_array_resize(length, width, array, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_array_increase_

#ifndef _di_f_memory_array_increase_by_
  f_status_t f_memory_array_increase_by(const f_number_unsigned_t amount, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (*used + amount > *size) {
      if (*used + amount > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      return private_f_memory_array_resize(*used + amount, width, array, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_array_increase_by_

#ifndef _di_f_memory_array_resize_
  f_status_t f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    return private_f_memory_array_resize(length, width, array, used, size);
  }
#endif // _di_f_memory_array_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../memory.h"
#include "private-array.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_arrays_adjust_
  f_status_t f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array)) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
      if (!callback) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    if (length < *size) {
      const f_status_t status = callback(length, *size, *array);
      if (F_status_is_error(status)) return status;
    }

    return private_f_memory_array_adjust(length, width, array, used, size);
  }
#endif // _di_f_memory_arrays_adjust_

#ifndef _di_f_memory_arrays_resize_
  f_status_t f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array)) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
      if (!callback) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    if (length < *size) {
      const f_status_t status = callback(length, *size, *array);
      if (F_status_is_error(status)) return status;
    }

    return private_f_memory_array_resize(length, width, array, used, size);
  }
#endif // _di_f_memory_arrays_resize_

#ifdef __cplusplus
} // extern "C"
#endif

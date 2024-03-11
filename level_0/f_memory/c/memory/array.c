#include "../memory.h"
#include "private-array.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_array_adjust_
  f_status_t f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** restrict const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    return private_f_memory_array_adjust(length, width, array, used, size);
  }
#endif // _di_f_memory_array_adjust_

#ifndef _di_f_memory_array_append_
  f_status_t f_memory_array_append(const void * const source, const size_t width, void ** const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!source) return F_status_set_error(F_parameter);
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (*used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    {
      const f_number_unsigned_t length = *used + F_memory_default_allocation_small_d;

      if (length > *size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        const f_status_t status = private_f_memory_array_resize(length, width, array, used, size);
        if (F_status_is_error(status)) return status;
      }
    }

    // Casting (void *) to (uint8_t *) should result in an increment of size 1 and avoids problems with (void *) having arithmetic issues.
    memcpy((void *) (((uint8_t *) (*array)) + (*used * width)), source, width);

    ++(*used);

    return F_okay;
  }
#endif // _di_f_memory_array_append_

#ifndef _di_f_memory_array_append_all_
  f_status_t f_memory_array_append_all(const void * const sources, const f_number_unsigned_t amount, const size_t width, void ** const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!sources) return F_status_set_error(F_parameter);
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (*used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    {
      const f_number_unsigned_t length = *used + amount;

      if (length > *size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        const f_status_t status = private_f_memory_array_resize(length, width, array, used, size);
        if (F_status_is_error(status)) return status;
      }
    }

    // Casting (void *) to (uint8_t *) should result in an increment of size 1 and avoids problems with (void *) having arithmetic issues.
    memcpy((void *) (((uint8_t *) (*array)) + (*used * width)), sources, width * amount);

    *used += amount;

    return F_okay;
  }
#endif // _di_f_memory_array_append_all_

#ifndef _di_f_memory_array_decimate_by_
  f_status_t f_memory_array_decimate_by(const f_number_unsigned_t amount, const size_t width, void ** restrict const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_memory_array_adjust((*size > amount) ? *size - amount : 0, width, array, used, size);
  }
#endif // _di_f_memory_array_decimate_by_

#ifndef _di_f_memory_array_decrease_by_
  f_status_t f_memory_array_decrease_by(const f_number_unsigned_t amount, const size_t width, void ** restrict const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_memory_array_resize((*size > amount) ? *size - amount : 0, width, array, used, size);
  }
#endif // _di_f_memory_array_decrease_by_

#ifndef _di_f_memory_array_increase_
  f_status_t f_memory_array_increase(const f_number_unsigned_t step, const size_t width, void ** restrict const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && *used + 1 > *size) {
      if (*used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = *used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (*used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_memory_array_resize(length, width, array, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_array_increase_

#ifndef _di_f_memory_array_increase_by_
  f_status_t f_memory_array_increase_by(const f_number_unsigned_t amount, const size_t width, void ** restrict const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (*used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = *used + amount;

      if (length > *size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_memory_array_resize(length, width, array, used, size);
      }
    }

    return F_data_not;
  }
#endif // _di_f_memory_array_increase_by_

#ifndef _di_f_memory_array_resize_
  f_status_t f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** restrict const array, f_number_unsigned_t * restrict const used, f_number_unsigned_t * restrict const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!width) return F_status_set_error(F_parameter);
      if (!array) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (*used > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);
    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    return private_f_memory_array_resize(length, width, array, used, size);
  }
#endif // _di_f_memory_array_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_ranges_adjust_
  f_status_t f_string_ranges_adjust(const f_string_length_t length, f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_ranges_adjust(length, ranges);
  }
#endif // _di_f_string_ranges_adjust_

#ifndef _di_f_string_ranges_decimate_
  f_status_t f_string_ranges_decimate(f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (ranges->size > 1) {
      return private_f_string_ranges_adjust(ranges->size - 1, ranges);
    }

    return private_f_string_ranges_destroy(ranges);
  }
#endif // _di_f_string_ranges_decimate_

#ifndef _di_f_string_ranges_decimate_by_
  f_status_t f_string_ranges_decimate_by(const f_array_length_t amount, f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (ranges->size - amount > 0) {
      return private_f_string_ranges_adjust(ranges->size - amount, ranges);
    }

    return private_f_string_ranges_destroy(ranges);
  }
#endif // _di_f_string_ranges_decimate_by_

#ifndef _di_f_string_ranges_decrease_
  f_status_t f_string_ranges_decrease(f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (ranges->size > 1) {
      return private_f_string_ranges_resize(ranges->size - 1, ranges);
    }

    return private_f_string_ranges_delete(ranges);
  }
#endif // _di_f_string_ranges_decrease_

#ifndef _di_f_string_ranges_decrease_by_
  f_status_t f_string_ranges_decrease_by(const f_array_length_t amount, f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (ranges->size - amount > 0) {
      return private_f_string_ranges_resize(ranges->size - amount, ranges);
    }

    return private_f_string_ranges_delete(ranges);
  }
#endif // _di_f_string_ranges_decrease_by_

#ifndef _di_f_string_ranges_delete_
  f_status_t f_string_ranges_delete(f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_ranges_delete(ranges);
  }
#endif // _di_f_string_ranges_delete_

#ifndef _di_f_string_ranges_destroy_
  f_status_t f_string_ranges_destroy(f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_ranges_destroy(ranges);
  }
#endif // _di_f_string_ranges_destroy_

#ifndef _di_f_string_ranges_increase_
  f_status_t f_string_ranges_increase(f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (ranges->used + 1 > ranges->size) {
      f_array_length_t size = ranges->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (ranges->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_ranges_resize(size, ranges);
    }

    return F_none;
  }
#endif // _di_f_string_ranges_increase_

#ifndef _di_f_string_ranges_increase_by_
  f_status_t f_string_ranges_increase_by(const f_array_length_t amount, f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (ranges->used + amount > ranges->size) {
      if (ranges->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_ranges_resize(ranges->used + amount, ranges);
    }

    return F_none;
  }
#endif // _di_f_string_ranges_increase_by_

#ifndef _di_f_string_ranges_resize_
  f_status_t f_string_ranges_resize(const f_string_length_t length, f_string_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_ranges_resize(length, ranges);
  }
#endif // _di_f_string_ranges_resize_

#ifdef __cplusplus
} // extern "C"
#endif

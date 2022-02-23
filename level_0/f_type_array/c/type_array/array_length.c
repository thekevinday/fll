#include "../type_array.h"
#include "array_length.h"
#include "private-array_length.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_array_lengths_adjust_
  f_status_t f_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_array_lengths_adjust(length, lengths);
  }
#endif // _di_f_array_lengths_adjust_

#ifndef _di_f_array_lengths_append_
  f_status_t f_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_array_lengths_append(source, destination);
  }
#endif // _di_f_array_lengths_append_

#ifndef _di_f_array_lengths_decimate_by_
  f_status_t f_array_lengths_decimate_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->size - amount > 0) {
      return private_f_array_lengths_adjust(lengths->size - amount, lengths);
    }

    return private_f_array_lengths_adjust(0, lengths);
  }
#endif // _di_f_array_lengths_decimate_by_

#ifndef _di_f_array_lengths_decrease_by_
  f_status_t f_array_lengths_decrease_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->size - amount > 0) {
      return private_f_array_lengths_resize(lengths->size - amount, lengths);
    }

    return private_f_array_lengths_resize(0, lengths);
  }
#endif // _di_f_array_lengths_decrease_by_

#ifndef _di_f_array_lengths_increase_
  f_status_t f_array_lengths_increase(const f_array_length_t step, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->used + 1 > lengths->size) {
      f_array_length_t size = lengths->used + step;

      if (size > F_array_length_t_size_d) {
        if (lengths->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_array_lengths_resize(size, lengths);
    }

    return F_data_not;
  }
#endif // _di_f_array_lengths_increase_

#ifndef _di_f_array_lengths_increase_by_
  f_status_t f_array_lengths_increase_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->used + amount > lengths->size) {
      if (lengths->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_array_lengths_resize(lengths->used + amount, lengths);
    }

    return F_data_not;
  }
#endif // _di_f_array_lengths_increase_by_

#ifndef _di_f_array_lengths_resize_
  f_status_t f_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_array_lengths_resize(length, lengths);
  }
#endif // _di_f_array_lengths_resize_

#ifndef _di_f_array_lengthss_adjust_
  f_status_t f_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_array_lengthss_adjust(length, lengthss);
  }
#endif // _di_f_array_lengthss_adjust_

#ifndef _di_f_array_lengthss_append_
  f_status_t f_array_lengthss_append(const f_array_lengthss_t source, f_array_lengthss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_array_lengthss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_array_lengths_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_array_lengthss_append_

#ifndef _di_f_array_lengthss_decimate_by_
  f_status_t f_array_lengthss_decimate_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->size - amount > 0) {
      return private_f_array_lengthss_adjust(lengthss->size - amount, lengthss);
    }

    return private_f_array_lengthss_adjust(0, lengthss);
  }
#endif // _di_f_array_lengthss_decimate_by_

#ifndef _di_f_array_lengthss_decrease_by_
  f_status_t f_array_lengthss_decrease_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->size - amount > 0) {
      return private_f_array_lengthss_resize(lengthss->size - amount, lengthss);
    }

    return private_f_array_lengthss_resize(0, lengthss);
  }
#endif // _di_f_array_lengthss_decrease_by_

#ifndef _di_f_array_lengthss_increase_
  f_status_t f_array_lengthss_increase(const f_array_length_t step, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->used + 1 > lengthss->size) {
      f_array_length_t size = lengthss->used + step;

      if (size > F_array_length_t_size_d) {
        if (lengthss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_array_lengthss_resize(size, lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_array_lengthss_increase_

#ifndef _di_f_array_lengthss_increase_by_
  f_status_t f_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->used + amount > lengthss->size) {
      if (lengthss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_array_lengthss_resize(lengthss->used + amount, lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_array_lengthss_increase_by_

#ifndef _di_f_array_lengthss_resize_
  f_status_t f_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_array_lengthss_resize(length, lengthss);
  }
#endif // _di_f_array_lengthss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

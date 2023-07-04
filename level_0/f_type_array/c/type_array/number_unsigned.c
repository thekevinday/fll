#include "../type_array.h"
#include "number_unsigned.h"
#include "private-number_unsigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_number_unsigneds_adjust_
  f_status_t f_number_unsigneds_adjust(const f_number_unsigned_t length, f_number_unsigneds_t * const lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_number_unsigneds_adjust(length, lengths);
  }
#endif // _di_f_number_unsigneds_adjust_

#ifndef _di_f_number_unsigneds_append_
  f_status_t f_number_unsigneds_append(const f_number_unsigned_t source, f_number_unsigneds_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_number_unsigneds_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // _di_f_number_unsigneds_append_

#ifndef _di_f_number_unsigneds_append_all_
  f_status_t f_number_unsigneds_append_all(const f_number_unsigneds_t source, f_number_unsigneds_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_number_unsigneds_append_all(source, destination);
  }
#endif // _di_f_number_unsigneds_append_all_

#ifndef _di_f_number_unsigneds_decimate_by_
  f_status_t f_number_unsigneds_decimate_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (lengths->size - amount > 0) {
      return private_f_number_unsigneds_adjust(lengths->size - amount, lengths);
    }

    return private_f_number_unsigneds_adjust(0, lengths);
  }
#endif // _di_f_number_unsigneds_decimate_by_

#ifndef _di_f_number_unsigneds_decrease_by_
  f_status_t f_number_unsigneds_decrease_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (lengths->size - amount > 0) {
      return private_f_number_unsigneds_resize(lengths->size - amount, lengths);
    }

    return private_f_number_unsigneds_resize(0, lengths);
  }
#endif // _di_f_number_unsigneds_decrease_by_

#ifndef _di_f_number_unsigneds_increase_
  f_status_t f_number_unsigneds_increase(const f_number_unsigned_t step, f_number_unsigneds_t * const lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && lengths->used + 1 > lengths->size) {
      f_number_unsigned_t size = lengths->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (lengths->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_number_unsigneds_resize(size, lengths);
    }

    return F_data_not;
  }
#endif // _di_f_number_unsigneds_increase_

#ifndef _di_f_number_unsigneds_increase_by_
  f_status_t f_number_unsigneds_increase_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (lengths->used + amount > lengths->size) {
      if (lengths->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_number_unsigneds_resize(lengths->used + amount, lengths);
    }

    return F_data_not;
  }
#endif // _di_f_number_unsigneds_increase_by_

#ifndef _di_f_number_unsigneds_resize_
  f_status_t f_number_unsigneds_resize(const f_number_unsigned_t length, f_number_unsigneds_t * const lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_number_unsigneds_resize(length, lengths);
  }
#endif // _di_f_number_unsigneds_resize_

#ifndef _di_f_number_unsignedss_adjust_
  f_status_t f_number_unsignedss_adjust(const f_number_unsigned_t length, f_number_unsignedss_t * const lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_number_unsignedss_adjust(length, lengthss);
  }
#endif // _di_f_number_unsignedss_adjust_

#ifndef _di_f_number_unsignedss_append_
  f_status_t f_number_unsignedss_append(const f_number_unsigneds_t source, f_number_unsignedss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_number_unsignedss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_number_unsigneds_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_number_unsignedss_append_

#ifndef _di_f_number_unsignedss_append_all_
  f_status_t f_number_unsignedss_append_all(const f_number_unsignedss_t source, f_number_unsignedss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_number_unsignedss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_number_unsigneds_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_number_unsignedss_append_all_

#ifndef _di_f_number_unsignedss_decimate_by_
  f_status_t f_number_unsignedss_decimate_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (lengthss->size - amount > 0) {
      return private_f_number_unsignedss_adjust(lengthss->size - amount, lengthss);
    }

    return private_f_number_unsignedss_adjust(0, lengthss);
  }
#endif // _di_f_number_unsignedss_decimate_by_

#ifndef _di_f_number_unsignedss_decrease_by_
  f_status_t f_number_unsignedss_decrease_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (lengthss->size - amount > 0) {
      return private_f_number_unsignedss_resize(lengthss->size - amount, lengthss);
    }

    return private_f_number_unsignedss_resize(0, lengthss);
  }
#endif // _di_f_number_unsignedss_decrease_by_

#ifndef _di_f_number_unsignedss_increase_
  f_status_t f_number_unsignedss_increase(const f_number_unsigned_t step, f_number_unsignedss_t * const lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && lengthss->used + 1 > lengthss->size) {
      f_number_unsigned_t size = lengthss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (lengthss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_number_unsignedss_resize(size, lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_number_unsignedss_increase_

#ifndef _di_f_number_unsignedss_increase_by_
  f_status_t f_number_unsignedss_increase_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (lengthss->used + amount > lengthss->size) {
      if (lengthss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_number_unsignedss_resize(lengthss->used + amount, lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_number_unsignedss_increase_by_

#ifndef _di_f_number_unsignedss_resize_
  f_status_t f_number_unsignedss_resize(const f_number_unsigned_t length, f_number_unsignedss_t * const lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_number_unsignedss_resize(length, lengthss);
  }
#endif // _di_f_number_unsignedss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

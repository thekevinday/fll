#include "../type_array.h"
#include "uint8.h"
#include "private-uint8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint8s_adjust_
  f_status_t f_uint8s_adjust(const f_number_unsigned_t length, f_uint8s_t * const uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint8s_adjust(length, uint8s);
  }
#endif // _di_f_uint8s_adjust_

#ifndef _di_f_uint8s_append_
  f_status_t f_uint8s_append(const uint8_t source, f_uint8s_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint8s_append(source, destination);
  }
#endif // _di_f_uint8s_append_

#ifndef _di_f_uint8s_append_all_
  f_status_t f_uint8s_append_all(const f_uint8s_t source, f_uint8s_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint8s_append_all(source, destination);
  }
#endif // _di_f_uint8s_append_all_

#ifndef _di_f_uint8s_decimate_by_
  f_status_t f_uint8s_decimate_by(const f_number_unsigned_t amount, f_uint8s_t * const uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint8s->size - amount > 0) {
      return private_f_uint8s_adjust(uint8s->size - amount, uint8s);
    }

    return private_f_uint8s_adjust(0, uint8s);
  }
#endif // _di_f_uint8s_decimate_by_

#ifndef _di_f_uint8s_decrease_by_
  f_status_t f_uint8s_decrease_by(const f_number_unsigned_t amount, f_uint8s_t * const uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint8s->size - amount > 0) {
      return private_f_uint8s_resize(uint8s->size - amount, uint8s);
    }

    return private_f_uint8s_resize(0, uint8s);
  }
#endif // _di_f_uint8s_decrease_by_

#ifndef _di_f_uint8s_increase_
  f_status_t f_uint8s_increase(const f_number_unsigned_t step, f_uint8s_t * const uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint8s->used + 1 > uint8s->size) {
      f_number_unsigned_t size = uint8s->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (uint8s->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_uint8s_resize(size, uint8s);
    }

    return F_data_not;
  }
#endif // _di_f_uint8s_increase_

#ifndef _di_f_uint8s_increase_by_
  f_status_t f_uint8s_increase_by(const f_number_unsigned_t amount, f_uint8s_t * const uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint8s->used + amount > uint8s->size) {
      if (uint8s->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint8s_resize(uint8s->used + amount, uint8s);
    }

    return F_data_not;
  }
#endif // _di_f_uint8s_increase_by_

#ifndef _di_f_uint8s_resize_
  f_status_t f_uint8s_resize(const f_number_unsigned_t length, f_uint8s_t * const uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint8s_resize(length, uint8s);
  }
#endif // _di_f_uint8s_resize_

#ifndef _di_f_uint8ss_adjust_
  f_status_t f_uint8ss_adjust(const f_number_unsigned_t length, f_uint8ss_t * const uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint8ss_adjust(length, uint8ss);
  }
#endif // _di_f_uint8ss_adjust_

#ifndef _di_f_uint8ss_append_
  f_status_t f_uint8ss_append(const f_uint8s_t source, f_uint8ss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_uint8ss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_uint8s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_uint8ss_append_

#ifndef _di_f_uint8ss_append_all_
  f_status_t f_uint8ss_append_all(const f_uint8ss_t source, f_uint8ss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint8ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_uint8s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_uint8ss_append_all_

#ifndef _di_f_uint8ss_decimate_by_
  f_status_t f_uint8ss_decimate_by(const f_number_unsigned_t amount, f_uint8ss_t * const uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint8ss->size - amount > 0) {
      return private_f_uint8ss_adjust(uint8ss->size - amount, uint8ss);
    }

    return private_f_uint8ss_adjust(0, uint8ss);
  }
#endif // _di_f_uint8ss_decimate_by_

#ifndef _di_f_uint8ss_decrease_by_
  f_status_t f_uint8ss_decrease_by(const f_number_unsigned_t amount, f_uint8ss_t * const uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint8ss->size - amount > 0) {
      return private_f_uint8ss_resize(uint8ss->size - amount, uint8ss);
    }

    return private_f_uint8ss_resize(0, uint8ss);
  }
#endif // _di_f_uint8ss_decrease_by_

#ifndef _di_f_uint8ss_increase_
  f_status_t f_uint8ss_increase(const f_number_unsigned_t step, f_uint8ss_t * const uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint8ss->used + 1 > uint8ss->size) {
      f_number_unsigned_t size = uint8ss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (uint8ss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_uint8ss_resize(size, uint8ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint8ss_increase_

#ifndef _di_f_uint8ss_increase_by_
  f_status_t f_uint8ss_increase_by(const f_number_unsigned_t amount, f_uint8ss_t * const uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint8ss->used + amount > uint8ss->size) {
      if (uint8ss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint8ss_resize(uint8ss->used + amount, uint8ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint8ss_increase_by_

#ifndef _di_f_uint8ss_resize_
  f_status_t f_uint8ss_resize(const f_number_unsigned_t length, f_uint8ss_t * const uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint8ss_resize(length, uint8ss);
  }
#endif // _di_f_uint8ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

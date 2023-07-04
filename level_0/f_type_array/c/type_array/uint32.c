#include "../type_array.h"
#include "uint32.h"
#include "private-uint32.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint32s_adjust_
  f_status_t f_uint32s_adjust(const f_number_unsigned_t length, f_uint32s_t * const uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32s_adjust(length, uint32s);
  }
#endif // _di_f_uint32s_adjust_

#ifndef _di_f_uint32s_append_
  f_status_t f_uint32s_append(const uint32_t source, f_uint32s_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32s_append(source, destination);
  }
#endif // _di_f_uint32s_append_

#ifndef _di_f_uint32s_append_all_
  f_status_t f_uint32s_append_all(const f_uint32s_t source, f_uint32s_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint32s_append_all(source, destination);
  }
#endif // _di_f_uint32s_append_all_

#ifndef _di_f_uint32s_decimate_by_
  f_status_t f_uint32s_decimate_by(const f_number_unsigned_t amount, f_uint32s_t * const uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint32s->size - amount > 0) {
      return private_f_uint32s_adjust(uint32s->size - amount, uint32s);
    }

    return private_f_uint32s_adjust(0, uint32s);
  }
#endif // _di_f_uint32s_decimate_by_

#ifndef _di_f_uint32s_decrease_by_
  f_status_t f_uint32s_decrease_by(const f_number_unsigned_t amount, f_uint32s_t * const uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint32s->size - amount > 0) {
      return private_f_uint32s_resize(uint32s->size - amount, uint32s);
    }

    return private_f_uint32s_resize(0, uint32s);
  }
#endif // _di_f_uint32s_decrease_by_

#ifndef _di_f_uint32s_increase_
  f_status_t f_uint32s_increase(const f_number_unsigned_t step, f_uint32s_t * const uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint32s->used + 1 > uint32s->size) {
      f_number_unsigned_t size = uint32s->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (uint32s->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_uint32s_resize(size, uint32s);
    }

    return F_data_not;
  }
#endif // _di_f_uint32s_increase_

#ifndef _di_f_uint32s_increase_by_
  f_status_t f_uint32s_increase_by(const f_number_unsigned_t amount, f_uint32s_t * const uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint32s->used + amount > uint32s->size) {
      if (uint32s->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint32s_resize(uint32s->used + amount, uint32s);
    }

    return F_data_not;
  }
#endif // _di_f_uint32s_increase_by_

#ifndef _di_f_uint32s_resize_
  f_status_t f_uint32s_resize(const f_number_unsigned_t length, f_uint32s_t * const uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32s_resize(length, uint32s);
  }
#endif // _di_f_uint32s_resize_

#ifndef _di_f_uint32ss_adjust_
  f_status_t f_uint32ss_adjust(const f_number_unsigned_t length, f_uint32ss_t * const uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32ss_adjust(length, uint32ss);
  }
#endif // _di_f_uint32ss_adjust_

#ifndef _di_f_uint32ss_append_
  f_status_t f_uint32ss_append(const f_uint32s_t source, f_uint32ss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_uint32ss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_uint32s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_uint32ss_append_

#ifndef _di_f_uint32ss_append_all_
  f_status_t f_uint32ss_append_all(const f_uint32ss_t source, f_uint32ss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint32ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_uint32s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_uint32ss_append_all_

#ifndef _di_f_uint32ss_decimate_by_
  f_status_t f_uint32ss_decimate_by(const f_number_unsigned_t amount, f_uint32ss_t * const uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint32ss->size - amount > 0) {
      return private_f_uint32ss_adjust(uint32ss->size - amount, uint32ss);
    }

    return private_f_uint32ss_adjust(0, uint32ss);
  }
#endif // _di_f_uint32ss_decimate_by_

#ifndef _di_f_uint32ss_decrease_by_
  f_status_t f_uint32ss_decrease_by(const f_number_unsigned_t amount, f_uint32ss_t * const uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint32ss->size - amount > 0) {
      return private_f_uint32ss_resize(uint32ss->size - amount, uint32ss);
    }

    return private_f_uint32ss_resize(0, uint32ss);
  }
#endif // _di_f_uint32ss_decrease_by_

#ifndef _di_f_uint32ss_increase_
  f_status_t f_uint32ss_increase(const f_number_unsigned_t step, f_uint32ss_t * const uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint32ss->used + 1 > uint32ss->size) {
      f_number_unsigned_t size = uint32ss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (uint32ss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_uint32ss_resize(size, uint32ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint32ss_increase_

#ifndef _di_f_uint32ss_increase_by_
  f_status_t f_uint32ss_increase_by(const f_number_unsigned_t amount, f_uint32ss_t * const uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint32ss->used + amount > uint32ss->size) {
      if (uint32ss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint32ss_resize(uint32ss->used + amount, uint32ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint32ss_increase_by_

#ifndef _di_f_uint32ss_resize_
  f_status_t f_uint32ss_resize(const f_number_unsigned_t length, f_uint32ss_t * const uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32ss_resize(length, uint32ss);
  }
#endif // _di_f_uint32ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

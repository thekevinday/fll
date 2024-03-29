#include "../type_array.h"
#include "uint128.h"
#include "private-uint128.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint128s_adjust_
  f_status_t f_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint128s_adjust(length, uint128s);
  }
#endif // _di_f_uint128s_adjust_

#ifndef _di_f_uint128s_append_
  f_status_t f_uint128s_append(const uint128_t source, f_uint128s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint128s_append(source, destination);
  }
#endif // _di_f_uint128s_append_

#ifndef _di_f_uint128s_append_all_
  f_status_t f_uint128s_append_all(const f_uint128s_t source, f_uint128s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint128s_append_all(source, destination);
  }
#endif // _di_f_uint128s_append_all_

#ifndef _di_f_uint128s_decimate_by_
  f_status_t f_uint128s_decimate_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint128s->size - amount > 0) {
      return private_f_uint128s_adjust(uint128s->size - amount, uint128s);
    }

    return private_f_uint128s_adjust(0, uint128s);
  }
#endif // _di_f_uint128s_decimate_by_

#ifndef _di_f_uint128s_decrease_by_
  f_status_t f_uint128s_decrease_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint128s->size - amount > 0) {
      return private_f_uint128s_resize(uint128s->size - amount, uint128s);
    }

    return private_f_uint128s_resize(0, uint128s);
  }
#endif // _di_f_uint128s_decrease_by_

#ifndef _di_f_uint128s_increase_
  f_status_t f_uint128s_increase(const f_array_length_t step, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint128s->used + 1 > uint128s->size) {
      f_array_length_t size = uint128s->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint128s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint128s_resize(size, uint128s);
    }

    return F_data_not;
  }
#endif // _di_f_uint128s_increase_

#ifndef _di_f_uint128s_increase_by_
  f_status_t f_uint128s_increase_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint128s->used + amount > uint128s->size) {
      if (uint128s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint128s_resize(uint128s->used + amount, uint128s);
    }

    return F_data_not;
  }
#endif // _di_f_uint128s_increase_by_

#ifndef _di_f_uint128s_resize_
  f_status_t f_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint128s_resize(length, uint128s);
  }
#endif // _di_f_uint128s_resize_

#ifndef _di_f_uint128ss_adjust_
  f_status_t f_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint128ss_adjust(length, uint128ss);
  }
#endif // _di_f_uint128ss_adjust_

#ifndef _di_f_uint128ss_append_
  f_status_t f_uint128ss_append(const f_uint128s_t source, f_uint128ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_uint128ss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_uint128s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_uint128ss_append_

#ifndef _di_f_uint128ss_append_all_
  f_status_t f_uint128ss_append_all(const f_uint128ss_t source, f_uint128ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint128ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_uint128s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_uint128ss_append_all_

#ifndef _di_f_uint128ss_decimate_by_
  f_status_t f_uint128ss_decimate_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint128ss->size - amount > 0) {
      return private_f_uint128ss_adjust(uint128ss->size - amount, uint128ss);
    }

    return private_f_uint128ss_adjust(0, uint128ss);
  }
#endif // _di_f_uint128ss_decimate_by_

#ifndef _di_f_uint128ss_decrease_by_
  f_status_t f_uint128ss_decrease_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint128ss->size - amount > 0) {
      return private_f_uint128ss_resize(uint128ss->size - amount, uint128ss);
    }

    return private_f_uint128ss_resize(0, uint128ss);
  }
#endif // _di_f_uint128ss_decrease_by_

#ifndef _di_f_uint128ss_increase_
  f_status_t f_uint128ss_increase(const f_array_length_t step, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint128ss->used + 1 > uint128ss->size) {
      f_array_length_t size = uint128ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint128ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint128ss_resize(size, uint128ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint128ss_increase_

#ifndef _di_f_uint128ss_increase_by_
  f_status_t f_uint128ss_increase_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint128ss->used + amount > uint128ss->size) {
      if (uint128ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint128ss_resize(uint128ss->used + amount, uint128ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint128ss_increase_by_

#ifndef _di_f_uint128ss_resize_
  f_status_t f_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint128ss_resize(length, uint128ss);
  }
#endif // _di_f_uint128ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

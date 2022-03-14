#include "../type_array.h"
#include "uint64.h"
#include "private-uint64.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint64s_adjust_
  f_status_t f_uint64s_adjust(const f_array_length_t length, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint64s_adjust(length, uint64s);
  }
#endif // _di_f_uint64s_adjust_

#ifndef _di_f_uint64s_append_
  f_status_t f_uint64s_append(const uint64_t source, f_uint64s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint64s_append(source, destination);
  }
#endif // _di_f_uint64s_append_

#ifndef _di_f_uint64s_append_all_
  f_status_t f_uint64s_append_all(const f_uint64s_t source, f_uint64s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint64s_append_all(source, destination);
  }
#endif // _di_f_uint64s_append_all_

#ifndef _di_f_uint64s_decimate_by_
  f_status_t f_uint64s_decimate_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint64s->size - amount > 0) {
      return private_f_uint64s_adjust(uint64s->size - amount, uint64s);
    }

    return private_f_uint64s_adjust(0, uint64s);
  }
#endif // _di_f_uint64s_decimate_by_

#ifndef _di_f_uint64s_decrease_by_
  f_status_t f_uint64s_decrease_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint64s->size - amount > 0) {
      return private_f_uint64s_resize(uint64s->size - amount, uint64s);
    }

    return private_f_uint64s_resize(0, uint64s);
  }
#endif // _di_f_uint64s_decrease_by_

#ifndef _di_f_uint64s_increase_
  f_status_t f_uint64s_increase(const f_array_length_t step, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint64s->used + 1 > uint64s->size) {
      f_array_length_t size = uint64s->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint64s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint64s_resize(size, uint64s);
    }

    return F_data_not;
  }
#endif // _di_f_uint64s_increase_

#ifndef _di_f_uint64s_increase_by_
  f_status_t f_uint64s_increase_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint64s->used + amount > uint64s->size) {
      if (uint64s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint64s_resize(uint64s->used + amount, uint64s);
    }

    return F_data_not;
  }
#endif // _di_f_uint64s_increase_by_

#ifndef _di_f_uint64s_resize_
  f_status_t f_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint64s_resize(length, uint64s);
  }
#endif // _di_f_uint64s_resize_

#ifndef _di_f_uint64ss_adjust_
  f_status_t f_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint64ss_adjust(length, uint64ss);
  }
#endif // _di_f_uint64ss_adjust_

#ifndef _di_f_uint64ss_append_
  f_status_t f_uint64ss_append(const f_uint64s_t source, f_uint64ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_uint64ss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_uint64s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_uint64ss_append_

#ifndef _di_f_uint64ss_append_all_
  f_status_t f_uint64ss_append_all(const f_uint64ss_t source, f_uint64ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint64ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_uint64s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_uint64ss_append_all_

#ifndef _di_f_uint64ss_decimate_by_
  f_status_t f_uint64ss_decimate_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint64ss->size - amount > 0) {
      return private_f_uint64ss_adjust(uint64ss->size - amount, uint64ss);
    }

    return private_f_uint64ss_adjust(0, uint64ss);
  }
#endif // _di_f_uint64ss_decimate_by_

#ifndef _di_f_uint64ss_decrease_by_
  f_status_t f_uint64ss_decrease_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint64ss->size - amount > 0) {
      return private_f_uint64ss_resize(uint64ss->size - amount, uint64ss);
    }

    return private_f_uint64ss_resize(0, uint64ss);
  }
#endif // _di_f_uint64ss_decrease_by_

#ifndef _di_f_uint64ss_increase_
  f_status_t f_uint64ss_increase(const f_array_length_t step, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint64ss->used + 1 > uint64ss->size) {
      f_array_length_t size = uint64ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint64ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint64ss_resize(size, uint64ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint64ss_increase_

#ifndef _di_f_uint64ss_increase_by_
  f_status_t f_uint64ss_increase_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint64ss->used + amount > uint64ss->size) {
      if (uint64ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint64ss_resize(uint64ss->used + amount, uint64ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint64ss_increase_by_

#ifndef _di_f_uint64ss_resize_
  f_status_t f_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint64ss_resize(length, uint64ss);
  }
#endif // _di_f_uint64ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

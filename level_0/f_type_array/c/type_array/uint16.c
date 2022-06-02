#include "../type_array.h"
#include "uint16.h"
#include "private-uint16.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint16s_adjust_
  f_status_t f_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16s_adjust(length, uint16s);
  }
#endif // _di_f_uint16s_adjust_

#ifndef _di_f_uint16s_append_
  f_status_t f_uint16s_append(const uint16_t source, f_uint16s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16s_append(source, destination);
  }
#endif // _di_f_uint16s_append_

#ifndef _di_f_uint16s_append_all_
  f_status_t f_uint16s_append_all(const f_uint16s_t source, f_uint16s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint16s_append_all(source, destination);
  }
#endif // _di_f_uint16s_append_all_

#ifndef _di_f_uint16s_decimate_by_
  f_status_t f_uint16s_decimate_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint16s->size - amount > 0) {
      return private_f_uint16s_adjust(uint16s->size - amount, uint16s);
    }

    return private_f_uint16s_adjust(0, uint16s);
  }
#endif // _di_f_uint16s_decimate_by_

#ifndef _di_f_uint16s_decrease_by_
  f_status_t f_uint16s_decrease_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint16s->size - amount > 0) {
      return private_f_uint16s_resize(uint16s->size - amount, uint16s);
    }

    return private_f_uint16s_resize(0, uint16s);
  }
#endif // _di_f_uint16s_decrease_by_

#ifndef _di_f_uint16s_increase_
  f_status_t f_uint16s_increase(const f_array_length_t step, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint16s->used + 1 > uint16s->size) {
      f_array_length_t size = uint16s->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint16s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint16s_resize(size, uint16s);
    }

    return F_data_not;
  }
#endif // _di_f_uint16s_increase_

#ifndef _di_f_uint16s_increase_by_
  f_status_t f_uint16s_increase_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint16s->used + amount > uint16s->size) {
      if (uint16s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint16s_resize(uint16s->used + amount, uint16s);
    }

    return F_data_not;
  }
#endif // _di_f_uint16s_increase_by_

#ifndef _di_f_uint16s_resize_
  f_status_t f_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16s_resize(length, uint16s);
  }
#endif // _di_f_uint16s_resize_

#ifndef _di_f_uint16ss_adjust_
  f_status_t f_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16ss_adjust(length, uint16ss);
  }
#endif // _di_f_uint16ss_adjust_

#ifndef _di_f_uint16ss_append_
  f_status_t f_uint16ss_append(const f_uint16s_t source, f_uint16ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_uint16ss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_uint16s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_uint16ss_append_

#ifndef _di_f_uint16ss_append_all_
  f_status_t f_uint16ss_append_all(const f_uint16ss_t source, f_uint16ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint16ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_uint16s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_uint16ss_append_all_

#ifndef _di_f_uint16ss_decimate_by_
  f_status_t f_uint16ss_decimate_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint16ss->size - amount > 0) {
      return private_f_uint16ss_adjust(uint16ss->size - amount, uint16ss);
    }

    return private_f_uint16ss_adjust(0, uint16ss);
  }
#endif // _di_f_uint16ss_decimate_by_

#ifndef _di_f_uint16ss_decrease_by_
  f_status_t f_uint16ss_decrease_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint16ss->size - amount > 0) {
      return private_f_uint16ss_resize(uint16ss->size - amount, uint16ss);
    }

    return private_f_uint16ss_resize(0, uint16ss);
  }
#endif // _di_f_uint16ss_decrease_by_

#ifndef _di_f_uint16ss_increase_
  f_status_t f_uint16ss_increase(const f_array_length_t step, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint16ss->used + 1 > uint16ss->size) {
      f_array_length_t size = uint16ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint16ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint16ss_resize(size, uint16ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint16ss_increase_

#ifndef _di_f_uint16ss_increase_by_
  f_status_t f_uint16ss_increase_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (uint16ss->used + amount > uint16ss->size) {
      if (uint16ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint16ss_resize(uint16ss->used + amount, uint16ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint16ss_increase_by_

#ifndef _di_f_uint16ss_resize_
  f_status_t f_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint16ss_resize(length, uint16ss);
  }
#endif // _di_f_uint16ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

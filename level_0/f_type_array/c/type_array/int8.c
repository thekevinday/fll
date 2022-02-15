#include "../type_array.h"
#include "int8.h"
#include "private-int8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_type_int8s_adjust_
  f_status_t f_type_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8s_adjust(length, int8s);
  }
#endif // _di_f_type_int8s_adjust_

#ifndef _di_f_type_int8s_append_
  f_status_t f_type_int8s_append(const f_int8s_t source, f_int8s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_type_int8s_append(source, destination);
  }
#endif // _di_f_type_int8s_append_

#ifndef _di_f_type_int8s_decimate_by_
  f_status_t f_type_int8s_decimate_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->size - amount > 0) {
      return private_f_type_int8s_adjust(int8s->size - amount, int8s);
    }

    return private_f_type_int8s_adjust(0, int8s);
  }
#endif // _di_f_type_int8s_decimate_by_

#ifndef _di_f_type_int8s_decrease_by_
  f_status_t f_type_int8s_decrease_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->size - amount > 0) {
      return private_f_type_int8s_resize(int8s->size - amount, int8s);
    }

    return private_f_type_int8s_resize(0, int8s);
  }
#endif // _di_f_type_int8s_decrease_by_

#ifndef _di_f_type_int8s_increase_
  f_status_t f_type_int8s_increase(const uint16_t step, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->used + 1 > int8s->size) {
      f_array_length_t size = int8s->used + step;

      if (size > F_array_length_t_size_d) {
        if (int8s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_type_int8s_resize(size, int8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8s_increase_

#ifndef _di_f_type_int8s_increase_by_
  f_status_t f_type_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->used + amount > int8s->size) {
      if (int8s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int8s_resize(int8s->used + amount, int8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8s_increase_by_

#ifndef _di_f_type_int8s_resize_
  f_status_t f_type_int8s_resize(const f_array_length_t length, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8s_resize(length, int8s);
  }
#endif // _di_f_type_int8s_resize_

#ifndef _di_f_type_int8ss_adjust_
  f_status_t f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8ss_adjust(length, int8ss);
  }
#endif // _di_f_type_int8ss_adjust_

#ifndef _di_f_type_int8ss_append_
  f_status_t f_type_int8ss_append(const f_int8ss_t source, f_int8ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int8ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_int8s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_int8ss_append_

#ifndef _di_f_type_int8ss_decimate_by_
  f_status_t f_type_int8ss_decimate_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->size - amount > 0) {
      return private_f_type_int8ss_adjust(int8ss->size - amount, int8ss);
    }

    return private_f_type_int8ss_adjust(0, int8ss);
  }
#endif // _di_f_type_int8ss_decimate_by_

#ifndef _di_f_type_int8ss_decrease_by_
  f_status_t f_type_int8ss_decrease_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->size - amount > 0) {
      return private_f_type_int8ss_resize(int8ss->size - amount, int8ss);
    }

    return private_f_type_int8ss_resize(0, int8ss);
  }
#endif // _di_f_type_int8ss_decrease_by_

#ifndef _di_f_type_int8ss_increase_
  f_status_t f_type_int8ss_increase(const uint16_t step, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->used + 1 > int8ss->size) {
      f_array_length_t size = int8ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (int8ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_type_int8ss_resize(size, int8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8ss_increase_

#ifndef _di_f_type_int8ss_increase_by_
  f_status_t f_type_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->used + amount > int8ss->size) {
      if (int8ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int8ss_resize(int8ss->used + amount, int8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8ss_increase_by_

#ifndef _di_f_type_int8ss_resize_
  f_status_t f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8ss_resize(length, int8ss);
  }
#endif // _di_f_type_int8ss_resize_

#ifndef _di_f_type_uint8s_adjust_
  f_status_t f_type_uint8s_adjust(const f_array_length_t length, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8s_adjust(length, uint8s);
  }
#endif // _di_f_type_uint8s_adjust_

#ifndef _di_f_type_uint8s_append_
  f_status_t f_type_uint8s_append(const f_uint8s_t source, f_uint8s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_type_uint8s_append(source, destination);
  }
#endif // _di_f_type_uint8s_append_

#ifndef _di_f_type_uint8s_decimate_by_
  f_status_t f_type_uint8s_decimate_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->size - amount > 0) {
      return private_f_type_uint8s_adjust(uint8s->size - amount, uint8s);
    }

    return private_f_type_uint8s_adjust(0, uint8s);
  }
#endif // _di_f_type_uint8s_decimate_by_

#ifndef _di_f_type_uint8s_decrease_by_
  f_status_t f_type_uint8s_decrease_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->size - amount > 0) {
      return private_f_type_uint8s_resize(uint8s->size - amount, uint8s);
    }

    return private_f_type_uint8s_resize(0, uint8s);
  }
#endif // _di_f_type_uint8s_decrease_by_

#ifndef _di_f_type_uint8s_increase_
  f_status_t f_type_uint8s_increase(const uint16_t step, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->used + 1 > uint8s->size) {
      f_array_length_t size = uint8s->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint8s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_type_uint8s_resize(size, uint8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8s_increase_

#ifndef _di_f_type_uint8s_increase_by_
  f_status_t f_type_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->used + amount > uint8s->size) {
      if (uint8s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint8s_resize(uint8s->used + amount, uint8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8s_increase_by_

#ifndef _di_f_type_uint8s_resize_
  f_status_t f_type_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8s_resize(length, uint8s);
  }
#endif // _di_f_type_uint8s_resize_

#ifndef _di_f_type_uint8ss_adjust_
  f_status_t f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8ss_adjust(length, uint8ss);
  }
#endif // _di_f_type_uint8ss_adjust_

#ifndef _di_f_type_uint8ss_append_
  f_status_t f_type_uint8ss_append(const f_uint8ss_t source, f_uint8ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint8ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_uint8s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_uint8ss_append_

#ifndef _di_f_type_uint8ss_decimate_by_
  f_status_t f_type_uint8ss_decimate_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->size - amount > 0) {
      return private_f_type_uint8ss_adjust(uint8ss->size - amount, uint8ss);
    }

    return private_f_type_uint8ss_adjust(0, uint8ss);
  }
#endif // _di_f_type_uint8ss_decimate_by_

#ifndef _di_f_type_uint8ss_decrease_by_
  f_status_t f_type_uint8ss_decrease_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->size - amount > 0) {
      return private_f_type_uint8ss_resize(uint8ss->size - amount, uint8ss);
    }

    return private_f_type_uint8ss_resize(0, uint8ss);
  }
#endif // _di_f_type_uint8ss_decrease_by_

#ifndef _di_f_type_uint8ss_increase_
  f_status_t f_type_uint8ss_increase(const uint16_t step, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->used + 1 > uint8ss->size) {
      f_array_length_t size = uint8ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint8ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_type_uint8ss_resize(size, uint8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8ss_increase_

#ifndef _di_f_type_uint8ss_increase_by_
  f_status_t f_type_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->used + amount > uint8ss->size) {
      if (uint8ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint8ss_resize(uint8ss->used + amount, uint8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8ss_increase_by_

#ifndef _di_f_type_uint8ss_resize_
  f_status_t f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8ss_resize(length, uint8ss);
  }
#endif // _di_f_type_uint8ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

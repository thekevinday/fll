#include "../type_array.h"
#include "int32.h"
#include "private-int32.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_int32s_adjust_
  f_status_t f_int32s_adjust(const f_array_length_t length, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int32s_adjust(length, int32s);
  }
#endif // _di_f_int32s_adjust_

#ifndef _di_f_int32s_append_
  f_status_t f_int32s_append(const f_int32s_t source, f_int32s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_int32s_append(source, destination);
  }
#endif // _di_f_int32s_append_

#ifndef _di_f_int32s_decimate_by_
  f_status_t f_int32s_decimate_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (int32s->size - amount > 0) {
      return private_f_int32s_adjust(int32s->size - amount, int32s);
    }

    return private_f_int32s_adjust(0, int32s);
  }
#endif // _di_f_int32s_decimate_by_

#ifndef _di_f_int32s_decrease_by_
  f_status_t f_int32s_decrease_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (int32s->size - amount > 0) {
      return private_f_int32s_resize(int32s->size - amount, int32s);
    }

    return private_f_int32s_resize(0, int32s);
  }
#endif // _di_f_int32s_decrease_by_

#ifndef _di_f_int32s_increase_
  f_status_t f_int32s_increase(const f_array_length_t step, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && int32s->used + 1 > int32s->size) {
      f_array_length_t size = int32s->used + step;

      if (size > F_array_length_t_size_d) {
        if (int32s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_int32s_resize(size, int32s);
    }

    return F_data_not;
  }
#endif // _di_f_int32s_increase_

#ifndef _di_f_int32s_increase_by_
  f_status_t f_int32s_increase_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (int32s->used + amount > int32s->size) {
      if (int32s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_int32s_resize(int32s->used + amount, int32s);
    }

    return F_data_not;
  }
#endif // _di_f_int32s_increase_by_

#ifndef _di_f_int32s_resize_
  f_status_t f_int32s_resize(const f_array_length_t length, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int32s_resize(length, int32s);
  }
#endif // _di_f_int32s_resize_

#ifndef _di_f_int32ss_adjust_
  f_status_t f_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int32ss_adjust(length, int32ss);
  }
#endif // _di_f_int32ss_adjust_

#ifndef _di_f_int32ss_append_
  f_status_t f_int32ss_append(const f_int32ss_t source, f_int32ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_int32ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_int32s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_int32ss_append_

#ifndef _di_f_int32ss_decimate_by_
  f_status_t f_int32ss_decimate_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (int32ss->size - amount > 0) {
      return private_f_int32ss_adjust(int32ss->size - amount, int32ss);
    }

    return private_f_int32ss_adjust(0, int32ss);
  }
#endif // _di_f_int32ss_decimate_by_

#ifndef _di_f_int32ss_decrease_by_
  f_status_t f_int32ss_decrease_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (int32ss->size - amount > 0) {
      return private_f_int32ss_resize(int32ss->size - amount, int32ss);
    }

    return private_f_int32ss_resize(0, int32ss);
  }
#endif // _di_f_int32ss_decrease_by_

#ifndef _di_f_int32ss_increase_
  f_status_t f_int32ss_increase(const f_array_length_t step, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && int32ss->used + 1 > int32ss->size) {
      f_array_length_t size = int32ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (int32ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_int32ss_resize(size, int32ss);
    }

    return F_data_not;
  }
#endif // _di_f_int32ss_increase_

#ifndef _di_f_int32ss_increase_by_
  f_status_t f_int32ss_increase_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (int32ss->used + amount > int32ss->size) {
      if (int32ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_int32ss_resize(int32ss->used + amount, int32ss);
    }

    return F_data_not;
  }
#endif // _di_f_int32ss_increase_by_

#ifndef _di_f_int32ss_resize_
  f_status_t f_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int32ss_resize(length, int32ss);
  }
#endif // _di_f_int32ss_resize_

#ifndef _di_f_uint32s_adjust_
  f_status_t f_uint32s_adjust(const f_array_length_t length, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32s_adjust(length, uint32s);
  }
#endif // _di_f_uint32s_adjust_

#ifndef _di_f_uint32s_append_
  f_status_t f_uint32s_append(const f_uint32s_t source, f_uint32s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_uint32s_append(source, destination);
  }
#endif // _di_f_uint32s_append_

#ifndef _di_f_uint32s_decimate_by_
  f_status_t f_uint32s_decimate_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint32s->size - amount > 0) {
      return private_f_uint32s_adjust(uint32s->size - amount, uint32s);
    }

    return private_f_uint32s_adjust(0, uint32s);
  }
#endif // _di_f_uint32s_decimate_by_

#ifndef _di_f_uint32s_decrease_by_
  f_status_t f_uint32s_decrease_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint32s->size - amount > 0) {
      return private_f_uint32s_resize(uint32s->size - amount, uint32s);
    }

    return private_f_uint32s_resize(0, uint32s);
  }
#endif // _di_f_uint32s_decrease_by_

#ifndef _di_f_uint32s_increase_
  f_status_t f_uint32s_increase(const f_array_length_t step, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint32s->used + 1 > uint32s->size) {
      f_array_length_t size = uint32s->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint32s->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint32s_resize(size, uint32s);
    }

    return F_data_not;
  }
#endif // _di_f_uint32s_increase_

#ifndef _di_f_uint32s_increase_by_
  f_status_t f_uint32s_increase_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint32s->used + amount > uint32s->size) {
      if (uint32s->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint32s_resize(uint32s->used + amount, uint32s);
    }

    return F_data_not;
  }
#endif // _di_f_uint32s_increase_by_

#ifndef _di_f_uint32s_resize_
  f_status_t f_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32s_resize(length, uint32s);
  }
#endif // _di_f_uint32s_resize_

#ifndef _di_f_uint32ss_adjust_
  f_status_t f_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32ss_adjust(length, uint32ss);
  }
#endif // _di_f_uint32ss_adjust_

#ifndef _di_f_uint32ss_append_
  f_status_t f_uint32ss_append(const f_uint32ss_t source, f_uint32ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_uint32ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_uint32s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_uint32ss_append_

#ifndef _di_f_uint32ss_decimate_by_
  f_status_t f_uint32ss_decimate_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint32ss->size - amount > 0) {
      return private_f_uint32ss_adjust(uint32ss->size - amount, uint32ss);
    }

    return private_f_uint32ss_adjust(0, uint32ss);
  }
#endif // _di_f_uint32ss_decimate_by_

#ifndef _di_f_uint32ss_decrease_by_
  f_status_t f_uint32ss_decrease_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint32ss->size - amount > 0) {
      return private_f_uint32ss_resize(uint32ss->size - amount, uint32ss);
    }

    return private_f_uint32ss_resize(0, uint32ss);
  }
#endif // _di_f_uint32ss_decrease_by_

#ifndef _di_f_uint32ss_increase_
  f_status_t f_uint32ss_increase(const f_array_length_t step, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && uint32ss->used + 1 > uint32ss->size) {
      f_array_length_t size = uint32ss->used + step;

      if (size > F_array_length_t_size_d) {
        if (uint32ss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_uint32ss_resize(size, uint32ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint32ss_increase_

#ifndef _di_f_uint32ss_increase_by_
  f_status_t f_uint32ss_increase_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (uint32ss->used + amount > uint32ss->size) {
      if (uint32ss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_uint32ss_resize(uint32ss->used + amount, uint32ss);
    }

    return F_data_not;
  }
#endif // _di_f_uint32ss_increase_by_

#ifndef _di_f_uint32ss_resize_
  f_status_t f_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_uint32ss_resize(length, uint32ss);
  }
#endif // _di_f_uint32ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#include "../type_array.h"
#include "int128.h"
#include "private-int128.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_int128s_adjust_
  f_status_t f_int128s_adjust(const f_number_unsigned_t length, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int128s_adjust(length, int128s);
  }
#endif // _di_f_int128s_adjust_

#ifndef _di_f_int128s_append_
  f_status_t f_int128s_append(const int128_t source, f_int128s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int128s_append(source, destination);
  }
#endif // _di_f_int128s_append_

#ifndef _di_f_int128s_append_all_
  f_status_t f_int128s_append_all(const f_int128s_t source, f_int128s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_int128s_append_all(source, destination);
  }
#endif // _di_f_int128s_append_all_

#ifndef _di_f_int128s_decimate_by_
  f_status_t f_int128s_decimate_by(const f_number_unsigned_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (int128s->size - amount > 0) {
      return private_f_int128s_adjust(int128s->size - amount, int128s);
    }

    return private_f_int128s_adjust(0, int128s);
  }
#endif // _di_f_int128s_decimate_by_

#ifndef _di_f_int128s_decrease_by_
  f_status_t f_int128s_decrease_by(const f_number_unsigned_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (int128s->size - amount > 0) {
      return private_f_int128s_resize(int128s->size - amount, int128s);
    }

    return private_f_int128s_resize(0, int128s);
  }
#endif // _di_f_int128s_decrease_by_

#ifndef _di_f_int128s_increase_
  f_status_t f_int128s_increase(const f_number_unsigned_t step, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && int128s->used + 1 > int128s->size) {
      f_number_unsigned_t size = int128s->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (int128s->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_int128s_resize(size, int128s);
    }

    return F_data_not;
  }
#endif // _di_f_int128s_increase_

#ifndef _di_f_int128s_increase_by_
  f_status_t f_int128s_increase_by(const f_number_unsigned_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (int128s->used + amount > int128s->size) {
      if (int128s->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_int128s_resize(int128s->used + amount, int128s);
    }

    return F_data_not;
  }
#endif // _di_f_int128s_increase_by_

#ifndef _di_f_int128s_resize_
  f_status_t f_int128s_resize(const f_number_unsigned_t length, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int128s_resize(length, int128s);
  }
#endif // _di_f_int128s_resize_

#ifndef _di_f_int128ss_adjust_
  f_status_t f_int128ss_adjust(const f_number_unsigned_t length, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int128ss_adjust(length, int128ss);
  }
#endif // _di_f_int128ss_adjust_

#ifndef _di_f_int128ss_append_
  f_status_t f_int128ss_append(const f_int128s_t source, f_int128ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_int128ss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_int128s_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_int128ss_append_

#ifndef _di_f_int128ss_append_all_
  f_status_t f_int128ss_append_all(const f_int128ss_t source, f_int128ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_int128ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_int128s_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_int128ss_append_all_

#ifndef _di_f_int128ss_decimate_by_
  f_status_t f_int128ss_decimate_by(const f_number_unsigned_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (int128ss->size - amount > 0) {
      return private_f_int128ss_adjust(int128ss->size - amount, int128ss);
    }

    return private_f_int128ss_adjust(0, int128ss);
  }
#endif // _di_f_int128ss_decimate_by_

#ifndef _di_f_int128ss_decrease_by_
  f_status_t f_int128ss_decrease_by(const f_number_unsigned_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (int128ss->size - amount > 0) {
      return private_f_int128ss_resize(int128ss->size - amount, int128ss);
    }

    return private_f_int128ss_resize(0, int128ss);
  }
#endif // _di_f_int128ss_decrease_by_

#ifndef _di_f_int128ss_increase_
  f_status_t f_int128ss_increase(const f_number_unsigned_t step, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && int128ss->used + 1 > int128ss->size) {
      f_number_unsigned_t size = int128ss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (int128ss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_int128ss_resize(size, int128ss);
    }

    return F_data_not;
  }
#endif // _di_f_int128ss_increase_

#ifndef _di_f_int128ss_increase_by_
  f_status_t f_int128ss_increase_by(const f_number_unsigned_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (int128ss->used + amount > int128ss->size) {
      if (int128ss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_int128ss_resize(int128ss->used + amount, int128ss);
    }

    return F_data_not;
  }
#endif // _di_f_int128ss_increase_by_

#ifndef _di_f_int128ss_resize_
  f_status_t f_int128ss_resize(const f_number_unsigned_t length, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_int128ss_resize(length, int128ss);
  }
#endif // _di_f_int128ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

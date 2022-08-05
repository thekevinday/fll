#include "../limit.h"
#include "set.h"
#include "private-set.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_limit_sets_adjust_
  f_status_t f_limit_sets_adjust(const f_array_length_t length, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_sets_adjust(length, sets);
  }
#endif // _di_f_limit_sets_adjust_

#ifndef _di_f_limit_sets_append_
  f_status_t f_limit_sets_append(const f_limit_set_t source, f_limit_sets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_sets_append(source, destination);
  }
#endif // _di_f_limit_sets_append_

#ifndef _di_f_limit_sets_append_all_
  f_status_t f_limit_sets_append_all(const f_limit_sets_t source, f_limit_sets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_limit_sets_append_all(source, destination);
  }
#endif // _di_f_limit_sets_append_all_

#ifndef _di_f_limit_sets_decimate_by_
  f_status_t f_limit_sets_decimate_by(const f_array_length_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sets->size > amount) {
      return private_f_limit_sets_adjust(sets->size - amount, sets);
    }

    return private_f_limit_sets_adjust(0, sets);
  }
#endif // _di_f_limit_sets_decimate_by_

#ifndef _di_f_limit_sets_decrease_by_
  f_status_t f_limit_sets_decrease_by(const f_array_length_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sets->size > amount) {
      return private_f_limit_sets_resize(sets->size - amount, sets);
    }

    return private_f_limit_sets_resize(0, sets);
  }
#endif // _di_f_limit_sets_decrease_by_

#ifndef _di_f_limit_sets_increase_
  f_status_t f_limit_sets_increase(const f_array_length_t step, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && sets->used + 1 > sets->size) {
      f_array_length_t size = sets->used + step;

      if (size > F_array_length_t_size_d) {
        if (sets->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_limit_sets_resize(size, sets);
    }

    return F_data_not;
  }
#endif // _di_f_limit_sets_increase_

#ifndef _di_f_limit_sets_increase_by_
  f_status_t f_limit_sets_increase_by(const f_array_length_t amount, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sets->used + amount > sets->size) {
      if (sets->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_limit_sets_resize(sets->used + amount, sets);
    }

    return F_data_not;
  }
#endif // _di_f_limit_sets_increase_by_

#ifndef _di_f_limit_sets_resize_
  f_status_t f_limit_sets_resize(const f_array_length_t length, f_limit_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_sets_resize(length, sets);
  }
#endif // _di_f_limit_sets_resize_

#ifndef _di_f_limit_setss_adjust_
  f_status_t f_limit_setss_adjust(const f_array_length_t length, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_setss_adjust(length, setss);
  }
#endif // _di_f_limit_setss_adjust_

#ifndef _di_f_limit_setss_append_
  f_status_t f_limit_setss_append(const f_limit_sets_t source, f_limit_setss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_limit_setss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_limit_sets_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_limit_setss_append_

#ifndef _di_f_limit_setss_append_all_
  f_status_t f_limit_setss_append_all(const f_limit_setss_t source, f_limit_setss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_limit_setss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_limit_sets_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_limit_setss_append_all_

#ifndef _di_f_limit_setss_decimate_by_
  f_status_t f_limit_setss_decimate_by(const f_array_length_t amount, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (setss->size > amount) {
      return private_f_limit_setss_adjust(setss->size - amount, setss);
    }

    return private_f_limit_setss_adjust(0, setss);
  }
#endif // _di_f_limit_setss_decimate_by_

#ifndef _di_f_limit_setss_decrease_by_
  f_status_t f_limit_setss_decrease_by(const f_array_length_t amount, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (setss->size > amount) {
      return private_f_limit_setss_resize(setss->size - amount, setss);
    }

    return private_f_limit_setss_resize(0, setss);
  }
#endif // _di_f_limit_setss_decrease_by_

#ifndef _di_f_limit_setss_increase_
  f_status_t f_limit_setss_increase(const f_array_length_t step, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && setss->used + 1 > setss->size) {
      f_array_length_t size = setss->used + step;

      if (size > F_array_length_t_size_d) {
        if (setss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_limit_setss_resize(size, setss);
    }

    return F_data_not;
  }
#endif // _di_f_limit_setss_increase_

#ifndef _di_f_limit_setss_increase_by_
  f_status_t f_limit_setss_increase_by(const f_array_length_t amount, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (setss->used + amount > setss->size) {
      if (setss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_limit_setss_resize(setss->used + amount, setss);
    }

    return F_data_not;
  }
#endif // _di_f_limit_setss_increase_by_

#ifndef _di_f_limit_setss_resize_
  f_status_t f_limit_setss_resize(const f_array_length_t length, f_limit_setss_t *setss) {
    #ifndef _di_level_0_parameter_checking_
      if (!setss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_limit_setss_resize(length, setss);
  }
#endif // _di_f_limit_setss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

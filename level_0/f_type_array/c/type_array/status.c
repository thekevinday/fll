#include "../type_array.h"
#include "status.h"
#include "private-status.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_statuss_adjust_
  f_status_t f_statuss_adjust(const f_array_length_t length, f_statuss_t *statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statuss_adjust(length, statuss);
  }
#endif // _di_f_statuss_adjust_

#ifndef _di_f_statuss_append_
  f_status_t f_statuss_append(const f_status_t source, f_statuss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statuss_append(source, destination);
  }
#endif // _di_f_statuss_append_

#ifndef _di_f_statuss_append_all_
  f_status_t f_statuss_append_all(const f_statuss_t source, f_statuss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_statuss_append_all(source, destination);
  }
#endif // _di_f_statuss_append_all_

#ifndef _di_f_statuss_decimate_by_
  f_status_t f_statuss_decimate_by(const f_array_length_t amount, f_statuss_t *statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statuss->size - amount > 0) {
      return private_f_statuss_adjust(statuss->size - amount, statuss);
    }

    return private_f_statuss_adjust(0, statuss);
  }
#endif // _di_f_statuss_decimate_by_

#ifndef _di_f_statuss_decrease_by_
  f_status_t f_statuss_decrease_by(const f_array_length_t amount, f_statuss_t *statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statuss->size - amount > 0) {
      return private_f_statuss_resize(statuss->size - amount, statuss);
    }

    return private_f_statuss_resize(0, statuss);
  }
#endif // _di_f_statuss_decrease_by_

#ifndef _di_f_statuss_increase_
  f_status_t f_statuss_increase(const f_array_length_t step, f_statuss_t *statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && statuss->used + 1 > statuss->size) {
      f_array_length_t size = statuss->used + step;

      if (size > F_array_length_t_size_d) {
        if (statuss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_statuss_resize(size, statuss);
    }

    return F_data_not;
  }
#endif // _di_f_statuss_increase_

#ifndef _di_f_statuss_increase_by_
  f_status_t f_statuss_increase_by(const f_array_length_t amount, f_statuss_t *statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statuss->used + amount > statuss->size) {
      if (statuss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_statuss_resize(statuss->used + amount, statuss);
    }

    return F_data_not;
  }
#endif // _di_f_statuss_increase_by_

#ifndef _di_f_statuss_resize_
  f_status_t f_statuss_resize(const f_array_length_t length, f_statuss_t *statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statuss_resize(length, statuss);
  }
#endif // _di_f_statuss_resize_

#ifndef _di_f_statusss_adjust_
  f_status_t f_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statusss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statusss_adjust(length, statusss);
  }
#endif // _di_f_statusss_adjust_

#ifndef _di_f_statusss_append_
  f_status_t f_statusss_append(const f_statuss_t source, f_statusss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_statusss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_statuss_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_statusss_append_

#ifndef _di_f_statusss_append_all_
  f_status_t f_statusss_append_all(const f_statusss_t source, f_statusss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_statusss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_statuss_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_statusss_append_all_

#ifndef _di_f_statusss_decimate_by_
  f_status_t f_statusss_decimate_by(const f_array_length_t amount, f_statusss_t *statusss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statusss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statusss->size - amount > 0) {
      return private_f_statusss_adjust(statusss->size - amount, statusss);
    }

    return private_f_statusss_adjust(0, statusss);
  }
#endif // _di_f_statusss_decimate_by_

#ifndef _di_f_statusss_decrease_by_
  f_status_t f_statusss_decrease_by(const f_array_length_t amount, f_statusss_t *statusss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statusss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statusss->size - amount > 0) {
      return private_f_statusss_resize(statusss->size - amount, statusss);
    }

    return private_f_statusss_resize(0, statusss);
  }
#endif // _di_f_statusss_decrease_by_

#ifndef _di_f_statusss_increase_
  f_status_t f_statusss_increase(const f_array_length_t step, f_statusss_t *statusss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statusss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && statusss->used + 1 > statusss->size) {
      f_array_length_t size = statusss->used + step;

      if (size > F_array_length_t_size_d) {
        if (statusss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_statusss_resize(size, statusss);
    }

    return F_data_not;
  }
#endif // _di_f_statusss_increase_

#ifndef _di_f_statusss_increase_by_
  f_status_t f_statusss_increase_by(const f_array_length_t amount, f_statusss_t *statusss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statusss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statusss->used + amount > statusss->size) {
      if (statusss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_statusss_resize(statusss->used + amount, statusss);
    }

    return F_data_not;
  }
#endif // _di_f_statusss_increase_by_

#ifndef _di_f_statusss_resize_
  f_status_t f_statusss_resize(const f_array_length_t length, f_statusss_t *statusss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statusss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statusss_resize(length, statusss);
  }
#endif // _di_f_statusss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

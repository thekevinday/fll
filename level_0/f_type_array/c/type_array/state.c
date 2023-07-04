#include "../type_array.h"
#include "state.h"
#include "private-state.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_states_adjust_
  f_status_t f_states_adjust(const f_number_unsigned_t length, f_states_t * const states) {
    #ifndef _di_level_0_parameter_checking_
      if (!states) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_states_adjust(length, states);
  }
#endif // _di_f_states_adjust_

#ifndef _di_f_states_append_
  f_status_t f_states_append(const f_state_t source, f_states_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_states_append(source, destination);
  }
#endif // _di_f_states_append_

#ifndef _di_f_states_append_all_
  f_status_t f_states_append_all(const f_states_t source, f_states_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_states_append_all(source, destination);
  }
#endif // _di_f_states_append_all_

#ifndef _di_f_states_decimate_by_
  f_status_t f_states_decimate_by(const f_number_unsigned_t amount, f_states_t * const states) {
    #ifndef _di_level_0_parameter_checking_
      if (!states) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (states->size - amount > 0) {
      return private_f_states_adjust(states->size - amount, states);
    }

    return private_f_states_adjust(0, states);
  }
#endif // _di_f_states_decimate_by_

#ifndef _di_f_states_decrease_by_
  f_status_t f_states_decrease_by(const f_number_unsigned_t amount, f_states_t * const states) {
    #ifndef _di_level_0_parameter_checking_
      if (!states) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (states->size - amount > 0) {
      return private_f_states_resize(states->size - amount, states);
    }

    return private_f_states_resize(0, states);
  }
#endif // _di_f_states_decrease_by_

#ifndef _di_f_states_increase_
  f_status_t f_states_increase(const f_number_unsigned_t step, f_states_t * const states) {
    #ifndef _di_level_0_parameter_checking_
      if (!states) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && states->used + 1 > states->size) {
      f_number_unsigned_t size = states->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (states->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_states_resize(size, states);
    }

    return F_data_not;
  }
#endif // _di_f_states_increase_

#ifndef _di_f_states_increase_by_
  f_status_t f_states_increase_by(const f_number_unsigned_t amount, f_states_t * const states) {
    #ifndef _di_level_0_parameter_checking_
      if (!states) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (states->used + amount > states->size) {
      if (states->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_states_resize(states->used + amount, states);
    }

    return F_data_not;
  }
#endif // _di_f_states_increase_by_

#ifndef _di_f_states_resize_
  f_status_t f_states_resize(const f_number_unsigned_t length, f_states_t * const states) {
    #ifndef _di_level_0_parameter_checking_
      if (!states) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_states_resize(length, states);
  }
#endif // _di_f_states_resize_

#ifndef _di_f_statess_adjust_
  f_status_t f_statess_adjust(const f_number_unsigned_t length, f_statess_t * const statess) {
    #ifndef _di_level_0_parameter_checking_
      if (!statess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statess_adjust(length, statess);
  }
#endif // _di_f_statess_adjust_

#ifndef _di_f_statess_append_
  f_status_t f_statess_append(const f_states_t source, f_statess_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_statess_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_states_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_statess_append_

#ifndef _di_f_statess_append_all_
  f_status_t f_statess_append_all(const f_statess_t source, f_statess_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_statess_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_states_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_statess_append_all_

#ifndef _di_f_statess_decimate_by_
  f_status_t f_statess_decimate_by(const f_number_unsigned_t amount, f_statess_t * const statess) {
    #ifndef _di_level_0_parameter_checking_
      if (!statess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statess->size - amount > 0) {
      return private_f_statess_adjust(statess->size - amount, statess);
    }

    return private_f_statess_adjust(0, statess);
  }
#endif // _di_f_statess_decimate_by_

#ifndef _di_f_statess_decrease_by_
  f_status_t f_statess_decrease_by(const f_number_unsigned_t amount, f_statess_t * const statess) {
    #ifndef _di_level_0_parameter_checking_
      if (!statess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statess->size - amount > 0) {
      return private_f_statess_resize(statess->size - amount, statess);
    }

    return private_f_statess_resize(0, statess);
  }
#endif // _di_f_statess_decrease_by_

#ifndef _di_f_statess_increase_
  f_status_t f_statess_increase(const f_number_unsigned_t step, f_statess_t * const statess) {
    #ifndef _di_level_0_parameter_checking_
      if (!statess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && statess->used + 1 > statess->size) {
      f_number_unsigned_t size = statess->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (statess->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_statess_resize(size, statess);
    }

    return F_data_not;
  }
#endif // _di_f_statess_increase_

#ifndef _di_f_statess_increase_by_
  f_status_t f_statess_increase_by(const f_number_unsigned_t amount, f_statess_t * const statess) {
    #ifndef _di_level_0_parameter_checking_
      if (!statess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (statess->used + amount > statess->size) {
      if (statess->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_statess_resize(statess->used + amount, statess);
    }

    return F_data_not;
  }
#endif // _di_f_statess_increase_by_

#ifndef _di_f_statess_resize_
  f_status_t f_statess_resize(const f_number_unsigned_t length, f_statess_t * const statess) {
    #ifndef _di_level_0_parameter_checking_
      if (!statess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_statess_resize(length, statess);
  }
#endif // _di_f_statess_resize_

#ifdef __cplusplus
} // extern "C"
#endif

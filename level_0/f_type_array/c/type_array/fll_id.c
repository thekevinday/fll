#include "../type_array.h"
#include "fll_id.h"
#include "private-fll_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fll_ids_adjust_
  f_status_t f_fll_ids_adjust(const f_array_length_t length, f_fll_ids_t *ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_ids_adjust(length, ids);
  }
#endif // _di_f_fll_ids_adjust_

#ifndef _di_f_fll_ids_append_
  f_status_t f_fll_ids_append(const f_fll_id_t source, f_fll_ids_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_ids_append(source, destination);
  }
#endif // _di_f_fll_ids_append_

#ifndef _di_f_fll_ids_append_all_
  f_status_t f_fll_ids_append_all(const f_fll_ids_t source, f_fll_ids_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_fll_ids_append_all(source, destination);
  }
#endif // _di_f_fll_ids_append_all_

#ifndef _di_f_fll_ids_decimate_by_
  f_status_t f_fll_ids_decimate_by(const f_array_length_t amount, f_fll_ids_t *ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (ids->size - amount > 0) {
      return private_f_fll_ids_adjust(ids->size - amount, ids);
    }

    return private_f_fll_ids_adjust(0, ids);
  }
#endif // _di_f_fll_ids_decimate_by_

#ifndef _di_f_fll_ids_decrease_by_
  f_status_t f_fll_ids_decrease_by(const f_array_length_t amount, f_fll_ids_t *ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (ids->size - amount > 0) {
      return private_f_fll_ids_resize(ids->size - amount, ids);
    }

    return private_f_fll_ids_resize(0, ids);
  }
#endif // _di_f_fll_ids_decrease_by_

#ifndef _di_f_fll_ids_increase_
  f_status_t f_fll_ids_increase(const f_array_length_t step, f_fll_ids_t *ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && ids->used + 1 > ids->size) {
      f_array_length_t size = ids->used + step;

      if (size > F_array_length_t_size_d) {
        if (ids->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_fll_ids_resize(size, ids);
    }

    return F_data_not;
  }
#endif // _di_f_fll_ids_increase_

#ifndef _di_f_fll_ids_increase_by_
  f_status_t f_fll_ids_increase_by(const f_array_length_t amount, f_fll_ids_t *ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (ids->used + amount > ids->size) {
      if (ids->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fll_ids_resize(ids->used + amount, ids);
    }

    return F_data_not;
  }
#endif // _di_f_fll_ids_increase_by_

#ifndef _di_f_fll_ids_resize_
  f_status_t f_fll_ids_resize(const f_array_length_t length, f_fll_ids_t *ids) {
    #ifndef _di_level_0_parameter_checking_
      if (!ids) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_ids_resize(length, ids);
  }
#endif // _di_f_fll_ids_resize_

#ifndef _di_f_fll_idss_adjust_
  f_status_t f_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *idss) {
    #ifndef _di_level_0_parameter_checking_
      if (!idss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_idss_adjust(length, idss);
  }
#endif // _di_f_fll_idss_adjust_

#ifndef _di_f_fll_idss_append_
  f_status_t f_fll_idss_append(const f_fll_ids_t source, f_fll_idss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_fll_idss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_fll_ids_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_fll_idss_append_

#ifndef _di_f_fll_idss_append_all_
  f_status_t f_fll_idss_append_all(const f_fll_idss_t source, f_fll_idss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_fll_idss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_fll_ids_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_fll_idss_append_all_

#ifndef _di_f_fll_idss_decimate_by_
  f_status_t f_fll_idss_decimate_by(const f_array_length_t amount, f_fll_idss_t *idss) {
    #ifndef _di_level_0_parameter_checking_
      if (!idss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (idss->size - amount > 0) {
      return private_f_fll_idss_adjust(idss->size - amount, idss);
    }

    return private_f_fll_idss_adjust(0, idss);
  }
#endif // _di_f_fll_idss_decimate_by_

#ifndef _di_f_fll_idss_decrease_by_
  f_status_t f_fll_idss_decrease_by(const f_array_length_t amount, f_fll_idss_t *idss) {
    #ifndef _di_level_0_parameter_checking_
      if (!idss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (idss->size - amount > 0) {
      return private_f_fll_idss_resize(idss->size - amount, idss);
    }

    return private_f_fll_idss_resize(0, idss);
  }
#endif // _di_f_fll_idss_decrease_by_

#ifndef _di_f_fll_idss_increase_
  f_status_t f_fll_idss_increase(const f_array_length_t step, f_fll_idss_t *idss) {
    #ifndef _di_level_0_parameter_checking_
      if (!idss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && idss->used + 1 > idss->size) {
      f_array_length_t size = idss->used + step;

      if (size > F_array_length_t_size_d) {
        if (idss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_fll_idss_resize(size, idss);
    }

    return F_data_not;
  }
#endif // _di_f_fll_idss_increase_

#ifndef _di_f_fll_idss_increase_by_
  f_status_t f_fll_idss_increase_by(const f_array_length_t amount, f_fll_idss_t *idss) {
    #ifndef _di_level_0_parameter_checking_
      if (!idss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (idss->used + amount > idss->size) {
      if (idss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fll_idss_resize(idss->used + amount, idss);
    }

    return F_data_not;
  }
#endif // _di_f_fll_idss_increase_by_

#ifndef _di_f_fll_idss_resize_
  f_status_t f_fll_idss_resize(const f_array_length_t length, f_fll_idss_t *idss) {
    #ifndef _di_level_0_parameter_checking_
      if (!idss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fll_idss_resize(length, idss);
  }
#endif // _di_f_fll_idss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

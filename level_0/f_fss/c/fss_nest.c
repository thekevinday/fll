#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_items_adjust_
  f_status_t f_fss_items_adjust(const f_array_length_t length, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_adjust(length, items);
  }
#endif // _di_f_fss_items_adjust_

#ifndef _di_f_fss_items_decimate_by_
  f_status_t f_fss_items_decimate_by(const f_array_length_t amount, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->size - amount > 0) {
      return private_f_fss_items_adjust(items->size - amount, items);
    }

    return private_f_fss_items_adjust(0, items);
  }
#endif // _di_f_fss_items_decimate_by_

#ifndef _di_f_fss_items_decrease_by_
  f_status_t f_fss_items_decrease_by(const f_array_length_t amount, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->size - amount > 0) {
      return private_f_fss_items_resize(items->size - amount, items);
    }

    return private_f_fss_items_resize(0, items);
  }
#endif // _di_f_fss_items_decrease_by_

#ifndef _di_f_fss_items_increase_
  f_status_t f_fss_items_increase(f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->used + 1 > items->size) {
      f_array_length_t size = items->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (items->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_items_resize(size, items);
    }

    return F_data_not;
  }
#endif // _di_f_fss_items_increase_

#ifndef _di_f_fss_items_increase_by_
  f_status_t f_fss_items_increase_by(const f_array_length_t amount, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->used + amount > items->size) {
      if (items->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_items_resize(items->used + amount, items);
    }

    return F_data_not;
  }
#endif // _di_f_fss_items_increase_by_

#ifndef _di_f_fss_items_resize_
  f_status_t f_fss_items_resize(const f_array_length_t length, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_resize(length, items);
  }
#endif // _di_f_fss_items_resize_

#ifndef _di_f_fss_nest_adjust_
  f_status_t f_fss_nest_adjust(const f_array_length_t length, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_adjust(length, nest);
  }
#endif // _di_f_fss_nest_adjust_

#ifndef _di_f_fss_nest_decimate_by_
  f_status_t f_fss_nest_decimate_by(const f_array_length_t amount, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->size - amount > 0) {
      return private_f_fss_nest_adjust(nest->size - amount, nest);
    }

    return private_f_fss_nest_adjust(0, nest);
  }
#endif // _di_f_fss_nest_decimate_by_

#ifndef _di_f_fss_nest_decrease_by_
  f_status_t f_fss_nest_decrease_by(const f_array_length_t amount, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->size - amount > 0) {
      return private_f_fss_nest_resize(nest->size - amount, nest);
    }

    return private_f_fss_nest_resize(0, nest);
  }
#endif // _di_f_fss_nest_decrease_by_

#ifndef _di_f_fss_nest_increase_
  f_status_t f_fss_nest_increase(f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->used + 1 > nest->size) {
      f_array_length_t size = nest->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (nest->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_nest_resize(size, nest);
    }

    return F_data_not;
  }
#endif // _di_f_fss_nest_increase_

#ifndef _di_f_fss_nest_increase_by_
  f_status_t f_fss_nest_increase_by(const f_array_length_t amount, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->used + amount > nest->size) {
      if (nest->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_nest_resize(nest->used + amount, nest);
    }

    return F_data_not;
  }
#endif // _di_f_fss_nest_increase_by_

#ifndef _di_f_fss_nest_resize_
  f_status_t f_fss_nest_resize(const f_array_length_t length, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_resize(length, nest);
  }
#endif // _di_f_fss_nest_resize_

#ifndef _di_f_fss_nests_adjust_
  f_status_t f_fss_nests_adjust(const f_array_length_t length, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_adjust(length, nests);
  }
#endif // _di_f_fss_nests_adjust_

#ifndef _di_f_fss_nests_decimate_by_
  f_status_t f_fss_nests_decimate_by(const f_array_length_t amount, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->size - amount > 0) {
      return private_f_fss_nests_adjust(nests->size - amount, nests);
    }

    return private_f_fss_nests_adjust(0, nests);
  }
#endif // _di_f_fss_nests_decimate_by_

#ifndef _di_f_fss_nests_decrease_by_
  f_status_t f_fss_nests_decrease_by(const f_array_length_t amount, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->size - amount > 0) {
      return private_f_fss_nests_resize(nests->size - amount, nests);
    }

    return private_f_fss_nests_resize(0, nests);
  }
#endif // _di_f_fss_nests_decrease_by_

#ifndef _di_f_fss_nests_increase_
  f_status_t f_fss_nests_increase(f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->used + 1 > nests->size) {
      f_array_length_t size = nests->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (nests->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_nests_resize(size, nests);
    }

    return F_data_not;
  }
#endif // _di_f_fss_nests_increase_

#ifndef _di_f_fss_nests_increase_by_
  f_status_t f_fss_nests_increase_by(const f_array_length_t amount, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->used + amount > nests->size) {
      if (nests->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_nests_resize(nests->used + amount, nests);
    }

    return F_data_not;
  }
#endif // _di_f_fss_nests_increase_by_

#ifndef _di_f_fss_nests_resize_
  f_status_t f_fss_nests_resize(const f_array_length_t length, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_resize(length, nests);
  }
#endif // _di_f_fss_nests_resize_

#ifdef __cplusplus
} // extern "C"
#endif

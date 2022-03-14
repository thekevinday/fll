#include "../string.h"
#include "../private-string.h"
#include "private-quantity.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_quantitys_adjust_
  f_status_t f_string_quantitys_adjust(const f_array_length_t length, f_string_quantitys_t * const quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_adjust(length, quantitys);
  }
#endif // _di_f_string_quantitys_adjust_

#ifndef _di_f_string_quantitys_append_
  f_status_t f_string_quantitys_append(const f_string_quantity_t source, f_string_quantitys_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_string_quantitys_adjust(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].start = source.start;
    destination->array[destination->used++].total = source.total;

    return F_none;
  }
#endif // _di_f_string_quantitys_append_

#ifndef _di_f_string_quantitys_append_all_
  f_status_t f_string_quantitys_append_all(const f_string_quantitys_t source, f_string_quantitys_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_string_quantitys_append_all(source, destination);
  }
#endif // _di_f_string_quantitys_append_all_

#ifndef _di_f_string_quantitys_decimate_by_
  f_status_t f_string_quantitys_decimate_by(const f_array_length_t amount, f_string_quantitys_t * const quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (quantitys->size - amount > 0) {
      return private_f_string_quantitys_adjust(quantitys->size - amount, quantitys);
    }

    return private_f_string_quantitys_adjust(0, quantitys);
  }
#endif // _di_f_string_quantitys_decimate_by_

#ifndef _di_f_string_quantitys_decrease_by_
  f_status_t f_string_quantitys_decrease_by(const f_array_length_t amount, f_string_quantitys_t * const quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (quantitys->size - amount > 0) {
      return private_f_string_quantitys_resize(quantitys->size - amount, quantitys);
    }

    return private_f_string_quantitys_resize(0, quantitys);
  }
#endif // _di_f_string_quantitys_decrease_by_

#ifndef _di_f_string_quantitys_increase_
  f_status_t f_string_quantitys_increase(const f_array_length_t step, f_string_quantitys_t * const quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && quantitys->used + 1 > quantitys->size) {
      f_array_length_t size = quantitys->used + step;

      if (size > F_array_length_t_size_d) {
        if (quantitys->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_string_quantitys_resize(size, quantitys);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantitys_increase_

#ifndef _di_f_string_quantitys_increase_by_
  f_status_t f_string_quantitys_increase_by(const f_array_length_t amount, f_string_quantitys_t * const quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (quantitys->used + amount > quantitys->size) {
      if (quantitys->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_quantitys_resize(quantitys->used + amount, quantitys);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantitys_increase_by_

#ifndef _di_f_string_quantitys_resize_
  f_status_t f_string_quantitys_resize(const f_array_length_t length, f_string_quantitys_t * const quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_resize(length, quantitys);
  }
#endif // _di_f_string_quantitys_resize_

#ifndef _di_f_string_quantityss_adjust_
  f_status_t f_string_quantityss_adjust(const f_array_length_t length, f_string_quantityss_t * const quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantityss_adjust(length, quantityss);
  }
#endif // _di_f_string_quantityss_adjust_

#ifndef _di_f_string_quantityss_append_
  f_status_t f_string_quantityss_append(const f_string_quantitys_t source, f_string_quantityss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_string_quantityss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_string_quantitys_append_all(source, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // _di_f_string_quantityss_append_

#ifndef _di_f_string_quantityss_append_all_
  f_status_t f_string_quantityss_append_all(const f_string_quantityss_t source, f_string_quantityss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_quantityss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_string_quantitys_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_string_quantityss_append_all_

#ifndef _di_f_string_quantityss_decimate_by_
  f_status_t f_string_quantityss_decimate_by(const f_array_length_t amount, f_string_quantityss_t * const quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (quantityss->size - amount > 0) {
      return private_f_string_quantityss_adjust(quantityss->size - amount, quantityss);
    }

    return private_f_string_quantityss_adjust(0, quantityss);
  }
#endif // _di_f_string_quantityss_decimate_by_

#ifndef _di_f_string_quantityss_decrease_by_
  f_status_t f_string_quantityss_decrease_by(const f_array_length_t amount, f_string_quantityss_t * const quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (quantityss->size - amount > 0) {
      return private_f_string_quantityss_resize(quantityss->size - amount, quantityss);
    }

    return private_f_string_quantityss_resize(0, quantityss);
  }
#endif // _di_f_string_quantityss_decrease_by_

#ifndef _di_f_string_quantityss_increase_
  f_status_t f_string_quantityss_increase(const f_array_length_t step, f_string_quantityss_t * const quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && quantityss->used + 1 > quantityss->size) {
      f_array_length_t size = quantityss->used + step;

      if (size > F_array_length_t_size_d) {
        if (quantityss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_string_quantityss_resize(size, quantityss);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantityss_increase_

#ifndef _di_f_string_quantityss_increase_by_
  f_status_t f_string_quantityss_increase_by(const f_array_length_t amount, f_string_quantityss_t * const quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (quantityss->used + amount > quantityss->size) {
      if (quantityss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_quantityss_resize(quantityss->used + amount, quantityss);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantityss_increase_by_

#ifndef _di_f_string_quantityss_resize_
  f_status_t f_string_quantityss_resize(const f_array_length_t length, f_string_quantityss_t * const quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantityss_resize(length, quantityss);
  }
#endif // _di_f_string_quantityss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

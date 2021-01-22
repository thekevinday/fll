#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_quantitys_adjust_
  f_status_t f_string_quantitys_adjust(const f_array_length_t length, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_adjust(length, quantitys);
  }
#endif // _di_f_string_quantitys_adjust_

#ifndef _di_f_string_quantitys_decimate_by_
  f_status_t f_string_quantitys_decimate_by(const f_array_length_t amount, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->size - amount > 0) {
      return private_f_string_quantitys_adjust(quantitys->size - amount, quantitys);
    }

    return private_f_string_quantitys_adjust(0, quantitys);
  }
#endif // _di_f_string_quantitys_decimate_by_

#ifndef _di_f_string_quantitys_decrease_by_
  f_status_t f_string_quantitys_decrease_by(const f_array_length_t amount, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->size - amount > 0) {
      return private_f_string_quantitys_resize(quantitys->size - amount, quantitys);
    }

    return private_f_string_quantitys_resize(0, quantitys);
  }
#endif // _di_f_string_quantitys_decrease_by_

#ifndef _di_f_string_quantitys_increase_
  f_status_t f_string_quantitys_increase(f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->used + 1 > quantitys->size) {
      f_array_length_t size = quantitys->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (quantitys->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_quantitys_resize(size, quantitys);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantitys_increase_

#ifndef _di_f_string_quantitys_increase_by_
  f_status_t f_string_quantitys_increase_by(const f_array_length_t amount, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantitys->used + amount > quantitys->size) {
      if (quantitys->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_quantitys_resize(quantitys->used + amount, quantitys);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantitys_increase_by_

#ifndef _di_f_string_quantitys_resize_
  f_status_t f_string_quantitys_resize(const f_array_length_t length, f_string_quantitys_t *quantitys) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantitys) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantitys_resize(length, quantitys);
  }
#endif // _di_f_string_quantitys_resize_

#ifndef _di_f_string_quantityss_adjust_
  f_status_t f_string_quantityss_adjust(const f_array_length_t length, f_string_quantityss_t *quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantityss_adjust(length, quantityss);
  }
#endif // _di_f_string_quantityss_adjust_

#ifndef _di_f_string_quantityss_decimate_by_
  f_status_t f_string_quantityss_decimate_by(const f_array_length_t amount, f_string_quantityss_t *quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantityss->size - amount > 0) {
      return private_f_string_quantityss_adjust(quantityss->size - amount, quantityss);
    }

    return private_f_string_quantityss_adjust(0, quantityss);
  }
#endif // _di_f_string_quantityss_decimate_by_

#ifndef _di_f_string_quantityss_decrease_by_
  f_status_t f_string_quantityss_decrease_by(const f_array_length_t amount, f_string_quantityss_t *quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantityss->size - amount > 0) {
      return private_f_string_quantityss_resize(quantityss->size - amount, quantityss);
    }

    return private_f_string_quantityss_resize(0, quantityss);
  }
#endif // _di_f_string_quantityss_decrease_by_

#ifndef _di_f_string_quantityss_increase_
  f_status_t f_string_quantityss_increase(f_string_quantityss_t *quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantityss->used + 1 > quantityss->size) {
      f_array_length_t size = quantityss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (quantityss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_quantityss_resize(size, quantityss);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantityss_increase_

#ifndef _di_f_string_quantityss_increase_by_
  f_status_t f_string_quantityss_increase_by(const f_array_length_t amount, f_string_quantityss_t *quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (quantityss->used + amount > quantityss->size) {
      if (quantityss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_quantityss_resize(quantityss->used + amount, quantityss);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantityss_increase_by_

#ifndef _di_f_string_quantityss_resize_
  f_status_t f_string_quantityss_resize(const f_array_length_t length, f_string_quantityss_t *quantityss) {
    #ifndef _di_level_0_parameter_checking_
      if (!quantityss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantityss_resize(length, quantityss);
  }
#endif // _di_f_string_quantityss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
